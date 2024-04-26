#ifndef __SYNC_H_
#define __SYNC_H_

#define SYNC_CB_NAME_SIZE 32

typedef unsigned int (*extract_fn)(unsigned int index, void *mem,
                                   unsigned int len);
typedef unsigned int (*restore_fn)(unsigned int index, void *mem,
                                   unsigned int len);

enum { EM_SYNC_CB_TYPE1, EM_SYNC_CB_TYPE2, SYNC_CB_NUM };

typedef struct {
  unsigned int reg;
  char name[SYNC_CB_NAME_SIZE];
  unsigned int data_elem_num;
  unsigned int data_elem_size;
  unsigned int mark_count;
  extract_fn extract;
  restore_fn restore;
  unsigned int *bit_map;
} ST_SYNC_CB;

#endif
