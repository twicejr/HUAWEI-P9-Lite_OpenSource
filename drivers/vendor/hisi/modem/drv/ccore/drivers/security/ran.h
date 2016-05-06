#ifndef RAN_H
#define RAN_H
#include "security_types.h"

u_long bsp_random(void);
void bsp_srandom(u_long seed);

#endif /* RAN_H */

