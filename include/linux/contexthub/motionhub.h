
// kernel\include\linux
#ifndef __LINUX_MOTIONHUB_H__
#define __LINUX_MOTIONHUB_H__
#include <linux/ioctl.h>

/* ioctl cmd define */
#define MHBIO                         0xB1

#define MHB_IOCTL_MOTION_START      _IOW(MHBIO, 0x01, short)
#define MHB_IOCTL_MOTION_STOP    _IOW(MHBIO, 0x02, short)
#define MHB_IOCTL_MOTION_ATTR_START      _IOW(MHBIO, 0x03, short)
#define MHB_IOCTL_MOTION_ATTR_STOP    _IOW(MHBIO, 0x04, short)
#define MHB_IOCTL_MOTION_INTERVAL_SET    _IOW(MHBIO, 0x05, short)

/*
  * Warning notes:
  * The below motion values  is used by mcu and hal sensorhub module,
  * the value MOTIONHUB_TYPE_XXX below must be consisted with MOTION_TYPE_XXX
  * of mcu and kernel\drivers\huawei\inputhub\protocol.h.
  */
#define MOTIONHUB_TYPE_PICKUP 0x01
#define MOTIONHUB_TYPE_FLIP 0x02
#define MOTIONHUB_TYPE_PROXIMITY 0x03
#define MOTIONHUB_TYPE_SHAKE 0x04
#define MOTIONHUB_TYPE_TAP 0x05
#define MOTIONHUB_TYPE_TILT 0x06
#define MOTIONHUB_TYPE_ROTATION 0x07
#define MOTIONHUB_TYPE_POCKET 0x08
#define MOTIONHUB_TYPE_ACTIVITY 0x09
#define MOTIONHUB_TYPE_TAKE_OFF 0x0a
#define MOTIONHUB_TYPE_HW_STEP_COUNTER 0x0b
#endif /* __LINUX_MOTIONHUB_H__ */
