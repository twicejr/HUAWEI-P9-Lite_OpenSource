

#ifndef _LOAD_IMAGE_H_
#define _LOAD_IMAGE_H_
#include <global_ddr_map.h>
#ifdef __cplusplus 
extern "C"
{
#endif

/*new struct for new platform*/
struct load_image_info {
	unsigned int ecoretype;
	unsigned int image_addr;
	unsigned int image_size;
	char *partion_name;
};

/*new func for new platform*/
int bsp_load_and_verify_image(struct load_image_info *img_info);

#define PTN_VRL_NAME               	"vrl"
#define PTN_MODEM_NAME			    "modem"
#define PTN_HIFI_NAME			    "fw_hifi"
#define PTN_MODEM_DSP_NAME			"modem_dsp"
#define PTN_MODEM_XDSP_NAME			"modem_dsp"
#define PTN_MODEM_DTB_NAME			"modem_dtb"
#define HIFI_RUN_ADDR               (HISI_RESERVED_HIFI_DATA_PHYMEM_BASE + 0x3CE000)
#define DDR_TLPHY_IMAGE_ADDR		(HISI_RESERVED_MODEM_PHYMEM_BASE + 0x100000)
#define DDR_MCORE_DTS_ADDR			(HISI_RESERVED_MODEM_PHYMEM_BASE + 0x6200000)

#define sec_print_err(fmt, ...)    (printk(KERN_ERR "[sec]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define sec_print_info(fmt, ...)   (printk(KERN_INFO "[sec]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define SEC_OK      			(0)
#define SEC_ERROR  				(-1)
#define SEC_FILE_NO_EXSIT		(-2)

#define VRL_SIZE					(0x1000)  /*VRL 4K*/
#define HIFI_SEC_MAX_NUM            32

#define BSP_RESET_NOTIFY_REPLY_OK 		   0
#define BSP_RESET_NOTIFY_SEND_FAILED      -1
#define BSP_RESET_NOTIFY_TIMEOUT          -2

typedef enum {
	BSP_CCORE = 0,
	BSP_HIFI,
	BSP_LPM3,
	BSP_BBE,
	BSP_CDSP,
	BSP_CCORE_TAS,
	BSP_CCORE_WAS,
	BSP_CCORE_CAS,
	BSP_BUTT
} BSP_CORE_TYPE_E;

struct image_head
{
	char image_name[16];
	char image_version[32];

	unsigned int image_index;
	unsigned int image_length;
	unsigned int load_addr;
	unsigned int crc;
	unsigned int is_sec;

	char reserved[128 - 16 - 32 -sizeof(unsigned int) * 5];
};

struct dsp_sect_desc_stru{
	unsigned short             	  usNo;
	unsigned char                 ucTcmType;
	unsigned char                 ucLoadType;
	unsigned int                  ulFileOffset;
	unsigned int                  ulTargetAddr;
	unsigned int                  ulSectSize;
};

struct dsp_bin_header_stru{
	char                          acDescription[24];
	unsigned int                  ulFileSize;
	unsigned int                  ulSectNum;
	struct dsp_sect_desc_stru     astSect[0];
};

struct drv_hifi_image_sec {
	unsigned short						sn;
	unsigned char						type;
	unsigned char						load_attib;
	unsigned int						src_offset;
	unsigned int						des_addr;
	unsigned int						size;
};

struct drv_hifi_image_head {
	char								time_stamp[24];
	unsigned int						image_size;
	unsigned int						sections_num;
	struct drv_hifi_image_sec			sections[HIFI_SEC_MAX_NUM];
};

int bsp_reset_request(BSP_CORE_TYPE_E ecoretype);
int bsp_reset_loadimage(BSP_CORE_TYPE_E ecoretype);
int bsp_image_seccheck(BSP_CORE_TYPE_E ecoretype);
int bsp_reset_core_notify(BSP_CORE_TYPE_E ecoretype, unsigned int cmdtype, unsigned int timeout_ms, unsigned int *retval);

#ifdef __cplusplus
}
#endif
#endif

