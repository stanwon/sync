#ifndef __QUEUE_H_
#define __QUEUE_H_

#include <stdbool.h>

#define MAC_ADDR_LEN 6
#define QUE_NUM 1023

typedef struct {
  unsigned char dst_addr[MAC_ADDR_LEN];
  unsigned char src_addr[MAC_ADDR_LEN];
  unsigned short frame_type;
  unsigned short payload_len;
  unsigned int msg_code;
  unsigned int pkg_num;
  unsigned char payload[4];
} ST_PHY_PKG;

typedef struct{
  unsigned short in;
  unsigned short out;
  ST_PHY_PKG *phy_pkg[QUE_NUM];
}ST_PHY_PKG_QUE;


void init_que();
void in_que(ST_PHY_PKG *p_pkg);
bool out_que(ST_PHY_PKG **p_pkg);
void print_que();

#endif
