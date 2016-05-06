/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c
	http://www.Dafocus.it/
**************************************************************************/
/*lint -e959 -e530 -e774 -e572 -e778 -e525 -e539 -e701 -e123 -e438 -e119 -e506 -e529 -e550 -e666 -e713 -e719 -e730 -e734 -e744 -e801 -e801 -e813 -e830 -e40 -e10 -e52 -e63 -e115 -e409 -e118 -e49 -e718 -e746 -e737 -e760 -e830 */
#define ENCODIX_CS0063

#include "ed_c_cs0063.h"
#include "ed_lib.h"
#if ED_COMMON_CRC != 0x328E3625 && ED_VERSION != 10152 && ED_VERSION != 10153
#error Invalid Encodix library files linked; used those distributed with Encodix 1.0.154
#endif


/* Free function for variable-sized sequence c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01 */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->ProfileValue.value != NULL) {
			EDFree (sp->data[i]->ProfileValue.value);
			sp->data[i]->ProfileValue.value = NULL;
		}
		sp->data[i]->ProfileValue.usedBits = 0;
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->ProfileValue.value != NULL) {
			EDFree (sp->data01.data[i0]->ProfileValue.value);
			sp->data01.data[i0]->ProfileValue.value = NULL;
		}
		sp->data01.data[i0]->ProfileValue.usedBits = 0;
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01 */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->ProfileValue.value != NULL) {
			EDFree (sp->data[i]->ProfileValue.value);
			sp->data[i]->ProfileValue.value = NULL;
		}
		sp->data[i]->ProfileValue.usedBits = 0;
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->ProfileValue.value != NULL) {
			EDFree (sp->data01.data[i0]->ProfileValue.value);
			sp->data01.data[i0]->ProfileValue.value = NULL;
		}
		sp->data01.data[i0]->ProfileValue.usedBits = 0;
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01 */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01 */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01 */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01 */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02 */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01 */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01* sp) {
	int i, i0;
	for (i=0; i<sp->items; i++) {
		for (i0=0; i0<sp->data[i]->data02.items; i0++) {
			EDFree (sp->data[i]->data02.data[i0]);
			sp->data[i]->data02.data[i0] = NULL;
		}
		if (sp->data[i]->data02.data) {EDFree (sp->data[i]->data02.data); sp->data[i]->data02.data = NULL; sp->data[i]->data02.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd* sp) {
	int i0;
	int i1;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		for (i1=0; i1<sp->data01.data[i0]->data02.items; i1++) {
			EDFree (sp->data01.data[i0]->data02.data[i1]);
			sp->data01.data[i0]->data02.data[i1] = NULL;
		}
		if (sp->data01.data[i0]->data02.data) {EDFree (sp->data01.data[i0]->data02.data); sp->data01.data[i0]->data02.data = NULL; sp->data01.data[i0]->data02.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02 */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01 */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01* sp) {
	int i, i0;
	for (i=0; i<sp->items; i++) {
		for (i0=0; i0<sp->data[i]->data02.items; i0++) {
			EDFree (sp->data[i]->data02.data[i0]);
			sp->data[i]->data02.data[i0] = NULL;
		}
		if (sp->data[i]->data02.data) {EDFree (sp->data[i]->data02.data); sp->data[i]->data02.data = NULL; sp->data[i]->data02.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev* sp) {
	int i0;
	int i1;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		for (i1=0; i1<sp->data01.data[i0]->data02.items; i1++) {
			EDFree (sp->data01.data[i0]->data02.data[i1]);
			sp->data01.data[i0]->data02.data[i1] = NULL;
		}
		if (sp->data01.data[i0]->data02.data) {EDFree (sp->data01.data[i0]->data02.data); sp->data01.data[i0]->data02.data = NULL; sp->data01.data[i0]->data02.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01 */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->ProfileValue.value != NULL) {
			EDFree (sp->data[i]->ProfileValue.value);
			sp->data[i]->ProfileValue.value = NULL;
		}
		sp->data[i]->ProfileValue.usedBits = 0;
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->ProfileValue.value != NULL) {
			EDFree (sp->data01.data[i0]->ProfileValue.value);
			sp->data01.data[i0]->ProfileValue.value = NULL;
		}
		sp->data01.data[i0]->ProfileValue.usedBits = 0;
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01 */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->ProfileValue.value != NULL) {
			EDFree (sp->data[i]->ProfileValue.value);
			sp->data[i]->ProfileValue.value = NULL;
		}
		sp->data[i]->ProfileValue.usedBits = 0;
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->ProfileValue.value != NULL) {
			EDFree (sp->data01.data[i0]->ProfileValue.value);
			sp->data01.data[i0]->ProfileValue.value = NULL;
		}
		sp->data01.data[i0]->ProfileValue.usedBits = 0;
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01 */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->ProfileValue.value != NULL) {
			EDFree (sp->data[i]->ProfileValue.value);
			sp->data[i]->ProfileValue.value = NULL;
		}
		sp->data[i]->ProfileValue.usedBits = 0;
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->ProfileValue.value != NULL) {
			EDFree (sp->data01.data[i0]->ProfileValue.value);
			sp->data01.data[i0]->ProfileValue.value = NULL;
		}
		sp->data01.data[i0]->ProfileValue.usedBits = 0;
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01 */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->ProfileValue.value != NULL) {
			EDFree (sp->data[i]->ProfileValue.value);
			sp->data[i]->ProfileValue.value = NULL;
		}
		sp->data[i]->ProfileValue.usedBits = 0;
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->ProfileValue.value != NULL) {
			EDFree (sp->data01.data[i0]->ProfileValue.value);
			sp->data01.data[i0]->ProfileValue.value = NULL;
		}
		sp->data01.data[i0]->ProfileValue.usedBits = 0;
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01 */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->ProtocolParameters.value != NULL) {
			EDFree (sp->data[i]->ProtocolParameters.value);
			sp->data[i]->ProtocolParameters.value = NULL;
		}
		sp->data[i]->ProtocolParameters.usedBits = 0;
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->ProtocolParameters.value != NULL) {
			EDFree (sp->data01.data[i0]->ProtocolParameters.value);
			sp->data01.data[i0]->ProtocolParameters.value = NULL;
		}
		sp->data01.data[i0]->ProtocolParameters.usedBits = 0;
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01 */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->ProtocolParameters.value != NULL) {
			EDFree (sp->data[i]->ProtocolParameters.value);
			sp->data[i]->ProtocolParameters.value = NULL;
		}
		sp->data[i]->ProtocolParameters.usedBits = 0;
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->ProtocolParameters.value != NULL) {
			EDFree (sp->data01.data[i0]->ProtocolParameters.value);
			sp->data01.data[i0]->ProtocolParameters.value = NULL;
		}
		sp->data01.data[i0]->ProtocolParameters.usedBits = 0;
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01 */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->ProtocolParameters.value != NULL) {
			EDFree (sp->data[i]->ProtocolParameters.value);
			sp->data[i]->ProtocolParameters.value = NULL;
		}
		sp->data[i]->ProtocolParameters.usedBits = 0;
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->ProtocolParameters.value != NULL) {
			EDFree (sp->data01.data[i0]->ProtocolParameters.value);
			sp->data01.data[i0]->ProtocolParameters.value = NULL;
		}
		sp->data01.data[i0]->ProtocolParameters.usedBits = 0;
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01 */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->ProtocolParameters.value != NULL) {
			EDFree (sp->data[i]->ProtocolParameters.value);
			sp->data[i]->ProtocolParameters.value = NULL;
		}
		sp->data[i]->ProtocolParameters.usedBits = 0;
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->ProtocolParameters.value != NULL) {
			EDFree (sp->data01.data[i0]->ProtocolParameters.value);
			sp->data01.data[i0]->ProtocolParameters.value = NULL;
		}
		sp->data01.data[i0]->ProtocolParameters.usedBits = 0;
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->SupportedProtocolParametersValues.value != NULL) {
		EDFree (sp->SupportedProtocolParametersValues.value);
		sp->SupportedProtocolParametersValues.value = NULL;
	}
	sp->SupportedProtocolParametersValues.usedBits = 0;

}

/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->SupportedProtocolParametersValues.value != NULL) {
		EDFree (sp->SupportedProtocolParametersValues.value);
		sp->SupportedProtocolParametersValues.value = NULL;
	}
	sp->SupportedProtocolParametersValues.usedBits = 0;

}

/* Free function for variable-sized sequence c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02 */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01 */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01* sp) {
	int i, i0;
	for (i=0; i<sp->items; i++) {
		for (i0=0; i0<sp->data[i]->data02.items; i0++) {
			EDFree (sp->data[i]->data02.data[i0]);
			sp->data[i]->data02.data[i0] = NULL;
		}
		if (sp->data[i]->data02.data) {EDFree (sp->data[i]->data02.data); sp->data[i]->data02.data = NULL; sp->data[i]->data02.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation* sp) {
	int i0;
	int i1;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		for (i1=0; i1<sp->data01.data[i0]->data02.items; i1++) {
			EDFree (sp->data01.data[i0]->data02.data[i1]);
			sp->data01.data[i0]->data02.data[i1] = NULL;
		}
		if (sp->data01.data[i0]->data02.data) {EDFree (sp->data01.data[i0]->data02.data); sp->data01.data[i0]->data02.data = NULL; sp->data01.data[i0]->data02.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03 */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02 */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02* sp) {
	int i, i0;
	for (i=0; i<sp->items; i++) {
		for (i0=0; i0<sp->data[i]->data03.items; i0++) {
			EDFree (sp->data[i]->data03.data[i0]);
			sp->data[i]->data03.data[i0] = NULL;
		}
		if (sp->data[i]->data03.data) {EDFree (sp->data[i]->data03.data); sp->data[i]->data03.data = NULL; sp->data[i]->data03.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01 */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01* sp) {
	int i, i0, i1;
	for (i=0; i<sp->items; i++) {
		for (i0=0; i0<sp->data[i]->data02.items; i0++) {
			for (i1=0; i1<sp->data[i]->data02.data[i0]->data03.items; i1++) {
				EDFree (sp->data[i]->data02.data[i0]->data03.data[i1]);
				sp->data[i]->data02.data[i0]->data03.data[i1] = NULL;
			}
			if (sp->data[i]->data02.data[i0]->data03.data) {EDFree (sp->data[i]->data02.data[i0]->data03.data); sp->data[i]->data02.data[i0]->data03.data = NULL; sp->data[i]->data02.data[i0]->data03.allocatedItems=0; /*FR02A*/}
			EDFree (sp->data[i]->data02.data[i0]);
			sp->data[i]->data02.data[i0] = NULL;
		}
		if (sp->data[i]->data02.data) {EDFree (sp->data[i]->data02.data); sp->data[i]->data02.data = NULL; sp->data[i]->data02.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation* sp) {
	int i0;
	int i1;
	int i2;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		for (i1=0; i1<sp->data01.data[i0]->data02.items; i1++) {
			for (i2=0; i2<sp->data01.data[i0]->data02.data[i1]->data03.items; i2++) {
				EDFree (sp->data01.data[i0]->data02.data[i1]->data03.data[i2]);
				sp->data01.data[i0]->data02.data[i1]->data03.data[i2] = NULL;
			}
			if (sp->data01.data[i0]->data02.data[i1]->data03.data) {EDFree (sp->data01.data[i0]->data02.data[i1]->data03.data); sp->data01.data[i0]->data02.data[i1]->data03.data = NULL; sp->data01.data[i0]->data02.data[i1]->data03.allocatedItems=0; /*FR02A*/}
			EDFree (sp->data01.data[i0]->data02.data[i1]);
			sp->data01.data[i0]->data02.data[i1] = NULL;
		}
		if (sp->data01.data[i0]->data02.data) {EDFree (sp->data01.data[i0]->data02.data); sp->data01.data[i0]->data02.data = NULL; sp->data01.data[i0]->data02.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01 */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->ProfileValue.value != NULL) {
			EDFree (sp->data[i]->ProfileValue.value);
			sp->data[i]->ProfileValue.value = NULL;
		}
		sp->data[i]->ProfileValue.usedBits = 0;
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->ProfileValue.value != NULL) {
			EDFree (sp->data01.data[i0]->ProfileValue.value);
			sp->data01.data[i0]->ProfileValue.value = NULL;
		}
		sp->data01.data[i0]->ProfileValue.usedBits = 0;
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01 */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->ProfileValue.value != NULL) {
			EDFree (sp->data[i]->ProfileValue.value);
			sp->data[i]->ProfileValue.value = NULL;
		}
		sp->data[i]->ProfileValue.usedBits = 0;
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->ProfileValue.value != NULL) {
			EDFree (sp->data01.data[i0]->ProfileValue.value);
			sp->data01.data[i0]->ProfileValue.value = NULL;
		}
		sp->data01.data[i0]->ProfileValue.usedBits = 0;
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01 */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01 */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01 */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01 */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01 */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02 */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01 */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01* sp) {
	int i, i0;
	for (i=0; i<sp->items; i++) {
		for (i0=0; i0<sp->data[i]->data02.items; i0++) {
			EDFree (sp->data[i]->data02.data[i0]);
			sp->data[i]->data02.data[i0] = NULL;
		}
		if (sp->data[i]->data02.data) {EDFree (sp->data[i]->data02.data); sp->data[i]->data02.data = NULL; sp->data[i]->data02.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd* sp) {
	int i0;
	int i1;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		for (i1=0; i1<sp->data01.data[i0]->data02.items; i1++) {
			EDFree (sp->data01.data[i0]->data02.data[i1]);
			sp->data01.data[i0]->data02.data[i1] = NULL;
		}
		if (sp->data01.data[i0]->data02.data) {EDFree (sp->data01.data[i0]->data02.data); sp->data01.data[i0]->data02.data = NULL; sp->data01.data[i0]->data02.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02 */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01 */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01* sp) {
	int i, i0;
	for (i=0; i<sp->items; i++) {
		for (i0=0; i0<sp->data[i]->data02.items; i0++) {
			EDFree (sp->data[i]->data02.data[i0]);
			sp->data[i]->data02.data[i0] = NULL;
		}
		if (sp->data[i]->data02.data) {EDFree (sp->data[i]->data02.data); sp->data[i]->data02.data = NULL; sp->data[i]->data02.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev* sp) {
	int i0;
	int i1;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		for (i1=0; i1<sp->data01.data[i0]->data02.items; i1++) {
			EDFree (sp->data01.data[i0]->data02.data[i1]);
			sp->data01.data[i0]->data02.data[i1] = NULL;
		}
		if (sp->data01.data[i0]->data02.data) {EDFree (sp->data01.data[i0]->data02.data); sp->data01.data[i0]->data02.data = NULL; sp->data01.data[i0]->data02.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01 */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->ProfileValue.value != NULL) {
			EDFree (sp->data[i]->ProfileValue.value);
			sp->data[i]->ProfileValue.value = NULL;
		}
		sp->data[i]->ProfileValue.usedBits = 0;
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->ProfileValue.value != NULL) {
			EDFree (sp->data01.data[i0]->ProfileValue.value);
			sp->data01.data[i0]->ProfileValue.value = NULL;
		}
		sp->data01.data[i0]->ProfileValue.usedBits = 0;
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01 */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->ProfileValue.value != NULL) {
			EDFree (sp->data[i]->ProfileValue.value);
			sp->data[i]->ProfileValue.value = NULL;
		}
		sp->data[i]->ProfileValue.usedBits = 0;
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->ProfileValue.value != NULL) {
			EDFree (sp->data01.data[i0]->ProfileValue.value);
			sp->data01.data[i0]->ProfileValue.value = NULL;
		}
		sp->data01.data[i0]->ProfileValue.usedBits = 0;
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01 */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->ProfileValue.value != NULL) {
			EDFree (sp->data[i]->ProfileValue.value);
			sp->data[i]->ProfileValue.value = NULL;
		}
		sp->data[i]->ProfileValue.usedBits = 0;
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->ProfileValue.value != NULL) {
			EDFree (sp->data01.data[i0]->ProfileValue.value);
			sp->data01.data[i0]->ProfileValue.value = NULL;
		}
		sp->data01.data[i0]->ProfileValue.usedBits = 0;
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01 */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->ProfileValue.value != NULL) {
			EDFree (sp->data[i]->ProfileValue.value);
			sp->data[i]->ProfileValue.value = NULL;
		}
		sp->data[i]->ProfileValue.usedBits = 0;
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->ProfileValue.value != NULL) {
			EDFree (sp->data01.data[i0]->ProfileValue.value);
			sp->data01.data[i0]->ProfileValue.value = NULL;
		}
		sp->data01.data[i0]->ProfileValue.usedBits = 0;
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01 */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->ProtocolParameters.value != NULL) {
			EDFree (sp->data[i]->ProtocolParameters.value);
			sp->data[i]->ProtocolParameters.value = NULL;
		}
		sp->data[i]->ProtocolParameters.usedBits = 0;
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->ProtocolParameters.value != NULL) {
			EDFree (sp->data01.data[i0]->ProtocolParameters.value);
			sp->data01.data[i0]->ProtocolParameters.value = NULL;
		}
		sp->data01.data[i0]->ProtocolParameters.usedBits = 0;
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01 */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->ProtocolParameters.value != NULL) {
			EDFree (sp->data[i]->ProtocolParameters.value);
			sp->data[i]->ProtocolParameters.value = NULL;
		}
		sp->data[i]->ProtocolParameters.usedBits = 0;
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->ProtocolParameters.value != NULL) {
			EDFree (sp->data01.data[i0]->ProtocolParameters.value);
			sp->data01.data[i0]->ProtocolParameters.value = NULL;
		}
		sp->data01.data[i0]->ProtocolParameters.usedBits = 0;
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01 */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->ProtocolParameters.value != NULL) {
			EDFree (sp->data[i]->ProtocolParameters.value);
			sp->data[i]->ProtocolParameters.value = NULL;
		}
		sp->data[i]->ProtocolParameters.usedBits = 0;
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->ProtocolParameters.value != NULL) {
			EDFree (sp->data01.data[i0]->ProtocolParameters.value);
			sp->data01.data[i0]->ProtocolParameters.value = NULL;
		}
		sp->data01.data[i0]->ProtocolParameters.usedBits = 0;
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01 */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->ProtocolParameters.value != NULL) {
			EDFree (sp->data[i]->ProtocolParameters.value);
			sp->data[i]->ProtocolParameters.value = NULL;
		}
		sp->data[i]->ProtocolParameters.usedBits = 0;
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->ProtocolParameters.value != NULL) {
			EDFree (sp->data01.data[i0]->ProtocolParameters.value);
			sp->data01.data[i0]->ProtocolParameters.value = NULL;
		}
		sp->data01.data[i0]->ProtocolParameters.usedBits = 0;
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->SupportedProtocolParametersValues.value != NULL) {
		EDFree (sp->SupportedProtocolParametersValues.value);
		sp->SupportedProtocolParametersValues.value = NULL;
	}
	sp->SupportedProtocolParametersValues.usedBits = 0;

}

/* Free function for variable-sized sequence c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02 */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01 */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01* sp) {
	int i, i0;
	for (i=0; i<sp->items; i++) {
		for (i0=0; i0<sp->data[i]->data02.items; i0++) {
			EDFree (sp->data[i]->data02.data[i0]);
			sp->data[i]->data02.data[i0] = NULL;
		}
		if (sp->data[i]->data02.data) {EDFree (sp->data[i]->data02.data); sp->data[i]->data02.data = NULL; sp->data[i]->data02.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation* sp) {
	int i0;
	int i1;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		for (i1=0; i1<sp->data01.data[i0]->data02.items; i1++) {
			EDFree (sp->data01.data[i0]->data02.data[i1]);
			sp->data01.data[i0]->data02.data[i1] = NULL;
		}
		if (sp->data01.data[i0]->data02.data) {EDFree (sp->data01.data[i0]->data02.data); sp->data01.data[i0]->data02.data = NULL; sp->data01.data[i0]->data02.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03 */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02 */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02* sp) {
	int i, i0;
	for (i=0; i<sp->items; i++) {
		for (i0=0; i0<sp->data[i]->data03.items; i0++) {
			EDFree (sp->data[i]->data03.data[i0]);
			sp->data[i]->data03.data[i0] = NULL;
		}
		if (sp->data[i]->data03.data) {EDFree (sp->data[i]->data03.data); sp->data[i]->data03.data = NULL; sp->data[i]->data03.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01 */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01* sp) {
	int i, i0, i1;
	for (i=0; i<sp->items; i++) {
		for (i0=0; i0<sp->data[i]->data02.items; i0++) {
			for (i1=0; i1<sp->data[i]->data02.data[i0]->data03.items; i1++) {
				EDFree (sp->data[i]->data02.data[i0]->data03.data[i1]);
				sp->data[i]->data02.data[i0]->data03.data[i1] = NULL;
			}
			if (sp->data[i]->data02.data[i0]->data03.data) {EDFree (sp->data[i]->data02.data[i0]->data03.data); sp->data[i]->data02.data[i0]->data03.data = NULL; sp->data[i]->data02.data[i0]->data03.allocatedItems=0; /*FR02A*/}
			EDFree (sp->data[i]->data02.data[i0]);
			sp->data[i]->data02.data[i0] = NULL;
		}
		if (sp->data[i]->data02.data) {EDFree (sp->data[i]->data02.data); sp->data[i]->data02.data = NULL; sp->data[i]->data02.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation* sp) {
	int i0;
	int i1;
	int i2;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		for (i1=0; i1<sp->data01.data[i0]->data02.items; i1++) {
			for (i2=0; i2<sp->data01.data[i0]->data02.data[i1]->data03.items; i2++) {
				EDFree (sp->data01.data[i0]->data02.data[i1]->data03.data[i2]);
				sp->data01.data[i0]->data02.data[i1]->data03.data[i2] = NULL;
			}
			if (sp->data01.data[i0]->data02.data[i1]->data03.data) {EDFree (sp->data01.data[i0]->data02.data[i1]->data03.data); sp->data01.data[i0]->data02.data[i1]->data03.data = NULL; sp->data01.data[i0]->data02.data[i1]->data03.allocatedItems=0; /*FR02A*/}
			EDFree (sp->data01.data[i0]->data02.data[i1]);
			sp->data01.data[i0]->data02.data[i1] = NULL;
		}
		if (sp->data01.data[i0]->data02.data) {EDFree (sp->data01.data[i0]->data02.data); sp->data01.data[i0]->data02.data = NULL; sp->data01.data[i0]->data02.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Values */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Values (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Values* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for union c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex* sp) {
	switch (sp->Present) {
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedQoSProfiles: {
			FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles (sp->u.ATSupportedQoSProfiles);
			EDFree (sp->u.ATSupportedQoSProfiles);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ANSupportedQoSProfiles: {
			FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles (sp->u.ANSupportedQoSProfiles);
			EDFree (sp->u.ANSupportedQoSProfiles);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_MaxLinkFlows: {
			FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows (sp->u.MaxLinkFlows);
			EDFree (sp->u.MaxLinkFlows);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_MaxReservations: {
			FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations (sp->u.MaxReservations);
			EDFree (sp->u.MaxReservations);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersFwd: {
			FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd (sp->u.FlowNNTimersFwd);
			EDFree (sp->u.FlowNNTimersFwd);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersRev: {
			FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev (sp->u.FlowNNTimersRev);
			EDFree (sp->u.FlowNNTimersRev);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationFwd: {
			FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd (sp->u.FlowNNReservationFwd);
			EDFree (sp->u.FlowNNReservationFwd);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationRev: {
			FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev (sp->u.FlowNNReservationRev);
			EDFree (sp->u.FlowNNReservationRev);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestFwd: {
			FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd (sp->u.ReservationKKQoSRequestFwd);
			EDFree (sp->u.ReservationKKQoSRequestFwd);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestRev: {
			FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev (sp->u.ReservationKKQoSRequestRev);
			EDFree (sp->u.ReservationKKQoSRequestRev);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseFwd: {
			FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd (sp->u.ReservationKKQoSResponseFwd);
			EDFree (sp->u.ReservationKKQoSResponseFwd);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseRev: {
			FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev (sp->u.ReservationKKQoSResponseRev);
			EDFree (sp->u.ReservationKKQoSResponseRev);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersFwd: {
			FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd (sp->u.FlowNNFlowProtocolParametersFwd);
			EDFree (sp->u.FlowNNFlowProtocolParametersFwd);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersRev: {
			FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev (sp->u.FlowNNFlowProtocolParametersRev);
			EDFree (sp->u.FlowNNFlowProtocolParametersRev);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersFwd: {
			FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd (sp->u.FlowNNRouteProtocolParametersFwd);
			EDFree (sp->u.FlowNNRouteProtocolParametersFwd);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersRev: {
			FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev (sp->u.FlowNNRouteProtocolParametersRev);
			EDFree (sp->u.FlowNNRouteProtocolParametersRev);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedFlowProtocolParametersPP: {
			FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP (sp->u.ATSupportedFlowProtocolParametersPP);
			EDFree (sp->u.ATSupportedFlowProtocolParametersPP);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedRouteProtocolParametersPP: {
			FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP (sp->u.ATSupportedRouteProtocolParametersPP);
			EDFree (sp->u.ATSupportedRouteProtocolParametersPP);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSFlowIDAssociation: {
			FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation (sp->u.ReservationKKBCMCSFlowIDAssociation);
			EDFree (sp->u.ReservationKKBCMCSFlowIDAssociation);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSProgramIDAssociation: {
			FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation (sp->u.ReservationKKBCMCSProgramIDAssociation);
			EDFree (sp->u.ReservationKKBCMCSProgramIDAssociation);

			break;
		}

		default:;
	}
	sp->Present = U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_NONE;
}

/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->Values.data) {EDFree (sp->Values.data); sp->Values.data = NULL; sp->Values.allocatedItems=0; /*FR02A*/}
	FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex (&(sp->complex));

}

/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for variable-sized sequence c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Values */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Values (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Values* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for union c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex* sp) {
	switch (sp->Present) {
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedQoSProfiles: {
			FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles (sp->u.ATSupportedQoSProfiles);
			EDFree (sp->u.ATSupportedQoSProfiles);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ANSupportedQoSProfiles: {
			FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles (sp->u.ANSupportedQoSProfiles);
			EDFree (sp->u.ANSupportedQoSProfiles);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_MaxLinkFlows: {
			FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows (sp->u.MaxLinkFlows);
			EDFree (sp->u.MaxLinkFlows);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_MaxReservations: {
			FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations (sp->u.MaxReservations);
			EDFree (sp->u.MaxReservations);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNSequenceLengthFwd: {
			FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd (sp->u.FlowNNSequenceLengthFwd);
			EDFree (sp->u.FlowNNSequenceLengthFwd);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersFwd: {
			FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd (sp->u.FlowNNTimersFwd);
			EDFree (sp->u.FlowNNTimersFwd);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersRev: {
			FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev (sp->u.FlowNNTimersRev);
			EDFree (sp->u.FlowNNTimersRev);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationFwd: {
			FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd (sp->u.FlowNNReservationFwd);
			EDFree (sp->u.FlowNNReservationFwd);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationRev: {
			FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev (sp->u.FlowNNReservationRev);
			EDFree (sp->u.FlowNNReservationRev);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestFwd: {
			FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd (sp->u.ReservationKKQoSRequestFwd);
			EDFree (sp->u.ReservationKKQoSRequestFwd);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestRev: {
			FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev (sp->u.ReservationKKQoSRequestRev);
			EDFree (sp->u.ReservationKKQoSRequestRev);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseFwd: {
			FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd (sp->u.ReservationKKQoSResponseFwd);
			EDFree (sp->u.ReservationKKQoSResponseFwd);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseRev: {
			FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev (sp->u.ReservationKKQoSResponseRev);
			EDFree (sp->u.ReservationKKQoSResponseRev);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersFwd: {
			FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd (sp->u.FlowNNFlowProtocolParametersFwd);
			EDFree (sp->u.FlowNNFlowProtocolParametersFwd);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersRev: {
			FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev (sp->u.FlowNNFlowProtocolParametersRev);
			EDFree (sp->u.FlowNNFlowProtocolParametersRev);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersFwd: {
			FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd (sp->u.FlowNNRouteProtocolParametersFwd);
			EDFree (sp->u.FlowNNRouteProtocolParametersFwd);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersRev: {
			FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev (sp->u.FlowNNRouteProtocolParametersRev);
			EDFree (sp->u.FlowNNRouteProtocolParametersRev);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedFlowProtocolParametersPP: {
			FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP (sp->u.ATSupportedFlowProtocolParametersPP);
			EDFree (sp->u.ATSupportedFlowProtocolParametersPP);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedRouteProtocolParametersPP: {
			FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP (sp->u.ATSupportedRouteProtocolParametersPP);
			EDFree (sp->u.ATSupportedRouteProtocolParametersPP);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSFlowIDAssociation: {
			FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation (sp->u.ReservationKKBCMCSFlowIDAssociation);
			EDFree (sp->u.ReservationKKBCMCSFlowIDAssociation);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSProgramIDAssociation: {
			FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation (sp->u.ReservationKKBCMCSProgramIDAssociation);
			EDFree (sp->u.ReservationKKBCMCSProgramIDAssociation);

			break;
		}

		default:;
	}
	sp->Present = U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_NONE;
}

/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->Values.data) {EDFree (sp->Values.data); sp->Values.data = NULL; sp->Values.allocatedItems=0; /*FR02A*/}
	FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex (&(sp->complex));

}

/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for variable-sized sequence c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01 */
void FREE_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01 (c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes (&(sp->data[i]->AttributeRecord));
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents */
void FREE_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents (c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes (&(sp->data01.data[i0]->AttributeRecord));
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01 */
void FREE_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01 (c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response (&(sp->data[i]->AttributeRecord));
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents */
void FREE_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents (c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response (&(sp->data01.data[i0]->AttributeRecord));
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for struct c_EMFPKA_RSP_INUSE_RouteSelect_contents */
void FREE_c_EMFPKA_RSP_INUSE_RouteSelect_contents (c_EMFPKA_RSP_INUSE_RouteSelect_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_EMFPKA_RSP_INUSE_RouteSelectAck_contents */
void FREE_c_EMFPKA_RSP_INUSE_RouteSelectAck_contents (c_EMFPKA_RSP_INUSE_RouteSelectAck_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_EMFPKA_RSP_INUSE_ActivateRoute_contents */
void FREE_c_EMFPKA_RSP_INUSE_ActivateRoute_contents (c_EMFPKA_RSP_INUSE_ActivateRoute_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_EMFPKA_RSP_INUSE_ActivateRouteAck_contents */
void FREE_c_EMFPKA_RSP_INUSE_ActivateRouteAck_contents (c_EMFPKA_RSP_INUSE_ActivateRouteAck_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_EMFPKA_RLP_INUSE_ResetTxIndication_contents */
void FREE_c_EMFPKA_RLP_INUSE_ResetTxIndication_contents (c_EMFPKA_RLP_INUSE_ResetTxIndication_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_EMFPKA_RLP_INUSE_ResetRxIndication_contents */
void FREE_c_EMFPKA_RLP_INUSE_ResetRxIndication_contents (c_EMFPKA_RLP_INUSE_ResetRxIndication_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents */
void FREE_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents (c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_EMFPKA_RLP_INUSE_ResetTxComplete_contents */
void FREE_c_EMFPKA_RLP_INUSE_ResetTxComplete_contents (c_EMFPKA_RLP_INUSE_ResetTxComplete_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_EMFPKA_RLP_INUSE_ResetRxComplete_contents */
void FREE_c_EMFPKA_RLP_INUSE_ResetRxComplete_contents (c_EMFPKA_RLP_INUSE_ResetRxComplete_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for variable-sized sequence c_EMFPKA_RLP_INUSE_Nak_contents_data01 */
void FREE_c_EMFPKA_RLP_INUSE_Nak_contents_data01 (c_EMFPKA_RLP_INUSE_Nak_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->FirstErasedDataUnit.value != NULL) {
			EDFree (sp->data[i]->FirstErasedDataUnit.value);
			sp->data[i]->FirstErasedDataUnit.value = NULL;
		}
		sp->data[i]->FirstErasedDataUnit.usedBits = 0;
		if (sp->data[i]->WindowLen.value != NULL) {
			EDFree (sp->data[i]->WindowLen.value);
			sp->data[i]->WindowLen.value = NULL;
		}
		sp->data[i]->WindowLen.usedBits = 0;
		if (sp->data[i]->VR.value != NULL) {
			EDFree (sp->data[i]->VR.value);
			sp->data[i]->VR.value = NULL;
		}
		sp->data[i]->VR.usedBits = 0;
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_EMFPKA_RLP_INUSE_Nak_contents */
void FREE_c_EMFPKA_RLP_INUSE_Nak_contents (c_EMFPKA_RLP_INUSE_Nak_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->FirstErasedDataUnit.value != NULL) {
			EDFree (sp->data01.data[i0]->FirstErasedDataUnit.value);
			sp->data01.data[i0]->FirstErasedDataUnit.value = NULL;
		}
		sp->data01.data[i0]->FirstErasedDataUnit.usedBits = 0;
		if (sp->data01.data[i0]->WindowLen.value != NULL) {
			EDFree (sp->data01.data[i0]->WindowLen.value);
			sp->data01.data[i0]->WindowLen.value = NULL;
		}
		sp->data01.data[i0]->WindowLen.usedBits = 0;
		if (sp->data01.data[i0]->VR.value != NULL) {
			EDFree (sp->data01.data[i0]->VR.value);
			sp->data01.data[i0]->VR.value = NULL;
		}
		sp->data01.data[i0]->VR.usedBits = 0;
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01 */
void FREE_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01 (c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->EmergencyIndication_Present) {
		}
		if (sp->data[i]->ReservationQueuingReq_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents */
void FREE_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents (c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->EmergencyIndication_Present) {
		}
		if (sp->data01.data[i0]->ReservationQueuingReq_Present) {
		}
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01 */
void FREE_c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01 (c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents */
void FREE_c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents (c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for struct c_EMFPKA_RLP_INUSE_ReservationAccept_contents */
void FREE_c_EMFPKA_RLP_INUSE_ReservationAccept_contents (c_EMFPKA_RLP_INUSE_ReservationAccept_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for variable-sized sequence c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02 */
void FREE_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02 (c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->RejectCode_Present) {
		}
		if (sp->data[i]->PendingDuration_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01 */
void FREE_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01 (c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01* sp) {
	int i, i0;
	for (i=0; i<sp->items; i++) {
		for (i0=0; i0<sp->data[i]->data02.items; i0++) {
			if (sp->data[i]->data02.data[i0]->RejectCode_Present) {
			}
			if (sp->data[i]->data02.data[i0]->PendingDuration_Present) {
			}
			EDFree (sp->data[i]->data02.data[i0]);
			sp->data[i]->data02.data[i0] = NULL;
		}
		if (sp->data[i]->data02.data) {EDFree (sp->data[i]->data02.data); sp->data[i]->data02.data = NULL; sp->data[i]->data02.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_EMFPKA_RLP_INUSE_ReservationReject_contents */
void FREE_c_EMFPKA_RLP_INUSE_ReservationReject_contents (c_EMFPKA_RLP_INUSE_ReservationReject_contents* sp) {
	int i0;
	int i1;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		for (i1=0; i1<sp->data01.data[i0]->data02.items; i1++) {
			if (sp->data01.data[i0]->data02.data[i1]->RejectCode_Present) {
			}
			if (sp->data01.data[i0]->data02.data[i1]->PendingDuration_Present) {
			}
			EDFree (sp->data01.data[i0]->data02.data[i1]);
			sp->data01.data[i0]->data02.data[i1] = NULL;
		}
		if (sp->data01.data[i0]->data02.data) {EDFree (sp->data01.data[i0]->data02.data); sp->data01.data[i0]->data02.data = NULL; sp->data01.data[i0]->data02.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01 */
void FREE_c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01 (c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_EMFPKA_RLP_INUSE_RevReservationOn_contents */
void FREE_c_EMFPKA_RLP_INUSE_RevReservationOn_contents (c_EMFPKA_RLP_INUSE_RevReservationOn_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01 */
void FREE_c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01 (c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_EMFPKA_RLP_INUSE_RevReservationOff_contents */
void FREE_c_EMFPKA_RLP_INUSE_RevReservationOff_contents (c_EMFPKA_RLP_INUSE_RevReservationOff_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01 */
void FREE_c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01 (c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_EMFPKA_RLP_INUSE_FwdReservationOff_contents */
void FREE_c_EMFPKA_RLP_INUSE_FwdReservationOff_contents (c_EMFPKA_RLP_INUSE_FwdReservationOff_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01 */
void FREE_c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01 (c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_EMFPKA_RLP_INUSE_FwdReservationOn_contents */
void FREE_c_EMFPKA_RLP_INUSE_FwdReservationOn_contents (c_EMFPKA_RLP_INUSE_FwdReservationOn_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for struct c_EMFPKA_RLP_INUSE_FwdReservationAck_contents */
void FREE_c_EMFPKA_RLP_INUSE_FwdReservationAck_contents (c_EMFPKA_RLP_INUSE_FwdReservationAck_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for variable-sized sequence c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01 */
void FREE_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01 (c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes (&(sp->data[i]->AttributeRecord));
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents */
void FREE_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents (c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes (&(sp->data01.data[i0]->AttributeRecord));
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for struct c_EMFPKA_RLP_INUSE_AttributeUpdateAccept_contents */
void FREE_c_EMFPKA_RLP_INUSE_AttributeUpdateAccept_contents (c_EMFPKA_RLP_INUSE_AttributeUpdateAccept_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_EMFPKA_RLP_INUSE_AttributeUpdateReject_contents */
void FREE_c_EMFPKA_RLP_INUSE_AttributeUpdateReject_contents (c_EMFPKA_RLP_INUSE_AttributeUpdateReject_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents */
void FREE_c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents (c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->HigherLayerPacket.value != NULL) {
		EDFree (sp->HigherLayerPacket.value);
		sp->HigherLayerPacket.value = NULL;
	}
	sp->HigherLayerPacket.usedBits = 0;

}

/* Free function for struct c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents */
void FREE_c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents (c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_EMFPKA_LUP_INUSE_LocationNotification_contents */
void FREE_c_EMFPKA_LUP_INUSE_LocationNotification_contents (c_EMFPKA_LUP_INUSE_LocationNotification_contents* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->LocationValue.value != NULL) {
		EDFree (sp->LocationValue.value);
		sp->LocationValue.value = NULL;
	}
	sp->LocationValue.usedBits = 0;

}

/* Free function for struct c_EMFPKA_LUP_INUSE_LocationAssignment_contents */
void FREE_c_EMFPKA_LUP_INUSE_LocationAssignment_contents (c_EMFPKA_LUP_INUSE_LocationAssignment_contents* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->LocationValue.value != NULL) {
		EDFree (sp->LocationValue.value);
		sp->LocationValue.value = NULL;
	}
	sp->LocationValue.usedBits = 0;

}

/* Free function for struct c_EMFPKA_LUP_INUSE_LocationComplete_contents */
void FREE_c_EMFPKA_LUP_INUSE_LocationComplete_contents (c_EMFPKA_LUP_INUSE_LocationComplete_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents */
void FREE_c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents (c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->StorageBLOB.value != NULL) {
		EDFree (sp->StorageBLOB.value);
		sp->StorageBLOB.value = NULL;
	}
	sp->StorageBLOB.usedBits = 0;

}

/* Free function for struct c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents */
void FREE_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents (c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->StorageBLOB.value != NULL) {
		EDFree (sp->StorageBLOB.value);
		sp->StorageBLOB.value = NULL;
	}
	sp->StorageBLOB.usedBits = 0;

}

/* Free function for struct c_EMFPKA_LUP_INUSE_StorageBLOBComplete_contents */
void FREE_c_EMFPKA_LUP_INUSE_StorageBLOBComplete_contents (c_EMFPKA_LUP_INUSE_StorageBLOBComplete_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_EMFPKA_FCP_INUSE_DataReady_contents */
void FREE_c_EMFPKA_FCP_INUSE_DataReady_contents (c_EMFPKA_FCP_INUSE_DataReady_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_EMFPKA_FCP_INUSE_DataReadyAck_contents */
void FREE_c_EMFPKA_FCP_INUSE_DataReadyAck_contents (c_EMFPKA_FCP_INUSE_DataReadyAck_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_EMFPKA_FCP_INUSE_RestartNetworkInterface_contents */
void FREE_c_EMFPKA_FCP_INUSE_RestartNetworkInterface_contents (c_EMFPKA_FCP_INUSE_RestartNetworkInterface_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck_contents */
void FREE_c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck_contents (c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for variable-sized sequence c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01 */
void FREE_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01 (c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes (&(sp->data[i]->AttributeRecord));
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents */
void FREE_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents (c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes (&(sp->data01.data[i0]->AttributeRecord));
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01 */
void FREE_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01 (c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response (&(sp->data[i]->AttributeRecord));
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents */
void FREE_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents (c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response (&(sp->data01.data[i0]->AttributeRecord));
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for struct c_MLMFPA_RSP_INUSE_RouteSelect_contents */
void FREE_c_MLMFPA_RSP_INUSE_RouteSelect_contents (c_MLMFPA_RSP_INUSE_RouteSelect_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_MLMFPA_RSP_INUSE_RouteSelectAck_contents */
void FREE_c_MLMFPA_RSP_INUSE_RouteSelectAck_contents (c_MLMFPA_RSP_INUSE_RouteSelectAck_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_MLMFPA_RSP_INUSE_ActivateRoute_contents */
void FREE_c_MLMFPA_RSP_INUSE_ActivateRoute_contents (c_MLMFPA_RSP_INUSE_ActivateRoute_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_MLMFPA_RSP_INUSE_ActivateRouteAck_contents */
void FREE_c_MLMFPA_RSP_INUSE_ActivateRouteAck_contents (c_MLMFPA_RSP_INUSE_ActivateRouteAck_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_MLMFPA_SRP_INUSE_ResetTxIndication_contents */
void FREE_c_MLMFPA_SRP_INUSE_ResetTxIndication_contents (c_MLMFPA_SRP_INUSE_ResetTxIndication_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_MLMFPA_SRP_INUSE_ResetRxIndication_contents */
void FREE_c_MLMFPA_SRP_INUSE_ResetRxIndication_contents (c_MLMFPA_SRP_INUSE_ResetRxIndication_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents */
void FREE_c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents (c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_MLMFPA_SRP_INUSE_ResetTxComplete_contents */
void FREE_c_MLMFPA_SRP_INUSE_ResetTxComplete_contents (c_MLMFPA_SRP_INUSE_ResetTxComplete_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_MLMFPA_SRP_INUSE_ResetRxComplete_contents */
void FREE_c_MLMFPA_SRP_INUSE_ResetRxComplete_contents (c_MLMFPA_SRP_INUSE_ResetRxComplete_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for variable-sized sequence c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01 */
void FREE_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01 (c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->LeadingEdge_Present) {
			if (sp->data[i]->LeadingEdge->value != NULL) {
				EDFree (sp->data[i]->LeadingEdge->value);
				sp->data[i]->LeadingEdge->value = NULL;
			}
			sp->data[i]->LeadingEdge->usedBits = 0;
			EDFree (sp->data[i]->LeadingEdge);
		}
		if (sp->data[i]->TrailingEdge.value != NULL) {
			EDFree (sp->data[i]->TrailingEdge.value);
			sp->data[i]->TrailingEdge.value = NULL;
		}
		sp->data[i]->TrailingEdge.usedBits = 0;
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02 */
void FREE_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02 (c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->LargestSAR.value != NULL) {
			EDFree (sp->data[i]->LargestSAR.value);
			sp->data[i]->LargestSAR.value = NULL;
		}
		sp->data[i]->LargestSAR.usedBits = 0;
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_MLMFPA_SRP_INUSE_MultiLinkNak_contents */
void FREE_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents (c_MLMFPA_SRP_INUSE_MultiLinkNak_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->LeadingEdge_Present) {
			if (sp->data01.data[i0]->LeadingEdge->value != NULL) {
				EDFree (sp->data01.data[i0]->LeadingEdge->value);
				sp->data01.data[i0]->LeadingEdge->value = NULL;
			}
			sp->data01.data[i0]->LeadingEdge->usedBits = 0;
			EDFree (sp->data01.data[i0]->LeadingEdge);
		}
		if (sp->data01.data[i0]->TrailingEdge.value != NULL) {
			EDFree (sp->data01.data[i0]->TrailingEdge.value);
			sp->data01.data[i0]->TrailingEdge.value = NULL;
		}
		sp->data01.data[i0]->TrailingEdge.usedBits = 0;
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data02.items; i0++) {
		if (sp->data02.data[i0]->LargestSAR.value != NULL) {
			EDFree (sp->data02.data[i0]->LargestSAR.value);
			sp->data02.data[i0]->LargestSAR.value = NULL;
		}
		sp->data02.data[i0]->LargestSAR.usedBits = 0;
		EDFree (sp->data02.data[i0]);
		sp->data02.data[i0] = NULL;
	}
	if (sp->data02.data) {EDFree (sp->data02.data); sp->data02.data = NULL; sp->data02.allocatedItems=0; /*FR02A*/}
	if (sp->VR.value != NULL) {
		EDFree (sp->VR.value);
		sp->VR.value = NULL;
	}
	sp->VR.usedBits = 0;

}

/* Free function for variable-sized sequence c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01 */
void FREE_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01 (c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->EmergencyIndication_Present) {
		}
		if (sp->data[i]->ReservationQueuingReq_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents */
void FREE_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents (c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->EmergencyIndication_Present) {
		}
		if (sp->data01.data[i0]->ReservationQueuingReq_Present) {
		}
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01 */
void FREE_c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01 (c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents */
void FREE_c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents (c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for struct c_MLMFPA_SRP_INUSE_ReservationAccept_contents */
void FREE_c_MLMFPA_SRP_INUSE_ReservationAccept_contents (c_MLMFPA_SRP_INUSE_ReservationAccept_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for variable-sized sequence c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02 */
void FREE_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02 (c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->RejectCode_Present) {
		}
		if (sp->data[i]->PendingDuration_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01 */
void FREE_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01 (c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01* sp) {
	int i, i0;
	for (i=0; i<sp->items; i++) {
		for (i0=0; i0<sp->data[i]->data02.items; i0++) {
			if (sp->data[i]->data02.data[i0]->RejectCode_Present) {
			}
			if (sp->data[i]->data02.data[i0]->PendingDuration_Present) {
			}
			EDFree (sp->data[i]->data02.data[i0]);
			sp->data[i]->data02.data[i0] = NULL;
		}
		if (sp->data[i]->data02.data) {EDFree (sp->data[i]->data02.data); sp->data[i]->data02.data = NULL; sp->data[i]->data02.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_MLMFPA_SRP_INUSE_ReservationReject_contents */
void FREE_c_MLMFPA_SRP_INUSE_ReservationReject_contents (c_MLMFPA_SRP_INUSE_ReservationReject_contents* sp) {
	int i0;
	int i1;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		for (i1=0; i1<sp->data01.data[i0]->data02.items; i1++) {
			if (sp->data01.data[i0]->data02.data[i1]->RejectCode_Present) {
			}
			if (sp->data01.data[i0]->data02.data[i1]->PendingDuration_Present) {
			}
			EDFree (sp->data01.data[i0]->data02.data[i1]);
			sp->data01.data[i0]->data02.data[i1] = NULL;
		}
		if (sp->data01.data[i0]->data02.data) {EDFree (sp->data01.data[i0]->data02.data); sp->data01.data[i0]->data02.data = NULL; sp->data01.data[i0]->data02.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01 */
void FREE_c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01 (c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_MLMFPA_SRP_INUSE_RevReservationOn_contents */
void FREE_c_MLMFPA_SRP_INUSE_RevReservationOn_contents (c_MLMFPA_SRP_INUSE_RevReservationOn_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01 */
void FREE_c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01 (c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_MLMFPA_SRP_INUSE_RevReservationOff_contents */
void FREE_c_MLMFPA_SRP_INUSE_RevReservationOff_contents (c_MLMFPA_SRP_INUSE_RevReservationOff_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01 */
void FREE_c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01 (c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_MLMFPA_SRP_INUSE_FwdReservationOff_contents */
void FREE_c_MLMFPA_SRP_INUSE_FwdReservationOff_contents (c_MLMFPA_SRP_INUSE_FwdReservationOff_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01 */
void FREE_c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01 (c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_MLMFPA_SRP_INUSE_FwdReservationOn_contents */
void FREE_c_MLMFPA_SRP_INUSE_FwdReservationOn_contents (c_MLMFPA_SRP_INUSE_FwdReservationOn_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for struct c_MLMFPA_SRP_INUSE_FwdReservationAck_contents */
void FREE_c_MLMFPA_SRP_INUSE_FwdReservationAck_contents (c_MLMFPA_SRP_INUSE_FwdReservationAck_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for variable-sized sequence c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01 */
void FREE_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01 (c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes (&(sp->data[i]->AttributeRecord));
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents */
void FREE_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents (c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes (&(sp->data01.data[i0]->AttributeRecord));
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for struct c_MLMFPA_SRP_INUSE_AttributeUpdateAccept_contents */
void FREE_c_MLMFPA_SRP_INUSE_AttributeUpdateAccept_contents (c_MLMFPA_SRP_INUSE_AttributeUpdateAccept_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_MLMFPA_SRP_INUSE_AttributeUpdateReject_contents */
void FREE_c_MLMFPA_SRP_INUSE_AttributeUpdateReject_contents (c_MLMFPA_SRP_INUSE_AttributeUpdateReject_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_MLMFPA_SRP_INUSE_Flush_contents */
void FREE_c_MLMFPA_SRP_INUSE_Flush_contents (c_MLMFPA_SRP_INUSE_Flush_contents* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->LastSARSequence.value != NULL) {
		EDFree (sp->LastSARSequence.value);
		sp->LastSARSequence.value = NULL;
	}
	sp->LastSARSequence.usedBits = 0;

}

/* Free function for variable-sized sequence c_MLMFPA_SRP_INUSE_Nak_contents_data01 */
void FREE_c_MLMFPA_SRP_INUSE_Nak_contents_data01 (c_MLMFPA_SRP_INUSE_Nak_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->FirstErasedDataUnit.value != NULL) {
			EDFree (sp->data[i]->FirstErasedDataUnit.value);
			sp->data[i]->FirstErasedDataUnit.value = NULL;
		}
		sp->data[i]->FirstErasedDataUnit.usedBits = 0;
		if (sp->data[i]->WindowLen.value != NULL) {
			EDFree (sp->data[i]->WindowLen.value);
			sp->data[i]->WindowLen.value = NULL;
		}
		sp->data[i]->WindowLen.usedBits = 0;
		if (sp->data[i]->VR.value != NULL) {
			EDFree (sp->data[i]->VR.value);
			sp->data[i]->VR.value = NULL;
		}
		sp->data[i]->VR.usedBits = 0;
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_MLMFPA_SRP_INUSE_Nak_contents */
void FREE_c_MLMFPA_SRP_INUSE_Nak_contents (c_MLMFPA_SRP_INUSE_Nak_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->FirstErasedDataUnit.value != NULL) {
			EDFree (sp->data01.data[i0]->FirstErasedDataUnit.value);
			sp->data01.data[i0]->FirstErasedDataUnit.value = NULL;
		}
		sp->data01.data[i0]->FirstErasedDataUnit.usedBits = 0;
		if (sp->data01.data[i0]->WindowLen.value != NULL) {
			EDFree (sp->data01.data[i0]->WindowLen.value);
			sp->data01.data[i0]->WindowLen.value = NULL;
		}
		sp->data01.data[i0]->WindowLen.usedBits = 0;
		if (sp->data01.data[i0]->VR.value != NULL) {
			EDFree (sp->data01.data[i0]->VR.value);
			sp->data01.data[i0]->VR.value = NULL;
		}
		sp->data01.data[i0]->VR.usedBits = 0;
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for struct c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents */
void FREE_c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents (c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->HigherLayerPacket.value != NULL) {
		EDFree (sp->HigherLayerPacket.value);
		sp->HigherLayerPacket.value = NULL;
	}
	sp->HigherLayerPacket.usedBits = 0;

}

/* Free function for struct c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents */
void FREE_c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents (c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_MLMFPA_LUP_INUSE_LocationNotification_contents */
void FREE_c_MLMFPA_LUP_INUSE_LocationNotification_contents (c_MLMFPA_LUP_INUSE_LocationNotification_contents* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->LocationValue.value != NULL) {
		EDFree (sp->LocationValue.value);
		sp->LocationValue.value = NULL;
	}
	sp->LocationValue.usedBits = 0;

}

/* Free function for struct c_MLMFPA_LUP_INUSE_LocationAssignment_contents */
void FREE_c_MLMFPA_LUP_INUSE_LocationAssignment_contents (c_MLMFPA_LUP_INUSE_LocationAssignment_contents* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->LocationValue.value != NULL) {
		EDFree (sp->LocationValue.value);
		sp->LocationValue.value = NULL;
	}
	sp->LocationValue.usedBits = 0;

}

/* Free function for struct c_MLMFPA_LUP_INUSE_LocationComplete_contents */
void FREE_c_MLMFPA_LUP_INUSE_LocationComplete_contents (c_MLMFPA_LUP_INUSE_LocationComplete_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents */
void FREE_c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents (c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->StorageBLOB.value != NULL) {
		EDFree (sp->StorageBLOB.value);
		sp->StorageBLOB.value = NULL;
	}
	sp->StorageBLOB.usedBits = 0;

}

/* Free function for struct c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents */
void FREE_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents (c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->StorageBLOB.value != NULL) {
		EDFree (sp->StorageBLOB.value);
		sp->StorageBLOB.value = NULL;
	}
	sp->StorageBLOB.usedBits = 0;

}

/* Free function for struct c_MLMFPA_LUP_INUSE_StorageBLOBComplete_contents */
void FREE_c_MLMFPA_LUP_INUSE_StorageBLOBComplete_contents (c_MLMFPA_LUP_INUSE_StorageBLOBComplete_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_MLMFPA_FCP_INUSE_DataReady_contents */
void FREE_c_MLMFPA_FCP_INUSE_DataReady_contents (c_MLMFPA_FCP_INUSE_DataReady_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_MLMFPA_FCP_INUSE_DataReadyAck_contents */
void FREE_c_MLMFPA_FCP_INUSE_DataReadyAck_contents (c_MLMFPA_FCP_INUSE_DataReadyAck_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_MLMFPA_FCP_INUSE_RestartNetworkInterface_contents */
void FREE_c_MLMFPA_FCP_INUSE_RestartNetworkInterface_contents (c_MLMFPA_FCP_INUSE_RestartNetworkInterface_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck_contents */
void FREE_c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck_contents (c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_EMFPKA_EMFPA_INCFG_ConfigurationRequest */
void FREE_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest (c_EMFPKA_EMFPA_INCFG_ConfigurationRequest* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_EMFPA_INCFG_ConfigurationResponse */
void FREE_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse (c_EMFPKA_EMFPA_INCFG_ConfigurationResponse* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_RSP_INUSE_RouteSelect */
void FREE_c_EMFPKA_RSP_INUSE_RouteSelect (c_EMFPKA_RSP_INUSE_RouteSelect* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_RSP_INUSE_RouteSelect_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_RSP_INUSE_RouteSelectAck */
void FREE_c_EMFPKA_RSP_INUSE_RouteSelectAck (c_EMFPKA_RSP_INUSE_RouteSelectAck* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_RSP_INUSE_RouteSelectAck_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_RSP_INUSE_ActivateRoute */
void FREE_c_EMFPKA_RSP_INUSE_ActivateRoute (c_EMFPKA_RSP_INUSE_ActivateRoute* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_RSP_INUSE_ActivateRoute_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_RSP_INUSE_ActivateRouteAck */
void FREE_c_EMFPKA_RSP_INUSE_ActivateRouteAck (c_EMFPKA_RSP_INUSE_ActivateRouteAck* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_RSP_INUSE_ActivateRouteAck_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_RLP_INUSE_ResetTxIndication */
void FREE_c_EMFPKA_RLP_INUSE_ResetTxIndication (c_EMFPKA_RLP_INUSE_ResetTxIndication* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_RLP_INUSE_ResetTxIndication_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_RLP_INUSE_ResetRxIndication */
void FREE_c_EMFPKA_RLP_INUSE_ResetRxIndication (c_EMFPKA_RLP_INUSE_ResetRxIndication* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_RLP_INUSE_ResetRxIndication_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_RLP_INUSE_ResetTxIndicationAck */
void FREE_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck (c_EMFPKA_RLP_INUSE_ResetTxIndicationAck* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_RLP_INUSE_ResetTxComplete */
void FREE_c_EMFPKA_RLP_INUSE_ResetTxComplete (c_EMFPKA_RLP_INUSE_ResetTxComplete* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_RLP_INUSE_ResetTxComplete_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_RLP_INUSE_ResetRxComplete */
void FREE_c_EMFPKA_RLP_INUSE_ResetRxComplete (c_EMFPKA_RLP_INUSE_ResetRxComplete* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_RLP_INUSE_ResetRxComplete_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_RLP_INUSE_Nak */
void FREE_c_EMFPKA_RLP_INUSE_Nak (c_EMFPKA_RLP_INUSE_Nak* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_RLP_INUSE_Nak_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_RLP_INUSE_ReservationOnRequest */
void FREE_c_EMFPKA_RLP_INUSE_ReservationOnRequest (c_EMFPKA_RLP_INUSE_ReservationOnRequest* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_RLP_INUSE_ReservationOffRequest */
void FREE_c_EMFPKA_RLP_INUSE_ReservationOffRequest (c_EMFPKA_RLP_INUSE_ReservationOffRequest* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_RLP_INUSE_ReservationAccept */
void FREE_c_EMFPKA_RLP_INUSE_ReservationAccept (c_EMFPKA_RLP_INUSE_ReservationAccept* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_RLP_INUSE_ReservationAccept_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_RLP_INUSE_ReservationReject */
void FREE_c_EMFPKA_RLP_INUSE_ReservationReject (c_EMFPKA_RLP_INUSE_ReservationReject* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_RLP_INUSE_ReservationReject_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_RLP_INUSE_RevReservationOn */
void FREE_c_EMFPKA_RLP_INUSE_RevReservationOn (c_EMFPKA_RLP_INUSE_RevReservationOn* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_RLP_INUSE_RevReservationOn_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_RLP_INUSE_RevReservationOff */
void FREE_c_EMFPKA_RLP_INUSE_RevReservationOff (c_EMFPKA_RLP_INUSE_RevReservationOff* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_RLP_INUSE_RevReservationOff_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_RLP_INUSE_FwdReservationOff */
void FREE_c_EMFPKA_RLP_INUSE_FwdReservationOff (c_EMFPKA_RLP_INUSE_FwdReservationOff* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_RLP_INUSE_FwdReservationOff_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_RLP_INUSE_FwdReservationOn */
void FREE_c_EMFPKA_RLP_INUSE_FwdReservationOn (c_EMFPKA_RLP_INUSE_FwdReservationOn* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_RLP_INUSE_FwdReservationOn_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_RLP_INUSE_FwdReservationAck */
void FREE_c_EMFPKA_RLP_INUSE_FwdReservationAck (c_EMFPKA_RLP_INUSE_FwdReservationAck* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_RLP_INUSE_FwdReservationAck_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_RLP_INUSE_AttributeUpdateRequest */
void FREE_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest (c_EMFPKA_RLP_INUSE_AttributeUpdateRequest* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_RLP_INUSE_AttributeUpdateAccept */
void FREE_c_EMFPKA_RLP_INUSE_AttributeUpdateAccept (c_EMFPKA_RLP_INUSE_AttributeUpdateAccept* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_RLP_INUSE_AttributeUpdateAccept_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_RLP_INUSE_AttributeUpdateReject */
void FREE_c_EMFPKA_RLP_INUSE_AttributeUpdateReject (c_EMFPKA_RLP_INUSE_AttributeUpdateReject* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_RLP_INUSE_AttributeUpdateReject_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_DOSP_INUSE_DataOverSignaling */
void FREE_c_EMFPKA_DOSP_INUSE_DataOverSignaling (c_EMFPKA_DOSP_INUSE_DataOverSignaling* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_DOSP_INUSE_DataOverSignalingAck */
void FREE_c_EMFPKA_DOSP_INUSE_DataOverSignalingAck (c_EMFPKA_DOSP_INUSE_DataOverSignalingAck* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_LUP_INUSE_LocationRequest */
void FREE_c_EMFPKA_LUP_INUSE_LocationRequest (c_EMFPKA_LUP_INUSE_LocationRequest* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_EMFPKA_LUP_INUSE_LocationNotification */
void FREE_c_EMFPKA_LUP_INUSE_LocationNotification (c_EMFPKA_LUP_INUSE_LocationNotification* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_LUP_INUSE_LocationNotification_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_LUP_INUSE_LocationAssignment */
void FREE_c_EMFPKA_LUP_INUSE_LocationAssignment (c_EMFPKA_LUP_INUSE_LocationAssignment* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_LUP_INUSE_LocationAssignment_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_LUP_INUSE_LocationComplete */
void FREE_c_EMFPKA_LUP_INUSE_LocationComplete (c_EMFPKA_LUP_INUSE_LocationComplete* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_LUP_INUSE_LocationComplete_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_LUP_INUSE_StorageBLOBRequest */
void FREE_c_EMFPKA_LUP_INUSE_StorageBLOBRequest (c_EMFPKA_LUP_INUSE_StorageBLOBRequest* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_EMFPKA_LUP_INUSE_StorageBLOBNotification */
void FREE_c_EMFPKA_LUP_INUSE_StorageBLOBNotification (c_EMFPKA_LUP_INUSE_StorageBLOBNotification* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_LUP_INUSE_StorageBLOBAssignment */
void FREE_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment (c_EMFPKA_LUP_INUSE_StorageBLOBAssignment* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_LUP_INUSE_StorageBLOBComplete */
void FREE_c_EMFPKA_LUP_INUSE_StorageBLOBComplete (c_EMFPKA_LUP_INUSE_StorageBLOBComplete* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_LUP_INUSE_StorageBLOBComplete_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_FCP_INUSE_XonRequest */
void FREE_c_EMFPKA_FCP_INUSE_XonRequest (c_EMFPKA_FCP_INUSE_XonRequest* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_EMFPKA_FCP_INUSE_XonResponse */
void FREE_c_EMFPKA_FCP_INUSE_XonResponse (c_EMFPKA_FCP_INUSE_XonResponse* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_EMFPKA_FCP_INUSE_XoffRequest */
void FREE_c_EMFPKA_FCP_INUSE_XoffRequest (c_EMFPKA_FCP_INUSE_XoffRequest* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_EMFPKA_FCP_INUSE_XoffResponse */
void FREE_c_EMFPKA_FCP_INUSE_XoffResponse (c_EMFPKA_FCP_INUSE_XoffResponse* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_EMFPKA_FCP_INUSE_DataReady */
void FREE_c_EMFPKA_FCP_INUSE_DataReady (c_EMFPKA_FCP_INUSE_DataReady* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_FCP_INUSE_DataReady_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_FCP_INUSE_DataReadyAck */
void FREE_c_EMFPKA_FCP_INUSE_DataReadyAck (c_EMFPKA_FCP_INUSE_DataReadyAck* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_FCP_INUSE_DataReadyAck_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_FCP_INUSE_RestartNetworkInterface */
void FREE_c_EMFPKA_FCP_INUSE_RestartNetworkInterface (c_EMFPKA_FCP_INUSE_RestartNetworkInterface* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_FCP_INUSE_RestartNetworkInterface_contents (&(sp->contents));

}

/* Free function for struct c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck */
void FREE_c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck (c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_MMFPA_INCFG_ConfigurationRequest */
void FREE_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest (c_MLMFPA_MMFPA_INCFG_ConfigurationRequest* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_MMFPA_INCFG_ConfigurationResponse */
void FREE_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse (c_MLMFPA_MMFPA_INCFG_ConfigurationResponse* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_RSP_INUSE_RouteSelect */
void FREE_c_MLMFPA_RSP_INUSE_RouteSelect (c_MLMFPA_RSP_INUSE_RouteSelect* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_RSP_INUSE_RouteSelect_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_RSP_INUSE_RouteSelectAck */
void FREE_c_MLMFPA_RSP_INUSE_RouteSelectAck (c_MLMFPA_RSP_INUSE_RouteSelectAck* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_RSP_INUSE_RouteSelectAck_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_RSP_INUSE_ActivateRoute */
void FREE_c_MLMFPA_RSP_INUSE_ActivateRoute (c_MLMFPA_RSP_INUSE_ActivateRoute* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_RSP_INUSE_ActivateRoute_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_RSP_INUSE_ActivateRouteAck */
void FREE_c_MLMFPA_RSP_INUSE_ActivateRouteAck (c_MLMFPA_RSP_INUSE_ActivateRouteAck* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_RSP_INUSE_ActivateRouteAck_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_SRP_INUSE_ResetTxIndication */
void FREE_c_MLMFPA_SRP_INUSE_ResetTxIndication (c_MLMFPA_SRP_INUSE_ResetTxIndication* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_SRP_INUSE_ResetTxIndication_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_SRP_INUSE_ResetRxIndication */
void FREE_c_MLMFPA_SRP_INUSE_ResetRxIndication (c_MLMFPA_SRP_INUSE_ResetRxIndication* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_SRP_INUSE_ResetRxIndication_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_SRP_INUSE_ResetTxIndicationAck */
void FREE_c_MLMFPA_SRP_INUSE_ResetTxIndicationAck (c_MLMFPA_SRP_INUSE_ResetTxIndicationAck* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_SRP_INUSE_ResetTxComplete */
void FREE_c_MLMFPA_SRP_INUSE_ResetTxComplete (c_MLMFPA_SRP_INUSE_ResetTxComplete* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_SRP_INUSE_ResetTxComplete_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_SRP_INUSE_ResetRxComplete */
void FREE_c_MLMFPA_SRP_INUSE_ResetRxComplete (c_MLMFPA_SRP_INUSE_ResetRxComplete* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_SRP_INUSE_ResetRxComplete_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_SRP_INUSE_MultiLinkNak */
void FREE_c_MLMFPA_SRP_INUSE_MultiLinkNak (c_MLMFPA_SRP_INUSE_MultiLinkNak* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_SRP_INUSE_ReservationOnRequest */
void FREE_c_MLMFPA_SRP_INUSE_ReservationOnRequest (c_MLMFPA_SRP_INUSE_ReservationOnRequest* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_SRP_INUSE_ReservationOffRequest */
void FREE_c_MLMFPA_SRP_INUSE_ReservationOffRequest (c_MLMFPA_SRP_INUSE_ReservationOffRequest* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_SRP_INUSE_ReservationAccept */
void FREE_c_MLMFPA_SRP_INUSE_ReservationAccept (c_MLMFPA_SRP_INUSE_ReservationAccept* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_SRP_INUSE_ReservationAccept_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_SRP_INUSE_ReservationReject */
void FREE_c_MLMFPA_SRP_INUSE_ReservationReject (c_MLMFPA_SRP_INUSE_ReservationReject* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_SRP_INUSE_ReservationReject_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_SRP_INUSE_RevReservationOn */
void FREE_c_MLMFPA_SRP_INUSE_RevReservationOn (c_MLMFPA_SRP_INUSE_RevReservationOn* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_SRP_INUSE_RevReservationOn_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_SRP_INUSE_RevReservationOff */
void FREE_c_MLMFPA_SRP_INUSE_RevReservationOff (c_MLMFPA_SRP_INUSE_RevReservationOff* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_SRP_INUSE_RevReservationOff_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_SRP_INUSE_FwdReservationOff */
void FREE_c_MLMFPA_SRP_INUSE_FwdReservationOff (c_MLMFPA_SRP_INUSE_FwdReservationOff* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_SRP_INUSE_FwdReservationOff_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_SRP_INUSE_FwdReservationOn */
void FREE_c_MLMFPA_SRP_INUSE_FwdReservationOn (c_MLMFPA_SRP_INUSE_FwdReservationOn* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_SRP_INUSE_FwdReservationOn_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_SRP_INUSE_FwdReservationAck */
void FREE_c_MLMFPA_SRP_INUSE_FwdReservationAck (c_MLMFPA_SRP_INUSE_FwdReservationAck* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_SRP_INUSE_FwdReservationAck_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_SRP_INUSE_AttributeUpdateRequest */
void FREE_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest (c_MLMFPA_SRP_INUSE_AttributeUpdateRequest* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_SRP_INUSE_AttributeUpdateAccept */
void FREE_c_MLMFPA_SRP_INUSE_AttributeUpdateAccept (c_MLMFPA_SRP_INUSE_AttributeUpdateAccept* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_SRP_INUSE_AttributeUpdateAccept_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_SRP_INUSE_AttributeUpdateReject */
void FREE_c_MLMFPA_SRP_INUSE_AttributeUpdateReject (c_MLMFPA_SRP_INUSE_AttributeUpdateReject* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_SRP_INUSE_AttributeUpdateReject_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_SRP_INUSE_Flush */
void FREE_c_MLMFPA_SRP_INUSE_Flush (c_MLMFPA_SRP_INUSE_Flush* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_SRP_INUSE_Flush_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_SRP_INUSE_Nak */
void FREE_c_MLMFPA_SRP_INUSE_Nak (c_MLMFPA_SRP_INUSE_Nak* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_SRP_INUSE_Nak_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_DOSP_INUSE_DataOverSignaling */
void FREE_c_MLMFPA_DOSP_INUSE_DataOverSignaling (c_MLMFPA_DOSP_INUSE_DataOverSignaling* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_DOSP_INUSE_DataOverSignalingAck */
void FREE_c_MLMFPA_DOSP_INUSE_DataOverSignalingAck (c_MLMFPA_DOSP_INUSE_DataOverSignalingAck* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_LUP_INUSE_LocationRequest */
void FREE_c_MLMFPA_LUP_INUSE_LocationRequest (c_MLMFPA_LUP_INUSE_LocationRequest* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_MLMFPA_LUP_INUSE_LocationNotification */
void FREE_c_MLMFPA_LUP_INUSE_LocationNotification (c_MLMFPA_LUP_INUSE_LocationNotification* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_LUP_INUSE_LocationNotification_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_LUP_INUSE_LocationAssignment */
void FREE_c_MLMFPA_LUP_INUSE_LocationAssignment (c_MLMFPA_LUP_INUSE_LocationAssignment* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_LUP_INUSE_LocationAssignment_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_LUP_INUSE_LocationComplete */
void FREE_c_MLMFPA_LUP_INUSE_LocationComplete (c_MLMFPA_LUP_INUSE_LocationComplete* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_LUP_INUSE_LocationComplete_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_LUP_INUSE_StorageBLOBRequest */
void FREE_c_MLMFPA_LUP_INUSE_StorageBLOBRequest (c_MLMFPA_LUP_INUSE_StorageBLOBRequest* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_MLMFPA_LUP_INUSE_StorageBLOBNotification */
void FREE_c_MLMFPA_LUP_INUSE_StorageBLOBNotification (c_MLMFPA_LUP_INUSE_StorageBLOBNotification* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_LUP_INUSE_StorageBLOBAssignment */
void FREE_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment (c_MLMFPA_LUP_INUSE_StorageBLOBAssignment* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_LUP_INUSE_StorageBLOBComplete */
void FREE_c_MLMFPA_LUP_INUSE_StorageBLOBComplete (c_MLMFPA_LUP_INUSE_StorageBLOBComplete* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_LUP_INUSE_StorageBLOBComplete_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_FCP_INUSE_XonRequest */
void FREE_c_MLMFPA_FCP_INUSE_XonRequest (c_MLMFPA_FCP_INUSE_XonRequest* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_MLMFPA_FCP_INUSE_XonResponse */
void FREE_c_MLMFPA_FCP_INUSE_XonResponse (c_MLMFPA_FCP_INUSE_XonResponse* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_MLMFPA_FCP_INUSE_XoffRequest */
void FREE_c_MLMFPA_FCP_INUSE_XoffRequest (c_MLMFPA_FCP_INUSE_XoffRequest* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_MLMFPA_FCP_INUSE_XoffResponse */
void FREE_c_MLMFPA_FCP_INUSE_XoffResponse (c_MLMFPA_FCP_INUSE_XoffResponse* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_MLMFPA_FCP_INUSE_DataReady */
void FREE_c_MLMFPA_FCP_INUSE_DataReady (c_MLMFPA_FCP_INUSE_DataReady* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_FCP_INUSE_DataReady_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_FCP_INUSE_DataReadyAck */
void FREE_c_MLMFPA_FCP_INUSE_DataReadyAck (c_MLMFPA_FCP_INUSE_DataReadyAck* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_FCP_INUSE_DataReadyAck_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_FCP_INUSE_RestartNetworkInterface */
void FREE_c_MLMFPA_FCP_INUSE_RestartNetworkInterface (c_MLMFPA_FCP_INUSE_RestartNetworkInterface* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_FCP_INUSE_RestartNetworkInterface_contents (&(sp->contents));

}

/* Free function for struct c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck */
void FREE_c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck (c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck_contents (&(sp->contents));

}

/* Free function for struct c_GenericTLV_cs0063 */
void FREE_c_GenericTLV_cs0063 (c_GenericTLV_cs0063* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->TLV_Data.value != NULL) {
		EDFree (sp->TLV_Data.value);
		sp->TLV_Data.value = NULL;
	}
	sp->TLV_Data.usedBits = 0;

}

/* SETITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data** tmp;
		tmp = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data**)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data));
			(sequence->data[i]->ProfileType) = 0;
			(sequence->data[i]->ProfileLength) = 0;
			sequence->data[i]->ProfileValue.value = NULL;
			sequence->data[i]->ProfileValue.usedBits = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->ProfileValue.value != NULL) {
					EDFree (sequence->data[i]->ProfileValue.value);
					sequence->data[i]->ProfileValue.value = NULL;
				}
				sequence->data[i]->ProfileValue.usedBits = 0;
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->ProfileValue.value != NULL) {
		EDFree (sp->ProfileValue.value);
		sp->ProfileValue.value = NULL;
	}
	sp->ProfileValue.usedBits = 0;

}

/* SETITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data** tmp;
		tmp = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data**)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data));
			(sequence->data[i]->ProfileType) = 0;
			(sequence->data[i]->ProfileLength) = 0;
			sequence->data[i]->ProfileValue.value = NULL;
			sequence->data[i]->ProfileValue.usedBits = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->ProfileValue.value != NULL) {
					EDFree (sequence->data[i]->ProfileValue.value);
					sequence->data[i]->ProfileValue.value = NULL;
				}
				sequence->data[i]->ProfileValue.usedBits = 0;
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->ProfileValue.value != NULL) {
		EDFree (sp->ProfileValue.value);
		sp->ProfileValue.value = NULL;
	}
	sp->ProfileValue.usedBits = 0;

}

/* SETITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data** tmp;
		tmp = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data**)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->MaxNumLinkFlowsFwd) = 0;
			(sequence->data[i]->MaxNumLinkFlowsRev) = 0;
			(sequence->data[i]->MaxActivatedLinkFlowsFwd) = 0;
			(sequence->data[i]->MaxActivatedLinkFlowsRev) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data** tmp;
		tmp = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data**)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->MaxNumReservationsFwd) = 0;
			(sequence->data[i]->MaxNumReservationsRev) = 0;
			(sequence->data[i]->MaxNumOpenReservationsFwd) = 0;
			(sequence->data[i]->MaxNumOpenReservationsRev) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data** tmp;
		tmp = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data**)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->AbortTimer) = 0;
			(sequence->data[i]->FlushTimer) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data** tmp;
		tmp = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data**)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->AbortTimer) = 0;
			(sequence->data[i]->FlushTimer) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01* sequence, int desiredItems)
{
	int i, i0;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data** tmp;
		tmp = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data**)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->ReservationCount) = 0;
			sequence->data[i]->data02.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				for (i0=0; i0<sequence->data[i]->data02.items; i0++) {
					EDFree (sequence->data[i]->data02.data[i0]);
					sequence->data[i]->data02.data[i0] = NULL;
				}
				if (sequence->data[i]->data02.data) {EDFree (sequence->data[i]->data02.data); sequence->data[i]->data02.data = NULL; sequence->data[i]->data02.allocatedItems=0; /*FR02A*/}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data02.items; i0++) {
		EDFree (sp->data02.data[i0]);
		sp->data02.data[i0] = NULL;
	}
	if (sp->data02.data) {EDFree (sp->data02.data); sp->data02.data = NULL; sp->data02.allocatedItems=0; /*FR02A*/}

}

/* SETITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02'. Existing items are not changed. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data** tmp;
		tmp = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data**)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data));
			(sequence->data[i]->ReservationLabel) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01* sequence, int desiredItems)
{
	int i, i0;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data** tmp;
		tmp = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data**)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->ReservationCount) = 0;
			sequence->data[i]->data02.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				for (i0=0; i0<sequence->data[i]->data02.items; i0++) {
					EDFree (sequence->data[i]->data02.data[i0]);
					sequence->data[i]->data02.data[i0] = NULL;
				}
				if (sequence->data[i]->data02.data) {EDFree (sequence->data[i]->data02.data); sequence->data[i]->data02.data = NULL; sequence->data[i]->data02.allocatedItems=0; /*FR02A*/}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data02.items; i0++) {
		EDFree (sp->data02.data[i0]);
		sp->data02.data[i0] = NULL;
	}
	if (sp->data02.data) {EDFree (sp->data02.data); sp->data02.data = NULL; sp->data02.allocatedItems=0; /*FR02A*/}

}

/* SETITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02'. Existing items are not changed. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data** tmp;
		tmp = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data**)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data));
			(sequence->data[i]->ReservationLabel) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data** tmp;
		tmp = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data**)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->ProfileType) = 0;
			(sequence->data[i]->ProfileLength) = 0;
			sequence->data[i]->ProfileValue.value = NULL;
			sequence->data[i]->ProfileValue.usedBits = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->ProfileValue.value != NULL) {
					EDFree (sequence->data[i]->ProfileValue.value);
					sequence->data[i]->ProfileValue.value = NULL;
				}
				sequence->data[i]->ProfileValue.usedBits = 0;
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->ProfileValue.value != NULL) {
		EDFree (sp->ProfileValue.value);
		sp->ProfileValue.value = NULL;
	}
	sp->ProfileValue.usedBits = 0;

}

/* SETITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data** tmp;
		tmp = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data**)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->ProfileType) = 0;
			(sequence->data[i]->ProfileLength) = 0;
			sequence->data[i]->ProfileValue.value = NULL;
			sequence->data[i]->ProfileValue.usedBits = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->ProfileValue.value != NULL) {
					EDFree (sequence->data[i]->ProfileValue.value);
					sequence->data[i]->ProfileValue.value = NULL;
				}
				sequence->data[i]->ProfileValue.usedBits = 0;
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->ProfileValue.value != NULL) {
		EDFree (sp->ProfileValue.value);
		sp->ProfileValue.value = NULL;
	}
	sp->ProfileValue.usedBits = 0;

}

/* SETITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data** tmp;
		tmp = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data**)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->ProfileType) = 0;
			(sequence->data[i]->ProfileLength) = 0;
			sequence->data[i]->ProfileValue.value = NULL;
			sequence->data[i]->ProfileValue.usedBits = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->ProfileValue.value != NULL) {
					EDFree (sequence->data[i]->ProfileValue.value);
					sequence->data[i]->ProfileValue.value = NULL;
				}
				sequence->data[i]->ProfileValue.usedBits = 0;
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->ProfileValue.value != NULL) {
		EDFree (sp->ProfileValue.value);
		sp->ProfileValue.value = NULL;
	}
	sp->ProfileValue.usedBits = 0;

}

/* SETITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data** tmp;
		tmp = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data**)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->ProfileType) = 0;
			(sequence->data[i]->ProfileLength) = 0;
			sequence->data[i]->ProfileValue.value = NULL;
			sequence->data[i]->ProfileValue.usedBits = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->ProfileValue.value != NULL) {
					EDFree (sequence->data[i]->ProfileValue.value);
					sequence->data[i]->ProfileValue.value = NULL;
				}
				sequence->data[i]->ProfileValue.usedBits = 0;
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->ProfileValue.value != NULL) {
		EDFree (sp->ProfileValue.value);
		sp->ProfileValue.value = NULL;
	}
	sp->ProfileValue.usedBits = 0;

}

/* SETITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data** tmp;
		tmp = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data**)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->ProtocolID) = 0;
			(sequence->data[i]->ProtocolParametersLength) = 0;
			sequence->data[i]->ProtocolParameters.value = NULL;
			sequence->data[i]->ProtocolParameters.usedBits = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->ProtocolParameters.value != NULL) {
					EDFree (sequence->data[i]->ProtocolParameters.value);
					sequence->data[i]->ProtocolParameters.value = NULL;
				}
				sequence->data[i]->ProtocolParameters.usedBits = 0;
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->ProtocolParameters.value != NULL) {
		EDFree (sp->ProtocolParameters.value);
		sp->ProtocolParameters.value = NULL;
	}
	sp->ProtocolParameters.usedBits = 0;

}

/* SETITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data** tmp;
		tmp = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data**)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->ProtocolID) = 0;
			(sequence->data[i]->ProtocolParametersLength) = 0;
			sequence->data[i]->ProtocolParameters.value = NULL;
			sequence->data[i]->ProtocolParameters.usedBits = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->ProtocolParameters.value != NULL) {
					EDFree (sequence->data[i]->ProtocolParameters.value);
					sequence->data[i]->ProtocolParameters.value = NULL;
				}
				sequence->data[i]->ProtocolParameters.usedBits = 0;
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->ProtocolParameters.value != NULL) {
		EDFree (sp->ProtocolParameters.value);
		sp->ProtocolParameters.value = NULL;
	}
	sp->ProtocolParameters.usedBits = 0;

}

/* SETITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data** tmp;
		tmp = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data**)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->ProtocolID) = 0;
			(sequence->data[i]->ProtocolParametersLength) = 0;
			sequence->data[i]->ProtocolParameters.value = NULL;
			sequence->data[i]->ProtocolParameters.usedBits = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->ProtocolParameters.value != NULL) {
					EDFree (sequence->data[i]->ProtocolParameters.value);
					sequence->data[i]->ProtocolParameters.value = NULL;
				}
				sequence->data[i]->ProtocolParameters.usedBits = 0;
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->ProtocolParameters.value != NULL) {
		EDFree (sp->ProtocolParameters.value);
		sp->ProtocolParameters.value = NULL;
	}
	sp->ProtocolParameters.usedBits = 0;

}

/* SETITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data** tmp;
		tmp = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data**)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->ProtocolID) = 0;
			(sequence->data[i]->ProtocolParametersLength) = 0;
			sequence->data[i]->ProtocolParameters.value = NULL;
			sequence->data[i]->ProtocolParameters.usedBits = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->ProtocolParameters.value != NULL) {
					EDFree (sequence->data[i]->ProtocolParameters.value);
					sequence->data[i]->ProtocolParameters.value = NULL;
				}
				sequence->data[i]->ProtocolParameters.usedBits = 0;
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->ProtocolParameters.value != NULL) {
		EDFree (sp->ProtocolParameters.value);
		sp->ProtocolParameters.value = NULL;
	}
	sp->ProtocolParameters.usedBits = 0;

}

/* SETITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01* sequence, int desiredItems)
{
	int i, i0;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data** tmp;
		tmp = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data**)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->BCMCSFlowCount) = 0;
			sequence->data[i]->data02.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				for (i0=0; i0<sequence->data[i]->data02.items; i0++) {
					EDFree (sequence->data[i]->data02.data[i0]);
					sequence->data[i]->data02.data[i0] = NULL;
				}
				if (sequence->data[i]->data02.data) {EDFree (sequence->data[i]->data02.data); sequence->data[i]->data02.data = NULL; sequence->data[i]->data02.allocatedItems=0; /*FR02A*/}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data02.items; i0++) {
		EDFree (sp->data02.data[i0]);
		sp->data02.data[i0] = NULL;
	}
	if (sp->data02.data) {EDFree (sp->data02.data); sp->data02.data = NULL; sp->data02.allocatedItems=0; /*FR02A*/}

}

/* SETITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02'. Existing items are not changed. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data** tmp;
		tmp = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data**)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data));
			(sequence->data[i]->BCMCSFlowID) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01* sequence, int desiredItems)
{
	int i, i0, i1;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data** tmp;
		tmp = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data**)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->ProgramCount) = 0;
			sequence->data[i]->data02.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				for (i0=0; i0<sequence->data[i]->data02.items; i0++) {
					for (i1=0; i1<sequence->data[i]->data02.data[i0]->data03.items; i1++) {
						EDFree (sequence->data[i]->data02.data[i0]->data03.data[i1]);
						sequence->data[i]->data02.data[i0]->data03.data[i1] = NULL;
					}
					if (sequence->data[i]->data02.data[i0]->data03.data) {EDFree (sequence->data[i]->data02.data[i0]->data03.data); sequence->data[i]->data02.data[i0]->data03.data = NULL; sequence->data[i]->data02.data[i0]->data03.allocatedItems=0; /*FR02A*/}
					EDFree (sequence->data[i]->data02.data[i0]);
					sequence->data[i]->data02.data[i0] = NULL;
				}
				if (sequence->data[i]->data02.data) {EDFree (sequence->data[i]->data02.data); sequence->data[i]->data02.data = NULL; sequence->data[i]->data02.allocatedItems=0; /*FR02A*/}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data* sp) {
	int i0;
	int i1;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data02.items; i0++) {
		for (i1=0; i1<sp->data02.data[i0]->data03.items; i1++) {
			EDFree (sp->data02.data[i0]->data03.data[i1]);
			sp->data02.data[i0]->data03.data[i1] = NULL;
		}
		if (sp->data02.data[i0]->data03.data) {EDFree (sp->data02.data[i0]->data03.data); sp->data02.data[i0]->data03.data = NULL; sp->data02.data[i0]->data03.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data02.data[i0]);
		sp->data02.data[i0] = NULL;
	}
	if (sp->data02.data) {EDFree (sp->data02.data); sp->data02.data = NULL; sp->data02.allocatedItems=0; /*FR02A*/}

}

/* SETITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02'. Existing items are not changed. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02* sequence, int desiredItems)
{
	int i, i0;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data** tmp;
		tmp = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data**)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data));
			(sequence->data[i]->ProgramIDLSBLength) = 0;
			(sequence->data[i]->ProgramIDLSBs) = 0;
			(sequence->data[i]->FlowDiscriminatorCount) = 0;
			sequence->data[i]->data03.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				for (i0=0; i0<sequence->data[i]->data03.items; i0++) {
					EDFree (sequence->data[i]->data03.data[i0]);
					sequence->data[i]->data03.data[i0] = NULL;
				}
				if (sequence->data[i]->data03.data) {EDFree (sequence->data[i]->data03.data); sequence->data[i]->data03.data = NULL; sequence->data[i]->data03.allocatedItems=0; /*FR02A*/}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data03.items; i0++) {
		EDFree (sp->data03.data[i0]);
		sp->data03.data[i0] = NULL;
	}
	if (sp->data03.data) {EDFree (sp->data03.data); sp->data03.data = NULL; sp->data03.allocatedItems=0; /*FR02A*/}

}

/* SETITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03'. Existing items are not changed. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data** tmp;
		tmp = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data**)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data));
			(sequence->data[i]->FlowDiscriminator) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data */
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data** tmp;
		tmp = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data**)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data));
			(sequence->data[i]->ProfileType) = 0;
			(sequence->data[i]->ProfileLength) = 0;
			sequence->data[i]->ProfileValue.value = NULL;
			sequence->data[i]->ProfileValue.usedBits = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->ProfileValue.value != NULL) {
					EDFree (sequence->data[i]->ProfileValue.value);
					sequence->data[i]->ProfileValue.value = NULL;
				}
				sequence->data[i]->ProfileValue.usedBits = 0;
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->ProfileValue.value != NULL) {
		EDFree (sp->ProfileValue.value);
		sp->ProfileValue.value = NULL;
	}
	sp->ProfileValue.usedBits = 0;

}

/* SETITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data** tmp;
		tmp = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data**)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data));
			(sequence->data[i]->ProfileType) = 0;
			(sequence->data[i]->ProfileLength) = 0;
			sequence->data[i]->ProfileValue.value = NULL;
			sequence->data[i]->ProfileValue.usedBits = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->ProfileValue.value != NULL) {
					EDFree (sequence->data[i]->ProfileValue.value);
					sequence->data[i]->ProfileValue.value = NULL;
				}
				sequence->data[i]->ProfileValue.usedBits = 0;
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->ProfileValue.value != NULL) {
		EDFree (sp->ProfileValue.value);
		sp->ProfileValue.value = NULL;
	}
	sp->ProfileValue.usedBits = 0;

}

/* SETITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data** tmp;
		tmp = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data**)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->MaxNumLinkFlowsFwd) = 0;
			(sequence->data[i]->MaxNumLinkFlowsRev) = 0;
			(sequence->data[i]->MaxActivatedLinkFlowsFwd) = 0;
			(sequence->data[i]->MaxActivatedLinkFlowsRev) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data** tmp;
		tmp = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data**)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->MaxNumReservationsFwd) = 0;
			(sequence->data[i]->MaxNumReservationsRev) = 0;
			(sequence->data[i]->MaxNumOpenReservationsFwd) = 0;
			(sequence->data[i]->MaxNumOpenReservationsRev) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_data** tmp;
		tmp = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_data**)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_data*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->SARSequenceLength) = 0;
			(sequence->data[i]->SARSequenceLengthShort) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_data */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_data (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data** tmp;
		tmp = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data**)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->AbortTimer) = 0;
			(sequence->data[i]->FlushTimer) = 0;
			(sequence->data[i]->NakDelayTimer) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data** tmp;
		tmp = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data**)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->AbortTimer) = 0;
			(sequence->data[i]->FlushTimer) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01* sequence, int desiredItems)
{
	int i, i0;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data** tmp;
		tmp = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data**)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->ReservationCount) = 0;
			sequence->data[i]->data02.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				for (i0=0; i0<sequence->data[i]->data02.items; i0++) {
					EDFree (sequence->data[i]->data02.data[i0]);
					sequence->data[i]->data02.data[i0] = NULL;
				}
				if (sequence->data[i]->data02.data) {EDFree (sequence->data[i]->data02.data); sequence->data[i]->data02.data = NULL; sequence->data[i]->data02.allocatedItems=0; /*FR02A*/}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data02.items; i0++) {
		EDFree (sp->data02.data[i0]);
		sp->data02.data[i0] = NULL;
	}
	if (sp->data02.data) {EDFree (sp->data02.data); sp->data02.data = NULL; sp->data02.allocatedItems=0; /*FR02A*/}

}

/* SETITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02'. Existing items are not changed. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data** tmp;
		tmp = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data**)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data));
			(sequence->data[i]->ReservationLabel) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01* sequence, int desiredItems)
{
	int i, i0;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data** tmp;
		tmp = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data**)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->ReservationCount) = 0;
			sequence->data[i]->data02.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				for (i0=0; i0<sequence->data[i]->data02.items; i0++) {
					EDFree (sequence->data[i]->data02.data[i0]);
					sequence->data[i]->data02.data[i0] = NULL;
				}
				if (sequence->data[i]->data02.data) {EDFree (sequence->data[i]->data02.data); sequence->data[i]->data02.data = NULL; sequence->data[i]->data02.allocatedItems=0; /*FR02A*/}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data02.items; i0++) {
		EDFree (sp->data02.data[i0]);
		sp->data02.data[i0] = NULL;
	}
	if (sp->data02.data) {EDFree (sp->data02.data); sp->data02.data = NULL; sp->data02.allocatedItems=0; /*FR02A*/}

}

/* SETITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02'. Existing items are not changed. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data** tmp;
		tmp = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data**)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data));
			(sequence->data[i]->ReservationLabel) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data** tmp;
		tmp = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data**)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->ProfileType) = 0;
			(sequence->data[i]->ProfileLength) = 0;
			sequence->data[i]->ProfileValue.value = NULL;
			sequence->data[i]->ProfileValue.usedBits = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->ProfileValue.value != NULL) {
					EDFree (sequence->data[i]->ProfileValue.value);
					sequence->data[i]->ProfileValue.value = NULL;
				}
				sequence->data[i]->ProfileValue.usedBits = 0;
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->ProfileValue.value != NULL) {
		EDFree (sp->ProfileValue.value);
		sp->ProfileValue.value = NULL;
	}
	sp->ProfileValue.usedBits = 0;

}

/* SETITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data** tmp;
		tmp = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data**)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->ProfileType) = 0;
			(sequence->data[i]->ProfileLength) = 0;
			sequence->data[i]->ProfileValue.value = NULL;
			sequence->data[i]->ProfileValue.usedBits = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->ProfileValue.value != NULL) {
					EDFree (sequence->data[i]->ProfileValue.value);
					sequence->data[i]->ProfileValue.value = NULL;
				}
				sequence->data[i]->ProfileValue.usedBits = 0;
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->ProfileValue.value != NULL) {
		EDFree (sp->ProfileValue.value);
		sp->ProfileValue.value = NULL;
	}
	sp->ProfileValue.usedBits = 0;

}

/* SETITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data** tmp;
		tmp = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data**)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->ProfileType) = 0;
			(sequence->data[i]->ProfileLength) = 0;
			sequence->data[i]->ProfileValue.value = NULL;
			sequence->data[i]->ProfileValue.usedBits = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->ProfileValue.value != NULL) {
					EDFree (sequence->data[i]->ProfileValue.value);
					sequence->data[i]->ProfileValue.value = NULL;
				}
				sequence->data[i]->ProfileValue.usedBits = 0;
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->ProfileValue.value != NULL) {
		EDFree (sp->ProfileValue.value);
		sp->ProfileValue.value = NULL;
	}
	sp->ProfileValue.usedBits = 0;

}

/* SETITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data** tmp;
		tmp = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data**)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->ProfileType) = 0;
			(sequence->data[i]->ProfileLength) = 0;
			sequence->data[i]->ProfileValue.value = NULL;
			sequence->data[i]->ProfileValue.usedBits = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->ProfileValue.value != NULL) {
					EDFree (sequence->data[i]->ProfileValue.value);
					sequence->data[i]->ProfileValue.value = NULL;
				}
				sequence->data[i]->ProfileValue.usedBits = 0;
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->ProfileValue.value != NULL) {
		EDFree (sp->ProfileValue.value);
		sp->ProfileValue.value = NULL;
	}
	sp->ProfileValue.usedBits = 0;

}

/* SETITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data** tmp;
		tmp = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data**)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->ProtocolID) = 0;
			(sequence->data[i]->ProtocolParametersLength) = 0;
			sequence->data[i]->ProtocolParameters.value = NULL;
			sequence->data[i]->ProtocolParameters.usedBits = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->ProtocolParameters.value != NULL) {
					EDFree (sequence->data[i]->ProtocolParameters.value);
					sequence->data[i]->ProtocolParameters.value = NULL;
				}
				sequence->data[i]->ProtocolParameters.usedBits = 0;
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->ProtocolParameters.value != NULL) {
		EDFree (sp->ProtocolParameters.value);
		sp->ProtocolParameters.value = NULL;
	}
	sp->ProtocolParameters.usedBits = 0;

}

/* SETITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data** tmp;
		tmp = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data**)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->ProtocolID) = 0;
			(sequence->data[i]->ProtocolParametersLength) = 0;
			sequence->data[i]->ProtocolParameters.value = NULL;
			sequence->data[i]->ProtocolParameters.usedBits = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->ProtocolParameters.value != NULL) {
					EDFree (sequence->data[i]->ProtocolParameters.value);
					sequence->data[i]->ProtocolParameters.value = NULL;
				}
				sequence->data[i]->ProtocolParameters.usedBits = 0;
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->ProtocolParameters.value != NULL) {
		EDFree (sp->ProtocolParameters.value);
		sp->ProtocolParameters.value = NULL;
	}
	sp->ProtocolParameters.usedBits = 0;

}

/* SETITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data** tmp;
		tmp = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data**)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->ProtocolID) = 0;
			(sequence->data[i]->ProtocolParametersLength) = 0;
			sequence->data[i]->ProtocolParameters.value = NULL;
			sequence->data[i]->ProtocolParameters.usedBits = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->ProtocolParameters.value != NULL) {
					EDFree (sequence->data[i]->ProtocolParameters.value);
					sequence->data[i]->ProtocolParameters.value = NULL;
				}
				sequence->data[i]->ProtocolParameters.usedBits = 0;
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->ProtocolParameters.value != NULL) {
		EDFree (sp->ProtocolParameters.value);
		sp->ProtocolParameters.value = NULL;
	}
	sp->ProtocolParameters.usedBits = 0;

}

/* SETITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data** tmp;
		tmp = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data**)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->ProtocolID) = 0;
			(sequence->data[i]->ProtocolParametersLength) = 0;
			sequence->data[i]->ProtocolParameters.value = NULL;
			sequence->data[i]->ProtocolParameters.usedBits = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->ProtocolParameters.value != NULL) {
					EDFree (sequence->data[i]->ProtocolParameters.value);
					sequence->data[i]->ProtocolParameters.value = NULL;
				}
				sequence->data[i]->ProtocolParameters.usedBits = 0;
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->ProtocolParameters.value != NULL) {
		EDFree (sp->ProtocolParameters.value);
		sp->ProtocolParameters.value = NULL;
	}
	sp->ProtocolParameters.usedBits = 0;

}

/* SETITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01* sequence, int desiredItems)
{
	int i, i0;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data** tmp;
		tmp = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data**)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->BCMCSFlowCount) = 0;
			sequence->data[i]->data02.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				for (i0=0; i0<sequence->data[i]->data02.items; i0++) {
					EDFree (sequence->data[i]->data02.data[i0]);
					sequence->data[i]->data02.data[i0] = NULL;
				}
				if (sequence->data[i]->data02.data) {EDFree (sequence->data[i]->data02.data); sequence->data[i]->data02.data = NULL; sequence->data[i]->data02.allocatedItems=0; /*FR02A*/}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data02.items; i0++) {
		EDFree (sp->data02.data[i0]);
		sp->data02.data[i0] = NULL;
	}
	if (sp->data02.data) {EDFree (sp->data02.data); sp->data02.data = NULL; sp->data02.allocatedItems=0; /*FR02A*/}

}

/* SETITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02'. Existing items are not changed. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data** tmp;
		tmp = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data**)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data));
			(sequence->data[i]->BCMCSFlowID) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01* sequence, int desiredItems)
{
	int i, i0, i1;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data** tmp;
		tmp = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data**)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->ProgramCount) = 0;
			sequence->data[i]->data02.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				for (i0=0; i0<sequence->data[i]->data02.items; i0++) {
					for (i1=0; i1<sequence->data[i]->data02.data[i0]->data03.items; i1++) {
						EDFree (sequence->data[i]->data02.data[i0]->data03.data[i1]);
						sequence->data[i]->data02.data[i0]->data03.data[i1] = NULL;
					}
					if (sequence->data[i]->data02.data[i0]->data03.data) {EDFree (sequence->data[i]->data02.data[i0]->data03.data); sequence->data[i]->data02.data[i0]->data03.data = NULL; sequence->data[i]->data02.data[i0]->data03.allocatedItems=0; /*FR02A*/}
					EDFree (sequence->data[i]->data02.data[i0]);
					sequence->data[i]->data02.data[i0] = NULL;
				}
				if (sequence->data[i]->data02.data) {EDFree (sequence->data[i]->data02.data); sequence->data[i]->data02.data = NULL; sequence->data[i]->data02.allocatedItems=0; /*FR02A*/}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data* sp) {
	int i0;
	int i1;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data02.items; i0++) {
		for (i1=0; i1<sp->data02.data[i0]->data03.items; i1++) {
			EDFree (sp->data02.data[i0]->data03.data[i1]);
			sp->data02.data[i0]->data03.data[i1] = NULL;
		}
		if (sp->data02.data[i0]->data03.data) {EDFree (sp->data02.data[i0]->data03.data); sp->data02.data[i0]->data03.data = NULL; sp->data02.data[i0]->data03.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data02.data[i0]);
		sp->data02.data[i0] = NULL;
	}
	if (sp->data02.data) {EDFree (sp->data02.data); sp->data02.data = NULL; sp->data02.allocatedItems=0; /*FR02A*/}

}

/* SETITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02'. Existing items are not changed. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02* sequence, int desiredItems)
{
	int i, i0;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data** tmp;
		tmp = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data**)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data));
			(sequence->data[i]->ProgramIDLSBLength) = 0;
			(sequence->data[i]->ProgramIDLSBs) = 0;
			(sequence->data[i]->FlowDiscriminatorCount) = 0;
			sequence->data[i]->data03.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				for (i0=0; i0<sequence->data[i]->data03.items; i0++) {
					EDFree (sequence->data[i]->data03.data[i0]);
					sequence->data[i]->data03.data[i0] = NULL;
				}
				if (sequence->data[i]->data03.data) {EDFree (sequence->data[i]->data03.data); sequence->data[i]->data03.data = NULL; sequence->data[i]->data03.allocatedItems=0; /*FR02A*/}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data03.items; i0++) {
		EDFree (sp->data03.data[i0]);
		sp->data03.data[i0] = NULL;
	}
	if (sp->data03.data) {EDFree (sp->data03.data); sp->data03.data = NULL; sp->data03.allocatedItems=0; /*FR02A*/}

}

/* SETITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03'. Existing items are not changed. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data** tmp;
		tmp = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data**)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data));
			(sequence->data[i]->FlowDiscriminator) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data */
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Values'. Existing items are not changed. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Values (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Values* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		ED_LONG* tmp;
		tmp = (ED_LONG*)EDAlloc (sizeof (ED_LONG) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (ED_LONG) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Set-present function for c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex LEVEL = 0 */
void GLOB_SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex* sp, TPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex toBeSetPresent) 
{
	FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex (sp);
	sp->Present = toBeSetPresent;
	
	switch (toBeSetPresent) {
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedQoSProfiles: {
			sp->u.ATSupportedQoSProfiles = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles));
			INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles (sp->u.ATSupportedQoSProfiles);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ANSupportedQoSProfiles: {
			sp->u.ANSupportedQoSProfiles = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles));
			INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles (sp->u.ANSupportedQoSProfiles);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_MaxLinkFlows: {
			sp->u.MaxLinkFlows = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows));
			INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows (sp->u.MaxLinkFlows);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_MaxReservations: {
			sp->u.MaxReservations = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations));
			INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations (sp->u.MaxReservations);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersFwd: {
			sp->u.FlowNNTimersFwd = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd));
			INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd (sp->u.FlowNNTimersFwd);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersRev: {
			sp->u.FlowNNTimersRev = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev));
			INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev (sp->u.FlowNNTimersRev);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationFwd: {
			sp->u.FlowNNReservationFwd = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd));
			INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd (sp->u.FlowNNReservationFwd);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationRev: {
			sp->u.FlowNNReservationRev = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev));
			INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev (sp->u.FlowNNReservationRev);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestFwd: {
			sp->u.ReservationKKQoSRequestFwd = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd));
			INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd (sp->u.ReservationKKQoSRequestFwd);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestRev: {
			sp->u.ReservationKKQoSRequestRev = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev));
			INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev (sp->u.ReservationKKQoSRequestRev);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseFwd: {
			sp->u.ReservationKKQoSResponseFwd = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd));
			INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd (sp->u.ReservationKKQoSResponseFwd);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseRev: {
			sp->u.ReservationKKQoSResponseRev = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev));
			INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev (sp->u.ReservationKKQoSResponseRev);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersFwd: {
			sp->u.FlowNNFlowProtocolParametersFwd = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd));
			INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd (sp->u.FlowNNFlowProtocolParametersFwd);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersRev: {
			sp->u.FlowNNFlowProtocolParametersRev = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev));
			INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev (sp->u.FlowNNFlowProtocolParametersRev);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersFwd: {
			sp->u.FlowNNRouteProtocolParametersFwd = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd));
			INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd (sp->u.FlowNNRouteProtocolParametersFwd);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersRev: {
			sp->u.FlowNNRouteProtocolParametersRev = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev));
			INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev (sp->u.FlowNNRouteProtocolParametersRev);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedFlowProtocolParametersPP: {
			sp->u.ATSupportedFlowProtocolParametersPP = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP));
			INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP (sp->u.ATSupportedFlowProtocolParametersPP);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedRouteProtocolParametersPP: {
			sp->u.ATSupportedRouteProtocolParametersPP = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP));
			INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP (sp->u.ATSupportedRouteProtocolParametersPP);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSFlowIDAssociation: {
			sp->u.ReservationKKBCMCSFlowIDAssociation = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation));
			INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation (sp->u.ReservationKKBCMCSFlowIDAssociation);

			break;
		}
		case U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSProgramIDAssociation: {
			sp->u.ReservationKKBCMCSProgramIDAssociation = (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation*)EDAlloc (sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation));
			INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation (sp->u.ReservationKKBCMCSProgramIDAssociation);

			break;
		}
		default:;	}
}

/* SETITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Values'. Existing items are not changed. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Values (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Values* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		ED_LONG* tmp;
		tmp = (ED_LONG*)EDAlloc (sizeof (ED_LONG) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (ED_LONG) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			(sequence->data[i]) = 0;
		}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Set-present function for c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex LEVEL = 0 */
void GLOB_SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex* sp, TPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex toBeSetPresent) 
{
	FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex (sp);
	sp->Present = toBeSetPresent;
	
	switch (toBeSetPresent) {
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedQoSProfiles: {
			sp->u.ATSupportedQoSProfiles = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles));
			INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles (sp->u.ATSupportedQoSProfiles);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ANSupportedQoSProfiles: {
			sp->u.ANSupportedQoSProfiles = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles));
			INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles (sp->u.ANSupportedQoSProfiles);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_MaxLinkFlows: {
			sp->u.MaxLinkFlows = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows));
			INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows (sp->u.MaxLinkFlows);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_MaxReservations: {
			sp->u.MaxReservations = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations));
			INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations (sp->u.MaxReservations);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNSequenceLengthFwd: {
			sp->u.FlowNNSequenceLengthFwd = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd));
			INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd (sp->u.FlowNNSequenceLengthFwd);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersFwd: {
			sp->u.FlowNNTimersFwd = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd));
			INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd (sp->u.FlowNNTimersFwd);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersRev: {
			sp->u.FlowNNTimersRev = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev));
			INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev (sp->u.FlowNNTimersRev);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationFwd: {
			sp->u.FlowNNReservationFwd = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd));
			INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd (sp->u.FlowNNReservationFwd);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationRev: {
			sp->u.FlowNNReservationRev = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev));
			INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev (sp->u.FlowNNReservationRev);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestFwd: {
			sp->u.ReservationKKQoSRequestFwd = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd));
			INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd (sp->u.ReservationKKQoSRequestFwd);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestRev: {
			sp->u.ReservationKKQoSRequestRev = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev));
			INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev (sp->u.ReservationKKQoSRequestRev);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseFwd: {
			sp->u.ReservationKKQoSResponseFwd = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd));
			INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd (sp->u.ReservationKKQoSResponseFwd);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseRev: {
			sp->u.ReservationKKQoSResponseRev = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev));
			INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev (sp->u.ReservationKKQoSResponseRev);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersFwd: {
			sp->u.FlowNNFlowProtocolParametersFwd = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd));
			INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd (sp->u.FlowNNFlowProtocolParametersFwd);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersRev: {
			sp->u.FlowNNFlowProtocolParametersRev = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev));
			INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev (sp->u.FlowNNFlowProtocolParametersRev);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersFwd: {
			sp->u.FlowNNRouteProtocolParametersFwd = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd));
			INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd (sp->u.FlowNNRouteProtocolParametersFwd);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersRev: {
			sp->u.FlowNNRouteProtocolParametersRev = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev));
			INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev (sp->u.FlowNNRouteProtocolParametersRev);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedFlowProtocolParametersPP: {
			sp->u.ATSupportedFlowProtocolParametersPP = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP));
			INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP (sp->u.ATSupportedFlowProtocolParametersPP);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedRouteProtocolParametersPP: {
			sp->u.ATSupportedRouteProtocolParametersPP = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP));
			INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP (sp->u.ATSupportedRouteProtocolParametersPP);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSFlowIDAssociation: {
			sp->u.ReservationKKBCMCSFlowIDAssociation = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation));
			INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation (sp->u.ReservationKKBCMCSFlowIDAssociation);

			break;
		}
		case U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSProgramIDAssociation: {
			sp->u.ReservationKKBCMCSProgramIDAssociation = (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation*)EDAlloc (sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation));
			INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation (sp->u.ReservationKKBCMCSProgramIDAssociation);

			break;
		}
		default:;	}
}

/* SETITEMS commands for type 'c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01'. Existing items are not changed. */
int SETITEMS_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01 (c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01_data** tmp;
		tmp = (c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01_data**)EDAlloc (sizeof (c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01_data*)EDAlloc (sizeof (c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01_data));
			(sequence->data[i]->AttributeLength) = 0;
			INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes (&(sequence->data[i]->AttributeRecord));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes (&(sequence->data[i]->AttributeRecord));
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01_data */
void FREE_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01_data (c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes (&(sp->AttributeRecord));

}

/* SETITEMS commands for type 'c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01'. Existing items are not changed. */
int SETITEMS_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01 (c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01_data** tmp;
		tmp = (c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01_data**)EDAlloc (sizeof (c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01_data*)EDAlloc (sizeof (c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01_data));
			(sequence->data[i]->AttributeLength) = 0;
			INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response (&(sequence->data[i]->AttributeRecord));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response (&(sequence->data[i]->AttributeRecord));
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01_data */
void FREE_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01_data (c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response (&(sp->AttributeRecord));

}

/* SETITEMS commands for type 'c_EMFPKA_RLP_INUSE_Nak_contents_data01'. Existing items are not changed. */
int SETITEMS_c_EMFPKA_RLP_INUSE_Nak_contents_data01 (c_EMFPKA_RLP_INUSE_Nak_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_EMFPKA_RLP_INUSE_Nak_contents_data01_data** tmp;
		tmp = (c_EMFPKA_RLP_INUSE_Nak_contents_data01_data**)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_Nak_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_EMFPKA_RLP_INUSE_Nak_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_EMFPKA_RLP_INUSE_Nak_contents_data01_data*)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_Nak_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_EMFPKA_RLP_INUSE_Nak_contents_data01_data));
			sequence->data[i]->FirstErasedDataUnit.value = NULL;
			sequence->data[i]->FirstErasedDataUnit.usedBits = 0;
			
			sequence->data[i]->WindowLen.value = NULL;
			sequence->data[i]->WindowLen.usedBits = 0;
			
			sequence->data[i]->VR.value = NULL;
			sequence->data[i]->VR.usedBits = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->FirstErasedDataUnit.value != NULL) {
					EDFree (sequence->data[i]->FirstErasedDataUnit.value);
					sequence->data[i]->FirstErasedDataUnit.value = NULL;
				}
				sequence->data[i]->FirstErasedDataUnit.usedBits = 0;
				if (sequence->data[i]->WindowLen.value != NULL) {
					EDFree (sequence->data[i]->WindowLen.value);
					sequence->data[i]->WindowLen.value = NULL;
				}
				sequence->data[i]->WindowLen.usedBits = 0;
				if (sequence->data[i]->VR.value != NULL) {
					EDFree (sequence->data[i]->VR.value);
					sequence->data[i]->VR.value = NULL;
				}
				sequence->data[i]->VR.usedBits = 0;
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_EMFPKA_RLP_INUSE_Nak_contents_data01_data */
void FREE_c_EMFPKA_RLP_INUSE_Nak_contents_data01_data (c_EMFPKA_RLP_INUSE_Nak_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->FirstErasedDataUnit.value != NULL) {
		EDFree (sp->FirstErasedDataUnit.value);
		sp->FirstErasedDataUnit.value = NULL;
	}
	sp->FirstErasedDataUnit.usedBits = 0;
	if (sp->WindowLen.value != NULL) {
		EDFree (sp->WindowLen.value);
		sp->WindowLen.value = NULL;
	}
	sp->WindowLen.usedBits = 0;
	if (sp->VR.value != NULL) {
		EDFree (sp->VR.value);
		sp->VR.value = NULL;
	}
	sp->VR.usedBits = 0;

}

/* SETITEMS commands for type 'c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01'. Existing items are not changed. */
int SETITEMS_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01 (c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data** tmp;
		tmp = (c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data**)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data*)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data));
			(sequence->data[i]->Link) = 0;
			(sequence->data[i]->ReservationLabel) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->EmergencyIndication_Present) {
				}
				if (sequence->data[i]->ReservationQueuingReq_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data */
void FREE_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data (c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01'. Existing items are not changed. */
int SETITEMS_c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01 (c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01_data** tmp;
		tmp = (c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01_data**)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01_data*)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01_data));
			(sequence->data[i]->Link) = 0;
			(sequence->data[i]->ReservationLabel) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01_data */
void FREE_c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01_data (c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01'. Existing items are not changed. */
int SETITEMS_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01 (c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01* sequence, int desiredItems)
{
	int i, i0;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data** tmp;
		tmp = (c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data**)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data*)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data));
			(sequence->data[i]->AllowableLink) = 0;
			(sequence->data[i]->AllowableReservationLabel) = 0;
			sequence->data[i]->data02.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				for (i0=0; i0<sequence->data[i]->data02.items; i0++) {
					if (sequence->data[i]->data02.data[i0]->RejectCode_Present) {
					}
					if (sequence->data[i]->data02.data[i0]->PendingDuration_Present) {
					}
					EDFree (sequence->data[i]->data02.data[i0]);
					sequence->data[i]->data02.data[i0] = NULL;
				}
				if (sequence->data[i]->data02.data) {EDFree (sequence->data[i]->data02.data); sequence->data[i]->data02.data = NULL; sequence->data[i]->data02.allocatedItems=0; /*FR02A*/}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data */
void FREE_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data (c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data02.items; i0++) {
		if (sp->data02.data[i0]->RejectCode_Present) {
		}
		if (sp->data02.data[i0]->PendingDuration_Present) {
		}
		EDFree (sp->data02.data[i0]);
		sp->data02.data[i0] = NULL;
	}
	if (sp->data02.data) {EDFree (sp->data02.data); sp->data02.data = NULL; sp->data02.allocatedItems=0; /*FR02A*/}

}

/* SETITEMS commands for type 'c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02'. Existing items are not changed. */
int SETITEMS_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02 (c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02_data** tmp;
		tmp = (c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02_data**)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02_data*)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02_data));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->RejectCode_Present) {
				}
				if (sequence->data[i]->PendingDuration_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02_data */
void FREE_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02_data (c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01'. Existing items are not changed. */
int SETITEMS_c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01 (c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01_data** tmp;
		tmp = (c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01_data**)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01_data*)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01_data));
			(sequence->data[i]->ReservationLabel) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01_data */
void FREE_c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01_data (c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01'. Existing items are not changed. */
int SETITEMS_c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01 (c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01_data** tmp;
		tmp = (c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01_data**)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01_data*)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01_data));
			(sequence->data[i]->ReservationLabel) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01_data */
void FREE_c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01_data (c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01'. Existing items are not changed. */
int SETITEMS_c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01 (c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01_data** tmp;
		tmp = (c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01_data**)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01_data*)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01_data));
			(sequence->data[i]->ReservationLabel) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01_data */
void FREE_c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01_data (c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01'. Existing items are not changed. */
int SETITEMS_c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01 (c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01_data** tmp;
		tmp = (c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01_data**)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01_data*)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01_data));
			(sequence->data[i]->ReservationLabel) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01_data */
void FREE_c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01_data (c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01'. Existing items are not changed. */
int SETITEMS_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01 (c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01_data** tmp;
		tmp = (c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01_data**)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01_data*)EDAlloc (sizeof (c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01_data));
			(sequence->data[i]->AttributeLength) = 0;
			INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes (&(sequence->data[i]->AttributeRecord));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes (&(sequence->data[i]->AttributeRecord));
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01_data */
void FREE_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01_data (c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes (&(sp->AttributeRecord));

}

/* SETITEMS commands for type 'c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01'. Existing items are not changed. */
int SETITEMS_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01 (c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01_data** tmp;
		tmp = (c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01_data**)EDAlloc (sizeof (c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01_data*)EDAlloc (sizeof (c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01_data));
			(sequence->data[i]->AttributeLength) = 0;
			INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes (&(sequence->data[i]->AttributeRecord));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes (&(sequence->data[i]->AttributeRecord));
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01_data */
void FREE_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01_data (c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes (&(sp->AttributeRecord));

}

/* SETITEMS commands for type 'c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01'. Existing items are not changed. */
int SETITEMS_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01 (c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01_data** tmp;
		tmp = (c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01_data**)EDAlloc (sizeof (c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01_data*)EDAlloc (sizeof (c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01_data));
			(sequence->data[i]->AttributeLength) = 0;
			INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response (&(sequence->data[i]->AttributeRecord));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response (&(sequence->data[i]->AttributeRecord));
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01_data */
void FREE_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01_data (c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response (&(sp->AttributeRecord));

}

/* SETITEMS commands for type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01'. Existing items are not changed. */
int SETITEMS_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01 (c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data** tmp;
		tmp = (c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data**)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data));
			(sequence->data[i]->DelayedNak) = 0;
			(sequence->data[i]->LeadingEdgeIncluded) = 0;
			sequence->data[i]->TrailingEdge.value = NULL;
			sequence->data[i]->TrailingEdge.usedBits = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->LeadingEdge_Present) {
					if (sequence->data[i]->LeadingEdge->value != NULL) {
						EDFree (sequence->data[i]->LeadingEdge->value);
						sequence->data[i]->LeadingEdge->value = NULL;
					}
					sequence->data[i]->LeadingEdge->usedBits = 0;
					EDFree (sequence->data[i]->LeadingEdge);
				}
				if (sequence->data[i]->TrailingEdge.value != NULL) {
					EDFree (sequence->data[i]->TrailingEdge.value);
					sequence->data[i]->TrailingEdge.value = NULL;
				}
				sequence->data[i]->TrailingEdge.usedBits = 0;
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data */
void FREE_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data (c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->LeadingEdge_Present) {
		if (sp->LeadingEdge->value != NULL) {
			EDFree (sp->LeadingEdge->value);
			sp->LeadingEdge->value = NULL;
		}
		sp->LeadingEdge->usedBits = 0;
		EDFree (sp->LeadingEdge);
		sp->LeadingEdge_Present = ED_FALSE;
	}
	if (sp->TrailingEdge.value != NULL) {
		EDFree (sp->TrailingEdge.value);
		sp->TrailingEdge.value = NULL;
	}
	sp->TrailingEdge.usedBits = 0;

}

void SETPRESENT_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data_LeadingEdge (c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->LeadingEdge_Present == present) return;
	sp->LeadingEdge_Present = present;
	if (present) {
		/*-->*/sp->LeadingEdge = (c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data_LeadingEdge*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data_LeadingEdge));
		sp->LeadingEdge->value = NULL;
		sp->LeadingEdge->usedBits = 0;
	} else {
		if (sp->LeadingEdge->value != NULL) {
			EDFree (sp->LeadingEdge->value);
			sp->LeadingEdge->value = NULL;
		}
		sp->LeadingEdge->usedBits = 0;
		EDFree (sp->LeadingEdge);
	}
}

/* SETITEMS commands for type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02'. Existing items are not changed. */
int SETITEMS_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02 (c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02_data** tmp;
		tmp = (c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02_data**)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02_data*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02_data));
			sequence->data[i]->LargestSAR.value = NULL;
			sequence->data[i]->LargestSAR.usedBits = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->LargestSAR.value != NULL) {
					EDFree (sequence->data[i]->LargestSAR.value);
					sequence->data[i]->LargestSAR.value = NULL;
				}
				sequence->data[i]->LargestSAR.usedBits = 0;
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02_data */
void FREE_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02_data (c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->LargestSAR.value != NULL) {
		EDFree (sp->LargestSAR.value);
		sp->LargestSAR.value = NULL;
	}
	sp->LargestSAR.usedBits = 0;

}

/* SETITEMS commands for type 'c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01'. Existing items are not changed. */
int SETITEMS_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01 (c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data** tmp;
		tmp = (c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data**)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data));
			(sequence->data[i]->Link) = 0;
			(sequence->data[i]->ReservationLabel) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->EmergencyIndication_Present) {
				}
				if (sequence->data[i]->ReservationQueuingReq_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data */
void FREE_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data (c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01'. Existing items are not changed. */
int SETITEMS_c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01 (c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01_data** tmp;
		tmp = (c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01_data**)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01_data*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01_data));
			(sequence->data[i]->Link) = 0;
			(sequence->data[i]->ReservationLabel) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01_data */
void FREE_c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01_data (c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01'. Existing items are not changed. */
int SETITEMS_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01 (c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01* sequence, int desiredItems)
{
	int i, i0;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data** tmp;
		tmp = (c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data**)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data));
			(sequence->data[i]->AllowableLink) = 0;
			(sequence->data[i]->AllowableReservationLabel) = 0;
			sequence->data[i]->data02.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				for (i0=0; i0<sequence->data[i]->data02.items; i0++) {
					if (sequence->data[i]->data02.data[i0]->RejectCode_Present) {
					}
					if (sequence->data[i]->data02.data[i0]->PendingDuration_Present) {
					}
					EDFree (sequence->data[i]->data02.data[i0]);
					sequence->data[i]->data02.data[i0] = NULL;
				}
				if (sequence->data[i]->data02.data) {EDFree (sequence->data[i]->data02.data); sequence->data[i]->data02.data = NULL; sequence->data[i]->data02.allocatedItems=0; /*FR02A*/}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data */
void FREE_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data (c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data02.items; i0++) {
		if (sp->data02.data[i0]->RejectCode_Present) {
		}
		if (sp->data02.data[i0]->PendingDuration_Present) {
		}
		EDFree (sp->data02.data[i0]);
		sp->data02.data[i0] = NULL;
	}
	if (sp->data02.data) {EDFree (sp->data02.data); sp->data02.data = NULL; sp->data02.allocatedItems=0; /*FR02A*/}

}

/* SETITEMS commands for type 'c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02'. Existing items are not changed. */
int SETITEMS_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02 (c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02_data** tmp;
		tmp = (c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02_data**)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02_data*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02_data));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->RejectCode_Present) {
				}
				if (sequence->data[i]->PendingDuration_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02_data */
void FREE_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02_data (c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01'. Existing items are not changed. */
int SETITEMS_c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01 (c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01_data** tmp;
		tmp = (c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01_data**)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01_data*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01_data));
			(sequence->data[i]->ReservationLabel) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01_data */
void FREE_c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01_data (c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01'. Existing items are not changed. */
int SETITEMS_c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01 (c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01_data** tmp;
		tmp = (c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01_data**)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01_data*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01_data));
			(sequence->data[i]->ReservationLabel) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01_data */
void FREE_c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01_data (c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01'. Existing items are not changed. */
int SETITEMS_c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01 (c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01_data** tmp;
		tmp = (c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01_data**)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01_data*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01_data));
			(sequence->data[i]->ReservationLabel) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01_data */
void FREE_c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01_data (c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01'. Existing items are not changed. */
int SETITEMS_c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01 (c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01_data** tmp;
		tmp = (c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01_data**)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01_data*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01_data));
			(sequence->data[i]->ReservationLabel) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01_data */
void FREE_c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01_data (c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01'. Existing items are not changed. */
int SETITEMS_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01 (c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01_data** tmp;
		tmp = (c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01_data**)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01_data*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01_data));
			(sequence->data[i]->AttributeLength) = 0;
			INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes (&(sequence->data[i]->AttributeRecord));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes (&(sequence->data[i]->AttributeRecord));
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01_data */
void FREE_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01_data (c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes (&(sp->AttributeRecord));

}

/* SETITEMS commands for type 'c_MLMFPA_SRP_INUSE_Nak_contents_data01'. Existing items are not changed. */
int SETITEMS_c_MLMFPA_SRP_INUSE_Nak_contents_data01 (c_MLMFPA_SRP_INUSE_Nak_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_MLMFPA_SRP_INUSE_Nak_contents_data01_data** tmp;
		tmp = (c_MLMFPA_SRP_INUSE_Nak_contents_data01_data**)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_Nak_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_MLMFPA_SRP_INUSE_Nak_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_MLMFPA_SRP_INUSE_Nak_contents_data01_data*)EDAlloc (sizeof (c_MLMFPA_SRP_INUSE_Nak_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_MLMFPA_SRP_INUSE_Nak_contents_data01_data));
			sequence->data[i]->FirstErasedDataUnit.value = NULL;
			sequence->data[i]->FirstErasedDataUnit.usedBits = 0;
			
			sequence->data[i]->WindowLen.value = NULL;
			sequence->data[i]->WindowLen.usedBits = 0;
			
			sequence->data[i]->VR.value = NULL;
			sequence->data[i]->VR.usedBits = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->FirstErasedDataUnit.value != NULL) {
					EDFree (sequence->data[i]->FirstErasedDataUnit.value);
					sequence->data[i]->FirstErasedDataUnit.value = NULL;
				}
				sequence->data[i]->FirstErasedDataUnit.usedBits = 0;
				if (sequence->data[i]->WindowLen.value != NULL) {
					EDFree (sequence->data[i]->WindowLen.value);
					sequence->data[i]->WindowLen.value = NULL;
				}
				sequence->data[i]->WindowLen.usedBits = 0;
				if (sequence->data[i]->VR.value != NULL) {
					EDFree (sequence->data[i]->VR.value);
					sequence->data[i]->VR.value = NULL;
				}
				sequence->data[i]->VR.usedBits = 0;
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_MLMFPA_SRP_INUSE_Nak_contents_data01_data */
void FREE_c_MLMFPA_SRP_INUSE_Nak_contents_data01_data (c_MLMFPA_SRP_INUSE_Nak_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->FirstErasedDataUnit.value != NULL) {
		EDFree (sp->FirstErasedDataUnit.value);
		sp->FirstErasedDataUnit.value = NULL;
	}
	sp->FirstErasedDataUnit.usedBits = 0;
	if (sp->WindowLen.value != NULL) {
		EDFree (sp->WindowLen.value);
		sp->WindowLen.value = NULL;
	}
	sp->WindowLen.usedBits = 0;
	if (sp->VR.value != NULL) {
		EDFree (sp->VR.value);
		sp->VR.value = NULL;
	}
	sp->VR.usedBits = 0;

}

