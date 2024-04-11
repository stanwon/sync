#include "../../queue.h"

extern ST_PHY_PKG_QUE g_phy_pkg_que;

int main() {
  int loop;
  ST_PHY_PKG phy_pkg[QUE_NUM];
  ST_PHY_PKG *p_phy_pkg;

  init_que();

  for (loop = 0; loop < QUE_NUM-1; loop++) {
    in_que(&phy_pkg[loop]);
  }

  out_que(&p_phy_pkg);

  print_que();
}
