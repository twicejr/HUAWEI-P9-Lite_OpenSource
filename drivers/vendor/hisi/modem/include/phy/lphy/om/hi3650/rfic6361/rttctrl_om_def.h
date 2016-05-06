typedef enum __RTT_CTRL_REQ_ID_ENUM__
{
    RTT_CTRL_SOCP_STATE_CHANGE_REQ,
}RTT_CTRL_REQ_ID_ENUM;

typedef enum __RTT_CTRL_CFN_ID_ENUM__
{
    RTT_CTRL_SOCP_STATE_CHANGE_CFN,
}RTT_CTRL_CFN_ID_ENUM;



typedef struct __RTT_CTRL_SOCP_STATE_CHANGE_REQ_STRU__
{
    UINT32 ulMsgID;
    UINT32 ulOpID;
    UINT8  ucStateChange;    /*0 Invalid;1: Valid */
    UINT8  ucReserved[3];
}RTT_CTRL_SOCP_STATE_CHANGE_REQ_STRU;

typedef struct __RTT_CTRL_SOCP_STATE_CHANGE_CFN_STRU__
{
    UINT32 ulMsgID;
    UINT32 ulOpID;
    UINT8  ucStateChange;    /*0 Invalid;1: Valid */
    UINT8  ucReserved[3];
}RTT_CTRL_SOCP_STATE_CHANGE_CFN_STRU;
