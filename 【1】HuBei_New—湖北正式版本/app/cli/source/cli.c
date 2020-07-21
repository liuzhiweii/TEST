/**
 * \file     test_parser.c
 * \brief    Test program for parser library. 
 * \details  This is a test program with a simple CLI that serves as a demo 
 *           as well.
 * \version  \verbatim $Id: test_parser.c 159 2011-10-29 09:29:58Z henry $ \endverbatim
 */
/*
 * Copyright (c) 2008-2009, 2011, Henry Kwok
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the project nor the names of its contributors
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY HENRY KWOK ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL HENRY KWOK BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "cparser.h"
#include "cparser_priv.h"
#include "cparser_token.h"
#include "cparser_tree.h"
#include "zmq.h"
#include "cli.h"

void *ctx=NULL;
void *req_socket_cfg=NULL;
void *req_socket_vmm=NULL;


/** Zeroize a data structure */
#define BZERO_OUTPUT memset(output, 0, sizeof(output)); output_ptr = output

extern char output[2000], *output_ptr;
extern int interactive;
int num_passed = 0, num_failed =0;

/**
 * Feed a string into the parser (skipping line buffering) 
 */
static void
feed_parser (cparser_t *parser, const char *str)
{
    int m, n;
    m = strlen(str);
    for (n = 0; n < m; n++) {
        cparser_input(parser, str[n], CPARSER_CHAR_REGULAR);
    }
}

/**
 * Update pass/fail counters and display a status string 
 */
static void
update_result (char *got, const char *expected, const char *test)
{
    int failed, n;

    failed = strcmp(got, expected);
    if (failed) {
        for (n = 0; n < strlen(expected); n++) {
            if (got[n] != expected[n]) {
                printf("Index %d: expected=%c  got=%c\n", n, expected[n], 
                       got[n]);
            }
        }
    }
    if (!failed) {
        printf("\nPASS: %s\n", test);
        num_passed++;
    } else {
        printf("\nFAIL: %s\n", test);
        num_failed++;
    }
    fflush(stdout);
}

static void
test_printc (const cparser_t *parser, const char ch)
{
    output_ptr += sprintf(output_ptr, "%c", ch);
}

static void
test_prints (const cparser_t *parser, const char *s)
{
    output_ptr += sprintf(output_ptr, "%s", s);
}
void set_zmq_socket_option(void *socket,int type,int value)
{
    int rc=0;
    rc =zmq_setsockopt(socket,type,&value,sizeof(int));
    CHECK_FAIL_NUMBER(rc,"zmq_setsockopt fail");
}
void set_zmq_tcp_socket_option(void *socket,int time_out)
{
	set_zmq_socket_option(socket,ZMQ_RCVTIMEO,time_out);
	set_zmq_socket_option(socket,ZMQ_SNDTIMEO,time_out);
    set_zmq_socket_option(socket,ZMQ_LINGER,0);
    set_zmq_socket_option(socket,ZMQ_TCP_KEEPALIVE,1);
    set_zmq_socket_option(socket,ZMQ_TCP_KEEPALIVE_CNT,2);
    set_zmq_socket_option(socket,ZMQ_TCP_KEEPALIVE_IDLE,1);
    set_zmq_socket_option(socket,ZMQ_TCP_KEEPALIVE_INTVL,1);
}

/*创建cfg 消息队列*/
void *create_zmq_cfg_sockets(void *ctx)
{
    int value;
    int ret;
	void *socket;


    socket = zmq_socket(ctx, ZMQ_REQ);
    if(NULL == socket)
    {
        printf("zmq_socket cfg failed\n");
        exit(-1);
    }
    
    
    set_zmq_tcp_socket_option(socket,2000);

    ret = zmq_connect(socket, "tcp://127.0.0.1:5504");
    if(ret < 0)
    {
        printf("connect tcp_req_socket cfg fail\n");
        return -1;
    }
    return socket;
}

/*创建vmm消息队列*/
void *create_zmq_vmm_sockets(void *ctx)
{
    int value;
    int ret;
	void *socket;


    socket = zmq_socket(ctx, ZMQ_REQ);
    if(NULL == socket)
    {
        printf("zmq_socket vmm failed\n");
        exit(-1);
    }
    
    
    set_zmq_tcp_socket_option(socket,2000);

    ret = zmq_connect(socket, "tcp://127.0.0.1:5503");
    if(ret < 0)
    {
        printf("connect tcp_req_socket vmm fail\n");
        return -1;
        //exit(-1);
    }
    return socket;
}


/*创建消息队列*/
void create_zmq_sockets()
{
    int value;
    int ret;

    ctx = zmq_init (1);
    if(NULL == ctx)
    {
        printf("create context fail!\n");
        exit(-1);
    }

    req_socket_cfg=create_zmq_cfg_sockets(ctx);
	req_socket_vmm=create_zmq_vmm_sockets(ctx);
    return;
}





/**
 * \brief    Entry point of the program.
 *
 * \param    argc Number of arguments.
 * \param    argv An array of argument strings.
 *
 * \return   Return 0.
 */
int
main (int argc, char *argv[])
{
    cparser_t parser;
    char *config_file = NULL;
    int ch, debug = 0, n;
    cparser_result_t rc;

    create_zmq_sockets();

    memset(&parser, 0, sizeof(parser));

    #if 0
    while (-1 != (ch = getopt(argc, argv, "pic:d"))) {
        switch (ch) {
            case 'p':
                printf("pid = %d\n", getpid());
                break;
            case 'i':
                interactive = 1;
                break;
            case 'c':
                config_file = optarg;
                break;
            case 'd':
                debug = 1;
                break;
        }
    }
    #endif

    interactive = 1;

    parser.cfg.root = &cparser_root;
    parser.cfg.ch_complete = '\t';
    /* 
     * Instead of making sure the terminal setting of the target and 
     * the host are the same. ch_erase and ch_del both are treated
     * as backspace.
     */
    parser.cfg.ch_erase = '\b';
    parser.cfg.ch_del = 127;
    parser.cfg.ch_help = '?';
    parser.cfg.flags = (debug ? CPARSER_FLAGS_DEBUG : 0);
    strcpy(parser.cfg.prompt, "cli# ");
    parser.cfg.fd = STDOUT_FILENO;
    cparser_io_config(&parser);

    if (CPARSER_OK != cparser_init(&parser.cfg, &parser)) {
        printf("Fail to initialize parser.\r\n");
	return -1;
    }
    if (interactive) {
        if (config_file) {
            (void)cparser_load_cmd(&parser, config_file);
        }
        cparser_run(&parser);
    } else {
        printf("not support\r\n");
    }
    return 0;
}
