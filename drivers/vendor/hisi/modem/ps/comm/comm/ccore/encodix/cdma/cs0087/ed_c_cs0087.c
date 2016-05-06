/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c
	http://www.Dafocus.it/
**************************************************************************/
/*lint -e959 -e530 -e774 -e572 -e778 -e525 -e539 -e701 -e123 -e438 -e119 -e506 -e529 -e550 -e666 -e713 -e719 -e730 -e734 -e744 -e801 -e801 -e813 -e830 -e40 */
#define ENCODIX_CS0087

#include "ed_c_cs0087.h"
#include "ed_lib.h"
#if ED_COMMON_CRC != 0x328E3625 && ED_VERSION != 10152 && ED_VERSION != 10153
#error Invalid Encodix library files linked; used those distributed with Encodix 1.0.154
#endif


/* Free function for struct c_RPD_Inter_RAT_Overhead_Messages_CS0024B */
void FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (c_RPD_Inter_RAT_Overhead_Messages_CS0024B* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_RPDSES_SL_UATIAssignment_contents */
void FREE_c_RPDSES_SL_UATIAssignment_contents (c_RPDSES_SL_UATIAssignment_contents* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->UATI104_Present) {
		EDFree (sp->UATI104);
		sp->UATI104_Present = ED_FALSE;
	}

}

void SETPRESENT_c_RPDSES_SL_UATIAssignment_contents_UATI104 (c_RPDSES_SL_UATIAssignment_contents* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->UATI104_Present == present) return;
	sp->UATI104_Present = present;
	if (present) {
		/*-->*/sp->UATI104 = (ED_BYTE*)EDAlloc ((size_t)13);
		ED_RESET_MEM (sp->UATI104, 13);
	} else {
		EDFree (sp->UATI104);
	}
}

/* Free function for variable-sized sequence c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01 */
void FREE_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01 (c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data[i]->AttributeRecord));
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents */
void FREE_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents (c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data01.data[i0]->AttributeRecord));
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01 */
void FREE_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01 (c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data[i]->AttributeRecord));
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents */
void FREE_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents (c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data01.data[i0]->AttributeRecord));
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for struct c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq_contents */
void FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq_contents (c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf_contents */
void FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf_contents (c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail_contents */
void FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail_contents (c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq_contents */
void FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq_contents (c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf_contents */
void FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf_contents (c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete_contents */
void FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete_contents (c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for variable-sized sequence c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01 */
void FREE_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01 (c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data[i]->AttributeRecord));
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents */
void FREE_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents (c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data01.data[i0]->AttributeRecord));
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01 */
void FREE_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01 (c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data[i]->AttributeRecord));
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents */
void FREE_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents (c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data01.data[i0]->AttributeRecord));
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for struct c_RPDCON_IRATINSP_INUSE_Sync_contents */
void FREE_c_RPDCON_IRATINSP_INUSE_Sync_contents (c_RPDCON_IRATINSP_INUSE_Sync_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for variable-sized sequence c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01 */
void FREE_c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01 (c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data[i]->AttributeRecord));
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents */
void FREE_c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents (c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data01.data[i0]->AttributeRecord));
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01 */
void FREE_c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01 (c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data[i]->AttributeRecord));
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents */
void FREE_c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents (c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data01.data[i0]->AttributeRecord));
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01 */
void FREE_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01 (c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents */
void FREE_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents (c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for struct c_RPDCON_IRATISP_INUSE_ConnectionDeny_contents */
void FREE_c_RPDCON_IRATISP_INUSE_ConnectionDeny_contents (c_RPDCON_IRATISP_INUSE_ConnectionDeny_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for variable-sized sequence c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01 */
void FREE_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01 (c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data[i]->AttributeRecord));
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents */
void FREE_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents (c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data01.data[i0]->AttributeRecord));
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for struct c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept_contents */
void FREE_c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept_contents (c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_RPDCON_IRATISP_INUSE_AttributeUpdateReject_contents */
void FREE_c_RPDCON_IRATISP_INUSE_AttributeUpdateReject_contents (c_RPDCON_IRATISP_INUSE_AttributeUpdateReject_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for variable-sized sequence c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01 */
void FREE_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01 (c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data[i]->AttributeRecord));
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents */
void FREE_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents (c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data01.data[i0]->AttributeRecord));
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01 */
void FREE_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01 (c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data[i]->AttributeRecord));
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents */
void FREE_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents (c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data01.data[i0]->AttributeRecord));
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01 */
void FREE_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01 (c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->Channel_Present) {
			EDFree (sp->data[i]->Channel);
			sp->data[i]->Channel = NULL;
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents */
void FREE_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents (c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->Channel_Present) {
			EDFree (sp->data01.data[i0]->Channel);
			sp->data01.data[i0]->Channel = NULL;
		}
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}
	if (sp->ReferencePilotChannel_Present) {
		EDFree (sp->ReferencePilotChannel);
		sp->ReferencePilotChannel = NULL;
		sp->ReferencePilotChannel_Present = ED_FALSE;
	}

}

void SETPRESENT_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel (c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->ReferencePilotChannel_Present == present) return;
	sp->ReferencePilotChannel_Present = present;
	if (present) {
		/*-->*/sp->ReferencePilotChannel = (c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel));
		ED_RESET_MEM (sp->ReferencePilotChannel, sizeof (c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel));
		(sp->ReferencePilotChannel->SystemType) = 0;
		(sp->ReferencePilotChannel->BandClass) = 0;
		(sp->ReferencePilotChannel->ChannelNumber) = 0;
	} else {
		EDFree (sp->ReferencePilotChannel);
		sp->ReferencePilotChannel = NULL;
	}
}

/* Free function for variable-sized sequence c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01 */
void FREE_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01 (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02 */
void FREE_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02 (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03 */
void FREE_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03 (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04 */
void FREE_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04 (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents */
void FREE_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	if (sp->Channel_Present) {
		EDFree (sp->Channel);
		sp->Channel = NULL;
		sp->Channel_Present = ED_FALSE;
	}
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data02.items; i0++) {
		EDFree (sp->data02.data[i0]);
		sp->data02.data[i0] = NULL;
	}
	if (sp->data02.data) {EDFree (sp->data02.data); sp->data02.data = NULL; sp->data02.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data03.items; i0++) {
		EDFree (sp->data03.data[i0]);
		sp->data03.data[i0] = NULL;
	}
	if (sp->data03.data) {EDFree (sp->data03.data); sp->data03.data = NULL; sp->data03.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data04.items; i0++) {
		EDFree (sp->data04.data[i0]);
		sp->data04.data[i0] = NULL;
	}
	if (sp->data04.data) {EDFree (sp->data04.data); sp->data04.data = NULL; sp->data04.allocatedItems=0; /*FR02A*/}

}

void SETPRESENT_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_Channel (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->Channel_Present == present) return;
	sp->Channel_Present = present;
	if (present) {
		/*-->*/sp->Channel = (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_Channel*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_Channel));
		ED_RESET_MEM (sp->Channel, sizeof (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_Channel));
		(sp->Channel->SystemType) = 0;
		(sp->Channel->BandClass) = 0;
		(sp->Channel->ChannelNumber) = 0;
	} else {
		EDFree (sp->Channel);
		sp->Channel = NULL;
	}
}

/* Free function for struct c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete_contents */
void FREE_c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete_contents (c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for variable-sized sequence c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01 */
void FREE_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01 (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02 */
void FREE_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02 (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->Channel_Present) {
			EDFree (sp->data[i]->Channel);
			sp->data[i]->Channel = NULL;
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03 */
void FREE_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03 (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->SearchWindowSize_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04 */
void FREE_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04 (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->SearchWindowOffset_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05 */
void FREE_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05 (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->FPDCHSupported_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATRUP_INUSE_NeighborList_contents */
void FREE_c_RPDCON_IRATRUP_INUSE_NeighborList_contents (c_RPDCON_IRATRUP_INUSE_NeighborList_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data02.items; i0++) {
		if (sp->data02.data[i0]->Channel_Present) {
			EDFree (sp->data02.data[i0]->Channel);
			sp->data02.data[i0]->Channel = NULL;
		}
		EDFree (sp->data02.data[i0]);
		sp->data02.data[i0] = NULL;
	}
	if (sp->data02.data) {EDFree (sp->data02.data); sp->data02.data = NULL; sp->data02.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data03.items; i0++) {
		if (sp->data03.data[i0]->SearchWindowSize_Present) {
		}
		EDFree (sp->data03.data[i0]);
		sp->data03.data[i0] = NULL;
	}
	if (sp->data03.data) {EDFree (sp->data03.data); sp->data03.data = NULL; sp->data03.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data04.items; i0++) {
		if (sp->data04.data[i0]->SearchWindowOffset_Present) {
		}
		EDFree (sp->data04.data[i0]);
		sp->data04.data[i0] = NULL;
	}
	if (sp->data04.data) {EDFree (sp->data04.data); sp->data04.data = NULL; sp->data04.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data05.items; i0++) {
		if (sp->data05.data[i0]->FPDCHSupported_Present) {
		}
		EDFree (sp->data05.data[i0]);
		sp->data05.data[i0] = NULL;
	}
	if (sp->data05.data) {EDFree (sp->data05.data); sp->data05.data = NULL; sp->data05.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01 */
void FREE_c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01 (c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data[i]->AttributeRecord));
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents */
void FREE_c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents (c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data01.data[i0]->AttributeRecord));
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for struct c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse_contents */
void FREE_c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse_contents (c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for variable-sized sequence c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01 */
void FREE_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01 (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02 */
void FREE_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02 (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->SectorSearchWindowSize_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03 */
void FREE_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03 (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->SectorSearchWindowOffset_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents */
void FREE_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	if (sp->Channel_Present) {
		EDFree (sp->Channel);
		sp->Channel = NULL;
		sp->Channel_Present = ED_FALSE;
	}
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data02.items; i0++) {
		if (sp->data02.data[i0]->SectorSearchWindowSize_Present) {
		}
		EDFree (sp->data02.data[i0]);
		sp->data02.data[i0] = NULL;
	}
	if (sp->data02.data) {EDFree (sp->data02.data); sp->data02.data = NULL; sp->data02.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data03.items; i0++) {
		if (sp->data03.data[i0]->SectorSearchWindowOffset_Present) {
		}
		EDFree (sp->data03.data[i0]);
		sp->data03.data[i0] = NULL;
	}
	if (sp->data03.data) {EDFree (sp->data03.data); sp->data03.data = NULL; sp->data03.allocatedItems=0; /*FR02A*/}

}

void SETPRESENT_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_Channel (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->Channel_Present == present) return;
	sp->Channel_Present = present;
	if (present) {
		/*-->*/sp->Channel = (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_Channel*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_Channel));
		ED_RESET_MEM (sp->Channel, sizeof (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_Channel));
		(sp->Channel->SystemType) = 0;
		(sp->Channel->BandClass) = 0;
		(sp->Channel->ChannelNumber) = 0;
	} else {
		EDFree (sp->Channel);
		sp->Channel = NULL;
	}
}

/* Free function for variable-sized sequence c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01 */
void FREE_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01 (c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data[i]->AttributeRecord));
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents */
void FREE_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents (c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data01.data[i0]->AttributeRecord));
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for struct c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept_contents */
void FREE_c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept_contents (c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject_contents */
void FREE_c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject_contents (c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for variable-sized sequence c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01 */
void FREE_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01 (c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data[i]->AttributeRecord));
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents */
void FREE_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents (c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data01.data[i0]->AttributeRecord));
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01 */
void FREE_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01 (c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data[i]->AttributeRecord));
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents */
void FREE_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents (c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data01.data[i0]->AttributeRecord));
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01 */
void FREE_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01 (c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02 */
void FREE_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02 (c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->ForwardTrafficValid127To64_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03 */
void FREE_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03 (c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->CompatibleReservedBits_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATOMP_INUSE_QuickConfig_contents */
void FREE_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents (c_RPDCON_IRATOMP_INUSE_QuickConfig_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data02.items; i0++) {
		if (sp->data02.data[i0]->ForwardTrafficValid127To64_Present) {
		}
		EDFree (sp->data02.data[i0]);
		sp->data02.data[i0] = NULL;
	}
	if (sp->data02.data) {EDFree (sp->data02.data); sp->data02.data = NULL; sp->data02.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data03.items; i0++) {
		if (sp->data03.data[i0]->CompatibleReservedBits_Present) {
		}
		EDFree (sp->data03.data[i0]);
		sp->data03.data[i0] = NULL;
	}
	if (sp->data03.data) {EDFree (sp->data03.data); sp->data03.data = NULL; sp->data03.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01 */
void FREE_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01 (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02 */
void FREE_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02 (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03 */
void FREE_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03 (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->NeighborChannel_Present) {
			EDFree (sp->data[i]->NeighborChannel);
			sp->data[i]->NeighborChannel = NULL;
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04 */
void FREE_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04 (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->NeighborSearchWindowSize_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05 */
void FREE_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05 (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->NeighborSearchWindowOffset_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06 */
void FREE_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06 (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07 */
void FREE_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07 (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->AccessHashingChannelMask.value != NULL) {
			EDFree (sp->data[i]->AccessHashingChannelMask.value);
			sp->data[i]->AccessHashingChannelMask.value = NULL;
		}
		sp->data[i]->AccessHashingChannelMask.usedBits = 0;
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08 */
void FREE_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08 (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->FPDCHSupported_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09 */
void FREE_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09 (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATOMP_INUSE_SectorParameters_contents */
void FREE_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data02.items; i0++) {
		EDFree (sp->data02.data[i0]);
		sp->data02.data[i0] = NULL;
	}
	if (sp->data02.data) {EDFree (sp->data02.data); sp->data02.data = NULL; sp->data02.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data03.items; i0++) {
		if (sp->data03.data[i0]->NeighborChannel_Present) {
			EDFree (sp->data03.data[i0]->NeighborChannel);
			sp->data03.data[i0]->NeighborChannel = NULL;
		}
		EDFree (sp->data03.data[i0]);
		sp->data03.data[i0] = NULL;
	}
	if (sp->data03.data) {EDFree (sp->data03.data); sp->data03.data = NULL; sp->data03.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data04.items; i0++) {
		if (sp->data04.data[i0]->NeighborSearchWindowSize_Present) {
		}
		EDFree (sp->data04.data[i0]);
		sp->data04.data[i0] = NULL;
	}
	if (sp->data04.data) {EDFree (sp->data04.data); sp->data04.data = NULL; sp->data04.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data05.items; i0++) {
		if (sp->data05.data[i0]->NeighborSearchWindowOffset_Present) {
		}
		EDFree (sp->data05.data[i0]);
		sp->data05.data[i0] = NULL;
	}
	if (sp->data05.data) {EDFree (sp->data05.data); sp->data05.data = NULL; sp->data05.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data06.items; i0++) {
		EDFree (sp->data06.data[i0]);
		sp->data06.data[i0] = NULL;
	}
	if (sp->data06.data) {EDFree (sp->data06.data); sp->data06.data = NULL; sp->data06.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data07.items; i0++) {
		if (sp->data07.data[i0]->AccessHashingChannelMask.value != NULL) {
			EDFree (sp->data07.data[i0]->AccessHashingChannelMask.value);
			sp->data07.data[i0]->AccessHashingChannelMask.value = NULL;
		}
		sp->data07.data[i0]->AccessHashingChannelMask.usedBits = 0;
		EDFree (sp->data07.data[i0]);
		sp->data07.data[i0] = NULL;
	}
	if (sp->data07.data) {EDFree (sp->data07.data); sp->data07.data = NULL; sp->data07.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data08.items; i0++) {
		if (sp->data08.data[i0]->FPDCHSupported_Present) {
		}
		EDFree (sp->data08.data[i0]);
		sp->data08.data[i0] = NULL;
	}
	if (sp->data08.data) {EDFree (sp->data08.data); sp->data08.data = NULL; sp->data08.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data09.items; i0++) {
		EDFree (sp->data09.data[i0]);
		sp->data09.data[i0] = NULL;
	}
	if (sp->data09.data) {EDFree (sp->data09.data); sp->data09.data = NULL; sp->data09.allocatedItems=0; /*FR02A*/}

}

/* Free function for struct c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters_contents */
void FREE_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters_contents (c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for variable-sized sequence c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID */
void FREE_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02 */
void FREE_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02 (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->EARFCNPriority_Present) {
		}
		if (sp->data[i]->RxLevMinEUTRA_Present) {
		}
		if (sp->data[i]->PEMax_Present) {
		}
		if (sp->data[i]->RxLevMinEUTRAOffsetIncl_Present) {
		}
		if (sp->data[i]->RxLevMinEUTRAOffset_Present) {
		}
		if (sp->data[i]->PLMNSameAsPreviousChannel_Present) {
		}
		if (sp->data[i]->NumPLMNIDs_Present) {
		}
		if (sp->data[i]->PLMNID.data) {EDFree (sp->data[i]->PLMNID.data); sp->data[i]->PLMNID.data = NULL; sp->data[i]->PLMNID.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID */
void FREE_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05 */
void FREE_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05 (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->ThreshXQ_Present) {
		}
		if (sp->data[i]->QualMinEUTRA_Present) {
		}
		if (sp->data[i]->QualMinEUTRAOffsetIncl_Present) {
		}
		if (sp->data[i]->QualMinEUTRAOffset_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01 */
void FREE_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01 (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01* sp) {
	int i, i0;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->OtherNeighborRATRecord_Present) {
			if (sp->data[i]->OtherNeighborRATRecord->value != NULL) {
				EDFree (sp->data[i]->OtherNeighborRATRecord->value);
				sp->data[i]->OtherNeighborRATRecord->value = NULL;
			}
			sp->data[i]->OtherNeighborRATRecord->usedBits = 0;
			EDFree (sp->data[i]->OtherNeighborRATRecord);
		}
		if (sp->data[i]->NeighborRATRecord_Present) {
			if (sp->data[i]->NeighborRATRecord->ServingPriority_Present) {
			}
			if (sp->data[i]->NeighborRATRecord->RxLevMinEUTRACommon_Present) {
			}
			if (sp->data[i]->NeighborRATRecord->PEMaxCommon_Present) {
			}
			if (sp->data[i]->NeighborRATRecord->RxLevMinEUTRAOffsetCommonIncl_Present) {
			}
			if (sp->data[i]->NeighborRATRecord->RxLevMinEUTRAOffsetCommon_Present) {
			}
			if (sp->data[i]->NeighborRATRecord->MaxReselectionTimer_Present) {
			}
			if (sp->data[i]->NeighborRATRecord->MinMeasurementBackoff_Present) {
			}
			if (sp->data[i]->NeighborRATRecord->MaxMeasurementBackoff_Present) {
			}
			for (i0=0; i0<sp->data[i]->NeighborRATRecord->data02.items; i0++) {
				if (sp->data[i]->NeighborRATRecord->data02.data[i0]->EARFCNPriority_Present) {
				}
				if (sp->data[i]->NeighborRATRecord->data02.data[i0]->RxLevMinEUTRA_Present) {
				}
				if (sp->data[i]->NeighborRATRecord->data02.data[i0]->PEMax_Present) {
				}
				if (sp->data[i]->NeighborRATRecord->data02.data[i0]->RxLevMinEUTRAOffsetIncl_Present) {
				}
				if (sp->data[i]->NeighborRATRecord->data02.data[i0]->RxLevMinEUTRAOffset_Present) {
				}
				if (sp->data[i]->NeighborRATRecord->data02.data[i0]->PLMNSameAsPreviousChannel_Present) {
				}
				if (sp->data[i]->NeighborRATRecord->data02.data[i0]->NumPLMNIDs_Present) {
				}
				if (sp->data[i]->NeighborRATRecord->data02.data[i0]->PLMNID.data) {EDFree (sp->data[i]->NeighborRATRecord->data02.data[i0]->PLMNID.data); sp->data[i]->NeighborRATRecord->data02.data[i0]->PLMNID.data = NULL; sp->data[i]->NeighborRATRecord->data02.data[i0]->PLMNID.allocatedItems=0; /*FR02A*/}
				EDFree (sp->data[i]->NeighborRATRecord->data02.data[i0]);
				sp->data[i]->NeighborRATRecord->data02.data[i0] = NULL;
			}
			if (sp->data[i]->NeighborRATRecord->data02.data) {EDFree (sp->data[i]->NeighborRATRecord->data02.data); sp->data[i]->NeighborRATRecord->data02.data = NULL; sp->data[i]->NeighborRATRecord->data02.allocatedItems=0; /*FR02A*/}
			if (sp->data[i]->NeighborRATRecord->ServingNetworkPLMNIncl_Present) {
			}
			if (sp->data[i]->NeighborRATRecord->NumServingPLMNIDs_Present) {
			}
			if (sp->data[i]->NeighborRATRecord->S_PLMNID.data) {EDFree (sp->data[i]->NeighborRATRecord->S_PLMNID.data); sp->data[i]->NeighborRATRecord->S_PLMNID.data = NULL; sp->data[i]->NeighborRATRecord->S_PLMNID.allocatedItems=0; /*FR02A*/}
			if (sp->data[i]->NeighborRATRecord->RSRQParametersIncluded_Present) {
			}
			if (sp->data[i]->NeighborRATRecord->QualMinEUTRACommon_Present) {
			}
			if (sp->data[i]->NeighborRATRecord->QualMinEUTRAOffsetCommonInc_Present) {
			}
			if (sp->data[i]->NeighborRATRecord->QualMinEUTRAOffsetCommon_Present) {
			}
			for (i0=0; i0<sp->data[i]->NeighborRATRecord->data05.items; i0++) {
				if (sp->data[i]->NeighborRATRecord->data05.data[i0]->ThreshXQ_Present) {
				}
				if (sp->data[i]->NeighborRATRecord->data05.data[i0]->QualMinEUTRA_Present) {
				}
				if (sp->data[i]->NeighborRATRecord->data05.data[i0]->QualMinEUTRAOffsetIncl_Present) {
				}
				if (sp->data[i]->NeighborRATRecord->data05.data[i0]->QualMinEUTRAOffset_Present) {
				}
				EDFree (sp->data[i]->NeighborRATRecord->data05.data[i0]);
				sp->data[i]->NeighborRATRecord->data05.data[i0] = NULL;
			}
			if (sp->data[i]->NeighborRATRecord->data05.data) {EDFree (sp->data[i]->NeighborRATRecord->data05.data); sp->data[i]->NeighborRATRecord->data05.data = NULL; sp->data[i]->NeighborRATRecord->data05.allocatedItems=0; /*FR02A*/}
			EDFree (sp->data[i]->NeighborRATRecord);
			sp->data[i]->NeighborRATRecord = NULL;
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents */
void FREE_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents* sp) {
	int i0;
	int i1;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->OtherNeighborRATRecord_Present) {
			if (sp->data01.data[i0]->OtherNeighborRATRecord->value != NULL) {
				EDFree (sp->data01.data[i0]->OtherNeighborRATRecord->value);
				sp->data01.data[i0]->OtherNeighborRATRecord->value = NULL;
			}
			sp->data01.data[i0]->OtherNeighborRATRecord->usedBits = 0;
			EDFree (sp->data01.data[i0]->OtherNeighborRATRecord);
		}
		if (sp->data01.data[i0]->NeighborRATRecord_Present) {
			if (sp->data01.data[i0]->NeighborRATRecord->ServingPriority_Present) {
			}
			if (sp->data01.data[i0]->NeighborRATRecord->RxLevMinEUTRACommon_Present) {
			}
			if (sp->data01.data[i0]->NeighborRATRecord->PEMaxCommon_Present) {
			}
			if (sp->data01.data[i0]->NeighborRATRecord->RxLevMinEUTRAOffsetCommonIncl_Present) {
			}
			if (sp->data01.data[i0]->NeighborRATRecord->RxLevMinEUTRAOffsetCommon_Present) {
			}
			if (sp->data01.data[i0]->NeighborRATRecord->MaxReselectionTimer_Present) {
			}
			if (sp->data01.data[i0]->NeighborRATRecord->MinMeasurementBackoff_Present) {
			}
			if (sp->data01.data[i0]->NeighborRATRecord->MaxMeasurementBackoff_Present) {
			}
			for (i1=0; i1<sp->data01.data[i0]->NeighborRATRecord->data02.items; i1++) {
				if (sp->data01.data[i0]->NeighborRATRecord->data02.data[i1]->EARFCNPriority_Present) {
				}
				if (sp->data01.data[i0]->NeighborRATRecord->data02.data[i1]->RxLevMinEUTRA_Present) {
				}
				if (sp->data01.data[i0]->NeighborRATRecord->data02.data[i1]->PEMax_Present) {
				}
				if (sp->data01.data[i0]->NeighborRATRecord->data02.data[i1]->RxLevMinEUTRAOffsetIncl_Present) {
				}
				if (sp->data01.data[i0]->NeighborRATRecord->data02.data[i1]->RxLevMinEUTRAOffset_Present) {
				}
				if (sp->data01.data[i0]->NeighborRATRecord->data02.data[i1]->PLMNSameAsPreviousChannel_Present) {
				}
				if (sp->data01.data[i0]->NeighborRATRecord->data02.data[i1]->NumPLMNIDs_Present) {
				}
				if (sp->data01.data[i0]->NeighborRATRecord->data02.data[i1]->PLMNID.data) {EDFree (sp->data01.data[i0]->NeighborRATRecord->data02.data[i1]->PLMNID.data); sp->data01.data[i0]->NeighborRATRecord->data02.data[i1]->PLMNID.data = NULL; sp->data01.data[i0]->NeighborRATRecord->data02.data[i1]->PLMNID.allocatedItems=0; /*FR02A*/}
				EDFree (sp->data01.data[i0]->NeighborRATRecord->data02.data[i1]);
				sp->data01.data[i0]->NeighborRATRecord->data02.data[i1] = NULL;
			}
			if (sp->data01.data[i0]->NeighborRATRecord->data02.data) {EDFree (sp->data01.data[i0]->NeighborRATRecord->data02.data); sp->data01.data[i0]->NeighborRATRecord->data02.data = NULL; sp->data01.data[i0]->NeighborRATRecord->data02.allocatedItems=0; /*FR02A*/}
			if (sp->data01.data[i0]->NeighborRATRecord->ServingNetworkPLMNIncl_Present) {
			}
			if (sp->data01.data[i0]->NeighborRATRecord->NumServingPLMNIDs_Present) {
			}
			if (sp->data01.data[i0]->NeighborRATRecord->S_PLMNID.data) {EDFree (sp->data01.data[i0]->NeighborRATRecord->S_PLMNID.data); sp->data01.data[i0]->NeighborRATRecord->S_PLMNID.data = NULL; sp->data01.data[i0]->NeighborRATRecord->S_PLMNID.allocatedItems=0; /*FR02A*/}
			if (sp->data01.data[i0]->NeighborRATRecord->RSRQParametersIncluded_Present) {
			}
			if (sp->data01.data[i0]->NeighborRATRecord->QualMinEUTRACommon_Present) {
			}
			if (sp->data01.data[i0]->NeighborRATRecord->QualMinEUTRAOffsetCommonInc_Present) {
			}
			if (sp->data01.data[i0]->NeighborRATRecord->QualMinEUTRAOffsetCommon_Present) {
			}
			for (i1=0; i1<sp->data01.data[i0]->NeighborRATRecord->data05.items; i1++) {
				if (sp->data01.data[i0]->NeighborRATRecord->data05.data[i1]->ThreshXQ_Present) {
				}
				if (sp->data01.data[i0]->NeighborRATRecord->data05.data[i1]->QualMinEUTRA_Present) {
				}
				if (sp->data01.data[i0]->NeighborRATRecord->data05.data[i1]->QualMinEUTRAOffsetIncl_Present) {
				}
				if (sp->data01.data[i0]->NeighborRATRecord->data05.data[i1]->QualMinEUTRAOffset_Present) {
				}
				EDFree (sp->data01.data[i0]->NeighborRATRecord->data05.data[i1]);
				sp->data01.data[i0]->NeighborRATRecord->data05.data[i1] = NULL;
			}
			if (sp->data01.data[i0]->NeighborRATRecord->data05.data) {EDFree (sp->data01.data[i0]->NeighborRATRecord->data05.data); sp->data01.data[i0]->NeighborRATRecord->data05.data = NULL; sp->data01.data[i0]->NeighborRATRecord->data05.allocatedItems=0; /*FR02A*/}
			EDFree (sp->data01.data[i0]->NeighborRATRecord);
			sp->data01.data[i0]->NeighborRATRecord = NULL;
		}
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01 */
void FREE_c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01 (c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data[i]->AttributeRecord));
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents */
void FREE_c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents (c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data01.data[i0]->AttributeRecord));
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01 */
void FREE_c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01 (c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data[i]->AttributeRecord));
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents */
void FREE_c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents (c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data01.data[i0]->AttributeRecord));
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01 */
void FREE_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01 (c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data[i]->AttributeRecord));
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents */
void FREE_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents (c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data01.data[i0]->AttributeRecord));
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01 */
void FREE_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01 (c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data[i]->AttributeRecord));
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents */
void FREE_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents (c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data01.data[i0]->AttributeRecord));
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for struct c_RPDCON_IRATQISP_INUSE_Page_contents */
void FREE_c_RPDCON_IRATQISP_INUSE_Page_contents (c_RPDCON_IRATQISP_INUSE_Page_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for variable-sized sequence c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01 */
void FREE_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01 (c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents */
void FREE_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents (c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for struct c_RPDCON_IRATQISP_INUSE_ConnectionDeny_contents */
void FREE_c_RPDCON_IRATQISP_INUSE_ConnectionDeny_contents (c_RPDCON_IRATQISP_INUSE_ConnectionDeny_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for variable-sized sequence c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01 */
void FREE_c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01 (c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATQISP_INUSE_QuickPage_contents */
void FREE_c_RPDCON_IRATQISP_INUSE_QuickPage_contents (c_RPDCON_IRATQISP_INUSE_QuickPage_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01 */
void FREE_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01 (c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data[i]->AttributeRecord));
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents */
void FREE_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents (c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data01.data[i0]->AttributeRecord));
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for struct c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept_contents */
void FREE_c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept_contents (c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject_contents */
void FREE_c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject_contents (c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for variable-sized sequence c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01 */
void FREE_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01 (c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data[i]->AttributeRecord));
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents */
void FREE_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents (c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data01.data[i0]->AttributeRecord));
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01 */
void FREE_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01 (c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data[i]->AttributeRecord));
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents */
void FREE_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents (c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data01.data[i0]->AttributeRecord));
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01 */
void FREE_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01 (c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->Channel_Present) {
			EDFree (sp->data[i]->Channel);
			sp->data[i]->Channel = NULL;
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents */
void FREE_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents (c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->Channel_Present) {
			EDFree (sp->data01.data[i0]->Channel);
			sp->data01.data[i0]->Channel = NULL;
		}
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}
	if (sp->ReferencePilotChannel_Present) {
		EDFree (sp->ReferencePilotChannel);
		sp->ReferencePilotChannel = NULL;
		sp->ReferencePilotChannel_Present = ED_FALSE;
	}

}

void SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel (c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->ReferencePilotChannel_Present == present) return;
	sp->ReferencePilotChannel_Present = present;
	if (present) {
		/*-->*/sp->ReferencePilotChannel = (c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel));
		ED_RESET_MEM (sp->ReferencePilotChannel, sizeof (c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel));
		(sp->ReferencePilotChannel->SystemType) = 0;
		(sp->ReferencePilotChannel->BandClass) = 0;
		(sp->ReferencePilotChannel->ChannelNumber) = 0;
	} else {
		EDFree (sp->ReferencePilotChannel);
		sp->ReferencePilotChannel = NULL;
	}
}

/* Free function for variable-sized sequence c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01 */
void FREE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01 (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02 */
void FREE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02 (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04 */
void FREE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04 (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->AssignedChannel_Present) {
			EDFree (sp->data[i]->AssignedChannel);
			sp->data[i]->AssignedChannel = NULL;
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05 */
void FREE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05 (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->ReverseBandClass_Present) {
		}
		if (sp->data[i]->ReverseChannelNumber_Present) {
		}
		if (sp->data[i]->ReverseChannelDroppingRank_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07 */
void FREE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07 (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->AssignedInterlaces_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08 */
void FREE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08 (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->ReverseLinkMACIndex_Present) {
		}
		if (sp->data[i]->RABMACIndex_Present) {
		}
		if (sp->data[i]->DeltaT2P_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06 */
void FREE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06 (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06* sp) {
	int i, i0;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->ForwardChannelIndexThisPilot_Present) {
		}
		if (sp->data[i]->PilotGroupID_Present) {
		}
		if (sp->data[i]->NumUniqueForwardTrafficMACIndices_Present) {
		}
		if (sp->data[i]->SchedulerTag_Present) {
		}
		if (sp->data[i]->AuxDRCCoverIncluded_Present) {
		}
		if (sp->data[i]->AuxDRCCover_Present) {
		}
		if (sp->data[i]->ForwardTrafficMACIndexPerInterlaceEnabled_Present) {
		}
		for (i0=0; i0<sp->data[i]->data07.items; i0++) {
			if (sp->data[i]->data07.data[i0]->AssignedInterlaces_Present) {
			}
			EDFree (sp->data[i]->data07.data[i0]);
			sp->data[i]->data07.data[i0] = NULL;
		}
		if (sp->data[i]->data07.data) {EDFree (sp->data[i]->data07.data); sp->data[i]->data07.data = NULL; sp->data[i]->data07.allocatedItems=0; /*FR02A*/}
		for (i0=0; i0<sp->data[i]->data08.items; i0++) {
			if (sp->data[i]->data08.data[i0]->ReverseLinkMACIndex_Present) {
			}
			if (sp->data[i]->data08.data[i0]->RABMACIndex_Present) {
			}
			if (sp->data[i]->data08.data[i0]->DeltaT2P_Present) {
			}
			EDFree (sp->data[i]->data08.data[i0]);
			sp->data[i]->data08.data[i0] = NULL;
		}
		if (sp->data[i]->data08.data) {EDFree (sp->data[i]->data08.data); sp->data[i]->data08.data = NULL; sp->data[i]->data08.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03 */
void FREE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03 (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03* sp) {
	int i, i0, i1;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->NumFwdChannelsThisSubActiveSet_Present) {
		}
		for (i0=0; i0<sp->data[i]->data04.items; i0++) {
			if (sp->data[i]->data04.data[i0]->AssignedChannel_Present) {
				EDFree (sp->data[i]->data04.data[i0]->AssignedChannel);
				sp->data[i]->data04.data[i0]->AssignedChannel = NULL;
			}
			EDFree (sp->data[i]->data04.data[i0]);
			sp->data[i]->data04.data[i0] = NULL;
		}
		if (sp->data[i]->data04.data) {EDFree (sp->data[i]->data04.data); sp->data[i]->data04.data = NULL; sp->data[i]->data04.allocatedItems=0; /*FR02A*/}
		if (sp->data[i]->FeedbackMultiplexingIndex_Present) {
		}
		if (sp->data[i]->FeedbackReverseChannelIndex_Present) {
		}
		if (sp->data[i]->DSCForThisSubActiveSetEnabled_Present) {
		}
		if (sp->data[i]->Next3FieldsSameAsBefore_Present) {
		}
		if (sp->data[i]->DRCLength_Present) {
		}
		if (sp->data[i]->DRCChannelGainBase_Present) {
		}
		if (sp->data[i]->ACKChannelGain_Present) {
		}
		if (sp->data[i]->NumReverseChannels_Present) {
		}
		for (i0=0; i0<sp->data[i]->data05.items; i0++) {
			if (sp->data[i]->data05.data[i0]->ReverseBandClass_Present) {
			}
			if (sp->data[i]->data05.data[i0]->ReverseChannelNumber_Present) {
			}
			if (sp->data[i]->data05.data[i0]->ReverseChannelDroppingRank_Present) {
			}
			EDFree (sp->data[i]->data05.data[i0]);
			sp->data[i]->data05.data[i0] = NULL;
		}
		if (sp->data[i]->data05.data) {EDFree (sp->data[i]->data05.data); sp->data[i]->data05.data = NULL; sp->data[i]->data05.allocatedItems=0; /*FR02A*/}
		for (i0=0; i0<sp->data[i]->data06.items; i0++) {
			if (sp->data[i]->data06.data[i0]->ForwardChannelIndexThisPilot_Present) {
			}
			if (sp->data[i]->data06.data[i0]->PilotGroupID_Present) {
			}
			if (sp->data[i]->data06.data[i0]->NumUniqueForwardTrafficMACIndices_Present) {
			}
			if (sp->data[i]->data06.data[i0]->SchedulerTag_Present) {
			}
			if (sp->data[i]->data06.data[i0]->AuxDRCCoverIncluded_Present) {
			}
			if (sp->data[i]->data06.data[i0]->AuxDRCCover_Present) {
			}
			if (sp->data[i]->data06.data[i0]->ForwardTrafficMACIndexPerInterlaceEnabled_Present) {
			}
			for (i1=0; i1<sp->data[i]->data06.data[i0]->data07.items; i1++) {
				if (sp->data[i]->data06.data[i0]->data07.data[i1]->AssignedInterlaces_Present) {
				}
				EDFree (sp->data[i]->data06.data[i0]->data07.data[i1]);
				sp->data[i]->data06.data[i0]->data07.data[i1] = NULL;
			}
			if (sp->data[i]->data06.data[i0]->data07.data) {EDFree (sp->data[i]->data06.data[i0]->data07.data); sp->data[i]->data06.data[i0]->data07.data = NULL; sp->data[i]->data06.data[i0]->data07.allocatedItems=0; /*FR02A*/}
			for (i1=0; i1<sp->data[i]->data06.data[i0]->data08.items; i1++) {
				if (sp->data[i]->data06.data[i0]->data08.data[i1]->ReverseLinkMACIndex_Present) {
				}
				if (sp->data[i]->data06.data[i0]->data08.data[i1]->RABMACIndex_Present) {
				}
				if (sp->data[i]->data06.data[i0]->data08.data[i1]->DeltaT2P_Present) {
				}
				EDFree (sp->data[i]->data06.data[i0]->data08.data[i1]);
				sp->data[i]->data06.data[i0]->data08.data[i1] = NULL;
			}
			if (sp->data[i]->data06.data[i0]->data08.data) {EDFree (sp->data[i]->data06.data[i0]->data08.data); sp->data[i]->data06.data[i0]->data08.data = NULL; sp->data[i]->data06.data[i0]->data08.allocatedItems=0; /*FR02A*/}
			EDFree (sp->data[i]->data06.data[i0]);
			sp->data[i]->data06.data[i0] = NULL;
		}
		if (sp->data[i]->data06.data) {EDFree (sp->data[i]->data06.data); sp->data[i]->data06.data = NULL; sp->data[i]->data06.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents */
void FREE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents* sp) {
	int i0;
	int i1;
	int i2;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data02.items; i0++) {
		EDFree (sp->data02.data[i0]);
		sp->data02.data[i0] = NULL;
	}
	if (sp->data02.data) {EDFree (sp->data02.data); sp->data02.data = NULL; sp->data02.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data03.items; i0++) {
		if (sp->data03.data[i0]->NumFwdChannelsThisSubActiveSet_Present) {
		}
		for (i1=0; i1<sp->data03.data[i0]->data04.items; i1++) {
			if (sp->data03.data[i0]->data04.data[i1]->AssignedChannel_Present) {
				EDFree (sp->data03.data[i0]->data04.data[i1]->AssignedChannel);
				sp->data03.data[i0]->data04.data[i1]->AssignedChannel = NULL;
			}
			EDFree (sp->data03.data[i0]->data04.data[i1]);
			sp->data03.data[i0]->data04.data[i1] = NULL;
		}
		if (sp->data03.data[i0]->data04.data) {EDFree (sp->data03.data[i0]->data04.data); sp->data03.data[i0]->data04.data = NULL; sp->data03.data[i0]->data04.allocatedItems=0; /*FR02A*/}
		if (sp->data03.data[i0]->FeedbackMultiplexingIndex_Present) {
		}
		if (sp->data03.data[i0]->FeedbackReverseChannelIndex_Present) {
		}
		if (sp->data03.data[i0]->DSCForThisSubActiveSetEnabled_Present) {
		}
		if (sp->data03.data[i0]->Next3FieldsSameAsBefore_Present) {
		}
		if (sp->data03.data[i0]->DRCLength_Present) {
		}
		if (sp->data03.data[i0]->DRCChannelGainBase_Present) {
		}
		if (sp->data03.data[i0]->ACKChannelGain_Present) {
		}
		if (sp->data03.data[i0]->NumReverseChannels_Present) {
		}
		for (i1=0; i1<sp->data03.data[i0]->data05.items; i1++) {
			if (sp->data03.data[i0]->data05.data[i1]->ReverseBandClass_Present) {
			}
			if (sp->data03.data[i0]->data05.data[i1]->ReverseChannelNumber_Present) {
			}
			if (sp->data03.data[i0]->data05.data[i1]->ReverseChannelDroppingRank_Present) {
			}
			EDFree (sp->data03.data[i0]->data05.data[i1]);
			sp->data03.data[i0]->data05.data[i1] = NULL;
		}
		if (sp->data03.data[i0]->data05.data) {EDFree (sp->data03.data[i0]->data05.data); sp->data03.data[i0]->data05.data = NULL; sp->data03.data[i0]->data05.allocatedItems=0; /*FR02A*/}
		for (i1=0; i1<sp->data03.data[i0]->data06.items; i1++) {
			if (sp->data03.data[i0]->data06.data[i1]->ForwardChannelIndexThisPilot_Present) {
			}
			if (sp->data03.data[i0]->data06.data[i1]->PilotGroupID_Present) {
			}
			if (sp->data03.data[i0]->data06.data[i1]->NumUniqueForwardTrafficMACIndices_Present) {
			}
			if (sp->data03.data[i0]->data06.data[i1]->SchedulerTag_Present) {
			}
			if (sp->data03.data[i0]->data06.data[i1]->AuxDRCCoverIncluded_Present) {
			}
			if (sp->data03.data[i0]->data06.data[i1]->AuxDRCCover_Present) {
			}
			if (sp->data03.data[i0]->data06.data[i1]->ForwardTrafficMACIndexPerInterlaceEnabled_Present) {
			}
			for (i2=0; i2<sp->data03.data[i0]->data06.data[i1]->data07.items; i2++) {
				if (sp->data03.data[i0]->data06.data[i1]->data07.data[i2]->AssignedInterlaces_Present) {
				}
				EDFree (sp->data03.data[i0]->data06.data[i1]->data07.data[i2]);
				sp->data03.data[i0]->data06.data[i1]->data07.data[i2] = NULL;
			}
			if (sp->data03.data[i0]->data06.data[i1]->data07.data) {EDFree (sp->data03.data[i0]->data06.data[i1]->data07.data); sp->data03.data[i0]->data06.data[i1]->data07.data = NULL; sp->data03.data[i0]->data06.data[i1]->data07.allocatedItems=0; /*FR02A*/}
			for (i2=0; i2<sp->data03.data[i0]->data06.data[i1]->data08.items; i2++) {
				if (sp->data03.data[i0]->data06.data[i1]->data08.data[i2]->ReverseLinkMACIndex_Present) {
				}
				if (sp->data03.data[i0]->data06.data[i1]->data08.data[i2]->RABMACIndex_Present) {
				}
				if (sp->data03.data[i0]->data06.data[i1]->data08.data[i2]->DeltaT2P_Present) {
				}
				EDFree (sp->data03.data[i0]->data06.data[i1]->data08.data[i2]);
				sp->data03.data[i0]->data06.data[i1]->data08.data[i2] = NULL;
			}
			if (sp->data03.data[i0]->data06.data[i1]->data08.data) {EDFree (sp->data03.data[i0]->data06.data[i1]->data08.data); sp->data03.data[i0]->data06.data[i1]->data08.data = NULL; sp->data03.data[i0]->data06.data[i1]->data08.allocatedItems=0; /*FR02A*/}
			EDFree (sp->data03.data[i0]->data06.data[i1]);
			sp->data03.data[i0]->data06.data[i1] = NULL;
		}
		if (sp->data03.data[i0]->data06.data) {EDFree (sp->data03.data[i0]->data06.data); sp->data03.data[i0]->data06.data = NULL; sp->data03.data[i0]->data06.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data03.data[i0]);
		sp->data03.data[i0] = NULL;
	}
	if (sp->data03.data) {EDFree (sp->data03.data); sp->data03.data = NULL; sp->data03.allocatedItems=0; /*FR02A*/}

}

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete_contents */
void FREE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete_contents (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for variable-sized sequence c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01 */
void FREE_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01 (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02 */
void FREE_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02 (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->Channel_Present) {
			EDFree (sp->data[i]->Channel);
			sp->data[i]->Channel = NULL;
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03 */
void FREE_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03 (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->SearchWindowSize_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04 */
void FREE_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04 (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->SearchWindowOffset_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05 */
void FREE_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05 (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->FPDCHSupported_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06 */
void FREE_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06 (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->PilotGroupID_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents */
void FREE_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data02.items; i0++) {
		if (sp->data02.data[i0]->Channel_Present) {
			EDFree (sp->data02.data[i0]->Channel);
			sp->data02.data[i0]->Channel = NULL;
		}
		EDFree (sp->data02.data[i0]);
		sp->data02.data[i0] = NULL;
	}
	if (sp->data02.data) {EDFree (sp->data02.data); sp->data02.data = NULL; sp->data02.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data03.items; i0++) {
		if (sp->data03.data[i0]->SearchWindowSize_Present) {
		}
		EDFree (sp->data03.data[i0]);
		sp->data03.data[i0] = NULL;
	}
	if (sp->data03.data) {EDFree (sp->data03.data); sp->data03.data = NULL; sp->data03.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data04.items; i0++) {
		if (sp->data04.data[i0]->SearchWindowOffset_Present) {
		}
		EDFree (sp->data04.data[i0]);
		sp->data04.data[i0] = NULL;
	}
	if (sp->data04.data) {EDFree (sp->data04.data); sp->data04.data = NULL; sp->data04.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data05.items; i0++) {
		if (sp->data05.data[i0]->FPDCHSupported_Present) {
		}
		EDFree (sp->data05.data[i0]);
		sp->data05.data[i0] = NULL;
	}
	if (sp->data05.data) {EDFree (sp->data05.data); sp->data05.data = NULL; sp->data05.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data06.items; i0++) {
		if (sp->data06.data[i0]->PilotGroupID_Present) {
		}
		EDFree (sp->data06.data[i0]);
		sp->data06.data[i0] = NULL;
	}
	if (sp->data06.data) {EDFree (sp->data06.data); sp->data06.data = NULL; sp->data06.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01 */
void FREE_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01 (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02 */
void FREE_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02 (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->SectorSearchWindowSize_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03 */
void FREE_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03 (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->SectorSearchWindowOffset_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents */
void FREE_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	if (sp->Channel_Present) {
		EDFree (sp->Channel);
		sp->Channel = NULL;
		sp->Channel_Present = ED_FALSE;
	}
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data02.items; i0++) {
		if (sp->data02.data[i0]->SectorSearchWindowSize_Present) {
		}
		EDFree (sp->data02.data[i0]);
		sp->data02.data[i0] = NULL;
	}
	if (sp->data02.data) {EDFree (sp->data02.data); sp->data02.data = NULL; sp->data02.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data03.items; i0++) {
		if (sp->data03.data[i0]->SectorSearchWindowOffset_Present) {
		}
		EDFree (sp->data03.data[i0]);
		sp->data03.data[i0] = NULL;
	}
	if (sp->data03.data) {EDFree (sp->data03.data); sp->data03.data = NULL; sp->data03.allocatedItems=0; /*FR02A*/}

}

void SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_Channel (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->Channel_Present == present) return;
	sp->Channel_Present = present;
	if (present) {
		/*-->*/sp->Channel = (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_Channel*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_Channel));
		ED_RESET_MEM (sp->Channel, sizeof (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_Channel));
		(sp->Channel->SystemType) = 0;
		(sp->Channel->BandClass) = 0;
		(sp->Channel->ChannelNumber) = 0;
	} else {
		EDFree (sp->Channel);
		sp->Channel = NULL;
	}
}

/* Free function for variable-sized sequence c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01 */
void FREE_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01 (c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data[i]->AttributeRecord));
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents */
void FREE_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents (c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data01.data[i0]->AttributeRecord));
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept_contents */
void FREE_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept_contents (c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject_contents */
void FREE_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject_contents (c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for variable-sized sequence c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01 */
void FREE_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01 (c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data[i]->AttributeRecord));
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents */
void FREE_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents (c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data01.data[i0]->AttributeRecord));
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01 */
void FREE_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01 (c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data[i]->AttributeRecord));
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents */
void FREE_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents (c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->data01.data[i0]->AttributeRecord));
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01 */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01 (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02 */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02 (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->ForwardTrafficValid127To64_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03 */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03 (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->ForwardTrafficValid130To383_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data02.items; i0++) {
		if (sp->data02.data[i0]->ForwardTrafficValid127To64_Present) {
		}
		EDFree (sp->data02.data[i0]);
		sp->data02.data[i0] = NULL;
	}
	if (sp->data02.data) {EDFree (sp->data02.data); sp->data02.data = NULL; sp->data02.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data03.items; i0++) {
		if (sp->data03.data[i0]->ForwardTrafficValid130To383_Present) {
		}
		EDFree (sp->data03.data[i0]);
		sp->data03.data[i0] = NULL;
	}
	if (sp->data03.data) {EDFree (sp->data03.data); sp->data03.data = NULL; sp->data03.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01 */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02 */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03 */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->NeighborChannel_Present) {
			EDFree (sp->data[i]->NeighborChannel);
			sp->data[i]->NeighborChannel = NULL;
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04 */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05 */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->NeighborSearchWindowOffset_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06 */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07 */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->AccessHashingChannelMask_Present) {
			if (sp->data[i]->AccessHashingChannelMask->value != NULL) {
				EDFree (sp->data[i]->AccessHashingChannelMask->value);
				sp->data[i]->AccessHashingChannelMask->value = NULL;
			}
			sp->data[i]->AccessHashingChannelMask->usedBits = 0;
			EDFree (sp->data[i]->AccessHashingChannelMask);
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08 */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->FPDCHSupported_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09 */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10 */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->PilotGroupID_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11 */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data02.items; i0++) {
		EDFree (sp->data02.data[i0]);
		sp->data02.data[i0] = NULL;
	}
	if (sp->data02.data) {EDFree (sp->data02.data); sp->data02.data = NULL; sp->data02.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data03.items; i0++) {
		if (sp->data03.data[i0]->NeighborChannel_Present) {
			EDFree (sp->data03.data[i0]->NeighborChannel);
			sp->data03.data[i0]->NeighborChannel = NULL;
		}
		EDFree (sp->data03.data[i0]);
		sp->data03.data[i0] = NULL;
	}
	if (sp->data03.data) {EDFree (sp->data03.data); sp->data03.data = NULL; sp->data03.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data04.items; i0++) {
		EDFree (sp->data04.data[i0]);
		sp->data04.data[i0] = NULL;
	}
	if (sp->data04.data) {EDFree (sp->data04.data); sp->data04.data = NULL; sp->data04.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data05.items; i0++) {
		if (sp->data05.data[i0]->NeighborSearchWindowOffset_Present) {
		}
		EDFree (sp->data05.data[i0]);
		sp->data05.data[i0] = NULL;
	}
	if (sp->data05.data) {EDFree (sp->data05.data); sp->data05.data = NULL; sp->data05.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data06.items; i0++) {
		EDFree (sp->data06.data[i0]);
		sp->data06.data[i0] = NULL;
	}
	if (sp->data06.data) {EDFree (sp->data06.data); sp->data06.data = NULL; sp->data06.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data07.items; i0++) {
		if (sp->data07.data[i0]->AccessHashingChannelMask_Present) {
			if (sp->data07.data[i0]->AccessHashingChannelMask->value != NULL) {
				EDFree (sp->data07.data[i0]->AccessHashingChannelMask->value);
				sp->data07.data[i0]->AccessHashingChannelMask->value = NULL;
			}
			sp->data07.data[i0]->AccessHashingChannelMask->usedBits = 0;
			EDFree (sp->data07.data[i0]->AccessHashingChannelMask);
		}
		EDFree (sp->data07.data[i0]);
		sp->data07.data[i0] = NULL;
	}
	if (sp->data07.data) {EDFree (sp->data07.data); sp->data07.data = NULL; sp->data07.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data08.items; i0++) {
		if (sp->data08.data[i0]->FPDCHSupported_Present) {
		}
		EDFree (sp->data08.data[i0]);
		sp->data08.data[i0] = NULL;
	}
	if (sp->data08.data) {EDFree (sp->data08.data); sp->data08.data = NULL; sp->data08.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data09.items; i0++) {
		EDFree (sp->data09.data[i0]);
		sp->data09.data[i0] = NULL;
	}
	if (sp->data09.data) {EDFree (sp->data09.data); sp->data09.data = NULL; sp->data09.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data10.items; i0++) {
		if (sp->data10.data[i0]->PilotGroupID_Present) {
		}
		EDFree (sp->data10.data[i0]);
		sp->data10.data[i0] = NULL;
	}
	if (sp->data10.data) {EDFree (sp->data10.data); sp->data10.data = NULL; sp->data10.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data11.items; i0++) {
		EDFree (sp->data11.data[i0]);
		sp->data11.data[i0] = NULL;
	}
	if (sp->data11.data) {EDFree (sp->data11.data); sp->data11.data = NULL; sp->data11.allocatedItems=0; /*FR02A*/}

}

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters_contents */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters_contents (c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters_contents* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for variable-sized sequence c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02 */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02 (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->EARFCNPriority_Present) {
		}
		if (sp->data[i]->RxLevMinEUTRA_Present) {
		}
		if (sp->data[i]->PEMax_Present) {
		}
		if (sp->data[i]->RxLevMinEUTRAOffsetIncl_Present) {
		}
		if (sp->data[i]->RxLevMinEUTRAOffset_Present) {
		}
		if (sp->data[i]->PLMNSameAsPreviousChannel_Present) {
		}
		if (sp->data[i]->NumPLMNIDs_Present) {
		}
		if (sp->data[i]->PLMNID.data) {EDFree (sp->data[i]->PLMNID.data); sp->data[i]->PLMNID.data = NULL; sp->data[i]->PLMNID.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05 */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05 (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->ThreshXQ_Present) {
		}
		if (sp->data[i]->QualMinEUTRA_Present) {
		}
		if (sp->data[i]->QualMinEUTRAOffsetIncl_Present) {
		}
		if (sp->data[i]->QualMinEUTRAOffset_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01 */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01 (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01* sp) {
	int i, i0;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->OtherNeighborRATRecord_Present) {
			if (sp->data[i]->OtherNeighborRATRecord->value != NULL) {
				EDFree (sp->data[i]->OtherNeighborRATRecord->value);
				sp->data[i]->OtherNeighborRATRecord->value = NULL;
			}
			sp->data[i]->OtherNeighborRATRecord->usedBits = 0;
			EDFree (sp->data[i]->OtherNeighborRATRecord);
		}
		if (sp->data[i]->NeighborRATRecord_Present) {
			if (sp->data[i]->NeighborRATRecord->ServingPriority_Present) {
			}
			if (sp->data[i]->NeighborRATRecord->RxLevMinEUTRACommon_Present) {
			}
			if (sp->data[i]->NeighborRATRecord->PEMaxCommon_Present) {
			}
			if (sp->data[i]->NeighborRATRecord->RxLevMinEUTRAOffsetCommonIncl_Present) {
			}
			if (sp->data[i]->NeighborRATRecord->RxLevMinEUTRAOffsetCommon_Present) {
			}
			if (sp->data[i]->NeighborRATRecord->MaxReselectionTimer_Present) {
			}
			if (sp->data[i]->NeighborRATRecord->MinMeasurementBackoff_Present) {
			}
			if (sp->data[i]->NeighborRATRecord->MaxMeasurementBackoff_Present) {
			}
			for (i0=0; i0<sp->data[i]->NeighborRATRecord->data02.items; i0++) {
				if (sp->data[i]->NeighborRATRecord->data02.data[i0]->EARFCNPriority_Present) {
				}
				if (sp->data[i]->NeighborRATRecord->data02.data[i0]->RxLevMinEUTRA_Present) {
				}
				if (sp->data[i]->NeighborRATRecord->data02.data[i0]->PEMax_Present) {
				}
				if (sp->data[i]->NeighborRATRecord->data02.data[i0]->RxLevMinEUTRAOffsetIncl_Present) {
				}
				if (sp->data[i]->NeighborRATRecord->data02.data[i0]->RxLevMinEUTRAOffset_Present) {
				}
				if (sp->data[i]->NeighborRATRecord->data02.data[i0]->PLMNSameAsPreviousChannel_Present) {
				}
				if (sp->data[i]->NeighborRATRecord->data02.data[i0]->NumPLMNIDs_Present) {
				}
				if (sp->data[i]->NeighborRATRecord->data02.data[i0]->PLMNID.data) {EDFree (sp->data[i]->NeighborRATRecord->data02.data[i0]->PLMNID.data); sp->data[i]->NeighborRATRecord->data02.data[i0]->PLMNID.data = NULL; sp->data[i]->NeighborRATRecord->data02.data[i0]->PLMNID.allocatedItems=0; /*FR02A*/}
				EDFree (sp->data[i]->NeighborRATRecord->data02.data[i0]);
				sp->data[i]->NeighborRATRecord->data02.data[i0] = NULL;
			}
			if (sp->data[i]->NeighborRATRecord->data02.data) {EDFree (sp->data[i]->NeighborRATRecord->data02.data); sp->data[i]->NeighborRATRecord->data02.data = NULL; sp->data[i]->NeighborRATRecord->data02.allocatedItems=0; /*FR02A*/}
			if (sp->data[i]->NeighborRATRecord->ServingNetworkPLMNIncl_Present) {
			}
			if (sp->data[i]->NeighborRATRecord->NumServingPLMNIDs_Present) {
			}
			if (sp->data[i]->NeighborRATRecord->S_PLMNID.data) {EDFree (sp->data[i]->NeighborRATRecord->S_PLMNID.data); sp->data[i]->NeighborRATRecord->S_PLMNID.data = NULL; sp->data[i]->NeighborRATRecord->S_PLMNID.allocatedItems=0; /*FR02A*/}
			if (sp->data[i]->NeighborRATRecord->RSRQParametersIncluded_Present) {
			}
			if (sp->data[i]->NeighborRATRecord->QualMinEUTRACommon_Present) {
			}
			if (sp->data[i]->NeighborRATRecord->QualMinEUTRAOffsetCommonInc_Present) {
			}
			if (sp->data[i]->NeighborRATRecord->QualMinEUTRAOffsetCommon_Present) {
			}
			for (i0=0; i0<sp->data[i]->NeighborRATRecord->data05.items; i0++) {
				if (sp->data[i]->NeighborRATRecord->data05.data[i0]->ThreshXQ_Present) {
				}
				if (sp->data[i]->NeighborRATRecord->data05.data[i0]->QualMinEUTRA_Present) {
				}
				if (sp->data[i]->NeighborRATRecord->data05.data[i0]->QualMinEUTRAOffsetIncl_Present) {
				}
				if (sp->data[i]->NeighborRATRecord->data05.data[i0]->QualMinEUTRAOffset_Present) {
				}
				EDFree (sp->data[i]->NeighborRATRecord->data05.data[i0]);
				sp->data[i]->NeighborRATRecord->data05.data[i0] = NULL;
			}
			if (sp->data[i]->NeighborRATRecord->data05.data) {EDFree (sp->data[i]->NeighborRATRecord->data05.data); sp->data[i]->NeighborRATRecord->data05.data = NULL; sp->data[i]->NeighborRATRecord->data05.allocatedItems=0; /*FR02A*/}
			EDFree (sp->data[i]->NeighborRATRecord);
			sp->data[i]->NeighborRATRecord = NULL;
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents* sp) {
	int i0;
	int i1;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->OtherNeighborRATRecord_Present) {
			if (sp->data01.data[i0]->OtherNeighborRATRecord->value != NULL) {
				EDFree (sp->data01.data[i0]->OtherNeighborRATRecord->value);
				sp->data01.data[i0]->OtherNeighborRATRecord->value = NULL;
			}
			sp->data01.data[i0]->OtherNeighborRATRecord->usedBits = 0;
			EDFree (sp->data01.data[i0]->OtherNeighborRATRecord);
		}
		if (sp->data01.data[i0]->NeighborRATRecord_Present) {
			if (sp->data01.data[i0]->NeighborRATRecord->ServingPriority_Present) {
			}
			if (sp->data01.data[i0]->NeighborRATRecord->RxLevMinEUTRACommon_Present) {
			}
			if (sp->data01.data[i0]->NeighborRATRecord->PEMaxCommon_Present) {
			}
			if (sp->data01.data[i0]->NeighborRATRecord->RxLevMinEUTRAOffsetCommonIncl_Present) {
			}
			if (sp->data01.data[i0]->NeighborRATRecord->RxLevMinEUTRAOffsetCommon_Present) {
			}
			if (sp->data01.data[i0]->NeighborRATRecord->MaxReselectionTimer_Present) {
			}
			if (sp->data01.data[i0]->NeighborRATRecord->MinMeasurementBackoff_Present) {
			}
			if (sp->data01.data[i0]->NeighborRATRecord->MaxMeasurementBackoff_Present) {
			}
			for (i1=0; i1<sp->data01.data[i0]->NeighborRATRecord->data02.items; i1++) {
				if (sp->data01.data[i0]->NeighborRATRecord->data02.data[i1]->EARFCNPriority_Present) {
				}
				if (sp->data01.data[i0]->NeighborRATRecord->data02.data[i1]->RxLevMinEUTRA_Present) {
				}
				if (sp->data01.data[i0]->NeighborRATRecord->data02.data[i1]->PEMax_Present) {
				}
				if (sp->data01.data[i0]->NeighborRATRecord->data02.data[i1]->RxLevMinEUTRAOffsetIncl_Present) {
				}
				if (sp->data01.data[i0]->NeighborRATRecord->data02.data[i1]->RxLevMinEUTRAOffset_Present) {
				}
				if (sp->data01.data[i0]->NeighborRATRecord->data02.data[i1]->PLMNSameAsPreviousChannel_Present) {
				}
				if (sp->data01.data[i0]->NeighborRATRecord->data02.data[i1]->NumPLMNIDs_Present) {
				}
				if (sp->data01.data[i0]->NeighborRATRecord->data02.data[i1]->PLMNID.data) {EDFree (sp->data01.data[i0]->NeighborRATRecord->data02.data[i1]->PLMNID.data); sp->data01.data[i0]->NeighborRATRecord->data02.data[i1]->PLMNID.data = NULL; sp->data01.data[i0]->NeighborRATRecord->data02.data[i1]->PLMNID.allocatedItems=0; /*FR02A*/}
				EDFree (sp->data01.data[i0]->NeighborRATRecord->data02.data[i1]);
				sp->data01.data[i0]->NeighborRATRecord->data02.data[i1] = NULL;
			}
			if (sp->data01.data[i0]->NeighborRATRecord->data02.data) {EDFree (sp->data01.data[i0]->NeighborRATRecord->data02.data); sp->data01.data[i0]->NeighborRATRecord->data02.data = NULL; sp->data01.data[i0]->NeighborRATRecord->data02.allocatedItems=0; /*FR02A*/}
			if (sp->data01.data[i0]->NeighborRATRecord->ServingNetworkPLMNIncl_Present) {
			}
			if (sp->data01.data[i0]->NeighborRATRecord->NumServingPLMNIDs_Present) {
			}
			if (sp->data01.data[i0]->NeighborRATRecord->S_PLMNID.data) {EDFree (sp->data01.data[i0]->NeighborRATRecord->S_PLMNID.data); sp->data01.data[i0]->NeighborRATRecord->S_PLMNID.data = NULL; sp->data01.data[i0]->NeighborRATRecord->S_PLMNID.allocatedItems=0; /*FR02A*/}
			if (sp->data01.data[i0]->NeighborRATRecord->RSRQParametersIncluded_Present) {
			}
			if (sp->data01.data[i0]->NeighborRATRecord->QualMinEUTRACommon_Present) {
			}
			if (sp->data01.data[i0]->NeighborRATRecord->QualMinEUTRAOffsetCommonInc_Present) {
			}
			if (sp->data01.data[i0]->NeighborRATRecord->QualMinEUTRAOffsetCommon_Present) {
			}
			for (i1=0; i1<sp->data01.data[i0]->NeighborRATRecord->data05.items; i1++) {
				if (sp->data01.data[i0]->NeighborRATRecord->data05.data[i1]->ThreshXQ_Present) {
				}
				if (sp->data01.data[i0]->NeighborRATRecord->data05.data[i1]->QualMinEUTRA_Present) {
				}
				if (sp->data01.data[i0]->NeighborRATRecord->data05.data[i1]->QualMinEUTRAOffsetIncl_Present) {
				}
				if (sp->data01.data[i0]->NeighborRATRecord->data05.data[i1]->QualMinEUTRAOffset_Present) {
				}
				EDFree (sp->data01.data[i0]->NeighborRATRecord->data05.data[i1]);
				sp->data01.data[i0]->NeighborRATRecord->data05.data[i1] = NULL;
			}
			if (sp->data01.data[i0]->NeighborRATRecord->data05.data) {EDFree (sp->data01.data[i0]->NeighborRATRecord->data05.data); sp->data01.data[i0]->NeighborRATRecord->data05.data = NULL; sp->data01.data[i0]->NeighborRATRecord->data05.allocatedItems=0; /*FR02A*/}
			EDFree (sp->data01.data[i0]->NeighborRATRecord);
			sp->data01.data[i0]->NeighborRATRecord = NULL;
		}
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01 */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01 (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->APSubnetLength_Present) {
		}
		if (sp->data[i]->APSubnet_Present) {
			if (sp->data[i]->APSubnet->value != NULL) {
				EDFree (sp->data[i]->APSubnet->value);
				sp->data[i]->APSubnet->value = NULL;
			}
			sp->data[i]->APSubnet->usedBits = 0;
			EDFree (sp->data[i]->APSubnet);
		}
		if (sp->data[i]->APBand_Present) {
		}
		if (sp->data[i]->APChannel_Present) {
		}
		if (sp->data[i]->APPNRecordType_Present) {
		}
		if (sp->data[i]->APPNRecordLength_Present) {
		}
		if (sp->data[i]->APPNRecord.value != NULL) {
			EDFree (sp->data[i]->APPNRecord.value);
			sp->data[i]->APPNRecord.value = NULL;
		}
		sp->data[i]->APPNRecord.usedBits = 0;
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->APSubnetLength_Present) {
		}
		if (sp->data01.data[i0]->APSubnet_Present) {
			if (sp->data01.data[i0]->APSubnet->value != NULL) {
				EDFree (sp->data01.data[i0]->APSubnet->value);
				sp->data01.data[i0]->APSubnet->value = NULL;
			}
			sp->data01.data[i0]->APSubnet->usedBits = 0;
			EDFree (sp->data01.data[i0]->APSubnet);
		}
		if (sp->data01.data[i0]->APBand_Present) {
		}
		if (sp->data01.data[i0]->APChannel_Present) {
		}
		if (sp->data01.data[i0]->APPNRecordType_Present) {
		}
		if (sp->data01.data[i0]->APPNRecordLength_Present) {
		}
		if (sp->data01.data[i0]->APPNRecord.value != NULL) {
			EDFree (sp->data01.data[i0]->APPNRecord.value);
			sp->data01.data[i0]->APPNRecord.value = NULL;
		}
		sp->data01.data[i0]->APPNRecord.usedBits = 0;
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01 */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01 (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->HandoffInfoValue.value != NULL) {
			EDFree (sp->data[i]->HandoffInfoValue.value);
			sp->data[i]->HandoffInfoValue.value = NULL;
		}
		sp->data[i]->HandoffInfoValue.usedBits = 0;
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	if (sp->Subnet.value != NULL) {
		EDFree (sp->Subnet.value);
		sp->Subnet.value = NULL;
	}
	sp->Subnet.usedBits = 0;
	if (sp->APID.value != NULL) {
		EDFree (sp->APID.value);
		sp->APID.value = NULL;
	}
	sp->APID.usedBits = 0;
	if (sp->LocationRecord.value != NULL) {
		EDFree (sp->LocationRecord.value);
		sp->LocationRecord.value = NULL;
	}
	sp->LocationRecord.usedBits = 0;
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->HandoffInfoValue.value != NULL) {
			EDFree (sp->data01.data[i0]->HandoffInfoValue.value);
			sp->data01.data[i0]->HandoffInfoValue.value = NULL;
		}
		sp->data01.data[i0]->HandoffInfoValue.usedBits = 0;
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01 */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01 (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01 */
void FREE_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01 (c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->PilotPN_Present) {
		}
		if (sp->data[i]->PilotStrengthNominal_Present) {
		}
		if (sp->data[i]->PilotStrengthCorrectionMin_Present) {
		}
		if (sp->data[i]->PilotStrengthCorrectionMax_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents */
void FREE_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents (c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->PilotPN_Present) {
		}
		if (sp->data01.data[i0]->PilotStrengthNominal_Present) {
		}
		if (sp->data01.data[i0]->PilotStrengthCorrectionMin_Present) {
		}
		if (sp->data01.data[i0]->PilotStrengthCorrectionMax_Present) {
		}
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01 */
void FREE_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01 (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03 */
void FREE_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03 (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->PilotIncluded_Present) {
		}
		if (sp->data[i]->OpenLoopAdjust_Present) {
		}
		if (sp->data[i]->InitialAdjust_Present) {
		}
		if (sp->data[i]->PilotStrengthIncluded_Present) {
		}
		if (sp->data[i]->PilotStrengthNominal_Present) {
		}
		if (sp->data[i]->PilotStrengthCorrectionMin_Present) {
		}
		if (sp->data[i]->PilotStrengthCorrectionMax_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02 */
void FREE_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02 (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02* sp) {
	int i, i0;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->ReverseCDMAChannel_Present) {
			EDFree (sp->data[i]->ReverseCDMAChannel);
			sp->data[i]->ReverseCDMAChannel = NULL;
		}
		for (i0=0; i0<sp->data[i]->data03.items; i0++) {
			if (sp->data[i]->data03.data[i0]->PilotIncluded_Present) {
			}
			if (sp->data[i]->data03.data[i0]->OpenLoopAdjust_Present) {
			}
			if (sp->data[i]->data03.data[i0]->InitialAdjust_Present) {
			}
			if (sp->data[i]->data03.data[i0]->PilotStrengthIncluded_Present) {
			}
			if (sp->data[i]->data03.data[i0]->PilotStrengthNominal_Present) {
			}
			if (sp->data[i]->data03.data[i0]->PilotStrengthCorrectionMin_Present) {
			}
			if (sp->data[i]->data03.data[i0]->PilotStrengthCorrectionMax_Present) {
			}
			EDFree (sp->data[i]->data03.data[i0]);
			sp->data[i]->data03.data[i0] = NULL;
		}
		if (sp->data[i]->data03.data) {EDFree (sp->data[i]->data03.data); sp->data[i]->data03.data = NULL; sp->data[i]->data03.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents */
void FREE_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents* sp) {
	int i0;
	int i1;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data02.items; i0++) {
		if (sp->data02.data[i0]->ReverseCDMAChannel_Present) {
			EDFree (sp->data02.data[i0]->ReverseCDMAChannel);
			sp->data02.data[i0]->ReverseCDMAChannel = NULL;
		}
		for (i1=0; i1<sp->data02.data[i0]->data03.items; i1++) {
			if (sp->data02.data[i0]->data03.data[i1]->PilotIncluded_Present) {
			}
			if (sp->data02.data[i0]->data03.data[i1]->OpenLoopAdjust_Present) {
			}
			if (sp->data02.data[i0]->data03.data[i1]->InitialAdjust_Present) {
			}
			if (sp->data02.data[i0]->data03.data[i1]->PilotStrengthIncluded_Present) {
			}
			if (sp->data02.data[i0]->data03.data[i1]->PilotStrengthNominal_Present) {
			}
			if (sp->data02.data[i0]->data03.data[i1]->PilotStrengthCorrectionMin_Present) {
			}
			if (sp->data02.data[i0]->data03.data[i1]->PilotStrengthCorrectionMax_Present) {
			}
			EDFree (sp->data02.data[i0]->data03.data[i1]);
			sp->data02.data[i0]->data03.data[i1] = NULL;
		}
		if (sp->data02.data[i0]->data03.data) {EDFree (sp->data02.data[i0]->data03.data); sp->data02.data[i0]->data03.data = NULL; sp->data02.data[i0]->data03.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data02.data[i0]);
		sp->data02.data[i0] = NULL;
	}
	if (sp->data02.data) {EDFree (sp->data02.data); sp->data02.data = NULL; sp->data02.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01 */
void FREE_c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01 (c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->PreferredControlChannelCycle_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle */
void FREE_c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle (c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->PreferredControlChannelCycle_Present) {
		}
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Inter_RAT_Idle_State_SlottedMode_data01 */
void FREE_c_RPD_Inter_RAT_Idle_State_SlottedMode_data01 (c_RPD_Inter_RAT_Idle_State_SlottedMode_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Inter_RAT_Idle_State_SlottedMode */
void FREE_c_RPD_Inter_RAT_Idle_State_SlottedMode (c_RPD_Inter_RAT_Idle_State_SlottedMode* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02 */
void FREE_c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02 (c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPD_Inter_RAT_Idle_State_PagingMask_data01 */
void FREE_c_RPD_Inter_RAT_Idle_State_PagingMask_data01 (c_RPD_Inter_RAT_Idle_State_PagingMask_data01* sp) {
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
/* Free function for struct c_RPD_Inter_RAT_Idle_State_PagingMask */
void FREE_c_RPD_Inter_RAT_Idle_State_PagingMask (c_RPD_Inter_RAT_Idle_State_PagingMask* sp) {
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

/* Free function for variable-sized sequence c_RPD_Inter_RAT_Route_Update_SearchParameters_data01 */
void FREE_c_RPD_Inter_RAT_Route_Update_SearchParameters_data01 (c_RPD_Inter_RAT_Route_Update_SearchParameters_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Inter_RAT_Route_Update_SearchParameters */
void FREE_c_RPD_Inter_RAT_Route_Update_SearchParameters (c_RPD_Inter_RAT_Route_Update_SearchParameters* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01 */
void FREE_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01 (c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->SoftSlope_Present) {
		}
		if (sp->data[i]->AddIntercept_Present) {
		}
		if (sp->data[i]->DropIntercept_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters */
void FREE_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters (c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->SoftSlope_Present) {
		}
		if (sp->data01.data[i0]->AddIntercept_Present) {
		}
		if (sp->data01.data[i0]->DropIntercept_Present) {
		}
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01 */
void FREE_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01 (c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->SoftSlope_Present) {
		}
		if (sp->data[i]->AddIntercept_Present) {
		}
		if (sp->data[i]->DropIntercept_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters */
void FREE_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters (c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->SoftSlope_Present) {
		}
		if (sp->data01.data[i0]->AddIntercept_Present) {
		}
		if (sp->data01.data[i0]->DropIntercept_Present) {
		}
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03 */
void FREE_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03 (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02 */
void FREE_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02 (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02* sp) {
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
/* Free function for variable-sized sequence c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01 */
void FREE_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01 (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01* sp) {
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
/* Free function for struct c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels */
void FREE_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels* sp) {
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

/* Free function for variable-sized sequence c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01 */
void FREE_c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01 (c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->PreferredControlChannelCycle_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle */
void FREE_c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle (c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->PreferredControlChannelCycle_Present) {
		}
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01 */
void FREE_c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01 (c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode */
void FREE_c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode (c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02 */
void FREE_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02 (c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01 */
void FREE_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01 (c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01* sp) {
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
/* Free function for struct c_RPD_Inter_RAT_Quick_Idle_State_PagingMask */
void FREE_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask (c_RPD_Inter_RAT_Quick_Idle_State_PagingMask* sp) {
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

/* Free function for variable-sized sequence c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01 */
void FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01 (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters */
void FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01 */
void FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01 (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->SoftSlope_Present) {
		}
		if (sp->data[i]->AddIntercept_Present) {
		}
		if (sp->data[i]->DropIntercept_Present) {
		}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters */
void FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data01.items; i0++) {
		if (sp->data01.data[i0]->SoftSlope_Present) {
		}
		if (sp->data01.data[i0]->AddIntercept_Present) {
		}
		if (sp->data01.data[i0]->DropIntercept_Present) {
		}
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03 */
void FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03 (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02 */
void FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02 (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02* sp) {
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
/* Free function for variable-sized sequence c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04 */
void FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04 (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		if (sp->data[i]->MultiBandBitMap.value != NULL) {
			EDFree (sp->data[i]->MultiBandBitMap.value);
			sp->data[i]->MultiBandBitMap.value = NULL;
		}
		sp->data[i]->MultiBandBitMap.usedBits = 0;
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01 */
void FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01 (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01* sp) {
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
		if (sp->data[i]->MultiBandCount_Present) {
		}
		if (sp->data[i]->MultiBandBitMapCount_Present) {
		}
		for (i0=0; i0<sp->data[i]->data04.items; i0++) {
			if (sp->data[i]->data04.data[i0]->MultiBandBitMap.value != NULL) {
				EDFree (sp->data[i]->data04.data[i0]->MultiBandBitMap.value);
				sp->data[i]->data04.data[i0]->MultiBandBitMap.value = NULL;
			}
			sp->data[i]->data04.data[i0]->MultiBandBitMap.usedBits = 0;
			EDFree (sp->data[i]->data04.data[i0]);
			sp->data[i]->data04.data[i0] = NULL;
		}
		if (sp->data[i]->data04.data) {EDFree (sp->data[i]->data04.data); sp->data[i]->data04.data = NULL; sp->data[i]->data04.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels */
void FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels* sp) {
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
		if (sp->data01.data[i0]->MultiBandCount_Present) {
		}
		if (sp->data01.data[i0]->MultiBandBitMapCount_Present) {
		}
		for (i1=0; i1<sp->data01.data[i0]->data04.items; i1++) {
			if (sp->data01.data[i0]->data04.data[i1]->MultiBandBitMap.value != NULL) {
				EDFree (sp->data01.data[i0]->data04.data[i1]->MultiBandBitMap.value);
				sp->data01.data[i0]->data04.data[i1]->MultiBandBitMap.value = NULL;
			}
			sp->data01.data[i0]->data04.data[i1]->MultiBandBitMap.usedBits = 0;
			EDFree (sp->data01.data[i0]->data04.data[i1]);
			sp->data01.data[i0]->data04.data[i1] = NULL;
		}
		if (sp->data01.data[i0]->data04.data) {EDFree (sp->data01.data[i0]->data04.data); sp->data01.data[i0]->data04.data = NULL; sp->data01.data[i0]->data04.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data01.data[i0]);
		sp->data01.data[i0] = NULL;
	}
	if (sp->data01.data) {EDFree (sp->data01.data); sp->data01.data = NULL; sp->data01.allocatedItems=0; /*FR02A*/}

}

/* Free function for variable-sized sequence c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02 */
void FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02 (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		EDFree (sp->data[i]);
		sp->data[i] = NULL;
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01 */
void FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01 (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01* sp) {
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
/* Free function for struct c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns */
void FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns* sp) {
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

/* Free function for struct c_RPDCON_IRATINSP_INUSE_Sync */
void FREE_c_RPDCON_IRATINSP_INUSE_Sync (c_RPDCON_IRATINSP_INUSE_Sync* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATINSP_INUSE_Sync_contents (&(sp->contents));

}

/* Free function for struct c_RPDSES_SL_UATIAssignment */
void FREE_c_RPDSES_SL_UATIAssignment (c_RPDSES_SL_UATIAssignment* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDSES_SL_UATIAssignment_contents (&(sp->contents));

}

/* Free function for struct c_RPDSES_SL_InterRATMobilityIndication */
void FREE_c_RPDSES_SL_InterRATMobilityIndication (c_RPDSES_SL_InterRATMobilityIndication* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_RPDSES_SL_InterRATMobilityAck */
void FREE_c_RPDSES_SL_InterRATMobilityAck (c_RPDSES_SL_InterRATMobilityAck* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_RPDCON_IRATSAP_INCFG_ConfigurationRequest */
void FREE_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest (c_RPDCON_IRATSAP_INCFG_ConfigurationRequest* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATSAP_INCFG_ConfigurationResponse */
void FREE_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse (c_RPDCON_IRATSAP_INCFG_ConfigurationResponse* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq */
void FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq (c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf */
void FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf (c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail */
void FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail (c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq */
void FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq (c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf */
void FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf (c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq */
void FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq (c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete */
void FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete (c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATINSP_INCFG_ConfigurationRequest */
void FREE_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest (c_RPDCON_IRATINSP_INCFG_ConfigurationRequest* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATINSP_INCFG_ConfigurationResponse */
void FREE_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse (c_RPDCON_IRATINSP_INCFG_ConfigurationResponse* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATISP_INCFG_ConfigurationRequest */
void FREE_c_RPDCON_IRATISP_INCFG_ConfigurationRequest (c_RPDCON_IRATISP_INCFG_ConfigurationRequest* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATISP_INCFG_ConfigurationResponse */
void FREE_c_RPDCON_IRATISP_INCFG_ConfigurationResponse (c_RPDCON_IRATISP_INCFG_ConfigurationResponse* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATISP_INUSE_Page */
void FREE_c_RPDCON_IRATISP_INUSE_Page (c_RPDCON_IRATISP_INUSE_Page* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_RPDCON_IRATISP_INUSE_ConnectionRequest */
void FREE_c_RPDCON_IRATISP_INUSE_ConnectionRequest (c_RPDCON_IRATISP_INUSE_ConnectionRequest* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATISP_INUSE_ConnectionDeny */
void FREE_c_RPDCON_IRATISP_INUSE_ConnectionDeny (c_RPDCON_IRATISP_INUSE_ConnectionDeny* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATISP_INUSE_ConnectionDeny_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest */
void FREE_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest (c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept */
void FREE_c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept (c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATISP_INUSE_AttributeUpdateReject */
void FREE_c_RPDCON_IRATISP_INUSE_AttributeUpdateReject (c_RPDCON_IRATISP_INUSE_AttributeUpdateReject* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATISP_INUSE_AttributeUpdateReject_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATRUP_INCFG_ConfigurationRequest */
void FREE_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest (c_RPDCON_IRATRUP_INCFG_ConfigurationRequest* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATRUP_INCFG_ConfigurationResponse */
void FREE_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse (c_RPDCON_IRATRUP_INCFG_ConfigurationResponse* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATRUP_INUSE_RouteUpdate */
void FREE_c_RPDCON_IRATRUP_INUSE_RouteUpdate (c_RPDCON_IRATRUP_INUSE_RouteUpdate* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment */
void FREE_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete */
void FREE_c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete (c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATRUP_INUSE_ResetReport */
void FREE_c_RPDCON_IRATRUP_INUSE_ResetReport (c_RPDCON_IRATRUP_INUSE_ResetReport* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_RPDCON_IRATRUP_INUSE_NeighborList */
void FREE_c_RPDCON_IRATRUP_INUSE_NeighborList (c_RPDCON_IRATRUP_INUSE_NeighborList* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATRUP_INUSE_NeighborList_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATRUP_INUSE_AttributeOverride */
void FREE_c_RPDCON_IRATRUP_INUSE_AttributeOverride (c_RPDCON_IRATRUP_INUSE_AttributeOverride* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse */
void FREE_c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse (c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest */
void FREE_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest */
void FREE_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest (c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept */
void FREE_c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept (c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject */
void FREE_c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject (c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATOMP_INCFG_ConfigurationRequest */
void FREE_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest (c_RPDCON_IRATOMP_INCFG_ConfigurationRequest* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATOMP_INCFG_ConfigurationResponse */
void FREE_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse (c_RPDCON_IRATOMP_INCFG_ConfigurationResponse* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATOMP_INUSE_QuickConfig */
void FREE_c_RPDCON_IRATOMP_INUSE_QuickConfig (c_RPDCON_IRATOMP_INUSE_QuickConfig* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATOMP_INUSE_SectorParameters */
void FREE_c_RPDCON_IRATOMP_INUSE_SectorParameters (c_RPDCON_IRATOMP_INUSE_SectorParameters* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters */
void FREE_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters (c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList */
void FREE_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_DSAP_INCFG_ConfigurationRequest */
void FREE_c_RPDCON_DSAP_INCFG_ConfigurationRequest (c_RPDCON_DSAP_INCFG_ConfigurationRequest* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_DSAP_INCFG_ConfigurationResponse */
void FREE_c_RPDCON_DSAP_INCFG_ConfigurationResponse (c_RPDCON_DSAP_INCFG_ConfigurationResponse* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATQISP_INCFG_ConfigurationRequest */
void FREE_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest (c_RPDCON_IRATQISP_INCFG_ConfigurationRequest* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATQISP_INCFG_ConfigurationResponse */
void FREE_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse (c_RPDCON_IRATQISP_INCFG_ConfigurationResponse* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATQISP_INUSE_Page */
void FREE_c_RPDCON_IRATQISP_INUSE_Page (c_RPDCON_IRATQISP_INUSE_Page* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATQISP_INUSE_Page_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATQISP_INUSE_ConnectionRequest */
void FREE_c_RPDCON_IRATQISP_INUSE_ConnectionRequest (c_RPDCON_IRATQISP_INUSE_ConnectionRequest* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATQISP_INUSE_ConnectionDeny */
void FREE_c_RPDCON_IRATQISP_INUSE_ConnectionDeny (c_RPDCON_IRATQISP_INUSE_ConnectionDeny* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATQISP_INUSE_ConnectionDeny_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATQISP_INUSE_QuickPage */
void FREE_c_RPDCON_IRATQISP_INUSE_QuickPage (c_RPDCON_IRATQISP_INUSE_QuickPage* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATQISP_INUSE_QuickPage_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest */
void FREE_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest (c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept */
void FREE_c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept (c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject */
void FREE_c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject (c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest */
void FREE_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest (c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse */
void FREE_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse (c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_RouteUpdate */
void FREE_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate (c_RPDCON_S1IRATRUP_INUSE_RouteUpdate* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment */
void FREE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete */
void FREE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_ResetReport */
void FREE_c_RPDCON_S1IRATRUP_INUSE_ResetReport (c_RPDCON_S1IRATRUP_INUSE_ResetReport* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_NeighborList */
void FREE_c_RPDCON_S1IRATRUP_INUSE_NeighborList (c_RPDCON_S1IRATRUP_INUSE_NeighborList* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest */
void FREE_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest */
void FREE_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest (c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept */
void FREE_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept (c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject */
void FREE_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject (c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest */
void FREE_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest (c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse */
void FREE_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse (c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters (c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents (&(sp->contents));

}

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents (&(sp->contents));

}

/* Free function for struct c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters */
void FREE_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters (c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents (&(sp->contents));

}

/* Free function for struct c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters */
void FREE_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents (&(sp->contents));

}

/* Free function for struct c_RPD_Session_Layer_Attributes */
void FREE_c_RPD_Session_Layer_Attributes (c_RPD_Session_Layer_Attributes* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for union c_RPD_Inter_RAT_Idle_State_complex */
void FREE_c_RPD_Inter_RAT_Idle_State_complex (c_RPD_Inter_RAT_Idle_State_complex* sp) {
	switch (sp->Present) {
		case U_c_RPD_Inter_RAT_Idle_State_complex_PreferredControlChannelCycle: {
			FREE_c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle (sp->u.PreferredControlChannelCycle);
			EDFree (sp->u.PreferredControlChannelCycle);

			break;
		}
		case U_c_RPD_Inter_RAT_Idle_State_complex_SlottedMode: {
			FREE_c_RPD_Inter_RAT_Idle_State_SlottedMode (sp->u.SlottedMode);
			EDFree (sp->u.SlottedMode);

			break;
		}
		case U_c_RPD_Inter_RAT_Idle_State_complex_PagingMask: {
			FREE_c_RPD_Inter_RAT_Idle_State_PagingMask (sp->u.PagingMask);
			EDFree (sp->u.PagingMask);

			break;
		}

		default:;
	}
	sp->Present = U_c_RPD_Inter_RAT_Idle_State_complex_NONE;
}

/* Free function for struct c_RPD_Inter_RAT_Idle_State */
void FREE_c_RPD_Inter_RAT_Idle_State (c_RPD_Inter_RAT_Idle_State* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Inter_RAT_Idle_State_complex (&(sp->complex));

}

/* Free function for union c_RPD_Inter_RAT_Route_Update_complex */
void FREE_c_RPD_Inter_RAT_Route_Update_complex (c_RPD_Inter_RAT_Route_Update_complex* sp) {
	switch (sp->Present) {
		case U_c_RPD_Inter_RAT_Route_Update_complex_SearchParameters: {
			FREE_c_RPD_Inter_RAT_Route_Update_SearchParameters (sp->u.SearchParameters);
			EDFree (sp->u.SearchParameters);

			break;
		}
		case U_c_RPD_Inter_RAT_Route_Update_complex_SetManagementSameChannelParameters: {
			FREE_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters (sp->u.SetManagementSameChannelParameters);
			EDFree (sp->u.SetManagementSameChannelParameters);

			break;
		}
		case U_c_RPD_Inter_RAT_Route_Update_complex_SetManagementDifferentChannelParameters: {
			FREE_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters (sp->u.SetManagementDifferentChannelParameters);
			EDFree (sp->u.SetManagementDifferentChannelParameters);

			break;
		}
		case U_c_RPD_Inter_RAT_Route_Update_complex_SupportedCDMAChannels: {
			FREE_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels (sp->u.SupportedCDMAChannels);
			EDFree (sp->u.SupportedCDMAChannels);

			break;
		}

		default:;
	}
	sp->Present = U_c_RPD_Inter_RAT_Route_Update_complex_NONE;
}

/* Free function for struct c_RPD_Inter_RAT_Route_Update */
void FREE_c_RPD_Inter_RAT_Route_Update (c_RPD_Inter_RAT_Route_Update* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Inter_RAT_Route_Update_complex (&(sp->complex));

}

/* Free function for struct c_RPD_Inter_RAT_Overhead_Messages */
void FREE_c_RPD_Inter_RAT_Overhead_Messages (c_RPD_Inter_RAT_Overhead_Messages* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for union c_RPD_Inter_RAT_Quick_Idle_State_complex */
void FREE_c_RPD_Inter_RAT_Quick_Idle_State_complex (c_RPD_Inter_RAT_Quick_Idle_State_complex* sp) {
	switch (sp->Present) {
		case U_c_RPD_Inter_RAT_Quick_Idle_State_complex_PreferredControlChannelCycle: {
			FREE_c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle (sp->u.PreferredControlChannelCycle);
			EDFree (sp->u.PreferredControlChannelCycle);

			break;
		}
		case U_c_RPD_Inter_RAT_Quick_Idle_State_complex_SlottedMode: {
			FREE_c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode (sp->u.SlottedMode);
			EDFree (sp->u.SlottedMode);

			break;
		}
		case U_c_RPD_Inter_RAT_Quick_Idle_State_complex_PagingMask: {
			FREE_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask (sp->u.PagingMask);
			EDFree (sp->u.PagingMask);

			break;
		}

		default:;
	}
	sp->Present = U_c_RPD_Inter_RAT_Quick_Idle_State_complex_NONE;
}

/* Free function for struct c_RPD_Inter_RAT_Quick_Idle_State */
void FREE_c_RPD_Inter_RAT_Quick_Idle_State (c_RPD_Inter_RAT_Quick_Idle_State* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Inter_RAT_Quick_Idle_State_complex (&(sp->complex));

}

/* Free function for union c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex */
void FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex (c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex* sp) {
	switch (sp->Present) {
		case U_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SearchParameters: {
			FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters (sp->u.SearchParameters);
			EDFree (sp->u.SearchParameters);

			break;
		}
		case U_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SetManagementParameters: {
			FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters (sp->u.SetManagementParameters);
			EDFree (sp->u.SetManagementParameters);

			break;
		}
		case U_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SupportedCDMAChannels: {
			FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels (sp->u.SupportedCDMAChannels);
			EDFree (sp->u.SupportedCDMAChannels);

			break;
		}
		case U_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SupportedDRXPatterns: {
			FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns (sp->u.SupportedDRXPatterns);
			EDFree (sp->u.SupportedDRXPatterns);

			break;
		}

		default:;
	}
	sp->Present = U_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_NONE;
}

/* Free function for struct c_RPD_Subtype1_based_Inter_RAT_Route_Update */
void FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update (c_RPD_Subtype1_based_Inter_RAT_Route_Update* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex (&(sp->complex));

}

/* Free function for struct c_GenericTLV_cs0087 */
void FREE_c_GenericTLV_cs0087 (c_GenericTLV_cs0087* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->TLV_Data.value != NULL) {
		EDFree (sp->TLV_Data.value);
		sp->TLV_Data.value = NULL;
	}
	sp->TLV_Data.usedBits = 0;

}

/* SETITEMS commands for type 'c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01 (c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01_data));
			(sequence->data[i]->AttributeLength) = 0;
			INIT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01_data */
void FREE_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01_data (c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->AttributeRecord));

}

/* SETITEMS commands for type 'c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01 (c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01_data));
			(sequence->data[i]->AttributeLength) = 0;
			INIT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01_data */
void FREE_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01_data (c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->AttributeRecord));

}

/* SETITEMS commands for type 'c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01 (c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01_data));
			(sequence->data[i]->AttributeLength) = 0;
			INIT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01_data */
void FREE_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01_data (c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->AttributeRecord));

}

/* SETITEMS commands for type 'c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01 (c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01_data));
			(sequence->data[i]->AttributeLength) = 0;
			INIT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01_data */
void FREE_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01_data (c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->AttributeRecord));

}

/* SETITEMS commands for type 'c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01 (c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01_data));
			(sequence->data[i]->AttributeLength) = 0;
			INIT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01_data */
void FREE_c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01_data (c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->AttributeRecord));

}

/* SETITEMS commands for type 'c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01 (c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01_data));
			(sequence->data[i]->AttributeLength) = 0;
			INIT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01_data */
void FREE_c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01_data (c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->AttributeRecord));

}

/* SETITEMS commands for type 'c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01 (c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data));
			(sequence->data[i]->PreferredChannel.SystemType) = 0;
			(sequence->data[i]->PreferredChannel.BandClass) = 0;
			(sequence->data[i]->PreferredChannel.ChannelNumber) = 0;
			
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

/* Free function for struct c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data */
void FREE_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data (c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel */
void FREE_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel (c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01 (c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01_data));
			(sequence->data[i]->AttributeLength) = 0;
			INIT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01_data */
void FREE_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01_data (c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->AttributeRecord));

}

/* SETITEMS commands for type 'c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01 (c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01_data));
			(sequence->data[i]->AttributeLength) = 0;
			INIT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01_data */
void FREE_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01_data (c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->AttributeRecord));

}

/* SETITEMS commands for type 'c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01 (c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01_data));
			(sequence->data[i]->AttributeLength) = 0;
			INIT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01_data */
void FREE_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01_data (c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->AttributeRecord));

}

/* SETITEMS commands for type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01 (c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data));
			(sequence->data[i]->PilotPNPhase) = 0;
			(sequence->data[i]->ChannelIncluded) = 0;
			(sequence->data[i]->PilotStrength) = 0;
			(sequence->data[i]->Keep) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->Channel_Present) {
					EDFree (sequence->data[i]->Channel);
					sequence->data[i]->Channel = NULL;
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data */
void FREE_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data (c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->Channel_Present) {
		EDFree (sp->Channel);
		sp->Channel = NULL;
		sp->Channel_Present = ED_FALSE;
	}

}

void SETPRESENT_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel (c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->Channel_Present == present) return;
	sp->Channel_Present = present;
	if (present) {
		/*-->*/sp->Channel = (c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel));
		ED_RESET_MEM (sp->Channel, sizeof (c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel));
		(sp->Channel->SystemType) = 0;
		(sp->Channel->BandClass) = 0;
		(sp->Channel->ChannelNumber) = 0;
	} else {
		EDFree (sp->Channel);
		sp->Channel = NULL;
	}
}

/* Free function for struct c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel */
void FREE_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel (c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel */
void FREE_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel (c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_Channel */
void FREE_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_Channel (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_Channel* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01 (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data));
			(sequence->data[i]->PilotPN) = 0;
			(sequence->data[i]->SofterHandoff) = 0;
			(sequence->data[i]->MACIndexLSBs) = 0;
			(sequence->data[i]->DRCCover) = 0;
			(sequence->data[i]->RABLength) = 0;
			(sequence->data[i]->RABOffset) = 0;
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

/* Free function for struct c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data */
void FREE_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02 (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data** tmp;
		tmp = (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data**)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data));
			(sequence->data[i]->RAChannelGain) = 0;
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

/* Free function for struct c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data */
void FREE_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03 (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data** tmp;
		tmp = (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data**)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data));
			(sequence->data[i]->MACIndexMSB) = 0;
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

/* Free function for struct c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data */
void FREE_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04 (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04_data** tmp;
		tmp = (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04_data**)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04_data*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04_data));
			(sequence->data[i]->DSC) = 0;
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

/* Free function for struct c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04_data */
void FREE_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04_data (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01 (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01_data));
			(sequence->data[i]->PilotPN) = 0;
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

/* Free function for struct c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01_data */
void FREE_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01_data (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02 (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data** tmp;
		tmp = (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data**)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data));
			(sequence->data[i]->ChannelIncluded) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->Channel_Present) {
					EDFree (sequence->data[i]->Channel);
					sequence->data[i]->Channel = NULL;
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data */
void FREE_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->Channel_Present) {
		EDFree (sp->Channel);
		sp->Channel = NULL;
		sp->Channel_Present = ED_FALSE;
	}

}

void SETPRESENT_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data_Channel (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->Channel_Present == present) return;
	sp->Channel_Present = present;
	if (present) {
		/*-->*/sp->Channel = (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data_Channel*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data_Channel));
		ED_RESET_MEM (sp->Channel, sizeof (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data_Channel));
		(sp->Channel->SystemType) = 0;
		(sp->Channel->BandClass) = 0;
		(sp->Channel->ChannelNumber) = 0;
	} else {
		EDFree (sp->Channel);
		sp->Channel = NULL;
	}
}

/* Free function for struct c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data_Channel */
void FREE_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data_Channel (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data_Channel* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03 (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03_data** tmp;
		tmp = (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03_data**)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03_data*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03_data));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->SearchWindowSize_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03_data */
void FREE_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03_data (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04 (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04_data** tmp;
		tmp = (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04_data**)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04_data*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04_data));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->SearchWindowOffset_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04_data */
void FREE_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04_data (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05 (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05_data** tmp;
		tmp = (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05_data**)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05_data*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05_data));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->FPDCHSupported_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05_data */
void FREE_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05_data (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01 (c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01_data));
			(sequence->data[i]->AttributeLength) = 0;
			INIT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01_data */
void FREE_c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01_data (c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->AttributeRecord));

}

/* Free function for struct c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_Channel */
void FREE_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_Channel (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_Channel* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01 (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data));
			(sequence->data[i]->SectorPilotPN) = 0;
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

/* Free function for struct c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data */
void FREE_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02 (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data** tmp;
		tmp = (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data**)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->SectorSearchWindowSize_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data */
void FREE_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03 (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data** tmp;
		tmp = (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data**)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->SectorSearchWindowOffset_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data */
void FREE_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01 (c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data));
			(sequence->data[i]->AttributeLength) = 0;
			INIT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data */
void FREE_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data (c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->AttributeRecord));

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01 (c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01_data));
			(sequence->data[i]->AttributeLength) = 0;
			INIT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01_data */
void FREE_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01_data (c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->AttributeRecord));

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01 (c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01_data));
			(sequence->data[i]->AttributeLength) = 0;
			INIT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01_data */
void FREE_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01_data (c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->AttributeRecord));

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01 (c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01_data));
			(sequence->data[i]->ForwardTrafficValid63To0) = 0;
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

/* Free function for struct c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01_data */
void FREE_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01_data (c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02 (c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02_data** tmp;
		tmp = (c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02_data**)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02_data*)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02_data));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->ForwardTrafficValid127To64_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02_data */
void FREE_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02_data (c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03 (c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03_data** tmp;
		tmp = (c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03_data**)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03_data*)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03_data));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->CompatibleReservedBits_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03_data */
void FREE_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03_data (c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01 (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data));
			(sequence->data[i]->Channel.SystemType) = 0;
			(sequence->data[i]->Channel.BandClass) = 0;
			(sequence->data[i]->Channel.ChannelNumber) = 0;
			
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

/* Free function for struct c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data */
void FREE_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data_Channel */
void FREE_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data_Channel (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data_Channel* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02 (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02_data** tmp;
		tmp = (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02_data**)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02_data*)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02_data));
			(sequence->data[i]->NeighborPilotPN) = 0;
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

/* Free function for struct c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02_data */
void FREE_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02_data (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03 (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data** tmp;
		tmp = (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data**)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data*)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data));
			(sequence->data[i]->NeighborChannelIncluded) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->NeighborChannel_Present) {
					EDFree (sequence->data[i]->NeighborChannel);
					sequence->data[i]->NeighborChannel = NULL;
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data */
void FREE_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->NeighborChannel_Present) {
		EDFree (sp->NeighborChannel);
		sp->NeighborChannel = NULL;
		sp->NeighborChannel_Present = ED_FALSE;
	}

}

void SETPRESENT_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data_NeighborChannel (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->NeighborChannel_Present == present) return;
	sp->NeighborChannel_Present = present;
	if (present) {
		/*-->*/sp->NeighborChannel = (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data_NeighborChannel*)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data_NeighborChannel));
		ED_RESET_MEM (sp->NeighborChannel, sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data_NeighborChannel));
		(sp->NeighborChannel->SystemType) = 0;
		(sp->NeighborChannel->BandClass) = 0;
		(sp->NeighborChannel->ChannelNumber) = 0;
	} else {
		EDFree (sp->NeighborChannel);
		sp->NeighborChannel = NULL;
	}
}

/* Free function for struct c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data_NeighborChannel */
void FREE_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data_NeighborChannel (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data_NeighborChannel* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04 (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04_data** tmp;
		tmp = (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04_data**)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04_data*)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04_data));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->NeighborSearchWindowSize_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04_data */
void FREE_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04_data (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05 (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05_data** tmp;
		tmp = (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05_data**)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05_data*)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05_data));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->NeighborSearchWindowOffset_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05_data */
void FREE_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05_data (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06 (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data** tmp;
		tmp = (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data**)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data*)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data));
			(sequence->data[i]->ExtendedChannel.SystemType) = 0;
			(sequence->data[i]->ExtendedChannel.BandClass) = 0;
			(sequence->data[i]->ExtendedChannel.ChannelNumber) = 0;
			
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

/* Free function for struct c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data */
void FREE_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data_ExtendedChannel */
void FREE_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data_ExtendedChannel (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data_ExtendedChannel* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07 (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07_data** tmp;
		tmp = (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07_data**)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07_data*)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07_data));
			(sequence->data[i]->AccessHashingChannelMaskSameAsPrevious) = 0;
			sequence->data[i]->AccessHashingChannelMask.value = NULL;
			sequence->data[i]->AccessHashingChannelMask.usedBits = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->AccessHashingChannelMask.value != NULL) {
					EDFree (sequence->data[i]->AccessHashingChannelMask.value);
					sequence->data[i]->AccessHashingChannelMask.value = NULL;
				}
				sequence->data[i]->AccessHashingChannelMask.usedBits = 0;
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07_data */
void FREE_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07_data (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->AccessHashingChannelMask.value != NULL) {
		EDFree (sp->AccessHashingChannelMask.value);
		sp->AccessHashingChannelMask.value = NULL;
	}
	sp->AccessHashingChannelMask.usedBits = 0;

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08 (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08_data** tmp;
		tmp = (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08_data**)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08_data*)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08_data));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->FPDCHSupported_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08_data */
void FREE_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08_data (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09 (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09_data** tmp;
		tmp = (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09_data**)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09_data*)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09_data));
			(sequence->data[i]->SecondaryColorCode) = 0;
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

/* Free function for struct c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09_data */
void FREE_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09_data (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01 (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01* sequence, int desiredItems)
{
	int i, i0;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data));
			(sequence->data[i]->RATType) = 0;
			(sequence->data[i]->NeighborRATRecordLength) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->OtherNeighborRATRecord_Present) {
					if (sequence->data[i]->OtherNeighborRATRecord->value != NULL) {
						EDFree (sequence->data[i]->OtherNeighborRATRecord->value);
						sequence->data[i]->OtherNeighborRATRecord->value = NULL;
					}
					sequence->data[i]->OtherNeighborRATRecord->usedBits = 0;
					EDFree (sequence->data[i]->OtherNeighborRATRecord);
				}
				if (sequence->data[i]->NeighborRATRecord_Present) {
					if (sequence->data[i]->NeighborRATRecord->ServingPriority_Present) {
					}
					if (sequence->data[i]->NeighborRATRecord->RxLevMinEUTRACommon_Present) {
					}
					if (sequence->data[i]->NeighborRATRecord->PEMaxCommon_Present) {
					}
					if (sequence->data[i]->NeighborRATRecord->RxLevMinEUTRAOffsetCommonIncl_Present) {
					}
					if (sequence->data[i]->NeighborRATRecord->RxLevMinEUTRAOffsetCommon_Present) {
					}
					if (sequence->data[i]->NeighborRATRecord->MaxReselectionTimer_Present) {
					}
					if (sequence->data[i]->NeighborRATRecord->MinMeasurementBackoff_Present) {
					}
					if (sequence->data[i]->NeighborRATRecord->MaxMeasurementBackoff_Present) {
					}
					for (i0=0; i0<sequence->data[i]->NeighborRATRecord->data02.items; i0++) {
						if (sequence->data[i]->NeighborRATRecord->data02.data[i0]->EARFCNPriority_Present) {
						}
						if (sequence->data[i]->NeighborRATRecord->data02.data[i0]->RxLevMinEUTRA_Present) {
						}
						if (sequence->data[i]->NeighborRATRecord->data02.data[i0]->PEMax_Present) {
						}
						if (sequence->data[i]->NeighborRATRecord->data02.data[i0]->RxLevMinEUTRAOffsetIncl_Present) {
						}
						if (sequence->data[i]->NeighborRATRecord->data02.data[i0]->RxLevMinEUTRAOffset_Present) {
						}
						if (sequence->data[i]->NeighborRATRecord->data02.data[i0]->PLMNSameAsPreviousChannel_Present) {
						}
						if (sequence->data[i]->NeighborRATRecord->data02.data[i0]->NumPLMNIDs_Present) {
						}
						if (sequence->data[i]->NeighborRATRecord->data02.data[i0]->PLMNID.data) {EDFree (sequence->data[i]->NeighborRATRecord->data02.data[i0]->PLMNID.data); sequence->data[i]->NeighborRATRecord->data02.data[i0]->PLMNID.data = NULL; sequence->data[i]->NeighborRATRecord->data02.data[i0]->PLMNID.allocatedItems=0; /*FR02A*/}
						EDFree (sequence->data[i]->NeighborRATRecord->data02.data[i0]);
						sequence->data[i]->NeighborRATRecord->data02.data[i0] = NULL;
					}
					if (sequence->data[i]->NeighborRATRecord->data02.data) {EDFree (sequence->data[i]->NeighborRATRecord->data02.data); sequence->data[i]->NeighborRATRecord->data02.data = NULL; sequence->data[i]->NeighborRATRecord->data02.allocatedItems=0; /*FR02A*/}
					if (sequence->data[i]->NeighborRATRecord->ServingNetworkPLMNIncl_Present) {
					}
					if (sequence->data[i]->NeighborRATRecord->NumServingPLMNIDs_Present) {
					}
					if (sequence->data[i]->NeighborRATRecord->S_PLMNID.data) {EDFree (sequence->data[i]->NeighborRATRecord->S_PLMNID.data); sequence->data[i]->NeighborRATRecord->S_PLMNID.data = NULL; sequence->data[i]->NeighborRATRecord->S_PLMNID.allocatedItems=0; /*FR02A*/}
					if (sequence->data[i]->NeighborRATRecord->RSRQParametersIncluded_Present) {
					}
					if (sequence->data[i]->NeighborRATRecord->QualMinEUTRACommon_Present) {
					}
					if (sequence->data[i]->NeighborRATRecord->QualMinEUTRAOffsetCommonInc_Present) {
					}
					if (sequence->data[i]->NeighborRATRecord->QualMinEUTRAOffsetCommon_Present) {
					}
					for (i0=0; i0<sequence->data[i]->NeighborRATRecord->data05.items; i0++) {
						if (sequence->data[i]->NeighborRATRecord->data05.data[i0]->ThreshXQ_Present) {
						}
						if (sequence->data[i]->NeighborRATRecord->data05.data[i0]->QualMinEUTRA_Present) {
						}
						if (sequence->data[i]->NeighborRATRecord->data05.data[i0]->QualMinEUTRAOffsetIncl_Present) {
						}
						if (sequence->data[i]->NeighborRATRecord->data05.data[i0]->QualMinEUTRAOffset_Present) {
						}
						EDFree (sequence->data[i]->NeighborRATRecord->data05.data[i0]);
						sequence->data[i]->NeighborRATRecord->data05.data[i0] = NULL;
					}
					if (sequence->data[i]->NeighborRATRecord->data05.data) {EDFree (sequence->data[i]->NeighborRATRecord->data05.data); sequence->data[i]->NeighborRATRecord->data05.data = NULL; sequence->data[i]->NeighborRATRecord->data05.allocatedItems=0; /*FR02A*/}
					EDFree (sequence->data[i]->NeighborRATRecord);
					sequence->data[i]->NeighborRATRecord = NULL;
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data */
void FREE_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	if (sp->OtherNeighborRATRecord_Present) {
		if (sp->OtherNeighborRATRecord->value != NULL) {
			EDFree (sp->OtherNeighborRATRecord->value);
			sp->OtherNeighborRATRecord->value = NULL;
		}
		sp->OtherNeighborRATRecord->usedBits = 0;
		EDFree (sp->OtherNeighborRATRecord);
		sp->OtherNeighborRATRecord_Present = ED_FALSE;
	}
	if (sp->NeighborRATRecord_Present) {
		if (sp->NeighborRATRecord->ServingPriority_Present) {
		}
		if (sp->NeighborRATRecord->RxLevMinEUTRACommon_Present) {
		}
		if (sp->NeighborRATRecord->PEMaxCommon_Present) {
		}
		if (sp->NeighborRATRecord->RxLevMinEUTRAOffsetCommonIncl_Present) {
		}
		if (sp->NeighborRATRecord->RxLevMinEUTRAOffsetCommon_Present) {
		}
		if (sp->NeighborRATRecord->MaxReselectionTimer_Present) {
		}
		if (sp->NeighborRATRecord->MinMeasurementBackoff_Present) {
		}
		if (sp->NeighborRATRecord->MaxMeasurementBackoff_Present) {
		}
		for (i0=0; i0<sp->NeighborRATRecord->data02.items; i0++) {
			if (sp->NeighborRATRecord->data02.data[i0]->EARFCNPriority_Present) {
			}
			if (sp->NeighborRATRecord->data02.data[i0]->RxLevMinEUTRA_Present) {
			}
			if (sp->NeighborRATRecord->data02.data[i0]->PEMax_Present) {
			}
			if (sp->NeighborRATRecord->data02.data[i0]->RxLevMinEUTRAOffsetIncl_Present) {
			}
			if (sp->NeighborRATRecord->data02.data[i0]->RxLevMinEUTRAOffset_Present) {
			}
			if (sp->NeighborRATRecord->data02.data[i0]->PLMNSameAsPreviousChannel_Present) {
			}
			if (sp->NeighborRATRecord->data02.data[i0]->NumPLMNIDs_Present) {
			}
			if (sp->NeighborRATRecord->data02.data[i0]->PLMNID.data) {EDFree (sp->NeighborRATRecord->data02.data[i0]->PLMNID.data); sp->NeighborRATRecord->data02.data[i0]->PLMNID.data = NULL; sp->NeighborRATRecord->data02.data[i0]->PLMNID.allocatedItems=0; /*FR02A*/}
			EDFree (sp->NeighborRATRecord->data02.data[i0]);
			sp->NeighborRATRecord->data02.data[i0] = NULL;
		}
		if (sp->NeighborRATRecord->data02.data) {EDFree (sp->NeighborRATRecord->data02.data); sp->NeighborRATRecord->data02.data = NULL; sp->NeighborRATRecord->data02.allocatedItems=0; /*FR02A*/}
		if (sp->NeighborRATRecord->ServingNetworkPLMNIncl_Present) {
		}
		if (sp->NeighborRATRecord->NumServingPLMNIDs_Present) {
		}
		if (sp->NeighborRATRecord->S_PLMNID.data) {EDFree (sp->NeighborRATRecord->S_PLMNID.data); sp->NeighborRATRecord->S_PLMNID.data = NULL; sp->NeighborRATRecord->S_PLMNID.allocatedItems=0; /*FR02A*/}
		if (sp->NeighborRATRecord->RSRQParametersIncluded_Present) {
		}
		if (sp->NeighborRATRecord->QualMinEUTRACommon_Present) {
		}
		if (sp->NeighborRATRecord->QualMinEUTRAOffsetCommonInc_Present) {
		}
		if (sp->NeighborRATRecord->QualMinEUTRAOffsetCommon_Present) {
		}
		for (i0=0; i0<sp->NeighborRATRecord->data05.items; i0++) {
			if (sp->NeighborRATRecord->data05.data[i0]->ThreshXQ_Present) {
			}
			if (sp->NeighborRATRecord->data05.data[i0]->QualMinEUTRA_Present) {
			}
			if (sp->NeighborRATRecord->data05.data[i0]->QualMinEUTRAOffsetIncl_Present) {
			}
			if (sp->NeighborRATRecord->data05.data[i0]->QualMinEUTRAOffset_Present) {
			}
			EDFree (sp->NeighborRATRecord->data05.data[i0]);
			sp->NeighborRATRecord->data05.data[i0] = NULL;
		}
		if (sp->NeighborRATRecord->data05.data) {EDFree (sp->NeighborRATRecord->data05.data); sp->NeighborRATRecord->data05.data = NULL; sp->NeighborRATRecord->data05.allocatedItems=0; /*FR02A*/}
		EDFree (sp->NeighborRATRecord);
		sp->NeighborRATRecord = NULL;
		sp->NeighborRATRecord_Present = ED_FALSE;
	}

}

void SETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_OtherNeighborRATRecord (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->OtherNeighborRATRecord_Present == present) return;
	sp->OtherNeighborRATRecord_Present = present;
	if (present) {
		/*-->*/sp->OtherNeighborRATRecord = (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_OtherNeighborRATRecord*)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_OtherNeighborRATRecord));
		sp->OtherNeighborRATRecord->value = NULL;
		sp->OtherNeighborRATRecord->usedBits = 0;
	} else {
		if (sp->OtherNeighborRATRecord->value != NULL) {
			EDFree (sp->OtherNeighborRATRecord->value);
			sp->OtherNeighborRATRecord->value = NULL;
		}
		sp->OtherNeighborRATRecord->usedBits = 0;
		EDFree (sp->OtherNeighborRATRecord);
	}
}

void SETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data* sp, ED_BOOLEAN present)
{
		int i0;
/* Do nothing if already compliant to the request */
	if (sp->NeighborRATRecord_Present == present) return;
	sp->NeighborRATRecord_Present = present;
	if (present) {
		/*-->*/sp->NeighborRATRecord = (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord*)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord));
		ED_RESET_MEM (sp->NeighborRATRecord, sizeof (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord));
		(sp->NeighborRATRecord->PriorityIncluded) = 0;
		(sp->NeighborRATRecord->ThreshServing) = 0;
		(sp->NeighborRATRecord->PerEARFCNParamsIncluded) = 0;
		(sp->NeighborRATRecord->MaxReselectionTimerIncluded) = 0;
		(sp->NeighborRATRecord->SearchBackOffTimerIncluded) = 0;
		(sp->NeighborRATRecord->PLMNIDIncluded) = 0;
		(sp->NeighborRATRecord->NumEUTRAFrequencies) = 0;
		sp->NeighborRATRecord->data02.items = 0;
		sp->NeighborRATRecord->S_PLMNID.items = 0;
		sp->NeighborRATRecord->data05.items = 0;
	} else {
		if (sp->NeighborRATRecord->ServingPriority_Present) {
		}
		if (sp->NeighborRATRecord->RxLevMinEUTRACommon_Present) {
		}
		if (sp->NeighborRATRecord->PEMaxCommon_Present) {
		}
		if (sp->NeighborRATRecord->RxLevMinEUTRAOffsetCommonIncl_Present) {
		}
		if (sp->NeighborRATRecord->RxLevMinEUTRAOffsetCommon_Present) {
		}
		if (sp->NeighborRATRecord->MaxReselectionTimer_Present) {
		}
		if (sp->NeighborRATRecord->MinMeasurementBackoff_Present) {
		}
		if (sp->NeighborRATRecord->MaxMeasurementBackoff_Present) {
		}
		for (i0=0; i0<sp->NeighborRATRecord->data02.items; i0++) {
			if (sp->NeighborRATRecord->data02.data[i0]->EARFCNPriority_Present) {
			}
			if (sp->NeighborRATRecord->data02.data[i0]->RxLevMinEUTRA_Present) {
			}
			if (sp->NeighborRATRecord->data02.data[i0]->PEMax_Present) {
			}
			if (sp->NeighborRATRecord->data02.data[i0]->RxLevMinEUTRAOffsetIncl_Present) {
			}
			if (sp->NeighborRATRecord->data02.data[i0]->RxLevMinEUTRAOffset_Present) {
			}
			if (sp->NeighborRATRecord->data02.data[i0]->PLMNSameAsPreviousChannel_Present) {
			}
			if (sp->NeighborRATRecord->data02.data[i0]->NumPLMNIDs_Present) {
			}
			if (sp->NeighborRATRecord->data02.data[i0]->PLMNID.data) {EDFree (sp->NeighborRATRecord->data02.data[i0]->PLMNID.data); sp->NeighborRATRecord->data02.data[i0]->PLMNID.data = NULL; sp->NeighborRATRecord->data02.data[i0]->PLMNID.allocatedItems=0; /*FR02A*/}
			EDFree (sp->NeighborRATRecord->data02.data[i0]);
			sp->NeighborRATRecord->data02.data[i0] = NULL;
		}
		if (sp->NeighborRATRecord->data02.data) {EDFree (sp->NeighborRATRecord->data02.data); sp->NeighborRATRecord->data02.data = NULL; sp->NeighborRATRecord->data02.allocatedItems=0; /*FR02A*/}
		if (sp->NeighborRATRecord->ServingNetworkPLMNIncl_Present) {
		}
		if (sp->NeighborRATRecord->NumServingPLMNIDs_Present) {
		}
		if (sp->NeighborRATRecord->S_PLMNID.data) {EDFree (sp->NeighborRATRecord->S_PLMNID.data); sp->NeighborRATRecord->S_PLMNID.data = NULL; sp->NeighborRATRecord->S_PLMNID.allocatedItems=0; /*FR02A*/}
		if (sp->NeighborRATRecord->RSRQParametersIncluded_Present) {
		}
		if (sp->NeighborRATRecord->QualMinEUTRACommon_Present) {
		}
		if (sp->NeighborRATRecord->QualMinEUTRAOffsetCommonInc_Present) {
		}
		if (sp->NeighborRATRecord->QualMinEUTRAOffsetCommon_Present) {
		}
		for (i0=0; i0<sp->NeighborRATRecord->data05.items; i0++) {
			if (sp->NeighborRATRecord->data05.data[i0]->ThreshXQ_Present) {
			}
			if (sp->NeighborRATRecord->data05.data[i0]->QualMinEUTRA_Present) {
			}
			if (sp->NeighborRATRecord->data05.data[i0]->QualMinEUTRAOffsetIncl_Present) {
			}
			if (sp->NeighborRATRecord->data05.data[i0]->QualMinEUTRAOffset_Present) {
			}
			EDFree (sp->NeighborRATRecord->data05.data[i0]);
			sp->NeighborRATRecord->data05.data[i0] = NULL;
		}
		if (sp->NeighborRATRecord->data05.data) {EDFree (sp->NeighborRATRecord->data05.data); sp->NeighborRATRecord->data05.data = NULL; sp->NeighborRATRecord->data05.allocatedItems=0; /*FR02A*/}
		EDFree (sp->NeighborRATRecord);
		sp->NeighborRATRecord = NULL;
	}
}

/* Free function for struct c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord */
void FREE_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data02.items; i0++) {
		if (sp->data02.data[i0]->EARFCNPriority_Present) {
		}
		if (sp->data02.data[i0]->RxLevMinEUTRA_Present) {
		}
		if (sp->data02.data[i0]->PEMax_Present) {
		}
		if (sp->data02.data[i0]->RxLevMinEUTRAOffsetIncl_Present) {
		}
		if (sp->data02.data[i0]->RxLevMinEUTRAOffset_Present) {
		}
		if (sp->data02.data[i0]->PLMNSameAsPreviousChannel_Present) {
		}
		if (sp->data02.data[i0]->NumPLMNIDs_Present) {
		}
		if (sp->data02.data[i0]->PLMNID.data) {EDFree (sp->data02.data[i0]->PLMNID.data); sp->data02.data[i0]->PLMNID.data = NULL; sp->data02.data[i0]->PLMNID.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data02.data[i0]);
		sp->data02.data[i0] = NULL;
	}
	if (sp->data02.data) {EDFree (sp->data02.data); sp->data02.data = NULL; sp->data02.allocatedItems=0; /*FR02A*/}
	if (sp->S_PLMNID.data) {EDFree (sp->S_PLMNID.data); sp->S_PLMNID.data = NULL; sp->S_PLMNID.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data05.items; i0++) {
		if (sp->data05.data[i0]->ThreshXQ_Present) {
		}
		if (sp->data05.data[i0]->QualMinEUTRA_Present) {
		}
		if (sp->data05.data[i0]->QualMinEUTRAOffsetIncl_Present) {
		}
		if (sp->data05.data[i0]->QualMinEUTRAOffset_Present) {
		}
		EDFree (sp->data05.data[i0]);
		sp->data05.data[i0] = NULL;
	}
	if (sp->data05.data) {EDFree (sp->data05.data); sp->data05.data = NULL; sp->data05.allocatedItems=0; /*FR02A*/}

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02 (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data** tmp;
		tmp = (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data**)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data*)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data));
			(sequence->data[i]->EARFCN) = 0;
			(sequence->data[i]->ThreshX) = 0;
			(sequence->data[i]->MeasurementBandwidth) = 0;
			sequence->data[i]->PLMNID.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->EARFCNPriority_Present) {
				}
				if (sequence->data[i]->RxLevMinEUTRA_Present) {
				}
				if (sequence->data[i]->PEMax_Present) {
				}
				if (sequence->data[i]->RxLevMinEUTRAOffsetIncl_Present) {
				}
				if (sequence->data[i]->RxLevMinEUTRAOffset_Present) {
				}
				if (sequence->data[i]->PLMNSameAsPreviousChannel_Present) {
				}
				if (sequence->data[i]->NumPLMNIDs_Present) {
				}
				if (sequence->data[i]->PLMNID.data) {EDFree (sequence->data[i]->PLMNID.data); sequence->data[i]->PLMNID.data = NULL; sequence->data[i]->PLMNID.allocatedItems=0; /*FR02A*/}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data */
void FREE_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->PLMNID.data) {EDFree (sp->PLMNID.data); sp->PLMNID.data = NULL; sp->PLMNID.allocatedItems=0; /*FR02A*/}

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID* sequence, int desiredItems)
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

/* SETITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID* sequence, int desiredItems)
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

/* SETITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05 (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data** tmp;
		tmp = (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data**)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data*)EDAlloc (sizeof (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->ThreshXQ_Present) {
				}
				if (sequence->data[i]->QualMinEUTRA_Present) {
				}
				if (sequence->data[i]->QualMinEUTRAOffsetIncl_Present) {
				}
				if (sequence->data[i]->QualMinEUTRAOffset_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data */
void FREE_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01 (c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01_data** tmp;
		tmp = (c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01_data));
			(sequence->data[i]->AttributeLength) = 0;
			INIT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01_data */
void FREE_c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01_data (c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->AttributeRecord));

}

/* SETITEMS commands for type 'c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01 (c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01_data** tmp;
		tmp = (c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01_data));
			(sequence->data[i]->AttributeLength) = 0;
			INIT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01_data */
void FREE_c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01_data (c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->AttributeRecord));

}

/* SETITEMS commands for type 'c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01 (c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01_data));
			(sequence->data[i]->AttributeLength) = 0;
			INIT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01_data */
void FREE_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01_data (c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->AttributeRecord));

}

/* SETITEMS commands for type 'c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01 (c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01_data));
			(sequence->data[i]->AttributeLength) = 0;
			INIT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01_data */
void FREE_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01_data (c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->AttributeRecord));

}

/* SETITEMS commands for type 'c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01 (c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data));
			(sequence->data[i]->PreferredChannel.SystemType) = 0;
			(sequence->data[i]->PreferredChannel.BandClass) = 0;
			(sequence->data[i]->PreferredChannel.ChannelNumber) = 0;
			
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

/* Free function for struct c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data */
void FREE_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data (c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel */
void FREE_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel (c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01 (c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01_data));
			(sequence->data[i]->QuickPageIndicator) = 0;
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

/* Free function for struct c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01_data */
void FREE_c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01_data (c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01 (c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01_data));
			(sequence->data[i]->AttributeLength) = 0;
			INIT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01_data */
void FREE_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01_data (c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->AttributeRecord));

}

/* SETITEMS commands for type 'c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01 (c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01_data** tmp;
		tmp = (c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01_data));
			(sequence->data[i]->AttributeLength) = 0;
			INIT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01_data */
void FREE_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01_data (c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->AttributeRecord));

}

/* SETITEMS commands for type 'c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01 (c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01_data** tmp;
		tmp = (c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01_data));
			(sequence->data[i]->AttributeLength) = 0;
			INIT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01_data */
void FREE_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01_data (c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->AttributeRecord));

}

/* SETITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01 (c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data** tmp;
		tmp = (c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data));
			(sequence->data[i]->PilotPNPhase) = 0;
			(sequence->data[i]->ChannelIncluded) = 0;
			(sequence->data[i]->PilotStrength) = 0;
			(sequence->data[i]->Keep) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->Channel_Present) {
					EDFree (sequence->data[i]->Channel);
					sequence->data[i]->Channel = NULL;
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data */
void FREE_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data (c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->Channel_Present) {
		EDFree (sp->Channel);
		sp->Channel = NULL;
		sp->Channel_Present = ED_FALSE;
	}

}

void SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel (c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->Channel_Present == present) return;
	sp->Channel_Present = present;
	if (present) {
		/*-->*/sp->Channel = (c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel));
		ED_RESET_MEM (sp->Channel, sizeof (c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel));
		(sp->Channel->SystemType) = 0;
		(sp->Channel->BandClass) = 0;
		(sp->Channel->ChannelNumber) = 0;
	} else {
		EDFree (sp->Channel);
		sp->Channel = NULL;
	}
}

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel */
void FREE_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel (c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel */
void FREE_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel (c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01 (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data** tmp;
		tmp = (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data));
			(sequence->data[i]->RAChannelGain) = 0;
			(sequence->data[i]->PilotPN) = 0;
			(sequence->data[i]->DRCCover) = 0;
			(sequence->data[i]->SofterHandoff) = 0;
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

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data */
void FREE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02'. Existing items are not changed. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02 (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data** tmp;
		tmp = (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data**)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data));
			(sequence->data[i]->DSC) = 0;
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

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data */
void FREE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03'. Existing items are not changed. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03 (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03* sequence, int desiredItems)
{
	int i, i0, i1;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data** tmp;
		tmp = (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data**)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data));
			sequence->data[i]->data04.items = 0;
			(sequence->data[i]->FeedbackEnabled) = 0;
			(sequence->data[i]->SubActiveSetCarriesControlChannel) = 0;
			(sequence->data[i]->ThisSubActiveSetNotReportable) = 0;
			(sequence->data[i]->NumReverseChannelsIncluded) = 0;
			sequence->data[i]->data05.items = 0;
			sequence->data[i]->data06.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->NumFwdChannelsThisSubActiveSet_Present) {
				}
				for (i0=0; i0<sequence->data[i]->data04.items; i0++) {
					if (sequence->data[i]->data04.data[i0]->AssignedChannel_Present) {
						EDFree (sequence->data[i]->data04.data[i0]->AssignedChannel);
						sequence->data[i]->data04.data[i0]->AssignedChannel = NULL;
					}
					EDFree (sequence->data[i]->data04.data[i0]);
					sequence->data[i]->data04.data[i0] = NULL;
				}
				if (sequence->data[i]->data04.data) {EDFree (sequence->data[i]->data04.data); sequence->data[i]->data04.data = NULL; sequence->data[i]->data04.allocatedItems=0; /*FR02A*/}
				if (sequence->data[i]->FeedbackMultiplexingIndex_Present) {
				}
				if (sequence->data[i]->FeedbackReverseChannelIndex_Present) {
				}
				if (sequence->data[i]->DSCForThisSubActiveSetEnabled_Present) {
				}
				if (sequence->data[i]->Next3FieldsSameAsBefore_Present) {
				}
				if (sequence->data[i]->DRCLength_Present) {
				}
				if (sequence->data[i]->DRCChannelGainBase_Present) {
				}
				if (sequence->data[i]->ACKChannelGain_Present) {
				}
				if (sequence->data[i]->NumReverseChannels_Present) {
				}
				for (i0=0; i0<sequence->data[i]->data05.items; i0++) {
					if (sequence->data[i]->data05.data[i0]->ReverseBandClass_Present) {
					}
					if (sequence->data[i]->data05.data[i0]->ReverseChannelNumber_Present) {
					}
					if (sequence->data[i]->data05.data[i0]->ReverseChannelDroppingRank_Present) {
					}
					EDFree (sequence->data[i]->data05.data[i0]);
					sequence->data[i]->data05.data[i0] = NULL;
				}
				if (sequence->data[i]->data05.data) {EDFree (sequence->data[i]->data05.data); sequence->data[i]->data05.data = NULL; sequence->data[i]->data05.allocatedItems=0; /*FR02A*/}
				for (i0=0; i0<sequence->data[i]->data06.items; i0++) {
					if (sequence->data[i]->data06.data[i0]->ForwardChannelIndexThisPilot_Present) {
					}
					if (sequence->data[i]->data06.data[i0]->PilotGroupID_Present) {
					}
					if (sequence->data[i]->data06.data[i0]->NumUniqueForwardTrafficMACIndices_Present) {
					}
					if (sequence->data[i]->data06.data[i0]->SchedulerTag_Present) {
					}
					if (sequence->data[i]->data06.data[i0]->AuxDRCCoverIncluded_Present) {
					}
					if (sequence->data[i]->data06.data[i0]->AuxDRCCover_Present) {
					}
					if (sequence->data[i]->data06.data[i0]->ForwardTrafficMACIndexPerInterlaceEnabled_Present) {
					}
					for (i1=0; i1<sequence->data[i]->data06.data[i0]->data07.items; i1++) {
						if (sequence->data[i]->data06.data[i0]->data07.data[i1]->AssignedInterlaces_Present) {
						}
						EDFree (sequence->data[i]->data06.data[i0]->data07.data[i1]);
						sequence->data[i]->data06.data[i0]->data07.data[i1] = NULL;
					}
					if (sequence->data[i]->data06.data[i0]->data07.data) {EDFree (sequence->data[i]->data06.data[i0]->data07.data); sequence->data[i]->data06.data[i0]->data07.data = NULL; sequence->data[i]->data06.data[i0]->data07.allocatedItems=0; /*FR02A*/}
					for (i1=0; i1<sequence->data[i]->data06.data[i0]->data08.items; i1++) {
						if (sequence->data[i]->data06.data[i0]->data08.data[i1]->ReverseLinkMACIndex_Present) {
						}
						if (sequence->data[i]->data06.data[i0]->data08.data[i1]->RABMACIndex_Present) {
						}
						if (sequence->data[i]->data06.data[i0]->data08.data[i1]->DeltaT2P_Present) {
						}
						EDFree (sequence->data[i]->data06.data[i0]->data08.data[i1]);
						sequence->data[i]->data06.data[i0]->data08.data[i1] = NULL;
					}
					if (sequence->data[i]->data06.data[i0]->data08.data) {EDFree (sequence->data[i]->data06.data[i0]->data08.data); sequence->data[i]->data06.data[i0]->data08.data = NULL; sequence->data[i]->data06.data[i0]->data08.allocatedItems=0; /*FR02A*/}
					EDFree (sequence->data[i]->data06.data[i0]);
					sequence->data[i]->data06.data[i0] = NULL;
				}
				if (sequence->data[i]->data06.data) {EDFree (sequence->data[i]->data06.data); sequence->data[i]->data06.data = NULL; sequence->data[i]->data06.allocatedItems=0; /*FR02A*/}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data */
void FREE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data* sp) {
	int i0;
	int i1;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data04.items; i0++) {
		if (sp->data04.data[i0]->AssignedChannel_Present) {
			EDFree (sp->data04.data[i0]->AssignedChannel);
			sp->data04.data[i0]->AssignedChannel = NULL;
		}
		EDFree (sp->data04.data[i0]);
		sp->data04.data[i0] = NULL;
	}
	if (sp->data04.data) {EDFree (sp->data04.data); sp->data04.data = NULL; sp->data04.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data05.items; i0++) {
		if (sp->data05.data[i0]->ReverseBandClass_Present) {
		}
		if (sp->data05.data[i0]->ReverseChannelNumber_Present) {
		}
		if (sp->data05.data[i0]->ReverseChannelDroppingRank_Present) {
		}
		EDFree (sp->data05.data[i0]);
		sp->data05.data[i0] = NULL;
	}
	if (sp->data05.data) {EDFree (sp->data05.data); sp->data05.data = NULL; sp->data05.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data06.items; i0++) {
		if (sp->data06.data[i0]->ForwardChannelIndexThisPilot_Present) {
		}
		if (sp->data06.data[i0]->PilotGroupID_Present) {
		}
		if (sp->data06.data[i0]->NumUniqueForwardTrafficMACIndices_Present) {
		}
		if (sp->data06.data[i0]->SchedulerTag_Present) {
		}
		if (sp->data06.data[i0]->AuxDRCCoverIncluded_Present) {
		}
		if (sp->data06.data[i0]->AuxDRCCover_Present) {
		}
		if (sp->data06.data[i0]->ForwardTrafficMACIndexPerInterlaceEnabled_Present) {
		}
		for (i1=0; i1<sp->data06.data[i0]->data07.items; i1++) {
			if (sp->data06.data[i0]->data07.data[i1]->AssignedInterlaces_Present) {
			}
			EDFree (sp->data06.data[i0]->data07.data[i1]);
			sp->data06.data[i0]->data07.data[i1] = NULL;
		}
		if (sp->data06.data[i0]->data07.data) {EDFree (sp->data06.data[i0]->data07.data); sp->data06.data[i0]->data07.data = NULL; sp->data06.data[i0]->data07.allocatedItems=0; /*FR02A*/}
		for (i1=0; i1<sp->data06.data[i0]->data08.items; i1++) {
			if (sp->data06.data[i0]->data08.data[i1]->ReverseLinkMACIndex_Present) {
			}
			if (sp->data06.data[i0]->data08.data[i1]->RABMACIndex_Present) {
			}
			if (sp->data06.data[i0]->data08.data[i1]->DeltaT2P_Present) {
			}
			EDFree (sp->data06.data[i0]->data08.data[i1]);
			sp->data06.data[i0]->data08.data[i1] = NULL;
		}
		if (sp->data06.data[i0]->data08.data) {EDFree (sp->data06.data[i0]->data08.data); sp->data06.data[i0]->data08.data = NULL; sp->data06.data[i0]->data08.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data06.data[i0]);
		sp->data06.data[i0] = NULL;
	}
	if (sp->data06.data) {EDFree (sp->data06.data); sp->data06.data = NULL; sp->data06.allocatedItems=0; /*FR02A*/}

}

/* SETITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04'. Existing items are not changed. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04 (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data** tmp;
		tmp = (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data**)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->AssignedChannel_Present) {
					EDFree (sequence->data[i]->AssignedChannel);
					sequence->data[i]->AssignedChannel = NULL;
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data */
void FREE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->AssignedChannel_Present) {
		EDFree (sp->AssignedChannel);
		sp->AssignedChannel = NULL;
		sp->AssignedChannel_Present = ED_FALSE;
	}

}

void SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data_AssignedChannel (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->AssignedChannel_Present == present) return;
	sp->AssignedChannel_Present = present;
	if (present) {
		/*-->*/sp->AssignedChannel = (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data_AssignedChannel*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data_AssignedChannel));
		ED_RESET_MEM (sp->AssignedChannel, sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data_AssignedChannel));
		(sp->AssignedChannel->SystemType) = 0;
		(sp->AssignedChannel->BandClass) = 0;
		(sp->AssignedChannel->ChannelNumber) = 0;
	} else {
		EDFree (sp->AssignedChannel);
		sp->AssignedChannel = NULL;
	}
}

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data_AssignedChannel */
void FREE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data_AssignedChannel (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data_AssignedChannel* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05'. Existing items are not changed. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05 (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data** tmp;
		tmp = (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data**)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data));
			(sequence->data[i]->ReverseChannelConfiguration) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->ReverseBandClass_Present) {
				}
				if (sequence->data[i]->ReverseChannelNumber_Present) {
				}
				if (sequence->data[i]->ReverseChannelDroppingRank_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data */
void FREE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06'. Existing items are not changed. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06 (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06* sequence, int desiredItems)
{
	int i, i0;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data** tmp;
		tmp = (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data**)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data));
			(sequence->data[i]->PilotInThisSectorIncluded) = 0;
			sequence->data[i]->data07.items = 0;
			sequence->data[i]->data08.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->ForwardChannelIndexThisPilot_Present) {
				}
				if (sequence->data[i]->PilotGroupID_Present) {
				}
				if (sequence->data[i]->NumUniqueForwardTrafficMACIndices_Present) {
				}
				if (sequence->data[i]->SchedulerTag_Present) {
				}
				if (sequence->data[i]->AuxDRCCoverIncluded_Present) {
				}
				if (sequence->data[i]->AuxDRCCover_Present) {
				}
				if (sequence->data[i]->ForwardTrafficMACIndexPerInterlaceEnabled_Present) {
				}
				for (i0=0; i0<sequence->data[i]->data07.items; i0++) {
					if (sequence->data[i]->data07.data[i0]->AssignedInterlaces_Present) {
					}
					EDFree (sequence->data[i]->data07.data[i0]);
					sequence->data[i]->data07.data[i0] = NULL;
				}
				if (sequence->data[i]->data07.data) {EDFree (sequence->data[i]->data07.data); sequence->data[i]->data07.data = NULL; sequence->data[i]->data07.allocatedItems=0; /*FR02A*/}
				for (i0=0; i0<sequence->data[i]->data08.items; i0++) {
					if (sequence->data[i]->data08.data[i0]->ReverseLinkMACIndex_Present) {
					}
					if (sequence->data[i]->data08.data[i0]->RABMACIndex_Present) {
					}
					if (sequence->data[i]->data08.data[i0]->DeltaT2P_Present) {
					}
					EDFree (sequence->data[i]->data08.data[i0]);
					sequence->data[i]->data08.data[i0] = NULL;
				}
				if (sequence->data[i]->data08.data) {EDFree (sequence->data[i]->data08.data); sequence->data[i]->data08.data = NULL; sequence->data[i]->data08.allocatedItems=0; /*FR02A*/}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data */
void FREE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data07.items; i0++) {
		if (sp->data07.data[i0]->AssignedInterlaces_Present) {
		}
		EDFree (sp->data07.data[i0]);
		sp->data07.data[i0] = NULL;
	}
	if (sp->data07.data) {EDFree (sp->data07.data); sp->data07.data = NULL; sp->data07.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data08.items; i0++) {
		if (sp->data08.data[i0]->ReverseLinkMACIndex_Present) {
		}
		if (sp->data08.data[i0]->RABMACIndex_Present) {
		}
		if (sp->data08.data[i0]->DeltaT2P_Present) {
		}
		EDFree (sp->data08.data[i0]);
		sp->data08.data[i0] = NULL;
	}
	if (sp->data08.data) {EDFree (sp->data08.data); sp->data08.data = NULL; sp->data08.allocatedItems=0; /*FR02A*/}

}

/* SETITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07'. Existing items are not changed. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07 (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07_data** tmp;
		tmp = (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07_data**)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07_data*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07_data));
			(sequence->data[i]->ForwardTrafficMACIndex) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->AssignedInterlaces_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07_data */
void FREE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07_data (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08'. Existing items are not changed. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08 (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data** tmp;
		tmp = (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data**)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->ReverseLinkMACIndex_Present) {
				}
				if (sequence->data[i]->RABMACIndex_Present) {
				}
				if (sequence->data[i]->DeltaT2P_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data */
void FREE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01 (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01_data** tmp;
		tmp = (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01_data));
			(sequence->data[i]->PilotPN) = 0;
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

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01_data */
void FREE_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01_data (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02'. Existing items are not changed. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02 (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data** tmp;
		tmp = (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data**)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data));
			(sequence->data[i]->ChannelIncluded) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->Channel_Present) {
					EDFree (sequence->data[i]->Channel);
					sequence->data[i]->Channel = NULL;
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data */
void FREE_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->Channel_Present) {
		EDFree (sp->Channel);
		sp->Channel = NULL;
		sp->Channel_Present = ED_FALSE;
	}

}

void SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data_Channel (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->Channel_Present == present) return;
	sp->Channel_Present = present;
	if (present) {
		/*-->*/sp->Channel = (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data_Channel*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data_Channel));
		ED_RESET_MEM (sp->Channel, sizeof (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data_Channel));
		(sp->Channel->SystemType) = 0;
		(sp->Channel->BandClass) = 0;
		(sp->Channel->ChannelNumber) = 0;
	} else {
		EDFree (sp->Channel);
		sp->Channel = NULL;
	}
}

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data_Channel */
void FREE_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data_Channel (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data_Channel* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03'. Existing items are not changed. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03 (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03_data** tmp;
		tmp = (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03_data**)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03_data*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03_data));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->SearchWindowSize_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03_data */
void FREE_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03_data (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04'. Existing items are not changed. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04 (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04_data** tmp;
		tmp = (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04_data**)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04_data*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04_data));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->SearchWindowOffset_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04_data */
void FREE_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04_data (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05'. Existing items are not changed. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05 (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05_data** tmp;
		tmp = (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05_data**)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05_data*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05_data));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->FPDCHSupported_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05_data */
void FREE_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05_data (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06'. Existing items are not changed. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06 (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06_data** tmp;
		tmp = (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06_data**)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06_data*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06_data));
			(sequence->data[i]->PilotGroupIDIncluded) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->PilotGroupID_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06_data */
void FREE_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06_data (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_Channel */
void FREE_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_Channel (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_Channel* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01 (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data** tmp;
		tmp = (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data));
			(sequence->data[i]->SectorPilotPN) = 0;
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

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data */
void FREE_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02'. Existing items are not changed. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02 (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data** tmp;
		tmp = (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data**)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->SectorSearchWindowSize_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data */
void FREE_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03'. Existing items are not changed. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03 (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data** tmp;
		tmp = (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data**)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->SectorSearchWindowOffset_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data */
void FREE_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01 (c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data** tmp;
		tmp = (c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data));
			(sequence->data[i]->AttributeLength) = 0;
			INIT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data */
void FREE_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data (c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->AttributeRecord));

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01 (c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01_data));
			(sequence->data[i]->AttributeLength) = 0;
			INIT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01_data */
void FREE_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01_data (c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->AttributeRecord));

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01 (c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01_data));
			(sequence->data[i]->AttributeLength) = 0;
			INIT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sequence->data[i]->AttributeRecord));
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01_data */
void FREE_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01_data (c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B (&(sp->AttributeRecord));

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01 (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01_data));
			(sequence->data[i]->ForwardTrafficValid63To0) = 0;
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

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01_data */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01_data (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02 (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02_data** tmp;
		tmp = (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02_data**)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02_data*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02_data));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->ForwardTrafficValid127To64_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02_data */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02_data (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03 (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03_data** tmp;
		tmp = (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03_data**)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03_data*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03_data));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->ForwardTrafficValid130To383_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03_data */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03_data (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data));
			(sequence->data[i]->Channel.SystemType) = 0;
			(sequence->data[i]->Channel.BandClass) = 0;
			(sequence->data[i]->Channel.ChannelNumber) = 0;
			
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

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data_Channel */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data_Channel (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data_Channel* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02_data** tmp;
		tmp = (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02_data**)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02_data*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02_data));
			(sequence->data[i]->NeighborPilotPN) = 0;
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

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02_data */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02_data (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data** tmp;
		tmp = (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data**)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data));
			(sequence->data[i]->NeighborChannelIncluded) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->NeighborChannel_Present) {
					EDFree (sequence->data[i]->NeighborChannel);
					sequence->data[i]->NeighborChannel = NULL;
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->NeighborChannel_Present) {
		EDFree (sp->NeighborChannel);
		sp->NeighborChannel = NULL;
		sp->NeighborChannel_Present = ED_FALSE;
	}

}

void SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data_NeighborChannel (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->NeighborChannel_Present == present) return;
	sp->NeighborChannel_Present = present;
	if (present) {
		/*-->*/sp->NeighborChannel = (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data_NeighborChannel*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data_NeighborChannel));
		ED_RESET_MEM (sp->NeighborChannel, sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data_NeighborChannel));
		(sp->NeighborChannel->SystemType) = 0;
		(sp->NeighborChannel->BandClass) = 0;
		(sp->NeighborChannel->ChannelNumber) = 0;
	} else {
		EDFree (sp->NeighborChannel);
		sp->NeighborChannel = NULL;
	}
}

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data_NeighborChannel */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data_NeighborChannel (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data_NeighborChannel* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04_data** tmp;
		tmp = (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04_data**)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04_data*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04_data));
			(sequence->data[i]->NeighborSearchWindowSize) = 0;
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

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04_data */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04_data (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05_data** tmp;
		tmp = (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05_data**)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05_data*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05_data));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->NeighborSearchWindowOffset_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05_data */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05_data (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data** tmp;
		tmp = (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data**)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data));
			(sequence->data[i]->ExtendedChannel.SystemType) = 0;
			(sequence->data[i]->ExtendedChannel.BandClass) = 0;
			(sequence->data[i]->ExtendedChannel.ChannelNumber) = 0;
			
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

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data_ExtendedChannel */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data_ExtendedChannel (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data_ExtendedChannel* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data** tmp;
		tmp = (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data**)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data));
			(sequence->data[i]->AccessHashingChannelMaskSameAsPrevious) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->AccessHashingChannelMask_Present) {
					if (sequence->data[i]->AccessHashingChannelMask->value != NULL) {
						EDFree (sequence->data[i]->AccessHashingChannelMask->value);
						sequence->data[i]->AccessHashingChannelMask->value = NULL;
					}
					sequence->data[i]->AccessHashingChannelMask->usedBits = 0;
					EDFree (sequence->data[i]->AccessHashingChannelMask);
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->AccessHashingChannelMask_Present) {
		if (sp->AccessHashingChannelMask->value != NULL) {
			EDFree (sp->AccessHashingChannelMask->value);
			sp->AccessHashingChannelMask->value = NULL;
		}
		sp->AccessHashingChannelMask->usedBits = 0;
		EDFree (sp->AccessHashingChannelMask);
		sp->AccessHashingChannelMask_Present = ED_FALSE;
	}

}

void SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data_AccessHashingChannelMask (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->AccessHashingChannelMask_Present == present) return;
	sp->AccessHashingChannelMask_Present = present;
	if (present) {
		/*-->*/sp->AccessHashingChannelMask = (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data_AccessHashingChannelMask*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data_AccessHashingChannelMask));
		sp->AccessHashingChannelMask->value = NULL;
		sp->AccessHashingChannelMask->usedBits = 0;
	} else {
		if (sp->AccessHashingChannelMask->value != NULL) {
			EDFree (sp->AccessHashingChannelMask->value);
			sp->AccessHashingChannelMask->value = NULL;
		}
		sp->AccessHashingChannelMask->usedBits = 0;
		EDFree (sp->AccessHashingChannelMask);
	}
}

/* SETITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08_data** tmp;
		tmp = (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08_data**)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08_data*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08_data));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->FPDCHSupported_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08_data */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08_data (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09_data** tmp;
		tmp = (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09_data**)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09_data*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09_data));
			(sequence->data[i]->SecondaryColorCode) = 0;
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

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09_data */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09_data (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10_data** tmp;
		tmp = (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10_data**)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10_data*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10_data));
			(sequence->data[i]->PilotGroupIDIncluded) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->PilotGroupID_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10_data */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10_data (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11_data** tmp;
		tmp = (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11_data**)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11_data*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11_data));
			(sequence->data[i]->ReverseBandClass) = 0;
			(sequence->data[i]->ReverseChannelNumber) = 0;
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

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11_data */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11_data (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01 (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01* sequence, int desiredItems)
{
	int i, i0;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data));
			(sequence->data[i]->RATType) = 0;
			(sequence->data[i]->NeighborRATRecordLength) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->OtherNeighborRATRecord_Present) {
					if (sequence->data[i]->OtherNeighborRATRecord->value != NULL) {
						EDFree (sequence->data[i]->OtherNeighborRATRecord->value);
						sequence->data[i]->OtherNeighborRATRecord->value = NULL;
					}
					sequence->data[i]->OtherNeighborRATRecord->usedBits = 0;
					EDFree (sequence->data[i]->OtherNeighborRATRecord);
				}
				if (sequence->data[i]->NeighborRATRecord_Present) {
					if (sequence->data[i]->NeighborRATRecord->ServingPriority_Present) {
					}
					if (sequence->data[i]->NeighborRATRecord->RxLevMinEUTRACommon_Present) {
					}
					if (sequence->data[i]->NeighborRATRecord->PEMaxCommon_Present) {
					}
					if (sequence->data[i]->NeighborRATRecord->RxLevMinEUTRAOffsetCommonIncl_Present) {
					}
					if (sequence->data[i]->NeighborRATRecord->RxLevMinEUTRAOffsetCommon_Present) {
					}
					if (sequence->data[i]->NeighborRATRecord->MaxReselectionTimer_Present) {
					}
					if (sequence->data[i]->NeighborRATRecord->MinMeasurementBackoff_Present) {
					}
					if (sequence->data[i]->NeighborRATRecord->MaxMeasurementBackoff_Present) {
					}
					for (i0=0; i0<sequence->data[i]->NeighborRATRecord->data02.items; i0++) {
						if (sequence->data[i]->NeighborRATRecord->data02.data[i0]->EARFCNPriority_Present) {
						}
						if (sequence->data[i]->NeighborRATRecord->data02.data[i0]->RxLevMinEUTRA_Present) {
						}
						if (sequence->data[i]->NeighborRATRecord->data02.data[i0]->PEMax_Present) {
						}
						if (sequence->data[i]->NeighborRATRecord->data02.data[i0]->RxLevMinEUTRAOffsetIncl_Present) {
						}
						if (sequence->data[i]->NeighborRATRecord->data02.data[i0]->RxLevMinEUTRAOffset_Present) {
						}
						if (sequence->data[i]->NeighborRATRecord->data02.data[i0]->PLMNSameAsPreviousChannel_Present) {
						}
						if (sequence->data[i]->NeighborRATRecord->data02.data[i0]->NumPLMNIDs_Present) {
						}
						if (sequence->data[i]->NeighborRATRecord->data02.data[i0]->PLMNID.data) {EDFree (sequence->data[i]->NeighborRATRecord->data02.data[i0]->PLMNID.data); sequence->data[i]->NeighborRATRecord->data02.data[i0]->PLMNID.data = NULL; sequence->data[i]->NeighborRATRecord->data02.data[i0]->PLMNID.allocatedItems=0; /*FR02A*/}
						EDFree (sequence->data[i]->NeighborRATRecord->data02.data[i0]);
						sequence->data[i]->NeighborRATRecord->data02.data[i0] = NULL;
					}
					if (sequence->data[i]->NeighborRATRecord->data02.data) {EDFree (sequence->data[i]->NeighborRATRecord->data02.data); sequence->data[i]->NeighborRATRecord->data02.data = NULL; sequence->data[i]->NeighborRATRecord->data02.allocatedItems=0; /*FR02A*/}
					if (sequence->data[i]->NeighborRATRecord->ServingNetworkPLMNIncl_Present) {
					}
					if (sequence->data[i]->NeighborRATRecord->NumServingPLMNIDs_Present) {
					}
					if (sequence->data[i]->NeighborRATRecord->S_PLMNID.data) {EDFree (sequence->data[i]->NeighborRATRecord->S_PLMNID.data); sequence->data[i]->NeighborRATRecord->S_PLMNID.data = NULL; sequence->data[i]->NeighborRATRecord->S_PLMNID.allocatedItems=0; /*FR02A*/}
					if (sequence->data[i]->NeighborRATRecord->RSRQParametersIncluded_Present) {
					}
					if (sequence->data[i]->NeighborRATRecord->QualMinEUTRACommon_Present) {
					}
					if (sequence->data[i]->NeighborRATRecord->QualMinEUTRAOffsetCommonInc_Present) {
					}
					if (sequence->data[i]->NeighborRATRecord->QualMinEUTRAOffsetCommon_Present) {
					}
					for (i0=0; i0<sequence->data[i]->NeighborRATRecord->data05.items; i0++) {
						if (sequence->data[i]->NeighborRATRecord->data05.data[i0]->ThreshXQ_Present) {
						}
						if (sequence->data[i]->NeighborRATRecord->data05.data[i0]->QualMinEUTRA_Present) {
						}
						if (sequence->data[i]->NeighborRATRecord->data05.data[i0]->QualMinEUTRAOffsetIncl_Present) {
						}
						if (sequence->data[i]->NeighborRATRecord->data05.data[i0]->QualMinEUTRAOffset_Present) {
						}
						EDFree (sequence->data[i]->NeighborRATRecord->data05.data[i0]);
						sequence->data[i]->NeighborRATRecord->data05.data[i0] = NULL;
					}
					if (sequence->data[i]->NeighborRATRecord->data05.data) {EDFree (sequence->data[i]->NeighborRATRecord->data05.data); sequence->data[i]->NeighborRATRecord->data05.data = NULL; sequence->data[i]->NeighborRATRecord->data05.allocatedItems=0; /*FR02A*/}
					EDFree (sequence->data[i]->NeighborRATRecord);
					sequence->data[i]->NeighborRATRecord = NULL;
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	if (sp->OtherNeighborRATRecord_Present) {
		if (sp->OtherNeighborRATRecord->value != NULL) {
			EDFree (sp->OtherNeighborRATRecord->value);
			sp->OtherNeighborRATRecord->value = NULL;
		}
		sp->OtherNeighborRATRecord->usedBits = 0;
		EDFree (sp->OtherNeighborRATRecord);
		sp->OtherNeighborRATRecord_Present = ED_FALSE;
	}
	if (sp->NeighborRATRecord_Present) {
		if (sp->NeighborRATRecord->ServingPriority_Present) {
		}
		if (sp->NeighborRATRecord->RxLevMinEUTRACommon_Present) {
		}
		if (sp->NeighborRATRecord->PEMaxCommon_Present) {
		}
		if (sp->NeighborRATRecord->RxLevMinEUTRAOffsetCommonIncl_Present) {
		}
		if (sp->NeighborRATRecord->RxLevMinEUTRAOffsetCommon_Present) {
		}
		if (sp->NeighborRATRecord->MaxReselectionTimer_Present) {
		}
		if (sp->NeighborRATRecord->MinMeasurementBackoff_Present) {
		}
		if (sp->NeighborRATRecord->MaxMeasurementBackoff_Present) {
		}
		for (i0=0; i0<sp->NeighborRATRecord->data02.items; i0++) {
			if (sp->NeighborRATRecord->data02.data[i0]->EARFCNPriority_Present) {
			}
			if (sp->NeighborRATRecord->data02.data[i0]->RxLevMinEUTRA_Present) {
			}
			if (sp->NeighborRATRecord->data02.data[i0]->PEMax_Present) {
			}
			if (sp->NeighborRATRecord->data02.data[i0]->RxLevMinEUTRAOffsetIncl_Present) {
			}
			if (sp->NeighborRATRecord->data02.data[i0]->RxLevMinEUTRAOffset_Present) {
			}
			if (sp->NeighborRATRecord->data02.data[i0]->PLMNSameAsPreviousChannel_Present) {
			}
			if (sp->NeighborRATRecord->data02.data[i0]->NumPLMNIDs_Present) {
			}
			if (sp->NeighborRATRecord->data02.data[i0]->PLMNID.data) {EDFree (sp->NeighborRATRecord->data02.data[i0]->PLMNID.data); sp->NeighborRATRecord->data02.data[i0]->PLMNID.data = NULL; sp->NeighborRATRecord->data02.data[i0]->PLMNID.allocatedItems=0; /*FR02A*/}
			EDFree (sp->NeighborRATRecord->data02.data[i0]);
			sp->NeighborRATRecord->data02.data[i0] = NULL;
		}
		if (sp->NeighborRATRecord->data02.data) {EDFree (sp->NeighborRATRecord->data02.data); sp->NeighborRATRecord->data02.data = NULL; sp->NeighborRATRecord->data02.allocatedItems=0; /*FR02A*/}
		if (sp->NeighborRATRecord->ServingNetworkPLMNIncl_Present) {
		}
		if (sp->NeighborRATRecord->NumServingPLMNIDs_Present) {
		}
		if (sp->NeighborRATRecord->S_PLMNID.data) {EDFree (sp->NeighborRATRecord->S_PLMNID.data); sp->NeighborRATRecord->S_PLMNID.data = NULL; sp->NeighborRATRecord->S_PLMNID.allocatedItems=0; /*FR02A*/}
		if (sp->NeighborRATRecord->RSRQParametersIncluded_Present) {
		}
		if (sp->NeighborRATRecord->QualMinEUTRACommon_Present) {
		}
		if (sp->NeighborRATRecord->QualMinEUTRAOffsetCommonInc_Present) {
		}
		if (sp->NeighborRATRecord->QualMinEUTRAOffsetCommon_Present) {
		}
		for (i0=0; i0<sp->NeighborRATRecord->data05.items; i0++) {
			if (sp->NeighborRATRecord->data05.data[i0]->ThreshXQ_Present) {
			}
			if (sp->NeighborRATRecord->data05.data[i0]->QualMinEUTRA_Present) {
			}
			if (sp->NeighborRATRecord->data05.data[i0]->QualMinEUTRAOffsetIncl_Present) {
			}
			if (sp->NeighborRATRecord->data05.data[i0]->QualMinEUTRAOffset_Present) {
			}
			EDFree (sp->NeighborRATRecord->data05.data[i0]);
			sp->NeighborRATRecord->data05.data[i0] = NULL;
		}
		if (sp->NeighborRATRecord->data05.data) {EDFree (sp->NeighborRATRecord->data05.data); sp->NeighborRATRecord->data05.data = NULL; sp->NeighborRATRecord->data05.allocatedItems=0; /*FR02A*/}
		EDFree (sp->NeighborRATRecord);
		sp->NeighborRATRecord = NULL;
		sp->NeighborRATRecord_Present = ED_FALSE;
	}

}

void SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_OtherNeighborRATRecord (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->OtherNeighborRATRecord_Present == present) return;
	sp->OtherNeighborRATRecord_Present = present;
	if (present) {
		/*-->*/sp->OtherNeighborRATRecord = (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_OtherNeighborRATRecord*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_OtherNeighborRATRecord));
		sp->OtherNeighborRATRecord->value = NULL;
		sp->OtherNeighborRATRecord->usedBits = 0;
	} else {
		if (sp->OtherNeighborRATRecord->value != NULL) {
			EDFree (sp->OtherNeighborRATRecord->value);
			sp->OtherNeighborRATRecord->value = NULL;
		}
		sp->OtherNeighborRATRecord->usedBits = 0;
		EDFree (sp->OtherNeighborRATRecord);
	}
}

void SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data* sp, ED_BOOLEAN present)
{
		int i0;
/* Do nothing if already compliant to the request */
	if (sp->NeighborRATRecord_Present == present) return;
	sp->NeighborRATRecord_Present = present;
	if (present) {
		/*-->*/sp->NeighborRATRecord = (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord));
		ED_RESET_MEM (sp->NeighborRATRecord, sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord));
		(sp->NeighborRATRecord->PriorityIncluded) = 0;
		(sp->NeighborRATRecord->ThreshServing) = 0;
		(sp->NeighborRATRecord->PerEARFCNParamsIncluded) = 0;
		(sp->NeighborRATRecord->MaxReselectionTimerIncluded) = 0;
		(sp->NeighborRATRecord->SearchBackOffTimerIncluded) = 0;
		(sp->NeighborRATRecord->PLMNIDIncluded) = 0;
		(sp->NeighborRATRecord->NumEUTRAFrequencies) = 0;
		sp->NeighborRATRecord->data02.items = 0;
		sp->NeighborRATRecord->S_PLMNID.items = 0;
		sp->NeighborRATRecord->data05.items = 0;
	} else {
		if (sp->NeighborRATRecord->ServingPriority_Present) {
		}
		if (sp->NeighborRATRecord->RxLevMinEUTRACommon_Present) {
		}
		if (sp->NeighborRATRecord->PEMaxCommon_Present) {
		}
		if (sp->NeighborRATRecord->RxLevMinEUTRAOffsetCommonIncl_Present) {
		}
		if (sp->NeighborRATRecord->RxLevMinEUTRAOffsetCommon_Present) {
		}
		if (sp->NeighborRATRecord->MaxReselectionTimer_Present) {
		}
		if (sp->NeighborRATRecord->MinMeasurementBackoff_Present) {
		}
		if (sp->NeighborRATRecord->MaxMeasurementBackoff_Present) {
		}
		for (i0=0; i0<sp->NeighborRATRecord->data02.items; i0++) {
			if (sp->NeighborRATRecord->data02.data[i0]->EARFCNPriority_Present) {
			}
			if (sp->NeighborRATRecord->data02.data[i0]->RxLevMinEUTRA_Present) {
			}
			if (sp->NeighborRATRecord->data02.data[i0]->PEMax_Present) {
			}
			if (sp->NeighborRATRecord->data02.data[i0]->RxLevMinEUTRAOffsetIncl_Present) {
			}
			if (sp->NeighborRATRecord->data02.data[i0]->RxLevMinEUTRAOffset_Present) {
			}
			if (sp->NeighborRATRecord->data02.data[i0]->PLMNSameAsPreviousChannel_Present) {
			}
			if (sp->NeighborRATRecord->data02.data[i0]->NumPLMNIDs_Present) {
			}
			if (sp->NeighborRATRecord->data02.data[i0]->PLMNID.data) {EDFree (sp->NeighborRATRecord->data02.data[i0]->PLMNID.data); sp->NeighborRATRecord->data02.data[i0]->PLMNID.data = NULL; sp->NeighborRATRecord->data02.data[i0]->PLMNID.allocatedItems=0; /*FR02A*/}
			EDFree (sp->NeighborRATRecord->data02.data[i0]);
			sp->NeighborRATRecord->data02.data[i0] = NULL;
		}
		if (sp->NeighborRATRecord->data02.data) {EDFree (sp->NeighborRATRecord->data02.data); sp->NeighborRATRecord->data02.data = NULL; sp->NeighborRATRecord->data02.allocatedItems=0; /*FR02A*/}
		if (sp->NeighborRATRecord->ServingNetworkPLMNIncl_Present) {
		}
		if (sp->NeighborRATRecord->NumServingPLMNIDs_Present) {
		}
		if (sp->NeighborRATRecord->S_PLMNID.data) {EDFree (sp->NeighborRATRecord->S_PLMNID.data); sp->NeighborRATRecord->S_PLMNID.data = NULL; sp->NeighborRATRecord->S_PLMNID.allocatedItems=0; /*FR02A*/}
		if (sp->NeighborRATRecord->RSRQParametersIncluded_Present) {
		}
		if (sp->NeighborRATRecord->QualMinEUTRACommon_Present) {
		}
		if (sp->NeighborRATRecord->QualMinEUTRAOffsetCommonInc_Present) {
		}
		if (sp->NeighborRATRecord->QualMinEUTRAOffsetCommon_Present) {
		}
		for (i0=0; i0<sp->NeighborRATRecord->data05.items; i0++) {
			if (sp->NeighborRATRecord->data05.data[i0]->ThreshXQ_Present) {
			}
			if (sp->NeighborRATRecord->data05.data[i0]->QualMinEUTRA_Present) {
			}
			if (sp->NeighborRATRecord->data05.data[i0]->QualMinEUTRAOffsetIncl_Present) {
			}
			if (sp->NeighborRATRecord->data05.data[i0]->QualMinEUTRAOffset_Present) {
			}
			EDFree (sp->NeighborRATRecord->data05.data[i0]);
			sp->NeighborRATRecord->data05.data[i0] = NULL;
		}
		if (sp->NeighborRATRecord->data05.data) {EDFree (sp->NeighborRATRecord->data05.data); sp->NeighborRATRecord->data05.data = NULL; sp->NeighborRATRecord->data05.allocatedItems=0; /*FR02A*/}
		EDFree (sp->NeighborRATRecord);
		sp->NeighborRATRecord = NULL;
	}
}

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data02.items; i0++) {
		if (sp->data02.data[i0]->EARFCNPriority_Present) {
		}
		if (sp->data02.data[i0]->RxLevMinEUTRA_Present) {
		}
		if (sp->data02.data[i0]->PEMax_Present) {
		}
		if (sp->data02.data[i0]->RxLevMinEUTRAOffsetIncl_Present) {
		}
		if (sp->data02.data[i0]->RxLevMinEUTRAOffset_Present) {
		}
		if (sp->data02.data[i0]->PLMNSameAsPreviousChannel_Present) {
		}
		if (sp->data02.data[i0]->NumPLMNIDs_Present) {
		}
		if (sp->data02.data[i0]->PLMNID.data) {EDFree (sp->data02.data[i0]->PLMNID.data); sp->data02.data[i0]->PLMNID.data = NULL; sp->data02.data[i0]->PLMNID.allocatedItems=0; /*FR02A*/}
		EDFree (sp->data02.data[i0]);
		sp->data02.data[i0] = NULL;
	}
	if (sp->data02.data) {EDFree (sp->data02.data); sp->data02.data = NULL; sp->data02.allocatedItems=0; /*FR02A*/}
	if (sp->S_PLMNID.data) {EDFree (sp->S_PLMNID.data); sp->S_PLMNID.data = NULL; sp->S_PLMNID.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->data05.items; i0++) {
		if (sp->data05.data[i0]->ThreshXQ_Present) {
		}
		if (sp->data05.data[i0]->QualMinEUTRA_Present) {
		}
		if (sp->data05.data[i0]->QualMinEUTRAOffsetIncl_Present) {
		}
		if (sp->data05.data[i0]->QualMinEUTRAOffset_Present) {
		}
		EDFree (sp->data05.data[i0]);
		sp->data05.data[i0] = NULL;
	}
	if (sp->data05.data) {EDFree (sp->data05.data); sp->data05.data = NULL; sp->data05.allocatedItems=0; /*FR02A*/}

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02 (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data** tmp;
		tmp = (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data**)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data));
			(sequence->data[i]->EARFCN) = 0;
			(sequence->data[i]->ThreshX) = 0;
			(sequence->data[i]->MeasurementBandwidth) = 0;
			sequence->data[i]->PLMNID.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->EARFCNPriority_Present) {
				}
				if (sequence->data[i]->RxLevMinEUTRA_Present) {
				}
				if (sequence->data[i]->PEMax_Present) {
				}
				if (sequence->data[i]->RxLevMinEUTRAOffsetIncl_Present) {
				}
				if (sequence->data[i]->RxLevMinEUTRAOffset_Present) {
				}
				if (sequence->data[i]->PLMNSameAsPreviousChannel_Present) {
				}
				if (sequence->data[i]->NumPLMNIDs_Present) {
				}
				if (sequence->data[i]->PLMNID.data) {EDFree (sequence->data[i]->PLMNID.data); sequence->data[i]->PLMNID.data = NULL; sequence->data[i]->PLMNID.allocatedItems=0; /*FR02A*/}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->PLMNID.data) {EDFree (sp->PLMNID.data); sp->PLMNID.data = NULL; sp->PLMNID.allocatedItems=0; /*FR02A*/}

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID* sequence, int desiredItems)
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

/* SETITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID* sequence, int desiredItems)
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

/* SETITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05 (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data** tmp;
		tmp = (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data**)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->ThreshXQ_Present) {
				}
				if (sequence->data[i]->QualMinEUTRA_Present) {
				}
				if (sequence->data[i]->QualMinEUTRAOffsetIncl_Present) {
				}
				if (sequence->data[i]->QualMinEUTRAOffset_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01 (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data));
			(sequence->data[i]->APAssociationType) = 0;
			(sequence->data[i]->APSubnetSameAsPrevious) = 0;
			(sequence->data[i]->APBandSameAsPrevious) = 0;
			(sequence->data[i]->APChannelSameAsPrevious) = 0;
			(sequence->data[i]->APPNRecordSameAsPrevious) = 0;
			sequence->data[i]->APPNRecord.value = NULL;
			sequence->data[i]->APPNRecord.usedBits = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->APSubnetLength_Present) {
				}
				if (sequence->data[i]->APSubnet_Present) {
					if (sequence->data[i]->APSubnet->value != NULL) {
						EDFree (sequence->data[i]->APSubnet->value);
						sequence->data[i]->APSubnet->value = NULL;
					}
					sequence->data[i]->APSubnet->usedBits = 0;
					EDFree (sequence->data[i]->APSubnet);
				}
				if (sequence->data[i]->APBand_Present) {
				}
				if (sequence->data[i]->APChannel_Present) {
				}
				if (sequence->data[i]->APPNRecordType_Present) {
				}
				if (sequence->data[i]->APPNRecordLength_Present) {
				}
				if (sequence->data[i]->APPNRecord.value != NULL) {
					EDFree (sequence->data[i]->APPNRecord.value);
					sequence->data[i]->APPNRecord.value = NULL;
				}
				sequence->data[i]->APPNRecord.usedBits = 0;
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->APSubnet_Present) {
		if (sp->APSubnet->value != NULL) {
			EDFree (sp->APSubnet->value);
			sp->APSubnet->value = NULL;
		}
		sp->APSubnet->usedBits = 0;
		EDFree (sp->APSubnet);
		sp->APSubnet_Present = ED_FALSE;
	}
	if (sp->APPNRecord.value != NULL) {
		EDFree (sp->APPNRecord.value);
		sp->APPNRecord.value = NULL;
	}
	sp->APPNRecord.usedBits = 0;

}

void SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APSubnet (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->APSubnet_Present == present) return;
	sp->APSubnet_Present = present;
	if (present) {
		/*-->*/sp->APSubnet = (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APSubnet*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APSubnet));
		sp->APSubnet->value = NULL;
		sp->APSubnet->usedBits = 0;
	} else {
		if (sp->APSubnet->value != NULL) {
			EDFree (sp->APSubnet->value);
			sp->APSubnet->value = NULL;
		}
		sp->APSubnet->usedBits = 0;
		EDFree (sp->APSubnet);
	}
}

/* SETITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01 (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data));
			(sequence->data[i]->HandoffInfoType) = 0;
			(sequence->data[i]->HandoffInfoLength) = 0;
			sequence->data[i]->HandoffInfoValue.value = NULL;
			sequence->data[i]->HandoffInfoValue.usedBits = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->HandoffInfoValue.value != NULL) {
					EDFree (sequence->data[i]->HandoffInfoValue.value);
					sequence->data[i]->HandoffInfoValue.value = NULL;
				}
				sequence->data[i]->HandoffInfoValue.usedBits = 0;
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->HandoffInfoValue.value != NULL) {
		EDFree (sp->HandoffInfoValue.value);
		sp->HandoffInfoValue.value = NULL;
	}
	sp->HandoffInfoValue.usedBits = 0;

}

/* SETITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01 (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01_data** tmp;
		tmp = (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01_data**)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01_data*)EDAlloc (sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01_data));
			(sequence->data[i]->CHARi) = 0;
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

/* Free function for struct c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01_data */
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01_data (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01 (c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data** tmp;
		tmp = (c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data**)EDAlloc (sizeof (c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data*)EDAlloc (sizeof (c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data));
			(sequence->data[i]->OpenLoopAdjust) = 0;
			(sequence->data[i]->InitialAdjust) = 0;
			(sequence->data[i]->PilotStrengthIncluded) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->PilotPN_Present) {
				}
				if (sequence->data[i]->PilotStrengthNominal_Present) {
				}
				if (sequence->data[i]->PilotStrengthCorrectionMin_Present) {
				}
				if (sequence->data[i]->PilotStrengthCorrectionMax_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data */
void FREE_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data (c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01'. Existing items are not changed. */
int SETITEMS_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01 (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01_data** tmp;
		tmp = (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01_data**)EDAlloc (sizeof (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01_data*)EDAlloc (sizeof (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01_data));
			(sequence->data[i]->PilotPN) = 0;
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

/* Free function for struct c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01_data */
void FREE_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01_data (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02'. Existing items are not changed. */
int SETITEMS_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02 (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02* sequence, int desiredItems)
{
	int i, i0;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data** tmp;
		tmp = (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data**)EDAlloc (sizeof (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data*)EDAlloc (sizeof (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data));
			sequence->data[i]->data03.items = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->ReverseCDMAChannel_Present) {
					EDFree (sequence->data[i]->ReverseCDMAChannel);
					sequence->data[i]->ReverseCDMAChannel = NULL;
				}
				for (i0=0; i0<sequence->data[i]->data03.items; i0++) {
					if (sequence->data[i]->data03.data[i0]->PilotIncluded_Present) {
					}
					if (sequence->data[i]->data03.data[i0]->OpenLoopAdjust_Present) {
					}
					if (sequence->data[i]->data03.data[i0]->InitialAdjust_Present) {
					}
					if (sequence->data[i]->data03.data[i0]->PilotStrengthIncluded_Present) {
					}
					if (sequence->data[i]->data03.data[i0]->PilotStrengthNominal_Present) {
					}
					if (sequence->data[i]->data03.data[i0]->PilotStrengthCorrectionMin_Present) {
					}
					if (sequence->data[i]->data03.data[i0]->PilotStrengthCorrectionMax_Present) {
					}
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

/* Free function for struct c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data */
void FREE_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	if (sp->ReverseCDMAChannel_Present) {
		EDFree (sp->ReverseCDMAChannel);
		sp->ReverseCDMAChannel = NULL;
		sp->ReverseCDMAChannel_Present = ED_FALSE;
	}
	for (i0=0; i0<sp->data03.items; i0++) {
		if (sp->data03.data[i0]->PilotIncluded_Present) {
		}
		if (sp->data03.data[i0]->OpenLoopAdjust_Present) {
		}
		if (sp->data03.data[i0]->InitialAdjust_Present) {
		}
		if (sp->data03.data[i0]->PilotStrengthIncluded_Present) {
		}
		if (sp->data03.data[i0]->PilotStrengthNominal_Present) {
		}
		if (sp->data03.data[i0]->PilotStrengthCorrectionMin_Present) {
		}
		if (sp->data03.data[i0]->PilotStrengthCorrectionMax_Present) {
		}
		EDFree (sp->data03.data[i0]);
		sp->data03.data[i0] = NULL;
	}
	if (sp->data03.data) {EDFree (sp->data03.data); sp->data03.data = NULL; sp->data03.allocatedItems=0; /*FR02A*/}

}

void SETPRESENT_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_ReverseCDMAChannel (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->ReverseCDMAChannel_Present == present) return;
	sp->ReverseCDMAChannel_Present = present;
	if (present) {
		/*-->*/sp->ReverseCDMAChannel = (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_ReverseCDMAChannel*)EDAlloc (sizeof (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_ReverseCDMAChannel));
		ED_RESET_MEM (sp->ReverseCDMAChannel, sizeof (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_ReverseCDMAChannel));
		(sp->ReverseCDMAChannel->SystemType) = 0;
		(sp->ReverseCDMAChannel->BandClass) = 0;
		(sp->ReverseCDMAChannel->ChannelNumber) = 0;
	} else {
		EDFree (sp->ReverseCDMAChannel);
		sp->ReverseCDMAChannel = NULL;
	}
}

/* Free function for struct c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_ReverseCDMAChannel */
void FREE_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_ReverseCDMAChannel (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_ReverseCDMAChannel* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03'. Existing items are not changed. */
int SETITEMS_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03 (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data** tmp;
		tmp = (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data**)EDAlloc (sizeof (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data*)EDAlloc (sizeof (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data));
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->PilotIncluded_Present) {
				}
				if (sequence->data[i]->OpenLoopAdjust_Present) {
				}
				if (sequence->data[i]->InitialAdjust_Present) {
				}
				if (sequence->data[i]->PilotStrengthIncluded_Present) {
				}
				if (sequence->data[i]->PilotStrengthNominal_Present) {
				}
				if (sequence->data[i]->PilotStrengthCorrectionMin_Present) {
				}
				if (sequence->data[i]->PilotStrengthCorrectionMax_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data */
void FREE_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01 (c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01_data** tmp;
		tmp = (c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01_data**)EDAlloc (sizeof (c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01_data*)EDAlloc (sizeof (c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->PreferredControlChannelCycleEnabled) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->PreferredControlChannelCycle_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01_data */
void FREE_c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01_data (c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPD_Inter_RAT_Idle_State_SlottedMode_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Inter_RAT_Idle_State_SlottedMode_data01 (c_RPD_Inter_RAT_Idle_State_SlottedMode_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data** tmp;
		tmp = (c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data**)EDAlloc (sizeof (c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data*)EDAlloc (sizeof (c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->SlotCycle1) = 0;
			(sequence->data[i]->SlotCycle2) = 0;
			(sequence->data[i]->SlotCycle3) = 0;
			(sequence->data[i]->WakeCount1) = 0;
			(sequence->data[i]->WakeCount2) = 0;
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

/* Free function for struct c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data */
void FREE_c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data (c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPD_Inter_RAT_Idle_State_PagingMask_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Inter_RAT_Idle_State_PagingMask_data01 (c_RPD_Inter_RAT_Idle_State_PagingMask_data01* sequence, int desiredItems)
{
	int i, i0;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data** tmp;
		tmp = (c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data**)EDAlloc (sizeof (c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data*)EDAlloc (sizeof (c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->MaskCount) = 0;
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

/* Free function for struct c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data */
void FREE_c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data (c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data02.items; i0++) {
		EDFree (sp->data02.data[i0]);
		sp->data02.data[i0] = NULL;
	}
	if (sp->data02.data) {EDFree (sp->data02.data); sp->data02.data = NULL; sp->data02.allocatedItems=0; /*FR02A*/}

}

/* SETITEMS commands for type 'c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02'. Existing items are not changed. */
int SETITEMS_c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02 (c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02_data** tmp;
		tmp = (c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02_data**)EDAlloc (sizeof (c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02_data*)EDAlloc (sizeof (c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02_data));
			(sequence->data[i]->MaskPurpose) = 0;
			(sequence->data[i]->PreMaskDuration) = 0;
			(sequence->data[i]->MaskDuration) = 0;
			(sequence->data[i]->PostMaskDuration) = 0;
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

/* Free function for struct c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02_data */
void FREE_c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02_data (c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPD_Inter_RAT_Route_Update_SearchParameters_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Inter_RAT_Route_Update_SearchParameters_data01 (c_RPD_Inter_RAT_Route_Update_SearchParameters_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data** tmp;
		tmp = (c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data**)EDAlloc (sizeof (c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data*)EDAlloc (sizeof (c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->PilotIncrement) = 0;
			(sequence->data[i]->SearchWindowActive) = 0;
			(sequence->data[i]->SearchWindowNeighbor) = 0;
			(sequence->data[i]->SearchWindowRemaining) = 0;
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

/* Free function for struct c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data */
void FREE_c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data (c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01 (c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data** tmp;
		tmp = (c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data**)EDAlloc (sizeof (c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data*)EDAlloc (sizeof (c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->PilotAdd) = 0;
			(sequence->data[i]->PilotCompare) = 0;
			(sequence->data[i]->PilotDrop) = 0;
			(sequence->data[i]->PilotDropTimer) = 0;
			(sequence->data[i]->DynamicThresholds) = 0;
			(sequence->data[i]->NeighborMaxAge) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->SoftSlope_Present) {
				}
				if (sequence->data[i]->AddIntercept_Present) {
				}
				if (sequence->data[i]->DropIntercept_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data */
void FREE_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data (c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01 (c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data** tmp;
		tmp = (c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data**)EDAlloc (sizeof (c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data*)EDAlloc (sizeof (c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->PilotAdd) = 0;
			(sequence->data[i]->PilotCompare) = 0;
			(sequence->data[i]->PilotDrop) = 0;
			(sequence->data[i]->PilotDropTimer) = 0;
			(sequence->data[i]->DynamicThresholds) = 0;
			(sequence->data[i]->NeighborMaxAge) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->SoftSlope_Present) {
				}
				if (sequence->data[i]->AddIntercept_Present) {
				}
				if (sequence->data[i]->DropIntercept_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data */
void FREE_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data (c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01 (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01* sequence, int desiredItems)
{
	int i, i0, i1;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data** tmp;
		tmp = (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data**)EDAlloc (sizeof (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data*)EDAlloc (sizeof (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->BandClassCount) = 0;
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

/* Free function for struct c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data */
void FREE_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data* sp) {
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

/* SETITEMS commands for type 'c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02'. Existing items are not changed. */
int SETITEMS_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02 (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02* sequence, int desiredItems)
{
	int i, i0;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data** tmp;
		tmp = (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data**)EDAlloc (sizeof (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data*)EDAlloc (sizeof (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data));
			(sequence->data[i]->BandClass) = 0;
			(sequence->data[i]->BandSubClassCount) = 0;
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

/* Free function for struct c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data */
void FREE_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data03.items; i0++) {
		EDFree (sp->data03.data[i0]);
		sp->data03.data[i0] = NULL;
	}
	if (sp->data03.data) {EDFree (sp->data03.data); sp->data03.data = NULL; sp->data03.allocatedItems=0; /*FR02A*/}

}

/* SETITEMS commands for type 'c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03'. Existing items are not changed. */
int SETITEMS_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03 (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data** tmp;
		tmp = (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data**)EDAlloc (sizeof (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data*)EDAlloc (sizeof (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data));
			(sequence->data[i]->BandSubClass) = 0;
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

/* Free function for struct c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data */
void FREE_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01 (c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01_data** tmp;
		tmp = (c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01_data**)EDAlloc (sizeof (c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01_data*)EDAlloc (sizeof (c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->PreferredControlChannelCycleEnabled) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->PreferredControlChannelCycle_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01_data */
void FREE_c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01_data (c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01 (c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data** tmp;
		tmp = (c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data**)EDAlloc (sizeof (c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data*)EDAlloc (sizeof (c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->SlotCycle1) = 0;
			(sequence->data[i]->SlotCycle2) = 0;
			(sequence->data[i]->SlotCycle3) = 0;
			(sequence->data[i]->WakeCount1) = 0;
			(sequence->data[i]->WakeCount2) = 0;
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

/* Free function for struct c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data */
void FREE_c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data (c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01 (c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01* sequence, int desiredItems)
{
	int i, i0;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data** tmp;
		tmp = (c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data**)EDAlloc (sizeof (c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data*)EDAlloc (sizeof (c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->MaskCount) = 0;
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

/* Free function for struct c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data */
void FREE_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data (c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data02.items; i0++) {
		EDFree (sp->data02.data[i0]);
		sp->data02.data[i0] = NULL;
	}
	if (sp->data02.data) {EDFree (sp->data02.data); sp->data02.data = NULL; sp->data02.allocatedItems=0; /*FR02A*/}

}

/* SETITEMS commands for type 'c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02'. Existing items are not changed. */
int SETITEMS_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02 (c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02_data** tmp;
		tmp = (c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02_data**)EDAlloc (sizeof (c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02_data*)EDAlloc (sizeof (c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02_data));
			(sequence->data[i]->MaskPurpose) = 0;
			(sequence->data[i]->PreMaskDuration) = 0;
			(sequence->data[i]->MaskDuration) = 0;
			(sequence->data[i]->PostMaskDuration) = 0;
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

/* Free function for struct c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02_data */
void FREE_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02_data (c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01 (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data** tmp;
		tmp = (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data**)EDAlloc (sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data*)EDAlloc (sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->PilotIncrement) = 0;
			(sequence->data[i]->SearchWindowActive) = 0;
			(sequence->data[i]->SearchWindowNeighbor) = 0;
			(sequence->data[i]->SearchWindowRemaining) = 0;
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

/* Free function for struct c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data */
void FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01 (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data** tmp;
		tmp = (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data**)EDAlloc (sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data*)EDAlloc (sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->PilotAdd) = 0;
			(sequence->data[i]->PilotCompare) = 0;
			(sequence->data[i]->PilotDrop) = 0;
			(sequence->data[i]->PilotDropTimer) = 0;
			(sequence->data[i]->DynamicThresholds) = 0;
			(sequence->data[i]->NeighborMaxAge) = 0;
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->SoftSlope_Present) {
				}
				if (sequence->data[i]->AddIntercept_Present) {
				}
				if (sequence->data[i]->DropIntercept_Present) {
				}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data */
void FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01 (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01* sequence, int desiredItems)
{
	int i, i0, i1;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data** tmp;
		tmp = (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data**)EDAlloc (sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data*)EDAlloc (sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->BandClassCount) = 0;
			sequence->data[i]->data02.items = 0;
			sequence->data[i]->data04.items = 0;
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
				if (sequence->data[i]->MultiBandCount_Present) {
				}
				if (sequence->data[i]->MultiBandBitMapCount_Present) {
				}
				for (i0=0; i0<sequence->data[i]->data04.items; i0++) {
					if (sequence->data[i]->data04.data[i0]->MultiBandBitMap.value != NULL) {
						EDFree (sequence->data[i]->data04.data[i0]->MultiBandBitMap.value);
						sequence->data[i]->data04.data[i0]->MultiBandBitMap.value = NULL;
					}
					sequence->data[i]->data04.data[i0]->MultiBandBitMap.usedBits = 0;
					EDFree (sequence->data[i]->data04.data[i0]);
					sequence->data[i]->data04.data[i0] = NULL;
				}
				if (sequence->data[i]->data04.data) {EDFree (sequence->data[i]->data04.data); sequence->data[i]->data04.data = NULL; sequence->data[i]->data04.allocatedItems=0; /*FR02A*/}
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data */
void FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data* sp) {
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
	for (i0=0; i0<sp->data04.items; i0++) {
		if (sp->data04.data[i0]->MultiBandBitMap.value != NULL) {
			EDFree (sp->data04.data[i0]->MultiBandBitMap.value);
			sp->data04.data[i0]->MultiBandBitMap.value = NULL;
		}
		sp->data04.data[i0]->MultiBandBitMap.usedBits = 0;
		EDFree (sp->data04.data[i0]);
		sp->data04.data[i0] = NULL;
	}
	if (sp->data04.data) {EDFree (sp->data04.data); sp->data04.data = NULL; sp->data04.allocatedItems=0; /*FR02A*/}

}

/* SETITEMS commands for type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02'. Existing items are not changed. */
int SETITEMS_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02 (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02* sequence, int desiredItems)
{
	int i, i0;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data** tmp;
		tmp = (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data**)EDAlloc (sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data*)EDAlloc (sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data));
			(sequence->data[i]->BandClass) = 0;
			(sequence->data[i]->InterFlexDuplexTag) = 0;
			(sequence->data[i]->IntraFlexDuplexFlag) = 0;
			(sequence->data[i]->BandSubClassCount) = 0;
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

/* Free function for struct c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data */
void FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data03.items; i0++) {
		EDFree (sp->data03.data[i0]);
		sp->data03.data[i0] = NULL;
	}
	if (sp->data03.data) {EDFree (sp->data03.data); sp->data03.data = NULL; sp->data03.allocatedItems=0; /*FR02A*/}

}

/* SETITEMS commands for type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03'. Existing items are not changed. */
int SETITEMS_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03 (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data** tmp;
		tmp = (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data**)EDAlloc (sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data*)EDAlloc (sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data));
			(sequence->data[i]->BandSubClass) = 0;
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

/* Free function for struct c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data */
void FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* SETITEMS commands for type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04'. Existing items are not changed. */
int SETITEMS_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04 (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04_data** tmp;
		tmp = (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04_data**)EDAlloc (sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04_data*)EDAlloc (sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04_data));
			sequence->data[i]->MultiBandBitMap.value = NULL;
			sequence->data[i]->MultiBandBitMap.usedBits = 0;
			
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				if (sequence->data[i]->MultiBandBitMap.value != NULL) {
					EDFree (sequence->data[i]->MultiBandBitMap.value);
					sequence->data[i]->MultiBandBitMap.value = NULL;
				}
				sequence->data[i]->MultiBandBitMap.usedBits = 0;
				EDFree (sequence->data[i]);
				sequence->data[i] = NULL;
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* Free function for struct c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04_data */
void FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04_data (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->MultiBandBitMap.value != NULL) {
		EDFree (sp->MultiBandBitMap.value);
		sp->MultiBandBitMap.value = NULL;
	}
	sp->MultiBandBitMap.usedBits = 0;

}

/* SETITEMS commands for type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01'. Existing items are not changed. */
int SETITEMS_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01 (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01* sequence, int desiredItems)
{
	int i, i0;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data** tmp;
		tmp = (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data**)EDAlloc (sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data*)EDAlloc (sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data));
			(sequence->data[i]->ValueID) = 0;
			(sequence->data[i]->NumberofDRXPatterns) = 0;
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

/* Free function for struct c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data */
void FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->data02.items; i0++) {
		EDFree (sp->data02.data[i0]);
		sp->data02.data[i0] = NULL;
	}
	if (sp->data02.data) {EDFree (sp->data02.data); sp->data02.data = NULL; sp->data02.allocatedItems=0; /*FR02A*/}

}

/* SETITEMS commands for type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02'. Existing items are not changed. */
int SETITEMS_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02 (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02_data** tmp;
		tmp = (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02_data**)EDAlloc (sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02_data*)EDAlloc (sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02_data));
			ED_RESET_MEM (sequence->data[i], sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02_data));
			(sequence->data[i]->SupportedDRXPattern) = 0;
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

/* Free function for struct c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02_data */
void FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02_data (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* Set-present function for c_RPD_Inter_RAT_Idle_State_complex LEVEL = -1 */
void GLOB_SETPRESENT_c_RPD_Inter_RAT_Idle_State_complex (c_RPD_Inter_RAT_Idle_State_complex* sp, TPRESENT_c_RPD_Inter_RAT_Idle_State_complex toBeSetPresent) 
{
	FREE_c_RPD_Inter_RAT_Idle_State_complex (sp);
	sp->Present = toBeSetPresent;
	
	switch (toBeSetPresent) {
		case U_c_RPD_Inter_RAT_Idle_State_complex_PreferredControlChannelCycle: {
			sp->u.PreferredControlChannelCycle = (c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle*)EDAlloc (sizeof (c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle));
			INIT_c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle (sp->u.PreferredControlChannelCycle);

			break;
		}
		case U_c_RPD_Inter_RAT_Idle_State_complex_SlottedMode: {
			sp->u.SlottedMode = (c_RPD_Inter_RAT_Idle_State_SlottedMode*)EDAlloc (sizeof (c_RPD_Inter_RAT_Idle_State_SlottedMode));
			INIT_c_RPD_Inter_RAT_Idle_State_SlottedMode (sp->u.SlottedMode);

			break;
		}
		case U_c_RPD_Inter_RAT_Idle_State_complex_PagingMask: {
			sp->u.PagingMask = (c_RPD_Inter_RAT_Idle_State_PagingMask*)EDAlloc (sizeof (c_RPD_Inter_RAT_Idle_State_PagingMask));
			INIT_c_RPD_Inter_RAT_Idle_State_PagingMask (sp->u.PagingMask);

			break;
		}
		default:;	}
}

/* Set-present function for c_RPD_Inter_RAT_Route_Update_complex LEVEL = -1 */
void GLOB_SETPRESENT_c_RPD_Inter_RAT_Route_Update_complex (c_RPD_Inter_RAT_Route_Update_complex* sp, TPRESENT_c_RPD_Inter_RAT_Route_Update_complex toBeSetPresent) 
{
	FREE_c_RPD_Inter_RAT_Route_Update_complex (sp);
	sp->Present = toBeSetPresent;
	
	switch (toBeSetPresent) {
		case U_c_RPD_Inter_RAT_Route_Update_complex_SearchParameters: {
			sp->u.SearchParameters = (c_RPD_Inter_RAT_Route_Update_SearchParameters*)EDAlloc (sizeof (c_RPD_Inter_RAT_Route_Update_SearchParameters));
			INIT_c_RPD_Inter_RAT_Route_Update_SearchParameters (sp->u.SearchParameters);

			break;
		}
		case U_c_RPD_Inter_RAT_Route_Update_complex_SetManagementSameChannelParameters: {
			sp->u.SetManagementSameChannelParameters = (c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters*)EDAlloc (sizeof (c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters));
			INIT_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters (sp->u.SetManagementSameChannelParameters);

			break;
		}
		case U_c_RPD_Inter_RAT_Route_Update_complex_SetManagementDifferentChannelParameters: {
			sp->u.SetManagementDifferentChannelParameters = (c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters*)EDAlloc (sizeof (c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters));
			INIT_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters (sp->u.SetManagementDifferentChannelParameters);

			break;
		}
		case U_c_RPD_Inter_RAT_Route_Update_complex_SupportedCDMAChannels: {
			sp->u.SupportedCDMAChannels = (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels*)EDAlloc (sizeof (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels));
			INIT_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels (sp->u.SupportedCDMAChannels);

			break;
		}
		default:;	}
}

/* Set-present function for c_RPD_Inter_RAT_Quick_Idle_State_complex LEVEL = -1 */
void GLOB_SETPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_complex (c_RPD_Inter_RAT_Quick_Idle_State_complex* sp, TPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_complex toBeSetPresent) 
{
	FREE_c_RPD_Inter_RAT_Quick_Idle_State_complex (sp);
	sp->Present = toBeSetPresent;
	
	switch (toBeSetPresent) {
		case U_c_RPD_Inter_RAT_Quick_Idle_State_complex_PreferredControlChannelCycle: {
			sp->u.PreferredControlChannelCycle = (c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle*)EDAlloc (sizeof (c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle));
			INIT_c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle (sp->u.PreferredControlChannelCycle);

			break;
		}
		case U_c_RPD_Inter_RAT_Quick_Idle_State_complex_SlottedMode: {
			sp->u.SlottedMode = (c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode*)EDAlloc (sizeof (c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode));
			INIT_c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode (sp->u.SlottedMode);

			break;
		}
		case U_c_RPD_Inter_RAT_Quick_Idle_State_complex_PagingMask: {
			sp->u.PagingMask = (c_RPD_Inter_RAT_Quick_Idle_State_PagingMask*)EDAlloc (sizeof (c_RPD_Inter_RAT_Quick_Idle_State_PagingMask));
			INIT_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask (sp->u.PagingMask);

			break;
		}
		default:;	}
}

/* Set-present function for c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex LEVEL = -1 */
void GLOB_SETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex (c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex* sp, TPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex toBeSetPresent) 
{
	FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex (sp);
	sp->Present = toBeSetPresent;
	
	switch (toBeSetPresent) {
		case U_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SearchParameters: {
			sp->u.SearchParameters = (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters*)EDAlloc (sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters));
			INIT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters (sp->u.SearchParameters);

			break;
		}
		case U_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SetManagementParameters: {
			sp->u.SetManagementParameters = (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters*)EDAlloc (sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters));
			INIT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters (sp->u.SetManagementParameters);

			break;
		}
		case U_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SupportedCDMAChannels: {
			sp->u.SupportedCDMAChannels = (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels*)EDAlloc (sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels));
			INIT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels (sp->u.SupportedCDMAChannels);

			break;
		}
		case U_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SupportedDRXPatterns: {
			sp->u.SupportedDRXPatterns = (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns*)EDAlloc (sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns));
			INIT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns (sp->u.SupportedDRXPatterns);

			break;
		}
		default:;	}
}

