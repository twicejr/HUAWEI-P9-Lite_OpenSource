#ifndef POST_FS_DATA_H
#define POST_FS_DATA_H

int wait_for_postfsdata(unsigned int timeout);
unsigned int get_postfsdata_flag(void);
void set_postfsdata_flag(int value);

#endif
