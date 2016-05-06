/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c
	http://www.Dafocus.it/
**************************************************************************/
/*lint -e959 -e530 -e774 -e572 -e778 -e525 -e539 -e701 -e123 -e438 -e119 -e506 -e529 -e550 -e666 -e713 -e719 -e730 -e734 -e744 -e801 -e801 -e813 -e830 -e40 -e10 -e52 -e63 -e115 -e409 -e118 -e49 -e718 -e746 -e737 -e760 -e830 */
#define ENCODIX_CS0004

#include "ed_c_cs0004.h"
#include "ed_lib.h"
#if ED_COMMON_CRC != 0x328E3625 && ED_VERSION != 10152 && ED_VERSION != 10153
#error Invalid Encodix library files linked; used those distributed with Encodix 1.0.154
#endif


/* Free function for struct c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh */
void FREE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh (c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->PILOT_WALSH.value != NULL) {
		EDFree (sp->PILOT_WALSH.value);
		sp->PILOT_WALSH.value = NULL;
	}
	sp->PILOT_WALSH.usedBits = 0;

}

/* Free function for struct c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields */
void FREE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields (c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->Walsh_Present) {
		FREE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh (sp->Walsh);
		EDFree (sp->Walsh);
		sp->Walsh_Present = ED_FALSE;
	}

}

void SETPRESENT_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh (c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->Walsh_Present == present) return;
	sp->Walsh_Present = present;
	if (present) {
		/*-->*/sp->Walsh = (c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh*)EDAlloc (sizeof (c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh));
		INIT_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh (sp->Walsh);
	} else {
		FREE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh (sp->Walsh);
		EDFree (sp->Walsh);
	}
}

/* Free function for struct c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0 */
void FREE_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0 (c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1 */
void FREE_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1 (c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0 */
void FREE_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0 (c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1 */
void FREE_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1 (c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS */
void FREE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS (c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields (&(sp->Type_specific_fields));

}

/* Free function for struct c_FCSCH_PDU_SDUs_data_Extended_Address */
void FREE_c_FCSCH_PDU_SDUs_data_Extended_Address (c_FCSCH_PDU_SDUs_data_Extended_Address* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->MEID.value != NULL) {
		EDFree (sp->MEID.value);
		sp->MEID.value = NULL;
	}
	sp->MEID.usedBits = 0;

}

/* Free function for struct c_FCSCH_PDU_SDUs_data_IMSI_S */
void FREE_c_FCSCH_PDU_SDUs_data_IMSI_S (c_FCSCH_PDU_SDUs_data_IMSI_S* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_FCSCH_PDU_SDUs_data_ESN */
void FREE_c_FCSCH_PDU_SDUs_data_ESN (c_FCSCH_PDU_SDUs_data_ESN* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->ESN.value != NULL) {
		EDFree (sp->ESN.value);
		sp->ESN.value = NULL;
	}
	sp->ESN.usedBits = 0;

}

/* Free function for struct c_FCSCH_PDU_SDUs_data_IMSI */
void FREE_c_FCSCH_PDU_SDUs_data_IMSI (c_FCSCH_PDU_SDUs_data_IMSI* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->IMSI_CLASS_0_Present) {
		FREE_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0 (sp->IMSI_CLASS_0);
		EDFree (sp->IMSI_CLASS_0);
		sp->IMSI_CLASS_0_Present = ED_FALSE;
	}
	if (sp->IMSI_CLASS_1_Present) {
		FREE_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1 (sp->IMSI_CLASS_1);
		EDFree (sp->IMSI_CLASS_1);
		sp->IMSI_CLASS_1_Present = ED_FALSE;
	}

}

void SETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0 (c_FCSCH_PDU_SDUs_data_IMSI* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->IMSI_CLASS_0_Present == present) return;
	sp->IMSI_CLASS_0_Present = present;
	if (present) {
		/*-->*/sp->IMSI_CLASS_0 = (c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0*)EDAlloc (sizeof (c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0));
		INIT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0 (sp->IMSI_CLASS_0);
	} else {
		FREE_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0 (sp->IMSI_CLASS_0);
		EDFree (sp->IMSI_CLASS_0);
	}
}

void SETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1 (c_FCSCH_PDU_SDUs_data_IMSI* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->IMSI_CLASS_1_Present == present) return;
	sp->IMSI_CLASS_1_Present = present;
	if (present) {
		/*-->*/sp->IMSI_CLASS_1 = (c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1*)EDAlloc (sizeof (c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1));
		INIT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1 (sp->IMSI_CLASS_1);
	} else {
		FREE_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1 (sp->IMSI_CLASS_1);
		EDFree (sp->IMSI_CLASS_1);
	}
}

/* Free function for struct c_FCSCH_PDU_SDUs_data_TMSI */
void FREE_c_FCSCH_PDU_SDUs_data_TMSI (c_FCSCH_PDU_SDUs_data_TMSI* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->TMSI_ZONE.value != NULL) {
		EDFree (sp->TMSI_ZONE.value);
		sp->TMSI_ZONE.value = NULL;
	}
	sp->TMSI_ZONE.usedBits = 0;
	if (sp->TMSI_CODE_ADDR.value != NULL) {
		EDFree (sp->TMSI_CODE_ADDR.value);
		sp->TMSI_CODE_ADDR.value = NULL;
	}
	sp->TMSI_CODE_ADDR.usedBits = 0;

}

/* Free function for struct c_FCSCH_PDU_SDUs_data_BROADCAST */
void FREE_c_FCSCH_PDU_SDUs_data_BROADCAST (c_FCSCH_PDU_SDUs_data_BROADCAST* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->BC_ADDR.value != NULL) {
		EDFree (sp->BC_ADDR.value);
		sp->BC_ADDR.value = NULL;
	}
	sp->BC_ADDR.usedBits = 0;

}

/* Free function for struct c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data */
void FREE_c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data (c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0 */
void FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0 (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1 */
void FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1 (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_r_csch_PDU_Addressing_IMSI_class_specific_subfields */
void FREE_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields (c_r_csch_PDU_Addressing_IMSI_class_specific_subfields* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->IMSI_CLASS_0_Present) {
		FREE_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0 (sp->IMSI_CLASS_0);
		EDFree (sp->IMSI_CLASS_0);
		sp->IMSI_CLASS_0_Present = ED_FALSE;
	}
	if (sp->IMSI_CLASS_1_Present) {
		FREE_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1 (sp->IMSI_CLASS_1);
		EDFree (sp->IMSI_CLASS_1);
		sp->IMSI_CLASS_1_Present = ED_FALSE;
	}

}

void SETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0 (c_r_csch_PDU_Addressing_IMSI_class_specific_subfields* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->IMSI_CLASS_0_Present == present) return;
	sp->IMSI_CLASS_0_Present = present;
	if (present) {
		/*-->*/sp->IMSI_CLASS_0 = (c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0*)EDAlloc (sizeof (c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0));
		INIT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0 (sp->IMSI_CLASS_0);
	} else {
		FREE_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0 (sp->IMSI_CLASS_0);
		EDFree (sp->IMSI_CLASS_0);
	}
}

void SETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1 (c_r_csch_PDU_Addressing_IMSI_class_specific_subfields* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->IMSI_CLASS_1_Present == present) return;
	sp->IMSI_CLASS_1_Present = present;
	if (present) {
		/*-->*/sp->IMSI_CLASS_1 = (c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1*)EDAlloc (sizeof (c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1));
		INIT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1 (sp->IMSI_CLASS_1);
	} else {
		FREE_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1 (sp->IMSI_CLASS_1);
		EDFree (sp->IMSI_CLASS_1);
	}
}

/* Free function for struct c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report */
void FREE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report (c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->AUX_PILOTS_Present) {
		FREE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS (sp->AUX_PILOTS);
		EDFree (sp->AUX_PILOTS);
		sp->AUX_PILOTS_Present = ED_FALSE;
	}

}

void SETPRESENT_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS (c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->AUX_PILOTS_Present == present) return;
	sp->AUX_PILOTS_Present = present;
	if (present) {
		/*-->*/sp->AUX_PILOTS = (c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS*)EDAlloc (sizeof (c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS));
		INIT_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS (sp->AUX_PILOTS);
	} else {
		FREE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS (sp->AUX_PILOTS);
		EDFree (sp->AUX_PILOTS);
	}
}

/* Free function for struct c_FCSCH_PDU_SDUs_data */
void FREE_c_FCSCH_PDU_SDUs_data (c_FCSCH_PDU_SDUs_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->IMSI_S_Present) {
		FREE_c_FCSCH_PDU_SDUs_data_IMSI_S (sp->IMSI_S);
		EDFree (sp->IMSI_S);
		sp->IMSI_S_Present = ED_FALSE;
	}
	if (sp->ESN_Present) {
		FREE_c_FCSCH_PDU_SDUs_data_ESN (sp->ESN);
		EDFree (sp->ESN);
		sp->ESN_Present = ED_FALSE;
	}
	if (sp->IMSI_Present) {
		FREE_c_FCSCH_PDU_SDUs_data_IMSI (sp->IMSI);
		EDFree (sp->IMSI);
		sp->IMSI_Present = ED_FALSE;
	}
	if (sp->TMSI_Present) {
		FREE_c_FCSCH_PDU_SDUs_data_TMSI (sp->TMSI);
		EDFree (sp->TMSI);
		sp->TMSI_Present = ED_FALSE;
	}
	if (sp->Extended_Address_Present) {
		FREE_c_FCSCH_PDU_SDUs_data_Extended_Address (sp->Extended_Address);
		EDFree (sp->Extended_Address);
		sp->Extended_Address_Present = ED_FALSE;
	}
	if (sp->BROADCAST_Present) {
		FREE_c_FCSCH_PDU_SDUs_data_BROADCAST (sp->BROADCAST);
		EDFree (sp->BROADCAST);
		sp->BROADCAST_Present = ED_FALSE;
	}
	if (sp->SDU.value != NULL) {
		EDFree (sp->SDU.value);
		sp->SDU.value = NULL;
	}
	sp->SDU.usedBits = 0;

}

void SETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_S (c_FCSCH_PDU_SDUs_data* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->IMSI_S_Present == present) return;
	sp->IMSI_S_Present = present;
	if (present) {
		/*-->*/sp->IMSI_S = (c_FCSCH_PDU_SDUs_data_IMSI_S*)EDAlloc (sizeof (c_FCSCH_PDU_SDUs_data_IMSI_S));
		INIT_c_FCSCH_PDU_SDUs_data_IMSI_S (sp->IMSI_S);
	} else {
		FREE_c_FCSCH_PDU_SDUs_data_IMSI_S (sp->IMSI_S);
		EDFree (sp->IMSI_S);
	}
}

void SETPRESENT_c_FCSCH_PDU_SDUs_data_ESN (c_FCSCH_PDU_SDUs_data* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->ESN_Present == present) return;
	sp->ESN_Present = present;
	if (present) {
		/*-->*/sp->ESN = (c_FCSCH_PDU_SDUs_data_ESN*)EDAlloc (sizeof (c_FCSCH_PDU_SDUs_data_ESN));
		INIT_c_FCSCH_PDU_SDUs_data_ESN (sp->ESN);
	} else {
		FREE_c_FCSCH_PDU_SDUs_data_ESN (sp->ESN);
		EDFree (sp->ESN);
	}
}

void SETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI (c_FCSCH_PDU_SDUs_data* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->IMSI_Present == present) return;
	sp->IMSI_Present = present;
	if (present) {
		/*-->*/sp->IMSI = (c_FCSCH_PDU_SDUs_data_IMSI*)EDAlloc (sizeof (c_FCSCH_PDU_SDUs_data_IMSI));
		INIT_c_FCSCH_PDU_SDUs_data_IMSI (sp->IMSI);
	} else {
		FREE_c_FCSCH_PDU_SDUs_data_IMSI (sp->IMSI);
		EDFree (sp->IMSI);
	}
}

void SETPRESENT_c_FCSCH_PDU_SDUs_data_TMSI (c_FCSCH_PDU_SDUs_data* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->TMSI_Present == present) return;
	sp->TMSI_Present = present;
	if (present) {
		/*-->*/sp->TMSI = (c_FCSCH_PDU_SDUs_data_TMSI*)EDAlloc (sizeof (c_FCSCH_PDU_SDUs_data_TMSI));
		INIT_c_FCSCH_PDU_SDUs_data_TMSI (sp->TMSI);
	} else {
		FREE_c_FCSCH_PDU_SDUs_data_TMSI (sp->TMSI);
		EDFree (sp->TMSI);
	}
}

void SETPRESENT_c_FCSCH_PDU_SDUs_data_Extended_Address (c_FCSCH_PDU_SDUs_data* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->Extended_Address_Present == present) return;
	sp->Extended_Address_Present = present;
	if (present) {
		/*-->*/sp->Extended_Address = (c_FCSCH_PDU_SDUs_data_Extended_Address*)EDAlloc (sizeof (c_FCSCH_PDU_SDUs_data_Extended_Address));
		INIT_c_FCSCH_PDU_SDUs_data_Extended_Address (sp->Extended_Address);
	} else {
		FREE_c_FCSCH_PDU_SDUs_data_Extended_Address (sp->Extended_Address);
		EDFree (sp->Extended_Address);
	}
}

void SETPRESENT_c_FCSCH_PDU_SDUs_data_BROADCAST (c_FCSCH_PDU_SDUs_data* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->BROADCAST_Present == present) return;
	sp->BROADCAST_Present = present;
	if (present) {
		/*-->*/sp->BROADCAST = (c_FCSCH_PDU_SDUs_data_BROADCAST*)EDAlloc (sizeof (c_FCSCH_PDU_SDUs_data_BROADCAST));
		INIT_c_FCSCH_PDU_SDUs_data_BROADCAST (sp->BROADCAST);
	} else {
		FREE_c_FCSCH_PDU_SDUs_data_BROADCAST (sp->BROADCAST);
		EDFree (sp->BROADCAST);
	}
}

/* Free function for struct c_GPM_PDU_page_records_data */
void FREE_c_GPM_PDU_page_records_data (c_GPM_PDU_page_records_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->IMSI_S_Present) {
		EDFree (sp->IMSI_S);
		sp->IMSI_S_Present = ED_FALSE;
	}
	if (sp->TMSI_ZONE.value != NULL) {
		EDFree (sp->TMSI_ZONE.value);
		sp->TMSI_ZONE.value = NULL;
	}
	sp->TMSI_ZONE.usedBits = 0;
	if (sp->BC_ADDR.value != NULL) {
		EDFree (sp->BC_ADDR.value);
		sp->BC_ADDR.value = NULL;
	}
	sp->BC_ADDR.usedBits = 0;
	if (sp->SDU.value != NULL) {
		EDFree (sp->SDU.value);
		sp->SDU.value = NULL;
	}
	sp->SDU.usedBits = 0;

}

void SETPRESENT_c_GPM_PDU_page_records_data_IMSI_S (c_GPM_PDU_page_records_data* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->IMSI_S_Present == present) return;
	sp->IMSI_S_Present = present;
	if (present) {
		/*-->*/sp->IMSI_S = (ED_BYTE*)EDAlloc ((size_t)5);
		ED_RESET_MEM (sp->IMSI_S, 5);
	} else {
		EDFree (sp->IMSI_S);
	}
}

/* Free function for struct c_f_csch_Universal_Page_Block_SUBRECORD_data */
void FREE_c_f_csch_Universal_Page_Block_SUBRECORD_data (c_f_csch_Universal_Page_Block_SUBRECORD_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->BC_ADDR_BLOCK.value != NULL) {
		EDFree (sp->BC_ADDR_BLOCK.value);
		sp->BC_ADDR_BLOCK.value = NULL;
	}
	sp->BC_ADDR_BLOCK.usedBits = 0;
	if (sp->IMSI_ADDR_BLOCK.value != NULL) {
		EDFree (sp->IMSI_ADDR_BLOCK.value);
		sp->IMSI_ADDR_BLOCK.value = NULL;
	}
	sp->IMSI_ADDR_BLOCK.usedBits = 0;
	if (sp->TMSI_ADDR_BLOCK.value != NULL) {
		EDFree (sp->TMSI_ADDR_BLOCK.value);
		sp->TMSI_ADDR_BLOCK.value = NULL;
	}
	sp->TMSI_ADDR_BLOCK.usedBits = 0;
	if (sp->RESERVED_ADDR_BLOCK.value != NULL) {
		EDFree (sp->RESERVED_ADDR_BLOCK.value);
		sp->RESERVED_ADDR_BLOCK.value = NULL;
	}
	sp->RESERVED_ADDR_BLOCK.usedBits = 0;

}

/* Free function for struct c_f_csch_Universal_Page_Block_page_records_data */
void FREE_c_f_csch_Universal_Page_Block_page_records_data (c_f_csch_Universal_Page_Block_page_records_data* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->TMSI_ZONE.value != NULL) {
		EDFree (sp->TMSI_ZONE.value);
		sp->TMSI_ZONE.value = NULL;
	}
	sp->TMSI_ZONE.usedBits = 0;
	if (sp->BC_ADDR_REMAINDER_Present) {
		if (sp->BC_ADDR_REMAINDER->value != NULL) {
			EDFree (sp->BC_ADDR_REMAINDER->value);
			sp->BC_ADDR_REMAINDER->value = NULL;
		}
		sp->BC_ADDR_REMAINDER->usedBits = 0;
		EDFree (sp->BC_ADDR_REMAINDER);
		sp->BC_ADDR_REMAINDER_Present = ED_FALSE;
	}
	if (sp->RESERVED_LEN.value != NULL) {
		EDFree (sp->RESERVED_LEN.value);
		sp->RESERVED_LEN.value = NULL;
	}
	sp->RESERVED_LEN.usedBits = 0;
	if (sp->RESERVED.value != NULL) {
		EDFree (sp->RESERVED.value);
		sp->RESERVED.value = NULL;
	}
	sp->RESERVED.usedBits = 0;
	if (sp->SDU.value != NULL) {
		EDFree (sp->SDU.value);
		sp->SDU.value = NULL;
	}
	sp->SDU.usedBits = 0;

}

void SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_BC_ADDR_REMAINDER (c_f_csch_Universal_Page_Block_page_records_data* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->BC_ADDR_REMAINDER_Present == present) return;
	sp->BC_ADDR_REMAINDER_Present = present;
	if (present) {
		/*-->*/sp->BC_ADDR_REMAINDER = (c_f_csch_Universal_Page_Block_page_records_data_BC_ADDR_REMAINDER*)EDAlloc (sizeof (c_f_csch_Universal_Page_Block_page_records_data_BC_ADDR_REMAINDER));
		sp->BC_ADDR_REMAINDER->value = NULL;
		sp->BC_ADDR_REMAINDER->usedBits = 0;
	} else {
		if (sp->BC_ADDR_REMAINDER->value != NULL) {
			EDFree (sp->BC_ADDR_REMAINDER->value);
			sp->BC_ADDR_REMAINDER->value = NULL;
		}
		sp->BC_ADDR_REMAINDER->usedBits = 0;
		EDFree (sp->BC_ADDR_REMAINDER);
	}
}

/* Free function for struct c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address */
void FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->MEID.value != NULL) {
		EDFree (sp->MEID.value);
		sp->MEID.value = NULL;
	}
	sp->MEID.usedBits = 0;

}

/* Free function for struct c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S */
void FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN */
void FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->ESN.value != NULL) {
		EDFree (sp->ESN.value);
		sp->ESN.value = NULL;
	}
	sp->ESN.usedBits = 0;

}

/* Free function for struct c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI */
void FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->IMSI_CLASS_0_Present) {
		FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0 (sp->IMSI_CLASS_0);
		EDFree (sp->IMSI_CLASS_0);
		sp->IMSI_CLASS_0_Present = ED_FALSE;
	}
	if (sp->IMSI_CLASS_1_Present) {
		FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1 (sp->IMSI_CLASS_1);
		EDFree (sp->IMSI_CLASS_1);
		sp->IMSI_CLASS_1_Present = ED_FALSE;
	}

}

void SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0 (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->IMSI_CLASS_0_Present == present) return;
	sp->IMSI_CLASS_0_Present = present;
	if (present) {
		/*-->*/sp->IMSI_CLASS_0 = (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0*)EDAlloc (sizeof (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0));
		INIT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0 (sp->IMSI_CLASS_0);
	} else {
		FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0 (sp->IMSI_CLASS_0);
		EDFree (sp->IMSI_CLASS_0);
	}
}

void SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1 (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->IMSI_CLASS_1_Present == present) return;
	sp->IMSI_CLASS_1_Present = present;
	if (present) {
		/*-->*/sp->IMSI_CLASS_1 = (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1*)EDAlloc (sizeof (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1));
		INIT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1 (sp->IMSI_CLASS_1);
	} else {
		FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1 (sp->IMSI_CLASS_1);
		EDFree (sp->IMSI_CLASS_1);
	}
}

/* Free function for struct c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI */
void FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->TMSI_ZONE.value != NULL) {
		EDFree (sp->TMSI_ZONE.value);
		sp->TMSI_ZONE.value = NULL;
	}
	sp->TMSI_ZONE.usedBits = 0;
	if (sp->TMSI_CODE_ADDR.value != NULL) {
		EDFree (sp->TMSI_CODE_ADDR.value);
		sp->TMSI_CODE_ADDR.value = NULL;
	}
	sp->TMSI_CODE_ADDR.usedBits = 0;

}

/* Free function for struct c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST */
void FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->BC_ADDR.value != NULL) {
		EDFree (sp->BC_ADDR.value);
		sp->BC_ADDR.value = NULL;
	}
	sp->BC_ADDR.usedBits = 0;

}

/* Free function for struct c_r_csch_PDU_LAC_Length */
void FREE_c_r_csch_PDU_LAC_Length (c_r_csch_PDU_LAC_Length* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_r_csch_PDU_Message_Type */
void FREE_c_r_csch_PDU_Message_Type (c_r_csch_PDU_Message_Type* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_r_csch_PDU_ARQ */
void FREE_c_r_csch_PDU_ARQ (c_r_csch_PDU_ARQ* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_r_csch_PDU_Addressing */
void FREE_c_r_csch_PDU_Addressing (c_r_csch_PDU_Addressing* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->MEID_Present) {
		EDFree (sp->MEID);
		sp->MEID_Present = ED_FALSE;
	}
	if (sp->IMSI_class_specific_subfields_Present) {
		FREE_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields (sp->IMSI_class_specific_subfields);
		EDFree (sp->IMSI_class_specific_subfields);
		sp->IMSI_class_specific_subfields_Present = ED_FALSE;
	}
	if (sp->TMSI_ZONE_Present) {
		if (sp->TMSI_ZONE->value != NULL) {
			EDFree (sp->TMSI_ZONE->value);
			sp->TMSI_ZONE->value = NULL;
		}
		sp->TMSI_ZONE->usedBits = 0;
		EDFree (sp->TMSI_ZONE);
		sp->TMSI_ZONE_Present = ED_FALSE;
	}
	if (sp->TMSI_CODE_ADDR_Present) {
		if (sp->TMSI_CODE_ADDR->value != NULL) {
			EDFree (sp->TMSI_CODE_ADDR->value);
			sp->TMSI_CODE_ADDR->value = NULL;
		}
		sp->TMSI_CODE_ADDR->usedBits = 0;
		EDFree (sp->TMSI_CODE_ADDR);
		sp->TMSI_CODE_ADDR_Present = ED_FALSE;
	}

}

void SETPRESENT_c_r_csch_PDU_Addressing_MEID (c_r_csch_PDU_Addressing* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->MEID_Present == present) return;
	sp->MEID_Present = present;
	if (present) {
		/*-->*/sp->MEID = (ED_BYTE*)EDAlloc ((size_t)7);
		ED_RESET_MEM (sp->MEID, 7);
	} else {
		EDFree (sp->MEID);
	}
}

void SETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields (c_r_csch_PDU_Addressing* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->IMSI_class_specific_subfields_Present == present) return;
	sp->IMSI_class_specific_subfields_Present = present;
	if (present) {
		/*-->*/sp->IMSI_class_specific_subfields = (c_r_csch_PDU_Addressing_IMSI_class_specific_subfields*)EDAlloc (sizeof (c_r_csch_PDU_Addressing_IMSI_class_specific_subfields));
		INIT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields (sp->IMSI_class_specific_subfields);
	} else {
		FREE_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields (sp->IMSI_class_specific_subfields);
		EDFree (sp->IMSI_class_specific_subfields);
	}
}

void SETPRESENT_c_r_csch_PDU_Addressing_TMSI_ZONE (c_r_csch_PDU_Addressing* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->TMSI_ZONE_Present == present) return;
	sp->TMSI_ZONE_Present = present;
	if (present) {
		/*-->*/sp->TMSI_ZONE = (c_r_csch_PDU_Addressing_TMSI_ZONE*)EDAlloc (sizeof (c_r_csch_PDU_Addressing_TMSI_ZONE));
		sp->TMSI_ZONE->value = NULL;
		sp->TMSI_ZONE->usedBits = 0;
	} else {
		if (sp->TMSI_ZONE->value != NULL) {
			EDFree (sp->TMSI_ZONE->value);
			sp->TMSI_ZONE->value = NULL;
		}
		sp->TMSI_ZONE->usedBits = 0;
		EDFree (sp->TMSI_ZONE);
	}
}

void SETPRESENT_c_r_csch_PDU_Addressing_TMSI_CODE_ADDR (c_r_csch_PDU_Addressing* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->TMSI_CODE_ADDR_Present == present) return;
	sp->TMSI_CODE_ADDR_Present = present;
	if (present) {
		/*-->*/sp->TMSI_CODE_ADDR = (c_r_csch_PDU_Addressing_TMSI_CODE_ADDR*)EDAlloc (sizeof (c_r_csch_PDU_Addressing_TMSI_CODE_ADDR));
		sp->TMSI_CODE_ADDR->value = NULL;
		sp->TMSI_CODE_ADDR->usedBits = 0;
	} else {
		if (sp->TMSI_CODE_ADDR->value != NULL) {
			EDFree (sp->TMSI_CODE_ADDR->value);
			sp->TMSI_CODE_ADDR->value = NULL;
		}
		sp->TMSI_CODE_ADDR->usedBits = 0;
		EDFree (sp->TMSI_CODE_ADDR);
	}
}

/* Free function for struct c_r_csch_PDU_Authentication */
void FREE_c_r_csch_PDU_Authentication (c_r_csch_PDU_Authentication* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_r_csch_PDU_Extended_Encryption */
void FREE_c_r_csch_PDU_Extended_Encryption (c_r_csch_PDU_Extended_Encryption* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for variable-sized sequence c_r_csch_Radio_Environment_Report_ADD_PILOTS */
void FREE_c_r_csch_Radio_Environment_Report_ADD_PILOTS (c_r_csch_Radio_Environment_Report_ADD_PILOTS* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data (sp->data[i]);
		EDFree (sp->data[i]);
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_r_csch_Radio_Environment_Report */
void FREE_c_r_csch_Radio_Environment_Report (c_r_csch_Radio_Environment_Report* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->ADD_PILOTS.items; i0++) {
		FREE_c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data (sp->ADD_PILOTS.data[i0]);
		EDFree (sp->ADD_PILOTS.data[i0]);
	}
	if (sp->ADD_PILOTS.data) {EDFree (sp->ADD_PILOTS.data); sp->ADD_PILOTS.data = NULL; sp->ADD_PILOTS.allocatedItems=0; /*FR02A*/}
	if (sp->Aux_Radio_Environment_Report_Present) {
		FREE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report (sp->Aux_Radio_Environment_Report);
		EDFree (sp->Aux_Radio_Environment_Report);
		sp->Aux_Radio_Environment_Report_Present = ED_FALSE;
	}

}

void SETPRESENT_c_r_csch_Radio_Environment_Report_Aux_Radio_Environment_Report (c_r_csch_Radio_Environment_Report* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->Aux_Radio_Environment_Report_Present == present) return;
	sp->Aux_Radio_Environment_Report_Present = present;
	if (present) {
		/*-->*/sp->Aux_Radio_Environment_Report = (c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report*)EDAlloc (sizeof (c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report));
		INIT_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report (sp->Aux_Radio_Environment_Report);
	} else {
		FREE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report (sp->Aux_Radio_Environment_Report);
		EDFree (sp->Aux_Radio_Environment_Report);
	}
}

/* Free function for struct c_f_dsch_PDU_Regular_Message_Type */
void FREE_c_f_dsch_PDU_Regular_Message_Type (c_f_dsch_PDU_Regular_Message_Type* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_f_dsch_PDU_Regular_ARQ */
void FREE_c_f_dsch_PDU_Regular_ARQ (c_f_dsch_PDU_Regular_ARQ* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_f_dsch_PDU_Regular_Encryption */
void FREE_c_f_dsch_PDU_Regular_Encryption (c_f_dsch_PDU_Regular_Encryption* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_f_dsch_PDU_Regular_Integrity_Fields */
void FREE_c_f_dsch_PDU_Regular_Integrity_Fields (c_f_dsch_PDU_Regular_Integrity_Fields* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_f_dsch_PDU_Regular_Extended_Encryption */
void FREE_c_f_dsch_PDU_Regular_Extended_Encryption (c_f_dsch_PDU_Regular_Extended_Encryption* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_f_dsch_PDU_Mini_ARQ */
void FREE_c_f_dsch_PDU_Mini_ARQ (c_f_dsch_PDU_Mini_ARQ* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_f_dsch_PDU_Mini_Message_Type */
void FREE_c_f_dsch_PDU_Mini_Message_Type (c_f_dsch_PDU_Mini_Message_Type* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_r_dsch_PDU_Regular_Message_Type */
void FREE_c_r_dsch_PDU_Regular_Message_Type (c_r_dsch_PDU_Regular_Message_Type* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_r_dsch_PDU_Regular_ARQ */
void FREE_c_r_dsch_PDU_Regular_ARQ (c_r_dsch_PDU_Regular_ARQ* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_r_dsch_PDU_Regular_Encryption */
void FREE_c_r_dsch_PDU_Regular_Encryption (c_r_dsch_PDU_Regular_Encryption* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_r_dsch_PDU_Regular_Integrity_Fields */
void FREE_c_r_dsch_PDU_Regular_Integrity_Fields (c_r_dsch_PDU_Regular_Integrity_Fields* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_r_dsch_PDU_Regular_Extended_Encryption */
void FREE_c_r_dsch_PDU_Regular_Extended_Encryption (c_r_dsch_PDU_Regular_Extended_Encryption* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_r_dsch_PDU_Mini_ARQ */
void FREE_c_r_dsch_PDU_Mini_ARQ (c_r_dsch_PDU_Mini_ARQ* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for struct c_r_dsch_PDU_Mini_Message_Type */
void FREE_c_r_dsch_PDU_Mini_Message_Type (c_r_dsch_PDU_Mini_Message_Type* sp) {
ED_WARNING_REMOVER(sp);

}

/* Free function for variable-sized sequence c_FCSCH_PDU_SDUs */
void FREE_c_FCSCH_PDU_SDUs (c_FCSCH_PDU_SDUs* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_FCSCH_PDU_SDUs_data (sp->data[i]);
		EDFree (sp->data[i]);
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_FCSCH_PDU */
void FREE_c_FCSCH_PDU (c_FCSCH_PDU* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	for (i0=0; i0<sp->SDUs.items; i0++) {
		FREE_c_FCSCH_PDU_SDUs_data (sp->SDUs.data[i0]);
		EDFree (sp->SDUs.data[i0]);
	}
	if (sp->SDUs.data) {EDFree (sp->SDUs.data); sp->SDUs.data = NULL; sp->SDUs.allocatedItems=0; /*FR02A*/}

}

/* Free function for struct c_FCSCH_SYNC_BROADCAST_PDU */
void FREE_c_FCSCH_SYNC_BROADCAST_PDU (c_FCSCH_SYNC_BROADCAST_PDU* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->SDU.value != NULL) {
		EDFree (sp->SDU.value);
		sp->SDU.value = NULL;
	}
	sp->SDU.usedBits = 0;

}

/* Free function for struct c_FCSCH_NON_PRIMARY_BROADCAST_PDU */
void FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU (c_FCSCH_NON_PRIMARY_BROADCAST_PDU* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->IMSI_S_Present) {
		FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S (sp->IMSI_S);
		EDFree (sp->IMSI_S);
		sp->IMSI_S_Present = ED_FALSE;
	}
	if (sp->ESN_Present) {
		FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN (sp->ESN);
		EDFree (sp->ESN);
		sp->ESN_Present = ED_FALSE;
	}
	if (sp->IMSI_Present) {
		FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI (sp->IMSI);
		EDFree (sp->IMSI);
		sp->IMSI_Present = ED_FALSE;
	}
	if (sp->TMSI_Present) {
		FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI (sp->TMSI);
		EDFree (sp->TMSI);
		sp->TMSI_Present = ED_FALSE;
	}
	if (sp->Extended_Address_Present) {
		FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address (sp->Extended_Address);
		EDFree (sp->Extended_Address);
		sp->Extended_Address_Present = ED_FALSE;
	}
	if (sp->BROADCAST_Present) {
		FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST (sp->BROADCAST);
		EDFree (sp->BROADCAST);
		sp->BROADCAST_Present = ED_FALSE;
	}
	if (sp->SDU.value != NULL) {
		EDFree (sp->SDU.value);
		sp->SDU.value = NULL;
	}
	sp->SDU.usedBits = 0;

}

void SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S (c_FCSCH_NON_PRIMARY_BROADCAST_PDU* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->IMSI_S_Present == present) return;
	sp->IMSI_S_Present = present;
	if (present) {
		/*-->*/sp->IMSI_S = (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S*)EDAlloc (sizeof (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S));
		INIT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S (sp->IMSI_S);
	} else {
		FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S (sp->IMSI_S);
		EDFree (sp->IMSI_S);
	}
}

void SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN (c_FCSCH_NON_PRIMARY_BROADCAST_PDU* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->ESN_Present == present) return;
	sp->ESN_Present = present;
	if (present) {
		/*-->*/sp->ESN = (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN*)EDAlloc (sizeof (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN));
		INIT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN (sp->ESN);
	} else {
		FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN (sp->ESN);
		EDFree (sp->ESN);
	}
}

void SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI (c_FCSCH_NON_PRIMARY_BROADCAST_PDU* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->IMSI_Present == present) return;
	sp->IMSI_Present = present;
	if (present) {
		/*-->*/sp->IMSI = (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI*)EDAlloc (sizeof (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI));
		INIT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI (sp->IMSI);
	} else {
		FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI (sp->IMSI);
		EDFree (sp->IMSI);
	}
}

void SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI (c_FCSCH_NON_PRIMARY_BROADCAST_PDU* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->TMSI_Present == present) return;
	sp->TMSI_Present = present;
	if (present) {
		/*-->*/sp->TMSI = (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI*)EDAlloc (sizeof (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI));
		INIT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI (sp->TMSI);
	} else {
		FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI (sp->TMSI);
		EDFree (sp->TMSI);
	}
}

void SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address (c_FCSCH_NON_PRIMARY_BROADCAST_PDU* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->Extended_Address_Present == present) return;
	sp->Extended_Address_Present = present;
	if (present) {
		/*-->*/sp->Extended_Address = (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address*)EDAlloc (sizeof (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address));
		INIT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address (sp->Extended_Address);
	} else {
		FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address (sp->Extended_Address);
		EDFree (sp->Extended_Address);
	}
}

void SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST (c_FCSCH_NON_PRIMARY_BROADCAST_PDU* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->BROADCAST_Present == present) return;
	sp->BROADCAST_Present = present;
	if (present) {
		/*-->*/sp->BROADCAST = (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST*)EDAlloc (sizeof (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST));
		INIT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST (sp->BROADCAST);
	} else {
		FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST (sp->BROADCAST);
		EDFree (sp->BROADCAST);
	}
}

/* Free function for variable-sized sequence c_GPM_PDU_page_records */
void FREE_c_GPM_PDU_page_records (c_GPM_PDU_page_records* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_GPM_PDU_page_records_data (sp->data[i]);
		EDFree (sp->data[i]);
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_GPM_PDU */
void FREE_c_GPM_PDU (c_GPM_PDU* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	if (sp->ADD_PFIELD.value != NULL) {
		EDFree (sp->ADD_PFIELD.value);
		sp->ADD_PFIELD.value = NULL;
	}
	sp->ADD_PFIELD.usedBits = 0;
	for (i0=0; i0<sp->page_records.items; i0++) {
		FREE_c_GPM_PDU_page_records_data (sp->page_records.data[i0]);
		EDFree (sp->page_records.data[i0]);
	}
	if (sp->page_records.data) {EDFree (sp->page_records.data); sp->page_records.data = NULL; sp->page_records.allocatedItems=0; /*FR02A*/}

}

/* Free function for struct c_UPM_PDU */
void FREE_c_UPM_PDU (c_UPM_PDU* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->Universal_Page_Block.value != NULL) {
		EDFree (sp->Universal_Page_Block.value);
		sp->Universal_Page_Block.value = NULL;
	}
	sp->Universal_Page_Block.usedBits = 0;

}

/* Free function for variable-sized sequence c_f_csch_Universal_Page_Block_BURST_TYPE */
void FREE_c_f_csch_Universal_Page_Block_BURST_TYPE (c_f_csch_Universal_Page_Block_BURST_TYPE* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_f_csch_Universal_Page_Block_SUBRECORD */
void FREE_c_f_csch_Universal_Page_Block_SUBRECORD (c_f_csch_Universal_Page_Block_SUBRECORD* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_f_csch_Universal_Page_Block_SUBRECORD_data (sp->data[i]);
		EDFree (sp->data[i]);
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for variable-sized sequence c_f_csch_Universal_Page_Block_page_records */
void FREE_c_f_csch_Universal_Page_Block_page_records (c_f_csch_Universal_Page_Block_page_records* sp) {
	int i;
	for (i=0; i<sp->items; i++) {
		FREE_c_f_csch_Universal_Page_Block_page_records_data (sp->data[i]);
		EDFree (sp->data[i]);
	}

	if (sp->data) {EDFree (sp->data); sp->data=NULL; sp->allocatedItems = 0;/*FR03*/}

}
/* Free function for struct c_f_csch_Universal_Page_Block */
void FREE_c_f_csch_Universal_Page_Block (c_f_csch_Universal_Page_Block* sp) {
	int i0;
ED_WARNING_REMOVER(sp);
	if (sp->BURST_TYPE.data) {EDFree (sp->BURST_TYPE.data); sp->BURST_TYPE.data = NULL; sp->BURST_TYPE.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->SUBRECORD.items; i0++) {
		FREE_c_f_csch_Universal_Page_Block_SUBRECORD_data (sp->SUBRECORD.data[i0]);
		EDFree (sp->SUBRECORD.data[i0]);
	}
	if (sp->SUBRECORD.data) {EDFree (sp->SUBRECORD.data); sp->SUBRECORD.data = NULL; sp->SUBRECORD.allocatedItems=0; /*FR02A*/}
	for (i0=0; i0<sp->page_records.items; i0++) {
		FREE_c_f_csch_Universal_Page_Block_page_records_data (sp->page_records.data[i0]);
		EDFree (sp->page_records.data[i0]);
	}
	if (sp->page_records.data) {EDFree (sp->page_records.data); sp->page_records.data = NULL; sp->page_records.allocatedItems=0; /*FR02A*/}

}

/* Free function for struct c_r_csch_PDU */
void FREE_c_r_csch_PDU (c_r_csch_PDU* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_r_csch_PDU_Message_Type (&(sp->Message_Type));
	if (sp->LAC_Length_Present) {
		FREE_c_r_csch_PDU_LAC_Length (sp->LAC_Length);
		EDFree (sp->LAC_Length);
		sp->LAC_Length_Present = ED_FALSE;
	}
	FREE_c_r_csch_PDU_ARQ (&(sp->ARQ));
	FREE_c_r_csch_PDU_Addressing (&(sp->Addressing));
	FREE_c_r_csch_PDU_Authentication (&(sp->Authentication));
	if (sp->Extended_Encryption_Present) {
		FREE_c_r_csch_PDU_Extended_Encryption (sp->Extended_Encryption);
		EDFree (sp->Extended_Encryption);
		sp->Extended_Encryption_Present = ED_FALSE;
	}
	if (sp->Radio_Environment_Report_Present) {
		FREE_c_r_csch_Radio_Environment_Report (sp->Radio_Environment_Report);
		EDFree (sp->Radio_Environment_Report);
		sp->Radio_Environment_Report_Present = ED_FALSE;
	}
	if (sp->SDU.value != NULL) {
		EDFree (sp->SDU.value);
		sp->SDU.value = NULL;
	}
	sp->SDU.usedBits = 0;

}

void SETPRESENT_c_r_csch_PDU_LAC_Length (c_r_csch_PDU* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->LAC_Length_Present == present) return;
	sp->LAC_Length_Present = present;
	if (present) {
		/*-->*/sp->LAC_Length = (c_r_csch_PDU_LAC_Length*)EDAlloc (sizeof (c_r_csch_PDU_LAC_Length));
		INIT_c_r_csch_PDU_LAC_Length (sp->LAC_Length);
	} else {
		FREE_c_r_csch_PDU_LAC_Length (sp->LAC_Length);
		EDFree (sp->LAC_Length);
	}
}

void SETPRESENT_c_r_csch_PDU_Extended_Encryption (c_r_csch_PDU* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->Extended_Encryption_Present == present) return;
	sp->Extended_Encryption_Present = present;
	if (present) {
		/*-->*/sp->Extended_Encryption = (c_r_csch_PDU_Extended_Encryption*)EDAlloc (sizeof (c_r_csch_PDU_Extended_Encryption));
		INIT_c_r_csch_PDU_Extended_Encryption (sp->Extended_Encryption);
	} else {
		FREE_c_r_csch_PDU_Extended_Encryption (sp->Extended_Encryption);
		EDFree (sp->Extended_Encryption);
	}
}

void SETPRESENT_c_r_csch_PDU_Radio_Environment_Report (c_r_csch_PDU* sp, ED_BOOLEAN present)
{
	/* Do nothing if already compliant to the request */
	if (sp->Radio_Environment_Report_Present == present) return;
	sp->Radio_Environment_Report_Present = present;
	if (present) {
		/*-->*/sp->Radio_Environment_Report = (c_r_csch_Radio_Environment_Report*)EDAlloc (sizeof (c_r_csch_Radio_Environment_Report));
		INIT_c_r_csch_Radio_Environment_Report (sp->Radio_Environment_Report);
	} else {
		FREE_c_r_csch_Radio_Environment_Report (sp->Radio_Environment_Report);
		EDFree (sp->Radio_Environment_Report);
	}
}

/* Free function for struct c_f_dsch_PDU_Regular */
void FREE_c_f_dsch_PDU_Regular (c_f_dsch_PDU_Regular* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_f_dsch_PDU_Regular_Message_Type (&(sp->Message_Type));
	FREE_c_f_dsch_PDU_Regular_ARQ (&(sp->ARQ));
	FREE_c_f_dsch_PDU_Regular_Encryption (&(sp->Encryption));
	FREE_c_f_dsch_PDU_Regular_Integrity_Fields (&(sp->Integrity_Fields));
	FREE_c_f_dsch_PDU_Regular_Extended_Encryption (&(sp->Extended_Encryption));
	if (sp->SDU.value != NULL) {
		EDFree (sp->SDU.value);
		sp->SDU.value = NULL;
	}
	sp->SDU.usedBits = 0;

}

/* Free function for struct c_f_dsch_PDU_Mini */
void FREE_c_f_dsch_PDU_Mini (c_f_dsch_PDU_Mini* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_f_dsch_PDU_Mini_ARQ (&(sp->ARQ));
	FREE_c_f_dsch_PDU_Mini_Message_Type (&(sp->Message_Type));
	if (sp->SDU.value != NULL) {
		EDFree (sp->SDU.value);
		sp->SDU.value = NULL;
	}
	sp->SDU.usedBits = 0;

}

/* Free function for struct c_r_dsch_PDU_Regular */
void FREE_c_r_dsch_PDU_Regular (c_r_dsch_PDU_Regular* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_r_dsch_PDU_Regular_Message_Type (&(sp->Message_Type));
	FREE_c_r_dsch_PDU_Regular_ARQ (&(sp->ARQ));
	FREE_c_r_dsch_PDU_Regular_Encryption (&(sp->Encryption));
	FREE_c_r_dsch_PDU_Regular_Integrity_Fields (&(sp->Integrity_Fields));
	FREE_c_r_dsch_PDU_Regular_Extended_Encryption (&(sp->Extended_Encryption));
	if (sp->SDU.value != NULL) {
		EDFree (sp->SDU.value);
		sp->SDU.value = NULL;
	}
	sp->SDU.usedBits = 0;

}

/* Free function for struct c_r_dsch_PDU_Mini */
void FREE_c_r_dsch_PDU_Mini (c_r_dsch_PDU_Mini* sp) {
ED_WARNING_REMOVER(sp);
	FREE_c_r_dsch_PDU_Mini_ARQ (&(sp->ARQ));
	FREE_c_r_dsch_PDU_Mini_Message_Type (&(sp->Message_Type));
	if (sp->SDU.value != NULL) {
		EDFree (sp->SDU.value);
		sp->SDU.value = NULL;
	}
	sp->SDU.usedBits = 0;

}

/* Free function for struct c_f_csch_UPM_Mobile_Station_Addressed */
void FREE_c_f_csch_UPM_Mobile_Station_Addressed (c_f_csch_UPM_Mobile_Station_Addressed* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->ADD_MS_RECORD.value != NULL) {
		EDFree (sp->ADD_MS_RECORD.value);
		sp->ADD_MS_RECORD.value = NULL;
	}
	sp->ADD_MS_RECORD.usedBits = 0;

}

/* Free function for struct c_f_csch_UPM_Enhanced_Broadcast_with_time_offset */
void FREE_c_f_csch_UPM_Enhanced_Broadcast_with_time_offset (c_f_csch_UPM_Enhanced_Broadcast_with_time_offset* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->ADD_BCAST_RECORD.value != NULL) {
		EDFree (sp->ADD_BCAST_RECORD.value);
		sp->ADD_BCAST_RECORD.value = NULL;
	}
	sp->ADD_BCAST_RECORD.usedBits = 0;

}

/* Free function for struct c_f_csch_UPM_Enhanced_Broadcast_without_time_offset */
void FREE_c_f_csch_UPM_Enhanced_Broadcast_without_time_offset (c_f_csch_UPM_Enhanced_Broadcast_without_time_offset* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->ADD_BCAST_RECORD.value != NULL) {
		EDFree (sp->ADD_BCAST_RECORD.value);
		sp->ADD_BCAST_RECORD.value = NULL;
	}
	sp->ADD_BCAST_RECORD.usedBits = 0;

}

/* Free function for struct c_GenericTLV_cs0004 */
void FREE_c_GenericTLV_cs0004 (c_GenericTLV_cs0004* sp) {
ED_WARNING_REMOVER(sp);
	if (sp->TLV_Data.value != NULL) {
		EDFree (sp->TLV_Data.value);
		sp->TLV_Data.value = NULL;
	}
	sp->TLV_Data.usedBits = 0;

}

/* SETITEMS commands for type 'c_r_csch_Radio_Environment_Report_ADD_PILOTS'. Existing items are not changed. */
int SETITEMS_c_r_csch_Radio_Environment_Report_ADD_PILOTS (c_r_csch_Radio_Environment_Report_ADD_PILOTS* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data** tmp;
		tmp = (c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data**)EDAlloc (sizeof (c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data*)EDAlloc (sizeof (c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data));
			INIT_c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data (sequence->data[i]);
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data (sequence->data[i]);
				EDFree (sequence->data[i]);
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* SETITEMS commands for type 'c_FCSCH_PDU_SDUs'. Existing items are not changed. */
int SETITEMS_c_FCSCH_PDU_SDUs (c_FCSCH_PDU_SDUs* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_FCSCH_PDU_SDUs_data** tmp;
		tmp = (c_FCSCH_PDU_SDUs_data**)EDAlloc (sizeof (c_FCSCH_PDU_SDUs_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_FCSCH_PDU_SDUs_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_FCSCH_PDU_SDUs_data*)EDAlloc (sizeof (c_FCSCH_PDU_SDUs_data));
			INIT_c_FCSCH_PDU_SDUs_data (sequence->data[i]);
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_FCSCH_PDU_SDUs_data (sequence->data[i]);
				EDFree (sequence->data[i]);
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* SETITEMS commands for type 'c_GPM_PDU_page_records'. Existing items are not changed. */
int SETITEMS_c_GPM_PDU_page_records (c_GPM_PDU_page_records* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_GPM_PDU_page_records_data** tmp;
		tmp = (c_GPM_PDU_page_records_data**)EDAlloc (sizeof (c_GPM_PDU_page_records_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_GPM_PDU_page_records_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_GPM_PDU_page_records_data*)EDAlloc (sizeof (c_GPM_PDU_page_records_data));
			INIT_c_GPM_PDU_page_records_data (sequence->data[i]);
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_GPM_PDU_page_records_data (sequence->data[i]);
				EDFree (sequence->data[i]);
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* SETITEMS commands for type 'c_f_csch_Universal_Page_Block_BURST_TYPE'. Existing items are not changed. */
int SETITEMS_c_f_csch_Universal_Page_Block_BURST_TYPE (c_f_csch_Universal_Page_Block_BURST_TYPE* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		ED_OCTET* tmp;
		tmp = (ED_OCTET*)EDAlloc (sizeof (ED_OCTET) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (ED_OCTET) * (size_t)sequence->items);
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

/* SETITEMS commands for type 'c_f_csch_Universal_Page_Block_SUBRECORD'. Existing items are not changed. */
int SETITEMS_c_f_csch_Universal_Page_Block_SUBRECORD (c_f_csch_Universal_Page_Block_SUBRECORD* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_f_csch_Universal_Page_Block_SUBRECORD_data** tmp;
		tmp = (c_f_csch_Universal_Page_Block_SUBRECORD_data**)EDAlloc (sizeof (c_f_csch_Universal_Page_Block_SUBRECORD_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_f_csch_Universal_Page_Block_SUBRECORD_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_f_csch_Universal_Page_Block_SUBRECORD_data*)EDAlloc (sizeof (c_f_csch_Universal_Page_Block_SUBRECORD_data));
			INIT_c_f_csch_Universal_Page_Block_SUBRECORD_data (sequence->data[i]);
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_f_csch_Universal_Page_Block_SUBRECORD_data (sequence->data[i]);
				EDFree (sequence->data[i]);
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

/* SETITEMS commands for type 'c_f_csch_Universal_Page_Block_page_records'. Existing items are not changed. */
int SETITEMS_c_f_csch_Universal_Page_Block_page_records (c_f_csch_Universal_Page_Block_page_records* sequence, int desiredItems)
{
	int i;
	/* ALK-UNI */
	if (sequence->allocatedItems < desiredItems) {
		int newSize = desiredItems + 0;
		c_f_csch_Universal_Page_Block_page_records_data** tmp;
		tmp = (c_f_csch_Universal_Page_Block_page_records_data**)EDAlloc (sizeof (c_f_csch_Universal_Page_Block_page_records_data*) * (size_t)(newSize));
		if (sequence->data) {
			if (tmp != NULL && sequence->items > 0) {
				memcpy (tmp, sequence->data, sizeof (c_f_csch_Universal_Page_Block_page_records_data*) * (size_t)sequence->items);
			}
			EDFree (sequence->data);
		}
		sequence->allocatedItems = newSize;
		sequence->data = tmp;
	
	}

	if (desiredItems > sequence->items) {
		for (i=sequence->items; i<desiredItems; i++) {
			sequence->data[i] = (c_f_csch_Universal_Page_Block_page_records_data*)EDAlloc (sizeof (c_f_csch_Universal_Page_Block_page_records_data));
			INIT_c_f_csch_Universal_Page_Block_page_records_data (sequence->data[i]);
		}
	}
	 else {
		for (i=desiredItems; i<sequence->items; i++) {
				FREE_c_f_csch_Universal_Page_Block_page_records_data (sequence->data[i]);
				EDFree (sequence->data[i]);
			}
	}

	sequence->items = desiredItems;
	return ED_NO_ERRORS;
}

