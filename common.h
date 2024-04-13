#ifndef __COMMON_H_
#define __COMMON_H_

#include "queue.h"
#include <fcntl.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_LEN 2048
#define PORT 50005

extern int s;

#endif
