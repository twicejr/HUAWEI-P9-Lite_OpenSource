/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c-recog
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __ed_c_recog_cs0024_h
#define __ed_c_recog_cs0024_h
#include "ed_c_cs0024.h"
#if ED_COMMON_CRC != 0x328E3625 && ED_VERSION != 10152 && ED_VERSION != 10153
#error Invalid Encodix library files linked; used those distributed with Encodix 1.0.154
#endif

#include "ed_user.h"
#define ED_MAXSIZE 600
#include "endec_configs_cs0024.h"

#ifdef __cplusplus
	extern "C" {
#endif

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group CONN_DINSP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_CONN_DINSP_INUSE_Unrecognized = 0,
	ID_CONN_DINSP_INUSE_CONN_DINSP_INUSE_Sync
} TCONN_DINSP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group CONN_DINSP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TCONN_DINSP_INUSE_Type Type;
	int MessageType;
	union {
		c_CONN_DINSP_INUSE_Sync* fld_c_CONN_DINSP_INUSE_Sync;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TCONN_DINSP_INUSE_Data;
#define INIT_TCONN_DINSP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TCONN_DINSP_INUSE_Data)), (sp)->Type=ID_CONN_DINSP_INUSE_Unrecognized)
void FREE_TCONN_DINSP_INUSE_Data (TCONN_DINSP_INUSE_Data* sp);

void SETPRESENT_TCONN_DINSP_INUSE_Data(TCONN_DINSP_INUSE_Data* sp, TCONN_DINSP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group SIGAPP_SLP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_SIGAPP_SLP_INCFG_Unrecognized = 0,
	ID_SIGAPP_SLP_INCFG_SIGAPP_SLP_INCFG_ConfigurationRequest,
	ID_SIGAPP_SLP_INCFG_SIGAPP_SLP_INCFG_ConfigurationResponse
} TSIGAPP_SLP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group SIGAPP_SLP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TSIGAPP_SLP_INCFG_Type Type;
	int MessageType;
	union {
		c_SIGAPP_SLP_INCFG_ConfigurationRequest* fld_c_SIGAPP_SLP_INCFG_ConfigurationRequest;
		c_SIGAPP_SLP_INCFG_ConfigurationResponse* fld_c_SIGAPP_SLP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TSIGAPP_SLP_INCFG_Data;
#define INIT_TSIGAPP_SLP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TSIGAPP_SLP_INCFG_Data)), (sp)->Type=ID_SIGAPP_SLP_INCFG_Unrecognized)
void FREE_TSIGAPP_SLP_INCFG_Data (TSIGAPP_SLP_INCFG_Data* sp);

void SETPRESENT_TSIGAPP_SLP_INCFG_Data(TSIGAPP_SLP_INCFG_Data* sp, TSIGAPP_SLP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group SIGAPP_SLP
--------------------------------------------------------------------*/
typedef enum {
	ID_SIGAPP_SLP_Unrecognized = 0,
	ID_SIGAPP_SLP_SIGAPP_SLP_Reset,
	ID_SIGAPP_SLP_SIGAPP_SLP_ResetAck
} TSIGAPP_SLP_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group SIGAPP_SLP
--------------------------------------------------------------------*/
typedef struct {
	TSIGAPP_SLP_Type Type;
	int MessageType;
	union {
		c_SIGAPP_SLP_Reset* fld_c_SIGAPP_SLP_Reset;
		c_SIGAPP_SLP_ResetAck* fld_c_SIGAPP_SLP_ResetAck;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TSIGAPP_SLP_Data;
#define INIT_TSIGAPP_SLP_Data(sp) (ED_RESET_MEM ((sp), sizeof (TSIGAPP_SLP_Data)), (sp)->Type=ID_SIGAPP_SLP_Unrecognized)
void FREE_TSIGAPP_SLP_Data (TSIGAPP_SLP_Data* sp);

void SETPRESENT_TSIGAPP_SLP_Data(TSIGAPP_SLP_Data* sp, TSIGAPP_SLP_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group PKTAPP_DPA_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_PKTAPP_DPA_INCFG_Unrecognized = 0,
	ID_PKTAPP_DPA_INCFG_PKTAPP_DPA_INCFG_ConfigurationRequest,
	ID_PKTAPP_DPA_INCFG_PKTAPP_DPA_INCFG_ConfigurationResponse
} TPKTAPP_DPA_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group PKTAPP_DPA_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TPKTAPP_DPA_INCFG_Type Type;
	int MessageType;
	union {
		c_PKTAPP_DPA_INCFG_ConfigurationRequest* fld_c_PKTAPP_DPA_INCFG_ConfigurationRequest;
		c_PKTAPP_DPA_INCFG_ConfigurationResponse* fld_c_PKTAPP_DPA_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TPKTAPP_DPA_INCFG_Data;
#define INIT_TPKTAPP_DPA_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TPKTAPP_DPA_INCFG_Data)), (sp)->Type=ID_PKTAPP_DPA_INCFG_Unrecognized)
void FREE_TPKTAPP_DPA_INCFG_Data (TPKTAPP_DPA_INCFG_Data* sp);

void SETPRESENT_TPKTAPP_DPA_INCFG_Data(TPKTAPP_DPA_INCFG_Data* sp, TPKTAPP_DPA_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group PKTAPP_RLP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_PKTAPP_RLP_INUSE_Unrecognized = 0,
	ID_PKTAPP_RLP_INUSE_PKTAPP_RLP_INUSE_Reset,
	ID_PKTAPP_RLP_INUSE_PKTAPP_RLP_INUSE_ResetAck,
	ID_PKTAPP_RLP_INUSE_PKTAPP_RLP_INUSE_Nak
} TPKTAPP_RLP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group PKTAPP_RLP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TPKTAPP_RLP_INUSE_Type Type;
	int MessageType;
	union {
		c_PKTAPP_RLP_INUSE_Reset* fld_c_PKTAPP_RLP_INUSE_Reset;
		c_PKTAPP_RLP_INUSE_ResetAck* fld_c_PKTAPP_RLP_INUSE_ResetAck;
		c_PKTAPP_RLP_INUSE_Nak* fld_c_PKTAPP_RLP_INUSE_Nak;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TPKTAPP_RLP_INUSE_Data;
#define INIT_TPKTAPP_RLP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TPKTAPP_RLP_INUSE_Data)), (sp)->Type=ID_PKTAPP_RLP_INUSE_Unrecognized)
void FREE_TPKTAPP_RLP_INUSE_Data (TPKTAPP_RLP_INUSE_Data* sp);

void SETPRESENT_TPKTAPP_RLP_INUSE_Data(TPKTAPP_RLP_INUSE_Data* sp, TPKTAPP_RLP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group PKTAPP_LUP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_PKTAPP_LUP_INUSE_Unrecognized = 0,
	ID_PKTAPP_LUP_INUSE_PKTAPP_LUP_INUSE_LocationRequest,
	ID_PKTAPP_LUP_INUSE_PKTAPP_LUP_INUSE_LocationNotification,
	ID_PKTAPP_LUP_INUSE_PKTAPP_LUP_INUSE_LocationAssignment,
	ID_PKTAPP_LUP_INUSE_PKTAPP_LUP_INUSE_LocationComplete
} TPKTAPP_LUP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group PKTAPP_LUP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TPKTAPP_LUP_INUSE_Type Type;
	int MessageType;
	union {
		c_PKTAPP_LUP_INUSE_LocationRequest* fld_c_PKTAPP_LUP_INUSE_LocationRequest;
		c_PKTAPP_LUP_INUSE_LocationNotification* fld_c_PKTAPP_LUP_INUSE_LocationNotification;
		c_PKTAPP_LUP_INUSE_LocationAssignment* fld_c_PKTAPP_LUP_INUSE_LocationAssignment;
		c_PKTAPP_LUP_INUSE_LocationComplete* fld_c_PKTAPP_LUP_INUSE_LocationComplete;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TPKTAPP_LUP_INUSE_Data;
#define INIT_TPKTAPP_LUP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TPKTAPP_LUP_INUSE_Data)), (sp)->Type=ID_PKTAPP_LUP_INUSE_Unrecognized)
void FREE_TPKTAPP_LUP_INUSE_Data (TPKTAPP_LUP_INUSE_Data* sp);

void SETPRESENT_TPKTAPP_LUP_INUSE_Data(TPKTAPP_LUP_INUSE_Data* sp, TPKTAPP_LUP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group PKTAPP_FCP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_PKTAPP_FCP_INUSE_Unrecognized = 0,
	ID_PKTAPP_FCP_INUSE_PKTAPP_FCP_INUSE_XonRequest,
	ID_PKTAPP_FCP_INUSE_PKTAPP_FCP_INUSE_XonResponse,
	ID_PKTAPP_FCP_INUSE_PKTAPP_FCP_INUSE_XoffRequest,
	ID_PKTAPP_FCP_INUSE_PKTAPP_FCP_INUSE_XoffResponse,
	ID_PKTAPP_FCP_INUSE_PKTAPP_FCP_INUSE_DataReady,
	ID_PKTAPP_FCP_INUSE_PKTAPP_FCP_INUSE_DataReadyAck
} TPKTAPP_FCP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group PKTAPP_FCP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TPKTAPP_FCP_INUSE_Type Type;
	int MessageType;
	union {
		c_PKTAPP_FCP_INUSE_XonRequest* fld_c_PKTAPP_FCP_INUSE_XonRequest;
		c_PKTAPP_FCP_INUSE_XonResponse* fld_c_PKTAPP_FCP_INUSE_XonResponse;
		c_PKTAPP_FCP_INUSE_XoffRequest* fld_c_PKTAPP_FCP_INUSE_XoffRequest;
		c_PKTAPP_FCP_INUSE_XoffResponse* fld_c_PKTAPP_FCP_INUSE_XoffResponse;
		c_PKTAPP_FCP_INUSE_DataReady* fld_c_PKTAPP_FCP_INUSE_DataReady;
		c_PKTAPP_FCP_INUSE_DataReadyAck* fld_c_PKTAPP_FCP_INUSE_DataReadyAck;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TPKTAPP_FCP_INUSE_Data;
#define INIT_TPKTAPP_FCP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TPKTAPP_FCP_INUSE_Data)), (sp)->Type=ID_PKTAPP_FCP_INUSE_Unrecognized)
void FREE_TPKTAPP_FCP_INUSE_Data (TPKTAPP_FCP_INUSE_Data* sp);

void SETPRESENT_TPKTAPP_FCP_INUSE_Data(TPKTAPP_FCP_INUSE_Data* sp, TPKTAPP_FCP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group MFPAPP_MFPA_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_MFPAPP_MFPA_INCFG_Unrecognized = 0,
	ID_MFPAPP_MFPA_INCFG_MFPAPP_MFPA_INCFG_ConfigurationRequest,
	ID_MFPAPP_MFPA_INCFG_MFPAPP_MFPA_INCFG_ConfigurationResponse
} TMFPAPP_MFPA_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group MFPAPP_MFPA_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TMFPAPP_MFPA_INCFG_Type Type;
	int MessageType;
	union {
		c_MFPAPP_MFPA_INCFG_ConfigurationRequest* fld_c_MFPAPP_MFPA_INCFG_ConfigurationRequest;
		c_MFPAPP_MFPA_INCFG_ConfigurationResponse* fld_c_MFPAPP_MFPA_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TMFPAPP_MFPA_INCFG_Data;
#define INIT_TMFPAPP_MFPA_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TMFPAPP_MFPA_INCFG_Data)), (sp)->Type=ID_MFPAPP_MFPA_INCFG_Unrecognized)
void FREE_TMFPAPP_MFPA_INCFG_Data (TMFPAPP_MFPA_INCFG_Data* sp);

void SETPRESENT_TMFPAPP_MFPA_INCFG_Data(TMFPAPP_MFPA_INCFG_Data* sp, TMFPAPP_MFPA_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group MFPAPP_RLP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_MFPAPP_RLP_INUSE_Unrecognized = 0,
	ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ResetTxIndication,
	ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ResetRxIndication,
	ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ResetTxIndicationAck,
	ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ResetTxComplete,
	ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ResetRxComplete,
	ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_Nak,
	ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ReservationOnRequest,
	ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ReservationOffRequest,
	ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ReservationAccept,
	ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ReservationReject,
	ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_RevReservationOn,
	ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_RevReservationOff,
	ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_FwdReservationOff,
	ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_FwdReservationOn,
	ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_FwdReservationAck,
	ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_AttributeUpdateRequest,
	ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_AttributeUpdateAccept,
	ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_AttributeUpdateReject
} TMFPAPP_RLP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group MFPAPP_RLP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TMFPAPP_RLP_INUSE_Type Type;
	int MessageType;
	union {
		c_MFPAPP_RLP_INUSE_ResetTxIndication* fld_c_MFPAPP_RLP_INUSE_ResetTxIndication;
		c_MFPAPP_RLP_INUSE_ResetRxIndication* fld_c_MFPAPP_RLP_INUSE_ResetRxIndication;
		c_MFPAPP_RLP_INUSE_ResetTxIndicationAck* fld_c_MFPAPP_RLP_INUSE_ResetTxIndicationAck;
		c_MFPAPP_RLP_INUSE_ResetTxComplete* fld_c_MFPAPP_RLP_INUSE_ResetTxComplete;
		c_MFPAPP_RLP_INUSE_ResetRxComplete* fld_c_MFPAPP_RLP_INUSE_ResetRxComplete;
		c_MFPAPP_RLP_INUSE_Nak* fld_c_MFPAPP_RLP_INUSE_Nak;
		c_MFPAPP_RLP_INUSE_ReservationOnRequest* fld_c_MFPAPP_RLP_INUSE_ReservationOnRequest;
		c_MFPAPP_RLP_INUSE_ReservationOffRequest* fld_c_MFPAPP_RLP_INUSE_ReservationOffRequest;
		c_MFPAPP_RLP_INUSE_ReservationAccept* fld_c_MFPAPP_RLP_INUSE_ReservationAccept;
		c_MFPAPP_RLP_INUSE_ReservationReject* fld_c_MFPAPP_RLP_INUSE_ReservationReject;
		c_MFPAPP_RLP_INUSE_RevReservationOn* fld_c_MFPAPP_RLP_INUSE_RevReservationOn;
		c_MFPAPP_RLP_INUSE_RevReservationOff* fld_c_MFPAPP_RLP_INUSE_RevReservationOff;
		c_MFPAPP_RLP_INUSE_FwdReservationOff* fld_c_MFPAPP_RLP_INUSE_FwdReservationOff;
		c_MFPAPP_RLP_INUSE_FwdReservationOn* fld_c_MFPAPP_RLP_INUSE_FwdReservationOn;
		c_MFPAPP_RLP_INUSE_FwdReservationAck* fld_c_MFPAPP_RLP_INUSE_FwdReservationAck;
		c_MFPAPP_RLP_INUSE_AttributeUpdateRequest* fld_c_MFPAPP_RLP_INUSE_AttributeUpdateRequest;
		c_MFPAPP_RLP_INUSE_AttributeUpdateAccept* fld_c_MFPAPP_RLP_INUSE_AttributeUpdateAccept;
		c_MFPAPP_RLP_INUSE_AttributeUpdateReject* fld_c_MFPAPP_RLP_INUSE_AttributeUpdateReject;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TMFPAPP_RLP_INUSE_Data;
#define INIT_TMFPAPP_RLP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TMFPAPP_RLP_INUSE_Data)), (sp)->Type=ID_MFPAPP_RLP_INUSE_Unrecognized)
void FREE_TMFPAPP_RLP_INUSE_Data (TMFPAPP_RLP_INUSE_Data* sp);

void SETPRESENT_TMFPAPP_RLP_INUSE_Data(TMFPAPP_RLP_INUSE_Data* sp, TMFPAPP_RLP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group MFPAPP_DOSP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_MFPAPP_DOSP_INUSE_Unrecognized = 0,
	ID_MFPAPP_DOSP_INUSE_MFPAPP_DOSP_INUSE_DataOverSignaling,
	ID_MFPAPP_DOSP_INUSE_MFPAPP_DOSP_INUSE_DataOverSignalingAck
} TMFPAPP_DOSP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group MFPAPP_DOSP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TMFPAPP_DOSP_INUSE_Type Type;
	int MessageType;
	union {
		c_MFPAPP_DOSP_INUSE_DataOverSignaling* fld_c_MFPAPP_DOSP_INUSE_DataOverSignaling;
		c_MFPAPP_DOSP_INUSE_DataOverSignalingAck* fld_c_MFPAPP_DOSP_INUSE_DataOverSignalingAck;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TMFPAPP_DOSP_INUSE_Data;
#define INIT_TMFPAPP_DOSP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TMFPAPP_DOSP_INUSE_Data)), (sp)->Type=ID_MFPAPP_DOSP_INUSE_Unrecognized)
void FREE_TMFPAPP_DOSP_INUSE_Data (TMFPAPP_DOSP_INUSE_Data* sp);

void SETPRESENT_TMFPAPP_DOSP_INUSE_Data(TMFPAPP_DOSP_INUSE_Data* sp, TMFPAPP_DOSP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group MFPAPP_LUP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_MFPAPP_LUP_INUSE_Unrecognized = 0,
	ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_LocationRequest,
	ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_LocationNotification,
	ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_LocationAssignment,
	ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_LocationComplete,
	ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_StorageBLOBRequest,
	ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_StorageBLOBNotification,
	ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_StorageBLOBAssignment,
	ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_StorageBLOBComplete
} TMFPAPP_LUP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group MFPAPP_LUP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TMFPAPP_LUP_INUSE_Type Type;
	int MessageType;
	union {
		c_MFPAPP_LUP_INUSE_LocationRequest* fld_c_MFPAPP_LUP_INUSE_LocationRequest;
		c_MFPAPP_LUP_INUSE_LocationNotification* fld_c_MFPAPP_LUP_INUSE_LocationNotification;
		c_MFPAPP_LUP_INUSE_LocationAssignment* fld_c_MFPAPP_LUP_INUSE_LocationAssignment;
		c_MFPAPP_LUP_INUSE_LocationComplete* fld_c_MFPAPP_LUP_INUSE_LocationComplete;
		c_MFPAPP_LUP_INUSE_StorageBLOBRequest* fld_c_MFPAPP_LUP_INUSE_StorageBLOBRequest;
		c_MFPAPP_LUP_INUSE_StorageBLOBNotification* fld_c_MFPAPP_LUP_INUSE_StorageBLOBNotification;
		c_MFPAPP_LUP_INUSE_StorageBLOBAssignment* fld_c_MFPAPP_LUP_INUSE_StorageBLOBAssignment;
		c_MFPAPP_LUP_INUSE_StorageBLOBComplete* fld_c_MFPAPP_LUP_INUSE_StorageBLOBComplete;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TMFPAPP_LUP_INUSE_Data;
#define INIT_TMFPAPP_LUP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TMFPAPP_LUP_INUSE_Data)), (sp)->Type=ID_MFPAPP_LUP_INUSE_Unrecognized)
void FREE_TMFPAPP_LUP_INUSE_Data (TMFPAPP_LUP_INUSE_Data* sp);

void SETPRESENT_TMFPAPP_LUP_INUSE_Data(TMFPAPP_LUP_INUSE_Data* sp, TMFPAPP_LUP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group MFPAPP_FCP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_MFPAPP_FCP_INUSE_Unrecognized = 0,
	ID_MFPAPP_FCP_INUSE_MFPAPP_FCP_INUSE_XonRequest,
	ID_MFPAPP_FCP_INUSE_MFPAPP_FCP_INUSE_XonResponse,
	ID_MFPAPP_FCP_INUSE_MFPAPP_FCP_INUSE_XoffRequest,
	ID_MFPAPP_FCP_INUSE_MFPAPP_FCP_INUSE_XoffResponse,
	ID_MFPAPP_FCP_INUSE_MFPAPP_FCP_INUSE_DataReady,
	ID_MFPAPP_FCP_INUSE_MFPAPP_FCP_INUSE_DataReadyAck
} TMFPAPP_FCP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group MFPAPP_FCP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TMFPAPP_FCP_INUSE_Type Type;
	int MessageType;
	union {
		c_MFPAPP_FCP_INUSE_XonRequest* fld_c_MFPAPP_FCP_INUSE_XonRequest;
		c_MFPAPP_FCP_INUSE_XonResponse* fld_c_MFPAPP_FCP_INUSE_XonResponse;
		c_MFPAPP_FCP_INUSE_XoffRequest* fld_c_MFPAPP_FCP_INUSE_XoffRequest;
		c_MFPAPP_FCP_INUSE_XoffResponse* fld_c_MFPAPP_FCP_INUSE_XoffResponse;
		c_MFPAPP_FCP_INUSE_DataReady* fld_c_MFPAPP_FCP_INUSE_DataReady;
		c_MFPAPP_FCP_INUSE_DataReadyAck* fld_c_MFPAPP_FCP_INUSE_DataReadyAck;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TMFPAPP_FCP_INUSE_Data;
#define INIT_TMFPAPP_FCP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TMFPAPP_FCP_INUSE_Data)), (sp)->Type=ID_MFPAPP_FCP_INUSE_Unrecognized)
void FREE_TMFPAPP_FCP_INUSE_Data (TMFPAPP_FCP_INUSE_Data* sp);

void SETPRESENT_TMFPAPP_FCP_INUSE_Data(TMFPAPP_FCP_INUSE_Data* sp, TMFPAPP_FCP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group STREAM_DSP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_STREAM_DSP_INCFG_Unrecognized = 0,
	ID_STREAM_DSP_INCFG_STREAM_DSP_INCFG_ConfigurationRequest,
	ID_STREAM_DSP_INCFG_STREAM_DSP_INCFG_ConfigurationResponse
} TSTREAM_DSP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group STREAM_DSP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TSTREAM_DSP_INCFG_Type Type;
	int MessageType;
	union {
		c_STREAM_DSP_INCFG_ConfigurationRequest* fld_c_STREAM_DSP_INCFG_ConfigurationRequest;
		c_STREAM_DSP_INCFG_ConfigurationResponse* fld_c_STREAM_DSP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TSTREAM_DSP_INCFG_Data;
#define INIT_TSTREAM_DSP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TSTREAM_DSP_INCFG_Data)), (sp)->Type=ID_STREAM_DSP_INCFG_Unrecognized)
void FREE_TSTREAM_DSP_INCFG_Data (TSTREAM_DSP_INCFG_Data* sp);

void SETPRESENT_TSTREAM_DSP_INCFG_Data(TSTREAM_DSP_INCFG_Data* sp, TSTREAM_DSP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group STREAM_GVSP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_STREAM_GVSP_INCFG_Unrecognized = 0,
	ID_STREAM_GVSP_INCFG_STREAM_GVSP_INCFG_ConfigurationRequest,
	ID_STREAM_GVSP_INCFG_STREAM_GVSP_INCFG_ConfigurationResponse
} TSTREAM_GVSP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group STREAM_GVSP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TSTREAM_GVSP_INCFG_Type Type;
	int MessageType;
	union {
		c_STREAM_GVSP_INCFG_ConfigurationRequest* fld_c_STREAM_GVSP_INCFG_ConfigurationRequest;
		c_STREAM_GVSP_INCFG_ConfigurationResponse* fld_c_STREAM_GVSP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TSTREAM_GVSP_INCFG_Data;
#define INIT_TSTREAM_GVSP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TSTREAM_GVSP_INCFG_Data)), (sp)->Type=ID_STREAM_GVSP_INCFG_Unrecognized)
void FREE_TSTREAM_GVSP_INCFG_Data (TSTREAM_GVSP_INCFG_Data* sp);

void SETPRESENT_TSTREAM_GVSP_INCFG_Data(TSTREAM_GVSP_INCFG_Data* sp, TSTREAM_GVSP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group SESSION_DSMP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_SESSION_DSMP_INCFG_Unrecognized = 0,
	ID_SESSION_DSMP_INCFG_SESSION_DSMP_INCFG_ConfigurationRequest,
	ID_SESSION_DSMP_INCFG_SESSION_DSMP_INCFG_ConfigurationResponse
} TSESSION_DSMP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group SESSION_DSMP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TSESSION_DSMP_INCFG_Type Type;
	int MessageType;
	union {
		c_SESSION_DSMP_INCFG_ConfigurationRequest* fld_c_SESSION_DSMP_INCFG_ConfigurationRequest;
		c_SESSION_DSMP_INCFG_ConfigurationResponse* fld_c_SESSION_DSMP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TSESSION_DSMP_INCFG_Data;
#define INIT_TSESSION_DSMP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TSESSION_DSMP_INCFG_Data)), (sp)->Type=ID_SESSION_DSMP_INCFG_Unrecognized)
void FREE_TSESSION_DSMP_INCFG_Data (TSESSION_DSMP_INCFG_Data* sp);

void SETPRESENT_TSESSION_DSMP_INCFG_Data(TSESSION_DSMP_INCFG_Data* sp, TSESSION_DSMP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group SESSION_DSMP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_SESSION_DSMP_INUSE_Unrecognized = 0,
	ID_SESSION_DSMP_INUSE_SESSION_DSMP_INUSE_SessionClose,
	ID_SESSION_DSMP_INUSE_SESSION_DSMP_INUSE_KeepAliveRequest,
	ID_SESSION_DSMP_INUSE_SESSION_DSMP_INUSE_KeepAliveResponse
} TSESSION_DSMP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group SESSION_DSMP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TSESSION_DSMP_INUSE_Type Type;
	int MessageType;
	union {
		c_SESSION_DSMP_INUSE_SessionClose* fld_c_SESSION_DSMP_INUSE_SessionClose;
		c_SESSION_DSMP_INUSE_KeepAliveRequest* fld_c_SESSION_DSMP_INUSE_KeepAliveRequest;
		c_SESSION_DSMP_INUSE_KeepAliveResponse* fld_c_SESSION_DSMP_INUSE_KeepAliveResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TSESSION_DSMP_INUSE_Data;
#define INIT_TSESSION_DSMP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TSESSION_DSMP_INUSE_Data)), (sp)->Type=ID_SESSION_DSMP_INUSE_Unrecognized)
void FREE_TSESSION_DSMP_INUSE_Data (TSESSION_DSMP_INUSE_Data* sp);

void SETPRESENT_TSESSION_DSMP_INUSE_Data(TSESSION_DSMP_INUSE_Data* sp, TSESSION_DSMP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group SESSION_DAMP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_SESSION_DAMP_INCFG_Unrecognized = 0,
	ID_SESSION_DAMP_INCFG_SESSION_DAMP_INCFG_ConfigurationRequest,
	ID_SESSION_DAMP_INCFG_SESSION_DAMP_INCFG_ConfigurationResponse
} TSESSION_DAMP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group SESSION_DAMP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TSESSION_DAMP_INCFG_Type Type;
	int MessageType;
	union {
		c_SESSION_DAMP_INCFG_ConfigurationRequest* fld_c_SESSION_DAMP_INCFG_ConfigurationRequest;
		c_SESSION_DAMP_INCFG_ConfigurationResponse* fld_c_SESSION_DAMP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TSESSION_DAMP_INCFG_Data;
#define INIT_TSESSION_DAMP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TSESSION_DAMP_INCFG_Data)), (sp)->Type=ID_SESSION_DAMP_INCFG_Unrecognized)
void FREE_TSESSION_DAMP_INCFG_Data (TSESSION_DAMP_INCFG_Data* sp);

void SETPRESENT_TSESSION_DAMP_INCFG_Data(TSESSION_DAMP_INCFG_Data* sp, TSESSION_DAMP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group SESSION_DAMP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_SESSION_DAMP_INUSE_Unrecognized = 0,
	ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_UATIRequest,
	ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_UATIAssignment,
	ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_UATIComplete,
	ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_HardwareIDRequest,
	ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_HardwareIDResponse,
	ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_AttributeUpdateRequest,
	ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_AttributeUpdateAccept,
	ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_AttributeUpdateReject
} TSESSION_DAMP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group SESSION_DAMP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TSESSION_DAMP_INUSE_Type Type;
	int MessageType;
	union {
		c_SESSION_DAMP_INUSE_UATIRequest* fld_c_SESSION_DAMP_INUSE_UATIRequest;
		c_SESSION_DAMP_INUSE_UATIAssignment* fld_c_SESSION_DAMP_INUSE_UATIAssignment;
		c_SESSION_DAMP_INUSE_UATIComplete* fld_c_SESSION_DAMP_INUSE_UATIComplete;
		c_SESSION_DAMP_INUSE_HardwareIDRequest* fld_c_SESSION_DAMP_INUSE_HardwareIDRequest;
		c_SESSION_DAMP_INUSE_HardwareIDResponse* fld_c_SESSION_DAMP_INUSE_HardwareIDResponse;
		c_SESSION_DAMP_INUSE_AttributeUpdateRequest* fld_c_SESSION_DAMP_INUSE_AttributeUpdateRequest;
		c_SESSION_DAMP_INUSE_AttributeUpdateAccept* fld_c_SESSION_DAMP_INUSE_AttributeUpdateAccept;
		c_SESSION_DAMP_INUSE_AttributeUpdateReject* fld_c_SESSION_DAMP_INUSE_AttributeUpdateReject;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TSESSION_DAMP_INUSE_Data;
#define INIT_TSESSION_DAMP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TSESSION_DAMP_INUSE_Data)), (sp)->Type=ID_SESSION_DAMP_INUSE_Unrecognized)
void FREE_TSESSION_DAMP_INUSE_Data (TSESSION_DAMP_INUSE_Data* sp);

void SETPRESENT_TSESSION_DAMP_INUSE_Data(TSESSION_DAMP_INUSE_Data* sp, TSESSION_DAMP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group SESSION_DSCP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_SESSION_DSCP_INUSE_Unrecognized = 0,
	ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_ConfigurationComplete,
	ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_ConfigurationStart,
	ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_ConfigurationRequest,
	ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_ConfigurationResponse,
	ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_SoftConfigurationComplete,
	ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_LockConfiguration,
	ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_LockConfigurationAck,
	ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_UnLockConfiguration,
	ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_UnLockConfigurationAck,
	ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_DeletePersonality,
	ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_DeletePersonalityAck,
	ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_AttributeUpdateRequest,
	ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_AttributeUpdateAccept,
	ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_AttributeUpdateReject
} TSESSION_DSCP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group SESSION_DSCP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TSESSION_DSCP_INUSE_Type Type;
	int MessageType;
	union {
		c_SESSION_DSCP_INUSE_ConfigurationComplete* fld_c_SESSION_DSCP_INUSE_ConfigurationComplete;
		c_SESSION_DSCP_INUSE_ConfigurationStart* fld_c_SESSION_DSCP_INUSE_ConfigurationStart;
		c_SESSION_DSCP_INUSE_ConfigurationRequest* fld_c_SESSION_DSCP_INUSE_ConfigurationRequest;
		c_SESSION_DSCP_INUSE_ConfigurationResponse* fld_c_SESSION_DSCP_INUSE_ConfigurationResponse;
		c_SESSION_DSCP_INUSE_SoftConfigurationComplete* fld_c_SESSION_DSCP_INUSE_SoftConfigurationComplete;
		c_SESSION_DSCP_INUSE_LockConfiguration* fld_c_SESSION_DSCP_INUSE_LockConfiguration;
		c_SESSION_DSCP_INUSE_LockConfigurationAck* fld_c_SESSION_DSCP_INUSE_LockConfigurationAck;
		c_SESSION_DSCP_INUSE_UnLockConfiguration* fld_c_SESSION_DSCP_INUSE_UnLockConfiguration;
		c_SESSION_DSCP_INUSE_UnLockConfigurationAck* fld_c_SESSION_DSCP_INUSE_UnLockConfigurationAck;
		c_SESSION_DSCP_INUSE_DeletePersonality* fld_c_SESSION_DSCP_INUSE_DeletePersonality;
		c_SESSION_DSCP_INUSE_DeletePersonalityAck* fld_c_SESSION_DSCP_INUSE_DeletePersonalityAck;
		c_SESSION_DSCP_INUSE_AttributeUpdateRequest* fld_c_SESSION_DSCP_INUSE_AttributeUpdateRequest;
		c_SESSION_DSCP_INUSE_AttributeUpdateAccept* fld_c_SESSION_DSCP_INUSE_AttributeUpdateAccept;
		c_SESSION_DSCP_INUSE_AttributeUpdateReject* fld_c_SESSION_DSCP_INUSE_AttributeUpdateReject;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TSESSION_DSCP_INUSE_Data;
#define INIT_TSESSION_DSCP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TSESSION_DSCP_INUSE_Data)), (sp)->Type=ID_SESSION_DSCP_INUSE_Unrecognized)
void FREE_TSESSION_DSCP_INUSE_Data (TSESSION_DSCP_INUSE_Data* sp);

void SETPRESENT_TSESSION_DSCP_INUSE_Data(TSESSION_DSCP_INUSE_Data* sp, TSESSION_DSCP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group SESSION_GMCDP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_SESSION_GMCDP_INCFG_Unrecognized = 0,
	ID_SESSION_GMCDP_INCFG_SESSION_GMCDP_INCFG_ConfigurationRequest,
	ID_SESSION_GMCDP_INCFG_SESSION_GMCDP_INCFG_ConfigurationResponse
} TSESSION_GMCDP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group SESSION_GMCDP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TSESSION_GMCDP_INCFG_Type Type;
	int MessageType;
	union {
		c_SESSION_GMCDP_INCFG_ConfigurationRequest* fld_c_SESSION_GMCDP_INCFG_ConfigurationRequest;
		c_SESSION_GMCDP_INCFG_ConfigurationResponse* fld_c_SESSION_GMCDP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TSESSION_GMCDP_INCFG_Data;
#define INIT_TSESSION_GMCDP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TSESSION_GMCDP_INCFG_Data)), (sp)->Type=ID_SESSION_GMCDP_INCFG_Unrecognized)
void FREE_TSESSION_GMCDP_INCFG_Data (TSESSION_GMCDP_INCFG_Data* sp);

void SETPRESENT_TSESSION_GMCDP_INCFG_Data(TSESSION_GMCDP_INCFG_Data* sp, TSESSION_GMCDP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group CONN_DALMP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_CONN_DALMP_INCFG_Unrecognized = 0,
	ID_CONN_DALMP_INCFG_CONN_DALMP_INCFG_ConfigurationRequest,
	ID_CONN_DALMP_INCFG_CONN_DALMP_INCFG_ConfigurationResponse
} TCONN_DALMP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group CONN_DALMP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TCONN_DALMP_INCFG_Type Type;
	int MessageType;
	union {
		c_CONN_DALMP_INCFG_ConfigurationRequest* fld_c_CONN_DALMP_INCFG_ConfigurationRequest;
		c_CONN_DALMP_INCFG_ConfigurationResponse* fld_c_CONN_DALMP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TCONN_DALMP_INCFG_Data;
#define INIT_TCONN_DALMP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TCONN_DALMP_INCFG_Data)), (sp)->Type=ID_CONN_DALMP_INCFG_Unrecognized)
void FREE_TCONN_DALMP_INCFG_Data (TCONN_DALMP_INCFG_Data* sp);

void SETPRESENT_TCONN_DALMP_INCFG_Data(TCONN_DALMP_INCFG_Data* sp, TCONN_DALMP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group CONN_DALMP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_CONN_DALMP_INUSE_Unrecognized = 0,
	ID_CONN_DALMP_INUSE_CONN_DALMP_INUSE_Redirect,
	ID_CONN_DALMP_INUSE_CONN_DALMP_INUSE_ConnectionFailureReport,
	ID_CONN_DALMP_INUSE_CONN_DALMP_INUSE_ConnectionFailureReportAck
} TCONN_DALMP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group CONN_DALMP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TCONN_DALMP_INUSE_Type Type;
	int MessageType;
	union {
		c_CONN_DALMP_INUSE_Redirect* fld_c_CONN_DALMP_INUSE_Redirect;
		c_CONN_DALMP_INUSE_ConnectionFailureReport* fld_c_CONN_DALMP_INUSE_ConnectionFailureReport;
		c_CONN_DALMP_INUSE_ConnectionFailureReportAck* fld_c_CONN_DALMP_INUSE_ConnectionFailureReportAck;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TCONN_DALMP_INUSE_Data;
#define INIT_TCONN_DALMP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TCONN_DALMP_INUSE_Data)), (sp)->Type=ID_CONN_DALMP_INUSE_Unrecognized)
void FREE_TCONN_DALMP_INUSE_Data (TCONN_DALMP_INUSE_Data* sp);

void SETPRESENT_TCONN_DALMP_INUSE_Data(TCONN_DALMP_INUSE_Data* sp, TCONN_DALMP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group CONN_DINSP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_CONN_DINSP_INCFG_Unrecognized = 0,
	ID_CONN_DINSP_INCFG_CONN_DINSP_INCFG_ConfigurationRequest,
	ID_CONN_DINSP_INCFG_CONN_DINSP_INCFG_ConfigurationResponse
} TCONN_DINSP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group CONN_DINSP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TCONN_DINSP_INCFG_Type Type;
	int MessageType;
	union {
		c_CONN_DINSP_INCFG_ConfigurationRequest* fld_c_CONN_DINSP_INCFG_ConfigurationRequest;
		c_CONN_DINSP_INCFG_ConfigurationResponse* fld_c_CONN_DINSP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TCONN_DINSP_INCFG_Data;
#define INIT_TCONN_DINSP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TCONN_DINSP_INCFG_Data)), (sp)->Type=ID_CONN_DINSP_INCFG_Unrecognized)
void FREE_TCONN_DINSP_INCFG_Data (TCONN_DINSP_INCFG_Data* sp);

void SETPRESENT_TCONN_DINSP_INCFG_Data(TCONN_DINSP_INCFG_Data* sp, TCONN_DINSP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group CONN_DIDSP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_CONN_DIDSP_INCFG_Unrecognized = 0,
	ID_CONN_DIDSP_INCFG_CONN_DIDSP_INCFG_ConfigurationRequest,
	ID_CONN_DIDSP_INCFG_CONN_DIDSP_INCFG_ConfigurationResponse
} TCONN_DIDSP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group CONN_DIDSP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TCONN_DIDSP_INCFG_Type Type;
	int MessageType;
	union {
		c_CONN_DIDSP_INCFG_ConfigurationRequest* fld_c_CONN_DIDSP_INCFG_ConfigurationRequest;
		c_CONN_DIDSP_INCFG_ConfigurationResponse* fld_c_CONN_DIDSP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TCONN_DIDSP_INCFG_Data;
#define INIT_TCONN_DIDSP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TCONN_DIDSP_INCFG_Data)), (sp)->Type=ID_CONN_DIDSP_INCFG_Unrecognized)
void FREE_TCONN_DIDSP_INCFG_Data (TCONN_DIDSP_INCFG_Data* sp);

void SETPRESENT_TCONN_DIDSP_INCFG_Data(TCONN_DIDSP_INCFG_Data* sp, TCONN_DIDSP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group CONN_DIDSP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_CONN_DIDSP_INUSE_Unrecognized = 0,
	ID_CONN_DIDSP_INUSE_CONN_DIDSP_INUSE_Page,
	ID_CONN_DIDSP_INUSE_CONN_DIDSP_INUSE_ConnectionRequest,
	ID_CONN_DIDSP_INUSE_CONN_DIDSP_INUSE_ConnectionDeny
} TCONN_DIDSP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group CONN_DIDSP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TCONN_DIDSP_INUSE_Type Type;
	int MessageType;
	union {
		c_CONN_DIDSP_INUSE_Page* fld_c_CONN_DIDSP_INUSE_Page;
		c_CONN_DIDSP_INUSE_ConnectionRequest* fld_c_CONN_DIDSP_INUSE_ConnectionRequest;
		c_CONN_DIDSP_INUSE_ConnectionDeny* fld_c_CONN_DIDSP_INUSE_ConnectionDeny;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TCONN_DIDSP_INUSE_Data;
#define INIT_TCONN_DIDSP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TCONN_DIDSP_INUSE_Data)), (sp)->Type=ID_CONN_DIDSP_INUSE_Unrecognized)
void FREE_TCONN_DIDSP_INUSE_Data (TCONN_DIDSP_INUSE_Data* sp);

void SETPRESENT_TCONN_DIDSP_INUSE_Data(TCONN_DIDSP_INUSE_Data* sp, TCONN_DIDSP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group CONN_EISP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_CONN_EISP_INCFG_Unrecognized = 0,
	ID_CONN_EISP_INCFG_CONN_EISP_INCFG_ConfigurationRequest,
	ID_CONN_EISP_INCFG_CONN_EISP_INCFG_ConfigurationResponse
} TCONN_EISP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group CONN_EISP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TCONN_EISP_INCFG_Type Type;
	int MessageType;
	union {
		c_CONN_EISP_INCFG_ConfigurationRequest* fld_c_CONN_EISP_INCFG_ConfigurationRequest;
		c_CONN_EISP_INCFG_ConfigurationResponse* fld_c_CONN_EISP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TCONN_EISP_INCFG_Data;
#define INIT_TCONN_EISP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TCONN_EISP_INCFG_Data)), (sp)->Type=ID_CONN_EISP_INCFG_Unrecognized)
void FREE_TCONN_EISP_INCFG_Data (TCONN_EISP_INCFG_Data* sp);

void SETPRESENT_TCONN_EISP_INCFG_Data(TCONN_EISP_INCFG_Data* sp, TCONN_EISP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group CONN_EISP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_CONN_EISP_INUSE_Unrecognized = 0,
	ID_CONN_EISP_INUSE_CONN_EISP_INUSE_Page,
	ID_CONN_EISP_INUSE_CONN_EISP_INUSE_ConnectionRequest,
	ID_CONN_EISP_INUSE_CONN_EISP_INUSE_ConnectionDeny,
	ID_CONN_EISP_INUSE_CONN_EISP_INUSE_AttributeUpdateRequest,
	ID_CONN_EISP_INUSE_CONN_EISP_INUSE_AttributeUpdateAccept,
	ID_CONN_EISP_INUSE_CONN_EISP_INUSE_AttributeUpdateReject
} TCONN_EISP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group CONN_EISP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TCONN_EISP_INUSE_Type Type;
	int MessageType;
	union {
		c_CONN_EISP_INUSE_Page* fld_c_CONN_EISP_INUSE_Page;
		c_CONN_EISP_INUSE_ConnectionRequest* fld_c_CONN_EISP_INUSE_ConnectionRequest;
		c_CONN_EISP_INUSE_ConnectionDeny* fld_c_CONN_EISP_INUSE_ConnectionDeny;
		c_CONN_EISP_INUSE_AttributeUpdateRequest* fld_c_CONN_EISP_INUSE_AttributeUpdateRequest;
		c_CONN_EISP_INUSE_AttributeUpdateAccept* fld_c_CONN_EISP_INUSE_AttributeUpdateAccept;
		c_CONN_EISP_INUSE_AttributeUpdateReject* fld_c_CONN_EISP_INUSE_AttributeUpdateReject;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TCONN_EISP_INUSE_Data;
#define INIT_TCONN_EISP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TCONN_EISP_INUSE_Data)), (sp)->Type=ID_CONN_EISP_INUSE_Unrecognized)
void FREE_TCONN_EISP_INUSE_Data (TCONN_EISP_INUSE_Data* sp);

void SETPRESENT_TCONN_EISP_INUSE_Data(TCONN_EISP_INUSE_Data* sp, TCONN_EISP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group CONN_QISP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_CONN_QISP_INCFG_Unrecognized = 0,
	ID_CONN_QISP_INCFG_CONN_QISP_INCFG_ConfigurationRequest,
	ID_CONN_QISP_INCFG_CONN_QISP_INCFG_ConfigurationResponse
} TCONN_QISP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group CONN_QISP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TCONN_QISP_INCFG_Type Type;
	int MessageType;
	union {
		c_CONN_QISP_INCFG_ConfigurationRequest* fld_c_CONN_QISP_INCFG_ConfigurationRequest;
		c_CONN_QISP_INCFG_ConfigurationResponse* fld_c_CONN_QISP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TCONN_QISP_INCFG_Data;
#define INIT_TCONN_QISP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TCONN_QISP_INCFG_Data)), (sp)->Type=ID_CONN_QISP_INCFG_Unrecognized)
void FREE_TCONN_QISP_INCFG_Data (TCONN_QISP_INCFG_Data* sp);

void SETPRESENT_TCONN_QISP_INCFG_Data(TCONN_QISP_INCFG_Data* sp, TCONN_QISP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group CONN_QISP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_CONN_QISP_INUSE_Unrecognized = 0,
	ID_CONN_QISP_INUSE_CONN_QISP_INUSE_Page,
	ID_CONN_QISP_INUSE_CONN_QISP_INUSE_ConnectionRequest,
	ID_CONN_QISP_INUSE_CONN_QISP_INUSE_ConnectionDeny,
	ID_CONN_QISP_INUSE_CONN_QISP_INUSE_QuickPage,
	ID_CONN_QISP_INUSE_CONN_QISP_INUSE_AttributeUpdateRequest,
	ID_CONN_QISP_INUSE_CONN_QISP_INUSE_AttributeUpdateAccept,
	ID_CONN_QISP_INUSE_CONN_QISP_INUSE_AttributeUpdateReject
} TCONN_QISP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group CONN_QISP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TCONN_QISP_INUSE_Type Type;
	int MessageType;
	union {
		c_CONN_QISP_INUSE_Page* fld_c_CONN_QISP_INUSE_Page;
		c_CONN_QISP_INUSE_ConnectionRequest* fld_c_CONN_QISP_INUSE_ConnectionRequest;
		c_CONN_QISP_INUSE_ConnectionDeny* fld_c_CONN_QISP_INUSE_ConnectionDeny;
		c_CONN_QISP_INUSE_QuickPage* fld_c_CONN_QISP_INUSE_QuickPage;
		c_CONN_QISP_INUSE_AttributeUpdateRequest* fld_c_CONN_QISP_INUSE_AttributeUpdateRequest;
		c_CONN_QISP_INUSE_AttributeUpdateAccept* fld_c_CONN_QISP_INUSE_AttributeUpdateAccept;
		c_CONN_QISP_INUSE_AttributeUpdateReject* fld_c_CONN_QISP_INUSE_AttributeUpdateReject;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TCONN_QISP_INUSE_Data;
#define INIT_TCONN_QISP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TCONN_QISP_INUSE_Data)), (sp)->Type=ID_CONN_QISP_INUSE_Unrecognized)
void FREE_TCONN_QISP_INUSE_Data (TCONN_QISP_INUSE_Data* sp);

void SETPRESENT_TCONN_QISP_INUSE_Data(TCONN_QISP_INUSE_Data* sp, TCONN_QISP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group CONN_DCSP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_CONN_DCSP_INCFG_Unrecognized = 0,
	ID_CONN_DCSP_INCFG_CONN_DCSP_INCFG_ConfigurationRequest,
	ID_CONN_DCSP_INCFG_CONN_DCSP_INCFG_ConfigurationResponse
} TCONN_DCSP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group CONN_DCSP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TCONN_DCSP_INCFG_Type Type;
	int MessageType;
	union {
		c_CONN_DCSP_INCFG_ConfigurationRequest* fld_c_CONN_DCSP_INCFG_ConfigurationRequest;
		c_CONN_DCSP_INCFG_ConfigurationResponse* fld_c_CONN_DCSP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TCONN_DCSP_INCFG_Data;
#define INIT_TCONN_DCSP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TCONN_DCSP_INCFG_Data)), (sp)->Type=ID_CONN_DCSP_INCFG_Unrecognized)
void FREE_TCONN_DCSP_INCFG_Data (TCONN_DCSP_INCFG_Data* sp);

void SETPRESENT_TCONN_DCSP_INCFG_Data(TCONN_DCSP_INCFG_Data* sp, TCONN_DCSP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group CONN_DCSP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_CONN_DCSP_INUSE_Unrecognized = 0,
	ID_CONN_DCSP_INUSE_CONN_DCSP_INUSE_ConnectionClose
} TCONN_DCSP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group CONN_DCSP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TCONN_DCSP_INUSE_Type Type;
	int MessageType;
	union {
		c_CONN_DCSP_INUSE_ConnectionClose* fld_c_CONN_DCSP_INUSE_ConnectionClose;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TCONN_DCSP_INUSE_Data;
#define INIT_TCONN_DCSP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TCONN_DCSP_INUSE_Data)), (sp)->Type=ID_CONN_DCSP_INUSE_Unrecognized)
void FREE_TCONN_DCSP_INUSE_Data (TCONN_DCSP_INUSE_Data* sp);

void SETPRESENT_TCONN_DCSP_INUSE_Data(TCONN_DCSP_INUSE_Data* sp, TCONN_DCSP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group CONN_DRUP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_CONN_DRUP_INCFG_Unrecognized = 0,
	ID_CONN_DRUP_INCFG_CONN_DRUP_INCFG_ConfigurationRequest,
	ID_CONN_DRUP_INCFG_CONN_DRUP_INCFG_ConfigurationResponse
} TCONN_DRUP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group CONN_DRUP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TCONN_DRUP_INCFG_Type Type;
	int MessageType;
	union {
		c_CONN_DRUP_INCFG_ConfigurationRequest* fld_c_CONN_DRUP_INCFG_ConfigurationRequest;
		c_CONN_DRUP_INCFG_ConfigurationResponse* fld_c_CONN_DRUP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TCONN_DRUP_INCFG_Data;
#define INIT_TCONN_DRUP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TCONN_DRUP_INCFG_Data)), (sp)->Type=ID_CONN_DRUP_INCFG_Unrecognized)
void FREE_TCONN_DRUP_INCFG_Data (TCONN_DRUP_INCFG_Data* sp);

void SETPRESENT_TCONN_DRUP_INCFG_Data(TCONN_DRUP_INCFG_Data* sp, TCONN_DRUP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group CONN_DRUP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_CONN_DRUP_INUSE_Unrecognized = 0,
	ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_RouteUpdate,
	ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_TrafficChannelAssignment,
	ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_TrafficChannelComplete,
	ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_ResetReport,
	ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_NeighborList,
	ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_AttributeOverride,
	ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_AttributeOverrideResponse,
	ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_RouteUpdateRequest,
	ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_AttributeUpdateRequest,
	ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_AttributeUpdateAccept,
	ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_AttributeUpdateReject
} TCONN_DRUP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group CONN_DRUP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TCONN_DRUP_INUSE_Type Type;
	int MessageType;
	union {
		c_CONN_DRUP_INUSE_RouteUpdate* fld_c_CONN_DRUP_INUSE_RouteUpdate;
		c_CONN_DRUP_INUSE_TrafficChannelAssignment* fld_c_CONN_DRUP_INUSE_TrafficChannelAssignment;
		c_CONN_DRUP_INUSE_TrafficChannelComplete* fld_c_CONN_DRUP_INUSE_TrafficChannelComplete;
		c_CONN_DRUP_INUSE_ResetReport* fld_c_CONN_DRUP_INUSE_ResetReport;
		c_CONN_DRUP_INUSE_NeighborList* fld_c_CONN_DRUP_INUSE_NeighborList;
		c_CONN_DRUP_INUSE_AttributeOverride* fld_c_CONN_DRUP_INUSE_AttributeOverride;
		c_CONN_DRUP_INUSE_AttributeOverrideResponse* fld_c_CONN_DRUP_INUSE_AttributeOverrideResponse;
		c_CONN_DRUP_INUSE_RouteUpdateRequest* fld_c_CONN_DRUP_INUSE_RouteUpdateRequest;
		c_CONN_DRUP_INUSE_AttributeUpdateRequest* fld_c_CONN_DRUP_INUSE_AttributeUpdateRequest;
		c_CONN_DRUP_INUSE_AttributeUpdateAccept* fld_c_CONN_DRUP_INUSE_AttributeUpdateAccept;
		c_CONN_DRUP_INUSE_AttributeUpdateReject* fld_c_CONN_DRUP_INUSE_AttributeUpdateReject;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TCONN_DRUP_INUSE_Data;
#define INIT_TCONN_DRUP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TCONN_DRUP_INUSE_Data)), (sp)->Type=ID_CONN_DRUP_INUSE_Unrecognized)
void FREE_TCONN_DRUP_INUSE_Data (TCONN_DRUP_INUSE_Data* sp);

void SETPRESENT_TCONN_DRUP_INUSE_Data(TCONN_DRUP_INUSE_Data* sp, TCONN_DRUP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group CONN_MRUP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_CONN_MRUP_INCFG_Unrecognized = 0,
	ID_CONN_MRUP_INCFG_CONN_MRUP_INCFG_ConfigurationRequest,
	ID_CONN_MRUP_INCFG_CONN_MRUP_INCFG_ConfigurationResponse
} TCONN_MRUP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group CONN_MRUP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TCONN_MRUP_INCFG_Type Type;
	int MessageType;
	union {
		c_CONN_MRUP_INCFG_ConfigurationRequest* fld_c_CONN_MRUP_INCFG_ConfigurationRequest;
		c_CONN_MRUP_INCFG_ConfigurationResponse* fld_c_CONN_MRUP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TCONN_MRUP_INCFG_Data;
#define INIT_TCONN_MRUP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TCONN_MRUP_INCFG_Data)), (sp)->Type=ID_CONN_MRUP_INCFG_Unrecognized)
void FREE_TCONN_MRUP_INCFG_Data (TCONN_MRUP_INCFG_Data* sp);

void SETPRESENT_TCONN_MRUP_INCFG_Data(TCONN_MRUP_INCFG_Data* sp, TCONN_MRUP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group CONN_MRUP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_CONN_MRUP_INUSE_Unrecognized = 0,
	ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_RouteUpdate,
	ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_TrafficChannelAssignment,
	ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_TrafficChannelComplete,
	ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_ResetReport,
	ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_NeighborList,
	ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_RouteUpdateRequest,
	ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_AttributeUpdateRequest,
	ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_AttributeUpdateAccept,
	ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_AttributeUpdateReject
} TCONN_MRUP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group CONN_MRUP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TCONN_MRUP_INUSE_Type Type;
	int MessageType;
	union {
		c_CONN_MRUP_INUSE_RouteUpdate* fld_c_CONN_MRUP_INUSE_RouteUpdate;
		c_CONN_MRUP_INUSE_TrafficChannelAssignment* fld_c_CONN_MRUP_INUSE_TrafficChannelAssignment;
		c_CONN_MRUP_INUSE_TrafficChannelComplete* fld_c_CONN_MRUP_INUSE_TrafficChannelComplete;
		c_CONN_MRUP_INUSE_ResetReport* fld_c_CONN_MRUP_INUSE_ResetReport;
		c_CONN_MRUP_INUSE_NeighborList* fld_c_CONN_MRUP_INUSE_NeighborList;
		c_CONN_MRUP_INUSE_RouteUpdateRequest* fld_c_CONN_MRUP_INUSE_RouteUpdateRequest;
		c_CONN_MRUP_INUSE_AttributeUpdateRequest* fld_c_CONN_MRUP_INUSE_AttributeUpdateRequest;
		c_CONN_MRUP_INUSE_AttributeUpdateAccept* fld_c_CONN_MRUP_INUSE_AttributeUpdateAccept;
		c_CONN_MRUP_INUSE_AttributeUpdateReject* fld_c_CONN_MRUP_INUSE_AttributeUpdateReject;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TCONN_MRUP_INUSE_Data;
#define INIT_TCONN_MRUP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TCONN_MRUP_INUSE_Data)), (sp)->Type=ID_CONN_MRUP_INUSE_Unrecognized)
void FREE_TCONN_MRUP_INUSE_Data (TCONN_MRUP_INUSE_Data* sp);

void SETPRESENT_TCONN_MRUP_INUSE_Data(TCONN_MRUP_INUSE_Data* sp, TCONN_MRUP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group CONN_DPCP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_CONN_DPCP_INCFG_Unrecognized = 0,
	ID_CONN_DPCP_INCFG_CONN_DPCP_INCFG_ConfigurationRequest,
	ID_CONN_DPCP_INCFG_CONN_DPCP_INCFG_ConfigurationResponse
} TCONN_DPCP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group CONN_DPCP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TCONN_DPCP_INCFG_Type Type;
	int MessageType;
	union {
		c_CONN_DPCP_INCFG_ConfigurationRequest* fld_c_CONN_DPCP_INCFG_ConfigurationRequest;
		c_CONN_DPCP_INCFG_ConfigurationResponse* fld_c_CONN_DPCP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TCONN_DPCP_INCFG_Data;
#define INIT_TCONN_DPCP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TCONN_DPCP_INCFG_Data)), (sp)->Type=ID_CONN_DPCP_INCFG_Unrecognized)
void FREE_TCONN_DPCP_INCFG_Data (TCONN_DPCP_INCFG_Data* sp);

void SETPRESENT_TCONN_DPCP_INCFG_Data(TCONN_DPCP_INCFG_Data* sp, TCONN_DPCP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group CONN_OMP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_CONN_OMP_INCFG_Unrecognized = 0,
	ID_CONN_OMP_INCFG_CONN_OMP_INCFG_ConfigurationRequest,
	ID_CONN_OMP_INCFG_CONN_OMP_INCFG_ConfigurationResponse
} TCONN_OMP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group CONN_OMP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TCONN_OMP_INCFG_Type Type;
	int MessageType;
	union {
		c_CONN_OMP_INCFG_ConfigurationRequest* fld_c_CONN_OMP_INCFG_ConfigurationRequest;
		c_CONN_OMP_INCFG_ConfigurationResponse* fld_c_CONN_OMP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TCONN_OMP_INCFG_Data;
#define INIT_TCONN_OMP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TCONN_OMP_INCFG_Data)), (sp)->Type=ID_CONN_OMP_INCFG_Unrecognized)
void FREE_TCONN_OMP_INCFG_Data (TCONN_OMP_INCFG_Data* sp);

void SETPRESENT_TCONN_OMP_INCFG_Data(TCONN_OMP_INCFG_Data* sp, TCONN_OMP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group CONN_OMP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_CONN_OMP_INUSE_Unrecognized = 0,
	ID_CONN_OMP_INUSE_CONN_OMP_INUSE_QuickConfig,
	ID_CONN_OMP_INUSE_CONN_OMP_INUSE_SectorParameters
} TCONN_OMP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group CONN_OMP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TCONN_OMP_INUSE_Type Type;
	int MessageType;
	union {
		c_CONN_OMP_INUSE_QuickConfig* fld_c_CONN_OMP_INUSE_QuickConfig;
		c_CONN_OMP_INUSE_SectorParameters* fld_c_CONN_OMP_INUSE_SectorParameters;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TCONN_OMP_INUSE_Data;
#define INIT_TCONN_OMP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TCONN_OMP_INUSE_Data)), (sp)->Type=ID_CONN_OMP_INUSE_Unrecognized)
void FREE_TCONN_OMP_INUSE_Data (TCONN_OMP_INUSE_Data* sp);

void SETPRESENT_TCONN_OMP_INUSE_Data(TCONN_OMP_INUSE_Data* sp, TCONN_OMP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group SECURITY_DSP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_SECURITY_DSP_INCFG_Unrecognized = 0,
	ID_SECURITY_DSP_INCFG_SECURITY_DSP_INCFG_ConfigurationRequest,
	ID_SECURITY_DSP_INCFG_SECURITY_DSP_INCFG_ConfigurationResponse
} TSECURITY_DSP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group SECURITY_DSP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TSECURITY_DSP_INCFG_Type Type;
	int MessageType;
	union {
		c_SECURITY_DSP_INCFG_ConfigurationRequest* fld_c_SECURITY_DSP_INCFG_ConfigurationRequest;
		c_SECURITY_DSP_INCFG_ConfigurationResponse* fld_c_SECURITY_DSP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TSECURITY_DSP_INCFG_Data;
#define INIT_TSECURITY_DSP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TSECURITY_DSP_INCFG_Data)), (sp)->Type=ID_SECURITY_DSP_INCFG_Unrecognized)
void FREE_TSECURITY_DSP_INCFG_Data (TSECURITY_DSP_INCFG_Data* sp);

void SETPRESENT_TSECURITY_DSP_INCFG_Data(TSECURITY_DSP_INCFG_Data* sp, TSECURITY_DSP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group SECURITY_GSP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_SECURITY_GSP_INCFG_Unrecognized = 0,
	ID_SECURITY_GSP_INCFG_SECURITY_GSP_INCFG_ConfigurationRequest,
	ID_SECURITY_GSP_INCFG_SECURITY_GSP_INCFG_ConfigurationResponse
} TSECURITY_GSP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group SECURITY_GSP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TSECURITY_GSP_INCFG_Type Type;
	int MessageType;
	union {
		c_SECURITY_GSP_INCFG_ConfigurationRequest* fld_c_SECURITY_GSP_INCFG_ConfigurationRequest;
		c_SECURITY_GSP_INCFG_ConfigurationResponse* fld_c_SECURITY_GSP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TSECURITY_GSP_INCFG_Data;
#define INIT_TSECURITY_GSP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TSECURITY_GSP_INCFG_Data)), (sp)->Type=ID_SECURITY_GSP_INCFG_Unrecognized)
void FREE_TSECURITY_GSP_INCFG_Data (TSECURITY_GSP_INCFG_Data* sp);

void SETPRESENT_TSECURITY_GSP_INCFG_Data(TSECURITY_GSP_INCFG_Data* sp, TSECURITY_GSP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group SECURITY_DKEP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_SECURITY_DKEP_INCFG_Unrecognized = 0,
	ID_SECURITY_DKEP_INCFG_SECURITY_DKEP_INCFG_ConfigurationRequest,
	ID_SECURITY_DKEP_INCFG_SECURITY_DKEP_INCFG_ConfigurationResponse
} TSECURITY_DKEP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group SECURITY_DKEP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TSECURITY_DKEP_INCFG_Type Type;
	int MessageType;
	union {
		c_SECURITY_DKEP_INCFG_ConfigurationRequest* fld_c_SECURITY_DKEP_INCFG_ConfigurationRequest;
		c_SECURITY_DKEP_INCFG_ConfigurationResponse* fld_c_SECURITY_DKEP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TSECURITY_DKEP_INCFG_Data;
#define INIT_TSECURITY_DKEP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TSECURITY_DKEP_INCFG_Data)), (sp)->Type=ID_SECURITY_DKEP_INCFG_Unrecognized)
void FREE_TSECURITY_DKEP_INCFG_Data (TSECURITY_DKEP_INCFG_Data* sp);

void SETPRESENT_TSECURITY_DKEP_INCFG_Data(TSECURITY_DKEP_INCFG_Data* sp, TSECURITY_DKEP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group SECURITY_DHKEP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_SECURITY_DHKEP_INCFG_Unrecognized = 0,
	ID_SECURITY_DHKEP_INCFG_SECURITY_DHKEP_INCFG_KeyRequest,
	ID_SECURITY_DHKEP_INCFG_SECURITY_DHKEP_INCFG_KeyResponse,
	ID_SECURITY_DHKEP_INCFG_SECURITY_DHKEP_INCFG_ANKeyComplete,
	ID_SECURITY_DHKEP_INCFG_SECURITY_DHKEP_INCFG_ATKeyComplete,
	ID_SECURITY_DHKEP_INCFG_SECURITY_DHKEP_INCFG_ConfigurationRequest,
	ID_SECURITY_DHKEP_INCFG_SECURITY_DHKEP_INCFG_ConfigurationResponse
} TSECURITY_DHKEP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group SECURITY_DHKEP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TSECURITY_DHKEP_INCFG_Type Type;
	int MessageType;
	union {
		c_SECURITY_DHKEP_INCFG_KeyRequest* fld_c_SECURITY_DHKEP_INCFG_KeyRequest;
		c_SECURITY_DHKEP_INCFG_KeyResponse* fld_c_SECURITY_DHKEP_INCFG_KeyResponse;
		c_SECURITY_DHKEP_INCFG_ANKeyComplete* fld_c_SECURITY_DHKEP_INCFG_ANKeyComplete;
		c_SECURITY_DHKEP_INCFG_ATKeyComplete* fld_c_SECURITY_DHKEP_INCFG_ATKeyComplete;
		c_SECURITY_DHKEP_INCFG_ConfigurationRequest* fld_c_SECURITY_DHKEP_INCFG_ConfigurationRequest;
		c_SECURITY_DHKEP_INCFG_ConfigurationResponse* fld_c_SECURITY_DHKEP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TSECURITY_DHKEP_INCFG_Data;
#define INIT_TSECURITY_DHKEP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TSECURITY_DHKEP_INCFG_Data)), (sp)->Type=ID_SECURITY_DHKEP_INCFG_Unrecognized)
void FREE_TSECURITY_DHKEP_INCFG_Data (TSECURITY_DHKEP_INCFG_Data* sp);

void SETPRESENT_TSECURITY_DHKEP_INCFG_Data(TSECURITY_DHKEP_INCFG_Data* sp, TSECURITY_DHKEP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group SECURITY_DAP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_SECURITY_DAP_INCFG_Unrecognized = 0,
	ID_SECURITY_DAP_INCFG_SECURITY_DAP_INCFG_ConfigurationRequest,
	ID_SECURITY_DAP_INCFG_SECURITY_DAP_INCFG_ConfigurationResponse
} TSECURITY_DAP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group SECURITY_DAP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TSECURITY_DAP_INCFG_Type Type;
	int MessageType;
	union {
		c_SECURITY_DAP_INCFG_ConfigurationRequest* fld_c_SECURITY_DAP_INCFG_ConfigurationRequest;
		c_SECURITY_DAP_INCFG_ConfigurationResponse* fld_c_SECURITY_DAP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TSECURITY_DAP_INCFG_Data;
#define INIT_TSECURITY_DAP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TSECURITY_DAP_INCFG_Data)), (sp)->Type=ID_SECURITY_DAP_INCFG_Unrecognized)
void FREE_TSECURITY_DAP_INCFG_Data (TSECURITY_DAP_INCFG_Data* sp);

void SETPRESENT_TSECURITY_DAP_INCFG_Data(TSECURITY_DAP_INCFG_Data* sp, TSECURITY_DAP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group SECURITY_SHA1AP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_SECURITY_SHA1AP_INCFG_Unrecognized = 0,
	ID_SECURITY_SHA1AP_INCFG_SECURITY_SHA1AP_INCFG_ConfigurationRequest,
	ID_SECURITY_SHA1AP_INCFG_SECURITY_SHA1AP_INCFG_ConfigurationResponse
} TSECURITY_SHA1AP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group SECURITY_SHA1AP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TSECURITY_SHA1AP_INCFG_Type Type;
	int MessageType;
	union {
		c_SECURITY_SHA1AP_INCFG_ConfigurationRequest* fld_c_SECURITY_SHA1AP_INCFG_ConfigurationRequest;
		c_SECURITY_SHA1AP_INCFG_ConfigurationResponse* fld_c_SECURITY_SHA1AP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TSECURITY_SHA1AP_INCFG_Data;
#define INIT_TSECURITY_SHA1AP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TSECURITY_SHA1AP_INCFG_Data)), (sp)->Type=ID_SECURITY_SHA1AP_INCFG_Unrecognized)
void FREE_TSECURITY_SHA1AP_INCFG_Data (TSECURITY_SHA1AP_INCFG_Data* sp);

void SETPRESENT_TSECURITY_SHA1AP_INCFG_Data(TSECURITY_SHA1AP_INCFG_Data* sp, TSECURITY_SHA1AP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group SECURITY_DEP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_SECURITY_DEP_INCFG_Unrecognized = 0,
	ID_SECURITY_DEP_INCFG_SECURITY_DEP_INCFG_ConfigurationRequest,
	ID_SECURITY_DEP_INCFG_SECURITY_DEP_INCFG_ConfigurationResponse
} TSECURITY_DEP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group SECURITY_DEP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TSECURITY_DEP_INCFG_Type Type;
	int MessageType;
	union {
		c_SECURITY_DEP_INCFG_ConfigurationRequest* fld_c_SECURITY_DEP_INCFG_ConfigurationRequest;
		c_SECURITY_DEP_INCFG_ConfigurationResponse* fld_c_SECURITY_DEP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TSECURITY_DEP_INCFG_Data;
#define INIT_TSECURITY_DEP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TSECURITY_DEP_INCFG_Data)), (sp)->Type=ID_SECURITY_DEP_INCFG_Unrecognized)
void FREE_TSECURITY_DEP_INCFG_Data (TSECURITY_DEP_INCFG_Data* sp);

void SETPRESENT_TSECURITY_DEP_INCFG_Data(TSECURITY_DEP_INCFG_Data* sp, TSECURITY_DEP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group MAC_DCCMACP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_MAC_DCCMACP_INCFG_Unrecognized = 0,
	ID_MAC_DCCMACP_INCFG_MAC_DCCMACP_INCFG_ConfigurationRequest,
	ID_MAC_DCCMACP_INCFG_MAC_DCCMACP_INCFG_ConfigurationResponse
} TMAC_DCCMACP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group MAC_DCCMACP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TMAC_DCCMACP_INCFG_Type Type;
	int MessageType;
	union {
		c_MAC_DCCMACP_INCFG_ConfigurationRequest* fld_c_MAC_DCCMACP_INCFG_ConfigurationRequest;
		c_MAC_DCCMACP_INCFG_ConfigurationResponse* fld_c_MAC_DCCMACP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TMAC_DCCMACP_INCFG_Data;
#define INIT_TMAC_DCCMACP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TMAC_DCCMACP_INCFG_Data)), (sp)->Type=ID_MAC_DCCMACP_INCFG_Unrecognized)
void FREE_TMAC_DCCMACP_INCFG_Data (TMAC_DCCMACP_INCFG_Data* sp);

void SETPRESENT_TMAC_DCCMACP_INCFG_Data(TMAC_DCCMACP_INCFG_Data* sp, TMAC_DCCMACP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group MAC_ECCMACP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_MAC_ECCMACP_INCFG_Unrecognized = 0,
	ID_MAC_ECCMACP_INCFG_MAC_ECCMACP_INCFG_ConfigurationRequest,
	ID_MAC_ECCMACP_INCFG_MAC_ECCMACP_INCFG_ConfigurationResponse
} TMAC_ECCMACP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group MAC_ECCMACP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TMAC_ECCMACP_INCFG_Type Type;
	int MessageType;
	union {
		c_MAC_ECCMACP_INCFG_ConfigurationRequest* fld_c_MAC_ECCMACP_INCFG_ConfigurationRequest;
		c_MAC_ECCMACP_INCFG_ConfigurationResponse* fld_c_MAC_ECCMACP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TMAC_ECCMACP_INCFG_Data;
#define INIT_TMAC_ECCMACP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TMAC_ECCMACP_INCFG_Data)), (sp)->Type=ID_MAC_ECCMACP_INCFG_Unrecognized)
void FREE_TMAC_ECCMACP_INCFG_Data (TMAC_ECCMACP_INCFG_Data* sp);

void SETPRESENT_TMAC_ECCMACP_INCFG_Data(TMAC_ECCMACP_INCFG_Data* sp, TMAC_ECCMACP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group MAC_DACMACP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_MAC_DACMACP_INCFG_Unrecognized = 0,
	ID_MAC_DACMACP_INCFG_MAC_DACMACP_INCFG_ConfigurationRequest,
	ID_MAC_DACMACP_INCFG_MAC_DACMACP_INCFG_ConfigurationResponse
} TMAC_DACMACP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group MAC_DACMACP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TMAC_DACMACP_INCFG_Type Type;
	int MessageType;
	union {
		c_MAC_DACMACP_INCFG_ConfigurationRequest* fld_c_MAC_DACMACP_INCFG_ConfigurationRequest;
		c_MAC_DACMACP_INCFG_ConfigurationResponse* fld_c_MAC_DACMACP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TMAC_DACMACP_INCFG_Data;
#define INIT_TMAC_DACMACP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TMAC_DACMACP_INCFG_Data)), (sp)->Type=ID_MAC_DACMACP_INCFG_Unrecognized)
void FREE_TMAC_DACMACP_INCFG_Data (TMAC_DACMACP_INCFG_Data* sp);

void SETPRESENT_TMAC_DACMACP_INCFG_Data(TMAC_DACMACP_INCFG_Data* sp, TMAC_DACMACP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group MAC_DACMACP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_MAC_DACMACP_INUSE_Unrecognized = 0,
	ID_MAC_DACMACP_INUSE_MAC_DACMACP_INUSE_ACAck,
	ID_MAC_DACMACP_INUSE_MAC_DACMACP_INUSE_AccessParameters
} TMAC_DACMACP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group MAC_DACMACP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TMAC_DACMACP_INUSE_Type Type;
	int MessageType;
	union {
		c_MAC_DACMACP_INUSE_ACAck* fld_c_MAC_DACMACP_INUSE_ACAck;
		c_MAC_DACMACP_INUSE_AccessParameters* fld_c_MAC_DACMACP_INUSE_AccessParameters;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TMAC_DACMACP_INUSE_Data;
#define INIT_TMAC_DACMACP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TMAC_DACMACP_INUSE_Data)), (sp)->Type=ID_MAC_DACMACP_INUSE_Unrecognized)
void FREE_TMAC_DACMACP_INUSE_Data (TMAC_DACMACP_INUSE_Data* sp);

void SETPRESENT_TMAC_DACMACP_INUSE_Data(TMAC_DACMACP_INUSE_Data* sp, TMAC_DACMACP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group MAC_EACMACP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_MAC_EACMACP_INCFG_Unrecognized = 0,
	ID_MAC_EACMACP_INCFG_MAC_EACMACP_INCFG_ConfigurationRequest,
	ID_MAC_EACMACP_INCFG_MAC_EACMACP_INCFG_ConfigurationResponse
} TMAC_EACMACP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group MAC_EACMACP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TMAC_EACMACP_INCFG_Type Type;
	int MessageType;
	union {
		c_MAC_EACMACP_INCFG_ConfigurationRequest* fld_c_MAC_EACMACP_INCFG_ConfigurationRequest;
		c_MAC_EACMACP_INCFG_ConfigurationResponse* fld_c_MAC_EACMACP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TMAC_EACMACP_INCFG_Data;
#define INIT_TMAC_EACMACP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TMAC_EACMACP_INCFG_Data)), (sp)->Type=ID_MAC_EACMACP_INCFG_Unrecognized)
void FREE_TMAC_EACMACP_INCFG_Data (TMAC_EACMACP_INCFG_Data* sp);

void SETPRESENT_TMAC_EACMACP_INCFG_Data(TMAC_EACMACP_INCFG_Data* sp, TMAC_EACMACP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group MAC_EACMACP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_MAC_EACMACP_INUSE_Unrecognized = 0,
	ID_MAC_EACMACP_INUSE_MAC_EACMACP_INUSE_ACAck,
	ID_MAC_EACMACP_INUSE_MAC_EACMACP_INUSE_AccessParameters,
	ID_MAC_EACMACP_INUSE_MAC_EACMACP_INUSE_AttributeUpdateRequest,
	ID_MAC_EACMACP_INUSE_MAC_EACMACP_INUSE_AttributeUpdateAccept,
	ID_MAC_EACMACP_INUSE_MAC_EACMACP_INUSE_AttributeUpdateReject
} TMAC_EACMACP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group MAC_EACMACP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TMAC_EACMACP_INUSE_Type Type;
	int MessageType;
	union {
		c_MAC_EACMACP_INUSE_ACAck* fld_c_MAC_EACMACP_INUSE_ACAck;
		c_MAC_EACMACP_INUSE_AccessParameters* fld_c_MAC_EACMACP_INUSE_AccessParameters;
		c_MAC_EACMACP_INUSE_AttributeUpdateRequest* fld_c_MAC_EACMACP_INUSE_AttributeUpdateRequest;
		c_MAC_EACMACP_INUSE_AttributeUpdateAccept* fld_c_MAC_EACMACP_INUSE_AttributeUpdateAccept;
		c_MAC_EACMACP_INUSE_AttributeUpdateReject* fld_c_MAC_EACMACP_INUSE_AttributeUpdateReject;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TMAC_EACMACP_INUSE_Data;
#define INIT_TMAC_EACMACP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TMAC_EACMACP_INUSE_Data)), (sp)->Type=ID_MAC_EACMACP_INUSE_Unrecognized)
void FREE_TMAC_EACMACP_INUSE_Data (TMAC_EACMACP_INUSE_Data* sp);

void SETPRESENT_TMAC_EACMACP_INUSE_Data(TMAC_EACMACP_INUSE_Data* sp, TMAC_EACMACP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group MAC_DFTCMACP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_MAC_DFTCMACP_INCFG_Unrecognized = 0,
	ID_MAC_DFTCMACP_INCFG_MAC_DFTCMACP_INCFG_ConfigurationRequest,
	ID_MAC_DFTCMACP_INCFG_MAC_DFTCMACP_INCFG_ConfigurationResponse
} TMAC_DFTCMACP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group MAC_DFTCMACP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TMAC_DFTCMACP_INCFG_Type Type;
	int MessageType;
	union {
		c_MAC_DFTCMACP_INCFG_ConfigurationRequest* fld_c_MAC_DFTCMACP_INCFG_ConfigurationRequest;
		c_MAC_DFTCMACP_INCFG_ConfigurationResponse* fld_c_MAC_DFTCMACP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TMAC_DFTCMACP_INCFG_Data;
#define INIT_TMAC_DFTCMACP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TMAC_DFTCMACP_INCFG_Data)), (sp)->Type=ID_MAC_DFTCMACP_INCFG_Unrecognized)
void FREE_TMAC_DFTCMACP_INCFG_Data (TMAC_DFTCMACP_INCFG_Data* sp);

void SETPRESENT_TMAC_DFTCMACP_INCFG_Data(TMAC_DFTCMACP_INCFG_Data* sp, TMAC_DFTCMACP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group MAC_DFTCMACP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_MAC_DFTCMACP_INUSE_Unrecognized = 0,
	ID_MAC_DFTCMACP_INUSE_MAC_DFTCMACP_INUSE_FixedModeEnable,
	ID_MAC_DFTCMACP_INUSE_MAC_DFTCMACP_INUSE_FixedModeXoff
} TMAC_DFTCMACP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group MAC_DFTCMACP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TMAC_DFTCMACP_INUSE_Type Type;
	int MessageType;
	union {
		c_MAC_DFTCMACP_INUSE_FixedModeEnable* fld_c_MAC_DFTCMACP_INUSE_FixedModeEnable;
		c_MAC_DFTCMACP_INUSE_FixedModeXoff* fld_c_MAC_DFTCMACP_INUSE_FixedModeXoff;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TMAC_DFTCMACP_INUSE_Data;
#define INIT_TMAC_DFTCMACP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TMAC_DFTCMACP_INUSE_Data)), (sp)->Type=ID_MAC_DFTCMACP_INUSE_Unrecognized)
void FREE_TMAC_DFTCMACP_INUSE_Data (TMAC_DFTCMACP_INUSE_Data* sp);

void SETPRESENT_TMAC_DFTCMACP_INUSE_Data(TMAC_DFTCMACP_INUSE_Data* sp, TMAC_DFTCMACP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group MAC_EFTCMACP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_MAC_EFTCMACP_INCFG_Unrecognized = 0,
	ID_MAC_EFTCMACP_INCFG_MAC_EFTCMACP_INCFG_ConfigurationRequest,
	ID_MAC_EFTCMACP_INCFG_MAC_EFTCMACP_INCFG_ConfigurationResponse
} TMAC_EFTCMACP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group MAC_EFTCMACP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TMAC_EFTCMACP_INCFG_Type Type;
	int MessageType;
	union {
		c_MAC_EFTCMACP_INCFG_ConfigurationRequest* fld_c_MAC_EFTCMACP_INCFG_ConfigurationRequest;
		c_MAC_EFTCMACP_INCFG_ConfigurationResponse* fld_c_MAC_EFTCMACP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TMAC_EFTCMACP_INCFG_Data;
#define INIT_TMAC_EFTCMACP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TMAC_EFTCMACP_INCFG_Data)), (sp)->Type=ID_MAC_EFTCMACP_INCFG_Unrecognized)
void FREE_TMAC_EFTCMACP_INCFG_Data (TMAC_EFTCMACP_INCFG_Data* sp);

void SETPRESENT_TMAC_EFTCMACP_INCFG_Data(TMAC_EFTCMACP_INCFG_Data* sp, TMAC_EFTCMACP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group MAC_EFTCMACP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_MAC_EFTCMACP_INUSE_Unrecognized = 0,
	ID_MAC_EFTCMACP_INUSE_MAC_EFTCMACP_INUSE_FixedModeEnable,
	ID_MAC_EFTCMACP_INUSE_MAC_EFTCMACP_INUSE_FixedModeXoff,
	ID_MAC_EFTCMACP_INUSE_MAC_EFTCMACP_INUSE_AttributeUpdateRequest,
	ID_MAC_EFTCMACP_INUSE_MAC_EFTCMACP_INUSE_AttributeUpdateAccept,
	ID_MAC_EFTCMACP_INUSE_MAC_EFTCMACP_INUSE_AttributeUpdateReject
} TMAC_EFTCMACP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group MAC_EFTCMACP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TMAC_EFTCMACP_INUSE_Type Type;
	int MessageType;
	union {
		c_MAC_EFTCMACP_INUSE_FixedModeEnable* fld_c_MAC_EFTCMACP_INUSE_FixedModeEnable;
		c_MAC_EFTCMACP_INUSE_FixedModeXoff* fld_c_MAC_EFTCMACP_INUSE_FixedModeXoff;
		c_MAC_EFTCMACP_INUSE_AttributeUpdateRequest* fld_c_MAC_EFTCMACP_INUSE_AttributeUpdateRequest;
		c_MAC_EFTCMACP_INUSE_AttributeUpdateAccept* fld_c_MAC_EFTCMACP_INUSE_AttributeUpdateAccept;
		c_MAC_EFTCMACP_INUSE_AttributeUpdateReject* fld_c_MAC_EFTCMACP_INUSE_AttributeUpdateReject;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TMAC_EFTCMACP_INUSE_Data;
#define INIT_TMAC_EFTCMACP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TMAC_EFTCMACP_INUSE_Data)), (sp)->Type=ID_MAC_EFTCMACP_INUSE_Unrecognized)
void FREE_TMAC_EFTCMACP_INUSE_Data (TMAC_EFTCMACP_INUSE_Data* sp);

void SETPRESENT_TMAC_EFTCMACP_INUSE_Data(TMAC_EFTCMACP_INUSE_Data* sp, TMAC_EFTCMACP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group MAC_MFTCMACP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_MAC_MFTCMACP_INCFG_Unrecognized = 0,
	ID_MAC_MFTCMACP_INCFG_MAC_MFTCMACP_INCFG_ConfigurationRequest,
	ID_MAC_MFTCMACP_INCFG_MAC_MFTCMACP_INCFG_ConfigurationResponse
} TMAC_MFTCMACP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group MAC_MFTCMACP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TMAC_MFTCMACP_INCFG_Type Type;
	int MessageType;
	union {
		c_MAC_MFTCMACP_INCFG_ConfigurationRequest* fld_c_MAC_MFTCMACP_INCFG_ConfigurationRequest;
		c_MAC_MFTCMACP_INCFG_ConfigurationResponse* fld_c_MAC_MFTCMACP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TMAC_MFTCMACP_INCFG_Data;
#define INIT_TMAC_MFTCMACP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TMAC_MFTCMACP_INCFG_Data)), (sp)->Type=ID_MAC_MFTCMACP_INCFG_Unrecognized)
void FREE_TMAC_MFTCMACP_INCFG_Data (TMAC_MFTCMACP_INCFG_Data* sp);

void SETPRESENT_TMAC_MFTCMACP_INCFG_Data(TMAC_MFTCMACP_INCFG_Data* sp, TMAC_MFTCMACP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group MAC_MFTCMACP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_MAC_MFTCMACP_INUSE_Unrecognized = 0,
	ID_MAC_MFTCMACP_INUSE_MAC_MFTCMACP_INUSE_FixedModeEnable,
	ID_MAC_MFTCMACP_INUSE_MAC_MFTCMACP_INUSE_FixedModeXoff,
	ID_MAC_MFTCMACP_INUSE_MAC_MFTCMACP_INUSE_AttributeUpdateRequest,
	ID_MAC_MFTCMACP_INUSE_MAC_MFTCMACP_INUSE_AttributeUpdateAccept,
	ID_MAC_MFTCMACP_INUSE_MAC_MFTCMACP_INUSE_AttributeUpdateReject
} TMAC_MFTCMACP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group MAC_MFTCMACP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TMAC_MFTCMACP_INUSE_Type Type;
	int MessageType;
	union {
		c_MAC_MFTCMACP_INUSE_FixedModeEnable* fld_c_MAC_MFTCMACP_INUSE_FixedModeEnable;
		c_MAC_MFTCMACP_INUSE_FixedModeXoff* fld_c_MAC_MFTCMACP_INUSE_FixedModeXoff;
		c_MAC_MFTCMACP_INUSE_AttributeUpdateRequest* fld_c_MAC_MFTCMACP_INUSE_AttributeUpdateRequest;
		c_MAC_MFTCMACP_INUSE_AttributeUpdateAccept* fld_c_MAC_MFTCMACP_INUSE_AttributeUpdateAccept;
		c_MAC_MFTCMACP_INUSE_AttributeUpdateReject* fld_c_MAC_MFTCMACP_INUSE_AttributeUpdateReject;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TMAC_MFTCMACP_INUSE_Data;
#define INIT_TMAC_MFTCMACP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TMAC_MFTCMACP_INUSE_Data)), (sp)->Type=ID_MAC_MFTCMACP_INUSE_Unrecognized)
void FREE_TMAC_MFTCMACP_INUSE_Data (TMAC_MFTCMACP_INUSE_Data* sp);

void SETPRESENT_TMAC_MFTCMACP_INUSE_Data(TMAC_MFTCMACP_INUSE_Data* sp, TMAC_MFTCMACP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group MAC_DRTCMACP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_MAC_DRTCMACP_INCFG_Unrecognized = 0,
	ID_MAC_DRTCMACP_INCFG_MAC_DRTCMACP_INCFG_ConfigurationRequest,
	ID_MAC_DRTCMACP_INCFG_MAC_DRTCMACP_INCFG_ConfigurationResponse
} TMAC_DRTCMACP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group MAC_DRTCMACP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TMAC_DRTCMACP_INCFG_Type Type;
	int MessageType;
	union {
		c_MAC_DRTCMACP_INCFG_ConfigurationRequest* fld_c_MAC_DRTCMACP_INCFG_ConfigurationRequest;
		c_MAC_DRTCMACP_INCFG_ConfigurationResponse* fld_c_MAC_DRTCMACP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TMAC_DRTCMACP_INCFG_Data;
#define INIT_TMAC_DRTCMACP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TMAC_DRTCMACP_INCFG_Data)), (sp)->Type=ID_MAC_DRTCMACP_INCFG_Unrecognized)
void FREE_TMAC_DRTCMACP_INCFG_Data (TMAC_DRTCMACP_INCFG_Data* sp);

void SETPRESENT_TMAC_DRTCMACP_INCFG_Data(TMAC_DRTCMACP_INCFG_Data* sp, TMAC_DRTCMACP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group MAC_DRTCMACP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_MAC_DRTCMACP_INUSE_Unrecognized = 0,
	ID_MAC_DRTCMACP_INUSE_MAC_DRTCMACP_INUSE_RTCAck,
	ID_MAC_DRTCMACP_INUSE_MAC_DRTCMACP_INUSE_BroadcastReverseRateLimit,
	ID_MAC_DRTCMACP_INUSE_MAC_DRTCMACP_INUSE_UnicastReverseRateLimit
} TMAC_DRTCMACP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group MAC_DRTCMACP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TMAC_DRTCMACP_INUSE_Type Type;
	int MessageType;
	union {
		c_MAC_DRTCMACP_INUSE_RTCAck* fld_c_MAC_DRTCMACP_INUSE_RTCAck;
		c_MAC_DRTCMACP_INUSE_BroadcastReverseRateLimit* fld_c_MAC_DRTCMACP_INUSE_BroadcastReverseRateLimit;
		c_MAC_DRTCMACP_INUSE_UnicastReverseRateLimit* fld_c_MAC_DRTCMACP_INUSE_UnicastReverseRateLimit;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TMAC_DRTCMACP_INUSE_Data;
#define INIT_TMAC_DRTCMACP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TMAC_DRTCMACP_INUSE_Data)), (sp)->Type=ID_MAC_DRTCMACP_INUSE_Unrecognized)
void FREE_TMAC_DRTCMACP_INUSE_Data (TMAC_DRTCMACP_INUSE_Data* sp);

void SETPRESENT_TMAC_DRTCMACP_INUSE_Data(TMAC_DRTCMACP_INUSE_Data* sp, TMAC_DRTCMACP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group MAC_S1RTCMACP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_MAC_S1RTCMACP_INCFG_Unrecognized = 0,
	ID_MAC_S1RTCMACP_INCFG_MAC_S1RTCMACP_INCFG_ConfigurationRequest,
	ID_MAC_S1RTCMACP_INCFG_MAC_S1RTCMACP_INCFG_ConfigurationResponse
} TMAC_S1RTCMACP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group MAC_S1RTCMACP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TMAC_S1RTCMACP_INCFG_Type Type;
	int MessageType;
	union {
		c_MAC_S1RTCMACP_INCFG_ConfigurationRequest* fld_c_MAC_S1RTCMACP_INCFG_ConfigurationRequest;
		c_MAC_S1RTCMACP_INCFG_ConfigurationResponse* fld_c_MAC_S1RTCMACP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TMAC_S1RTCMACP_INCFG_Data;
#define INIT_TMAC_S1RTCMACP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TMAC_S1RTCMACP_INCFG_Data)), (sp)->Type=ID_MAC_S1RTCMACP_INCFG_Unrecognized)
void FREE_TMAC_S1RTCMACP_INCFG_Data (TMAC_S1RTCMACP_INCFG_Data* sp);

void SETPRESENT_TMAC_S1RTCMACP_INCFG_Data(TMAC_S1RTCMACP_INCFG_Data* sp, TMAC_S1RTCMACP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group MAC_S1RTCMACP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_MAC_S1RTCMACP_INUSE_Unrecognized = 0,
	ID_MAC_S1RTCMACP_INUSE_MAC_S1RTCMACP_INUSE_RTCAck,
	ID_MAC_S1RTCMACP_INUSE_MAC_S1RTCMACP_INUSE_BroadcastReverseRateLimit,
	ID_MAC_S1RTCMACP_INUSE_MAC_S1RTCMACP_INUSE_UnicastReverseRateLimit,
	ID_MAC_S1RTCMACP_INUSE_MAC_S1RTCMACP_INUSE_AttributeUpdateRequest,
	ID_MAC_S1RTCMACP_INUSE_MAC_S1RTCMACP_INUSE_AttributeUpdateAccept,
	ID_MAC_S1RTCMACP_INUSE_MAC_S1RTCMACP_INUSE_AttributeUpdateReject
} TMAC_S1RTCMACP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group MAC_S1RTCMACP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TMAC_S1RTCMACP_INUSE_Type Type;
	int MessageType;
	union {
		c_MAC_S1RTCMACP_INUSE_RTCAck* fld_c_MAC_S1RTCMACP_INUSE_RTCAck;
		c_MAC_S1RTCMACP_INUSE_BroadcastReverseRateLimit* fld_c_MAC_S1RTCMACP_INUSE_BroadcastReverseRateLimit;
		c_MAC_S1RTCMACP_INUSE_UnicastReverseRateLimit* fld_c_MAC_S1RTCMACP_INUSE_UnicastReverseRateLimit;
		c_MAC_S1RTCMACP_INUSE_AttributeUpdateRequest* fld_c_MAC_S1RTCMACP_INUSE_AttributeUpdateRequest;
		c_MAC_S1RTCMACP_INUSE_AttributeUpdateAccept* fld_c_MAC_S1RTCMACP_INUSE_AttributeUpdateAccept;
		c_MAC_S1RTCMACP_INUSE_AttributeUpdateReject* fld_c_MAC_S1RTCMACP_INUSE_AttributeUpdateReject;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TMAC_S1RTCMACP_INUSE_Data;
#define INIT_TMAC_S1RTCMACP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TMAC_S1RTCMACP_INUSE_Data)), (sp)->Type=ID_MAC_S1RTCMACP_INUSE_Unrecognized)
void FREE_TMAC_S1RTCMACP_INUSE_Data (TMAC_S1RTCMACP_INUSE_Data* sp);

void SETPRESENT_TMAC_S1RTCMACP_INUSE_Data(TMAC_S1RTCMACP_INUSE_Data* sp, TMAC_S1RTCMACP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group MAC_S3RTCMACP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_MAC_S3RTCMACP_INCFG_Unrecognized = 0,
	ID_MAC_S3RTCMACP_INCFG_MAC_S3RTCMACP_INCFG_ConfigurationRequest,
	ID_MAC_S3RTCMACP_INCFG_MAC_S3RTCMACP_INCFG_ConfigurationResponse
} TMAC_S3RTCMACP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group MAC_S3RTCMACP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TMAC_S3RTCMACP_INCFG_Type Type;
	int MessageType;
	union {
		c_MAC_S3RTCMACP_INCFG_ConfigurationRequest* fld_c_MAC_S3RTCMACP_INCFG_ConfigurationRequest;
		c_MAC_S3RTCMACP_INCFG_ConfigurationResponse* fld_c_MAC_S3RTCMACP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TMAC_S3RTCMACP_INCFG_Data;
#define INIT_TMAC_S3RTCMACP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TMAC_S3RTCMACP_INCFG_Data)), (sp)->Type=ID_MAC_S3RTCMACP_INCFG_Unrecognized)
void FREE_TMAC_S3RTCMACP_INCFG_Data (TMAC_S3RTCMACP_INCFG_Data* sp);

void SETPRESENT_TMAC_S3RTCMACP_INCFG_Data(TMAC_S3RTCMACP_INCFG_Data* sp, TMAC_S3RTCMACP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group MAC_S3RTCMACP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_MAC_S3RTCMACP_INUSE_Unrecognized = 0,
	ID_MAC_S3RTCMACP_INUSE_MAC_S3RTCMACP_INUSE_RTCAck,
	ID_MAC_S3RTCMACP_INUSE_MAC_S3RTCMACP_INUSE_Request,
	ID_MAC_S3RTCMACP_INUSE_MAC_S3RTCMACP_INUSE_Grant,
	ID_MAC_S3RTCMACP_INUSE_MAC_S3RTCMACP_INUSE_AttributeUpdateRequest,
	ID_MAC_S3RTCMACP_INUSE_MAC_S3RTCMACP_INUSE_AttributeUpdateAccept,
	ID_MAC_S3RTCMACP_INUSE_MAC_S3RTCMACP_INUSE_AttributeUpdateReject
} TMAC_S3RTCMACP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group MAC_S3RTCMACP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TMAC_S3RTCMACP_INUSE_Type Type;
	int MessageType;
	union {
		c_MAC_S3RTCMACP_INUSE_RTCAck* fld_c_MAC_S3RTCMACP_INUSE_RTCAck;
		c_MAC_S3RTCMACP_INUSE_Request* fld_c_MAC_S3RTCMACP_INUSE_Request;
		c_MAC_S3RTCMACP_INUSE_Grant* fld_c_MAC_S3RTCMACP_INUSE_Grant;
		c_MAC_S3RTCMACP_INUSE_AttributeUpdateRequest* fld_c_MAC_S3RTCMACP_INUSE_AttributeUpdateRequest;
		c_MAC_S3RTCMACP_INUSE_AttributeUpdateAccept* fld_c_MAC_S3RTCMACP_INUSE_AttributeUpdateAccept;
		c_MAC_S3RTCMACP_INUSE_AttributeUpdateReject* fld_c_MAC_S3RTCMACP_INUSE_AttributeUpdateReject;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TMAC_S3RTCMACP_INUSE_Data;
#define INIT_TMAC_S3RTCMACP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TMAC_S3RTCMACP_INUSE_Data)), (sp)->Type=ID_MAC_S3RTCMACP_INUSE_Unrecognized)
void FREE_TMAC_S3RTCMACP_INUSE_Data (TMAC_S3RTCMACP_INUSE_Data* sp);

void SETPRESENT_TMAC_S3RTCMACP_INUSE_Data(TMAC_S3RTCMACP_INUSE_Data* sp, TMAC_S3RTCMACP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group MAC_MRTCMACP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_MAC_MRTCMACP_INCFG_Unrecognized = 0,
	ID_MAC_MRTCMACP_INCFG_MAC_MRTCMACP_INCFG_ConfigurationRequest,
	ID_MAC_MRTCMACP_INCFG_MAC_MRTCMACP_INCFG_ConfigurationResponse
} TMAC_MRTCMACP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group MAC_MRTCMACP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TMAC_MRTCMACP_INCFG_Type Type;
	int MessageType;
	union {
		c_MAC_MRTCMACP_INCFG_ConfigurationRequest* fld_c_MAC_MRTCMACP_INCFG_ConfigurationRequest;
		c_MAC_MRTCMACP_INCFG_ConfigurationResponse* fld_c_MAC_MRTCMACP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TMAC_MRTCMACP_INCFG_Data;
#define INIT_TMAC_MRTCMACP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TMAC_MRTCMACP_INCFG_Data)), (sp)->Type=ID_MAC_MRTCMACP_INCFG_Unrecognized)
void FREE_TMAC_MRTCMACP_INCFG_Data (TMAC_MRTCMACP_INCFG_Data* sp);

void SETPRESENT_TMAC_MRTCMACP_INCFG_Data(TMAC_MRTCMACP_INCFG_Data* sp, TMAC_MRTCMACP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group MAC_MRTCMACP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_MAC_MRTCMACP_INUSE_Unrecognized = 0,
	ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_RTCAck,
	ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_CarrierRequest,
	ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped,
	ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck,
	ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_Request,
	ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_Grant,
	ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_AttributeUpdateRequest,
	ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_AttributeUpdateAccept,
	ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_AttributeUpdateReject
} TMAC_MRTCMACP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group MAC_MRTCMACP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TMAC_MRTCMACP_INUSE_Type Type;
	int MessageType;
	union {
		c_MAC_MRTCMACP_INUSE_RTCAck* fld_c_MAC_MRTCMACP_INUSE_RTCAck;
		c_MAC_MRTCMACP_INUSE_CarrierRequest* fld_c_MAC_MRTCMACP_INUSE_CarrierRequest;
		c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped* fld_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped;
		c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck* fld_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck;
		c_MAC_MRTCMACP_INUSE_Request* fld_c_MAC_MRTCMACP_INUSE_Request;
		c_MAC_MRTCMACP_INUSE_Grant* fld_c_MAC_MRTCMACP_INUSE_Grant;
		c_MAC_MRTCMACP_INUSE_AttributeUpdateRequest* fld_c_MAC_MRTCMACP_INUSE_AttributeUpdateRequest;
		c_MAC_MRTCMACP_INUSE_AttributeUpdateAccept* fld_c_MAC_MRTCMACP_INUSE_AttributeUpdateAccept;
		c_MAC_MRTCMACP_INUSE_AttributeUpdateReject* fld_c_MAC_MRTCMACP_INUSE_AttributeUpdateReject;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TMAC_MRTCMACP_INUSE_Data;
#define INIT_TMAC_MRTCMACP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TMAC_MRTCMACP_INUSE_Data)), (sp)->Type=ID_MAC_MRTCMACP_INUSE_Unrecognized)
void FREE_TMAC_MRTCMACP_INUSE_Data (TMAC_MRTCMACP_INUSE_Data* sp);

void SETPRESENT_TMAC_MRTCMACP_INUSE_Data(TMAC_MRTCMACP_INUSE_Data* sp, TMAC_MRTCMACP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group PHYS01_DS0S1PLPI_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_PHYS01_DS0S1PLPI_INCFG_Unrecognized = 0,
	ID_PHYS01_DS0S1PLPI_INCFG_PHYS01_DS0S1PLPI_INCFG_ConfigurationRequest,
	ID_PHYS01_DS0S1PLPI_INCFG_PHYS01_DS0S1PLPI_INCFG_ConfigurationResponse
} TPHYS01_DS0S1PLPI_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group PHYS01_DS0S1PLPI_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TPHYS01_DS0S1PLPI_INCFG_Type Type;
	int MessageType;
	union {
		c_PHYS01_DS0S1PLPI_INCFG_ConfigurationRequest* fld_c_PHYS01_DS0S1PLPI_INCFG_ConfigurationRequest;
		c_PHYS01_DS0S1PLPI_INCFG_ConfigurationResponse* fld_c_PHYS01_DS0S1PLPI_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TPHYS01_DS0S1PLPI_INCFG_Data;
#define INIT_TPHYS01_DS0S1PLPI_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TPHYS01_DS0S1PLPI_INCFG_Data)), (sp)->Type=ID_PHYS01_DS0S1PLPI_INCFG_Unrecognized)
void FREE_TPHYS01_DS0S1PLPI_INCFG_Data (TPHYS01_DS0S1PLPI_INCFG_Data* sp);

void SETPRESENT_TPHYS01_DS0S1PLPI_INCFG_Data(TPHYS01_DS0S1PLPI_INCFG_Data* sp, TPHYS01_DS0S1PLPI_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group PHYS2_S2PLPI_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_PHYS2_S2PLPI_INCFG_Unrecognized = 0,
	ID_PHYS2_S2PLPI_INCFG_PHYS2_S2PLPI_INCFG_ConfigurationRequest,
	ID_PHYS2_S2PLPI_INCFG_PHYS2_S2PLPI_INCFG_ConfigurationResponse
} TPHYS2_S2PLPI_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group PHYS2_S2PLPI_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TPHYS2_S2PLPI_INCFG_Type Type;
	int MessageType;
	union {
		c_PHYS2_S2PLPI_INCFG_ConfigurationRequest* fld_c_PHYS2_S2PLPI_INCFG_ConfigurationRequest;
		c_PHYS2_S2PLPI_INCFG_ConfigurationResponse* fld_c_PHYS2_S2PLPI_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TPHYS2_S2PLPI_INCFG_Data;
#define INIT_TPHYS2_S2PLPI_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TPHYS2_S2PLPI_INCFG_Data)), (sp)->Type=ID_PHYS2_S2PLPI_INCFG_Unrecognized)
void FREE_TPHYS2_S2PLPI_INCFG_Data (TPHYS2_S2PLPI_INCFG_Data* sp);

void SETPRESENT_TPHYS2_S2PLPI_INCFG_Data(TPHYS2_S2PLPI_INCFG_Data* sp, TPHYS2_S2PLPI_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group PHYS3_S3PLPI_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_PHYS3_S3PLPI_INCFG_Unrecognized = 0,
	ID_PHYS3_S3PLPI_INCFG_PHYS3_S3PLPI_INCFG_ConfigurationRequest,
	ID_PHYS3_S3PLPI_INCFG_PHYS3_S3PLPI_INCFG_ConfigurationResponse
} TPHYS3_S3PLPI_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group PHYS3_S3PLPI_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TPHYS3_S3PLPI_INCFG_Type Type;
	int MessageType;
	union {
		c_PHYS3_S3PLPI_INCFG_ConfigurationRequest* fld_c_PHYS3_S3PLPI_INCFG_ConfigurationRequest;
		c_PHYS3_S3PLPI_INCFG_ConfigurationResponse* fld_c_PHYS3_S3PLPI_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TPHYS3_S3PLPI_INCFG_Data;
#define INIT_TPHYS3_S3PLPI_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TPHYS3_S3PLPI_INCFG_Data)), (sp)->Type=ID_PHYS3_S3PLPI_INCFG_Unrecognized)
void FREE_TPHYS3_S3PLPI_INCFG_Data (TPHYS3_S3PLPI_INCFG_Data* sp);

void SETPRESENT_TPHYS3_S3PLPI_INCFG_Data(TPHYS3_S3PLPI_INCFG_Data* sp, TPHYS3_S3PLPI_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group PHYS3_S3PLPI_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_PHYS3_S3PLPI_INUSE_Unrecognized = 0,
	ID_PHYS3_S3PLPI_INUSE_PHYS3_S3PLPI_INUSE_AttributeUpdateRequest,
	ID_PHYS3_S3PLPI_INUSE_PHYS3_S3PLPI_INUSE_AttributeUpdateAccept,
	ID_PHYS3_S3PLPI_INUSE_PHYS3_S3PLPI_INUSE_AttributeUpdateReject
} TPHYS3_S3PLPI_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group PHYS3_S3PLPI_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TPHYS3_S3PLPI_INUSE_Type Type;
	int MessageType;
	union {
		c_PHYS3_S3PLPI_INUSE_AttributeUpdateRequest* fld_c_PHYS3_S3PLPI_INUSE_AttributeUpdateRequest;
		c_PHYS3_S3PLPI_INUSE_AttributeUpdateAccept* fld_c_PHYS3_S3PLPI_INUSE_AttributeUpdateAccept;
		c_PHYS3_S3PLPI_INUSE_AttributeUpdateReject* fld_c_PHYS3_S3PLPI_INUSE_AttributeUpdateReject;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TPHYS3_S3PLPI_INUSE_Data;
#define INIT_TPHYS3_S3PLPI_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TPHYS3_S3PLPI_INUSE_Data)), (sp)->Type=ID_PHYS3_S3PLPI_INUSE_Unrecognized)
void FREE_TPHYS3_S3PLPI_INUSE_Data (TPHYS3_S3PLPI_INUSE_Data* sp);

void SETPRESENT_TPHYS3_S3PLPI_INUSE_Data(TPHYS3_S3PLPI_INUSE_Data* sp, TPHYS3_S3PLPI_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group GEN_GCP
--------------------------------------------------------------------*/
typedef enum {
	ID_GEN_GCP_Unrecognized = 0,
	ID_GEN_GCP_GEN_GCP_ConfigurationRequest,
	ID_GEN_GCP_GEN_GCP_ConfigurationResponse
} TGEN_GCP_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group GEN_GCP
--------------------------------------------------------------------*/
typedef struct {
	TGEN_GCP_Type Type;
	int MessageType;
	union {
		c_GEN_GCP_ConfigurationRequest* fld_c_GEN_GCP_ConfigurationRequest;
		c_GEN_GCP_ConfigurationResponse* fld_c_GEN_GCP_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TGEN_GCP_Data;
#define INIT_TGEN_GCP_Data(sp) (ED_RESET_MEM ((sp), sizeof (TGEN_GCP_Data)), (sp)->Type=ID_GEN_GCP_Unrecognized)
void FREE_TGEN_GCP_Data (TGEN_GCP_Data* sp);

void SETPRESENT_TGEN_GCP_Data(TGEN_GCP_Data* sp, TGEN_GCP_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group GEN_GAUP
--------------------------------------------------------------------*/
typedef enum {
	ID_GEN_GAUP_Unrecognized = 0,
	ID_GEN_GAUP_GEN_GAUP_AttributeUpdateRequest,
	ID_GEN_GAUP_GEN_GAUP_AttributeUpdateAccept,
	ID_GEN_GAUP_GEN_GAUP_AttributeUpdateReject
} TGEN_GAUP_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group GEN_GAUP
--------------------------------------------------------------------*/
typedef struct {
	TGEN_GAUP_Type Type;
	int MessageType;
	union {
		c_GEN_GAUP_AttributeUpdateRequest* fld_c_GEN_GAUP_AttributeUpdateRequest;
		c_GEN_GAUP_AttributeUpdateAccept* fld_c_GEN_GAUP_AttributeUpdateAccept;
		c_GEN_GAUP_AttributeUpdateReject* fld_c_GEN_GAUP_AttributeUpdateReject;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TGEN_GAUP_Data;
#define INIT_TGEN_GAUP_Data(sp) (ED_RESET_MEM ((sp), sizeof (TGEN_GAUP_Data)), (sp)->Type=ID_GEN_GAUP_Unrecognized)
void FREE_TGEN_GAUP_Data (TGEN_GAUP_Data* sp);

void SETPRESENT_TGEN_GAUP_Data(TGEN_GAUP_Data* sp, TGEN_GAUP_Type toBeSetPresent);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_CONN_DINSP_INUSE (const char* buffer, TCONN_DINSP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_DINSP_INUSE (const char* buffer, int len, TCONN_DINSP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_CONN_DINSP_INUSE (char* buffer, ED_EXLONG bitOffset, TCONN_DINSP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_SIGAPP_SLP_INCFG (const char* buffer, TSIGAPP_SLP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_SIGAPP_SLP_INCFG (const char* buffer, int len, TSIGAPP_SLP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_SIGAPP_SLP_INCFG (char* buffer, ED_EXLONG bitOffset, TSIGAPP_SLP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_SIGAPP_SLP (const char* buffer, TSIGAPP_SLP_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_SIGAPP_SLP (const char* buffer, int len, TSIGAPP_SLP_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_SIGAPP_SLP (char* buffer, ED_EXLONG bitOffset, TSIGAPP_SLP_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_PKTAPP_DPA_INCFG (const char* buffer, TPKTAPP_DPA_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_PKTAPP_DPA_INCFG (const char* buffer, int len, TPKTAPP_DPA_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_PKTAPP_DPA_INCFG (char* buffer, ED_EXLONG bitOffset, TPKTAPP_DPA_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_PKTAPP_RLP_INUSE (const char* buffer, TPKTAPP_RLP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_PKTAPP_RLP_INUSE (const char* buffer, int len, TPKTAPP_RLP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_PKTAPP_RLP_INUSE (char* buffer, ED_EXLONG bitOffset, TPKTAPP_RLP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_PKTAPP_LUP_INUSE (const char* buffer, TPKTAPP_LUP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_PKTAPP_LUP_INUSE (const char* buffer, int len, TPKTAPP_LUP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_PKTAPP_LUP_INUSE (char* buffer, ED_EXLONG bitOffset, TPKTAPP_LUP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_PKTAPP_FCP_INUSE (const char* buffer, TPKTAPP_FCP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_PKTAPP_FCP_INUSE (const char* buffer, int len, TPKTAPP_FCP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_PKTAPP_FCP_INUSE (char* buffer, ED_EXLONG bitOffset, TPKTAPP_FCP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_MFPAPP_MFPA_INCFG (const char* buffer, TMFPAPP_MFPA_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MFPAPP_MFPA_INCFG (const char* buffer, int len, TMFPAPP_MFPA_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_MFPAPP_MFPA_INCFG (char* buffer, ED_EXLONG bitOffset, TMFPAPP_MFPA_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_MFPAPP_RLP_INUSE (const char* buffer, TMFPAPP_RLP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MFPAPP_RLP_INUSE (const char* buffer, int len, TMFPAPP_RLP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_MFPAPP_RLP_INUSE (char* buffer, ED_EXLONG bitOffset, TMFPAPP_RLP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_MFPAPP_DOSP_INUSE (const char* buffer, TMFPAPP_DOSP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MFPAPP_DOSP_INUSE (const char* buffer, int len, TMFPAPP_DOSP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_MFPAPP_DOSP_INUSE (char* buffer, ED_EXLONG bitOffset, TMFPAPP_DOSP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_MFPAPP_LUP_INUSE (const char* buffer, TMFPAPP_LUP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MFPAPP_LUP_INUSE (const char* buffer, int len, TMFPAPP_LUP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_MFPAPP_LUP_INUSE (char* buffer, ED_EXLONG bitOffset, TMFPAPP_LUP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_MFPAPP_FCP_INUSE (const char* buffer, TMFPAPP_FCP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MFPAPP_FCP_INUSE (const char* buffer, int len, TMFPAPP_FCP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_MFPAPP_FCP_INUSE (char* buffer, ED_EXLONG bitOffset, TMFPAPP_FCP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_STREAM_DSP_INCFG (const char* buffer, TSTREAM_DSP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_STREAM_DSP_INCFG (const char* buffer, int len, TSTREAM_DSP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_STREAM_DSP_INCFG (char* buffer, ED_EXLONG bitOffset, TSTREAM_DSP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_STREAM_GVSP_INCFG (const char* buffer, TSTREAM_GVSP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_STREAM_GVSP_INCFG (const char* buffer, int len, TSTREAM_GVSP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_STREAM_GVSP_INCFG (char* buffer, ED_EXLONG bitOffset, TSTREAM_GVSP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_SESSION_DSMP_INCFG (const char* buffer, TSESSION_DSMP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_SESSION_DSMP_INCFG (const char* buffer, int len, TSESSION_DSMP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_SESSION_DSMP_INCFG (char* buffer, ED_EXLONG bitOffset, TSESSION_DSMP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_SESSION_DSMP_INUSE (const char* buffer, TSESSION_DSMP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_SESSION_DSMP_INUSE (const char* buffer, int len, TSESSION_DSMP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_SESSION_DSMP_INUSE (char* buffer, ED_EXLONG bitOffset, TSESSION_DSMP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_SESSION_DAMP_INCFG (const char* buffer, TSESSION_DAMP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_SESSION_DAMP_INCFG (const char* buffer, int len, TSESSION_DAMP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_SESSION_DAMP_INCFG (char* buffer, ED_EXLONG bitOffset, TSESSION_DAMP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_SESSION_DAMP_INUSE (const char* buffer, TSESSION_DAMP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_SESSION_DAMP_INUSE (const char* buffer, int len, TSESSION_DAMP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_SESSION_DAMP_INUSE (char* buffer, ED_EXLONG bitOffset, TSESSION_DAMP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_SESSION_DSCP_INUSE (const char* buffer, TSESSION_DSCP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_SESSION_DSCP_INUSE (const char* buffer, int len, TSESSION_DSCP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_SESSION_DSCP_INUSE (char* buffer, ED_EXLONG bitOffset, TSESSION_DSCP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_SESSION_GMCDP_INCFG (const char* buffer, TSESSION_GMCDP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_SESSION_GMCDP_INCFG (const char* buffer, int len, TSESSION_GMCDP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_SESSION_GMCDP_INCFG (char* buffer, ED_EXLONG bitOffset, TSESSION_GMCDP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_CONN_DALMP_INCFG (const char* buffer, TCONN_DALMP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_DALMP_INCFG (const char* buffer, int len, TCONN_DALMP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_CONN_DALMP_INCFG (char* buffer, ED_EXLONG bitOffset, TCONN_DALMP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_CONN_DALMP_INUSE (const char* buffer, TCONN_DALMP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_DALMP_INUSE (const char* buffer, int len, TCONN_DALMP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_CONN_DALMP_INUSE (char* buffer, ED_EXLONG bitOffset, TCONN_DALMP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_CONN_DINSP_INCFG (const char* buffer, TCONN_DINSP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_DINSP_INCFG (const char* buffer, int len, TCONN_DINSP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_CONN_DINSP_INCFG (char* buffer, ED_EXLONG bitOffset, TCONN_DINSP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_CONN_DIDSP_INCFG (const char* buffer, TCONN_DIDSP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_DIDSP_INCFG (const char* buffer, int len, TCONN_DIDSP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_CONN_DIDSP_INCFG (char* buffer, ED_EXLONG bitOffset, TCONN_DIDSP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_CONN_DIDSP_INUSE (const char* buffer, TCONN_DIDSP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_DIDSP_INUSE (const char* buffer, int len, TCONN_DIDSP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_CONN_DIDSP_INUSE (char* buffer, ED_EXLONG bitOffset, TCONN_DIDSP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_CONN_EISP_INCFG (const char* buffer, TCONN_EISP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_EISP_INCFG (const char* buffer, int len, TCONN_EISP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_CONN_EISP_INCFG (char* buffer, ED_EXLONG bitOffset, TCONN_EISP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_CONN_EISP_INUSE (const char* buffer, TCONN_EISP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_EISP_INUSE (const char* buffer, int len, TCONN_EISP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_CONN_EISP_INUSE (char* buffer, ED_EXLONG bitOffset, TCONN_EISP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_CONN_QISP_INCFG (const char* buffer, TCONN_QISP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_QISP_INCFG (const char* buffer, int len, TCONN_QISP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_CONN_QISP_INCFG (char* buffer, ED_EXLONG bitOffset, TCONN_QISP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_CONN_QISP_INUSE (const char* buffer, TCONN_QISP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_QISP_INUSE (const char* buffer, int len, TCONN_QISP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_CONN_QISP_INUSE (char* buffer, ED_EXLONG bitOffset, TCONN_QISP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_CONN_DCSP_INCFG (const char* buffer, TCONN_DCSP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_DCSP_INCFG (const char* buffer, int len, TCONN_DCSP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_CONN_DCSP_INCFG (char* buffer, ED_EXLONG bitOffset, TCONN_DCSP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_CONN_DCSP_INUSE (const char* buffer, TCONN_DCSP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_DCSP_INUSE (const char* buffer, int len, TCONN_DCSP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_CONN_DCSP_INUSE (char* buffer, ED_EXLONG bitOffset, TCONN_DCSP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_CONN_DRUP_INCFG (const char* buffer, TCONN_DRUP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_DRUP_INCFG (const char* buffer, int len, TCONN_DRUP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_CONN_DRUP_INCFG (char* buffer, ED_EXLONG bitOffset, TCONN_DRUP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_CONN_DRUP_INUSE (const char* buffer, TCONN_DRUP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_DRUP_INUSE (const char* buffer, int len, TCONN_DRUP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_CONN_DRUP_INUSE (char* buffer, ED_EXLONG bitOffset, TCONN_DRUP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_CONN_MRUP_INCFG (const char* buffer, TCONN_MRUP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_MRUP_INCFG (const char* buffer, int len, TCONN_MRUP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_CONN_MRUP_INCFG (char* buffer, ED_EXLONG bitOffset, TCONN_MRUP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_CONN_MRUP_INUSE (const char* buffer, TCONN_MRUP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_MRUP_INUSE (const char* buffer, int len, TCONN_MRUP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_CONN_MRUP_INUSE (char* buffer, ED_EXLONG bitOffset, TCONN_MRUP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_CONN_DPCP_INCFG (const char* buffer, TCONN_DPCP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_DPCP_INCFG (const char* buffer, int len, TCONN_DPCP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_CONN_DPCP_INCFG (char* buffer, ED_EXLONG bitOffset, TCONN_DPCP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_CONN_OMP_INCFG (const char* buffer, TCONN_OMP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_OMP_INCFG (const char* buffer, int len, TCONN_OMP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_CONN_OMP_INCFG (char* buffer, ED_EXLONG bitOffset, TCONN_OMP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_CONN_OMP_INUSE (const char* buffer, TCONN_OMP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_OMP_INUSE (const char* buffer, int len, TCONN_OMP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_CONN_OMP_INUSE (char* buffer, ED_EXLONG bitOffset, TCONN_OMP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_SECURITY_DSP_INCFG (const char* buffer, TSECURITY_DSP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_SECURITY_DSP_INCFG (const char* buffer, int len, TSECURITY_DSP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_SECURITY_DSP_INCFG (char* buffer, ED_EXLONG bitOffset, TSECURITY_DSP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_SECURITY_GSP_INCFG (const char* buffer, TSECURITY_GSP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_SECURITY_GSP_INCFG (const char* buffer, int len, TSECURITY_GSP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_SECURITY_GSP_INCFG (char* buffer, ED_EXLONG bitOffset, TSECURITY_GSP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_SECURITY_DKEP_INCFG (const char* buffer, TSECURITY_DKEP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_SECURITY_DKEP_INCFG (const char* buffer, int len, TSECURITY_DKEP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_SECURITY_DKEP_INCFG (char* buffer, ED_EXLONG bitOffset, TSECURITY_DKEP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_SECURITY_DHKEP_INCFG (const char* buffer, TSECURITY_DHKEP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_SECURITY_DHKEP_INCFG (const char* buffer, int len, TSECURITY_DHKEP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_SECURITY_DHKEP_INCFG (char* buffer, ED_EXLONG bitOffset, TSECURITY_DHKEP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_SECURITY_DAP_INCFG (const char* buffer, TSECURITY_DAP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_SECURITY_DAP_INCFG (const char* buffer, int len, TSECURITY_DAP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_SECURITY_DAP_INCFG (char* buffer, ED_EXLONG bitOffset, TSECURITY_DAP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_SECURITY_SHA1AP_INCFG (const char* buffer, TSECURITY_SHA1AP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_SECURITY_SHA1AP_INCFG (const char* buffer, int len, TSECURITY_SHA1AP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_SECURITY_SHA1AP_INCFG (char* buffer, ED_EXLONG bitOffset, TSECURITY_SHA1AP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_SECURITY_DEP_INCFG (const char* buffer, TSECURITY_DEP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_SECURITY_DEP_INCFG (const char* buffer, int len, TSECURITY_DEP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_SECURITY_DEP_INCFG (char* buffer, ED_EXLONG bitOffset, TSECURITY_DEP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_MAC_DCCMACP_INCFG (const char* buffer, TMAC_DCCMACP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_DCCMACP_INCFG (const char* buffer, int len, TMAC_DCCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_MAC_DCCMACP_INCFG (char* buffer, ED_EXLONG bitOffset, TMAC_DCCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_MAC_ECCMACP_INCFG (const char* buffer, TMAC_ECCMACP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_ECCMACP_INCFG (const char* buffer, int len, TMAC_ECCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_MAC_ECCMACP_INCFG (char* buffer, ED_EXLONG bitOffset, TMAC_ECCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_MAC_DACMACP_INCFG (const char* buffer, TMAC_DACMACP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_DACMACP_INCFG (const char* buffer, int len, TMAC_DACMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_MAC_DACMACP_INCFG (char* buffer, ED_EXLONG bitOffset, TMAC_DACMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_MAC_DACMACP_INUSE (const char* buffer, TMAC_DACMACP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_DACMACP_INUSE (const char* buffer, int len, TMAC_DACMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_MAC_DACMACP_INUSE (char* buffer, ED_EXLONG bitOffset, TMAC_DACMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_MAC_EACMACP_INCFG (const char* buffer, TMAC_EACMACP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_EACMACP_INCFG (const char* buffer, int len, TMAC_EACMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_MAC_EACMACP_INCFG (char* buffer, ED_EXLONG bitOffset, TMAC_EACMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_MAC_EACMACP_INUSE (const char* buffer, TMAC_EACMACP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_EACMACP_INUSE (const char* buffer, int len, TMAC_EACMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_MAC_EACMACP_INUSE (char* buffer, ED_EXLONG bitOffset, TMAC_EACMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_MAC_DFTCMACP_INCFG (const char* buffer, TMAC_DFTCMACP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_DFTCMACP_INCFG (const char* buffer, int len, TMAC_DFTCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_MAC_DFTCMACP_INCFG (char* buffer, ED_EXLONG bitOffset, TMAC_DFTCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_MAC_DFTCMACP_INUSE (const char* buffer, TMAC_DFTCMACP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_DFTCMACP_INUSE (const char* buffer, int len, TMAC_DFTCMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_MAC_DFTCMACP_INUSE (char* buffer, ED_EXLONG bitOffset, TMAC_DFTCMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_MAC_EFTCMACP_INCFG (const char* buffer, TMAC_EFTCMACP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_EFTCMACP_INCFG (const char* buffer, int len, TMAC_EFTCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_MAC_EFTCMACP_INCFG (char* buffer, ED_EXLONG bitOffset, TMAC_EFTCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_MAC_EFTCMACP_INUSE (const char* buffer, TMAC_EFTCMACP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_EFTCMACP_INUSE (const char* buffer, int len, TMAC_EFTCMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_MAC_EFTCMACP_INUSE (char* buffer, ED_EXLONG bitOffset, TMAC_EFTCMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_MAC_MFTCMACP_INCFG (const char* buffer, TMAC_MFTCMACP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_MFTCMACP_INCFG (const char* buffer, int len, TMAC_MFTCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_MAC_MFTCMACP_INCFG (char* buffer, ED_EXLONG bitOffset, TMAC_MFTCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_MAC_MFTCMACP_INUSE (const char* buffer, TMAC_MFTCMACP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_MFTCMACP_INUSE (const char* buffer, int len, TMAC_MFTCMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_MAC_MFTCMACP_INUSE (char* buffer, ED_EXLONG bitOffset, TMAC_MFTCMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_MAC_DRTCMACP_INCFG (const char* buffer, TMAC_DRTCMACP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_DRTCMACP_INCFG (const char* buffer, int len, TMAC_DRTCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_MAC_DRTCMACP_INCFG (char* buffer, ED_EXLONG bitOffset, TMAC_DRTCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_MAC_DRTCMACP_INUSE (const char* buffer, TMAC_DRTCMACP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_DRTCMACP_INUSE (const char* buffer, int len, TMAC_DRTCMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_MAC_DRTCMACP_INUSE (char* buffer, ED_EXLONG bitOffset, TMAC_DRTCMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_MAC_S1RTCMACP_INCFG (const char* buffer, TMAC_S1RTCMACP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_S1RTCMACP_INCFG (const char* buffer, int len, TMAC_S1RTCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_MAC_S1RTCMACP_INCFG (char* buffer, ED_EXLONG bitOffset, TMAC_S1RTCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_MAC_S1RTCMACP_INUSE (const char* buffer, TMAC_S1RTCMACP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_S1RTCMACP_INUSE (const char* buffer, int len, TMAC_S1RTCMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_MAC_S1RTCMACP_INUSE (char* buffer, ED_EXLONG bitOffset, TMAC_S1RTCMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_MAC_S3RTCMACP_INCFG (const char* buffer, TMAC_S3RTCMACP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_S3RTCMACP_INCFG (const char* buffer, int len, TMAC_S3RTCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_MAC_S3RTCMACP_INCFG (char* buffer, ED_EXLONG bitOffset, TMAC_S3RTCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_MAC_S3RTCMACP_INUSE (const char* buffer, TMAC_S3RTCMACP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_S3RTCMACP_INUSE (const char* buffer, int len, TMAC_S3RTCMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_MAC_S3RTCMACP_INUSE (char* buffer, ED_EXLONG bitOffset, TMAC_S3RTCMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_MAC_MRTCMACP_INCFG (const char* buffer, TMAC_MRTCMACP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_MRTCMACP_INCFG (const char* buffer, int len, TMAC_MRTCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_MAC_MRTCMACP_INCFG (char* buffer, ED_EXLONG bitOffset, TMAC_MRTCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_MAC_MRTCMACP_INUSE (const char* buffer, TMAC_MRTCMACP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_MRTCMACP_INUSE (const char* buffer, int len, TMAC_MRTCMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_MAC_MRTCMACP_INUSE (char* buffer, ED_EXLONG bitOffset, TMAC_MRTCMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_PHYS01_DS0S1PLPI_INCFG (const char* buffer, TPHYS01_DS0S1PLPI_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_PHYS01_DS0S1PLPI_INCFG (const char* buffer, int len, TPHYS01_DS0S1PLPI_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_PHYS01_DS0S1PLPI_INCFG (char* buffer, ED_EXLONG bitOffset, TPHYS01_DS0S1PLPI_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_PHYS2_S2PLPI_INCFG (const char* buffer, TPHYS2_S2PLPI_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_PHYS2_S2PLPI_INCFG (const char* buffer, int len, TPHYS2_S2PLPI_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_PHYS2_S2PLPI_INCFG (char* buffer, ED_EXLONG bitOffset, TPHYS2_S2PLPI_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_PHYS3_S3PLPI_INCFG (const char* buffer, TPHYS3_S3PLPI_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_PHYS3_S3PLPI_INCFG (const char* buffer, int len, TPHYS3_S3PLPI_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_PHYS3_S3PLPI_INCFG (char* buffer, ED_EXLONG bitOffset, TPHYS3_S3PLPI_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_PHYS3_S3PLPI_INUSE (const char* buffer, TPHYS3_S3PLPI_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_PHYS3_S3PLPI_INUSE (const char* buffer, int len, TPHYS3_S3PLPI_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_PHYS3_S3PLPI_INUSE (char* buffer, ED_EXLONG bitOffset, TPHYS3_S3PLPI_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_GEN_GCP (const char* buffer, TGEN_GCP_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_GEN_GCP (const char* buffer, int len, TGEN_GCP_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_GEN_GCP (char* buffer, ED_EXLONG bitOffset, TGEN_GCP_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_GEN_GAUP (const char* buffer, TGEN_GAUP_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_GEN_GAUP (const char* buffer, int len, TGEN_GAUP_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_GEN_GAUP (char* buffer, ED_EXLONG bitOffset, TGEN_GAUP_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);

#ifdef __cplusplus
	}
#endif
#endif

