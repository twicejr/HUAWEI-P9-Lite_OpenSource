/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c-recog
	http://www.Dafocus.it/
**************************************************************************/
/*lint -e959 -e530 -e774 -e572 -e778 -e525 -e539 -e701 -e123 -e438 -e119 -e506 -e529 -e550 -e666 -e713 -e719 -e730 -e734 -e744 -e801 -e801 -e813 -e830 -e40 */
#define ENCODIX_CS0024

#include "ed_c_recog_cs0024.h"
#include "ed_lib.h"
#include "CONN_DINSP_INUSE_cs0024.h"
#include "SIGAPP_SLP_INCFG_cs0024.h"
#include "SIGAPP_SLP_cs0024.h"
#include "PKTAPP_DPA_INCFG_cs0024.h"
#include "PKTAPP_RLP_INUSE_cs0024.h"
#include "PKTAPP_LUP_INUSE_cs0024.h"
#include "PKTAPP_FCP_INUSE_cs0024.h"
#include "MFPAPP_MFPA_INCFG_cs0024.h"
#include "MFPAPP_RLP_INUSE_cs0024.h"
#include "MFPAPP_DOSP_INUSE_cs0024.h"
#include "MFPAPP_LUP_INUSE_cs0024.h"
#include "MFPAPP_FCP_INUSE_cs0024.h"
#include "STREAM_DSP_INCFG_cs0024.h"
#include "STREAM_GVSP_INCFG_cs0024.h"
#include "SESSION_DSMP_INCFG_cs0024.h"
#include "SESSION_DSMP_INUSE_cs0024.h"
#include "SESSION_DAMP_INCFG_cs0024.h"
#include "SESSION_DAMP_INUSE_cs0024.h"
#include "SESSION_DSCP_INUSE_cs0024.h"
#include "SESSION_GMCDP_INCFG_cs0024.h"
#include "CONN_DALMP_INCFG_cs0024.h"
#include "CONN_DALMP_INUSE_cs0024.h"
#include "CONN_DINSP_INCFG_cs0024.h"
#include "CONN_DIDSP_INCFG_cs0024.h"
#include "CONN_DIDSP_INUSE_cs0024.h"
#include "CONN_EISP_INCFG_cs0024.h"
#include "CONN_EISP_INUSE_cs0024.h"
#include "CONN_QISP_INCFG_cs0024.h"
#include "CONN_QISP_INUSE_cs0024.h"
#include "CONN_DCSP_INCFG_cs0024.h"
#include "CONN_DCSP_INUSE_cs0024.h"
#include "CONN_DRUP_INCFG_cs0024.h"
#include "CONN_DRUP_INUSE_cs0024.h"
#include "CONN_MRUP_INCFG_cs0024.h"
#include "CONN_MRUP_INUSE_cs0024.h"
#include "CONN_DPCP_INCFG_cs0024.h"
#include "CONN_OMP_INCFG_cs0024.h"
#include "CONN_OMP_INUSE_cs0024.h"
#include "SECURITY_DSP_INCFG_cs0024.h"
#include "SECURITY_GSP_INCFG_cs0024.h"
#include "SECURITY_DKEP_INCFG_cs0024.h"
#include "SECURITY_DHKEP_INCFG_cs0024.h"
#include "SECURITY_DAP_INCFG_cs0024.h"
#include "SECURITY_SHA1AP_INCFG_cs0024.h"
#include "SECURITY_DEP_INCFG_cs0024.h"
#include "MAC_DCCMACP_INCFG_cs0024.h"
#include "MAC_ECCMACP_INCFG_cs0024.h"
#include "MAC_DACMACP_INCFG_cs0024.h"
#include "MAC_DACMACP_INUSE_cs0024.h"
#include "MAC_EACMACP_INCFG_cs0024.h"
#include "MAC_EACMACP_INUSE_cs0024.h"
#include "MAC_DFTCMACP_INCFG_cs0024.h"
#include "MAC_DFTCMACP_INUSE_cs0024.h"
#include "MAC_EFTCMACP_INCFG_cs0024.h"
#include "MAC_EFTCMACP_INUSE_cs0024.h"
#include "MAC_MFTCMACP_INCFG_cs0024.h"
#include "MAC_MFTCMACP_INUSE_cs0024.h"
#include "MAC_DRTCMACP_INCFG_cs0024.h"
#include "MAC_DRTCMACP_INUSE_cs0024.h"
#include "MAC_S1RTCMACP_INCFG_cs0024.h"
#include "MAC_S1RTCMACP_INUSE_cs0024.h"
#include "MAC_S3RTCMACP_INCFG_cs0024.h"
#include "MAC_S3RTCMACP_INUSE_cs0024.h"
#include "MAC_MRTCMACP_INCFG_cs0024.h"
#include "MAC_MRTCMACP_INUSE_cs0024.h"
#include "PHYS01_DS0S1PLPI_INCFG_cs0024.h"
#include "PHYS2_S2PLPI_INCFG_cs0024.h"
#include "PHYS3_S3PLPI_INCFG_cs0024.h"
#include "PHYS3_S3PLPI_INUSE_cs0024.h"
#include "GEN_GCP_cs0024.h"
#include "GEN_GAUP_cs0024.h"
#if ED_COMMON_CRC != 0x328E3625 && ED_VERSION != 10152 && ED_VERSION != 10153
#error Invalid Encodix library files linked; used those distributed with Encodix 1.0.154
#endif


void SETPRESENT_TCONN_DINSP_INUSE_Data (TCONN_DINSP_INUSE_Data* sp, TCONN_DINSP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TCONN_DINSP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_CONN_DINSP_INUSE_CONN_DINSP_INUSE_Sync: {
			sp->Data.fld_c_CONN_DINSP_INUSE_Sync = (c_CONN_DINSP_INUSE_Sync*)EDAlloc (sizeof (c_CONN_DINSP_INUSE_Sync));
			INIT_c_CONN_DINSP_INUSE_Sync (sp->Data.fld_c_CONN_DINSP_INUSE_Sync);
			break;
		}
		
		default:;
	}
}

void FREE_TCONN_DINSP_INUSE_Data (TCONN_DINSP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_CONN_DINSP_INUSE_CONN_DINSP_INUSE_Sync: {
			FREE_c_CONN_DINSP_INUSE_Sync (sp->Data.fld_c_CONN_DINSP_INUSE_Sync);
	EDFree (sp->Data.fld_c_CONN_DINSP_INUSE_Sync );
			break;
		}
		
		default:;
	}

	sp->Type = ID_CONN_DINSP_INUSE_Unrecognized;
}

void SETPRESENT_TSIGAPP_SLP_INCFG_Data (TSIGAPP_SLP_INCFG_Data* sp, TSIGAPP_SLP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TSIGAPP_SLP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_SIGAPP_SLP_INCFG_SIGAPP_SLP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_SIGAPP_SLP_INCFG_ConfigurationRequest = (c_SIGAPP_SLP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_SIGAPP_SLP_INCFG_ConfigurationRequest));
			INIT_c_SIGAPP_SLP_INCFG_ConfigurationRequest (sp->Data.fld_c_SIGAPP_SLP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_SIGAPP_SLP_INCFG_SIGAPP_SLP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_SIGAPP_SLP_INCFG_ConfigurationResponse = (c_SIGAPP_SLP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_SIGAPP_SLP_INCFG_ConfigurationResponse));
			INIT_c_SIGAPP_SLP_INCFG_ConfigurationResponse (sp->Data.fld_c_SIGAPP_SLP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TSIGAPP_SLP_INCFG_Data (TSIGAPP_SLP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_SIGAPP_SLP_INCFG_SIGAPP_SLP_INCFG_ConfigurationRequest: {
			FREE_c_SIGAPP_SLP_INCFG_ConfigurationRequest (sp->Data.fld_c_SIGAPP_SLP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_SIGAPP_SLP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_SIGAPP_SLP_INCFG_SIGAPP_SLP_INCFG_ConfigurationResponse: {
			FREE_c_SIGAPP_SLP_INCFG_ConfigurationResponse (sp->Data.fld_c_SIGAPP_SLP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_SIGAPP_SLP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_SIGAPP_SLP_INCFG_Unrecognized;
}

void SETPRESENT_TSIGAPP_SLP_Data (TSIGAPP_SLP_Data* sp, TSIGAPP_SLP_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TSIGAPP_SLP_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_SIGAPP_SLP_SIGAPP_SLP_Reset: {
			sp->Data.fld_c_SIGAPP_SLP_Reset = (c_SIGAPP_SLP_Reset*)EDAlloc (sizeof (c_SIGAPP_SLP_Reset));
			INIT_c_SIGAPP_SLP_Reset (sp->Data.fld_c_SIGAPP_SLP_Reset);
			break;
		}
		
		case ID_SIGAPP_SLP_SIGAPP_SLP_ResetAck: {
			sp->Data.fld_c_SIGAPP_SLP_ResetAck = (c_SIGAPP_SLP_ResetAck*)EDAlloc (sizeof (c_SIGAPP_SLP_ResetAck));
			INIT_c_SIGAPP_SLP_ResetAck (sp->Data.fld_c_SIGAPP_SLP_ResetAck);
			break;
		}
		
		default:;
	}
}

void FREE_TSIGAPP_SLP_Data (TSIGAPP_SLP_Data* sp)
{
	switch (sp->Type) {
		case ID_SIGAPP_SLP_SIGAPP_SLP_Reset: {
			FREE_c_SIGAPP_SLP_Reset (sp->Data.fld_c_SIGAPP_SLP_Reset);
	EDFree (sp->Data.fld_c_SIGAPP_SLP_Reset );
			break;
		}
		
		case ID_SIGAPP_SLP_SIGAPP_SLP_ResetAck: {
			FREE_c_SIGAPP_SLP_ResetAck (sp->Data.fld_c_SIGAPP_SLP_ResetAck);
	EDFree (sp->Data.fld_c_SIGAPP_SLP_ResetAck );
			break;
		}
		
		default:;
	}

	sp->Type = ID_SIGAPP_SLP_Unrecognized;
}

void SETPRESENT_TPKTAPP_DPA_INCFG_Data (TPKTAPP_DPA_INCFG_Data* sp, TPKTAPP_DPA_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TPKTAPP_DPA_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_PKTAPP_DPA_INCFG_PKTAPP_DPA_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_PKTAPP_DPA_INCFG_ConfigurationRequest = (c_PKTAPP_DPA_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_PKTAPP_DPA_INCFG_ConfigurationRequest));
			INIT_c_PKTAPP_DPA_INCFG_ConfigurationRequest (sp->Data.fld_c_PKTAPP_DPA_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_PKTAPP_DPA_INCFG_PKTAPP_DPA_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_PKTAPP_DPA_INCFG_ConfigurationResponse = (c_PKTAPP_DPA_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_PKTAPP_DPA_INCFG_ConfigurationResponse));
			INIT_c_PKTAPP_DPA_INCFG_ConfigurationResponse (sp->Data.fld_c_PKTAPP_DPA_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TPKTAPP_DPA_INCFG_Data (TPKTAPP_DPA_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_PKTAPP_DPA_INCFG_PKTAPP_DPA_INCFG_ConfigurationRequest: {
			FREE_c_PKTAPP_DPA_INCFG_ConfigurationRequest (sp->Data.fld_c_PKTAPP_DPA_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_PKTAPP_DPA_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_PKTAPP_DPA_INCFG_PKTAPP_DPA_INCFG_ConfigurationResponse: {
			FREE_c_PKTAPP_DPA_INCFG_ConfigurationResponse (sp->Data.fld_c_PKTAPP_DPA_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_PKTAPP_DPA_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_PKTAPP_DPA_INCFG_Unrecognized;
}

void SETPRESENT_TPKTAPP_RLP_INUSE_Data (TPKTAPP_RLP_INUSE_Data* sp, TPKTAPP_RLP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TPKTAPP_RLP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_PKTAPP_RLP_INUSE_PKTAPP_RLP_INUSE_Reset: {
			sp->Data.fld_c_PKTAPP_RLP_INUSE_Reset = (c_PKTAPP_RLP_INUSE_Reset*)EDAlloc (sizeof (c_PKTAPP_RLP_INUSE_Reset));
			INIT_c_PKTAPP_RLP_INUSE_Reset (sp->Data.fld_c_PKTAPP_RLP_INUSE_Reset);
			break;
		}
		
		case ID_PKTAPP_RLP_INUSE_PKTAPP_RLP_INUSE_ResetAck: {
			sp->Data.fld_c_PKTAPP_RLP_INUSE_ResetAck = (c_PKTAPP_RLP_INUSE_ResetAck*)EDAlloc (sizeof (c_PKTAPP_RLP_INUSE_ResetAck));
			INIT_c_PKTAPP_RLP_INUSE_ResetAck (sp->Data.fld_c_PKTAPP_RLP_INUSE_ResetAck);
			break;
		}
		
		case ID_PKTAPP_RLP_INUSE_PKTAPP_RLP_INUSE_Nak: {
			sp->Data.fld_c_PKTAPP_RLP_INUSE_Nak = (c_PKTAPP_RLP_INUSE_Nak*)EDAlloc (sizeof (c_PKTAPP_RLP_INUSE_Nak));
			INIT_c_PKTAPP_RLP_INUSE_Nak (sp->Data.fld_c_PKTAPP_RLP_INUSE_Nak);
			break;
		}
		
		default:;
	}
}

void FREE_TPKTAPP_RLP_INUSE_Data (TPKTAPP_RLP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_PKTAPP_RLP_INUSE_PKTAPP_RLP_INUSE_Reset: {
			FREE_c_PKTAPP_RLP_INUSE_Reset (sp->Data.fld_c_PKTAPP_RLP_INUSE_Reset);
	EDFree (sp->Data.fld_c_PKTAPP_RLP_INUSE_Reset );
			break;
		}
		
		case ID_PKTAPP_RLP_INUSE_PKTAPP_RLP_INUSE_ResetAck: {
			FREE_c_PKTAPP_RLP_INUSE_ResetAck (sp->Data.fld_c_PKTAPP_RLP_INUSE_ResetAck);
	EDFree (sp->Data.fld_c_PKTAPP_RLP_INUSE_ResetAck );
			break;
		}
		
		case ID_PKTAPP_RLP_INUSE_PKTAPP_RLP_INUSE_Nak: {
			FREE_c_PKTAPP_RLP_INUSE_Nak (sp->Data.fld_c_PKTAPP_RLP_INUSE_Nak);
	EDFree (sp->Data.fld_c_PKTAPP_RLP_INUSE_Nak );
			break;
		}
		
		default:;
	}

	sp->Type = ID_PKTAPP_RLP_INUSE_Unrecognized;
}

void SETPRESENT_TPKTAPP_LUP_INUSE_Data (TPKTAPP_LUP_INUSE_Data* sp, TPKTAPP_LUP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TPKTAPP_LUP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_PKTAPP_LUP_INUSE_PKTAPP_LUP_INUSE_LocationRequest: {
			sp->Data.fld_c_PKTAPP_LUP_INUSE_LocationRequest = (c_PKTAPP_LUP_INUSE_LocationRequest*)EDAlloc (sizeof (c_PKTAPP_LUP_INUSE_LocationRequest));
			INIT_c_PKTAPP_LUP_INUSE_LocationRequest (sp->Data.fld_c_PKTAPP_LUP_INUSE_LocationRequest);
			break;
		}
		
		case ID_PKTAPP_LUP_INUSE_PKTAPP_LUP_INUSE_LocationNotification: {
			sp->Data.fld_c_PKTAPP_LUP_INUSE_LocationNotification = (c_PKTAPP_LUP_INUSE_LocationNotification*)EDAlloc (sizeof (c_PKTAPP_LUP_INUSE_LocationNotification));
			INIT_c_PKTAPP_LUP_INUSE_LocationNotification (sp->Data.fld_c_PKTAPP_LUP_INUSE_LocationNotification);
			break;
		}
		
		case ID_PKTAPP_LUP_INUSE_PKTAPP_LUP_INUSE_LocationAssignment: {
			sp->Data.fld_c_PKTAPP_LUP_INUSE_LocationAssignment = (c_PKTAPP_LUP_INUSE_LocationAssignment*)EDAlloc (sizeof (c_PKTAPP_LUP_INUSE_LocationAssignment));
			INIT_c_PKTAPP_LUP_INUSE_LocationAssignment (sp->Data.fld_c_PKTAPP_LUP_INUSE_LocationAssignment);
			break;
		}
		
		case ID_PKTAPP_LUP_INUSE_PKTAPP_LUP_INUSE_LocationComplete: {
			sp->Data.fld_c_PKTAPP_LUP_INUSE_LocationComplete = (c_PKTAPP_LUP_INUSE_LocationComplete*)EDAlloc (sizeof (c_PKTAPP_LUP_INUSE_LocationComplete));
			INIT_c_PKTAPP_LUP_INUSE_LocationComplete (sp->Data.fld_c_PKTAPP_LUP_INUSE_LocationComplete);
			break;
		}
		
		default:;
	}
}

void FREE_TPKTAPP_LUP_INUSE_Data (TPKTAPP_LUP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_PKTAPP_LUP_INUSE_PKTAPP_LUP_INUSE_LocationRequest: {
			FREE_c_PKTAPP_LUP_INUSE_LocationRequest (sp->Data.fld_c_PKTAPP_LUP_INUSE_LocationRequest);
	EDFree (sp->Data.fld_c_PKTAPP_LUP_INUSE_LocationRequest );
			break;
		}
		
		case ID_PKTAPP_LUP_INUSE_PKTAPP_LUP_INUSE_LocationNotification: {
			FREE_c_PKTAPP_LUP_INUSE_LocationNotification (sp->Data.fld_c_PKTAPP_LUP_INUSE_LocationNotification);
	EDFree (sp->Data.fld_c_PKTAPP_LUP_INUSE_LocationNotification );
			break;
		}
		
		case ID_PKTAPP_LUP_INUSE_PKTAPP_LUP_INUSE_LocationAssignment: {
			FREE_c_PKTAPP_LUP_INUSE_LocationAssignment (sp->Data.fld_c_PKTAPP_LUP_INUSE_LocationAssignment);
	EDFree (sp->Data.fld_c_PKTAPP_LUP_INUSE_LocationAssignment );
			break;
		}
		
		case ID_PKTAPP_LUP_INUSE_PKTAPP_LUP_INUSE_LocationComplete: {
			FREE_c_PKTAPP_LUP_INUSE_LocationComplete (sp->Data.fld_c_PKTAPP_LUP_INUSE_LocationComplete);
	EDFree (sp->Data.fld_c_PKTAPP_LUP_INUSE_LocationComplete );
			break;
		}
		
		default:;
	}

	sp->Type = ID_PKTAPP_LUP_INUSE_Unrecognized;
}

void SETPRESENT_TPKTAPP_FCP_INUSE_Data (TPKTAPP_FCP_INUSE_Data* sp, TPKTAPP_FCP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TPKTAPP_FCP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_PKTAPP_FCP_INUSE_PKTAPP_FCP_INUSE_XonRequest: {
			sp->Data.fld_c_PKTAPP_FCP_INUSE_XonRequest = (c_PKTAPP_FCP_INUSE_XonRequest*)EDAlloc (sizeof (c_PKTAPP_FCP_INUSE_XonRequest));
			INIT_c_PKTAPP_FCP_INUSE_XonRequest (sp->Data.fld_c_PKTAPP_FCP_INUSE_XonRequest);
			break;
		}
		
		case ID_PKTAPP_FCP_INUSE_PKTAPP_FCP_INUSE_XonResponse: {
			sp->Data.fld_c_PKTAPP_FCP_INUSE_XonResponse = (c_PKTAPP_FCP_INUSE_XonResponse*)EDAlloc (sizeof (c_PKTAPP_FCP_INUSE_XonResponse));
			INIT_c_PKTAPP_FCP_INUSE_XonResponse (sp->Data.fld_c_PKTAPP_FCP_INUSE_XonResponse);
			break;
		}
		
		case ID_PKTAPP_FCP_INUSE_PKTAPP_FCP_INUSE_XoffRequest: {
			sp->Data.fld_c_PKTAPP_FCP_INUSE_XoffRequest = (c_PKTAPP_FCP_INUSE_XoffRequest*)EDAlloc (sizeof (c_PKTAPP_FCP_INUSE_XoffRequest));
			INIT_c_PKTAPP_FCP_INUSE_XoffRequest (sp->Data.fld_c_PKTAPP_FCP_INUSE_XoffRequest);
			break;
		}
		
		case ID_PKTAPP_FCP_INUSE_PKTAPP_FCP_INUSE_XoffResponse: {
			sp->Data.fld_c_PKTAPP_FCP_INUSE_XoffResponse = (c_PKTAPP_FCP_INUSE_XoffResponse*)EDAlloc (sizeof (c_PKTAPP_FCP_INUSE_XoffResponse));
			INIT_c_PKTAPP_FCP_INUSE_XoffResponse (sp->Data.fld_c_PKTAPP_FCP_INUSE_XoffResponse);
			break;
		}
		
		case ID_PKTAPP_FCP_INUSE_PKTAPP_FCP_INUSE_DataReady: {
			sp->Data.fld_c_PKTAPP_FCP_INUSE_DataReady = (c_PKTAPP_FCP_INUSE_DataReady*)EDAlloc (sizeof (c_PKTAPP_FCP_INUSE_DataReady));
			INIT_c_PKTAPP_FCP_INUSE_DataReady (sp->Data.fld_c_PKTAPP_FCP_INUSE_DataReady);
			break;
		}
		
		case ID_PKTAPP_FCP_INUSE_PKTAPP_FCP_INUSE_DataReadyAck: {
			sp->Data.fld_c_PKTAPP_FCP_INUSE_DataReadyAck = (c_PKTAPP_FCP_INUSE_DataReadyAck*)EDAlloc (sizeof (c_PKTAPP_FCP_INUSE_DataReadyAck));
			INIT_c_PKTAPP_FCP_INUSE_DataReadyAck (sp->Data.fld_c_PKTAPP_FCP_INUSE_DataReadyAck);
			break;
		}
		
		default:;
	}
}

void FREE_TPKTAPP_FCP_INUSE_Data (TPKTAPP_FCP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_PKTAPP_FCP_INUSE_PKTAPP_FCP_INUSE_XonRequest: {
			FREE_c_PKTAPP_FCP_INUSE_XonRequest (sp->Data.fld_c_PKTAPP_FCP_INUSE_XonRequest);
	EDFree (sp->Data.fld_c_PKTAPP_FCP_INUSE_XonRequest );
			break;
		}
		
		case ID_PKTAPP_FCP_INUSE_PKTAPP_FCP_INUSE_XonResponse: {
			FREE_c_PKTAPP_FCP_INUSE_XonResponse (sp->Data.fld_c_PKTAPP_FCP_INUSE_XonResponse);
	EDFree (sp->Data.fld_c_PKTAPP_FCP_INUSE_XonResponse );
			break;
		}
		
		case ID_PKTAPP_FCP_INUSE_PKTAPP_FCP_INUSE_XoffRequest: {
			FREE_c_PKTAPP_FCP_INUSE_XoffRequest (sp->Data.fld_c_PKTAPP_FCP_INUSE_XoffRequest);
	EDFree (sp->Data.fld_c_PKTAPP_FCP_INUSE_XoffRequest );
			break;
		}
		
		case ID_PKTAPP_FCP_INUSE_PKTAPP_FCP_INUSE_XoffResponse: {
			FREE_c_PKTAPP_FCP_INUSE_XoffResponse (sp->Data.fld_c_PKTAPP_FCP_INUSE_XoffResponse);
	EDFree (sp->Data.fld_c_PKTAPP_FCP_INUSE_XoffResponse );
			break;
		}
		
		case ID_PKTAPP_FCP_INUSE_PKTAPP_FCP_INUSE_DataReady: {
			FREE_c_PKTAPP_FCP_INUSE_DataReady (sp->Data.fld_c_PKTAPP_FCP_INUSE_DataReady);
	EDFree (sp->Data.fld_c_PKTAPP_FCP_INUSE_DataReady );
			break;
		}
		
		case ID_PKTAPP_FCP_INUSE_PKTAPP_FCP_INUSE_DataReadyAck: {
			FREE_c_PKTAPP_FCP_INUSE_DataReadyAck (sp->Data.fld_c_PKTAPP_FCP_INUSE_DataReadyAck);
	EDFree (sp->Data.fld_c_PKTAPP_FCP_INUSE_DataReadyAck );
			break;
		}
		
		default:;
	}

	sp->Type = ID_PKTAPP_FCP_INUSE_Unrecognized;
}

void SETPRESENT_TMFPAPP_MFPA_INCFG_Data (TMFPAPP_MFPA_INCFG_Data* sp, TMFPAPP_MFPA_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TMFPAPP_MFPA_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_MFPAPP_MFPA_INCFG_MFPAPP_MFPA_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_MFPAPP_MFPA_INCFG_ConfigurationRequest = (c_MFPAPP_MFPA_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_MFPAPP_MFPA_INCFG_ConfigurationRequest));
			INIT_c_MFPAPP_MFPA_INCFG_ConfigurationRequest (sp->Data.fld_c_MFPAPP_MFPA_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_MFPAPP_MFPA_INCFG_MFPAPP_MFPA_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_MFPAPP_MFPA_INCFG_ConfigurationResponse = (c_MFPAPP_MFPA_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_MFPAPP_MFPA_INCFG_ConfigurationResponse));
			INIT_c_MFPAPP_MFPA_INCFG_ConfigurationResponse (sp->Data.fld_c_MFPAPP_MFPA_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TMFPAPP_MFPA_INCFG_Data (TMFPAPP_MFPA_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_MFPAPP_MFPA_INCFG_MFPAPP_MFPA_INCFG_ConfigurationRequest: {
			FREE_c_MFPAPP_MFPA_INCFG_ConfigurationRequest (sp->Data.fld_c_MFPAPP_MFPA_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_MFPAPP_MFPA_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_MFPAPP_MFPA_INCFG_MFPAPP_MFPA_INCFG_ConfigurationResponse: {
			FREE_c_MFPAPP_MFPA_INCFG_ConfigurationResponse (sp->Data.fld_c_MFPAPP_MFPA_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_MFPAPP_MFPA_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_MFPAPP_MFPA_INCFG_Unrecognized;
}

void SETPRESENT_TMFPAPP_RLP_INUSE_Data (TMFPAPP_RLP_INUSE_Data* sp, TMFPAPP_RLP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TMFPAPP_RLP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ResetTxIndication: {
			sp->Data.fld_c_MFPAPP_RLP_INUSE_ResetTxIndication = (c_MFPAPP_RLP_INUSE_ResetTxIndication*)EDAlloc (sizeof (c_MFPAPP_RLP_INUSE_ResetTxIndication));
			INIT_c_MFPAPP_RLP_INUSE_ResetTxIndication (sp->Data.fld_c_MFPAPP_RLP_INUSE_ResetTxIndication);
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ResetRxIndication: {
			sp->Data.fld_c_MFPAPP_RLP_INUSE_ResetRxIndication = (c_MFPAPP_RLP_INUSE_ResetRxIndication*)EDAlloc (sizeof (c_MFPAPP_RLP_INUSE_ResetRxIndication));
			INIT_c_MFPAPP_RLP_INUSE_ResetRxIndication (sp->Data.fld_c_MFPAPP_RLP_INUSE_ResetRxIndication);
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ResetTxIndicationAck: {
			sp->Data.fld_c_MFPAPP_RLP_INUSE_ResetTxIndicationAck = (c_MFPAPP_RLP_INUSE_ResetTxIndicationAck*)EDAlloc (sizeof (c_MFPAPP_RLP_INUSE_ResetTxIndicationAck));
			INIT_c_MFPAPP_RLP_INUSE_ResetTxIndicationAck (sp->Data.fld_c_MFPAPP_RLP_INUSE_ResetTxIndicationAck);
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ResetTxComplete: {
			sp->Data.fld_c_MFPAPP_RLP_INUSE_ResetTxComplete = (c_MFPAPP_RLP_INUSE_ResetTxComplete*)EDAlloc (sizeof (c_MFPAPP_RLP_INUSE_ResetTxComplete));
			INIT_c_MFPAPP_RLP_INUSE_ResetTxComplete (sp->Data.fld_c_MFPAPP_RLP_INUSE_ResetTxComplete);
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ResetRxComplete: {
			sp->Data.fld_c_MFPAPP_RLP_INUSE_ResetRxComplete = (c_MFPAPP_RLP_INUSE_ResetRxComplete*)EDAlloc (sizeof (c_MFPAPP_RLP_INUSE_ResetRxComplete));
			INIT_c_MFPAPP_RLP_INUSE_ResetRxComplete (sp->Data.fld_c_MFPAPP_RLP_INUSE_ResetRxComplete);
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_Nak: {
			sp->Data.fld_c_MFPAPP_RLP_INUSE_Nak = (c_MFPAPP_RLP_INUSE_Nak*)EDAlloc (sizeof (c_MFPAPP_RLP_INUSE_Nak));
			INIT_c_MFPAPP_RLP_INUSE_Nak (sp->Data.fld_c_MFPAPP_RLP_INUSE_Nak);
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ReservationOnRequest: {
			sp->Data.fld_c_MFPAPP_RLP_INUSE_ReservationOnRequest = (c_MFPAPP_RLP_INUSE_ReservationOnRequest*)EDAlloc (sizeof (c_MFPAPP_RLP_INUSE_ReservationOnRequest));
			INIT_c_MFPAPP_RLP_INUSE_ReservationOnRequest (sp->Data.fld_c_MFPAPP_RLP_INUSE_ReservationOnRequest);
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ReservationOffRequest: {
			sp->Data.fld_c_MFPAPP_RLP_INUSE_ReservationOffRequest = (c_MFPAPP_RLP_INUSE_ReservationOffRequest*)EDAlloc (sizeof (c_MFPAPP_RLP_INUSE_ReservationOffRequest));
			INIT_c_MFPAPP_RLP_INUSE_ReservationOffRequest (sp->Data.fld_c_MFPAPP_RLP_INUSE_ReservationOffRequest);
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ReservationAccept: {
			sp->Data.fld_c_MFPAPP_RLP_INUSE_ReservationAccept = (c_MFPAPP_RLP_INUSE_ReservationAccept*)EDAlloc (sizeof (c_MFPAPP_RLP_INUSE_ReservationAccept));
			INIT_c_MFPAPP_RLP_INUSE_ReservationAccept (sp->Data.fld_c_MFPAPP_RLP_INUSE_ReservationAccept);
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ReservationReject: {
			sp->Data.fld_c_MFPAPP_RLP_INUSE_ReservationReject = (c_MFPAPP_RLP_INUSE_ReservationReject*)EDAlloc (sizeof (c_MFPAPP_RLP_INUSE_ReservationReject));
			INIT_c_MFPAPP_RLP_INUSE_ReservationReject (sp->Data.fld_c_MFPAPP_RLP_INUSE_ReservationReject);
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_RevReservationOn: {
			sp->Data.fld_c_MFPAPP_RLP_INUSE_RevReservationOn = (c_MFPAPP_RLP_INUSE_RevReservationOn*)EDAlloc (sizeof (c_MFPAPP_RLP_INUSE_RevReservationOn));
			INIT_c_MFPAPP_RLP_INUSE_RevReservationOn (sp->Data.fld_c_MFPAPP_RLP_INUSE_RevReservationOn);
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_RevReservationOff: {
			sp->Data.fld_c_MFPAPP_RLP_INUSE_RevReservationOff = (c_MFPAPP_RLP_INUSE_RevReservationOff*)EDAlloc (sizeof (c_MFPAPP_RLP_INUSE_RevReservationOff));
			INIT_c_MFPAPP_RLP_INUSE_RevReservationOff (sp->Data.fld_c_MFPAPP_RLP_INUSE_RevReservationOff);
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_FwdReservationOff: {
			sp->Data.fld_c_MFPAPP_RLP_INUSE_FwdReservationOff = (c_MFPAPP_RLP_INUSE_FwdReservationOff*)EDAlloc (sizeof (c_MFPAPP_RLP_INUSE_FwdReservationOff));
			INIT_c_MFPAPP_RLP_INUSE_FwdReservationOff (sp->Data.fld_c_MFPAPP_RLP_INUSE_FwdReservationOff);
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_FwdReservationOn: {
			sp->Data.fld_c_MFPAPP_RLP_INUSE_FwdReservationOn = (c_MFPAPP_RLP_INUSE_FwdReservationOn*)EDAlloc (sizeof (c_MFPAPP_RLP_INUSE_FwdReservationOn));
			INIT_c_MFPAPP_RLP_INUSE_FwdReservationOn (sp->Data.fld_c_MFPAPP_RLP_INUSE_FwdReservationOn);
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_FwdReservationAck: {
			sp->Data.fld_c_MFPAPP_RLP_INUSE_FwdReservationAck = (c_MFPAPP_RLP_INUSE_FwdReservationAck*)EDAlloc (sizeof (c_MFPAPP_RLP_INUSE_FwdReservationAck));
			INIT_c_MFPAPP_RLP_INUSE_FwdReservationAck (sp->Data.fld_c_MFPAPP_RLP_INUSE_FwdReservationAck);
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_AttributeUpdateRequest: {
			sp->Data.fld_c_MFPAPP_RLP_INUSE_AttributeUpdateRequest = (c_MFPAPP_RLP_INUSE_AttributeUpdateRequest*)EDAlloc (sizeof (c_MFPAPP_RLP_INUSE_AttributeUpdateRequest));
			INIT_c_MFPAPP_RLP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_MFPAPP_RLP_INUSE_AttributeUpdateRequest);
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_AttributeUpdateAccept: {
			sp->Data.fld_c_MFPAPP_RLP_INUSE_AttributeUpdateAccept = (c_MFPAPP_RLP_INUSE_AttributeUpdateAccept*)EDAlloc (sizeof (c_MFPAPP_RLP_INUSE_AttributeUpdateAccept));
			INIT_c_MFPAPP_RLP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_MFPAPP_RLP_INUSE_AttributeUpdateAccept);
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_AttributeUpdateReject: {
			sp->Data.fld_c_MFPAPP_RLP_INUSE_AttributeUpdateReject = (c_MFPAPP_RLP_INUSE_AttributeUpdateReject*)EDAlloc (sizeof (c_MFPAPP_RLP_INUSE_AttributeUpdateReject));
			INIT_c_MFPAPP_RLP_INUSE_AttributeUpdateReject (sp->Data.fld_c_MFPAPP_RLP_INUSE_AttributeUpdateReject);
			break;
		}
		
		default:;
	}
}

void FREE_TMFPAPP_RLP_INUSE_Data (TMFPAPP_RLP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ResetTxIndication: {
			FREE_c_MFPAPP_RLP_INUSE_ResetTxIndication (sp->Data.fld_c_MFPAPP_RLP_INUSE_ResetTxIndication);
	EDFree (sp->Data.fld_c_MFPAPP_RLP_INUSE_ResetTxIndication );
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ResetRxIndication: {
			FREE_c_MFPAPP_RLP_INUSE_ResetRxIndication (sp->Data.fld_c_MFPAPP_RLP_INUSE_ResetRxIndication);
	EDFree (sp->Data.fld_c_MFPAPP_RLP_INUSE_ResetRxIndication );
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ResetTxIndicationAck: {
			FREE_c_MFPAPP_RLP_INUSE_ResetTxIndicationAck (sp->Data.fld_c_MFPAPP_RLP_INUSE_ResetTxIndicationAck);
	EDFree (sp->Data.fld_c_MFPAPP_RLP_INUSE_ResetTxIndicationAck );
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ResetTxComplete: {
			FREE_c_MFPAPP_RLP_INUSE_ResetTxComplete (sp->Data.fld_c_MFPAPP_RLP_INUSE_ResetTxComplete);
	EDFree (sp->Data.fld_c_MFPAPP_RLP_INUSE_ResetTxComplete );
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ResetRxComplete: {
			FREE_c_MFPAPP_RLP_INUSE_ResetRxComplete (sp->Data.fld_c_MFPAPP_RLP_INUSE_ResetRxComplete);
	EDFree (sp->Data.fld_c_MFPAPP_RLP_INUSE_ResetRxComplete );
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_Nak: {
			FREE_c_MFPAPP_RLP_INUSE_Nak (sp->Data.fld_c_MFPAPP_RLP_INUSE_Nak);
	EDFree (sp->Data.fld_c_MFPAPP_RLP_INUSE_Nak );
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ReservationOnRequest: {
			FREE_c_MFPAPP_RLP_INUSE_ReservationOnRequest (sp->Data.fld_c_MFPAPP_RLP_INUSE_ReservationOnRequest);
	EDFree (sp->Data.fld_c_MFPAPP_RLP_INUSE_ReservationOnRequest );
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ReservationOffRequest: {
			FREE_c_MFPAPP_RLP_INUSE_ReservationOffRequest (sp->Data.fld_c_MFPAPP_RLP_INUSE_ReservationOffRequest);
	EDFree (sp->Data.fld_c_MFPAPP_RLP_INUSE_ReservationOffRequest );
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ReservationAccept: {
			FREE_c_MFPAPP_RLP_INUSE_ReservationAccept (sp->Data.fld_c_MFPAPP_RLP_INUSE_ReservationAccept);
	EDFree (sp->Data.fld_c_MFPAPP_RLP_INUSE_ReservationAccept );
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ReservationReject: {
			FREE_c_MFPAPP_RLP_INUSE_ReservationReject (sp->Data.fld_c_MFPAPP_RLP_INUSE_ReservationReject);
	EDFree (sp->Data.fld_c_MFPAPP_RLP_INUSE_ReservationReject );
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_RevReservationOn: {
			FREE_c_MFPAPP_RLP_INUSE_RevReservationOn (sp->Data.fld_c_MFPAPP_RLP_INUSE_RevReservationOn);
	EDFree (sp->Data.fld_c_MFPAPP_RLP_INUSE_RevReservationOn );
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_RevReservationOff: {
			FREE_c_MFPAPP_RLP_INUSE_RevReservationOff (sp->Data.fld_c_MFPAPP_RLP_INUSE_RevReservationOff);
	EDFree (sp->Data.fld_c_MFPAPP_RLP_INUSE_RevReservationOff );
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_FwdReservationOff: {
			FREE_c_MFPAPP_RLP_INUSE_FwdReservationOff (sp->Data.fld_c_MFPAPP_RLP_INUSE_FwdReservationOff);
	EDFree (sp->Data.fld_c_MFPAPP_RLP_INUSE_FwdReservationOff );
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_FwdReservationOn: {
			FREE_c_MFPAPP_RLP_INUSE_FwdReservationOn (sp->Data.fld_c_MFPAPP_RLP_INUSE_FwdReservationOn);
	EDFree (sp->Data.fld_c_MFPAPP_RLP_INUSE_FwdReservationOn );
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_FwdReservationAck: {
			FREE_c_MFPAPP_RLP_INUSE_FwdReservationAck (sp->Data.fld_c_MFPAPP_RLP_INUSE_FwdReservationAck);
	EDFree (sp->Data.fld_c_MFPAPP_RLP_INUSE_FwdReservationAck );
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_AttributeUpdateRequest: {
			FREE_c_MFPAPP_RLP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_MFPAPP_RLP_INUSE_AttributeUpdateRequest);
	EDFree (sp->Data.fld_c_MFPAPP_RLP_INUSE_AttributeUpdateRequest );
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_AttributeUpdateAccept: {
			FREE_c_MFPAPP_RLP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_MFPAPP_RLP_INUSE_AttributeUpdateAccept);
	EDFree (sp->Data.fld_c_MFPAPP_RLP_INUSE_AttributeUpdateAccept );
			break;
		}
		
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_AttributeUpdateReject: {
			FREE_c_MFPAPP_RLP_INUSE_AttributeUpdateReject (sp->Data.fld_c_MFPAPP_RLP_INUSE_AttributeUpdateReject);
	EDFree (sp->Data.fld_c_MFPAPP_RLP_INUSE_AttributeUpdateReject );
			break;
		}
		
		default:;
	}

	sp->Type = ID_MFPAPP_RLP_INUSE_Unrecognized;
}

void SETPRESENT_TMFPAPP_DOSP_INUSE_Data (TMFPAPP_DOSP_INUSE_Data* sp, TMFPAPP_DOSP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TMFPAPP_DOSP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_MFPAPP_DOSP_INUSE_MFPAPP_DOSP_INUSE_DataOverSignaling: {
			sp->Data.fld_c_MFPAPP_DOSP_INUSE_DataOverSignaling = (c_MFPAPP_DOSP_INUSE_DataOverSignaling*)EDAlloc (sizeof (c_MFPAPP_DOSP_INUSE_DataOverSignaling));
			INIT_c_MFPAPP_DOSP_INUSE_DataOverSignaling (sp->Data.fld_c_MFPAPP_DOSP_INUSE_DataOverSignaling);
			break;
		}
		
		case ID_MFPAPP_DOSP_INUSE_MFPAPP_DOSP_INUSE_DataOverSignalingAck: {
			sp->Data.fld_c_MFPAPP_DOSP_INUSE_DataOverSignalingAck = (c_MFPAPP_DOSP_INUSE_DataOverSignalingAck*)EDAlloc (sizeof (c_MFPAPP_DOSP_INUSE_DataOverSignalingAck));
			INIT_c_MFPAPP_DOSP_INUSE_DataOverSignalingAck (sp->Data.fld_c_MFPAPP_DOSP_INUSE_DataOverSignalingAck);
			break;
		}
		
		default:;
	}
}

void FREE_TMFPAPP_DOSP_INUSE_Data (TMFPAPP_DOSP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_MFPAPP_DOSP_INUSE_MFPAPP_DOSP_INUSE_DataOverSignaling: {
			FREE_c_MFPAPP_DOSP_INUSE_DataOverSignaling (sp->Data.fld_c_MFPAPP_DOSP_INUSE_DataOverSignaling);
	EDFree (sp->Data.fld_c_MFPAPP_DOSP_INUSE_DataOverSignaling );
			break;
		}
		
		case ID_MFPAPP_DOSP_INUSE_MFPAPP_DOSP_INUSE_DataOverSignalingAck: {
			FREE_c_MFPAPP_DOSP_INUSE_DataOverSignalingAck (sp->Data.fld_c_MFPAPP_DOSP_INUSE_DataOverSignalingAck);
	EDFree (sp->Data.fld_c_MFPAPP_DOSP_INUSE_DataOverSignalingAck );
			break;
		}
		
		default:;
	}

	sp->Type = ID_MFPAPP_DOSP_INUSE_Unrecognized;
}

void SETPRESENT_TMFPAPP_LUP_INUSE_Data (TMFPAPP_LUP_INUSE_Data* sp, TMFPAPP_LUP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TMFPAPP_LUP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_LocationRequest: {
			sp->Data.fld_c_MFPAPP_LUP_INUSE_LocationRequest = (c_MFPAPP_LUP_INUSE_LocationRequest*)EDAlloc (sizeof (c_MFPAPP_LUP_INUSE_LocationRequest));
			INIT_c_MFPAPP_LUP_INUSE_LocationRequest (sp->Data.fld_c_MFPAPP_LUP_INUSE_LocationRequest);
			break;
		}
		
		case ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_LocationNotification: {
			sp->Data.fld_c_MFPAPP_LUP_INUSE_LocationNotification = (c_MFPAPP_LUP_INUSE_LocationNotification*)EDAlloc (sizeof (c_MFPAPP_LUP_INUSE_LocationNotification));
			INIT_c_MFPAPP_LUP_INUSE_LocationNotification (sp->Data.fld_c_MFPAPP_LUP_INUSE_LocationNotification);
			break;
		}
		
		case ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_LocationAssignment: {
			sp->Data.fld_c_MFPAPP_LUP_INUSE_LocationAssignment = (c_MFPAPP_LUP_INUSE_LocationAssignment*)EDAlloc (sizeof (c_MFPAPP_LUP_INUSE_LocationAssignment));
			INIT_c_MFPAPP_LUP_INUSE_LocationAssignment (sp->Data.fld_c_MFPAPP_LUP_INUSE_LocationAssignment);
			break;
		}
		
		case ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_LocationComplete: {
			sp->Data.fld_c_MFPAPP_LUP_INUSE_LocationComplete = (c_MFPAPP_LUP_INUSE_LocationComplete*)EDAlloc (sizeof (c_MFPAPP_LUP_INUSE_LocationComplete));
			INIT_c_MFPAPP_LUP_INUSE_LocationComplete (sp->Data.fld_c_MFPAPP_LUP_INUSE_LocationComplete);
			break;
		}
		
		case ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_StorageBLOBRequest: {
			sp->Data.fld_c_MFPAPP_LUP_INUSE_StorageBLOBRequest = (c_MFPAPP_LUP_INUSE_StorageBLOBRequest*)EDAlloc (sizeof (c_MFPAPP_LUP_INUSE_StorageBLOBRequest));
			INIT_c_MFPAPP_LUP_INUSE_StorageBLOBRequest (sp->Data.fld_c_MFPAPP_LUP_INUSE_StorageBLOBRequest);
			break;
		}
		
		case ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_StorageBLOBNotification: {
			sp->Data.fld_c_MFPAPP_LUP_INUSE_StorageBLOBNotification = (c_MFPAPP_LUP_INUSE_StorageBLOBNotification*)EDAlloc (sizeof (c_MFPAPP_LUP_INUSE_StorageBLOBNotification));
			INIT_c_MFPAPP_LUP_INUSE_StorageBLOBNotification (sp->Data.fld_c_MFPAPP_LUP_INUSE_StorageBLOBNotification);
			break;
		}
		
		case ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_StorageBLOBAssignment: {
			sp->Data.fld_c_MFPAPP_LUP_INUSE_StorageBLOBAssignment = (c_MFPAPP_LUP_INUSE_StorageBLOBAssignment*)EDAlloc (sizeof (c_MFPAPP_LUP_INUSE_StorageBLOBAssignment));
			INIT_c_MFPAPP_LUP_INUSE_StorageBLOBAssignment (sp->Data.fld_c_MFPAPP_LUP_INUSE_StorageBLOBAssignment);
			break;
		}
		
		case ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_StorageBLOBComplete: {
			sp->Data.fld_c_MFPAPP_LUP_INUSE_StorageBLOBComplete = (c_MFPAPP_LUP_INUSE_StorageBLOBComplete*)EDAlloc (sizeof (c_MFPAPP_LUP_INUSE_StorageBLOBComplete));
			INIT_c_MFPAPP_LUP_INUSE_StorageBLOBComplete (sp->Data.fld_c_MFPAPP_LUP_INUSE_StorageBLOBComplete);
			break;
		}
		
		default:;
	}
}

void FREE_TMFPAPP_LUP_INUSE_Data (TMFPAPP_LUP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_LocationRequest: {
			FREE_c_MFPAPP_LUP_INUSE_LocationRequest (sp->Data.fld_c_MFPAPP_LUP_INUSE_LocationRequest);
	EDFree (sp->Data.fld_c_MFPAPP_LUP_INUSE_LocationRequest );
			break;
		}
		
		case ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_LocationNotification: {
			FREE_c_MFPAPP_LUP_INUSE_LocationNotification (sp->Data.fld_c_MFPAPP_LUP_INUSE_LocationNotification);
	EDFree (sp->Data.fld_c_MFPAPP_LUP_INUSE_LocationNotification );
			break;
		}
		
		case ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_LocationAssignment: {
			FREE_c_MFPAPP_LUP_INUSE_LocationAssignment (sp->Data.fld_c_MFPAPP_LUP_INUSE_LocationAssignment);
	EDFree (sp->Data.fld_c_MFPAPP_LUP_INUSE_LocationAssignment );
			break;
		}
		
		case ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_LocationComplete: {
			FREE_c_MFPAPP_LUP_INUSE_LocationComplete (sp->Data.fld_c_MFPAPP_LUP_INUSE_LocationComplete);
	EDFree (sp->Data.fld_c_MFPAPP_LUP_INUSE_LocationComplete );
			break;
		}
		
		case ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_StorageBLOBRequest: {
			FREE_c_MFPAPP_LUP_INUSE_StorageBLOBRequest (sp->Data.fld_c_MFPAPP_LUP_INUSE_StorageBLOBRequest);
	EDFree (sp->Data.fld_c_MFPAPP_LUP_INUSE_StorageBLOBRequest );
			break;
		}
		
		case ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_StorageBLOBNotification: {
			FREE_c_MFPAPP_LUP_INUSE_StorageBLOBNotification (sp->Data.fld_c_MFPAPP_LUP_INUSE_StorageBLOBNotification);
	EDFree (sp->Data.fld_c_MFPAPP_LUP_INUSE_StorageBLOBNotification );
			break;
		}
		
		case ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_StorageBLOBAssignment: {
			FREE_c_MFPAPP_LUP_INUSE_StorageBLOBAssignment (sp->Data.fld_c_MFPAPP_LUP_INUSE_StorageBLOBAssignment);
	EDFree (sp->Data.fld_c_MFPAPP_LUP_INUSE_StorageBLOBAssignment );
			break;
		}
		
		case ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_StorageBLOBComplete: {
			FREE_c_MFPAPP_LUP_INUSE_StorageBLOBComplete (sp->Data.fld_c_MFPAPP_LUP_INUSE_StorageBLOBComplete);
	EDFree (sp->Data.fld_c_MFPAPP_LUP_INUSE_StorageBLOBComplete );
			break;
		}
		
		default:;
	}

	sp->Type = ID_MFPAPP_LUP_INUSE_Unrecognized;
}

void SETPRESENT_TMFPAPP_FCP_INUSE_Data (TMFPAPP_FCP_INUSE_Data* sp, TMFPAPP_FCP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TMFPAPP_FCP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_MFPAPP_FCP_INUSE_MFPAPP_FCP_INUSE_XonRequest: {
			sp->Data.fld_c_MFPAPP_FCP_INUSE_XonRequest = (c_MFPAPP_FCP_INUSE_XonRequest*)EDAlloc (sizeof (c_MFPAPP_FCP_INUSE_XonRequest));
			INIT_c_MFPAPP_FCP_INUSE_XonRequest (sp->Data.fld_c_MFPAPP_FCP_INUSE_XonRequest);
			break;
		}
		
		case ID_MFPAPP_FCP_INUSE_MFPAPP_FCP_INUSE_XonResponse: {
			sp->Data.fld_c_MFPAPP_FCP_INUSE_XonResponse = (c_MFPAPP_FCP_INUSE_XonResponse*)EDAlloc (sizeof (c_MFPAPP_FCP_INUSE_XonResponse));
			INIT_c_MFPAPP_FCP_INUSE_XonResponse (sp->Data.fld_c_MFPAPP_FCP_INUSE_XonResponse);
			break;
		}
		
		case ID_MFPAPP_FCP_INUSE_MFPAPP_FCP_INUSE_XoffRequest: {
			sp->Data.fld_c_MFPAPP_FCP_INUSE_XoffRequest = (c_MFPAPP_FCP_INUSE_XoffRequest*)EDAlloc (sizeof (c_MFPAPP_FCP_INUSE_XoffRequest));
			INIT_c_MFPAPP_FCP_INUSE_XoffRequest (sp->Data.fld_c_MFPAPP_FCP_INUSE_XoffRequest);
			break;
		}
		
		case ID_MFPAPP_FCP_INUSE_MFPAPP_FCP_INUSE_XoffResponse: {
			sp->Data.fld_c_MFPAPP_FCP_INUSE_XoffResponse = (c_MFPAPP_FCP_INUSE_XoffResponse*)EDAlloc (sizeof (c_MFPAPP_FCP_INUSE_XoffResponse));
			INIT_c_MFPAPP_FCP_INUSE_XoffResponse (sp->Data.fld_c_MFPAPP_FCP_INUSE_XoffResponse);
			break;
		}
		
		case ID_MFPAPP_FCP_INUSE_MFPAPP_FCP_INUSE_DataReady: {
			sp->Data.fld_c_MFPAPP_FCP_INUSE_DataReady = (c_MFPAPP_FCP_INUSE_DataReady*)EDAlloc (sizeof (c_MFPAPP_FCP_INUSE_DataReady));
			INIT_c_MFPAPP_FCP_INUSE_DataReady (sp->Data.fld_c_MFPAPP_FCP_INUSE_DataReady);
			break;
		}
		
		case ID_MFPAPP_FCP_INUSE_MFPAPP_FCP_INUSE_DataReadyAck: {
			sp->Data.fld_c_MFPAPP_FCP_INUSE_DataReadyAck = (c_MFPAPP_FCP_INUSE_DataReadyAck*)EDAlloc (sizeof (c_MFPAPP_FCP_INUSE_DataReadyAck));
			INIT_c_MFPAPP_FCP_INUSE_DataReadyAck (sp->Data.fld_c_MFPAPP_FCP_INUSE_DataReadyAck);
			break;
		}
		
		default:;
	}
}

void FREE_TMFPAPP_FCP_INUSE_Data (TMFPAPP_FCP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_MFPAPP_FCP_INUSE_MFPAPP_FCP_INUSE_XonRequest: {
			FREE_c_MFPAPP_FCP_INUSE_XonRequest (sp->Data.fld_c_MFPAPP_FCP_INUSE_XonRequest);
	EDFree (sp->Data.fld_c_MFPAPP_FCP_INUSE_XonRequest );
			break;
		}
		
		case ID_MFPAPP_FCP_INUSE_MFPAPP_FCP_INUSE_XonResponse: {
			FREE_c_MFPAPP_FCP_INUSE_XonResponse (sp->Data.fld_c_MFPAPP_FCP_INUSE_XonResponse);
	EDFree (sp->Data.fld_c_MFPAPP_FCP_INUSE_XonResponse );
			break;
		}
		
		case ID_MFPAPP_FCP_INUSE_MFPAPP_FCP_INUSE_XoffRequest: {
			FREE_c_MFPAPP_FCP_INUSE_XoffRequest (sp->Data.fld_c_MFPAPP_FCP_INUSE_XoffRequest);
	EDFree (sp->Data.fld_c_MFPAPP_FCP_INUSE_XoffRequest );
			break;
		}
		
		case ID_MFPAPP_FCP_INUSE_MFPAPP_FCP_INUSE_XoffResponse: {
			FREE_c_MFPAPP_FCP_INUSE_XoffResponse (sp->Data.fld_c_MFPAPP_FCP_INUSE_XoffResponse);
	EDFree (sp->Data.fld_c_MFPAPP_FCP_INUSE_XoffResponse );
			break;
		}
		
		case ID_MFPAPP_FCP_INUSE_MFPAPP_FCP_INUSE_DataReady: {
			FREE_c_MFPAPP_FCP_INUSE_DataReady (sp->Data.fld_c_MFPAPP_FCP_INUSE_DataReady);
	EDFree (sp->Data.fld_c_MFPAPP_FCP_INUSE_DataReady );
			break;
		}
		
		case ID_MFPAPP_FCP_INUSE_MFPAPP_FCP_INUSE_DataReadyAck: {
			FREE_c_MFPAPP_FCP_INUSE_DataReadyAck (sp->Data.fld_c_MFPAPP_FCP_INUSE_DataReadyAck);
	EDFree (sp->Data.fld_c_MFPAPP_FCP_INUSE_DataReadyAck );
			break;
		}
		
		default:;
	}

	sp->Type = ID_MFPAPP_FCP_INUSE_Unrecognized;
}

void SETPRESENT_TSTREAM_DSP_INCFG_Data (TSTREAM_DSP_INCFG_Data* sp, TSTREAM_DSP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TSTREAM_DSP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_STREAM_DSP_INCFG_STREAM_DSP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_STREAM_DSP_INCFG_ConfigurationRequest = (c_STREAM_DSP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_STREAM_DSP_INCFG_ConfigurationRequest));
			INIT_c_STREAM_DSP_INCFG_ConfigurationRequest (sp->Data.fld_c_STREAM_DSP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_STREAM_DSP_INCFG_STREAM_DSP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_STREAM_DSP_INCFG_ConfigurationResponse = (c_STREAM_DSP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_STREAM_DSP_INCFG_ConfigurationResponse));
			INIT_c_STREAM_DSP_INCFG_ConfigurationResponse (sp->Data.fld_c_STREAM_DSP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TSTREAM_DSP_INCFG_Data (TSTREAM_DSP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_STREAM_DSP_INCFG_STREAM_DSP_INCFG_ConfigurationRequest: {
			FREE_c_STREAM_DSP_INCFG_ConfigurationRequest (sp->Data.fld_c_STREAM_DSP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_STREAM_DSP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_STREAM_DSP_INCFG_STREAM_DSP_INCFG_ConfigurationResponse: {
			FREE_c_STREAM_DSP_INCFG_ConfigurationResponse (sp->Data.fld_c_STREAM_DSP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_STREAM_DSP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_STREAM_DSP_INCFG_Unrecognized;
}

void SETPRESENT_TSTREAM_GVSP_INCFG_Data (TSTREAM_GVSP_INCFG_Data* sp, TSTREAM_GVSP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TSTREAM_GVSP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_STREAM_GVSP_INCFG_STREAM_GVSP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_STREAM_GVSP_INCFG_ConfigurationRequest = (c_STREAM_GVSP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_STREAM_GVSP_INCFG_ConfigurationRequest));
			INIT_c_STREAM_GVSP_INCFG_ConfigurationRequest (sp->Data.fld_c_STREAM_GVSP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_STREAM_GVSP_INCFG_STREAM_GVSP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_STREAM_GVSP_INCFG_ConfigurationResponse = (c_STREAM_GVSP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_STREAM_GVSP_INCFG_ConfigurationResponse));
			INIT_c_STREAM_GVSP_INCFG_ConfigurationResponse (sp->Data.fld_c_STREAM_GVSP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TSTREAM_GVSP_INCFG_Data (TSTREAM_GVSP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_STREAM_GVSP_INCFG_STREAM_GVSP_INCFG_ConfigurationRequest: {
			FREE_c_STREAM_GVSP_INCFG_ConfigurationRequest (sp->Data.fld_c_STREAM_GVSP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_STREAM_GVSP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_STREAM_GVSP_INCFG_STREAM_GVSP_INCFG_ConfigurationResponse: {
			FREE_c_STREAM_GVSP_INCFG_ConfigurationResponse (sp->Data.fld_c_STREAM_GVSP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_STREAM_GVSP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_STREAM_GVSP_INCFG_Unrecognized;
}

void SETPRESENT_TSESSION_DSMP_INCFG_Data (TSESSION_DSMP_INCFG_Data* sp, TSESSION_DSMP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TSESSION_DSMP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_SESSION_DSMP_INCFG_SESSION_DSMP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_SESSION_DSMP_INCFG_ConfigurationRequest = (c_SESSION_DSMP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_SESSION_DSMP_INCFG_ConfigurationRequest));
			INIT_c_SESSION_DSMP_INCFG_ConfigurationRequest (sp->Data.fld_c_SESSION_DSMP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_SESSION_DSMP_INCFG_SESSION_DSMP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_SESSION_DSMP_INCFG_ConfigurationResponse = (c_SESSION_DSMP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_SESSION_DSMP_INCFG_ConfigurationResponse));
			INIT_c_SESSION_DSMP_INCFG_ConfigurationResponse (sp->Data.fld_c_SESSION_DSMP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TSESSION_DSMP_INCFG_Data (TSESSION_DSMP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_SESSION_DSMP_INCFG_SESSION_DSMP_INCFG_ConfigurationRequest: {
			FREE_c_SESSION_DSMP_INCFG_ConfigurationRequest (sp->Data.fld_c_SESSION_DSMP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_SESSION_DSMP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_SESSION_DSMP_INCFG_SESSION_DSMP_INCFG_ConfigurationResponse: {
			FREE_c_SESSION_DSMP_INCFG_ConfigurationResponse (sp->Data.fld_c_SESSION_DSMP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_SESSION_DSMP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_SESSION_DSMP_INCFG_Unrecognized;
}

void SETPRESENT_TSESSION_DSMP_INUSE_Data (TSESSION_DSMP_INUSE_Data* sp, TSESSION_DSMP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TSESSION_DSMP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_SESSION_DSMP_INUSE_SESSION_DSMP_INUSE_SessionClose: {
			sp->Data.fld_c_SESSION_DSMP_INUSE_SessionClose = (c_SESSION_DSMP_INUSE_SessionClose*)EDAlloc (sizeof (c_SESSION_DSMP_INUSE_SessionClose));
			INIT_c_SESSION_DSMP_INUSE_SessionClose (sp->Data.fld_c_SESSION_DSMP_INUSE_SessionClose);
			break;
		}
		
		case ID_SESSION_DSMP_INUSE_SESSION_DSMP_INUSE_KeepAliveRequest: {
			sp->Data.fld_c_SESSION_DSMP_INUSE_KeepAliveRequest = (c_SESSION_DSMP_INUSE_KeepAliveRequest*)EDAlloc (sizeof (c_SESSION_DSMP_INUSE_KeepAliveRequest));
			INIT_c_SESSION_DSMP_INUSE_KeepAliveRequest (sp->Data.fld_c_SESSION_DSMP_INUSE_KeepAliveRequest);
			break;
		}
		
		case ID_SESSION_DSMP_INUSE_SESSION_DSMP_INUSE_KeepAliveResponse: {
			sp->Data.fld_c_SESSION_DSMP_INUSE_KeepAliveResponse = (c_SESSION_DSMP_INUSE_KeepAliveResponse*)EDAlloc (sizeof (c_SESSION_DSMP_INUSE_KeepAliveResponse));
			INIT_c_SESSION_DSMP_INUSE_KeepAliveResponse (sp->Data.fld_c_SESSION_DSMP_INUSE_KeepAliveResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TSESSION_DSMP_INUSE_Data (TSESSION_DSMP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_SESSION_DSMP_INUSE_SESSION_DSMP_INUSE_SessionClose: {
			FREE_c_SESSION_DSMP_INUSE_SessionClose (sp->Data.fld_c_SESSION_DSMP_INUSE_SessionClose);
	EDFree (sp->Data.fld_c_SESSION_DSMP_INUSE_SessionClose );
			break;
		}
		
		case ID_SESSION_DSMP_INUSE_SESSION_DSMP_INUSE_KeepAliveRequest: {
			FREE_c_SESSION_DSMP_INUSE_KeepAliveRequest (sp->Data.fld_c_SESSION_DSMP_INUSE_KeepAliveRequest);
	EDFree (sp->Data.fld_c_SESSION_DSMP_INUSE_KeepAliveRequest );
			break;
		}
		
		case ID_SESSION_DSMP_INUSE_SESSION_DSMP_INUSE_KeepAliveResponse: {
			FREE_c_SESSION_DSMP_INUSE_KeepAliveResponse (sp->Data.fld_c_SESSION_DSMP_INUSE_KeepAliveResponse);
	EDFree (sp->Data.fld_c_SESSION_DSMP_INUSE_KeepAliveResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_SESSION_DSMP_INUSE_Unrecognized;
}

void SETPRESENT_TSESSION_DAMP_INCFG_Data (TSESSION_DAMP_INCFG_Data* sp, TSESSION_DAMP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TSESSION_DAMP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_SESSION_DAMP_INCFG_SESSION_DAMP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_SESSION_DAMP_INCFG_ConfigurationRequest = (c_SESSION_DAMP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_SESSION_DAMP_INCFG_ConfigurationRequest));
			INIT_c_SESSION_DAMP_INCFG_ConfigurationRequest (sp->Data.fld_c_SESSION_DAMP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_SESSION_DAMP_INCFG_SESSION_DAMP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_SESSION_DAMP_INCFG_ConfigurationResponse = (c_SESSION_DAMP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_SESSION_DAMP_INCFG_ConfigurationResponse));
			INIT_c_SESSION_DAMP_INCFG_ConfigurationResponse (sp->Data.fld_c_SESSION_DAMP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TSESSION_DAMP_INCFG_Data (TSESSION_DAMP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_SESSION_DAMP_INCFG_SESSION_DAMP_INCFG_ConfigurationRequest: {
			FREE_c_SESSION_DAMP_INCFG_ConfigurationRequest (sp->Data.fld_c_SESSION_DAMP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_SESSION_DAMP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_SESSION_DAMP_INCFG_SESSION_DAMP_INCFG_ConfigurationResponse: {
			FREE_c_SESSION_DAMP_INCFG_ConfigurationResponse (sp->Data.fld_c_SESSION_DAMP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_SESSION_DAMP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_SESSION_DAMP_INCFG_Unrecognized;
}

void SETPRESENT_TSESSION_DAMP_INUSE_Data (TSESSION_DAMP_INUSE_Data* sp, TSESSION_DAMP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TSESSION_DAMP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_UATIRequest: {
			sp->Data.fld_c_SESSION_DAMP_INUSE_UATIRequest = (c_SESSION_DAMP_INUSE_UATIRequest*)EDAlloc (sizeof (c_SESSION_DAMP_INUSE_UATIRequest));
			INIT_c_SESSION_DAMP_INUSE_UATIRequest (sp->Data.fld_c_SESSION_DAMP_INUSE_UATIRequest);
			break;
		}
		
		case ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_UATIAssignment: {
			sp->Data.fld_c_SESSION_DAMP_INUSE_UATIAssignment = (c_SESSION_DAMP_INUSE_UATIAssignment*)EDAlloc (sizeof (c_SESSION_DAMP_INUSE_UATIAssignment));
			INIT_c_SESSION_DAMP_INUSE_UATIAssignment (sp->Data.fld_c_SESSION_DAMP_INUSE_UATIAssignment);
			break;
		}
		
		case ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_UATIComplete: {
			sp->Data.fld_c_SESSION_DAMP_INUSE_UATIComplete = (c_SESSION_DAMP_INUSE_UATIComplete*)EDAlloc (sizeof (c_SESSION_DAMP_INUSE_UATIComplete));
			INIT_c_SESSION_DAMP_INUSE_UATIComplete (sp->Data.fld_c_SESSION_DAMP_INUSE_UATIComplete);
			break;
		}
		
		case ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_HardwareIDRequest: {
			sp->Data.fld_c_SESSION_DAMP_INUSE_HardwareIDRequest = (c_SESSION_DAMP_INUSE_HardwareIDRequest*)EDAlloc (sizeof (c_SESSION_DAMP_INUSE_HardwareIDRequest));
			INIT_c_SESSION_DAMP_INUSE_HardwareIDRequest (sp->Data.fld_c_SESSION_DAMP_INUSE_HardwareIDRequest);
			break;
		}
		
		case ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_HardwareIDResponse: {
			sp->Data.fld_c_SESSION_DAMP_INUSE_HardwareIDResponse = (c_SESSION_DAMP_INUSE_HardwareIDResponse*)EDAlloc (sizeof (c_SESSION_DAMP_INUSE_HardwareIDResponse));
			INIT_c_SESSION_DAMP_INUSE_HardwareIDResponse (sp->Data.fld_c_SESSION_DAMP_INUSE_HardwareIDResponse);
			break;
		}
		
		case ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_AttributeUpdateRequest: {
			sp->Data.fld_c_SESSION_DAMP_INUSE_AttributeUpdateRequest = (c_SESSION_DAMP_INUSE_AttributeUpdateRequest*)EDAlloc (sizeof (c_SESSION_DAMP_INUSE_AttributeUpdateRequest));
			INIT_c_SESSION_DAMP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_SESSION_DAMP_INUSE_AttributeUpdateRequest);
			break;
		}
		
		case ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_AttributeUpdateAccept: {
			sp->Data.fld_c_SESSION_DAMP_INUSE_AttributeUpdateAccept = (c_SESSION_DAMP_INUSE_AttributeUpdateAccept*)EDAlloc (sizeof (c_SESSION_DAMP_INUSE_AttributeUpdateAccept));
			INIT_c_SESSION_DAMP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_SESSION_DAMP_INUSE_AttributeUpdateAccept);
			break;
		}
		
		case ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_AttributeUpdateReject: {
			sp->Data.fld_c_SESSION_DAMP_INUSE_AttributeUpdateReject = (c_SESSION_DAMP_INUSE_AttributeUpdateReject*)EDAlloc (sizeof (c_SESSION_DAMP_INUSE_AttributeUpdateReject));
			INIT_c_SESSION_DAMP_INUSE_AttributeUpdateReject (sp->Data.fld_c_SESSION_DAMP_INUSE_AttributeUpdateReject);
			break;
		}
		
		default:;
	}
}

void FREE_TSESSION_DAMP_INUSE_Data (TSESSION_DAMP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_UATIRequest: {
			FREE_c_SESSION_DAMP_INUSE_UATIRequest (sp->Data.fld_c_SESSION_DAMP_INUSE_UATIRequest);
	EDFree (sp->Data.fld_c_SESSION_DAMP_INUSE_UATIRequest );
			break;
		}
		
		case ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_UATIAssignment: {
			FREE_c_SESSION_DAMP_INUSE_UATIAssignment (sp->Data.fld_c_SESSION_DAMP_INUSE_UATIAssignment);
	EDFree (sp->Data.fld_c_SESSION_DAMP_INUSE_UATIAssignment );
			break;
		}
		
		case ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_UATIComplete: {
			FREE_c_SESSION_DAMP_INUSE_UATIComplete (sp->Data.fld_c_SESSION_DAMP_INUSE_UATIComplete);
	EDFree (sp->Data.fld_c_SESSION_DAMP_INUSE_UATIComplete );
			break;
		}
		
		case ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_HardwareIDRequest: {
			FREE_c_SESSION_DAMP_INUSE_HardwareIDRequest (sp->Data.fld_c_SESSION_DAMP_INUSE_HardwareIDRequest);
	EDFree (sp->Data.fld_c_SESSION_DAMP_INUSE_HardwareIDRequest );
			break;
		}
		
		case ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_HardwareIDResponse: {
			FREE_c_SESSION_DAMP_INUSE_HardwareIDResponse (sp->Data.fld_c_SESSION_DAMP_INUSE_HardwareIDResponse);
	EDFree (sp->Data.fld_c_SESSION_DAMP_INUSE_HardwareIDResponse );
			break;
		}
		
		case ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_AttributeUpdateRequest: {
			FREE_c_SESSION_DAMP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_SESSION_DAMP_INUSE_AttributeUpdateRequest);
	EDFree (sp->Data.fld_c_SESSION_DAMP_INUSE_AttributeUpdateRequest );
			break;
		}
		
		case ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_AttributeUpdateAccept: {
			FREE_c_SESSION_DAMP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_SESSION_DAMP_INUSE_AttributeUpdateAccept);
	EDFree (sp->Data.fld_c_SESSION_DAMP_INUSE_AttributeUpdateAccept );
			break;
		}
		
		case ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_AttributeUpdateReject: {
			FREE_c_SESSION_DAMP_INUSE_AttributeUpdateReject (sp->Data.fld_c_SESSION_DAMP_INUSE_AttributeUpdateReject);
	EDFree (sp->Data.fld_c_SESSION_DAMP_INUSE_AttributeUpdateReject );
			break;
		}
		
		default:;
	}

	sp->Type = ID_SESSION_DAMP_INUSE_Unrecognized;
}

void SETPRESENT_TSESSION_DSCP_INUSE_Data (TSESSION_DSCP_INUSE_Data* sp, TSESSION_DSCP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TSESSION_DSCP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_ConfigurationComplete: {
			sp->Data.fld_c_SESSION_DSCP_INUSE_ConfigurationComplete = (c_SESSION_DSCP_INUSE_ConfigurationComplete*)EDAlloc (sizeof (c_SESSION_DSCP_INUSE_ConfigurationComplete));
			INIT_c_SESSION_DSCP_INUSE_ConfigurationComplete (sp->Data.fld_c_SESSION_DSCP_INUSE_ConfigurationComplete);
			break;
		}
		
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_ConfigurationStart: {
			sp->Data.fld_c_SESSION_DSCP_INUSE_ConfigurationStart = (c_SESSION_DSCP_INUSE_ConfigurationStart*)EDAlloc (sizeof (c_SESSION_DSCP_INUSE_ConfigurationStart));
			INIT_c_SESSION_DSCP_INUSE_ConfigurationStart (sp->Data.fld_c_SESSION_DSCP_INUSE_ConfigurationStart);
			break;
		}
		
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_ConfigurationRequest: {
			sp->Data.fld_c_SESSION_DSCP_INUSE_ConfigurationRequest = (c_SESSION_DSCP_INUSE_ConfigurationRequest*)EDAlloc (sizeof (c_SESSION_DSCP_INUSE_ConfigurationRequest));
			INIT_c_SESSION_DSCP_INUSE_ConfigurationRequest (sp->Data.fld_c_SESSION_DSCP_INUSE_ConfigurationRequest);
			break;
		}
		
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_ConfigurationResponse: {
			sp->Data.fld_c_SESSION_DSCP_INUSE_ConfigurationResponse = (c_SESSION_DSCP_INUSE_ConfigurationResponse*)EDAlloc (sizeof (c_SESSION_DSCP_INUSE_ConfigurationResponse));
			INIT_c_SESSION_DSCP_INUSE_ConfigurationResponse (sp->Data.fld_c_SESSION_DSCP_INUSE_ConfigurationResponse);
			break;
		}
		
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_SoftConfigurationComplete: {
			sp->Data.fld_c_SESSION_DSCP_INUSE_SoftConfigurationComplete = (c_SESSION_DSCP_INUSE_SoftConfigurationComplete*)EDAlloc (sizeof (c_SESSION_DSCP_INUSE_SoftConfigurationComplete));
			INIT_c_SESSION_DSCP_INUSE_SoftConfigurationComplete (sp->Data.fld_c_SESSION_DSCP_INUSE_SoftConfigurationComplete);
			break;
		}
		
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_LockConfiguration: {
			sp->Data.fld_c_SESSION_DSCP_INUSE_LockConfiguration = (c_SESSION_DSCP_INUSE_LockConfiguration*)EDAlloc (sizeof (c_SESSION_DSCP_INUSE_LockConfiguration));
			INIT_c_SESSION_DSCP_INUSE_LockConfiguration (sp->Data.fld_c_SESSION_DSCP_INUSE_LockConfiguration);
			break;
		}
		
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_LockConfigurationAck: {
			sp->Data.fld_c_SESSION_DSCP_INUSE_LockConfigurationAck = (c_SESSION_DSCP_INUSE_LockConfigurationAck*)EDAlloc (sizeof (c_SESSION_DSCP_INUSE_LockConfigurationAck));
			INIT_c_SESSION_DSCP_INUSE_LockConfigurationAck (sp->Data.fld_c_SESSION_DSCP_INUSE_LockConfigurationAck);
			break;
		}
		
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_UnLockConfiguration: {
			sp->Data.fld_c_SESSION_DSCP_INUSE_UnLockConfiguration = (c_SESSION_DSCP_INUSE_UnLockConfiguration*)EDAlloc (sizeof (c_SESSION_DSCP_INUSE_UnLockConfiguration));
			INIT_c_SESSION_DSCP_INUSE_UnLockConfiguration (sp->Data.fld_c_SESSION_DSCP_INUSE_UnLockConfiguration);
			break;
		}
		
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_UnLockConfigurationAck: {
			sp->Data.fld_c_SESSION_DSCP_INUSE_UnLockConfigurationAck = (c_SESSION_DSCP_INUSE_UnLockConfigurationAck*)EDAlloc (sizeof (c_SESSION_DSCP_INUSE_UnLockConfigurationAck));
			INIT_c_SESSION_DSCP_INUSE_UnLockConfigurationAck (sp->Data.fld_c_SESSION_DSCP_INUSE_UnLockConfigurationAck);
			break;
		}
		
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_DeletePersonality: {
			sp->Data.fld_c_SESSION_DSCP_INUSE_DeletePersonality = (c_SESSION_DSCP_INUSE_DeletePersonality*)EDAlloc (sizeof (c_SESSION_DSCP_INUSE_DeletePersonality));
			INIT_c_SESSION_DSCP_INUSE_DeletePersonality (sp->Data.fld_c_SESSION_DSCP_INUSE_DeletePersonality);
			break;
		}
		
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_DeletePersonalityAck: {
			sp->Data.fld_c_SESSION_DSCP_INUSE_DeletePersonalityAck = (c_SESSION_DSCP_INUSE_DeletePersonalityAck*)EDAlloc (sizeof (c_SESSION_DSCP_INUSE_DeletePersonalityAck));
			INIT_c_SESSION_DSCP_INUSE_DeletePersonalityAck (sp->Data.fld_c_SESSION_DSCP_INUSE_DeletePersonalityAck);
			break;
		}
		
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_AttributeUpdateRequest: {
			sp->Data.fld_c_SESSION_DSCP_INUSE_AttributeUpdateRequest = (c_SESSION_DSCP_INUSE_AttributeUpdateRequest*)EDAlloc (sizeof (c_SESSION_DSCP_INUSE_AttributeUpdateRequest));
			INIT_c_SESSION_DSCP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_SESSION_DSCP_INUSE_AttributeUpdateRequest);
			break;
		}
		
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_AttributeUpdateAccept: {
			sp->Data.fld_c_SESSION_DSCP_INUSE_AttributeUpdateAccept = (c_SESSION_DSCP_INUSE_AttributeUpdateAccept*)EDAlloc (sizeof (c_SESSION_DSCP_INUSE_AttributeUpdateAccept));
			INIT_c_SESSION_DSCP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_SESSION_DSCP_INUSE_AttributeUpdateAccept);
			break;
		}
		
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_AttributeUpdateReject: {
			sp->Data.fld_c_SESSION_DSCP_INUSE_AttributeUpdateReject = (c_SESSION_DSCP_INUSE_AttributeUpdateReject*)EDAlloc (sizeof (c_SESSION_DSCP_INUSE_AttributeUpdateReject));
			INIT_c_SESSION_DSCP_INUSE_AttributeUpdateReject (sp->Data.fld_c_SESSION_DSCP_INUSE_AttributeUpdateReject);
			break;
		}
		
		default:;
	}
}

void FREE_TSESSION_DSCP_INUSE_Data (TSESSION_DSCP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_ConfigurationComplete: {
			FREE_c_SESSION_DSCP_INUSE_ConfigurationComplete (sp->Data.fld_c_SESSION_DSCP_INUSE_ConfigurationComplete);
	EDFree (sp->Data.fld_c_SESSION_DSCP_INUSE_ConfigurationComplete );
			break;
		}
		
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_ConfigurationStart: {
			FREE_c_SESSION_DSCP_INUSE_ConfigurationStart (sp->Data.fld_c_SESSION_DSCP_INUSE_ConfigurationStart);
	EDFree (sp->Data.fld_c_SESSION_DSCP_INUSE_ConfigurationStart );
			break;
		}
		
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_ConfigurationRequest: {
			FREE_c_SESSION_DSCP_INUSE_ConfigurationRequest (sp->Data.fld_c_SESSION_DSCP_INUSE_ConfigurationRequest);
	EDFree (sp->Data.fld_c_SESSION_DSCP_INUSE_ConfigurationRequest );
			break;
		}
		
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_ConfigurationResponse: {
			FREE_c_SESSION_DSCP_INUSE_ConfigurationResponse (sp->Data.fld_c_SESSION_DSCP_INUSE_ConfigurationResponse);
	EDFree (sp->Data.fld_c_SESSION_DSCP_INUSE_ConfigurationResponse );
			break;
		}
		
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_SoftConfigurationComplete: {
			FREE_c_SESSION_DSCP_INUSE_SoftConfigurationComplete (sp->Data.fld_c_SESSION_DSCP_INUSE_SoftConfigurationComplete);
	EDFree (sp->Data.fld_c_SESSION_DSCP_INUSE_SoftConfigurationComplete );
			break;
		}
		
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_LockConfiguration: {
			FREE_c_SESSION_DSCP_INUSE_LockConfiguration (sp->Data.fld_c_SESSION_DSCP_INUSE_LockConfiguration);
	EDFree (sp->Data.fld_c_SESSION_DSCP_INUSE_LockConfiguration );
			break;
		}
		
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_LockConfigurationAck: {
			FREE_c_SESSION_DSCP_INUSE_LockConfigurationAck (sp->Data.fld_c_SESSION_DSCP_INUSE_LockConfigurationAck);
	EDFree (sp->Data.fld_c_SESSION_DSCP_INUSE_LockConfigurationAck );
			break;
		}
		
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_UnLockConfiguration: {
			FREE_c_SESSION_DSCP_INUSE_UnLockConfiguration (sp->Data.fld_c_SESSION_DSCP_INUSE_UnLockConfiguration);
	EDFree (sp->Data.fld_c_SESSION_DSCP_INUSE_UnLockConfiguration );
			break;
		}
		
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_UnLockConfigurationAck: {
			FREE_c_SESSION_DSCP_INUSE_UnLockConfigurationAck (sp->Data.fld_c_SESSION_DSCP_INUSE_UnLockConfigurationAck);
	EDFree (sp->Data.fld_c_SESSION_DSCP_INUSE_UnLockConfigurationAck );
			break;
		}
		
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_DeletePersonality: {
			FREE_c_SESSION_DSCP_INUSE_DeletePersonality (sp->Data.fld_c_SESSION_DSCP_INUSE_DeletePersonality);
	EDFree (sp->Data.fld_c_SESSION_DSCP_INUSE_DeletePersonality );
			break;
		}
		
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_DeletePersonalityAck: {
			FREE_c_SESSION_DSCP_INUSE_DeletePersonalityAck (sp->Data.fld_c_SESSION_DSCP_INUSE_DeletePersonalityAck);
	EDFree (sp->Data.fld_c_SESSION_DSCP_INUSE_DeletePersonalityAck );
			break;
		}
		
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_AttributeUpdateRequest: {
			FREE_c_SESSION_DSCP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_SESSION_DSCP_INUSE_AttributeUpdateRequest);
	EDFree (sp->Data.fld_c_SESSION_DSCP_INUSE_AttributeUpdateRequest );
			break;
		}
		
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_AttributeUpdateAccept: {
			FREE_c_SESSION_DSCP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_SESSION_DSCP_INUSE_AttributeUpdateAccept);
	EDFree (sp->Data.fld_c_SESSION_DSCP_INUSE_AttributeUpdateAccept );
			break;
		}
		
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_AttributeUpdateReject: {
			FREE_c_SESSION_DSCP_INUSE_AttributeUpdateReject (sp->Data.fld_c_SESSION_DSCP_INUSE_AttributeUpdateReject);
	EDFree (sp->Data.fld_c_SESSION_DSCP_INUSE_AttributeUpdateReject );
			break;
		}
		
		default:;
	}

	sp->Type = ID_SESSION_DSCP_INUSE_Unrecognized;
}

void SETPRESENT_TSESSION_GMCDP_INCFG_Data (TSESSION_GMCDP_INCFG_Data* sp, TSESSION_GMCDP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TSESSION_GMCDP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_SESSION_GMCDP_INCFG_SESSION_GMCDP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_SESSION_GMCDP_INCFG_ConfigurationRequest = (c_SESSION_GMCDP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_SESSION_GMCDP_INCFG_ConfigurationRequest));
			INIT_c_SESSION_GMCDP_INCFG_ConfigurationRequest (sp->Data.fld_c_SESSION_GMCDP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_SESSION_GMCDP_INCFG_SESSION_GMCDP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_SESSION_GMCDP_INCFG_ConfigurationResponse = (c_SESSION_GMCDP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_SESSION_GMCDP_INCFG_ConfigurationResponse));
			INIT_c_SESSION_GMCDP_INCFG_ConfigurationResponse (sp->Data.fld_c_SESSION_GMCDP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TSESSION_GMCDP_INCFG_Data (TSESSION_GMCDP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_SESSION_GMCDP_INCFG_SESSION_GMCDP_INCFG_ConfigurationRequest: {
			FREE_c_SESSION_GMCDP_INCFG_ConfigurationRequest (sp->Data.fld_c_SESSION_GMCDP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_SESSION_GMCDP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_SESSION_GMCDP_INCFG_SESSION_GMCDP_INCFG_ConfigurationResponse: {
			FREE_c_SESSION_GMCDP_INCFG_ConfigurationResponse (sp->Data.fld_c_SESSION_GMCDP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_SESSION_GMCDP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_SESSION_GMCDP_INCFG_Unrecognized;
}

void SETPRESENT_TCONN_DALMP_INCFG_Data (TCONN_DALMP_INCFG_Data* sp, TCONN_DALMP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TCONN_DALMP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_CONN_DALMP_INCFG_CONN_DALMP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_CONN_DALMP_INCFG_ConfigurationRequest = (c_CONN_DALMP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_CONN_DALMP_INCFG_ConfigurationRequest));
			INIT_c_CONN_DALMP_INCFG_ConfigurationRequest (sp->Data.fld_c_CONN_DALMP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_CONN_DALMP_INCFG_CONN_DALMP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_CONN_DALMP_INCFG_ConfigurationResponse = (c_CONN_DALMP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_CONN_DALMP_INCFG_ConfigurationResponse));
			INIT_c_CONN_DALMP_INCFG_ConfigurationResponse (sp->Data.fld_c_CONN_DALMP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TCONN_DALMP_INCFG_Data (TCONN_DALMP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_CONN_DALMP_INCFG_CONN_DALMP_INCFG_ConfigurationRequest: {
			FREE_c_CONN_DALMP_INCFG_ConfigurationRequest (sp->Data.fld_c_CONN_DALMP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_CONN_DALMP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_CONN_DALMP_INCFG_CONN_DALMP_INCFG_ConfigurationResponse: {
			FREE_c_CONN_DALMP_INCFG_ConfigurationResponse (sp->Data.fld_c_CONN_DALMP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_CONN_DALMP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_CONN_DALMP_INCFG_Unrecognized;
}

void SETPRESENT_TCONN_DALMP_INUSE_Data (TCONN_DALMP_INUSE_Data* sp, TCONN_DALMP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TCONN_DALMP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_CONN_DALMP_INUSE_CONN_DALMP_INUSE_Redirect: {
			sp->Data.fld_c_CONN_DALMP_INUSE_Redirect = (c_CONN_DALMP_INUSE_Redirect*)EDAlloc (sizeof (c_CONN_DALMP_INUSE_Redirect));
			INIT_c_CONN_DALMP_INUSE_Redirect (sp->Data.fld_c_CONN_DALMP_INUSE_Redirect);
			break;
		}
		
		case ID_CONN_DALMP_INUSE_CONN_DALMP_INUSE_ConnectionFailureReport: {
			sp->Data.fld_c_CONN_DALMP_INUSE_ConnectionFailureReport = (c_CONN_DALMP_INUSE_ConnectionFailureReport*)EDAlloc (sizeof (c_CONN_DALMP_INUSE_ConnectionFailureReport));
			INIT_c_CONN_DALMP_INUSE_ConnectionFailureReport (sp->Data.fld_c_CONN_DALMP_INUSE_ConnectionFailureReport);
			break;
		}
		
		case ID_CONN_DALMP_INUSE_CONN_DALMP_INUSE_ConnectionFailureReportAck: {
			sp->Data.fld_c_CONN_DALMP_INUSE_ConnectionFailureReportAck = (c_CONN_DALMP_INUSE_ConnectionFailureReportAck*)EDAlloc (sizeof (c_CONN_DALMP_INUSE_ConnectionFailureReportAck));
			INIT_c_CONN_DALMP_INUSE_ConnectionFailureReportAck (sp->Data.fld_c_CONN_DALMP_INUSE_ConnectionFailureReportAck);
			break;
		}
		
		default:;
	}
}

void FREE_TCONN_DALMP_INUSE_Data (TCONN_DALMP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_CONN_DALMP_INUSE_CONN_DALMP_INUSE_Redirect: {
			FREE_c_CONN_DALMP_INUSE_Redirect (sp->Data.fld_c_CONN_DALMP_INUSE_Redirect);
	EDFree (sp->Data.fld_c_CONN_DALMP_INUSE_Redirect );
			break;
		}
		
		case ID_CONN_DALMP_INUSE_CONN_DALMP_INUSE_ConnectionFailureReport: {
			FREE_c_CONN_DALMP_INUSE_ConnectionFailureReport (sp->Data.fld_c_CONN_DALMP_INUSE_ConnectionFailureReport);
	EDFree (sp->Data.fld_c_CONN_DALMP_INUSE_ConnectionFailureReport );
			break;
		}
		
		case ID_CONN_DALMP_INUSE_CONN_DALMP_INUSE_ConnectionFailureReportAck: {
			FREE_c_CONN_DALMP_INUSE_ConnectionFailureReportAck (sp->Data.fld_c_CONN_DALMP_INUSE_ConnectionFailureReportAck);
	EDFree (sp->Data.fld_c_CONN_DALMP_INUSE_ConnectionFailureReportAck );
			break;
		}
		
		default:;
	}

	sp->Type = ID_CONN_DALMP_INUSE_Unrecognized;
}

void SETPRESENT_TCONN_DINSP_INCFG_Data (TCONN_DINSP_INCFG_Data* sp, TCONN_DINSP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TCONN_DINSP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_CONN_DINSP_INCFG_CONN_DINSP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_CONN_DINSP_INCFG_ConfigurationRequest = (c_CONN_DINSP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_CONN_DINSP_INCFG_ConfigurationRequest));
			INIT_c_CONN_DINSP_INCFG_ConfigurationRequest (sp->Data.fld_c_CONN_DINSP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_CONN_DINSP_INCFG_CONN_DINSP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_CONN_DINSP_INCFG_ConfigurationResponse = (c_CONN_DINSP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_CONN_DINSP_INCFG_ConfigurationResponse));
			INIT_c_CONN_DINSP_INCFG_ConfigurationResponse (sp->Data.fld_c_CONN_DINSP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TCONN_DINSP_INCFG_Data (TCONN_DINSP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_CONN_DINSP_INCFG_CONN_DINSP_INCFG_ConfigurationRequest: {
			FREE_c_CONN_DINSP_INCFG_ConfigurationRequest (sp->Data.fld_c_CONN_DINSP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_CONN_DINSP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_CONN_DINSP_INCFG_CONN_DINSP_INCFG_ConfigurationResponse: {
			FREE_c_CONN_DINSP_INCFG_ConfigurationResponse (sp->Data.fld_c_CONN_DINSP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_CONN_DINSP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_CONN_DINSP_INCFG_Unrecognized;
}

void SETPRESENT_TCONN_DIDSP_INCFG_Data (TCONN_DIDSP_INCFG_Data* sp, TCONN_DIDSP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TCONN_DIDSP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_CONN_DIDSP_INCFG_CONN_DIDSP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_CONN_DIDSP_INCFG_ConfigurationRequest = (c_CONN_DIDSP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_CONN_DIDSP_INCFG_ConfigurationRequest));
			INIT_c_CONN_DIDSP_INCFG_ConfigurationRequest (sp->Data.fld_c_CONN_DIDSP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_CONN_DIDSP_INCFG_CONN_DIDSP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_CONN_DIDSP_INCFG_ConfigurationResponse = (c_CONN_DIDSP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_CONN_DIDSP_INCFG_ConfigurationResponse));
			INIT_c_CONN_DIDSP_INCFG_ConfigurationResponse (sp->Data.fld_c_CONN_DIDSP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TCONN_DIDSP_INCFG_Data (TCONN_DIDSP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_CONN_DIDSP_INCFG_CONN_DIDSP_INCFG_ConfigurationRequest: {
			FREE_c_CONN_DIDSP_INCFG_ConfigurationRequest (sp->Data.fld_c_CONN_DIDSP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_CONN_DIDSP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_CONN_DIDSP_INCFG_CONN_DIDSP_INCFG_ConfigurationResponse: {
			FREE_c_CONN_DIDSP_INCFG_ConfigurationResponse (sp->Data.fld_c_CONN_DIDSP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_CONN_DIDSP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_CONN_DIDSP_INCFG_Unrecognized;
}

void SETPRESENT_TCONN_DIDSP_INUSE_Data (TCONN_DIDSP_INUSE_Data* sp, TCONN_DIDSP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TCONN_DIDSP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_CONN_DIDSP_INUSE_CONN_DIDSP_INUSE_Page: {
			sp->Data.fld_c_CONN_DIDSP_INUSE_Page = (c_CONN_DIDSP_INUSE_Page*)EDAlloc (sizeof (c_CONN_DIDSP_INUSE_Page));
			INIT_c_CONN_DIDSP_INUSE_Page (sp->Data.fld_c_CONN_DIDSP_INUSE_Page);
			break;
		}
		
		case ID_CONN_DIDSP_INUSE_CONN_DIDSP_INUSE_ConnectionRequest: {
			sp->Data.fld_c_CONN_DIDSP_INUSE_ConnectionRequest = (c_CONN_DIDSP_INUSE_ConnectionRequest*)EDAlloc (sizeof (c_CONN_DIDSP_INUSE_ConnectionRequest));
			INIT_c_CONN_DIDSP_INUSE_ConnectionRequest (sp->Data.fld_c_CONN_DIDSP_INUSE_ConnectionRequest);
			break;
		}
		
		case ID_CONN_DIDSP_INUSE_CONN_DIDSP_INUSE_ConnectionDeny: {
			sp->Data.fld_c_CONN_DIDSP_INUSE_ConnectionDeny = (c_CONN_DIDSP_INUSE_ConnectionDeny*)EDAlloc (sizeof (c_CONN_DIDSP_INUSE_ConnectionDeny));
			INIT_c_CONN_DIDSP_INUSE_ConnectionDeny (sp->Data.fld_c_CONN_DIDSP_INUSE_ConnectionDeny);
			break;
		}
		
		default:;
	}
}

void FREE_TCONN_DIDSP_INUSE_Data (TCONN_DIDSP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_CONN_DIDSP_INUSE_CONN_DIDSP_INUSE_Page: {
			FREE_c_CONN_DIDSP_INUSE_Page (sp->Data.fld_c_CONN_DIDSP_INUSE_Page);
	EDFree (sp->Data.fld_c_CONN_DIDSP_INUSE_Page );
			break;
		}
		
		case ID_CONN_DIDSP_INUSE_CONN_DIDSP_INUSE_ConnectionRequest: {
			FREE_c_CONN_DIDSP_INUSE_ConnectionRequest (sp->Data.fld_c_CONN_DIDSP_INUSE_ConnectionRequest);
	EDFree (sp->Data.fld_c_CONN_DIDSP_INUSE_ConnectionRequest );
			break;
		}
		
		case ID_CONN_DIDSP_INUSE_CONN_DIDSP_INUSE_ConnectionDeny: {
			FREE_c_CONN_DIDSP_INUSE_ConnectionDeny (sp->Data.fld_c_CONN_DIDSP_INUSE_ConnectionDeny);
	EDFree (sp->Data.fld_c_CONN_DIDSP_INUSE_ConnectionDeny );
			break;
		}
		
		default:;
	}

	sp->Type = ID_CONN_DIDSP_INUSE_Unrecognized;
}

void SETPRESENT_TCONN_EISP_INCFG_Data (TCONN_EISP_INCFG_Data* sp, TCONN_EISP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TCONN_EISP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_CONN_EISP_INCFG_CONN_EISP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_CONN_EISP_INCFG_ConfigurationRequest = (c_CONN_EISP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_CONN_EISP_INCFG_ConfigurationRequest));
			INIT_c_CONN_EISP_INCFG_ConfigurationRequest (sp->Data.fld_c_CONN_EISP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_CONN_EISP_INCFG_CONN_EISP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_CONN_EISP_INCFG_ConfigurationResponse = (c_CONN_EISP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_CONN_EISP_INCFG_ConfigurationResponse));
			INIT_c_CONN_EISP_INCFG_ConfigurationResponse (sp->Data.fld_c_CONN_EISP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TCONN_EISP_INCFG_Data (TCONN_EISP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_CONN_EISP_INCFG_CONN_EISP_INCFG_ConfigurationRequest: {
			FREE_c_CONN_EISP_INCFG_ConfigurationRequest (sp->Data.fld_c_CONN_EISP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_CONN_EISP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_CONN_EISP_INCFG_CONN_EISP_INCFG_ConfigurationResponse: {
			FREE_c_CONN_EISP_INCFG_ConfigurationResponse (sp->Data.fld_c_CONN_EISP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_CONN_EISP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_CONN_EISP_INCFG_Unrecognized;
}

void SETPRESENT_TCONN_EISP_INUSE_Data (TCONN_EISP_INUSE_Data* sp, TCONN_EISP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TCONN_EISP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_CONN_EISP_INUSE_CONN_EISP_INUSE_Page: {
			sp->Data.fld_c_CONN_EISP_INUSE_Page = (c_CONN_EISP_INUSE_Page*)EDAlloc (sizeof (c_CONN_EISP_INUSE_Page));
			INIT_c_CONN_EISP_INUSE_Page (sp->Data.fld_c_CONN_EISP_INUSE_Page);
			break;
		}
		
		case ID_CONN_EISP_INUSE_CONN_EISP_INUSE_ConnectionRequest: {
			sp->Data.fld_c_CONN_EISP_INUSE_ConnectionRequest = (c_CONN_EISP_INUSE_ConnectionRequest*)EDAlloc (sizeof (c_CONN_EISP_INUSE_ConnectionRequest));
			INIT_c_CONN_EISP_INUSE_ConnectionRequest (sp->Data.fld_c_CONN_EISP_INUSE_ConnectionRequest);
			break;
		}
		
		case ID_CONN_EISP_INUSE_CONN_EISP_INUSE_ConnectionDeny: {
			sp->Data.fld_c_CONN_EISP_INUSE_ConnectionDeny = (c_CONN_EISP_INUSE_ConnectionDeny*)EDAlloc (sizeof (c_CONN_EISP_INUSE_ConnectionDeny));
			INIT_c_CONN_EISP_INUSE_ConnectionDeny (sp->Data.fld_c_CONN_EISP_INUSE_ConnectionDeny);
			break;
		}
		
		case ID_CONN_EISP_INUSE_CONN_EISP_INUSE_AttributeUpdateRequest: {
			sp->Data.fld_c_CONN_EISP_INUSE_AttributeUpdateRequest = (c_CONN_EISP_INUSE_AttributeUpdateRequest*)EDAlloc (sizeof (c_CONN_EISP_INUSE_AttributeUpdateRequest));
			INIT_c_CONN_EISP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_CONN_EISP_INUSE_AttributeUpdateRequest);
			break;
		}
		
		case ID_CONN_EISP_INUSE_CONN_EISP_INUSE_AttributeUpdateAccept: {
			sp->Data.fld_c_CONN_EISP_INUSE_AttributeUpdateAccept = (c_CONN_EISP_INUSE_AttributeUpdateAccept*)EDAlloc (sizeof (c_CONN_EISP_INUSE_AttributeUpdateAccept));
			INIT_c_CONN_EISP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_CONN_EISP_INUSE_AttributeUpdateAccept);
			break;
		}
		
		case ID_CONN_EISP_INUSE_CONN_EISP_INUSE_AttributeUpdateReject: {
			sp->Data.fld_c_CONN_EISP_INUSE_AttributeUpdateReject = (c_CONN_EISP_INUSE_AttributeUpdateReject*)EDAlloc (sizeof (c_CONN_EISP_INUSE_AttributeUpdateReject));
			INIT_c_CONN_EISP_INUSE_AttributeUpdateReject (sp->Data.fld_c_CONN_EISP_INUSE_AttributeUpdateReject);
			break;
		}
		
		default:;
	}
}

void FREE_TCONN_EISP_INUSE_Data (TCONN_EISP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_CONN_EISP_INUSE_CONN_EISP_INUSE_Page: {
			FREE_c_CONN_EISP_INUSE_Page (sp->Data.fld_c_CONN_EISP_INUSE_Page);
	EDFree (sp->Data.fld_c_CONN_EISP_INUSE_Page );
			break;
		}
		
		case ID_CONN_EISP_INUSE_CONN_EISP_INUSE_ConnectionRequest: {
			FREE_c_CONN_EISP_INUSE_ConnectionRequest (sp->Data.fld_c_CONN_EISP_INUSE_ConnectionRequest);
	EDFree (sp->Data.fld_c_CONN_EISP_INUSE_ConnectionRequest );
			break;
		}
		
		case ID_CONN_EISP_INUSE_CONN_EISP_INUSE_ConnectionDeny: {
			FREE_c_CONN_EISP_INUSE_ConnectionDeny (sp->Data.fld_c_CONN_EISP_INUSE_ConnectionDeny);
	EDFree (sp->Data.fld_c_CONN_EISP_INUSE_ConnectionDeny );
			break;
		}
		
		case ID_CONN_EISP_INUSE_CONN_EISP_INUSE_AttributeUpdateRequest: {
			FREE_c_CONN_EISP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_CONN_EISP_INUSE_AttributeUpdateRequest);
	EDFree (sp->Data.fld_c_CONN_EISP_INUSE_AttributeUpdateRequest );
			break;
		}
		
		case ID_CONN_EISP_INUSE_CONN_EISP_INUSE_AttributeUpdateAccept: {
			FREE_c_CONN_EISP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_CONN_EISP_INUSE_AttributeUpdateAccept);
	EDFree (sp->Data.fld_c_CONN_EISP_INUSE_AttributeUpdateAccept );
			break;
		}
		
		case ID_CONN_EISP_INUSE_CONN_EISP_INUSE_AttributeUpdateReject: {
			FREE_c_CONN_EISP_INUSE_AttributeUpdateReject (sp->Data.fld_c_CONN_EISP_INUSE_AttributeUpdateReject);
	EDFree (sp->Data.fld_c_CONN_EISP_INUSE_AttributeUpdateReject );
			break;
		}
		
		default:;
	}

	sp->Type = ID_CONN_EISP_INUSE_Unrecognized;
}

void SETPRESENT_TCONN_QISP_INCFG_Data (TCONN_QISP_INCFG_Data* sp, TCONN_QISP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TCONN_QISP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_CONN_QISP_INCFG_CONN_QISP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_CONN_QISP_INCFG_ConfigurationRequest = (c_CONN_QISP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_CONN_QISP_INCFG_ConfigurationRequest));
			INIT_c_CONN_QISP_INCFG_ConfigurationRequest (sp->Data.fld_c_CONN_QISP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_CONN_QISP_INCFG_CONN_QISP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_CONN_QISP_INCFG_ConfigurationResponse = (c_CONN_QISP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_CONN_QISP_INCFG_ConfigurationResponse));
			INIT_c_CONN_QISP_INCFG_ConfigurationResponse (sp->Data.fld_c_CONN_QISP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TCONN_QISP_INCFG_Data (TCONN_QISP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_CONN_QISP_INCFG_CONN_QISP_INCFG_ConfigurationRequest: {
			FREE_c_CONN_QISP_INCFG_ConfigurationRequest (sp->Data.fld_c_CONN_QISP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_CONN_QISP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_CONN_QISP_INCFG_CONN_QISP_INCFG_ConfigurationResponse: {
			FREE_c_CONN_QISP_INCFG_ConfigurationResponse (sp->Data.fld_c_CONN_QISP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_CONN_QISP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_CONN_QISP_INCFG_Unrecognized;
}

void SETPRESENT_TCONN_QISP_INUSE_Data (TCONN_QISP_INUSE_Data* sp, TCONN_QISP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TCONN_QISP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_CONN_QISP_INUSE_CONN_QISP_INUSE_Page: {
			sp->Data.fld_c_CONN_QISP_INUSE_Page = (c_CONN_QISP_INUSE_Page*)EDAlloc (sizeof (c_CONN_QISP_INUSE_Page));
			INIT_c_CONN_QISP_INUSE_Page (sp->Data.fld_c_CONN_QISP_INUSE_Page);
			break;
		}
		
		case ID_CONN_QISP_INUSE_CONN_QISP_INUSE_ConnectionRequest: {
			sp->Data.fld_c_CONN_QISP_INUSE_ConnectionRequest = (c_CONN_QISP_INUSE_ConnectionRequest*)EDAlloc (sizeof (c_CONN_QISP_INUSE_ConnectionRequest));
			INIT_c_CONN_QISP_INUSE_ConnectionRequest (sp->Data.fld_c_CONN_QISP_INUSE_ConnectionRequest);
			break;
		}
		
		case ID_CONN_QISP_INUSE_CONN_QISP_INUSE_ConnectionDeny: {
			sp->Data.fld_c_CONN_QISP_INUSE_ConnectionDeny = (c_CONN_QISP_INUSE_ConnectionDeny*)EDAlloc (sizeof (c_CONN_QISP_INUSE_ConnectionDeny));
			INIT_c_CONN_QISP_INUSE_ConnectionDeny (sp->Data.fld_c_CONN_QISP_INUSE_ConnectionDeny);
			break;
		}
		
		case ID_CONN_QISP_INUSE_CONN_QISP_INUSE_QuickPage: {
			sp->Data.fld_c_CONN_QISP_INUSE_QuickPage = (c_CONN_QISP_INUSE_QuickPage*)EDAlloc (sizeof (c_CONN_QISP_INUSE_QuickPage));
			INIT_c_CONN_QISP_INUSE_QuickPage (sp->Data.fld_c_CONN_QISP_INUSE_QuickPage);
			break;
		}
		
		case ID_CONN_QISP_INUSE_CONN_QISP_INUSE_AttributeUpdateRequest: {
			sp->Data.fld_c_CONN_QISP_INUSE_AttributeUpdateRequest = (c_CONN_QISP_INUSE_AttributeUpdateRequest*)EDAlloc (sizeof (c_CONN_QISP_INUSE_AttributeUpdateRequest));
			INIT_c_CONN_QISP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_CONN_QISP_INUSE_AttributeUpdateRequest);
			break;
		}
		
		case ID_CONN_QISP_INUSE_CONN_QISP_INUSE_AttributeUpdateAccept: {
			sp->Data.fld_c_CONN_QISP_INUSE_AttributeUpdateAccept = (c_CONN_QISP_INUSE_AttributeUpdateAccept*)EDAlloc (sizeof (c_CONN_QISP_INUSE_AttributeUpdateAccept));
			INIT_c_CONN_QISP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_CONN_QISP_INUSE_AttributeUpdateAccept);
			break;
		}
		
		case ID_CONN_QISP_INUSE_CONN_QISP_INUSE_AttributeUpdateReject: {
			sp->Data.fld_c_CONN_QISP_INUSE_AttributeUpdateReject = (c_CONN_QISP_INUSE_AttributeUpdateReject*)EDAlloc (sizeof (c_CONN_QISP_INUSE_AttributeUpdateReject));
			INIT_c_CONN_QISP_INUSE_AttributeUpdateReject (sp->Data.fld_c_CONN_QISP_INUSE_AttributeUpdateReject);
			break;
		}
		
		default:;
	}
}

void FREE_TCONN_QISP_INUSE_Data (TCONN_QISP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_CONN_QISP_INUSE_CONN_QISP_INUSE_Page: {
			FREE_c_CONN_QISP_INUSE_Page (sp->Data.fld_c_CONN_QISP_INUSE_Page);
	EDFree (sp->Data.fld_c_CONN_QISP_INUSE_Page );
			break;
		}
		
		case ID_CONN_QISP_INUSE_CONN_QISP_INUSE_ConnectionRequest: {
			FREE_c_CONN_QISP_INUSE_ConnectionRequest (sp->Data.fld_c_CONN_QISP_INUSE_ConnectionRequest);
	EDFree (sp->Data.fld_c_CONN_QISP_INUSE_ConnectionRequest );
			break;
		}
		
		case ID_CONN_QISP_INUSE_CONN_QISP_INUSE_ConnectionDeny: {
			FREE_c_CONN_QISP_INUSE_ConnectionDeny (sp->Data.fld_c_CONN_QISP_INUSE_ConnectionDeny);
	EDFree (sp->Data.fld_c_CONN_QISP_INUSE_ConnectionDeny );
			break;
		}
		
		case ID_CONN_QISP_INUSE_CONN_QISP_INUSE_QuickPage: {
			FREE_c_CONN_QISP_INUSE_QuickPage (sp->Data.fld_c_CONN_QISP_INUSE_QuickPage);
	EDFree (sp->Data.fld_c_CONN_QISP_INUSE_QuickPage );
			break;
		}
		
		case ID_CONN_QISP_INUSE_CONN_QISP_INUSE_AttributeUpdateRequest: {
			FREE_c_CONN_QISP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_CONN_QISP_INUSE_AttributeUpdateRequest);
	EDFree (sp->Data.fld_c_CONN_QISP_INUSE_AttributeUpdateRequest );
			break;
		}
		
		case ID_CONN_QISP_INUSE_CONN_QISP_INUSE_AttributeUpdateAccept: {
			FREE_c_CONN_QISP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_CONN_QISP_INUSE_AttributeUpdateAccept);
	EDFree (sp->Data.fld_c_CONN_QISP_INUSE_AttributeUpdateAccept );
			break;
		}
		
		case ID_CONN_QISP_INUSE_CONN_QISP_INUSE_AttributeUpdateReject: {
			FREE_c_CONN_QISP_INUSE_AttributeUpdateReject (sp->Data.fld_c_CONN_QISP_INUSE_AttributeUpdateReject);
	EDFree (sp->Data.fld_c_CONN_QISP_INUSE_AttributeUpdateReject );
			break;
		}
		
		default:;
	}

	sp->Type = ID_CONN_QISP_INUSE_Unrecognized;
}

void SETPRESENT_TCONN_DCSP_INCFG_Data (TCONN_DCSP_INCFG_Data* sp, TCONN_DCSP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TCONN_DCSP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_CONN_DCSP_INCFG_CONN_DCSP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_CONN_DCSP_INCFG_ConfigurationRequest = (c_CONN_DCSP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_CONN_DCSP_INCFG_ConfigurationRequest));
			INIT_c_CONN_DCSP_INCFG_ConfigurationRequest (sp->Data.fld_c_CONN_DCSP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_CONN_DCSP_INCFG_CONN_DCSP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_CONN_DCSP_INCFG_ConfigurationResponse = (c_CONN_DCSP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_CONN_DCSP_INCFG_ConfigurationResponse));
			INIT_c_CONN_DCSP_INCFG_ConfigurationResponse (sp->Data.fld_c_CONN_DCSP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TCONN_DCSP_INCFG_Data (TCONN_DCSP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_CONN_DCSP_INCFG_CONN_DCSP_INCFG_ConfigurationRequest: {
			FREE_c_CONN_DCSP_INCFG_ConfigurationRequest (sp->Data.fld_c_CONN_DCSP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_CONN_DCSP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_CONN_DCSP_INCFG_CONN_DCSP_INCFG_ConfigurationResponse: {
			FREE_c_CONN_DCSP_INCFG_ConfigurationResponse (sp->Data.fld_c_CONN_DCSP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_CONN_DCSP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_CONN_DCSP_INCFG_Unrecognized;
}

void SETPRESENT_TCONN_DCSP_INUSE_Data (TCONN_DCSP_INUSE_Data* sp, TCONN_DCSP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TCONN_DCSP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_CONN_DCSP_INUSE_CONN_DCSP_INUSE_ConnectionClose: {
			sp->Data.fld_c_CONN_DCSP_INUSE_ConnectionClose = (c_CONN_DCSP_INUSE_ConnectionClose*)EDAlloc (sizeof (c_CONN_DCSP_INUSE_ConnectionClose));
			INIT_c_CONN_DCSP_INUSE_ConnectionClose (sp->Data.fld_c_CONN_DCSP_INUSE_ConnectionClose);
			break;
		}
		
		default:;
	}
}

void FREE_TCONN_DCSP_INUSE_Data (TCONN_DCSP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_CONN_DCSP_INUSE_CONN_DCSP_INUSE_ConnectionClose: {
			FREE_c_CONN_DCSP_INUSE_ConnectionClose (sp->Data.fld_c_CONN_DCSP_INUSE_ConnectionClose);
	EDFree (sp->Data.fld_c_CONN_DCSP_INUSE_ConnectionClose );
			break;
		}
		
		default:;
	}

	sp->Type = ID_CONN_DCSP_INUSE_Unrecognized;
}

void SETPRESENT_TCONN_DRUP_INCFG_Data (TCONN_DRUP_INCFG_Data* sp, TCONN_DRUP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TCONN_DRUP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_CONN_DRUP_INCFG_CONN_DRUP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_CONN_DRUP_INCFG_ConfigurationRequest = (c_CONN_DRUP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_CONN_DRUP_INCFG_ConfigurationRequest));
			INIT_c_CONN_DRUP_INCFG_ConfigurationRequest (sp->Data.fld_c_CONN_DRUP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_CONN_DRUP_INCFG_CONN_DRUP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_CONN_DRUP_INCFG_ConfigurationResponse = (c_CONN_DRUP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_CONN_DRUP_INCFG_ConfigurationResponse));
			INIT_c_CONN_DRUP_INCFG_ConfigurationResponse (sp->Data.fld_c_CONN_DRUP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TCONN_DRUP_INCFG_Data (TCONN_DRUP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_CONN_DRUP_INCFG_CONN_DRUP_INCFG_ConfigurationRequest: {
			FREE_c_CONN_DRUP_INCFG_ConfigurationRequest (sp->Data.fld_c_CONN_DRUP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_CONN_DRUP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_CONN_DRUP_INCFG_CONN_DRUP_INCFG_ConfigurationResponse: {
			FREE_c_CONN_DRUP_INCFG_ConfigurationResponse (sp->Data.fld_c_CONN_DRUP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_CONN_DRUP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_CONN_DRUP_INCFG_Unrecognized;
}

void SETPRESENT_TCONN_DRUP_INUSE_Data (TCONN_DRUP_INUSE_Data* sp, TCONN_DRUP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TCONN_DRUP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_RouteUpdate: {
			sp->Data.fld_c_CONN_DRUP_INUSE_RouteUpdate = (c_CONN_DRUP_INUSE_RouteUpdate*)EDAlloc (sizeof (c_CONN_DRUP_INUSE_RouteUpdate));
			INIT_c_CONN_DRUP_INUSE_RouteUpdate (sp->Data.fld_c_CONN_DRUP_INUSE_RouteUpdate);
			break;
		}
		
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_TrafficChannelAssignment: {
			sp->Data.fld_c_CONN_DRUP_INUSE_TrafficChannelAssignment = (c_CONN_DRUP_INUSE_TrafficChannelAssignment*)EDAlloc (sizeof (c_CONN_DRUP_INUSE_TrafficChannelAssignment));
			INIT_c_CONN_DRUP_INUSE_TrafficChannelAssignment (sp->Data.fld_c_CONN_DRUP_INUSE_TrafficChannelAssignment);
			break;
		}
		
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_TrafficChannelComplete: {
			sp->Data.fld_c_CONN_DRUP_INUSE_TrafficChannelComplete = (c_CONN_DRUP_INUSE_TrafficChannelComplete*)EDAlloc (sizeof (c_CONN_DRUP_INUSE_TrafficChannelComplete));
			INIT_c_CONN_DRUP_INUSE_TrafficChannelComplete (sp->Data.fld_c_CONN_DRUP_INUSE_TrafficChannelComplete);
			break;
		}
		
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_ResetReport: {
			sp->Data.fld_c_CONN_DRUP_INUSE_ResetReport = (c_CONN_DRUP_INUSE_ResetReport*)EDAlloc (sizeof (c_CONN_DRUP_INUSE_ResetReport));
			INIT_c_CONN_DRUP_INUSE_ResetReport (sp->Data.fld_c_CONN_DRUP_INUSE_ResetReport);
			break;
		}
		
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_NeighborList: {
			sp->Data.fld_c_CONN_DRUP_INUSE_NeighborList = (c_CONN_DRUP_INUSE_NeighborList*)EDAlloc (sizeof (c_CONN_DRUP_INUSE_NeighborList));
			INIT_c_CONN_DRUP_INUSE_NeighborList (sp->Data.fld_c_CONN_DRUP_INUSE_NeighborList);
			break;
		}
		
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_AttributeOverride: {
			sp->Data.fld_c_CONN_DRUP_INUSE_AttributeOverride = (c_CONN_DRUP_INUSE_AttributeOverride*)EDAlloc (sizeof (c_CONN_DRUP_INUSE_AttributeOverride));
			INIT_c_CONN_DRUP_INUSE_AttributeOverride (sp->Data.fld_c_CONN_DRUP_INUSE_AttributeOverride);
			break;
		}
		
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_AttributeOverrideResponse: {
			sp->Data.fld_c_CONN_DRUP_INUSE_AttributeOverrideResponse = (c_CONN_DRUP_INUSE_AttributeOverrideResponse*)EDAlloc (sizeof (c_CONN_DRUP_INUSE_AttributeOverrideResponse));
			INIT_c_CONN_DRUP_INUSE_AttributeOverrideResponse (sp->Data.fld_c_CONN_DRUP_INUSE_AttributeOverrideResponse);
			break;
		}
		
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_RouteUpdateRequest: {
			sp->Data.fld_c_CONN_DRUP_INUSE_RouteUpdateRequest = (c_CONN_DRUP_INUSE_RouteUpdateRequest*)EDAlloc (sizeof (c_CONN_DRUP_INUSE_RouteUpdateRequest));
			INIT_c_CONN_DRUP_INUSE_RouteUpdateRequest (sp->Data.fld_c_CONN_DRUP_INUSE_RouteUpdateRequest);
			break;
		}
		
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_AttributeUpdateRequest: {
			sp->Data.fld_c_CONN_DRUP_INUSE_AttributeUpdateRequest = (c_CONN_DRUP_INUSE_AttributeUpdateRequest*)EDAlloc (sizeof (c_CONN_DRUP_INUSE_AttributeUpdateRequest));
			INIT_c_CONN_DRUP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_CONN_DRUP_INUSE_AttributeUpdateRequest);
			break;
		}
		
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_AttributeUpdateAccept: {
			sp->Data.fld_c_CONN_DRUP_INUSE_AttributeUpdateAccept = (c_CONN_DRUP_INUSE_AttributeUpdateAccept*)EDAlloc (sizeof (c_CONN_DRUP_INUSE_AttributeUpdateAccept));
			INIT_c_CONN_DRUP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_CONN_DRUP_INUSE_AttributeUpdateAccept);
			break;
		}
		
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_AttributeUpdateReject: {
			sp->Data.fld_c_CONN_DRUP_INUSE_AttributeUpdateReject = (c_CONN_DRUP_INUSE_AttributeUpdateReject*)EDAlloc (sizeof (c_CONN_DRUP_INUSE_AttributeUpdateReject));
			INIT_c_CONN_DRUP_INUSE_AttributeUpdateReject (sp->Data.fld_c_CONN_DRUP_INUSE_AttributeUpdateReject);
			break;
		}
		
		default:;
	}
}

void FREE_TCONN_DRUP_INUSE_Data (TCONN_DRUP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_RouteUpdate: {
			FREE_c_CONN_DRUP_INUSE_RouteUpdate (sp->Data.fld_c_CONN_DRUP_INUSE_RouteUpdate);
	EDFree (sp->Data.fld_c_CONN_DRUP_INUSE_RouteUpdate );
			break;
		}
		
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_TrafficChannelAssignment: {
			FREE_c_CONN_DRUP_INUSE_TrafficChannelAssignment (sp->Data.fld_c_CONN_DRUP_INUSE_TrafficChannelAssignment);
	EDFree (sp->Data.fld_c_CONN_DRUP_INUSE_TrafficChannelAssignment );
			break;
		}
		
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_TrafficChannelComplete: {
			FREE_c_CONN_DRUP_INUSE_TrafficChannelComplete (sp->Data.fld_c_CONN_DRUP_INUSE_TrafficChannelComplete);
	EDFree (sp->Data.fld_c_CONN_DRUP_INUSE_TrafficChannelComplete );
			break;
		}
		
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_ResetReport: {
			FREE_c_CONN_DRUP_INUSE_ResetReport (sp->Data.fld_c_CONN_DRUP_INUSE_ResetReport);
	EDFree (sp->Data.fld_c_CONN_DRUP_INUSE_ResetReport );
			break;
		}
		
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_NeighborList: {
			FREE_c_CONN_DRUP_INUSE_NeighborList (sp->Data.fld_c_CONN_DRUP_INUSE_NeighborList);
	EDFree (sp->Data.fld_c_CONN_DRUP_INUSE_NeighborList );
			break;
		}
		
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_AttributeOverride: {
			FREE_c_CONN_DRUP_INUSE_AttributeOverride (sp->Data.fld_c_CONN_DRUP_INUSE_AttributeOverride);
	EDFree (sp->Data.fld_c_CONN_DRUP_INUSE_AttributeOverride );
			break;
		}
		
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_AttributeOverrideResponse: {
			FREE_c_CONN_DRUP_INUSE_AttributeOverrideResponse (sp->Data.fld_c_CONN_DRUP_INUSE_AttributeOverrideResponse);
	EDFree (sp->Data.fld_c_CONN_DRUP_INUSE_AttributeOverrideResponse );
			break;
		}
		
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_RouteUpdateRequest: {
			FREE_c_CONN_DRUP_INUSE_RouteUpdateRequest (sp->Data.fld_c_CONN_DRUP_INUSE_RouteUpdateRequest);
	EDFree (sp->Data.fld_c_CONN_DRUP_INUSE_RouteUpdateRequest );
			break;
		}
		
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_AttributeUpdateRequest: {
			FREE_c_CONN_DRUP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_CONN_DRUP_INUSE_AttributeUpdateRequest);
	EDFree (sp->Data.fld_c_CONN_DRUP_INUSE_AttributeUpdateRequest );
			break;
		}
		
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_AttributeUpdateAccept: {
			FREE_c_CONN_DRUP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_CONN_DRUP_INUSE_AttributeUpdateAccept);
	EDFree (sp->Data.fld_c_CONN_DRUP_INUSE_AttributeUpdateAccept );
			break;
		}
		
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_AttributeUpdateReject: {
			FREE_c_CONN_DRUP_INUSE_AttributeUpdateReject (sp->Data.fld_c_CONN_DRUP_INUSE_AttributeUpdateReject);
	EDFree (sp->Data.fld_c_CONN_DRUP_INUSE_AttributeUpdateReject );
			break;
		}
		
		default:;
	}

	sp->Type = ID_CONN_DRUP_INUSE_Unrecognized;
}

void SETPRESENT_TCONN_MRUP_INCFG_Data (TCONN_MRUP_INCFG_Data* sp, TCONN_MRUP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TCONN_MRUP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_CONN_MRUP_INCFG_CONN_MRUP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_CONN_MRUP_INCFG_ConfigurationRequest = (c_CONN_MRUP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_CONN_MRUP_INCFG_ConfigurationRequest));
			INIT_c_CONN_MRUP_INCFG_ConfigurationRequest (sp->Data.fld_c_CONN_MRUP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_CONN_MRUP_INCFG_CONN_MRUP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_CONN_MRUP_INCFG_ConfigurationResponse = (c_CONN_MRUP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_CONN_MRUP_INCFG_ConfigurationResponse));
			INIT_c_CONN_MRUP_INCFG_ConfigurationResponse (sp->Data.fld_c_CONN_MRUP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TCONN_MRUP_INCFG_Data (TCONN_MRUP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_CONN_MRUP_INCFG_CONN_MRUP_INCFG_ConfigurationRequest: {
			FREE_c_CONN_MRUP_INCFG_ConfigurationRequest (sp->Data.fld_c_CONN_MRUP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_CONN_MRUP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_CONN_MRUP_INCFG_CONN_MRUP_INCFG_ConfigurationResponse: {
			FREE_c_CONN_MRUP_INCFG_ConfigurationResponse (sp->Data.fld_c_CONN_MRUP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_CONN_MRUP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_CONN_MRUP_INCFG_Unrecognized;
}

void SETPRESENT_TCONN_MRUP_INUSE_Data (TCONN_MRUP_INUSE_Data* sp, TCONN_MRUP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TCONN_MRUP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_RouteUpdate: {
			sp->Data.fld_c_CONN_MRUP_INUSE_RouteUpdate = (c_CONN_MRUP_INUSE_RouteUpdate*)EDAlloc (sizeof (c_CONN_MRUP_INUSE_RouteUpdate));
			INIT_c_CONN_MRUP_INUSE_RouteUpdate (sp->Data.fld_c_CONN_MRUP_INUSE_RouteUpdate);
			break;
		}
		
		case ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_TrafficChannelAssignment: {
			sp->Data.fld_c_CONN_MRUP_INUSE_TrafficChannelAssignment = (c_CONN_MRUP_INUSE_TrafficChannelAssignment*)EDAlloc (sizeof (c_CONN_MRUP_INUSE_TrafficChannelAssignment));
			INIT_c_CONN_MRUP_INUSE_TrafficChannelAssignment (sp->Data.fld_c_CONN_MRUP_INUSE_TrafficChannelAssignment);
			break;
		}
		
		case ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_TrafficChannelComplete: {
			sp->Data.fld_c_CONN_MRUP_INUSE_TrafficChannelComplete = (c_CONN_MRUP_INUSE_TrafficChannelComplete*)EDAlloc (sizeof (c_CONN_MRUP_INUSE_TrafficChannelComplete));
			INIT_c_CONN_MRUP_INUSE_TrafficChannelComplete (sp->Data.fld_c_CONN_MRUP_INUSE_TrafficChannelComplete);
			break;
		}
		
		case ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_ResetReport: {
			sp->Data.fld_c_CONN_MRUP_INUSE_ResetReport = (c_CONN_MRUP_INUSE_ResetReport*)EDAlloc (sizeof (c_CONN_MRUP_INUSE_ResetReport));
			INIT_c_CONN_MRUP_INUSE_ResetReport (sp->Data.fld_c_CONN_MRUP_INUSE_ResetReport);
			break;
		}
		
		case ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_NeighborList: {
			sp->Data.fld_c_CONN_MRUP_INUSE_NeighborList = (c_CONN_MRUP_INUSE_NeighborList*)EDAlloc (sizeof (c_CONN_MRUP_INUSE_NeighborList));
			INIT_c_CONN_MRUP_INUSE_NeighborList (sp->Data.fld_c_CONN_MRUP_INUSE_NeighborList);
			break;
		}
		
		case ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_RouteUpdateRequest: {
			sp->Data.fld_c_CONN_MRUP_INUSE_RouteUpdateRequest = (c_CONN_MRUP_INUSE_RouteUpdateRequest*)EDAlloc (sizeof (c_CONN_MRUP_INUSE_RouteUpdateRequest));
			INIT_c_CONN_MRUP_INUSE_RouteUpdateRequest (sp->Data.fld_c_CONN_MRUP_INUSE_RouteUpdateRequest);
			break;
		}
		
		case ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_AttributeUpdateRequest: {
			sp->Data.fld_c_CONN_MRUP_INUSE_AttributeUpdateRequest = (c_CONN_MRUP_INUSE_AttributeUpdateRequest*)EDAlloc (sizeof (c_CONN_MRUP_INUSE_AttributeUpdateRequest));
			INIT_c_CONN_MRUP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_CONN_MRUP_INUSE_AttributeUpdateRequest);
			break;
		}
		
		case ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_AttributeUpdateAccept: {
			sp->Data.fld_c_CONN_MRUP_INUSE_AttributeUpdateAccept = (c_CONN_MRUP_INUSE_AttributeUpdateAccept*)EDAlloc (sizeof (c_CONN_MRUP_INUSE_AttributeUpdateAccept));
			INIT_c_CONN_MRUP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_CONN_MRUP_INUSE_AttributeUpdateAccept);
			break;
		}
		
		case ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_AttributeUpdateReject: {
			sp->Data.fld_c_CONN_MRUP_INUSE_AttributeUpdateReject = (c_CONN_MRUP_INUSE_AttributeUpdateReject*)EDAlloc (sizeof (c_CONN_MRUP_INUSE_AttributeUpdateReject));
			INIT_c_CONN_MRUP_INUSE_AttributeUpdateReject (sp->Data.fld_c_CONN_MRUP_INUSE_AttributeUpdateReject);
			break;
		}
		
		default:;
	}
}

void FREE_TCONN_MRUP_INUSE_Data (TCONN_MRUP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_RouteUpdate: {
			FREE_c_CONN_MRUP_INUSE_RouteUpdate (sp->Data.fld_c_CONN_MRUP_INUSE_RouteUpdate);
	EDFree (sp->Data.fld_c_CONN_MRUP_INUSE_RouteUpdate );
			break;
		}
		
		case ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_TrafficChannelAssignment: {
			FREE_c_CONN_MRUP_INUSE_TrafficChannelAssignment (sp->Data.fld_c_CONN_MRUP_INUSE_TrafficChannelAssignment);
	EDFree (sp->Data.fld_c_CONN_MRUP_INUSE_TrafficChannelAssignment );
			break;
		}
		
		case ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_TrafficChannelComplete: {
			FREE_c_CONN_MRUP_INUSE_TrafficChannelComplete (sp->Data.fld_c_CONN_MRUP_INUSE_TrafficChannelComplete);
	EDFree (sp->Data.fld_c_CONN_MRUP_INUSE_TrafficChannelComplete );
			break;
		}
		
		case ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_ResetReport: {
			FREE_c_CONN_MRUP_INUSE_ResetReport (sp->Data.fld_c_CONN_MRUP_INUSE_ResetReport);
	EDFree (sp->Data.fld_c_CONN_MRUP_INUSE_ResetReport );
			break;
		}
		
		case ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_NeighborList: {
			FREE_c_CONN_MRUP_INUSE_NeighborList (sp->Data.fld_c_CONN_MRUP_INUSE_NeighborList);
	EDFree (sp->Data.fld_c_CONN_MRUP_INUSE_NeighborList );
			break;
		}
		
		case ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_RouteUpdateRequest: {
			FREE_c_CONN_MRUP_INUSE_RouteUpdateRequest (sp->Data.fld_c_CONN_MRUP_INUSE_RouteUpdateRequest);
	EDFree (sp->Data.fld_c_CONN_MRUP_INUSE_RouteUpdateRequest );
			break;
		}
		
		case ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_AttributeUpdateRequest: {
			FREE_c_CONN_MRUP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_CONN_MRUP_INUSE_AttributeUpdateRequest);
	EDFree (sp->Data.fld_c_CONN_MRUP_INUSE_AttributeUpdateRequest );
			break;
		}
		
		case ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_AttributeUpdateAccept: {
			FREE_c_CONN_MRUP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_CONN_MRUP_INUSE_AttributeUpdateAccept);
	EDFree (sp->Data.fld_c_CONN_MRUP_INUSE_AttributeUpdateAccept );
			break;
		}
		
		case ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_AttributeUpdateReject: {
			FREE_c_CONN_MRUP_INUSE_AttributeUpdateReject (sp->Data.fld_c_CONN_MRUP_INUSE_AttributeUpdateReject);
	EDFree (sp->Data.fld_c_CONN_MRUP_INUSE_AttributeUpdateReject );
			break;
		}
		
		default:;
	}

	sp->Type = ID_CONN_MRUP_INUSE_Unrecognized;
}

void SETPRESENT_TCONN_DPCP_INCFG_Data (TCONN_DPCP_INCFG_Data* sp, TCONN_DPCP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TCONN_DPCP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_CONN_DPCP_INCFG_CONN_DPCP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_CONN_DPCP_INCFG_ConfigurationRequest = (c_CONN_DPCP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_CONN_DPCP_INCFG_ConfigurationRequest));
			INIT_c_CONN_DPCP_INCFG_ConfigurationRequest (sp->Data.fld_c_CONN_DPCP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_CONN_DPCP_INCFG_CONN_DPCP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_CONN_DPCP_INCFG_ConfigurationResponse = (c_CONN_DPCP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_CONN_DPCP_INCFG_ConfigurationResponse));
			INIT_c_CONN_DPCP_INCFG_ConfigurationResponse (sp->Data.fld_c_CONN_DPCP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TCONN_DPCP_INCFG_Data (TCONN_DPCP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_CONN_DPCP_INCFG_CONN_DPCP_INCFG_ConfigurationRequest: {
			FREE_c_CONN_DPCP_INCFG_ConfigurationRequest (sp->Data.fld_c_CONN_DPCP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_CONN_DPCP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_CONN_DPCP_INCFG_CONN_DPCP_INCFG_ConfigurationResponse: {
			FREE_c_CONN_DPCP_INCFG_ConfigurationResponse (sp->Data.fld_c_CONN_DPCP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_CONN_DPCP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_CONN_DPCP_INCFG_Unrecognized;
}

void SETPRESENT_TCONN_OMP_INCFG_Data (TCONN_OMP_INCFG_Data* sp, TCONN_OMP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TCONN_OMP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_CONN_OMP_INCFG_CONN_OMP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_CONN_OMP_INCFG_ConfigurationRequest = (c_CONN_OMP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_CONN_OMP_INCFG_ConfigurationRequest));
			INIT_c_CONN_OMP_INCFG_ConfigurationRequest (sp->Data.fld_c_CONN_OMP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_CONN_OMP_INCFG_CONN_OMP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_CONN_OMP_INCFG_ConfigurationResponse = (c_CONN_OMP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_CONN_OMP_INCFG_ConfigurationResponse));
			INIT_c_CONN_OMP_INCFG_ConfigurationResponse (sp->Data.fld_c_CONN_OMP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TCONN_OMP_INCFG_Data (TCONN_OMP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_CONN_OMP_INCFG_CONN_OMP_INCFG_ConfigurationRequest: {
			FREE_c_CONN_OMP_INCFG_ConfigurationRequest (sp->Data.fld_c_CONN_OMP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_CONN_OMP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_CONN_OMP_INCFG_CONN_OMP_INCFG_ConfigurationResponse: {
			FREE_c_CONN_OMP_INCFG_ConfigurationResponse (sp->Data.fld_c_CONN_OMP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_CONN_OMP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_CONN_OMP_INCFG_Unrecognized;
}

void SETPRESENT_TCONN_OMP_INUSE_Data (TCONN_OMP_INUSE_Data* sp, TCONN_OMP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TCONN_OMP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_CONN_OMP_INUSE_CONN_OMP_INUSE_QuickConfig: {
			sp->Data.fld_c_CONN_OMP_INUSE_QuickConfig = (c_CONN_OMP_INUSE_QuickConfig*)EDAlloc (sizeof (c_CONN_OMP_INUSE_QuickConfig));
			INIT_c_CONN_OMP_INUSE_QuickConfig (sp->Data.fld_c_CONN_OMP_INUSE_QuickConfig);
			break;
		}
		
		case ID_CONN_OMP_INUSE_CONN_OMP_INUSE_SectorParameters: {
			sp->Data.fld_c_CONN_OMP_INUSE_SectorParameters = (c_CONN_OMP_INUSE_SectorParameters*)EDAlloc (sizeof (c_CONN_OMP_INUSE_SectorParameters));
			INIT_c_CONN_OMP_INUSE_SectorParameters (sp->Data.fld_c_CONN_OMP_INUSE_SectorParameters);
			break;
		}
		
		default:;
	}
}

void FREE_TCONN_OMP_INUSE_Data (TCONN_OMP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_CONN_OMP_INUSE_CONN_OMP_INUSE_QuickConfig: {
			FREE_c_CONN_OMP_INUSE_QuickConfig (sp->Data.fld_c_CONN_OMP_INUSE_QuickConfig);
	EDFree (sp->Data.fld_c_CONN_OMP_INUSE_QuickConfig );
			break;
		}
		
		case ID_CONN_OMP_INUSE_CONN_OMP_INUSE_SectorParameters: {
			FREE_c_CONN_OMP_INUSE_SectorParameters (sp->Data.fld_c_CONN_OMP_INUSE_SectorParameters);
	EDFree (sp->Data.fld_c_CONN_OMP_INUSE_SectorParameters );
			break;
		}
		
		default:;
	}

	sp->Type = ID_CONN_OMP_INUSE_Unrecognized;
}

void SETPRESENT_TSECURITY_DSP_INCFG_Data (TSECURITY_DSP_INCFG_Data* sp, TSECURITY_DSP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TSECURITY_DSP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_SECURITY_DSP_INCFG_SECURITY_DSP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_SECURITY_DSP_INCFG_ConfigurationRequest = (c_SECURITY_DSP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_SECURITY_DSP_INCFG_ConfigurationRequest));
			INIT_c_SECURITY_DSP_INCFG_ConfigurationRequest (sp->Data.fld_c_SECURITY_DSP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_SECURITY_DSP_INCFG_SECURITY_DSP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_SECURITY_DSP_INCFG_ConfigurationResponse = (c_SECURITY_DSP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_SECURITY_DSP_INCFG_ConfigurationResponse));
			INIT_c_SECURITY_DSP_INCFG_ConfigurationResponse (sp->Data.fld_c_SECURITY_DSP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TSECURITY_DSP_INCFG_Data (TSECURITY_DSP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_SECURITY_DSP_INCFG_SECURITY_DSP_INCFG_ConfigurationRequest: {
			FREE_c_SECURITY_DSP_INCFG_ConfigurationRequest (sp->Data.fld_c_SECURITY_DSP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_SECURITY_DSP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_SECURITY_DSP_INCFG_SECURITY_DSP_INCFG_ConfigurationResponse: {
			FREE_c_SECURITY_DSP_INCFG_ConfigurationResponse (sp->Data.fld_c_SECURITY_DSP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_SECURITY_DSP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_SECURITY_DSP_INCFG_Unrecognized;
}

void SETPRESENT_TSECURITY_GSP_INCFG_Data (TSECURITY_GSP_INCFG_Data* sp, TSECURITY_GSP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TSECURITY_GSP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_SECURITY_GSP_INCFG_SECURITY_GSP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_SECURITY_GSP_INCFG_ConfigurationRequest = (c_SECURITY_GSP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_SECURITY_GSP_INCFG_ConfigurationRequest));
			INIT_c_SECURITY_GSP_INCFG_ConfigurationRequest (sp->Data.fld_c_SECURITY_GSP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_SECURITY_GSP_INCFG_SECURITY_GSP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_SECURITY_GSP_INCFG_ConfigurationResponse = (c_SECURITY_GSP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_SECURITY_GSP_INCFG_ConfigurationResponse));
			INIT_c_SECURITY_GSP_INCFG_ConfigurationResponse (sp->Data.fld_c_SECURITY_GSP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TSECURITY_GSP_INCFG_Data (TSECURITY_GSP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_SECURITY_GSP_INCFG_SECURITY_GSP_INCFG_ConfigurationRequest: {
			FREE_c_SECURITY_GSP_INCFG_ConfigurationRequest (sp->Data.fld_c_SECURITY_GSP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_SECURITY_GSP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_SECURITY_GSP_INCFG_SECURITY_GSP_INCFG_ConfigurationResponse: {
			FREE_c_SECURITY_GSP_INCFG_ConfigurationResponse (sp->Data.fld_c_SECURITY_GSP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_SECURITY_GSP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_SECURITY_GSP_INCFG_Unrecognized;
}

void SETPRESENT_TSECURITY_DKEP_INCFG_Data (TSECURITY_DKEP_INCFG_Data* sp, TSECURITY_DKEP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TSECURITY_DKEP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_SECURITY_DKEP_INCFG_SECURITY_DKEP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_SECURITY_DKEP_INCFG_ConfigurationRequest = (c_SECURITY_DKEP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_SECURITY_DKEP_INCFG_ConfigurationRequest));
			INIT_c_SECURITY_DKEP_INCFG_ConfigurationRequest (sp->Data.fld_c_SECURITY_DKEP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_SECURITY_DKEP_INCFG_SECURITY_DKEP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_SECURITY_DKEP_INCFG_ConfigurationResponse = (c_SECURITY_DKEP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_SECURITY_DKEP_INCFG_ConfigurationResponse));
			INIT_c_SECURITY_DKEP_INCFG_ConfigurationResponse (sp->Data.fld_c_SECURITY_DKEP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TSECURITY_DKEP_INCFG_Data (TSECURITY_DKEP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_SECURITY_DKEP_INCFG_SECURITY_DKEP_INCFG_ConfigurationRequest: {
			FREE_c_SECURITY_DKEP_INCFG_ConfigurationRequest (sp->Data.fld_c_SECURITY_DKEP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_SECURITY_DKEP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_SECURITY_DKEP_INCFG_SECURITY_DKEP_INCFG_ConfigurationResponse: {
			FREE_c_SECURITY_DKEP_INCFG_ConfigurationResponse (sp->Data.fld_c_SECURITY_DKEP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_SECURITY_DKEP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_SECURITY_DKEP_INCFG_Unrecognized;
}

void SETPRESENT_TSECURITY_DHKEP_INCFG_Data (TSECURITY_DHKEP_INCFG_Data* sp, TSECURITY_DHKEP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TSECURITY_DHKEP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_SECURITY_DHKEP_INCFG_SECURITY_DHKEP_INCFG_KeyRequest: {
			sp->Data.fld_c_SECURITY_DHKEP_INCFG_KeyRequest = (c_SECURITY_DHKEP_INCFG_KeyRequest*)EDAlloc (sizeof (c_SECURITY_DHKEP_INCFG_KeyRequest));
			INIT_c_SECURITY_DHKEP_INCFG_KeyRequest (sp->Data.fld_c_SECURITY_DHKEP_INCFG_KeyRequest);
			break;
		}
		
		case ID_SECURITY_DHKEP_INCFG_SECURITY_DHKEP_INCFG_KeyResponse: {
			sp->Data.fld_c_SECURITY_DHKEP_INCFG_KeyResponse = (c_SECURITY_DHKEP_INCFG_KeyResponse*)EDAlloc (sizeof (c_SECURITY_DHKEP_INCFG_KeyResponse));
			INIT_c_SECURITY_DHKEP_INCFG_KeyResponse (sp->Data.fld_c_SECURITY_DHKEP_INCFG_KeyResponse);
			break;
		}
		
		case ID_SECURITY_DHKEP_INCFG_SECURITY_DHKEP_INCFG_ANKeyComplete: {
			sp->Data.fld_c_SECURITY_DHKEP_INCFG_ANKeyComplete = (c_SECURITY_DHKEP_INCFG_ANKeyComplete*)EDAlloc (sizeof (c_SECURITY_DHKEP_INCFG_ANKeyComplete));
			INIT_c_SECURITY_DHKEP_INCFG_ANKeyComplete (sp->Data.fld_c_SECURITY_DHKEP_INCFG_ANKeyComplete);
			break;
		}
		
		case ID_SECURITY_DHKEP_INCFG_SECURITY_DHKEP_INCFG_ATKeyComplete: {
			sp->Data.fld_c_SECURITY_DHKEP_INCFG_ATKeyComplete = (c_SECURITY_DHKEP_INCFG_ATKeyComplete*)EDAlloc (sizeof (c_SECURITY_DHKEP_INCFG_ATKeyComplete));
			INIT_c_SECURITY_DHKEP_INCFG_ATKeyComplete (sp->Data.fld_c_SECURITY_DHKEP_INCFG_ATKeyComplete);
			break;
		}
		
		case ID_SECURITY_DHKEP_INCFG_SECURITY_DHKEP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_SECURITY_DHKEP_INCFG_ConfigurationRequest = (c_SECURITY_DHKEP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_SECURITY_DHKEP_INCFG_ConfigurationRequest));
			INIT_c_SECURITY_DHKEP_INCFG_ConfigurationRequest (sp->Data.fld_c_SECURITY_DHKEP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_SECURITY_DHKEP_INCFG_SECURITY_DHKEP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_SECURITY_DHKEP_INCFG_ConfigurationResponse = (c_SECURITY_DHKEP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_SECURITY_DHKEP_INCFG_ConfigurationResponse));
			INIT_c_SECURITY_DHKEP_INCFG_ConfigurationResponse (sp->Data.fld_c_SECURITY_DHKEP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TSECURITY_DHKEP_INCFG_Data (TSECURITY_DHKEP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_SECURITY_DHKEP_INCFG_SECURITY_DHKEP_INCFG_KeyRequest: {
			FREE_c_SECURITY_DHKEP_INCFG_KeyRequest (sp->Data.fld_c_SECURITY_DHKEP_INCFG_KeyRequest);
	EDFree (sp->Data.fld_c_SECURITY_DHKEP_INCFG_KeyRequest );
			break;
		}
		
		case ID_SECURITY_DHKEP_INCFG_SECURITY_DHKEP_INCFG_KeyResponse: {
			FREE_c_SECURITY_DHKEP_INCFG_KeyResponse (sp->Data.fld_c_SECURITY_DHKEP_INCFG_KeyResponse);
	EDFree (sp->Data.fld_c_SECURITY_DHKEP_INCFG_KeyResponse );
			break;
		}
		
		case ID_SECURITY_DHKEP_INCFG_SECURITY_DHKEP_INCFG_ANKeyComplete: {
			FREE_c_SECURITY_DHKEP_INCFG_ANKeyComplete (sp->Data.fld_c_SECURITY_DHKEP_INCFG_ANKeyComplete);
	EDFree (sp->Data.fld_c_SECURITY_DHKEP_INCFG_ANKeyComplete );
			break;
		}
		
		case ID_SECURITY_DHKEP_INCFG_SECURITY_DHKEP_INCFG_ATKeyComplete: {
			FREE_c_SECURITY_DHKEP_INCFG_ATKeyComplete (sp->Data.fld_c_SECURITY_DHKEP_INCFG_ATKeyComplete);
	EDFree (sp->Data.fld_c_SECURITY_DHKEP_INCFG_ATKeyComplete );
			break;
		}
		
		case ID_SECURITY_DHKEP_INCFG_SECURITY_DHKEP_INCFG_ConfigurationRequest: {
			FREE_c_SECURITY_DHKEP_INCFG_ConfigurationRequest (sp->Data.fld_c_SECURITY_DHKEP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_SECURITY_DHKEP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_SECURITY_DHKEP_INCFG_SECURITY_DHKEP_INCFG_ConfigurationResponse: {
			FREE_c_SECURITY_DHKEP_INCFG_ConfigurationResponse (sp->Data.fld_c_SECURITY_DHKEP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_SECURITY_DHKEP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_SECURITY_DHKEP_INCFG_Unrecognized;
}

void SETPRESENT_TSECURITY_DAP_INCFG_Data (TSECURITY_DAP_INCFG_Data* sp, TSECURITY_DAP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TSECURITY_DAP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_SECURITY_DAP_INCFG_SECURITY_DAP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_SECURITY_DAP_INCFG_ConfigurationRequest = (c_SECURITY_DAP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_SECURITY_DAP_INCFG_ConfigurationRequest));
			INIT_c_SECURITY_DAP_INCFG_ConfigurationRequest (sp->Data.fld_c_SECURITY_DAP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_SECURITY_DAP_INCFG_SECURITY_DAP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_SECURITY_DAP_INCFG_ConfigurationResponse = (c_SECURITY_DAP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_SECURITY_DAP_INCFG_ConfigurationResponse));
			INIT_c_SECURITY_DAP_INCFG_ConfigurationResponse (sp->Data.fld_c_SECURITY_DAP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TSECURITY_DAP_INCFG_Data (TSECURITY_DAP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_SECURITY_DAP_INCFG_SECURITY_DAP_INCFG_ConfigurationRequest: {
			FREE_c_SECURITY_DAP_INCFG_ConfigurationRequest (sp->Data.fld_c_SECURITY_DAP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_SECURITY_DAP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_SECURITY_DAP_INCFG_SECURITY_DAP_INCFG_ConfigurationResponse: {
			FREE_c_SECURITY_DAP_INCFG_ConfigurationResponse (sp->Data.fld_c_SECURITY_DAP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_SECURITY_DAP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_SECURITY_DAP_INCFG_Unrecognized;
}

void SETPRESENT_TSECURITY_SHA1AP_INCFG_Data (TSECURITY_SHA1AP_INCFG_Data* sp, TSECURITY_SHA1AP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TSECURITY_SHA1AP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_SECURITY_SHA1AP_INCFG_SECURITY_SHA1AP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_SECURITY_SHA1AP_INCFG_ConfigurationRequest = (c_SECURITY_SHA1AP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_SECURITY_SHA1AP_INCFG_ConfigurationRequest));
			INIT_c_SECURITY_SHA1AP_INCFG_ConfigurationRequest (sp->Data.fld_c_SECURITY_SHA1AP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_SECURITY_SHA1AP_INCFG_SECURITY_SHA1AP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_SECURITY_SHA1AP_INCFG_ConfigurationResponse = (c_SECURITY_SHA1AP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_SECURITY_SHA1AP_INCFG_ConfigurationResponse));
			INIT_c_SECURITY_SHA1AP_INCFG_ConfigurationResponse (sp->Data.fld_c_SECURITY_SHA1AP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TSECURITY_SHA1AP_INCFG_Data (TSECURITY_SHA1AP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_SECURITY_SHA1AP_INCFG_SECURITY_SHA1AP_INCFG_ConfigurationRequest: {
			FREE_c_SECURITY_SHA1AP_INCFG_ConfigurationRequest (sp->Data.fld_c_SECURITY_SHA1AP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_SECURITY_SHA1AP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_SECURITY_SHA1AP_INCFG_SECURITY_SHA1AP_INCFG_ConfigurationResponse: {
			FREE_c_SECURITY_SHA1AP_INCFG_ConfigurationResponse (sp->Data.fld_c_SECURITY_SHA1AP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_SECURITY_SHA1AP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_SECURITY_SHA1AP_INCFG_Unrecognized;
}

void SETPRESENT_TSECURITY_DEP_INCFG_Data (TSECURITY_DEP_INCFG_Data* sp, TSECURITY_DEP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TSECURITY_DEP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_SECURITY_DEP_INCFG_SECURITY_DEP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_SECURITY_DEP_INCFG_ConfigurationRequest = (c_SECURITY_DEP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_SECURITY_DEP_INCFG_ConfigurationRequest));
			INIT_c_SECURITY_DEP_INCFG_ConfigurationRequest (sp->Data.fld_c_SECURITY_DEP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_SECURITY_DEP_INCFG_SECURITY_DEP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_SECURITY_DEP_INCFG_ConfigurationResponse = (c_SECURITY_DEP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_SECURITY_DEP_INCFG_ConfigurationResponse));
			INIT_c_SECURITY_DEP_INCFG_ConfigurationResponse (sp->Data.fld_c_SECURITY_DEP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TSECURITY_DEP_INCFG_Data (TSECURITY_DEP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_SECURITY_DEP_INCFG_SECURITY_DEP_INCFG_ConfigurationRequest: {
			FREE_c_SECURITY_DEP_INCFG_ConfigurationRequest (sp->Data.fld_c_SECURITY_DEP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_SECURITY_DEP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_SECURITY_DEP_INCFG_SECURITY_DEP_INCFG_ConfigurationResponse: {
			FREE_c_SECURITY_DEP_INCFG_ConfigurationResponse (sp->Data.fld_c_SECURITY_DEP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_SECURITY_DEP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_SECURITY_DEP_INCFG_Unrecognized;
}

void SETPRESENT_TMAC_DCCMACP_INCFG_Data (TMAC_DCCMACP_INCFG_Data* sp, TMAC_DCCMACP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TMAC_DCCMACP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_MAC_DCCMACP_INCFG_MAC_DCCMACP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_MAC_DCCMACP_INCFG_ConfigurationRequest = (c_MAC_DCCMACP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_MAC_DCCMACP_INCFG_ConfigurationRequest));
			INIT_c_MAC_DCCMACP_INCFG_ConfigurationRequest (sp->Data.fld_c_MAC_DCCMACP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_MAC_DCCMACP_INCFG_MAC_DCCMACP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_MAC_DCCMACP_INCFG_ConfigurationResponse = (c_MAC_DCCMACP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_MAC_DCCMACP_INCFG_ConfigurationResponse));
			INIT_c_MAC_DCCMACP_INCFG_ConfigurationResponse (sp->Data.fld_c_MAC_DCCMACP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TMAC_DCCMACP_INCFG_Data (TMAC_DCCMACP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_MAC_DCCMACP_INCFG_MAC_DCCMACP_INCFG_ConfigurationRequest: {
			FREE_c_MAC_DCCMACP_INCFG_ConfigurationRequest (sp->Data.fld_c_MAC_DCCMACP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_MAC_DCCMACP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_MAC_DCCMACP_INCFG_MAC_DCCMACP_INCFG_ConfigurationResponse: {
			FREE_c_MAC_DCCMACP_INCFG_ConfigurationResponse (sp->Data.fld_c_MAC_DCCMACP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_MAC_DCCMACP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_MAC_DCCMACP_INCFG_Unrecognized;
}

void SETPRESENT_TMAC_ECCMACP_INCFG_Data (TMAC_ECCMACP_INCFG_Data* sp, TMAC_ECCMACP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TMAC_ECCMACP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_MAC_ECCMACP_INCFG_MAC_ECCMACP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_MAC_ECCMACP_INCFG_ConfigurationRequest = (c_MAC_ECCMACP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_MAC_ECCMACP_INCFG_ConfigurationRequest));
			INIT_c_MAC_ECCMACP_INCFG_ConfigurationRequest (sp->Data.fld_c_MAC_ECCMACP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_MAC_ECCMACP_INCFG_MAC_ECCMACP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_MAC_ECCMACP_INCFG_ConfigurationResponse = (c_MAC_ECCMACP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_MAC_ECCMACP_INCFG_ConfigurationResponse));
			INIT_c_MAC_ECCMACP_INCFG_ConfigurationResponse (sp->Data.fld_c_MAC_ECCMACP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TMAC_ECCMACP_INCFG_Data (TMAC_ECCMACP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_MAC_ECCMACP_INCFG_MAC_ECCMACP_INCFG_ConfigurationRequest: {
			FREE_c_MAC_ECCMACP_INCFG_ConfigurationRequest (sp->Data.fld_c_MAC_ECCMACP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_MAC_ECCMACP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_MAC_ECCMACP_INCFG_MAC_ECCMACP_INCFG_ConfigurationResponse: {
			FREE_c_MAC_ECCMACP_INCFG_ConfigurationResponse (sp->Data.fld_c_MAC_ECCMACP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_MAC_ECCMACP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_MAC_ECCMACP_INCFG_Unrecognized;
}

void SETPRESENT_TMAC_DACMACP_INCFG_Data (TMAC_DACMACP_INCFG_Data* sp, TMAC_DACMACP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TMAC_DACMACP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_MAC_DACMACP_INCFG_MAC_DACMACP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_MAC_DACMACP_INCFG_ConfigurationRequest = (c_MAC_DACMACP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_MAC_DACMACP_INCFG_ConfigurationRequest));
			INIT_c_MAC_DACMACP_INCFG_ConfigurationRequest (sp->Data.fld_c_MAC_DACMACP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_MAC_DACMACP_INCFG_MAC_DACMACP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_MAC_DACMACP_INCFG_ConfigurationResponse = (c_MAC_DACMACP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_MAC_DACMACP_INCFG_ConfigurationResponse));
			INIT_c_MAC_DACMACP_INCFG_ConfigurationResponse (sp->Data.fld_c_MAC_DACMACP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TMAC_DACMACP_INCFG_Data (TMAC_DACMACP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_MAC_DACMACP_INCFG_MAC_DACMACP_INCFG_ConfigurationRequest: {
			FREE_c_MAC_DACMACP_INCFG_ConfigurationRequest (sp->Data.fld_c_MAC_DACMACP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_MAC_DACMACP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_MAC_DACMACP_INCFG_MAC_DACMACP_INCFG_ConfigurationResponse: {
			FREE_c_MAC_DACMACP_INCFG_ConfigurationResponse (sp->Data.fld_c_MAC_DACMACP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_MAC_DACMACP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_MAC_DACMACP_INCFG_Unrecognized;
}

void SETPRESENT_TMAC_DACMACP_INUSE_Data (TMAC_DACMACP_INUSE_Data* sp, TMAC_DACMACP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TMAC_DACMACP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_MAC_DACMACP_INUSE_MAC_DACMACP_INUSE_ACAck: {
			sp->Data.fld_c_MAC_DACMACP_INUSE_ACAck = (c_MAC_DACMACP_INUSE_ACAck*)EDAlloc (sizeof (c_MAC_DACMACP_INUSE_ACAck));
			INIT_c_MAC_DACMACP_INUSE_ACAck (sp->Data.fld_c_MAC_DACMACP_INUSE_ACAck);
			break;
		}
		
		case ID_MAC_DACMACP_INUSE_MAC_DACMACP_INUSE_AccessParameters: {
			sp->Data.fld_c_MAC_DACMACP_INUSE_AccessParameters = (c_MAC_DACMACP_INUSE_AccessParameters*)EDAlloc (sizeof (c_MAC_DACMACP_INUSE_AccessParameters));
			INIT_c_MAC_DACMACP_INUSE_AccessParameters (sp->Data.fld_c_MAC_DACMACP_INUSE_AccessParameters);
			break;
		}
		
		default:;
	}
}

void FREE_TMAC_DACMACP_INUSE_Data (TMAC_DACMACP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_MAC_DACMACP_INUSE_MAC_DACMACP_INUSE_ACAck: {
			FREE_c_MAC_DACMACP_INUSE_ACAck (sp->Data.fld_c_MAC_DACMACP_INUSE_ACAck);
	EDFree (sp->Data.fld_c_MAC_DACMACP_INUSE_ACAck );
			break;
		}
		
		case ID_MAC_DACMACP_INUSE_MAC_DACMACP_INUSE_AccessParameters: {
			FREE_c_MAC_DACMACP_INUSE_AccessParameters (sp->Data.fld_c_MAC_DACMACP_INUSE_AccessParameters);
	EDFree (sp->Data.fld_c_MAC_DACMACP_INUSE_AccessParameters );
			break;
		}
		
		default:;
	}

	sp->Type = ID_MAC_DACMACP_INUSE_Unrecognized;
}

void SETPRESENT_TMAC_EACMACP_INCFG_Data (TMAC_EACMACP_INCFG_Data* sp, TMAC_EACMACP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TMAC_EACMACP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_MAC_EACMACP_INCFG_MAC_EACMACP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_MAC_EACMACP_INCFG_ConfigurationRequest = (c_MAC_EACMACP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_MAC_EACMACP_INCFG_ConfigurationRequest));
			INIT_c_MAC_EACMACP_INCFG_ConfigurationRequest (sp->Data.fld_c_MAC_EACMACP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_MAC_EACMACP_INCFG_MAC_EACMACP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_MAC_EACMACP_INCFG_ConfigurationResponse = (c_MAC_EACMACP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_MAC_EACMACP_INCFG_ConfigurationResponse));
			INIT_c_MAC_EACMACP_INCFG_ConfigurationResponse (sp->Data.fld_c_MAC_EACMACP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TMAC_EACMACP_INCFG_Data (TMAC_EACMACP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_MAC_EACMACP_INCFG_MAC_EACMACP_INCFG_ConfigurationRequest: {
			FREE_c_MAC_EACMACP_INCFG_ConfigurationRequest (sp->Data.fld_c_MAC_EACMACP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_MAC_EACMACP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_MAC_EACMACP_INCFG_MAC_EACMACP_INCFG_ConfigurationResponse: {
			FREE_c_MAC_EACMACP_INCFG_ConfigurationResponse (sp->Data.fld_c_MAC_EACMACP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_MAC_EACMACP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_MAC_EACMACP_INCFG_Unrecognized;
}

void SETPRESENT_TMAC_EACMACP_INUSE_Data (TMAC_EACMACP_INUSE_Data* sp, TMAC_EACMACP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TMAC_EACMACP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_MAC_EACMACP_INUSE_MAC_EACMACP_INUSE_ACAck: {
			sp->Data.fld_c_MAC_EACMACP_INUSE_ACAck = (c_MAC_EACMACP_INUSE_ACAck*)EDAlloc (sizeof (c_MAC_EACMACP_INUSE_ACAck));
			INIT_c_MAC_EACMACP_INUSE_ACAck (sp->Data.fld_c_MAC_EACMACP_INUSE_ACAck);
			break;
		}
		
		case ID_MAC_EACMACP_INUSE_MAC_EACMACP_INUSE_AccessParameters: {
			sp->Data.fld_c_MAC_EACMACP_INUSE_AccessParameters = (c_MAC_EACMACP_INUSE_AccessParameters*)EDAlloc (sizeof (c_MAC_EACMACP_INUSE_AccessParameters));
			INIT_c_MAC_EACMACP_INUSE_AccessParameters (sp->Data.fld_c_MAC_EACMACP_INUSE_AccessParameters);
			break;
		}
		
		case ID_MAC_EACMACP_INUSE_MAC_EACMACP_INUSE_AttributeUpdateRequest: {
			sp->Data.fld_c_MAC_EACMACP_INUSE_AttributeUpdateRequest = (c_MAC_EACMACP_INUSE_AttributeUpdateRequest*)EDAlloc (sizeof (c_MAC_EACMACP_INUSE_AttributeUpdateRequest));
			INIT_c_MAC_EACMACP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_MAC_EACMACP_INUSE_AttributeUpdateRequest);
			break;
		}
		
		case ID_MAC_EACMACP_INUSE_MAC_EACMACP_INUSE_AttributeUpdateAccept: {
			sp->Data.fld_c_MAC_EACMACP_INUSE_AttributeUpdateAccept = (c_MAC_EACMACP_INUSE_AttributeUpdateAccept*)EDAlloc (sizeof (c_MAC_EACMACP_INUSE_AttributeUpdateAccept));
			INIT_c_MAC_EACMACP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_MAC_EACMACP_INUSE_AttributeUpdateAccept);
			break;
		}
		
		case ID_MAC_EACMACP_INUSE_MAC_EACMACP_INUSE_AttributeUpdateReject: {
			sp->Data.fld_c_MAC_EACMACP_INUSE_AttributeUpdateReject = (c_MAC_EACMACP_INUSE_AttributeUpdateReject*)EDAlloc (sizeof (c_MAC_EACMACP_INUSE_AttributeUpdateReject));
			INIT_c_MAC_EACMACP_INUSE_AttributeUpdateReject (sp->Data.fld_c_MAC_EACMACP_INUSE_AttributeUpdateReject);
			break;
		}
		
		default:;
	}
}

void FREE_TMAC_EACMACP_INUSE_Data (TMAC_EACMACP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_MAC_EACMACP_INUSE_MAC_EACMACP_INUSE_ACAck: {
			FREE_c_MAC_EACMACP_INUSE_ACAck (sp->Data.fld_c_MAC_EACMACP_INUSE_ACAck);
	EDFree (sp->Data.fld_c_MAC_EACMACP_INUSE_ACAck );
			break;
		}
		
		case ID_MAC_EACMACP_INUSE_MAC_EACMACP_INUSE_AccessParameters: {
			FREE_c_MAC_EACMACP_INUSE_AccessParameters (sp->Data.fld_c_MAC_EACMACP_INUSE_AccessParameters);
	EDFree (sp->Data.fld_c_MAC_EACMACP_INUSE_AccessParameters );
			break;
		}
		
		case ID_MAC_EACMACP_INUSE_MAC_EACMACP_INUSE_AttributeUpdateRequest: {
			FREE_c_MAC_EACMACP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_MAC_EACMACP_INUSE_AttributeUpdateRequest);
	EDFree (sp->Data.fld_c_MAC_EACMACP_INUSE_AttributeUpdateRequest );
			break;
		}
		
		case ID_MAC_EACMACP_INUSE_MAC_EACMACP_INUSE_AttributeUpdateAccept: {
			FREE_c_MAC_EACMACP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_MAC_EACMACP_INUSE_AttributeUpdateAccept);
	EDFree (sp->Data.fld_c_MAC_EACMACP_INUSE_AttributeUpdateAccept );
			break;
		}
		
		case ID_MAC_EACMACP_INUSE_MAC_EACMACP_INUSE_AttributeUpdateReject: {
			FREE_c_MAC_EACMACP_INUSE_AttributeUpdateReject (sp->Data.fld_c_MAC_EACMACP_INUSE_AttributeUpdateReject);
	EDFree (sp->Data.fld_c_MAC_EACMACP_INUSE_AttributeUpdateReject );
			break;
		}
		
		default:;
	}

	sp->Type = ID_MAC_EACMACP_INUSE_Unrecognized;
}

void SETPRESENT_TMAC_DFTCMACP_INCFG_Data (TMAC_DFTCMACP_INCFG_Data* sp, TMAC_DFTCMACP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TMAC_DFTCMACP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_MAC_DFTCMACP_INCFG_MAC_DFTCMACP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_MAC_DFTCMACP_INCFG_ConfigurationRequest = (c_MAC_DFTCMACP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_MAC_DFTCMACP_INCFG_ConfigurationRequest));
			INIT_c_MAC_DFTCMACP_INCFG_ConfigurationRequest (sp->Data.fld_c_MAC_DFTCMACP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_MAC_DFTCMACP_INCFG_MAC_DFTCMACP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_MAC_DFTCMACP_INCFG_ConfigurationResponse = (c_MAC_DFTCMACP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_MAC_DFTCMACP_INCFG_ConfigurationResponse));
			INIT_c_MAC_DFTCMACP_INCFG_ConfigurationResponse (sp->Data.fld_c_MAC_DFTCMACP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TMAC_DFTCMACP_INCFG_Data (TMAC_DFTCMACP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_MAC_DFTCMACP_INCFG_MAC_DFTCMACP_INCFG_ConfigurationRequest: {
			FREE_c_MAC_DFTCMACP_INCFG_ConfigurationRequest (sp->Data.fld_c_MAC_DFTCMACP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_MAC_DFTCMACP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_MAC_DFTCMACP_INCFG_MAC_DFTCMACP_INCFG_ConfigurationResponse: {
			FREE_c_MAC_DFTCMACP_INCFG_ConfigurationResponse (sp->Data.fld_c_MAC_DFTCMACP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_MAC_DFTCMACP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_MAC_DFTCMACP_INCFG_Unrecognized;
}

void SETPRESENT_TMAC_DFTCMACP_INUSE_Data (TMAC_DFTCMACP_INUSE_Data* sp, TMAC_DFTCMACP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TMAC_DFTCMACP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_MAC_DFTCMACP_INUSE_MAC_DFTCMACP_INUSE_FixedModeEnable: {
			sp->Data.fld_c_MAC_DFTCMACP_INUSE_FixedModeEnable = (c_MAC_DFTCMACP_INUSE_FixedModeEnable*)EDAlloc (sizeof (c_MAC_DFTCMACP_INUSE_FixedModeEnable));
			INIT_c_MAC_DFTCMACP_INUSE_FixedModeEnable (sp->Data.fld_c_MAC_DFTCMACP_INUSE_FixedModeEnable);
			break;
		}
		
		case ID_MAC_DFTCMACP_INUSE_MAC_DFTCMACP_INUSE_FixedModeXoff: {
			sp->Data.fld_c_MAC_DFTCMACP_INUSE_FixedModeXoff = (c_MAC_DFTCMACP_INUSE_FixedModeXoff*)EDAlloc (sizeof (c_MAC_DFTCMACP_INUSE_FixedModeXoff));
			INIT_c_MAC_DFTCMACP_INUSE_FixedModeXoff (sp->Data.fld_c_MAC_DFTCMACP_INUSE_FixedModeXoff);
			break;
		}
		
		default:;
	}
}

void FREE_TMAC_DFTCMACP_INUSE_Data (TMAC_DFTCMACP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_MAC_DFTCMACP_INUSE_MAC_DFTCMACP_INUSE_FixedModeEnable: {
			FREE_c_MAC_DFTCMACP_INUSE_FixedModeEnable (sp->Data.fld_c_MAC_DFTCMACP_INUSE_FixedModeEnable);
	EDFree (sp->Data.fld_c_MAC_DFTCMACP_INUSE_FixedModeEnable );
			break;
		}
		
		case ID_MAC_DFTCMACP_INUSE_MAC_DFTCMACP_INUSE_FixedModeXoff: {
			FREE_c_MAC_DFTCMACP_INUSE_FixedModeXoff (sp->Data.fld_c_MAC_DFTCMACP_INUSE_FixedModeXoff);
	EDFree (sp->Data.fld_c_MAC_DFTCMACP_INUSE_FixedModeXoff );
			break;
		}
		
		default:;
	}

	sp->Type = ID_MAC_DFTCMACP_INUSE_Unrecognized;
}

void SETPRESENT_TMAC_EFTCMACP_INCFG_Data (TMAC_EFTCMACP_INCFG_Data* sp, TMAC_EFTCMACP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TMAC_EFTCMACP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_MAC_EFTCMACP_INCFG_MAC_EFTCMACP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_MAC_EFTCMACP_INCFG_ConfigurationRequest = (c_MAC_EFTCMACP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_MAC_EFTCMACP_INCFG_ConfigurationRequest));
			INIT_c_MAC_EFTCMACP_INCFG_ConfigurationRequest (sp->Data.fld_c_MAC_EFTCMACP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_MAC_EFTCMACP_INCFG_MAC_EFTCMACP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_MAC_EFTCMACP_INCFG_ConfigurationResponse = (c_MAC_EFTCMACP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_MAC_EFTCMACP_INCFG_ConfigurationResponse));
			INIT_c_MAC_EFTCMACP_INCFG_ConfigurationResponse (sp->Data.fld_c_MAC_EFTCMACP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TMAC_EFTCMACP_INCFG_Data (TMAC_EFTCMACP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_MAC_EFTCMACP_INCFG_MAC_EFTCMACP_INCFG_ConfigurationRequest: {
			FREE_c_MAC_EFTCMACP_INCFG_ConfigurationRequest (sp->Data.fld_c_MAC_EFTCMACP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_MAC_EFTCMACP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_MAC_EFTCMACP_INCFG_MAC_EFTCMACP_INCFG_ConfigurationResponse: {
			FREE_c_MAC_EFTCMACP_INCFG_ConfigurationResponse (sp->Data.fld_c_MAC_EFTCMACP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_MAC_EFTCMACP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_MAC_EFTCMACP_INCFG_Unrecognized;
}

void SETPRESENT_TMAC_EFTCMACP_INUSE_Data (TMAC_EFTCMACP_INUSE_Data* sp, TMAC_EFTCMACP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TMAC_EFTCMACP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_MAC_EFTCMACP_INUSE_MAC_EFTCMACP_INUSE_FixedModeEnable: {
			sp->Data.fld_c_MAC_EFTCMACP_INUSE_FixedModeEnable = (c_MAC_EFTCMACP_INUSE_FixedModeEnable*)EDAlloc (sizeof (c_MAC_EFTCMACP_INUSE_FixedModeEnable));
			INIT_c_MAC_EFTCMACP_INUSE_FixedModeEnable (sp->Data.fld_c_MAC_EFTCMACP_INUSE_FixedModeEnable);
			break;
		}
		
		case ID_MAC_EFTCMACP_INUSE_MAC_EFTCMACP_INUSE_FixedModeXoff: {
			sp->Data.fld_c_MAC_EFTCMACP_INUSE_FixedModeXoff = (c_MAC_EFTCMACP_INUSE_FixedModeXoff*)EDAlloc (sizeof (c_MAC_EFTCMACP_INUSE_FixedModeXoff));
			INIT_c_MAC_EFTCMACP_INUSE_FixedModeXoff (sp->Data.fld_c_MAC_EFTCMACP_INUSE_FixedModeXoff);
			break;
		}
		
		case ID_MAC_EFTCMACP_INUSE_MAC_EFTCMACP_INUSE_AttributeUpdateRequest: {
			sp->Data.fld_c_MAC_EFTCMACP_INUSE_AttributeUpdateRequest = (c_MAC_EFTCMACP_INUSE_AttributeUpdateRequest*)EDAlloc (sizeof (c_MAC_EFTCMACP_INUSE_AttributeUpdateRequest));
			INIT_c_MAC_EFTCMACP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_MAC_EFTCMACP_INUSE_AttributeUpdateRequest);
			break;
		}
		
		case ID_MAC_EFTCMACP_INUSE_MAC_EFTCMACP_INUSE_AttributeUpdateAccept: {
			sp->Data.fld_c_MAC_EFTCMACP_INUSE_AttributeUpdateAccept = (c_MAC_EFTCMACP_INUSE_AttributeUpdateAccept*)EDAlloc (sizeof (c_MAC_EFTCMACP_INUSE_AttributeUpdateAccept));
			INIT_c_MAC_EFTCMACP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_MAC_EFTCMACP_INUSE_AttributeUpdateAccept);
			break;
		}
		
		case ID_MAC_EFTCMACP_INUSE_MAC_EFTCMACP_INUSE_AttributeUpdateReject: {
			sp->Data.fld_c_MAC_EFTCMACP_INUSE_AttributeUpdateReject = (c_MAC_EFTCMACP_INUSE_AttributeUpdateReject*)EDAlloc (sizeof (c_MAC_EFTCMACP_INUSE_AttributeUpdateReject));
			INIT_c_MAC_EFTCMACP_INUSE_AttributeUpdateReject (sp->Data.fld_c_MAC_EFTCMACP_INUSE_AttributeUpdateReject);
			break;
		}
		
		default:;
	}
}

void FREE_TMAC_EFTCMACP_INUSE_Data (TMAC_EFTCMACP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_MAC_EFTCMACP_INUSE_MAC_EFTCMACP_INUSE_FixedModeEnable: {
			FREE_c_MAC_EFTCMACP_INUSE_FixedModeEnable (sp->Data.fld_c_MAC_EFTCMACP_INUSE_FixedModeEnable);
	EDFree (sp->Data.fld_c_MAC_EFTCMACP_INUSE_FixedModeEnable );
			break;
		}
		
		case ID_MAC_EFTCMACP_INUSE_MAC_EFTCMACP_INUSE_FixedModeXoff: {
			FREE_c_MAC_EFTCMACP_INUSE_FixedModeXoff (sp->Data.fld_c_MAC_EFTCMACP_INUSE_FixedModeXoff);
	EDFree (sp->Data.fld_c_MAC_EFTCMACP_INUSE_FixedModeXoff );
			break;
		}
		
		case ID_MAC_EFTCMACP_INUSE_MAC_EFTCMACP_INUSE_AttributeUpdateRequest: {
			FREE_c_MAC_EFTCMACP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_MAC_EFTCMACP_INUSE_AttributeUpdateRequest);
	EDFree (sp->Data.fld_c_MAC_EFTCMACP_INUSE_AttributeUpdateRequest );
			break;
		}
		
		case ID_MAC_EFTCMACP_INUSE_MAC_EFTCMACP_INUSE_AttributeUpdateAccept: {
			FREE_c_MAC_EFTCMACP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_MAC_EFTCMACP_INUSE_AttributeUpdateAccept);
	EDFree (sp->Data.fld_c_MAC_EFTCMACP_INUSE_AttributeUpdateAccept );
			break;
		}
		
		case ID_MAC_EFTCMACP_INUSE_MAC_EFTCMACP_INUSE_AttributeUpdateReject: {
			FREE_c_MAC_EFTCMACP_INUSE_AttributeUpdateReject (sp->Data.fld_c_MAC_EFTCMACP_INUSE_AttributeUpdateReject);
	EDFree (sp->Data.fld_c_MAC_EFTCMACP_INUSE_AttributeUpdateReject );
			break;
		}
		
		default:;
	}

	sp->Type = ID_MAC_EFTCMACP_INUSE_Unrecognized;
}

void SETPRESENT_TMAC_MFTCMACP_INCFG_Data (TMAC_MFTCMACP_INCFG_Data* sp, TMAC_MFTCMACP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TMAC_MFTCMACP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_MAC_MFTCMACP_INCFG_MAC_MFTCMACP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_MAC_MFTCMACP_INCFG_ConfigurationRequest = (c_MAC_MFTCMACP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_MAC_MFTCMACP_INCFG_ConfigurationRequest));
			INIT_c_MAC_MFTCMACP_INCFG_ConfigurationRequest (sp->Data.fld_c_MAC_MFTCMACP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_MAC_MFTCMACP_INCFG_MAC_MFTCMACP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_MAC_MFTCMACP_INCFG_ConfigurationResponse = (c_MAC_MFTCMACP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_MAC_MFTCMACP_INCFG_ConfigurationResponse));
			INIT_c_MAC_MFTCMACP_INCFG_ConfigurationResponse (sp->Data.fld_c_MAC_MFTCMACP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TMAC_MFTCMACP_INCFG_Data (TMAC_MFTCMACP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_MAC_MFTCMACP_INCFG_MAC_MFTCMACP_INCFG_ConfigurationRequest: {
			FREE_c_MAC_MFTCMACP_INCFG_ConfigurationRequest (sp->Data.fld_c_MAC_MFTCMACP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_MAC_MFTCMACP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_MAC_MFTCMACP_INCFG_MAC_MFTCMACP_INCFG_ConfigurationResponse: {
			FREE_c_MAC_MFTCMACP_INCFG_ConfigurationResponse (sp->Data.fld_c_MAC_MFTCMACP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_MAC_MFTCMACP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_MAC_MFTCMACP_INCFG_Unrecognized;
}

void SETPRESENT_TMAC_MFTCMACP_INUSE_Data (TMAC_MFTCMACP_INUSE_Data* sp, TMAC_MFTCMACP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TMAC_MFTCMACP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_MAC_MFTCMACP_INUSE_MAC_MFTCMACP_INUSE_FixedModeEnable: {
			sp->Data.fld_c_MAC_MFTCMACP_INUSE_FixedModeEnable = (c_MAC_MFTCMACP_INUSE_FixedModeEnable*)EDAlloc (sizeof (c_MAC_MFTCMACP_INUSE_FixedModeEnable));
			INIT_c_MAC_MFTCMACP_INUSE_FixedModeEnable (sp->Data.fld_c_MAC_MFTCMACP_INUSE_FixedModeEnable);
			break;
		}
		
		case ID_MAC_MFTCMACP_INUSE_MAC_MFTCMACP_INUSE_FixedModeXoff: {
			sp->Data.fld_c_MAC_MFTCMACP_INUSE_FixedModeXoff = (c_MAC_MFTCMACP_INUSE_FixedModeXoff*)EDAlloc (sizeof (c_MAC_MFTCMACP_INUSE_FixedModeXoff));
			INIT_c_MAC_MFTCMACP_INUSE_FixedModeXoff (sp->Data.fld_c_MAC_MFTCMACP_INUSE_FixedModeXoff);
			break;
		}
		
		case ID_MAC_MFTCMACP_INUSE_MAC_MFTCMACP_INUSE_AttributeUpdateRequest: {
			sp->Data.fld_c_MAC_MFTCMACP_INUSE_AttributeUpdateRequest = (c_MAC_MFTCMACP_INUSE_AttributeUpdateRequest*)EDAlloc (sizeof (c_MAC_MFTCMACP_INUSE_AttributeUpdateRequest));
			INIT_c_MAC_MFTCMACP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_MAC_MFTCMACP_INUSE_AttributeUpdateRequest);
			break;
		}
		
		case ID_MAC_MFTCMACP_INUSE_MAC_MFTCMACP_INUSE_AttributeUpdateAccept: {
			sp->Data.fld_c_MAC_MFTCMACP_INUSE_AttributeUpdateAccept = (c_MAC_MFTCMACP_INUSE_AttributeUpdateAccept*)EDAlloc (sizeof (c_MAC_MFTCMACP_INUSE_AttributeUpdateAccept));
			INIT_c_MAC_MFTCMACP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_MAC_MFTCMACP_INUSE_AttributeUpdateAccept);
			break;
		}
		
		case ID_MAC_MFTCMACP_INUSE_MAC_MFTCMACP_INUSE_AttributeUpdateReject: {
			sp->Data.fld_c_MAC_MFTCMACP_INUSE_AttributeUpdateReject = (c_MAC_MFTCMACP_INUSE_AttributeUpdateReject*)EDAlloc (sizeof (c_MAC_MFTCMACP_INUSE_AttributeUpdateReject));
			INIT_c_MAC_MFTCMACP_INUSE_AttributeUpdateReject (sp->Data.fld_c_MAC_MFTCMACP_INUSE_AttributeUpdateReject);
			break;
		}
		
		default:;
	}
}

void FREE_TMAC_MFTCMACP_INUSE_Data (TMAC_MFTCMACP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_MAC_MFTCMACP_INUSE_MAC_MFTCMACP_INUSE_FixedModeEnable: {
			FREE_c_MAC_MFTCMACP_INUSE_FixedModeEnable (sp->Data.fld_c_MAC_MFTCMACP_INUSE_FixedModeEnable);
	EDFree (sp->Data.fld_c_MAC_MFTCMACP_INUSE_FixedModeEnable );
			break;
		}
		
		case ID_MAC_MFTCMACP_INUSE_MAC_MFTCMACP_INUSE_FixedModeXoff: {
			FREE_c_MAC_MFTCMACP_INUSE_FixedModeXoff (sp->Data.fld_c_MAC_MFTCMACP_INUSE_FixedModeXoff);
	EDFree (sp->Data.fld_c_MAC_MFTCMACP_INUSE_FixedModeXoff );
			break;
		}
		
		case ID_MAC_MFTCMACP_INUSE_MAC_MFTCMACP_INUSE_AttributeUpdateRequest: {
			FREE_c_MAC_MFTCMACP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_MAC_MFTCMACP_INUSE_AttributeUpdateRequest);
	EDFree (sp->Data.fld_c_MAC_MFTCMACP_INUSE_AttributeUpdateRequest );
			break;
		}
		
		case ID_MAC_MFTCMACP_INUSE_MAC_MFTCMACP_INUSE_AttributeUpdateAccept: {
			FREE_c_MAC_MFTCMACP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_MAC_MFTCMACP_INUSE_AttributeUpdateAccept);
	EDFree (sp->Data.fld_c_MAC_MFTCMACP_INUSE_AttributeUpdateAccept );
			break;
		}
		
		case ID_MAC_MFTCMACP_INUSE_MAC_MFTCMACP_INUSE_AttributeUpdateReject: {
			FREE_c_MAC_MFTCMACP_INUSE_AttributeUpdateReject (sp->Data.fld_c_MAC_MFTCMACP_INUSE_AttributeUpdateReject);
	EDFree (sp->Data.fld_c_MAC_MFTCMACP_INUSE_AttributeUpdateReject );
			break;
		}
		
		default:;
	}

	sp->Type = ID_MAC_MFTCMACP_INUSE_Unrecognized;
}

void SETPRESENT_TMAC_DRTCMACP_INCFG_Data (TMAC_DRTCMACP_INCFG_Data* sp, TMAC_DRTCMACP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TMAC_DRTCMACP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_MAC_DRTCMACP_INCFG_MAC_DRTCMACP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_MAC_DRTCMACP_INCFG_ConfigurationRequest = (c_MAC_DRTCMACP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_MAC_DRTCMACP_INCFG_ConfigurationRequest));
			INIT_c_MAC_DRTCMACP_INCFG_ConfigurationRequest (sp->Data.fld_c_MAC_DRTCMACP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_MAC_DRTCMACP_INCFG_MAC_DRTCMACP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_MAC_DRTCMACP_INCFG_ConfigurationResponse = (c_MAC_DRTCMACP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_MAC_DRTCMACP_INCFG_ConfigurationResponse));
			INIT_c_MAC_DRTCMACP_INCFG_ConfigurationResponse (sp->Data.fld_c_MAC_DRTCMACP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TMAC_DRTCMACP_INCFG_Data (TMAC_DRTCMACP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_MAC_DRTCMACP_INCFG_MAC_DRTCMACP_INCFG_ConfigurationRequest: {
			FREE_c_MAC_DRTCMACP_INCFG_ConfigurationRequest (sp->Data.fld_c_MAC_DRTCMACP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_MAC_DRTCMACP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_MAC_DRTCMACP_INCFG_MAC_DRTCMACP_INCFG_ConfigurationResponse: {
			FREE_c_MAC_DRTCMACP_INCFG_ConfigurationResponse (sp->Data.fld_c_MAC_DRTCMACP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_MAC_DRTCMACP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_MAC_DRTCMACP_INCFG_Unrecognized;
}

void SETPRESENT_TMAC_DRTCMACP_INUSE_Data (TMAC_DRTCMACP_INUSE_Data* sp, TMAC_DRTCMACP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TMAC_DRTCMACP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_MAC_DRTCMACP_INUSE_MAC_DRTCMACP_INUSE_RTCAck: {
			sp->Data.fld_c_MAC_DRTCMACP_INUSE_RTCAck = (c_MAC_DRTCMACP_INUSE_RTCAck*)EDAlloc (sizeof (c_MAC_DRTCMACP_INUSE_RTCAck));
			INIT_c_MAC_DRTCMACP_INUSE_RTCAck (sp->Data.fld_c_MAC_DRTCMACP_INUSE_RTCAck);
			break;
		}
		
		case ID_MAC_DRTCMACP_INUSE_MAC_DRTCMACP_INUSE_BroadcastReverseRateLimit: {
			sp->Data.fld_c_MAC_DRTCMACP_INUSE_BroadcastReverseRateLimit = (c_MAC_DRTCMACP_INUSE_BroadcastReverseRateLimit*)EDAlloc (sizeof (c_MAC_DRTCMACP_INUSE_BroadcastReverseRateLimit));
			INIT_c_MAC_DRTCMACP_INUSE_BroadcastReverseRateLimit (sp->Data.fld_c_MAC_DRTCMACP_INUSE_BroadcastReverseRateLimit);
			break;
		}
		
		case ID_MAC_DRTCMACP_INUSE_MAC_DRTCMACP_INUSE_UnicastReverseRateLimit: {
			sp->Data.fld_c_MAC_DRTCMACP_INUSE_UnicastReverseRateLimit = (c_MAC_DRTCMACP_INUSE_UnicastReverseRateLimit*)EDAlloc (sizeof (c_MAC_DRTCMACP_INUSE_UnicastReverseRateLimit));
			INIT_c_MAC_DRTCMACP_INUSE_UnicastReverseRateLimit (sp->Data.fld_c_MAC_DRTCMACP_INUSE_UnicastReverseRateLimit);
			break;
		}
		
		default:;
	}
}

void FREE_TMAC_DRTCMACP_INUSE_Data (TMAC_DRTCMACP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_MAC_DRTCMACP_INUSE_MAC_DRTCMACP_INUSE_RTCAck: {
			FREE_c_MAC_DRTCMACP_INUSE_RTCAck (sp->Data.fld_c_MAC_DRTCMACP_INUSE_RTCAck);
	EDFree (sp->Data.fld_c_MAC_DRTCMACP_INUSE_RTCAck );
			break;
		}
		
		case ID_MAC_DRTCMACP_INUSE_MAC_DRTCMACP_INUSE_BroadcastReverseRateLimit: {
			FREE_c_MAC_DRTCMACP_INUSE_BroadcastReverseRateLimit (sp->Data.fld_c_MAC_DRTCMACP_INUSE_BroadcastReverseRateLimit);
	EDFree (sp->Data.fld_c_MAC_DRTCMACP_INUSE_BroadcastReverseRateLimit );
			break;
		}
		
		case ID_MAC_DRTCMACP_INUSE_MAC_DRTCMACP_INUSE_UnicastReverseRateLimit: {
			FREE_c_MAC_DRTCMACP_INUSE_UnicastReverseRateLimit (sp->Data.fld_c_MAC_DRTCMACP_INUSE_UnicastReverseRateLimit);
	EDFree (sp->Data.fld_c_MAC_DRTCMACP_INUSE_UnicastReverseRateLimit );
			break;
		}
		
		default:;
	}

	sp->Type = ID_MAC_DRTCMACP_INUSE_Unrecognized;
}

void SETPRESENT_TMAC_S1RTCMACP_INCFG_Data (TMAC_S1RTCMACP_INCFG_Data* sp, TMAC_S1RTCMACP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TMAC_S1RTCMACP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_MAC_S1RTCMACP_INCFG_MAC_S1RTCMACP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_MAC_S1RTCMACP_INCFG_ConfigurationRequest = (c_MAC_S1RTCMACP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_MAC_S1RTCMACP_INCFG_ConfigurationRequest));
			INIT_c_MAC_S1RTCMACP_INCFG_ConfigurationRequest (sp->Data.fld_c_MAC_S1RTCMACP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_MAC_S1RTCMACP_INCFG_MAC_S1RTCMACP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_MAC_S1RTCMACP_INCFG_ConfigurationResponse = (c_MAC_S1RTCMACP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_MAC_S1RTCMACP_INCFG_ConfigurationResponse));
			INIT_c_MAC_S1RTCMACP_INCFG_ConfigurationResponse (sp->Data.fld_c_MAC_S1RTCMACP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TMAC_S1RTCMACP_INCFG_Data (TMAC_S1RTCMACP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_MAC_S1RTCMACP_INCFG_MAC_S1RTCMACP_INCFG_ConfigurationRequest: {
			FREE_c_MAC_S1RTCMACP_INCFG_ConfigurationRequest (sp->Data.fld_c_MAC_S1RTCMACP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_MAC_S1RTCMACP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_MAC_S1RTCMACP_INCFG_MAC_S1RTCMACP_INCFG_ConfigurationResponse: {
			FREE_c_MAC_S1RTCMACP_INCFG_ConfigurationResponse (sp->Data.fld_c_MAC_S1RTCMACP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_MAC_S1RTCMACP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_MAC_S1RTCMACP_INCFG_Unrecognized;
}

void SETPRESENT_TMAC_S1RTCMACP_INUSE_Data (TMAC_S1RTCMACP_INUSE_Data* sp, TMAC_S1RTCMACP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TMAC_S1RTCMACP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_MAC_S1RTCMACP_INUSE_MAC_S1RTCMACP_INUSE_RTCAck: {
			sp->Data.fld_c_MAC_S1RTCMACP_INUSE_RTCAck = (c_MAC_S1RTCMACP_INUSE_RTCAck*)EDAlloc (sizeof (c_MAC_S1RTCMACP_INUSE_RTCAck));
			INIT_c_MAC_S1RTCMACP_INUSE_RTCAck (sp->Data.fld_c_MAC_S1RTCMACP_INUSE_RTCAck);
			break;
		}
		
		case ID_MAC_S1RTCMACP_INUSE_MAC_S1RTCMACP_INUSE_BroadcastReverseRateLimit: {
			sp->Data.fld_c_MAC_S1RTCMACP_INUSE_BroadcastReverseRateLimit = (c_MAC_S1RTCMACP_INUSE_BroadcastReverseRateLimit*)EDAlloc (sizeof (c_MAC_S1RTCMACP_INUSE_BroadcastReverseRateLimit));
			INIT_c_MAC_S1RTCMACP_INUSE_BroadcastReverseRateLimit (sp->Data.fld_c_MAC_S1RTCMACP_INUSE_BroadcastReverseRateLimit);
			break;
		}
		
		case ID_MAC_S1RTCMACP_INUSE_MAC_S1RTCMACP_INUSE_UnicastReverseRateLimit: {
			sp->Data.fld_c_MAC_S1RTCMACP_INUSE_UnicastReverseRateLimit = (c_MAC_S1RTCMACP_INUSE_UnicastReverseRateLimit*)EDAlloc (sizeof (c_MAC_S1RTCMACP_INUSE_UnicastReverseRateLimit));
			INIT_c_MAC_S1RTCMACP_INUSE_UnicastReverseRateLimit (sp->Data.fld_c_MAC_S1RTCMACP_INUSE_UnicastReverseRateLimit);
			break;
		}
		
		case ID_MAC_S1RTCMACP_INUSE_MAC_S1RTCMACP_INUSE_AttributeUpdateRequest: {
			sp->Data.fld_c_MAC_S1RTCMACP_INUSE_AttributeUpdateRequest = (c_MAC_S1RTCMACP_INUSE_AttributeUpdateRequest*)EDAlloc (sizeof (c_MAC_S1RTCMACP_INUSE_AttributeUpdateRequest));
			INIT_c_MAC_S1RTCMACP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_MAC_S1RTCMACP_INUSE_AttributeUpdateRequest);
			break;
		}
		
		case ID_MAC_S1RTCMACP_INUSE_MAC_S1RTCMACP_INUSE_AttributeUpdateAccept: {
			sp->Data.fld_c_MAC_S1RTCMACP_INUSE_AttributeUpdateAccept = (c_MAC_S1RTCMACP_INUSE_AttributeUpdateAccept*)EDAlloc (sizeof (c_MAC_S1RTCMACP_INUSE_AttributeUpdateAccept));
			INIT_c_MAC_S1RTCMACP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_MAC_S1RTCMACP_INUSE_AttributeUpdateAccept);
			break;
		}
		
		case ID_MAC_S1RTCMACP_INUSE_MAC_S1RTCMACP_INUSE_AttributeUpdateReject: {
			sp->Data.fld_c_MAC_S1RTCMACP_INUSE_AttributeUpdateReject = (c_MAC_S1RTCMACP_INUSE_AttributeUpdateReject*)EDAlloc (sizeof (c_MAC_S1RTCMACP_INUSE_AttributeUpdateReject));
			INIT_c_MAC_S1RTCMACP_INUSE_AttributeUpdateReject (sp->Data.fld_c_MAC_S1RTCMACP_INUSE_AttributeUpdateReject);
			break;
		}
		
		default:;
	}
}

void FREE_TMAC_S1RTCMACP_INUSE_Data (TMAC_S1RTCMACP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_MAC_S1RTCMACP_INUSE_MAC_S1RTCMACP_INUSE_RTCAck: {
			FREE_c_MAC_S1RTCMACP_INUSE_RTCAck (sp->Data.fld_c_MAC_S1RTCMACP_INUSE_RTCAck);
	EDFree (sp->Data.fld_c_MAC_S1RTCMACP_INUSE_RTCAck );
			break;
		}
		
		case ID_MAC_S1RTCMACP_INUSE_MAC_S1RTCMACP_INUSE_BroadcastReverseRateLimit: {
			FREE_c_MAC_S1RTCMACP_INUSE_BroadcastReverseRateLimit (sp->Data.fld_c_MAC_S1RTCMACP_INUSE_BroadcastReverseRateLimit);
	EDFree (sp->Data.fld_c_MAC_S1RTCMACP_INUSE_BroadcastReverseRateLimit );
			break;
		}
		
		case ID_MAC_S1RTCMACP_INUSE_MAC_S1RTCMACP_INUSE_UnicastReverseRateLimit: {
			FREE_c_MAC_S1RTCMACP_INUSE_UnicastReverseRateLimit (sp->Data.fld_c_MAC_S1RTCMACP_INUSE_UnicastReverseRateLimit);
	EDFree (sp->Data.fld_c_MAC_S1RTCMACP_INUSE_UnicastReverseRateLimit );
			break;
		}
		
		case ID_MAC_S1RTCMACP_INUSE_MAC_S1RTCMACP_INUSE_AttributeUpdateRequest: {
			FREE_c_MAC_S1RTCMACP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_MAC_S1RTCMACP_INUSE_AttributeUpdateRequest);
	EDFree (sp->Data.fld_c_MAC_S1RTCMACP_INUSE_AttributeUpdateRequest );
			break;
		}
		
		case ID_MAC_S1RTCMACP_INUSE_MAC_S1RTCMACP_INUSE_AttributeUpdateAccept: {
			FREE_c_MAC_S1RTCMACP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_MAC_S1RTCMACP_INUSE_AttributeUpdateAccept);
	EDFree (sp->Data.fld_c_MAC_S1RTCMACP_INUSE_AttributeUpdateAccept );
			break;
		}
		
		case ID_MAC_S1RTCMACP_INUSE_MAC_S1RTCMACP_INUSE_AttributeUpdateReject: {
			FREE_c_MAC_S1RTCMACP_INUSE_AttributeUpdateReject (sp->Data.fld_c_MAC_S1RTCMACP_INUSE_AttributeUpdateReject);
	EDFree (sp->Data.fld_c_MAC_S1RTCMACP_INUSE_AttributeUpdateReject );
			break;
		}
		
		default:;
	}

	sp->Type = ID_MAC_S1RTCMACP_INUSE_Unrecognized;
}

void SETPRESENT_TMAC_S3RTCMACP_INCFG_Data (TMAC_S3RTCMACP_INCFG_Data* sp, TMAC_S3RTCMACP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TMAC_S3RTCMACP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_MAC_S3RTCMACP_INCFG_MAC_S3RTCMACP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_MAC_S3RTCMACP_INCFG_ConfigurationRequest = (c_MAC_S3RTCMACP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_MAC_S3RTCMACP_INCFG_ConfigurationRequest));
			INIT_c_MAC_S3RTCMACP_INCFG_ConfigurationRequest (sp->Data.fld_c_MAC_S3RTCMACP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_MAC_S3RTCMACP_INCFG_MAC_S3RTCMACP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_MAC_S3RTCMACP_INCFG_ConfigurationResponse = (c_MAC_S3RTCMACP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_MAC_S3RTCMACP_INCFG_ConfigurationResponse));
			INIT_c_MAC_S3RTCMACP_INCFG_ConfigurationResponse (sp->Data.fld_c_MAC_S3RTCMACP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TMAC_S3RTCMACP_INCFG_Data (TMAC_S3RTCMACP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_MAC_S3RTCMACP_INCFG_MAC_S3RTCMACP_INCFG_ConfigurationRequest: {
			FREE_c_MAC_S3RTCMACP_INCFG_ConfigurationRequest (sp->Data.fld_c_MAC_S3RTCMACP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_MAC_S3RTCMACP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_MAC_S3RTCMACP_INCFG_MAC_S3RTCMACP_INCFG_ConfigurationResponse: {
			FREE_c_MAC_S3RTCMACP_INCFG_ConfigurationResponse (sp->Data.fld_c_MAC_S3RTCMACP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_MAC_S3RTCMACP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_MAC_S3RTCMACP_INCFG_Unrecognized;
}

void SETPRESENT_TMAC_S3RTCMACP_INUSE_Data (TMAC_S3RTCMACP_INUSE_Data* sp, TMAC_S3RTCMACP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TMAC_S3RTCMACP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_MAC_S3RTCMACP_INUSE_MAC_S3RTCMACP_INUSE_RTCAck: {
			sp->Data.fld_c_MAC_S3RTCMACP_INUSE_RTCAck = (c_MAC_S3RTCMACP_INUSE_RTCAck*)EDAlloc (sizeof (c_MAC_S3RTCMACP_INUSE_RTCAck));
			INIT_c_MAC_S3RTCMACP_INUSE_RTCAck (sp->Data.fld_c_MAC_S3RTCMACP_INUSE_RTCAck);
			break;
		}
		
		case ID_MAC_S3RTCMACP_INUSE_MAC_S3RTCMACP_INUSE_Request: {
			sp->Data.fld_c_MAC_S3RTCMACP_INUSE_Request = (c_MAC_S3RTCMACP_INUSE_Request*)EDAlloc (sizeof (c_MAC_S3RTCMACP_INUSE_Request));
			INIT_c_MAC_S3RTCMACP_INUSE_Request (sp->Data.fld_c_MAC_S3RTCMACP_INUSE_Request);
			break;
		}
		
		case ID_MAC_S3RTCMACP_INUSE_MAC_S3RTCMACP_INUSE_Grant: {
			sp->Data.fld_c_MAC_S3RTCMACP_INUSE_Grant = (c_MAC_S3RTCMACP_INUSE_Grant*)EDAlloc (sizeof (c_MAC_S3RTCMACP_INUSE_Grant));
			INIT_c_MAC_S3RTCMACP_INUSE_Grant (sp->Data.fld_c_MAC_S3RTCMACP_INUSE_Grant);
			break;
		}
		
		case ID_MAC_S3RTCMACP_INUSE_MAC_S3RTCMACP_INUSE_AttributeUpdateRequest: {
			sp->Data.fld_c_MAC_S3RTCMACP_INUSE_AttributeUpdateRequest = (c_MAC_S3RTCMACP_INUSE_AttributeUpdateRequest*)EDAlloc (sizeof (c_MAC_S3RTCMACP_INUSE_AttributeUpdateRequest));
			INIT_c_MAC_S3RTCMACP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_MAC_S3RTCMACP_INUSE_AttributeUpdateRequest);
			break;
		}
		
		case ID_MAC_S3RTCMACP_INUSE_MAC_S3RTCMACP_INUSE_AttributeUpdateAccept: {
			sp->Data.fld_c_MAC_S3RTCMACP_INUSE_AttributeUpdateAccept = (c_MAC_S3RTCMACP_INUSE_AttributeUpdateAccept*)EDAlloc (sizeof (c_MAC_S3RTCMACP_INUSE_AttributeUpdateAccept));
			INIT_c_MAC_S3RTCMACP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_MAC_S3RTCMACP_INUSE_AttributeUpdateAccept);
			break;
		}
		
		case ID_MAC_S3RTCMACP_INUSE_MAC_S3RTCMACP_INUSE_AttributeUpdateReject: {
			sp->Data.fld_c_MAC_S3RTCMACP_INUSE_AttributeUpdateReject = (c_MAC_S3RTCMACP_INUSE_AttributeUpdateReject*)EDAlloc (sizeof (c_MAC_S3RTCMACP_INUSE_AttributeUpdateReject));
			INIT_c_MAC_S3RTCMACP_INUSE_AttributeUpdateReject (sp->Data.fld_c_MAC_S3RTCMACP_INUSE_AttributeUpdateReject);
			break;
		}
		
		default:;
	}
}

void FREE_TMAC_S3RTCMACP_INUSE_Data (TMAC_S3RTCMACP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_MAC_S3RTCMACP_INUSE_MAC_S3RTCMACP_INUSE_RTCAck: {
			FREE_c_MAC_S3RTCMACP_INUSE_RTCAck (sp->Data.fld_c_MAC_S3RTCMACP_INUSE_RTCAck);
	EDFree (sp->Data.fld_c_MAC_S3RTCMACP_INUSE_RTCAck );
			break;
		}
		
		case ID_MAC_S3RTCMACP_INUSE_MAC_S3RTCMACP_INUSE_Request: {
			FREE_c_MAC_S3RTCMACP_INUSE_Request (sp->Data.fld_c_MAC_S3RTCMACP_INUSE_Request);
	EDFree (sp->Data.fld_c_MAC_S3RTCMACP_INUSE_Request );
			break;
		}
		
		case ID_MAC_S3RTCMACP_INUSE_MAC_S3RTCMACP_INUSE_Grant: {
			FREE_c_MAC_S3RTCMACP_INUSE_Grant (sp->Data.fld_c_MAC_S3RTCMACP_INUSE_Grant);
	EDFree (sp->Data.fld_c_MAC_S3RTCMACP_INUSE_Grant );
			break;
		}
		
		case ID_MAC_S3RTCMACP_INUSE_MAC_S3RTCMACP_INUSE_AttributeUpdateRequest: {
			FREE_c_MAC_S3RTCMACP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_MAC_S3RTCMACP_INUSE_AttributeUpdateRequest);
	EDFree (sp->Data.fld_c_MAC_S3RTCMACP_INUSE_AttributeUpdateRequest );
			break;
		}
		
		case ID_MAC_S3RTCMACP_INUSE_MAC_S3RTCMACP_INUSE_AttributeUpdateAccept: {
			FREE_c_MAC_S3RTCMACP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_MAC_S3RTCMACP_INUSE_AttributeUpdateAccept);
	EDFree (sp->Data.fld_c_MAC_S3RTCMACP_INUSE_AttributeUpdateAccept );
			break;
		}
		
		case ID_MAC_S3RTCMACP_INUSE_MAC_S3RTCMACP_INUSE_AttributeUpdateReject: {
			FREE_c_MAC_S3RTCMACP_INUSE_AttributeUpdateReject (sp->Data.fld_c_MAC_S3RTCMACP_INUSE_AttributeUpdateReject);
	EDFree (sp->Data.fld_c_MAC_S3RTCMACP_INUSE_AttributeUpdateReject );
			break;
		}
		
		default:;
	}

	sp->Type = ID_MAC_S3RTCMACP_INUSE_Unrecognized;
}

void SETPRESENT_TMAC_MRTCMACP_INCFG_Data (TMAC_MRTCMACP_INCFG_Data* sp, TMAC_MRTCMACP_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TMAC_MRTCMACP_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_MAC_MRTCMACP_INCFG_MAC_MRTCMACP_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_MAC_MRTCMACP_INCFG_ConfigurationRequest = (c_MAC_MRTCMACP_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_MAC_MRTCMACP_INCFG_ConfigurationRequest));
			INIT_c_MAC_MRTCMACP_INCFG_ConfigurationRequest (sp->Data.fld_c_MAC_MRTCMACP_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_MAC_MRTCMACP_INCFG_MAC_MRTCMACP_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_MAC_MRTCMACP_INCFG_ConfigurationResponse = (c_MAC_MRTCMACP_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_MAC_MRTCMACP_INCFG_ConfigurationResponse));
			INIT_c_MAC_MRTCMACP_INCFG_ConfigurationResponse (sp->Data.fld_c_MAC_MRTCMACP_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TMAC_MRTCMACP_INCFG_Data (TMAC_MRTCMACP_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_MAC_MRTCMACP_INCFG_MAC_MRTCMACP_INCFG_ConfigurationRequest: {
			FREE_c_MAC_MRTCMACP_INCFG_ConfigurationRequest (sp->Data.fld_c_MAC_MRTCMACP_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_MAC_MRTCMACP_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_MAC_MRTCMACP_INCFG_MAC_MRTCMACP_INCFG_ConfigurationResponse: {
			FREE_c_MAC_MRTCMACP_INCFG_ConfigurationResponse (sp->Data.fld_c_MAC_MRTCMACP_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_MAC_MRTCMACP_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_MAC_MRTCMACP_INCFG_Unrecognized;
}

void SETPRESENT_TMAC_MRTCMACP_INUSE_Data (TMAC_MRTCMACP_INUSE_Data* sp, TMAC_MRTCMACP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TMAC_MRTCMACP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_RTCAck: {
			sp->Data.fld_c_MAC_MRTCMACP_INUSE_RTCAck = (c_MAC_MRTCMACP_INUSE_RTCAck*)EDAlloc (sizeof (c_MAC_MRTCMACP_INUSE_RTCAck));
			INIT_c_MAC_MRTCMACP_INUSE_RTCAck (sp->Data.fld_c_MAC_MRTCMACP_INUSE_RTCAck);
			break;
		}
		
		case ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_CarrierRequest: {
			sp->Data.fld_c_MAC_MRTCMACP_INUSE_CarrierRequest = (c_MAC_MRTCMACP_INUSE_CarrierRequest*)EDAlloc (sizeof (c_MAC_MRTCMACP_INUSE_CarrierRequest));
			INIT_c_MAC_MRTCMACP_INUSE_CarrierRequest (sp->Data.fld_c_MAC_MRTCMACP_INUSE_CarrierRequest);
			break;
		}
		
		case ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped: {
			sp->Data.fld_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped = (c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped*)EDAlloc (sizeof (c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped));
			INIT_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped (sp->Data.fld_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped);
			break;
		}
		
		case ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck: {
			sp->Data.fld_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck = (c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck*)EDAlloc (sizeof (c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck));
			INIT_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck (sp->Data.fld_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck);
			break;
		}
		
		case ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_Request: {
			sp->Data.fld_c_MAC_MRTCMACP_INUSE_Request = (c_MAC_MRTCMACP_INUSE_Request*)EDAlloc (sizeof (c_MAC_MRTCMACP_INUSE_Request));
			INIT_c_MAC_MRTCMACP_INUSE_Request (sp->Data.fld_c_MAC_MRTCMACP_INUSE_Request);
			break;
		}
		
		case ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_Grant: {
			sp->Data.fld_c_MAC_MRTCMACP_INUSE_Grant = (c_MAC_MRTCMACP_INUSE_Grant*)EDAlloc (sizeof (c_MAC_MRTCMACP_INUSE_Grant));
			INIT_c_MAC_MRTCMACP_INUSE_Grant (sp->Data.fld_c_MAC_MRTCMACP_INUSE_Grant);
			break;
		}
		
		case ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_AttributeUpdateRequest: {
			sp->Data.fld_c_MAC_MRTCMACP_INUSE_AttributeUpdateRequest = (c_MAC_MRTCMACP_INUSE_AttributeUpdateRequest*)EDAlloc (sizeof (c_MAC_MRTCMACP_INUSE_AttributeUpdateRequest));
			INIT_c_MAC_MRTCMACP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_MAC_MRTCMACP_INUSE_AttributeUpdateRequest);
			break;
		}
		
		case ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_AttributeUpdateAccept: {
			sp->Data.fld_c_MAC_MRTCMACP_INUSE_AttributeUpdateAccept = (c_MAC_MRTCMACP_INUSE_AttributeUpdateAccept*)EDAlloc (sizeof (c_MAC_MRTCMACP_INUSE_AttributeUpdateAccept));
			INIT_c_MAC_MRTCMACP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_MAC_MRTCMACP_INUSE_AttributeUpdateAccept);
			break;
		}
		
		case ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_AttributeUpdateReject: {
			sp->Data.fld_c_MAC_MRTCMACP_INUSE_AttributeUpdateReject = (c_MAC_MRTCMACP_INUSE_AttributeUpdateReject*)EDAlloc (sizeof (c_MAC_MRTCMACP_INUSE_AttributeUpdateReject));
			INIT_c_MAC_MRTCMACP_INUSE_AttributeUpdateReject (sp->Data.fld_c_MAC_MRTCMACP_INUSE_AttributeUpdateReject);
			break;
		}
		
		default:;
	}
}

void FREE_TMAC_MRTCMACP_INUSE_Data (TMAC_MRTCMACP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_RTCAck: {
			FREE_c_MAC_MRTCMACP_INUSE_RTCAck (sp->Data.fld_c_MAC_MRTCMACP_INUSE_RTCAck);
	EDFree (sp->Data.fld_c_MAC_MRTCMACP_INUSE_RTCAck );
			break;
		}
		
		case ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_CarrierRequest: {
			FREE_c_MAC_MRTCMACP_INUSE_CarrierRequest (sp->Data.fld_c_MAC_MRTCMACP_INUSE_CarrierRequest);
	EDFree (sp->Data.fld_c_MAC_MRTCMACP_INUSE_CarrierRequest );
			break;
		}
		
		case ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped: {
			FREE_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped (sp->Data.fld_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped);
	EDFree (sp->Data.fld_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped );
			break;
		}
		
		case ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck: {
			FREE_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck (sp->Data.fld_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck);
	EDFree (sp->Data.fld_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck );
			break;
		}
		
		case ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_Request: {
			FREE_c_MAC_MRTCMACP_INUSE_Request (sp->Data.fld_c_MAC_MRTCMACP_INUSE_Request);
	EDFree (sp->Data.fld_c_MAC_MRTCMACP_INUSE_Request );
			break;
		}
		
		case ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_Grant: {
			FREE_c_MAC_MRTCMACP_INUSE_Grant (sp->Data.fld_c_MAC_MRTCMACP_INUSE_Grant);
	EDFree (sp->Data.fld_c_MAC_MRTCMACP_INUSE_Grant );
			break;
		}
		
		case ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_AttributeUpdateRequest: {
			FREE_c_MAC_MRTCMACP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_MAC_MRTCMACP_INUSE_AttributeUpdateRequest);
	EDFree (sp->Data.fld_c_MAC_MRTCMACP_INUSE_AttributeUpdateRequest );
			break;
		}
		
		case ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_AttributeUpdateAccept: {
			FREE_c_MAC_MRTCMACP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_MAC_MRTCMACP_INUSE_AttributeUpdateAccept);
	EDFree (sp->Data.fld_c_MAC_MRTCMACP_INUSE_AttributeUpdateAccept );
			break;
		}
		
		case ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_AttributeUpdateReject: {
			FREE_c_MAC_MRTCMACP_INUSE_AttributeUpdateReject (sp->Data.fld_c_MAC_MRTCMACP_INUSE_AttributeUpdateReject);
	EDFree (sp->Data.fld_c_MAC_MRTCMACP_INUSE_AttributeUpdateReject );
			break;
		}
		
		default:;
	}

	sp->Type = ID_MAC_MRTCMACP_INUSE_Unrecognized;
}

void SETPRESENT_TPHYS01_DS0S1PLPI_INCFG_Data (TPHYS01_DS0S1PLPI_INCFG_Data* sp, TPHYS01_DS0S1PLPI_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TPHYS01_DS0S1PLPI_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_PHYS01_DS0S1PLPI_INCFG_PHYS01_DS0S1PLPI_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_PHYS01_DS0S1PLPI_INCFG_ConfigurationRequest = (c_PHYS01_DS0S1PLPI_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_PHYS01_DS0S1PLPI_INCFG_ConfigurationRequest));
			INIT_c_PHYS01_DS0S1PLPI_INCFG_ConfigurationRequest (sp->Data.fld_c_PHYS01_DS0S1PLPI_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_PHYS01_DS0S1PLPI_INCFG_PHYS01_DS0S1PLPI_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_PHYS01_DS0S1PLPI_INCFG_ConfigurationResponse = (c_PHYS01_DS0S1PLPI_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_PHYS01_DS0S1PLPI_INCFG_ConfigurationResponse));
			INIT_c_PHYS01_DS0S1PLPI_INCFG_ConfigurationResponse (sp->Data.fld_c_PHYS01_DS0S1PLPI_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TPHYS01_DS0S1PLPI_INCFG_Data (TPHYS01_DS0S1PLPI_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_PHYS01_DS0S1PLPI_INCFG_PHYS01_DS0S1PLPI_INCFG_ConfigurationRequest: {
			FREE_c_PHYS01_DS0S1PLPI_INCFG_ConfigurationRequest (sp->Data.fld_c_PHYS01_DS0S1PLPI_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_PHYS01_DS0S1PLPI_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_PHYS01_DS0S1PLPI_INCFG_PHYS01_DS0S1PLPI_INCFG_ConfigurationResponse: {
			FREE_c_PHYS01_DS0S1PLPI_INCFG_ConfigurationResponse (sp->Data.fld_c_PHYS01_DS0S1PLPI_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_PHYS01_DS0S1PLPI_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_PHYS01_DS0S1PLPI_INCFG_Unrecognized;
}

void SETPRESENT_TPHYS2_S2PLPI_INCFG_Data (TPHYS2_S2PLPI_INCFG_Data* sp, TPHYS2_S2PLPI_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TPHYS2_S2PLPI_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_PHYS2_S2PLPI_INCFG_PHYS2_S2PLPI_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_PHYS2_S2PLPI_INCFG_ConfigurationRequest = (c_PHYS2_S2PLPI_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_PHYS2_S2PLPI_INCFG_ConfigurationRequest));
			INIT_c_PHYS2_S2PLPI_INCFG_ConfigurationRequest (sp->Data.fld_c_PHYS2_S2PLPI_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_PHYS2_S2PLPI_INCFG_PHYS2_S2PLPI_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_PHYS2_S2PLPI_INCFG_ConfigurationResponse = (c_PHYS2_S2PLPI_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_PHYS2_S2PLPI_INCFG_ConfigurationResponse));
			INIT_c_PHYS2_S2PLPI_INCFG_ConfigurationResponse (sp->Data.fld_c_PHYS2_S2PLPI_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TPHYS2_S2PLPI_INCFG_Data (TPHYS2_S2PLPI_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_PHYS2_S2PLPI_INCFG_PHYS2_S2PLPI_INCFG_ConfigurationRequest: {
			FREE_c_PHYS2_S2PLPI_INCFG_ConfigurationRequest (sp->Data.fld_c_PHYS2_S2PLPI_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_PHYS2_S2PLPI_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_PHYS2_S2PLPI_INCFG_PHYS2_S2PLPI_INCFG_ConfigurationResponse: {
			FREE_c_PHYS2_S2PLPI_INCFG_ConfigurationResponse (sp->Data.fld_c_PHYS2_S2PLPI_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_PHYS2_S2PLPI_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_PHYS2_S2PLPI_INCFG_Unrecognized;
}

void SETPRESENT_TPHYS3_S3PLPI_INCFG_Data (TPHYS3_S3PLPI_INCFG_Data* sp, TPHYS3_S3PLPI_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TPHYS3_S3PLPI_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_PHYS3_S3PLPI_INCFG_PHYS3_S3PLPI_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_PHYS3_S3PLPI_INCFG_ConfigurationRequest = (c_PHYS3_S3PLPI_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_PHYS3_S3PLPI_INCFG_ConfigurationRequest));
			INIT_c_PHYS3_S3PLPI_INCFG_ConfigurationRequest (sp->Data.fld_c_PHYS3_S3PLPI_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_PHYS3_S3PLPI_INCFG_PHYS3_S3PLPI_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_PHYS3_S3PLPI_INCFG_ConfigurationResponse = (c_PHYS3_S3PLPI_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_PHYS3_S3PLPI_INCFG_ConfigurationResponse));
			INIT_c_PHYS3_S3PLPI_INCFG_ConfigurationResponse (sp->Data.fld_c_PHYS3_S3PLPI_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TPHYS3_S3PLPI_INCFG_Data (TPHYS3_S3PLPI_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_PHYS3_S3PLPI_INCFG_PHYS3_S3PLPI_INCFG_ConfigurationRequest: {
			FREE_c_PHYS3_S3PLPI_INCFG_ConfigurationRequest (sp->Data.fld_c_PHYS3_S3PLPI_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_PHYS3_S3PLPI_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_PHYS3_S3PLPI_INCFG_PHYS3_S3PLPI_INCFG_ConfigurationResponse: {
			FREE_c_PHYS3_S3PLPI_INCFG_ConfigurationResponse (sp->Data.fld_c_PHYS3_S3PLPI_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_PHYS3_S3PLPI_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_PHYS3_S3PLPI_INCFG_Unrecognized;
}

void SETPRESENT_TPHYS3_S3PLPI_INUSE_Data (TPHYS3_S3PLPI_INUSE_Data* sp, TPHYS3_S3PLPI_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TPHYS3_S3PLPI_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_PHYS3_S3PLPI_INUSE_PHYS3_S3PLPI_INUSE_AttributeUpdateRequest: {
			sp->Data.fld_c_PHYS3_S3PLPI_INUSE_AttributeUpdateRequest = (c_PHYS3_S3PLPI_INUSE_AttributeUpdateRequest*)EDAlloc (sizeof (c_PHYS3_S3PLPI_INUSE_AttributeUpdateRequest));
			INIT_c_PHYS3_S3PLPI_INUSE_AttributeUpdateRequest (sp->Data.fld_c_PHYS3_S3PLPI_INUSE_AttributeUpdateRequest);
			break;
		}
		
		case ID_PHYS3_S3PLPI_INUSE_PHYS3_S3PLPI_INUSE_AttributeUpdateAccept: {
			sp->Data.fld_c_PHYS3_S3PLPI_INUSE_AttributeUpdateAccept = (c_PHYS3_S3PLPI_INUSE_AttributeUpdateAccept*)EDAlloc (sizeof (c_PHYS3_S3PLPI_INUSE_AttributeUpdateAccept));
			INIT_c_PHYS3_S3PLPI_INUSE_AttributeUpdateAccept (sp->Data.fld_c_PHYS3_S3PLPI_INUSE_AttributeUpdateAccept);
			break;
		}
		
		case ID_PHYS3_S3PLPI_INUSE_PHYS3_S3PLPI_INUSE_AttributeUpdateReject: {
			sp->Data.fld_c_PHYS3_S3PLPI_INUSE_AttributeUpdateReject = (c_PHYS3_S3PLPI_INUSE_AttributeUpdateReject*)EDAlloc (sizeof (c_PHYS3_S3PLPI_INUSE_AttributeUpdateReject));
			INIT_c_PHYS3_S3PLPI_INUSE_AttributeUpdateReject (sp->Data.fld_c_PHYS3_S3PLPI_INUSE_AttributeUpdateReject);
			break;
		}
		
		default:;
	}
}

void FREE_TPHYS3_S3PLPI_INUSE_Data (TPHYS3_S3PLPI_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_PHYS3_S3PLPI_INUSE_PHYS3_S3PLPI_INUSE_AttributeUpdateRequest: {
			FREE_c_PHYS3_S3PLPI_INUSE_AttributeUpdateRequest (sp->Data.fld_c_PHYS3_S3PLPI_INUSE_AttributeUpdateRequest);
	EDFree (sp->Data.fld_c_PHYS3_S3PLPI_INUSE_AttributeUpdateRequest );
			break;
		}
		
		case ID_PHYS3_S3PLPI_INUSE_PHYS3_S3PLPI_INUSE_AttributeUpdateAccept: {
			FREE_c_PHYS3_S3PLPI_INUSE_AttributeUpdateAccept (sp->Data.fld_c_PHYS3_S3PLPI_INUSE_AttributeUpdateAccept);
	EDFree (sp->Data.fld_c_PHYS3_S3PLPI_INUSE_AttributeUpdateAccept );
			break;
		}
		
		case ID_PHYS3_S3PLPI_INUSE_PHYS3_S3PLPI_INUSE_AttributeUpdateReject: {
			FREE_c_PHYS3_S3PLPI_INUSE_AttributeUpdateReject (sp->Data.fld_c_PHYS3_S3PLPI_INUSE_AttributeUpdateReject);
	EDFree (sp->Data.fld_c_PHYS3_S3PLPI_INUSE_AttributeUpdateReject );
			break;
		}
		
		default:;
	}

	sp->Type = ID_PHYS3_S3PLPI_INUSE_Unrecognized;
}

void SETPRESENT_TGEN_GCP_Data (TGEN_GCP_Data* sp, TGEN_GCP_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TGEN_GCP_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_GEN_GCP_GEN_GCP_ConfigurationRequest: {
			sp->Data.fld_c_GEN_GCP_ConfigurationRequest = (c_GEN_GCP_ConfigurationRequest*)EDAlloc (sizeof (c_GEN_GCP_ConfigurationRequest));
			INIT_c_GEN_GCP_ConfigurationRequest (sp->Data.fld_c_GEN_GCP_ConfigurationRequest);
			break;
		}
		
		case ID_GEN_GCP_GEN_GCP_ConfigurationResponse: {
			sp->Data.fld_c_GEN_GCP_ConfigurationResponse = (c_GEN_GCP_ConfigurationResponse*)EDAlloc (sizeof (c_GEN_GCP_ConfigurationResponse));
			INIT_c_GEN_GCP_ConfigurationResponse (sp->Data.fld_c_GEN_GCP_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TGEN_GCP_Data (TGEN_GCP_Data* sp)
{
	switch (sp->Type) {
		case ID_GEN_GCP_GEN_GCP_ConfigurationRequest: {
			FREE_c_GEN_GCP_ConfigurationRequest (sp->Data.fld_c_GEN_GCP_ConfigurationRequest);
	EDFree (sp->Data.fld_c_GEN_GCP_ConfigurationRequest );
			break;
		}
		
		case ID_GEN_GCP_GEN_GCP_ConfigurationResponse: {
			FREE_c_GEN_GCP_ConfigurationResponse (sp->Data.fld_c_GEN_GCP_ConfigurationResponse);
	EDFree (sp->Data.fld_c_GEN_GCP_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_GEN_GCP_Unrecognized;
}

void SETPRESENT_TGEN_GAUP_Data (TGEN_GAUP_Data* sp, TGEN_GAUP_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TGEN_GAUP_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_GEN_GAUP_GEN_GAUP_AttributeUpdateRequest: {
			sp->Data.fld_c_GEN_GAUP_AttributeUpdateRequest = (c_GEN_GAUP_AttributeUpdateRequest*)EDAlloc (sizeof (c_GEN_GAUP_AttributeUpdateRequest));
			INIT_c_GEN_GAUP_AttributeUpdateRequest (sp->Data.fld_c_GEN_GAUP_AttributeUpdateRequest);
			break;
		}
		
		case ID_GEN_GAUP_GEN_GAUP_AttributeUpdateAccept: {
			sp->Data.fld_c_GEN_GAUP_AttributeUpdateAccept = (c_GEN_GAUP_AttributeUpdateAccept*)EDAlloc (sizeof (c_GEN_GAUP_AttributeUpdateAccept));
			INIT_c_GEN_GAUP_AttributeUpdateAccept (sp->Data.fld_c_GEN_GAUP_AttributeUpdateAccept);
			break;
		}
		
		case ID_GEN_GAUP_GEN_GAUP_AttributeUpdateReject: {
			sp->Data.fld_c_GEN_GAUP_AttributeUpdateReject = (c_GEN_GAUP_AttributeUpdateReject*)EDAlloc (sizeof (c_GEN_GAUP_AttributeUpdateReject));
			INIT_c_GEN_GAUP_AttributeUpdateReject (sp->Data.fld_c_GEN_GAUP_AttributeUpdateReject);
			break;
		}
		
		default:;
	}
}

void FREE_TGEN_GAUP_Data (TGEN_GAUP_Data* sp)
{
	switch (sp->Type) {
		case ID_GEN_GAUP_GEN_GAUP_AttributeUpdateRequest: {
			FREE_c_GEN_GAUP_AttributeUpdateRequest (sp->Data.fld_c_GEN_GAUP_AttributeUpdateRequest);
	EDFree (sp->Data.fld_c_GEN_GAUP_AttributeUpdateRequest );
			break;
		}
		
		case ID_GEN_GAUP_GEN_GAUP_AttributeUpdateAccept: {
			FREE_c_GEN_GAUP_AttributeUpdateAccept (sp->Data.fld_c_GEN_GAUP_AttributeUpdateAccept);
	EDFree (sp->Data.fld_c_GEN_GAUP_AttributeUpdateAccept );
			break;
		}
		
		case ID_GEN_GAUP_GEN_GAUP_AttributeUpdateReject: {
			FREE_c_GEN_GAUP_AttributeUpdateReject (sp->Data.fld_c_GEN_GAUP_AttributeUpdateReject);
	EDFree (sp->Data.fld_c_GEN_GAUP_AttributeUpdateReject );
			break;
		}
		
		default:;
	}

	sp->Type = ID_GEN_GAUP_Unrecognized;
}

#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_CONN_DINSP_INUSE (const char* buffer, TCONN_DINSP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal CONN_DINSP_INUSE_Sync */
		case 0x0000: {
			SETPRESENT_TCONN_DINSP_INUSE_Data (data, ID_CONN_DINSP_INUSE_CONN_DINSP_INUSE_Sync);
			INIT_c_CONN_DINSP_INUSE_Sync (data->Data.fld_c_CONN_DINSP_INUSE_Sync);
			retLen = DECODE_c_CONN_DINSP_INUSE_Sync (buffer, 0, data->Data.fld_c_CONN_DINSP_INUSE_Sync, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_CONN_DINSP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_DINSP_INUSE (const char* buffer, int len, TCONN_DINSP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_CONN_DINSP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_CONN_DINSP_INUSE (char* buffer, ED_EXLONG bitOffset, TCONN_DINSP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_CONN_DINSP_INUSE_CONN_DINSP_INUSE_Sync: {
			retLen = ENCODE_c_CONN_DINSP_INUSE_Sync (buffer, 0, data->Data.fld_c_CONN_DINSP_INUSE_Sync, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_SIGAPP_SLP_INCFG (const char* buffer, TSIGAPP_SLP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal SIGAPP_SLP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TSIGAPP_SLP_INCFG_Data (data, ID_SIGAPP_SLP_INCFG_SIGAPP_SLP_INCFG_ConfigurationRequest);
			INIT_c_SIGAPP_SLP_INCFG_ConfigurationRequest (data->Data.fld_c_SIGAPP_SLP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_SIGAPP_SLP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_SIGAPP_SLP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SIGAPP_SLP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TSIGAPP_SLP_INCFG_Data (data, ID_SIGAPP_SLP_INCFG_SIGAPP_SLP_INCFG_ConfigurationResponse);
			INIT_c_SIGAPP_SLP_INCFG_ConfigurationResponse (data->Data.fld_c_SIGAPP_SLP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_SIGAPP_SLP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_SIGAPP_SLP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_SIGAPP_SLP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_SIGAPP_SLP_INCFG (const char* buffer, int len, TSIGAPP_SLP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_SIGAPP_SLP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_SIGAPP_SLP_INCFG (char* buffer, ED_EXLONG bitOffset, TSIGAPP_SLP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_SIGAPP_SLP_INCFG_SIGAPP_SLP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_SIGAPP_SLP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_SIGAPP_SLP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_SIGAPP_SLP_INCFG_SIGAPP_SLP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_SIGAPP_SLP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_SIGAPP_SLP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_SIGAPP_SLP (const char* buffer, TSIGAPP_SLP_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal SIGAPP_SLP_Reset */
		case 0x0000: {
			SETPRESENT_TSIGAPP_SLP_Data (data, ID_SIGAPP_SLP_SIGAPP_SLP_Reset);
			INIT_c_SIGAPP_SLP_Reset (data->Data.fld_c_SIGAPP_SLP_Reset);
			retLen = DECODE_c_SIGAPP_SLP_Reset (buffer, 0, data->Data.fld_c_SIGAPP_SLP_Reset, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SIGAPP_SLP_ResetAck */
		case 0x0001: {
			SETPRESENT_TSIGAPP_SLP_Data (data, ID_SIGAPP_SLP_SIGAPP_SLP_ResetAck);
			INIT_c_SIGAPP_SLP_ResetAck (data->Data.fld_c_SIGAPP_SLP_ResetAck);
			retLen = DECODE_c_SIGAPP_SLP_ResetAck (buffer, 0, data->Data.fld_c_SIGAPP_SLP_ResetAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_SIGAPP_SLP_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_SIGAPP_SLP (const char* buffer, int len, TSIGAPP_SLP_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_SIGAPP_SLP (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_SIGAPP_SLP (char* buffer, ED_EXLONG bitOffset, TSIGAPP_SLP_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_SIGAPP_SLP_SIGAPP_SLP_Reset: {
			retLen = ENCODE_c_SIGAPP_SLP_Reset (buffer, 0, data->Data.fld_c_SIGAPP_SLP_Reset, pCSN1CContextSet);
			break;
		}
		case ID_SIGAPP_SLP_SIGAPP_SLP_ResetAck: {
			retLen = ENCODE_c_SIGAPP_SLP_ResetAck (buffer, 0, data->Data.fld_c_SIGAPP_SLP_ResetAck, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_PKTAPP_DPA_INCFG (const char* buffer, TPKTAPP_DPA_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal PKTAPP_DPA_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TPKTAPP_DPA_INCFG_Data (data, ID_PKTAPP_DPA_INCFG_PKTAPP_DPA_INCFG_ConfigurationRequest);
			INIT_c_PKTAPP_DPA_INCFG_ConfigurationRequest (data->Data.fld_c_PKTAPP_DPA_INCFG_ConfigurationRequest);
			retLen = DECODE_c_PKTAPP_DPA_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_PKTAPP_DPA_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal PKTAPP_DPA_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TPKTAPP_DPA_INCFG_Data (data, ID_PKTAPP_DPA_INCFG_PKTAPP_DPA_INCFG_ConfigurationResponse);
			INIT_c_PKTAPP_DPA_INCFG_ConfigurationResponse (data->Data.fld_c_PKTAPP_DPA_INCFG_ConfigurationResponse);
			retLen = DECODE_c_PKTAPP_DPA_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_PKTAPP_DPA_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_PKTAPP_DPA_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_PKTAPP_DPA_INCFG (const char* buffer, int len, TPKTAPP_DPA_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_PKTAPP_DPA_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_PKTAPP_DPA_INCFG (char* buffer, ED_EXLONG bitOffset, TPKTAPP_DPA_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_PKTAPP_DPA_INCFG_PKTAPP_DPA_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_PKTAPP_DPA_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_PKTAPP_DPA_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_PKTAPP_DPA_INCFG_PKTAPP_DPA_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_PKTAPP_DPA_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_PKTAPP_DPA_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_PKTAPP_RLP_INUSE (const char* buffer, TPKTAPP_RLP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal PKTAPP_RLP_INUSE_Reset */
		case 0x0000: {
			SETPRESENT_TPKTAPP_RLP_INUSE_Data (data, ID_PKTAPP_RLP_INUSE_PKTAPP_RLP_INUSE_Reset);
			INIT_c_PKTAPP_RLP_INUSE_Reset (data->Data.fld_c_PKTAPP_RLP_INUSE_Reset);
			retLen = DECODE_c_PKTAPP_RLP_INUSE_Reset (buffer, 0, data->Data.fld_c_PKTAPP_RLP_INUSE_Reset, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal PKTAPP_RLP_INUSE_ResetAck */
		case 0x0001: {
			SETPRESENT_TPKTAPP_RLP_INUSE_Data (data, ID_PKTAPP_RLP_INUSE_PKTAPP_RLP_INUSE_ResetAck);
			INIT_c_PKTAPP_RLP_INUSE_ResetAck (data->Data.fld_c_PKTAPP_RLP_INUSE_ResetAck);
			retLen = DECODE_c_PKTAPP_RLP_INUSE_ResetAck (buffer, 0, data->Data.fld_c_PKTAPP_RLP_INUSE_ResetAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal PKTAPP_RLP_INUSE_Nak */
		case 0x0002: {
			SETPRESENT_TPKTAPP_RLP_INUSE_Data (data, ID_PKTAPP_RLP_INUSE_PKTAPP_RLP_INUSE_Nak);
			INIT_c_PKTAPP_RLP_INUSE_Nak (data->Data.fld_c_PKTAPP_RLP_INUSE_Nak);
			retLen = DECODE_c_PKTAPP_RLP_INUSE_Nak (buffer, 0, data->Data.fld_c_PKTAPP_RLP_INUSE_Nak, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_PKTAPP_RLP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_PKTAPP_RLP_INUSE (const char* buffer, int len, TPKTAPP_RLP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_PKTAPP_RLP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_PKTAPP_RLP_INUSE (char* buffer, ED_EXLONG bitOffset, TPKTAPP_RLP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_PKTAPP_RLP_INUSE_PKTAPP_RLP_INUSE_Reset: {
			retLen = ENCODE_c_PKTAPP_RLP_INUSE_Reset (buffer, 0, data->Data.fld_c_PKTAPP_RLP_INUSE_Reset, pCSN1CContextSet);
			break;
		}
		case ID_PKTAPP_RLP_INUSE_PKTAPP_RLP_INUSE_ResetAck: {
			retLen = ENCODE_c_PKTAPP_RLP_INUSE_ResetAck (buffer, 0, data->Data.fld_c_PKTAPP_RLP_INUSE_ResetAck, pCSN1CContextSet);
			break;
		}
		case ID_PKTAPP_RLP_INUSE_PKTAPP_RLP_INUSE_Nak: {
			retLen = ENCODE_c_PKTAPP_RLP_INUSE_Nak (buffer, 0, data->Data.fld_c_PKTAPP_RLP_INUSE_Nak, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_PKTAPP_LUP_INUSE (const char* buffer, TPKTAPP_LUP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal PKTAPP_LUP_INUSE_LocationRequest */
		case 0x0003: {
			SETPRESENT_TPKTAPP_LUP_INUSE_Data (data, ID_PKTAPP_LUP_INUSE_PKTAPP_LUP_INUSE_LocationRequest);
			INIT_c_PKTAPP_LUP_INUSE_LocationRequest (data->Data.fld_c_PKTAPP_LUP_INUSE_LocationRequest);
			retLen = DECODE_c_PKTAPP_LUP_INUSE_LocationRequest (buffer, 0, data->Data.fld_c_PKTAPP_LUP_INUSE_LocationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal PKTAPP_LUP_INUSE_LocationNotification */
		case 0x0004: {
			SETPRESENT_TPKTAPP_LUP_INUSE_Data (data, ID_PKTAPP_LUP_INUSE_PKTAPP_LUP_INUSE_LocationNotification);
			INIT_c_PKTAPP_LUP_INUSE_LocationNotification (data->Data.fld_c_PKTAPP_LUP_INUSE_LocationNotification);
			retLen = DECODE_c_PKTAPP_LUP_INUSE_LocationNotification (buffer, 0, data->Data.fld_c_PKTAPP_LUP_INUSE_LocationNotification, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal PKTAPP_LUP_INUSE_LocationAssignment */
		case 0x0005: {
			SETPRESENT_TPKTAPP_LUP_INUSE_Data (data, ID_PKTAPP_LUP_INUSE_PKTAPP_LUP_INUSE_LocationAssignment);
			INIT_c_PKTAPP_LUP_INUSE_LocationAssignment (data->Data.fld_c_PKTAPP_LUP_INUSE_LocationAssignment);
			retLen = DECODE_c_PKTAPP_LUP_INUSE_LocationAssignment (buffer, 0, data->Data.fld_c_PKTAPP_LUP_INUSE_LocationAssignment, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal PKTAPP_LUP_INUSE_LocationComplete */
		case 0x0006: {
			SETPRESENT_TPKTAPP_LUP_INUSE_Data (data, ID_PKTAPP_LUP_INUSE_PKTAPP_LUP_INUSE_LocationComplete);
			INIT_c_PKTAPP_LUP_INUSE_LocationComplete (data->Data.fld_c_PKTAPP_LUP_INUSE_LocationComplete);
			retLen = DECODE_c_PKTAPP_LUP_INUSE_LocationComplete (buffer, 0, data->Data.fld_c_PKTAPP_LUP_INUSE_LocationComplete, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_PKTAPP_LUP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_PKTAPP_LUP_INUSE (const char* buffer, int len, TPKTAPP_LUP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_PKTAPP_LUP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_PKTAPP_LUP_INUSE (char* buffer, ED_EXLONG bitOffset, TPKTAPP_LUP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_PKTAPP_LUP_INUSE_PKTAPP_LUP_INUSE_LocationRequest: {
			retLen = ENCODE_c_PKTAPP_LUP_INUSE_LocationRequest (buffer, 0, data->Data.fld_c_PKTAPP_LUP_INUSE_LocationRequest, pCSN1CContextSet);
			break;
		}
		case ID_PKTAPP_LUP_INUSE_PKTAPP_LUP_INUSE_LocationNotification: {
			retLen = ENCODE_c_PKTAPP_LUP_INUSE_LocationNotification (buffer, 0, data->Data.fld_c_PKTAPP_LUP_INUSE_LocationNotification, pCSN1CContextSet);
			break;
		}
		case ID_PKTAPP_LUP_INUSE_PKTAPP_LUP_INUSE_LocationAssignment: {
			retLen = ENCODE_c_PKTAPP_LUP_INUSE_LocationAssignment (buffer, 0, data->Data.fld_c_PKTAPP_LUP_INUSE_LocationAssignment, pCSN1CContextSet);
			break;
		}
		case ID_PKTAPP_LUP_INUSE_PKTAPP_LUP_INUSE_LocationComplete: {
			retLen = ENCODE_c_PKTAPP_LUP_INUSE_LocationComplete (buffer, 0, data->Data.fld_c_PKTAPP_LUP_INUSE_LocationComplete, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_PKTAPP_FCP_INUSE (const char* buffer, TPKTAPP_FCP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal PKTAPP_FCP_INUSE_XonRequest */
		case 0x0007: {
			SETPRESENT_TPKTAPP_FCP_INUSE_Data (data, ID_PKTAPP_FCP_INUSE_PKTAPP_FCP_INUSE_XonRequest);
			INIT_c_PKTAPP_FCP_INUSE_XonRequest (data->Data.fld_c_PKTAPP_FCP_INUSE_XonRequest);
			retLen = DECODE_c_PKTAPP_FCP_INUSE_XonRequest (buffer, 0, data->Data.fld_c_PKTAPP_FCP_INUSE_XonRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal PKTAPP_FCP_INUSE_XonResponse */
		case 0x0008: {
			SETPRESENT_TPKTAPP_FCP_INUSE_Data (data, ID_PKTAPP_FCP_INUSE_PKTAPP_FCP_INUSE_XonResponse);
			INIT_c_PKTAPP_FCP_INUSE_XonResponse (data->Data.fld_c_PKTAPP_FCP_INUSE_XonResponse);
			retLen = DECODE_c_PKTAPP_FCP_INUSE_XonResponse (buffer, 0, data->Data.fld_c_PKTAPP_FCP_INUSE_XonResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal PKTAPP_FCP_INUSE_XoffRequest */
		case 0x0009: {
			SETPRESENT_TPKTAPP_FCP_INUSE_Data (data, ID_PKTAPP_FCP_INUSE_PKTAPP_FCP_INUSE_XoffRequest);
			INIT_c_PKTAPP_FCP_INUSE_XoffRequest (data->Data.fld_c_PKTAPP_FCP_INUSE_XoffRequest);
			retLen = DECODE_c_PKTAPP_FCP_INUSE_XoffRequest (buffer, 0, data->Data.fld_c_PKTAPP_FCP_INUSE_XoffRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal PKTAPP_FCP_INUSE_XoffResponse */
		case 0x000A: {
			SETPRESENT_TPKTAPP_FCP_INUSE_Data (data, ID_PKTAPP_FCP_INUSE_PKTAPP_FCP_INUSE_XoffResponse);
			INIT_c_PKTAPP_FCP_INUSE_XoffResponse (data->Data.fld_c_PKTAPP_FCP_INUSE_XoffResponse);
			retLen = DECODE_c_PKTAPP_FCP_INUSE_XoffResponse (buffer, 0, data->Data.fld_c_PKTAPP_FCP_INUSE_XoffResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal PKTAPP_FCP_INUSE_DataReady */
		case 0x000B: {
			SETPRESENT_TPKTAPP_FCP_INUSE_Data (data, ID_PKTAPP_FCP_INUSE_PKTAPP_FCP_INUSE_DataReady);
			INIT_c_PKTAPP_FCP_INUSE_DataReady (data->Data.fld_c_PKTAPP_FCP_INUSE_DataReady);
			retLen = DECODE_c_PKTAPP_FCP_INUSE_DataReady (buffer, 0, data->Data.fld_c_PKTAPP_FCP_INUSE_DataReady, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal PKTAPP_FCP_INUSE_DataReadyAck */
		case 0x000C: {
			SETPRESENT_TPKTAPP_FCP_INUSE_Data (data, ID_PKTAPP_FCP_INUSE_PKTAPP_FCP_INUSE_DataReadyAck);
			INIT_c_PKTAPP_FCP_INUSE_DataReadyAck (data->Data.fld_c_PKTAPP_FCP_INUSE_DataReadyAck);
			retLen = DECODE_c_PKTAPP_FCP_INUSE_DataReadyAck (buffer, 0, data->Data.fld_c_PKTAPP_FCP_INUSE_DataReadyAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_PKTAPP_FCP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_PKTAPP_FCP_INUSE (const char* buffer, int len, TPKTAPP_FCP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_PKTAPP_FCP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_PKTAPP_FCP_INUSE (char* buffer, ED_EXLONG bitOffset, TPKTAPP_FCP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_PKTAPP_FCP_INUSE_PKTAPP_FCP_INUSE_XonRequest: {
			retLen = ENCODE_c_PKTAPP_FCP_INUSE_XonRequest (buffer, 0, data->Data.fld_c_PKTAPP_FCP_INUSE_XonRequest, pCSN1CContextSet);
			break;
		}
		case ID_PKTAPP_FCP_INUSE_PKTAPP_FCP_INUSE_XonResponse: {
			retLen = ENCODE_c_PKTAPP_FCP_INUSE_XonResponse (buffer, 0, data->Data.fld_c_PKTAPP_FCP_INUSE_XonResponse, pCSN1CContextSet);
			break;
		}
		case ID_PKTAPP_FCP_INUSE_PKTAPP_FCP_INUSE_XoffRequest: {
			retLen = ENCODE_c_PKTAPP_FCP_INUSE_XoffRequest (buffer, 0, data->Data.fld_c_PKTAPP_FCP_INUSE_XoffRequest, pCSN1CContextSet);
			break;
		}
		case ID_PKTAPP_FCP_INUSE_PKTAPP_FCP_INUSE_XoffResponse: {
			retLen = ENCODE_c_PKTAPP_FCP_INUSE_XoffResponse (buffer, 0, data->Data.fld_c_PKTAPP_FCP_INUSE_XoffResponse, pCSN1CContextSet);
			break;
		}
		case ID_PKTAPP_FCP_INUSE_PKTAPP_FCP_INUSE_DataReady: {
			retLen = ENCODE_c_PKTAPP_FCP_INUSE_DataReady (buffer, 0, data->Data.fld_c_PKTAPP_FCP_INUSE_DataReady, pCSN1CContextSet);
			break;
		}
		case ID_PKTAPP_FCP_INUSE_PKTAPP_FCP_INUSE_DataReadyAck: {
			retLen = ENCODE_c_PKTAPP_FCP_INUSE_DataReadyAck (buffer, 0, data->Data.fld_c_PKTAPP_FCP_INUSE_DataReadyAck, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_MFPAPP_MFPA_INCFG (const char* buffer, TMFPAPP_MFPA_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal MFPAPP_MFPA_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TMFPAPP_MFPA_INCFG_Data (data, ID_MFPAPP_MFPA_INCFG_MFPAPP_MFPA_INCFG_ConfigurationRequest);
			INIT_c_MFPAPP_MFPA_INCFG_ConfigurationRequest (data->Data.fld_c_MFPAPP_MFPA_INCFG_ConfigurationRequest);
			retLen = DECODE_c_MFPAPP_MFPA_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_MFPAPP_MFPA_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MFPAPP_MFPA_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TMFPAPP_MFPA_INCFG_Data (data, ID_MFPAPP_MFPA_INCFG_MFPAPP_MFPA_INCFG_ConfigurationResponse);
			INIT_c_MFPAPP_MFPA_INCFG_ConfigurationResponse (data->Data.fld_c_MFPAPP_MFPA_INCFG_ConfigurationResponse);
			retLen = DECODE_c_MFPAPP_MFPA_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_MFPAPP_MFPA_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_MFPAPP_MFPA_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MFPAPP_MFPA_INCFG (const char* buffer, int len, TMFPAPP_MFPA_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_MFPAPP_MFPA_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_MFPAPP_MFPA_INCFG (char* buffer, ED_EXLONG bitOffset, TMFPAPP_MFPA_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_MFPAPP_MFPA_INCFG_MFPAPP_MFPA_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_MFPAPP_MFPA_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_MFPAPP_MFPA_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_MFPAPP_MFPA_INCFG_MFPAPP_MFPA_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_MFPAPP_MFPA_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_MFPAPP_MFPA_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_MFPAPP_RLP_INUSE (const char* buffer, TMFPAPP_RLP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal MFPAPP_RLP_INUSE_ResetTxIndication */
		case 0x0000: {
			SETPRESENT_TMFPAPP_RLP_INUSE_Data (data, ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ResetTxIndication);
			INIT_c_MFPAPP_RLP_INUSE_ResetTxIndication (data->Data.fld_c_MFPAPP_RLP_INUSE_ResetTxIndication);
			retLen = DECODE_c_MFPAPP_RLP_INUSE_ResetTxIndication (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_ResetTxIndication, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MFPAPP_RLP_INUSE_ResetRxIndication */
		case 0x0001: {
			SETPRESENT_TMFPAPP_RLP_INUSE_Data (data, ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ResetRxIndication);
			INIT_c_MFPAPP_RLP_INUSE_ResetRxIndication (data->Data.fld_c_MFPAPP_RLP_INUSE_ResetRxIndication);
			retLen = DECODE_c_MFPAPP_RLP_INUSE_ResetRxIndication (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_ResetRxIndication, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MFPAPP_RLP_INUSE_ResetTxIndicationAck */
		case 0x000D: {
			SETPRESENT_TMFPAPP_RLP_INUSE_Data (data, ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ResetTxIndicationAck);
			INIT_c_MFPAPP_RLP_INUSE_ResetTxIndicationAck (data->Data.fld_c_MFPAPP_RLP_INUSE_ResetTxIndicationAck);
			retLen = DECODE_c_MFPAPP_RLP_INUSE_ResetTxIndicationAck (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_ResetTxIndicationAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MFPAPP_RLP_INUSE_ResetTxComplete */
		case 0x000E: {
			SETPRESENT_TMFPAPP_RLP_INUSE_Data (data, ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ResetTxComplete);
			INIT_c_MFPAPP_RLP_INUSE_ResetTxComplete (data->Data.fld_c_MFPAPP_RLP_INUSE_ResetTxComplete);
			retLen = DECODE_c_MFPAPP_RLP_INUSE_ResetTxComplete (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_ResetTxComplete, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MFPAPP_RLP_INUSE_ResetRxComplete */
		case 0x000F: {
			SETPRESENT_TMFPAPP_RLP_INUSE_Data (data, ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ResetRxComplete);
			INIT_c_MFPAPP_RLP_INUSE_ResetRxComplete (data->Data.fld_c_MFPAPP_RLP_INUSE_ResetRxComplete);
			retLen = DECODE_c_MFPAPP_RLP_INUSE_ResetRxComplete (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_ResetRxComplete, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MFPAPP_RLP_INUSE_Nak */
		case 0x0002: {
			SETPRESENT_TMFPAPP_RLP_INUSE_Data (data, ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_Nak);
			INIT_c_MFPAPP_RLP_INUSE_Nak (data->Data.fld_c_MFPAPP_RLP_INUSE_Nak);
			retLen = DECODE_c_MFPAPP_RLP_INUSE_Nak (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_Nak, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MFPAPP_RLP_INUSE_ReservationOnRequest */
		case 0x0016: {
			SETPRESENT_TMFPAPP_RLP_INUSE_Data (data, ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ReservationOnRequest);
			INIT_c_MFPAPP_RLP_INUSE_ReservationOnRequest (data->Data.fld_c_MFPAPP_RLP_INUSE_ReservationOnRequest);
			retLen = DECODE_c_MFPAPP_RLP_INUSE_ReservationOnRequest (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_ReservationOnRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MFPAPP_RLP_INUSE_ReservationOffRequest */
		case 0x0017: {
			SETPRESENT_TMFPAPP_RLP_INUSE_Data (data, ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ReservationOffRequest);
			INIT_c_MFPAPP_RLP_INUSE_ReservationOffRequest (data->Data.fld_c_MFPAPP_RLP_INUSE_ReservationOffRequest);
			retLen = DECODE_c_MFPAPP_RLP_INUSE_ReservationOffRequest (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_ReservationOffRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MFPAPP_RLP_INUSE_ReservationAccept */
		case 0x0018: {
			SETPRESENT_TMFPAPP_RLP_INUSE_Data (data, ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ReservationAccept);
			INIT_c_MFPAPP_RLP_INUSE_ReservationAccept (data->Data.fld_c_MFPAPP_RLP_INUSE_ReservationAccept);
			retLen = DECODE_c_MFPAPP_RLP_INUSE_ReservationAccept (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_ReservationAccept, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MFPAPP_RLP_INUSE_ReservationReject */
		case 0x0019: {
			SETPRESENT_TMFPAPP_RLP_INUSE_Data (data, ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ReservationReject);
			INIT_c_MFPAPP_RLP_INUSE_ReservationReject (data->Data.fld_c_MFPAPP_RLP_INUSE_ReservationReject);
			retLen = DECODE_c_MFPAPP_RLP_INUSE_ReservationReject (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_ReservationReject, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MFPAPP_RLP_INUSE_RevReservationOn */
		case 0x001A: {
			SETPRESENT_TMFPAPP_RLP_INUSE_Data (data, ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_RevReservationOn);
			INIT_c_MFPAPP_RLP_INUSE_RevReservationOn (data->Data.fld_c_MFPAPP_RLP_INUSE_RevReservationOn);
			retLen = DECODE_c_MFPAPP_RLP_INUSE_RevReservationOn (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_RevReservationOn, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MFPAPP_RLP_INUSE_RevReservationOff */
		case 0x001B: {
			SETPRESENT_TMFPAPP_RLP_INUSE_Data (data, ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_RevReservationOff);
			INIT_c_MFPAPP_RLP_INUSE_RevReservationOff (data->Data.fld_c_MFPAPP_RLP_INUSE_RevReservationOff);
			retLen = DECODE_c_MFPAPP_RLP_INUSE_RevReservationOff (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_RevReservationOff, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MFPAPP_RLP_INUSE_FwdReservationOff */
		case 0x0022: {
			SETPRESENT_TMFPAPP_RLP_INUSE_Data (data, ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_FwdReservationOff);
			INIT_c_MFPAPP_RLP_INUSE_FwdReservationOff (data->Data.fld_c_MFPAPP_RLP_INUSE_FwdReservationOff);
			retLen = DECODE_c_MFPAPP_RLP_INUSE_FwdReservationOff (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_FwdReservationOff, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MFPAPP_RLP_INUSE_FwdReservationOn */
		case 0x0023: {
			SETPRESENT_TMFPAPP_RLP_INUSE_Data (data, ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_FwdReservationOn);
			INIT_c_MFPAPP_RLP_INUSE_FwdReservationOn (data->Data.fld_c_MFPAPP_RLP_INUSE_FwdReservationOn);
			retLen = DECODE_c_MFPAPP_RLP_INUSE_FwdReservationOn (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_FwdReservationOn, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MFPAPP_RLP_INUSE_FwdReservationAck */
		case 0x0024: {
			SETPRESENT_TMFPAPP_RLP_INUSE_Data (data, ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_FwdReservationAck);
			INIT_c_MFPAPP_RLP_INUSE_FwdReservationAck (data->Data.fld_c_MFPAPP_RLP_INUSE_FwdReservationAck);
			retLen = DECODE_c_MFPAPP_RLP_INUSE_FwdReservationAck (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_FwdReservationAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MFPAPP_RLP_INUSE_AttributeUpdateRequest */
		case 0x0052: {
			SETPRESENT_TMFPAPP_RLP_INUSE_Data (data, ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_AttributeUpdateRequest);
			INIT_c_MFPAPP_RLP_INUSE_AttributeUpdateRequest (data->Data.fld_c_MFPAPP_RLP_INUSE_AttributeUpdateRequest);
			retLen = DECODE_c_MFPAPP_RLP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_AttributeUpdateRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MFPAPP_RLP_INUSE_AttributeUpdateAccept */
		case 0x0053: {
			SETPRESENT_TMFPAPP_RLP_INUSE_Data (data, ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_AttributeUpdateAccept);
			INIT_c_MFPAPP_RLP_INUSE_AttributeUpdateAccept (data->Data.fld_c_MFPAPP_RLP_INUSE_AttributeUpdateAccept);
			retLen = DECODE_c_MFPAPP_RLP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_AttributeUpdateAccept, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MFPAPP_RLP_INUSE_AttributeUpdateReject */
		case 0x0054: {
			SETPRESENT_TMFPAPP_RLP_INUSE_Data (data, ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_AttributeUpdateReject);
			INIT_c_MFPAPP_RLP_INUSE_AttributeUpdateReject (data->Data.fld_c_MFPAPP_RLP_INUSE_AttributeUpdateReject);
			retLen = DECODE_c_MFPAPP_RLP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_AttributeUpdateReject, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_MFPAPP_RLP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MFPAPP_RLP_INUSE (const char* buffer, int len, TMFPAPP_RLP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_MFPAPP_RLP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_MFPAPP_RLP_INUSE (char* buffer, ED_EXLONG bitOffset, TMFPAPP_RLP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ResetTxIndication: {
			retLen = ENCODE_c_MFPAPP_RLP_INUSE_ResetTxIndication (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_ResetTxIndication, pCSN1CContextSet);
			break;
		}
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ResetRxIndication: {
			retLen = ENCODE_c_MFPAPP_RLP_INUSE_ResetRxIndication (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_ResetRxIndication, pCSN1CContextSet);
			break;
		}
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ResetTxIndicationAck: {
			retLen = ENCODE_c_MFPAPP_RLP_INUSE_ResetTxIndicationAck (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_ResetTxIndicationAck, pCSN1CContextSet);
			break;
		}
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ResetTxComplete: {
			retLen = ENCODE_c_MFPAPP_RLP_INUSE_ResetTxComplete (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_ResetTxComplete, pCSN1CContextSet);
			break;
		}
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ResetRxComplete: {
			retLen = ENCODE_c_MFPAPP_RLP_INUSE_ResetRxComplete (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_ResetRxComplete, pCSN1CContextSet);
			break;
		}
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_Nak: {
			retLen = ENCODE_c_MFPAPP_RLP_INUSE_Nak (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_Nak, pCSN1CContextSet);
			break;
		}
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ReservationOnRequest: {
			retLen = ENCODE_c_MFPAPP_RLP_INUSE_ReservationOnRequest (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_ReservationOnRequest, pCSN1CContextSet);
			break;
		}
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ReservationOffRequest: {
			retLen = ENCODE_c_MFPAPP_RLP_INUSE_ReservationOffRequest (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_ReservationOffRequest, pCSN1CContextSet);
			break;
		}
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ReservationAccept: {
			retLen = ENCODE_c_MFPAPP_RLP_INUSE_ReservationAccept (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_ReservationAccept, pCSN1CContextSet);
			break;
		}
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_ReservationReject: {
			retLen = ENCODE_c_MFPAPP_RLP_INUSE_ReservationReject (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_ReservationReject, pCSN1CContextSet);
			break;
		}
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_RevReservationOn: {
			retLen = ENCODE_c_MFPAPP_RLP_INUSE_RevReservationOn (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_RevReservationOn, pCSN1CContextSet);
			break;
		}
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_RevReservationOff: {
			retLen = ENCODE_c_MFPAPP_RLP_INUSE_RevReservationOff (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_RevReservationOff, pCSN1CContextSet);
			break;
		}
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_FwdReservationOff: {
			retLen = ENCODE_c_MFPAPP_RLP_INUSE_FwdReservationOff (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_FwdReservationOff, pCSN1CContextSet);
			break;
		}
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_FwdReservationOn: {
			retLen = ENCODE_c_MFPAPP_RLP_INUSE_FwdReservationOn (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_FwdReservationOn, pCSN1CContextSet);
			break;
		}
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_FwdReservationAck: {
			retLen = ENCODE_c_MFPAPP_RLP_INUSE_FwdReservationAck (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_FwdReservationAck, pCSN1CContextSet);
			break;
		}
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_AttributeUpdateRequest: {
			retLen = ENCODE_c_MFPAPP_RLP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_AttributeUpdateRequest, pCSN1CContextSet);
			break;
		}
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_AttributeUpdateAccept: {
			retLen = ENCODE_c_MFPAPP_RLP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_AttributeUpdateAccept, pCSN1CContextSet);
			break;
		}
		case ID_MFPAPP_RLP_INUSE_MFPAPP_RLP_INUSE_AttributeUpdateReject: {
			retLen = ENCODE_c_MFPAPP_RLP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_MFPAPP_RLP_INUSE_AttributeUpdateReject, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_MFPAPP_DOSP_INUSE (const char* buffer, TMFPAPP_DOSP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal MFPAPP_DOSP_INUSE_DataOverSignaling */
		case 0x0014: {
			SETPRESENT_TMFPAPP_DOSP_INUSE_Data (data, ID_MFPAPP_DOSP_INUSE_MFPAPP_DOSP_INUSE_DataOverSignaling);
			INIT_c_MFPAPP_DOSP_INUSE_DataOverSignaling (data->Data.fld_c_MFPAPP_DOSP_INUSE_DataOverSignaling);
			retLen = DECODE_c_MFPAPP_DOSP_INUSE_DataOverSignaling (buffer, 0, data->Data.fld_c_MFPAPP_DOSP_INUSE_DataOverSignaling, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MFPAPP_DOSP_INUSE_DataOverSignalingAck */
		case 0x0015: {
			SETPRESENT_TMFPAPP_DOSP_INUSE_Data (data, ID_MFPAPP_DOSP_INUSE_MFPAPP_DOSP_INUSE_DataOverSignalingAck);
			INIT_c_MFPAPP_DOSP_INUSE_DataOverSignalingAck (data->Data.fld_c_MFPAPP_DOSP_INUSE_DataOverSignalingAck);
			retLen = DECODE_c_MFPAPP_DOSP_INUSE_DataOverSignalingAck (buffer, 0, data->Data.fld_c_MFPAPP_DOSP_INUSE_DataOverSignalingAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_MFPAPP_DOSP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MFPAPP_DOSP_INUSE (const char* buffer, int len, TMFPAPP_DOSP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_MFPAPP_DOSP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_MFPAPP_DOSP_INUSE (char* buffer, ED_EXLONG bitOffset, TMFPAPP_DOSP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_MFPAPP_DOSP_INUSE_MFPAPP_DOSP_INUSE_DataOverSignaling: {
			retLen = ENCODE_c_MFPAPP_DOSP_INUSE_DataOverSignaling (buffer, 0, data->Data.fld_c_MFPAPP_DOSP_INUSE_DataOverSignaling, pCSN1CContextSet);
			break;
		}
		case ID_MFPAPP_DOSP_INUSE_MFPAPP_DOSP_INUSE_DataOverSignalingAck: {
			retLen = ENCODE_c_MFPAPP_DOSP_INUSE_DataOverSignalingAck (buffer, 0, data->Data.fld_c_MFPAPP_DOSP_INUSE_DataOverSignalingAck, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_MFPAPP_LUP_INUSE (const char* buffer, TMFPAPP_LUP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal MFPAPP_LUP_INUSE_LocationRequest */
		case 0x0003: {
			SETPRESENT_TMFPAPP_LUP_INUSE_Data (data, ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_LocationRequest);
			INIT_c_MFPAPP_LUP_INUSE_LocationRequest (data->Data.fld_c_MFPAPP_LUP_INUSE_LocationRequest);
			retLen = DECODE_c_MFPAPP_LUP_INUSE_LocationRequest (buffer, 0, data->Data.fld_c_MFPAPP_LUP_INUSE_LocationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MFPAPP_LUP_INUSE_LocationNotification */
		case 0x0004: {
			SETPRESENT_TMFPAPP_LUP_INUSE_Data (data, ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_LocationNotification);
			INIT_c_MFPAPP_LUP_INUSE_LocationNotification (data->Data.fld_c_MFPAPP_LUP_INUSE_LocationNotification);
			retLen = DECODE_c_MFPAPP_LUP_INUSE_LocationNotification (buffer, 0, data->Data.fld_c_MFPAPP_LUP_INUSE_LocationNotification, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MFPAPP_LUP_INUSE_LocationAssignment */
		case 0x0005: {
			SETPRESENT_TMFPAPP_LUP_INUSE_Data (data, ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_LocationAssignment);
			INIT_c_MFPAPP_LUP_INUSE_LocationAssignment (data->Data.fld_c_MFPAPP_LUP_INUSE_LocationAssignment);
			retLen = DECODE_c_MFPAPP_LUP_INUSE_LocationAssignment (buffer, 0, data->Data.fld_c_MFPAPP_LUP_INUSE_LocationAssignment, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MFPAPP_LUP_INUSE_LocationComplete */
		case 0x0006: {
			SETPRESENT_TMFPAPP_LUP_INUSE_Data (data, ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_LocationComplete);
			INIT_c_MFPAPP_LUP_INUSE_LocationComplete (data->Data.fld_c_MFPAPP_LUP_INUSE_LocationComplete);
			retLen = DECODE_c_MFPAPP_LUP_INUSE_LocationComplete (buffer, 0, data->Data.fld_c_MFPAPP_LUP_INUSE_LocationComplete, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MFPAPP_LUP_INUSE_StorageBLOBRequest */
		case 0x0010: {
			SETPRESENT_TMFPAPP_LUP_INUSE_Data (data, ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_StorageBLOBRequest);
			INIT_c_MFPAPP_LUP_INUSE_StorageBLOBRequest (data->Data.fld_c_MFPAPP_LUP_INUSE_StorageBLOBRequest);
			retLen = DECODE_c_MFPAPP_LUP_INUSE_StorageBLOBRequest (buffer, 0, data->Data.fld_c_MFPAPP_LUP_INUSE_StorageBLOBRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MFPAPP_LUP_INUSE_StorageBLOBNotification */
		case 0x0011: {
			SETPRESENT_TMFPAPP_LUP_INUSE_Data (data, ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_StorageBLOBNotification);
			INIT_c_MFPAPP_LUP_INUSE_StorageBLOBNotification (data->Data.fld_c_MFPAPP_LUP_INUSE_StorageBLOBNotification);
			retLen = DECODE_c_MFPAPP_LUP_INUSE_StorageBLOBNotification (buffer, 0, data->Data.fld_c_MFPAPP_LUP_INUSE_StorageBLOBNotification, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MFPAPP_LUP_INUSE_StorageBLOBAssignment */
		case 0x0012: {
			SETPRESENT_TMFPAPP_LUP_INUSE_Data (data, ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_StorageBLOBAssignment);
			INIT_c_MFPAPP_LUP_INUSE_StorageBLOBAssignment (data->Data.fld_c_MFPAPP_LUP_INUSE_StorageBLOBAssignment);
			retLen = DECODE_c_MFPAPP_LUP_INUSE_StorageBLOBAssignment (buffer, 0, data->Data.fld_c_MFPAPP_LUP_INUSE_StorageBLOBAssignment, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MFPAPP_LUP_INUSE_StorageBLOBComplete */
		case 0x0013: {
			SETPRESENT_TMFPAPP_LUP_INUSE_Data (data, ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_StorageBLOBComplete);
			INIT_c_MFPAPP_LUP_INUSE_StorageBLOBComplete (data->Data.fld_c_MFPAPP_LUP_INUSE_StorageBLOBComplete);
			retLen = DECODE_c_MFPAPP_LUP_INUSE_StorageBLOBComplete (buffer, 0, data->Data.fld_c_MFPAPP_LUP_INUSE_StorageBLOBComplete, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_MFPAPP_LUP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MFPAPP_LUP_INUSE (const char* buffer, int len, TMFPAPP_LUP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_MFPAPP_LUP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_MFPAPP_LUP_INUSE (char* buffer, ED_EXLONG bitOffset, TMFPAPP_LUP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_LocationRequest: {
			retLen = ENCODE_c_MFPAPP_LUP_INUSE_LocationRequest (buffer, 0, data->Data.fld_c_MFPAPP_LUP_INUSE_LocationRequest, pCSN1CContextSet);
			break;
		}
		case ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_LocationNotification: {
			retLen = ENCODE_c_MFPAPP_LUP_INUSE_LocationNotification (buffer, 0, data->Data.fld_c_MFPAPP_LUP_INUSE_LocationNotification, pCSN1CContextSet);
			break;
		}
		case ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_LocationAssignment: {
			retLen = ENCODE_c_MFPAPP_LUP_INUSE_LocationAssignment (buffer, 0, data->Data.fld_c_MFPAPP_LUP_INUSE_LocationAssignment, pCSN1CContextSet);
			break;
		}
		case ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_LocationComplete: {
			retLen = ENCODE_c_MFPAPP_LUP_INUSE_LocationComplete (buffer, 0, data->Data.fld_c_MFPAPP_LUP_INUSE_LocationComplete, pCSN1CContextSet);
			break;
		}
		case ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_StorageBLOBRequest: {
			retLen = ENCODE_c_MFPAPP_LUP_INUSE_StorageBLOBRequest (buffer, 0, data->Data.fld_c_MFPAPP_LUP_INUSE_StorageBLOBRequest, pCSN1CContextSet);
			break;
		}
		case ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_StorageBLOBNotification: {
			retLen = ENCODE_c_MFPAPP_LUP_INUSE_StorageBLOBNotification (buffer, 0, data->Data.fld_c_MFPAPP_LUP_INUSE_StorageBLOBNotification, pCSN1CContextSet);
			break;
		}
		case ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_StorageBLOBAssignment: {
			retLen = ENCODE_c_MFPAPP_LUP_INUSE_StorageBLOBAssignment (buffer, 0, data->Data.fld_c_MFPAPP_LUP_INUSE_StorageBLOBAssignment, pCSN1CContextSet);
			break;
		}
		case ID_MFPAPP_LUP_INUSE_MFPAPP_LUP_INUSE_StorageBLOBComplete: {
			retLen = ENCODE_c_MFPAPP_LUP_INUSE_StorageBLOBComplete (buffer, 0, data->Data.fld_c_MFPAPP_LUP_INUSE_StorageBLOBComplete, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_MFPAPP_FCP_INUSE (const char* buffer, TMFPAPP_FCP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal MFPAPP_FCP_INUSE_XonRequest */
		case 0x0007: {
			SETPRESENT_TMFPAPP_FCP_INUSE_Data (data, ID_MFPAPP_FCP_INUSE_MFPAPP_FCP_INUSE_XonRequest);
			INIT_c_MFPAPP_FCP_INUSE_XonRequest (data->Data.fld_c_MFPAPP_FCP_INUSE_XonRequest);
			retLen = DECODE_c_MFPAPP_FCP_INUSE_XonRequest (buffer, 0, data->Data.fld_c_MFPAPP_FCP_INUSE_XonRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MFPAPP_FCP_INUSE_XonResponse */
		case 0x0008: {
			SETPRESENT_TMFPAPP_FCP_INUSE_Data (data, ID_MFPAPP_FCP_INUSE_MFPAPP_FCP_INUSE_XonResponse);
			INIT_c_MFPAPP_FCP_INUSE_XonResponse (data->Data.fld_c_MFPAPP_FCP_INUSE_XonResponse);
			retLen = DECODE_c_MFPAPP_FCP_INUSE_XonResponse (buffer, 0, data->Data.fld_c_MFPAPP_FCP_INUSE_XonResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MFPAPP_FCP_INUSE_XoffRequest */
		case 0x0009: {
			SETPRESENT_TMFPAPP_FCP_INUSE_Data (data, ID_MFPAPP_FCP_INUSE_MFPAPP_FCP_INUSE_XoffRequest);
			INIT_c_MFPAPP_FCP_INUSE_XoffRequest (data->Data.fld_c_MFPAPP_FCP_INUSE_XoffRequest);
			retLen = DECODE_c_MFPAPP_FCP_INUSE_XoffRequest (buffer, 0, data->Data.fld_c_MFPAPP_FCP_INUSE_XoffRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MFPAPP_FCP_INUSE_XoffResponse */
		case 0x000A: {
			SETPRESENT_TMFPAPP_FCP_INUSE_Data (data, ID_MFPAPP_FCP_INUSE_MFPAPP_FCP_INUSE_XoffResponse);
			INIT_c_MFPAPP_FCP_INUSE_XoffResponse (data->Data.fld_c_MFPAPP_FCP_INUSE_XoffResponse);
			retLen = DECODE_c_MFPAPP_FCP_INUSE_XoffResponse (buffer, 0, data->Data.fld_c_MFPAPP_FCP_INUSE_XoffResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MFPAPP_FCP_INUSE_DataReady */
		case 0x000B: {
			SETPRESENT_TMFPAPP_FCP_INUSE_Data (data, ID_MFPAPP_FCP_INUSE_MFPAPP_FCP_INUSE_DataReady);
			INIT_c_MFPAPP_FCP_INUSE_DataReady (data->Data.fld_c_MFPAPP_FCP_INUSE_DataReady);
			retLen = DECODE_c_MFPAPP_FCP_INUSE_DataReady (buffer, 0, data->Data.fld_c_MFPAPP_FCP_INUSE_DataReady, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MFPAPP_FCP_INUSE_DataReadyAck */
		case 0x000C: {
			SETPRESENT_TMFPAPP_FCP_INUSE_Data (data, ID_MFPAPP_FCP_INUSE_MFPAPP_FCP_INUSE_DataReadyAck);
			INIT_c_MFPAPP_FCP_INUSE_DataReadyAck (data->Data.fld_c_MFPAPP_FCP_INUSE_DataReadyAck);
			retLen = DECODE_c_MFPAPP_FCP_INUSE_DataReadyAck (buffer, 0, data->Data.fld_c_MFPAPP_FCP_INUSE_DataReadyAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_MFPAPP_FCP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MFPAPP_FCP_INUSE (const char* buffer, int len, TMFPAPP_FCP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_MFPAPP_FCP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_MFPAPP_FCP_INUSE (char* buffer, ED_EXLONG bitOffset, TMFPAPP_FCP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_MFPAPP_FCP_INUSE_MFPAPP_FCP_INUSE_XonRequest: {
			retLen = ENCODE_c_MFPAPP_FCP_INUSE_XonRequest (buffer, 0, data->Data.fld_c_MFPAPP_FCP_INUSE_XonRequest, pCSN1CContextSet);
			break;
		}
		case ID_MFPAPP_FCP_INUSE_MFPAPP_FCP_INUSE_XonResponse: {
			retLen = ENCODE_c_MFPAPP_FCP_INUSE_XonResponse (buffer, 0, data->Data.fld_c_MFPAPP_FCP_INUSE_XonResponse, pCSN1CContextSet);
			break;
		}
		case ID_MFPAPP_FCP_INUSE_MFPAPP_FCP_INUSE_XoffRequest: {
			retLen = ENCODE_c_MFPAPP_FCP_INUSE_XoffRequest (buffer, 0, data->Data.fld_c_MFPAPP_FCP_INUSE_XoffRequest, pCSN1CContextSet);
			break;
		}
		case ID_MFPAPP_FCP_INUSE_MFPAPP_FCP_INUSE_XoffResponse: {
			retLen = ENCODE_c_MFPAPP_FCP_INUSE_XoffResponse (buffer, 0, data->Data.fld_c_MFPAPP_FCP_INUSE_XoffResponse, pCSN1CContextSet);
			break;
		}
		case ID_MFPAPP_FCP_INUSE_MFPAPP_FCP_INUSE_DataReady: {
			retLen = ENCODE_c_MFPAPP_FCP_INUSE_DataReady (buffer, 0, data->Data.fld_c_MFPAPP_FCP_INUSE_DataReady, pCSN1CContextSet);
			break;
		}
		case ID_MFPAPP_FCP_INUSE_MFPAPP_FCP_INUSE_DataReadyAck: {
			retLen = ENCODE_c_MFPAPP_FCP_INUSE_DataReadyAck (buffer, 0, data->Data.fld_c_MFPAPP_FCP_INUSE_DataReadyAck, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_STREAM_DSP_INCFG (const char* buffer, TSTREAM_DSP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal STREAM_DSP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TSTREAM_DSP_INCFG_Data (data, ID_STREAM_DSP_INCFG_STREAM_DSP_INCFG_ConfigurationRequest);
			INIT_c_STREAM_DSP_INCFG_ConfigurationRequest (data->Data.fld_c_STREAM_DSP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_STREAM_DSP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_STREAM_DSP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal STREAM_DSP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TSTREAM_DSP_INCFG_Data (data, ID_STREAM_DSP_INCFG_STREAM_DSP_INCFG_ConfigurationResponse);
			INIT_c_STREAM_DSP_INCFG_ConfigurationResponse (data->Data.fld_c_STREAM_DSP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_STREAM_DSP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_STREAM_DSP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_STREAM_DSP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_STREAM_DSP_INCFG (const char* buffer, int len, TSTREAM_DSP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_STREAM_DSP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_STREAM_DSP_INCFG (char* buffer, ED_EXLONG bitOffset, TSTREAM_DSP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_STREAM_DSP_INCFG_STREAM_DSP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_STREAM_DSP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_STREAM_DSP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_STREAM_DSP_INCFG_STREAM_DSP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_STREAM_DSP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_STREAM_DSP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_STREAM_GVSP_INCFG (const char* buffer, TSTREAM_GVSP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal STREAM_GVSP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TSTREAM_GVSP_INCFG_Data (data, ID_STREAM_GVSP_INCFG_STREAM_GVSP_INCFG_ConfigurationRequest);
			INIT_c_STREAM_GVSP_INCFG_ConfigurationRequest (data->Data.fld_c_STREAM_GVSP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_STREAM_GVSP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_STREAM_GVSP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal STREAM_GVSP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TSTREAM_GVSP_INCFG_Data (data, ID_STREAM_GVSP_INCFG_STREAM_GVSP_INCFG_ConfigurationResponse);
			INIT_c_STREAM_GVSP_INCFG_ConfigurationResponse (data->Data.fld_c_STREAM_GVSP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_STREAM_GVSP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_STREAM_GVSP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_STREAM_GVSP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_STREAM_GVSP_INCFG (const char* buffer, int len, TSTREAM_GVSP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_STREAM_GVSP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_STREAM_GVSP_INCFG (char* buffer, ED_EXLONG bitOffset, TSTREAM_GVSP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_STREAM_GVSP_INCFG_STREAM_GVSP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_STREAM_GVSP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_STREAM_GVSP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_STREAM_GVSP_INCFG_STREAM_GVSP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_STREAM_GVSP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_STREAM_GVSP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_SESSION_DSMP_INCFG (const char* buffer, TSESSION_DSMP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal SESSION_DSMP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TSESSION_DSMP_INCFG_Data (data, ID_SESSION_DSMP_INCFG_SESSION_DSMP_INCFG_ConfigurationRequest);
			INIT_c_SESSION_DSMP_INCFG_ConfigurationRequest (data->Data.fld_c_SESSION_DSMP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_SESSION_DSMP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_SESSION_DSMP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SESSION_DSMP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TSESSION_DSMP_INCFG_Data (data, ID_SESSION_DSMP_INCFG_SESSION_DSMP_INCFG_ConfigurationResponse);
			INIT_c_SESSION_DSMP_INCFG_ConfigurationResponse (data->Data.fld_c_SESSION_DSMP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_SESSION_DSMP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_SESSION_DSMP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_SESSION_DSMP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_SESSION_DSMP_INCFG (const char* buffer, int len, TSESSION_DSMP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_SESSION_DSMP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_SESSION_DSMP_INCFG (char* buffer, ED_EXLONG bitOffset, TSESSION_DSMP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_SESSION_DSMP_INCFG_SESSION_DSMP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_SESSION_DSMP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_SESSION_DSMP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_SESSION_DSMP_INCFG_SESSION_DSMP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_SESSION_DSMP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_SESSION_DSMP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_SESSION_DSMP_INUSE (const char* buffer, TSESSION_DSMP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal SESSION_DSMP_INUSE_SessionClose */
		case 0x0001: {
			SETPRESENT_TSESSION_DSMP_INUSE_Data (data, ID_SESSION_DSMP_INUSE_SESSION_DSMP_INUSE_SessionClose);
			INIT_c_SESSION_DSMP_INUSE_SessionClose (data->Data.fld_c_SESSION_DSMP_INUSE_SessionClose);
			retLen = DECODE_c_SESSION_DSMP_INUSE_SessionClose (buffer, 0, data->Data.fld_c_SESSION_DSMP_INUSE_SessionClose, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SESSION_DSMP_INUSE_KeepAliveRequest */
		case 0x0002: {
			SETPRESENT_TSESSION_DSMP_INUSE_Data (data, ID_SESSION_DSMP_INUSE_SESSION_DSMP_INUSE_KeepAliveRequest);
			INIT_c_SESSION_DSMP_INUSE_KeepAliveRequest (data->Data.fld_c_SESSION_DSMP_INUSE_KeepAliveRequest);
			retLen = DECODE_c_SESSION_DSMP_INUSE_KeepAliveRequest (buffer, 0, data->Data.fld_c_SESSION_DSMP_INUSE_KeepAliveRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SESSION_DSMP_INUSE_KeepAliveResponse */
		case 0x0003: {
			SETPRESENT_TSESSION_DSMP_INUSE_Data (data, ID_SESSION_DSMP_INUSE_SESSION_DSMP_INUSE_KeepAliveResponse);
			INIT_c_SESSION_DSMP_INUSE_KeepAliveResponse (data->Data.fld_c_SESSION_DSMP_INUSE_KeepAliveResponse);
			retLen = DECODE_c_SESSION_DSMP_INUSE_KeepAliveResponse (buffer, 0, data->Data.fld_c_SESSION_DSMP_INUSE_KeepAliveResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_SESSION_DSMP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_SESSION_DSMP_INUSE (const char* buffer, int len, TSESSION_DSMP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_SESSION_DSMP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_SESSION_DSMP_INUSE (char* buffer, ED_EXLONG bitOffset, TSESSION_DSMP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_SESSION_DSMP_INUSE_SESSION_DSMP_INUSE_SessionClose: {
			retLen = ENCODE_c_SESSION_DSMP_INUSE_SessionClose (buffer, 0, data->Data.fld_c_SESSION_DSMP_INUSE_SessionClose, pCSN1CContextSet);
			break;
		}
		case ID_SESSION_DSMP_INUSE_SESSION_DSMP_INUSE_KeepAliveRequest: {
			retLen = ENCODE_c_SESSION_DSMP_INUSE_KeepAliveRequest (buffer, 0, data->Data.fld_c_SESSION_DSMP_INUSE_KeepAliveRequest, pCSN1CContextSet);
			break;
		}
		case ID_SESSION_DSMP_INUSE_SESSION_DSMP_INUSE_KeepAliveResponse: {
			retLen = ENCODE_c_SESSION_DSMP_INUSE_KeepAliveResponse (buffer, 0, data->Data.fld_c_SESSION_DSMP_INUSE_KeepAliveResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_SESSION_DAMP_INCFG (const char* buffer, TSESSION_DAMP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal SESSION_DAMP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TSESSION_DAMP_INCFG_Data (data, ID_SESSION_DAMP_INCFG_SESSION_DAMP_INCFG_ConfigurationRequest);
			INIT_c_SESSION_DAMP_INCFG_ConfigurationRequest (data->Data.fld_c_SESSION_DAMP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_SESSION_DAMP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_SESSION_DAMP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SESSION_DAMP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TSESSION_DAMP_INCFG_Data (data, ID_SESSION_DAMP_INCFG_SESSION_DAMP_INCFG_ConfigurationResponse);
			INIT_c_SESSION_DAMP_INCFG_ConfigurationResponse (data->Data.fld_c_SESSION_DAMP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_SESSION_DAMP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_SESSION_DAMP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_SESSION_DAMP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_SESSION_DAMP_INCFG (const char* buffer, int len, TSESSION_DAMP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_SESSION_DAMP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_SESSION_DAMP_INCFG (char* buffer, ED_EXLONG bitOffset, TSESSION_DAMP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_SESSION_DAMP_INCFG_SESSION_DAMP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_SESSION_DAMP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_SESSION_DAMP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_SESSION_DAMP_INCFG_SESSION_DAMP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_SESSION_DAMP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_SESSION_DAMP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_SESSION_DAMP_INUSE (const char* buffer, TSESSION_DAMP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal SESSION_DAMP_INUSE_UATIRequest */
		case 0x0000: {
			SETPRESENT_TSESSION_DAMP_INUSE_Data (data, ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_UATIRequest);
			INIT_c_SESSION_DAMP_INUSE_UATIRequest (data->Data.fld_c_SESSION_DAMP_INUSE_UATIRequest);
			retLen = DECODE_c_SESSION_DAMP_INUSE_UATIRequest (buffer, 0, data->Data.fld_c_SESSION_DAMP_INUSE_UATIRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SESSION_DAMP_INUSE_UATIAssignment */
		case 0x0001: {
			SETPRESENT_TSESSION_DAMP_INUSE_Data (data, ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_UATIAssignment);
			INIT_c_SESSION_DAMP_INUSE_UATIAssignment (data->Data.fld_c_SESSION_DAMP_INUSE_UATIAssignment);
			retLen = DECODE_c_SESSION_DAMP_INUSE_UATIAssignment (buffer, 0, data->Data.fld_c_SESSION_DAMP_INUSE_UATIAssignment, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SESSION_DAMP_INUSE_UATIComplete */
		case 0x0002: {
			SETPRESENT_TSESSION_DAMP_INUSE_Data (data, ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_UATIComplete);
			INIT_c_SESSION_DAMP_INUSE_UATIComplete (data->Data.fld_c_SESSION_DAMP_INUSE_UATIComplete);
			retLen = DECODE_c_SESSION_DAMP_INUSE_UATIComplete (buffer, 0, data->Data.fld_c_SESSION_DAMP_INUSE_UATIComplete, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SESSION_DAMP_INUSE_HardwareIDRequest */
		case 0x0003: {
			SETPRESENT_TSESSION_DAMP_INUSE_Data (data, ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_HardwareIDRequest);
			INIT_c_SESSION_DAMP_INUSE_HardwareIDRequest (data->Data.fld_c_SESSION_DAMP_INUSE_HardwareIDRequest);
			retLen = DECODE_c_SESSION_DAMP_INUSE_HardwareIDRequest (buffer, 0, data->Data.fld_c_SESSION_DAMP_INUSE_HardwareIDRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SESSION_DAMP_INUSE_HardwareIDResponse */
		case 0x0004: {
			SETPRESENT_TSESSION_DAMP_INUSE_Data (data, ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_HardwareIDResponse);
			INIT_c_SESSION_DAMP_INUSE_HardwareIDResponse (data->Data.fld_c_SESSION_DAMP_INUSE_HardwareIDResponse);
			retLen = DECODE_c_SESSION_DAMP_INUSE_HardwareIDResponse (buffer, 0, data->Data.fld_c_SESSION_DAMP_INUSE_HardwareIDResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SESSION_DAMP_INUSE_AttributeUpdateRequest */
		case 0x0052: {
			SETPRESENT_TSESSION_DAMP_INUSE_Data (data, ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_AttributeUpdateRequest);
			INIT_c_SESSION_DAMP_INUSE_AttributeUpdateRequest (data->Data.fld_c_SESSION_DAMP_INUSE_AttributeUpdateRequest);
			retLen = DECODE_c_SESSION_DAMP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_SESSION_DAMP_INUSE_AttributeUpdateRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SESSION_DAMP_INUSE_AttributeUpdateAccept */
		case 0x0053: {
			SETPRESENT_TSESSION_DAMP_INUSE_Data (data, ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_AttributeUpdateAccept);
			INIT_c_SESSION_DAMP_INUSE_AttributeUpdateAccept (data->Data.fld_c_SESSION_DAMP_INUSE_AttributeUpdateAccept);
			retLen = DECODE_c_SESSION_DAMP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_SESSION_DAMP_INUSE_AttributeUpdateAccept, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SESSION_DAMP_INUSE_AttributeUpdateReject */
		case 0x0054: {
			SETPRESENT_TSESSION_DAMP_INUSE_Data (data, ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_AttributeUpdateReject);
			INIT_c_SESSION_DAMP_INUSE_AttributeUpdateReject (data->Data.fld_c_SESSION_DAMP_INUSE_AttributeUpdateReject);
			retLen = DECODE_c_SESSION_DAMP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_SESSION_DAMP_INUSE_AttributeUpdateReject, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_SESSION_DAMP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_SESSION_DAMP_INUSE (const char* buffer, int len, TSESSION_DAMP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_SESSION_DAMP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_SESSION_DAMP_INUSE (char* buffer, ED_EXLONG bitOffset, TSESSION_DAMP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_UATIRequest: {
			retLen = ENCODE_c_SESSION_DAMP_INUSE_UATIRequest (buffer, 0, data->Data.fld_c_SESSION_DAMP_INUSE_UATIRequest, pCSN1CContextSet);
			break;
		}
		case ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_UATIAssignment: {
			retLen = ENCODE_c_SESSION_DAMP_INUSE_UATIAssignment (buffer, 0, data->Data.fld_c_SESSION_DAMP_INUSE_UATIAssignment, pCSN1CContextSet);
			break;
		}
		case ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_UATIComplete: {
			retLen = ENCODE_c_SESSION_DAMP_INUSE_UATIComplete (buffer, 0, data->Data.fld_c_SESSION_DAMP_INUSE_UATIComplete, pCSN1CContextSet);
			break;
		}
		case ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_HardwareIDRequest: {
			retLen = ENCODE_c_SESSION_DAMP_INUSE_HardwareIDRequest (buffer, 0, data->Data.fld_c_SESSION_DAMP_INUSE_HardwareIDRequest, pCSN1CContextSet);
			break;
		}
		case ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_HardwareIDResponse: {
			retLen = ENCODE_c_SESSION_DAMP_INUSE_HardwareIDResponse (buffer, 0, data->Data.fld_c_SESSION_DAMP_INUSE_HardwareIDResponse, pCSN1CContextSet);
			break;
		}
		case ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_AttributeUpdateRequest: {
			retLen = ENCODE_c_SESSION_DAMP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_SESSION_DAMP_INUSE_AttributeUpdateRequest, pCSN1CContextSet);
			break;
		}
		case ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_AttributeUpdateAccept: {
			retLen = ENCODE_c_SESSION_DAMP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_SESSION_DAMP_INUSE_AttributeUpdateAccept, pCSN1CContextSet);
			break;
		}
		case ID_SESSION_DAMP_INUSE_SESSION_DAMP_INUSE_AttributeUpdateReject: {
			retLen = ENCODE_c_SESSION_DAMP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_SESSION_DAMP_INUSE_AttributeUpdateReject, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_SESSION_DSCP_INUSE (const char* buffer, TSESSION_DSCP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal SESSION_DSCP_INUSE_ConfigurationComplete */
		case 0x0000: {
			SETPRESENT_TSESSION_DSCP_INUSE_Data (data, ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_ConfigurationComplete);
			INIT_c_SESSION_DSCP_INUSE_ConfigurationComplete (data->Data.fld_c_SESSION_DSCP_INUSE_ConfigurationComplete);
			retLen = DECODE_c_SESSION_DSCP_INUSE_ConfigurationComplete (buffer, 0, data->Data.fld_c_SESSION_DSCP_INUSE_ConfigurationComplete, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SESSION_DSCP_INUSE_ConfigurationStart */
		case 0x0001: {
			SETPRESENT_TSESSION_DSCP_INUSE_Data (data, ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_ConfigurationStart);
			INIT_c_SESSION_DSCP_INUSE_ConfigurationStart (data->Data.fld_c_SESSION_DSCP_INUSE_ConfigurationStart);
			retLen = DECODE_c_SESSION_DSCP_INUSE_ConfigurationStart (buffer, 0, data->Data.fld_c_SESSION_DSCP_INUSE_ConfigurationStart, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SESSION_DSCP_INUSE_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TSESSION_DSCP_INUSE_Data (data, ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_ConfigurationRequest);
			INIT_c_SESSION_DSCP_INUSE_ConfigurationRequest (data->Data.fld_c_SESSION_DSCP_INUSE_ConfigurationRequest);
			retLen = DECODE_c_SESSION_DSCP_INUSE_ConfigurationRequest (buffer, 0, data->Data.fld_c_SESSION_DSCP_INUSE_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SESSION_DSCP_INUSE_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TSESSION_DSCP_INUSE_Data (data, ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_ConfigurationResponse);
			INIT_c_SESSION_DSCP_INUSE_ConfigurationResponse (data->Data.fld_c_SESSION_DSCP_INUSE_ConfigurationResponse);
			retLen = DECODE_c_SESSION_DSCP_INUSE_ConfigurationResponse (buffer, 0, data->Data.fld_c_SESSION_DSCP_INUSE_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SESSION_DSCP_INUSE_SoftConfigurationComplete */
		case 0x0002: {
			SETPRESENT_TSESSION_DSCP_INUSE_Data (data, ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_SoftConfigurationComplete);
			INIT_c_SESSION_DSCP_INUSE_SoftConfigurationComplete (data->Data.fld_c_SESSION_DSCP_INUSE_SoftConfigurationComplete);
			retLen = DECODE_c_SESSION_DSCP_INUSE_SoftConfigurationComplete (buffer, 0, data->Data.fld_c_SESSION_DSCP_INUSE_SoftConfigurationComplete, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SESSION_DSCP_INUSE_LockConfiguration */
		case 0x0003: {
			SETPRESENT_TSESSION_DSCP_INUSE_Data (data, ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_LockConfiguration);
			INIT_c_SESSION_DSCP_INUSE_LockConfiguration (data->Data.fld_c_SESSION_DSCP_INUSE_LockConfiguration);
			retLen = DECODE_c_SESSION_DSCP_INUSE_LockConfiguration (buffer, 0, data->Data.fld_c_SESSION_DSCP_INUSE_LockConfiguration, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SESSION_DSCP_INUSE_LockConfigurationAck */
		case 0x0004: {
			SETPRESENT_TSESSION_DSCP_INUSE_Data (data, ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_LockConfigurationAck);
			INIT_c_SESSION_DSCP_INUSE_LockConfigurationAck (data->Data.fld_c_SESSION_DSCP_INUSE_LockConfigurationAck);
			retLen = DECODE_c_SESSION_DSCP_INUSE_LockConfigurationAck (buffer, 0, data->Data.fld_c_SESSION_DSCP_INUSE_LockConfigurationAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SESSION_DSCP_INUSE_UnLockConfiguration */
		case 0x0005: {
			SETPRESENT_TSESSION_DSCP_INUSE_Data (data, ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_UnLockConfiguration);
			INIT_c_SESSION_DSCP_INUSE_UnLockConfiguration (data->Data.fld_c_SESSION_DSCP_INUSE_UnLockConfiguration);
			retLen = DECODE_c_SESSION_DSCP_INUSE_UnLockConfiguration (buffer, 0, data->Data.fld_c_SESSION_DSCP_INUSE_UnLockConfiguration, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SESSION_DSCP_INUSE_UnLockConfigurationAck */
		case 0x0006: {
			SETPRESENT_TSESSION_DSCP_INUSE_Data (data, ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_UnLockConfigurationAck);
			INIT_c_SESSION_DSCP_INUSE_UnLockConfigurationAck (data->Data.fld_c_SESSION_DSCP_INUSE_UnLockConfigurationAck);
			retLen = DECODE_c_SESSION_DSCP_INUSE_UnLockConfigurationAck (buffer, 0, data->Data.fld_c_SESSION_DSCP_INUSE_UnLockConfigurationAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SESSION_DSCP_INUSE_DeletePersonality */
		case 0x0007: {
			SETPRESENT_TSESSION_DSCP_INUSE_Data (data, ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_DeletePersonality);
			INIT_c_SESSION_DSCP_INUSE_DeletePersonality (data->Data.fld_c_SESSION_DSCP_INUSE_DeletePersonality);
			retLen = DECODE_c_SESSION_DSCP_INUSE_DeletePersonality (buffer, 0, data->Data.fld_c_SESSION_DSCP_INUSE_DeletePersonality, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SESSION_DSCP_INUSE_DeletePersonalityAck */
		case 0x0008: {
			SETPRESENT_TSESSION_DSCP_INUSE_Data (data, ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_DeletePersonalityAck);
			INIT_c_SESSION_DSCP_INUSE_DeletePersonalityAck (data->Data.fld_c_SESSION_DSCP_INUSE_DeletePersonalityAck);
			retLen = DECODE_c_SESSION_DSCP_INUSE_DeletePersonalityAck (buffer, 0, data->Data.fld_c_SESSION_DSCP_INUSE_DeletePersonalityAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SESSION_DSCP_INUSE_AttributeUpdateRequest */
		case 0x0052: {
			SETPRESENT_TSESSION_DSCP_INUSE_Data (data, ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_AttributeUpdateRequest);
			INIT_c_SESSION_DSCP_INUSE_AttributeUpdateRequest (data->Data.fld_c_SESSION_DSCP_INUSE_AttributeUpdateRequest);
			retLen = DECODE_c_SESSION_DSCP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_SESSION_DSCP_INUSE_AttributeUpdateRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SESSION_DSCP_INUSE_AttributeUpdateAccept */
		case 0x0053: {
			SETPRESENT_TSESSION_DSCP_INUSE_Data (data, ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_AttributeUpdateAccept);
			INIT_c_SESSION_DSCP_INUSE_AttributeUpdateAccept (data->Data.fld_c_SESSION_DSCP_INUSE_AttributeUpdateAccept);
			retLen = DECODE_c_SESSION_DSCP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_SESSION_DSCP_INUSE_AttributeUpdateAccept, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SESSION_DSCP_INUSE_AttributeUpdateReject */
		case 0x0054: {
			SETPRESENT_TSESSION_DSCP_INUSE_Data (data, ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_AttributeUpdateReject);
			INIT_c_SESSION_DSCP_INUSE_AttributeUpdateReject (data->Data.fld_c_SESSION_DSCP_INUSE_AttributeUpdateReject);
			retLen = DECODE_c_SESSION_DSCP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_SESSION_DSCP_INUSE_AttributeUpdateReject, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_SESSION_DSCP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_SESSION_DSCP_INUSE (const char* buffer, int len, TSESSION_DSCP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_SESSION_DSCP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_SESSION_DSCP_INUSE (char* buffer, ED_EXLONG bitOffset, TSESSION_DSCP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_ConfigurationComplete: {
			retLen = ENCODE_c_SESSION_DSCP_INUSE_ConfigurationComplete (buffer, 0, data->Data.fld_c_SESSION_DSCP_INUSE_ConfigurationComplete, pCSN1CContextSet);
			break;
		}
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_ConfigurationStart: {
			retLen = ENCODE_c_SESSION_DSCP_INUSE_ConfigurationStart (buffer, 0, data->Data.fld_c_SESSION_DSCP_INUSE_ConfigurationStart, pCSN1CContextSet);
			break;
		}
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_ConfigurationRequest: {
			retLen = ENCODE_c_SESSION_DSCP_INUSE_ConfigurationRequest (buffer, 0, data->Data.fld_c_SESSION_DSCP_INUSE_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_ConfigurationResponse: {
			retLen = ENCODE_c_SESSION_DSCP_INUSE_ConfigurationResponse (buffer, 0, data->Data.fld_c_SESSION_DSCP_INUSE_ConfigurationResponse, pCSN1CContextSet);
			break;
		}
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_SoftConfigurationComplete: {
			retLen = ENCODE_c_SESSION_DSCP_INUSE_SoftConfigurationComplete (buffer, 0, data->Data.fld_c_SESSION_DSCP_INUSE_SoftConfigurationComplete, pCSN1CContextSet);
			break;
		}
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_LockConfiguration: {
			retLen = ENCODE_c_SESSION_DSCP_INUSE_LockConfiguration (buffer, 0, data->Data.fld_c_SESSION_DSCP_INUSE_LockConfiguration, pCSN1CContextSet);
			break;
		}
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_LockConfigurationAck: {
			retLen = ENCODE_c_SESSION_DSCP_INUSE_LockConfigurationAck (buffer, 0, data->Data.fld_c_SESSION_DSCP_INUSE_LockConfigurationAck, pCSN1CContextSet);
			break;
		}
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_UnLockConfiguration: {
			retLen = ENCODE_c_SESSION_DSCP_INUSE_UnLockConfiguration (buffer, 0, data->Data.fld_c_SESSION_DSCP_INUSE_UnLockConfiguration, pCSN1CContextSet);
			break;
		}
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_UnLockConfigurationAck: {
			retLen = ENCODE_c_SESSION_DSCP_INUSE_UnLockConfigurationAck (buffer, 0, data->Data.fld_c_SESSION_DSCP_INUSE_UnLockConfigurationAck, pCSN1CContextSet);
			break;
		}
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_DeletePersonality: {
			retLen = ENCODE_c_SESSION_DSCP_INUSE_DeletePersonality (buffer, 0, data->Data.fld_c_SESSION_DSCP_INUSE_DeletePersonality, pCSN1CContextSet);
			break;
		}
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_DeletePersonalityAck: {
			retLen = ENCODE_c_SESSION_DSCP_INUSE_DeletePersonalityAck (buffer, 0, data->Data.fld_c_SESSION_DSCP_INUSE_DeletePersonalityAck, pCSN1CContextSet);
			break;
		}
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_AttributeUpdateRequest: {
			retLen = ENCODE_c_SESSION_DSCP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_SESSION_DSCP_INUSE_AttributeUpdateRequest, pCSN1CContextSet);
			break;
		}
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_AttributeUpdateAccept: {
			retLen = ENCODE_c_SESSION_DSCP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_SESSION_DSCP_INUSE_AttributeUpdateAccept, pCSN1CContextSet);
			break;
		}
		case ID_SESSION_DSCP_INUSE_SESSION_DSCP_INUSE_AttributeUpdateReject: {
			retLen = ENCODE_c_SESSION_DSCP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_SESSION_DSCP_INUSE_AttributeUpdateReject, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_SESSION_GMCDP_INCFG (const char* buffer, TSESSION_GMCDP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal SESSION_GMCDP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TSESSION_GMCDP_INCFG_Data (data, ID_SESSION_GMCDP_INCFG_SESSION_GMCDP_INCFG_ConfigurationRequest);
			INIT_c_SESSION_GMCDP_INCFG_ConfigurationRequest (data->Data.fld_c_SESSION_GMCDP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_SESSION_GMCDP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_SESSION_GMCDP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SESSION_GMCDP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TSESSION_GMCDP_INCFG_Data (data, ID_SESSION_GMCDP_INCFG_SESSION_GMCDP_INCFG_ConfigurationResponse);
			INIT_c_SESSION_GMCDP_INCFG_ConfigurationResponse (data->Data.fld_c_SESSION_GMCDP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_SESSION_GMCDP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_SESSION_GMCDP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_SESSION_GMCDP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_SESSION_GMCDP_INCFG (const char* buffer, int len, TSESSION_GMCDP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_SESSION_GMCDP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_SESSION_GMCDP_INCFG (char* buffer, ED_EXLONG bitOffset, TSESSION_GMCDP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_SESSION_GMCDP_INCFG_SESSION_GMCDP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_SESSION_GMCDP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_SESSION_GMCDP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_SESSION_GMCDP_INCFG_SESSION_GMCDP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_SESSION_GMCDP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_SESSION_GMCDP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_CONN_DALMP_INCFG (const char* buffer, TCONN_DALMP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal CONN_DALMP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TCONN_DALMP_INCFG_Data (data, ID_CONN_DALMP_INCFG_CONN_DALMP_INCFG_ConfigurationRequest);
			INIT_c_CONN_DALMP_INCFG_ConfigurationRequest (data->Data.fld_c_CONN_DALMP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_CONN_DALMP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_CONN_DALMP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_DALMP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TCONN_DALMP_INCFG_Data (data, ID_CONN_DALMP_INCFG_CONN_DALMP_INCFG_ConfigurationResponse);
			INIT_c_CONN_DALMP_INCFG_ConfigurationResponse (data->Data.fld_c_CONN_DALMP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_CONN_DALMP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_CONN_DALMP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_CONN_DALMP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_DALMP_INCFG (const char* buffer, int len, TCONN_DALMP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_CONN_DALMP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_CONN_DALMP_INCFG (char* buffer, ED_EXLONG bitOffset, TCONN_DALMP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_CONN_DALMP_INCFG_CONN_DALMP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_CONN_DALMP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_CONN_DALMP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_CONN_DALMP_INCFG_CONN_DALMP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_CONN_DALMP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_CONN_DALMP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_CONN_DALMP_INUSE (const char* buffer, TCONN_DALMP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal CONN_DALMP_INUSE_Redirect */
		case 0x0000: {
			SETPRESENT_TCONN_DALMP_INUSE_Data (data, ID_CONN_DALMP_INUSE_CONN_DALMP_INUSE_Redirect);
			INIT_c_CONN_DALMP_INUSE_Redirect (data->Data.fld_c_CONN_DALMP_INUSE_Redirect);
			retLen = DECODE_c_CONN_DALMP_INUSE_Redirect (buffer, 0, data->Data.fld_c_CONN_DALMP_INUSE_Redirect, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_DALMP_INUSE_ConnectionFailureReport */
		case 0x0001: {
			SETPRESENT_TCONN_DALMP_INUSE_Data (data, ID_CONN_DALMP_INUSE_CONN_DALMP_INUSE_ConnectionFailureReport);
			INIT_c_CONN_DALMP_INUSE_ConnectionFailureReport (data->Data.fld_c_CONN_DALMP_INUSE_ConnectionFailureReport);
			retLen = DECODE_c_CONN_DALMP_INUSE_ConnectionFailureReport (buffer, 0, data->Data.fld_c_CONN_DALMP_INUSE_ConnectionFailureReport, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_DALMP_INUSE_ConnectionFailureReportAck */
		case 0x0002: {
			SETPRESENT_TCONN_DALMP_INUSE_Data (data, ID_CONN_DALMP_INUSE_CONN_DALMP_INUSE_ConnectionFailureReportAck);
			INIT_c_CONN_DALMP_INUSE_ConnectionFailureReportAck (data->Data.fld_c_CONN_DALMP_INUSE_ConnectionFailureReportAck);
			retLen = DECODE_c_CONN_DALMP_INUSE_ConnectionFailureReportAck (buffer, 0, data->Data.fld_c_CONN_DALMP_INUSE_ConnectionFailureReportAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_CONN_DALMP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_DALMP_INUSE (const char* buffer, int len, TCONN_DALMP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_CONN_DALMP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_CONN_DALMP_INUSE (char* buffer, ED_EXLONG bitOffset, TCONN_DALMP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_CONN_DALMP_INUSE_CONN_DALMP_INUSE_Redirect: {
			retLen = ENCODE_c_CONN_DALMP_INUSE_Redirect (buffer, 0, data->Data.fld_c_CONN_DALMP_INUSE_Redirect, pCSN1CContextSet);
			break;
		}
		case ID_CONN_DALMP_INUSE_CONN_DALMP_INUSE_ConnectionFailureReport: {
			retLen = ENCODE_c_CONN_DALMP_INUSE_ConnectionFailureReport (buffer, 0, data->Data.fld_c_CONN_DALMP_INUSE_ConnectionFailureReport, pCSN1CContextSet);
			break;
		}
		case ID_CONN_DALMP_INUSE_CONN_DALMP_INUSE_ConnectionFailureReportAck: {
			retLen = ENCODE_c_CONN_DALMP_INUSE_ConnectionFailureReportAck (buffer, 0, data->Data.fld_c_CONN_DALMP_INUSE_ConnectionFailureReportAck, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_CONN_DINSP_INCFG (const char* buffer, TCONN_DINSP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal CONN_DINSP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TCONN_DINSP_INCFG_Data (data, ID_CONN_DINSP_INCFG_CONN_DINSP_INCFG_ConfigurationRequest);
			INIT_c_CONN_DINSP_INCFG_ConfigurationRequest (data->Data.fld_c_CONN_DINSP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_CONN_DINSP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_CONN_DINSP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_DINSP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TCONN_DINSP_INCFG_Data (data, ID_CONN_DINSP_INCFG_CONN_DINSP_INCFG_ConfigurationResponse);
			INIT_c_CONN_DINSP_INCFG_ConfigurationResponse (data->Data.fld_c_CONN_DINSP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_CONN_DINSP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_CONN_DINSP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_CONN_DINSP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_DINSP_INCFG (const char* buffer, int len, TCONN_DINSP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_CONN_DINSP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_CONN_DINSP_INCFG (char* buffer, ED_EXLONG bitOffset, TCONN_DINSP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_CONN_DINSP_INCFG_CONN_DINSP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_CONN_DINSP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_CONN_DINSP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_CONN_DINSP_INCFG_CONN_DINSP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_CONN_DINSP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_CONN_DINSP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_CONN_DIDSP_INCFG (const char* buffer, TCONN_DIDSP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal CONN_DIDSP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TCONN_DIDSP_INCFG_Data (data, ID_CONN_DIDSP_INCFG_CONN_DIDSP_INCFG_ConfigurationRequest);
			INIT_c_CONN_DIDSP_INCFG_ConfigurationRequest (data->Data.fld_c_CONN_DIDSP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_CONN_DIDSP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_CONN_DIDSP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_DIDSP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TCONN_DIDSP_INCFG_Data (data, ID_CONN_DIDSP_INCFG_CONN_DIDSP_INCFG_ConfigurationResponse);
			INIT_c_CONN_DIDSP_INCFG_ConfigurationResponse (data->Data.fld_c_CONN_DIDSP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_CONN_DIDSP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_CONN_DIDSP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_CONN_DIDSP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_DIDSP_INCFG (const char* buffer, int len, TCONN_DIDSP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_CONN_DIDSP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_CONN_DIDSP_INCFG (char* buffer, ED_EXLONG bitOffset, TCONN_DIDSP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_CONN_DIDSP_INCFG_CONN_DIDSP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_CONN_DIDSP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_CONN_DIDSP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_CONN_DIDSP_INCFG_CONN_DIDSP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_CONN_DIDSP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_CONN_DIDSP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_CONN_DIDSP_INUSE (const char* buffer, TCONN_DIDSP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal CONN_DIDSP_INUSE_Page */
		case 0x0000: {
			SETPRESENT_TCONN_DIDSP_INUSE_Data (data, ID_CONN_DIDSP_INUSE_CONN_DIDSP_INUSE_Page);
			INIT_c_CONN_DIDSP_INUSE_Page (data->Data.fld_c_CONN_DIDSP_INUSE_Page);
			retLen = DECODE_c_CONN_DIDSP_INUSE_Page (buffer, 0, data->Data.fld_c_CONN_DIDSP_INUSE_Page, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_DIDSP_INUSE_ConnectionRequest */
		case 0x0001: {
			SETPRESENT_TCONN_DIDSP_INUSE_Data (data, ID_CONN_DIDSP_INUSE_CONN_DIDSP_INUSE_ConnectionRequest);
			INIT_c_CONN_DIDSP_INUSE_ConnectionRequest (data->Data.fld_c_CONN_DIDSP_INUSE_ConnectionRequest);
			retLen = DECODE_c_CONN_DIDSP_INUSE_ConnectionRequest (buffer, 0, data->Data.fld_c_CONN_DIDSP_INUSE_ConnectionRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_DIDSP_INUSE_ConnectionDeny */
		case 0x0002: {
			SETPRESENT_TCONN_DIDSP_INUSE_Data (data, ID_CONN_DIDSP_INUSE_CONN_DIDSP_INUSE_ConnectionDeny);
			INIT_c_CONN_DIDSP_INUSE_ConnectionDeny (data->Data.fld_c_CONN_DIDSP_INUSE_ConnectionDeny);
			retLen = DECODE_c_CONN_DIDSP_INUSE_ConnectionDeny (buffer, 0, data->Data.fld_c_CONN_DIDSP_INUSE_ConnectionDeny, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_CONN_DIDSP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_DIDSP_INUSE (const char* buffer, int len, TCONN_DIDSP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_CONN_DIDSP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_CONN_DIDSP_INUSE (char* buffer, ED_EXLONG bitOffset, TCONN_DIDSP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_CONN_DIDSP_INUSE_CONN_DIDSP_INUSE_Page: {
			retLen = ENCODE_c_CONN_DIDSP_INUSE_Page (buffer, 0, data->Data.fld_c_CONN_DIDSP_INUSE_Page, pCSN1CContextSet);
			break;
		}
		case ID_CONN_DIDSP_INUSE_CONN_DIDSP_INUSE_ConnectionRequest: {
			retLen = ENCODE_c_CONN_DIDSP_INUSE_ConnectionRequest (buffer, 0, data->Data.fld_c_CONN_DIDSP_INUSE_ConnectionRequest, pCSN1CContextSet);
			break;
		}
		case ID_CONN_DIDSP_INUSE_CONN_DIDSP_INUSE_ConnectionDeny: {
			retLen = ENCODE_c_CONN_DIDSP_INUSE_ConnectionDeny (buffer, 0, data->Data.fld_c_CONN_DIDSP_INUSE_ConnectionDeny, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_CONN_EISP_INCFG (const char* buffer, TCONN_EISP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal CONN_EISP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TCONN_EISP_INCFG_Data (data, ID_CONN_EISP_INCFG_CONN_EISP_INCFG_ConfigurationRequest);
			INIT_c_CONN_EISP_INCFG_ConfigurationRequest (data->Data.fld_c_CONN_EISP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_CONN_EISP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_CONN_EISP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_EISP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TCONN_EISP_INCFG_Data (data, ID_CONN_EISP_INCFG_CONN_EISP_INCFG_ConfigurationResponse);
			INIT_c_CONN_EISP_INCFG_ConfigurationResponse (data->Data.fld_c_CONN_EISP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_CONN_EISP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_CONN_EISP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_CONN_EISP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_EISP_INCFG (const char* buffer, int len, TCONN_EISP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_CONN_EISP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_CONN_EISP_INCFG (char* buffer, ED_EXLONG bitOffset, TCONN_EISP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_CONN_EISP_INCFG_CONN_EISP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_CONN_EISP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_CONN_EISP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_CONN_EISP_INCFG_CONN_EISP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_CONN_EISP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_CONN_EISP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_CONN_EISP_INUSE (const char* buffer, TCONN_EISP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal CONN_EISP_INUSE_Page */
		case 0x0000: {
			SETPRESENT_TCONN_EISP_INUSE_Data (data, ID_CONN_EISP_INUSE_CONN_EISP_INUSE_Page);
			INIT_c_CONN_EISP_INUSE_Page (data->Data.fld_c_CONN_EISP_INUSE_Page);
			retLen = DECODE_c_CONN_EISP_INUSE_Page (buffer, 0, data->Data.fld_c_CONN_EISP_INUSE_Page, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_EISP_INUSE_ConnectionRequest */
		case 0x0001: {
			SETPRESENT_TCONN_EISP_INUSE_Data (data, ID_CONN_EISP_INUSE_CONN_EISP_INUSE_ConnectionRequest);
			INIT_c_CONN_EISP_INUSE_ConnectionRequest (data->Data.fld_c_CONN_EISP_INUSE_ConnectionRequest);
			retLen = DECODE_c_CONN_EISP_INUSE_ConnectionRequest (buffer, 0, data->Data.fld_c_CONN_EISP_INUSE_ConnectionRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_EISP_INUSE_ConnectionDeny */
		case 0x0002: {
			SETPRESENT_TCONN_EISP_INUSE_Data (data, ID_CONN_EISP_INUSE_CONN_EISP_INUSE_ConnectionDeny);
			INIT_c_CONN_EISP_INUSE_ConnectionDeny (data->Data.fld_c_CONN_EISP_INUSE_ConnectionDeny);
			retLen = DECODE_c_CONN_EISP_INUSE_ConnectionDeny (buffer, 0, data->Data.fld_c_CONN_EISP_INUSE_ConnectionDeny, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_EISP_INUSE_AttributeUpdateRequest */
		case 0x0052: {
			SETPRESENT_TCONN_EISP_INUSE_Data (data, ID_CONN_EISP_INUSE_CONN_EISP_INUSE_AttributeUpdateRequest);
			INIT_c_CONN_EISP_INUSE_AttributeUpdateRequest (data->Data.fld_c_CONN_EISP_INUSE_AttributeUpdateRequest);
			retLen = DECODE_c_CONN_EISP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_CONN_EISP_INUSE_AttributeUpdateRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_EISP_INUSE_AttributeUpdateAccept */
		case 0x0053: {
			SETPRESENT_TCONN_EISP_INUSE_Data (data, ID_CONN_EISP_INUSE_CONN_EISP_INUSE_AttributeUpdateAccept);
			INIT_c_CONN_EISP_INUSE_AttributeUpdateAccept (data->Data.fld_c_CONN_EISP_INUSE_AttributeUpdateAccept);
			retLen = DECODE_c_CONN_EISP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_CONN_EISP_INUSE_AttributeUpdateAccept, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_EISP_INUSE_AttributeUpdateReject */
		case 0x0054: {
			SETPRESENT_TCONN_EISP_INUSE_Data (data, ID_CONN_EISP_INUSE_CONN_EISP_INUSE_AttributeUpdateReject);
			INIT_c_CONN_EISP_INUSE_AttributeUpdateReject (data->Data.fld_c_CONN_EISP_INUSE_AttributeUpdateReject);
			retLen = DECODE_c_CONN_EISP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_CONN_EISP_INUSE_AttributeUpdateReject, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_CONN_EISP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_EISP_INUSE (const char* buffer, int len, TCONN_EISP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_CONN_EISP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_CONN_EISP_INUSE (char* buffer, ED_EXLONG bitOffset, TCONN_EISP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_CONN_EISP_INUSE_CONN_EISP_INUSE_Page: {
			retLen = ENCODE_c_CONN_EISP_INUSE_Page (buffer, 0, data->Data.fld_c_CONN_EISP_INUSE_Page, pCSN1CContextSet);
			break;
		}
		case ID_CONN_EISP_INUSE_CONN_EISP_INUSE_ConnectionRequest: {
			retLen = ENCODE_c_CONN_EISP_INUSE_ConnectionRequest (buffer, 0, data->Data.fld_c_CONN_EISP_INUSE_ConnectionRequest, pCSN1CContextSet);
			break;
		}
		case ID_CONN_EISP_INUSE_CONN_EISP_INUSE_ConnectionDeny: {
			retLen = ENCODE_c_CONN_EISP_INUSE_ConnectionDeny (buffer, 0, data->Data.fld_c_CONN_EISP_INUSE_ConnectionDeny, pCSN1CContextSet);
			break;
		}
		case ID_CONN_EISP_INUSE_CONN_EISP_INUSE_AttributeUpdateRequest: {
			retLen = ENCODE_c_CONN_EISP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_CONN_EISP_INUSE_AttributeUpdateRequest, pCSN1CContextSet);
			break;
		}
		case ID_CONN_EISP_INUSE_CONN_EISP_INUSE_AttributeUpdateAccept: {
			retLen = ENCODE_c_CONN_EISP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_CONN_EISP_INUSE_AttributeUpdateAccept, pCSN1CContextSet);
			break;
		}
		case ID_CONN_EISP_INUSE_CONN_EISP_INUSE_AttributeUpdateReject: {
			retLen = ENCODE_c_CONN_EISP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_CONN_EISP_INUSE_AttributeUpdateReject, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_CONN_QISP_INCFG (const char* buffer, TCONN_QISP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal CONN_QISP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TCONN_QISP_INCFG_Data (data, ID_CONN_QISP_INCFG_CONN_QISP_INCFG_ConfigurationRequest);
			INIT_c_CONN_QISP_INCFG_ConfigurationRequest (data->Data.fld_c_CONN_QISP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_CONN_QISP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_CONN_QISP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_QISP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TCONN_QISP_INCFG_Data (data, ID_CONN_QISP_INCFG_CONN_QISP_INCFG_ConfigurationResponse);
			INIT_c_CONN_QISP_INCFG_ConfigurationResponse (data->Data.fld_c_CONN_QISP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_CONN_QISP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_CONN_QISP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_CONN_QISP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_QISP_INCFG (const char* buffer, int len, TCONN_QISP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_CONN_QISP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_CONN_QISP_INCFG (char* buffer, ED_EXLONG bitOffset, TCONN_QISP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_CONN_QISP_INCFG_CONN_QISP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_CONN_QISP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_CONN_QISP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_CONN_QISP_INCFG_CONN_QISP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_CONN_QISP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_CONN_QISP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_CONN_QISP_INUSE (const char* buffer, TCONN_QISP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal CONN_QISP_INUSE_Page */
		case 0x0000: {
			SETPRESENT_TCONN_QISP_INUSE_Data (data, ID_CONN_QISP_INUSE_CONN_QISP_INUSE_Page);
			INIT_c_CONN_QISP_INUSE_Page (data->Data.fld_c_CONN_QISP_INUSE_Page);
			retLen = DECODE_c_CONN_QISP_INUSE_Page (buffer, 0, data->Data.fld_c_CONN_QISP_INUSE_Page, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_QISP_INUSE_ConnectionRequest */
		case 0x0001: {
			SETPRESENT_TCONN_QISP_INUSE_Data (data, ID_CONN_QISP_INUSE_CONN_QISP_INUSE_ConnectionRequest);
			INIT_c_CONN_QISP_INUSE_ConnectionRequest (data->Data.fld_c_CONN_QISP_INUSE_ConnectionRequest);
			retLen = DECODE_c_CONN_QISP_INUSE_ConnectionRequest (buffer, 0, data->Data.fld_c_CONN_QISP_INUSE_ConnectionRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_QISP_INUSE_ConnectionDeny */
		case 0x0002: {
			SETPRESENT_TCONN_QISP_INUSE_Data (data, ID_CONN_QISP_INUSE_CONN_QISP_INUSE_ConnectionDeny);
			INIT_c_CONN_QISP_INUSE_ConnectionDeny (data->Data.fld_c_CONN_QISP_INUSE_ConnectionDeny);
			retLen = DECODE_c_CONN_QISP_INUSE_ConnectionDeny (buffer, 0, data->Data.fld_c_CONN_QISP_INUSE_ConnectionDeny, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_QISP_INUSE_QuickPage */
		case 0x0003: {
			SETPRESENT_TCONN_QISP_INUSE_Data (data, ID_CONN_QISP_INUSE_CONN_QISP_INUSE_QuickPage);
			INIT_c_CONN_QISP_INUSE_QuickPage (data->Data.fld_c_CONN_QISP_INUSE_QuickPage);
			retLen = DECODE_c_CONN_QISP_INUSE_QuickPage (buffer, 0, data->Data.fld_c_CONN_QISP_INUSE_QuickPage, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_QISP_INUSE_AttributeUpdateRequest */
		case 0x0052: {
			SETPRESENT_TCONN_QISP_INUSE_Data (data, ID_CONN_QISP_INUSE_CONN_QISP_INUSE_AttributeUpdateRequest);
			INIT_c_CONN_QISP_INUSE_AttributeUpdateRequest (data->Data.fld_c_CONN_QISP_INUSE_AttributeUpdateRequest);
			retLen = DECODE_c_CONN_QISP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_CONN_QISP_INUSE_AttributeUpdateRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_QISP_INUSE_AttributeUpdateAccept */
		case 0x0053: {
			SETPRESENT_TCONN_QISP_INUSE_Data (data, ID_CONN_QISP_INUSE_CONN_QISP_INUSE_AttributeUpdateAccept);
			INIT_c_CONN_QISP_INUSE_AttributeUpdateAccept (data->Data.fld_c_CONN_QISP_INUSE_AttributeUpdateAccept);
			retLen = DECODE_c_CONN_QISP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_CONN_QISP_INUSE_AttributeUpdateAccept, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_QISP_INUSE_AttributeUpdateReject */
		case 0x0054: {
			SETPRESENT_TCONN_QISP_INUSE_Data (data, ID_CONN_QISP_INUSE_CONN_QISP_INUSE_AttributeUpdateReject);
			INIT_c_CONN_QISP_INUSE_AttributeUpdateReject (data->Data.fld_c_CONN_QISP_INUSE_AttributeUpdateReject);
			retLen = DECODE_c_CONN_QISP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_CONN_QISP_INUSE_AttributeUpdateReject, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_CONN_QISP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_QISP_INUSE (const char* buffer, int len, TCONN_QISP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_CONN_QISP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_CONN_QISP_INUSE (char* buffer, ED_EXLONG bitOffset, TCONN_QISP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_CONN_QISP_INUSE_CONN_QISP_INUSE_Page: {
			retLen = ENCODE_c_CONN_QISP_INUSE_Page (buffer, 0, data->Data.fld_c_CONN_QISP_INUSE_Page, pCSN1CContextSet);
			break;
		}
		case ID_CONN_QISP_INUSE_CONN_QISP_INUSE_ConnectionRequest: {
			retLen = ENCODE_c_CONN_QISP_INUSE_ConnectionRequest (buffer, 0, data->Data.fld_c_CONN_QISP_INUSE_ConnectionRequest, pCSN1CContextSet);
			break;
		}
		case ID_CONN_QISP_INUSE_CONN_QISP_INUSE_ConnectionDeny: {
			retLen = ENCODE_c_CONN_QISP_INUSE_ConnectionDeny (buffer, 0, data->Data.fld_c_CONN_QISP_INUSE_ConnectionDeny, pCSN1CContextSet);
			break;
		}
		case ID_CONN_QISP_INUSE_CONN_QISP_INUSE_QuickPage: {
			retLen = ENCODE_c_CONN_QISP_INUSE_QuickPage (buffer, 0, data->Data.fld_c_CONN_QISP_INUSE_QuickPage, pCSN1CContextSet);
			break;
		}
		case ID_CONN_QISP_INUSE_CONN_QISP_INUSE_AttributeUpdateRequest: {
			retLen = ENCODE_c_CONN_QISP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_CONN_QISP_INUSE_AttributeUpdateRequest, pCSN1CContextSet);
			break;
		}
		case ID_CONN_QISP_INUSE_CONN_QISP_INUSE_AttributeUpdateAccept: {
			retLen = ENCODE_c_CONN_QISP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_CONN_QISP_INUSE_AttributeUpdateAccept, pCSN1CContextSet);
			break;
		}
		case ID_CONN_QISP_INUSE_CONN_QISP_INUSE_AttributeUpdateReject: {
			retLen = ENCODE_c_CONN_QISP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_CONN_QISP_INUSE_AttributeUpdateReject, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_CONN_DCSP_INCFG (const char* buffer, TCONN_DCSP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal CONN_DCSP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TCONN_DCSP_INCFG_Data (data, ID_CONN_DCSP_INCFG_CONN_DCSP_INCFG_ConfigurationRequest);
			INIT_c_CONN_DCSP_INCFG_ConfigurationRequest (data->Data.fld_c_CONN_DCSP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_CONN_DCSP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_CONN_DCSP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_DCSP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TCONN_DCSP_INCFG_Data (data, ID_CONN_DCSP_INCFG_CONN_DCSP_INCFG_ConfigurationResponse);
			INIT_c_CONN_DCSP_INCFG_ConfigurationResponse (data->Data.fld_c_CONN_DCSP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_CONN_DCSP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_CONN_DCSP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_CONN_DCSP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_DCSP_INCFG (const char* buffer, int len, TCONN_DCSP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_CONN_DCSP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_CONN_DCSP_INCFG (char* buffer, ED_EXLONG bitOffset, TCONN_DCSP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_CONN_DCSP_INCFG_CONN_DCSP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_CONN_DCSP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_CONN_DCSP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_CONN_DCSP_INCFG_CONN_DCSP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_CONN_DCSP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_CONN_DCSP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_CONN_DCSP_INUSE (const char* buffer, TCONN_DCSP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal CONN_DCSP_INUSE_ConnectionClose */
		case 0x0000: {
			SETPRESENT_TCONN_DCSP_INUSE_Data (data, ID_CONN_DCSP_INUSE_CONN_DCSP_INUSE_ConnectionClose);
			INIT_c_CONN_DCSP_INUSE_ConnectionClose (data->Data.fld_c_CONN_DCSP_INUSE_ConnectionClose);
			retLen = DECODE_c_CONN_DCSP_INUSE_ConnectionClose (buffer, 0, data->Data.fld_c_CONN_DCSP_INUSE_ConnectionClose, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_CONN_DCSP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_DCSP_INUSE (const char* buffer, int len, TCONN_DCSP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_CONN_DCSP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_CONN_DCSP_INUSE (char* buffer, ED_EXLONG bitOffset, TCONN_DCSP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_CONN_DCSP_INUSE_CONN_DCSP_INUSE_ConnectionClose: {
			retLen = ENCODE_c_CONN_DCSP_INUSE_ConnectionClose (buffer, 0, data->Data.fld_c_CONN_DCSP_INUSE_ConnectionClose, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_CONN_DRUP_INCFG (const char* buffer, TCONN_DRUP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal CONN_DRUP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TCONN_DRUP_INCFG_Data (data, ID_CONN_DRUP_INCFG_CONN_DRUP_INCFG_ConfigurationRequest);
			INIT_c_CONN_DRUP_INCFG_ConfigurationRequest (data->Data.fld_c_CONN_DRUP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_CONN_DRUP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_CONN_DRUP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_DRUP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TCONN_DRUP_INCFG_Data (data, ID_CONN_DRUP_INCFG_CONN_DRUP_INCFG_ConfigurationResponse);
			INIT_c_CONN_DRUP_INCFG_ConfigurationResponse (data->Data.fld_c_CONN_DRUP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_CONN_DRUP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_CONN_DRUP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_CONN_DRUP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_DRUP_INCFG (const char* buffer, int len, TCONN_DRUP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_CONN_DRUP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_CONN_DRUP_INCFG (char* buffer, ED_EXLONG bitOffset, TCONN_DRUP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_CONN_DRUP_INCFG_CONN_DRUP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_CONN_DRUP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_CONN_DRUP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_CONN_DRUP_INCFG_CONN_DRUP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_CONN_DRUP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_CONN_DRUP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_CONN_DRUP_INUSE (const char* buffer, TCONN_DRUP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal CONN_DRUP_INUSE_RouteUpdate */
		case 0x0000: {
			SETPRESENT_TCONN_DRUP_INUSE_Data (data, ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_RouteUpdate);
			INIT_c_CONN_DRUP_INUSE_RouteUpdate (data->Data.fld_c_CONN_DRUP_INUSE_RouteUpdate);
			retLen = DECODE_c_CONN_DRUP_INUSE_RouteUpdate (buffer, 0, data->Data.fld_c_CONN_DRUP_INUSE_RouteUpdate, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_DRUP_INUSE_TrafficChannelAssignment */
		case 0x0001: {
			SETPRESENT_TCONN_DRUP_INUSE_Data (data, ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_TrafficChannelAssignment);
			INIT_c_CONN_DRUP_INUSE_TrafficChannelAssignment (data->Data.fld_c_CONN_DRUP_INUSE_TrafficChannelAssignment);
			retLen = DECODE_c_CONN_DRUP_INUSE_TrafficChannelAssignment (buffer, 0, data->Data.fld_c_CONN_DRUP_INUSE_TrafficChannelAssignment, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_DRUP_INUSE_TrafficChannelComplete */
		case 0x0002: {
			SETPRESENT_TCONN_DRUP_INUSE_Data (data, ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_TrafficChannelComplete);
			INIT_c_CONN_DRUP_INUSE_TrafficChannelComplete (data->Data.fld_c_CONN_DRUP_INUSE_TrafficChannelComplete);
			retLen = DECODE_c_CONN_DRUP_INUSE_TrafficChannelComplete (buffer, 0, data->Data.fld_c_CONN_DRUP_INUSE_TrafficChannelComplete, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_DRUP_INUSE_ResetReport */
		case 0x0003: {
			SETPRESENT_TCONN_DRUP_INUSE_Data (data, ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_ResetReport);
			INIT_c_CONN_DRUP_INUSE_ResetReport (data->Data.fld_c_CONN_DRUP_INUSE_ResetReport);
			retLen = DECODE_c_CONN_DRUP_INUSE_ResetReport (buffer, 0, data->Data.fld_c_CONN_DRUP_INUSE_ResetReport, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_DRUP_INUSE_NeighborList */
		case 0x0004: {
			SETPRESENT_TCONN_DRUP_INUSE_Data (data, ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_NeighborList);
			INIT_c_CONN_DRUP_INUSE_NeighborList (data->Data.fld_c_CONN_DRUP_INUSE_NeighborList);
			retLen = DECODE_c_CONN_DRUP_INUSE_NeighborList (buffer, 0, data->Data.fld_c_CONN_DRUP_INUSE_NeighborList, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_DRUP_INUSE_AttributeOverride */
		case 0x0005: {
			SETPRESENT_TCONN_DRUP_INUSE_Data (data, ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_AttributeOverride);
			INIT_c_CONN_DRUP_INUSE_AttributeOverride (data->Data.fld_c_CONN_DRUP_INUSE_AttributeOverride);
			retLen = DECODE_c_CONN_DRUP_INUSE_AttributeOverride (buffer, 0, data->Data.fld_c_CONN_DRUP_INUSE_AttributeOverride, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_DRUP_INUSE_AttributeOverrideResponse */
		case 0x0006: {
			SETPRESENT_TCONN_DRUP_INUSE_Data (data, ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_AttributeOverrideResponse);
			INIT_c_CONN_DRUP_INUSE_AttributeOverrideResponse (data->Data.fld_c_CONN_DRUP_INUSE_AttributeOverrideResponse);
			retLen = DECODE_c_CONN_DRUP_INUSE_AttributeOverrideResponse (buffer, 0, data->Data.fld_c_CONN_DRUP_INUSE_AttributeOverrideResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_DRUP_INUSE_RouteUpdateRequest */
		case 0x0007: {
			SETPRESENT_TCONN_DRUP_INUSE_Data (data, ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_RouteUpdateRequest);
			INIT_c_CONN_DRUP_INUSE_RouteUpdateRequest (data->Data.fld_c_CONN_DRUP_INUSE_RouteUpdateRequest);
			retLen = DECODE_c_CONN_DRUP_INUSE_RouteUpdateRequest (buffer, 0, data->Data.fld_c_CONN_DRUP_INUSE_RouteUpdateRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_DRUP_INUSE_AttributeUpdateRequest */
		case 0x0052: {
			SETPRESENT_TCONN_DRUP_INUSE_Data (data, ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_AttributeUpdateRequest);
			INIT_c_CONN_DRUP_INUSE_AttributeUpdateRequest (data->Data.fld_c_CONN_DRUP_INUSE_AttributeUpdateRequest);
			retLen = DECODE_c_CONN_DRUP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_CONN_DRUP_INUSE_AttributeUpdateRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_DRUP_INUSE_AttributeUpdateAccept */
		case 0x0053: {
			SETPRESENT_TCONN_DRUP_INUSE_Data (data, ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_AttributeUpdateAccept);
			INIT_c_CONN_DRUP_INUSE_AttributeUpdateAccept (data->Data.fld_c_CONN_DRUP_INUSE_AttributeUpdateAccept);
			retLen = DECODE_c_CONN_DRUP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_CONN_DRUP_INUSE_AttributeUpdateAccept, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_DRUP_INUSE_AttributeUpdateReject */
		case 0x0054: {
			SETPRESENT_TCONN_DRUP_INUSE_Data (data, ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_AttributeUpdateReject);
			INIT_c_CONN_DRUP_INUSE_AttributeUpdateReject (data->Data.fld_c_CONN_DRUP_INUSE_AttributeUpdateReject);
			retLen = DECODE_c_CONN_DRUP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_CONN_DRUP_INUSE_AttributeUpdateReject, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_CONN_DRUP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_DRUP_INUSE (const char* buffer, int len, TCONN_DRUP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_CONN_DRUP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_CONN_DRUP_INUSE (char* buffer, ED_EXLONG bitOffset, TCONN_DRUP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_RouteUpdate: {
			retLen = ENCODE_c_CONN_DRUP_INUSE_RouteUpdate (buffer, 0, data->Data.fld_c_CONN_DRUP_INUSE_RouteUpdate, pCSN1CContextSet);
			break;
		}
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_TrafficChannelAssignment: {
			retLen = ENCODE_c_CONN_DRUP_INUSE_TrafficChannelAssignment (buffer, 0, data->Data.fld_c_CONN_DRUP_INUSE_TrafficChannelAssignment, pCSN1CContextSet);
			break;
		}
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_TrafficChannelComplete: {
			retLen = ENCODE_c_CONN_DRUP_INUSE_TrafficChannelComplete (buffer, 0, data->Data.fld_c_CONN_DRUP_INUSE_TrafficChannelComplete, pCSN1CContextSet);
			break;
		}
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_ResetReport: {
			retLen = ENCODE_c_CONN_DRUP_INUSE_ResetReport (buffer, 0, data->Data.fld_c_CONN_DRUP_INUSE_ResetReport, pCSN1CContextSet);
			break;
		}
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_NeighborList: {
			retLen = ENCODE_c_CONN_DRUP_INUSE_NeighborList (buffer, 0, data->Data.fld_c_CONN_DRUP_INUSE_NeighborList, pCSN1CContextSet);
			break;
		}
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_AttributeOverride: {
			retLen = ENCODE_c_CONN_DRUP_INUSE_AttributeOverride (buffer, 0, data->Data.fld_c_CONN_DRUP_INUSE_AttributeOverride, pCSN1CContextSet);
			break;
		}
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_AttributeOverrideResponse: {
			retLen = ENCODE_c_CONN_DRUP_INUSE_AttributeOverrideResponse (buffer, 0, data->Data.fld_c_CONN_DRUP_INUSE_AttributeOverrideResponse, pCSN1CContextSet);
			break;
		}
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_RouteUpdateRequest: {
			retLen = ENCODE_c_CONN_DRUP_INUSE_RouteUpdateRequest (buffer, 0, data->Data.fld_c_CONN_DRUP_INUSE_RouteUpdateRequest, pCSN1CContextSet);
			break;
		}
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_AttributeUpdateRequest: {
			retLen = ENCODE_c_CONN_DRUP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_CONN_DRUP_INUSE_AttributeUpdateRequest, pCSN1CContextSet);
			break;
		}
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_AttributeUpdateAccept: {
			retLen = ENCODE_c_CONN_DRUP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_CONN_DRUP_INUSE_AttributeUpdateAccept, pCSN1CContextSet);
			break;
		}
		case ID_CONN_DRUP_INUSE_CONN_DRUP_INUSE_AttributeUpdateReject: {
			retLen = ENCODE_c_CONN_DRUP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_CONN_DRUP_INUSE_AttributeUpdateReject, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_CONN_MRUP_INCFG (const char* buffer, TCONN_MRUP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal CONN_MRUP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TCONN_MRUP_INCFG_Data (data, ID_CONN_MRUP_INCFG_CONN_MRUP_INCFG_ConfigurationRequest);
			INIT_c_CONN_MRUP_INCFG_ConfigurationRequest (data->Data.fld_c_CONN_MRUP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_CONN_MRUP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_CONN_MRUP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_MRUP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TCONN_MRUP_INCFG_Data (data, ID_CONN_MRUP_INCFG_CONN_MRUP_INCFG_ConfigurationResponse);
			INIT_c_CONN_MRUP_INCFG_ConfigurationResponse (data->Data.fld_c_CONN_MRUP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_CONN_MRUP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_CONN_MRUP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_CONN_MRUP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_MRUP_INCFG (const char* buffer, int len, TCONN_MRUP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_CONN_MRUP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_CONN_MRUP_INCFG (char* buffer, ED_EXLONG bitOffset, TCONN_MRUP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_CONN_MRUP_INCFG_CONN_MRUP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_CONN_MRUP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_CONN_MRUP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_CONN_MRUP_INCFG_CONN_MRUP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_CONN_MRUP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_CONN_MRUP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_CONN_MRUP_INUSE (const char* buffer, TCONN_MRUP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal CONN_MRUP_INUSE_RouteUpdate */
		case 0x0000: {
			SETPRESENT_TCONN_MRUP_INUSE_Data (data, ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_RouteUpdate);
			INIT_c_CONN_MRUP_INUSE_RouteUpdate (data->Data.fld_c_CONN_MRUP_INUSE_RouteUpdate);
			retLen = DECODE_c_CONN_MRUP_INUSE_RouteUpdate (buffer, 0, data->Data.fld_c_CONN_MRUP_INUSE_RouteUpdate, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_MRUP_INUSE_TrafficChannelAssignment */
		case 0x0001: {
			SETPRESENT_TCONN_MRUP_INUSE_Data (data, ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_TrafficChannelAssignment);
			INIT_c_CONN_MRUP_INUSE_TrafficChannelAssignment (data->Data.fld_c_CONN_MRUP_INUSE_TrafficChannelAssignment);
			retLen = DECODE_c_CONN_MRUP_INUSE_TrafficChannelAssignment (buffer, 0, data->Data.fld_c_CONN_MRUP_INUSE_TrafficChannelAssignment, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_MRUP_INUSE_TrafficChannelComplete */
		case 0x0002: {
			SETPRESENT_TCONN_MRUP_INUSE_Data (data, ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_TrafficChannelComplete);
			INIT_c_CONN_MRUP_INUSE_TrafficChannelComplete (data->Data.fld_c_CONN_MRUP_INUSE_TrafficChannelComplete);
			retLen = DECODE_c_CONN_MRUP_INUSE_TrafficChannelComplete (buffer, 0, data->Data.fld_c_CONN_MRUP_INUSE_TrafficChannelComplete, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_MRUP_INUSE_ResetReport */
		case 0x0003: {
			SETPRESENT_TCONN_MRUP_INUSE_Data (data, ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_ResetReport);
			INIT_c_CONN_MRUP_INUSE_ResetReport (data->Data.fld_c_CONN_MRUP_INUSE_ResetReport);
			retLen = DECODE_c_CONN_MRUP_INUSE_ResetReport (buffer, 0, data->Data.fld_c_CONN_MRUP_INUSE_ResetReport, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_MRUP_INUSE_NeighborList */
		case 0x0004: {
			SETPRESENT_TCONN_MRUP_INUSE_Data (data, ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_NeighborList);
			INIT_c_CONN_MRUP_INUSE_NeighborList (data->Data.fld_c_CONN_MRUP_INUSE_NeighborList);
			retLen = DECODE_c_CONN_MRUP_INUSE_NeighborList (buffer, 0, data->Data.fld_c_CONN_MRUP_INUSE_NeighborList, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_MRUP_INUSE_RouteUpdateRequest */
		case 0x0007: {
			SETPRESENT_TCONN_MRUP_INUSE_Data (data, ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_RouteUpdateRequest);
			INIT_c_CONN_MRUP_INUSE_RouteUpdateRequest (data->Data.fld_c_CONN_MRUP_INUSE_RouteUpdateRequest);
			retLen = DECODE_c_CONN_MRUP_INUSE_RouteUpdateRequest (buffer, 0, data->Data.fld_c_CONN_MRUP_INUSE_RouteUpdateRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_MRUP_INUSE_AttributeUpdateRequest */
		case 0x0052: {
			SETPRESENT_TCONN_MRUP_INUSE_Data (data, ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_AttributeUpdateRequest);
			INIT_c_CONN_MRUP_INUSE_AttributeUpdateRequest (data->Data.fld_c_CONN_MRUP_INUSE_AttributeUpdateRequest);
			retLen = DECODE_c_CONN_MRUP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_CONN_MRUP_INUSE_AttributeUpdateRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_MRUP_INUSE_AttributeUpdateAccept */
		case 0x0053: {
			SETPRESENT_TCONN_MRUP_INUSE_Data (data, ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_AttributeUpdateAccept);
			INIT_c_CONN_MRUP_INUSE_AttributeUpdateAccept (data->Data.fld_c_CONN_MRUP_INUSE_AttributeUpdateAccept);
			retLen = DECODE_c_CONN_MRUP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_CONN_MRUP_INUSE_AttributeUpdateAccept, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_MRUP_INUSE_AttributeUpdateReject */
		case 0x0054: {
			SETPRESENT_TCONN_MRUP_INUSE_Data (data, ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_AttributeUpdateReject);
			INIT_c_CONN_MRUP_INUSE_AttributeUpdateReject (data->Data.fld_c_CONN_MRUP_INUSE_AttributeUpdateReject);
			retLen = DECODE_c_CONN_MRUP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_CONN_MRUP_INUSE_AttributeUpdateReject, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_CONN_MRUP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_MRUP_INUSE (const char* buffer, int len, TCONN_MRUP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_CONN_MRUP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_CONN_MRUP_INUSE (char* buffer, ED_EXLONG bitOffset, TCONN_MRUP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_RouteUpdate: {
			retLen = ENCODE_c_CONN_MRUP_INUSE_RouteUpdate (buffer, 0, data->Data.fld_c_CONN_MRUP_INUSE_RouteUpdate, pCSN1CContextSet);
			break;
		}
		case ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_TrafficChannelAssignment: {
			retLen = ENCODE_c_CONN_MRUP_INUSE_TrafficChannelAssignment (buffer, 0, data->Data.fld_c_CONN_MRUP_INUSE_TrafficChannelAssignment, pCSN1CContextSet);
			break;
		}
		case ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_TrafficChannelComplete: {
			retLen = ENCODE_c_CONN_MRUP_INUSE_TrafficChannelComplete (buffer, 0, data->Data.fld_c_CONN_MRUP_INUSE_TrafficChannelComplete, pCSN1CContextSet);
			break;
		}
		case ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_ResetReport: {
			retLen = ENCODE_c_CONN_MRUP_INUSE_ResetReport (buffer, 0, data->Data.fld_c_CONN_MRUP_INUSE_ResetReport, pCSN1CContextSet);
			break;
		}
		case ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_NeighborList: {
			retLen = ENCODE_c_CONN_MRUP_INUSE_NeighborList (buffer, 0, data->Data.fld_c_CONN_MRUP_INUSE_NeighborList, pCSN1CContextSet);
			break;
		}
		case ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_RouteUpdateRequest: {
			retLen = ENCODE_c_CONN_MRUP_INUSE_RouteUpdateRequest (buffer, 0, data->Data.fld_c_CONN_MRUP_INUSE_RouteUpdateRequest, pCSN1CContextSet);
			break;
		}
		case ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_AttributeUpdateRequest: {
			retLen = ENCODE_c_CONN_MRUP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_CONN_MRUP_INUSE_AttributeUpdateRequest, pCSN1CContextSet);
			break;
		}
		case ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_AttributeUpdateAccept: {
			retLen = ENCODE_c_CONN_MRUP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_CONN_MRUP_INUSE_AttributeUpdateAccept, pCSN1CContextSet);
			break;
		}
		case ID_CONN_MRUP_INUSE_CONN_MRUP_INUSE_AttributeUpdateReject: {
			retLen = ENCODE_c_CONN_MRUP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_CONN_MRUP_INUSE_AttributeUpdateReject, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_CONN_DPCP_INCFG (const char* buffer, TCONN_DPCP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal CONN_DPCP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TCONN_DPCP_INCFG_Data (data, ID_CONN_DPCP_INCFG_CONN_DPCP_INCFG_ConfigurationRequest);
			INIT_c_CONN_DPCP_INCFG_ConfigurationRequest (data->Data.fld_c_CONN_DPCP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_CONN_DPCP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_CONN_DPCP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_DPCP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TCONN_DPCP_INCFG_Data (data, ID_CONN_DPCP_INCFG_CONN_DPCP_INCFG_ConfigurationResponse);
			INIT_c_CONN_DPCP_INCFG_ConfigurationResponse (data->Data.fld_c_CONN_DPCP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_CONN_DPCP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_CONN_DPCP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_CONN_DPCP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_DPCP_INCFG (const char* buffer, int len, TCONN_DPCP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_CONN_DPCP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_CONN_DPCP_INCFG (char* buffer, ED_EXLONG bitOffset, TCONN_DPCP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_CONN_DPCP_INCFG_CONN_DPCP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_CONN_DPCP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_CONN_DPCP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_CONN_DPCP_INCFG_CONN_DPCP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_CONN_DPCP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_CONN_DPCP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_CONN_OMP_INCFG (const char* buffer, TCONN_OMP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal CONN_OMP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TCONN_OMP_INCFG_Data (data, ID_CONN_OMP_INCFG_CONN_OMP_INCFG_ConfigurationRequest);
			INIT_c_CONN_OMP_INCFG_ConfigurationRequest (data->Data.fld_c_CONN_OMP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_CONN_OMP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_CONN_OMP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_OMP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TCONN_OMP_INCFG_Data (data, ID_CONN_OMP_INCFG_CONN_OMP_INCFG_ConfigurationResponse);
			INIT_c_CONN_OMP_INCFG_ConfigurationResponse (data->Data.fld_c_CONN_OMP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_CONN_OMP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_CONN_OMP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_CONN_OMP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_OMP_INCFG (const char* buffer, int len, TCONN_OMP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_CONN_OMP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_CONN_OMP_INCFG (char* buffer, ED_EXLONG bitOffset, TCONN_OMP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_CONN_OMP_INCFG_CONN_OMP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_CONN_OMP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_CONN_OMP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_CONN_OMP_INCFG_CONN_OMP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_CONN_OMP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_CONN_OMP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_CONN_OMP_INUSE (const char* buffer, TCONN_OMP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal CONN_OMP_INUSE_QuickConfig */
		case 0x0000: {
			SETPRESENT_TCONN_OMP_INUSE_Data (data, ID_CONN_OMP_INUSE_CONN_OMP_INUSE_QuickConfig);
			INIT_c_CONN_OMP_INUSE_QuickConfig (data->Data.fld_c_CONN_OMP_INUSE_QuickConfig);
			retLen = DECODE_c_CONN_OMP_INUSE_QuickConfig (buffer, 0, data->Data.fld_c_CONN_OMP_INUSE_QuickConfig, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal CONN_OMP_INUSE_SectorParameters */
		case 0x0001: {
			SETPRESENT_TCONN_OMP_INUSE_Data (data, ID_CONN_OMP_INUSE_CONN_OMP_INUSE_SectorParameters);
			INIT_c_CONN_OMP_INUSE_SectorParameters (data->Data.fld_c_CONN_OMP_INUSE_SectorParameters);
			retLen = DECODE_c_CONN_OMP_INUSE_SectorParameters (buffer, 0, data->Data.fld_c_CONN_OMP_INUSE_SectorParameters, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_CONN_OMP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_CONN_OMP_INUSE (const char* buffer, int len, TCONN_OMP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_CONN_OMP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_CONN_OMP_INUSE (char* buffer, ED_EXLONG bitOffset, TCONN_OMP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_CONN_OMP_INUSE_CONN_OMP_INUSE_QuickConfig: {
			retLen = ENCODE_c_CONN_OMP_INUSE_QuickConfig (buffer, 0, data->Data.fld_c_CONN_OMP_INUSE_QuickConfig, pCSN1CContextSet);
			break;
		}
		case ID_CONN_OMP_INUSE_CONN_OMP_INUSE_SectorParameters: {
			retLen = ENCODE_c_CONN_OMP_INUSE_SectorParameters (buffer, 0, data->Data.fld_c_CONN_OMP_INUSE_SectorParameters, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_SECURITY_DSP_INCFG (const char* buffer, TSECURITY_DSP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal SECURITY_DSP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TSECURITY_DSP_INCFG_Data (data, ID_SECURITY_DSP_INCFG_SECURITY_DSP_INCFG_ConfigurationRequest);
			INIT_c_SECURITY_DSP_INCFG_ConfigurationRequest (data->Data.fld_c_SECURITY_DSP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_SECURITY_DSP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_SECURITY_DSP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SECURITY_DSP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TSECURITY_DSP_INCFG_Data (data, ID_SECURITY_DSP_INCFG_SECURITY_DSP_INCFG_ConfigurationResponse);
			INIT_c_SECURITY_DSP_INCFG_ConfigurationResponse (data->Data.fld_c_SECURITY_DSP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_SECURITY_DSP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_SECURITY_DSP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_SECURITY_DSP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_SECURITY_DSP_INCFG (const char* buffer, int len, TSECURITY_DSP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_SECURITY_DSP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_SECURITY_DSP_INCFG (char* buffer, ED_EXLONG bitOffset, TSECURITY_DSP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_SECURITY_DSP_INCFG_SECURITY_DSP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_SECURITY_DSP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_SECURITY_DSP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_SECURITY_DSP_INCFG_SECURITY_DSP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_SECURITY_DSP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_SECURITY_DSP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_SECURITY_GSP_INCFG (const char* buffer, TSECURITY_GSP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal SECURITY_GSP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TSECURITY_GSP_INCFG_Data (data, ID_SECURITY_GSP_INCFG_SECURITY_GSP_INCFG_ConfigurationRequest);
			INIT_c_SECURITY_GSP_INCFG_ConfigurationRequest (data->Data.fld_c_SECURITY_GSP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_SECURITY_GSP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_SECURITY_GSP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SECURITY_GSP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TSECURITY_GSP_INCFG_Data (data, ID_SECURITY_GSP_INCFG_SECURITY_GSP_INCFG_ConfigurationResponse);
			INIT_c_SECURITY_GSP_INCFG_ConfigurationResponse (data->Data.fld_c_SECURITY_GSP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_SECURITY_GSP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_SECURITY_GSP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_SECURITY_GSP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_SECURITY_GSP_INCFG (const char* buffer, int len, TSECURITY_GSP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_SECURITY_GSP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_SECURITY_GSP_INCFG (char* buffer, ED_EXLONG bitOffset, TSECURITY_GSP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_SECURITY_GSP_INCFG_SECURITY_GSP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_SECURITY_GSP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_SECURITY_GSP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_SECURITY_GSP_INCFG_SECURITY_GSP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_SECURITY_GSP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_SECURITY_GSP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_SECURITY_DKEP_INCFG (const char* buffer, TSECURITY_DKEP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal SECURITY_DKEP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TSECURITY_DKEP_INCFG_Data (data, ID_SECURITY_DKEP_INCFG_SECURITY_DKEP_INCFG_ConfigurationRequest);
			INIT_c_SECURITY_DKEP_INCFG_ConfigurationRequest (data->Data.fld_c_SECURITY_DKEP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_SECURITY_DKEP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_SECURITY_DKEP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SECURITY_DKEP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TSECURITY_DKEP_INCFG_Data (data, ID_SECURITY_DKEP_INCFG_SECURITY_DKEP_INCFG_ConfigurationResponse);
			INIT_c_SECURITY_DKEP_INCFG_ConfigurationResponse (data->Data.fld_c_SECURITY_DKEP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_SECURITY_DKEP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_SECURITY_DKEP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_SECURITY_DKEP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_SECURITY_DKEP_INCFG (const char* buffer, int len, TSECURITY_DKEP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_SECURITY_DKEP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_SECURITY_DKEP_INCFG (char* buffer, ED_EXLONG bitOffset, TSECURITY_DKEP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_SECURITY_DKEP_INCFG_SECURITY_DKEP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_SECURITY_DKEP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_SECURITY_DKEP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_SECURITY_DKEP_INCFG_SECURITY_DKEP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_SECURITY_DKEP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_SECURITY_DKEP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_SECURITY_DHKEP_INCFG (const char* buffer, TSECURITY_DHKEP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal SECURITY_DHKEP_INCFG_KeyRequest */
		case 0x0000: {
			SETPRESENT_TSECURITY_DHKEP_INCFG_Data (data, ID_SECURITY_DHKEP_INCFG_SECURITY_DHKEP_INCFG_KeyRequest);
			INIT_c_SECURITY_DHKEP_INCFG_KeyRequest (data->Data.fld_c_SECURITY_DHKEP_INCFG_KeyRequest);
			retLen = DECODE_c_SECURITY_DHKEP_INCFG_KeyRequest (buffer, 0, data->Data.fld_c_SECURITY_DHKEP_INCFG_KeyRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SECURITY_DHKEP_INCFG_KeyResponse */
		case 0x0001: {
			SETPRESENT_TSECURITY_DHKEP_INCFG_Data (data, ID_SECURITY_DHKEP_INCFG_SECURITY_DHKEP_INCFG_KeyResponse);
			INIT_c_SECURITY_DHKEP_INCFG_KeyResponse (data->Data.fld_c_SECURITY_DHKEP_INCFG_KeyResponse);
			retLen = DECODE_c_SECURITY_DHKEP_INCFG_KeyResponse (buffer, 0, data->Data.fld_c_SECURITY_DHKEP_INCFG_KeyResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SECURITY_DHKEP_INCFG_ANKeyComplete */
		case 0x0002: {
			SETPRESENT_TSECURITY_DHKEP_INCFG_Data (data, ID_SECURITY_DHKEP_INCFG_SECURITY_DHKEP_INCFG_ANKeyComplete);
			INIT_c_SECURITY_DHKEP_INCFG_ANKeyComplete (data->Data.fld_c_SECURITY_DHKEP_INCFG_ANKeyComplete);
			retLen = DECODE_c_SECURITY_DHKEP_INCFG_ANKeyComplete (buffer, 0, data->Data.fld_c_SECURITY_DHKEP_INCFG_ANKeyComplete, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SECURITY_DHKEP_INCFG_ATKeyComplete */
		case 0x0003: {
			SETPRESENT_TSECURITY_DHKEP_INCFG_Data (data, ID_SECURITY_DHKEP_INCFG_SECURITY_DHKEP_INCFG_ATKeyComplete);
			INIT_c_SECURITY_DHKEP_INCFG_ATKeyComplete (data->Data.fld_c_SECURITY_DHKEP_INCFG_ATKeyComplete);
			retLen = DECODE_c_SECURITY_DHKEP_INCFG_ATKeyComplete (buffer, 0, data->Data.fld_c_SECURITY_DHKEP_INCFG_ATKeyComplete, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SECURITY_DHKEP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TSECURITY_DHKEP_INCFG_Data (data, ID_SECURITY_DHKEP_INCFG_SECURITY_DHKEP_INCFG_ConfigurationRequest);
			INIT_c_SECURITY_DHKEP_INCFG_ConfigurationRequest (data->Data.fld_c_SECURITY_DHKEP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_SECURITY_DHKEP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_SECURITY_DHKEP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SECURITY_DHKEP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TSECURITY_DHKEP_INCFG_Data (data, ID_SECURITY_DHKEP_INCFG_SECURITY_DHKEP_INCFG_ConfigurationResponse);
			INIT_c_SECURITY_DHKEP_INCFG_ConfigurationResponse (data->Data.fld_c_SECURITY_DHKEP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_SECURITY_DHKEP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_SECURITY_DHKEP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_SECURITY_DHKEP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_SECURITY_DHKEP_INCFG (const char* buffer, int len, TSECURITY_DHKEP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_SECURITY_DHKEP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_SECURITY_DHKEP_INCFG (char* buffer, ED_EXLONG bitOffset, TSECURITY_DHKEP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_SECURITY_DHKEP_INCFG_SECURITY_DHKEP_INCFG_KeyRequest: {
			retLen = ENCODE_c_SECURITY_DHKEP_INCFG_KeyRequest (buffer, 0, data->Data.fld_c_SECURITY_DHKEP_INCFG_KeyRequest, pCSN1CContextSet);
			break;
		}
		case ID_SECURITY_DHKEP_INCFG_SECURITY_DHKEP_INCFG_KeyResponse: {
			retLen = ENCODE_c_SECURITY_DHKEP_INCFG_KeyResponse (buffer, 0, data->Data.fld_c_SECURITY_DHKEP_INCFG_KeyResponse, pCSN1CContextSet);
			break;
		}
		case ID_SECURITY_DHKEP_INCFG_SECURITY_DHKEP_INCFG_ANKeyComplete: {
			retLen = ENCODE_c_SECURITY_DHKEP_INCFG_ANKeyComplete (buffer, 0, data->Data.fld_c_SECURITY_DHKEP_INCFG_ANKeyComplete, pCSN1CContextSet);
			break;
		}
		case ID_SECURITY_DHKEP_INCFG_SECURITY_DHKEP_INCFG_ATKeyComplete: {
			retLen = ENCODE_c_SECURITY_DHKEP_INCFG_ATKeyComplete (buffer, 0, data->Data.fld_c_SECURITY_DHKEP_INCFG_ATKeyComplete, pCSN1CContextSet);
			break;
		}
		case ID_SECURITY_DHKEP_INCFG_SECURITY_DHKEP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_SECURITY_DHKEP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_SECURITY_DHKEP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_SECURITY_DHKEP_INCFG_SECURITY_DHKEP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_SECURITY_DHKEP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_SECURITY_DHKEP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_SECURITY_DAP_INCFG (const char* buffer, TSECURITY_DAP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal SECURITY_DAP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TSECURITY_DAP_INCFG_Data (data, ID_SECURITY_DAP_INCFG_SECURITY_DAP_INCFG_ConfigurationRequest);
			INIT_c_SECURITY_DAP_INCFG_ConfigurationRequest (data->Data.fld_c_SECURITY_DAP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_SECURITY_DAP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_SECURITY_DAP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SECURITY_DAP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TSECURITY_DAP_INCFG_Data (data, ID_SECURITY_DAP_INCFG_SECURITY_DAP_INCFG_ConfigurationResponse);
			INIT_c_SECURITY_DAP_INCFG_ConfigurationResponse (data->Data.fld_c_SECURITY_DAP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_SECURITY_DAP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_SECURITY_DAP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_SECURITY_DAP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_SECURITY_DAP_INCFG (const char* buffer, int len, TSECURITY_DAP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_SECURITY_DAP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_SECURITY_DAP_INCFG (char* buffer, ED_EXLONG bitOffset, TSECURITY_DAP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_SECURITY_DAP_INCFG_SECURITY_DAP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_SECURITY_DAP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_SECURITY_DAP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_SECURITY_DAP_INCFG_SECURITY_DAP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_SECURITY_DAP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_SECURITY_DAP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_SECURITY_SHA1AP_INCFG (const char* buffer, TSECURITY_SHA1AP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal SECURITY_SHA1AP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TSECURITY_SHA1AP_INCFG_Data (data, ID_SECURITY_SHA1AP_INCFG_SECURITY_SHA1AP_INCFG_ConfigurationRequest);
			INIT_c_SECURITY_SHA1AP_INCFG_ConfigurationRequest (data->Data.fld_c_SECURITY_SHA1AP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_SECURITY_SHA1AP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_SECURITY_SHA1AP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SECURITY_SHA1AP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TSECURITY_SHA1AP_INCFG_Data (data, ID_SECURITY_SHA1AP_INCFG_SECURITY_SHA1AP_INCFG_ConfigurationResponse);
			INIT_c_SECURITY_SHA1AP_INCFG_ConfigurationResponse (data->Data.fld_c_SECURITY_SHA1AP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_SECURITY_SHA1AP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_SECURITY_SHA1AP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_SECURITY_SHA1AP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_SECURITY_SHA1AP_INCFG (const char* buffer, int len, TSECURITY_SHA1AP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_SECURITY_SHA1AP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_SECURITY_SHA1AP_INCFG (char* buffer, ED_EXLONG bitOffset, TSECURITY_SHA1AP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_SECURITY_SHA1AP_INCFG_SECURITY_SHA1AP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_SECURITY_SHA1AP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_SECURITY_SHA1AP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_SECURITY_SHA1AP_INCFG_SECURITY_SHA1AP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_SECURITY_SHA1AP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_SECURITY_SHA1AP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_SECURITY_DEP_INCFG (const char* buffer, TSECURITY_DEP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal SECURITY_DEP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TSECURITY_DEP_INCFG_Data (data, ID_SECURITY_DEP_INCFG_SECURITY_DEP_INCFG_ConfigurationRequest);
			INIT_c_SECURITY_DEP_INCFG_ConfigurationRequest (data->Data.fld_c_SECURITY_DEP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_SECURITY_DEP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_SECURITY_DEP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal SECURITY_DEP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TSECURITY_DEP_INCFG_Data (data, ID_SECURITY_DEP_INCFG_SECURITY_DEP_INCFG_ConfigurationResponse);
			INIT_c_SECURITY_DEP_INCFG_ConfigurationResponse (data->Data.fld_c_SECURITY_DEP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_SECURITY_DEP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_SECURITY_DEP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_SECURITY_DEP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_SECURITY_DEP_INCFG (const char* buffer, int len, TSECURITY_DEP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_SECURITY_DEP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_SECURITY_DEP_INCFG (char* buffer, ED_EXLONG bitOffset, TSECURITY_DEP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_SECURITY_DEP_INCFG_SECURITY_DEP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_SECURITY_DEP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_SECURITY_DEP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_SECURITY_DEP_INCFG_SECURITY_DEP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_SECURITY_DEP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_SECURITY_DEP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_MAC_DCCMACP_INCFG (const char* buffer, TMAC_DCCMACP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal MAC_DCCMACP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TMAC_DCCMACP_INCFG_Data (data, ID_MAC_DCCMACP_INCFG_MAC_DCCMACP_INCFG_ConfigurationRequest);
			INIT_c_MAC_DCCMACP_INCFG_ConfigurationRequest (data->Data.fld_c_MAC_DCCMACP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_MAC_DCCMACP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_MAC_DCCMACP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_DCCMACP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TMAC_DCCMACP_INCFG_Data (data, ID_MAC_DCCMACP_INCFG_MAC_DCCMACP_INCFG_ConfigurationResponse);
			INIT_c_MAC_DCCMACP_INCFG_ConfigurationResponse (data->Data.fld_c_MAC_DCCMACP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_MAC_DCCMACP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_MAC_DCCMACP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_MAC_DCCMACP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_DCCMACP_INCFG (const char* buffer, int len, TMAC_DCCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_MAC_DCCMACP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_MAC_DCCMACP_INCFG (char* buffer, ED_EXLONG bitOffset, TMAC_DCCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_MAC_DCCMACP_INCFG_MAC_DCCMACP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_MAC_DCCMACP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_MAC_DCCMACP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_MAC_DCCMACP_INCFG_MAC_DCCMACP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_MAC_DCCMACP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_MAC_DCCMACP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_MAC_ECCMACP_INCFG (const char* buffer, TMAC_ECCMACP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal MAC_ECCMACP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TMAC_ECCMACP_INCFG_Data (data, ID_MAC_ECCMACP_INCFG_MAC_ECCMACP_INCFG_ConfigurationRequest);
			INIT_c_MAC_ECCMACP_INCFG_ConfigurationRequest (data->Data.fld_c_MAC_ECCMACP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_MAC_ECCMACP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_MAC_ECCMACP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_ECCMACP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TMAC_ECCMACP_INCFG_Data (data, ID_MAC_ECCMACP_INCFG_MAC_ECCMACP_INCFG_ConfigurationResponse);
			INIT_c_MAC_ECCMACP_INCFG_ConfigurationResponse (data->Data.fld_c_MAC_ECCMACP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_MAC_ECCMACP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_MAC_ECCMACP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_MAC_ECCMACP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_ECCMACP_INCFG (const char* buffer, int len, TMAC_ECCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_MAC_ECCMACP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_MAC_ECCMACP_INCFG (char* buffer, ED_EXLONG bitOffset, TMAC_ECCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_MAC_ECCMACP_INCFG_MAC_ECCMACP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_MAC_ECCMACP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_MAC_ECCMACP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_MAC_ECCMACP_INCFG_MAC_ECCMACP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_MAC_ECCMACP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_MAC_ECCMACP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_MAC_DACMACP_INCFG (const char* buffer, TMAC_DACMACP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal MAC_DACMACP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TMAC_DACMACP_INCFG_Data (data, ID_MAC_DACMACP_INCFG_MAC_DACMACP_INCFG_ConfigurationRequest);
			INIT_c_MAC_DACMACP_INCFG_ConfigurationRequest (data->Data.fld_c_MAC_DACMACP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_MAC_DACMACP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_MAC_DACMACP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_DACMACP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TMAC_DACMACP_INCFG_Data (data, ID_MAC_DACMACP_INCFG_MAC_DACMACP_INCFG_ConfigurationResponse);
			INIT_c_MAC_DACMACP_INCFG_ConfigurationResponse (data->Data.fld_c_MAC_DACMACP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_MAC_DACMACP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_MAC_DACMACP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_MAC_DACMACP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_DACMACP_INCFG (const char* buffer, int len, TMAC_DACMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_MAC_DACMACP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_MAC_DACMACP_INCFG (char* buffer, ED_EXLONG bitOffset, TMAC_DACMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_MAC_DACMACP_INCFG_MAC_DACMACP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_MAC_DACMACP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_MAC_DACMACP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_MAC_DACMACP_INCFG_MAC_DACMACP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_MAC_DACMACP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_MAC_DACMACP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_MAC_DACMACP_INUSE (const char* buffer, TMAC_DACMACP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal MAC_DACMACP_INUSE_ACAck */
		case 0x0000: {
			SETPRESENT_TMAC_DACMACP_INUSE_Data (data, ID_MAC_DACMACP_INUSE_MAC_DACMACP_INUSE_ACAck);
			INIT_c_MAC_DACMACP_INUSE_ACAck (data->Data.fld_c_MAC_DACMACP_INUSE_ACAck);
			retLen = DECODE_c_MAC_DACMACP_INUSE_ACAck (buffer, 0, data->Data.fld_c_MAC_DACMACP_INUSE_ACAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_DACMACP_INUSE_AccessParameters */
		case 0x0001: {
			SETPRESENT_TMAC_DACMACP_INUSE_Data (data, ID_MAC_DACMACP_INUSE_MAC_DACMACP_INUSE_AccessParameters);
			INIT_c_MAC_DACMACP_INUSE_AccessParameters (data->Data.fld_c_MAC_DACMACP_INUSE_AccessParameters);
			retLen = DECODE_c_MAC_DACMACP_INUSE_AccessParameters (buffer, 0, data->Data.fld_c_MAC_DACMACP_INUSE_AccessParameters, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_MAC_DACMACP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_DACMACP_INUSE (const char* buffer, int len, TMAC_DACMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_MAC_DACMACP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_MAC_DACMACP_INUSE (char* buffer, ED_EXLONG bitOffset, TMAC_DACMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_MAC_DACMACP_INUSE_MAC_DACMACP_INUSE_ACAck: {
			retLen = ENCODE_c_MAC_DACMACP_INUSE_ACAck (buffer, 0, data->Data.fld_c_MAC_DACMACP_INUSE_ACAck, pCSN1CContextSet);
			break;
		}
		case ID_MAC_DACMACP_INUSE_MAC_DACMACP_INUSE_AccessParameters: {
			retLen = ENCODE_c_MAC_DACMACP_INUSE_AccessParameters (buffer, 0, data->Data.fld_c_MAC_DACMACP_INUSE_AccessParameters, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_MAC_EACMACP_INCFG (const char* buffer, TMAC_EACMACP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal MAC_EACMACP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TMAC_EACMACP_INCFG_Data (data, ID_MAC_EACMACP_INCFG_MAC_EACMACP_INCFG_ConfigurationRequest);
			INIT_c_MAC_EACMACP_INCFG_ConfigurationRequest (data->Data.fld_c_MAC_EACMACP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_MAC_EACMACP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_MAC_EACMACP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_EACMACP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TMAC_EACMACP_INCFG_Data (data, ID_MAC_EACMACP_INCFG_MAC_EACMACP_INCFG_ConfigurationResponse);
			INIT_c_MAC_EACMACP_INCFG_ConfigurationResponse (data->Data.fld_c_MAC_EACMACP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_MAC_EACMACP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_MAC_EACMACP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_MAC_EACMACP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_EACMACP_INCFG (const char* buffer, int len, TMAC_EACMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_MAC_EACMACP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_MAC_EACMACP_INCFG (char* buffer, ED_EXLONG bitOffset, TMAC_EACMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_MAC_EACMACP_INCFG_MAC_EACMACP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_MAC_EACMACP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_MAC_EACMACP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_MAC_EACMACP_INCFG_MAC_EACMACP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_MAC_EACMACP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_MAC_EACMACP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_MAC_EACMACP_INUSE (const char* buffer, TMAC_EACMACP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal MAC_EACMACP_INUSE_ACAck */
		case 0x0000: {
			SETPRESENT_TMAC_EACMACP_INUSE_Data (data, ID_MAC_EACMACP_INUSE_MAC_EACMACP_INUSE_ACAck);
			INIT_c_MAC_EACMACP_INUSE_ACAck (data->Data.fld_c_MAC_EACMACP_INUSE_ACAck);
			retLen = DECODE_c_MAC_EACMACP_INUSE_ACAck (buffer, 0, data->Data.fld_c_MAC_EACMACP_INUSE_ACAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_EACMACP_INUSE_AccessParameters */
		case 0x0001: {
			SETPRESENT_TMAC_EACMACP_INUSE_Data (data, ID_MAC_EACMACP_INUSE_MAC_EACMACP_INUSE_AccessParameters);
			INIT_c_MAC_EACMACP_INUSE_AccessParameters (data->Data.fld_c_MAC_EACMACP_INUSE_AccessParameters);
			retLen = DECODE_c_MAC_EACMACP_INUSE_AccessParameters (buffer, 0, data->Data.fld_c_MAC_EACMACP_INUSE_AccessParameters, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_EACMACP_INUSE_AttributeUpdateRequest */
		case 0x0052: {
			SETPRESENT_TMAC_EACMACP_INUSE_Data (data, ID_MAC_EACMACP_INUSE_MAC_EACMACP_INUSE_AttributeUpdateRequest);
			INIT_c_MAC_EACMACP_INUSE_AttributeUpdateRequest (data->Data.fld_c_MAC_EACMACP_INUSE_AttributeUpdateRequest);
			retLen = DECODE_c_MAC_EACMACP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_MAC_EACMACP_INUSE_AttributeUpdateRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_EACMACP_INUSE_AttributeUpdateAccept */
		case 0x0053: {
			SETPRESENT_TMAC_EACMACP_INUSE_Data (data, ID_MAC_EACMACP_INUSE_MAC_EACMACP_INUSE_AttributeUpdateAccept);
			INIT_c_MAC_EACMACP_INUSE_AttributeUpdateAccept (data->Data.fld_c_MAC_EACMACP_INUSE_AttributeUpdateAccept);
			retLen = DECODE_c_MAC_EACMACP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_MAC_EACMACP_INUSE_AttributeUpdateAccept, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_EACMACP_INUSE_AttributeUpdateReject */
		case 0x0054: {
			SETPRESENT_TMAC_EACMACP_INUSE_Data (data, ID_MAC_EACMACP_INUSE_MAC_EACMACP_INUSE_AttributeUpdateReject);
			INIT_c_MAC_EACMACP_INUSE_AttributeUpdateReject (data->Data.fld_c_MAC_EACMACP_INUSE_AttributeUpdateReject);
			retLen = DECODE_c_MAC_EACMACP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_MAC_EACMACP_INUSE_AttributeUpdateReject, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_MAC_EACMACP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_EACMACP_INUSE (const char* buffer, int len, TMAC_EACMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_MAC_EACMACP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_MAC_EACMACP_INUSE (char* buffer, ED_EXLONG bitOffset, TMAC_EACMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_MAC_EACMACP_INUSE_MAC_EACMACP_INUSE_ACAck: {
			retLen = ENCODE_c_MAC_EACMACP_INUSE_ACAck (buffer, 0, data->Data.fld_c_MAC_EACMACP_INUSE_ACAck, pCSN1CContextSet);
			break;
		}
		case ID_MAC_EACMACP_INUSE_MAC_EACMACP_INUSE_AccessParameters: {
			retLen = ENCODE_c_MAC_EACMACP_INUSE_AccessParameters (buffer, 0, data->Data.fld_c_MAC_EACMACP_INUSE_AccessParameters, pCSN1CContextSet);
			break;
		}
		case ID_MAC_EACMACP_INUSE_MAC_EACMACP_INUSE_AttributeUpdateRequest: {
			retLen = ENCODE_c_MAC_EACMACP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_MAC_EACMACP_INUSE_AttributeUpdateRequest, pCSN1CContextSet);
			break;
		}
		case ID_MAC_EACMACP_INUSE_MAC_EACMACP_INUSE_AttributeUpdateAccept: {
			retLen = ENCODE_c_MAC_EACMACP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_MAC_EACMACP_INUSE_AttributeUpdateAccept, pCSN1CContextSet);
			break;
		}
		case ID_MAC_EACMACP_INUSE_MAC_EACMACP_INUSE_AttributeUpdateReject: {
			retLen = ENCODE_c_MAC_EACMACP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_MAC_EACMACP_INUSE_AttributeUpdateReject, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_MAC_DFTCMACP_INCFG (const char* buffer, TMAC_DFTCMACP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal MAC_DFTCMACP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TMAC_DFTCMACP_INCFG_Data (data, ID_MAC_DFTCMACP_INCFG_MAC_DFTCMACP_INCFG_ConfigurationRequest);
			INIT_c_MAC_DFTCMACP_INCFG_ConfigurationRequest (data->Data.fld_c_MAC_DFTCMACP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_MAC_DFTCMACP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_MAC_DFTCMACP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_DFTCMACP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TMAC_DFTCMACP_INCFG_Data (data, ID_MAC_DFTCMACP_INCFG_MAC_DFTCMACP_INCFG_ConfigurationResponse);
			INIT_c_MAC_DFTCMACP_INCFG_ConfigurationResponse (data->Data.fld_c_MAC_DFTCMACP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_MAC_DFTCMACP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_MAC_DFTCMACP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_MAC_DFTCMACP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_DFTCMACP_INCFG (const char* buffer, int len, TMAC_DFTCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_MAC_DFTCMACP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_MAC_DFTCMACP_INCFG (char* buffer, ED_EXLONG bitOffset, TMAC_DFTCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_MAC_DFTCMACP_INCFG_MAC_DFTCMACP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_MAC_DFTCMACP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_MAC_DFTCMACP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_MAC_DFTCMACP_INCFG_MAC_DFTCMACP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_MAC_DFTCMACP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_MAC_DFTCMACP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_MAC_DFTCMACP_INUSE (const char* buffer, TMAC_DFTCMACP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal MAC_DFTCMACP_INUSE_FixedModeEnable */
		case 0x0000: {
			SETPRESENT_TMAC_DFTCMACP_INUSE_Data (data, ID_MAC_DFTCMACP_INUSE_MAC_DFTCMACP_INUSE_FixedModeEnable);
			INIT_c_MAC_DFTCMACP_INUSE_FixedModeEnable (data->Data.fld_c_MAC_DFTCMACP_INUSE_FixedModeEnable);
			retLen = DECODE_c_MAC_DFTCMACP_INUSE_FixedModeEnable (buffer, 0, data->Data.fld_c_MAC_DFTCMACP_INUSE_FixedModeEnable, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_DFTCMACP_INUSE_FixedModeXoff */
		case 0x0001: {
			SETPRESENT_TMAC_DFTCMACP_INUSE_Data (data, ID_MAC_DFTCMACP_INUSE_MAC_DFTCMACP_INUSE_FixedModeXoff);
			INIT_c_MAC_DFTCMACP_INUSE_FixedModeXoff (data->Data.fld_c_MAC_DFTCMACP_INUSE_FixedModeXoff);
			retLen = DECODE_c_MAC_DFTCMACP_INUSE_FixedModeXoff (buffer, 0, data->Data.fld_c_MAC_DFTCMACP_INUSE_FixedModeXoff, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_MAC_DFTCMACP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_DFTCMACP_INUSE (const char* buffer, int len, TMAC_DFTCMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_MAC_DFTCMACP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_MAC_DFTCMACP_INUSE (char* buffer, ED_EXLONG bitOffset, TMAC_DFTCMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_MAC_DFTCMACP_INUSE_MAC_DFTCMACP_INUSE_FixedModeEnable: {
			retLen = ENCODE_c_MAC_DFTCMACP_INUSE_FixedModeEnable (buffer, 0, data->Data.fld_c_MAC_DFTCMACP_INUSE_FixedModeEnable, pCSN1CContextSet);
			break;
		}
		case ID_MAC_DFTCMACP_INUSE_MAC_DFTCMACP_INUSE_FixedModeXoff: {
			retLen = ENCODE_c_MAC_DFTCMACP_INUSE_FixedModeXoff (buffer, 0, data->Data.fld_c_MAC_DFTCMACP_INUSE_FixedModeXoff, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_MAC_EFTCMACP_INCFG (const char* buffer, TMAC_EFTCMACP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal MAC_EFTCMACP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TMAC_EFTCMACP_INCFG_Data (data, ID_MAC_EFTCMACP_INCFG_MAC_EFTCMACP_INCFG_ConfigurationRequest);
			INIT_c_MAC_EFTCMACP_INCFG_ConfigurationRequest (data->Data.fld_c_MAC_EFTCMACP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_MAC_EFTCMACP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_MAC_EFTCMACP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_EFTCMACP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TMAC_EFTCMACP_INCFG_Data (data, ID_MAC_EFTCMACP_INCFG_MAC_EFTCMACP_INCFG_ConfigurationResponse);
			INIT_c_MAC_EFTCMACP_INCFG_ConfigurationResponse (data->Data.fld_c_MAC_EFTCMACP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_MAC_EFTCMACP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_MAC_EFTCMACP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_MAC_EFTCMACP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_EFTCMACP_INCFG (const char* buffer, int len, TMAC_EFTCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_MAC_EFTCMACP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_MAC_EFTCMACP_INCFG (char* buffer, ED_EXLONG bitOffset, TMAC_EFTCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_MAC_EFTCMACP_INCFG_MAC_EFTCMACP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_MAC_EFTCMACP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_MAC_EFTCMACP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_MAC_EFTCMACP_INCFG_MAC_EFTCMACP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_MAC_EFTCMACP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_MAC_EFTCMACP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_MAC_EFTCMACP_INUSE (const char* buffer, TMAC_EFTCMACP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal MAC_EFTCMACP_INUSE_FixedModeEnable */
		case 0x0000: {
			SETPRESENT_TMAC_EFTCMACP_INUSE_Data (data, ID_MAC_EFTCMACP_INUSE_MAC_EFTCMACP_INUSE_FixedModeEnable);
			INIT_c_MAC_EFTCMACP_INUSE_FixedModeEnable (data->Data.fld_c_MAC_EFTCMACP_INUSE_FixedModeEnable);
			retLen = DECODE_c_MAC_EFTCMACP_INUSE_FixedModeEnable (buffer, 0, data->Data.fld_c_MAC_EFTCMACP_INUSE_FixedModeEnable, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_EFTCMACP_INUSE_FixedModeXoff */
		case 0x0001: {
			SETPRESENT_TMAC_EFTCMACP_INUSE_Data (data, ID_MAC_EFTCMACP_INUSE_MAC_EFTCMACP_INUSE_FixedModeXoff);
			INIT_c_MAC_EFTCMACP_INUSE_FixedModeXoff (data->Data.fld_c_MAC_EFTCMACP_INUSE_FixedModeXoff);
			retLen = DECODE_c_MAC_EFTCMACP_INUSE_FixedModeXoff (buffer, 0, data->Data.fld_c_MAC_EFTCMACP_INUSE_FixedModeXoff, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_EFTCMACP_INUSE_AttributeUpdateRequest */
		case 0x0052: {
			SETPRESENT_TMAC_EFTCMACP_INUSE_Data (data, ID_MAC_EFTCMACP_INUSE_MAC_EFTCMACP_INUSE_AttributeUpdateRequest);
			INIT_c_MAC_EFTCMACP_INUSE_AttributeUpdateRequest (data->Data.fld_c_MAC_EFTCMACP_INUSE_AttributeUpdateRequest);
			retLen = DECODE_c_MAC_EFTCMACP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_MAC_EFTCMACP_INUSE_AttributeUpdateRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_EFTCMACP_INUSE_AttributeUpdateAccept */
		case 0x0053: {
			SETPRESENT_TMAC_EFTCMACP_INUSE_Data (data, ID_MAC_EFTCMACP_INUSE_MAC_EFTCMACP_INUSE_AttributeUpdateAccept);
			INIT_c_MAC_EFTCMACP_INUSE_AttributeUpdateAccept (data->Data.fld_c_MAC_EFTCMACP_INUSE_AttributeUpdateAccept);
			retLen = DECODE_c_MAC_EFTCMACP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_MAC_EFTCMACP_INUSE_AttributeUpdateAccept, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_EFTCMACP_INUSE_AttributeUpdateReject */
		case 0x0054: {
			SETPRESENT_TMAC_EFTCMACP_INUSE_Data (data, ID_MAC_EFTCMACP_INUSE_MAC_EFTCMACP_INUSE_AttributeUpdateReject);
			INIT_c_MAC_EFTCMACP_INUSE_AttributeUpdateReject (data->Data.fld_c_MAC_EFTCMACP_INUSE_AttributeUpdateReject);
			retLen = DECODE_c_MAC_EFTCMACP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_MAC_EFTCMACP_INUSE_AttributeUpdateReject, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_MAC_EFTCMACP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_EFTCMACP_INUSE (const char* buffer, int len, TMAC_EFTCMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_MAC_EFTCMACP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_MAC_EFTCMACP_INUSE (char* buffer, ED_EXLONG bitOffset, TMAC_EFTCMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_MAC_EFTCMACP_INUSE_MAC_EFTCMACP_INUSE_FixedModeEnable: {
			retLen = ENCODE_c_MAC_EFTCMACP_INUSE_FixedModeEnable (buffer, 0, data->Data.fld_c_MAC_EFTCMACP_INUSE_FixedModeEnable, pCSN1CContextSet);
			break;
		}
		case ID_MAC_EFTCMACP_INUSE_MAC_EFTCMACP_INUSE_FixedModeXoff: {
			retLen = ENCODE_c_MAC_EFTCMACP_INUSE_FixedModeXoff (buffer, 0, data->Data.fld_c_MAC_EFTCMACP_INUSE_FixedModeXoff, pCSN1CContextSet);
			break;
		}
		case ID_MAC_EFTCMACP_INUSE_MAC_EFTCMACP_INUSE_AttributeUpdateRequest: {
			retLen = ENCODE_c_MAC_EFTCMACP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_MAC_EFTCMACP_INUSE_AttributeUpdateRequest, pCSN1CContextSet);
			break;
		}
		case ID_MAC_EFTCMACP_INUSE_MAC_EFTCMACP_INUSE_AttributeUpdateAccept: {
			retLen = ENCODE_c_MAC_EFTCMACP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_MAC_EFTCMACP_INUSE_AttributeUpdateAccept, pCSN1CContextSet);
			break;
		}
		case ID_MAC_EFTCMACP_INUSE_MAC_EFTCMACP_INUSE_AttributeUpdateReject: {
			retLen = ENCODE_c_MAC_EFTCMACP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_MAC_EFTCMACP_INUSE_AttributeUpdateReject, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_MAC_MFTCMACP_INCFG (const char* buffer, TMAC_MFTCMACP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal MAC_MFTCMACP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TMAC_MFTCMACP_INCFG_Data (data, ID_MAC_MFTCMACP_INCFG_MAC_MFTCMACP_INCFG_ConfigurationRequest);
			INIT_c_MAC_MFTCMACP_INCFG_ConfigurationRequest (data->Data.fld_c_MAC_MFTCMACP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_MAC_MFTCMACP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_MAC_MFTCMACP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_MFTCMACP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TMAC_MFTCMACP_INCFG_Data (data, ID_MAC_MFTCMACP_INCFG_MAC_MFTCMACP_INCFG_ConfigurationResponse);
			INIT_c_MAC_MFTCMACP_INCFG_ConfigurationResponse (data->Data.fld_c_MAC_MFTCMACP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_MAC_MFTCMACP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_MAC_MFTCMACP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_MAC_MFTCMACP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_MFTCMACP_INCFG (const char* buffer, int len, TMAC_MFTCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_MAC_MFTCMACP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_MAC_MFTCMACP_INCFG (char* buffer, ED_EXLONG bitOffset, TMAC_MFTCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_MAC_MFTCMACP_INCFG_MAC_MFTCMACP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_MAC_MFTCMACP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_MAC_MFTCMACP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_MAC_MFTCMACP_INCFG_MAC_MFTCMACP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_MAC_MFTCMACP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_MAC_MFTCMACP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_MAC_MFTCMACP_INUSE (const char* buffer, TMAC_MFTCMACP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal MAC_MFTCMACP_INUSE_FixedModeEnable */
		case 0x0000: {
			SETPRESENT_TMAC_MFTCMACP_INUSE_Data (data, ID_MAC_MFTCMACP_INUSE_MAC_MFTCMACP_INUSE_FixedModeEnable);
			INIT_c_MAC_MFTCMACP_INUSE_FixedModeEnable (data->Data.fld_c_MAC_MFTCMACP_INUSE_FixedModeEnable);
			retLen = DECODE_c_MAC_MFTCMACP_INUSE_FixedModeEnable (buffer, 0, data->Data.fld_c_MAC_MFTCMACP_INUSE_FixedModeEnable, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_MFTCMACP_INUSE_FixedModeXoff */
		case 0x0001: {
			SETPRESENT_TMAC_MFTCMACP_INUSE_Data (data, ID_MAC_MFTCMACP_INUSE_MAC_MFTCMACP_INUSE_FixedModeXoff);
			INIT_c_MAC_MFTCMACP_INUSE_FixedModeXoff (data->Data.fld_c_MAC_MFTCMACP_INUSE_FixedModeXoff);
			retLen = DECODE_c_MAC_MFTCMACP_INUSE_FixedModeXoff (buffer, 0, data->Data.fld_c_MAC_MFTCMACP_INUSE_FixedModeXoff, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_MFTCMACP_INUSE_AttributeUpdateRequest */
		case 0x0052: {
			SETPRESENT_TMAC_MFTCMACP_INUSE_Data (data, ID_MAC_MFTCMACP_INUSE_MAC_MFTCMACP_INUSE_AttributeUpdateRequest);
			INIT_c_MAC_MFTCMACP_INUSE_AttributeUpdateRequest (data->Data.fld_c_MAC_MFTCMACP_INUSE_AttributeUpdateRequest);
			retLen = DECODE_c_MAC_MFTCMACP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_MAC_MFTCMACP_INUSE_AttributeUpdateRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_MFTCMACP_INUSE_AttributeUpdateAccept */
		case 0x0053: {
			SETPRESENT_TMAC_MFTCMACP_INUSE_Data (data, ID_MAC_MFTCMACP_INUSE_MAC_MFTCMACP_INUSE_AttributeUpdateAccept);
			INIT_c_MAC_MFTCMACP_INUSE_AttributeUpdateAccept (data->Data.fld_c_MAC_MFTCMACP_INUSE_AttributeUpdateAccept);
			retLen = DECODE_c_MAC_MFTCMACP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_MAC_MFTCMACP_INUSE_AttributeUpdateAccept, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_MFTCMACP_INUSE_AttributeUpdateReject */
		case 0x0054: {
			SETPRESENT_TMAC_MFTCMACP_INUSE_Data (data, ID_MAC_MFTCMACP_INUSE_MAC_MFTCMACP_INUSE_AttributeUpdateReject);
			INIT_c_MAC_MFTCMACP_INUSE_AttributeUpdateReject (data->Data.fld_c_MAC_MFTCMACP_INUSE_AttributeUpdateReject);
			retLen = DECODE_c_MAC_MFTCMACP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_MAC_MFTCMACP_INUSE_AttributeUpdateReject, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_MAC_MFTCMACP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_MFTCMACP_INUSE (const char* buffer, int len, TMAC_MFTCMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_MAC_MFTCMACP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_MAC_MFTCMACP_INUSE (char* buffer, ED_EXLONG bitOffset, TMAC_MFTCMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_MAC_MFTCMACP_INUSE_MAC_MFTCMACP_INUSE_FixedModeEnable: {
			retLen = ENCODE_c_MAC_MFTCMACP_INUSE_FixedModeEnable (buffer, 0, data->Data.fld_c_MAC_MFTCMACP_INUSE_FixedModeEnable, pCSN1CContextSet);
			break;
		}
		case ID_MAC_MFTCMACP_INUSE_MAC_MFTCMACP_INUSE_FixedModeXoff: {
			retLen = ENCODE_c_MAC_MFTCMACP_INUSE_FixedModeXoff (buffer, 0, data->Data.fld_c_MAC_MFTCMACP_INUSE_FixedModeXoff, pCSN1CContextSet);
			break;
		}
		case ID_MAC_MFTCMACP_INUSE_MAC_MFTCMACP_INUSE_AttributeUpdateRequest: {
			retLen = ENCODE_c_MAC_MFTCMACP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_MAC_MFTCMACP_INUSE_AttributeUpdateRequest, pCSN1CContextSet);
			break;
		}
		case ID_MAC_MFTCMACP_INUSE_MAC_MFTCMACP_INUSE_AttributeUpdateAccept: {
			retLen = ENCODE_c_MAC_MFTCMACP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_MAC_MFTCMACP_INUSE_AttributeUpdateAccept, pCSN1CContextSet);
			break;
		}
		case ID_MAC_MFTCMACP_INUSE_MAC_MFTCMACP_INUSE_AttributeUpdateReject: {
			retLen = ENCODE_c_MAC_MFTCMACP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_MAC_MFTCMACP_INUSE_AttributeUpdateReject, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_MAC_DRTCMACP_INCFG (const char* buffer, TMAC_DRTCMACP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal MAC_DRTCMACP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TMAC_DRTCMACP_INCFG_Data (data, ID_MAC_DRTCMACP_INCFG_MAC_DRTCMACP_INCFG_ConfigurationRequest);
			INIT_c_MAC_DRTCMACP_INCFG_ConfigurationRequest (data->Data.fld_c_MAC_DRTCMACP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_MAC_DRTCMACP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_MAC_DRTCMACP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_DRTCMACP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TMAC_DRTCMACP_INCFG_Data (data, ID_MAC_DRTCMACP_INCFG_MAC_DRTCMACP_INCFG_ConfigurationResponse);
			INIT_c_MAC_DRTCMACP_INCFG_ConfigurationResponse (data->Data.fld_c_MAC_DRTCMACP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_MAC_DRTCMACP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_MAC_DRTCMACP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_MAC_DRTCMACP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_DRTCMACP_INCFG (const char* buffer, int len, TMAC_DRTCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_MAC_DRTCMACP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_MAC_DRTCMACP_INCFG (char* buffer, ED_EXLONG bitOffset, TMAC_DRTCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_MAC_DRTCMACP_INCFG_MAC_DRTCMACP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_MAC_DRTCMACP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_MAC_DRTCMACP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_MAC_DRTCMACP_INCFG_MAC_DRTCMACP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_MAC_DRTCMACP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_MAC_DRTCMACP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_MAC_DRTCMACP_INUSE (const char* buffer, TMAC_DRTCMACP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal MAC_DRTCMACP_INUSE_RTCAck */
		case 0x0000: {
			SETPRESENT_TMAC_DRTCMACP_INUSE_Data (data, ID_MAC_DRTCMACP_INUSE_MAC_DRTCMACP_INUSE_RTCAck);
			INIT_c_MAC_DRTCMACP_INUSE_RTCAck (data->Data.fld_c_MAC_DRTCMACP_INUSE_RTCAck);
			retLen = DECODE_c_MAC_DRTCMACP_INUSE_RTCAck (buffer, 0, data->Data.fld_c_MAC_DRTCMACP_INUSE_RTCAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_DRTCMACP_INUSE_BroadcastReverseRateLimit */
		case 0x0001: {
			SETPRESENT_TMAC_DRTCMACP_INUSE_Data (data, ID_MAC_DRTCMACP_INUSE_MAC_DRTCMACP_INUSE_BroadcastReverseRateLimit);
			INIT_c_MAC_DRTCMACP_INUSE_BroadcastReverseRateLimit (data->Data.fld_c_MAC_DRTCMACP_INUSE_BroadcastReverseRateLimit);
			retLen = DECODE_c_MAC_DRTCMACP_INUSE_BroadcastReverseRateLimit (buffer, 0, data->Data.fld_c_MAC_DRTCMACP_INUSE_BroadcastReverseRateLimit, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_DRTCMACP_INUSE_UnicastReverseRateLimit */
		case 0x0002: {
			SETPRESENT_TMAC_DRTCMACP_INUSE_Data (data, ID_MAC_DRTCMACP_INUSE_MAC_DRTCMACP_INUSE_UnicastReverseRateLimit);
			INIT_c_MAC_DRTCMACP_INUSE_UnicastReverseRateLimit (data->Data.fld_c_MAC_DRTCMACP_INUSE_UnicastReverseRateLimit);
			retLen = DECODE_c_MAC_DRTCMACP_INUSE_UnicastReverseRateLimit (buffer, 0, data->Data.fld_c_MAC_DRTCMACP_INUSE_UnicastReverseRateLimit, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_MAC_DRTCMACP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_DRTCMACP_INUSE (const char* buffer, int len, TMAC_DRTCMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_MAC_DRTCMACP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_MAC_DRTCMACP_INUSE (char* buffer, ED_EXLONG bitOffset, TMAC_DRTCMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_MAC_DRTCMACP_INUSE_MAC_DRTCMACP_INUSE_RTCAck: {
			retLen = ENCODE_c_MAC_DRTCMACP_INUSE_RTCAck (buffer, 0, data->Data.fld_c_MAC_DRTCMACP_INUSE_RTCAck, pCSN1CContextSet);
			break;
		}
		case ID_MAC_DRTCMACP_INUSE_MAC_DRTCMACP_INUSE_BroadcastReverseRateLimit: {
			retLen = ENCODE_c_MAC_DRTCMACP_INUSE_BroadcastReverseRateLimit (buffer, 0, data->Data.fld_c_MAC_DRTCMACP_INUSE_BroadcastReverseRateLimit, pCSN1CContextSet);
			break;
		}
		case ID_MAC_DRTCMACP_INUSE_MAC_DRTCMACP_INUSE_UnicastReverseRateLimit: {
			retLen = ENCODE_c_MAC_DRTCMACP_INUSE_UnicastReverseRateLimit (buffer, 0, data->Data.fld_c_MAC_DRTCMACP_INUSE_UnicastReverseRateLimit, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_MAC_S1RTCMACP_INCFG (const char* buffer, TMAC_S1RTCMACP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal MAC_S1RTCMACP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TMAC_S1RTCMACP_INCFG_Data (data, ID_MAC_S1RTCMACP_INCFG_MAC_S1RTCMACP_INCFG_ConfigurationRequest);
			INIT_c_MAC_S1RTCMACP_INCFG_ConfigurationRequest (data->Data.fld_c_MAC_S1RTCMACP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_MAC_S1RTCMACP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_MAC_S1RTCMACP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_S1RTCMACP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TMAC_S1RTCMACP_INCFG_Data (data, ID_MAC_S1RTCMACP_INCFG_MAC_S1RTCMACP_INCFG_ConfigurationResponse);
			INIT_c_MAC_S1RTCMACP_INCFG_ConfigurationResponse (data->Data.fld_c_MAC_S1RTCMACP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_MAC_S1RTCMACP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_MAC_S1RTCMACP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_MAC_S1RTCMACP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_S1RTCMACP_INCFG (const char* buffer, int len, TMAC_S1RTCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_MAC_S1RTCMACP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_MAC_S1RTCMACP_INCFG (char* buffer, ED_EXLONG bitOffset, TMAC_S1RTCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_MAC_S1RTCMACP_INCFG_MAC_S1RTCMACP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_MAC_S1RTCMACP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_MAC_S1RTCMACP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_MAC_S1RTCMACP_INCFG_MAC_S1RTCMACP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_MAC_S1RTCMACP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_MAC_S1RTCMACP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_MAC_S1RTCMACP_INUSE (const char* buffer, TMAC_S1RTCMACP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal MAC_S1RTCMACP_INUSE_RTCAck */
		case 0x0000: {
			SETPRESENT_TMAC_S1RTCMACP_INUSE_Data (data, ID_MAC_S1RTCMACP_INUSE_MAC_S1RTCMACP_INUSE_RTCAck);
			INIT_c_MAC_S1RTCMACP_INUSE_RTCAck (data->Data.fld_c_MAC_S1RTCMACP_INUSE_RTCAck);
			retLen = DECODE_c_MAC_S1RTCMACP_INUSE_RTCAck (buffer, 0, data->Data.fld_c_MAC_S1RTCMACP_INUSE_RTCAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_S1RTCMACP_INUSE_BroadcastReverseRateLimit */
		case 0x0001: {
			SETPRESENT_TMAC_S1RTCMACP_INUSE_Data (data, ID_MAC_S1RTCMACP_INUSE_MAC_S1RTCMACP_INUSE_BroadcastReverseRateLimit);
			INIT_c_MAC_S1RTCMACP_INUSE_BroadcastReverseRateLimit (data->Data.fld_c_MAC_S1RTCMACP_INUSE_BroadcastReverseRateLimit);
			retLen = DECODE_c_MAC_S1RTCMACP_INUSE_BroadcastReverseRateLimit (buffer, 0, data->Data.fld_c_MAC_S1RTCMACP_INUSE_BroadcastReverseRateLimit, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_S1RTCMACP_INUSE_UnicastReverseRateLimit */
		case 0x0002: {
			SETPRESENT_TMAC_S1RTCMACP_INUSE_Data (data, ID_MAC_S1RTCMACP_INUSE_MAC_S1RTCMACP_INUSE_UnicastReverseRateLimit);
			INIT_c_MAC_S1RTCMACP_INUSE_UnicastReverseRateLimit (data->Data.fld_c_MAC_S1RTCMACP_INUSE_UnicastReverseRateLimit);
			retLen = DECODE_c_MAC_S1RTCMACP_INUSE_UnicastReverseRateLimit (buffer, 0, data->Data.fld_c_MAC_S1RTCMACP_INUSE_UnicastReverseRateLimit, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_S1RTCMACP_INUSE_AttributeUpdateRequest */
		case 0x0052: {
			SETPRESENT_TMAC_S1RTCMACP_INUSE_Data (data, ID_MAC_S1RTCMACP_INUSE_MAC_S1RTCMACP_INUSE_AttributeUpdateRequest);
			INIT_c_MAC_S1RTCMACP_INUSE_AttributeUpdateRequest (data->Data.fld_c_MAC_S1RTCMACP_INUSE_AttributeUpdateRequest);
			retLen = DECODE_c_MAC_S1RTCMACP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_MAC_S1RTCMACP_INUSE_AttributeUpdateRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_S1RTCMACP_INUSE_AttributeUpdateAccept */
		case 0x0053: {
			SETPRESENT_TMAC_S1RTCMACP_INUSE_Data (data, ID_MAC_S1RTCMACP_INUSE_MAC_S1RTCMACP_INUSE_AttributeUpdateAccept);
			INIT_c_MAC_S1RTCMACP_INUSE_AttributeUpdateAccept (data->Data.fld_c_MAC_S1RTCMACP_INUSE_AttributeUpdateAccept);
			retLen = DECODE_c_MAC_S1RTCMACP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_MAC_S1RTCMACP_INUSE_AttributeUpdateAccept, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_S1RTCMACP_INUSE_AttributeUpdateReject */
		case 0x0054: {
			SETPRESENT_TMAC_S1RTCMACP_INUSE_Data (data, ID_MAC_S1RTCMACP_INUSE_MAC_S1RTCMACP_INUSE_AttributeUpdateReject);
			INIT_c_MAC_S1RTCMACP_INUSE_AttributeUpdateReject (data->Data.fld_c_MAC_S1RTCMACP_INUSE_AttributeUpdateReject);
			retLen = DECODE_c_MAC_S1RTCMACP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_MAC_S1RTCMACP_INUSE_AttributeUpdateReject, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_MAC_S1RTCMACP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_S1RTCMACP_INUSE (const char* buffer, int len, TMAC_S1RTCMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_MAC_S1RTCMACP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_MAC_S1RTCMACP_INUSE (char* buffer, ED_EXLONG bitOffset, TMAC_S1RTCMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_MAC_S1RTCMACP_INUSE_MAC_S1RTCMACP_INUSE_RTCAck: {
			retLen = ENCODE_c_MAC_S1RTCMACP_INUSE_RTCAck (buffer, 0, data->Data.fld_c_MAC_S1RTCMACP_INUSE_RTCAck, pCSN1CContextSet);
			break;
		}
		case ID_MAC_S1RTCMACP_INUSE_MAC_S1RTCMACP_INUSE_BroadcastReverseRateLimit: {
			retLen = ENCODE_c_MAC_S1RTCMACP_INUSE_BroadcastReverseRateLimit (buffer, 0, data->Data.fld_c_MAC_S1RTCMACP_INUSE_BroadcastReverseRateLimit, pCSN1CContextSet);
			break;
		}
		case ID_MAC_S1RTCMACP_INUSE_MAC_S1RTCMACP_INUSE_UnicastReverseRateLimit: {
			retLen = ENCODE_c_MAC_S1RTCMACP_INUSE_UnicastReverseRateLimit (buffer, 0, data->Data.fld_c_MAC_S1RTCMACP_INUSE_UnicastReverseRateLimit, pCSN1CContextSet);
			break;
		}
		case ID_MAC_S1RTCMACP_INUSE_MAC_S1RTCMACP_INUSE_AttributeUpdateRequest: {
			retLen = ENCODE_c_MAC_S1RTCMACP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_MAC_S1RTCMACP_INUSE_AttributeUpdateRequest, pCSN1CContextSet);
			break;
		}
		case ID_MAC_S1RTCMACP_INUSE_MAC_S1RTCMACP_INUSE_AttributeUpdateAccept: {
			retLen = ENCODE_c_MAC_S1RTCMACP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_MAC_S1RTCMACP_INUSE_AttributeUpdateAccept, pCSN1CContextSet);
			break;
		}
		case ID_MAC_S1RTCMACP_INUSE_MAC_S1RTCMACP_INUSE_AttributeUpdateReject: {
			retLen = ENCODE_c_MAC_S1RTCMACP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_MAC_S1RTCMACP_INUSE_AttributeUpdateReject, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_MAC_S3RTCMACP_INCFG (const char* buffer, TMAC_S3RTCMACP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal MAC_S3RTCMACP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TMAC_S3RTCMACP_INCFG_Data (data, ID_MAC_S3RTCMACP_INCFG_MAC_S3RTCMACP_INCFG_ConfigurationRequest);
			INIT_c_MAC_S3RTCMACP_INCFG_ConfigurationRequest (data->Data.fld_c_MAC_S3RTCMACP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_MAC_S3RTCMACP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_MAC_S3RTCMACP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_S3RTCMACP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TMAC_S3RTCMACP_INCFG_Data (data, ID_MAC_S3RTCMACP_INCFG_MAC_S3RTCMACP_INCFG_ConfigurationResponse);
			INIT_c_MAC_S3RTCMACP_INCFG_ConfigurationResponse (data->Data.fld_c_MAC_S3RTCMACP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_MAC_S3RTCMACP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_MAC_S3RTCMACP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_MAC_S3RTCMACP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_S3RTCMACP_INCFG (const char* buffer, int len, TMAC_S3RTCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_MAC_S3RTCMACP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_MAC_S3RTCMACP_INCFG (char* buffer, ED_EXLONG bitOffset, TMAC_S3RTCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_MAC_S3RTCMACP_INCFG_MAC_S3RTCMACP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_MAC_S3RTCMACP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_MAC_S3RTCMACP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_MAC_S3RTCMACP_INCFG_MAC_S3RTCMACP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_MAC_S3RTCMACP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_MAC_S3RTCMACP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_MAC_S3RTCMACP_INUSE (const char* buffer, TMAC_S3RTCMACP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal MAC_S3RTCMACP_INUSE_RTCAck */
		case 0x0000: {
			SETPRESENT_TMAC_S3RTCMACP_INUSE_Data (data, ID_MAC_S3RTCMACP_INUSE_MAC_S3RTCMACP_INUSE_RTCAck);
			INIT_c_MAC_S3RTCMACP_INUSE_RTCAck (data->Data.fld_c_MAC_S3RTCMACP_INUSE_RTCAck);
			retLen = DECODE_c_MAC_S3RTCMACP_INUSE_RTCAck (buffer, 0, data->Data.fld_c_MAC_S3RTCMACP_INUSE_RTCAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_S3RTCMACP_INUSE_Request */
		case 0x0002: {
			SETPRESENT_TMAC_S3RTCMACP_INUSE_Data (data, ID_MAC_S3RTCMACP_INUSE_MAC_S3RTCMACP_INUSE_Request);
			INIT_c_MAC_S3RTCMACP_INUSE_Request (data->Data.fld_c_MAC_S3RTCMACP_INUSE_Request);
			retLen = DECODE_c_MAC_S3RTCMACP_INUSE_Request (buffer, 0, data->Data.fld_c_MAC_S3RTCMACP_INUSE_Request, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_S3RTCMACP_INUSE_Grant */
		case 0x0003: {
			SETPRESENT_TMAC_S3RTCMACP_INUSE_Data (data, ID_MAC_S3RTCMACP_INUSE_MAC_S3RTCMACP_INUSE_Grant);
			INIT_c_MAC_S3RTCMACP_INUSE_Grant (data->Data.fld_c_MAC_S3RTCMACP_INUSE_Grant);
			retLen = DECODE_c_MAC_S3RTCMACP_INUSE_Grant (buffer, 0, data->Data.fld_c_MAC_S3RTCMACP_INUSE_Grant, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_S3RTCMACP_INUSE_AttributeUpdateRequest */
		case 0x0052: {
			SETPRESENT_TMAC_S3RTCMACP_INUSE_Data (data, ID_MAC_S3RTCMACP_INUSE_MAC_S3RTCMACP_INUSE_AttributeUpdateRequest);
			INIT_c_MAC_S3RTCMACP_INUSE_AttributeUpdateRequest (data->Data.fld_c_MAC_S3RTCMACP_INUSE_AttributeUpdateRequest);
			retLen = DECODE_c_MAC_S3RTCMACP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_MAC_S3RTCMACP_INUSE_AttributeUpdateRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_S3RTCMACP_INUSE_AttributeUpdateAccept */
		case 0x0053: {
			SETPRESENT_TMAC_S3RTCMACP_INUSE_Data (data, ID_MAC_S3RTCMACP_INUSE_MAC_S3RTCMACP_INUSE_AttributeUpdateAccept);
			INIT_c_MAC_S3RTCMACP_INUSE_AttributeUpdateAccept (data->Data.fld_c_MAC_S3RTCMACP_INUSE_AttributeUpdateAccept);
			retLen = DECODE_c_MAC_S3RTCMACP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_MAC_S3RTCMACP_INUSE_AttributeUpdateAccept, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_S3RTCMACP_INUSE_AttributeUpdateReject */
		case 0x0054: {
			SETPRESENT_TMAC_S3RTCMACP_INUSE_Data (data, ID_MAC_S3RTCMACP_INUSE_MAC_S3RTCMACP_INUSE_AttributeUpdateReject);
			INIT_c_MAC_S3RTCMACP_INUSE_AttributeUpdateReject (data->Data.fld_c_MAC_S3RTCMACP_INUSE_AttributeUpdateReject);
			retLen = DECODE_c_MAC_S3RTCMACP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_MAC_S3RTCMACP_INUSE_AttributeUpdateReject, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_MAC_S3RTCMACP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_S3RTCMACP_INUSE (const char* buffer, int len, TMAC_S3RTCMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_MAC_S3RTCMACP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_MAC_S3RTCMACP_INUSE (char* buffer, ED_EXLONG bitOffset, TMAC_S3RTCMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_MAC_S3RTCMACP_INUSE_MAC_S3RTCMACP_INUSE_RTCAck: {
			retLen = ENCODE_c_MAC_S3RTCMACP_INUSE_RTCAck (buffer, 0, data->Data.fld_c_MAC_S3RTCMACP_INUSE_RTCAck, pCSN1CContextSet);
			break;
		}
		case ID_MAC_S3RTCMACP_INUSE_MAC_S3RTCMACP_INUSE_Request: {
			retLen = ENCODE_c_MAC_S3RTCMACP_INUSE_Request (buffer, 0, data->Data.fld_c_MAC_S3RTCMACP_INUSE_Request, pCSN1CContextSet);
			break;
		}
		case ID_MAC_S3RTCMACP_INUSE_MAC_S3RTCMACP_INUSE_Grant: {
			retLen = ENCODE_c_MAC_S3RTCMACP_INUSE_Grant (buffer, 0, data->Data.fld_c_MAC_S3RTCMACP_INUSE_Grant, pCSN1CContextSet);
			break;
		}
		case ID_MAC_S3RTCMACP_INUSE_MAC_S3RTCMACP_INUSE_AttributeUpdateRequest: {
			retLen = ENCODE_c_MAC_S3RTCMACP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_MAC_S3RTCMACP_INUSE_AttributeUpdateRequest, pCSN1CContextSet);
			break;
		}
		case ID_MAC_S3RTCMACP_INUSE_MAC_S3RTCMACP_INUSE_AttributeUpdateAccept: {
			retLen = ENCODE_c_MAC_S3RTCMACP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_MAC_S3RTCMACP_INUSE_AttributeUpdateAccept, pCSN1CContextSet);
			break;
		}
		case ID_MAC_S3RTCMACP_INUSE_MAC_S3RTCMACP_INUSE_AttributeUpdateReject: {
			retLen = ENCODE_c_MAC_S3RTCMACP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_MAC_S3RTCMACP_INUSE_AttributeUpdateReject, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_MAC_MRTCMACP_INCFG (const char* buffer, TMAC_MRTCMACP_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal MAC_MRTCMACP_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TMAC_MRTCMACP_INCFG_Data (data, ID_MAC_MRTCMACP_INCFG_MAC_MRTCMACP_INCFG_ConfigurationRequest);
			INIT_c_MAC_MRTCMACP_INCFG_ConfigurationRequest (data->Data.fld_c_MAC_MRTCMACP_INCFG_ConfigurationRequest);
			retLen = DECODE_c_MAC_MRTCMACP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_MAC_MRTCMACP_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_MRTCMACP_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TMAC_MRTCMACP_INCFG_Data (data, ID_MAC_MRTCMACP_INCFG_MAC_MRTCMACP_INCFG_ConfigurationResponse);
			INIT_c_MAC_MRTCMACP_INCFG_ConfigurationResponse (data->Data.fld_c_MAC_MRTCMACP_INCFG_ConfigurationResponse);
			retLen = DECODE_c_MAC_MRTCMACP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_MAC_MRTCMACP_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_MAC_MRTCMACP_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_MRTCMACP_INCFG (const char* buffer, int len, TMAC_MRTCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_MAC_MRTCMACP_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_MAC_MRTCMACP_INCFG (char* buffer, ED_EXLONG bitOffset, TMAC_MRTCMACP_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_MAC_MRTCMACP_INCFG_MAC_MRTCMACP_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_MAC_MRTCMACP_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_MAC_MRTCMACP_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_MAC_MRTCMACP_INCFG_MAC_MRTCMACP_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_MAC_MRTCMACP_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_MAC_MRTCMACP_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_MAC_MRTCMACP_INUSE (const char* buffer, TMAC_MRTCMACP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal MAC_MRTCMACP_INUSE_RTCAck */
		case 0x0000: {
			SETPRESENT_TMAC_MRTCMACP_INUSE_Data (data, ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_RTCAck);
			INIT_c_MAC_MRTCMACP_INUSE_RTCAck (data->Data.fld_c_MAC_MRTCMACP_INUSE_RTCAck);
			retLen = DECODE_c_MAC_MRTCMACP_INUSE_RTCAck (buffer, 0, data->Data.fld_c_MAC_MRTCMACP_INUSE_RTCAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_MRTCMACP_INUSE_CarrierRequest */
		case 0x0004: {
			SETPRESENT_TMAC_MRTCMACP_INUSE_Data (data, ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_CarrierRequest);
			INIT_c_MAC_MRTCMACP_INUSE_CarrierRequest (data->Data.fld_c_MAC_MRTCMACP_INUSE_CarrierRequest);
			retLen = DECODE_c_MAC_MRTCMACP_INUSE_CarrierRequest (buffer, 0, data->Data.fld_c_MAC_MRTCMACP_INUSE_CarrierRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped */
		case 0x0005: {
			SETPRESENT_TMAC_MRTCMACP_INUSE_Data (data, ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped);
			INIT_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped (data->Data.fld_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped);
			retLen = DECODE_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped (buffer, 0, data->Data.fld_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck */
		case 0x0006: {
			SETPRESENT_TMAC_MRTCMACP_INUSE_Data (data, ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck);
			INIT_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck (data->Data.fld_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck);
			retLen = DECODE_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck (buffer, 0, data->Data.fld_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_MRTCMACP_INUSE_Request */
		case 0x0002: {
			SETPRESENT_TMAC_MRTCMACP_INUSE_Data (data, ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_Request);
			INIT_c_MAC_MRTCMACP_INUSE_Request (data->Data.fld_c_MAC_MRTCMACP_INUSE_Request);
			retLen = DECODE_c_MAC_MRTCMACP_INUSE_Request (buffer, 0, data->Data.fld_c_MAC_MRTCMACP_INUSE_Request, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_MRTCMACP_INUSE_Grant */
		case 0x0003: {
			SETPRESENT_TMAC_MRTCMACP_INUSE_Data (data, ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_Grant);
			INIT_c_MAC_MRTCMACP_INUSE_Grant (data->Data.fld_c_MAC_MRTCMACP_INUSE_Grant);
			retLen = DECODE_c_MAC_MRTCMACP_INUSE_Grant (buffer, 0, data->Data.fld_c_MAC_MRTCMACP_INUSE_Grant, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_MRTCMACP_INUSE_AttributeUpdateRequest */
		case 0x0052: {
			SETPRESENT_TMAC_MRTCMACP_INUSE_Data (data, ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_AttributeUpdateRequest);
			INIT_c_MAC_MRTCMACP_INUSE_AttributeUpdateRequest (data->Data.fld_c_MAC_MRTCMACP_INUSE_AttributeUpdateRequest);
			retLen = DECODE_c_MAC_MRTCMACP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_MAC_MRTCMACP_INUSE_AttributeUpdateRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_MRTCMACP_INUSE_AttributeUpdateAccept */
		case 0x0053: {
			SETPRESENT_TMAC_MRTCMACP_INUSE_Data (data, ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_AttributeUpdateAccept);
			INIT_c_MAC_MRTCMACP_INUSE_AttributeUpdateAccept (data->Data.fld_c_MAC_MRTCMACP_INUSE_AttributeUpdateAccept);
			retLen = DECODE_c_MAC_MRTCMACP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_MAC_MRTCMACP_INUSE_AttributeUpdateAccept, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MAC_MRTCMACP_INUSE_AttributeUpdateReject */
		case 0x0054: {
			SETPRESENT_TMAC_MRTCMACP_INUSE_Data (data, ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_AttributeUpdateReject);
			INIT_c_MAC_MRTCMACP_INUSE_AttributeUpdateReject (data->Data.fld_c_MAC_MRTCMACP_INUSE_AttributeUpdateReject);
			retLen = DECODE_c_MAC_MRTCMACP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_MAC_MRTCMACP_INUSE_AttributeUpdateReject, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_MAC_MRTCMACP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MAC_MRTCMACP_INUSE (const char* buffer, int len, TMAC_MRTCMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_MAC_MRTCMACP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_MAC_MRTCMACP_INUSE (char* buffer, ED_EXLONG bitOffset, TMAC_MRTCMACP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_RTCAck: {
			retLen = ENCODE_c_MAC_MRTCMACP_INUSE_RTCAck (buffer, 0, data->Data.fld_c_MAC_MRTCMACP_INUSE_RTCAck, pCSN1CContextSet);
			break;
		}
		case ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_CarrierRequest: {
			retLen = ENCODE_c_MAC_MRTCMACP_INUSE_CarrierRequest (buffer, 0, data->Data.fld_c_MAC_MRTCMACP_INUSE_CarrierRequest, pCSN1CContextSet);
			break;
		}
		case ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped: {
			retLen = ENCODE_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped (buffer, 0, data->Data.fld_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDropped, pCSN1CContextSet);
			break;
		}
		case ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck: {
			retLen = ENCODE_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck (buffer, 0, data->Data.fld_c_MAC_MRTCMACP_INUSE_ReverseCDMAChannelDroppedAck, pCSN1CContextSet);
			break;
		}
		case ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_Request: {
			retLen = ENCODE_c_MAC_MRTCMACP_INUSE_Request (buffer, 0, data->Data.fld_c_MAC_MRTCMACP_INUSE_Request, pCSN1CContextSet);
			break;
		}
		case ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_Grant: {
			retLen = ENCODE_c_MAC_MRTCMACP_INUSE_Grant (buffer, 0, data->Data.fld_c_MAC_MRTCMACP_INUSE_Grant, pCSN1CContextSet);
			break;
		}
		case ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_AttributeUpdateRequest: {
			retLen = ENCODE_c_MAC_MRTCMACP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_MAC_MRTCMACP_INUSE_AttributeUpdateRequest, pCSN1CContextSet);
			break;
		}
		case ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_AttributeUpdateAccept: {
			retLen = ENCODE_c_MAC_MRTCMACP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_MAC_MRTCMACP_INUSE_AttributeUpdateAccept, pCSN1CContextSet);
			break;
		}
		case ID_MAC_MRTCMACP_INUSE_MAC_MRTCMACP_INUSE_AttributeUpdateReject: {
			retLen = ENCODE_c_MAC_MRTCMACP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_MAC_MRTCMACP_INUSE_AttributeUpdateReject, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_PHYS01_DS0S1PLPI_INCFG (const char* buffer, TPHYS01_DS0S1PLPI_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal PHYS01_DS0S1PLPI_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TPHYS01_DS0S1PLPI_INCFG_Data (data, ID_PHYS01_DS0S1PLPI_INCFG_PHYS01_DS0S1PLPI_INCFG_ConfigurationRequest);
			INIT_c_PHYS01_DS0S1PLPI_INCFG_ConfigurationRequest (data->Data.fld_c_PHYS01_DS0S1PLPI_INCFG_ConfigurationRequest);
			retLen = DECODE_c_PHYS01_DS0S1PLPI_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_PHYS01_DS0S1PLPI_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal PHYS01_DS0S1PLPI_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TPHYS01_DS0S1PLPI_INCFG_Data (data, ID_PHYS01_DS0S1PLPI_INCFG_PHYS01_DS0S1PLPI_INCFG_ConfigurationResponse);
			INIT_c_PHYS01_DS0S1PLPI_INCFG_ConfigurationResponse (data->Data.fld_c_PHYS01_DS0S1PLPI_INCFG_ConfigurationResponse);
			retLen = DECODE_c_PHYS01_DS0S1PLPI_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_PHYS01_DS0S1PLPI_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_PHYS01_DS0S1PLPI_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_PHYS01_DS0S1PLPI_INCFG (const char* buffer, int len, TPHYS01_DS0S1PLPI_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_PHYS01_DS0S1PLPI_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_PHYS01_DS0S1PLPI_INCFG (char* buffer, ED_EXLONG bitOffset, TPHYS01_DS0S1PLPI_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_PHYS01_DS0S1PLPI_INCFG_PHYS01_DS0S1PLPI_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_PHYS01_DS0S1PLPI_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_PHYS01_DS0S1PLPI_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_PHYS01_DS0S1PLPI_INCFG_PHYS01_DS0S1PLPI_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_PHYS01_DS0S1PLPI_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_PHYS01_DS0S1PLPI_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_PHYS2_S2PLPI_INCFG (const char* buffer, TPHYS2_S2PLPI_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal PHYS2_S2PLPI_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TPHYS2_S2PLPI_INCFG_Data (data, ID_PHYS2_S2PLPI_INCFG_PHYS2_S2PLPI_INCFG_ConfigurationRequest);
			INIT_c_PHYS2_S2PLPI_INCFG_ConfigurationRequest (data->Data.fld_c_PHYS2_S2PLPI_INCFG_ConfigurationRequest);
			retLen = DECODE_c_PHYS2_S2PLPI_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_PHYS2_S2PLPI_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal PHYS2_S2PLPI_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TPHYS2_S2PLPI_INCFG_Data (data, ID_PHYS2_S2PLPI_INCFG_PHYS2_S2PLPI_INCFG_ConfigurationResponse);
			INIT_c_PHYS2_S2PLPI_INCFG_ConfigurationResponse (data->Data.fld_c_PHYS2_S2PLPI_INCFG_ConfigurationResponse);
			retLen = DECODE_c_PHYS2_S2PLPI_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_PHYS2_S2PLPI_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_PHYS2_S2PLPI_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_PHYS2_S2PLPI_INCFG (const char* buffer, int len, TPHYS2_S2PLPI_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_PHYS2_S2PLPI_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_PHYS2_S2PLPI_INCFG (char* buffer, ED_EXLONG bitOffset, TPHYS2_S2PLPI_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_PHYS2_S2PLPI_INCFG_PHYS2_S2PLPI_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_PHYS2_S2PLPI_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_PHYS2_S2PLPI_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_PHYS2_S2PLPI_INCFG_PHYS2_S2PLPI_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_PHYS2_S2PLPI_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_PHYS2_S2PLPI_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_PHYS3_S3PLPI_INCFG (const char* buffer, TPHYS3_S3PLPI_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal PHYS3_S3PLPI_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TPHYS3_S3PLPI_INCFG_Data (data, ID_PHYS3_S3PLPI_INCFG_PHYS3_S3PLPI_INCFG_ConfigurationRequest);
			INIT_c_PHYS3_S3PLPI_INCFG_ConfigurationRequest (data->Data.fld_c_PHYS3_S3PLPI_INCFG_ConfigurationRequest);
			retLen = DECODE_c_PHYS3_S3PLPI_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_PHYS3_S3PLPI_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal PHYS3_S3PLPI_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TPHYS3_S3PLPI_INCFG_Data (data, ID_PHYS3_S3PLPI_INCFG_PHYS3_S3PLPI_INCFG_ConfigurationResponse);
			INIT_c_PHYS3_S3PLPI_INCFG_ConfigurationResponse (data->Data.fld_c_PHYS3_S3PLPI_INCFG_ConfigurationResponse);
			retLen = DECODE_c_PHYS3_S3PLPI_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_PHYS3_S3PLPI_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_PHYS3_S3PLPI_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_PHYS3_S3PLPI_INCFG (const char* buffer, int len, TPHYS3_S3PLPI_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_PHYS3_S3PLPI_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_PHYS3_S3PLPI_INCFG (char* buffer, ED_EXLONG bitOffset, TPHYS3_S3PLPI_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_PHYS3_S3PLPI_INCFG_PHYS3_S3PLPI_INCFG_ConfigurationRequest: {
			retLen = ENCODE_c_PHYS3_S3PLPI_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_PHYS3_S3PLPI_INCFG_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_PHYS3_S3PLPI_INCFG_PHYS3_S3PLPI_INCFG_ConfigurationResponse: {
			retLen = ENCODE_c_PHYS3_S3PLPI_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_PHYS3_S3PLPI_INCFG_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_PHYS3_S3PLPI_INUSE (const char* buffer, TPHYS3_S3PLPI_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal PHYS3_S3PLPI_INUSE_AttributeUpdateRequest */
		case 0x0052: {
			SETPRESENT_TPHYS3_S3PLPI_INUSE_Data (data, ID_PHYS3_S3PLPI_INUSE_PHYS3_S3PLPI_INUSE_AttributeUpdateRequest);
			INIT_c_PHYS3_S3PLPI_INUSE_AttributeUpdateRequest (data->Data.fld_c_PHYS3_S3PLPI_INUSE_AttributeUpdateRequest);
			retLen = DECODE_c_PHYS3_S3PLPI_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_PHYS3_S3PLPI_INUSE_AttributeUpdateRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal PHYS3_S3PLPI_INUSE_AttributeUpdateAccept */
		case 0x0053: {
			SETPRESENT_TPHYS3_S3PLPI_INUSE_Data (data, ID_PHYS3_S3PLPI_INUSE_PHYS3_S3PLPI_INUSE_AttributeUpdateAccept);
			INIT_c_PHYS3_S3PLPI_INUSE_AttributeUpdateAccept (data->Data.fld_c_PHYS3_S3PLPI_INUSE_AttributeUpdateAccept);
			retLen = DECODE_c_PHYS3_S3PLPI_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_PHYS3_S3PLPI_INUSE_AttributeUpdateAccept, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal PHYS3_S3PLPI_INUSE_AttributeUpdateReject */
		case 0x0054: {
			SETPRESENT_TPHYS3_S3PLPI_INUSE_Data (data, ID_PHYS3_S3PLPI_INUSE_PHYS3_S3PLPI_INUSE_AttributeUpdateReject);
			INIT_c_PHYS3_S3PLPI_INUSE_AttributeUpdateReject (data->Data.fld_c_PHYS3_S3PLPI_INUSE_AttributeUpdateReject);
			retLen = DECODE_c_PHYS3_S3PLPI_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_PHYS3_S3PLPI_INUSE_AttributeUpdateReject, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_PHYS3_S3PLPI_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_PHYS3_S3PLPI_INUSE (const char* buffer, int len, TPHYS3_S3PLPI_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_PHYS3_S3PLPI_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_PHYS3_S3PLPI_INUSE (char* buffer, ED_EXLONG bitOffset, TPHYS3_S3PLPI_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_PHYS3_S3PLPI_INUSE_PHYS3_S3PLPI_INUSE_AttributeUpdateRequest: {
			retLen = ENCODE_c_PHYS3_S3PLPI_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_PHYS3_S3PLPI_INUSE_AttributeUpdateRequest, pCSN1CContextSet);
			break;
		}
		case ID_PHYS3_S3PLPI_INUSE_PHYS3_S3PLPI_INUSE_AttributeUpdateAccept: {
			retLen = ENCODE_c_PHYS3_S3PLPI_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_PHYS3_S3PLPI_INUSE_AttributeUpdateAccept, pCSN1CContextSet);
			break;
		}
		case ID_PHYS3_S3PLPI_INUSE_PHYS3_S3PLPI_INUSE_AttributeUpdateReject: {
			retLen = ENCODE_c_PHYS3_S3PLPI_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_PHYS3_S3PLPI_INUSE_AttributeUpdateReject, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_GEN_GCP (const char* buffer, TGEN_GCP_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal GEN_GCP_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TGEN_GCP_Data (data, ID_GEN_GCP_GEN_GCP_ConfigurationRequest);
			INIT_c_GEN_GCP_ConfigurationRequest (data->Data.fld_c_GEN_GCP_ConfigurationRequest);
			retLen = DECODE_c_GEN_GCP_ConfigurationRequest (buffer, 0, data->Data.fld_c_GEN_GCP_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal GEN_GCP_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TGEN_GCP_Data (data, ID_GEN_GCP_GEN_GCP_ConfigurationResponse);
			INIT_c_GEN_GCP_ConfigurationResponse (data->Data.fld_c_GEN_GCP_ConfigurationResponse);
			retLen = DECODE_c_GEN_GCP_ConfigurationResponse (buffer, 0, data->Data.fld_c_GEN_GCP_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_GEN_GCP_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_GEN_GCP (const char* buffer, int len, TGEN_GCP_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_GEN_GCP (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_GEN_GCP (char* buffer, ED_EXLONG bitOffset, TGEN_GCP_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_GEN_GCP_GEN_GCP_ConfigurationRequest: {
			retLen = ENCODE_c_GEN_GCP_ConfigurationRequest (buffer, 0, data->Data.fld_c_GEN_GCP_ConfigurationRequest, pCSN1CContextSet);
			break;
		}
		case ID_GEN_GCP_GEN_GCP_ConfigurationResponse: {
			retLen = ENCODE_c_GEN_GCP_ConfigurationResponse (buffer, 0, data->Data.fld_c_GEN_GCP_ConfigurationResponse, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}
#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_GEN_GAUP (const char* buffer, TGEN_GAUP_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal GEN_GAUP_AttributeUpdateRequest */
		case 0x0052: {
			SETPRESENT_TGEN_GAUP_Data (data, ID_GEN_GAUP_GEN_GAUP_AttributeUpdateRequest);
			INIT_c_GEN_GAUP_AttributeUpdateRequest (data->Data.fld_c_GEN_GAUP_AttributeUpdateRequest);
			retLen = DECODE_c_GEN_GAUP_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_GEN_GAUP_AttributeUpdateRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal GEN_GAUP_AttributeUpdateAccept */
		case 0x0053: {
			SETPRESENT_TGEN_GAUP_Data (data, ID_GEN_GAUP_GEN_GAUP_AttributeUpdateAccept);
			INIT_c_GEN_GAUP_AttributeUpdateAccept (data->Data.fld_c_GEN_GAUP_AttributeUpdateAccept);
			retLen = DECODE_c_GEN_GAUP_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_GEN_GAUP_AttributeUpdateAccept, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal GEN_GAUP_AttributeUpdateReject */
		case 0x0054: {
			SETPRESENT_TGEN_GAUP_Data (data, ID_GEN_GAUP_GEN_GAUP_AttributeUpdateReject);
			INIT_c_GEN_GAUP_AttributeUpdateReject (data->Data.fld_c_GEN_GAUP_AttributeUpdateReject);
			retLen = DECODE_c_GEN_GAUP_AttributeUpdateReject (buffer, 0, data->Data.fld_c_GEN_GAUP_AttributeUpdateReject, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_GEN_GAUP_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_GEN_GAUP (const char* buffer, int len, TGEN_GAUP_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_GEN_GAUP (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

/* Set encoder */
int SetEncode_GEN_GAUP (char* buffer, ED_EXLONG bitOffset, TGEN_GAUP_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
{
	int retLen = ED_UNKNOWN_MESSAGE;
	ED_WARNING_REMOVER(bitOffset);
	
	switch (data->Type) {
		case ID_GEN_GAUP_GEN_GAUP_AttributeUpdateRequest: {
			retLen = ENCODE_c_GEN_GAUP_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_GEN_GAUP_AttributeUpdateRequest, pCSN1CContextSet);
			break;
		}
		case ID_GEN_GAUP_GEN_GAUP_AttributeUpdateAccept: {
			retLen = ENCODE_c_GEN_GAUP_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_GEN_GAUP_AttributeUpdateAccept, pCSN1CContextSet);
			break;
		}
		case ID_GEN_GAUP_GEN_GAUP_AttributeUpdateReject: {
			retLen = ENCODE_c_GEN_GAUP_AttributeUpdateReject (buffer, 0, data->Data.fld_c_GEN_GAUP_AttributeUpdateReject, pCSN1CContextSet);
			break;
		}

		default:;
	}
	return retLen;
}

