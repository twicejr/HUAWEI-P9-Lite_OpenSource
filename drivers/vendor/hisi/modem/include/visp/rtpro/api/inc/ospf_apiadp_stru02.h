/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ospf_apiadp_stru02.h
*
*  Project Code: VISPV1R7C02
*   Module Name: OSPF  
*   Description: 
*   01 OSPF 适配模块定义的结构(Query 结构)
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-11-25   liangjicheng             Create                              
*******************************************************************************/

#ifndef OSPF_APIADP_STRU02_H
#define OSPF_APIADP_STRU02_H

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/*此数据结构中包含AMB_OSPF_PM_LSDB中的全部not-accessible项*/
typedef struct tagOSPF_LSDB_KEY
{
    UCHAR ucAreaId[4];
    ULONG ulType;
    UCHAR ucLsId[4];
    UCHAR ucRouterId[4];
    ULONG ulProcessId;
}OSPF_LSDB_KEY_S;

typedef struct tagOSPF_CFG_GRHELPER
{
    ULONG ulHelperMode;
    ULONG ulGrPeriod;
    /*Add for BC3D02908*/
    ULONG ulAccNum;
    /*end BC3D02908*/
}OSPF_CFG_GRHELPER_S;

/*Note:此数据结构包含MIB中的全部not-accessiable项*/
typedef struct tagOSPF_SHOWIF_KEY
{
    UCHAR ucIpAddr[4];
    ULONG ulAddr_less_if;
    ULONG ulProcessId;
}OSPF_SHOWIF_KEY_S;

/*此数据结构包含AMB_OSPF_PM_NBR中的所有not-accessiable项*/
typedef struct tagOSPF_NBR_KEY
{
    UCHAR ucIpAddr[4];
    ULONG ulAddr_Less_If;
    ULONG ulProcessId;
}OSPF_NBR_KEY_S;

/*此数据结构包含ospf routing表的key*/
typedef struct tagOSPF_ROUTING_KEY
{
    ULONG ulProcessId;
    UCHAR ucDstIp[4];
    UCHAR ucDstIpMask[4];
    ULONG ulAssiciated_Area_Id;
    UCHAR ucDestType;
    UCHAR ucPadding[3];
}OSPF_ROUTING_KEY_S;

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
typedef struct tagOSPF_SHOWNETWORK_INFO
{
    USHORT usProcessId;
    USHORT   usIsAllVRF;
    ULONG  ulVrfIndex;
}OSPF_SHOWNETWORK_INFO_S;
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

typedef struct tagOSPF_NETWORK_KEY
{
    ULONG ulNotFirst;
    ULONG ulProcessId;
    ULONG ulArea;
    ULONG ulNetworkAddr;
    ULONG ulNetworkLen;
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    ULONG ulVrfIndex;
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}OSPF_NETWORK_KEY_S;


/*此数据结据包含AMB_OSPF_PM_VIRT_IF全部的not-accessiable项*/
typedef struct tagOSPF_VIRTUAL_IF_KEY
{
    UCHAR ucAreaId[4];
    UCHAR ucNeighbor[4];
    ULONG ulProcessId;
}OSPF_VIRTUAL_IF_KEY_S;

/*此数据结构包含AMB_OSPF_PM_VIRT_LOCAL_LSDB所有的not-accessiable项*/
typedef struct tagOSPF_VIRTUAL_LSDB_KEY
{
    UCHAR uctransit_area_id[4];
    UCHAR ucneighbor[4];
    ULONG ultype;
    UCHAR ucls_id[4];
    UCHAR ucrouter_id[4];
    ULONG ulappl_index;
}OSPF_VIRTUAL_LSDB_KEY_S;

typedef struct tagOSPF_VIRTUAL_NBR_KEY
{
    UCHAR ucarea_id[4];
    UCHAR ucrtr_id[4];
    ULONG ulappl_index;    
}OSPF_VIRTUAL_NBR_KEY_S;

/*此数据结构包括ospf entity mib中的所有not-accessiable项*/
typedef struct tagOSPF_ENTITY_KEY
{
    ULONG ulProcessId;             /*OSPF实例号*/
}OSPF_ENTITY_KEY_S;

/*此数据结构包括ospf area mib中的所有not-accessiable项*/
typedef struct tagOSPF_AREA_KEY
{
    UCHAR ucAreaId[4];
    ULONG ulProcessId;    
    ULONG ulGetAreaFlag;  /* DTS2010093002164 liangjicheng 2010-10-12 增加标志区分是否已经获取*/
}OSPF_AREA_KEY_S;

/*此数据结构包括ospf if metric mib中的所有not-accessiable项*/
typedef struct tagOSPF_IF_METRIC_KEY
{
    UCHAR ucIPAddr[4];             /*address*/
    ULONG ulAddr_Less_If;          /*address less if*/
    ULONG ulTos;                   /*The type of service metric being referenced*/
    ULONG ulProcess_Id;            /*Process Id*/
}OSPF_IF_METRIC_KEY_S;

/*此数据结构包括ospf area agg中的所有not-accessible项*/
typedef struct tagOSPF_AREA_AGG_KEY
{
    UCHAR ucAreaId[4];             /*area id*/
    ULONG ulLsdb_Type;             /*Lsdb type*/
    UCHAR ucIpAddr[4];             /*address*/
    UCHAR ucIpMask[4];             /*ip mask*/
    ULONG ulProcessId;             /*process id*/
}OSPF_AREA_AGG_KEY_S;

/*Added by guo00178934, OSPF区域配置参数和区域状态, 2011/11/25   问题单号:DTS2011092904809  */
typedef struct tagOSPF_CFGAREA_LOG
{
    ULONG  ulAreaId;                    /*区域ID*/ 
    USHORT bNoFlag;                     /*表明配置还是删除区域,1配置，0删除*/
    USHORT usProcessId;                 /*进程id*/
    ULONG  ulAreaStatus;                /*row_status|admin_status|oper_status|ambl_state*/
}OSPF_CFGAREA_LOG_S;
/* End of Added by guo00178934, 2011/11/25   问题单号:DTS2011092904809  */


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif
