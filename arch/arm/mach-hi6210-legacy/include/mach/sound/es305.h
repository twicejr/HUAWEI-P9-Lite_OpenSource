#ifndef AUDIENCE_ES305_H
#define AUDIENCE_ES305_H

#include <linux/ioctl.h>

#define ES305_NAME  "audience_es305"

#define ENABLE_DIAG_IOCTLS 1

struct es305_platform_data {
    uint32_t gpio_es305_wakeup;
    uint32_t gpio_es305_reset;
};

struct es305_img {
    unsigned char *buf;
    unsigned img_size;
};

/* path ids */
/* FIX ME */
enum ES305_PATHID {
    ES305_PATH_SUSPEND,             /* */
    ES305_PATH_INCALL_RECEIVER,     /* */
    ES305_PATH_INCALL_HEADSET,
    ES305_PATH_INCALL_SPEAKER,
    ES305_PATH_INCALL_BT,
    ES305_PATH_VR_NO_NS_RECEIVER,
    ES305_PATH_VR_NO_NS_HEADSET,
    ES305_PATH_VR_NO_NS_SPEAKER,
    ES305_PATH_VR_NO_NS_BT,
    ES305_PATH_VR_NS_RECEIVER,
    ES305_PATH_VR_NS_HEADSET,
    ES305_PATH_VR_NS_SPEAKER,
    ES305_PATH_VR_NS_BT,
    ES305_PATH_RECORD_RECEIVER,
    ES305_PATH_RECORD_HEADSET,
    ES305_PATH_RECORD_SPEAKER,
    ES305_PATH_RECORD_BT,
    ES305_PATH_CAMCORDER
};

/* noise suppression states */
enum ES305_NS_STATES {
    ES305_NS_STATE_AUTO,    /* leave mode as selected by driver */
    ES305_NS_STATE_OFF,     /* disable noise suppression */
    ES305_NS_STATE_CT,      /* force close talk mode */
    ES305_NS_STATE_FT,      /* force far talk mode */
    ES305_NS_NUM_STATES
};

/* max size of firmware */
#define ES305_MAX_FW_SIZE ( 100 * 1024 ) /* 100K */

/* IOCTLs for Audience ES305 */
#define ES305_IOCTL_MAGIC 'u'

#define ES305_BOOTUP_INIT  _IOW(ES305_IOCTL_MAGIC, 0x01, struct es305_img *)
#define ES305_SET_PATHID   _IOW(ES305_IOCTL_MAGIC, 0x02, enum ES305_PATHID)
#define ES305_SET_NS_STATE _IOW(ES305_IOCTL_MAGIC, 0x03, enum ES305_NS_STATES)
#define ES305_SET_SLEEP    _IOW(ES305_IOCTL_MAGIC, 0x04, unsigned)
/* For Diag */
#define ES305_READ_DATA    _IOR(ES305_IOCTL_MAGIC, 0x10, unsigned)
#define ES305_WRITE_MSG    _IOW(ES305_IOCTL_MAGIC, 0x11, unsigned)

/* commands */
/* sync polling mode */
#define AUDIENCE_MSG_SYNC               ( 0x80000000 )
#define AUDIENCE_MSG_SLEEP_SYNC         ( 0x80000001 )

/* sleep mode */
#define AUDIENCE_MSG_SLEEP_MODE         ( 0x80100001 )

/* reset */
#define AUDIENCE_MSG_RESET_IMMEDIATE    ( 0x80020000 )
#define AUDIENCE_MSG_RESET_DELAYED      ( 0x80020001 )

/* bootload initiate */
#define AUDIENCE_MSG_BOOTLOADINITIATE   ( 0x80030000 )

#define AUDIENCE_MSG_BOOT_BYTE1         ( 0x00 )
#define AUDIENCE_MSG_BOOT_BYTE2         ( 0x01 )
#define AUDIENCE_MSG_BOOT_ACK           ( 0x01 )

/******************************************************************************/
/* device parameter */
#define AUDIENCE_MSG_GETDEVICEPARM      ( 0x800B )
#define AUDIENCE_MSG_SETDEVICEPARMID    ( 0x800C )
#define AUDIENCE_MSG_SETDEVICEPARM      ( 0x800D )

/* port ids */
#define AUDIENCE_PORT_A                 ( 0x0A )
#define AUDIENCE_PORT_B                 ( 0x0B )
#define AUDIENCE_PORT_C                 ( 0x0C )
#define AUDIENCE_PORT_D                 ( 0x0D )

/* parameters */
#define WORD_LENGTH                     ( 0x00 )
#define DEL_FROM_FS_TX                  ( 0x02 )
#define DEL_FROM_FS_RX                  ( 0x03 )
#define LATCH_EDGE                      ( 0x04 )
#define ENDIANNESS                      ( 0x05 )
#define TRISTATE                        ( 0x06 )
#define PORT_MODE                       ( 0x07 )

/* parameters values */
#define WORDLENGTH_16BIT                ( 0x0F ) /* default */
#define WORDLENGTH_24BIT                ( 0x17 )

#define LATCH_EDGE_TX_F_RX_R            ( 0x00 )
#define LATCH_EDGE_TX_R_RX_F            ( 0x03 ) /* default */

#define ENDIANNESS_LITTLE               ( 0x00 )
#define ENDIANNESS_BIG                  ( 0x01 ) /* default */

#define TRISTATE_DISABLE                ( 0x00 ) /* default */
#define TRISTATE_ENABLE                 ( 0x01 )

/* algorithm algorithmmeter */
#define AUDIENCE_MSG_GETALGORITHMPARM   ( 0x8016 )
#define AUDIENCE_MSG_SETALGORITHMPARMID ( 0x8017 )
#define AUDIENCE_MSG_SETALGORITHMPARM   ( 0x8018 )
/******************************************************************************/

/* general definitions */
#define AUDIENCE_RESET_STABLE_TIME      ( 1 ) /* ms / keep 4 cycles in clk */
#define AUDIENCE_POLLING_TIME           ( 20 ) /* ms */
#define AUDIENCE_WAKEUP_TIME            ( 30 ) /* ms */
#define AUDIENCE_SW_RESET_TIME          ( 20 ) /* ms */
#define AUDIENCE_I2C_ACCESS_DELAY_TIME  ( 50 ) /* ms */
#define AUDIENCE_BOOT_ACK_TIME          ( 1  ) /* ms */
#define AUDIENCE_BOOT_SYNC_TIME         ( 120 ) /* ms */
#define AUDIENCE_SLEEP_TIME             ( 20 ) /* ms */
#define AUDIENCE_ACK_ERROR              ( 0xFF )
#define AUDIENCE_ACK_NONE               ( 0x00 )

#define RETRY_TIMES                     ( 5 )
#define POLLING_RETRY_TIMES             ( 3 )
#define ES305_CMD_FIFO_DEPTH            ( 128 )

/* return value */
#define AUDIENCE_SW_RESET_OK            ( 1 )
#define AUDIENCE_SW_RESET_ERROR         ( 2 )

#endif //AUDIENCE_ES305_H