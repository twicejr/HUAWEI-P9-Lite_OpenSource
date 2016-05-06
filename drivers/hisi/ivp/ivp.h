#ifndef _IVP_H_
#define _IVP_H_
//This is used to compat  mmap for Android 32Bit to Kernel 64Bit.
//Must compat with IVP DTS
#define IVP_MMAP_SHIFT         (4)

struct ivp_sect_info {
    char name[64];
    unsigned int index;
    unsigned int len;
    unsigned int ivp_addr;
    unsigned int reserved;
    union {
        unsigned long acpu_addr;
        char compat32[8];
    };
};

#define IVP_IOCTL_SECTCOUNT       _IOR('v', 0x70, unsigned int)
#define IVP_IOCTL_SECTINFO        _IOWR('v', 0x71, struct ivp_sect_info)
#define IVP_IOCTL_DSP_RUN         _IOW('v', 0x72, unsigned int)
#define IVP_IOCTL_DSP_SUSPEND     _IOW('v', 0x73, unsigned int)
#define IVP_IOCTL_DSP_RESUME      _IOW('v', 0x74, unsigned int)
#define IVP_IOCTL_DSP_STOP        _IOW('v', 0x75, unsigned int)
#define IVP_IOCTL_QUERY_RUNSTALL  _IOR('v', 0x76, unsigned int)
#define IVP_IOCTL_QUERY_WAITI     _IOR('v', 0x77, unsigned int)
#define IVP_IOCTL_TRIGGER_NMI     _IOW('v', 0x78, unsigned int)
#define IVP_IOCTL_WATCHDOG        _IOR('v', 0x79, unsigned int)
#define IVP_IOCTL_WATCHDOG_SLEEP        _IOR('v', 0x7a, unsigned int)

#define IVP_IOCTL_SMMU_INVALIDATE_TLB _IOW('v', 0x7b, unsigned int)


#define IVP_IOCTL_IPC_FLUSH_ENABLE    _IOWR('v', 0x89, unsigned int)
#endif /* IVP_H_ */
