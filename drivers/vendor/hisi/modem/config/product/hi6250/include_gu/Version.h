

#ifndef __VERSION_H__
#define __VERSION_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

#define PRODUCT_ID                      "BALONGSPC2H"
#define HARD_VERSION                    "BALONGSPC2H"
#define PRODUCT_VERSION                 "V3R1C1B020"


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* end of Version.h */
