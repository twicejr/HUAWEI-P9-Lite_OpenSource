#ifndef __IPC_MSG_H__
#define __IPC_MSG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  宏定义
*****************************************************************************/
/*********************SEND MODE DEFINE*********************/
#define SYNC_MODE			1
#define ASYNC_MODE			0

/***********************CMD DEFINE***********************/
#define CMD_ON				0
#define CMD_OFF				1
#define CMD_INQUIRY			2
#define CMD_SETTING			3
#define CMD_NOTIFY          4
#define CMD_TEST			5
#define MAX_CMD				6

#define OBJ_AP				0
#define OBJ_LITTLE_CLUSTER	1
#define OBJ_BIG_CLUSTER		2
#define OBJ_GPU				3
#define OBJ_DDR				4
#define OBJ_ASP				5
#define OBJ_HIFI				6
#define OBJ_IOM3			7
#define OBJ_LPM3			8
#define OBJ_MODEM			9
#define OBJ_SYS				10
#define OBJ_HKADC			11
#define OBJ_REGULATOR		12
#define OBJ_CLK				13
#define OBJ_TEMPERTURE		14
#define OBJ_COUL			15
#define OBJ_PSCI				16
#define OBJ_TELEMNTN             17
#define OBJ_MCA             		18
#define OBJ_TEST		              19
#define MAX_CMD_OBJ		20

#define TYPE_POWER			1
#define TYPE_CLK				2
#define TYPE_CORE			3
#define TYPE_CLUSTER		4
#define TYPE_SLEEP			5
#define TYPE_SR				6
#define TYPE_MODE			7
#define TYPE_UPLIMIT		8
#define TYPE_DNLIMIT		9
#define TYPE_FREQ			10
#define TYPE_T				11
#define TYPE_VOLT			12
#define TYPE_RESET			13
#define TYPE_PWC			14
#define TYPE_TEST			15

/* mail size */
#define MAX_MAIL_SIZE		8
#define IPC_CMD(src, obj, cmd, type)	(((src) << 24) | ((obj) << 16) | ((cmd) << 8) | (type))

/*****************************************************************************
  消息头定义
*****************************************************************************/


/*****************************************************************************
  消息定义
*****************************************************************************/


/*****************************************************************************
  结构体定义
*****************************************************************************/
struct cmd_parse {
    unsigned char	cmd_type;
    unsigned char	cmd;
    unsigned char	cmd_obj;
    unsigned char	cmd_src;
    unsigned char	cmd_para[4];
};

struct ipc_msg {
    union {
        unsigned int	data[MAX_MAIL_SIZE];
        struct cmd_parse cmd_mix;
    };
    unsigned char	ipc_id;
    unsigned char	mailbox_id;
    unsigned char	dest_id;
    unsigned char	wait_id;
    unsigned char	mode;
    unsigned char	end_id;
};

/*****************************************************************************
  联合体定义
*****************************************************************************/
union ipc_data {
    unsigned int	data[MAX_MAIL_SIZE];
    struct cmd_parse cmd_mix;
};

/*****************************************************************************
  其它定义
*****************************************************************************/


/*****************************************************************************
  全局变量声明
*****************************************************************************/


/*****************************************************************************
  函数声明
*****************************************************************************/
extern int ipc_msg_send(unsigned int obj, struct ipc_msg *msg, unsigned int mode);
extern int ipc_msg_req_callback(unsigned int obj, unsigned int cmd, int (*func)(union ipc_data *));
extern int ipc_msg_put_callback(unsigned int obj, unsigned int cmd);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif/*__IPC_MSG_H__*/
