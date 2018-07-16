#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>

#define DEBUG       1
#define debug(...) \
            do { if (DEBUG) fprintf(stdout, __VA_ARGS__); } while (0)
                
#endif //   DEBUG_H
