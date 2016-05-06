/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名      : ScApSec.c
  版 本 号      : 初稿
  作    者      : h59254
  生成日期      : 2012年8月27日
  最近修改      :
  功能描述      : 该C文件给出了ScApSec模块的实现
  函数列表      :
  修改历史      :
  1.日    期    : 2012年8月27日
    作    者    : h59254
    修改内容    : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "ScApSec.h"
#include "ScCtx.h"
#include "NVIM_Interface.h"
#include "omnvinterface.h"
#include "mdrv.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/*lint -e767 修改人:胡骏 00184875;原因:Log打印 */
#define    THIS_FILE_ID        PS_FILE_ID_SC_APSEC_C
/*lint +e767 修改人:胡骏 00184875;*/

/*****************************************************************************
  2 全局变量声明
*****************************************************************************/
VOS_UINT8  g_aucSecItemCasID[]          = {0x00, 0x0F};
VOS_UINT8  g_aucSecItemKlReal[]         = {0xF0, 0x0D, 0xB5, 0xA3, 0xCC, 0xF6, 0xEC, 0x55,
                                           0x1F, 0x08, 0x72, 0x55, 0xBB, 0x55, 0x65, 0x13};
VOS_UINT8  g_aucSecItemKlTemp[]         = {0xF0, 0x0D, 0xB5, 0xA3, 0xCC, 0xF6, 0xEC, 0x55,
                                           0x1F, 0x08, 0x72, 0x55, 0xBB, 0x55, 0x65, 0x13};
VOS_UINT8  g_aucTestSecItemMePubKey[]   = {0xE2, 0x89, 0x67, 0x2A, 0xDC, 0x39, 0xD2, 0x97,
                                           0xB1, 0x8C, 0xF4, 0xF5, 0xAC, 0x04, 0x91, 0x1A,
                                           0xB6, 0x36, 0xDB, 0xAC, 0xBA, 0x68, 0xF6, 0x4B,
                                           0xD8, 0x7E, 0x53, 0x74, 0x65, 0x3A, 0x62, 0x20,
                                           0x68, 0xBA, 0xB7, 0x51, 0x3B, 0x8C, 0x63, 0x1F,
                                           0xA1, 0xFC, 0x04, 0xE9, 0x19, 0x32, 0xE6, 0x97,
                                           0xF7, 0xE3, 0xF0, 0xF6, 0x1E, 0x2A, 0xE4, 0x2D,
                                           0xD1, 0xA0, 0x21, 0xDA, 0x26, 0xC6, 0x16, 0xDA,
                                           0x9E, 0xF6, 0x58, 0xBC, 0x33, 0x55, 0xF3, 0xE0,
                                           0x8D, 0xA4, 0x26, 0x8E, 0x2F, 0xBF, 0x16, 0x79,
                                           0x21, 0xA1, 0x10, 0x8B, 0x52, 0x94, 0x36, 0x9A,
                                           0x2A, 0xA6, 0xCC, 0x68, 0x6B, 0x3D, 0x2E, 0xD6,
                                           0x84, 0xC2, 0x18, 0x6C, 0xCD, 0xFB, 0xA2, 0xF3,
                                           0x86, 0x78, 0x52, 0xDD, 0xD9, 0x6E, 0xDC, 0x24,
                                           0x59, 0x6D, 0xA0, 0x61, 0x04, 0x83, 0x09, 0x9F,
                                           0x10, 0x6A, 0xA8, 0x86, 0x5E, 0xFA, 0x79, 0xA1};
VOS_UINT8  g_aucTestSecItemMePriKey[]   = {0xC0, 0x71, 0xAD, 0x7C, 0xD1, 0x9D, 0x25, 0x73,
                                           0xCC, 0x57, 0x4C, 0x79, 0xAF, 0x6A, 0x29, 0xC2,
                                           0xA1, 0x6C, 0xB4, 0xED, 0x65, 0x66, 0x69, 0x65,
                                           0x41, 0x42, 0xFF, 0xAE, 0x6F, 0x98, 0x4B, 0x67,
                                           0xF0, 0xD0, 0x3D, 0x8E, 0xFA, 0xA1, 0x66, 0x4B,
                                           0xA7, 0x16, 0x2B, 0x2D, 0xC2, 0x44, 0x65, 0x74,
                                           0x50, 0x18, 0x09, 0xC9, 0x6B, 0x13, 0x50, 0xC8,
                                           0x43, 0xBE, 0x5F, 0x43, 0xAD, 0x90, 0xB6, 0x33,
                                           0xE4, 0xD6, 0x7E, 0x95, 0x5F, 0xCF, 0x8B, 0x09,
                                           0x8C, 0xD6, 0x66, 0x43, 0xFD, 0xA6, 0xB8, 0x55,
                                           0xDA, 0x14, 0x49, 0xF2, 0xB6, 0xB8, 0x4D, 0x36,
                                           0xE0, 0x70, 0x0C, 0x0D, 0xFA, 0xBB, 0x60, 0x41,
                                           0x82, 0x7C, 0x4C, 0xEE, 0xE4, 0x5C, 0x14, 0xFC,
                                           0x33, 0x76, 0x75, 0xF3, 0x3A, 0x4E, 0xA5, 0xAC,
                                           0xE4, 0x6C, 0xD7, 0xC2, 0xB4, 0xD8, 0xD7, 0xAE,
                                           0x4F, 0x03, 0x05, 0x92, 0x63, 0x92, 0x0B, 0x81};
VOS_UINT8  g_aucTestSecItemMeSign[]     = {0x54, 0x44, 0xE4, 0x6E, 0xE0, 0xE3, 0xC0, 0xB2,
                                           0x94, 0x70, 0xE0, 0x6D, 0x71, 0xD2, 0xEB, 0x2B,
                                           0x61, 0x3B, 0x80, 0x21, 0xAA, 0x66, 0x2A, 0x93,
                                           0x64, 0xE9, 0xA5, 0x55, 0x01, 0x5F, 0x5B, 0xFB,
                                           0x8F, 0x35, 0x87, 0xB4, 0xBD, 0x5B, 0x9D, 0xA1,
                                           0xB4, 0x8E, 0xCB, 0x3C, 0xAA, 0xB8, 0xA6, 0x3D,
                                           0x01, 0xC9, 0xA4, 0x17, 0x81, 0xB1, 0xC0, 0xF8,
                                           0x5F, 0xBE, 0xF5, 0xA3, 0x96, 0x5D, 0xFB, 0x53,
                                           0xF4, 0x5D, 0xEF, 0x71, 0x4B, 0xBB, 0x84, 0x91,
                                           0x9B, 0x17, 0x56, 0x5F, 0xB9, 0x97, 0x15, 0x85,
                                           0x09, 0x66, 0xFF, 0xBA, 0xA4, 0xA9, 0x93, 0xCE,
                                           0x16, 0xD4, 0x65, 0x29, 0xC5, 0xA0, 0xA8, 0x00,
                                           0x5D, 0xAB, 0xC1, 0xA5, 0xB8, 0x52, 0xF9, 0x4B,
                                           0x7C, 0xAB, 0xB6, 0x57, 0xFA, 0xCF, 0xF9, 0xF9,
                                           0xFA, 0x64, 0xF5, 0x77, 0x77, 0x46, 0x32, 0xFE,
                                           0x8B, 0xE2, 0x30, 0x16, 0x6E, 0x1E, 0x10, 0xEE,
                                           0xB6, 0x3F, 0x2F, 0x57, 0x07, 0x2F, 0x8F, 0x3C,
                                           0xA4, 0x03, 0x09, 0x33, 0x1E, 0x26, 0x4C, 0x91,
                                           0xC4, 0x3B, 0x73, 0x3D, 0x97, 0xB3, 0x24, 0x27,
                                           0xE6, 0x32, 0xDB, 0x9E, 0x73, 0xF0, 0x1B, 0x12,
                                           0x86, 0x4C, 0x38, 0xA8, 0x58, 0xDD, 0xDE, 0xA6,
                                           0xAB, 0xD0, 0x55, 0x2E, 0x8A, 0x83, 0x78, 0xEE,
                                           0xC8, 0x61, 0x5A, 0x8B, 0x3B, 0xAA, 0x98, 0x5E,
                                           0x78, 0xD2, 0x27, 0xFC, 0x58, 0x95, 0xCD, 0xBC,
                                           0xC4, 0x46, 0x42, 0x98, 0x83, 0x2A, 0x13, 0x6D,
                                           0xB5, 0x9E, 0xBA, 0xB5, 0xBB, 0x33, 0x04, 0xD6,
                                           0x7E, 0xE4, 0x4E, 0x6A, 0xB0, 0xE5, 0x52, 0xD0,
                                           0x7F, 0xF9, 0x31, 0xE1, 0xB4, 0x1F, 0xAE, 0x0A,
                                           0xA7, 0x10, 0x68, 0x31, 0x5D, 0x33, 0xBC, 0xD6,
                                           0x3E, 0x8E, 0x15, 0xB1, 0x00, 0xF5, 0xC0, 0x9A,
                                           0x73, 0x6F, 0xA3, 0x32, 0xE4, 0x2C, 0xE3, 0x50,
                                           0x5D, 0x3F, 0xF5, 0xF5, 0x8E, 0xAF, 0xEA, 0x1C};
VOS_UINT8  g_aucDCMSecItemMePubKey[]    = {0x7B, 0xD4, 0x43, 0x88, 0xCA, 0xEB, 0xC5, 0xBA,
                                           0x81, 0x12, 0x62, 0x31, 0x19, 0xEC, 0x5B, 0x7C,
                                           0x19, 0x3D, 0x4E, 0x6A, 0x40, 0x9B, 0xF6, 0xD4,
                                           0xC5, 0x5A, 0xD5, 0x46, 0x6F, 0xED, 0x56, 0xE9,
                                           0xF7, 0xA2, 0xAC, 0x3C, 0x53, 0xCF, 0xEB, 0xDF,
                                           0x3D, 0x9C, 0xAF, 0x8A, 0x2C, 0x2A, 0x45, 0xD5,
                                           0x90, 0x3F, 0x85, 0x7A, 0x97, 0x2F, 0xA8, 0x9E,
                                           0x67, 0x89, 0x44, 0x2A, 0xB1, 0x0A, 0xF3, 0x2A,
                                           0xD2, 0xCC, 0x86, 0xDD, 0xA2, 0x25, 0xE9, 0xED,
                                           0xC2, 0x89, 0x64, 0x7E, 0x71, 0xCC, 0xE4, 0xC9,
                                           0x79, 0x9E, 0xDF, 0x48, 0x4E, 0xC8, 0x14, 0xB5,
                                           0xA9, 0x51, 0x45, 0xB7, 0x4D, 0xC5, 0xD7, 0x97,
                                           0x6B, 0x8E, 0xFE, 0x66, 0xC0, 0x9F, 0xB7, 0x91,
                                           0xA6, 0xFD, 0x6E, 0x6F, 0xDE, 0x64, 0x9C, 0x92,
                                           0xEB, 0x9E, 0xC0, 0x3C, 0xA9, 0x81, 0xBF, 0x2A,
                                           0xE2, 0xE0, 0x6D, 0x74, 0x28, 0x82, 0xE8, 0x31};
VOS_UINT8  g_aucDCMSecItemMePriKey[]    = {0x56, 0xE3, 0xEC, 0x7B, 0xB9, 0x80, 0x55, 0xDF,
                                           0xF8, 0x20, 0x11, 0x3C, 0xC9, 0x26, 0xFC, 0x4F,
                                           0x09, 0x5A, 0xE6, 0x82, 0x52, 0x51, 0xDE, 0x93,
                                           0x10, 0xE5, 0x1B, 0x10, 0xF1, 0x0B, 0x46, 0xD8,
                                           0xA8, 0x46, 0xC2, 0xBB, 0x16, 0x48, 0xA9, 0x07,
                                           0x9E, 0x31, 0x2B, 0x50, 0x36, 0x8B, 0x77, 0x33,
                                           0x53, 0xA3, 0xEF, 0x22, 0xC5, 0xA1, 0xD0, 0x9D,
                                           0x4E, 0xA3, 0x98, 0x6C, 0xA8, 0x8C, 0xB9, 0x72,
                                           0x0E, 0x6C, 0xA6, 0x76, 0x2C, 0xC2, 0xF6, 0xBC,
                                           0x60, 0xA6, 0xE5, 0xDE, 0x48, 0xC7, 0xD8, 0x1E,
                                           0xD1, 0x21, 0xBD, 0x0A, 0xAB, 0x5F, 0x90, 0x61,
                                           0x8A, 0xED, 0xD0, 0x0F, 0x29, 0x96, 0xB7, 0xB3,
                                           0xBC, 0x21, 0x43, 0x36, 0x0A, 0x1C, 0x3F, 0xAA,
                                           0xA3, 0x0D, 0x0F, 0xD9, 0xC3, 0x71, 0x32, 0x82,
                                           0xA2, 0x3C, 0x1E, 0xA1, 0x6A, 0xE9, 0x09, 0x01,
                                           0xBC, 0xCE, 0x65, 0xAE, 0x30, 0x35, 0xEC, 0x5D};
VOS_UINT8  g_aucDCMSecItemMeSign[]      = {0x16, 0x21, 0xDF, 0xC2, 0xE7, 0xB8, 0xD6, 0x10,
                                           0x32, 0x10, 0x13, 0xD7, 0x19, 0x45, 0x6F, 0xFF,
                                           0x7B, 0xB3, 0x24, 0xEA, 0x72, 0x36, 0x51, 0xC6,
                                           0x40, 0x37, 0x12, 0x19, 0x5B, 0xFF, 0xC8, 0xF8,
                                           0xBC, 0x89, 0xAC, 0x8F, 0x67, 0x3B, 0xF1, 0x76,
                                           0x2E, 0x1B, 0x65, 0x86, 0xA2, 0x4A, 0x1E, 0x89,
                                           0x54, 0x45, 0x25, 0xB9, 0x16, 0x42, 0x17, 0xE4,
                                           0x09, 0xE6, 0x83, 0x5D, 0xC9, 0xF3, 0xCB, 0x16,
                                           0x37, 0x5E, 0xCD, 0x22, 0x0E, 0x5D, 0xF3, 0xA8,
                                           0xF6, 0x9D, 0x65, 0x2B, 0x57, 0xF9, 0x13, 0xF1,
                                           0xEF, 0x0F, 0x28, 0x3D, 0x96, 0xD5, 0x2A, 0xFF,
                                           0xB6, 0x59, 0x89, 0xAC, 0xCB, 0x50, 0x4C, 0x9D,
                                           0xE6, 0x0B, 0x09, 0xF7, 0xB4, 0x6F, 0xFB, 0x05,
                                           0xB2, 0x5C, 0x17, 0x3B, 0xBB, 0x6D, 0x26, 0x11,
                                           0x1E, 0x70, 0x64, 0x95, 0xF7, 0xD5, 0x5F, 0x5B,
                                           0x91, 0xC1, 0x9D, 0x87, 0x91, 0x36, 0xC7, 0x82,
                                           0xB9, 0xC0, 0xDC, 0x1A, 0xBC, 0x34, 0x2A, 0x2E,
                                           0x25, 0x4B, 0x39, 0x31, 0x9E, 0x6A, 0x7C, 0x71,
                                           0xF9, 0xA4, 0x47, 0x56, 0x45, 0x1A, 0xCB, 0x3E,
                                           0x5D, 0x22, 0xF1, 0x18, 0x43, 0xFC, 0x46, 0xA4,
                                           0xBE, 0xF8, 0x51, 0x69, 0x24, 0x83, 0x97, 0x0E,
                                           0x63, 0x12, 0x20, 0xD7, 0x85, 0x0B, 0x77, 0x58,
                                           0xC7, 0xCC, 0x3B, 0x30, 0xF7, 0xB9, 0x72, 0x87,
                                           0x66, 0x54, 0x10, 0xA5, 0x94, 0xA5, 0x5B, 0x53,
                                           0xEC, 0x00, 0x9C, 0xBD, 0x3E, 0x4B, 0xBA, 0x40,
                                           0x09, 0xA3, 0xFD, 0x7E, 0x44, 0x17, 0x81, 0x8B,
                                           0x8B, 0xB1, 0x2C, 0x5F, 0x4A, 0x55, 0x67, 0xF2,
                                           0xBC, 0x93, 0xC3, 0xE0, 0x0A, 0xEE, 0x98, 0x8B,
                                           0x00, 0xDE, 0x50, 0x15, 0xE0, 0xA5, 0xA0, 0xC2,
                                           0x21, 0x51, 0xA1, 0x25, 0xBE, 0x31, 0xCB, 0x8C,
                                           0xFA, 0xF3, 0x63, 0xB8, 0x76, 0xBC, 0xCB, 0xFF,
                                           0xF5, 0xA5, 0x5C, 0x86, 0x85, 0x2F, 0x2F, 0xE0};

/* 安全存储项默认值表 */
SC_APSEC_SECTURE_ITEM_STRU        g_astSecItemDefaultTbl[][SC_SECURITY_ITEM_NUM] = {
   {{SC_APSEC_ITME_UE_IMEI_I,        0,                                 VOS_NULL_PTR},
    {SC_APSEC_ITME_MMB_KL_TEMP,      sizeof(g_aucSecItemKlTemp),        g_aucSecItemKlTemp},
    {SC_APSEC_ITME_MMB_KL_REAL,      sizeof(g_aucSecItemKlReal),        g_aucSecItemKlReal},
    {SC_APSEC_ITME_MMB_CASID,        sizeof(g_aucSecItemCasID),         g_aucSecItemCasID},
    {SC_APSEC_ITME_MMB_ME_PUBKEY,    sizeof(g_aucTestSecItemMePubKey),  g_aucTestSecItemMePubKey},
    {SC_APSEC_ITME_MMB_ME_PRIVKEY,   sizeof(g_aucTestSecItemMePriKey),  g_aucTestSecItemMePriKey},
    {SC_APSEC_ITME_MMB_ME_SIGNATURE, sizeof(g_aucTestSecItemMeSign),    g_aucTestSecItemMeSign},
    {SC_APSEC_ITME_MMB_SEC_SRV_STAT, 0,                                 VOS_NULL_PTR},
    {SC_APSEC_ITME_MMB_SEC_NITZ,     0,                                 VOS_NULL_PTR},
    {SC_APSEC_ITME_MMB_SEC_RTC,      0,                                 VOS_NULL_PTR},
    {SC_APSEC_ITME_MMB_NUM,          0,                                 VOS_NULL_PTR},
    {SC_APSEC_ITME_MMB_RESERVED2,    0,                                 VOS_NULL_PTR},
    {SC_APSEC_ITME_MMB_RESERVED3,    0,                                 VOS_NULL_PTR},
    {SC_APSEC_ITME_MMB_RESERVED4,    0,                                 VOS_NULL_PTR},
    {SC_APSEC_ITME_MMB_RESERVED5,    0,                                 VOS_NULL_PTR},
    {SC_APSEC_ITME_MMB_RESERVED6,    0,                                 VOS_NULL_PTR}},
   {{SC_APSEC_ITME_UE_IMEI_I,        0,                                 VOS_NULL_PTR},
    {SC_APSEC_ITME_MMB_KL_TEMP,      sizeof(g_aucSecItemKlTemp),        g_aucSecItemKlTemp},
    {SC_APSEC_ITME_MMB_KL_REAL,      sizeof(g_aucSecItemKlReal),        g_aucSecItemKlReal},
    {SC_APSEC_ITME_MMB_CASID,        sizeof(g_aucSecItemCasID),         g_aucSecItemCasID},
    {SC_APSEC_ITME_MMB_ME_PUBKEY,    sizeof(g_aucDCMSecItemMePubKey),   g_aucDCMSecItemMePubKey},
    {SC_APSEC_ITME_MMB_ME_PRIVKEY,   sizeof(g_aucDCMSecItemMePriKey),   g_aucDCMSecItemMePriKey},
    {SC_APSEC_ITME_MMB_ME_SIGNATURE, sizeof(g_aucDCMSecItemMeSign),     g_aucDCMSecItemMeSign},
    {SC_APSEC_ITME_MMB_SEC_SRV_STAT, 0,                                 VOS_NULL_PTR},
    {SC_APSEC_ITME_MMB_SEC_NITZ,     0,                                 VOS_NULL_PTR},
    {SC_APSEC_ITME_MMB_SEC_RTC,      0,                                 VOS_NULL_PTR},
    {SC_APSEC_ITME_MMB_NUM,          0,                                 VOS_NULL_PTR},
    {SC_APSEC_ITME_MMB_RESERVED2,    0,                                 VOS_NULL_PTR},
    {SC_APSEC_ITME_MMB_RESERVED3,    0,                                 VOS_NULL_PTR},
    {SC_APSEC_ITME_MMB_RESERVED4,    0,                                 VOS_NULL_PTR},
    {SC_APSEC_ITME_MMB_RESERVED5,    0,                                 VOS_NULL_PTR},
    {SC_APSEC_ITME_MMB_RESERVED6,    0,                                 VOS_NULL_PTR}},
};

/*****************************************************************************
  3 函数申明
*****************************************************************************/


/*****************************************************************************
 函 数 名  : SC_APSEC_EncryptItem
 功能描述  : 安全存储项更新接口
 输入参数  : pucSrc: 未加密数据
             ulItemLen: item的长度
 输出参数  : pucDest:加密后密文
 返 回 值  : VOS_UINT32
 修改历史      :
  1.日    期   : 2012年8月27日
    作    者   : h59254
    修改内容   : V7R1C50 ISDB安全存储项目新增
*****************************************************************************/
VOS_UINT32  SC_APSEC_EncryptItem(
    VOS_UINT32                          ulItemLen,
    const VOS_CHAR                     *pucSrc,
    VOS_CHAR                           *pucDest)
{
    SC_APSEC_ENCRYPT_STRU               stEncrypt;
    VOS_INT                             lHashLen;
    VOS_INT32                           lResult;
    VOS_UINT32                          ulKeyLen;
    VOS_UINT8                           aucKey[SC_KEY_LEN];
    VOS_INT                             lEncrypeCodeLen;


    ulKeyLen                            =   SC_KEY_LEN;

    /* 生成ASSK */
    if (SC_ERROR_CODE_NO_ERROR != SC_COMM_GenerateKey(SC_ASSK_STRING, SC_ASSK_STRLEN, aucKey, ulKeyLen))
    {
        SC_ERROR_LOG("SC_APSEC_ItemEncrypt: SC_COMM_GenerateKey is failed.");

        return VOS_ERR;
    }

    /* 除固定PADDING填充C以外，其它默认清空为全0 */
    /*lint -e534*/
    VOS_MemSet((VOS_VOID*)(stEncrypt.aucEncryptContent),
                           0,
                           SC_SECURITY_ITEM_LENGTH_SIZE + SC_SECURITY_ITEM_CONTENT_SIZE + SC_SECURITY_ITEM_HASH_SIZE);

    VOS_MemSet((VOS_VOID*)(stEncrypt.aucEncryptContent + SC_SECURITY_ITEM_LENGTH_SIZE + SC_SECURITY_ITEM_CONTENT_SIZE + SC_SECURITY_ITEM_HASH_SIZE),
               SC_SECURITY_ITEM_PADDING_VALUE,
               SC_SECURITY_ITEM_PADDING_SIZE);
    /*lint +e534*/

    lHashLen                            =   SC_HASH_LEN;

    /* 填充长度和内容信息到结构体中准备进行加密 */
    *(VOS_UINT32 *)stEncrypt.aucEncryptContent              =   ulItemLen;

    /*lint -e534*/
    VOS_MemCpy(stEncrypt.aucEncryptContent + SC_SECURITY_ITEM_LENGTH_SIZE, pucSrc, ulItemLen);
    /*lint +e534*/

    /* 对长度信息和内容字段(全部256个字节)计算128位的HASH值 */
    lResult = mdrv_crypto_hash((VOS_CHAR*)(stEncrypt.aucEncryptContent),
                          (VOS_INT)(SC_SECURITY_ITEM_CONTENT_SIZE + SC_SECURITY_ITEM_LENGTH_SIZE),
                          CRYPTO_ALGORITHM_SHA256,
                          (VOS_CHAR *)(stEncrypt.aucEncryptContent + SC_SECURITY_ITEM_LENGTH_SIZE + SC_SECURITY_ITEM_CONTENT_SIZE),
                          &lHashLen);


    /* 如果DRV计算返回的结果不是OK或者DRV计算出来的HASH不是16字节 */
    if ((VOS_OK != lResult)
        || (SC_HASH_LEN != lHashLen))
    {
        SC_ERROR2_LOG("SC_APSEC_ItemEncrypt: mdrv_crypto_hash is Failed.", lResult, lHashLen);

        /* 返回HASH生成失败 */
        return VOS_ERR;
    }

    /* AES_ECB(hash,ASSK) */
    lEncrypeCodeLen =   sizeof(SC_APSEC_ENCRYPT_STRU);

    lResult = mdrv_crypto_enc((VOS_CHAR*)(stEncrypt.aucEncryptContent),
                             sizeof(SC_APSEC_ENCRYPT_STRU),
                             CRYPTO_ENCRYPT_ALGORITHM_AES_ECB,
                             (VOS_CHAR *)aucKey,
                             (VOS_INT)ulKeyLen,
                             (VOS_CHAR *)pucDest,
                             &lEncrypeCodeLen);

    /* 算法返回失败或长度不为SC_APSEC_ENCRYPT_STRU的大小 */
    if ((sizeof(SC_APSEC_ENCRYPT_STRU) != lEncrypeCodeLen)
        || (VOS_OK != lResult))
    {
        SC_ERROR2_LOG("SC_APSEC_ItemEncrypt: mdrv_crypto_enc is failed.", lResult, lEncrypeCodeLen);

        return VOS_ERR;
    }

    return VOS_OK;
}



/*****************************************************************************
 函 数 名  : SC_APSEC_UpdateSecItem
 功能描述  : 安全存储项更新接口
 输入参数  : pstSecItem: 需要更新的安全存储项内容
             enSecItemId:安全存储项ID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 修改历史      :
  1.日    期   : 2012年8月27日
    作    者   : h59254
    修改内容   : V7R1C50 ISDB安全存储项目新增
*****************************************************************************/
VOS_UINT32  SC_APSEC_UpdateSecItem(
    SC_APSEC_ITME_ENUM_UINT32           enSecItemId,
    SC_APSEC_DEFAULT_ITEM_STRU         *pstSecItem)
{
    SC_APSEC_DEFAULT_ITEM_STRU          stDefaulItem;
    SC_APSEC_ITEM_STRU                 *pstSecItemAddr;
    SC_CONTEXT_STRU                    *pstScContextAddr;
    VOS_CHAR                           *pucFile;
    VOS_CHAR                           *pucTmp;
    VOS_UINT32                          ulResult;
    VOS_INT                             lHashLen;
    VOS_INT32                           lResult;
    VOS_UINT32                          i;

    /* 为整个文件分配内存，后续一次写入 */
    pucFile         =   (VOS_CHAR *)VOS_MemAlloc(CCPU_PID_PAM_OM,
                                                 DYNAMIC_MEM_PT,
                                                 SC_SECURITY_ITEM_NUM * sizeof(SC_APSEC_ENCRYPT_STRU));

    if (VOS_NULL_PTR == pucFile)
    {
        SC_ERROR_LOG("SC_APSEC_UpdateSecItem: Alloc memory failed.");

        return VOS_ERR;
    }

    /* 写入前先做初始化，失败了就按全部存储项为空处理 */
    if (VOS_OK != SC_APSEC_InitDualBackFile())
    {
        SC_ERROR_LOG("SC_APSEC_UpdateSecItem: SC_APSEC_InitDualBackFile fail.");
    }

    /* 根据内存中的数据重新生成文件内存。即使全局变量中的
       内容全部是空的(比如第一次写入也没关系)，安全存储项内容按全0处理 */
    pstSecItemAddr  = SC_CTX_GetApSecItemBaseAddr();

    for (i = 0; i < SC_SECURITY_ITEM_NUM; i++)
    {
        /* 如果某项内容为空，用全0来计算 */
        if (0 == pstSecItemAddr->ulItemLen)
        {
            /*lint -e534*/
            VOS_MemSet((VOS_VOID *)stDefaulItem.aucContent, 0, SC_SECURITY_ITEM_CONTENT_SIZE);
            /*lint +e534*/
            pucTmp  = (VOS_CHAR *)stDefaulItem.aucContent;
        }
        else
        {
            pucTmp  = pstSecItemAddr->pucContent;
        }

        if (VOS_OK != SC_APSEC_EncryptItem(pstSecItemAddr->ulItemLen,
                                            pucTmp,
                                            pucFile + (i * sizeof(SC_APSEC_ENCRYPT_STRU))))
        {
            SC_ERROR_LOG("SC_APSEC_UpdateSecItem: SC_APSEC_EncryptItem failed.");

            /*lint -e534*/
            VOS_MemFree(CCPU_PID_PAM_OM, pucFile);
            /*lint +e534*/

            return VOS_ERR;
        }

        pstSecItemAddr++;
    }


    /* 对需要写入的安全存储项计算加密 */
    if (VOS_OK != SC_APSEC_EncryptItem(pstSecItem->ulItemLen,
                                        (VOS_CHAR *)pstSecItem->aucContent,
                                        pucFile + (enSecItemId * sizeof(SC_APSEC_ENCRYPT_STRU))))
    {
        SC_ERROR_LOG("SC_APSEC_UpdateSecItem: SC_APSEC_EncryptItem failed.");

        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pucFile);
        /*lint +e534*/

        return VOS_ERR;
    }

    /* 双文件备份写入 */
    pstScContextAddr=   SC_CTX_GetScCtxAddr();

    ulResult        =   SC_COMM_WriteFile(pstScContextAddr->stScApSecGlobalVar.pApSecFileA,
                                          (VOS_UINT8 *)pucFile,
                                          SC_SECURITY_ITEM_NUM * sizeof(SC_APSEC_ENCRYPT_STRU));

    ulResult        |=  SC_COMM_WriteFile(pstScContextAddr->stScApSecGlobalVar.pApSecFileC,
                                          (VOS_UINT8 *)pucFile,
                                          SC_SECURITY_ITEM_NUM * sizeof(SC_APSEC_ENCRYPT_STRU));

    /*lint -e534*/
    VOS_MemFree(CCPU_PID_PAM_OM, pucFile);
    /*lint +e534*/

    if (VOS_OK != ulResult)
    {
        SC_ERROR_LOG("SC_APSEC_UpdateSecItem: Dual back file write failed.");

        return VOS_ERR;
    }

    /* 写入文件成功，同步到内存中 */
    pstSecItemAddr                  =   SC_CTX_GetApSecItemBaseAddr();
    pstSecItemAddr                  +=  enSecItemId;

    pstSecItemAddr->ulItemLen       =   pstSecItem->ulItemLen;

    /* 释放原先内存中的数据，重新拷贝数据 */
    if (VOS_NULL_PTR != pstSecItemAddr->pucContent)
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstSecItemAddr->pucContent);
        /*lint +e534*/
    }

    pstSecItemAddr->pucContent      =   (VOS_CHAR *)VOS_MemAlloc(CCPU_PID_PAM_OM,
                                                                 STATIC_MEM_PT,
                                                                 pstSecItemAddr->ulItemLen);

    if (VOS_NULL_PTR == pstSecItemAddr->pucContent)
    {
        SC_ERROR_LOG("SC_APSEC_UpdateSecItem: Alloc memory fail.");

        return VOS_ERR;
    }

    /* 对长度信息和内容字段(全部256个字节)计算128位的HASH值 */
    lHashLen = SC_HASH_LEN;

    lResult = mdrv_crypto_hash((VOS_CHAR*)pstSecItem,
                          (VOS_INT)(SC_SECURITY_ITEM_CONTENT_SIZE + SC_SECURITY_ITEM_LENGTH_SIZE),
                          CRYPTO_ALGORITHM_SHA256,
                          (VOS_CHAR *)(pstSecItem->aucHash),
                          &lHashLen);


    /* 如果DRV计算返回的结果不是OK或者DRV计算出来的HASH不是16字节 */
    if ((VOS_OK != lResult)
        || (SC_HASH_LEN != lHashLen))
    {
        SC_ERROR2_LOG("SC_APSEC_UpdateSecItem: mdrv_crypto_hash is Failed.", lResult, lHashLen);

        /* 返回HASH生成失败 */
        return VOS_ERR;
    }

    /* 拷贝数据和HASH到内存中，并设置文件初始化状态 */
    /*lint -e534*/
    VOS_MemCpy(pstSecItemAddr->pucContent, pstSecItem->aucContent, pstSecItem->ulItemLen);
    VOS_MemCpy(pstSecItemAddr->aucHash, pstSecItem->aucHash, SC_SECURITY_ITEM_HASH_SIZE);
    /*lint +e534*/

    SC_APSEC_SetFileInitState(SC_SECURITY_FILE_STATE_INIT);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : SC_APSEC_GetFileInitState
 功能描述  : 获取双备份文件初始化状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 双备份文件初始化状态
 修改历史      :
  1.日    期   : 2012年8月30日
    作    者   : h59254
    修改内容   : V7R1C50 ISDB安全存储项目新增
*****************************************************************************/
VOS_UINT32  SC_APSEC_GetFileInitState(VOS_VOID)
{
    VOS_UINT32                         *pulFileInitState;

    pulFileInitState                    =   SC_CTX_GetApSecInitStateAddr();

    return *pulFileInitState;
}

/*****************************************************************************
 函 数 名  : SC_APSEC_SetFileInitState
 功能描述  : 设置双备份文件初始化状态
 输入参数  : ulState:双备份文件初始化状态
 输出参数  : 无
 返 回 值  : 无
 修改历史      :
  1.日    期   : 2012年8月30日
    作    者   : h59254
    修改内容   : V7R1C50 ISDB安全存储项目新增
*****************************************************************************/
VOS_VOID  SC_APSEC_SetFileInitState(SC_APSEC_FILE_STATE_INIT_ENUM_UINT32 ulState)
{
    VOS_UINT32                         *pulFileInitState;

    pulFileInitState                    =   SC_CTX_GetApSecInitStateAddr();

    *pulFileInitState                   =   ulState;

    return;
}

/*****************************************************************************
 函 数 名  : SC_APSEC_ReadEncryptFile
 功能描述  : 备份加密文件读取到内存中
 输入参数  : pucFile:文件路径
 输出参数  : ppstEncryptFile:文件内容在内存中保存的地址
 返 回 值  : 加密文件在内存中的地址
 修改历史      :
  1.日    期   : 2012年8月31日
    作    者   : h59254
    修改内容   : V7R1C50 ISDB安全存储项目新增
*****************************************************************************/
SC_APSEC_ENCRYPT_STRU*  SC_APSEC_ReadEncryptFile(VOS_CHAR *pucFile)

{
    SC_APSEC_ENCRYPT_STRU              *pstEncryptFile;

    /* 按文件大小申请内存，将所有内容读取到内存中 */
    pstEncryptFile  =   (SC_APSEC_ENCRYPT_STRU *)VOS_MemAlloc(CCPU_PID_PAM_OM,
                                                              DYNAMIC_MEM_PT,
                                                              SC_SECURITY_ITEM_NUM * sizeof(SC_APSEC_ENCRYPT_STRU));

    if (VOS_NULL_PTR == pstEncryptFile)
    {
        SC_ERROR_LOG("SC_APSEC_ReadEncryptFile: Alloc memory failed.");

        return VOS_NULL_PTR;
    }

    if (VOS_OK != SC_COMM_ReadFile(pucFile,
                                   (VOS_UINT8 *)pstEncryptFile,
                                   SC_SECURITY_ITEM_NUM * sizeof(SC_APSEC_ENCRYPT_STRU)))
    {
        SC_ERROR_LOG("SC_APSEC_ReadEncryptFile: SC_COMM_ReadFile failed.");

        /*lint -e534*/
        VOS_MemSet((VOS_VOID *)pstEncryptFile, 0, SC_SECURITY_ITEM_NUM * sizeof(SC_APSEC_ENCRYPT_STRU));
        /*lint +e534*/

        if (VOS_OK != SC_COMM_WriteFile(pucFile, (VOS_UINT8 *)pstEncryptFile, SC_SECURITY_ITEM_NUM * sizeof(SC_APSEC_ENCRYPT_STRU)))
        {
            /*lint -e534*/
            VOS_MemFree(CCPU_PID_PAM_OM, pstEncryptFile);
            /*lint +e534*/

            return VOS_NULL_PTR;
        }
    }

    return pstEncryptFile;
}

/*****************************************************************************
 函 数 名  : SC_APSEC_ReadEncryptItem
 功能描述  : 双备份文件加密存储项读取，完成HASH检验并解密
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 双备份文件初始化状态
 修改历史      :
  1.日    期   : 2012年8月30日
    作    者   : h59254
    修改内容   : V7R1C50 ISDB安全存储项目新增
*****************************************************************************/
VOS_UINT32  SC_APSEC_ReadEncryptItem(
    SC_APSEC_ITME_ENUM_UINT32           enSecItemId,
    SC_APSEC_ENCRYPT_STRU              *pstFileContent,
    SC_APSEC_DEFAULT_ITEM_STRU         *pstSecItem)
{
    SC_APSEC_ENCRYPT_STRU              *pstEncryptItem;
    SC_APSEC_ENCRYPT_STRU               stDecryptItem;
    VOS_INT                             lResult;
    VOS_UINT32                          ulKeyLen;
    VOS_UINT8                           aucKey[SC_KEY_LEN];
    VOS_UINT8                           aucHashData[SC_HASH_LEN];
    VOS_UINT8                           aucPadding[SC_SECURITY_ITEM_PADDING_SIZE];
    VOS_INT                             lHashLen;
    VOS_INT                             lDecryptLen;

    /* 生成ASSK用于解密 */
    ulKeyLen        =   SC_KEY_LEN;

    if (VOS_OK != SC_COMM_GenerateKey(SC_ASSK_STRING, SC_ASSK_STRLEN, aucKey, ulKeyLen))
    {
        SC_ERROR_LOG("SC_APSEC_ReadEncryptItem: SC_COMM_GenerateKey failed.");

        return VOS_ERR;
    }

    /* 根据存储项ID取偏移得到内容 */
    pstEncryptItem  =   pstFileContent + enSecItemId;
    lDecryptLen     =   sizeof(SC_APSEC_ENCRYPT_STRU);

    /* 用ASSK和AES-ECB算法解密 */
    lResult         =   mdrv_crypto_dec((VOS_CHAR*)(pstEncryptItem),
                                       sizeof(SC_APSEC_ENCRYPT_STRU),
                                       CRYPTO_ENCRYPT_ALGORITHM_AES_ECB,
                                       (VOS_CHAR *)aucKey,
                                       (VOS_INT)ulKeyLen,
                                       (VOS_CHAR *)(&stDecryptItem),
                                       &lDecryptLen);

    /* 判断解密结果和解密长度是否匹配 */
    if ((lDecryptLen != sizeof(SC_APSEC_ENCRYPT_STRU))
      || (VOS_OK != lResult))
    {
        SC_ERROR2_LOG("SC_APSEC_ReadEncryptItem: mdrv_crypto_dec failed, lResult %X, lDecryptLen %X", lResult, lDecryptLen);

        return VOS_ERR;
    }

    /* 用解密后的长度和内容数据计算HASH */
    lHashLen    =   SC_HASH_LEN;

    lResult     =   mdrv_crypto_hash((VOS_CHAR *)(&stDecryptItem),
                                (VOS_INT)(SC_SECURITY_ITEM_LENGTH_SIZE + SC_SECURITY_ITEM_CONTENT_SIZE),
                                CRYPTO_ALGORITHM_SHA256,
                                (VOS_CHAR *)aucHashData,
                                &lHashLen);

    if ((VOS_OK != lResult)
      ||(SC_HASH_LEN != lHashLen))
    {
        SC_ERROR2_LOG("SC_APSEC_ReadEncryptItem: mdrv_crypto_hash failed, lResult %X, lHashLen %X", lResult, lHashLen);

        return VOS_ERR;
    }

    /* 用解密的HASH数据与新计算的HASH进行匹配 */
    if (VOS_OK != VOS_MemCmp((VOS_VOID *)aucHashData,
                             (VOS_VOID *)(stDecryptItem.aucEncryptContent + SC_SECURITY_ITEM_LENGTH_SIZE + SC_SECURITY_ITEM_CONTENT_SIZE),
                             SC_HASH_LEN))
    {
        SC_ERROR_LOG("SC_APSEC_ReadEncryptItem: Compare HASH failed.");

        return VOS_ERR;
    }

    /* 填充PADDING数据 */
    /*lint -e534*/
    VOS_MemSet(aucPadding, SC_SECURITY_ITEM_PADDING_VALUE, SC_SECURITY_ITEM_PADDING_SIZE);
    /*lint +e534*/

    /* 用解密的PADDING数据与aucPadding匹配 */
    if (VOS_OK != VOS_MemCmp((VOS_VOID *)aucPadding,
                             (VOS_VOID *)(stDecryptItem.aucEncryptContent + SC_SECURITY_ITEM_LENGTH_SIZE \
                                         + SC_SECURITY_ITEM_CONTENT_SIZE + SC_SECURITY_ITEM_HASH_SIZE),
                              SC_SECURITY_ITEM_PADDING_SIZE))
    {
        SC_ERROR_LOG("SC_APSEC_ReadEncryptItem: Compare PADDING failed.");

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemCpy((VOS_VOID *)pstSecItem, (VOS_VOID *)(&stDecryptItem), sizeof(SC_APSEC_DEFAULT_ITEM_STRU));
    /*lint +e534*/

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : SC_APSEC_ResyncFile
 功能描述  : 双备份文件重同步处理函数
 输入参数  : ulSyncFileFlg:双备份文件重同步标记
 输出参数  : 无
 返 回 值  : 双备份文件初始化状态
 修改历史      :
  1.日    期   : 2012年9月3日
    作    者   : h59254
    修改内容   : V7R1C50 ISDB安全存储项目新增
*****************************************************************************/
VOS_UINT32 SC_APSEC_ResyncFile(VOS_UINT32 ulSyncFileFlg)
{
    /* 双备份文件重新写入 */
    if (VOS_TRUE == ulSyncFileFlg)
    {
        return SC_APSEC_FreshDualBackFile();
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : SC_APSEC_GetFileSyncFlg
 功能描述  : 双备份文件重同步标记获取函数
 输入参数  : enSecItemId:安全存储项
             pstEncryptFileA:指向加密文件A中安全存储项的指针
             pstEncryptFileC:指向加密文件C中安全存储项的指针
 输出参数  : pstSecItemA:加密文件A解密后得到的安全存储项
             pstSecItemC:加密文件C解密后得到的安全存储项
             pulFileSyncFlgA:文件A需要重同步的标记
             pulFileSyncFlgC:文件C需要重同步的标记
 返 回 值  : 双备份文件初始化状态
 修改历史      :
  1.日    期   : 2012年9月3日
    作    者   : h59254
    修改内容   : V7R1C50 ISDB安全存储项目新增
*****************************************************************************/
VOS_VOID    SC_APSEC_GetFileSyncFlg(
    SC_APSEC_ITME_ENUM_UINT32           enSecItemId,
    SC_APSEC_ENCRYPT_STRU              *pstEncryptFileA,
    SC_APSEC_ENCRYPT_STRU              *pstEncryptFileC,
    SC_APSEC_DEFAULT_ITEM_STRU         *pstSecItemA,
    SC_APSEC_DEFAULT_ITEM_STRU         *pstSecItemC,
    VOS_UINT32                         *pulFileSyncFlgA,
    VOS_UINT32                         *pulFileSyncFlgC)
{
    /* 双文件读取 */
    if (VOS_OK != SC_APSEC_ReadEncryptItem(enSecItemId, pstEncryptFileA, pstSecItemA))
    {
        /*设置文件A同步标记*/
        *pulFileSyncFlgA    =   VOS_TRUE;
    }

    if (VOS_OK != SC_APSEC_ReadEncryptItem(enSecItemId, pstEncryptFileC, pstSecItemC))
    {
        /*设置文件C同步标记*/
        *pulFileSyncFlgC    =   VOS_TRUE;
    }

    return;
}


/*****************************************************************************
 函 数 名  : SC_APSEC_InitDualBackFile
 功能描述  : 双备份文件解密后的数据初始化到内存中
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 双备份文件初始化状态
 修改历史      :
  1.日    期   : 2012年8月30日
    作    者   : h59254
    修改内容   : V7R1C50 ISDB安全存储项目新增
*****************************************************************************/
VOS_UINT32  SC_APSEC_InitDualBackFile(VOS_VOID)
{
    SC_APSEC_DEFAULT_ITEM_STRU          stApSecItemA;
    SC_APSEC_DEFAULT_ITEM_STRU          stApSecItemC;
    SC_APSEC_DEFAULT_ITEM_STRU         *pstApSecItem;
    SC_APSEC_ENCRYPT_STRU              *pstEncryptFileA;
    SC_APSEC_ENCRYPT_STRU              *pstEncryptFileC;
    SC_APSEC_ITEM_STRU                 *pstApSecItemAddr;
    SC_CONTEXT_STRU                    *pstScContextAddr;
    VOS_UINT32                          ulFileASyncFlg;
    VOS_UINT32                          ulFileCSyncFlg;
    VOS_UINT32                          ulSyncFileFlg;
    VOS_UINT32                          i;

    ulFileASyncFlg  =   VOS_FALSE;
    ulFileCSyncFlg  =   VOS_FALSE;
    ulSyncFileFlg   =   VOS_FALSE;

    /* 判断双备份文件是否已经初始化完成，已完成不再初始化 */
    if (SC_SECURITY_FILE_STATE_INIT == SC_APSEC_GetFileInitState())
    {
        SC_NORMAL_LOG("SC_APSEC_InitDualBackFile: File Init");

        return VOS_OK;
    }

    pstScContextAddr    =   SC_CTX_GetScCtxAddr();

    /* 将双备份文件密文内容读取到内存中，待解密 */
    pstEncryptFileA =   SC_APSEC_ReadEncryptFile(pstScContextAddr->stScApSecGlobalVar.pApSecFileA);

    if (VOS_NULL_PTR == pstEncryptFileA)
    {
        SC_ERROR_LOG("SC_APSEC_InitDualBackFile: SC_APSEC_ReadEncryptFile FileA failed.");

        return VOS_ERR;
    }

    pstEncryptFileC =   SC_APSEC_ReadEncryptFile(pstScContextAddr->stScApSecGlobalVar.pApSecFileC);

    if (VOS_NULL_PTR == pstEncryptFileC)
    {
        SC_ERROR_LOG("SC_APSEC_InitDualBackFile: SC_APSEC_ReadEncryptFile FileC failed.");

        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstEncryptFileA);
        /*lint +e534*/

        return VOS_ERR;
    }

    for (i = 0; i < SC_SECURITY_ITEM_NUM; i++)
    {
        /* 将指向正确解密项的指针设置为空 */
        pstApSecItem    =   VOS_NULL_PTR;

        /* 重同步标记位获取函数，并获取到解密后的内容 */
        SC_APSEC_GetFileSyncFlg(i,
                                pstEncryptFileA,
                                pstEncryptFileC,
                                &stApSecItemA,
                                &stApSecItemC,
                                &ulFileASyncFlg,
                                &ulFileCSyncFlg);

        /* 两个标记同时为假，说明文件内容正确 */
        if ((VOS_FALSE == ulFileCSyncFlg)
            && (VOS_FALSE == ulFileASyncFlg))
        {
            /* 文件读取成功后需要对比两个文件内容 */
            if (VOS_OK != VOS_MemCmp((VOS_VOID *)(stApSecItemA.aucContent),
                                     (VOS_VOID *)(stApSecItemC.aucContent),
                                     sizeof(stApSecItemA.aucContent)))

            {
                /* 如果解密、HASH计算、匹配成功，但两个文件的内容不同，无法判断哪个是正确的
                   继续初始化下一项，文件内容不拷贝到内存中去 */
                SC_NORMAL_LOG("SC_APSEC_InitDualBackFile: FileA not eq FileC.");

                continue;
            }

            /* 两个文件内容比较正确，随意用一个解析出来地址赋值 */
            pstApSecItem    =   &stApSecItemA;
        }
        /* 两个标记同时为真，说明文件内容都不正确，此项不初始化，继续下一个 */
        else if((VOS_TRUE == ulFileCSyncFlg)
            && (VOS_TRUE == ulFileASyncFlg))
        {
            SC_NORMAL_LOG("SC_APSEC_InitDualBackFile: FileA & FileC wrong.");

            continue;
        }
        /* 两个标记一真一假，用正确的安全项内容拷贝到内容中并设置标记同步双备份文件 */
        else
        {
            /* 得到正确的解密项 */
            pstApSecItem    =   (VOS_TRUE == ulFileASyncFlg)?(&stApSecItemC):(&stApSecItemA);

            /* 设置文件同步标记 */
            ulSyncFileFlg   =   VOS_TRUE;

            SC_NORMAL_LOG("SC_APSEC_InitDualBackFile: FileA or FileC is OK.");
        }

        pstApSecItemAddr                =   SC_CTX_GetApSecItemBaseAddr();

        pstApSecItemAddr                +=  i;

        /* 清空原先数据 */
        if (VOS_NULL_PTR != pstApSecItemAddr->pucContent)
        {
            /*lint -e534*/
            VOS_MemFree(CCPU_PID_PAM_OM, pstApSecItemAddr->pucContent);
            /*lint +e534*/

            pstApSecItemAddr->ulItemLen =   0;
            pstApSecItemAddr->pucContent=   VOS_NULL_PTR;
        }

        /* 如果读取到的数据内容长度为0，初始化下一个数据 */
        if (VOS_NULL == pstApSecItem->ulItemLen)
        {
            continue;
        }

        /* 为全局变量中的指针重新分配内存 */
        pstApSecItemAddr->ulItemLen     =   pstApSecItem->ulItemLen;
        pstApSecItemAddr->pucContent    =   (VOS_CHAR *)VOS_MemAlloc(CCPU_PID_PAM_OM, STATIC_MEM_PT, pstApSecItemAddr->ulItemLen);

        if (VOS_NULL_PTR == pstApSecItemAddr->pucContent)
        {
            SC_ERROR_LOG("SC_APSEC_InitDualBackFile: Alloc memory for new item fail.");

            pstApSecItemAddr->ulItemLen =   0;

            continue;
        }

        /* 将数据和HASH拷贝到内存中 */
        /*lint -e534*/
        VOS_MemCpy(pstApSecItemAddr->pucContent, pstApSecItem->aucContent, pstApSecItemAddr->ulItemLen);
        VOS_MemCpy(pstApSecItemAddr->aucHash, pstApSecItem->aucHash, SC_HASH_LEN);
        /*lint +e534*/
    }

    /* 释放之前申请的所有内存 */
    /*lint -e534*/
    VOS_MemFree(CCPU_PID_PAM_OM, pstEncryptFileA);
    VOS_MemFree(CCPU_PID_PAM_OM, pstEncryptFileC);
    /*lint +e534*/

    /* 初始化成功，设置文件初始化状态 */
    SC_APSEC_SetFileInitState(SC_SECURITY_FILE_STATE_INIT);

    return SC_APSEC_ResyncFile(ulSyncFileFlg);
}



/*****************************************************************************
 函 数 名  : SC_APSEC_ReadSecItem
 功能描述  : 安全存储荐读取
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 双备份文件初始化状态
 修改历史      :
  1.日    期   : 2012年8月30日
    作    者   : h59254
    修改内容   : V7R1C50 ISDB安全存储项目新增
  2.日    期   : 2012年11月22日
    作    者   : l00198894
    修改内容   : 增加安全项默认值
  3.日    期   : 2013年01月24日
    作    者   : l00198894
    修改内容   : DTS2013012209538: 安全项值为全0时作为无效值
  4.日    期   : 2013年01月30日
    作    者   : l00198894
    修改内容   : DTS2013013008710: 安全项值为全0xFF且存在默认值时返回默认值
*****************************************************************************/
VOS_UINT32  SC_APSEC_ReadSecItem(
    SC_APSEC_ITME_ENUM_UINT32           enSecItemId,
    SC_APSEC_DEFAULT_ITEM_STRU         *pstSecItem)
{
    SC_APSEC_ITEM_STRU                 *pstApSecItemAddr;
    VOS_UINT8                           aucHashData[SC_HASH_LEN];
    VOS_UINT8                           aucData[SC_SECURITY_ITEM_LENGTH_SIZE + SC_SECURITY_ITEM_CONTENT_SIZE];
    VOS_INT                             lHashLen;
    VOS_INT32                           lResult;
    VOS_UINT32                          ulLoop;

    pstApSecItemAddr                    =   SC_CTX_GetApSecItemBaseAddr();
    pstApSecItemAddr                    +=  enSecItemId;

    /* 先做双备份文件初始化 */
    if (VOS_OK != SC_APSEC_InitDualBackFile())
    {
        SC_ERROR_LOG("SC_APSEC_ReadSecItem: SC_APSEC_InitDualBackFile fail.");

        /* Modified by l00198894 for 安全存储 新增需求, 2012/11/22, begin */
        /* 双备份文件读取异常，返回默认值 */
        return SC_APSEC_GetDefaultSecItem(enSecItemId, pstSecItem);
        /* Modified by l00198894 for 安全存储 新增需求, 2012/11/22, end */
    }

    /* 有可能文件不存在，写入某项之后再去读取一个不存在的项，需要判断指针是否为空 */
    if ((VOS_NULL_PTR == pstApSecItemAddr->pucContent)
        || (0 == pstApSecItemAddr->ulItemLen))
    {
        SC_ERROR_LOG("SC_APSEC_ReadSecItem: Item is null.");

        /* Modified by l00198894 for 安全存储 新增需求, 2012/11/22, begin */
        /* 安全项未写入值，返回默认值 */
        return SC_APSEC_GetDefaultSecItem(enSecItemId, pstSecItem);
        /* Modified by l00198894 for 安全存储 新增需求, 2012/11/22, end */
    }

    /* 用解密后的长度和内容数据计算HASH */
    /*lint -e534*/
    VOS_MemSet((VOS_VOID *)aucData, 0, SC_SECURITY_ITEM_LENGTH_SIZE + SC_SECURITY_ITEM_CONTENT_SIZE);
    VOS_MemCpy((VOS_VOID *)aucData, (VOS_VOID *)(&pstApSecItemAddr->ulItemLen), SC_SECURITY_ITEM_LENGTH_SIZE);
    VOS_MemCpy((VOS_VOID *)(aucData + SC_SECURITY_ITEM_LENGTH_SIZE),
               (VOS_VOID *)pstApSecItemAddr->pucContent,
               pstApSecItemAddr->ulItemLen);
    /*lint +e534*/

    lHashLen    =   SC_HASH_LEN;

    lResult     = mdrv_crypto_hash((VOS_CHAR *)(aucData),
                              (VOS_INT)(SC_SECURITY_ITEM_LENGTH_SIZE + SC_SECURITY_ITEM_CONTENT_SIZE),
                              CRYPTO_ALGORITHM_SHA256,
                              (VOS_CHAR *)aucHashData,
                              &lHashLen);

    if ((VOS_OK != lResult)
      ||(SC_HASH_LEN != lHashLen))
    {
        SC_ERROR2_LOG("SC_APSEC_ReadSecItem: mdrv_crypto_hash fail lResult %d, lHashLen.", lResult, lHashLen);

        /* Modified by l00198894 for 安全存储 新增需求, 2012/11/22, begin */
        /* 底软接口HASH失败，返回默认值 */
        return SC_APSEC_GetDefaultSecItem(enSecItemId, pstSecItem);
        /* Modified by l00198894 for 安全存储 新增需求, 2012/11/22, end */
    }

    /* 将计算出的HASH与全局变量中的比较 */
    if (VOS_OK != VOS_MemCmp((VOS_VOID *)aucHashData, (VOS_VOID *)pstApSecItemAddr->aucHash, SC_HASH_LEN))
    {
        SC_ERROR_LOG("SC_APSEC_ReadSecItem: Compare HASH fail.");

        /* Modified by l00198894 for 安全存储 新增需求, 2012/11/22, begin */
        /* 全局变量中的安全项被篡改，返回默认值 */
        return SC_APSEC_GetDefaultSecItem(enSecItemId, pstSecItem);
        /* Modified by l00198894 for 安全存储 新增需求, 2012/11/22, end */
    }

    /* 安全存储项值有效性判断，存在默认值且为全0xFF则返回默认值 */
    for (ulLoop = 0; ulLoop < pstApSecItemAddr->ulItemLen; ulLoop++)
    {
        if (0xFF != (VOS_UINT8)(*(pstApSecItemAddr->pucContent + ulLoop)))
        {
            break;
        }
    }
    if (ulLoop >= pstApSecItemAddr->ulItemLen)
    {
        /*  安全存储项值全为0xFF，有默认值返回默认值 */
        SC_NORMAL_LOG("SC_APSEC_ReadSecItem: Item Values Are All 0xFF.");
        if (VOS_OK == SC_APSEC_GetDefaultSecItem(enSecItemId, pstSecItem))
        {
            return VOS_OK;
        }
    }

    /* 从内存中读取安全存储项的内容 */
    pstSecItem->ulItemLen               =   pstApSecItemAddr->ulItemLen;

    /*lint -e534*/
    VOS_MemCpy(pstSecItem->aucContent, pstApSecItemAddr->pucContent, pstSecItem->ulItemLen);
    /*lint +e534*/

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : SC_APSEC_FreshDualBackFile
 功能描述  : 安全存储双备份文件刷新
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 双备份文件初始化状态
 修改历史      :
  1.日    期   : 2012年8月31日
    作    者   : h59254
    修改内容   : V7R1C50 ISDB安全存储项目新增
*****************************************************************************/
VOS_UINT32  SC_APSEC_FreshDualBackFile(VOS_VOID)
{
    SC_APSEC_ITEM_STRU                 *pstSecItemAddr;
    SC_CONTEXT_STRU                    *pstScContextAddr;
    SC_APSEC_DEFAULT_ITEM_STRU          stDefaulItem;
    VOS_UINT32                          ulResult;
    VOS_UINT8                          *pucFile;
    VOS_UINT8                          *pucFileTmp;
    VOS_CHAR                           *pucTmp;
    VOS_UINT32                          i;

    pstSecItemAddr                      =   SC_CTX_GetApSecItemBaseAddr();
    pstScContextAddr                    =   SC_CTX_GetScCtxAddr();

    pucFile =   (VOS_UINT8 *)VOS_MemAlloc(CCPU_PID_PAM_OM,
                                          DYNAMIC_MEM_PT,
                                          SC_SECURITY_ITEM_NUM * sizeof(SC_APSEC_ENCRYPT_STRU));

    if (VOS_NULL_PTR == pucFile)
    {
        SC_ERROR_LOG("SC_APSEC_FreshDualBackFile: Alloc memory fail.");

        return VOS_ERR;
    }

    pucFileTmp  =   pucFile;

    /*lint -e534*/
    VOS_MemSet((VOS_VOID *)(&stDefaulItem), 0, sizeof(SC_APSEC_DEFAULT_ITEM_STRU));
    /*lint +e534*/

    for (i = 0; i < SC_SECURITY_ITEM_NUM; i++)
    {
        /* 如果某项内容为空，用全0来计算 */
        if (0 == pstSecItemAddr->ulItemLen)
        {
            pucTmp  = (VOS_CHAR *)stDefaulItem.aucContent;
        }
        else
        {
            pucTmp  = pstSecItemAddr->pucContent;
        }

        if (VOS_OK != SC_APSEC_EncryptItem(pstSecItemAddr->ulItemLen, pucTmp, (VOS_CHAR *)pucFileTmp))
        {
            SC_ERROR_LOG("SC_APSEC_FreshDualBackFile: SC_APSEC_EncryptItem fail.");

            /*lint -e534*/
            VOS_MemFree(CCPU_PID_PAM_OM, pucFile);
            /*lint +e534*/

            return VOS_ERR;
        }

        /* 安全存储文件指针和全局变量的指针都指向下一单元 */
        pucFileTmp += sizeof(SC_APSEC_ENCRYPT_STRU);
        pstSecItemAddr++;
    }

    /* 双文件备份写入 */
    ulResult        =   SC_COMM_WriteFile(pstScContextAddr->stScApSecGlobalVar.pApSecFileA,
                                          (VOS_UINT8 *)pucFile,
                                          SC_SECURITY_ITEM_NUM * sizeof(SC_APSEC_ENCRYPT_STRU));

    ulResult        |=  SC_COMM_WriteFile(pstScContextAddr->stScApSecGlobalVar.pApSecFileC,
                                          (VOS_UINT8 *)pucFile,
                                          SC_SECURITY_ITEM_NUM * sizeof(SC_APSEC_ENCRYPT_STRU));

    /*lint -e534*/
    VOS_MemFree(CCPU_PID_PAM_OM, pucFile);
    /*lint +e534*/

    /* 如果只有一个文件更新成功，那另一个文件更新失败会导致下次开机时两个文件检验
       通过，但两边不匹配文件初始化失败 */
    if (VOS_OK != ulResult)
    {
        SC_ERROR_LOG("SC_APSEC_FreshDualBackFile: Dual back file write fail.");

        return VOS_ERR;
    }

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : SC_APSEC_IncrementSeqID
 功能描述  : 本地全局变量中的SeqID自增1
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月2日
    作    者   : 李紫剑/00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SC_APSEC_IncrementSeqID( VOS_VOID )
{
    VOS_UINT8                           ucSeqID;

    /* 初始化 */
    ucSeqID = SC_CTX_GetApSecSeqID();

    /* 增加1 */
    if (SC_APSEC_SP_SEQID_MAX_VALUE == ucSeqID)
    {
        /* 当SeqID达到最大值，置为最小值 */
        ucSeqID = SC_APSEC_SP_SEQID_MIN_VALUE;
    }
    else
    {
        ucSeqID++;
    }

    SC_CTX_SetApSecSeqID(ucSeqID);

    return;
}

/*****************************************************************************
 函 数 名  : SC_APSEC_RegressSeqID
 功能描述  : 复原本地全局变量中的SeqID
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月2日
    作    者   : 李紫剑/00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SC_APSEC_RegressSeqID( VOS_VOID )
{
    SC_CTX_SetApSecSeqID(SC_APSEC_SP_SEQID_MIN_VALUE);

    return;
}

/*****************************************************************************
 函 数 名  : SC_APSEC_GenerateSecATkey
 功能描述  : 完成生成安全AT key功能
 输入参数  : VOS_UINT32 *pulSPLen       -- 安全封包长度字节数
             VOS_UINT8  *pucSecPacket   -- 安全封包二进制码流
 输出参数  : VOS_UINT32 *pulSPLen       -- 回复安全封包长度字节数
             VOS_UINT8  *pucSecPacket   -- 回复安全封包二进制码流
 返 回 值  : VOS_OK     -- 安全AT key生成成功
             VOS_ERR    -- 安全AT key生成失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月31日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 SC_APSEC_GenerateSecATkey(
    VOS_UINT32                         *pulSPLen,
    VOS_UINT8                          *pucSecPacket )
{
    VOS_INT32                           lRetrun;
    SC_APSEC_SECURE_PACKET_STRU        *pstSecPacket;
    SC_APSEC_SECURE_PACKET_STRU         stSecPacketCnf;
    SC_APSEC_SP_FLAG_STRU              *pstFlag;
    VOS_UINT8                           aucSATK[SC_KEY_LEN];
    VOS_INT8                            acConvkey[SC_KEY_LEN];
    VOS_INT                             lLen;
    VOS_UINT8                          *pucSecATkey;
    VOS_CHAR                            acSecureCode[] = {0x1D, 0x1F, 0x25, 0x29,
                                                          0x2B, 0x2F, 0x35, 0x3B,
                                                          0x3D, 0x43, 0x47, 0x49,
                                                          0x4F, 0x53, 0x59, 0x61};

    /* 初始化 */
    pstSecPacket    = (SC_APSEC_SECURE_PACKET_STRU *)pucSecPacket;

    /* 校验SeqID、MajorVer、MinorVer、Flag等 */
    pstFlag         = (SC_APSEC_SP_FLAG_STRU *)&pstSecPacket->stHeader.ucFlag;
    if ( (0 != pstSecPacket->stHeader.ucSeqID)
      || (SC_APSEC_SP_MAJOR_AT_KEY != pstSecPacket->stHeader.ucMajorCMD)
      || (SC_APSEC_SP_MINOR_AT_KEY != pstSecPacket->stHeader.ucMinorCMD)
      || (SC_APSEC_SP_FLAG_AT_KEY != pstSecPacket->stHeader.ucFlag)
      || (SC_APSEC_SP_RANDOM_LEN != pstSecPacket->usDataLen) )
    {
        pstFlag->ucType     = SC_APSEC_SP_FLAG_CNF;
        pstFlag->ucResult   = SC_APSEC_SP_FLAG_RLT_PARAERR;
        return VOS_OK;
    }

    /* 调用DRV提供的API获取SATK */
    if (SC_ERROR_CODE_NO_ERROR != SC_COMM_GenerateKey(SC_SATK_STRING,
                                                      SC_SATK_STRLEN,
                                                      aucSATK,
                                                      SC_KEY_LEN))
    {
        SC_ERROR_LOG("SC_APSEC_GenerateSecATkey: SC_COMM_GenerateKey is failed.");
        return VOS_ERR;
    }

    /* 使用SATK对固定码流进行AES-ECB加密 */
    lLen            = SC_KEY_LEN;
    lRetrun         = mdrv_crypto_enc(acSecureCode,
                                     sizeof(acSecureCode),
                                     CRYPTO_ENCRYPT_ALGORITHM_AES_ECB,
                                     (VOS_CHAR*)aucSATK,
                                     SC_KEY_LEN,
                                     (VOS_CHAR*)acConvkey,
                                     &lLen);
    if ( (VOS_OK != lRetrun) || (SC_KEY_LEN != lLen) )
    {
        SC_ERROR2_LOG("SC_APSEC_GenerateSecATkey: AES-ECB Encrypt Failed lRetrun %X, lLen %X",lRetrun, lLen);
        return VOS_ERR;
    }

    /* 使用获取的密文对随机数进行加密 */
    lLen            = SC_SEC_AT_KEY_LEN;
    pucSecATkey     = SC_CTX_GetSecATkeyAddr();
    lRetrun         = mdrv_crypto_enc((VOS_CHAR*)pstSecPacket->aucData,
                                     pstSecPacket->usDataLen,
                                     CRYPTO_ENCRYPT_ALGORITHM_AES_ECB,
                                     (VOS_CHAR*)acConvkey,
                                     SC_KEY_LEN,
                                     (VOS_CHAR*)pucSecATkey,
                                     &lLen);
    if ( (VOS_OK != lRetrun) || (lLen != pstSecPacket->usDataLen) )
    {
        SC_ERROR2_LOG("SC_APSEC_GenerateSecATkey: AES-ECB Encrypt Failed lRetrun %X, lLen %X",lRetrun, lLen);
        return VOS_ERR;
    }

    /* 将生成的安全AT key保存到全局变量中 */
    SC_CTX_SetSecATkeyFlg(VOS_TRUE);

    /* 复原SeqID为最小值 */
    SC_APSEC_RegressSeqID();

    /* 将安全AT key填入到回复安全封包中 */
    pstFlag->ucType         = SC_APSEC_SP_FLAG_CNF;
    pstFlag->ucResult       = SC_APSEC_SP_FLAG_RLT_SUCCESS;
    pstSecPacket->usDataLen = SC_SEC_AT_KEY_LEN;
    /*lint -e534*/
    VOS_MemCpy(pstSecPacket->aucData, pucSecATkey, SC_SEC_AT_KEY_LEN);
    /*lint +e534*/
    stSecPacketCnf          = *pstSecPacket;

    /* 使用安全AT key对安全封包进行加密，并返回 */
    return SC_APSEC_EncryptSecPacket(&stSecPacketCnf, pucSecPacket, pulSPLen);
}

/*****************************************************************************
 函 数 名  : SC_APSEC_DecryptSecPacket
 功能描述  : 使用AES-ECB算法解密安全封包
 输入参数  : VOS_UINT8     *pucCipherSP     -- 安全封包密文
             VOS_UINT32     ulCipherSPLen   -- 安全封包密文长度
 输出参数  : SC_APSEC_SECURE_PACKET_STRU   *pstSecPacket    -- 解密后的安全封包
 返 回 值  : SC_APSEC_DECRYPT_RESULT_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月2日
    作    者   : 李紫剑/00198894
    修改内容   : 新生成函数

*****************************************************************************/
SC_APSEC_SP_RESULT_ENUM_UINT32 SC_APSEC_DecryptSecPacket(
    VOS_UINT8                          *pucCipherSP,
    VOS_UINT32                          ulCipherSPLen,
    SC_APSEC_SECURE_PACKET_STRU        *pstSecPacket )
{
    VOS_UINT8                          *pucSecATkey;
    VOS_UINT32                          ulSPLen;
    VOS_UINT32                          ulPaddingLen;
    VOS_INT32                           lResult;
    VOS_UINT32                          ulLoop;

    /* 获取安全AT key */
    if (VOS_TRUE != SC_CTX_GetSecATkeyFlg())
    {
        SC_ERROR_LOG("SC_APSEC_DecryptSecPacket: There is no Secure AT Key!");
        return SC_APSEC_SP_NO_SATK;
    }
    pucSecATkey     = SC_CTX_GetSecATkeyAddr();

    /* 调用DRV的解密接口 */
    ulSPLen         = sizeof(SC_APSEC_SECURE_PACKET_STRU);
    /*lint -e534*/
    VOS_MemSet(pstSecPacket, 0x00, ulSPLen);
    /*lint +e534*/

    lResult         = mdrv_crypto_dec((VOS_CHAR*)pucCipherSP,
                                     (VOS_INT32)ulCipherSPLen,
                                     CRYPTO_ENCRYPT_ALGORITHM_AES_ECB,
                                     (VOS_CHAR*)pucSecATkey,
                                     SC_SEC_AT_KEY_LEN,
                                     (VOS_CHAR*)pstSecPacket,
                                     (VOS_INT*)&ulSPLen);

    if ( (VOS_OK != lResult) || (ulCipherSPLen != ulSPLen) )
    {
        SC_ERROR2_LOG("SC_APSEC_DecryptSecPacket: AES-ECB Decrypt Failed lResult, ulSPLen ", lResult, ulSPLen);
        return SC_APSEC_SP_ERROR;
    }

    /* 对安全封包的Padding位进行校验 */
    if (SC_SECURITY_ITEM_CONTENT_SIZE < pstSecPacket->usDataLen)
    {
        SC_ERROR1_LOG("SC_APSEC_DecryptSecPacket: Secure Packet DataLen Error, usDataLen ", pstSecPacket->usDataLen);
        return SC_APSEC_SP_PADDING_ERR;
    }

    ulPaddingLen    = ulCipherSPLen
                    - sizeof(SC_APSEC_SP_HEADER_STRU)
                    - sizeof(VOS_UINT16)
                    - pstSecPacket->usDataLen;
    for (ulLoop = pstSecPacket->usDataLen;
         ulLoop < pstSecPacket->usDataLen + ulPaddingLen;
         ulLoop++)
    {
        if (pstSecPacket->aucData[ulLoop] != (VOS_UINT8)ulPaddingLen)
        {
            break;
        }
    }
    if (ulLoop < (pstSecPacket->usDataLen + ulPaddingLen))
    {
        SC_ERROR_LOG("SC_APSEC_DecryptSecPacket: Padding Bits Check Failed!");
        return SC_APSEC_SP_PADDING_ERR;
    }

    return SC_APSEC_SP_OK;
}

/*****************************************************************************
 函 数 名  : SC_APSEC_CheckSecPacket
 功能描述  : 检查安全封包校验位
 输入参数  : pstSecPacket   -- 待校验的安全封包
 输出参数  : 无
 返 回 值  : SC_APSEC_SP_RESULT_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月2日
    作    者   : 李紫剑/00198894
    修改内容   : 新生成函数

*****************************************************************************/
SC_APSEC_SP_RESULT_ENUM_UINT32 SC_APSEC_CheckSecPacket(
    SC_APSEC_SECURE_PACKET_STRU        *pstSecPacket )
{
    VOS_UINT8                           ucSeqID;
    SC_APSEC_SP_MAJOR_CMD_STRU         *pstMajorCMD;
    SC_APSEC_SP_MINOR_CMD_STRU         *pstMinorCMD;
    SC_APSEC_SP_FLAG_STRU              *pstFlag;

    /* 获取本地全局变量中的SeqID */
    ucSeqID = SC_CTX_GetApSecSeqID();

    /* 校验SeqID */
    if (ucSeqID != pstSecPacket->stHeader.ucSeqID)
    {
        SC_ERROR_LOG("SC_APSEC_CheckSecPacket: SeqID not Match!");
        return SC_APSEC_SP_SEQID_ERR;
    }

    /* 检验命令版本 */
    pstMajorCMD     = (SC_APSEC_SP_MAJOR_CMD_STRU*)&pstSecPacket->stHeader.ucMajorCMD;
    pstMinorCMD     = (SC_APSEC_SP_MINOR_CMD_STRU*)&pstSecPacket->stHeader.ucMinorCMD;
    if ( (SC_APSEC_SP_MAJOR_VERSION != pstMajorCMD->ucVer)
      || (SC_APSEC_SP_MINOR_VERSION != pstMinorCMD->ucVer)
      || (0 != pstMajorCMD->ucReserved) )
    {
        SC_ERROR_LOG("SC_APSEC_CheckSecPacket: CMD Version not Match!");
        return SC_APSEC_SP_PARA_ERR;
    }

    /* 检查安全封包标志位 */
    pstFlag         = (SC_APSEC_SP_FLAG_STRU*)&pstSecPacket->stHeader.ucFlag;
    if ( (SC_APSEC_SP_FLAG_REQ != pstFlag->ucType)
        || (VOS_NULL != pstFlag->ucAtSec)
        || (VOS_NULL != pstFlag->ucResult) )
    {
        SC_ERROR_LOG("SC_APSEC_CheckSecPacket: Flag Check Failed!");
        return SC_APSEC_SP_PARA_ERR;
    }

    return SC_APSEC_SP_OK;
}

/*****************************************************************************
 函 数 名  : SC_APSEC_EncryptSecPacket
 功能描述  : 使用AES-ECB算法加密安全封包
 输入参数  : SC_APSEC_SECURE_PACKET_STRU   *pstSecPacket    -- 待加密的安全封包
 输出参数  : VOS_UINT8     *pucCipherSP     -- 安全封包密文
             VOS_UINT32    *ulCipherSPLen   -- 安全封包密文长度
 返 回 值  : VOS_UINT32
                VOS_OK  : 解密成功
                VOS_ERR : 解密失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月31日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 SC_APSEC_EncryptSecPacket(
    SC_APSEC_SECURE_PACKET_STRU        *pstSecPacket,
    VOS_UINT8                          *pucCipherSP,
    VOS_UINT32                         *pulCipherSPLen)
{
    VOS_UINT8                          *pucSecATkey;
    VOS_UINT32                          ulPaddingLen;
    VOS_UINT32                          ulLen;
    VOS_INT32                           lResult;

    /* 获取安全AT key */
    if (VOS_TRUE != SC_CTX_GetSecATkeyFlg())
    {
        SC_ERROR_LOG("SC_APSEC_EncryptSecPacket: There is no Secure AT Key!");
        return VOS_ERR;
    }
    pucSecATkey     = SC_CTX_GetSecATkeyAddr();

    /* 填充Padding位 */
    ulLen           = sizeof(SC_APSEC_SP_HEADER_STRU)
                    + sizeof(VOS_UINT16)
                    + pstSecPacket->usDataLen;
    if (0 != (ulLen % SC_AES_TEXT_MIN_LEN))
    {
        /* 如果当前安全封包大小不为16的倍数，补足Padding位 */
        ulPaddingLen    = SC_AES_TEXT_MIN_LEN - (ulLen % SC_AES_TEXT_MIN_LEN);
        /*lint -e534*/
        VOS_MemSet((VOS_UINT8*)pstSecPacket + ulLen,
                   (VOS_CHAR)ulPaddingLen,
                   ulPaddingLen);
        /*lint +e534*/
        ulLen       += ulPaddingLen;
    }

    /* 调用DRV的加密接口 */
    lResult         = mdrv_crypto_enc((VOS_CHAR*)pstSecPacket,
                                     (VOS_INT)ulLen,
                                     CRYPTO_ENCRYPT_ALGORITHM_AES_ECB,
                                     (VOS_CHAR*)pucSecATkey,
                                     SC_SEC_AT_KEY_LEN,
                                     (VOS_CHAR*)pucCipherSP,
                                     (VOS_INT*)pulCipherSPLen);
    if ( (VOS_OK != lResult) || (ulLen != *pulCipherSPLen) )
    {
        SC_ERROR2_LOG("SC_APSEC_EncryptSecPacket: AES-ECB Encrypt Failed lResult %X, ulLen %X",lResult,ulLen);
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : SC_APSEC_DealSecureStorage
 功能描述  : 处理安全存储命令
 输入参数  : SC_APSEC_SECURE_PACKET_STRU  *pstSecPacket -- 待处理的安全封包
 输出参数  : SC_APSEC_SECURE_PACKET_STRU  *pstSecPacket -- 处理完成的安全封包
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月2日
    作    者   : 李紫剑/00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SC_APSEC_DealSecureStorage(
    SC_APSEC_SECURE_PACKET_STRU        *pstSecPacket )
{
    SC_APSEC_SP_MINOR_CMD_STRU         *pstMinorCMD;
    SC_APSEC_SP_FLAG_STRU              *pstFlag;
    VOS_UINT32                          ulResult;
    SC_APSEC_DEFAULT_ITEM_STRU          stSecItem;

    /* 初始化 */
    pstMinorCMD     = (SC_APSEC_SP_MINOR_CMD_STRU*)&pstSecPacket->stHeader.ucMinorCMD;
    pstFlag         = (SC_APSEC_SP_FLAG_STRU*)&pstSecPacket->stHeader.ucFlag;
    /*lint -e534*/
    VOS_MemSet(&stSecItem, 0x00, sizeof(SC_APSEC_DEFAULT_ITEM_STRU));
    /*lint +e534*/

    /* 根据命令标志位执行相应操作 */
    switch (pstMinorCMD->ucType)
    {
        /* 读取安全数据 */
        case SC_APSEC_SP_MINOR_READ:
            ulResult = SC_APSEC_ReadSecItem((SC_APSEC_ITME_ENUM_UINT32)pstMinorCMD->ucSecItem,
                                            &stSecItem);
            if (VOS_OK == ulResult)
            {
                pstSecPacket->usDataLen = (VOS_UINT16)stSecItem.ulItemLen;
                /*lint -e534*/
                VOS_MemCpy(pstSecPacket->aucData, stSecItem.aucContent, stSecItem.ulItemLen);
                /*lint +e534*/
                pstFlag->ucResult       = SC_APSEC_SP_FLAG_RLT_SUCCESS;
            }
            else
            {
                pstFlag->ucResult       = SC_APSEC_SP_FLAG_RLT_DUALBACK_FAILED;
                pstSecPacket->usDataLen = 0;
            }
            break;
        /* 存储安全数据 */
        case SC_APSEC_SP_MINOR_WRITE:
            stSecItem.ulItemLen = pstSecPacket->usDataLen;
            /*lint -e534*/
            VOS_MemCpy(stSecItem.aucContent, pstSecPacket->aucData, stSecItem.ulItemLen);
            /*lint +e534*/
            ulResult = SC_APSEC_UpdateSecItem((SC_APSEC_ITME_ENUM_UINT32)pstMinorCMD->ucSecItem,
                                              &stSecItem);
            if (VOS_OK == ulResult)
            {
                pstFlag->ucResult       = SC_APSEC_SP_FLAG_RLT_SUCCESS;
            }
            else
            {
                pstFlag->ucResult       = SC_APSEC_SP_FLAG_RLT_DUALBACK_FAILED;
            }
            break;
        default:
            pstFlag->ucResult           = SC_APSEC_SP_FLAG_RLT_PARAERR;
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : SC_APSEC_CreateSecPacket
 功能描述  : 根据结果值填写回复安全封包
 输入参数  : enResult                   -- 安全封包处理结果值
             pstSecPacket               -- 源安全封包
 输出参数  : VOS_UINT8  *pucSecPacket   -- 回复安全封包二进制码流
             VOS_UINT32 *pulSPLen       -- 回复安全封包长度字节数
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月31日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 SC_APSEC_CreateSecPacket(
    SC_APSEC_SP_RESULT_ENUM_UINT32      enResult,
    SC_APSEC_SECURE_PACKET_STRU        *pstSecPacket,
    VOS_UINT8                          *pucSecPacket,
    VOS_UINT32                         *pulSPLen )
{
    SC_APSEC_SP_MAJOR_CMD_STRU         *pstMajorCMD;
    SC_APSEC_SP_MINOR_CMD_STRU         *pstMinorCMD;
    SC_APSEC_SP_FLAG_STRU              *pstFlag;

    pstMajorCMD     = (SC_APSEC_SP_MAJOR_CMD_STRU*)&pstSecPacket->stHeader.ucMajorCMD;
    pstMinorCMD     = (SC_APSEC_SP_MINOR_CMD_STRU*)&pstSecPacket->stHeader.ucMinorCMD;
    pstFlag         = (SC_APSEC_SP_FLAG_STRU*)&pstSecPacket->stHeader.ucFlag;

    /* 根据对应的结果值填写回复安全封包 */
    switch(enResult)
    {
        case SC_APSEC_SP_OK:
            /* 正常处理安全封包，直接加密后返回 */
            pstFlag->ucType             = SC_APSEC_SP_FLAG_CNF;
            return SC_APSEC_EncryptSecPacket(pstSecPacket, pucSecPacket, pulSPLen);
        case SC_APSEC_SP_NO_SATK:
            /* 由于没有安全AT key导致的解密失败, 填写对应封包 */
            /*lint -e534*/
            VOS_MemSet(pstSecPacket, 0x00, sizeof(SC_APSEC_SECURE_PACKET_STRU));
            /*lint +e534*/
            pstMajorCMD->ucType         = SC_APSEC_SP_MAJOR_SECSTORE;
            pstMajorCMD->ucVer          = SC_APSEC_SP_MAJOR_VERSION;
            pstMinorCMD->ucType         = SC_APSEC_SP_MINOR_READ;
            pstMinorCMD->ucVer          = SC_APSEC_SP_MINOR_VERSION;
            pstFlag->ucType             = SC_APSEC_SP_FLAG_CNF;
            pstFlag->ucAtSec            = SC_APSEC_SP_FLAG_ATSEC_REQ_AT_KEY;
            /*lint -e534*/
            VOS_MemCpy(pucSecPacket, pstSecPacket, sizeof(SC_APSEC_SECURE_PACKET_STRU));
            /*lint +e534*/
            *pulSPLen       = sizeof(SC_APSEC_SP_HEADER_STRU) + sizeof(VOS_UINT16);
            return VOS_OK;
        case SC_APSEC_SP_PADDING_ERR:
            /* Padding位校验失败, 填写对应封包 */
            /*lint -e534*/
            VOS_MemSet(pstSecPacket, 0x00, sizeof(SC_APSEC_SECURE_PACKET_STRU));
            /*lint +e534*/
            pstMajorCMD->ucType         = SC_APSEC_SP_MAJOR_SECSTORE;
            pstMajorCMD->ucVer          = SC_APSEC_SP_MAJOR_VERSION;
            pstMinorCMD->ucType         = SC_APSEC_SP_MINOR_READ;
            pstMinorCMD->ucVer          = SC_APSEC_SP_MINOR_VERSION;
            pstFlag->ucType             = SC_APSEC_SP_FLAG_CNF;
            pstFlag->ucAtSec            = SC_APSEC_SP_FLAG_ATSEC_PARA_ERR;
            return SC_APSEC_EncryptSecPacket(pstSecPacket, pucSecPacket, pulSPLen);
        case SC_APSEC_SP_SEQID_ERR:
            /* SeqID校验失败，填写对应封包 */
            pstFlag->ucAtSec            = SC_APSEC_SP_FLAG_ATSEC_SEQID_ERR;
            pstFlag->ucType             = SC_APSEC_SP_FLAG_CNF;
            return SC_APSEC_EncryptSecPacket(pstSecPacket, pucSecPacket, pulSPLen);
        case SC_APSEC_SP_PARA_ERR:
            /* 安全存储封包参数错误，填写对应封包 */
            pstFlag->ucType             = SC_APSEC_SP_FLAG_CNF;
            pstFlag->ucResult           = SC_APSEC_SP_FLAG_RLT_PARAERR;
            return SC_APSEC_EncryptSecPacket(pstSecPacket, pucSecPacket, pulSPLen);
        default:
            return VOS_ERR;
    }
}

/*****************************************************************************
 函 数 名  : SC_APSEC_ParseSecPacket
 功能描述  : 解析安全封包
 输入参数  : VOS_UINT32 *pulSPLen       -- 安全封包长度字节数
             VOS_UINT8  *pucSecPacket   -- 安全封包二进制码流
 输出参数  : VOS_UINT32 *pulSPLen       -- 回复安全封包长度字节数
             VOS_UINT8  *pucSecPacket   -- 回复安全封包二进制码流
 返 回 值  : VOS_OK     -- 安全封包解析成功
             VOS_ERR    -- 安全封包解析失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月31日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 SC_APSEC_ParseSecPacket(
    VOS_UINT32                         *pulSPLen,
    VOS_UINT8                          *pucSecPacket )
{
    SC_APSEC_SP_RESULT_ENUM_UINT32      enResult;
    SC_APSEC_SECURE_PACKET_STRU         stSecPacket;
    SC_APSEC_SP_MAJOR_CMD_STRU         *pstMajorCMD;

    /* 检查参数有效性 */
    if ( (VOS_NULL_PTR == pulSPLen) || (VOS_NULL_PTR == pucSecPacket) )
    {
        SC_ERROR_LOG("SC_APSEC_ParseSecPacket: Para is NULL pointer!");
        return VOS_ERR;
    }

    /* 安全封包长度字节数不是16的倍数，调用生成安全AT key接口 */
    if (0 != (*pulSPLen % SC_AES_TEXT_MIN_LEN))
    {
        return SC_APSEC_GenerateSecATkey(pulSPLen, pucSecPacket);
    }

    /* 安全封包长度字节数是16的倍数，则使用安全AT key进行AES-ECB解密 */
    enResult        = SC_APSEC_DecryptSecPacket(pucSecPacket, *pulSPLen, &stSecPacket);
    if (SC_APSEC_SP_OK != enResult)
    {
        /* 安全封包解密失败，SeqID仍然自增1 */
        SC_APSEC_IncrementSeqID();

        /* 安全AT接口校验失败，返回对应安全封包 */
        return SC_APSEC_CreateSecPacket(enResult, &stSecPacket, pucSecPacket, pulSPLen);
    }

    /* 校验SeqID、MajorVer、MinorVer、Flag等 */
    pstMajorCMD     = (SC_APSEC_SP_MAJOR_CMD_STRU*)&stSecPacket.stHeader.ucMajorCMD;
    enResult        = SC_APSEC_CheckSecPacket(&stSecPacket);
    if (SC_APSEC_SP_OK == enResult)
    {
        /* 校验成功，根据数据段调用对应的接口函数 */
        switch ( pstMajorCMD->ucType )
        {
            case SC_APSEC_SP_MAJOR_SECSTORE:
                SC_APSEC_DealSecureStorage(&stSecPacket);
                break;
            default:
                enResult    = SC_APSEC_SP_PARA_ERR;
        }
    }

    /* 本地全局变量中的SeqID自增1 */
    SC_APSEC_IncrementSeqID();

    /* 填写安全封包, 并返回 */
    return SC_APSEC_CreateSecPacket(enResult, &stSecPacket, pucSecPacket, pulSPLen);
}

/*****************************************************************************
 函 数 名  : SC_APSEC_GetSecItemDefaultTbl
 功能描述  : 获取安全项默认值表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : SC_APSEC_SECTURE_ITEM_STRU     -- 安全项默认值表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年01月05日
    作    者   : l00198894
    修改内容   : DTS2013010400039: ISDB安全存储增加NV项，控制默认值版本

*****************************************************************************/
SC_APSEC_SECTURE_ITEM_STRU* SC_APSEC_GetSecItemDefaultTbl(VOS_VOID)
{
    OM_ISDB_DEFAULT_KEY_STRU     stDefaultKeyVer;

    stDefaultKeyVer.aenISDBKey[0] = SC_APSEC_DEFAULT_KEY_VER_BUTT;

    if (NV_OK != NV_Read(en_NV_Item_ISDB_DEFAULT_KEY, &stDefaultKeyVer, sizeof(stDefaultKeyVer)))
    {
        SC_ERROR_LOG("SC_APSEC_GetSecItemDefaultTbl: NV_Read failed!");
        return VOS_NULL_PTR;
    }

    if (SC_APSEC_DEFAULT_KEY_VER_BUTT <= stDefaultKeyVer.aenISDBKey[0])
    {
        SC_ERROR1_LOG("SC_APSEC_GetSecItemDefaultTbl: Error SC_APSEC_DEFAULT_KEY_VER: ", stDefaultKeyVer.aenISDBKey[0]);
        return VOS_NULL_PTR;
    }

    return g_astSecItemDefaultTbl[stDefaultKeyVer.aenISDBKey[0]];
}

/*****************************************************************************
 函 数 名  : SC_APSEC_GetDefaultSecItem
 功能描述  : 获取安全项默认值
 输入参数  : SC_APSEC_ITME_ENUM_UINT32   enSecItemId    -- 安全项ID
 输出参数  : SC_APSEC_DEFAULT_ITEM_STRU *pstSecItem     -- 安全项默认值
 返 回 值  : VOS_OK     -- 安全项默认值获取成功
             VOS_ERR    -- 安全项默认值获取失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月22日
    作    者   : l00198894
    修改内容   : 新生成函数

  2.日    期   : 2013年01月05日
    作    者   : l00198894
    修改内容   : DTS2013010400039: ISDB安全存储增加NV项，控制默认值版本

*****************************************************************************/
VOS_UINT32 SC_APSEC_GetDefaultSecItem(
    SC_APSEC_ITME_ENUM_UINT32           enSecItemId,
    SC_APSEC_DEFAULT_ITEM_STRU         *pstSecItem)
{
    VOS_UINT8                           ucLoop;
    SC_APSEC_SECTURE_ITEM_STRU         *pastSecItemDefaultTbl;

    pastSecItemDefaultTbl = SC_APSEC_GetSecItemDefaultTbl();

    if (VOS_NULL_PTR == pastSecItemDefaultTbl)
    {
        return VOS_ERR;
    }

    for (ucLoop = 0; ucLoop < SC_SECURITY_ITEM_NUM; ucLoop++)
    {
        if (pastSecItemDefaultTbl[ucLoop].enItemId == enSecItemId)
        {
            if ( (0 == pastSecItemDefaultTbl[ucLoop].ulItemLen)
              || (VOS_NULL_PTR == pastSecItemDefaultTbl[ucLoop].pucContent) )
            {
                /* 该安全项无默认值，直接返回VOS_ERR */
                return VOS_ERR;
            }
            else
            {
                /* 将安全项默认值填写到返回结构中 */
                pstSecItem->ulItemLen = pastSecItemDefaultTbl[ucLoop].ulItemLen;
                /*lint -e534*/
                VOS_MemCpy(pstSecItem->aucContent,
                           pastSecItemDefaultTbl[ucLoop].pucContent,
                           pastSecItemDefaultTbl[ucLoop].ulItemLen);
                /*lint +e534*/
                return VOS_OK;
            }
        }
    }

    return VOS_ERR;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
