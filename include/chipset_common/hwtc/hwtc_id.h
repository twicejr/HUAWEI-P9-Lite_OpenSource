


#ifndef __HWTC_ID_H__
#define __HWTC_ID_H__ 

/* this value must be kept in sync with MAX_ENTRY_COUNT in kernel/drivers/hwtc/hwtc.h */
#define HWTC_TABLE_SIZE                             500

#define HWTC_LOW_TABLE_SIZE                         HWTC_TABLE_SIZE
#define HWTC_SUPER_TABLE_SIZE                       HWTC_TABLE_SIZE

/* In huawei trace counter low level table, 
 * 80% entry is used for hal and framework layer,
 * 20% entry is used for kernel layer.
 */
#define HWTC_LID_END                                 (0x10000000 + HWTC_LOW_TABLE_SIZE*8/10)
#define HWTC_KLID_START                              (HWTC_LID_END + 1)
#define HWTC_KLID_END                                (0x10000000 + HWTC_LOW_TABLE_SIZE)

#define HWTC_SLID_START                              (0x30000000)
#define HWTC_SLID_END                                (0x30000000 + HWTC_SUPER_TABLE_SIZE)

enum HWTC_low_table_id_type {
    HWTC_KLID_CAMERA_START                            = HWTC_KLID_START,
    HWTC_KLID_CAMERA_START_STREAMING                  = HWTC_KLID_CAMERA_START,
    HWTC_KLID_CAMERA_STOP_STREAMING,


    HWTC_KLID_LCD_START,
    /* TODO */


    /* TODO OTHER MODULE */



    /* The HWTC_KLID_LAST id is last id, please add id behind it. */
    HWTC_KLID_LAST
};

#endif /* __HWTC_ID_H__ */
