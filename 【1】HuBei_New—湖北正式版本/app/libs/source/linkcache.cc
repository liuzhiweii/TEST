#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 

#include "db.h"
#include "linkcache.h"
#include "logm.h"
#include "abn.h"


#define DB_DIR "/data/"
#define DB_PATH DB_DIR"test.db"
#define DB_PATH_M DB_DIR"__db.test.db"



using namespace std;


LinkCache::LinkCache()
{
	m_db = NULL;
    m_dbc =	NULL;
    return;
}


int LinkCache::connectDb()
{
    int ret;
    FILE *errfile;
    DB_ENV *dbenv;
    

    verifyDb();

    //db_env_create(&dbenv, 0);
    //dbenv->log_set_config(dbenv, DB_LOG_AUTO_REMOVE|DB_LOG_IN_MEMORY, 1);
    

    ret = db_create(&m_db, NULL, 0);
    if(ret != 0)
    {
    	logm_err("create db handle fail %d\n", ret);
		abn_debug("create db handle fail %d", ret);
    	return ret;
    }

    ret = m_db->set_heapsize(m_db, 0, 24000000, 0);
    if(ret != 0)
    {
    	logm_err("set db heapsize fail %d\n", ret);
		abn_debug("set db heapsize fail %d\n", ret);
    	m_db->close(m_db, 0);
    	return ret;
    }

    ret = m_db->open(m_db, NULL, DB_PATH, NULL, DB_HEAP, DB_CREATE, 0664);    
	if(ret != 0)
	{
		logm_err("open db fail %d\n", ret);
		remove(DB_PATH);
		ret = m_db->open(m_db, NULL, DB_PATH, NULL, DB_HEAP, DB_CREATE, 0664); 
		if(ret != 0)
		{
			logm_err("open db fail again %d\n", ret);	
			abn_debug("open db fail again %d\n", ret);
			m_db->close(m_db, 0);			
			return ret;
		}
    }
	
	ret = m_db->cursor(m_db, NULL, &m_dbc, 0);
	if(ret != 0)
	{
		logm_err("get db cursor fail %d\n", ret);
		abn_debug("get db cursor fail %d\n", ret);
		m_db->close(m_db, 0);
    	return ret;
	}
	
    return 0;
}

int LinkCache::cacheData(unsigned char *data, unsigned int dataLength)
{
	int ret;
	DBT key;
	DBT value;
    DB_HEAP_RID rid;    

    assert(data);
    assert(m_db);

	memset(&key, 0, sizeof(DBT));
    memset(&value, 0, sizeof(DBT));
    key.data = &rid;
    key.size = key.ulen = sizeof(DB_HEAP_RID);
    key.flags = DB_DBT_USERMEM;
    value.data = data;
    value.size = dataLength;
    value.flags = DB_DBT_USERMEM;

    ret = m_db->put(m_db, NULL, &key, &value, DB_APPEND);
    if(ret == DB_HEAP_FULL)
    {
    	logm_err("db full, put fail!\n");
    	_deleteOldRecord();
    	ret = m_db->put(m_db, NULL, &key, &value, DB_APPEND);
    }
    logm_debug("cacheData ret:%d\n",ret);
	if(0!=m_db->sync(m_db,0))
	{
		logm_debug("sync db failed\n");
		abn_debug("sync db failed");
	}
    return ret;
}

int LinkCache::restoreData(unsigned char *data, unsigned int *dataLength)
{
	int ret;
	DBT key;
	DBT value;

	assert(data);
	assert(dataLength);
    assert(m_db);
    assert(m_dbc);


	memset(&key, 0, sizeof(DBT));
    memset(&value, 0, sizeof(DBT));
    
    ret = m_dbc->get(m_dbc, &key, &value, DB_NEXT);
	
	if(DB_NOTFOUND== ret)
    {
    	logm_err("last record\n", ret);
    	return 1;
    }
    else if(0 != ret)
    {
    	logm_err("get next db item fail %d\n", ret);
		abn_debug("get next db item fail %d\n", ret);
    	return ret;
    }

    memcpy(data, value.data, value.size);
    *dataLength = value.size;
    
	ret = m_dbc->del(m_dbc, 0);
	if(0 != ret)
    {
    	logm_err("del next db item fail %d\n", ret);
		abn_debug("del next db item fail %d\n", ret);
    	return ret;
    }  
	if(0!=m_db->sync(m_db,0))
	{
		logm_debug("sync db failed\n");
		abn_debug("sync db failed");
	}
    logm_debug("restoreData success\n");
	return 0;
}

int LinkCache::getData(unsigned char *data, unsigned int *dataLength)
{
	int ret;
	DBT key;
	DBT value;

	assert(data);
	assert(dataLength);
    assert(m_db);
    assert(m_dbc);


	memset(&key, 0, sizeof(DBT));
    memset(&value, 0, sizeof(DBT));
    
    ret = m_dbc->get(m_dbc, &key, &value, DB_NEXT);
	
	if(DB_NOTFOUND== ret)
    {
    	logm_err("last record\n", ret);
    	return 1;
    }
    else if(0 != ret)
    {
    	logm_err("get next db item fail %d\n", ret);
		abn_debug("get next db item fail %d\n", ret);
    	return ret;
    }

    memcpy(data, value.data, value.size);
    *dataLength = value.size;
    
    logm_debug("getData success\n");
	return 0;
}


int LinkCache::delData()
{
	int ret;
    assert(m_dbc);

	ret = m_dbc->del(m_dbc, 0);
	if(0 != ret)
    {
    	logm_err("del next db item fail %d\n", ret);
		abn_debug("del next db item fail %d\n", ret);
    	return ret;
    }  
	if(0!=m_db->sync(m_db,0))
	{
		logm_debug("sync db failed\n");
		abn_debug("sync db failed");
	}
    logm_debug("del db success\n");
	return 0;
}



void LinkCache::_deleteOldRecord(void)
{
	int ret;
	DBT key;
	DBT value;

	logm_err("_deleteOldRecord\n");

	for(int i=0; i<100; ++i)
	{
		memset(&key, 0, sizeof(DBT));
	    memset(&value, 0, sizeof(DBT));	    
	    ret = m_dbc->get(m_dbc, &key, &value, DB_NEXT);
	    if(0 != ret) 
	    { 
	    	logm_err("get next fail\n");
	    	return;
	    }
		ret = m_dbc->del(m_dbc, 0);
		if(0 != ret) 
		{		
			logm_err("del next fail\n");
			return;
		}

		logm_err("del %d success\n", i);
	}

	return;
}

void LinkCache::verifyDb()
{
	FILE *dbfile;
	DB *dbp;
	int ret;
	FILE *errfile;
	
	remove(DB_PATH_M);
	
	dbfile = fopen(DB_PATH, "r");
	if(NULL == dbfile)
	{
		logm_err("db file not exist\n");
		//abn_debug("db file not exist\n");
		return;
	}
	fclose(dbfile);	


	logm_err("db file exist\n");
	
	ret = db_create(&dbp, NULL, 0);
	if(ret != 0)
	{
		logm_err("create db fail\n");
		abn_debug("create db fail\n");
		return;
	}

	errfile = fopen(DB_DIR"err.log", "w");
	if(NULL == errfile)
	{
		logm_err("open std error fail\n");
		abn_debug("open std error fail\n");
		dbp->close(dbp, 0);
		return;
	}

	logm_err("stderr file exist\n");

	ret = dbp->verify(dbp, DB_PATH, NULL, errfile,0);//DB_SALVAGE
	if(0 != ret)
	{
		logm_err("verify db fail %d\n", ret);
		abn_debug("verify db fail %d\n", ret);
		//remove(DB_PATH);		
		fclose(errfile);
		return;
	}
	fclose(errfile);

	logm_err("verify db success\n");
	return;
	
}


void LinkCache::closeDb(void)
{
	if(NULL!=m_dbc)
	{
		m_dbc->close(m_dbc);
		m_dbc = NULL;
	}
	if(NULL!=m_db)
	{
		m_db->close(m_db, 0);
		m_db = NULL;
	}
	return;
}


void LinkCache::removeDb(void)
{
	/*int ret;
    ret=m_db->remove(m_db, DB_PATH, NULL, 0); 
	if(ret!=0)
	{
		logm_debug("remove db failed ret:%d\n",ret);
	}*/
	remove(DB_PATH);
	return;
}



void LinkCache::checkDbExist(void)
{
	if(access(DB_PATH, F_OK)==0) 
	{
		logm_debug("db file exist\n");
	}
	else
	{
		logm_debug("db file not exist,maybe removed by other thread\n");
		closeDb();
		connectDb();
	}
	return;
}


