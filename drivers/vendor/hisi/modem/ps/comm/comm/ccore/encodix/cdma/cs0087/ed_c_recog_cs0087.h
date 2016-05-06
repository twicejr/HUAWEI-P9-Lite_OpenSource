/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c-recog
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __ed_c_recog_cs0087_h
#define __ed_c_recog_cs0087_h
#include "ed_c_cs0087.h"
#if ED_COMMON_CRC != 0x328E3625 && ED_VERSION != 10152 && ED_VERSION != 10153
#error Invalid Encodix library files linked; used those distributed with Encodix 1.0.154
#endif

#include "ed_user.h"
#define ED_MAXSIZE 600
#include "endec_configs_cs0087.h"

#ifdef __cplusplus
	extern "C" {
#endif

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group RPDCON_IRATINSP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_RPDCON_IRATINSP_INUSE_Unrecognized = 0,
	ID_RPDCON_IRATINSP_INUSE_RPDCON_IRATINSP_INUSE_Sync
} TRPDCON_IRATINSP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group RPDCON_IRATINSP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TRPDCON_IRATINSP_INUSE_Type Type;
	int MessageType;
	union {
		c_RPDCON_IRATINSP_INUSE_Sync* fld_c_RPDCON_IRATINSP_INUSE_Sync;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TRPDCON_IRATINSP_INUSE_Data;
#define INIT_TRPDCON_IRATINSP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TRPDCON_IRATINSP_INUSE_Data)), (sp)->Type=ID_RPDCON_IRATINSP_INUSE_Unrecognized)
void FREE_TRPDCON_IRATINSP_INUSE_Data (TRPDCON_IRATINSP_INUSE_Data* sp);

void SETPRESENT_TRPDCON_IRATINSP_INUSE_Data(TRPDCON_IRATINSP_INUSE_Data* sp, TRPDCON_IRATINSP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group RPDSES_SL
--------------------------------------------------------------------*/
typedef enum {
	ID_RPDSES_SL_Unrecognized = 0,
	ID_RPDSES_SL_RPDSES_SL_UATIAssignment,
	ID_RPDSES_SL_RPDSES_SL_InterRATMobilityIndication,
	ID_RPDSES_SL_RPDSES_SL_InterRATMobilityAck
} TRPDSES_SL_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group RPDSES_SL
--------------------------------------------------------------------*/
typedef struct {
	TRPDSES_SL_Type Type;
	int MessageType;
	union {
		c_RPDSES_SL_UATIAssignment* fld_c_RPDSES_SL_UATIAssignment;
		c_RPDSES_SL_InterRATMobilityIndication* fld_c_RPDSES_SL_InterRATMobilityIndication;
		c_RPDSES_SL_InterRATMobilityAck* fld_c_RPDSES_SL_InterRATMobilityAck;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TRPDSES_SL_Data;
#define INIT_TRPDSES_SL_Data(sp) (ED_RESET_MEM ((sp), sizeof (TRPDSES_SL_Data)), (sp)->Type=ID_RPDSES_SL_Unrecognized)
void FREE_TRPDSES_SL_Data (TRPDSES_SL_Data* sp);

void SETPRESENT_TRPDSES_SL_Data(TRPDSES_SL_Data* sp, TRPDSES_SL_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group RPDCON_IRATSAP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_RPDCON_IRATSAP_INCFG_Unrecognized = 0,
	ID_RPDCON_IRATSAP_INCFG_RPDCON_IRATSAP_INCFG_ConfigurationRequest,
	ID_RPDCON_IRATSAP_INCFG_RPDCON_IRATSAP_INCFG_ConfigurationResponse
} TRPDCON_IRATSAP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group RPDCON_IRATSAP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TRPDCON_IRATSAP_INCFG_Type Type;
	int MessageType;
	union {
		c_RPDCON_IRATSAP_INCFG_ConfigurationRequest* fld_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest;
		c_RPDCON_IRATSAP_INCFG_ConfigurationResponse* fld_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TRPDCON_IRATSAP_INCFG_Data;
#define INIT_TRPDCON_IRATSAP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TRPDCON_IRATSAP_INCFG_Data)), (sp)->Type=ID_RPDCON_IRATSAP_INCFG_Unrecognized)
void FREE_TRPDCON_IRATSAP_INCFG_Data (TRPDCON_IRATSAP_INCFG_Data* sp);

void SETPRESENT_TRPDCON_IRATSAP_INCFG_Data(TRPDCON_IRATSAP_INCFG_Data* sp, TRPDCON_IRATSAP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group RPDCON_IRATSAP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_RPDCON_IRATSAP_INUSE_Unrecognized = 0,
	ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq,
	ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf,
	ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail,
	ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq,
	ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf,
	ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq,
	ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete
} TRPDCON_IRATSAP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group RPDCON_IRATSAP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TRPDCON_IRATSAP_INUSE_Type Type;
	int MessageType;
	union {
		c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq* fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq;
		c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf* fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf;
		c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail* fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail;
		c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq* fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq;
		c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf* fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf;
		c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq* fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq;
		c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete* fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TRPDCON_IRATSAP_INUSE_Data;
#define INIT_TRPDCON_IRATSAP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TRPDCON_IRATSAP_INUSE_Data)), (sp)->Type=ID_RPDCON_IRATSAP_INUSE_Unrecognized)
void FREE_TRPDCON_IRATSAP_INUSE_Data (TRPDCON_IRATSAP_INUSE_Data* sp);

void SETPRESENT_TRPDCON_IRATSAP_INUSE_Data(TRPDCON_IRATSAP_INUSE_Data* sp, TRPDCON_IRATSAP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group RPDCON_IRATINSP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_RPDCON_IRATINSP_INCFG_Unrecognized = 0,
	ID_RPDCON_IRATINSP_INCFG_RPDCON_IRATINSP_INCFG_ConfigurationRequest,
	ID_RPDCON_IRATINSP_INCFG_RPDCON_IRATINSP_INCFG_ConfigurationResponse
} TRPDCON_IRATINSP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group RPDCON_IRATINSP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TRPDCON_IRATINSP_INCFG_Type Type;
	int MessageType;
	union {
		c_RPDCON_IRATINSP_INCFG_ConfigurationRequest* fld_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest;
		c_RPDCON_IRATINSP_INCFG_ConfigurationResponse* fld_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TRPDCON_IRATINSP_INCFG_Data;
#define INIT_TRPDCON_IRATINSP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TRPDCON_IRATINSP_INCFG_Data)), (sp)->Type=ID_RPDCON_IRATINSP_INCFG_Unrecognized)
void FREE_TRPDCON_IRATINSP_INCFG_Data (TRPDCON_IRATINSP_INCFG_Data* sp);

void SETPRESENT_TRPDCON_IRATINSP_INCFG_Data(TRPDCON_IRATINSP_INCFG_Data* sp, TRPDCON_IRATINSP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group RPDCON_IRATISP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_RPDCON_IRATISP_INCFG_Unrecognized = 0,
	ID_RPDCON_IRATISP_INCFG_RPDCON_IRATISP_INCFG_ConfigurationRequest,
	ID_RPDCON_IRATISP_INCFG_RPDCON_IRATISP_INCFG_ConfigurationResponse
} TRPDCON_IRATISP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group RPDCON_IRATISP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TRPDCON_IRATISP_INCFG_Type Type;
	int MessageType;
	union {
		c_RPDCON_IRATISP_INCFG_ConfigurationRequest* fld_c_RPDCON_IRATISP_INCFG_ConfigurationRequest;
		c_RPDCON_IRATISP_INCFG_ConfigurationResponse* fld_c_RPDCON_IRATISP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TRPDCON_IRATISP_INCFG_Data;
#define INIT_TRPDCON_IRATISP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TRPDCON_IRATISP_INCFG_Data)), (sp)->Type=ID_RPDCON_IRATISP_INCFG_Unrecognized)
void FREE_TRPDCON_IRATISP_INCFG_Data (TRPDCON_IRATISP_INCFG_Data* sp);

void SETPRESENT_TRPDCON_IRATISP_INCFG_Data(TRPDCON_IRATISP_INCFG_Data* sp, TRPDCON_IRATISP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group RPDCON_IRATISP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_RPDCON_IRATISP_INUSE_Unrecognized = 0,
	ID_RPDCON_IRATISP_INUSE_RPDCON_IRATISP_INUSE_Page,
	ID_RPDCON_IRATISP_INUSE_RPDCON_IRATISP_INUSE_ConnectionRequest,
	ID_RPDCON_IRATISP_INUSE_RPDCON_IRATISP_INUSE_ConnectionDeny,
	ID_RPDCON_IRATISP_INUSE_RPDCON_IRATISP_INUSE_AttributeUpdateRequest,
	ID_RPDCON_IRATISP_INUSE_RPDCON_IRATISP_INUSE_AttributeUpdateAccept,
	ID_RPDCON_IRATISP_INUSE_RPDCON_IRATISP_INUSE_AttributeUpdateReject
} TRPDCON_IRATISP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group RPDCON_IRATISP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TRPDCON_IRATISP_INUSE_Type Type;
	int MessageType;
	union {
		c_RPDCON_IRATISP_INUSE_Page* fld_c_RPDCON_IRATISP_INUSE_Page;
		c_RPDCON_IRATISP_INUSE_ConnectionRequest* fld_c_RPDCON_IRATISP_INUSE_ConnectionRequest;
		c_RPDCON_IRATISP_INUSE_ConnectionDeny* fld_c_RPDCON_IRATISP_INUSE_ConnectionDeny;
		c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest* fld_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest;
		c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept* fld_c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept;
		c_RPDCON_IRATISP_INUSE_AttributeUpdateReject* fld_c_RPDCON_IRATISP_INUSE_AttributeUpdateReject;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TRPDCON_IRATISP_INUSE_Data;
#define INIT_TRPDCON_IRATISP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TRPDCON_IRATISP_INUSE_Data)), (sp)->Type=ID_RPDCON_IRATISP_INUSE_Unrecognized)
void FREE_TRPDCON_IRATISP_INUSE_Data (TRPDCON_IRATISP_INUSE_Data* sp);

void SETPRESENT_TRPDCON_IRATISP_INUSE_Data(TRPDCON_IRATISP_INUSE_Data* sp, TRPDCON_IRATISP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group RPDCON_IRATRUP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_RPDCON_IRATRUP_INCFG_Unrecognized = 0,
	ID_RPDCON_IRATRUP_INCFG_RPDCON_IRATRUP_INCFG_ConfigurationRequest,
	ID_RPDCON_IRATRUP_INCFG_RPDCON_IRATRUP_INCFG_ConfigurationResponse
} TRPDCON_IRATRUP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group RPDCON_IRATRUP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TRPDCON_IRATRUP_INCFG_Type Type;
	int MessageType;
	union {
		c_RPDCON_IRATRUP_INCFG_ConfigurationRequest* fld_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest;
		c_RPDCON_IRATRUP_INCFG_ConfigurationResponse* fld_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TRPDCON_IRATRUP_INCFG_Data;
#define INIT_TRPDCON_IRATRUP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TRPDCON_IRATRUP_INCFG_Data)), (sp)->Type=ID_RPDCON_IRATRUP_INCFG_Unrecognized)
void FREE_TRPDCON_IRATRUP_INCFG_Data (TRPDCON_IRATRUP_INCFG_Data* sp);

void SETPRESENT_TRPDCON_IRATRUP_INCFG_Data(TRPDCON_IRATRUP_INCFG_Data* sp, TRPDCON_IRATRUP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group RPDCON_IRATRUP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_RPDCON_IRATRUP_INUSE_Unrecognized = 0,
	ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_RouteUpdate,
	ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment,
	ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_TrafficChannelComplete,
	ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_ResetReport,
	ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_NeighborList,
	ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_AttributeOverride,
	ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse,
	ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_RouteUpdateRequest,
	ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest,
	ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept,
	ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_AttributeUpdateReject
} TRPDCON_IRATRUP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group RPDCON_IRATRUP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TRPDCON_IRATRUP_INUSE_Type Type;
	int MessageType;
	union {
		c_RPDCON_IRATRUP_INUSE_RouteUpdate* fld_c_RPDCON_IRATRUP_INUSE_RouteUpdate;
		c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment* fld_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment;
		c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete* fld_c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete;
		c_RPDCON_IRATRUP_INUSE_ResetReport* fld_c_RPDCON_IRATRUP_INUSE_ResetReport;
		c_RPDCON_IRATRUP_INUSE_NeighborList* fld_c_RPDCON_IRATRUP_INUSE_NeighborList;
		c_RPDCON_IRATRUP_INUSE_AttributeOverride* fld_c_RPDCON_IRATRUP_INUSE_AttributeOverride;
		c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse* fld_c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse;
		c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest* fld_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest;
		c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest* fld_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest;
		c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept* fld_c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept;
		c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject* fld_c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TRPDCON_IRATRUP_INUSE_Data;
#define INIT_TRPDCON_IRATRUP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TRPDCON_IRATRUP_INUSE_Data)), (sp)->Type=ID_RPDCON_IRATRUP_INUSE_Unrecognized)
void FREE_TRPDCON_IRATRUP_INUSE_Data (TRPDCON_IRATRUP_INUSE_Data* sp);

void SETPRESENT_TRPDCON_IRATRUP_INUSE_Data(TRPDCON_IRATRUP_INUSE_Data* sp, TRPDCON_IRATRUP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group RPDCON_IRATOMP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_RPDCON_IRATOMP_INCFG_Unrecognized = 0,
	ID_RPDCON_IRATOMP_INCFG_RPDCON_IRATOMP_INCFG_ConfigurationRequest,
	ID_RPDCON_IRATOMP_INCFG_RPDCON_IRATOMP_INCFG_ConfigurationResponse
} TRPDCON_IRATOMP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group RPDCON_IRATOMP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TRPDCON_IRATOMP_INCFG_Type Type;
	int MessageType;
	union {
		c_RPDCON_IRATOMP_INCFG_ConfigurationRequest* fld_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest;
		c_RPDCON_IRATOMP_INCFG_ConfigurationResponse* fld_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TRPDCON_IRATOMP_INCFG_Data;
#define INIT_TRPDCON_IRATOMP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TRPDCON_IRATOMP_INCFG_Data)), (sp)->Type=ID_RPDCON_IRATOMP_INCFG_Unrecognized)
void FREE_TRPDCON_IRATOMP_INCFG_Data (TRPDCON_IRATOMP_INCFG_Data* sp);

void SETPRESENT_TRPDCON_IRATOMP_INCFG_Data(TRPDCON_IRATOMP_INCFG_Data* sp, TRPDCON_IRATOMP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group RPDCON_IRATOMP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_RPDCON_IRATOMP_INUSE_Unrecognized = 0,
	ID_RPDCON_IRATOMP_INUSE_RPDCON_IRATOMP_INUSE_QuickConfig,
	ID_RPDCON_IRATOMP_INUSE_RPDCON_IRATOMP_INUSE_SectorParameters,
	ID_RPDCON_IRATOMP_INUSE_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters,
	ID_RPDCON_IRATOMP_INUSE_RPDCON_IRATOMP_INUSE_OtherRATNeighborList
} TRPDCON_IRATOMP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group RPDCON_IRATOMP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TRPDCON_IRATOMP_INUSE_Type Type;
	int MessageType;
	union {
		c_RPDCON_IRATOMP_INUSE_QuickConfig* fld_c_RPDCON_IRATOMP_INUSE_QuickConfig;
		c_RPDCON_IRATOMP_INUSE_SectorParameters* fld_c_RPDCON_IRATOMP_INUSE_SectorParameters;
		c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters* fld_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters;
		c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList* fld_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TRPDCON_IRATOMP_INUSE_Data;
#define INIT_TRPDCON_IRATOMP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TRPDCON_IRATOMP_INUSE_Data)), (sp)->Type=ID_RPDCON_IRATOMP_INUSE_Unrecognized)
void FREE_TRPDCON_IRATOMP_INUSE_Data (TRPDCON_IRATOMP_INUSE_Data* sp);

void SETPRESENT_TRPDCON_IRATOMP_INUSE_Data(TRPDCON_IRATOMP_INUSE_Data* sp, TRPDCON_IRATOMP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group RPDCON_DSAP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_RPDCON_DSAP_INCFG_Unrecognized = 0,
	ID_RPDCON_DSAP_INCFG_RPDCON_DSAP_INCFG_ConfigurationRequest,
	ID_RPDCON_DSAP_INCFG_RPDCON_DSAP_INCFG_ConfigurationResponse
} TRPDCON_DSAP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group RPDCON_DSAP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TRPDCON_DSAP_INCFG_Type Type;
	int MessageType;
	union {
		c_RPDCON_DSAP_INCFG_ConfigurationRequest* fld_c_RPDCON_DSAP_INCFG_ConfigurationRequest;
		c_RPDCON_DSAP_INCFG_ConfigurationResponse* fld_c_RPDCON_DSAP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TRPDCON_DSAP_INCFG_Data;
#define INIT_TRPDCON_DSAP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TRPDCON_DSAP_INCFG_Data)), (sp)->Type=ID_RPDCON_DSAP_INCFG_Unrecognized)
void FREE_TRPDCON_DSAP_INCFG_Data (TRPDCON_DSAP_INCFG_Data* sp);

void SETPRESENT_TRPDCON_DSAP_INCFG_Data(TRPDCON_DSAP_INCFG_Data* sp, TRPDCON_DSAP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group RPDCON_IRATQISP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_RPDCON_IRATQISP_INCFG_Unrecognized = 0,
	ID_RPDCON_IRATQISP_INCFG_RPDCON_IRATQISP_INCFG_ConfigurationRequest,
	ID_RPDCON_IRATQISP_INCFG_RPDCON_IRATQISP_INCFG_ConfigurationResponse
} TRPDCON_IRATQISP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group RPDCON_IRATQISP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TRPDCON_IRATQISP_INCFG_Type Type;
	int MessageType;
	union {
		c_RPDCON_IRATQISP_INCFG_ConfigurationRequest* fld_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest;
		c_RPDCON_IRATQISP_INCFG_ConfigurationResponse* fld_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TRPDCON_IRATQISP_INCFG_Data;
#define INIT_TRPDCON_IRATQISP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TRPDCON_IRATQISP_INCFG_Data)), (sp)->Type=ID_RPDCON_IRATQISP_INCFG_Unrecognized)
void FREE_TRPDCON_IRATQISP_INCFG_Data (TRPDCON_IRATQISP_INCFG_Data* sp);

void SETPRESENT_TRPDCON_IRATQISP_INCFG_Data(TRPDCON_IRATQISP_INCFG_Data* sp, TRPDCON_IRATQISP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group RPDCON_IRATQISP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_RPDCON_IRATQISP_INUSE_Unrecognized = 0,
	ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_Page,
	ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_ConnectionRequest,
	ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_ConnectionDeny,
	ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_QuickPage,
	ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest,
	ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept,
	ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_AttributeUpdateReject
} TRPDCON_IRATQISP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group RPDCON_IRATQISP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TRPDCON_IRATQISP_INUSE_Type Type;
	int MessageType;
	union {
		c_RPDCON_IRATQISP_INUSE_Page* fld_c_RPDCON_IRATQISP_INUSE_Page;
		c_RPDCON_IRATQISP_INUSE_ConnectionRequest* fld_c_RPDCON_IRATQISP_INUSE_ConnectionRequest;
		c_RPDCON_IRATQISP_INUSE_ConnectionDeny* fld_c_RPDCON_IRATQISP_INUSE_ConnectionDeny;
		c_RPDCON_IRATQISP_INUSE_QuickPage* fld_c_RPDCON_IRATQISP_INUSE_QuickPage;
		c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest* fld_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest;
		c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept* fld_c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept;
		c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject* fld_c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TRPDCON_IRATQISP_INUSE_Data;
#define INIT_TRPDCON_IRATQISP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TRPDCON_IRATQISP_INUSE_Data)), (sp)->Type=ID_RPDCON_IRATQISP_INUSE_Unrecognized)
void FREE_TRPDCON_IRATQISP_INUSE_Data (TRPDCON_IRATQISP_INUSE_Data* sp);

void SETPRESENT_TRPDCON_IRATQISP_INUSE_Data(TRPDCON_IRATQISP_INUSE_Data* sp, TRPDCON_IRATQISP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group RPDCON_S1IRATRUP_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_RPDCON_S1IRATRUP_INCFG_Unrecognized = 0,
	ID_RPDCON_S1IRATRUP_INCFG_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest,
	ID_RPDCON_S1IRATRUP_INCFG_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse
} TRPDCON_S1IRATRUP_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group RPDCON_S1IRATRUP_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TRPDCON_S1IRATRUP_INCFG_Type Type;
	int MessageType;
	union {
		c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest* fld_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest;
		c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse* fld_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TRPDCON_S1IRATRUP_INCFG_Data;
#define INIT_TRPDCON_S1IRATRUP_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TRPDCON_S1IRATRUP_INCFG_Data)), (sp)->Type=ID_RPDCON_S1IRATRUP_INCFG_Unrecognized)
void FREE_TRPDCON_S1IRATRUP_INCFG_Data (TRPDCON_S1IRATRUP_INCFG_Data* sp);

void SETPRESENT_TRPDCON_S1IRATRUP_INCFG_Data(TRPDCON_S1IRATRUP_INCFG_Data* sp, TRPDCON_S1IRATRUP_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group RPDCON_S1IRATRUP_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_RPDCON_S1IRATRUP_INUSE_Unrecognized = 0,
	ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_RouteUpdate,
	ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment,
	ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete,
	ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_ResetReport,
	ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_NeighborList,
	ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest,
	ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest,
	ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept,
	ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject
} TRPDCON_S1IRATRUP_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group RPDCON_S1IRATRUP_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TRPDCON_S1IRATRUP_INUSE_Type Type;
	int MessageType;
	union {
		c_RPDCON_S1IRATRUP_INUSE_RouteUpdate* fld_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate;
		c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment* fld_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment;
		c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete* fld_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete;
		c_RPDCON_S1IRATRUP_INUSE_ResetReport* fld_c_RPDCON_S1IRATRUP_INUSE_ResetReport;
		c_RPDCON_S1IRATRUP_INUSE_NeighborList* fld_c_RPDCON_S1IRATRUP_INUSE_NeighborList;
		c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest* fld_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest;
		c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest* fld_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest;
		c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept* fld_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept;
		c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject* fld_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TRPDCON_S1IRATRUP_INUSE_Data;
#define INIT_TRPDCON_S1IRATRUP_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TRPDCON_S1IRATRUP_INUSE_Data)), (sp)->Type=ID_RPDCON_S1IRATRUP_INUSE_Unrecognized)
void FREE_TRPDCON_S1IRATRUP_INUSE_Data (TRPDCON_S1IRATRUP_INUSE_Data* sp);

void SETPRESENT_TRPDCON_S1IRATRUP_INUSE_Data(TRPDCON_S1IRATRUP_INUSE_Data* sp, TRPDCON_S1IRATRUP_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group RPDCON_IRATOMPCS0024B_INCFG
--------------------------------------------------------------------*/
typedef enum {
	ID_RPDCON_IRATOMPCS0024B_INCFG_Unrecognized = 0,
	ID_RPDCON_IRATOMPCS0024B_INCFG_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest,
	ID_RPDCON_IRATOMPCS0024B_INCFG_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse
} TRPDCON_IRATOMPCS0024B_INCFG_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group RPDCON_IRATOMPCS0024B_INCFG
--------------------------------------------------------------------*/
typedef struct {
	TRPDCON_IRATOMPCS0024B_INCFG_Type Type;
	int MessageType;
	union {
		c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest* fld_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest;
		c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse* fld_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TRPDCON_IRATOMPCS0024B_INCFG_Data;
#define INIT_TRPDCON_IRATOMPCS0024B_INCFG_Data(sp) (ED_RESET_MEM ((sp), sizeof (TRPDCON_IRATOMPCS0024B_INCFG_Data)), (sp)->Type=ID_RPDCON_IRATOMPCS0024B_INCFG_Unrecognized)
void FREE_TRPDCON_IRATOMPCS0024B_INCFG_Data (TRPDCON_IRATOMPCS0024B_INCFG_Data* sp);

void SETPRESENT_TRPDCON_IRATOMPCS0024B_INCFG_Data(TRPDCON_IRATOMPCS0024B_INCFG_Data* sp, TRPDCON_IRATOMPCS0024B_INCFG_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group RPDCON_IRATOMPCS0024B_INUSE
--------------------------------------------------------------------*/
typedef enum {
	ID_RPDCON_IRATOMPCS0024B_INUSE_Unrecognized = 0,
	ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig,
	ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters,
	ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters,
	ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList,
	ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation,
	ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification,
	ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText
} TRPDCON_IRATOMPCS0024B_INUSE_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group RPDCON_IRATOMPCS0024B_INUSE
--------------------------------------------------------------------*/
typedef struct {
	TRPDCON_IRATOMPCS0024B_INUSE_Type Type;
	int MessageType;
	union {
		c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig* fld_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig;
		c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters* fld_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters;
		c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters* fld_c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters;
		c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList* fld_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList;
		c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation* fld_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation;
		c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification* fld_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification;
		c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText* fld_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TRPDCON_IRATOMPCS0024B_INUSE_Data;
#define INIT_TRPDCON_IRATOMPCS0024B_INUSE_Data(sp) (ED_RESET_MEM ((sp), sizeof (TRPDCON_IRATOMPCS0024B_INUSE_Data)), (sp)->Type=ID_RPDCON_IRATOMPCS0024B_INUSE_Unrecognized)
void FREE_TRPDCON_IRATOMPCS0024B_INUSE_Data (TRPDCON_IRATOMPCS0024B_INUSE_Data* sp);

void SETPRESENT_TRPDCON_IRATOMPCS0024B_INUSE_Data(TRPDCON_IRATOMPCS0024B_INUSE_Data* sp, TRPDCON_IRATOMPCS0024B_INUSE_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group RPDRAT_ATS3RTCMACPR
--------------------------------------------------------------------*/
typedef enum {
	ID_RPDRAT_ATS3RTCMACPR_Unrecognized = 0,
	ID_RPDRAT_ATS3RTCMACPR_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters
} TRPDRAT_ATS3RTCMACPR_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group RPDRAT_ATS3RTCMACPR
--------------------------------------------------------------------*/
typedef struct {
	TRPDRAT_ATS3RTCMACPR_Type Type;
	int MessageType;
	union {
		c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters* fld_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TRPDRAT_ATS3RTCMACPR_Data;
#define INIT_TRPDRAT_ATS3RTCMACPR_Data(sp) (ED_RESET_MEM ((sp), sizeof (TRPDRAT_ATS3RTCMACPR_Data)), (sp)->Type=ID_RPDRAT_ATS3RTCMACPR_Unrecognized)
void FREE_TRPDRAT_ATS3RTCMACPR_Data (TRPDRAT_ATS3RTCMACPR_Data* sp);

void SETPRESENT_TRPDRAT_ATS3RTCMACPR_Data(TRPDRAT_ATS3RTCMACPR_Data* sp, TRPDRAT_ATS3RTCMACPR_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group RPDRAT_ATS4RTCMACPR
--------------------------------------------------------------------*/
typedef enum {
	ID_RPDRAT_ATS4RTCMACPR_Unrecognized = 0,
	ID_RPDRAT_ATS4RTCMACPR_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters
} TRPDRAT_ATS4RTCMACPR_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group RPDRAT_ATS4RTCMACPR
--------------------------------------------------------------------*/
typedef struct {
	TRPDRAT_ATS4RTCMACPR_Type Type;
	int MessageType;
	union {
		c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters* fld_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TRPDRAT_ATS4RTCMACPR_Data;
#define INIT_TRPDRAT_ATS4RTCMACPR_Data(sp) (ED_RESET_MEM ((sp), sizeof (TRPDRAT_ATS4RTCMACPR_Data)), (sp)->Type=ID_RPDRAT_ATS4RTCMACPR_Unrecognized)
void FREE_TRPDRAT_ATS4RTCMACPR_Data (TRPDRAT_ATS4RTCMACPR_Data* sp);

void SETPRESENT_TRPDRAT_ATS4RTCMACPR_Data(TRPDRAT_ATS4RTCMACPR_Data* sp, TRPDRAT_ATS4RTCMACPR_Type toBeSetPresent);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_RPDCON_IRATINSP_INUSE (const char* buffer, TRPDCON_IRATINSP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_IRATINSP_INUSE (const char* buffer, int len, TRPDCON_IRATINSP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_RPDCON_IRATINSP_INUSE (char* buffer, ED_EXLONG bitOffset, TRPDCON_IRATINSP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_RPDSES_SL (const char* buffer, TRPDSES_SL_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDSES_SL (const char* buffer, int len, TRPDSES_SL_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_RPDSES_SL (char* buffer, ED_EXLONG bitOffset, TRPDSES_SL_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_RPDCON_IRATSAP_INCFG (const char* buffer, TRPDCON_IRATSAP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_IRATSAP_INCFG (const char* buffer, int len, TRPDCON_IRATSAP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_RPDCON_IRATSAP_INCFG (char* buffer, ED_EXLONG bitOffset, TRPDCON_IRATSAP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_RPDCON_IRATSAP_INUSE (const char* buffer, TRPDCON_IRATSAP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_IRATSAP_INUSE (const char* buffer, int len, TRPDCON_IRATSAP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_RPDCON_IRATSAP_INUSE (char* buffer, ED_EXLONG bitOffset, TRPDCON_IRATSAP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_RPDCON_IRATINSP_INCFG (const char* buffer, TRPDCON_IRATINSP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_IRATINSP_INCFG (const char* buffer, int len, TRPDCON_IRATINSP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_RPDCON_IRATINSP_INCFG (char* buffer, ED_EXLONG bitOffset, TRPDCON_IRATINSP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_RPDCON_IRATISP_INCFG (const char* buffer, TRPDCON_IRATISP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_IRATISP_INCFG (const char* buffer, int len, TRPDCON_IRATISP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_RPDCON_IRATISP_INCFG (char* buffer, ED_EXLONG bitOffset, TRPDCON_IRATISP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_RPDCON_IRATISP_INUSE (const char* buffer, TRPDCON_IRATISP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_IRATISP_INUSE (const char* buffer, int len, TRPDCON_IRATISP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_RPDCON_IRATISP_INUSE (char* buffer, ED_EXLONG bitOffset, TRPDCON_IRATISP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_RPDCON_IRATRUP_INCFG (const char* buffer, TRPDCON_IRATRUP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_IRATRUP_INCFG (const char* buffer, int len, TRPDCON_IRATRUP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_RPDCON_IRATRUP_INCFG (char* buffer, ED_EXLONG bitOffset, TRPDCON_IRATRUP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_RPDCON_IRATRUP_INUSE (const char* buffer, TRPDCON_IRATRUP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_IRATRUP_INUSE (const char* buffer, int len, TRPDCON_IRATRUP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_RPDCON_IRATRUP_INUSE (char* buffer, ED_EXLONG bitOffset, TRPDCON_IRATRUP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_RPDCON_IRATOMP_INCFG (const char* buffer, TRPDCON_IRATOMP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_IRATOMP_INCFG (const char* buffer, int len, TRPDCON_IRATOMP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_RPDCON_IRATOMP_INCFG (char* buffer, ED_EXLONG bitOffset, TRPDCON_IRATOMP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_RPDCON_IRATOMP_INUSE (const char* buffer, TRPDCON_IRATOMP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_IRATOMP_INUSE (const char* buffer, int len, TRPDCON_IRATOMP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_RPDCON_IRATOMP_INUSE (char* buffer, ED_EXLONG bitOffset, TRPDCON_IRATOMP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_RPDCON_DSAP_INCFG (const char* buffer, TRPDCON_DSAP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_DSAP_INCFG (const char* buffer, int len, TRPDCON_DSAP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_RPDCON_DSAP_INCFG (char* buffer, ED_EXLONG bitOffset, TRPDCON_DSAP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_RPDCON_IRATQISP_INCFG (const char* buffer, TRPDCON_IRATQISP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_IRATQISP_INCFG (const char* buffer, int len, TRPDCON_IRATQISP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_RPDCON_IRATQISP_INCFG (char* buffer, ED_EXLONG bitOffset, TRPDCON_IRATQISP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_RPDCON_IRATQISP_INUSE (const char* buffer, TRPDCON_IRATQISP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_IRATQISP_INUSE (const char* buffer, int len, TRPDCON_IRATQISP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_RPDCON_IRATQISP_INUSE (char* buffer, ED_EXLONG bitOffset, TRPDCON_IRATQISP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_RPDCON_S1IRATRUP_INCFG (const char* buffer, TRPDCON_S1IRATRUP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_S1IRATRUP_INCFG (const char* buffer, int len, TRPDCON_S1IRATRUP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_RPDCON_S1IRATRUP_INCFG (char* buffer, ED_EXLONG bitOffset, TRPDCON_S1IRATRUP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_RPDCON_S1IRATRUP_INUSE (const char* buffer, TRPDCON_S1IRATRUP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_S1IRATRUP_INUSE (const char* buffer, int len, TRPDCON_S1IRATRUP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_RPDCON_S1IRATRUP_INUSE (char* buffer, ED_EXLONG bitOffset, TRPDCON_S1IRATRUP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_RPDCON_IRATOMPCS0024B_INCFG (const char* buffer, TRPDCON_IRATOMPCS0024B_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_IRATOMPCS0024B_INCFG (const char* buffer, int len, TRPDCON_IRATOMPCS0024B_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_RPDCON_IRATOMPCS0024B_INCFG (char* buffer, ED_EXLONG bitOffset, TRPDCON_IRATOMPCS0024B_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_RPDCON_IRATOMPCS0024B_INUSE (const char* buffer, TRPDCON_IRATOMPCS0024B_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_IRATOMPCS0024B_INUSE (const char* buffer, int len, TRPDCON_IRATOMPCS0024B_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_RPDCON_IRATOMPCS0024B_INUSE (char* buffer, ED_EXLONG bitOffset, TRPDCON_IRATOMPCS0024B_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_RPDRAT_ATS3RTCMACPR (const char* buffer, TRPDRAT_ATS3RTCMACPR_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDRAT_ATS3RTCMACPR (const char* buffer, int len, TRPDRAT_ATS3RTCMACPR_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_RPDRAT_ATS3RTCMACPR (char* buffer, ED_EXLONG bitOffset, TRPDRAT_ATS3RTCMACPR_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_RPDRAT_ATS4RTCMACPR (const char* buffer, TRPDRAT_ATS4RTCMACPR_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDRAT_ATS4RTCMACPR (const char* buffer, int len, TRPDRAT_ATS4RTCMACPR_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);
#endif

/* Set encode function */
int SetEncode_RPDRAT_ATS4RTCMACPR (char* buffer, ED_EXLONG bitOffset, TRPDRAT_ATS4RTCMACPR_Data* data, struct SCSN1CContextSet* pCSN1CContextSet);

#ifdef __cplusplus
	}
#endif
#endif

