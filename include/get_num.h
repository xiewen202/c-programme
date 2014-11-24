#ifndef GET_NUM.H
#define GET_NUM.H

#define GN_NONNEG 01 //vale must be >= 0
#define GN_GT_0   02 //vale must be > 0

#define GN_ANNY_BASE 0100
#define GN_BASE_8    0200
#define GN_BASE_16   0400

long getLong(const char *arg,int flags,const char *name);
long getInt(const char *arg,int flags,const char *name);

#endif //GET_NUM.H
