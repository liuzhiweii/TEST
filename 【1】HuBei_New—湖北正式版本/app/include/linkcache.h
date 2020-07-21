#ifndef __LINKCACHE__
#define __LINKCACHE__
#include "db.h"

#define DB_HEAP_SIZE    20000000

class LinkCache
{
public:
    LinkCache();
    int connectDb();
    int cacheData(unsigned char *data, unsigned int dataLength);
    int restoreData(unsigned char *data, unsigned int *dataLength);
    void closeDb(void);    
	void verifyDb(void);
	int getData(unsigned char *data, unsigned int *dataLength);
	int delData();
	void removeDb();
	void checkDbExist();
private:
	void _deleteOldRecord(void);
	DB *m_db;
    DBC *m_dbc;
};


#endif



