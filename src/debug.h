#ifndef __DEBUG_H
#define __DEBUG_H

//#include <stdarg.h>
#include <stdio.h>

#define debug(fmt, ...) \
        do { if (DEBUG) fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
                                __LINE__, __func__, ##__VA_ARGS__); } while (0)


#endif /*__DEBUG_H*/
