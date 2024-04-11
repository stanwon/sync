#include <fcntl.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 50005

int s;

int main() {
  struct sockaddr_in server_addr;
  char recv_buf[2048];

  // create socket
  s = socket(AF_INET, SOCK_DGRAM, 0);
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(0);
  server_addr.sin_port = htons(PORT);

  while (1) {
    sendto(s, "test", sizeof("test"), 0, (struct sockaddr *)&server_addr, (socklen_t)sizeof(server_addr));
    sleep(1);
  }

  return 0;
}

