/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c-recog
	http://www.Dafocus.it/
**************************************************************************/
/*lint -e959 -e530 -e774 -e572 -e778 -e525 -e539 -e701 -e123 -e438 -e119 -e506 -e529 -e550 -e666 -e713 -e719 -e730 -e734 -e744 -e801 -e801 -e813 -e830 -e40 -e10 -e52 -e63 -e115 -e409 -e118 -e49 -e718 -e746 -e737 -e760 -e830 */
#define ENCODIX_CS0063

#include "ed_c_recog_cs0063.h"
#include "ed_lib.h"
#include "EMFPKA_EMFPA_INCFG_cs0063.h"
#include "EMFPKA_RSP_INUSE_cs0063.h"
#include "EMFPKA_RLP_INUSE_cs0063.h"
#include "EMFPKA_DOSP_INUSE_cs0063.h"
#include "EMFPKA_LUP_INUSE_cs0063.h"
#include "EMFPKA_FCP_INUSE_cs0063.h"
#include "MLMFPA_MMFPA_INCFG_cs0063.h"
#include "MLMFPA_RSP_INUSE_cs0063.h"
#include "MLMFPA_SRP_INUSE_cs0063.h"
#include "MLMFPA_DOSP_INUSE_cs0063.h"
#include "MLMFPA_LUP_INUSE_cs0063.h"
#include "MLMFPA_FCP_INUSE_cs0063.h"
#if ED_COMMON_CRC != 0x328E3625 && ED_VERSION != 10152 && ED_VERSION != 10153
#error Invalid Encodix library files linked; used those distributed with Encodix 1.0.154
#endif


void SETPRESENT_TEMFPKA_EMFPA_INCFG_Data (TEMFPKA_EMFPA_INCFG_Data* sp, TEMFPKA_EMFPA_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TEMFPKA_EMFPA_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_EMFPKA_EMFPA_INCFG_EMFPKA_EMFPA_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest = (c_EMFPKA_EMFPA_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_EMFPKA_EMFPA_INCFG_ConfigurationRequest));
			INIT_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest (sp->Data.fld_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_EMFPKA_EMFPA_INCFG_EMFPKA_EMFPA_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse = (c_EMFPKA_EMFPA_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_EMFPKA_EMFPA_INCFG_ConfigurationResponse));
			INIT_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse (sp->Data.fld_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TEMFPKA_EMFPA_INCFG_Data (TEMFPKA_EMFPA_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_EMFPKA_EMFPA_INCFG_EMFPKA_EMFPA_INCFG_ConfigurationRequest: {
			FREE_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest (sp->Data.fld_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_EMFPKA_EMFPA_INCFG_EMFPKA_EMFPA_INCFG_ConfigurationResponse: {
			FREE_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse (sp->Data.fld_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_EMFPKA_EMFPA_INCFG_Unrecognized;
}

void SETPRESENT_TEMFPKA_RSP_INUSE_Data (TEMFPKA_RSP_INUSE_Data* sp, TEMFPKA_RSP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TEMFPKA_RSP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_EMFPKA_RSP_INUSE_EMFPKA_RSP_INUSE_RouteSelect: {
			sp->Data.fld_c_EMFPKA_RSP_INUSE_RouteSelect = (c_EMFPKA_RSP_INUSE_RouteSelect*)EDAlloc (sizeof (c_EMFPKA_RSP_INUSE_RouteSelect));
			INIT_c_EMFPKA_RSP_INUSE_RouteSelect (sp->Data.fld_c_EMFPKA_RSP_INUSE_RouteSelect);
			break;
		}
		
		case ID_EMFPKA_RSP_INUSE_EMFPKA_RSP_INUSE_RouteSelectAck: {
			sp->Data.fld_c_EMFPKA_RSP_INUSE_RouteSelectAck = (c_EMFPKA_RSP_INUSE_RouteSelectAck*)EDAlloc (sizeof (c_EMFPKA_RSP_INUSE_RouteSelectAck));
			INIT_c_EMFPKA_RSP_INUSE_RouteSelectAck (sp->Data.fld_c_EMFPKA_RSP_INUSE_RouteSelectAck);
			break;
		}
		
		case ID_EMFPKA_RSP_INUSE_EMFPKA_RSP_INUSE_ActivateRoute: {
			sp->Data.fld_c_EMFPKA_RSP_INUSE_ActivateRoute = (c_EMFPKA_RSP_INUSE_ActivateRoute*)EDAlloc (sizeof (c_EMFPKA_RSP_INUSE_ActivateRoute));
			INIT_c_EMFPKA_RSP_INUSE_ActivateRoute (sp->Data.fld_c_EMFPKA_RSP_INUSE_ActivateRoute);
			break;
		}
		
		case ID_EMFPKA_RSP_INUSE_EMFPKA_RSP_INUSE_ActivateRouteAck: {
			sp->Data.fld_c_EMFPKA_RSP_INUSE_ActivateRouteAck = (c_EMFPKA_RSP_INUSE_ActivateRouteAck*)EDAlloc (sizeof (c_EMFPKA_RSP_INUSE_ActivateRouteAck));
			INIT_c_EMFPKA_RSP_INUSE_ActivateRouteAck (sp->Data.fld_c_EMFPKA_RSP_INUSE_ActivateRouteAck);
			break;
		}
		
		default:;
	}
}

void FREE_TEMFPKA_RSP_INUSE_Data (TEMFPKA_RSP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_EMFPKA_RSP_INUSE_EMFPKA_RSP_INUSE_RouteSelect: {
			FREE_c_EMFPKA_RSP_INUSE_RouteSelect (sp->Data.fld_c_EMFPKA_RSP_INUSE_RouteSelect);
	EDFree (sp->Data.fld_c_EMFPKA_RSP_INUSE_RouteSelect );
			break;
		}
		
		case ID_EMFPKA_RSP_INUSE_EMFPKA_RSP_INUSE_RouteSelectAck: {
			FREE_c_EMFPKA_RSP_INUSE_RouteSelectAck (sp->Data.fld_c_EMFPKA_RSP_INUSE_RouteSelectAck);
	EDFree (sp->Data.fld_c_EMFPKA_RSP_INUSE_RouteSelectAck );
			break;
		}
		
		case ID_EMFPKA_RSP_INUSE_EMFPKA_RSP_INUSE_ActivateRoute: {
			FREE_c_EMFPKA_RSP_INUSE_ActivateRoute (sp->Data.fld_c_EMFPKA_RSP_INUSE_ActivateRoute);
	EDFree (sp->Data.fld_c_EMFPKA_RSP_INUSE_ActivateRoute );
			break;
		}
		
		case ID_EMFPKA_RSP_INUSE_EMFPKA_RSP_INUSE_ActivateRouteAck: {
			FREE_c_EMFPKA_RSP_INUSE_ActivateRouteAck (sp->Data.fld_c_EMFPKA_RSP_INUSE_ActivateRouteAck);
	EDFree (sp->Data.fld_c_EMFPKA_RSP_INUSE_ActivateRouteAck );
			break;
		}
		
		default:;
	}

	sp->Type = ID_EMFPKA_RSP_INUSE_Unrecognized;
}

void SETPRESENT_TEMFPKA_RLP_INUSE_Data (TEMFPKA_RLP_INUSE_Data* sp, TEMFPKA_RLP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TEMFPKA_RLP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ResetTxIndication: {
			sp->Data.fld_c_EMFPKA_RLP_INUSE_ResetTxIndication = (c_EMFPKA_RLP_INUSE_ResetTxIndication*)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_ResetTxIndication));
			INIT_c_EMFPKA_RLP_INUSE_ResetTxIndication (sp->Data.fld_c_EMFPKA_RLP_INUSE_ResetTxIndication);
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ResetRxIndication: {
			sp->Data.fld_c_EMFPKA_RLP_INUSE_ResetRxIndication = (c_EMFPKA_RLP_INUSE_ResetRxIndication*)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_ResetRxIndication));
			INIT_c_EMFPKA_RLP_INUSE_ResetRxIndication (sp->Data.fld_c_EMFPKA_RLP_INUSE_ResetRxIndication);
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ResetTxIndicationAck: {
			sp->Data.fld_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck = (c_EMFPKA_RLP_INUSE_ResetTxIndicationAck*)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_ResetTxIndicationAck));
			INIT_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck (sp->Data.fld_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck);
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ResetTxComplete: {
			sp->Data.fld_c_EMFPKA_RLP_INUSE_ResetTxComplete = (c_EMFPKA_RLP_INUSE_ResetTxComplete*)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_ResetTxComplete));
			INIT_c_EMFPKA_RLP_INUSE_ResetTxComplete (sp->Data.fld_c_EMFPKA_RLP_INUSE_ResetTxComplete);
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ResetRxComplete: {
			sp->Data.fld_c_EMFPKA_RLP_INUSE_ResetRxComplete = (c_EMFPKA_RLP_INUSE_ResetRxComplete*)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_ResetRxComplete));
			INIT_c_EMFPKA_RLP_INUSE_ResetRxComplete (sp->Data.fld_c_EMFPKA_RLP_INUSE_ResetRxComplete);
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_Nak: {
			sp->Data.fld_c_EMFPKA_RLP_INUSE_Nak = (c_EMFPKA_RLP_INUSE_Nak*)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_Nak));
			INIT_c_EMFPKA_RLP_INUSE_Nak (sp->Data.fld_c_EMFPKA_RLP_INUSE_Nak);
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ReservationOnRequest: {
			sp->Data.fld_c_EMFPKA_RLP_INUSE_ReservationOnRequest = (c_EMFPKA_RLP_INUSE_ReservationOnRequest*)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_ReservationOnRequest));
			INIT_c_EMFPKA_RLP_INUSE_ReservationOnRequest (sp->Data.fld_c_EMFPKA_RLP_INUSE_ReservationOnRequest);
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ReservationOffRequest: {
			sp->Data.fld_c_EMFPKA_RLP_INUSE_ReservationOffRequest = (c_EMFPKA_RLP_INUSE_ReservationOffRequest*)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_ReservationOffRequest));
			INIT_c_EMFPKA_RLP_INUSE_ReservationOffRequest (sp->Data.fld_c_EMFPKA_RLP_INUSE_ReservationOffRequest);
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ReservationAccept: {
			sp->Data.fld_c_EMFPKA_RLP_INUSE_ReservationAccept = (c_EMFPKA_RLP_INUSE_ReservationAccept*)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_ReservationAccept));
			INIT_c_EMFPKA_RLP_INUSE_ReservationAccept (sp->Data.fld_c_EMFPKA_RLP_INUSE_ReservationAccept);
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ReservationReject: {
			sp->Data.fld_c_EMFPKA_RLP_INUSE_ReservationReject = (c_EMFPKA_RLP_INUSE_ReservationReject*)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_ReservationReject));
			INIT_c_EMFPKA_RLP_INUSE_ReservationReject (sp->Data.fld_c_EMFPKA_RLP_INUSE_ReservationReject);
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_RevReservationOn: {
			sp->Data.fld_c_EMFPKA_RLP_INUSE_RevReservationOn = (c_EMFPKA_RLP_INUSE_RevReservationOn*)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_RevReservationOn));
			INIT_c_EMFPKA_RLP_INUSE_RevReservationOn (sp->Data.fld_c_EMFPKA_RLP_INUSE_RevReservationOn);
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_RevReservationOff: {
			sp->Data.fld_c_EMFPKA_RLP_INUSE_RevReservationOff = (c_EMFPKA_RLP_INUSE_RevReservationOff*)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_RevReservationOff));
			INIT_c_EMFPKA_RLP_INUSE_RevReservationOff (sp->Data.fld_c_EMFPKA_RLP_INUSE_RevReservationOff);
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_FwdReservationOff: {
			sp->Data.fld_c_EMFPKA_RLP_INUSE_FwdReservationOff = (c_EMFPKA_RLP_INUSE_FwdReservationOff*)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_FwdReservationOff));
			INIT_c_EMFPKA_RLP_INUSE_FwdReservationOff (sp->Data.fld_c_EMFPKA_RLP_INUSE_FwdReservationOff);
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_FwdReservationOn: {
			sp->Data.fld_c_EMFPKA_RLP_INUSE_FwdReservationOn = (c_EMFPKA_RLP_INUSE_FwdReservationOn*)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_FwdReservationOn));
			INIT_c_EMFPKA_RLP_INUSE_FwdReservationOn (sp->Data.fld_c_EMFPKA_RLP_INUSE_FwdReservationOn);
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_FwdReservationAck: {
			sp->Data.fld_c_EMFPKA_RLP_INUSE_FwdReservationAck = (c_EMFPKA_RLP_INUSE_FwdReservationAck*)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_FwdReservationAck));
			INIT_c_EMFPKA_RLP_INUSE_FwdReservationAck (sp->Data.fld_c_EMFPKA_RLP_INUSE_FwdReservationAck);
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_AttributeUpdateRequest: {
			sp->Data.fld_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest = (c_EMFPKA_RLP_INUSE_AttributeUpdateRequest*)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_AttributeUpdateRequest));
			INIT_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest);
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_AttributeUpdateAccept: {
			sp->Data.fld_c_EMFPKA_RLP_INUSE_AttributeUpdateAccept = (c_EMFPKA_RLP_INUSE_AttributeUpdateAccept*)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_AttributeUpdateAccept));
			INIT_c_EMFPKA_RLP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_EMFPKA_RLP_INUSE_AttributeUpdateAccept);
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_AttributeUpdateReject: {
			sp->Data.fld_c_EMFPKA_RLP_INUSE_AttributeUpdateReject = (c_EMFPKA_RLP_INUSE_AttributeUpdateReject*)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_AttributeUpdateReject));
			INIT_c_EMFPKA_RLP_INUSE_AttributeUpdateReject (sp->Data.fld_c_EMFPKA_RLP_INUSE_AttributeUpdateReject);
			break;
		}
		
		default:;
	}
}

void FREE_TEMFPKA_RLP_INUSE_Data (TEMFPKA_RLP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ResetTxIndication: {
			FREE_c_EMFPKA_RLP_INUSE_ResetTxIndication (sp->Data.fld_c_EMFPKA_RLP_INUSE_ResetTxIndication);
	EDFree (sp->Data.fld_c_EMFPKA_RLP_INUSE_ResetTxIndication );
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ResetRxIndication: {
			FREE_c_EMFPKA_RLP_INUSE_ResetRxIndication (sp->Data.fld_c_EMFPKA_RLP_INUSE_ResetRxIndication);
	EDFree (sp->Data.fld_c_EMFPKA_RLP_INUSE_ResetRxIndication );
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ResetTxIndicationAck: {
			FREE_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck (sp->Data.fld_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck);
	EDFree (sp->Data.fld_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck );
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ResetTxComplete: {
			FREE_c_EMFPKA_RLP_INUSE_ResetTxComplete (sp->Data.fld_c_EMFPKA_RLP_INUSE_ResetTxComplete);
	EDFree (sp->Data.fld_c_EMFPKA_RLP_INUSE_ResetTxComplete );
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ResetRxComplete: {
			FREE_c_EMFPKA_RLP_INUSE_ResetRxComplete (sp->Data.fld_c_EMFPKA_RLP_INUSE_ResetRxComplete);
	EDFree (sp->Data.fld_c_EMFPKA_RLP_INUSE_ResetRxComplete );
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_Nak: {
			FREE_c_EMFPKA_RLP_INUSE_Nak (sp->Data.fld_c_EMFPKA_RLP_INUSE_Nak);
	EDFree (sp->Data.fld_c_EMFPKA_RLP_INUSE_Nak );
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ReservationOnRequest: {
			FREE_c_EMFPKA_RLP_INUSE_ReservationOnRequest (sp->Data.fld_c_EMFPKA_RLP_INUSE_ReservationOnRequest);
	EDFree (sp->Data.fld_c_EMFPKA_RLP_INUSE_ReservationOnRequest );
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ReservationOffRequest: {
			FREE_c_EMFPKA_RLP_INUSE_ReservationOffRequest (sp->Data.fld_c_EMFPKA_RLP_INUSE_ReservationOffRequest);
	EDFree (sp->Data.fld_c_EMFPKA_RLP_INUSE_ReservationOffRequest );
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ReservationAccept: {
			FREE_c_EMFPKA_RLP_INUSE_ReservationAccept (sp->Data.fld_c_EMFPKA_RLP_INUSE_ReservationAccept);
	EDFree (sp->Data.fld_c_EMFPKA_RLP_INUSE_ReservationAccept );
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ReservationReject: {
			FREE_c_EMFPKA_RLP_INUSE_ReservationReject (sp->Data.fld_c_EMFPKA_RLP_INUSE_ReservationReject);
	EDFree (sp->Data.fld_c_EMFPKA_RLP_INUSE_ReservationReject );
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_RevReservationOn: {
			FREE_c_EMFPKA_RLP_INUSE_RevReservationOn (sp->Data.fld_c_EMFPKA_RLP_INUSE_RevReservationOn);
	EDFree (sp->Data.fld_c_EMFPKA_RLP_INUSE_RevReservationOn );
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_RevReservationOff: {
			FREE_c_EMFPKA_RLP_INUSE_RevReservationOff (sp->Data.fld_c_EMFPKA_RLP_INUSE_RevReservationOff);
	EDFree (sp->Data.fld_c_EMFPKA_RLP_INUSE_RevReservationOff );
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_FwdReservationOff: {
			FREE_c_EMFPKA_RLP_INUSE_FwdReservationOff (sp->Data.fld_c_EMFPKA_RLP_INUSE_FwdReservationOff);
	EDFree (sp->Data.fld_c_EMFPKA_RLP_INUSE_FwdReservationOff );
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_FwdReservationOn: {
			FREE_c_EMFPKA_RLP_INUSE_FwdReservationOn (sp->Data.fld_c_EMFPKA_RLP_INUSE_FwdReservationOn);
	EDFree (sp->Data.fld_c_EMFPKA_RLP_INUSE_FwdReservationOn );
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_FwdReservationAck: {
			FREE_c_EMFPKA_RLP_INUSE_FwdReservationAck (sp->Data.fld_c_EMFPKA_RLP_INUSE_FwdReservationAck);
	EDFree (sp->Data.fld_c_EMFPKA_RLP_INUSE_FwdReservationAck );
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_AttributeUpdateRequest: {
			FREE_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest);
	EDFree (sp->Data.fld_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest );
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_AttributeUpdateAccept: {
			FREE_c_EMFPKA_RLP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_EMFPKA_RLP_INUSE_AttributeUpdateAccept);
	EDFree (sp->Data.fld_c_EMFPKA_RLP_INUSE_AttributeUpdateAccept );
			break;
		}
		
		case ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_AttributeUpdateReject: {
			FREE_c_EMFPKA_RLP_INUSE_AttributeUpdateReject (sp->Data.fld_c_EMFPKA_RLP_INUSE_AttributeUpdateReject);
	EDFree (sp->Data.fld_c_EMFPKA_RLP_INUSE_AttributeUpdateReject );
			break;
		}
		
		default:;
	}

	sp->Type = ID_EMFPKA_RLP_INUSE_Unrecognized;
}

void SETPRESENT_TEMFPKA_DOSP_INUSE_Data (TEMFPKA_DOSP_INUSE_Data* sp, TEMFPKA_DOSP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TEMFPKA_DOSP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_EMFPKA_DOSP_INUSE_EMFPKA_DOSP_INUSE_DataOverSignaling: {
			sp->Data.fld_c_EMFPKA_DOSP_INUSE_DataOverSignaling = (c_EMFPKA_DOSP_INUSE_DataOverSignaling*)EDAlloc (sizeof (c_EMFPKA_DOSP_INUSE_DataOverSignaling));
			INIT_c_EMFPKA_DOSP_INUSE_DataOverSignaling (sp->Data.fld_c_EMFPKA_DOSP_INUSE_DataOverSignaling);
			break;
		}
		
		case ID_EMFPKA_DOSP_INUSE_EMFPKA_DOSP_INUSE_DataOverSignalingAck: {
			sp->Data.fld_c_EMFPKA_DOSP_INUSE_DataOverSignalingAck = (c_EMFPKA_DOSP_INUSE_DataOverSignalingAck*)EDAlloc (sizeof (c_EMFPKA_DOSP_INUSE_DataOverSignalingAck));
			INIT_c_EMFPKA_DOSP_INUSE_DataOverSignalingAck (sp->Data.fld_c_EMFPKA_DOSP_INUSE_DataOverSignalingAck);
			break;
		}
		
		default:;
	}
}

void FREE_TEMFPKA_DOSP_INUSE_Data (TEMFPKA_DOSP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_EMFPKA_DOSP_INUSE_EMFPKA_DOSP_INUSE_DataOverSignaling: {
			FREE_c_EMFPKA_DOSP_INUSE_DataOverSignaling (sp->Data.fld_c_EMFPKA_DOSP_INUSE_DataOverSignaling);
	EDFree (sp->Data.fld_c_EMFPKA_DOSP_INUSE_DataOverSignaling );
			break;
		}
		
		case ID_EMFPKA_DOSP_INUSE_EMFPKA_DOSP_INUSE_DataOverSignalingAck: {
			FREE_c_EMFPKA_DOSP_INUSE_DataOverSignalingAck (sp->Data.fld_c_EMFPKA_DOSP_INUSE_DataOverSignalingAck);
	EDFree (sp->Data.fld_c_EMFPKA_DOSP_INUSE_DataOverSignalingAck );
			break;
		}
		
		default:;
	}

	sp->Type = ID_EMFPKA_DOSP_INUSE_Unrecognized;
}

void SETPRESENT_TEMFPKA_LUP_INUSE_Data (TEMFPKA_LUP_INUSE_Data* sp, TEMFPKA_LUP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TEMFPKA_LUP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_EMFPKA_LUP_INUSE_EMFPKA_LUP_INUSE_LocationRequest: {
			sp->Data.fld_c_EMFPKA_LUP_INUSE_LocationRequest = (c_EMFPKA_LUP_INUSE_LocationRequest*)EDAlloc (sizeof (c_EMFPKA_LUP_INUSE_LocationRequest));
			INIT_c_EMFPKA_LUP_INUSE_LocationRequest (sp->Data.fld_c_EMFPKA_LUP_INUSE_LocationRequest);
			break;
		}
		
		case ID_EMFPKA_LUP_INUSE_EMFPKA_LUP_INUSE_LocationNotification: {
			sp->Data.fld_c_EMFPKA_LUP_INUSE_LocationNotification = (c_EMFPKA_LUP_INUSE_LocationNotification*)EDAlloc (sizeof (c_EMFPKA_LUP_INUSE_LocationNotification));
			INIT_c_EMFPKA_LUP_INUSE_LocationNotification (sp->Data.fld_c_EMFPKA_LUP_INUSE_LocationNotification);
			break;
		}
		
		case ID_EMFPKA_LUP_INUSE_EMFPKA_LUP_INUSE_LocationAssignment: {
			sp->Data.fld_c_EMFPKA_LUP_INUSE_LocationAssignment = (c_EMFPKA_LUP_INUSE_LocationAssignment*)EDAlloc (sizeof (c_EMFPKA_LUP_INUSE_LocationAssignment));
			INIT_c_EMFPKA_LUP_INUSE_LocationAssignment (sp->Data.fld_c_EMFPKA_LUP_INUSE_LocationAssignment);
			break;
		}
		
		case ID_EMFPKA_LUP_INUSE_EMFPKA_LUP_INUSE_LocationComplete: {
			sp->Data.fld_c_EMFPKA_LUP_INUSE_LocationComplete = (c_EMFPKA_LUP_INUSE_LocationComplete*)EDAlloc (sizeof (c_EMFPKA_LUP_INUSE_LocationComplete));
			INIT_c_EMFPKA_LUP_INUSE_LocationComplete (sp->Data.fld_c_EMFPKA_LUP_INUSE_LocationComplete);
			break;
		}
		
		case ID_EMFPKA_LUP_INUSE_EMFPKA_LUP_INUSE_StorageBLOBRequest: {
			sp->Data.fld_c_EMFPKA_LUP_INUSE_StorageBLOBRequest = (c_EMFPKA_LUP_INUSE_StorageBLOBRequest*)EDAlloc (sizeof (c_EMFPKA_LUP_INUSE_StorageBLOBRequest));
			INIT_c_EMFPKA_LUP_INUSE_StorageBLOBRequest (sp->Data.fld_c_EMFPKA_LUP_INUSE_StorageBLOBRequest);
			break;
		}
		
		case ID_EMFPKA_LUP_INUSE_EMFPKA_LUP_INUSE_StorageBLOBNotification: {
			sp->Data.fld_c_EMFPKA_LUP_INUSE_StorageBLOBNotification = (c_EMFPKA_LUP_INUSE_StorageBLOBNotification*)EDAlloc (sizeof (c_EMFPKA_LUP_INUSE_StorageBLOBNotification));
			INIT_c_EMFPKA_LUP_INUSE_StorageBLOBNotification (sp->Data.fld_c_EMFPKA_LUP_INUSE_StorageBLOBNotification);
			break;
		}
		
		case ID_EMFPKA_LUP_INUSE_EMFPKA_LUP_INUSE_StorageBLOBAssignment: {
			sp->Data.fld_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment = (c_EMFPKA_LUP_INUSE_StorageBLOBAssignment*)EDAlloc (sizeof (c_EMFPKA_LUP_INUSE_StorageBLOBAssignment));
			INIT_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment (sp->Data.fld_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment);
			break;
		}
		
		case ID_EMFPKA_LUP_INUSE_EMFPKA_LUP_INUSE_StorageBLOBComplete: {
			sp->Data.fld_c_EMFPKA_LUP_INUSE_StorageBLOBComplete = (c_EMFPKA_LUP_INUSE_StorageBLOBComplete*)EDAlloc (sizeof (c_EMFPKA_LUP_INUSE_StorageBLOBComplete));
			INIT_c_EMFPKA_LUP_INUSE_StorageBLOBComplete (sp->Data.fld_c_EMFPKA_LUP_INUSE_StorageBLOBComplete);
			break;
		}
		
		default:;
	}
}

void FREE_TEMFPKA_LUP_INUSE_Data (TEMFPKA_LUP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_EMFPKA_LUP_INUSE_EMFPKA_LUP_INUSE_LocationRequest: {
			FREE_c_EMFPKA_LUP_INUSE_LocationRequest (sp->Data.fld_c_EMFPKA_LUP_INUSE_LocationRequest);
	EDFree (sp->Data.fld_c_EMFPKA_LUP_INUSE_LocationRequest );
			break;
		}
		
		case ID_EMFPKA_LUP_INUSE_EMFPKA_LUP_INUSE_LocationNotification: {
			FREE_c_EMFPKA_LUP_INUSE_LocationNotification (sp->Data.fld_c_EMFPKA_LUP_INUSE_LocationNotification);
	EDFree (sp->Data.fld_c_EMFPKA_LUP_INUSE_LocationNotification );
			break;
		}
		
		case ID_EMFPKA_LUP_INUSE_EMFPKA_LUP_INUSE_LocationAssignment: {
			FREE_c_EMFPKA_LUP_INUSE_LocationAssignment (sp->Data.fld_c_EMFPKA_LUP_INUSE_LocationAssignment);
	EDFree (sp->Data.fld_c_EMFPKA_LUP_INUSE_LocationAssignment );
			break;
		}
		
		case ID_EMFPKA_LUP_INUSE_EMFPKA_LUP_INUSE_LocationComplete: {
			FREE_c_EMFPKA_LUP_INUSE_LocationComplete (sp->Data.fld_c_EMFPKA_LUP_INUSE_LocationComplete);
	EDFree (sp->Data.fld_c_EMFPKA_LUP_INUSE_LocationComplete );
			break;
		}
		
		case ID_EMFPKA_LUP_INUSE_EMFPKA_LUP_INUSE_StorageBLOBRequest: {
			FREE_c_EMFPKA_LUP_INUSE_StorageBLOBRequest (sp->Data.fld_c_EMFPKA_LUP_INUSE_StorageBLOBRequest);
	EDFree (sp->Data.fld_c_EMFPKA_LUP_INUSE_StorageBLOBRequest );
			break;
		}
		
		case ID_EMFPKA_LUP_INUSE_EMFPKA_LUP_INUSE_StorageBLOBNotification: {
			FREE_c_EMFPKA_LUP_INUSE_StorageBLOBNotification (sp->Data.fld_c_EMFPKA_LUP_INUSE_StorageBLOBNotification);
	EDFree (sp->Data.fld_c_EMFPKA_LUP_INUSE_StorageBLOBNotification );
			break;
		}
		
		case ID_EMFPKA_LUP_INUSE_EMFPKA_LUP_INUSE_StorageBLOBAssignment: {
			FREE_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment (sp->Data.fld_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment);
	EDFree (sp->Data.fld_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment );
			break;
		}
		
		case ID_EMFPKA_LUP_INUSE_EMFPKA_LUP_INUSE_StorageBLOBComplete: {
			FREE_c_EMFPKA_LUP_INUSE_StorageBLOBComplete (sp->Data.fld_c_EMFPKA_LUP_INUSE_StorageBLOBComplete);
	EDFree (sp->Data.fld_c_EMFPKA_LUP_INUSE_StorageBLOBComplete );
			break;
		}
		
		default:;
	}

	sp->Type = ID_EMFPKA_LUP_INUSE_Unrecognized;
}

void SETPRESENT_TEMFPKA_FCP_INUSE_Data (TEMFPKA_FCP_INUSE_Data* sp, TEMFPKA_FCP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TEMFPKA_FCP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_EMFPKA_FCP_INUSE_EMFPKA_FCP_INUSE_XonRequest: {
			sp->Data.fld_c_EMFPKA_FCP_INUSE_XonRequest = (c_EMFPKA_FCP_INUSE_XonRequest*)EDAlloc (sizeof (c_EMFPKA_FCP_INUSE_XonRequest));
			INIT_c_EMFPKA_FCP_INUSE_XonRequest (sp->Data.fld_c_EMFPKA_FCP_INUSE_XonRequest);
			break;
		}
		
		case ID_EMFPKA_FCP_INUSE_EMFPKA_FCP_INUSE_XonResponse: {
			sp->Data.fld_c_EMFPKA_FCP_INUSE_XonResponse = (c_EMFPKA_FCP_INUSE_XonResponse*)EDAlloc (sizeof (c_EMFPKA_FCP_INUSE_XonResponse));
			INIT_c_EMFPKA_FCP_INUSE_XonResponse (sp->Data.fld_c_EMFPKA_FCP_INUSE_XonResponse);
			break;
		}
		
		case ID_EMFPKA_FCP_INUSE_EMFPKA_FCP_INUSE_XoffRequest: {
			sp->Data.fld_c_EMFPKA_FCP_INUSE_XoffRequest = (c_EMFPKA_FCP_INUSE_XoffRequest*)EDAlloc (sizeof (c_EMFPKA_FCP_INUSE_XoffRequest));
			INIT_c_EMFPKA_FCP_INUSE_XoffRequest (sp->Data.fld_c_EMFPKA_FCP_INUSE_XoffRequest);
			break;
		}
		
		case ID_EMFPKA_FCP_INUSE_EMFPKA_FCP_INUSE_XoffResponse: {
			sp->Data.fld_c_EMFPKA_FCP_INUSE_XoffResponse = (c_EMFPKA_FCP_INUSE_XoffResponse*)EDAlloc (sizeof (c_EMFPKA_FCP_INUSE_XoffResponse));
			INIT_c_EMFPKA_FCP_INUSE_XoffResponse (sp->Data.fld_c_EMFPKA_FCP_INUSE_XoffResponse);
			break;
		}
		
		case ID_EMFPKA_FCP_INUSE_EMFPKA_FCP_INUSE_DataReady: {
			sp->Data.fld_c_EMFPKA_FCP_INUSE_DataReady = (c_EMFPKA_FCP_INUSE_DataReady*)EDAlloc (sizeof (c_EMFPKA_FCP_INUSE_DataReady));
			INIT_c_EMFPKA_FCP_INUSE_DataReady (sp->Data.fld_c_EMFPKA_FCP_INUSE_DataReady);
			break;
		}
		
		case ID_EMFPKA_FCP_INUSE_EMFPKA_FCP_INUSE_DataReadyAck: {
			sp->Data.fld_c_EMFPKA_FCP_INUSE_DataReadyAck = (c_EMFPKA_FCP_INUSE_DataReadyAck*)EDAlloc (sizeof (c_EMFPKA_FCP_INUSE_DataReadyAck));
			INIT_c_EMFPKA_FCP_INUSE_DataReadyAck (sp->Data.fld_c_EMFPKA_FCP_INUSE_DataReadyAck);
			break;
		}
		
		case ID_EMFPKA_FCP_INUSE_EMFPKA_FCP_INUSE_RestartNetworkInterface: {
			sp->Data.fld_c_EMFPKA_FCP_INUSE_RestartNetworkInterface = (c_EMFPKA_FCP_INUSE_RestartNetworkInterface*)EDAlloc (sizeof (c_EMFPKA_FCP_INUSE_RestartNetworkInterface));
			INIT_c_EMFPKA_FCP_INUSE_RestartNetworkInterface (sp->Data.fld_c_EMFPKA_FCP_INUSE_RestartNetworkInterface);
			break;
		}
		
		case ID_EMFPKA_FCP_INUSE_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck: {
			sp->Data.fld_c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck = (c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck*)EDAlloc (sizeof (c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck));
			INIT_c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck (sp->Data.fld_c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck);
			break;
		}
		
		default:;
	}
}

void FREE_TEMFPKA_FCP_INUSE_Data (TEMFPKA_FCP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_EMFPKA_FCP_INUSE_EMFPKA_FCP_INUSE_XonRequest: {
			FREE_c_EMFPKA_FCP_INUSE_XonRequest (sp->Data.fld_c_EMFPKA_FCP_INUSE_XonRequest);
	EDFree (sp->Data.fld_c_EMFPKA_FCP_INUSE_XonRequest );
			break;
		}
		
		case ID_EMFPKA_FCP_INUSE_EMFPKA_FCP_INUSE_XonResponse: {
			FREE_c_EMFPKA_FCP_INUSE_XonResponse (sp->Data.fld_c_EMFPKA_FCP_INUSE_XonResponse);
	EDFree (sp->Data.fld_c_EMFPKA_FCP_INUSE_XonResponse );
			break;
		}
		
		case ID_EMFPKA_FCP_INUSE_EMFPKA_FCP_INUSE_XoffRequest: {
			FREE_c_EMFPKA_FCP_INUSE_XoffRequest (sp->Data.fld_c_EMFPKA_FCP_INUSE_XoffRequest);
	EDFree (sp->Data.fld_c_EMFPKA_FCP_INUSE_XoffRequest );
			break;
		}
		
		case ID_EMFPKA_FCP_INUSE_EMFPKA_FCP_INUSE_XoffResponse: {
			FREE_c_EMFPKA_FCP_INUSE_XoffResponse (sp->Data.fld_c_EMFPKA_FCP_INUSE_XoffResponse);
	EDFree (sp->Data.fld_c_EMFPKA_FCP_INUSE_XoffResponse );
			break;
		}
		
		case ID_EMFPKA_FCP_INUSE_EMFPKA_FCP_INUSE_DataReady: {
			FREE_c_EMFPKA_FCP_INUSE_DataReady (sp->Data.fld_c_EMFPKA_FCP_INUSE_DataReady);
	EDFree (sp->Data.fld_c_EMFPKA_FCP_INUSE_DataReady );
			break;
		}
		
		case ID_EMFPKA_FCP_INUSE_EMFPKA_FCP_INUSE_DataReadyAck: {
			FREE_c_EMFPKA_FCP_INUSE_DataReadyAck (sp->Data.fld_c_EMFPKA_FCP_INUSE_DataReadyAck);
	EDFree (sp->Data.fld_c_EMFPKA_FCP_INUSE_DataReadyAck );
			break;
		}
		
		case ID_EMFPKA_FCP_INUSE_EMFPKA_FCP_INUSE_RestartNetworkInterface: {
			FREE_c_EMFPKA_FCP_INUSE_RestartNetworkInterface (sp->Data.fld_c_EMFPKA_FCP_INUSE_RestartNetworkInterface);
	EDFree (sp->Data.fld_c_EMFPKA_FCP_INUSE_RestartNetworkInterface );
			break;
		}
		
		case ID_EMFPKA_FCP_INUSE_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck: {
			FREE_c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck (sp->Data.fld_c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck);
	EDFree (sp->Data.fld_c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck );
			break;
		}
		
		default:;
	}

	sp->Type = ID_EMFPKA_FCP_INUSE_Unrecognized;
}

void SETPRESENT_TMLMFPA_MMFPA_INCFG_Data (TMLMFPA_MMFPA_INCFG_Data* sp, TMLMFPA_MMFPA_INCFG_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TMLMFPA_MMFPA_INCFG_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_MLMFPA_MMFPA_INCFG_MLMFPA_MMFPA_INCFG_ConfigurationRequest: {
			sp->Data.fld_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest = (c_MLMFPA_MMFPA_INCFG_ConfigurationRequest*)EDAlloc (sizeof (c_MLMFPA_MMFPA_INCFG_ConfigurationRequest));
			INIT_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest (sp->Data.fld_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest);
			break;
		}
		
		case ID_MLMFPA_MMFPA_INCFG_MLMFPA_MMFPA_INCFG_ConfigurationResponse: {
			sp->Data.fld_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse = (c_MLMFPA_MMFPA_INCFG_ConfigurationResponse*)EDAlloc (sizeof (c_MLMFPA_MMFPA_INCFG_ConfigurationResponse));
			INIT_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse (sp->Data.fld_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse);
			break;
		}
		
		default:;
	}
}

void FREE_TMLMFPA_MMFPA_INCFG_Data (TMLMFPA_MMFPA_INCFG_Data* sp)
{
	switch (sp->Type) {
		case ID_MLMFPA_MMFPA_INCFG_MLMFPA_MMFPA_INCFG_ConfigurationRequest: {
			FREE_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest (sp->Data.fld_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest);
	EDFree (sp->Data.fld_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest );
			break;
		}
		
		case ID_MLMFPA_MMFPA_INCFG_MLMFPA_MMFPA_INCFG_ConfigurationResponse: {
			FREE_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse (sp->Data.fld_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse);
	EDFree (sp->Data.fld_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse );
			break;
		}
		
		default:;
	}

	sp->Type = ID_MLMFPA_MMFPA_INCFG_Unrecognized;
}

void SETPRESENT_TMLMFPA_RSP_INUSE_Data (TMLMFPA_RSP_INUSE_Data* sp, TMLMFPA_RSP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TMLMFPA_RSP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_MLMFPA_RSP_INUSE_MLMFPA_RSP_INUSE_RouteSelect: {
			sp->Data.fld_c_MLMFPA_RSP_INUSE_RouteSelect = (c_MLMFPA_RSP_INUSE_RouteSelect*)EDAlloc (sizeof (c_MLMFPA_RSP_INUSE_RouteSelect));
			INIT_c_MLMFPA_RSP_INUSE_RouteSelect (sp->Data.fld_c_MLMFPA_RSP_INUSE_RouteSelect);
			break;
		}
		
		case ID_MLMFPA_RSP_INUSE_MLMFPA_RSP_INUSE_RouteSelectAck: {
			sp->Data.fld_c_MLMFPA_RSP_INUSE_RouteSelectAck = (c_MLMFPA_RSP_INUSE_RouteSelectAck*)EDAlloc (sizeof (c_MLMFPA_RSP_INUSE_RouteSelectAck));
			INIT_c_MLMFPA_RSP_INUSE_RouteSelectAck (sp->Data.fld_c_MLMFPA_RSP_INUSE_RouteSelectAck);
			break;
		}
		
		case ID_MLMFPA_RSP_INUSE_MLMFPA_RSP_INUSE_ActivateRoute: {
			sp->Data.fld_c_MLMFPA_RSP_INUSE_ActivateRoute = (c_MLMFPA_RSP_INUSE_ActivateRoute*)EDAlloc (sizeof (c_MLMFPA_RSP_INUSE_ActivateRoute));
			INIT_c_MLMFPA_RSP_INUSE_ActivateRoute (sp->Data.fld_c_MLMFPA_RSP_INUSE_ActivateRoute);
			break;
		}
		
		case ID_MLMFPA_RSP_INUSE_MLMFPA_RSP_INUSE_ActivateRouteAck: {
			sp->Data.fld_c_MLMFPA_RSP_INUSE_ActivateRouteAck = (c_MLMFPA_RSP_INUSE_ActivateRouteAck*)EDAlloc (sizeof (c_MLMFPA_RSP_INUSE_ActivateRouteAck));
			INIT_c_MLMFPA_RSP_INUSE_ActivateRouteAck (sp->Data.fld_c_MLMFPA_RSP_INUSE_ActivateRouteAck);
			break;
		}
		
		default:;
	}
}

void FREE_TMLMFPA_RSP_INUSE_Data (TMLMFPA_RSP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_MLMFPA_RSP_INUSE_MLMFPA_RSP_INUSE_RouteSelect: {
			FREE_c_MLMFPA_RSP_INUSE_RouteSelect (sp->Data.fld_c_MLMFPA_RSP_INUSE_RouteSelect);
	EDFree (sp->Data.fld_c_MLMFPA_RSP_INUSE_RouteSelect );
			break;
		}
		
		case ID_MLMFPA_RSP_INUSE_MLMFPA_RSP_INUSE_RouteSelectAck: {
			FREE_c_MLMFPA_RSP_INUSE_RouteSelectAck (sp->Data.fld_c_MLMFPA_RSP_INUSE_RouteSelectAck);
	EDFree (sp->Data.fld_c_MLMFPA_RSP_INUSE_RouteSelectAck );
			break;
		}
		
		case ID_MLMFPA_RSP_INUSE_MLMFPA_RSP_INUSE_ActivateRoute: {
			FREE_c_MLMFPA_RSP_INUSE_ActivateRoute (sp->Data.fld_c_MLMFPA_RSP_INUSE_ActivateRoute);
	EDFree (sp->Data.fld_c_MLMFPA_RSP_INUSE_ActivateRoute );
			break;
		}
		
		case ID_MLMFPA_RSP_INUSE_MLMFPA_RSP_INUSE_ActivateRouteAck: {
			FREE_c_MLMFPA_RSP_INUSE_ActivateRouteAck (sp->Data.fld_c_MLMFPA_RSP_INUSE_ActivateRouteAck);
	EDFree (sp->Data.fld_c_MLMFPA_RSP_INUSE_ActivateRouteAck );
			break;
		}
		
		default:;
	}

	sp->Type = ID_MLMFPA_RSP_INUSE_Unrecognized;
}

void SETPRESENT_TMLMFPA_SRP_INUSE_Data (TMLMFPA_SRP_INUSE_Data* sp, TMLMFPA_SRP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TMLMFPA_SRP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ResetTxIndication: {
			sp->Data.fld_c_MLMFPA_SRP_INUSE_ResetTxIndication = (c_MLMFPA_SRP_INUSE_ResetTxIndication*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_ResetTxIndication));
			INIT_c_MLMFPA_SRP_INUSE_ResetTxIndication (sp->Data.fld_c_MLMFPA_SRP_INUSE_ResetTxIndication);
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ResetRxIndication: {
			sp->Data.fld_c_MLMFPA_SRP_INUSE_ResetRxIndication = (c_MLMFPA_SRP_INUSE_ResetRxIndication*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_ResetRxIndication));
			INIT_c_MLMFPA_SRP_INUSE_ResetRxIndication (sp->Data.fld_c_MLMFPA_SRP_INUSE_ResetRxIndication);
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ResetTxIndicationAck: {
			sp->Data.fld_c_MLMFPA_SRP_INUSE_ResetTxIndicationAck = (c_MLMFPA_SRP_INUSE_ResetTxIndicationAck*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_ResetTxIndicationAck));
			INIT_c_MLMFPA_SRP_INUSE_ResetTxIndicationAck (sp->Data.fld_c_MLMFPA_SRP_INUSE_ResetTxIndicationAck);
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ResetTxComplete: {
			sp->Data.fld_c_MLMFPA_SRP_INUSE_ResetTxComplete = (c_MLMFPA_SRP_INUSE_ResetTxComplete*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_ResetTxComplete));
			INIT_c_MLMFPA_SRP_INUSE_ResetTxComplete (sp->Data.fld_c_MLMFPA_SRP_INUSE_ResetTxComplete);
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ResetRxComplete: {
			sp->Data.fld_c_MLMFPA_SRP_INUSE_ResetRxComplete = (c_MLMFPA_SRP_INUSE_ResetRxComplete*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_ResetRxComplete));
			INIT_c_MLMFPA_SRP_INUSE_ResetRxComplete (sp->Data.fld_c_MLMFPA_SRP_INUSE_ResetRxComplete);
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_MultiLinkNak: {
			sp->Data.fld_c_MLMFPA_SRP_INUSE_MultiLinkNak = (c_MLMFPA_SRP_INUSE_MultiLinkNak*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_MultiLinkNak));
			INIT_c_MLMFPA_SRP_INUSE_MultiLinkNak (sp->Data.fld_c_MLMFPA_SRP_INUSE_MultiLinkNak);
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ReservationOnRequest: {
			sp->Data.fld_c_MLMFPA_SRP_INUSE_ReservationOnRequest = (c_MLMFPA_SRP_INUSE_ReservationOnRequest*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_ReservationOnRequest));
			INIT_c_MLMFPA_SRP_INUSE_ReservationOnRequest (sp->Data.fld_c_MLMFPA_SRP_INUSE_ReservationOnRequest);
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ReservationOffRequest: {
			sp->Data.fld_c_MLMFPA_SRP_INUSE_ReservationOffRequest = (c_MLMFPA_SRP_INUSE_ReservationOffRequest*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_ReservationOffRequest));
			INIT_c_MLMFPA_SRP_INUSE_ReservationOffRequest (sp->Data.fld_c_MLMFPA_SRP_INUSE_ReservationOffRequest);
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ReservationAccept: {
			sp->Data.fld_c_MLMFPA_SRP_INUSE_ReservationAccept = (c_MLMFPA_SRP_INUSE_ReservationAccept*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_ReservationAccept));
			INIT_c_MLMFPA_SRP_INUSE_ReservationAccept (sp->Data.fld_c_MLMFPA_SRP_INUSE_ReservationAccept);
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ReservationReject: {
			sp->Data.fld_c_MLMFPA_SRP_INUSE_ReservationReject = (c_MLMFPA_SRP_INUSE_ReservationReject*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_ReservationReject));
			INIT_c_MLMFPA_SRP_INUSE_ReservationReject (sp->Data.fld_c_MLMFPA_SRP_INUSE_ReservationReject);
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_RevReservationOn: {
			sp->Data.fld_c_MLMFPA_SRP_INUSE_RevReservationOn = (c_MLMFPA_SRP_INUSE_RevReservationOn*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_RevReservationOn));
			INIT_c_MLMFPA_SRP_INUSE_RevReservationOn (sp->Data.fld_c_MLMFPA_SRP_INUSE_RevReservationOn);
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_RevReservationOff: {
			sp->Data.fld_c_MLMFPA_SRP_INUSE_RevReservationOff = (c_MLMFPA_SRP_INUSE_RevReservationOff*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_RevReservationOff));
			INIT_c_MLMFPA_SRP_INUSE_RevReservationOff (sp->Data.fld_c_MLMFPA_SRP_INUSE_RevReservationOff);
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_FwdReservationOff: {
			sp->Data.fld_c_MLMFPA_SRP_INUSE_FwdReservationOff = (c_MLMFPA_SRP_INUSE_FwdReservationOff*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_FwdReservationOff));
			INIT_c_MLMFPA_SRP_INUSE_FwdReservationOff (sp->Data.fld_c_MLMFPA_SRP_INUSE_FwdReservationOff);
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_FwdReservationOn: {
			sp->Data.fld_c_MLMFPA_SRP_INUSE_FwdReservationOn = (c_MLMFPA_SRP_INUSE_FwdReservationOn*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_FwdReservationOn));
			INIT_c_MLMFPA_SRP_INUSE_FwdReservationOn (sp->Data.fld_c_MLMFPA_SRP_INUSE_FwdReservationOn);
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_FwdReservationAck: {
			sp->Data.fld_c_MLMFPA_SRP_INUSE_FwdReservationAck = (c_MLMFPA_SRP_INUSE_FwdReservationAck*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_FwdReservationAck));
			INIT_c_MLMFPA_SRP_INUSE_FwdReservationAck (sp->Data.fld_c_MLMFPA_SRP_INUSE_FwdReservationAck);
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_AttributeUpdateRequest: {
			sp->Data.fld_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest = (c_MLMFPA_SRP_INUSE_AttributeUpdateRequest*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_AttributeUpdateRequest));
			INIT_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest);
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_AttributeUpdateAccept: {
			sp->Data.fld_c_MLMFPA_SRP_INUSE_AttributeUpdateAccept = (c_MLMFPA_SRP_INUSE_AttributeUpdateAccept*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_AttributeUpdateAccept));
			INIT_c_MLMFPA_SRP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_MLMFPA_SRP_INUSE_AttributeUpdateAccept);
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_AttributeUpdateReject: {
			sp->Data.fld_c_MLMFPA_SRP_INUSE_AttributeUpdateReject = (c_MLMFPA_SRP_INUSE_AttributeUpdateReject*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_AttributeUpdateReject));
			INIT_c_MLMFPA_SRP_INUSE_AttributeUpdateReject (sp->Data.fld_c_MLMFPA_SRP_INUSE_AttributeUpdateReject);
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_Flush: {
			sp->Data.fld_c_MLMFPA_SRP_INUSE_Flush = (c_MLMFPA_SRP_INUSE_Flush*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_Flush));
			INIT_c_MLMFPA_SRP_INUSE_Flush (sp->Data.fld_c_MLMFPA_SRP_INUSE_Flush);
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_Nak: {
			sp->Data.fld_c_MLMFPA_SRP_INUSE_Nak = (c_MLMFPA_SRP_INUSE_Nak*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_Nak));
			INIT_c_MLMFPA_SRP_INUSE_Nak (sp->Data.fld_c_MLMFPA_SRP_INUSE_Nak);
			break;
		}
		
		default:;
	}
}

void FREE_TMLMFPA_SRP_INUSE_Data (TMLMFPA_SRP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ResetTxIndication: {
			FREE_c_MLMFPA_SRP_INUSE_ResetTxIndication (sp->Data.fld_c_MLMFPA_SRP_INUSE_ResetTxIndication);
	EDFree (sp->Data.fld_c_MLMFPA_SRP_INUSE_ResetTxIndication );
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ResetRxIndication: {
			FREE_c_MLMFPA_SRP_INUSE_ResetRxIndication (sp->Data.fld_c_MLMFPA_SRP_INUSE_ResetRxIndication);
	EDFree (sp->Data.fld_c_MLMFPA_SRP_INUSE_ResetRxIndication );
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ResetTxIndicationAck: {
			FREE_c_MLMFPA_SRP_INUSE_ResetTxIndicationAck (sp->Data.fld_c_MLMFPA_SRP_INUSE_ResetTxIndicationAck);
	EDFree (sp->Data.fld_c_MLMFPA_SRP_INUSE_ResetTxIndicationAck );
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ResetTxComplete: {
			FREE_c_MLMFPA_SRP_INUSE_ResetTxComplete (sp->Data.fld_c_MLMFPA_SRP_INUSE_ResetTxComplete);
	EDFree (sp->Data.fld_c_MLMFPA_SRP_INUSE_ResetTxComplete );
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ResetRxComplete: {
			FREE_c_MLMFPA_SRP_INUSE_ResetRxComplete (sp->Data.fld_c_MLMFPA_SRP_INUSE_ResetRxComplete);
	EDFree (sp->Data.fld_c_MLMFPA_SRP_INUSE_ResetRxComplete );
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_MultiLinkNak: {
			FREE_c_MLMFPA_SRP_INUSE_MultiLinkNak (sp->Data.fld_c_MLMFPA_SRP_INUSE_MultiLinkNak);
	EDFree (sp->Data.fld_c_MLMFPA_SRP_INUSE_MultiLinkNak );
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ReservationOnRequest: {
			FREE_c_MLMFPA_SRP_INUSE_ReservationOnRequest (sp->Data.fld_c_MLMFPA_SRP_INUSE_ReservationOnRequest);
	EDFree (sp->Data.fld_c_MLMFPA_SRP_INUSE_ReservationOnRequest );
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ReservationOffRequest: {
			FREE_c_MLMFPA_SRP_INUSE_ReservationOffRequest (sp->Data.fld_c_MLMFPA_SRP_INUSE_ReservationOffRequest);
	EDFree (sp->Data.fld_c_MLMFPA_SRP_INUSE_ReservationOffRequest );
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ReservationAccept: {
			FREE_c_MLMFPA_SRP_INUSE_ReservationAccept (sp->Data.fld_c_MLMFPA_SRP_INUSE_ReservationAccept);
	EDFree (sp->Data.fld_c_MLMFPA_SRP_INUSE_ReservationAccept );
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ReservationReject: {
			FREE_c_MLMFPA_SRP_INUSE_ReservationReject (sp->Data.fld_c_MLMFPA_SRP_INUSE_ReservationReject);
	EDFree (sp->Data.fld_c_MLMFPA_SRP_INUSE_ReservationReject );
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_RevReservationOn: {
			FREE_c_MLMFPA_SRP_INUSE_RevReservationOn (sp->Data.fld_c_MLMFPA_SRP_INUSE_RevReservationOn);
	EDFree (sp->Data.fld_c_MLMFPA_SRP_INUSE_RevReservationOn );
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_RevReservationOff: {
			FREE_c_MLMFPA_SRP_INUSE_RevReservationOff (sp->Data.fld_c_MLMFPA_SRP_INUSE_RevReservationOff);
	EDFree (sp->Data.fld_c_MLMFPA_SRP_INUSE_RevReservationOff );
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_FwdReservationOff: {
			FREE_c_MLMFPA_SRP_INUSE_FwdReservationOff (sp->Data.fld_c_MLMFPA_SRP_INUSE_FwdReservationOff);
	EDFree (sp->Data.fld_c_MLMFPA_SRP_INUSE_FwdReservationOff );
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_FwdReservationOn: {
			FREE_c_MLMFPA_SRP_INUSE_FwdReservationOn (sp->Data.fld_c_MLMFPA_SRP_INUSE_FwdReservationOn);
	EDFree (sp->Data.fld_c_MLMFPA_SRP_INUSE_FwdReservationOn );
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_FwdReservationAck: {
			FREE_c_MLMFPA_SRP_INUSE_FwdReservationAck (sp->Data.fld_c_MLMFPA_SRP_INUSE_FwdReservationAck);
	EDFree (sp->Data.fld_c_MLMFPA_SRP_INUSE_FwdReservationAck );
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_AttributeUpdateRequest: {
			FREE_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest (sp->Data.fld_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest);
	EDFree (sp->Data.fld_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest );
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_AttributeUpdateAccept: {
			FREE_c_MLMFPA_SRP_INUSE_AttributeUpdateAccept (sp->Data.fld_c_MLMFPA_SRP_INUSE_AttributeUpdateAccept);
	EDFree (sp->Data.fld_c_MLMFPA_SRP_INUSE_AttributeUpdateAccept );
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_AttributeUpdateReject: {
			FREE_c_MLMFPA_SRP_INUSE_AttributeUpdateReject (sp->Data.fld_c_MLMFPA_SRP_INUSE_AttributeUpdateReject);
	EDFree (sp->Data.fld_c_MLMFPA_SRP_INUSE_AttributeUpdateReject );
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_Flush: {
			FREE_c_MLMFPA_SRP_INUSE_Flush (sp->Data.fld_c_MLMFPA_SRP_INUSE_Flush);
	EDFree (sp->Data.fld_c_MLMFPA_SRP_INUSE_Flush );
			break;
		}
		
		case ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_Nak: {
			FREE_c_MLMFPA_SRP_INUSE_Nak (sp->Data.fld_c_MLMFPA_SRP_INUSE_Nak);
	EDFree (sp->Data.fld_c_MLMFPA_SRP_INUSE_Nak );
			break;
		}
		
		default:;
	}

	sp->Type = ID_MLMFPA_SRP_INUSE_Unrecognized;
}

void SETPRESENT_TMLMFPA_DOSP_INUSE_Data (TMLMFPA_DOSP_INUSE_Data* sp, TMLMFPA_DOSP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TMLMFPA_DOSP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_MLMFPA_DOSP_INUSE_MLMFPA_DOSP_INUSE_DataOverSignaling: {
			sp->Data.fld_c_MLMFPA_DOSP_INUSE_DataOverSignaling = (c_MLMFPA_DOSP_INUSE_DataOverSignaling*)EDAlloc (sizeof (c_MLMFPA_DOSP_INUSE_DataOverSignaling));
			INIT_c_MLMFPA_DOSP_INUSE_DataOverSignaling (sp->Data.fld_c_MLMFPA_DOSP_INUSE_DataOverSignaling);
			break;
		}
		
		case ID_MLMFPA_DOSP_INUSE_MLMFPA_DOSP_INUSE_DataOverSignalingAck: {
			sp->Data.fld_c_MLMFPA_DOSP_INUSE_DataOverSignalingAck = (c_MLMFPA_DOSP_INUSE_DataOverSignalingAck*)EDAlloc (sizeof (c_MLMFPA_DOSP_INUSE_DataOverSignalingAck));
			INIT_c_MLMFPA_DOSP_INUSE_DataOverSignalingAck (sp->Data.fld_c_MLMFPA_DOSP_INUSE_DataOverSignalingAck);
			break;
		}
		
		default:;
	}
}

void FREE_TMLMFPA_DOSP_INUSE_Data (TMLMFPA_DOSP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_MLMFPA_DOSP_INUSE_MLMFPA_DOSP_INUSE_DataOverSignaling: {
			FREE_c_MLMFPA_DOSP_INUSE_DataOverSignaling (sp->Data.fld_c_MLMFPA_DOSP_INUSE_DataOverSignaling);
	EDFree (sp->Data.fld_c_MLMFPA_DOSP_INUSE_DataOverSignaling );
			break;
		}
		
		case ID_MLMFPA_DOSP_INUSE_MLMFPA_DOSP_INUSE_DataOverSignalingAck: {
			FREE_c_MLMFPA_DOSP_INUSE_DataOverSignalingAck (sp->Data.fld_c_MLMFPA_DOSP_INUSE_DataOverSignalingAck);
	EDFree (sp->Data.fld_c_MLMFPA_DOSP_INUSE_DataOverSignalingAck );
			break;
		}
		
		default:;
	}

	sp->Type = ID_MLMFPA_DOSP_INUSE_Unrecognized;
}

void SETPRESENT_TMLMFPA_LUP_INUSE_Data (TMLMFPA_LUP_INUSE_Data* sp, TMLMFPA_LUP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TMLMFPA_LUP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_MLMFPA_LUP_INUSE_MLMFPA_LUP_INUSE_LocationRequest: {
			sp->Data.fld_c_MLMFPA_LUP_INUSE_LocationRequest = (c_MLMFPA_LUP_INUSE_LocationRequest*)EDAlloc (sizeof (c_MLMFPA_LUP_INUSE_LocationRequest));
			INIT_c_MLMFPA_LUP_INUSE_LocationRequest (sp->Data.fld_c_MLMFPA_LUP_INUSE_LocationRequest);
			break;
		}
		
		case ID_MLMFPA_LUP_INUSE_MLMFPA_LUP_INUSE_LocationNotification: {
			sp->Data.fld_c_MLMFPA_LUP_INUSE_LocationNotification = (c_MLMFPA_LUP_INUSE_LocationNotification*)EDAlloc (sizeof (c_MLMFPA_LUP_INUSE_LocationNotification));
			INIT_c_MLMFPA_LUP_INUSE_LocationNotification (sp->Data.fld_c_MLMFPA_LUP_INUSE_LocationNotification);
			break;
		}
		
		case ID_MLMFPA_LUP_INUSE_MLMFPA_LUP_INUSE_LocationAssignment: {
			sp->Data.fld_c_MLMFPA_LUP_INUSE_LocationAssignment = (c_MLMFPA_LUP_INUSE_LocationAssignment*)EDAlloc (sizeof (c_MLMFPA_LUP_INUSE_LocationAssignment));
			INIT_c_MLMFPA_LUP_INUSE_LocationAssignment (sp->Data.fld_c_MLMFPA_LUP_INUSE_LocationAssignment);
			break;
		}
		
		case ID_MLMFPA_LUP_INUSE_MLMFPA_LUP_INUSE_LocationComplete: {
			sp->Data.fld_c_MLMFPA_LUP_INUSE_LocationComplete = (c_MLMFPA_LUP_INUSE_LocationComplete*)EDAlloc (sizeof (c_MLMFPA_LUP_INUSE_LocationComplete));
			INIT_c_MLMFPA_LUP_INUSE_LocationComplete (sp->Data.fld_c_MLMFPA_LUP_INUSE_LocationComplete);
			break;
		}
		
		case ID_MLMFPA_LUP_INUSE_MLMFPA_LUP_INUSE_StorageBLOBRequest: {
			sp->Data.fld_c_MLMFPA_LUP_INUSE_StorageBLOBRequest = (c_MLMFPA_LUP_INUSE_StorageBLOBRequest*)EDAlloc (sizeof (c_MLMFPA_LUP_INUSE_StorageBLOBRequest));
			INIT_c_MLMFPA_LUP_INUSE_StorageBLOBRequest (sp->Data.fld_c_MLMFPA_LUP_INUSE_StorageBLOBRequest);
			break;
		}
		
		case ID_MLMFPA_LUP_INUSE_MLMFPA_LUP_INUSE_StorageBLOBNotification: {
			sp->Data.fld_c_MLMFPA_LUP_INUSE_StorageBLOBNotification = (c_MLMFPA_LUP_INUSE_StorageBLOBNotification*)EDAlloc (sizeof (c_MLMFPA_LUP_INUSE_StorageBLOBNotification));
			INIT_c_MLMFPA_LUP_INUSE_StorageBLOBNotification (sp->Data.fld_c_MLMFPA_LUP_INUSE_StorageBLOBNotification);
			break;
		}
		
		case ID_MLMFPA_LUP_INUSE_MLMFPA_LUP_INUSE_StorageBLOBAssignment: {
			sp->Data.fld_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment = (c_MLMFPA_LUP_INUSE_StorageBLOBAssignment*)EDAlloc (sizeof (c_MLMFPA_LUP_INUSE_StorageBLOBAssignment));
			INIT_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment (sp->Data.fld_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment);
			break;
		}
		
		case ID_MLMFPA_LUP_INUSE_MLMFPA_LUP_INUSE_StorageBLOBComplete: {
			sp->Data.fld_c_MLMFPA_LUP_INUSE_StorageBLOBComplete = (c_MLMFPA_LUP_INUSE_StorageBLOBComplete*)EDAlloc (sizeof (c_MLMFPA_LUP_INUSE_StorageBLOBComplete));
			INIT_c_MLMFPA_LUP_INUSE_StorageBLOBComplete (sp->Data.fld_c_MLMFPA_LUP_INUSE_StorageBLOBComplete);
			break;
		}
		
		default:;
	}
}

void FREE_TMLMFPA_LUP_INUSE_Data (TMLMFPA_LUP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_MLMFPA_LUP_INUSE_MLMFPA_LUP_INUSE_LocationRequest: {
			FREE_c_MLMFPA_LUP_INUSE_LocationRequest (sp->Data.fld_c_MLMFPA_LUP_INUSE_LocationRequest);
	EDFree (sp->Data.fld_c_MLMFPA_LUP_INUSE_LocationRequest );
			break;
		}
		
		case ID_MLMFPA_LUP_INUSE_MLMFPA_LUP_INUSE_LocationNotification: {
			FREE_c_MLMFPA_LUP_INUSE_LocationNotification (sp->Data.fld_c_MLMFPA_LUP_INUSE_LocationNotification);
	EDFree (sp->Data.fld_c_MLMFPA_LUP_INUSE_LocationNotification );
			break;
		}
		
		case ID_MLMFPA_LUP_INUSE_MLMFPA_LUP_INUSE_LocationAssignment: {
			FREE_c_MLMFPA_LUP_INUSE_LocationAssignment (sp->Data.fld_c_MLMFPA_LUP_INUSE_LocationAssignment);
	EDFree (sp->Data.fld_c_MLMFPA_LUP_INUSE_LocationAssignment );
			break;
		}
		
		case ID_MLMFPA_LUP_INUSE_MLMFPA_LUP_INUSE_LocationComplete: {
			FREE_c_MLMFPA_LUP_INUSE_LocationComplete (sp->Data.fld_c_MLMFPA_LUP_INUSE_LocationComplete);
	EDFree (sp->Data.fld_c_MLMFPA_LUP_INUSE_LocationComplete );
			break;
		}
		
		case ID_MLMFPA_LUP_INUSE_MLMFPA_LUP_INUSE_StorageBLOBRequest: {
			FREE_c_MLMFPA_LUP_INUSE_StorageBLOBRequest (sp->Data.fld_c_MLMFPA_LUP_INUSE_StorageBLOBRequest);
	EDFree (sp->Data.fld_c_MLMFPA_LUP_INUSE_StorageBLOBRequest );
			break;
		}
		
		case ID_MLMFPA_LUP_INUSE_MLMFPA_LUP_INUSE_StorageBLOBNotification: {
			FREE_c_MLMFPA_LUP_INUSE_StorageBLOBNotification (sp->Data.fld_c_MLMFPA_LUP_INUSE_StorageBLOBNotification);
	EDFree (sp->Data.fld_c_MLMFPA_LUP_INUSE_StorageBLOBNotification );
			break;
		}
		
		case ID_MLMFPA_LUP_INUSE_MLMFPA_LUP_INUSE_StorageBLOBAssignment: {
			FREE_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment (sp->Data.fld_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment);
	EDFree (sp->Data.fld_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment );
			break;
		}
		
		case ID_MLMFPA_LUP_INUSE_MLMFPA_LUP_INUSE_StorageBLOBComplete: {
			FREE_c_MLMFPA_LUP_INUSE_StorageBLOBComplete (sp->Data.fld_c_MLMFPA_LUP_INUSE_StorageBLOBComplete);
	EDFree (sp->Data.fld_c_MLMFPA_LUP_INUSE_StorageBLOBComplete );
			break;
		}
		
		default:;
	}

	sp->Type = ID_MLMFPA_LUP_INUSE_Unrecognized;
}

void SETPRESENT_TMLMFPA_FCP_INUSE_Data (TMLMFPA_FCP_INUSE_Data* sp, TMLMFPA_FCP_INUSE_Type toBeSetPresent)
{
	if (sp->Type == toBeSetPresent) return;
	FREE_TMLMFPA_FCP_INUSE_Data (sp);
	sp->Type = toBeSetPresent;

	switch (sp->Type) {
		case ID_MLMFPA_FCP_INUSE_MLMFPA_FCP_INUSE_XonRequest: {
			sp->Data.fld_c_MLMFPA_FCP_INUSE_XonRequest = (c_MLMFPA_FCP_INUSE_XonRequest*)EDAlloc (sizeof (c_MLMFPA_FCP_INUSE_XonRequest));
			INIT_c_MLMFPA_FCP_INUSE_XonRequest (sp->Data.fld_c_MLMFPA_FCP_INUSE_XonRequest);
			break;
		}
		
		case ID_MLMFPA_FCP_INUSE_MLMFPA_FCP_INUSE_XonResponse: {
			sp->Data.fld_c_MLMFPA_FCP_INUSE_XonResponse = (c_MLMFPA_FCP_INUSE_XonResponse*)EDAlloc (sizeof (c_MLMFPA_FCP_INUSE_XonResponse));
			INIT_c_MLMFPA_FCP_INUSE_XonResponse (sp->Data.fld_c_MLMFPA_FCP_INUSE_XonResponse);
			break;
		}
		
		case ID_MLMFPA_FCP_INUSE_MLMFPA_FCP_INUSE_XoffRequest: {
			sp->Data.fld_c_MLMFPA_FCP_INUSE_XoffRequest = (c_MLMFPA_FCP_INUSE_XoffRequest*)EDAlloc (sizeof (c_MLMFPA_FCP_INUSE_XoffRequest));
			INIT_c_MLMFPA_FCP_INUSE_XoffRequest (sp->Data.fld_c_MLMFPA_FCP_INUSE_XoffRequest);
			break;
		}
		
		case ID_MLMFPA_FCP_INUSE_MLMFPA_FCP_INUSE_XoffResponse: {
			sp->Data.fld_c_MLMFPA_FCP_INUSE_XoffResponse = (c_MLMFPA_FCP_INUSE_XoffResponse*)EDAlloc (sizeof (c_MLMFPA_FCP_INUSE_XoffResponse));
			INIT_c_MLMFPA_FCP_INUSE_XoffResponse (sp->Data.fld_c_MLMFPA_FCP_INUSE_XoffResponse);
			break;
		}
		
		case ID_MLMFPA_FCP_INUSE_MLMFPA_FCP_INUSE_DataReady: {
			sp->Data.fld_c_MLMFPA_FCP_INUSE_DataReady = (c_MLMFPA_FCP_INUSE_DataReady*)EDAlloc (sizeof (c_MLMFPA_FCP_INUSE_DataReady));
			INIT_c_MLMFPA_FCP_INUSE_DataReady (sp->Data.fld_c_MLMFPA_FCP_INUSE_DataReady);
			break;
		}
		
		case ID_MLMFPA_FCP_INUSE_MLMFPA_FCP_INUSE_DataReadyAck: {
			sp->Data.fld_c_MLMFPA_FCP_INUSE_DataReadyAck = (c_MLMFPA_FCP_INUSE_DataReadyAck*)EDAlloc (sizeof (c_MLMFPA_FCP_INUSE_DataReadyAck));
			INIT_c_MLMFPA_FCP_INUSE_DataReadyAck (sp->Data.fld_c_MLMFPA_FCP_INUSE_DataReadyAck);
			break;
		}
		
		case ID_MLMFPA_FCP_INUSE_MLMFPA_FCP_INUSE_RestartNetworkInterface: {
			sp->Data.fld_c_MLMFPA_FCP_INUSE_RestartNetworkInterface = (c_MLMFPA_FCP_INUSE_RestartNetworkInterface*)EDAlloc (sizeof (c_MLMFPA_FCP_INUSE_RestartNetworkInterface));
			INIT_c_MLMFPA_FCP_INUSE_RestartNetworkInterface (sp->Data.fld_c_MLMFPA_FCP_INUSE_RestartNetworkInterface);
			break;
		}
		
		case ID_MLMFPA_FCP_INUSE_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck: {
			sp->Data.fld_c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck = (c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck*)EDAlloc (sizeof (c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck));
			INIT_c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck (sp->Data.fld_c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck);
			break;
		}
		
		default:;
	}
}

void FREE_TMLMFPA_FCP_INUSE_Data (TMLMFPA_FCP_INUSE_Data* sp)
{
	switch (sp->Type) {
		case ID_MLMFPA_FCP_INUSE_MLMFPA_FCP_INUSE_XonRequest: {
			FREE_c_MLMFPA_FCP_INUSE_XonRequest (sp->Data.fld_c_MLMFPA_FCP_INUSE_XonRequest);
	EDFree (sp->Data.fld_c_MLMFPA_FCP_INUSE_XonRequest );
			break;
		}
		
		case ID_MLMFPA_FCP_INUSE_MLMFPA_FCP_INUSE_XonResponse: {
			FREE_c_MLMFPA_FCP_INUSE_XonResponse (sp->Data.fld_c_MLMFPA_FCP_INUSE_XonResponse);
	EDFree (sp->Data.fld_c_MLMFPA_FCP_INUSE_XonResponse );
			break;
		}
		
		case ID_MLMFPA_FCP_INUSE_MLMFPA_FCP_INUSE_XoffRequest: {
			FREE_c_MLMFPA_FCP_INUSE_XoffRequest (sp->Data.fld_c_MLMFPA_FCP_INUSE_XoffRequest);
	EDFree (sp->Data.fld_c_MLMFPA_FCP_INUSE_XoffRequest );
			break;
		}
		
		case ID_MLMFPA_FCP_INUSE_MLMFPA_FCP_INUSE_XoffResponse: {
			FREE_c_MLMFPA_FCP_INUSE_XoffResponse (sp->Data.fld_c_MLMFPA_FCP_INUSE_XoffResponse);
	EDFree (sp->Data.fld_c_MLMFPA_FCP_INUSE_XoffResponse );
			break;
		}
		
		case ID_MLMFPA_FCP_INUSE_MLMFPA_FCP_INUSE_DataReady: {
			FREE_c_MLMFPA_FCP_INUSE_DataReady (sp->Data.fld_c_MLMFPA_FCP_INUSE_DataReady);
	EDFree (sp->Data.fld_c_MLMFPA_FCP_INUSE_DataReady );
			break;
		}
		
		case ID_MLMFPA_FCP_INUSE_MLMFPA_FCP_INUSE_DataReadyAck: {
			FREE_c_MLMFPA_FCP_INUSE_DataReadyAck (sp->Data.fld_c_MLMFPA_FCP_INUSE_DataReadyAck);
	EDFree (sp->Data.fld_c_MLMFPA_FCP_INUSE_DataReadyAck );
			break;
		}
		
		case ID_MLMFPA_FCP_INUSE_MLMFPA_FCP_INUSE_RestartNetworkInterface: {
			FREE_c_MLMFPA_FCP_INUSE_RestartNetworkInterface (sp->Data.fld_c_MLMFPA_FCP_INUSE_RestartNetworkInterface);
	EDFree (sp->Data.fld_c_MLMFPA_FCP_INUSE_RestartNetworkInterface );
			break;
		}
		
		case ID_MLMFPA_FCP_INUSE_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck: {
			FREE_c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck (sp->Data.fld_c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck);
	EDFree (sp->Data.fld_c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck );
			break;
		}
		
		default:;
	}

	sp->Type = ID_MLMFPA_FCP_INUSE_Unrecognized;
}

#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_EMFPKA_EMFPA_INCFG (const char* buffer, TEMFPKA_EMFPA_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal EMFPKA_EMFPA_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TEMFPKA_EMFPA_INCFG_Data (data, ID_EMFPKA_EMFPA_INCFG_EMFPKA_EMFPA_INCFG_ConfigurationRequest);
			INIT_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest (data->Data.fld_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest);
			retLen = DECODE_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_EMFPA_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TEMFPKA_EMFPA_INCFG_Data (data, ID_EMFPKA_EMFPA_INCFG_EMFPKA_EMFPA_INCFG_ConfigurationResponse);
			INIT_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse (data->Data.fld_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse);
			retLen = DECODE_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_EMFPKA_EMFPA_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_EMFPKA_EMFPA_INCFG (const char* buffer, int len, TEMFPKA_EMFPA_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_EMFPKA_EMFPA_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_EMFPKA_RSP_INUSE (const char* buffer, TEMFPKA_RSP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal EMFPKA_RSP_INUSE_RouteSelect */
		case 0x001E: {
			SETPRESENT_TEMFPKA_RSP_INUSE_Data (data, ID_EMFPKA_RSP_INUSE_EMFPKA_RSP_INUSE_RouteSelect);
			INIT_c_EMFPKA_RSP_INUSE_RouteSelect (data->Data.fld_c_EMFPKA_RSP_INUSE_RouteSelect);
			retLen = DECODE_c_EMFPKA_RSP_INUSE_RouteSelect (buffer, 0, data->Data.fld_c_EMFPKA_RSP_INUSE_RouteSelect, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_RSP_INUSE_RouteSelectAck */
		case 0x001F: {
			SETPRESENT_TEMFPKA_RSP_INUSE_Data (data, ID_EMFPKA_RSP_INUSE_EMFPKA_RSP_INUSE_RouteSelectAck);
			INIT_c_EMFPKA_RSP_INUSE_RouteSelectAck (data->Data.fld_c_EMFPKA_RSP_INUSE_RouteSelectAck);
			retLen = DECODE_c_EMFPKA_RSP_INUSE_RouteSelectAck (buffer, 0, data->Data.fld_c_EMFPKA_RSP_INUSE_RouteSelectAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_RSP_INUSE_ActivateRoute */
		case 0x0020: {
			SETPRESENT_TEMFPKA_RSP_INUSE_Data (data, ID_EMFPKA_RSP_INUSE_EMFPKA_RSP_INUSE_ActivateRoute);
			INIT_c_EMFPKA_RSP_INUSE_ActivateRoute (data->Data.fld_c_EMFPKA_RSP_INUSE_ActivateRoute);
			retLen = DECODE_c_EMFPKA_RSP_INUSE_ActivateRoute (buffer, 0, data->Data.fld_c_EMFPKA_RSP_INUSE_ActivateRoute, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_RSP_INUSE_ActivateRouteAck */
		case 0x0021: {
			SETPRESENT_TEMFPKA_RSP_INUSE_Data (data, ID_EMFPKA_RSP_INUSE_EMFPKA_RSP_INUSE_ActivateRouteAck);
			INIT_c_EMFPKA_RSP_INUSE_ActivateRouteAck (data->Data.fld_c_EMFPKA_RSP_INUSE_ActivateRouteAck);
			retLen = DECODE_c_EMFPKA_RSP_INUSE_ActivateRouteAck (buffer, 0, data->Data.fld_c_EMFPKA_RSP_INUSE_ActivateRouteAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_EMFPKA_RSP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_EMFPKA_RSP_INUSE (const char* buffer, int len, TEMFPKA_RSP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_EMFPKA_RSP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_EMFPKA_RLP_INUSE (const char* buffer, TEMFPKA_RLP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal EMFPKA_RLP_INUSE_ResetTxIndication */
		case 0x0000: {
			SETPRESENT_TEMFPKA_RLP_INUSE_Data (data, ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ResetTxIndication);
			INIT_c_EMFPKA_RLP_INUSE_ResetTxIndication (data->Data.fld_c_EMFPKA_RLP_INUSE_ResetTxIndication);
			retLen = DECODE_c_EMFPKA_RLP_INUSE_ResetTxIndication (buffer, 0, data->Data.fld_c_EMFPKA_RLP_INUSE_ResetTxIndication, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_RLP_INUSE_ResetRxIndication */
		case 0x0001: {
			SETPRESENT_TEMFPKA_RLP_INUSE_Data (data, ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ResetRxIndication);
			INIT_c_EMFPKA_RLP_INUSE_ResetRxIndication (data->Data.fld_c_EMFPKA_RLP_INUSE_ResetRxIndication);
			retLen = DECODE_c_EMFPKA_RLP_INUSE_ResetRxIndication (buffer, 0, data->Data.fld_c_EMFPKA_RLP_INUSE_ResetRxIndication, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_RLP_INUSE_ResetTxIndicationAck */
		case 0x000D: {
			SETPRESENT_TEMFPKA_RLP_INUSE_Data (data, ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ResetTxIndicationAck);
			INIT_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck (data->Data.fld_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck);
			retLen = DECODE_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck (buffer, 0, data->Data.fld_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_RLP_INUSE_ResetTxComplete */
		case 0x000E: {
			SETPRESENT_TEMFPKA_RLP_INUSE_Data (data, ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ResetTxComplete);
			INIT_c_EMFPKA_RLP_INUSE_ResetTxComplete (data->Data.fld_c_EMFPKA_RLP_INUSE_ResetTxComplete);
			retLen = DECODE_c_EMFPKA_RLP_INUSE_ResetTxComplete (buffer, 0, data->Data.fld_c_EMFPKA_RLP_INUSE_ResetTxComplete, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_RLP_INUSE_ResetRxComplete */
		case 0x000F: {
			SETPRESENT_TEMFPKA_RLP_INUSE_Data (data, ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ResetRxComplete);
			INIT_c_EMFPKA_RLP_INUSE_ResetRxComplete (data->Data.fld_c_EMFPKA_RLP_INUSE_ResetRxComplete);
			retLen = DECODE_c_EMFPKA_RLP_INUSE_ResetRxComplete (buffer, 0, data->Data.fld_c_EMFPKA_RLP_INUSE_ResetRxComplete, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_RLP_INUSE_Nak */
		case 0x0002: {
			SETPRESENT_TEMFPKA_RLP_INUSE_Data (data, ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_Nak);
			INIT_c_EMFPKA_RLP_INUSE_Nak (data->Data.fld_c_EMFPKA_RLP_INUSE_Nak);
			retLen = DECODE_c_EMFPKA_RLP_INUSE_Nak (buffer, 0, data->Data.fld_c_EMFPKA_RLP_INUSE_Nak, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_RLP_INUSE_ReservationOnRequest */
		case 0x0016: {
			SETPRESENT_TEMFPKA_RLP_INUSE_Data (data, ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ReservationOnRequest);
			INIT_c_EMFPKA_RLP_INUSE_ReservationOnRequest (data->Data.fld_c_EMFPKA_RLP_INUSE_ReservationOnRequest);
			retLen = DECODE_c_EMFPKA_RLP_INUSE_ReservationOnRequest (buffer, 0, data->Data.fld_c_EMFPKA_RLP_INUSE_ReservationOnRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_RLP_INUSE_ReservationOffRequest */
		case 0x0017: {
			SETPRESENT_TEMFPKA_RLP_INUSE_Data (data, ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ReservationOffRequest);
			INIT_c_EMFPKA_RLP_INUSE_ReservationOffRequest (data->Data.fld_c_EMFPKA_RLP_INUSE_ReservationOffRequest);
			retLen = DECODE_c_EMFPKA_RLP_INUSE_ReservationOffRequest (buffer, 0, data->Data.fld_c_EMFPKA_RLP_INUSE_ReservationOffRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_RLP_INUSE_ReservationAccept */
		case 0x0018: {
			SETPRESENT_TEMFPKA_RLP_INUSE_Data (data, ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ReservationAccept);
			INIT_c_EMFPKA_RLP_INUSE_ReservationAccept (data->Data.fld_c_EMFPKA_RLP_INUSE_ReservationAccept);
			retLen = DECODE_c_EMFPKA_RLP_INUSE_ReservationAccept (buffer, 0, data->Data.fld_c_EMFPKA_RLP_INUSE_ReservationAccept, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_RLP_INUSE_ReservationReject */
		case 0x0019: {
			SETPRESENT_TEMFPKA_RLP_INUSE_Data (data, ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_ReservationReject);
			INIT_c_EMFPKA_RLP_INUSE_ReservationReject (data->Data.fld_c_EMFPKA_RLP_INUSE_ReservationReject);
			retLen = DECODE_c_EMFPKA_RLP_INUSE_ReservationReject (buffer, 0, data->Data.fld_c_EMFPKA_RLP_INUSE_ReservationReject, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_RLP_INUSE_RevReservationOn */
		case 0x001A: {
			SETPRESENT_TEMFPKA_RLP_INUSE_Data (data, ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_RevReservationOn);
			INIT_c_EMFPKA_RLP_INUSE_RevReservationOn (data->Data.fld_c_EMFPKA_RLP_INUSE_RevReservationOn);
			retLen = DECODE_c_EMFPKA_RLP_INUSE_RevReservationOn (buffer, 0, data->Data.fld_c_EMFPKA_RLP_INUSE_RevReservationOn, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_RLP_INUSE_RevReservationOff */
		case 0x001B: {
			SETPRESENT_TEMFPKA_RLP_INUSE_Data (data, ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_RevReservationOff);
			INIT_c_EMFPKA_RLP_INUSE_RevReservationOff (data->Data.fld_c_EMFPKA_RLP_INUSE_RevReservationOff);
			retLen = DECODE_c_EMFPKA_RLP_INUSE_RevReservationOff (buffer, 0, data->Data.fld_c_EMFPKA_RLP_INUSE_RevReservationOff, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_RLP_INUSE_FwdReservationOff */
		case 0x0022: {
			SETPRESENT_TEMFPKA_RLP_INUSE_Data (data, ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_FwdReservationOff);
			INIT_c_EMFPKA_RLP_INUSE_FwdReservationOff (data->Data.fld_c_EMFPKA_RLP_INUSE_FwdReservationOff);
			retLen = DECODE_c_EMFPKA_RLP_INUSE_FwdReservationOff (buffer, 0, data->Data.fld_c_EMFPKA_RLP_INUSE_FwdReservationOff, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_RLP_INUSE_FwdReservationOn */
		case 0x0023: {
			SETPRESENT_TEMFPKA_RLP_INUSE_Data (data, ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_FwdReservationOn);
			INIT_c_EMFPKA_RLP_INUSE_FwdReservationOn (data->Data.fld_c_EMFPKA_RLP_INUSE_FwdReservationOn);
			retLen = DECODE_c_EMFPKA_RLP_INUSE_FwdReservationOn (buffer, 0, data->Data.fld_c_EMFPKA_RLP_INUSE_FwdReservationOn, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_RLP_INUSE_FwdReservationAck */
		case 0x0024: {
			SETPRESENT_TEMFPKA_RLP_INUSE_Data (data, ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_FwdReservationAck);
			INIT_c_EMFPKA_RLP_INUSE_FwdReservationAck (data->Data.fld_c_EMFPKA_RLP_INUSE_FwdReservationAck);
			retLen = DECODE_c_EMFPKA_RLP_INUSE_FwdReservationAck (buffer, 0, data->Data.fld_c_EMFPKA_RLP_INUSE_FwdReservationAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_RLP_INUSE_AttributeUpdateRequest */
		case 0x0052: {
			SETPRESENT_TEMFPKA_RLP_INUSE_Data (data, ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_AttributeUpdateRequest);
			INIT_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest (data->Data.fld_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest);
			retLen = DECODE_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_RLP_INUSE_AttributeUpdateAccept */
		case 0x0053: {
			SETPRESENT_TEMFPKA_RLP_INUSE_Data (data, ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_AttributeUpdateAccept);
			INIT_c_EMFPKA_RLP_INUSE_AttributeUpdateAccept (data->Data.fld_c_EMFPKA_RLP_INUSE_AttributeUpdateAccept);
			retLen = DECODE_c_EMFPKA_RLP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_EMFPKA_RLP_INUSE_AttributeUpdateAccept, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_RLP_INUSE_AttributeUpdateReject */
		case 0x0054: {
			SETPRESENT_TEMFPKA_RLP_INUSE_Data (data, ID_EMFPKA_RLP_INUSE_EMFPKA_RLP_INUSE_AttributeUpdateReject);
			INIT_c_EMFPKA_RLP_INUSE_AttributeUpdateReject (data->Data.fld_c_EMFPKA_RLP_INUSE_AttributeUpdateReject);
			retLen = DECODE_c_EMFPKA_RLP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_EMFPKA_RLP_INUSE_AttributeUpdateReject, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_EMFPKA_RLP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_EMFPKA_RLP_INUSE (const char* buffer, int len, TEMFPKA_RLP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_EMFPKA_RLP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_EMFPKA_DOSP_INUSE (const char* buffer, TEMFPKA_DOSP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal EMFPKA_DOSP_INUSE_DataOverSignaling */
		case 0x0014: {
			SETPRESENT_TEMFPKA_DOSP_INUSE_Data (data, ID_EMFPKA_DOSP_INUSE_EMFPKA_DOSP_INUSE_DataOverSignaling);
			INIT_c_EMFPKA_DOSP_INUSE_DataOverSignaling (data->Data.fld_c_EMFPKA_DOSP_INUSE_DataOverSignaling);
			retLen = DECODE_c_EMFPKA_DOSP_INUSE_DataOverSignaling (buffer, 0, data->Data.fld_c_EMFPKA_DOSP_INUSE_DataOverSignaling, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_DOSP_INUSE_DataOverSignalingAck */
		case 0x0015: {
			SETPRESENT_TEMFPKA_DOSP_INUSE_Data (data, ID_EMFPKA_DOSP_INUSE_EMFPKA_DOSP_INUSE_DataOverSignalingAck);
			INIT_c_EMFPKA_DOSP_INUSE_DataOverSignalingAck (data->Data.fld_c_EMFPKA_DOSP_INUSE_DataOverSignalingAck);
			retLen = DECODE_c_EMFPKA_DOSP_INUSE_DataOverSignalingAck (buffer, 0, data->Data.fld_c_EMFPKA_DOSP_INUSE_DataOverSignalingAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_EMFPKA_DOSP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_EMFPKA_DOSP_INUSE (const char* buffer, int len, TEMFPKA_DOSP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_EMFPKA_DOSP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_EMFPKA_LUP_INUSE (const char* buffer, TEMFPKA_LUP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal EMFPKA_LUP_INUSE_LocationRequest */
		case 0x0003: {
			SETPRESENT_TEMFPKA_LUP_INUSE_Data (data, ID_EMFPKA_LUP_INUSE_EMFPKA_LUP_INUSE_LocationRequest);
			INIT_c_EMFPKA_LUP_INUSE_LocationRequest (data->Data.fld_c_EMFPKA_LUP_INUSE_LocationRequest);
			retLen = DECODE_c_EMFPKA_LUP_INUSE_LocationRequest (buffer, 0, data->Data.fld_c_EMFPKA_LUP_INUSE_LocationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_LUP_INUSE_LocationNotification */
		case 0x0004: {
			SETPRESENT_TEMFPKA_LUP_INUSE_Data (data, ID_EMFPKA_LUP_INUSE_EMFPKA_LUP_INUSE_LocationNotification);
			INIT_c_EMFPKA_LUP_INUSE_LocationNotification (data->Data.fld_c_EMFPKA_LUP_INUSE_LocationNotification);
			retLen = DECODE_c_EMFPKA_LUP_INUSE_LocationNotification (buffer, 0, data->Data.fld_c_EMFPKA_LUP_INUSE_LocationNotification, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_LUP_INUSE_LocationAssignment */
		case 0x0005: {
			SETPRESENT_TEMFPKA_LUP_INUSE_Data (data, ID_EMFPKA_LUP_INUSE_EMFPKA_LUP_INUSE_LocationAssignment);
			INIT_c_EMFPKA_LUP_INUSE_LocationAssignment (data->Data.fld_c_EMFPKA_LUP_INUSE_LocationAssignment);
			retLen = DECODE_c_EMFPKA_LUP_INUSE_LocationAssignment (buffer, 0, data->Data.fld_c_EMFPKA_LUP_INUSE_LocationAssignment, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_LUP_INUSE_LocationComplete */
		case 0x0006: {
			SETPRESENT_TEMFPKA_LUP_INUSE_Data (data, ID_EMFPKA_LUP_INUSE_EMFPKA_LUP_INUSE_LocationComplete);
			INIT_c_EMFPKA_LUP_INUSE_LocationComplete (data->Data.fld_c_EMFPKA_LUP_INUSE_LocationComplete);
			retLen = DECODE_c_EMFPKA_LUP_INUSE_LocationComplete (buffer, 0, data->Data.fld_c_EMFPKA_LUP_INUSE_LocationComplete, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_LUP_INUSE_StorageBLOBRequest */
		case 0x0010: {
			SETPRESENT_TEMFPKA_LUP_INUSE_Data (data, ID_EMFPKA_LUP_INUSE_EMFPKA_LUP_INUSE_StorageBLOBRequest);
			INIT_c_EMFPKA_LUP_INUSE_StorageBLOBRequest (data->Data.fld_c_EMFPKA_LUP_INUSE_StorageBLOBRequest);
			retLen = DECODE_c_EMFPKA_LUP_INUSE_StorageBLOBRequest (buffer, 0, data->Data.fld_c_EMFPKA_LUP_INUSE_StorageBLOBRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_LUP_INUSE_StorageBLOBNotification */
		case 0x0011: {
			SETPRESENT_TEMFPKA_LUP_INUSE_Data (data, ID_EMFPKA_LUP_INUSE_EMFPKA_LUP_INUSE_StorageBLOBNotification);
			INIT_c_EMFPKA_LUP_INUSE_StorageBLOBNotification (data->Data.fld_c_EMFPKA_LUP_INUSE_StorageBLOBNotification);
			retLen = DECODE_c_EMFPKA_LUP_INUSE_StorageBLOBNotification (buffer, 0, data->Data.fld_c_EMFPKA_LUP_INUSE_StorageBLOBNotification, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_LUP_INUSE_StorageBLOBAssignment */
		case 0x0012: {
			SETPRESENT_TEMFPKA_LUP_INUSE_Data (data, ID_EMFPKA_LUP_INUSE_EMFPKA_LUP_INUSE_StorageBLOBAssignment);
			INIT_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment (data->Data.fld_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment);
			retLen = DECODE_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment (buffer, 0, data->Data.fld_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_LUP_INUSE_StorageBLOBComplete */
		case 0x0013: {
			SETPRESENT_TEMFPKA_LUP_INUSE_Data (data, ID_EMFPKA_LUP_INUSE_EMFPKA_LUP_INUSE_StorageBLOBComplete);
			INIT_c_EMFPKA_LUP_INUSE_StorageBLOBComplete (data->Data.fld_c_EMFPKA_LUP_INUSE_StorageBLOBComplete);
			retLen = DECODE_c_EMFPKA_LUP_INUSE_StorageBLOBComplete (buffer, 0, data->Data.fld_c_EMFPKA_LUP_INUSE_StorageBLOBComplete, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_EMFPKA_LUP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_EMFPKA_LUP_INUSE (const char* buffer, int len, TEMFPKA_LUP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_EMFPKA_LUP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_EMFPKA_FCP_INUSE (const char* buffer, TEMFPKA_FCP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal EMFPKA_FCP_INUSE_XonRequest */
		case 0x0007: {
			SETPRESENT_TEMFPKA_FCP_INUSE_Data (data, ID_EMFPKA_FCP_INUSE_EMFPKA_FCP_INUSE_XonRequest);
			INIT_c_EMFPKA_FCP_INUSE_XonRequest (data->Data.fld_c_EMFPKA_FCP_INUSE_XonRequest);
			retLen = DECODE_c_EMFPKA_FCP_INUSE_XonRequest (buffer, 0, data->Data.fld_c_EMFPKA_FCP_INUSE_XonRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_FCP_INUSE_XonResponse */
		case 0x0008: {
			SETPRESENT_TEMFPKA_FCP_INUSE_Data (data, ID_EMFPKA_FCP_INUSE_EMFPKA_FCP_INUSE_XonResponse);
			INIT_c_EMFPKA_FCP_INUSE_XonResponse (data->Data.fld_c_EMFPKA_FCP_INUSE_XonResponse);
			retLen = DECODE_c_EMFPKA_FCP_INUSE_XonResponse (buffer, 0, data->Data.fld_c_EMFPKA_FCP_INUSE_XonResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_FCP_INUSE_XoffRequest */
		case 0x0009: {
			SETPRESENT_TEMFPKA_FCP_INUSE_Data (data, ID_EMFPKA_FCP_INUSE_EMFPKA_FCP_INUSE_XoffRequest);
			INIT_c_EMFPKA_FCP_INUSE_XoffRequest (data->Data.fld_c_EMFPKA_FCP_INUSE_XoffRequest);
			retLen = DECODE_c_EMFPKA_FCP_INUSE_XoffRequest (buffer, 0, data->Data.fld_c_EMFPKA_FCP_INUSE_XoffRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_FCP_INUSE_XoffResponse */
		case 0x000A: {
			SETPRESENT_TEMFPKA_FCP_INUSE_Data (data, ID_EMFPKA_FCP_INUSE_EMFPKA_FCP_INUSE_XoffResponse);
			INIT_c_EMFPKA_FCP_INUSE_XoffResponse (data->Data.fld_c_EMFPKA_FCP_INUSE_XoffResponse);
			retLen = DECODE_c_EMFPKA_FCP_INUSE_XoffResponse (buffer, 0, data->Data.fld_c_EMFPKA_FCP_INUSE_XoffResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_FCP_INUSE_DataReady */
		case 0x000B: {
			SETPRESENT_TEMFPKA_FCP_INUSE_Data (data, ID_EMFPKA_FCP_INUSE_EMFPKA_FCP_INUSE_DataReady);
			INIT_c_EMFPKA_FCP_INUSE_DataReady (data->Data.fld_c_EMFPKA_FCP_INUSE_DataReady);
			retLen = DECODE_c_EMFPKA_FCP_INUSE_DataReady (buffer, 0, data->Data.fld_c_EMFPKA_FCP_INUSE_DataReady, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_FCP_INUSE_DataReadyAck */
		case 0x000C: {
			SETPRESENT_TEMFPKA_FCP_INUSE_Data (data, ID_EMFPKA_FCP_INUSE_EMFPKA_FCP_INUSE_DataReadyAck);
			INIT_c_EMFPKA_FCP_INUSE_DataReadyAck (data->Data.fld_c_EMFPKA_FCP_INUSE_DataReadyAck);
			retLen = DECODE_c_EMFPKA_FCP_INUSE_DataReadyAck (buffer, 0, data->Data.fld_c_EMFPKA_FCP_INUSE_DataReadyAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_FCP_INUSE_RestartNetworkInterface */
		case 0x001C: {
			SETPRESENT_TEMFPKA_FCP_INUSE_Data (data, ID_EMFPKA_FCP_INUSE_EMFPKA_FCP_INUSE_RestartNetworkInterface);
			INIT_c_EMFPKA_FCP_INUSE_RestartNetworkInterface (data->Data.fld_c_EMFPKA_FCP_INUSE_RestartNetworkInterface);
			retLen = DECODE_c_EMFPKA_FCP_INUSE_RestartNetworkInterface (buffer, 0, data->Data.fld_c_EMFPKA_FCP_INUSE_RestartNetworkInterface, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck */
		case 0x001D: {
			SETPRESENT_TEMFPKA_FCP_INUSE_Data (data, ID_EMFPKA_FCP_INUSE_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck);
			INIT_c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck (data->Data.fld_c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck);
			retLen = DECODE_c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck (buffer, 0, data->Data.fld_c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_EMFPKA_FCP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_EMFPKA_FCP_INUSE (const char* buffer, int len, TEMFPKA_FCP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_EMFPKA_FCP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_MLMFPA_MMFPA_INCFG (const char* buffer, TMLMFPA_MMFPA_INCFG_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal MLMFPA_MMFPA_INCFG_ConfigurationRequest */
		case 0x0050: {
			SETPRESENT_TMLMFPA_MMFPA_INCFG_Data (data, ID_MLMFPA_MMFPA_INCFG_MLMFPA_MMFPA_INCFG_ConfigurationRequest);
			INIT_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest (data->Data.fld_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest);
			retLen = DECODE_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest (buffer, 0, data->Data.fld_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_MMFPA_INCFG_ConfigurationResponse */
		case 0x0051: {
			SETPRESENT_TMLMFPA_MMFPA_INCFG_Data (data, ID_MLMFPA_MMFPA_INCFG_MLMFPA_MMFPA_INCFG_ConfigurationResponse);
			INIT_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse (data->Data.fld_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse);
			retLen = DECODE_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse (buffer, 0, data->Data.fld_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_MLMFPA_MMFPA_INCFG_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MLMFPA_MMFPA_INCFG (const char* buffer, int len, TMLMFPA_MMFPA_INCFG_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_MLMFPA_MMFPA_INCFG (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_MLMFPA_RSP_INUSE (const char* buffer, TMLMFPA_RSP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal MLMFPA_RSP_INUSE_RouteSelect */
		case 0x001E: {
			SETPRESENT_TMLMFPA_RSP_INUSE_Data (data, ID_MLMFPA_RSP_INUSE_MLMFPA_RSP_INUSE_RouteSelect);
			INIT_c_MLMFPA_RSP_INUSE_RouteSelect (data->Data.fld_c_MLMFPA_RSP_INUSE_RouteSelect);
			retLen = DECODE_c_MLMFPA_RSP_INUSE_RouteSelect (buffer, 0, data->Data.fld_c_MLMFPA_RSP_INUSE_RouteSelect, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_RSP_INUSE_RouteSelectAck */
		case 0x001F: {
			SETPRESENT_TMLMFPA_RSP_INUSE_Data (data, ID_MLMFPA_RSP_INUSE_MLMFPA_RSP_INUSE_RouteSelectAck);
			INIT_c_MLMFPA_RSP_INUSE_RouteSelectAck (data->Data.fld_c_MLMFPA_RSP_INUSE_RouteSelectAck);
			retLen = DECODE_c_MLMFPA_RSP_INUSE_RouteSelectAck (buffer, 0, data->Data.fld_c_MLMFPA_RSP_INUSE_RouteSelectAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_RSP_INUSE_ActivateRoute */
		case 0x0020: {
			SETPRESENT_TMLMFPA_RSP_INUSE_Data (data, ID_MLMFPA_RSP_INUSE_MLMFPA_RSP_INUSE_ActivateRoute);
			INIT_c_MLMFPA_RSP_INUSE_ActivateRoute (data->Data.fld_c_MLMFPA_RSP_INUSE_ActivateRoute);
			retLen = DECODE_c_MLMFPA_RSP_INUSE_ActivateRoute (buffer, 0, data->Data.fld_c_MLMFPA_RSP_INUSE_ActivateRoute, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_RSP_INUSE_ActivateRouteAck */
		case 0x0021: {
			SETPRESENT_TMLMFPA_RSP_INUSE_Data (data, ID_MLMFPA_RSP_INUSE_MLMFPA_RSP_INUSE_ActivateRouteAck);
			INIT_c_MLMFPA_RSP_INUSE_ActivateRouteAck (data->Data.fld_c_MLMFPA_RSP_INUSE_ActivateRouteAck);
			retLen = DECODE_c_MLMFPA_RSP_INUSE_ActivateRouteAck (buffer, 0, data->Data.fld_c_MLMFPA_RSP_INUSE_ActivateRouteAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_MLMFPA_RSP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MLMFPA_RSP_INUSE (const char* buffer, int len, TMLMFPA_RSP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_MLMFPA_RSP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_MLMFPA_SRP_INUSE (const char* buffer, TMLMFPA_SRP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal MLMFPA_SRP_INUSE_ResetTxIndication */
		case 0x0000: {
			SETPRESENT_TMLMFPA_SRP_INUSE_Data (data, ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ResetTxIndication);
			INIT_c_MLMFPA_SRP_INUSE_ResetTxIndication (data->Data.fld_c_MLMFPA_SRP_INUSE_ResetTxIndication);
			retLen = DECODE_c_MLMFPA_SRP_INUSE_ResetTxIndication (buffer, 0, data->Data.fld_c_MLMFPA_SRP_INUSE_ResetTxIndication, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_SRP_INUSE_ResetRxIndication */
		case 0x0001: {
			SETPRESENT_TMLMFPA_SRP_INUSE_Data (data, ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ResetRxIndication);
			INIT_c_MLMFPA_SRP_INUSE_ResetRxIndication (data->Data.fld_c_MLMFPA_SRP_INUSE_ResetRxIndication);
			retLen = DECODE_c_MLMFPA_SRP_INUSE_ResetRxIndication (buffer, 0, data->Data.fld_c_MLMFPA_SRP_INUSE_ResetRxIndication, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_SRP_INUSE_ResetTxIndicationAck */
		case 0x000D: {
			SETPRESENT_TMLMFPA_SRP_INUSE_Data (data, ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ResetTxIndicationAck);
			INIT_c_MLMFPA_SRP_INUSE_ResetTxIndicationAck (data->Data.fld_c_MLMFPA_SRP_INUSE_ResetTxIndicationAck);
			retLen = DECODE_c_MLMFPA_SRP_INUSE_ResetTxIndicationAck (buffer, 0, data->Data.fld_c_MLMFPA_SRP_INUSE_ResetTxIndicationAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_SRP_INUSE_ResetTxComplete */
		case 0x000E: {
			SETPRESENT_TMLMFPA_SRP_INUSE_Data (data, ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ResetTxComplete);
			INIT_c_MLMFPA_SRP_INUSE_ResetTxComplete (data->Data.fld_c_MLMFPA_SRP_INUSE_ResetTxComplete);
			retLen = DECODE_c_MLMFPA_SRP_INUSE_ResetTxComplete (buffer, 0, data->Data.fld_c_MLMFPA_SRP_INUSE_ResetTxComplete, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_SRP_INUSE_ResetRxComplete */
		case 0x000F: {
			SETPRESENT_TMLMFPA_SRP_INUSE_Data (data, ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ResetRxComplete);
			INIT_c_MLMFPA_SRP_INUSE_ResetRxComplete (data->Data.fld_c_MLMFPA_SRP_INUSE_ResetRxComplete);
			retLen = DECODE_c_MLMFPA_SRP_INUSE_ResetRxComplete (buffer, 0, data->Data.fld_c_MLMFPA_SRP_INUSE_ResetRxComplete, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_SRP_INUSE_MultiLinkNak */
		case 0x0025: {
			SETPRESENT_TMLMFPA_SRP_INUSE_Data (data, ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_MultiLinkNak);
			INIT_c_MLMFPA_SRP_INUSE_MultiLinkNak (data->Data.fld_c_MLMFPA_SRP_INUSE_MultiLinkNak);
			retLen = DECODE_c_MLMFPA_SRP_INUSE_MultiLinkNak (buffer, 0, data->Data.fld_c_MLMFPA_SRP_INUSE_MultiLinkNak, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_SRP_INUSE_ReservationOnRequest */
		case 0x0016: {
			SETPRESENT_TMLMFPA_SRP_INUSE_Data (data, ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ReservationOnRequest);
			INIT_c_MLMFPA_SRP_INUSE_ReservationOnRequest (data->Data.fld_c_MLMFPA_SRP_INUSE_ReservationOnRequest);
			retLen = DECODE_c_MLMFPA_SRP_INUSE_ReservationOnRequest (buffer, 0, data->Data.fld_c_MLMFPA_SRP_INUSE_ReservationOnRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_SRP_INUSE_ReservationOffRequest */
		case 0x0017: {
			SETPRESENT_TMLMFPA_SRP_INUSE_Data (data, ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ReservationOffRequest);
			INIT_c_MLMFPA_SRP_INUSE_ReservationOffRequest (data->Data.fld_c_MLMFPA_SRP_INUSE_ReservationOffRequest);
			retLen = DECODE_c_MLMFPA_SRP_INUSE_ReservationOffRequest (buffer, 0, data->Data.fld_c_MLMFPA_SRP_INUSE_ReservationOffRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_SRP_INUSE_ReservationAccept */
		case 0x0018: {
			SETPRESENT_TMLMFPA_SRP_INUSE_Data (data, ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ReservationAccept);
			INIT_c_MLMFPA_SRP_INUSE_ReservationAccept (data->Data.fld_c_MLMFPA_SRP_INUSE_ReservationAccept);
			retLen = DECODE_c_MLMFPA_SRP_INUSE_ReservationAccept (buffer, 0, data->Data.fld_c_MLMFPA_SRP_INUSE_ReservationAccept, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_SRP_INUSE_ReservationReject */
		case 0x0019: {
			SETPRESENT_TMLMFPA_SRP_INUSE_Data (data, ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_ReservationReject);
			INIT_c_MLMFPA_SRP_INUSE_ReservationReject (data->Data.fld_c_MLMFPA_SRP_INUSE_ReservationReject);
			retLen = DECODE_c_MLMFPA_SRP_INUSE_ReservationReject (buffer, 0, data->Data.fld_c_MLMFPA_SRP_INUSE_ReservationReject, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_SRP_INUSE_RevReservationOn */
		case 0x001A: {
			SETPRESENT_TMLMFPA_SRP_INUSE_Data (data, ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_RevReservationOn);
			INIT_c_MLMFPA_SRP_INUSE_RevReservationOn (data->Data.fld_c_MLMFPA_SRP_INUSE_RevReservationOn);
			retLen = DECODE_c_MLMFPA_SRP_INUSE_RevReservationOn (buffer, 0, data->Data.fld_c_MLMFPA_SRP_INUSE_RevReservationOn, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_SRP_INUSE_RevReservationOff */
		case 0x001B: {
			SETPRESENT_TMLMFPA_SRP_INUSE_Data (data, ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_RevReservationOff);
			INIT_c_MLMFPA_SRP_INUSE_RevReservationOff (data->Data.fld_c_MLMFPA_SRP_INUSE_RevReservationOff);
			retLen = DECODE_c_MLMFPA_SRP_INUSE_RevReservationOff (buffer, 0, data->Data.fld_c_MLMFPA_SRP_INUSE_RevReservationOff, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_SRP_INUSE_FwdReservationOff */
		case 0x0022: {
			SETPRESENT_TMLMFPA_SRP_INUSE_Data (data, ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_FwdReservationOff);
			INIT_c_MLMFPA_SRP_INUSE_FwdReservationOff (data->Data.fld_c_MLMFPA_SRP_INUSE_FwdReservationOff);
			retLen = DECODE_c_MLMFPA_SRP_INUSE_FwdReservationOff (buffer, 0, data->Data.fld_c_MLMFPA_SRP_INUSE_FwdReservationOff, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_SRP_INUSE_FwdReservationOn */
		case 0x0023: {
			SETPRESENT_TMLMFPA_SRP_INUSE_Data (data, ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_FwdReservationOn);
			INIT_c_MLMFPA_SRP_INUSE_FwdReservationOn (data->Data.fld_c_MLMFPA_SRP_INUSE_FwdReservationOn);
			retLen = DECODE_c_MLMFPA_SRP_INUSE_FwdReservationOn (buffer, 0, data->Data.fld_c_MLMFPA_SRP_INUSE_FwdReservationOn, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_SRP_INUSE_FwdReservationAck */
		case 0x0024: {
			SETPRESENT_TMLMFPA_SRP_INUSE_Data (data, ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_FwdReservationAck);
			INIT_c_MLMFPA_SRP_INUSE_FwdReservationAck (data->Data.fld_c_MLMFPA_SRP_INUSE_FwdReservationAck);
			retLen = DECODE_c_MLMFPA_SRP_INUSE_FwdReservationAck (buffer, 0, data->Data.fld_c_MLMFPA_SRP_INUSE_FwdReservationAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_SRP_INUSE_AttributeUpdateRequest */
		case 0x0052: {
			SETPRESENT_TMLMFPA_SRP_INUSE_Data (data, ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_AttributeUpdateRequest);
			INIT_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest (data->Data.fld_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest);
			retLen = DECODE_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest (buffer, 0, data->Data.fld_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_SRP_INUSE_AttributeUpdateAccept */
		case 0x0053: {
			SETPRESENT_TMLMFPA_SRP_INUSE_Data (data, ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_AttributeUpdateAccept);
			INIT_c_MLMFPA_SRP_INUSE_AttributeUpdateAccept (data->Data.fld_c_MLMFPA_SRP_INUSE_AttributeUpdateAccept);
			retLen = DECODE_c_MLMFPA_SRP_INUSE_AttributeUpdateAccept (buffer, 0, data->Data.fld_c_MLMFPA_SRP_INUSE_AttributeUpdateAccept, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_SRP_INUSE_AttributeUpdateReject */
		case 0x0054: {
			SETPRESENT_TMLMFPA_SRP_INUSE_Data (data, ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_AttributeUpdateReject);
			INIT_c_MLMFPA_SRP_INUSE_AttributeUpdateReject (data->Data.fld_c_MLMFPA_SRP_INUSE_AttributeUpdateReject);
			retLen = DECODE_c_MLMFPA_SRP_INUSE_AttributeUpdateReject (buffer, 0, data->Data.fld_c_MLMFPA_SRP_INUSE_AttributeUpdateReject, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_SRP_INUSE_Flush */
		case 0x0026: {
			SETPRESENT_TMLMFPA_SRP_INUSE_Data (data, ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_Flush);
			INIT_c_MLMFPA_SRP_INUSE_Flush (data->Data.fld_c_MLMFPA_SRP_INUSE_Flush);
			retLen = DECODE_c_MLMFPA_SRP_INUSE_Flush (buffer, 0, data->Data.fld_c_MLMFPA_SRP_INUSE_Flush, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_SRP_INUSE_Nak */
		case 0x0002: {
			SETPRESENT_TMLMFPA_SRP_INUSE_Data (data, ID_MLMFPA_SRP_INUSE_MLMFPA_SRP_INUSE_Nak);
			INIT_c_MLMFPA_SRP_INUSE_Nak (data->Data.fld_c_MLMFPA_SRP_INUSE_Nak);
			retLen = DECODE_c_MLMFPA_SRP_INUSE_Nak (buffer, 0, data->Data.fld_c_MLMFPA_SRP_INUSE_Nak, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_MLMFPA_SRP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MLMFPA_SRP_INUSE (const char* buffer, int len, TMLMFPA_SRP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_MLMFPA_SRP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_MLMFPA_DOSP_INUSE (const char* buffer, TMLMFPA_DOSP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal MLMFPA_DOSP_INUSE_DataOverSignaling */
		case 0x0014: {
			SETPRESENT_TMLMFPA_DOSP_INUSE_Data (data, ID_MLMFPA_DOSP_INUSE_MLMFPA_DOSP_INUSE_DataOverSignaling);
			INIT_c_MLMFPA_DOSP_INUSE_DataOverSignaling (data->Data.fld_c_MLMFPA_DOSP_INUSE_DataOverSignaling);
			retLen = DECODE_c_MLMFPA_DOSP_INUSE_DataOverSignaling (buffer, 0, data->Data.fld_c_MLMFPA_DOSP_INUSE_DataOverSignaling, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_DOSP_INUSE_DataOverSignalingAck */
		case 0x0015: {
			SETPRESENT_TMLMFPA_DOSP_INUSE_Data (data, ID_MLMFPA_DOSP_INUSE_MLMFPA_DOSP_INUSE_DataOverSignalingAck);
			INIT_c_MLMFPA_DOSP_INUSE_DataOverSignalingAck (data->Data.fld_c_MLMFPA_DOSP_INUSE_DataOverSignalingAck);
			retLen = DECODE_c_MLMFPA_DOSP_INUSE_DataOverSignalingAck (buffer, 0, data->Data.fld_c_MLMFPA_DOSP_INUSE_DataOverSignalingAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_MLMFPA_DOSP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MLMFPA_DOSP_INUSE (const char* buffer, int len, TMLMFPA_DOSP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_MLMFPA_DOSP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_MLMFPA_LUP_INUSE (const char* buffer, TMLMFPA_LUP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal MLMFPA_LUP_INUSE_LocationRequest */
		case 0x0003: {
			SETPRESENT_TMLMFPA_LUP_INUSE_Data (data, ID_MLMFPA_LUP_INUSE_MLMFPA_LUP_INUSE_LocationRequest);
			INIT_c_MLMFPA_LUP_INUSE_LocationRequest (data->Data.fld_c_MLMFPA_LUP_INUSE_LocationRequest);
			retLen = DECODE_c_MLMFPA_LUP_INUSE_LocationRequest (buffer, 0, data->Data.fld_c_MLMFPA_LUP_INUSE_LocationRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_LUP_INUSE_LocationNotification */
		case 0x0004: {
			SETPRESENT_TMLMFPA_LUP_INUSE_Data (data, ID_MLMFPA_LUP_INUSE_MLMFPA_LUP_INUSE_LocationNotification);
			INIT_c_MLMFPA_LUP_INUSE_LocationNotification (data->Data.fld_c_MLMFPA_LUP_INUSE_LocationNotification);
			retLen = DECODE_c_MLMFPA_LUP_INUSE_LocationNotification (buffer, 0, data->Data.fld_c_MLMFPA_LUP_INUSE_LocationNotification, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_LUP_INUSE_LocationAssignment */
		case 0x0005: {
			SETPRESENT_TMLMFPA_LUP_INUSE_Data (data, ID_MLMFPA_LUP_INUSE_MLMFPA_LUP_INUSE_LocationAssignment);
			INIT_c_MLMFPA_LUP_INUSE_LocationAssignment (data->Data.fld_c_MLMFPA_LUP_INUSE_LocationAssignment);
			retLen = DECODE_c_MLMFPA_LUP_INUSE_LocationAssignment (buffer, 0, data->Data.fld_c_MLMFPA_LUP_INUSE_LocationAssignment, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_LUP_INUSE_LocationComplete */
		case 0x0006: {
			SETPRESENT_TMLMFPA_LUP_INUSE_Data (data, ID_MLMFPA_LUP_INUSE_MLMFPA_LUP_INUSE_LocationComplete);
			INIT_c_MLMFPA_LUP_INUSE_LocationComplete (data->Data.fld_c_MLMFPA_LUP_INUSE_LocationComplete);
			retLen = DECODE_c_MLMFPA_LUP_INUSE_LocationComplete (buffer, 0, data->Data.fld_c_MLMFPA_LUP_INUSE_LocationComplete, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_LUP_INUSE_StorageBLOBRequest */
		case 0x0010: {
			SETPRESENT_TMLMFPA_LUP_INUSE_Data (data, ID_MLMFPA_LUP_INUSE_MLMFPA_LUP_INUSE_StorageBLOBRequest);
			INIT_c_MLMFPA_LUP_INUSE_StorageBLOBRequest (data->Data.fld_c_MLMFPA_LUP_INUSE_StorageBLOBRequest);
			retLen = DECODE_c_MLMFPA_LUP_INUSE_StorageBLOBRequest (buffer, 0, data->Data.fld_c_MLMFPA_LUP_INUSE_StorageBLOBRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_LUP_INUSE_StorageBLOBNotification */
		case 0x0011: {
			SETPRESENT_TMLMFPA_LUP_INUSE_Data (data, ID_MLMFPA_LUP_INUSE_MLMFPA_LUP_INUSE_StorageBLOBNotification);
			INIT_c_MLMFPA_LUP_INUSE_StorageBLOBNotification (data->Data.fld_c_MLMFPA_LUP_INUSE_StorageBLOBNotification);
			retLen = DECODE_c_MLMFPA_LUP_INUSE_StorageBLOBNotification (buffer, 0, data->Data.fld_c_MLMFPA_LUP_INUSE_StorageBLOBNotification, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_LUP_INUSE_StorageBLOBAssignment */
		case 0x0012: {
			SETPRESENT_TMLMFPA_LUP_INUSE_Data (data, ID_MLMFPA_LUP_INUSE_MLMFPA_LUP_INUSE_StorageBLOBAssignment);
			INIT_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment (data->Data.fld_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment);
			retLen = DECODE_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment (buffer, 0, data->Data.fld_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_LUP_INUSE_StorageBLOBComplete */
		case 0x0013: {
			SETPRESENT_TMLMFPA_LUP_INUSE_Data (data, ID_MLMFPA_LUP_INUSE_MLMFPA_LUP_INUSE_StorageBLOBComplete);
			INIT_c_MLMFPA_LUP_INUSE_StorageBLOBComplete (data->Data.fld_c_MLMFPA_LUP_INUSE_StorageBLOBComplete);
			retLen = DECODE_c_MLMFPA_LUP_INUSE_StorageBLOBComplete (buffer, 0, data->Data.fld_c_MLMFPA_LUP_INUSE_StorageBLOBComplete, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_MLMFPA_LUP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MLMFPA_LUP_INUSE (const char* buffer, int len, TMLMFPA_LUP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_MLMFPA_LUP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif

#ifdef ED_REVERSED_INTEGER
#error ED_REVERSED_INTEGER is defined!
#endif


int SetDecode_MLMFPA_FCP_INUSE (const char* buffer, TMLMFPA_FCP_INUSE_Data* data, int bitLen, struct SCSN1CContextSet* pCSN1CContextSet)
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
			/* Detect signal MLMFPA_FCP_INUSE_XonRequest */
		case 0x0007: {
			SETPRESENT_TMLMFPA_FCP_INUSE_Data (data, ID_MLMFPA_FCP_INUSE_MLMFPA_FCP_INUSE_XonRequest);
			INIT_c_MLMFPA_FCP_INUSE_XonRequest (data->Data.fld_c_MLMFPA_FCP_INUSE_XonRequest);
			retLen = DECODE_c_MLMFPA_FCP_INUSE_XonRequest (buffer, 0, data->Data.fld_c_MLMFPA_FCP_INUSE_XonRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_FCP_INUSE_XonResponse */
		case 0x0008: {
			SETPRESENT_TMLMFPA_FCP_INUSE_Data (data, ID_MLMFPA_FCP_INUSE_MLMFPA_FCP_INUSE_XonResponse);
			INIT_c_MLMFPA_FCP_INUSE_XonResponse (data->Data.fld_c_MLMFPA_FCP_INUSE_XonResponse);
			retLen = DECODE_c_MLMFPA_FCP_INUSE_XonResponse (buffer, 0, data->Data.fld_c_MLMFPA_FCP_INUSE_XonResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_FCP_INUSE_XoffRequest */
		case 0x0009: {
			SETPRESENT_TMLMFPA_FCP_INUSE_Data (data, ID_MLMFPA_FCP_INUSE_MLMFPA_FCP_INUSE_XoffRequest);
			INIT_c_MLMFPA_FCP_INUSE_XoffRequest (data->Data.fld_c_MLMFPA_FCP_INUSE_XoffRequest);
			retLen = DECODE_c_MLMFPA_FCP_INUSE_XoffRequest (buffer, 0, data->Data.fld_c_MLMFPA_FCP_INUSE_XoffRequest, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_FCP_INUSE_XoffResponse */
		case 0x000A: {
			SETPRESENT_TMLMFPA_FCP_INUSE_Data (data, ID_MLMFPA_FCP_INUSE_MLMFPA_FCP_INUSE_XoffResponse);
			INIT_c_MLMFPA_FCP_INUSE_XoffResponse (data->Data.fld_c_MLMFPA_FCP_INUSE_XoffResponse);
			retLen = DECODE_c_MLMFPA_FCP_INUSE_XoffResponse (buffer, 0, data->Data.fld_c_MLMFPA_FCP_INUSE_XoffResponse, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_FCP_INUSE_DataReady */
		case 0x000B: {
			SETPRESENT_TMLMFPA_FCP_INUSE_Data (data, ID_MLMFPA_FCP_INUSE_MLMFPA_FCP_INUSE_DataReady);
			INIT_c_MLMFPA_FCP_INUSE_DataReady (data->Data.fld_c_MLMFPA_FCP_INUSE_DataReady);
			retLen = DECODE_c_MLMFPA_FCP_INUSE_DataReady (buffer, 0, data->Data.fld_c_MLMFPA_FCP_INUSE_DataReady, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_FCP_INUSE_DataReadyAck */
		case 0x000C: {
			SETPRESENT_TMLMFPA_FCP_INUSE_Data (data, ID_MLMFPA_FCP_INUSE_MLMFPA_FCP_INUSE_DataReadyAck);
			INIT_c_MLMFPA_FCP_INUSE_DataReadyAck (data->Data.fld_c_MLMFPA_FCP_INUSE_DataReadyAck);
			retLen = DECODE_c_MLMFPA_FCP_INUSE_DataReadyAck (buffer, 0, data->Data.fld_c_MLMFPA_FCP_INUSE_DataReadyAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_FCP_INUSE_RestartNetworkInterface */
		case 0x001C: {
			SETPRESENT_TMLMFPA_FCP_INUSE_Data (data, ID_MLMFPA_FCP_INUSE_MLMFPA_FCP_INUSE_RestartNetworkInterface);
			INIT_c_MLMFPA_FCP_INUSE_RestartNetworkInterface (data->Data.fld_c_MLMFPA_FCP_INUSE_RestartNetworkInterface);
			retLen = DECODE_c_MLMFPA_FCP_INUSE_RestartNetworkInterface (buffer, 0, data->Data.fld_c_MLMFPA_FCP_INUSE_RestartNetworkInterface, bitLen, pCSN1CContextSet);
		
			return retLen;
		}
		/* Detect signal MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck */
		case 0x001D: {
			SETPRESENT_TMLMFPA_FCP_INUSE_Data (data, ID_MLMFPA_FCP_INUSE_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck);
			INIT_c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck (data->Data.fld_c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck);
			retLen = DECODE_c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck (buffer, 0, data->Data.fld_c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck, bitLen, pCSN1CContextSet);
		
			return retLen;
		}

		default:;
	}
	data->Type = ID_MLMFPA_FCP_INUSE_Unrecognized;

	return ED_UNKNOWN_MESSAGE;
}
			
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_MLMFPA_FCP_INUSE (const char* buffer, int len, TMLMFPA_FCP_INUSE_Data* data, struct SCSN1CContextSet* pCSN1CContextSet)
	{
		if (SetDecode_MLMFPA_FCP_INUSE (buffer, data, len*8, pCSN1CContextSet) < 0) {
			return ED_FALSE;
		}
		else {
			return ED_TRUE;
		}
	}
#endif


