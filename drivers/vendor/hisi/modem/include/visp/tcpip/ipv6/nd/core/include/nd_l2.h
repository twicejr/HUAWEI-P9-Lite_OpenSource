


#ifndef _ND_L2_H
#define _ND_L2_H

#ifdef  __cplusplus
extern "C"{
#endif  /* #ifdef  __cplusplus */

#define IP6_ND_ADDRESS_TO_NETWORK(dst, src)\
{\
    dst[0] = VOS_HTONL(src[0]);\
    dst[1] = VOS_HTONL(src[1]);\
    dst[2] = VOS_HTONL(src[2]);\
    dst[3] = VOS_HTONL(src[3]);\
}

#define IP6_ND_HOST_PREFIX_LENGTH    128

enum IP6_ND_enum_for_return
{
    IP6_ND_enum_for_return_Continue = 1,
    IP6_ND_enum_for_return_OK,
    IP6_ND_enum_for_return_ERROR,
};

enum IP6_ND_enum_for_delete_type
{
    IP6_ND_enum_for_delete_All = 1,
    IP6_ND_enum_for_delete_Dynamic,
    IP6_ND_enum_for_delete_Static,
};

struct tagND_FOR_DO_SOMETHING_S;

typedef ULONG (*IP6_ND_FOR_DO_Proc_Type)(ND_NBENTRY_S*,struct tagND_FOR_DO_SOMETHING_S* );

typedef struct tagND_FOR_DO_SOMETHING_S
{
    ULONG       ulType;
    ULONG       ulSlot;
    ULONG       ulIfIndex;
    ULONG       ulItemNum;
    ULONG       ulSecond;
    ULONG       ulUSecond;
    USHORT      usVlanId;
    USHORT      usMasterOld;
    USHORT      usMasterNew;
    USHORT      usPad;
    NDINFO_S   *pstNDInfo;
    ND_TIMER_S  *pstNDTimer;
    IN6ADDR_S   stPrefix;
    IN6ADDR_S   stPrefixMask;
    IP6_ND_FOR_DO_Proc_Type     p_Do_Func;
    DLL_S       stPortInfo;
    USHORT      usStartVlanId;
    USHORT      usEndVlanId;
    ULONG       ulVrfIndex;
}ND_FOR_DO_SOMETHING_S;

#ifdef  __cplusplus
}
#endif  /* #ifdef  __cplusplus */

#endif  /* _ND_L2_H*/

