/**
 * @file vos_libc.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：OSAL的C函数头文件。 \n
 */

/**@defgroup vos_libc libc
 *@ingroup OSAL
*/

#ifndef __VOS_LIBC_H__
#define __VOS_LIBC_H__

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)

#include <stdarg.h>
#include "vos_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#ifndef VOS_NTOHL

#define VOS_NTOHL(x)    ((((x) & 0x000000ff) << 24) | \
             (((x) & 0x0000ff00) <<  8) | \
             (((x) & 0x00ff0000) >>  8) | \
             (((x) & 0xff000000) >> 24))

#define VOS_HTONL(x)    ((((x) & 0x000000ff) << 24) | \
             (((x) & 0x0000ff00) <<  8) | \
             (((x) & 0x00ff0000) >>  8) | \
             (((x) & 0xff000000) >> 24))

#define VOS_NTOHS(x)    ((((x) & 0x00ff) << 8) | \
             (((x) & 0xff00) >> 8))

#define VOS_HTONS(x)    ((((x) & 0x00ff) << 8) | \
             (((x) & 0xff00) >> 8))

#endif //VOS_NTOHL

#define VOS_DBGASSERT(lExpression)

/**
 * @ingroup vos_libc
 * 判断字符是否为大写字母。
 */
#define VOS_isupper(c)  (((c) >= 'A' && (c) <= 'Z') ?  1 : 0)

/**
 * @ingroup vos_libc
 * 判断字符是否为小写字母。
 */
#define VOS_islower(c)  (((c) >= 'a' && (c) <= 'z') ?  1 : 0)

/**
 * @ingroup vos_libc
 * 判断字符是否为字母。
 */
#define VOS_isalpha(c)  (VOS_isupper(c) || VOS_islower(c))

/**
 * @ingroup vos_libc
 * 判断字符是否为数字。
 */
#define VOS_isdigit(c)  (((c) >= '0' && (c) <= '9') ?  1 : 0)

/**
 * @ingroup vos_libc
 * 把源地址Src的内存数据拷贝到目的内存地址Dest。
 */
#define VOS_CopyVar(Dest, Src) \
{\
    (VOID)VOS_Mem_Copy((VOID *)&(Dest), (VOID *)&(Src), sizeof(Dest)); \
}

/**
 * @ingroup vos_libc
 * OSAL Libc错误码：格式化的控制字符串为空。
 *
 * 值: 0x00000050
 *
 * 解决方案: 请输入有效的格式化的控制字符串。
 */
#define VOS_ERR_NULL_FORMAT_STR                 0x00000050

/**
 * @ingroup  vos_libc
 * @brief 从缓冲区中按指定格式输入字符。
 *
 * @par 描述:
 * 从pscIBuf里读进数据，依照pfmt的格式将数据写入到可选参数里。
 *
 * @attention
 * <ul>
 * <li>分隔符是空格。</li>
 * <li>用户保证格式化的字符串中可分解的子串的格式与格式化控制字符串中的格式匹配。</li>
 * <li>用户保证存放格式化数据的可变参数空间足够。</li>
 * <li>如果pscIBuf包含的个数比需要的少，那么只能解析pscIBuf中包含的字符。</li>
 * <li>支持x、d、s、u几种格式化类型。</li>
 * </ul>
 *
 * @param pscIBuf [IN] 类型#VOS_CHAR *，格式化的字符串。取值范围为非空。
 * @param pfmt [IN] 类型#VOS_CHAR *，格式化控制字符串。取值范围为非空。
 * @param ... [OUT] 可选参数。
 *
 * @retval #-1                                  pscIBuf或pfmt为空。
 * @retval #非负数                              从格式化的缓存中读到的值的个数。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  无
 */
extern VOS_INT32 VOS_sscanf(const VOS_CHAR *pscIBuf, const VOS_CHAR *pfmt, ...);

/**
 * @ingroup  vos_libc
 * @brief 比较两个内存区域字符。
 *
 * @par 描述:
 * 用来比较pDestPtr和pSrcPtr所指的内存区域前ulCmpLen个字符。字符串大小的比较是以ASCII码表上的顺序来决定，此顺序亦为字符的值，将比较的差值保存在plRetResult中。
 *
 * @attention 无
 *
 * @param pDestPtr [IN] 类型#const VOS_VOID *，要比较的内存地址。取值范围为非空。
 * @param pSrcPtr [IN] 类型#const VOS_VOID *，要比较的内存地址。取值范围为非空。
 * @param uvCmpLen [IN] 类型#VOS_SIZE_T，比较的字符数。取值范围为正整数。
 * @param plRetResult [OUT] 类型#VOS_INT32 *，存储比较的结果。结果说明: 大于0说明pDestPtr大于pSrcPtr。等于0说明pDestPtr等于pSrcPtr。小于0说明pDestPtr小于pSrcPtr。
 *
 * @retval #VOS_ERROR                           0xFFFFFFFF，pDestPtr、pSrcPtr、plRetResult有一个为空或uvCmpLen为0。
 * @retval #VOS_OK                              0x00000000，比较成功。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  无
 */
extern VOS_UINT32 VOS_Mem_Cmp(const VOS_VOID *pDestPtr, const VOS_VOID *pSrcPtr, VOS_SIZE_T uvCmpLen, VOS_INT32 *plRetResult);

/**
 * @ingroup  vos_libc
 * @brief 将指定的内存区域以特定的值填充。
 *
 * @par 描述:
 * 会将参数pBufPtr所指的内存内容前ulSetLen个字节以参数uChar填入。
 *
 * @attention 无
 *
 * @param pBufPtr [IN/OUT] 类型#VOS_CHAR *，要填充的内存地址。取值范围为非空。
 * @param uChar [IN] 类型#VOS_CHAR，要填入的内存值。取值范围为非空。
 * @param uvSetLen [IN] 类型#VOS_SIZE_T，要填充的字符数。取值范围为正整数。
 *
 * @retval #VOS_ERROR                           0xFFFFFFFF，pBufPtr为空或uvSetLen为0。
 * @retval #VOS_OK                              0x00000000，内存设置成功。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_MemSet
 */
extern VOS_UINT32 VOS_Mem_Set(VOS_CHAR *pBufPtr, VOS_CHAR uChar, VOS_SIZE_T uvSetLen);

/**
 * @ingroup  vos_libc
 * @brief 将指定的内存区域以特定的值填充。
 *
 * @par 描述:
 * 会将参数pBufPtr所指的内存内容前ulSetLen个字节以参数uChar填入。
 *
 * @attention 无
 *
 * @param pBufPtr [IN/OUT] 类型#VOS_CHAR *，要填充的内存地址。取值范围为非空。
 * @param uChar [IN] 类型#VOS_CHAR，要填入的内存值。取值范围为非空。
 * @param uvSetLen [IN] 类型#VOS_SIZE_T，要填充的字符数。取值范围为正整数。
 *
 * @retval #VOS_ERROR                           0xFFFFFFFF，pBufPtr为空或uvSetLen为0。
 * @retval #VOS_OK                              0x00000000，内存设置成功。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_Mem_Set
 */
extern VOS_UINT32 VOS_MemSet(VOS_VOID *pBufPtr, VOS_CHAR uChar, VOS_SIZE_T uvSetLen);

/**
 * @ingroup  vos_libc
 * @brief 比较两个字符串的前n个字符。
 *
 * @par 描述:
 * 用户必须保证传入参数的有效性，如果pscStr1或pscStr2为空指针，则该接口返回0，此时与字符串相等时的返回值相同。
 *
 * @attention 无
 *
 * @param pscStr1 [IN] 类型#const VOS_CHAR *，被比较的字符串1。取值范围为非空。
 * @param pscStr2 [IN] 类型#const VOS_CHAR *，被比较的字符串2。取值范围为非空。
 * @param ulLen [IN] 类型#VOS_UINT32，要比较的字符数。取值范围为正整数。
 *
 * @retval #0                                   pscStr1等于pscStr2或pscStr1与pscStr2中有一个为空指针或ulLen为0。
 * @retval #大于0                               pscStr1大于pscStr2。
 * @retval #小于0                               pscStr1小于pscStr2。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_strncmp
 */
extern VOS_INT32 VOS_StrNCmp(const VOS_CHAR *pscStr1, const VOS_CHAR *pscStr2, VOS_UINT32 ulLen);

/**
 * @ingroup  vos_libc
 * @brief 比较字符串，但不区分字母的大小写。
 *
 * @par 描述:
 * 用户必须保证传入参数的有效性，如果pscStr1或pscStr2为空指针，则该接口返回0，此时与字符串相等时的返回值相同。
 *
 * @attention
 * <ul><li>用户必须保证传入参数不为空指针，否则该接口返回0，此时与字符串相等时的返回值相同，无法根据返回值判断函数是否执行成功。</li></ul>
 *
 * @param pscStr1 [IN] 类型#const VOS_CHAR *，被比较的字符串1。取值范围为非空。
 * @param pscStr2 [IN] 类型#const VOS_CHAR *，被比较的字符串2。取值范围为非空。
 *
 * @retval #0                                   pscStr1等于pscStr2或pscStr1与pscStr2中有一个为空指针。
 * @retval #大于0                               pscStr1大于pscStr2。
 * @retval #小于0                               pscStr1小于pscStr2。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_stricmp
 */
extern VOS_INTPTR VOS_StrICmp(VOS_CHAR *pscStr1, VOS_CHAR *pscStr2);

/**
 * @ingroup  vos_libc
 * @brief 将字符串转换为无符号整数。
 *
 * @par 描述:
 * 将字符串pcStr转换为无符号整数，存储到pnVal中。
 *
 * @attention 无
 *
 * @param pcStr [IN] 类型#const VOS_CHAR *，要转换的原字符串。取值范围为非空。
 * @param pnVal [OUT] 类型#VOS_UINT32 *，用于存储转换后的整数。取值范围为非空。
 *
 * @retval #-1                                  入参pcStr或pnVal为空。
 * @retval #VOS_OK                              0x00000000，转换成功。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_atol
 */
extern VOS_INT32 VOS_atoul(const VOS_CHAR *pcStr, VOS_UINT32 *pnVal);

/**
 * @ingroup  vos_libc
 * @brief 将指定的内存区域以0值填充。
 *
 * @par 描述:
 * 将参数pBufPtr所指的内存内容前ulSetLen个字节以0值填入。
 *
 * @attention 无
 *
 * @param pBufPtr [IN/OUT] 类型#VOS_CHAR *，被设置内存区域的地址。取值范围为非空。
 * @param uvSetLen [IN] 类型#VOS_SIZE_T，指定内存区域的大小。传入0时，不对内存做任何填充。取值范围为非负数。
 *
 * @retval #VOS_ERROR                           0xFFFFFFFF，pBufPtr为空。
 * @retval #VOS_OK                              0x00000000，内存设置成功。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  无
 */
extern VOS_UINT32 VOS_Mem_Zero(VOS_CHAR *pBufPtr, VOS_SIZE_T uvSetLen);

/**
 * @ingroup  vos_libc
 * @brief 把一个内存区域的值拷贝到另外一个内存区域中。
 *
 * @par 描述:
 * 从源pSrcPtr所指的内存地址的起始位置开始拷贝uvCopyLen个字节到目标pDestPtr所指的内存地址的起始位置中。
 *
 * @attention 无
 *
 * @param pDestPtr [IN/OUT] 类型#VOS_VOID *，目的内存。取值范围为非空。
 * @param pSrcPtr [IN] 类型#const VOS_VOID *，来源内存。取值范围为非空。
 * @param uvCopyLen [IN] 类型#VOS_SIZE_T，拷贝的字节数。取值范围为正整数。
 *
 * @retval #VOS_ERROR                           0xFFFFFFFF，pBufPtr与pSrcPtr中有一个为空或uvCopyLen为0。
 * @retval #VOS_OK                              0x00000000，拷贝成功。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  无
 */
extern VOS_UINT32 VOS_Mem_Copy(VOS_VOID *pDestPtr, const VOS_VOID *pSrcPtr, VOS_SIZE_T uvCopyLen);

/**
 * @ingroup  vos_libc
 * @brief 查找字符串中最后一个出现的指定字符。
 *
 * @par 描述:
 * 用来找出参数pscStr字符串中最后一个出现的参数scChar地址，然后将该字符出现的地址返回。如果未找到，返回VOS_NULL_PTR。
 *
 * @attention 无
 *
 * @param pscStr [IN] 类型#VOS_CHAR *，给定的字符串。取值范围为非空。
 * @param scChar [IN] 类型#VOS_CHAR，要查找的字符。取值范围为任意字符。
 *
 * @retval #VOS_NULL_PTR                        0x00000000，pscStr为空或未找到指定字符。
 * @retval #任意值                              该字符所在地址。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  无
 */
extern VOS_CHAR * VOS_StrRChr(VOS_CHAR *pscStr, VOS_CHAR scChar);

/**
 * @ingroup  vos_libc
 * @brief 从指定的内存块中搜索指定字符。
 *
 * @par 描述:
 * 从头开始搜索pvBuf所指的内存内容前siSize个字节，直到发现第一个值为ucChar的字节，则返回指向该字节的指针。
 *
 * @attention 无
 *
 * @param pvBuf [IN] 类型#const VOS_VOID *，被搜索字符串的地址。取值范围为非空。
 * @param ucChar [IN] 类型#VOS_CHAR，被搜索的字符。取值范围为任意字符。
 * @param siSize [IN] 类型#VOS_INT32，被搜索内存的大小。取值范围为正整数。
 *
 * @retval #VOS_NULL_PTR                        0x00000000，pvBuf为空或siSize为0或未搜索到指定字符。
 * @retval #任意值                              搜索到字符的地址。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  无
 */
extern VOS_VOID * VOS_MemChr(const VOS_VOID *pvBuf, VOS_CHAR ucChar, VOS_INT32 siSize);

/**
 * @ingroup  vos_libc
 * @brief 将字符串转化为无符号整数。
 *
 * @par 描述:
 * 将参数szStr字符串转换为无符号整数。
 *
 * @attention 无
 *
 * @param szStr [IN] 类型#const VOS_CHAR *，被转换字符串的地址。取值范围为非空。
 * @param puiVal [OUT] 类型#VOS_UINT32 *，转换后无符号整数的地址。取值范围为非空。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，szStr或puiVal为空。
 * @retval #VOS_OK                              0x00000000，转化成功。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  无
 */
extern VOS_INT32 VOS_StrToUint32(const VOS_CHAR *szStr, VOS_UINT32 *puiVal);

/**
 * @ingroup  vos_libc
 * @brief 查找字符串中第一个出现的指定字符。
 *
 * @par 描述:
 * 在参数pcChar字符串中查找第一次出现参数scChar字符的地址，然后将该字符出现的地址返回。
 *
 * @attention 无
 *
 * @param pcChar [IN] 类型#const VOS_CHAR *，源字符串。取值范围为非空。
 * @param scChar [IN] 类型#VOS_CHAR，要查找的字符。取值范围为任意字符。
 *
 * @retval #VOS_NULL_PTR                        0x00000000，pcChar为空或未查找到指定字符。
 * @retval #任意值                              参数scChar出现的地址。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  无
 */
extern VOS_CHAR * VOS_strchr(const VOS_CHAR *pcChar, VOS_CHAR scChar);

/**
 * @ingroup  vos_libc
 * @brief 两个字符串之间的拷贝。
 *
 * @par 描述:
 * 将参数pcsrc字符串拷贝至参数pcdest所指的地址。
 *
 * @attention
 * <ul><li>如果参数pcdest所指的内存空间比pcsrc的小，可能会造成缓冲溢出的错误情况。</li></ul>
 *
 * @param pcdest [IN/OUT] 类型#VOS_CHAR *，目的字符串。取值范围为非空。
 * @param pcsrc  [IN] 类型#const VOS_CHAR *，源字符串。取值范围为非空。
 *
 * @retval #VOS_NULL_PTR                        0x00000000，pcdest或pcsrc为空。
 * @retval #任意值                              目的字符串的起始地址。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_StrCpy
 */
extern VOS_CHAR * VOS_strcpy(VOS_CHAR *pcdest, const VOS_CHAR *pcsrc);

/**
 * @ingroup  vos_libc
 * @brief 两个字符串之间的拷贝。
 *
 * @par 描述:
 * 将参数pcsrc字符串拷贝至参数pcdst所指的地址。
 *
 * @attention
 * <ul><li>如果参数pcdst所指的内存空间比pcsrc的小，可能会造成缓冲溢出的错误情况。</li></ul>
 *
 * @param pcdst [IN/OUT] 类型#VOS_CHAR *，目的字符串。取值范围为非空。
 * @param pcsrc [IN] 类型#const VOS_CHAR *，源字符串。取值范围为非空。
 *
 * @retval #VOS_NULL_PTR                        0x00000000，pcdst或pcsrc为空。
 * @retval #任意值                              目的字符串的起始地址。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_strcpy
 */
extern VOS_CHAR * VOS_StrCpy(VOS_CHAR *pcdst, const VOS_CHAR *pcsrc);

/**
 * @ingroup  vos_libc
 * @brief 将一个字符串的前n个字符拷贝到另一个字符串中。
 *
 * @par 描述:
 * 将参数pcsrc字符串前n个字符拷贝至参数pcdest所指的地址。
 *
 * @attention
 * <ul><li>调用函数后，注意判断返回的地址是否为空，否则可能会访问空指针。</li></ul>
 *
 * @param pcdest [IN/OUT] 类型#VOS_CHAR *，目的字符串。取值范围为非空。
 * @param pcsrc  [IN] 类型#const VOS_CHAR *，源字符串。取值范围为非空。
 * @param n [IN] 类型#VOS_UINT32，拷贝字符数。取值范围为正整数。
 *
 * @retval #任意值                              目的字符串的起始地址。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  无
 */
extern VOS_CHAR * VOS_strncpy(VOS_CHAR *pcdest, const VOS_CHAR *pcsrc, VOS_UINT32 n);

/**
 * @ingroup  vos_libc
 * @brief 把指定字符串添加到另一字符串结尾处。
 *
 * @par 描述:
 * 把pcsrc所指字符串添加到pcdest结尾处(覆盖pcdest结尾处的结束符)并添加结束符。pcsrc和pcdest所指内存区域不可以重叠且pcdest必须有足够的空间来容纳pcsrc的字符串。返回指向pcdest的指针。
 *
 * @attention 无
 *
 * @param pcdest [IN/OUT] 类型#VOS_CHAR *，目的字符串。取值范围为非空。
 * @param pcsrc [IN] 类型#const VOS_CHAR *，源字符串。取值范围为非空。
 *
 * @retval #VOS_NULL_PTR                        0x00000000，pcdst或pcsrc为空。
 * @retval #任意值                              添加后的字符串地址。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  无
 */
extern VOS_CHAR * VOS_strcat(VOS_CHAR *pcdest, const VOS_CHAR *pcsrc);

/**
 * @ingroup  vos_libc
 * @brief 把一个字符串的前n个字符添加到另一个字符串尾。
 *
 * @par 描述:
 * 把参数pscSrc所指字符串的前uvCount个字符添加到参数pscDest字符串结尾处(覆盖参数pscDest字符串结束符)并添加结束符。pscSrc和pscDest所指内存区域不可以重叠且pscDest必须有足够的空间来容纳pscSrc的字符串。返回指向pscDest的指针。
 *
 * @attention 无
 *
 * @param pscDest [IN/OUT] 类型#VOS_CHAR *，目的字符串。取值范围为非空。
 * @param pscSrc [IN] 类型#VOS_CHAR *，源字符串。取值范围为非空。
 * @param uvCount [IN] 类型#VOS_SIZE_T，字符个数。取值范围为正整数。
 *
 * @retval #VOS_NULL_PTR                        0x00000000，pcdst或pcsrc为空或uvCount为0。
 * @retval #任意值                              添加后的字符串地址。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  无
 */
extern VOS_CHAR * VOS_StrNCat(VOS_CHAR *pscDest, VOS_CHAR *pscSrc, VOS_SIZE_T uvCount);

/**
 * @ingroup  vos_libc
 * @brief 获取给定字符串的长度。
 *
 * @par 描述:
 * 获取给定字符串pcstr的长度，不包括结束符。
 *
 * @attention 无
 *
 * @param pcstr [IN] 类型#const VOS_CHAR *，要获取长度的字符串。取值范围为非空。
 *
 * @retval #VOS_NULL，                          0x00000000，pcstr为空。
 * @retval #正整数                              字符串长度。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  无
 */
extern VOS_UINT32 VOS_strlen(const VOS_CHAR *pcstr);

/**
 * @ingroup  vos_libc
 * @brief 在字符串中搜索指定字符串。
 *
 * @par 描述:
 * 在字符串pscStr1中搜索字符串pscStr2，并返回字符串pscStr2第一次出现的地址。
 *
 * @attention 无
 *
 * @param pscStr1 [IN] 类型#VOS_CHAR *，源字符串。取值范围为非空。
 * @param pscStr2 [IN] 类型#VOS_CHAR *，要搜索的字符串。取值范围为非空。
 *
 * @retval #VOS_NULL_PTR，                      0x00000000，pscStr1或pscStr2为空。
 * @retval #任意值                              第一次成功查找到字符串pscStr2的地址。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  无
 */
extern VOS_CHAR * VOS_StrStr(VOS_CHAR *pscStr1, VOS_CHAR *pscStr2);

/**
 * @ingroup  vos_libc
 * @brief 比较两个字符串。
 *
 * @par 描述:
 * 用户必须保证传入参数的有效性，如果pscStr1或pscStr2为空指针，则该接口返回0，此时与字符串相等时的返回值相同。
 *
 * @attention 无
 *
 * @param pscStr1 [IN] 类型#const VOS_CHAR *，被比较的字符串1。取值范围为非空。
 * @param pscStr2 [IN] 类型#const VOS_CHAR *，被比较的字符串2。取值范围为非空。
 *
 * @retval #0                                   pscStr1等于pscStr2或pscStr1与pscStr2中有一个为空。
 * @retval #大于0                               pscStr1大于pscStr2。
 * @retval #小于0                               pscStr1小于pscStr2。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  无
 */
extern VOS_INT32 VOS_strcmp(const VOS_CHAR *pscStr1, const VOS_CHAR *pscStr2);

/**
 * @ingroup  vos_libc
 * @brief 比较两个字符串的前n个字符。
 *
 * @par 描述:
 * 用户必须保证传入参数的有效性，如果pscStr1或pscStr2为空指针，则该接口返回0，此时与字符串相等时的返回值相同。
 *
 * @attention 无
 *
 * @param pscStr1 [IN] 类型#const VOS_CHAR *，被比较的字符串1。取值范围为非空。
 * @param pscStr2 [IN] 类型#const VOS_CHAR *，被比较的字符串2。取值范围为非空。
 * @param ulLen [IN] 类型#VOS_UINT32，被比较的字符数。取值范围为正整数。
 *
 * @retval #0                                   pscStr1等于pscStr2或pscStr1与pscStr2中有一个为空或ulLen为0。
 * @retval #大于0                               pscStr1大于pscStr2。
 * @retval #小于0                               pscStr1小于pscStr2。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_StrNCmp
 */
extern VOS_INT32 VOS_strncmp(const VOS_CHAR *pscStr1, const VOS_CHAR *pscStr2, VOS_UINT32 ulLen);

/**
 * @ingroup  vos_libc
 * @brief 把小写字母转换成等价的大写字母。
 *
 * @par 描述:
 * 把给定的小写字母cChar转换成等价的大写字母。
 *
 * @attention
 * <ul><li>如果给定的字母不在['a', 'z']的取值范围内，则不进行转换，原值返回。</li></ul>
 *
 * @param cChar [IN] 类型#VOS_CHAR，需要转换的字母，取值范围为任意字符。
 *
 * @retval #任意字符                            转换后的字母或者原值。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_tolower
 */
extern VOS_CHAR VOS_toupper(VOS_CHAR cChar);

/**
 * @ingroup  vos_libc
 * @brief 把大写字母转换成等价的小写字母。
 *
 * @par 描述:
 * 把给定的大写字母cChar转换成等价的小写字母。
 *
 * @attention
 * <ul><li>如果给定的字母不在['A', 'Z']的取值范围内，则不进行转换，原值返回。</li></ul>
 *
 * @param cChar [IN] 类型#VOS_CHAR，需要转换的字母，取值范围为任意字符。
 *
 * @retval #任意字符                            转换后的字母或者原值。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_toupper
 */
extern VOS_CHAR VOS_tolower(VOS_CHAR cChar);

/**
 * @ingroup  vos_libc
 * @brief 比较字符串，但不区分字母的大小写。
 *
 * @par 描述:
 * 用户必须保证传入参数的有效性，如果pscStr1或pscStr2为空指针，则该接口返回0，此时与字符串相等时的返回值相同。
 *
 * @attention
 * <ul><li>用户必须保证传入参数不为空指针，否则该接口返回0，此时与字符串相等时的返回值相同，无法根据返回值判断函数是否执行成功。</li></ul>
 *
 * @param pscStr1 [IN] 类型#const VOS_CHAR *，被比较的字符串1。取值范围为非空。
 * @param pscStr2 [IN] 类型#const VOS_CHAR *，被比较的字符串2。取值范围为非空。
 *
 * @retval #0                                   pscStr1等于pscStr2或pscStr1与pscStr2中有一个为空。
 * @retval #大于0                               pscStr1大于pscStr2。
 * @retval #小于0                               pscStr1小于pscStr2。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_StrICmp
 */
extern VOS_INT32 VOS_stricmp(const VOS_CHAR *pscStr1, const VOS_CHAR *pscStr2);

/**
 * @ingroup  vos_libc
 * @brief 比较两个字符串的前n个字符，但不区分大小写。
 *
 * @par 描述:
 * 用来比较参数pscStr1和pscStr2字符串的前ulLen个字符，但不区分大小写。
 *
 * @attention
 * <ul><li>用户必须保证传入参数的有效性，如果pscStr1或pscStr2为空指针，则该接口返回0，此时与字符串相等时的返回值相同。</li></ul>
 *
 * @param pscStr1 [IN] 类型#const VOS_CHAR *，被比较的字符串1。取值范围为非空。
 * @param pscStr2 [IN] 类型#const VOS_CHAR *，被比较的字符串2。取值范围为非空。
 * @param ulLen [IN] 类型#VOS_UINT32，被比较的字符数。取值范围为正整数。
 *
 * @retval #0                                   pscStr1等于pscStr2或pscStr1与pscStr2中有一个为空或ulLen为0。
 * @retval #大于0                               pscStr1大于pscStr2。
 * @retval #小于0                               pscStr1小于pscStr2。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  无
 */
extern VOS_INT32 VOS_strnicmp(const VOS_CHAR *pscStr1, const VOS_CHAR *pscStr2, VOS_UINT32 ulLen);

/**
 * @ingroup  vos_libc
 * @brief 将格式化数据写入到字符串中。
 *
 * @par 描述:
 * 将格式化数据写入到字符串中。
 *
 * @attention
 * <ul>
 * <li>用户保证格式化的缓存空间足够。</li>
 * <li>用户保证格式化控制字符串中的格式类型与可变参数类型匹配。</li>
 * <li>支持d、x、s、u、p几种格式化类型。</li>
 * </ul>
 *
 * @param pscStr [OUT] 类型#VOS_CHAR *，格式化的缓存。取值范围为非空。
 * @param pscFormat [IN] 类型#const VOS_CHAR *，格式化控制字符串。取值范围为非空。
 * @param argument [IN] 类型#va_list，指向可变参数列表的指针。取值范围为非空。
 *
 * @retval #-1                                  pscStr或pscFormat为空。
 * @retval #非负数                              返回写入的字符的个数。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  无
 */
extern VOS_INT32 VOS_vsprintf(VOS_CHAR *pscStr, const VOS_CHAR *pscFormat, va_list argument);

/**
 * @ingroup  vos_libc
 * @brief 将格式化数据写入到字符串中。
 *
 * @par 描述:
 * 将格式化数据写入到字符串中。
 *
 * @attention
 * <ul>
 * <li>用户保证格式化的缓存空间足够。</li>
 * <li>用户保证格式化控制字符串中的格式类型与可变参数类型匹配。</li>
 * <li>支持d、x、s、u、p几种格式化类型。</li>
 * </ul>
 *
 * @param pscStr [OUT] 类型#VOS_CHAR *，格式化的缓存。取值范围为非空。
 * @param pscFmt [IN] 类型#const VOS_CHAR *，格式化控制字符串。取值范围为非空。
 * @param ... [IN] 可选参数。
 *
 * @retval #-1                                  pscStr或pscFmt为空。
 * @retval #非负数                              返回写入的字符的个数。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  无
 */
extern VOS_INT32 VOS_sprintf(VOS_CHAR * pscStr, const VOS_CHAR *pscFmt, ...);

/**
 * @ingroup  vos_libc
 * @brief 根据可变参数列表指针，将格式化数据写入到字符串中。
 *
 * @par 描述:
 * 根据格式化的数据，写入固定个数的字符到字符串中。
 *
 * @attention
 * <ul>
 * <li>用户保证格式化的缓存空间足够。</li>
 * <li>用户保证格式化控制字符串中的格式类型与可变参数类型匹配。</li>
 * <li>字符个数包括结束符，也就是说该API只往缓存中写入uiMaxStrLen-1个字符，然后添加结束符。</li>
 * <li>支持d、x、s、u几种格式化类型。</li>
 * </ul>
 *
 * @param pscStr [OUT] 类型#VOS_CHAR *，格式化的缓存。取值范围为非空。
 * @param uiMaxStrLen [IN] 参数类型VOS_UINT32。表示格式化字符串的最大长度。取值范围为正整数。
 * @param pscFormat [IN] 类型#const VOS_CHAR *，格式化控制字符串。取值范围为非空。
 * @param arguments [IN] 类型#va_list，指向可变参数列表的指针。取值范围为非空。
 *
 * @retval #-1                                  pscStr或pscFormat为空或uiMaxStrLen为0或格式化后的字符数超过uiMaxStrLen。
 * @retval #非负数                              返回写入的字符的个数。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  无
 */
extern VOS_INT32 VOS_nvsprintf(VOS_CHAR *pscStr, VOS_UINT32 uiMaxStrLen, const VOS_CHAR *pscFormat, va_list arguments);

/**
 * @ingroup  vos_libc
 * @brief 将格式化数据写入到字符串中。
 *
 * @par 描述:
 * 根据格式化的数据，写入固定个数的字符到字符串中。
 *
 * @attention
 * <ul>
 * <li>用户保证格式化的缓存空间足够。</li>
 * <li>用户保证格式化控制字符串中的格式类型与可变参数类型匹配。</li>
 * <li>字符个数包括结束符，也就是说该API只往缓存中写入uiMaxStrLen-1个字符，然后添加结束符。</li>
 * <li>支持d、x、s、u几种格式化类型。</li>
 * </ul>
 *
 * @param pscStr [OUT] 类型#VOS_CHAR *，格式化的缓存。取值范围为非空。
 * @param uiMaxStrLen [IN] 参数类型VOS_UINT32。表示格式化字符串的最大长度。取值范围为正整数。
 * @param pscFmt [IN] 类型#const VOS_CHAR *，格式化控制字符串。取值范围为非空。
 * @param ... [IN] 可选参数。
 *
 * @retval #-1                                  pscStr或pscFmt为空或uiMaxStrLen为0或格式化后的字符数超过uiMaxStrLen。
 * @retval #非负数                              返回写入的字符的个数。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  无
 */
extern VOS_INT32 VOS_nsprintf(VOS_CHAR *pscStr, VOS_UINT32 uiMaxStrLen, const VOS_CHAR *pscFmt, ...);

#if (OS_OPTION_IO_INTF == YES)
/**
 * @ingroup  vos_libc
 * @brief 将格式化字符输出到串口。
 *
 * @par 描述:
 * 将格式化字符输出到串口。
 *
 * @attention
 * <ul>
 * <li>不支持中断中打印。</li>
 * <li>用户保证格式化控制字符串中的格式类型与可变参数类型匹配。</li>
 * <li>用户保证格式化后的字符数不超过512个，包括结束符。</li>
 * <li>支持c、d、i、x、s、%几种格式化类型。</li>
 * <li>本接口至少需要536字节的栈空间，用户保证调用用此接口的任务栈空间足够。</li>
 * </ul>
 *
 * @param pscFormat [IN] 类型#VOS_CHAR *，格式化的控制字符串。取值范围为非空。
 * @param ... [IN] 可选参数。
 *
 * @retval #-1                                  pscFormat为空、添加打印前缀失败、格式化后的字符数超过512或者字符输出失败。
 * @retval #VOS_OK                              0x00000000，字符输出成功。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  无
 */
extern VOS_INT32 vos_printf(VOS_CHAR *pscFormat, ...);

/**
 * @ingroup  vos_libc
 * @brief 将错误信息字符串打印到屏幕。
 *
 * @par 描述:
 * 将错误信息字符串打印到屏幕。
 *
 * @attention
 * <ul><li>用户保证格式化后的字符数不超过512个，包括结束符。</li></ul>
 *
 * @param s [IN] 类型#const VOS_CHAR *，错误信息字符串。
 *
 * @retval 无
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  无
 */
extern VOS_VOID perror(const VOS_CHAR *s);
#endif

/**
 * @ingroup  vos_libc
 * @brief 将字符串转换为有符号整数。
 *
 * @par 描述:
 * 将字符串pcStr转换为有符号整数，存储到pnVal中。
 *
 * @attention 无
 *
 * @param pcStr [IN] 类型#const VOS_CHAR *，要转换的原字符串。取值范围为非空。
 * @param pnVal [OUT] 类型#VOS_INT32 *，用于存储转换后的整数。取值范围为非空。
 *
 * @retval #VOS_ERROR                           0xFFFFFFFF，pcStr或pnVal为空。
 * @retval #VOS_OK                              0x00000000，转换成功。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_atoul
 */
extern VOS_INT32 VOS_atol(const VOS_CHAR *pcStr, VOS_INT32 *pnVal);

/**
 * @ingroup  vos_libc
 * @brief 把内存中指定长度的数据复制到目标内存处。
 *
 * @par 描述:
 * 拷贝pvSrc所指的内存内容前uvCount个字节到pvDest所指的地址上。
 *
 * @attention 无
 *
 * @param pvDest [IN/OUT] 类型#VOS_VOID *，目的内存。取值范围为非空。
 * @param pvSrc [IN] 类型#const VOS_VOID *，来源内存。取值范围为非空。
 * @param uvCount [IN] 类型#VOS_SIZE_T，拷贝的字节数。取值范围为正整数。
 *
 * @retval #VOS_NULL_PTR                        0xFFFFFFFF，pvDest与pSrcPtr中有一个为空或uvCount为0。
 * @retval #任意值                              目的内存的地址。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  无
 */
extern VOS_VOID * VOS_MemCpy(VOS_VOID *pvDest, const VOS_VOID *pvSrc, VOS_SIZE_T uvCount);

/**
 * @ingroup  vos_libc
 * @brief 把字符串中的所有小写字母转换成等价的大写字母。
 *
 * @par 描述:
 * 把给定字符串pcChar中的所有小写字母转换成等价的大写字母。
 *
 * @attention
 * <ul><li>如果给定的字母不在['a', 'z']的取值范围内，则不进行转换。</li></ul>
 *
 * @param pcChar [IN] 类型#VOS_CHAR *，需要转换的字符串，取值范围为非空。
 *
 * @retval 无
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_lowercase
 */
extern VOS_VOID VOS_uppercase(VOS_CHAR *pcChar);

/**
 * @ingroup  vos_libc
 * @brief 把字符串中的所有大写字母转换成等价的小写字母。
 *
 * @par 描述:
 * 把给定字符串pcChar中的所有大写字母转换成等价的小写字母。
 *
 * @attention
 * <ul><li>如果给定的字母不在['A', 'Z']的取值范围内，则不进行转换。</li></ul>
 *
 * @param pcChar [IN] 类型#VOS_CHAR *，需要转换的字符串，取值范围为非空。
 *
 * @retval 无
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_uppercase
 */
extern VOS_VOID VOS_lowercase(VOS_CHAR *pcChar);

/**
 * @ingroup  vos_libc
 * @brief 获取给定字符串的长度。
 *
 * @par 描述:
 * 获取给定字符串pcstr的长度，不包括结束符。
 *
 * @attention 无
 *
 * @param pscStr [IN] 类型#VOS_CHAR *，要获取长度的字符串。取值范围为非空。
 *
 * @retval #0，                                 0x00000000，pscStr为空。
 * @retval #正整数                              字符串长度。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  无
 */
extern VOS_SIZE_T VOS_StrLen(VOS_CHAR *pscStr);

/**
 * @ingroup  vos_libc
 * @brief 比较两个字符串。
 *
 * @par 描述:
 * 用户必须保证传入参数的有效性，如果pscStr1或pscStr2为空指针，则该接口返回0，此时与字符串相等时的返回值相同。
 *
 * @attention 无
 *
 * @param pscStr1 [IN] 类型#const VOS_CHAR *，被比较的字符串1。取值范围为非空。
 * @param pscStr2 [IN] 类型#const VOS_CHAR *，被比较的字符串2。取值范围为非空。
 *
 * @retval #0                                   pscStr1等于pscStr2或pscStr1与pscStr2中有一个为空。
 * @retval #大于0                               pscStr1串大于pscStr2。
 * @retval #小于0                               pscStr1串小于pscStr2。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  无
 */
extern VOS_INT32 VOS_StrCmp(const VOS_CHAR *pscStr1, const VOS_CHAR *pscStr2);

/**
 * @ingroup  vos_libc
 * @brief 将字符串按照给定分隔符进行分割。
 *
 * @par 描述:
 * 将字符串*ppcstringp按照pcdelim中给定的任一字符进行分割，被分割后*ppcstringp指向分割之后的下一字符串的起始地址。
 *
 * @attention
 * <ul><li>接口内部未对入参做有效性判断，需要用户保证传入参数的有效性。</li></ul>
 *
 * @param ppcstringp [IN] 类型#VOS_CHAR **，欲进行分割的字符串。取值范围为非空，且*ppcstringp为非空。
 * @param pcdelim [IN] 类型#const VOS_CHAR *，给定的分隔符字符串。取值范围为非空。
 *
 * @retval #VOS_NULL_PTR                        0x00000000，ppcstringp、*ppcstringp或pcdelim为空。
 * @retval #任意值                              传入*ppcstringp字符串的起始地址。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  无
 */
extern VOS_CHAR * VOS_strsep(register VOS_CHAR **ppcstringp, register const VOS_CHAR *pcdelim);

/**
 * @ingroup  vos_libc
 * @brief 将字符串格式("***.***.***.***")的IP地址转换为整数格式的IP地址。
 *
 * @par 描述:
 * 将传入的字符串格式的IP地址pscStr，转换为整数格式，转换结果存储到pulIpAddr指向的地址。
 *
 * @attention 无
 *
 * @param pscStr [IN] 类型#VOS_CHAR *，需要转换为整数类型的字符串格式的IP地址。取值范围为非空。
 * @param pulIpAddr [OUT] 类型#VOS_UINT32 *，存储转换后的整数。取值范围为非空。
 *
 * @retval #VOS_ERROR                           0xFFFFFFFF，pscStr与pulIpAddr中有一个为空或传入的字符串格式的IP地址不合法。
 * @retval #VOS_OK                              0x00000000，转换成功。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  无
 */
extern VOS_INT32 VOS_StrToIpAddr(VOS_CHAR *pscStr, VOS_UINT32 *pulIpAddr);

/**
 * @ingroup  vos_libc
 * @brief 将整数格式的IP地址转换为字符串格式("***.***.***.***")的IP地址。
 *
 * @par 描述:
 * 将传入的整数格式的IP地址ulAddr，转换为字符串格式，转换结果存储到pscStr指向的地址。
 *
 * @attention 无
 *
 * @param ulAddr [IN] 类型#VOS_UINT32，需要转换为字符串的整型IP地址。取值范围为任意值。
 * @param pscStr [OUT] 类型#VOS_CHAR *，用于存储转换后的字符串。取值范围为非空。
 *
 * @retval #VOS_NULL_PTR                        0x00000000，pscStr为空。
 * @retval #任意值                              转换后的字符串的地址。
 * @par 依赖:
 * <ul><li>vos_libc.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  无
 */
extern VOS_CHAR * VOS_IpAddrToStr(VOS_UINT32 ulAddr, VOS_CHAR *pscStr);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

#endif //__VOS_LIBC_H__

