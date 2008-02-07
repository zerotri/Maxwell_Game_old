#ifndef UTILS_H
#define UTILS_H
#ifndef NULL
#define NULL 0
#endif
#ifdef TIME_USE_FLOATS
    typedef float time_type;
    #define SECONDS(x) ((time_type)x)
    #define MILLISECONDS(x) (((time_type)x)*0.01f)
#else
    typedef unsigned int time_type;
    #define SECONDS(x) ((time_type)x*1000)
    #define MILLISECONDS(x) (((time_type)x)*10)
#endif
#define SET_XY(__name, __x, __y) __name.x = (__x); __name.y = (__y)
#define SET_TXY(__name, __x, __y) __name.tx = (__x); __name.ty = (__y)
#define SET_TLBR(__name, __t, __l, __b, __r)	__name.uTop = (__t);\
												__name.uLeft = (__l);\
												__name.uBottom = (__b);\
												__name.uRight = (__r)
#define LONGLONGUNSIGNED(x) x##LLU
#define LONGLONGSIGNED(x) x##LL
void Log(char* format,...);

#endif
