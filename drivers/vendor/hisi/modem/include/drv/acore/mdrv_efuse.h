

#ifndef __MDRV_ACORE_EFUSE_H__
#define __MDRV_ACORE_EFUSE_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "mdrv_efuse_common.h"

    /*************************************************
     *  函 数 名   : mdrv_efuse_get_chipid
     *  功能描述   : mdrv_efuse_get_chipid
     *  输入参数   : buf: data buffer
     *               len: length of the group
     *  输出参数   :
     *  返 回 值   : OK                (0)
     *               BUF_ERROR         (-55)
     *               LEN_ERROR         (-56)
     *               READ_EFUSE_ERROR  (-57)
     *  修改历史   :
     *  日    期 : 2013年8月12日
     *  作    者 : l00225826
     *  修改内容 : 新生成函数
     *************************************************/
    int mdrv_efuse_get_chipid(unsigned char* buf,int length);

    /*************************************************
     *  函 数 名   : mdrv_efuse_get_dieid
     *  功能描述   : mdrv_efuse_get_dieid
     *  输入参数   : buf: data buffer
     *               len: length of the buf in bytes
     *  输出参数   :
     *  返 回 值   : OK                (0)
     *               BUF_ERROR         (-55)
     *               LEN_ERROR         (-56)
     *               READ_EFUSE_ERROR  (-57)

     *  修改历史   :
     *  日    期 : 2013年8月12日
     *  作    者 : l00225826
     *  修改内容 : 新生成函数
     *************************************************/
    int mdrv_efuse_get_dieid(unsigned char* buf, int length);


#define MDRV_EFUSE_IOCTL_CMD_GET_SOCID          (0)
#define MDRV_EFUSE_IOCTL_CMD_SET_KCE            (1)
#define MDRV_EFUSE_IOCTL_CMD_GET_KCE            (2)
#define MDRV_EFUSE_IOCTL_CMD_SET_SECURESTATE    (3)
#define MDRV_EFUSE_IOCTL_CMD_GET_SECURESTATE    (4)
#define MDRV_EFUSE_IOCTL_CMD_SET_SECUREDEBUG    (5)
#define MDRV_EFUSE_IOCTL_CMD_GET_SECUREDEBUG    (6)
#define MDRV_EFUSE_IOCTL_CMD_SET_DBGEN          (7)
#define MDRV_EFUSE_IOCTL_CMD_GET_DBGEN          (8)
#define MDRV_EFUSE_IOCTL_CMD_SET_NIDEN          (9)
#define MDRV_EFUSE_IOCTL_CMD_GET_NIDEN          (10)
#define MDRV_EFUSE_IOCTL_CMD_SET_SPIDEN         (11)
#define MDRV_EFUSE_IOCTL_CMD_GET_SPIDEN         (12)
#define MDRV_EFUSE_IOCTL_CMD_SET_SPNIDEN        (13)
#define MDRV_EFUSE_IOCTL_CMD_GET_SPNIDEN        (14)
#define MDRV_EFUSE_IOCTL_CMD_SET_HIFIDBGEN      (15)
#define MDRV_EFUSE_IOCTL_CMD_GET_HIFIDBGEN      (16)
#define MDRV_EFUSE_IOCTL_CMD_SET_BBE16DBGEN     (17)
#define MDRV_EFUSE_IOCTL_CMD_GET_BBE16DBGEN     (18)
#define MDRV_EFUSE_IOCTL_CMD_SET_CSDEVICEEN     (19)
#define MDRV_EFUSE_IOCTL_CMD_GET_CSDEVICEEN     (20)
#define MDRV_EFUSE_IOCTL_CMD_SET_JTAGEN         (21)
#define MDRV_EFUSE_IOCTL_CMD_GET_JTAGEN         (22)
#define MDRV_EFUSE_IOCTL_CMD_SET_SECDBGRESET    (23)
#define MDRV_EFUSE_IOCTL_CMD_GET_SECDBGRESET    (24)
#define MDRV_EFUSE_IOCTL_CMD_SET_CSRESET        (25)
#define MDRV_EFUSE_IOCTL_CMD_GET_CSRESET        (26)
#define MDRV_EFUSE_IOCTL_CMD_SET_DFTSEL         (27)
#define MDRV_EFUSE_IOCTL_CMD_GET_DFTSEL         (28)
#define MDRV_EFUSE_IOCTL_CMD_SET_AUTHKEY        (29)
#define MDRV_EFUSE_IOCTL_CMD_GET_AUTHKEY        (30)
#define MDRV_EFUSE_IOCTL_CMD_SET_AUTHKEYRD      (31)
#define MDRV_EFUSE_IOCTL_CMD_GET_AUTHKEYRD      (32)
#define MDRV_EFUSE_IOCTL_CMD_SET_NSIVERIFY      (33)
#define MDRV_EFUSE_IOCTL_CMD_GET_NSIVERIFY      (34)


    /*************************************************
     *  函 数 名   : mdrv_efuse_ioctl
     *  功能描述   : Efuse中相关域的烧写和读取
     *  输入参数   : cmd: MDRV_EFUSE_IOCTL_CMD_ 相关的宏，每个宏与同名的AT命令对应
     *               arg: 与该命令对应的参数
     *               buf: data buffer
     *               len: length of the group
     *  输出参数   : 无
     *  返 回 值   : ret
     *
     *

     MDRV_EFUSE_IOCTL_CMD_GET_SOCID
        arg     NA
        buf     Buffer地址
        len     Buffer长度，不小于8
        ret     <0 -- ERROR
                0  -- OK
        desciption      ^SOCID? 读取芯片的SOCID(256 bits)

     MDRV_EFUSE_IOCTL_CMD_SET_KCE
        arg     NA
        buf     Buffer地址
        len     Buffer长度，不小于4
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^KCE=<value> 烧入 128bit 的KEY,用于image的加解密

     MDRV_EFUSE_IOCTL_CMD_GET_KCE
        arg     NA
        buf     Buffer地址
        len     Buffer长度，不小于4
        ret     <0 -- ERROR
                0  -- OK
        desciption      KCE不可读取，该命令用不到

     MDRV_EFUSE_IOCTL_CMD_SET_SECURESTATE
        arg     0  -- 未设置芯片安全状态
                1  -- 设置芯片为安全状态
                2  -- 设置芯片为非安全状态
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^SECURESTATE=<value> 控制芯片的安全状态

     MDRV_EFUSE_IOCTL_CMD_GET_SECURESTATE
        arg     NA
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- 未设置芯片安全状态
                1  -- 设置芯片为安全状态
                2  -- 设置芯片为非安全状态
        desciption      ^SECURESTATE? 获取芯片的安全状态

     MDRV_EFUSE_IOCTL_CMD_SET_SECUREDEBUG
        arg     0  -- Secure privilege debug
                1  -- 通过密码保护的方式进行鉴权，鉴权通过之后才能使能debug功能
                2  -- 控制信号由eFuse中的烧写值确定
                3  -- DCU决定
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^SECUREDEBUG=<value> 设置终端芯片的DEBUG 模式

     MDRV_EFUSE_IOCTL_CMD_GET_SECUREDEBUG
        arg     NA
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- Secure privilege debug
                1  -- 通过密码保护的方式进行鉴权，鉴权通过之后才能使能debug功能
                2  -- 控制信号由eFuse中的烧写值确定
                3  -- DCU决定
        desciption      ^SECUREDEBUG? 获取芯片的DEBUG 模式

     MDRV_EFUSE_IOCTL_CMD_SET_DBGEN
        arg     0  -- 打开
                1  -- 关闭
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^DEBUGEN=<value> 控制是否开启非安全世界侵入式调试功能(只在AT^SECUREDEBUG为0b10时有效)

     MDRV_EFUSE_IOCTL_CMD_GET_DBGEN
        arg     NA
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- 打开
                1  -- 关闭
        desciption      ^DEBUGEN? 获取是否开启非安全世界侵入式调试功能(只在AT^SECUREDEBUG为0b10时有效)

     MDRV_EFUSE_IOCTL_CMD_SET_NIDEN
        arg     0  -- 打开
                1  -- 关闭
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^NIDEN=<value> 控制是否开启非安全世界非侵入式调试功能(只在AT^SECUREDEBUG为0b10时有效)

     MDRV_EFUSE_IOCTL_CMD_GET_NIDEN
        arg     NA
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- 打开
                1  -- 关闭
        desciption      ^NIDEN? 获取是否开启非安全世界非侵入式调试功能(只在AT^SECUREDEBUG为0b10时有效)

     MDRV_EFUSE_IOCTL_CMD_SET_SPIDEN
        arg     0  -- 打开
                1  -- 关闭
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^SPIDEN=<value> 控制是否开启安全世界侵入式调试功能(只在AT^SECUREDEBUG为0b10时有效)

     MDRV_EFUSE_IOCTL_CMD_GET_SPIDEN
        arg     NA
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- 打开
                1  -- 关闭
        desciption      ^SPIDEN? 获取是否开启安全世界侵入式调试功能(只在AT^SECUREDEBUG为0b10时有效)

     MDRV_EFUSE_IOCTL_CMD_SET_SPNIDEN
        arg     0  -- 打开
                1  -- 关闭
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^SPNIDEN=<value> 控制是否开启安全世界非侵入式调试功能(只在AT^SECUREDEBUG为0b10时有效)

     MDRV_EFUSE_IOCTL_CMD_GET_SPNIDEN
        arg     NA
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- 打开
                1  -- 关闭
        desciption      ^SPNIDEN? 获取是否开启安全世界非侵入式调试功能(只在AT^SECUREDEBUG为0b10时有效)

     MDRV_EFUSE_IOCTL_CMD_SET_HIFIDBGEN
        arg     0  -- 打开
                1  -- 关闭
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^HIFIDBGEN=<value> 控制是否开启HiFi调试功能(只在AT^SECUREDEBUG为0b10时有效)

     MDRV_EFUSE_IOCTL_CMD_GET_HIFIDBGEN
        arg     NA
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- 打开
                1  -- 关闭
        desciption      ^HIFIDBGEN? 获取是否开启HiFi调试功能(只在AT^SECUREDEBUG为0b10时有效)

     MDRV_EFUSE_IOCTL_CMD_SET_BBE16DBGEN
        arg     0  -- 打开
                1  -- 关闭
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^BBE16DBGEN=<value> 控制是否开启BBE16调试功能(只在AT^SECUREDEBUG为0b10时有效)

     MDRV_EFUSE_IOCTL_CMD_GET_BBE16DBGEN
        arg     NA
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- 打开
                1  -- 关闭
        desciption      ^BBE16DBGEN? 获取是否开启BBE16调试功能(只在AT^SECUREDEBUG为0b10时有效)

     MDRV_EFUSE_IOCTL_CMD_SET_CSDEVICEEN
        arg     0  -- 打开
                1  -- 关闭
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^CSDEVICEEN=<value> 控制是否开启Coresight调试功能(只在AT^SECUREDEBUG为0b10时有效)

     MDRV_EFUSE_IOCTL_CMD_GET_CSDEVICEEN
        arg     NA
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- 打开
                1  -- 关闭
        desciption      ^CSDEVICEEN? 获取是否开启Coresight调试功能(只在AT^SECUREDEBUG为0b10时有效)

     MDRV_EFUSE_IOCTL_CMD_SET_JTAGEN
        arg     0  -- 打开
                1  -- 关闭
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^JTAGEN=<value> 控制是否开启JTAG调试功能

     MDRV_EFUSE_IOCTL_CMD_GET_JTAGEN
        arg     NA
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- 打开
                1  -- 关闭
        desciption      ^JTAGEN? 获取是否开启JTAG调试功能

     MDRV_EFUSE_IOCTL_CMD_SET_SECDBGRESET
        arg     0  -- 默认不复位
                1  -- 复位
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^SECDBGRESET=<value> 控制是否在进行安全世界调试时，临时复位SEC Engine

     MDRV_EFUSE_IOCTL_CMD_GET_SECDBGRESET
        arg     NA
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- 默认不复位
                1  -- 复位
        desciption      ^SECDBGRESET? 获取是否在进行安全世界调试时，临时复位SEC Engine

     MDRV_EFUSE_IOCTL_CMD_SET_CSRESET
        arg     0  -- 默认不复位
                1  -- 复位
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^CSRESET=<value> 控制是否在用Coresight调试时，临时复位SEC Engine

     MDRV_EFUSE_IOCTL_CMD_GET_CSRESET
        arg     NA
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- 默认不复位
                1  -- 复位"
        desciption      ^CSRESET? 获取是否在用Coresight调试时，临时复位SEC Engine

     MDRV_EFUSE_IOCTL_CMD_SET_DFTSEL
        arg     0  -- 打开状态
                1  -- 关闭状态
                2/3 -- 永久关闭状态
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^DFTSEL=<value> 控制DFTSCAN 的等级

     MDRV_EFUSE_IOCTL_CMD_GET_DFTSEL
        arg     NA
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- 打开状态
                1  -- 关闭状态
                2/3 -- 永久关闭状态
        desciption      ^DFTSEL? 获取DFTSCAN 的等级

     MDRV_EFUSE_IOCTL_CMD_SET_AUTHKEY
        arg     NA
        buf     Buffer地址
        len     Buffer长度，不小于2
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^AUTHKEY=<value> 烧入 64 bits 的 DFT 和密码鉴权的认证密码

     MDRV_EFUSE_IOCTL_CMD_GET_AUTHKEY
        arg     NA
        buf     Buffer地址
        len     Buffer长度，不小于2
        ret     <0 -- ERROR
                0  -- OK
        desciption      ^AUTHKEY? 读取芯片64 bits 的 DFT 和密码鉴权的认证密码

     MDRV_EFUSE_IOCTL_CMD_SET_AUTHKEYRD
        arg     0  -- 软件可读
                1  -- 软件不可读
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^AUTHKEYRD=<value> 控制AUTHKEY 是否可读

     MDRV_EFUSE_IOCTL_CMD_GET_AUTHKEYRD
        arg     NA
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- 软件可读
                1  -- 软件不可读
        desciption      ^AUTHKEYRD? 获取AUTHKEY 是否可读

     MDRV_EFUSE_IOCTL_CMD_SET_NSIVERIFY
        arg     0  -- 关闭校验
                1  -- 打开校验
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- OK
                1  -- REPEAT
        desciption      ^NSIVERIFY=<value> 控制是否开启非安全产品镜像完整性校验

     MDRV_EFUSE_IOCTL_CMD_GET_NSIVERIFY
        arg     NA
        buf     NA
        len     NA
        ret     <0 -- ERROR
                0  -- 关闭校验
                1  -- 打开校验
        desciption      ^NSIVERIFY? 获取是否开启非安全产品镜像完整性校验

     *  修改历史   :
     *  日    期 : 2015年11月28日
     *  作    者 : z00227143
     *  修改内容 : 新生成函数
     *************************************************/
    int mdrv_efuse_ioctl(int cmd, int arg, unsigned char* buf, int len);


#ifdef __cplusplus
}
#endif
#endif

