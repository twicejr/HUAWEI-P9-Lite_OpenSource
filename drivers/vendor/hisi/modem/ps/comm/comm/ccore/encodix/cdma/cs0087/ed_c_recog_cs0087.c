/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c-recog
	http://www.Dafocus.it/
**************************************************************************/
/*lint -e959 -e530 -e774 -e572 -e778 -e525 -e539 -e701 -e123 -e438 -e119 -e506 -e529 -e550 -e666 -e713 -e719 -e730 -e734 -e744 -e801 -e801 -e813 -e830 -e40 */
#define ENCODIX_CS0087

#include "ed_c_recog_cs0087.h"
#include "ed_lib.h"
#include "RPDCON_IRATINSP_INUSE_cs0087.h"
#include "RPDSES_SL_cs0087.h"
#include "RPDCON_IRATSAP_INCFG_cs0087.h"
#include "RPDCON_IRATSAP_INUSE_cs0087.h"
#include "RPDCON_IRATINSP_INCFG_cs0087.h"
#include "RPDCON_IRATISP_INCFG_cs0087.h"
#include "RPDCON_IRATISP_INUSE_cs0087.h"
#include "RPDCON_IRATRUP_INCFG_cs0087.h"
#include "RPDCON_IRATRUP_INUSE_cs0087.h"
#include "RPDCON_IRATOMP_INCFG_cs0087.h"
#include "RPDCON_IRATOMP_INUSE_cs0087.h"
#include "RPDCON_DSAP_INCFG_cs0087.h"
#include "RPDCON_IRATQISP_INCFG_cs0087.h"
#include "RPDCON_IRATQISP_INUSE_cs0087.h"
#include "RPDCON_S1IRATRUP_INCFG_cs0087.h"
#include "RPDCON_S1IRATRUP_INUSE_cs0087.h"
#include "RPDCON_IRATOMPCS0024B_INCFG_cs0087.h"
#include "RPDCON_IRATOMPCS0024B_INUSE_cs0087.h"
#include "RPDRAT_ATS3RTCMACPR_cs0087.h"
#include "RPDRAT_ATS4RTCMACPR_cs0087.h"
#if ED_COMMON_CRC != 0x328E3625 && ED_VERSION != 10152 && ED_VERSION != 10153
#error Invalid Encodix library files linked; used those distributed with Encodix 1.0.154
#endif


void SETPRESENT_TRPDCON_IRATINSP_INUSE_Data (TRPDCON_IRATINSP_INUSE_Data* sp, TRPDCON_IRATINSP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TRPDCON_IRATINSP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_RPDCON_IRATINSP_INUSE_RPDCON_IRATINSP_INUSE_Sync: {
			sp->Data.fld_c_RPDCON_IRATINSP_INUSE_Sync = (c_RPDCON_IRATINSP_INUSE_Sync*)EDAlloc (sizeof (c_RPDCON_IRATINSP_INUSE_Sync));
			INIT_c_RPDCON_IRATINSP_INUSE_Sync (sp->Data.fld_c_RPDCON_IRATINSP_INUSE_Sync);
			break;
		}
		
		default:;
	}
}

void FREE_TRPDCON_IRATINSP_INUSE_Data (TRPDCON_IRATINSP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_RPDCON_IRATINSP_INUSE_RPDCON_IRATINSP_INUSE_Sync: {
			FREE_c_RPDCON_IRATINSP_INUSE_Sync (sp->Data.fld_c_RPDCON_IRATINSP_INUSE_Sync);
	EDFree (sp->Data.fld_c_RPDCON_IRATINSP_INUSE_Sync );
			break;
		}
		
		default:;
	}

	sp->Type = ID_RPDCON_IRATINSP_INUSE_Unrecognized;
}

void SETPRESENT_TRPDSES_SL_Data (TRPDSES_SL_Data* sp, TRPDSES_SL_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TRPDSES_SL_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_RPDSES_SL_RPDSES_SL_UATIAssignment: {
			sp->Data.fld_c_RPDSES_SL_UATIAssignment = (c_RPDSES_SL_UATIAssignment*)EDAlloc (sizeof (c_RPDSES_SL_UATIAssignment));
			INIT_c_RPDSES_SL_UATIAssignment (sp->Data.fld_c_RPDSES_SL_UATIAssignment);
			break;
		}
		
		case ID_RPDSES_SL_RPDSES_SL_InterRATMobilityIndication: {
			sp->Data.fld_c_RPDSES_SL_InterRATMobilityIndication = (c_RPDSES_SL_InterRATMobilityIndication*)EDAlloc (sizeof (c_RPDSES_SL_InterRATMobilityIndication));
			INIT_c_RPDSES_SL_InterRATMobilityIndication (sp->Data.fld_c_RPDSES_SL_InterRATMobilityIndication);
			break;
		}
		
		case ID_RPDSES_SL_RPDSES_SL_InterRATMobilityAck: {
			sp->Data.fld_c_RPDSES_SL_InterRATMobilityAck = (c_RPDSES_SL_InterRATMobilityAck*)EDAlloc (sizeof (c_RPDSES_SL_InterRATMobilityAck));
			INIT_c_RPDSES_SL_InterRATMobilityAck (sp->Data.fld_c_RPDSES_SL_InterRATMobilityAck);
			break;
		}
		
		default:;
	}
}

void FREE_TRPDSES_SL_Data (TRPDSES_SL_Data* sp)
{
	switch (sp->Type) {
		case ID_RPDSES_SL_RPDSES_SL_UATIAssignment: {
			FREE_c_RPDSES_SL_UATIAssignment (sp->Data.fld_c_RPDSES_SL_UATIAssignment);
	EDFree (sp->Data.fld_c_RPDSES_SL_UATIAssignment );
			break;
		}
		
		case ID_RPDSES_SL_RPDSES_SL_InterRATMobilityIndication: {
			FREE_c_RPDSES_SL_InterRATMobilityIndication (sp->Data.fld_c_RPDSES_SL_InterRATMobilityIndication);
	EDFree (sp->Data.fld_c_RPDSES_SL_InterRATMobilityIndication );
			break;
		}
		
		case ID_RPDSES_SL_RPDSES_SL_InterRATMobilityAck: {
			FREE_c_RPDSES_SL_InterRATMobilityAck (sp->Data.fld_c_RPDSES_SL_InterRATMobilityAck);
	EDFree (sp->Data.fld_c_RPDSES_SL_InterRATMobilityAck );
			break;
		}
		
		default:;
	}

	sp->Type = ID_RPDSES_SL_Unrecognized;
}

void SETPRESENT_TRPDCON_IRATSAP_INCFG_Data (TRPDCON_IRATSAP_INCFG_Data* sp, TRPDCON_IRATSAP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TRPDCON_IRATSAP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_RPDCON_IRATSAP_INCFG_RPDCON_IRATSAP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest = (c_RPDCON_IRATSAP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_RPDCON_IRATSAP_INCFG_ConfigurationRequest));
			INIT_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest (sp->Data.fld_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_RPDCON_IRATSAP_INCFG_RPDCON_IRATSAP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse = (c_RPDCON_IRATSAP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_RPDCON_IRATSAP_INCFG_ConfigurationResponse));
			INIT_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse (sp->Data.fld_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TRPDCON_IRATSAP_INCFG_Data (TRPDCON_IRATSAP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_RPDCON_IRATSAP_INCFG_RPDCON_IRATSAP_INCFG_ConfigurationRequest: {
			FREE_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest (sp->Data.fld_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_RPDCON_IRATSAP_INCFG_RPDCON_IRATSAP_INCFG_ConfigurationResponse: {
			FREE_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse (sp->Data.fld_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_RPDCON_IRATSAP_INCFG_Unrecognized;
}

void SETPRESENT_TRPDCON_IRATSAP_INUSE_Data (TRPDCON_IRATSAP_INUSE_Data* sp, TRPDCON_IRATSAP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TRPDCON_IRATSAP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq: {
			sp->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq = (c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq*)EDAlloc (sizeof (c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq));
			INIT_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq (sp->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq);
			break;
		}
		
		case ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf: {
			sp->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf = (c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf*)EDAlloc (sizeof (c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf));
			INIT_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf (sp->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf);
			break;
		}
		
		case ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail: {
			sp->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail = (c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail*)EDAlloc (sizeof (c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail));
			INIT_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail (sp->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail);
			break;
		}
		
		case ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq: {
			sp->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq = (c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq*)EDAlloc (sizeof (c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq));
			INIT_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq (sp->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq);
			break;
		}
		
		case ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf: {
			sp->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf = (c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf*)EDAlloc (sizeof (c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf));
			INIT_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf (sp->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf);
			break;
		}
		
		case ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq: {
			sp->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq = (c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq*)EDAlloc (sizeof (c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq));
			INIT_c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq (sp->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq);
			break;
		}
		
		case ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete: {
			sp->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete = (c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete*)EDAlloc (sizeof (c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete));
			INIT_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete (sp->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete);
			break;
		}
		
		default:;
	}
}

void FREE_TRPDCON_IRATSAP_INUSE_Data (TRPDCON_IRATSAP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq: {
			FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq (sp->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq);
	EDFree (sp->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq );
			break;
		}
		
		case ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf: {
			FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf (sp->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf);
	EDFree (sp->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf );
			break;
		}
		
		case ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail: {
			FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail (sp->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail);
	EDFree (sp->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail );
			break;
		}
		
		case ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq: {
			FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq (sp->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq);
	EDFree (sp->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq );
			break;
		}
		
		case ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf: {
			FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf (sp->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf);
	EDFree (sp->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf );
			break;
		}
		
		case ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq: {
			FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq (sp->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq);
	EDFree (sp->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq );
			break;
		}
		
		case ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete: {
			FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete (sp->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete);
	EDFree (sp->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete );
			break;
		}
		
		default:;
	}

	sp->Type = ID_RPDCON_IRATSAP_INUSE_Unrecognized;
}

void SETPRESENT_TRPDCON_IRATINSP_INCFG_Data (TRPDCON_IRATINSP_INCFG_Data* sp, TRPDCON_IRATINSP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TRPDCON_IRATINSP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_RPDCON_IRATINSP_INCFG_RPDCON_IRATINSP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest = (c_RPDCON_IRATINSP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_RPDCON_IRATINSP_INCFG_ConfigurationRequest));
			INIT_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest (sp->Data.fld_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_RPDCON_IRATINSP_INCFG_RPDCON_IRATINSP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse = (c_RPDCON_IRATINSP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_RPDCON_IRATINSP_INCFG_ConfigurationResponse));
			INIT_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse (sp->Data.fld_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TRPDCON_IRATINSP_INCFG_Data (TRPDCON_IRATINSP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_RPDCON_IRATINSP_INCFG_RPDCON_IRATINSP_INCFG_ConfigurationRequest: {
			FREE_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest (sp->Data.fld_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_RPDCON_IRATINSP_INCFG_RPDCON_IRATINSP_INCFG_ConfigurationResponse: {
			FREE_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse (sp->Data.fld_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_RPDCON_IRATINSP_INCFG_Unrecognized;
}

void SETPRESENT_TRPDCON_IRATISP_INCFG_Data (TRPDCON_IRATISP_INCFG_Data* sp, TRPDCON_IRATISP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TRPDCON_IRATISP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_RPDCON_IRATISP_INCFG_RPDCON_IRATISP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_RPDCON_IRATISP_INCFG_ConfigurationRequest = (c_RPDCON_IRATISP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_RPDCON_IRATISP_INCFG_ConfigurationRequest));
			INIT_c_RPDCON_IRATISP_INCFG_ConfigurationRequest (sp->Data.fld_c_RPDCON_IRATISP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_RPDCON_IRATISP_INCFG_RPDCON_IRATISP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_RPDCON_IRATISP_INCFG_ConfigurationResponse = (c_RPDCON_IRATISP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_RPDCON_IRATISP_INCFG_ConfigurationResponse));
			INIT_c_RPDCON_IRATISP_INCFG_ConfigurationResponse (sp->Data.fld_c_RPDCON_IRATISP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TRPDCON_IRATISP_INCFG_Data (TRPDCON_IRATISP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_RPDCON_IRATISP_INCFG_RPDCON_IRATISP_INCFG_ConfigurationRequest: {
			FREE_c_RPDCON_IRATISP_INCFG_ConfigurationRequest (sp->Data.fld_c_RPDCON_IRATISP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_RPDCON_IRATISP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_RPDCON_IRATISP_INCFG_RPDCON_IRATISP_INCFG_ConfigurationResponse: {
			FREE_c_RPDCON_IRATISP_INCFG_ConfigurationResponse (sp->Data.fld_c_RPDCON_IRATISP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_RPDCON_IRATISP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_RPDCON_IRATISP_INCFG_Unrecognized;
}

void SETPRESENT_TRPDCON_IRATISP_INUSE_Data (TRPDCON_IRATISP_INUSE_Data* sp, TRPDCON_IRATISP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TRPDCON_IRATISP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_RPDCON_IRATISP_INUSE_RPDCON_IRATISP_INUSE_Page: {
			sp->Data.fld_c_RPDCON_IRATISP_INUSE_Page = (c_RPDCON_IRATISP_INUSE_Page*)EDAlloc (sizeof (c_RPDCON_IRATISP_INUSE_Page));
			INIT_c_RPDCON_IRATISP_INUSE_Page (sp->Data.fld_c_RPDCON_IRATISP_INUSE_Page);
			break;
		}
		
		case ID_RPDCON_IRATISP_INUSE_RPDCON_IRATISP_INUSE_ConnectionRequest: {
			sp->Data.fld_c_RPDCON_IRATISP_INUSE_ConnectionRequest = (c_RPDCON_IRATISP_INUSE_ConnectionRequest*)EDAlloc (sizeof (c_RPDCON_IRATISP_INUSE_ConnectionRequest));
			INIT_c_RPDCON_IRATISP_INUSE_ConnectionRequest (sp->Data.fld_c_RPDCON_IRATISP_INUSE_ConnectionRequest);
			break;
		}
		
		case ID_RPDCON_IRATISP_INUSE_RPDCON_IRATISP_INUSE_ConnectionDeny: {
			sp->Data.fld_c_RPDCON_IRATISP_INUSE_ConnectionDeny = (c_RPDCON_IRATISP_INUSE_ConnectionDeny*)EDAlloc (sizeof (c_RPDCON_IRATISP_INUSE_ConnectionDeny));
			INIT_c_RPDCON_IRATISP_INUSE_ConnectionDeny (sp->Data.fld_c_RPDCON_IRATISP_INUSE_ConnectionDeny);
			break;
		}
		
		case ID_RPDCON_IRATISP_INUSE_RPDCON_IRATISP_INUSE_AttributeUpdateRequest: {
			sp->Data.fld_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest = (c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest*)EDAlloc (sizeof (c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest));
			INIT_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest);
			break;
		}
		
		case ID_RPDCON_IRATISP_INUSE_RPDCON_IRATISP_INUSE_AttributeUpdateAccept: {
			sp->Data.fld_c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept = (c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept*)EDAlloc (sizeof (c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept));
			INIT_c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept);
			break;
		}
		
		case ID_RPDCON_IRATISP_INUSE_RPDCON_IRATISP_INUSE_AttributeUpdateReject: {
			sp->Data.fld_c_RPDCON_IRATISP_INUSE_AttributeUpdateReject = (c_RPDCON_IRATISP_INUSE_AttributeUpdateReject*)EDAlloc (sizeof (c_RPDCON_IRATISP_INUSE_AttributeUpdateReject));
			INIT_c_RPDCON_IRATISP_INUSE_AttributeUpdateReject (sp->Data.fld_c_RPDCON_IRATISP_INUSE_AttributeUpdateReject);
			break;
		}
		
		default:;
	}
}

void FREE_TRPDCON_IRATISP_INUSE_Data (TRPDCON_IRATISP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_RPDCON_IRATISP_INUSE_RPDCON_IRATISP_INUSE_Page: {
			FREE_c_RPDCON_IRATISP_INUSE_Page (sp->Data.fld_c_RPDCON_IRATISP_INUSE_Page);
	EDFree (sp->Data.fld_c_RPDCON_IRATISP_INUSE_Page );
			break;
		}
		
		case ID_RPDCON_IRATISP_INUSE_RPDCON_IRATISP_INUSE_ConnectionRequest: {
			FREE_c_RPDCON_IRATISP_INUSE_ConnectionRequest (sp->Data.fld_c_RPDCON_IRATISP_INUSE_ConnectionRequest);
	EDFree (sp->Data.fld_c_RPDCON_IRATISP_INUSE_ConnectionRequest );
			break;
		}
		
		case ID_RPDCON_IRATISP_INUSE_RPDCON_IRATISP_INUSE_ConnectionDeny: {
			FREE_c_RPDCON_IRATISP_INUSE_ConnectionDeny (sp->Data.fld_c_RPDCON_IRATISP_INUSE_ConnectionDeny);
	EDFree (sp->Data.fld_c_RPDCON_IRATISP_INUSE_ConnectionDeny );
			break;
		}
		
		case ID_RPDCON_IRATISP_INUSE_RPDCON_IRATISP_INUSE_AttributeUpdateRequest: {
			FREE_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest);
	EDFree (sp->Data.fld_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest );
			break;
		}
		
		case ID_RPDCON_IRATISP_INUSE_RPDCON_IRATISP_INUSE_AttributeUpdateAccept: {
			FREE_c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept);
	EDFree (sp->Data.fld_c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept );
			break;
		}
		
		case ID_RPDCON_IRATISP_INUSE_RPDCON_IRATISP_INUSE_AttributeUpdateReject: {
			FREE_c_RPDCON_IRATISP_INUSE_AttributeUpdateReject (sp->Data.fld_c_RPDCON_IRATISP_INUSE_AttributeUpdateReject);
	EDFree (sp->Data.fld_c_RPDCON_IRATISP_INUSE_AttributeUpdateReject );
			break;
		}
		
		default:;
	}

	sp->Type = ID_RPDCON_IRATISP_INUSE_Unrecognized;
}

void SETPRESENT_TRPDCON_IRATRUP_INCFG_Data (TRPDCON_IRATRUP_INCFG_Data* sp, TRPDCON_IRATRUP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TRPDCON_IRATRUP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_RPDCON_IRATRUP_INCFG_RPDCON_IRATRUP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest = (c_RPDCON_IRATRUP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INCFG_ConfigurationRequest));
			INIT_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest (sp->Data.fld_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_RPDCON_IRATRUP_INCFG_RPDCON_IRATRUP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse = (c_RPDCON_IRATRUP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INCFG_ConfigurationResponse));
			INIT_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse (sp->Data.fld_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TRPDCON_IRATRUP_INCFG_Data (TRPDCON_IRATRUP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_RPDCON_IRATRUP_INCFG_RPDCON_IRATRUP_INCFG_ConfigurationRequest: {
			FREE_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest (sp->Data.fld_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_RPDCON_IRATRUP_INCFG_RPDCON_IRATRUP_INCFG_ConfigurationResponse: {
			FREE_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse (sp->Data.fld_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_RPDCON_IRATRUP_INCFG_Unrecognized;
}

void SETPRESENT_TRPDCON_IRATRUP_INUSE_Data (TRPDCON_IRATRUP_INUSE_Data* sp, TRPDCON_IRATRUP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TRPDCON_IRATRUP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_RouteUpdate: {
			sp->Data.fld_c_RPDCON_IRATRUP_INUSE_RouteUpdate = (c_RPDCON_IRATRUP_INUSE_RouteUpdate*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_RouteUpdate));
			INIT_c_RPDCON_IRATRUP_INUSE_RouteUpdate (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_RouteUpdate);
			break;
		}
		
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment: {
			sp->Data.fld_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment = (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment));
			INIT_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment);
			break;
		}
		
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_TrafficChannelComplete: {
			sp->Data.fld_c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete = (c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete));
			INIT_c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete);
			break;
		}
		
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_ResetReport: {
			sp->Data.fld_c_RPDCON_IRATRUP_INUSE_ResetReport = (c_RPDCON_IRATRUP_INUSE_ResetReport*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_ResetReport));
			INIT_c_RPDCON_IRATRUP_INUSE_ResetReport (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_ResetReport);
			break;
		}
		
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_NeighborList: {
			sp->Data.fld_c_RPDCON_IRATRUP_INUSE_NeighborList = (c_RPDCON_IRATRUP_INUSE_NeighborList*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_NeighborList));
			INIT_c_RPDCON_IRATRUP_INUSE_NeighborList (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_NeighborList);
			break;
		}
		
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_AttributeOverride: {
			sp->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeOverride = (c_RPDCON_IRATRUP_INUSE_AttributeOverride*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_AttributeOverride));
			INIT_c_RPDCON_IRATRUP_INUSE_AttributeOverride (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeOverride);
			break;
		}
		
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse: {
			sp->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse = (c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse));
			INIT_c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse);
			break;
		}
		
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_RouteUpdateRequest: {
			sp->Data.fld_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest = (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest));
			INIT_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest);
			break;
		}
		
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest: {
			sp->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest = (c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest));
			INIT_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest);
			break;
		}
		
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept: {
			sp->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept = (c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept));
			INIT_c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept);
			break;
		}
		
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_AttributeUpdateReject: {
			sp->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject = (c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject));
			INIT_c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject);
			break;
		}
		
		default:;
	}
}

void FREE_TRPDCON_IRATRUP_INUSE_Data (TRPDCON_IRATRUP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_RouteUpdate: {
			FREE_c_RPDCON_IRATRUP_INUSE_RouteUpdate (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_RouteUpdate);
	EDFree (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_RouteUpdate );
			break;
		}
		
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment: {
			FREE_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment);
	EDFree (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment );
			break;
		}
		
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_TrafficChannelComplete: {
			FREE_c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete);
	EDFree (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete );
			break;
		}
		
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_ResetReport: {
			FREE_c_RPDCON_IRATRUP_INUSE_ResetReport (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_ResetReport);
	EDFree (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_ResetReport );
			break;
		}
		
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_NeighborList: {
			FREE_c_RPDCON_IRATRUP_INUSE_NeighborList (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_NeighborList);
	EDFree (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_NeighborList );
			break;
		}
		
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_AttributeOverride: {
			FREE_c_RPDCON_IRATRUP_INUSE_AttributeOverride (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeOverride);
	EDFree (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeOverride );
			break;
		}
		
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse: {
			FREE_c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse);
	EDFree (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse );
			break;
		}
		
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_RouteUpdateRequest: {
			FREE_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest);
	EDFree (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest );
			break;
		}
		
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest: {
			FREE_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest);
	EDFree (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest );
			break;
		}
		
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept: {
			FREE_c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept);
	EDFree (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept );
			break;
		}
		
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_AttributeUpdateReject: {
			FREE_c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject);
	EDFree (sp->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject );
			break;
		}
		
		default:;
	}

	sp->Type = ID_RPDCON_IRATRUP_INUSE_Unrecognized;
}

void SETPRESENT_TRPDCON_IRATOMP_INCFG_Data (TRPDCON_IRATOMP_INCFG_Data* sp, TRPDCON_IRATOMP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TRPDCON_IRATOMP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_RPDCON_IRATOMP_INCFG_RPDCON_IRATOMP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest = (c_RPDCON_IRATOMP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_RPDCON_IRATOMP_INCFG_ConfigurationRequest));
			INIT_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest (sp->Data.fld_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_RPDCON_IRATOMP_INCFG_RPDCON_IRATOMP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse = (c_RPDCON_IRATOMP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_RPDCON_IRATOMP_INCFG_ConfigurationResponse));
			INIT_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse (sp->Data.fld_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TRPDCON_IRATOMP_INCFG_Data (TRPDCON_IRATOMP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_RPDCON_IRATOMP_INCFG_RPDCON_IRATOMP_INCFG_ConfigurationRequest: {
			FREE_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest (sp->Data.fld_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_RPDCON_IRATOMP_INCFG_RPDCON_IRATOMP_INCFG_ConfigurationResponse: {
			FREE_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse (sp->Data.fld_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_RPDCON_IRATOMP_INCFG_Unrecognized;
}

void SETPRESENT_TRPDCON_IRATOMP_INUSE_Data (TRPDCON_IRATOMP_INUSE_Data* sp, TRPDCON_IRATOMP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TRPDCON_IRATOMP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_RPDCON_IRATOMP_INUSE_RPDCON_IRATOMP_INUSE_QuickConfig: {
			sp->Data.fld_c_RPDCON_IRATOMP_INUSE_QuickConfig = (c_RPDCON_IRATOMP_INUSE_QuickConfig*)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_QuickConfig));
			INIT_c_RPDCON_IRATOMP_INUSE_QuickConfig (sp->Data.fld_c_RPDCON_IRATOMP_INUSE_QuickConfig);
			break;
		}
		
		case ID_RPDCON_IRATOMP_INUSE_RPDCON_IRATOMP_INUSE_SectorParameters: {
			sp->Data.fld_c_RPDCON_IRATOMP_INUSE_SectorParameters = (c_RPDCON_IRATOMP_INUSE_SectorParameters*)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters));
			INIT_c_RPDCON_IRATOMP_INUSE_SectorParameters (sp->Data.fld_c_RPDCON_IRATOMP_INUSE_SectorParameters);
			break;
		}
		
		case ID_RPDCON_IRATOMP_INUSE_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters: {
			sp->Data.fld_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters = (c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters*)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters));
			INIT_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters (sp->Data.fld_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters);
			break;
		}
		
		case ID_RPDCON_IRATOMP_INUSE_RPDCON_IRATOMP_INUSE_OtherRATNeighborList: {
			sp->Data.fld_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList = (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList*)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList));
			INIT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList (sp->Data.fld_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList);
			break;
		}
		
		default:;
	}
}

void FREE_TRPDCON_IRATOMP_INUSE_Data (TRPDCON_IRATOMP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_RPDCON_IRATOMP_INUSE_RPDCON_IRATOMP_INUSE_QuickConfig: {
			FREE_c_RPDCON_IRATOMP_INUSE_QuickConfig (sp->Data.fld_c_RPDCON_IRATOMP_INUSE_QuickConfig);
	EDFree (sp->Data.fld_c_RPDCON_IRATOMP_INUSE_QuickConfig );
			break;
		}
		
		case ID_RPDCON_IRATOMP_INUSE_RPDCON_IRATOMP_INUSE_SectorParameters: {
			FREE_c_RPDCON_IRATOMP_INUSE_SectorParameters (sp->Data.fld_c_RPDCON_IRATOMP_INUSE_SectorParameters);
	EDFree (sp->Data.fld_c_RPDCON_IRATOMP_INUSE_SectorParameters );
			break;
		}
		
		case ID_RPDCON_IRATOMP_INUSE_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters: {
			FREE_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters (sp->Data.fld_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters);
	EDFree (sp->Data.fld_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters );
			break;
		}
		
		case ID_RPDCON_IRATOMP_INUSE_RPDCON_IRATOMP_INUSE_OtherRATNeighborList: {
			FREE_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList (sp->Data.fld_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList);
	EDFree (sp->Data.fld_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList );
			break;
		}
		
		default:;
	}

	sp->Type = ID_RPDCON_IRATOMP_INUSE_Unrecognized;
}

void SETPRESENT_TRPDCON_DSAP_INCFG_Data (TRPDCON_DSAP_INCFG_Data* sp, TRPDCON_DSAP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TRPDCON_DSAP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_RPDCON_DSAP_INCFG_RPDCON_DSAP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_RPDCON_DSAP_INCFG_ConfigurationRequest = (c_RPDCON_DSAP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_RPDCON_DSAP_INCFG_ConfigurationRequest));
			INIT_c_RPDCON_DSAP_INCFG_ConfigurationRequest (sp->Data.fld_c_RPDCON_DSAP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_RPDCON_DSAP_INCFG_RPDCON_DSAP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_RPDCON_DSAP_INCFG_ConfigurationResponse = (c_RPDCON_DSAP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_RPDCON_DSAP_INCFG_ConfigurationResponse));
			INIT_c_RPDCON_DSAP_INCFG_ConfigurationResponse (sp->Data.fld_c_RPDCON_DSAP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TRPDCON_DSAP_INCFG_Data (TRPDCON_DSAP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_RPDCON_DSAP_INCFG_RPDCON_DSAP_INCFG_ConfigurationRequest: {
			FREE_c_RPDCON_DSAP_INCFG_ConfigurationRequest (sp->Data.fld_c_RPDCON_DSAP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_RPDCON_DSAP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_RPDCON_DSAP_INCFG_RPDCON_DSAP_INCFG_ConfigurationResponse: {
			FREE_c_RPDCON_DSAP_INCFG_ConfigurationResponse (sp->Data.fld_c_RPDCON_DSAP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_RPDCON_DSAP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_RPDCON_DSAP_INCFG_Unrecognized;
}

void SETPRESENT_TRPDCON_IRATQISP_INCFG_Data (TRPDCON_IRATQISP_INCFG_Data* sp, TRPDCON_IRATQISP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TRPDCON_IRATQISP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_RPDCON_IRATQISP_INCFG_RPDCON_IRATQISP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest = (c_RPDCON_IRATQISP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_RPDCON_IRATQISP_INCFG_ConfigurationRequest));
			INIT_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest (sp->Data.fld_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_RPDCON_IRATQISP_INCFG_RPDCON_IRATQISP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse = (c_RPDCON_IRATQISP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_RPDCON_IRATQISP_INCFG_ConfigurationResponse));
			INIT_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse (sp->Data.fld_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TRPDCON_IRATQISP_INCFG_Data (TRPDCON_IRATQISP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_RPDCON_IRATQISP_INCFG_RPDCON_IRATQISP_INCFG_ConfigurationRequest: {
			FREE_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest (sp->Data.fld_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_RPDCON_IRATQISP_INCFG_RPDCON_IRATQISP_INCFG_ConfigurationResponse: {
			FREE_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse (sp->Data.fld_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_RPDCON_IRATQISP_INCFG_Unrecognized;
}

void SETPRESENT_TRPDCON_IRATQISP_INUSE_Data (TRPDCON_IRATQISP_INUSE_Data* sp, TRPDCON_IRATQISP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TRPDCON_IRATQISP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_Page: {
			sp->Data.fld_c_RPDCON_IRATQISP_INUSE_Page = (c_RPDCON_IRATQISP_INUSE_Page*)EDAlloc (sizeof (c_RPDCON_IRATQISP_INUSE_Page));
			INIT_c_RPDCON_IRATQISP_INUSE_Page (sp->Data.fld_c_RPDCON_IRATQISP_INUSE_Page);
			break;
		}
		
		case ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_ConnectionRequest: {
			sp->Data.fld_c_RPDCON_IRATQISP_INUSE_ConnectionRequest = (c_RPDCON_IRATQISP_INUSE_ConnectionRequest*)EDAlloc (sizeof (c_RPDCON_IRATQISP_INUSE_ConnectionRequest));
			INIT_c_RPDCON_IRATQISP_INUSE_ConnectionRequest (sp->Data.fld_c_RPDCON_IRATQISP_INUSE_ConnectionRequest);
			break;
		}
		
		case ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_ConnectionDeny: {
			sp->Data.fld_c_RPDCON_IRATQISP_INUSE_ConnectionDeny = (c_RPDCON_IRATQISP_INUSE_ConnectionDeny*)EDAlloc (sizeof (c_RPDCON_IRATQISP_INUSE_ConnectionDeny));
			INIT_c_RPDCON_IRATQISP_INUSE_ConnectionDeny (sp->Data.fld_c_RPDCON_IRATQISP_INUSE_ConnectionDeny);
			break;
		}
		
		case ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_QuickPage: {
			sp->Data.fld_c_RPDCON_IRATQISP_INUSE_QuickPage = (c_RPDCON_IRATQISP_INUSE_QuickPage*)EDAlloc (sizeof (c_RPDCON_IRATQISP_INUSE_QuickPage));
			INIT_c_RPDCON_IRATQISP_INUSE_QuickPage (sp->Data.fld_c_RPDCON_IRATQISP_INUSE_QuickPage);
			break;
		}
		
		case ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest: {
			sp->Data.fld_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest = (c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest*)EDAlloc (sizeof (c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest));
			INIT_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest);
			break;
		}
		
		case ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept: {
			sp->Data.fld_c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept = (c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept*)EDAlloc (sizeof (c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept));
			INIT_c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept);
			break;
		}
		
		case ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_AttributeUpdateReject: {
			sp->Data.fld_c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject = (c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject*)EDAlloc (sizeof (c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject));
			INIT_c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject (sp->Data.fld_c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject);
			break;
		}
		
		default:;
	}
}

void FREE_TRPDCON_IRATQISP_INUSE_Data (TRPDCON_IRATQISP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_Page: {
			FREE_c_RPDCON_IRATQISP_INUSE_Page (sp->Data.fld_c_RPDCON_IRATQISP_INUSE_Page);
	EDFree (sp->Data.fld_c_RPDCON_IRATQISP_INUSE_Page );
			break;
		}
		
		case ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_ConnectionRequest: {
			FREE_c_RPDCON_IRATQISP_INUSE_ConnectionRequest (sp->Data.fld_c_RPDCON_IRATQISP_INUSE_ConnectionRequest);
	EDFree (sp->Data.fld_c_RPDCON_IRATQISP_INUSE_ConnectionRequest );
			break;
		}
		
		case ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_ConnectionDeny: {
			FREE_c_RPDCON_IRATQISP_INUSE_ConnectionDeny (sp->Data.fld_c_RPDCON_IRATQISP_INUSE_ConnectionDeny);
	EDFree (sp->Data.fld_c_RPDCON_IRATQISP_INUSE_ConnectionDeny );
			break;
		}
		
		case ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_QuickPage: {
			FREE_c_RPDCON_IRATQISP_INUSE_QuickPage (sp->Data.fld_c_RPDCON_IRATQISP_INUSE_QuickPage);
	EDFree (sp->Data.fld_c_RPDCON_IRATQISP_INUSE_QuickPage );
			break;
		}
		
		case ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest: {
			FREE_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest);
	EDFree (sp->Data.fld_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest );
			break;
		}
		
		case ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept: {
			FREE_c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept);
	EDFree (sp->Data.fld_c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept );
			break;
		}
		
		case ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_AttributeUpdateReject: {
			FREE_c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject (sp->Data.fld_c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject);
	EDFree (sp->Data.fld_c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject );
			break;
		}
		
		default:;
	}

	sp->Type = ID_RPDCON_IRATQISP_INUSE_Unrecognized;
}

void SETPRESENT_TRPDCON_S1IRATRUP_INCFG_Data (TRPDCON_S1IRATRUP_INCFG_Data* sp, TRPDCON_S1IRATRUP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TRPDCON_S1IRATRUP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_RPDCON_S1IRATRUP_INCFG_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest = (c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest));
			INIT_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest (sp->Data.fld_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_RPDCON_S1IRATRUP_INCFG_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse = (c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse));
			INIT_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse (sp->Data.fld_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TRPDCON_S1IRATRUP_INCFG_Data (TRPDCON_S1IRATRUP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_RPDCON_S1IRATRUP_INCFG_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest: {
			FREE_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest (sp->Data.fld_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_RPDCON_S1IRATRUP_INCFG_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse: {
			FREE_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse (sp->Data.fld_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_RPDCON_S1IRATRUP_INCFG_Unrecognized;
}

void SETPRESENT_TRPDCON_S1IRATRUP_INUSE_Data (TRPDCON_S1IRATRUP_INUSE_Data* sp, TRPDCON_S1IRATRUP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TRPDCON_S1IRATRUP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_RouteUpdate: {
			sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate = (c_RPDCON_S1IRATRUP_INUSE_RouteUpdate*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_RouteUpdate));
			INIT_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate (sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate);
			break;
		}
		
		case ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment: {
			sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment = (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment));
			INIT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment (sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment);
			break;
		}
		
		case ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete: {
			sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete = (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete));
			INIT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete (sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete);
			break;
		}
		
		case ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_ResetReport: {
			sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_ResetReport = (c_RPDCON_S1IRATRUP_INUSE_ResetReport*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_ResetReport));
			INIT_c_RPDCON_S1IRATRUP_INUSE_ResetReport (sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_ResetReport);
			break;
		}
		
		case ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_NeighborList: {
			sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_NeighborList = (c_RPDCON_S1IRATRUP_INUSE_NeighborList*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_NeighborList));
			INIT_c_RPDCON_S1IRATRUP_INUSE_NeighborList (sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_NeighborList);
			break;
		}
		
		case ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest: {
			sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest = (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest));
			INIT_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest (sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest);
			break;
		}
		
		case ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest: {
			sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest = (c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest));
			INIT_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest);
			break;
		}
		
		case ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept: {
			sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept = (c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept));
			INIT_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept);
			break;
		}
		
		case ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject: {
			sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject = (c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject));
			INIT_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject (sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject);
			break;
		}
		
		default:;
	}
}

void FREE_TRPDCON_S1IRATRUP_INUSE_Data (TRPDCON_S1IRATRUP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_RouteUpdate: {
			FREE_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate (sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate);
	EDFree (sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate );
			break;
		}
		
		case ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment: {
			FREE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment (sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment);
	EDFree (sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment );
			break;
		}
		
		case ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete: {
			FREE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete (sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete);
	EDFree (sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete );
			break;
		}
		
		case ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_ResetReport: {
			FREE_c_RPDCON_S1IRATRUP_INUSE_ResetReport (sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_ResetReport);
	EDFree (sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_ResetReport );
			break;
		}
		
		case ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_NeighborList: {
			FREE_c_RPDCON_S1IRATRUP_INUSE_NeighborList (sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_NeighborList);
	EDFree (sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_NeighborList );
			break;
		}
		
		case ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest: {
			FREE_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest (sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest);
	EDFree (sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest );
			break;
		}
		
		case ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest: {
			FREE_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest);
	EDFree (sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest );
			break;
		}
		
		case ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept: {
			FREE_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept);
	EDFree (sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept );
			break;
		}
		
		case ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject: {
			FREE_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject (sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject);
	EDFree (sp->Data.fld_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject );
			break;
		}
		
		default:;
	}

	sp->Type = ID_RPDCON_S1IRATRUP_INUSE_Unrecognized;
}

void SETPRESENT_TRPDCON_IRATOMPCS0024B_INCFG_Data (TRPDCON_IRATOMPCS0024B_INCFG_Data* sp, TRPDCON_IRATOMPCS0024B_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TRPDCON_IRATOMPCS0024B_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_RPDCON_IRATOMPCS0024B_INCFG_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest = (c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest));
			INIT_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest (sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_RPDCON_IRATOMPCS0024B_INCFG_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse = (c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse));
			INIT_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse (sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TRPDCON_IRATOMPCS0024B_INCFG_Data (TRPDCON_IRATOMPCS0024B_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_RPDCON_IRATOMPCS0024B_INCFG_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest: {
			FREE_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest (sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_RPDCON_IRATOMPCS0024B_INCFG_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse: {
			FREE_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse (sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_RPDCON_IRATOMPCS0024B_INCFG_Unrecognized;
}

void SETPRESENT_TRPDCON_IRATOMPCS0024B_INUSE_Data (TRPDCON_IRATOMPCS0024B_INUSE_Data* sp, TRPDCON_IRATOMPCS0024B_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TRPDCON_IRATOMPCS0024B_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig: {
			sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig = (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig));
			INIT_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig (sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig);
			break;
		}
		
		case ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters: {
			sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters = (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters));
			INIT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters (sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters);
			break;
		}
		
		case ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters: {
			sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters = (c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters));
			INIT_c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters (sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters);
			break;
		}
		
		case ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList: {
			sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList = (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList));
			INIT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList (sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList);
			break;
		}
		
		case ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation: {
			sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation = (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation));
			INIT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation (sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation);
			break;
		}
		
		case ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification: {
			sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification = (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification));
			INIT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification (sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification);
			break;
		}
		
		case ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText: {
			sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText = (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText));
			INIT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText (sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText);
			break;
		}
		
		default:;
	}
}

void FREE_TRPDCON_IRATOMPCS0024B_INUSE_Data (TRPDCON_IRATOMPCS0024B_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig: {
			FREE_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig (sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig);
	EDFree (sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig );
			break;
		}
		
		case ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters: {
			FREE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters (sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters);
	EDFree (sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters );
			break;
		}
		
		case ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters: {
			FREE_c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters (sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters);
	EDFree (sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters );
			break;
		}
		
		case ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList: {
			FREE_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList (sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList);
	EDFree (sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList );
			break;
		}
		
		case ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation: {
			FREE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation (sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation);
	EDFree (sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation );
			break;
		}
		
		case ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification: {
			FREE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification (sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification);
	EDFree (sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification );
			break;
		}
		
		case ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText: {
			FREE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText (sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText);
	EDFree (sp->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText );
			break;
		}
		
		default:;
	}

	sp->Type = ID_RPDCON_IRATOMPCS0024B_INUSE_Unrecognized;
}

void SETPRESENT_TRPDRAT_ATS3RTCMACPR_Data (TRPDRAT_ATS3RTCMACPR_Data* sp, TRPDRAT_ATS3RTCMACPR_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TRPDRAT_ATS3RTCMACPR_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_RPDRAT_ATS3RTCMACPR_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters: {
			sp->Data.fld_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters = (c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters*)EDAlloc (sizeof (c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters));
			INIT_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters (sp->Data.fld_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters);
			break;
		}
		
		default:;
	}
}

void FREE_TRPDRAT_ATS3RTCMACPR_Data (TRPDRAT_ATS3RTCMACPR_Data* sp)
{
	switch (sp->Type) {
		case ID_RPDRAT_ATS3RTCMACPR_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters: {
			FREE_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters (sp->Data.fld_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters);
	EDFree (sp->Data.fld_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters );
			break;
		}
		
		default:;
	}

	sp->Type = ID_RPDRAT_ATS3RTCMACPR_Unrecognized;
}

void SETPRESENT_TRPDRAT_ATS4RTCMACPR_Data (TRPDRAT_ATS4RTCMACPR_Data* sp, TRPDRAT_ATS4RTCMACPR_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TRPDRAT_ATS4RTCMACPR_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_RPDRAT_ATS4RTCMACPR_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters: {
			sp->Data.fld_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters = (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters*)EDAlloc (sizeof (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters));
			INIT_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters (sp->Data.fld_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters);
			break;
		}
		
		default:;
	}
}

void FREE_TRPDRAT_ATS4RTCMACPR_Data (TRPDRAT_ATS4RTCMACPR_Data* sp)
{
	switch (sp->Type) {
		case ID_RPDRAT_ATS4RTCMACPR_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters: {
			FREE_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters (sp->Data.fld_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters);
	EDFree (sp->Data.fld_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters );
			break;
		}
		
		default:;
	}

	sp->Type = ID_RPDRAT_ATS4RTCMACPR_Unrecognized;
}

#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_RPDCON_IRATINSP_INUSE (const char* buffer, TRPDCON_IRATINSP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = 0;
	
	/*-----------------------------------------------------------------
		Key is set to a single value containing protocol discriminator,
		skip indicator and message type.
		For example, message ASSIGNMENT_COMMAND has:
			skip indicator         = 0000 (0x0)
			protocol discriminator = 0110 (0x6)
			message type           = 00101110 (0x2E)
		In this case, key will be set to 0x602E.
		Skip indicator could be in some cases a transaction identifier.
		In such cases, it will be set to 0 for matching purposes.
	------------------------------------------------------------------*/
	unsigned /****/ int key /*1*/ = ((unsigned char)buffer [0])>> 6/*2*/;/*3*/
	data->MessageType = (int)((unsigned char)buffer [0]);
	
	ED_WARNING_REMOVER(key);
	switch (key & 0xFF03) {
			/* Detect signal RPDCON_IRATINSP_INUSE_Sync */
		case 0x0000: {
			SETPRESENT_TRPDCON_IRATINSP_INUSE_Data (data, ID_RPDCON_IRATINSP_INUSE_RPDCON_IRATINSP_INUSE_Sync);
			INIT_c_RPDCON_IRATINSP_INUSE_Sync (data->Data.fld_c_RPDCON_IRATINSP_INUSE_Sync);
			retLen = DECODE_c_RPDCON_IRATINSP_INUSE_Sync (buffer, 0, data->Data.fld_c_RPDCON_IRATINSP_INUSE_Sync, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_RPDCON_IRATINSP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_IRATINSP_INUSE (const char* buffer, int len, TRPDCON_IRATINSP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_RPDCON_IRATINSP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_RPDCON_IRATINSP_INUSE (char* buffer, ED_EXLONG bitOffset, TRPDCON_IRATINSP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_RPDCON_IRATINSP_INUSE_RPDCON_IRATINSP_INUSE_Sync: {
			retLen = ENCODE_c_RPDCON_IRATINSP_INUSE_Sync (buffer, 0, data->Data.fld_c_RPDCON_IRATINSP_INUSE_Sync, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_RPDSES_SL (const char* buffer, TRPDSES_SL_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = 0;
	
	/*-----------------------------------------------------------------
		Key is set to a single value containing protocol discriminator,
		skip indicator and message type.
		For example, message ASSIGNMENT_COMMAND has:
			skip indicator         = 0000 (0x0)
			protocol discriminator = 0110 (0x6)
			message type           = 00101110 (0x2E)
		In this case, key will be set to 0x602E.
		Skip indicator could be in some cases a transaction identifier.
		In such cases, it will be set to 0 for matching purposes.
	------------------------------------------------------------------*/
	unsigned /****/ int key /*1*/ = ((unsigned char)buffer [0])/*2*/;/*3*/
	data->MessageType = (int)((unsigned char)buffer [0]);
	
	ED_WARNING_REMOVER(key);
	switch (key) {
			/* Detect signal RPDSES_SL_UATIAssignment */
		case 0x0001: {
			SETPRESENT_TRPDSES_SL_Data (data, ID_RPDSES_SL_RPDSES_SL_UATIAssignment);
			INIT_c_RPDSES_SL_UATIAssignment (data->Data.fld_c_RPDSES_SL_UATIAssignment);
			retLen = DECODE_c_RPDSES_SL_UATIAssignment (buffer, 0, data->Data.fld_c_RPDSES_SL_UATIAssignment, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDSES_SL_InterRATMobilityIndication */
		case 0x0005: {
			SETPRESENT_TRPDSES_SL_Data (data, ID_RPDSES_SL_RPDSES_SL_InterRATMobilityIndication);
			INIT_c_RPDSES_SL_InterRATMobilityIndication (data->Data.fld_c_RPDSES_SL_InterRATMobilityIndication);
			retLen = DECODE_c_RPDSES_SL_InterRATMobilityIndication (buffer, 0, data->Data.fld_c_RPDSES_SL_InterRATMobilityIndication, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDSES_SL_InterRATMobilityAck */
		case 0x0006: {
			SETPRESENT_TRPDSES_SL_Data (data, ID_RPDSES_SL_RPDSES_SL_InterRATMobilityAck);
			INIT_c_RPDSES_SL_InterRATMobilityAck (data->Data.fld_c_RPDSES_SL_InterRATMobilityAck);
			retLen = DECODE_c_RPDSES_SL_InterRATMobilityAck (buffer, 0, data->Data.fld_c_RPDSES_SL_InterRATMobilityAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_RPDSES_SL_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDSES_SL (const char* buffer, int len, TRPDSES_SL_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_RPDSES_SL (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_RPDSES_SL (char* buffer, ED_EXLONG bitOffset, TRPDSES_SL_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_RPDSES_SL_RPDSES_SL_UATIAssignment: {
			retLen = ENCODE_c_RPDSES_SL_UATIAssignment (buffer, 0, data->Data.fld_c_RPDSES_SL_UATIAssignment, pCSN1CContextSet);
			break;
		}
		case ID_RPDSES_SL_RPDSES_SL_InterRATMobilityIndication: {
			retLen = ENCODE_c_RPDSES_SL_InterRATMobilityIndication (buffer, 0, data->Data.fld_c_RPDSES_SL_InterRATMobilityIndication, pCSN1CContextSet);
			break;
		}
		case ID_RPDSES_SL_RPDSES_SL_InterRATMobilityAck: {
			retLen = ENCODE_c_RPDSES_SL_InterRATMobilityAck (buffer, 0, data->Data.fld_c_RPDSES_SL_InterRATMobilityAck, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_RPDCON_IRATSAP_INCFG (const char* buffer, TRPDCON_IRATSAP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = 0;
	
	/*-----------------------------------------------------------------
		Key is set to a single value containing protocol discriminator,
		skip indicator and message type.
		For example, message ASSIGNMENT_COMMAND has:
			skip indicator         = 0000 (0x0)
			protocol discriminator = 0110 (0x6)
			message type           = 00101110 (0x2E)
		In this case, key will be set to 0x602E.
		Skip indicator could be in some cases a transaction identifier.
		In such cases, it will be set to 0 for matching purposes.
	------------------------------------------------------------------*/
	unsigned /****/ int key /*1*/ = ((unsigned char)buffer [0])/*2*/;/*3*/
	data->MessageType = (int)((unsigned char)buffer [0]);
	
	ED_WARNING_REMOVER(key);
	switch (key) {
			/* Detect signal RPDCON_IRATSAP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TRPDCON_IRATSAP_INCFG_Data (data, ID_RPDCON_IRATSAP_INCFG_RPDCON_IRATSAP_INCFG_ConfigurationRequest);
			INIT_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest (data->Data.fld_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATSAP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TRPDCON_IRATSAP_INCFG_Data (data, ID_RPDCON_IRATSAP_INCFG_RPDCON_IRATSAP_INCFG_ConfigurationResponse);
			INIT_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse (data->Data.fld_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_RPDCON_IRATSAP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_IRATSAP_INCFG (const char* buffer, int len, TRPDCON_IRATSAP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_RPDCON_IRATSAP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_RPDCON_IRATSAP_INCFG (char* buffer, ED_EXLONG bitOffset, TRPDCON_IRATSAP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_RPDCON_IRATSAP_INCFG_RPDCON_IRATSAP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATSAP_INCFG_RPDCON_IRATSAP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_RPDCON_IRATSAP_INUSE (const char* buffer, TRPDCON_IRATSAP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = 0;
	
	/*-----------------------------------------------------------------
		Key is set to a single value containing protocol discriminator,
		skip indicator and message type.
		For example, message ASSIGNMENT_COMMAND has:
			skip indicator         = 0000 (0x0)
			protocol discriminator = 0110 (0x6)
			message type           = 00101110 (0x2E)
		In this case, key will be set to 0x602E.
		Skip indicator could be in some cases a transaction identifier.
		In such cases, it will be set to 0 for matching purposes.
	------------------------------------------------------------------*/
	unsigned /****/ int key /*1*/ = ((unsigned char)buffer [0])/*2*/;/*3*/
	data->MessageType = (int)((unsigned char)buffer [0]);
	
	ED_WARNING_REMOVER(key);
	switch (key) {
			/* Detect signal RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq */
		case 0x0000: {
			SETPRESENT_TRPDCON_IRATSAP_INUSE_Data (data, ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq);
			INIT_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq (data->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq);
			retLen = DECODE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq (buffer, 0, data->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf */
		case 0x0001: {
			SETPRESENT_TRPDCON_IRATSAP_INUSE_Data (data, ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf);
			INIT_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf (data->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf);
			retLen = DECODE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf (buffer, 0, data->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail */
		case 0x0002: {
			SETPRESENT_TRPDCON_IRATSAP_INUSE_Data (data, ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail);
			INIT_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail (data->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail);
			retLen = DECODE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail (buffer, 0, data->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq */
		case 0x0003: {
			SETPRESENT_TRPDCON_IRATSAP_INUSE_Data (data, ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq);
			INIT_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq (data->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq);
			retLen = DECODE_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq (buffer, 0, data->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf */
		case 0x0004: {
			SETPRESENT_TRPDCON_IRATSAP_INUSE_Data (data, ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf);
			INIT_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf (data->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf);
			retLen = DECODE_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf (buffer, 0, data->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATSAP_INUSE_AlternateLinkPageReq */
		case 0x0005: {
			SETPRESENT_TRPDCON_IRATSAP_INUSE_Data (data, ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq);
			INIT_c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq (data->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq);
			retLen = DECODE_c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq (buffer, 0, data->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete */
		case 0x0006: {
			SETPRESENT_TRPDCON_IRATSAP_INUSE_Data (data, ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete);
			INIT_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete (data->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete);
			retLen = DECODE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete (buffer, 0, data->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_RPDCON_IRATSAP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_IRATSAP_INUSE (const char* buffer, int len, TRPDCON_IRATSAP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_RPDCON_IRATSAP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_RPDCON_IRATSAP_INUSE (char* buffer, ED_EXLONG bitOffset, TRPDCON_IRATSAP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq: {
			retLen = ENCODE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq (buffer, 0, data->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf: {
			retLen = ENCODE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf (buffer, 0, data->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail: {
			retLen = ENCODE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail (buffer, 0, data->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq: {
			retLen = ENCODE_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq (buffer, 0, data->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf: {
			retLen = ENCODE_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf (buffer, 0, data->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq: {
			retLen = ENCODE_c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq (buffer, 0, data->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATSAP_INUSE_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete: {
			retLen = ENCODE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete (buffer, 0, data->Data.fld_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_RPDCON_IRATINSP_INCFG (const char* buffer, TRPDCON_IRATINSP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = 0;
	
	/*-----------------------------------------------------------------
		Key is set to a single value containing protocol discriminator,
		skip indicator and message type.
		For example, message ASSIGNMENT_COMMAND has:
			skip indicator         = 0000 (0x0)
			protocol discriminator = 0110 (0x6)
			message type           = 00101110 (0x2E)
		In this case, key will be set to 0x602E.
		Skip indicator could be in some cases a transaction identifier.
		In such cases, it will be set to 0 for matching purposes.
	------------------------------------------------------------------*/
	unsigned /****/ int key /*1*/ = ((unsigned char)buffer [0])/*2*/;/*3*/
	data->MessageType = (int)((unsigned char)buffer [0]);
	
	ED_WARNING_REMOVER(key);
	switch (key) {
			/* Detect signal RPDCON_IRATINSP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TRPDCON_IRATINSP_INCFG_Data (data, ID_RPDCON_IRATINSP_INCFG_RPDCON_IRATINSP_INCFG_ConfigurationRequest);
			INIT_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest (data->Data.fld_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATINSP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TRPDCON_IRATINSP_INCFG_Data (data, ID_RPDCON_IRATINSP_INCFG_RPDCON_IRATINSP_INCFG_ConfigurationResponse);
			INIT_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse (data->Data.fld_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_RPDCON_IRATINSP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_IRATINSP_INCFG (const char* buffer, int len, TRPDCON_IRATINSP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_RPDCON_IRATINSP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_RPDCON_IRATINSP_INCFG (char* buffer, ED_EXLONG bitOffset, TRPDCON_IRATINSP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_RPDCON_IRATINSP_INCFG_RPDCON_IRATINSP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATINSP_INCFG_RPDCON_IRATINSP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_RPDCON_IRATISP_INCFG (const char* buffer, TRPDCON_IRATISP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = 0;
	
	/*-----------------------------------------------------------------
		Key is set to a single value containing protocol discriminator,
		skip indicator and message type.
		For example, message ASSIGNMENT_COMMAND has:
			skip indicator         = 0000 (0x0)
			protocol discriminator = 0110 (0x6)
			message type           = 00101110 (0x2E)
		In this case, key will be set to 0x602E.
		Skip indicator could be in some cases a transaction identifier.
		In such cases, it will be set to 0 for matching purposes.
	------------------------------------------------------------------*/
	unsigned /****/ int key /*1*/ = ((unsigned char)buffer [0])/*2*/;/*3*/
	data->MessageType = (int)((unsigned char)buffer [0]);
	
	ED_WARNING_REMOVER(key);
	switch (key) {
			/* Detect signal RPDCON_IRATISP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TRPDCON_IRATISP_INCFG_Data (data, ID_RPDCON_IRATISP_INCFG_RPDCON_IRATISP_INCFG_ConfigurationRequest);
			INIT_c_RPDCON_IRATISP_INCFG_ConfigurationRequest (data->Data.fld_c_RPDCON_IRATISP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_RPDCON_IRATISP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_RPDCON_IRATISP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATISP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TRPDCON_IRATISP_INCFG_Data (data, ID_RPDCON_IRATISP_INCFG_RPDCON_IRATISP_INCFG_ConfigurationResponse);
			INIT_c_RPDCON_IRATISP_INCFG_ConfigurationResponse (data->Data.fld_c_RPDCON_IRATISP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_RPDCON_IRATISP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_RPDCON_IRATISP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_RPDCON_IRATISP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_IRATISP_INCFG (const char* buffer, int len, TRPDCON_IRATISP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_RPDCON_IRATISP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_RPDCON_IRATISP_INCFG (char* buffer, ED_EXLONG bitOffset, TRPDCON_IRATISP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_RPDCON_IRATISP_INCFG_RPDCON_IRATISP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_RPDCON_IRATISP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_RPDCON_IRATISP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATISP_INCFG_RPDCON_IRATISP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_RPDCON_IRATISP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_RPDCON_IRATISP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_RPDCON_IRATISP_INUSE (const char* buffer, TRPDCON_IRATISP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = 0;
	
	/*-----------------------------------------------------------------
		Key is set to a single value containing protocol discriminator,
		skip indicator and message type.
		For example, message ASSIGNMENT_COMMAND has:
			skip indicator         = 0000 (0x0)
			protocol discriminator = 0110 (0x6)
			message type           = 00101110 (0x2E)
		In this case, key will be set to 0x602E.
		Skip indicator could be in some cases a transaction identifier.
		In such cases, it will be set to 0 for matching purposes.
	------------------------------------------------------------------*/
	unsigned /****/ int key /*1*/ = ((unsigned char)buffer [0])/*2*/;/*3*/
	data->MessageType = (int)((unsigned char)buffer [0]);
	
	ED_WARNING_REMOVER(key);
	switch (key) {
			/* Detect signal RPDCON_IRATISP_INUSE_Page */
		case 0x0000: {
			SETPRESENT_TRPDCON_IRATISP_INUSE_Data (data, ID_RPDCON_IRATISP_INUSE_RPDCON_IRATISP_INUSE_Page);
			INIT_c_RPDCON_IRATISP_INUSE_Page (data->Data.fld_c_RPDCON_IRATISP_INUSE_Page);
			retLen = DECODE_c_RPDCON_IRATISP_INUSE_Page (buffer, 0, data->Data.fld_c_RPDCON_IRATISP_INUSE_Page, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATISP_INUSE_ConnectionRequest */
		case 0x0001: {
			SETPRESENT_TRPDCON_IRATISP_INUSE_Data (data, ID_RPDCON_IRATISP_INUSE_RPDCON_IRATISP_INUSE_ConnectionRequest);
			INIT_c_RPDCON_IRATISP_INUSE_ConnectionRequest (data->Data.fld_c_RPDCON_IRATISP_INUSE_ConnectionRequest);
			retLen = DECODE_c_RPDCON_IRATISP_INUSE_ConnectionRequest (buffer, 0, data->Data.fld_c_RPDCON_IRATISP_INUSE_ConnectionRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATISP_INUSE_ConnectionDeny */
		case 0x0002: {
			SETPRESENT_TRPDCON_IRATISP_INUSE_Data (data, ID_RPDCON_IRATISP_INUSE_RPDCON_IRATISP_INUSE_ConnectionDeny);
			INIT_c_RPDCON_IRATISP_INUSE_ConnectionDeny (data->Data.fld_c_RPDCON_IRATISP_INUSE_ConnectionDeny);
			retLen = DECODE_c_RPDCON_IRATISP_INUSE_ConnectionDeny (buffer, 0, data->Data.fld_c_RPDCON_IRATISP_INUSE_ConnectionDeny, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATISP_INUSE_AttributeUpdateRequest */
		case 0x0052: {
			SETPRESENT_TRPDCON_IRATISP_INUSE_Data (data, ID_RPDCON_IRATISP_INUSE_RPDCON_IRATISP_INUSE_AttributeUpdateRequest);
			INIT_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest (data->Data.fld_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest);
			retLen = DECODE_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATISP_INUSE_AttributeUpdateAccept */
		case 0x0053: {
			SETPRESENT_TRPDCON_IRATISP_INUSE_Data (data, ID_RPDCON_IRATISP_INUSE_RPDCON_IRATISP_INUSE_AttributeUpdateAccept);
			INIT_c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept (data->Data.fld_c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept);
			retLen = DECODE_c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATISP_INUSE_AttributeUpdateReject */
		case 0x0054: {
			SETPRESENT_TRPDCON_IRATISP_INUSE_Data (data, ID_RPDCON_IRATISP_INUSE_RPDCON_IRATISP_INUSE_AttributeUpdateReject);
			INIT_c_RPDCON_IRATISP_INUSE_AttributeUpdateReject (data->Data.fld_c_RPDCON_IRATISP_INUSE_AttributeUpdateReject);
			retLen = DECODE_c_RPDCON_IRATISP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_RPDCON_IRATISP_INUSE_AttributeUpdateReject, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_RPDCON_IRATISP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_IRATISP_INUSE (const char* buffer, int len, TRPDCON_IRATISP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_RPDCON_IRATISP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_RPDCON_IRATISP_INUSE (char* buffer, ED_EXLONG bitOffset, TRPDCON_IRATISP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_RPDCON_IRATISP_INUSE_RPDCON_IRATISP_INUSE_Page: {
			retLen = ENCODE_c_RPDCON_IRATISP_INUSE_Page (buffer, 0, data->Data.fld_c_RPDCON_IRATISP_INUSE_Page, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATISP_INUSE_RPDCON_IRATISP_INUSE_ConnectionRequest: {
			retLen = ENCODE_c_RPDCON_IRATISP_INUSE_ConnectionRequest (buffer, 0, data->Data.fld_c_RPDCON_IRATISP_INUSE_ConnectionRequest, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATISP_INUSE_RPDCON_IRATISP_INUSE_ConnectionDeny: {
			retLen = ENCODE_c_RPDCON_IRATISP_INUSE_ConnectionDeny (buffer, 0, data->Data.fld_c_RPDCON_IRATISP_INUSE_ConnectionDeny, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATISP_INUSE_RPDCON_IRATISP_INUSE_AttributeUpdateRequest: {
			retLen = ENCODE_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATISP_INUSE_RPDCON_IRATISP_INUSE_AttributeUpdateAccept: {
			retLen = ENCODE_c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATISP_INUSE_RPDCON_IRATISP_INUSE_AttributeUpdateReject: {
			retLen = ENCODE_c_RPDCON_IRATISP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_RPDCON_IRATISP_INUSE_AttributeUpdateReject, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_RPDCON_IRATRUP_INCFG (const char* buffer, TRPDCON_IRATRUP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = 0;
	
	/*-----------------------------------------------------------------
		Key is set to a single value containing protocol discriminator,
		skip indicator and message type.
		For example, message ASSIGNMENT_COMMAND has:
			skip indicator         = 0000 (0x0)
			protocol discriminator = 0110 (0x6)
			message type           = 00101110 (0x2E)
		In this case, key will be set to 0x602E.
		Skip indicator could be in some cases a transaction identifier.
		In such cases, it will be set to 0 for matching purposes.
	------------------------------------------------------------------*/
	unsigned /****/ int key /*1*/ = ((unsigned char)buffer [0])/*2*/;/*3*/
	data->MessageType = (int)((unsigned char)buffer [0]);
	
	ED_WARNING_REMOVER(key);
	switch (key) {
			/* Detect signal RPDCON_IRATRUP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TRPDCON_IRATRUP_INCFG_Data (data, ID_RPDCON_IRATRUP_INCFG_RPDCON_IRATRUP_INCFG_ConfigurationRequest);
			INIT_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest (data->Data.fld_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATRUP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TRPDCON_IRATRUP_INCFG_Data (data, ID_RPDCON_IRATRUP_INCFG_RPDCON_IRATRUP_INCFG_ConfigurationResponse);
			INIT_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse (data->Data.fld_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_RPDCON_IRATRUP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_IRATRUP_INCFG (const char* buffer, int len, TRPDCON_IRATRUP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_RPDCON_IRATRUP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_RPDCON_IRATRUP_INCFG (char* buffer, ED_EXLONG bitOffset, TRPDCON_IRATRUP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_RPDCON_IRATRUP_INCFG_RPDCON_IRATRUP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATRUP_INCFG_RPDCON_IRATRUP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_RPDCON_IRATRUP_INUSE (const char* buffer, TRPDCON_IRATRUP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = 0;
	
	/*-----------------------------------------------------------------
		Key is set to a single value containing protocol discriminator,
		skip indicator and message type.
		For example, message ASSIGNMENT_COMMAND has:
			skip indicator         = 0000 (0x0)
			protocol discriminator = 0110 (0x6)
			message type           = 00101110 (0x2E)
		In this case, key will be set to 0x602E.
		Skip indicator could be in some cases a transaction identifier.
		In such cases, it will be set to 0 for matching purposes.
	------------------------------------------------------------------*/
	unsigned /****/ int key /*1*/ = ((unsigned char)buffer [0])/*2*/;/*3*/
	data->MessageType = (int)((unsigned char)buffer [0]);
	
	ED_WARNING_REMOVER(key);
	switch (key) {
			/* Detect signal RPDCON_IRATRUP_INUSE_RouteUpdate */
		case 0x0000: {
			SETPRESENT_TRPDCON_IRATRUP_INUSE_Data (data, ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_RouteUpdate);
			INIT_c_RPDCON_IRATRUP_INUSE_RouteUpdate (data->Data.fld_c_RPDCON_IRATRUP_INUSE_RouteUpdate);
			retLen = DECODE_c_RPDCON_IRATRUP_INUSE_RouteUpdate (buffer, 0, data->Data.fld_c_RPDCON_IRATRUP_INUSE_RouteUpdate, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATRUP_INUSE_TrafficChannelAssignment */
		case 0x0001: {
			SETPRESENT_TRPDCON_IRATRUP_INUSE_Data (data, ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment);
			INIT_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment (data->Data.fld_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment);
			retLen = DECODE_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment (buffer, 0, data->Data.fld_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATRUP_INUSE_TrafficChannelComplete */
		case 0x0002: {
			SETPRESENT_TRPDCON_IRATRUP_INUSE_Data (data, ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_TrafficChannelComplete);
			INIT_c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete (data->Data.fld_c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete);
			retLen = DECODE_c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete (buffer, 0, data->Data.fld_c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATRUP_INUSE_ResetReport */
		case 0x0003: {
			SETPRESENT_TRPDCON_IRATRUP_INUSE_Data (data, ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_ResetReport);
			INIT_c_RPDCON_IRATRUP_INUSE_ResetReport (data->Data.fld_c_RPDCON_IRATRUP_INUSE_ResetReport);
			retLen = DECODE_c_RPDCON_IRATRUP_INUSE_ResetReport (buffer, 0, data->Data.fld_c_RPDCON_IRATRUP_INUSE_ResetReport, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATRUP_INUSE_NeighborList */
		case 0x0004: {
			SETPRESENT_TRPDCON_IRATRUP_INUSE_Data (data, ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_NeighborList);
			INIT_c_RPDCON_IRATRUP_INUSE_NeighborList (data->Data.fld_c_RPDCON_IRATRUP_INUSE_NeighborList);
			retLen = DECODE_c_RPDCON_IRATRUP_INUSE_NeighborList (buffer, 0, data->Data.fld_c_RPDCON_IRATRUP_INUSE_NeighborList, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATRUP_INUSE_AttributeOverride */
		case 0x0005: {
			SETPRESENT_TRPDCON_IRATRUP_INUSE_Data (data, ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_AttributeOverride);
			INIT_c_RPDCON_IRATRUP_INUSE_AttributeOverride (data->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeOverride);
			retLen = DECODE_c_RPDCON_IRATRUP_INUSE_AttributeOverride (buffer, 0, data->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeOverride, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATRUP_INUSE_AttributeOverrideResponse */
		case 0x0006: {
			SETPRESENT_TRPDCON_IRATRUP_INUSE_Data (data, ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse);
			INIT_c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse (data->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse);
			retLen = DECODE_c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse (buffer, 0, data->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATRUP_INUSE_RouteUpdateRequest */
		case 0x0007: {
			SETPRESENT_TRPDCON_IRATRUP_INUSE_Data (data, ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_RouteUpdateRequest);
			INIT_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest (data->Data.fld_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest);
			retLen = DECODE_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest (buffer, 0, data->Data.fld_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATRUP_INUSE_AttributeUpdateRequest */
		case 0x0052: {
			SETPRESENT_TRPDCON_IRATRUP_INUSE_Data (data, ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest);
			INIT_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest (data->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest);
			retLen = DECODE_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATRUP_INUSE_AttributeUpdateAccept */
		case 0x0053: {
			SETPRESENT_TRPDCON_IRATRUP_INUSE_Data (data, ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept);
			INIT_c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept (data->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept);
			retLen = DECODE_c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATRUP_INUSE_AttributeUpdateReject */
		case 0x0054: {
			SETPRESENT_TRPDCON_IRATRUP_INUSE_Data (data, ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_AttributeUpdateReject);
			INIT_c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject (data->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject);
			retLen = DECODE_c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_RPDCON_IRATRUP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_IRATRUP_INUSE (const char* buffer, int len, TRPDCON_IRATRUP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_RPDCON_IRATRUP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_RPDCON_IRATRUP_INUSE (char* buffer, ED_EXLONG bitOffset, TRPDCON_IRATRUP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_RouteUpdate: {
			retLen = ENCODE_c_RPDCON_IRATRUP_INUSE_RouteUpdate (buffer, 0, data->Data.fld_c_RPDCON_IRATRUP_INUSE_RouteUpdate, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment: {
			retLen = ENCODE_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment (buffer, 0, data->Data.fld_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_TrafficChannelComplete: {
			retLen = ENCODE_c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete (buffer, 0, data->Data.fld_c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_ResetReport: {
			retLen = ENCODE_c_RPDCON_IRATRUP_INUSE_ResetReport (buffer, 0, data->Data.fld_c_RPDCON_IRATRUP_INUSE_ResetReport, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_NeighborList: {
			retLen = ENCODE_c_RPDCON_IRATRUP_INUSE_NeighborList (buffer, 0, data->Data.fld_c_RPDCON_IRATRUP_INUSE_NeighborList, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_AttributeOverride: {
			retLen = ENCODE_c_RPDCON_IRATRUP_INUSE_AttributeOverride (buffer, 0, data->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeOverride, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse: {
			retLen = ENCODE_c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse (buffer, 0, data->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_RouteUpdateRequest: {
			retLen = ENCODE_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest (buffer, 0, data->Data.fld_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest: {
			retLen = ENCODE_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept: {
			retLen = ENCODE_c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATRUP_INUSE_RPDCON_IRATRUP_INUSE_AttributeUpdateReject: {
			retLen = ENCODE_c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_RPDCON_IRATOMP_INCFG (const char* buffer, TRPDCON_IRATOMP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = 0;
	
	/*-----------------------------------------------------------------
		Key is set to a single value containing protocol discriminator,
		skip indicator and message type.
		For example, message ASSIGNMENT_COMMAND has:
			skip indicator         = 0000 (0x0)
			protocol discriminator = 0110 (0x6)
			message type           = 00101110 (0x2E)
		In this case, key will be set to 0x602E.
		Skip indicator could be in some cases a transaction identifier.
		In such cases, it will be set to 0 for matching purposes.
	------------------------------------------------------------------*/
	unsigned /****/ int key /*1*/ = ((unsigned char)buffer [0])/*2*/;/*3*/
	data->MessageType = (int)((unsigned char)buffer [0]);
	
	ED_WARNING_REMOVER(key);
	switch (key) {
			/* Detect signal RPDCON_IRATOMP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TRPDCON_IRATOMP_INCFG_Data (data, ID_RPDCON_IRATOMP_INCFG_RPDCON_IRATOMP_INCFG_ConfigurationRequest);
			INIT_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest (data->Data.fld_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATOMP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TRPDCON_IRATOMP_INCFG_Data (data, ID_RPDCON_IRATOMP_INCFG_RPDCON_IRATOMP_INCFG_ConfigurationResponse);
			INIT_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse (data->Data.fld_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_RPDCON_IRATOMP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_IRATOMP_INCFG (const char* buffer, int len, TRPDCON_IRATOMP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_RPDCON_IRATOMP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_RPDCON_IRATOMP_INCFG (char* buffer, ED_EXLONG bitOffset, TRPDCON_IRATOMP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_RPDCON_IRATOMP_INCFG_RPDCON_IRATOMP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATOMP_INCFG_RPDCON_IRATOMP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_RPDCON_IRATOMP_INUSE (const char* buffer, TRPDCON_IRATOMP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = 0;
	
	/*-----------------------------------------------------------------
		Key is set to a single value containing protocol discriminator,
		skip indicator and message type.
		For example, message ASSIGNMENT_COMMAND has:
			skip indicator         = 0000 (0x0)
			protocol discriminator = 0110 (0x6)
			message type           = 00101110 (0x2E)
		In this case, key will be set to 0x602E.
		Skip indicator could be in some cases a transaction identifier.
		In such cases, it will be set to 0 for matching purposes.
	------------------------------------------------------------------*/
	unsigned /****/ int key /*1*/ = ((unsigned char)buffer [0])/*2*/;/*3*/
	data->MessageType = (int)((unsigned char)buffer [0]);
	
	ED_WARNING_REMOVER(key);
	switch (key) {
			/* Detect signal RPDCON_IRATOMP_INUSE_QuickConfig */
		case 0x0000: {
			SETPRESENT_TRPDCON_IRATOMP_INUSE_Data (data, ID_RPDCON_IRATOMP_INUSE_RPDCON_IRATOMP_INUSE_QuickConfig);
			INIT_c_RPDCON_IRATOMP_INUSE_QuickConfig (data->Data.fld_c_RPDCON_IRATOMP_INUSE_QuickConfig);
			retLen = DECODE_c_RPDCON_IRATOMP_INUSE_QuickConfig (buffer, 0, data->Data.fld_c_RPDCON_IRATOMP_INUSE_QuickConfig, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATOMP_INUSE_SectorParameters */
		case 0x0001: {
			SETPRESENT_TRPDCON_IRATOMP_INUSE_Data (data, ID_RPDCON_IRATOMP_INUSE_RPDCON_IRATOMP_INUSE_SectorParameters);
			INIT_c_RPDCON_IRATOMP_INUSE_SectorParameters (data->Data.fld_c_RPDCON_IRATOMP_INUSE_SectorParameters);
			retLen = DECODE_c_RPDCON_IRATOMP_INUSE_SectorParameters (buffer, 0, data->Data.fld_c_RPDCON_IRATOMP_INUSE_SectorParameters, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATOMP_INUSE_HRPDSilenceParameters */
		case 0x0002: {
			SETPRESENT_TRPDCON_IRATOMP_INUSE_Data (data, ID_RPDCON_IRATOMP_INUSE_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters);
			INIT_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters (data->Data.fld_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters);
			retLen = DECODE_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters (buffer, 0, data->Data.fld_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATOMP_INUSE_OtherRATNeighborList */
		case 0x0003: {
			SETPRESENT_TRPDCON_IRATOMP_INUSE_Data (data, ID_RPDCON_IRATOMP_INUSE_RPDCON_IRATOMP_INUSE_OtherRATNeighborList);
			INIT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList (data->Data.fld_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList);
			retLen = DECODE_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList (buffer, 0, data->Data.fld_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_RPDCON_IRATOMP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_IRATOMP_INUSE (const char* buffer, int len, TRPDCON_IRATOMP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_RPDCON_IRATOMP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_RPDCON_IRATOMP_INUSE (char* buffer, ED_EXLONG bitOffset, TRPDCON_IRATOMP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_RPDCON_IRATOMP_INUSE_RPDCON_IRATOMP_INUSE_QuickConfig: {
			retLen = ENCODE_c_RPDCON_IRATOMP_INUSE_QuickConfig (buffer, 0, data->Data.fld_c_RPDCON_IRATOMP_INUSE_QuickConfig, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATOMP_INUSE_RPDCON_IRATOMP_INUSE_SectorParameters: {
			retLen = ENCODE_c_RPDCON_IRATOMP_INUSE_SectorParameters (buffer, 0, data->Data.fld_c_RPDCON_IRATOMP_INUSE_SectorParameters, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATOMP_INUSE_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters: {
			retLen = ENCODE_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters (buffer, 0, data->Data.fld_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATOMP_INUSE_RPDCON_IRATOMP_INUSE_OtherRATNeighborList: {
			retLen = ENCODE_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList (buffer, 0, data->Data.fld_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_RPDCON_DSAP_INCFG (const char* buffer, TRPDCON_DSAP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = 0;
	
	/*-----------------------------------------------------------------
		Key is set to a single value containing protocol discriminator,
		skip indicator and message type.
		For example, message ASSIGNMENT_COMMAND has:
			skip indicator         = 0000 (0x0)
			protocol discriminator = 0110 (0x6)
			message type           = 00101110 (0x2E)
		In this case, key will be set to 0x602E.
		Skip indicator could be in some cases a transaction identifier.
		In such cases, it will be set to 0 for matching purposes.
	------------------------------------------------------------------*/
	unsigned /****/ int key /*1*/ = ((unsigned char)buffer [0])/*2*/;/*3*/
	data->MessageType = (int)((unsigned char)buffer [0]);
	
	ED_WARNING_REMOVER(key);
	switch (key) {
			/* Detect signal RPDCON_DSAP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TRPDCON_DSAP_INCFG_Data (data, ID_RPDCON_DSAP_INCFG_RPDCON_DSAP_INCFG_ConfigurationRequest);
			INIT_c_RPDCON_DSAP_INCFG_ConfigurationRequest (data->Data.fld_c_RPDCON_DSAP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_RPDCON_DSAP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_RPDCON_DSAP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_DSAP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TRPDCON_DSAP_INCFG_Data (data, ID_RPDCON_DSAP_INCFG_RPDCON_DSAP_INCFG_ConfigurationResponse);
			INIT_c_RPDCON_DSAP_INCFG_ConfigurationResponse (data->Data.fld_c_RPDCON_DSAP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_RPDCON_DSAP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_RPDCON_DSAP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_RPDCON_DSAP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_DSAP_INCFG (const char* buffer, int len, TRPDCON_DSAP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_RPDCON_DSAP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_RPDCON_DSAP_INCFG (char* buffer, ED_EXLONG bitOffset, TRPDCON_DSAP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_RPDCON_DSAP_INCFG_RPDCON_DSAP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_RPDCON_DSAP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_RPDCON_DSAP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_DSAP_INCFG_RPDCON_DSAP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_RPDCON_DSAP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_RPDCON_DSAP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_RPDCON_IRATQISP_INCFG (const char* buffer, TRPDCON_IRATQISP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = 0;
	
	/*-----------------------------------------------------------------
		Key is set to a single value containing protocol discriminator,
		skip indicator and message type.
		For example, message ASSIGNMENT_COMMAND has:
			skip indicator         = 0000 (0x0)
			protocol discriminator = 0110 (0x6)
			message type           = 00101110 (0x2E)
		In this case, key will be set to 0x602E.
		Skip indicator could be in some cases a transaction identifier.
		In such cases, it will be set to 0 for matching purposes.
	------------------------------------------------------------------*/
	unsigned /****/ int key /*1*/ = ((unsigned char)buffer [0])/*2*/;/*3*/
	data->MessageType = (int)((unsigned char)buffer [0]);
	
	ED_WARNING_REMOVER(key);
	switch (key) {
			/* Detect signal RPDCON_IRATQISP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TRPDCON_IRATQISP_INCFG_Data (data, ID_RPDCON_IRATQISP_INCFG_RPDCON_IRATQISP_INCFG_ConfigurationRequest);
			INIT_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest (data->Data.fld_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATQISP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TRPDCON_IRATQISP_INCFG_Data (data, ID_RPDCON_IRATQISP_INCFG_RPDCON_IRATQISP_INCFG_ConfigurationResponse);
			INIT_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse (data->Data.fld_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_RPDCON_IRATQISP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_IRATQISP_INCFG (const char* buffer, int len, TRPDCON_IRATQISP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_RPDCON_IRATQISP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_RPDCON_IRATQISP_INCFG (char* buffer, ED_EXLONG bitOffset, TRPDCON_IRATQISP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_RPDCON_IRATQISP_INCFG_RPDCON_IRATQISP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATQISP_INCFG_RPDCON_IRATQISP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_RPDCON_IRATQISP_INUSE (const char* buffer, TRPDCON_IRATQISP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = 0;
	
	/*-----------------------------------------------------------------
		Key is set to a single value containing protocol discriminator,
		skip indicator and message type.
		For example, message ASSIGNMENT_COMMAND has:
			skip indicator         = 0000 (0x0)
			protocol discriminator = 0110 (0x6)
			message type           = 00101110 (0x2E)
		In this case, key will be set to 0x602E.
		Skip indicator could be in some cases a transaction identifier.
		In such cases, it will be set to 0 for matching purposes.
	------------------------------------------------------------------*/
	unsigned /****/ int key /*1*/ = ((unsigned char)buffer [0])/*2*/;/*3*/
	data->MessageType = (int)((unsigned char)buffer [0]);
	
	ED_WARNING_REMOVER(key);
	switch (key) {
			/* Detect signal RPDCON_IRATQISP_INUSE_Page */
		case 0x0000: {
			SETPRESENT_TRPDCON_IRATQISP_INUSE_Data (data, ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_Page);
			INIT_c_RPDCON_IRATQISP_INUSE_Page (data->Data.fld_c_RPDCON_IRATQISP_INUSE_Page);
			retLen = DECODE_c_RPDCON_IRATQISP_INUSE_Page (buffer, 0, data->Data.fld_c_RPDCON_IRATQISP_INUSE_Page, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATQISP_INUSE_ConnectionRequest */
		case 0x0001: {
			SETPRESENT_TRPDCON_IRATQISP_INUSE_Data (data, ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_ConnectionRequest);
			INIT_c_RPDCON_IRATQISP_INUSE_ConnectionRequest (data->Data.fld_c_RPDCON_IRATQISP_INUSE_ConnectionRequest);
			retLen = DECODE_c_RPDCON_IRATQISP_INUSE_ConnectionRequest (buffer, 0, data->Data.fld_c_RPDCON_IRATQISP_INUSE_ConnectionRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATQISP_INUSE_ConnectionDeny */
		case 0x0002: {
			SETPRESENT_TRPDCON_IRATQISP_INUSE_Data (data, ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_ConnectionDeny);
			INIT_c_RPDCON_IRATQISP_INUSE_ConnectionDeny (data->Data.fld_c_RPDCON_IRATQISP_INUSE_ConnectionDeny);
			retLen = DECODE_c_RPDCON_IRATQISP_INUSE_ConnectionDeny (buffer, 0, data->Data.fld_c_RPDCON_IRATQISP_INUSE_ConnectionDeny, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATQISP_INUSE_QuickPage */
		case 0x0003: {
			SETPRESENT_TRPDCON_IRATQISP_INUSE_Data (data, ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_QuickPage);
			INIT_c_RPDCON_IRATQISP_INUSE_QuickPage (data->Data.fld_c_RPDCON_IRATQISP_INUSE_QuickPage);
			retLen = DECODE_c_RPDCON_IRATQISP_INUSE_QuickPage (buffer, 0, data->Data.fld_c_RPDCON_IRATQISP_INUSE_QuickPage, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATQISP_INUSE_AttributeUpdateRequest */
		case 0x0052: {
			SETPRESENT_TRPDCON_IRATQISP_INUSE_Data (data, ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest);
			INIT_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest (data->Data.fld_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest);
			retLen = DECODE_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATQISP_INUSE_AttributeUpdateAccept */
		case 0x0053: {
			SETPRESENT_TRPDCON_IRATQISP_INUSE_Data (data, ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept);
			INIT_c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept (data->Data.fld_c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept);
			retLen = DECODE_c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATQISP_INUSE_AttributeUpdateReject */
		case 0x0054: {
			SETPRESENT_TRPDCON_IRATQISP_INUSE_Data (data, ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_AttributeUpdateReject);
			INIT_c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject (data->Data.fld_c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject);
			retLen = DECODE_c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_RPDCON_IRATQISP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_IRATQISP_INUSE (const char* buffer, int len, TRPDCON_IRATQISP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_RPDCON_IRATQISP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_RPDCON_IRATQISP_INUSE (char* buffer, ED_EXLONG bitOffset, TRPDCON_IRATQISP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_Page: {
			retLen = ENCODE_c_RPDCON_IRATQISP_INUSE_Page (buffer, 0, data->Data.fld_c_RPDCON_IRATQISP_INUSE_Page, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_ConnectionRequest: {
			retLen = ENCODE_c_RPDCON_IRATQISP_INUSE_ConnectionRequest (buffer, 0, data->Data.fld_c_RPDCON_IRATQISP_INUSE_ConnectionRequest, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_ConnectionDeny: {
			retLen = ENCODE_c_RPDCON_IRATQISP_INUSE_ConnectionDeny (buffer, 0, data->Data.fld_c_RPDCON_IRATQISP_INUSE_ConnectionDeny, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_QuickPage: {
			retLen = ENCODE_c_RPDCON_IRATQISP_INUSE_QuickPage (buffer, 0, data->Data.fld_c_RPDCON_IRATQISP_INUSE_QuickPage, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest: {
			retLen = ENCODE_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept: {
			retLen = ENCODE_c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATQISP_INUSE_RPDCON_IRATQISP_INUSE_AttributeUpdateReject: {
			retLen = ENCODE_c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_RPDCON_S1IRATRUP_INCFG (const char* buffer, TRPDCON_S1IRATRUP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = 0;
	
	/*-----------------------------------------------------------------
		Key is set to a single value containing protocol discriminator,
		skip indicator and message type.
		For example, message ASSIGNMENT_COMMAND has:
			skip indicator         = 0000 (0x0)
			protocol discriminator = 0110 (0x6)
			message type           = 00101110 (0x2E)
		In this case, key will be set to 0x602E.
		Skip indicator could be in some cases a transaction identifier.
		In such cases, it will be set to 0 for matching purposes.
	------------------------------------------------------------------*/
	unsigned /****/ int key /*1*/ = ((unsigned char)buffer [0])/*2*/;/*3*/
	data->MessageType = (int)((unsigned char)buffer [0]);
	
	ED_WARNING_REMOVER(key);
	switch (key) {
			/* Detect signal RPDCON_S1IRATRUP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TRPDCON_S1IRATRUP_INCFG_Data (data, ID_RPDCON_S1IRATRUP_INCFG_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest);
			INIT_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest (data->Data.fld_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_S1IRATRUP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TRPDCON_S1IRATRUP_INCFG_Data (data, ID_RPDCON_S1IRATRUP_INCFG_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse);
			INIT_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse (data->Data.fld_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_RPDCON_S1IRATRUP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_S1IRATRUP_INCFG (const char* buffer, int len, TRPDCON_S1IRATRUP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_RPDCON_S1IRATRUP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_RPDCON_S1IRATRUP_INCFG (char* buffer, ED_EXLONG bitOffset, TRPDCON_S1IRATRUP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_RPDCON_S1IRATRUP_INCFG_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_S1IRATRUP_INCFG_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_RPDCON_S1IRATRUP_INUSE (const char* buffer, TRPDCON_S1IRATRUP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = 0;
	
	/*-----------------------------------------------------------------
		Key is set to a single value containing protocol discriminator,
		skip indicator and message type.
		For example, message ASSIGNMENT_COMMAND has:
			skip indicator         = 0000 (0x0)
			protocol discriminator = 0110 (0x6)
			message type           = 00101110 (0x2E)
		In this case, key will be set to 0x602E.
		Skip indicator could be in some cases a transaction identifier.
		In such cases, it will be set to 0 for matching purposes.
	------------------------------------------------------------------*/
	unsigned /****/ int key /*1*/ = ((unsigned char)buffer [0])/*2*/;/*3*/
	data->MessageType = (int)((unsigned char)buffer [0]);
	
	ED_WARNING_REMOVER(key);
	switch (key) {
			/* Detect signal RPDCON_S1IRATRUP_INUSE_RouteUpdate */
		case 0x0000: {
			SETPRESENT_TRPDCON_S1IRATRUP_INUSE_Data (data, ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_RouteUpdate);
			INIT_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate (data->Data.fld_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate);
			retLen = DECODE_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate (buffer, 0, data->Data.fld_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment */
		case 0x0001: {
			SETPRESENT_TRPDCON_S1IRATRUP_INUSE_Data (data, ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment);
			INIT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment (data->Data.fld_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment);
			retLen = DECODE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment (buffer, 0, data->Data.fld_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete */
		case 0x0002: {
			SETPRESENT_TRPDCON_S1IRATRUP_INUSE_Data (data, ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete);
			INIT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete (data->Data.fld_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete);
			retLen = DECODE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete (buffer, 0, data->Data.fld_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_S1IRATRUP_INUSE_ResetReport */
		case 0x0003: {
			SETPRESENT_TRPDCON_S1IRATRUP_INUSE_Data (data, ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_ResetReport);
			INIT_c_RPDCON_S1IRATRUP_INUSE_ResetReport (data->Data.fld_c_RPDCON_S1IRATRUP_INUSE_ResetReport);
			retLen = DECODE_c_RPDCON_S1IRATRUP_INUSE_ResetReport (buffer, 0, data->Data.fld_c_RPDCON_S1IRATRUP_INUSE_ResetReport, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_S1IRATRUP_INUSE_NeighborList */
		case 0x0004: {
			SETPRESENT_TRPDCON_S1IRATRUP_INUSE_Data (data, ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_NeighborList);
			INIT_c_RPDCON_S1IRATRUP_INUSE_NeighborList (data->Data.fld_c_RPDCON_S1IRATRUP_INUSE_NeighborList);
			retLen = DECODE_c_RPDCON_S1IRATRUP_INUSE_NeighborList (buffer, 0, data->Data.fld_c_RPDCON_S1IRATRUP_INUSE_NeighborList, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest */
		case 0x0007: {
			SETPRESENT_TRPDCON_S1IRATRUP_INUSE_Data (data, ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest);
			INIT_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest (data->Data.fld_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest);
			retLen = DECODE_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest (buffer, 0, data->Data.fld_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest */
		case 0x0052: {
			SETPRESENT_TRPDCON_S1IRATRUP_INUSE_Data (data, ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest);
			INIT_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest (data->Data.fld_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest);
			retLen = DECODE_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept */
		case 0x0053: {
			SETPRESENT_TRPDCON_S1IRATRUP_INUSE_Data (data, ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept);
			INIT_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept (data->Data.fld_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept);
			retLen = DECODE_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject */
		case 0x0054: {
			SETPRESENT_TRPDCON_S1IRATRUP_INUSE_Data (data, ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject);
			INIT_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject (data->Data.fld_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject);
			retLen = DECODE_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_RPDCON_S1IRATRUP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_S1IRATRUP_INUSE (const char* buffer, int len, TRPDCON_S1IRATRUP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_RPDCON_S1IRATRUP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_RPDCON_S1IRATRUP_INUSE (char* buffer, ED_EXLONG bitOffset, TRPDCON_S1IRATRUP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_RouteUpdate: {
			retLen = ENCODE_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate (buffer, 0, data->Data.fld_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment: {
			retLen = ENCODE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment (buffer, 0, data->Data.fld_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete: {
			retLen = ENCODE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete (buffer, 0, data->Data.fld_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_ResetReport: {
			retLen = ENCODE_c_RPDCON_S1IRATRUP_INUSE_ResetReport (buffer, 0, data->Data.fld_c_RPDCON_S1IRATRUP_INUSE_ResetReport, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_NeighborList: {
			retLen = ENCODE_c_RPDCON_S1IRATRUP_INUSE_NeighborList (buffer, 0, data->Data.fld_c_RPDCON_S1IRATRUP_INUSE_NeighborList, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest: {
			retLen = ENCODE_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest (buffer, 0, data->Data.fld_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest: {
			retLen = ENCODE_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept: {
			retLen = ENCODE_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_S1IRATRUP_INUSE_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject: {
			retLen = ENCODE_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_RPDCON_IRATOMPCS0024B_INCFG (const char* buffer, TRPDCON_IRATOMPCS0024B_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = 0;
	
	/*-----------------------------------------------------------------
		Key is set to a single value containing protocol discriminator,
		skip indicator and message type.
		For example, message ASSIGNMENT_COMMAND has:
			skip indicator         = 0000 (0x0)
			protocol discriminator = 0110 (0x6)
			message type           = 00101110 (0x2E)
		In this case, key will be set to 0x602E.
		Skip indicator could be in some cases a transaction identifier.
		In such cases, it will be set to 0 for matching purposes.
	------------------------------------------------------------------*/
	unsigned /****/ int key /*1*/ = ((unsigned char)buffer [0])/*2*/;/*3*/
	data->MessageType = (int)((unsigned char)buffer [0]);
	
	ED_WARNING_REMOVER(key);
	switch (key) {
			/* Detect signal RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TRPDCON_IRATOMPCS0024B_INCFG_Data (data, ID_RPDCON_IRATOMPCS0024B_INCFG_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest);
			INIT_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest (data->Data.fld_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest);
			retLen = DECODE_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TRPDCON_IRATOMPCS0024B_INCFG_Data (data, ID_RPDCON_IRATOMPCS0024B_INCFG_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse);
			INIT_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse (data->Data.fld_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse);
			retLen = DECODE_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_RPDCON_IRATOMPCS0024B_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_IRATOMPCS0024B_INCFG (const char* buffer, int len, TRPDCON_IRATOMPCS0024B_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_RPDCON_IRATOMPCS0024B_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_RPDCON_IRATOMPCS0024B_INCFG (char* buffer, ED_EXLONG bitOffset, TRPDCON_IRATOMPCS0024B_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_RPDCON_IRATOMPCS0024B_INCFG_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATOMPCS0024B_INCFG_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_RPDCON_IRATOMPCS0024B_INUSE (const char* buffer, TRPDCON_IRATOMPCS0024B_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = 0;
	
	/*-----------------------------------------------------------------
		Key is set to a single value containing protocol discriminator,
		skip indicator and message type.
		For example, message ASSIGNMENT_COMMAND has:
			skip indicator         = 0000 (0x0)
			protocol discriminator = 0110 (0x6)
			message type           = 00101110 (0x2E)
		In this case, key will be set to 0x602E.
		Skip indicator could be in some cases a transaction identifier.
		In such cases, it will be set to 0 for matching purposes.
	------------------------------------------------------------------*/
	unsigned /****/ int key /*1*/ = ((unsigned char)buffer [0])/*2*/;/*3*/
	data->MessageType = (int)((unsigned char)buffer [0]);
	
	ED_WARNING_REMOVER(key);
	switch (key) {
			/* Detect signal RPDCON_IRATOMPCS0024B_INUSE_QuickConfig */
		case 0x0000: {
			SETPRESENT_TRPDCON_IRATOMPCS0024B_INUSE_Data (data, ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig);
			INIT_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig (data->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig);
			retLen = DECODE_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig (buffer, 0, data->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATOMPCS0024B_INUSE_SectorParameters */
		case 0x0001: {
			SETPRESENT_TRPDCON_IRATOMPCS0024B_INUSE_Data (data, ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters);
			INIT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters (data->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters);
			retLen = DECODE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters (buffer, 0, data->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters */
		case 0x0002: {
			SETPRESENT_TRPDCON_IRATOMPCS0024B_INUSE_Data (data, ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters);
			INIT_c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters (data->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters);
			retLen = DECODE_c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters (buffer, 0, data->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList */
		case 0x0003: {
			SETPRESENT_TRPDCON_IRATOMPCS0024B_INUSE_Data (data, ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList);
			INIT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList (data->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList);
			retLen = DECODE_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList (buffer, 0, data->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation */
		case 0x0004: {
			SETPRESENT_TRPDCON_IRATOMPCS0024B_INUSE_Data (data, ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation);
			INIT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation (data->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation);
			retLen = DECODE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation (buffer, 0, data->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification */
		case 0x0005: {
			SETPRESENT_TRPDCON_IRATOMPCS0024B_INUSE_Data (data, ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification);
			INIT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification (data->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification);
			retLen = DECODE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification (buffer, 0, data->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText */
		case 0x0006: {
			SETPRESENT_TRPDCON_IRATOMPCS0024B_INUSE_Data (data, ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText);
			INIT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText (data->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText);
			retLen = DECODE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText (buffer, 0, data->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_RPDCON_IRATOMPCS0024B_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDCON_IRATOMPCS0024B_INUSE (const char* buffer, int len, TRPDCON_IRATOMPCS0024B_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_RPDCON_IRATOMPCS0024B_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_RPDCON_IRATOMPCS0024B_INUSE (char* buffer, ED_EXLONG bitOffset, TRPDCON_IRATOMPCS0024B_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig: {
			retLen = ENCODE_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig (buffer, 0, data->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters: {
			retLen = ENCODE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters (buffer, 0, data->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters: {
			retLen = ENCODE_c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters (buffer, 0, data->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList: {
			retLen = ENCODE_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList (buffer, 0, data->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation: {
			retLen = ENCODE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation (buffer, 0, data->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification: {
			retLen = ENCODE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification (buffer, 0, data->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification, pCSN1CContextSet);
			break;
		}
		case ID_RPDCON_IRATOMPCS0024B_INUSE_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText: {
			retLen = ENCODE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText (buffer, 0, data->Data.fld_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_RPDRAT_ATS3RTCMACPR (const char* buffer, TRPDRAT_ATS3RTCMACPR_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = 0;
	
	/*-----------------------------------------------------------------
		Key is set to a single value containing protocol discriminator,
		skip indicator and message type.
		For example, message ASSIGNMENT_COMMAND has:
			skip indicator         = 0000 (0x0)
			protocol discriminator = 0110 (0x6)
			message type           = 00101110 (0x2E)
		In this case, key will be set to 0x602E.
		Skip indicator could be in some cases a transaction identifier.
		In such cases, it will be set to 0 for matching purposes.
	------------------------------------------------------------------*/
	unsigned /****/ int key /*1*/ = ((unsigned char)buffer [0])/*2*/;/*3*/
	data->MessageType = (int)((unsigned char)buffer [0]);
	
	ED_WARNING_REMOVER(key);
	switch (key) {
			/* Detect signal RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters */
		case 0x0007: {
			SETPRESENT_TRPDRAT_ATS3RTCMACPR_Data (data, ID_RPDRAT_ATS3RTCMACPR_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters);
			INIT_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters (data->Data.fld_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters);
			retLen = DECODE_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters (buffer, 0, data->Data.fld_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_RPDRAT_ATS3RTCMACPR_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDRAT_ATS3RTCMACPR (const char* buffer, int len, TRPDRAT_ATS3RTCMACPR_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_RPDRAT_ATS3RTCMACPR (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_RPDRAT_ATS3RTCMACPR (char* buffer, ED_EXLONG bitOffset, TRPDRAT_ATS3RTCMACPR_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_RPDRAT_ATS3RTCMACPR_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters: {
			retLen = ENCODE_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters (buffer, 0, data->Data.fld_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_RPDRAT_ATS4RTCMACPR (const char* buffer, TRPDRAT_ATS4RTCMACPR_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = 0;
	
	/*-----------------------------------------------------------------
		Key is set to a single value containing protocol discriminator,
		skip indicator and message type.
		For example, message ASSIGNMENT_COMMAND has:
			skip indicator         = 0000 (0x0)
			protocol discriminator = 0110 (0x6)
			message type           = 00101110 (0x2E)
		In this case, key will be set to 0x602E.
		Skip indicator could be in some cases a transaction identifier.
		In such cases, it will be set to 0 for matching purposes.
	------------------------------------------------------------------*/
	unsigned /****/ int key /*1*/ = ((unsigned char)buffer [0])/*2*/;/*3*/
	data->MessageType = (int)((unsigned char)buffer [0]);
	
	ED_WARNING_REMOVER(key);
	switch (key) {
			/* Detect signal RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters */
		case 0x0007: {
			SETPRESENT_TRPDRAT_ATS4RTCMACPR_Data (data, ID_RPDRAT_ATS4RTCMACPR_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters);
			INIT_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters (data->Data.fld_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters);
			retLen = DECODE_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters (buffer, 0, data->Data.fld_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_RPDRAT_ATS4RTCMACPR_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RPDRAT_ATS4RTCMACPR (const char* buffer, int len, TRPDRAT_ATS4RTCMACPR_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_RPDRAT_ATS4RTCMACPR (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_RPDRAT_ATS4RTCMACPR (char* buffer, ED_EXLONG bitOffset, TRPDRAT_ATS4RTCMACPR_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_RPDRAT_ATS4RTCMACPR_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters: {
			retLen = ENCODE_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters (buffer, 0, data->Data.fld_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}

