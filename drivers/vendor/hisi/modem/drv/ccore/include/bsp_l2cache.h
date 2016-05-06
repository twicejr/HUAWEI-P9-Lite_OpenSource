

#ifndef __L2CACHE_BALONG_H__
#define __L2CACHE_BALONG_H__

#ifdef CONFIG_BALONG_L2CACHE
void l2cache_HardBootInit(void);
#else

static inline void l2cache_HardBootInit(void)
{   return;}
#endif



#endif


