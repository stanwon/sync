#include "common.h"
#include "recv.h"

int s;

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
