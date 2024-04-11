#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

ST_PHY_PKG_QUE g_phy_pkg_que;

void init_que() {
  int loop;

  g_phy_pkg_que.out = 0;
  g_phy_pkg_que.in = 0;
  for (loop = 0; loop < QUE_NUM; loop++) {
    g_phy_pkg_que.phy_pkg[0] = NULL;
  }
}

void in_que(ST_PHY_PKG *p_pkg) {
  if (NULL == p_pkg) {
    printf("Null pointer.\n");
    return;
  }

  if ((g_phy_pkg_que.in + 1) % QUE_NUM == g_phy_pkg_que.out) {
    printf("Full.\n");
    // free(p_pkg);
    return;
  }

  g_phy_pkg_que.phy_pkg[g_phy_pkg_que.in] = p_pkg;
  g_phy_pkg_que.in = (g_phy_pkg_que.in + 1) % QUE_NUM;
}

bool out_que(ST_PHY_PKG **pp_pkg) {
  if (g_phy_pkg_que.in == g_phy_pkg_que.out) {
    printf("Empty.\n");
    return false;
  }

  *pp_pkg = g_phy_pkg_que.phy_pkg[g_phy_pkg_que.out];
  g_phy_pkg_que.phy_pkg[g_phy_pkg_que.out] = NULL;
  g_phy_pkg_que.out = (g_phy_pkg_que.out + 1) % QUE_NUM;
  return true;
}

void print_que() {
  printf("in: %u\n", g_phy_pkg_que.in);
  printf("out: %u\n", g_phy_pkg_que.out);
}
