/*
 *  Sensor Hub driver
 *
 * Copyright (C) 2012 Huawei, Inc.
 * Author: qindiwen <qindiwen@huawei.com>
 *
 */

#ifndef __LINUX_SENSORHUB_H__
#define __LINUX_SENSORHUB_H__
#include <linux/ioctl.h>

/* ioctl cmd define */
#define SHBIO                         0xB1

#define SHB_IOCTL_APP_ENABLE_SENSOR         _IOW(SHBIO, 0x01, short)
#define SHB_IOCTL_APP_DISABLE_SENSOR        _IOW(SHBIO, 0x02, short)
#define SHB_IOCTL_APP_DELAY_SENSOR          _IOW(SHBIO, 0x03, short)

#define SHB_IOCTL_APP_GET_SENSOR_MCU_MODE   _IOR(SHBIO, 0x51, short)
struct ioctl_para {
    int32_t shbtype;
    union {
        int32_t delay_ms;
        //other cmd para
    };
};
/*
  * Warning notes:
  * The below sensor values  is used by mcu and hal sensorhub module,
  * it must be careful to modify the below values.
  */
enum {
    SENSORHUB_TYPE_BEGIN = 1,
    SENSORHUB_TYPE_ACCELEROMETER = SENSORHUB_TYPE_BEGIN,
    SENSORHUB_TYPE_GYROSCOPE,
    SENSORHUB_TYPE_MAGNETIC,
    SENSORHUB_TYPE_LIGHT,
    SENSORHUB_TYPE_PROXIMITY,
    SENSORHUB_TYPE_ROTATESCREEN,
    SENSORHUB_TYPE_LINEARACCELERATE,
    SENSORHUB_TYPE_GRAVITY,
    SENSORHUB_TYPE_ORIENTATION,
    SENSORHUB_TYPE_ROTATEVECTOR,
    SENSORHUB_TYPE_PRESSURE,
    SENSORHUB_TYPE_TEMPERATURE,
    SENSORHUB_TYPE_RELATIVE_HUMIDITY,
    SENSORHUB_TYPE_AMBIENT_TEMPERATURE,
    SENSORHUB_TYPE_MCU_LABC,
    SENSORHUB_TYPE_HALL,
    SENSORHUB_TYPE_MAGNETIC_FIELD_UNCALIBRATED,
    SENSORHUB_TYPE_GAME_ROTATION_VECTOR,
    SENSORHUB_TYPE_GYROSCOPE_UNCALIBRATED,
    SENSORHUB_TYPE_SIGNIFICANT_MOTION,
    SENSORHUB_TYPE_STEP_DETECTOR,
    SENSORHUB_TYPE_STEP_COUNTER,
    SENSORHUB_TYPE_GEOMAGNETIC_ROTATION_VECTOR,
    SENSORHUB_TYPE_HANDPRESS,
    SENSORHUB_TYPE_CAP_PROX,

    SENSORHUB_TYPE_END
};

/*begin huangwen 20120706*/
extern int getSensorMcuMode(void);
/*end huangwen 20120706*/
extern int set_backlight_brightness(int brightness);
#endif /* __LINUX_SENSORHUB_H__ */
