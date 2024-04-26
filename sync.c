#include "sync.h"
#include "common.h"
#include <stdlib.h>
#include <string.h>

ST_SYNC_CB *g_sync_cb;

void init_sync() {
  int loop;
  ST_SYNC_CB *sync_cb;

  g_sync_cb = (ST_SYNC_CB *)malloc(sizeof(ST_SYNC_CB) * SYNC_CB_NUM);
  if (NULL == g_sync_cb) {
    printf("Fail to alloc memory for g_sync_cb.\n");
    exit(-1);
  }

  for (loop = 0; loop < SYNC_CB_NUM; loop++) {
    sync_cb = &g_sync_cb[loop];

    sync_cb->reg = false;
    memset(sync_cb->name, 0, SYNC_CB_NAME_SIZE);
    sync_cb->bit_map = NULL;
    sync_cb->extract = NULL;
    sync_cb->restore = NULL;
    sync_cb->mark_count = 0;
    sync_cb->data_elem_num = 0;
    sync_cb->data_elem_size = 0;
  }
}

int sync_register(unsigned int type, char *name, unsigned int data_elem_num,
                  unsigned int data_elem_size, restore_fn restore,
                  extract_fn extract) {
  ST_SYNC_CB *sync_cb;
  unsigned int *bit_map;
  int bit_map_num;

  if (NULL == name || '\0' == name[0] || 0 == data_elem_size ||
      0 == data_elem_num || type >= SYNC_CB_NUM) {
    printf("sync_cb_register: Fail to register.\n");
    exit(-1);
  }

  sync_cb = &g_sync_cb[type];
  if (true == sync_cb->reg) {
    printf("sync_cb_register: Fail to register.\n");
    exit(-1);
  }

  bit_map_num = (data_elem_num - 1) / 32 + 1;
  bit_map = (unsigned int *)malloc(sizeof(unsigned int) * bit_map_num);
  if (NULL == bit_map) {
    printf("sync_cb_register: Fail to register.\n");
    exit(-1);
  }
  memset(bit_map, 0, sizeof(unsigned int) * bit_map_num);

  sync_cb->reg = true;
  strncpy(sync_cb->name, name, SYNC_CB_NAME_SIZE);
  sync_cb->bit_map = bit_map;
  sync_cb->data_elem_num = data_elem_num;
  sync_cb->data_elem_size = data_elem_size;
  sync_cb->mark_count = 0;
  sync_cb->restore = restore;
  sync_cb->extract = extract;

  return 0;
}

void sync_mark(unsigned int type, unsigned int index) {
  ST_SYNC_CB *sync_cb;
  unsigned int word_idx, shift_idx;

  if (type >= SYNC_CB_NUM) {
    printf("sync_mark: Fail to mark.\n");
    exit(-1);
  }

  sync_cb = &g_sync_cb[type];
  if (!sync_cb->reg || index > sync_cb->data_elem_num) {
    printf("sync_mark: Fail to mark.\n");
    exit(-1);
  }

  word_idx = index / 32;
  shift_idx = index % 32;

  sync_cb->bit_map[word_idx] |= 1 << shift_idx;
  sync_cb->mark_count++;
}
