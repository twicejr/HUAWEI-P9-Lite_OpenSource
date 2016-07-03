

enum
{
    NV_ICC_REQ_SYS  = 64,
    NV_ICC_REQ_INSTANT_FLUSH = 65,        /*立即写入请求,需要等待回复*/
    NV_ICC_REQ_CCORE_DELAY_FLUSH = 66,    /*ccore 延迟写入请求，不需要等待回复*/
    NV_REQ_ACORE_DELAY_FLUSH = 67,        /*acore 延迟写入请求，不需要等待回复*/
    NV_ICC_CNF      = 127,
    NV_ICC_RESUME   = 0xFF  /*请求恢复DDR中的nv数据*/
};
#define NV_ICC_MSG_TYPE_SUM (6)


struct nv_icc_stru
{
    unsigned int msg_type;          /*msg type*/
    unsigned int data_off;          /*data off */
    unsigned int data_len;          /*data len*/
    unsigned int ret;
    unsigned int itemid;
    unsigned int slice;
};

struct nv_icc_msg_name
{
    unsigned int msg_type;
    char         cpu[5];
    char         work[32];
};

int nvim_msg_parse(unsigned int typeid, char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr);

