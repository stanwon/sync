#include "common.h"
#include "queue.h"
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
  char *buf = NULL;
  int is_received = false;
  init();
  while (1) {
    sleep(2);
    is_received = out_que((ST_PHY_PKG **)&buf);

    if (!is_received) {
      continue;
    }

    if (NULL != buf) {
      printf("%s\n", buf);
      free(buf);
    }
  }
  close(s);
  exit(0);
}
