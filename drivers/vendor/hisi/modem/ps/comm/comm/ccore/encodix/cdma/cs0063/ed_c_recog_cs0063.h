/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c-recog
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __ed_c_recog_cs0063_h
#define __ed_c_recog_cs0063_h
#include "ed_c_cs0063.h"
#if ED_COMMON_CRC != 0x328E3625 && ED_VERSION != 10152 && ED_VERSION != 10153
#error Invalid Encodix library files linked; used those distributed with Encodix 1.0.154
#endif

#include "ed_user.h"
#define ED_MAXSIZE 600
#include "endec_configs_cs0063.h"

#ifdef __cplusplus
	extern "C" {
#endif

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group EMFPKA_EMFPA_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_EMFPKA_EMFPA_INCFG_Unrecognized = 0,
	ID_EMFPKA_EMFPA_INCFG_EMFPKA_EMFPA_INCFG_ConfigurationRequest,
	ID_EMFPKA_EMFPA_INCFG_EMFPKA_EMFPA_INCFG_ConfigurationResponse
} TEMFPKA_EMFPA_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group EMFPKA_EMFPA_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TEMFPKA_EMFPA_INCFG_Type Type;
	int MessageType;
	union {
		c_EMFPKA_EMFPA_INCFG_ConfigurationRequest* fld_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest;
		c_EMFPKA_EMFPA_INCFG_ConfigurationResponse* fld_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TEMFPKA_EMFPA_INCFG_Data;
#define INIT_TEMFPKA_EMFPA_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TEMFPKA_EMFPA_INCFG_Data)), (sp)->Type=ID_EMFPKA_EMFPA_INCFG_Unrecognized)
void FREE_TEMFPKA_EMFPA_INCFG_Data (TEMFPKA_EMFPA_INCFG_Data* sp);

void SETPRESENT_TEMFPKA_EMFPA_INCFG_Data(TEMFPKA_EMFPA_INCFG_Data* sp, TEMFPKA_EMFPA_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group EMFPKA_RSP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_EMFPKA_RSP_INUSE_Unrecognized = 0,
	ID_EMFPKA_RSP_INUSE_EMFPKA_RSP_INUSE_RouteSelect,
	ID_EMFPKA_RSP_INUSE_EMFPKA_RSP_INUSE_RouteSelectAck,
	ID_EMFPKA_RSP_INUSE_EMFPKA_RSP_INUSE_ActivateRoute,
	ID_EMFPKA_RSP_INUSE_EMFPKA_RSP_INUSE_ActivateRouteAck
} TEMFPKA_RSP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group EMFPKA_RSP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TEMFPKA_RSP_INUSE_Type Type;
	int MessageType;
	union {
		c_EMFPKA_RSP_INUSE_RouteSelect* fld_c_EMFPKA_RSP_INUSE_RouteSelect;
		c_EMFPKA_RSP_INUSE_RouteSelectAck* fld_c_EMFPKA_RSP_INUSE_RouteSelectAck;
		c_EMFPKA_RSP_INUSE_ActivateRoute* fld_c_EMFPKA_RSP_INUSE_ActivateRoute;
		c_EMFPKA_RSP_INUSE_ActivateRouteAck* fld_c_EMFPKA_RSP_INUSE_ActivateRouteAck;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TEMFPKA_RSP_INUSE_Data;
#define INIT_TEMFPKA_RSP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TEMFPKA_RSP_INUSE_Data)), (sp)->Type=ID_EMFPKA_RSP_INUSE_Unrecognized)
void FREE_TEMFPKA_RSP_INUSE_Data (TEMFPKA_RSP_INUSE_Data* sp);

void SETPRESENT_TEMFPKA_RSP_INUSE_Data(TEMFPKA_RSP_INUSE_Data* sp, TEMFPKA_RSP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group EMFPKA_RLP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_EMFPKA_RLP_INUSE_Unrecognized = 0,
	ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ResetTxIndication,
	ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ResetRxIndication,
	ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ResetTxIndicationAck,
	ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ResetTxComplete,
	ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ResetRxComplete,
	ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_Nak,
	ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ReservationOnRequest,
	ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ReservationOffRequest,
	ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ReservationAccept,
	ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ReservationReject,
	ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_RevReservationOn,
	ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_RevReservationOff,
	ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_FwdReservationOff,
	ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_FwdReservationOn,
	ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_FwdReservationAck,
	ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_AttributeUpdateRequest,
	ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_AttributeUpdateAccept,
	ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_AttributeUpdateReject
} TEMFPKA_RLP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group EMFPKA_RLP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TEMFPKA_RLP_INUSE_Type Type;
	int MessageType;
	union {
		c_EMFPKA_RLP_INUSE_ResetTxIndication* fld_c_EMFPKA_RLP_INUSE_ResetTxIndication;
		c_EMFPKA_RLP_INUSE_ResetRxIndication* fld_c_EMFPKA_RLP_INUSE_ResetRxIndication;
		c_EMFPKA_RLP_INUSE_ResetTxIndicationAck* fld_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck;
		c_EMFPKA_RLP_INUSE_ResetTxComplete* fld_c_EMFPKA_RLP_INUSE_ResetTxComplete;
		c_EMFPKA_RLP_INUSE_ResetRxComplete* fld_c_EMFPKA_RLP_INUSE_ResetRxComplete;
		c_EMFPKA_RLP_INUSE_Nak* fld_c_EMFPKA_RLP_INUSE_Nak;
		c_EMFPKA_RLP_INUSE_ReservationOnRequest* fld_c_EMFPKA_RLP_INUSE_ReservationOnRequest;
		c_EMFPKA_RLP_INUSE_ReservationOffRequest* fld_c_EMFPKA_RLP_INUSE_ReservationOffRequest;
		c_EMFPKA_RLP_INUSE_ReservationAccept* fld_c_EMFPKA_RLP_INUSE_ReservationAccept;
		c_EMFPKA_RLP_INUSE_ReservationReject* fld_c_EMFPKA_RLP_INUSE_ReservationReject;
		c_EMFPKA_RLP_INUSE_RevReservationOn* fld_c_EMFPKA_RLP_INUSE_RevReservationOn;
		c_EMFPKA_RLP_INUSE_RevReservationOff* fld_c_EMFPKA_RLP_INUSE_RevReservationOff;
		c_EMFPKA_RLP_INUSE_FwdReservationOff* fld_c_EMFPKA_RLP_INUSE_FwdReservationOff;
		c_EMFPKA_RLP_INUSE_FwdReservationOn* fld_c_EMFPKA_RLP_INUSE_FwdReservationOn;
		c_EMFPKA_RLP_INUSE_FwdReservationAck* fld_c_EMFPKA_RLP_INUSE_FwdReservationAck;
		c_EMFPKA_RLP_INUSE_AttributeUpdateRequest* fld_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest;
		c_EMFPKA_RLP_INUSE_AttributeUpdateAccept* fld_c_EMFPKA_RLP_INUSE_AttributeUpdateAccept;
		c_EMFPKA_RLP_INUSE_AttributeUpdateReject* fld_c_EMFPKA_RLP_INUSE_AttributeUpdateReject;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TEMFPKA_RLP_INUSE_Data;
#define INIT_TEMFPKA_RLP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TEMFPKA_RLP_INUSE_Data)), (sp)->Type=ID_EMFPKA_RLP_INUSE_Unrecognized)
void FREE_TEMFPKA_RLP_INUSE_Data (TEMFPKA_RLP_INUSE_Data* sp);

void SETPRESENT_TEMFPKA_RLP_INUSE_Data(TEMFPKA_RLP_INUSE_Data* sp, TEMFPKA_RLP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group EMFPKA_DOSP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_EMFPKA_DOSP_INUSE_Unrecognized = 0,
	ID_EMFPKA_DOSP_INUSE_EMFPKA_DOSP_INUSE_DataOverSignaling,
	ID_EMFPKA_DOSP_INUSE_EMFPKA_DOSP_INUSE_DataOverSignalingAck
} TEMFPKA_DOSP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group EMFPKA_DOSP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TEMFPKA_DOSP_INUSE_Type Type;
	int MessageType;
	union {
		c_EMFPKA_DOSP_INUSE_DataOverSignaling* fld_c_EMFPKA_DOSP_INUSE_DataOverSignaling;
		c_EMFPKA_DOSP_INUSE_DataOverSignalingAck* fld_c_EMFPKA_DOSP_INUSE_DataOverSignalingAck;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TEMFPKA_DOSP_INUSE_Data;
#define INIT_TEMFPKA_DOSP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TEMFPKA_DOSP_INUSE_Data)), (sp)->Type=ID_EMFPKA_DOSP_INUSE_Unrecognized)
void FREE_TEMFPKA_DOSP_INUSE_Data (TEMFPKA_DOSP_INUSE_Data* sp);

void SETPRESENT_TEMFPKA_DOSP_INUSE_Data(TEMFPKA_DOSP_INUSE_Data* sp, TEMFPKA_DOSP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group EMFPKA_LUP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_EMFPKA_LUP_INUSE_Unrecognized = 0,
	ID_EMFPKA_LUP_INUSE_EMFPKA_LUP_INUSE_LocationRequest,
	ID_EMFPKA_LUP_INUSE_EMFPKA_LUP_INUSE_LocationNotification,
	ID_EMFPKA_LUP_INUSE_EMFPKA_LUP_INUSE_LocationAssignment,
	ID_EMFPKA_LUP_INUSE_EMFPKA_LUP_INUSE_LocationComplete,
	ID_EMFPKA_LUP_INUSE_EMFPKA_LUP_INUSE_StorageBLOBRequest,
	ID_EMFPKA_LUP_INUSE_EMFPKA_LUP_INUSE_StorageBLOBNotification,
	ID_EMFPKA_LUP_INUSE_EMFPKA_LUP_INUSE_StorageBLOBAssignment,
	ID_EMFPKA_LUP_INUSE_EMFPKA_LUP_INUSE_StorageBLOBComplete
} TEMFPKA_LUP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group EMFPKA_LUP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TEMFPKA_LUP_INUSE_Type Type;
	int MessageType;
	union {
		c_EMFPKA_LUP_INUSE_LocationRequest* fld_c_EMFPKA_LUP_INUSE_LocationRequest;
		c_EMFPKA_LUP_INUSE_LocationNotification* fld_c_EMFPKA_LUP_INUSE_LocationNotification;
		c_EMFPKA_LUP_INUSE_LocationAssignment* fld_c_EMFPKA_LUP_INUSE_LocationAssignment;
		c_EMFPKA_LUP_INUSE_LocationComplete* fld_c_EMFPKA_LUP_INUSE_LocationComplete;
		c_EMFPKA_LUP_INUSE_StorageBLOBRequest* fld_c_EMFPKA_LUP_INUSE_StorageBLOBRequest;
		c_EMFPKA_LUP_INUSE_StorageBLOBNotification* fld_c_EMFPKA_LUP_INUSE_StorageBLOBNotification;
		c_EMFPKA_LUP_INUSE_StorageBLOBAssignment* fld_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment;
		c_EMFPKA_LUP_INUSE_StorageBLOBComplete* fld_c_EMFPKA_LUP_INUSE_StorageBLOBComplete;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TEMFPKA_LUP_INUSE_Data;
#define INIT_TEMFPKA_LUP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TEMFPKA_LUP_INUSE_Data)), (sp)->Type=ID_EMFPKA_LUP_INUSE_Unrecognized)
void FREE_TEMFPKA_LUP_INUSE_Data (TEMFPKA_LUP_INUSE_Data* sp);

void SETPRESENT_TEMFPKA_LUP_INUSE_Data(TEMFPKA_LUP_INUSE_Data* sp, TEMFPKA_LUP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group EMFPKA_FCP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_EMFPKA_FCP_INUSE_Unrecognized = 0,
	ID_EMFPKA_FCP_INUSE_EMFPKA_FCP_INUSE_XonRequest,
	ID_EMFPKA_FCP_INUSE_EMFPKA_FCP_INUSE_XonResponse,
	ID_EMFPKA_FCP_INUSE_EMFPKA_FCP_INUSE_XoffRequest,
	ID_EMFPKA_FCP_INUSE_EMFPKA_FCP_INUSE_XoffResponse,
	ID_EMFPKA_FCP_INUSE_EMFPKA_FCP_INUSE_DataReady,
	ID_EMFPKA_FCP_INUSE_EMFPKA_FCP_INUSE_DataReadyAck,
	ID_EMFPKA_FCP_INUSE_EMFPKA_FCP_INUSE_RestartNetworkInterface,
	ID_EMFPKA_FCP_INUSE_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck
} TEMFPKA_FCP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group EMFPKA_FCP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TEMFPKA_FCP_INUSE_Type Type;
	int MessageType;
	union {
		c_EMFPKA_FCP_INUSE_XonRequest* fld_c_EMFPKA_FCP_INUSE_XonRequest;
		c_EMFPKA_FCP_INUSE_XonResponse* fld_c_EMFPKA_FCP_INUSE_XonResponse;
		c_EMFPKA_FCP_INUSE_XoffRequest* fld_c_EMFPKA_FCP_INUSE_XoffRequest;
		c_EMFPKA_FCP_INUSE_XoffResponse* fld_c_EMFPKA_FCP_INUSE_XoffResponse;
		c_EMFPKA_FCP_INUSE_DataReady* fld_c_EMFPKA_FCP_INUSE_DataReady;
		c_EMFPKA_FCP_INUSE_DataReadyAck* fld_c_EMFPKA_FCP_INUSE_DataReadyAck;
		c_EMFPKA_FCP_INUSE_RestartNetworkInterface* fld_c_EMFPKA_FCP_INUSE_RestartNetworkInterface;
		c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck* fld_c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TEMFPKA_FCP_INUSE_Data;
#define INIT_TEMFPKA_FCP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TEMFPKA_FCP_INUSE_Data)), (sp)->Type=ID_EMFPKA_FCP_INUSE_Unrecognized)
void FREE_TEMFPKA_FCP_INUSE_Data (TEMFPKA_FCP_INUSE_Data* sp);

void SETPRESENT_TEMFPKA_FCP_INUSE_Data(TEMFPKA_FCP_INUSE_Data* sp, TEMFPKA_FCP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group MLMFPA_MMFPA_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_MLMFPA_MMFPA_INCFG_Unrecognized = 0,
	ID_MLMFPA_MMFPA_INCFG_MLMFPA_MMFPA_INCFG_ConfigurationRequest,
	ID_MLMFPA_MMFPA_INCFG_MLMFPA_MMFPA_INCFG_ConfigurationResponse
} TMLMFPA_MMFPA_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group MLMFPA_MMFPA_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TMLMFPA_MMFPA_INCFG_Type Type;
	int MessageType;
	union {
		c_MLMFPA_MMFPA_INCFG_ConfigurationRequest* fld_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest;
		c_MLMFPA_MMFPA_INCFG_ConfigurationResponse* fld_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TMLMFPA_MMFPA_INCFG_Data;
#define INIT_TMLMFPA_MMFPA_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TMLMFPA_MMFPA_INCFG_Data)), (sp)->Type=ID_MLMFPA_MMFPA_INCFG_Unrecognized)
void FREE_TMLMFPA_MMFPA_INCFG_Data (TMLMFPA_MMFPA_INCFG_Data* sp);

void SETPRESENT_TMLMFPA_MMFPA_INCFG_Data(TMLMFPA_MMFPA_INCFG_Data* sp, TMLMFPA_MMFPA_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group MLMFPA_RSP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_MLMFPA_RSP_INUSE_Unrecognized = 0,
	ID_MLMFPA_RSP_INUSE_MLMFPA_RSP_INUSE_RouteSelect,
	ID_MLMFPA_RSP_INUSE_MLMFPA_RSP_INUSE_RouteSelectAck,
	ID_MLMFPA_RSP_INUSE_MLMFPA_RSP_INUSE_ActivateRoute,
	ID_MLMFPA_RSP_INUSE_MLMFPA_RSP_INUSE_ActivateRouteAck
} TMLMFPA_RSP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group MLMFPA_RSP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TMLMFPA_RSP_INUSE_Type Type;
	int MessageType;
	union {
		c_MLMFPA_RSP_INUSE_RouteSelect* fld_c_MLMFPA_RSP_INUSE_RouteSelect;
		c_MLMFPA_RSP_INUSE_RouteSelectAck* fld_c_MLMFPA_RSP_INUSE_RouteSelectAck;
		c_MLMFPA_RSP_INUSE_ActivateRoute* fld_c_MLMFPA_RSP_INUSE_ActivateRoute;
		c_MLMFPA_RSP_INUSE_ActivateRouteAck* fld_c_MLMFPA_RSP_INUSE_ActivateRouteAck;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TMLMFPA_RSP_INUSE_Data;
#define INIT_TMLMFPA_RSP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TMLMFPA_RSP_INUSE_Data)), (sp)->Type=ID_MLMFPA_RSP_INUSE_Unrecognized)
void FREE_TMLMFPA_RSP_INUSE_Data (TMLMFPA_RSP_INUSE_Data* sp);

void SETPRESENT_TMLMFPA_RSP_INUSE_Data(TMLMFPA_RSP_INUSE_Data* sp, TMLMFPA_RSP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group MLMFPA_SRP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_MLMFPA_SRP_INUSE_Unrecognized = 0,
	ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ResetTxIndication,
	ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ResetRxIndication,
	ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ResetTxIndicationAck,
	ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ResetTxComplete,
	ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ResetRxComplete,
	ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_MultiLinkNak,
	ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ReservationOnRequest,
	ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ReservationOffRequest,
	ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ReservationAccept,
	ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ReservationReject,
	ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_RevReservationOn,
	ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_RevReservationOff,
	ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_FwdReservationOff,
	ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_FwdReservationOn,
	ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_FwdReservationAck,
	ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_AttributeUpdateRequest,
	ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_AttributeUpdateAccept,
	ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_AttributeUpdateReject,
	ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_Flush,
	ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_Nak
} TMLMFPA_SRP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group MLMFPA_SRP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TMLMFPA_SRP_INUSE_Type Type;
	int MessageType;
	union {
		c_MLMFPA_SRP_INUSE_ResetTxIndication* fld_c_MLMFPA_SRP_INUSE_ResetTxIndication;
		c_MLMFPA_SRP_INUSE_ResetRxIndication* fld_c_MLMFPA_SRP_INUSE_ResetRxIndication;
		c_MLMFPA_SRP_INUSE_ResetTxIndicationAck* fld_c_MLMFPA_SRP_INUSE_ResetTxIndicationAck;
		c_MLMFPA_SRP_INUSE_ResetTxComplete* fld_c_MLMFPA_SRP_INUSE_ResetTxComplete;
		c_MLMFPA_SRP_INUSE_ResetRxComplete* fld_c_MLMFPA_SRP_INUSE_ResetRxComplete;
		c_MLMFPA_SRP_INUSE_MultiLinkNak* fld_c_MLMFPA_SRP_INUSE_MultiLinkNak;
		c_MLMFPA_SRP_INUSE_ReservationOnRequest* fld_c_MLMFPA_SRP_INUSE_ReservationOnRequest;
		c_MLMFPA_SRP_INUSE_ReservationOffRequest* fld_c_MLMFPA_SRP_INUSE_ReservationOffRequest;
		c_MLMFPA_SRP_INUSE_ReservationAccept* fld_c_MLMFPA_SRP_INUSE_ReservationAccept;
		c_MLMFPA_SRP_INUSE_ReservationReject* fld_c_MLMFPA_SRP_INUSE_ReservationReject;
		c_MLMFPA_SRP_INUSE_RevReservationOn* fld_c_MLMFPA_SRP_INUSE_RevReservationOn;
		c_MLMFPA_SRP_INUSE_RevReservationOff* fld_c_MLMFPA_SRP_INUSE_RevReservationOff;
		c_MLMFPA_SRP_INUSE_FwdReservationOff* fld_c_MLMFPA_SRP_INUSE_FwdReservationOff;
		c_MLMFPA_SRP_INUSE_FwdReservationOn* fld_c_MLMFPA_SRP_INUSE_FwdReservationOn;
		c_MLMFPA_SRP_INUSE_FwdReservationAck* fld_c_MLMFPA_SRP_INUSE_FwdReservationAck;
		c_MLMFPA_SRP_INUSE_AttributeUpdateRequest* fld_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest;
		c_MLMFPA_SRP_INUSE_AttributeUpdateAccept* fld_c_MLMFPA_SRP_INUSE_AttributeUpdateAccept;
		c_MLMFPA_SRP_INUSE_AttributeUpdateReject* fld_c_MLMFPA_SRP_INUSE_AttributeUpdateReject;
		c_MLMFPA_SRP_INUSE_Flush* fld_c_MLMFPA_SRP_INUSE_Flush;
		c_MLMFPA_SRP_INUSE_Nak* fld_c_MLMFPA_SRP_INUSE_Nak;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TMLMFPA_SRP_INUSE_Data;
#define INIT_TMLMFPA_SRP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TMLMFPA_SRP_INUSE_Data)), (sp)->Type=ID_MLMFPA_SRP_INUSE_Unrecognized)
void FREE_TMLMFPA_SRP_INUSE_Data (TMLMFPA_SRP_INUSE_Data* sp);

void SETPRESENT_TMLMFPA_SRP_INUSE_Data(TMLMFPA_SRP_INUSE_Data* sp, TMLMFPA_SRP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group MLMFPA_DOSP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_MLMFPA_DOSP_INUSE_Unrecognized = 0,
	ID_MLMFPA_DOSP_INUSE_MLMFPA_DOSP_INUSE_DataOverSignaling,
	ID_MLMFPA_DOSP_INUSE_MLMFPA_DOSP_INUSE_DataOverSignalingAck
} TMLMFPA_DOSP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group MLMFPA_DOSP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TMLMFPA_DOSP_INUSE_Type Type;
	int MessageType;
	union {
		c_MLMFPA_DOSP_INUSE_DataOverSignaling* fld_c_MLMFPA_DOSP_INUSE_DataOverSignaling;
		c_MLMFPA_DOSP_INUSE_DataOverSignalingAck* fld_c_MLMFPA_DOSP_INUSE_DataOverSignalingAck;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TMLMFPA_DOSP_INUSE_Data;
#define INIT_TMLMFPA_DOSP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TMLMFPA_DOSP_INUSE_Data)), (sp)->Type=ID_MLMFPA_DOSP_INUSE_Unrecognized)
void FREE_TMLMFPA_DOSP_INUSE_Data (TMLMFPA_DOSP_INUSE_Data* sp);

void SETPRESENT_TMLMFPA_DOSP_INUSE_Data(TMLMFPA_DOSP_INUSE_Data* sp, TMLMFPA_DOSP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group MLMFPA_LUP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_MLMFPA_LUP_INUSE_Unrecognized = 0,
	ID_MLMFPA_LUP_INUSE_MLMFPA_LUP_INUSE_LocationRequest,
	ID_MLMFPA_LUP_INUSE_MLMFPA_LUP_INUSE_LocationNotification,
	ID_MLMFPA_LUP_INUSE_MLMFPA_LUP_INUSE_LocationAssignment,
	ID_MLMFPA_LUP_INUSE_MLMFPA_LUP_INUSE_LocationComplete,
	ID_MLMFPA_LUP_INUSE_MLMFPA_LUP_INUSE_StorageBLOBRequest,
	ID_MLMFPA_LUP_INUSE_MLMFPA_LUP_INUSE_StorageBLOBNotification,
	ID_MLMFPA_LUP_INUSE_MLMFPA_LUP_INUSE_StorageBLOBAssignment,
	ID_MLMFPA_LUP_INUSE_MLMFPA_LUP_INUSE_StorageBLOBComplete
} TMLMFPA_LUP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group MLMFPA_LUP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TMLMFPA_LUP_INUSE_Type Type;
	int MessageType;
	union {
		c_MLMFPA_LUP_INUSE_LocationRequest* fld_c_MLMFPA_LUP_INUSE_LocationRequest;
		c_MLMFPA_LUP_INUSE_LocationNotification* fld_c_MLMFPA_LUP_INUSE_LocationNotification;
		c_MLMFPA_LUP_INUSE_LocationAssignment* fld_c_MLMFPA_LUP_INUSE_LocationAssignment;
		c_MLMFPA_LUP_INUSE_LocationComplete* fld_c_MLMFPA_LUP_INUSE_LocationComplete;
		c_MLMFPA_LUP_INUSE_StorageBLOBRequest* fld_c_MLMFPA_LUP_INUSE_StorageBLOBRequest;
		c_MLMFPA_LUP_INUSE_StorageBLOBNotification* fld_c_MLMFPA_LUP_INUSE_StorageBLOBNotification;
		c_MLMFPA_LUP_INUSE_StorageBLOBAssignment* fld_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment;
		c_MLMFPA_LUP_INUSE_StorageBLOBComplete* fld_c_MLMFPA_LUP_INUSE_StorageBLOBComplete;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TMLMFPA_LUP_INUSE_Data;
#define INIT_TMLMFPA_LUP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TMLMFPA_LUP_INUSE_Data)), (sp)->Type=ID_MLMFPA_LUP_INUSE_Unrecognized)
void FREE_TMLMFPA_LUP_INUSE_Data (TMLMFPA_LUP_INUSE_Data* sp);

void SETPRESENT_TMLMFPA_LUP_INUSE_Data(TMLMFPA_LUP_INUSE_Data* sp, TMLMFPA_LUP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group MLMFPA_FCP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_MLMFPA_FCP_INUSE_Unrecognized = 0,
	ID_MLMFPA_FCP_INUSE_MLMFPA_FCP_INUSE_XonRequest,
	ID_MLMFPA_FCP_INUSE_MLMFPA_FCP_INUSE_XonResponse,
	ID_MLMFPA_FCP_INUSE_MLMFPA_FCP_INUSE_XoffRequest,
	ID_MLMFPA_FCP_INUSE_MLMFPA_FCP_INUSE_XoffResponse,
	ID_MLMFPA_FCP_INUSE_MLMFPA_FCP_INUSE_DataReady,
	ID_MLMFPA_FCP_INUSE_MLMFPA_FCP_INUSE_DataReadyAck,
	ID_MLMFPA_FCP_INUSE_MLMFPA_FCP_INUSE_RestartNetworkInterface,
	ID_MLMFPA_FCP_INUSE_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck
} TMLMFPA_FCP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group MLMFPA_FCP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TMLMFPA_FCP_INUSE_Type Type;
	int MessageType;
	union {
		c_MLMFPA_FCP_INUSE_XonRequest* fld_c_MLMFPA_FCP_INUSE_XonRequest;
		c_MLMFPA_FCP_INUSE_XonResponse* fld_c_MLMFPA_FCP_INUSE_XonResponse;
		c_MLMFPA_FCP_INUSE_XoffRequest* fld_c_MLMFPA_FCP_INUSE_XoffRequest;
		c_MLMFPA_FCP_INUSE_XoffResponse* fld_c_MLMFPA_FCP_INUSE_XoffResponse;
		c_MLMFPA_FCP_INUSE_DataReady* fld_c_MLMFPA_FCP_INUSE_DataReady;
		c_MLMFPA_FCP_INUSE_DataReadyAck* fld_c_MLMFPA_FCP_INUSE_DataReadyAck;
		c_MLMFPA_FCP_INUSE_RestartNetworkInterface* fld_c_MLMFPA_FCP_INUSE_RestartNetworkInterface;
		c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck* fld_c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TMLMFPA_FCP_INUSE_Data;
#define INIT_TMLMFPA_FCP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TMLMFPA_FCP_INUSE_Data)), (sp)->Type=ID_MLMFPA_FCP_INUSE_Unrecognized)
void FREE_TMLMFPA_FCP_INUSE_Data (TMLMFPA_FCP_INUSE_Data* sp);

void SETPRESENT_TMLMFPA_FCP_INUSE_Data(TMLMFPA_FCP_INUSE_Data* sp, TMLMFPA_FCP_INUSE_Type toBeSetPresent);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_EMFPKA_EMFPA_INCFG (const char* buffer, TEMFPKA_EMFPA_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_EMFPKA_EMFPA_INCFG (const char* buffer, int len, TEMFPKA_EMFPA_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_EMFPKA_RSP_INUSE (const char* buffer, TEMFPKA_RSP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_EMFPKA_RSP_INUSE (const char* buffer, int len, TEMFPKA_RSP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_EMFPKA_RLP_INUSE (const char* buffer, TEMFPKA_RLP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_EMFPKA_RLP_INUSE (const char* buffer, int len, TEMFPKA_RLP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_EMFPKA_DOSP_INUSE (const char* buffer, TEMFPKA_DOSP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_EMFPKA_DOSP_INUSE (const char* buffer, int len, TEMFPKA_DOSP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_EMFPKA_LUP_INUSE (const char* buffer, TEMFPKA_LUP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_EMFPKA_LUP_INUSE (const char* buffer, int len, TEMFPKA_LUP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_EMFPKA_FCP_INUSE (const char* buffer, TEMFPKA_FCP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_EMFPKA_FCP_INUSE (const char* buffer, int len, TEMFPKA_FCP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_MLMFPA_MMFPA_INCFG (const char* buffer, TMLMFPA_MMFPA_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MLMFPA_MMFPA_INCFG (const char* buffer, int len, TMLMFPA_MMFPA_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_MLMFPA_RSP_INUSE (const char* buffer, TMLMFPA_RSP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MLMFPA_RSP_INUSE (const char* buffer, int len, TMLMFPA_RSP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_MLMFPA_SRP_INUSE (const char* buffer, TMLMFPA_SRP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MLMFPA_SRP_INUSE (const char* buffer, int len, TMLMFPA_SRP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_MLMFPA_DOSP_INUSE (const char* buffer, TMLMFPA_DOSP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MLMFPA_DOSP_INUSE (const char* buffer, int len, TMLMFPA_DOSP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_MLMFPA_LUP_INUSE (const char* buffer, TMLMFPA_LUP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MLMFPA_LUP_INUSE (const char* buffer, int len, TMLMFPA_LUP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_MLMFPA_FCP_INUSE (const char* buffer, TMLMFPA_FCP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MLMFPA_FCP_INUSE (const char* buffer, int len, TMLMFPA_FCP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

#ifdef __cplusplus
	}
#endif
#endif

