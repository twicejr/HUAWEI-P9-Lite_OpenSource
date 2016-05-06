#ifndef _PWRCTRL_MULTI_MCA_H
#define _PWRCTRL_MULTI_MCA_H

#include <linux/hisi/pm/pwrctrl_multi_def.h>

#define MCA_UDATA_REQ_SIZE              (16)
#define MCA_UDATA_RSP_SIZE              (8)

#define MCA_UDATA_REQ_NAME_SIZE              (16)


typedef enum
{
    MCA_SESSION_SYNC,
    MCA_SESSION_ASYN,
    MCA_SESSION_NRSP
} MCA_SESSION_TYPE;

typedef enum
{
    MCA_CMD_RSP = 0,            /* MCA Reserved for response.   */

    /* Declare MCA command ID. */
    MCA_CMD_DFS_ENABLE,         /* Enable DFS device.           */
    MCA_CMD_DFS_DISABLE,        /* Disnable DFS device.         */
    MCA_CMD_DFS_STATE,          /* Get DFS device state.        */
    MCA_CMD_DFS_LOCK,           /* Lock DFS profile.            */
    MCA_CMD_DFS_UNLOCK,         /* Unlock DFS profile.          */
    MCA_CMD_DFS_PFNUM,          /* Get DFS profile number.      */
    MCA_CMD_DFS_CURRENT,        /* Get current DFS profile.     */
    MCA_CMD_DFS_TARGET,         /* Set DFS profile.             */
    MCA_CMD_DFS_RPFPLI,         /* Get DFS policy profile.      */
    MCA_CMD_DFS_WPFPLI,         /* Write DFS policy profile.    */
    MCA_CMD_DFS_SETPLI,         /* Set All DFS policy profile.    */
    MCA_CMD_DFS_RQQOS,          /* DFS QoS request.             */
    MCA_CMD_DFS_RLQOS,          /* DFS QoS release.             */
    MCA_CMD_DFS_UDQOS,          /* DFS QoS update.              */
    MCA_CMD_DFS_SETPROFILE,         /* Set All DFS profile.    */
    /* V8R1B050新增上下电命令 */
    MCA_CMD_PM_RQQOS,           /* PM QoS request.              */
    MCA_CMD_PM_RLQOS,           /* PM QoS release.              */
    MCA_CMD_PM_UDQOS,           /* PM QoS update.               */
    
    MCA_CMD_MCU_SHELL,          /* use MCU shell in adb shell   */
    MCA_CMD_END                 /* NERVER REACH.                */
} MCA_CMD_ID;

union mca_udata_req
{
    char data[MCA_UDATA_REQ_SIZE];

    /* Declare MCA command udata structure. */

    struct {char name[MCA_UDATA_REQ_NAME_SIZE];} dfs_devid_req;

    struct {char name[MCA_UDATA_REQ_NAME_SIZE];} dfs_polid_req;

    struct {char name[MCA_UDATA_REQ_NAME_SIZE];} dfs_qosid_req;

    struct {s32_t dev_id;} dfs_enable_req;

    struct {s32_t dev_id;} dfs_disable_req;

    struct {s32_t dev_id;} dfs_state_req;

    struct {s32_t dev_id; u32_t prof_id;} dfs_lock_req;

    struct {s32_t dev_id;} dfs_unlock_req;

    struct {s32_t dev_id;} dfs_pfnum_req;

    struct {s32_t dev_id;} dfs_current_req;

    struct {s32_t dev_id; u32_t prof_id;} dfs_target_req;

    struct {s32_t policy_id; u32_t prof_id;} dfs_rpfpli_req;
#if 0 /*don't use now*/    

    struct {s32_t policy_id; u32_t prof_id; s32_t pli_buf[POLICY_LEN / BYTES_PER_UINT32];} dfs_wpfpli_req;

	struct {s32_t policy_id; s32_t pli_buf[POLICY_MAX_TOTAL_SIZE / BYTES_PER_UINT32];} dfs_setpli_req;
#else
    struct {s32_t policy_id; u32_t prof_id; s32_t pli_buf[1];} dfs_wpfpli_req;

    struct {s32_t policy_id; s32_t pli_buf[1];} dfs_setpli_req;  
#endif

	struct {s32_t qos_id; u32_t req_value; s32_t core_id;} dfs_rqqos_req;

    struct {s32_t qos_id; s32_t req_id; s32_t core_id;} dfs_rlqos_req;

    struct {s32_t qos_id; s32_t req_id; u32_t req_value; s32_t core_id;} dfs_udqos_req;
#if 0 /*don't use now*/ 
	struct {s32_t dev_id; u32_t prof_buf[PROFILE_MAX_TOTAL_SIZE / BYTES_PER_UINT32];} dfs_set_prof_req;
#else
	struct {s32_t dev_id; u32_t prof_buf[1];} dfs_set_prof_req; 
#endif
    /*V8R1B050新增*/

    struct {u32_t module_id; s32_t qos_id; u32_t req_value;} pm_rqqos_req;

    struct {u32_t module_id; s32_t qos_id; s32_t req_id;} pm_rlqos_req;

    struct {u32_t module_id; s32_t qos_id; s32_t req_id; u32_t req_value;} pm_udqos_req;

    /*V8R1B071新增*/

    struct {u32_t req_value;} acpu_dfs_req;
};

union mca_udata_rsp
{
    char data[MCA_UDATA_RSP_SIZE];

    /* Declare MCA command udata structure. */
    /*假命令用于表示返回失败的情况*/
    /*struct {char name[MCA_UDATA_REQ_SIZE];} dfs_devid_req;*/
    struct {s32_t ret;} dfs_default_rsp;

    struct {s32_t ret; s32_t id;} dfs_devid_rsp;

    struct {s32_t ret; s32_t id;} dfs_polid_rsp;

    struct {s32_t ret; s32_t id;} dfs_qosid_rsp;

    struct {s32_t ret;} dfs_enable_rsp;

    struct {s32_t ret;} dfs_disable_rsp;

    struct {s32_t ret; u32_t state;} dfs_state_rsp;

    struct {s32_t ret;} dfs_lock_rsp;

    struct {s32_t ret;} dfs_unlock_rsp;

    struct {s32_t ret; u32_t prof_num;} dfs_pfnum_rsp;

    struct {s32_t ret; u32_t prof_id;} dfs_current_rsp;

    struct {s32_t ret;} dfs_target_rsp;
#if 0 /*don't use now*/ 
    struct {s32_t ret; s32_t pli_buf[POLICY_LEN / BYTES_PER_UINT32];} dfs_rpfpli_rsp;
#else
    struct {s32_t ret; s32_t pli_buf[1];} dfs_rpfpli_rsp;
#endif
    struct {s32_t ret;} dfs_wpfpli_rsp;

    struct {s32_t ret;} dfs_setpli_rsp;
    struct {s32_t ret; s32_t req_id;} dfs_rqqos_rsp;

    struct {s32_t ret; s32_t req_id;} dfs_rlqos_rsp;

    struct {s32_t ret;} dfs_udqos_rsp;
    struct {s32_t ret;} dfs_set_prof_rsp;

    /*V8R1B050新增*/

    struct {s32_t ret; s32_t req_id;} pm_rqqos_rsp;

    struct {s32_t ret; s32_t req_id;} pm_rlqos_rsp;

    struct {s32_t ret;} pm_udqos_rsp;
    
    /*V8R1B071新增*/
    struct {s32_t ret;} acpu_dfs_rsp;

};


struct mca_frame
{
    int sid;
    int stype;
    unsigned int cmd_id;
    union mca_udata_req udata;
};

#endif
