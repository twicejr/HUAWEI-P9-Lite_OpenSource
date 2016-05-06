

#ifndef _TEEK_NS_CLIENT_H_
#define _TEEK_NS_CLIENT_H_

#include <linux/mutex.h>
#include <linux/list.h>

#include "teek_client_type.h"
#include "tc_ns_client.h"

//#define TC_DEBUG

#define TC_NS_CLIENT_IOC_MAGIC  't'
#define TC_NS_CLIENT_DEV            "tc_ns_client"
#define TC_NS_CLIENT_DEV_NAME   "/dev/tc_ns_client"

#ifdef TC_DEBUG
#define TCDEBUG(fmt, args...) printk(KERN_INFO "%s(%i, %s): " fmt, \
        __func__, current->pid, current->comm, ## args)
#else
#define TCDEBUG(fmt, args...)
#endif

#ifdef TC_VERBOSE
#define TCVERBOSE(fmt, args...) printk(KERN_DEBUG "%s(%i, %s): " fmt, \
        __func__, current->pid, current->comm, ## args)
#else
#define TCVERBOSE(fmt, args...)
#endif

#define TCERR(fmt, args...) printk(KERN_ERR "%s(%i, %s): " fmt, \
        __func__, current->pid, current->comm, ## args)

#define TC_IPI_DEBUG

#ifdef TC_IPI_DEBUG
#define TC_TIME_DEBUG(fmt, args...) printk(KERN_INFO "%s(%i, %s): " fmt "\n", \
        __func__, current->pid, current->comm, ## args)
#else
#define TC_TIME_DEBUG(fmt, args...)
#endif

#ifdef CONFIG_SECURE_EXTENSION
#define TC_ASYNC_NOTIFY_SUPPORT
#endif

#define EXCEPTION_MEM_SIZE (8*1024)     //mem for exception handling

#define TSP_REQUEST			0xB2000008
#define TSP_RESPONSE			0xB2000009
#define TSP_REE_SIQ			0xB200000A
#define TSP_CRASH			0xB200000B

#define TSP_PREEMPTED		0xB2000005

#define TC_CALL_GLOBAL		0x01
#define TC_CALL_SYNC		0x02
#define TC_CALL_LOGIN           0x04

#define TEE_REQ_FROM_USER_MODE   0x0
#define TEE_REQ_FROM_KERNEL_MODE 0x1


/* Max sizes for login info buffer comming from teecd */
#define MAX_PACKAGE_NAME_LEN 255
/* The apk certificate format is as follows:
 * modulus_size(4bytes) ||modulus buffer(256 bytes) || exponent size(4 bytes) || exponent buffer(1 bytes)
 */
#define MAX_PUBKEY_LEN 512

typedef struct tag_TC_NS_DEV_File{
    unsigned int dev_file_id;
    unsigned int service_cnt;
    unsigned int shared_mem_cnt;
    struct mutex service_lock;
    struct mutex shared_mem_lock;
    struct list_head shared_mem_list;
    struct list_head head;
    struct list_head services_list;
    /* Device is linked to call from kernel */
    uint8_t kernel_api;
/* client login info provided by teecd, can be either package name and public
 * key or uid(for non android services/daemons) */
/* login information can only be set once, dont' allow subsequent calls */
    bool login_setup;
    uint32_t pkg_name_len;
    uint8_t pkg_name[MAX_PACKAGE_NAME_LEN];
    uint32_t pub_key_len;
    uint8_t pub_key[MAX_PUBKEY_LEN];
    int load_app_flag;
} TC_NS_DEV_File;

typedef union
{
    struct
    {
        unsigned int buffer;
        unsigned int size;
    } memref;
    struct
    {
        unsigned int a;
        unsigned int b;
    } value;
} TC_NS_Parameter;

typedef struct tag_TC_NS_Login{
    unsigned int method;
    unsigned int mdata;
} TC_NS_Login;

typedef struct tag_TC_NS_Operation{
    unsigned int    paramTypes;
    TC_NS_Parameter params[4];
} TC_NS_Operation;

typedef struct tag_TC_NS_Temp_Buf{
    void *temp_buffer;
    unsigned int size;
} TC_NS_Temp_Buf;

typedef struct __attribute__ ((__packed__)) tag_TC_NS_SMC_CMD{
    unsigned int    uuid_phys;
    unsigned int    cmd_id;
    unsigned int    dev_file_id;
    unsigned int    context_id;
    unsigned int    agent_id;
    unsigned int    operation_phys;
    unsigned int    login_method;
    unsigned int    login_data;
    unsigned int    err_origin;
    unsigned int    ret_val;
    unsigned int    event_nr;
    unsigned int    remap;
    unsigned int    uid;
    bool    started;
} TC_NS_SMC_CMD;

typedef struct tag_TC_NS_Shared_MEM{
    void*           kernel_addr;
    void*           user_addr;
    unsigned int    len;
    struct list_head head;
} TC_NS_Shared_MEM;



typedef struct tag_TC_NS_Service{
    unsigned char uuid[16];
    struct mutex session_lock;
    struct list_head head;
    struct list_head session_list;
} TC_NS_Service;

/**
 * @brief
 */
struct TC_wait_data {
    wait_queue_head_t send_cmd_wq;
    int               send_wait_flag;
};

typedef struct tag_TC_NS_Session{
    unsigned int session_id;
    struct list_head head;
    struct TC_wait_data wait_data;
    struct mutex ta_session_lock;
} TC_NS_Session;


TC_NS_Service *tc_find_service(struct list_head *services, char *uuid);
TC_NS_Session *tc_find_session(struct list_head *session_list,
					  unsigned int session_id);


int TC_NS_ClientOpen(TC_NS_DEV_File **dev_file, uint8_t kernel_api);
int TC_NS_ClientClose(TC_NS_DEV_File *dev, int flag);
int is_agent_alive(unsigned int agent_id);

int TC_NS_OpenSession(TC_NS_DEV_File *dev_file, TC_NS_ClientContext
				  *context);
int TC_NS_CloseSession(TC_NS_DEV_File *dev_file,
				   TC_NS_ClientContext *context);
int TC_NS_Send_CMD(TC_NS_DEV_File *dev_file, TC_NS_ClientContext *context);


uint32_t TC_NS_get_uid(void);

#endif
