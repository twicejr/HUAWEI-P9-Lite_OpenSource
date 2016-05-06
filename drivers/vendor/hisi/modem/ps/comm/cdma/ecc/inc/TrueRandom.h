#ifndef _LOIS_TRUERANDOM_H
#define _LOIS_TRUERANDOM_H

//本头文件仅在C++编译器中适用，当仅用C编译时，应该去掉extern "C"选项。

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif
//extern "C"   // C++ option, This line should be deleted when using with C compiler
//{
    /* 返回导频能量 */
    unsigned int cGetPower(void);
    /* 返回电池电量 */
    unsigned int cGetBattery(void);
    /* 返回场强 */
    unsigned int cGetRSSI(void);
    /* 返回信噪比 */
    unsigned int cGetEcio(void);
    /* 返回Pilot strength */
    unsigned int cGetPilotStrength(void);
    /* 返回时间 */
    unsigned int cGetTime(void);

    /* 获取一个随机数
     *
     * 参数：
     * [OUT] pbOut，用于获取随机数的缓冲区
     * [IN] iLen，pbOut缓冲区的长度，即要获取的随机数的字节长度
     *
     * 返回值：
     * 实际返回的随机数字节长度
    */
    int TrueRandom (unsigned char *pbOut, int iLen);
//}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif // #ifndef _LOIS_TRUERANDOM_H

