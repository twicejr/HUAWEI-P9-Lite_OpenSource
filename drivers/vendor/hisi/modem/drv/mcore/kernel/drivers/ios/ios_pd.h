#ifndef _IOS_PD_H_
#define _IOS_PD_H_


void gpio_suspend(void);
void gpio_resume(void);

void ios_init(void);
void ios_suspend(void);
void ios_resume(void);

#endif