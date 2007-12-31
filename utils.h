#ifndef UTILS_H
#define UTILS_H
#include <hge.h>
#define SET_XY(__name, __x, __y) __name.x = (__x); __name.y = (__y)
#define SET_TXY(__name, __x, __y) __name.tx = (__x); __name.ty = (__y)
#define SET_TLBR(__name, __t, __l, __b, __r)	__name.uTop = (__t);\
												__name.uLeft = (__l);\
												__name.uBottom = (__b);\
												__name.uRight = (__r)
#define HWCOL(__col) (__col.GetHWColor())


#endif
