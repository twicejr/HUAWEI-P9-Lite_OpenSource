#ifndef __ANC_HS_INTERFACE__
#define __ANC_HS_INTERFACE__

enum {
    ANC_HS_NORMAL_4POLE    = 0,
    ANC_HS_NORMAL_3POLE,
    ANC_HS_HEADSET,
    ANC_HS_REVERT_4POLE,
    ANC_HS_NONE,
};

#define ANC_HS_ENABLE_CHARGE 0
#define ANC_HS_DISABLE_CHARGE 1

#define ANC_HS_ENABLE_5VOLTATE 1
#define ANC_HS_DISABLE_5VOLTATE 0

/*IO controls for user*/
#define IOCTL_ANC_HS_CHARGE_ENABLE_CMD          _IO('A', 0x01)
#define IOCTL_ANC_HS_CHARGE_DISABLE_CMD         _IO('A', 0x02)
#define IOCTL_ANC_HS_GET_CHARGE_STATUS_CMD               _IOR('A', 0xFF, __u32)
#define IOCTL_ANC_HS_GET_HEADSET_CMD            _IOR('A', 0xFE, __u32)
#define IOCTL_ANC_HS_GET_VBST_5VOLTAGE_CMD            _IOR('A', 0xFD, __u32)
#define IOCTL_ANC_HS_GET_VDD_BUCK_VOLTAGE_CMD            _IOR('A', 0xFC, __u32)
#define IOCTL_ANC_HS_GET_HEADSET_RESISTANCE_CMD            _IOR('A', 0xFB, __u32)

enum {
    NO_MAX14744,
    HANDSET_PLUG_IN,
    HANDSET_PLUG_OUT,
};

enum {
    ANC_HS_MIC_GND_DISCONNECT        = 0,
    ANC_HS_MIC_GND_CONNECT           = 1,
};

/* codec operate used by anc_hs driver*/
struct anc_hs_codec_ops {
    bool (*check_headset_in)(void *);
    void (*btn_report)(int, int);
    void (*codec_resume_lock)(void *, bool);
    void (*plug_in_detect)(void *);
    void (*plug_out_detect)(void *);
};

struct anc_hs_dev{
    char *name;
    struct anc_hs_codec_ops ops;
};

struct anc_hs_ops {
    int (*anc_hs_dev_register)(struct anc_hs_dev *dev, void * codec_data);
    int (*anc_hs_check_headset_pluged_in)(void);
    void (*anc_hs_start_charge)(void);
    void (*anc_hs_charge_detect)(int saradc_value, int headset_type);
    void (*anc_hs_stop_charge)(void);
    void (*anc_hs_force_charge)(int disable);
    bool (*check_anc_hs_support)(void);
    void (*anc_hs_5v_control)(int enable);
    bool (*anc_hs_plug_enable)(void);
    void (*anc_hs_invert_hs_control)(int);
    void (*anc_hs_refresh_headset_type)(int);
};

int anc_hs_interface_dev_register(struct anc_hs_dev *dev, void * codec_data);

int anc_hs_interface_check_headset_pluged_in(void);

void anc_hs_interface_start_charge(void);

void anc_hs_interface_charge_detect(int saradc_value, int headset_type);

void anc_hs_interface_stop_charge(void);

void anc_hs_interface_force_charge(int disable);

bool check_anc_hs_interface_support(void);

int anc_hs_ops_register(struct anc_hs_ops *ops);

void anc_hs_interface_5v_control(int enable);

bool anc_hs_interface_plug_enable(void);

void anc_hs_interface_invert_hs_control(int connect);

void anc_hs_interface_refresh_headset_type(int headset_type);

#endif
