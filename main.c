#include <fcntl.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include "common.h"

#define PORT 50005

int s;

void *recv_task() {
  int rc;
  int flags;
  int max_fd;
  fd_set set;
  int buf_size = 96 * 1024;
  struct sockaddr_in listen_addr;
  struct sockaddr_in client_addr;
  int client_addr_len;
  int recv_len;
  char recv_buf[2048];

  // create socket
  s = socket(AF_INET, SOCK_DGRAM, 0);
  listen_addr.sin_family = AF_INET;
  listen_addr.sin_addr.s_addr = htonl(0);
  listen_addr.sin_port = htons(PORT);
  // bind address
  if (0 > bind(s, (struct sockaddr *)&listen_addr, sizeof(listen_addr))) {
    printf("Fail to bind.\n");
    exit(-1);
  }

  // set flags and options
  flags = fcntl(s, F_GETFL, 0);
  fcntl(s, F_SETFL, flags | O_NONBLOCK);
  setsockopt(s, SOL_SOCKET, SO_SNDBUF, (void *)&buf_size, sizeof(buf_size));
  setsockopt(s, SOL_SOCKET, SO_RCVBUF, (void *)&buf_size, sizeof(buf_size));

  // put socket to listening set
  FD_ZERO(&set);
  FD_SET(s, &set);
  max_fd = s + 1;
  while (1) {
    // select available socket
    rc = select(max_fd, &set, NULL, NULL, NULL);
    if (0 > rc) {
      continue;
    }
    if (!FD_ISSET(s, &set)) {
      continue;
    }
    client_addr_len = sizeof(client_addr);

    if (0 > (recv_len =
                 recvfrom(s, recv_buf, 2048, 0, (struct sockaddr *)&client_addr,
                          (socklen_t *)&client_addr_len))) {
      printf("Fail to receive data from socket.\n");
      exit(-1);
    }

    printf("%s\n", recv_buf);
  }

  return NULL;
}

void init() {
  pthread_t tid;
  if (0 != pthread_create(&tid, NULL, recv_task, NULL)) {
    printf("Fail to create recv_task.\n");
    exit(-1);
  }
}

int main() {
  init();
  while (1) {
  }
  close(s);
  exit(0);
}
