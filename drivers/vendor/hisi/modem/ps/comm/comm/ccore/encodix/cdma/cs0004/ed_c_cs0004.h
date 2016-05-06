/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __ed_c_cs0004_h_H
#define __ed_c_cs0004_h_H
#include "ed_dynamic.h"
#include "ed_data.h"
#if ED_COMMON_CRC != 0x328E3625 && ED_VERSION != 10152 && ED_VERSION != 10153
#error Invalid Encodix library files linked; used those distributed with Encodix 1.0.154
#endif

#ifndef ED_DOT
#define ED_DOT ->
#endif
#ifndef ED_AMP
#define ED_AMP(a) a
#endif
#define ED_DYNAMIC_DEFAULT 1

#ifdef __cplusplus
extern "C" {
#endif


/* Access member 'QOF' of type 'c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh' as a variable reference */
#define VAR_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh_QOF(var) var

/* Access member 'QOF' of type 'c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh' as a pointer */
#define PTR_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh_QOF(var) (&var)

/* Access member 'WALSH_LENGTH' of type 'c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh' as a variable reference */
#define VAR_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh_WALSH_LENGTH(var) var

/* Access member 'WALSH_LENGTH' of type 'c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh' as a pointer */
#define PTR_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh_WALSH_LENGTH(var) (&var)

/* Access member 'PILOT_WALSH' of type 'c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh' as a variable reference */
#define VAR_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh_PILOT_WALSH(var) var

/* Access member 'PILOT_WALSH' of type 'c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh' as a pointer */
#define PTR_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh_PILOT_WALSH(var) (&var)

/* DEFINITION OF BINARY c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh_PILOT_WALSH */
typedef struct _c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh_PILOT_WALSH {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh_PILOT_WALSH;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh_PILOT_WALSH(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh {

	ED_OCTET QOF; /* ODY01a *//*GBD01b*/
	ED_OCTET WALSH_LENGTH; /* ODY01a *//*GBD01b*/
	c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh_PILOT_WALSH PILOT_WALSH; /* Static, variable size; bits needed 16 *//*GBD01b*/

}	c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh;
#define INIT_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh(sp) ED_RESET_MEM ((sp), sizeof (c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh))
/*FRK03a*/
void FREE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh(c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh* sp);

/* Access member 'Walsh' of type 'c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields' as a variable reference */
#define VAR_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh(var) (*var)

/* Access member 'Walsh' of type 'c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields' as a pointer */
#define PTR_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh(var) var


/*-A----------------------------------*/
typedef struct _c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields {

	c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh *Walsh; /* ODY01 *//*GBD01b*/
	ED_BOOLEAN Walsh_Present;

}	c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields;
#define INIT_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields(sp) ED_RESET_MEM ((sp), sizeof (c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields))
/*FRK03a*/
void FREE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields(c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields* sp);
void SETPRESENT_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh (c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields* sp, ED_BOOLEAN present);
#define GETPRESENT_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields_Walsh(sp) ((sp)->Walsh_Present)

/* Access member 'IMSI_CLASS_0_TYPE' of type 'c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0_IMSI_CLASS_0_TYPE(var) var

/* Access member 'IMSI_CLASS_0_TYPE' of type 'c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0_IMSI_CLASS_0_TYPE(var) (&var)

/* Access member 'MCC10' of type 'c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0_MCC10(var) var

/* Access member 'MCC10' of type 'c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0_MCC10(var) (&var)

/* Access member 'IMSI_11_12' of type 'c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0_IMSI_11_12(var) var

/* Access member 'IMSI_11_12' of type 'c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0_IMSI_11_12(var) (&var)

/* Access member 'IMSI_S' of type 'c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0_IMSI_S(var) var

/* Access member 'IMSI_S' of type 'c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0_IMSI_S(var) (&var)


/*-A----------------------------------*/
typedef struct _c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0 {

	ED_OCTET IMSI_CLASS_0_TYPE; /* ODY01a *//*GBD01b*/
	ED_LONG MCC10; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN MCC10_Present;
	ED_OCTET IMSI_11_12; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN IMSI_11_12_Present;
	ED_BYTE IMSI_S [5]; /* Static, fixed size; bits needed 34 *//*GBD01b*/

}	c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0;
#define INIT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0(sp) ED_RESET_MEM ((sp), sizeof (c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0))
/*FRK03a*/
void FREE_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0(c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0* sp);
#define SETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0_MCC10(sp,present) ((sp)->MCC10_Present = present)
#define GETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0_MCC10(sp) ((sp)->MCC10_Present)
#define SETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0_IMSI_11_12(sp,present) ((sp)->IMSI_11_12_Present = present)
#define GETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0_IMSI_11_12(sp) ((sp)->IMSI_11_12_Present)

/* Access member 'IMSI_CLASS_1_TYPE' of type 'c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1_IMSI_CLASS_1_TYPE(var) var

/* Access member 'IMSI_CLASS_1_TYPE' of type 'c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1_IMSI_CLASS_1_TYPE(var) (&var)

/* Access member 'IMSI_ADDR_NUM' of type 'c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1_IMSI_ADDR_NUM(var) var

/* Access member 'IMSI_ADDR_NUM' of type 'c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1_IMSI_ADDR_NUM(var) (&var)

/* Access member 'MCC' of type 'c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1_MCC(var) var

/* Access member 'MCC' of type 'c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1_MCC(var) (&var)

/* Access member 'IMSI_11_12' of type 'c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1_IMSI_11_12(var) var

/* Access member 'IMSI_11_12' of type 'c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1_IMSI_11_12(var) (&var)

/* Access member 'IMSI_S' of type 'c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1_IMSI_S(var) var

/* Access member 'IMSI_S' of type 'c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1_IMSI_S(var) (&var)


/*-A----------------------------------*/
typedef struct _c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1 {

	ED_BOOLEAN IMSI_CLASS_1_TYPE; /* ODY01a *//*GBD01b*/
	ED_OCTET IMSI_ADDR_NUM; /* ODY01a *//*GBD01b*/
	ED_LONG MCC; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN MCC_Present;
	ED_OCTET IMSI_11_12; /* ODY01a *//*GBD01b*/
	ED_BYTE IMSI_S [5]; /* Static, fixed size; bits needed 34 *//*GBD01b*/

}	c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1;
#define INIT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1(sp) ED_RESET_MEM ((sp), sizeof (c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1))
/*FRK03a*/
void FREE_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1(c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1* sp);
#define SETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1_MCC(sp,present) ((sp)->MCC_Present = present)
#define GETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1_MCC(sp) ((sp)->MCC_Present)

/* Access member 'IMSI_CLASS_0_TYPE' of type 'c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0' as a variable reference */
#define VAR_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0_IMSI_CLASS_0_TYPE(var) var

/* Access member 'IMSI_CLASS_0_TYPE' of type 'c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0' as a pointer */
#define PTR_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0_IMSI_CLASS_0_TYPE(var) (&var)

/* Access member 'MCC10' of type 'c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0' as a variable reference */
#define VAR_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0_MCC10(var) var

/* Access member 'MCC10' of type 'c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0' as a pointer */
#define PTR_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0_MCC10(var) (&var)

/* Access member 'IMSI_11_12' of type 'c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0' as a variable reference */
#define VAR_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0_IMSI_11_12(var) var

/* Access member 'IMSI_11_12' of type 'c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0' as a pointer */
#define PTR_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0_IMSI_11_12(var) (&var)

/* Access member 'IMSI_S' of type 'c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0' as a variable reference */
#define VAR_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0_IMSI_S(var) var

/* Access member 'IMSI_S' of type 'c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0' as a pointer */
#define PTR_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0_IMSI_S(var) (&var)


/*-A----------------------------------*/
typedef struct _c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0 {

	ED_OCTET IMSI_CLASS_0_TYPE; /* ODY01a *//*GBD01b*/
	ED_LONG MCC10; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN MCC10_Present;
	ED_OCTET IMSI_11_12; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN IMSI_11_12_Present;
	ED_BYTE IMSI_S [5]; /* Static, fixed size; bits needed 34 *//*GBD01b*/

}	c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0;
#define INIT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0(sp) ED_RESET_MEM ((sp), sizeof (c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0))
/*FRK03a*/
void FREE_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0(c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0* sp);
#define SETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0_MCC10(sp,present) ((sp)->MCC10_Present = present)
#define GETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0_MCC10(sp) ((sp)->MCC10_Present)
#define SETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0_IMSI_11_12(sp,present) ((sp)->IMSI_11_12_Present = present)
#define GETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0_IMSI_11_12(sp) ((sp)->IMSI_11_12_Present)

/* Access member 'IMSI_CLASS_1_TYPE' of type 'c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1' as a variable reference */
#define VAR_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1_IMSI_CLASS_1_TYPE(var) var

/* Access member 'IMSI_CLASS_1_TYPE' of type 'c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1' as a pointer */
#define PTR_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1_IMSI_CLASS_1_TYPE(var) (&var)

/* Access member 'IMSI_ADDR_NUM' of type 'c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1' as a variable reference */
#define VAR_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1_IMSI_ADDR_NUM(var) var

/* Access member 'IMSI_ADDR_NUM' of type 'c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1' as a pointer */
#define PTR_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1_IMSI_ADDR_NUM(var) (&var)

/* Access member 'MCC' of type 'c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1' as a variable reference */
#define VAR_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1_MCC(var) var

/* Access member 'MCC' of type 'c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1' as a pointer */
#define PTR_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1_MCC(var) (&var)

/* Access member 'IMSI_11_12' of type 'c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1' as a variable reference */
#define VAR_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1_IMSI_11_12(var) var

/* Access member 'IMSI_11_12' of type 'c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1' as a pointer */
#define PTR_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1_IMSI_11_12(var) (&var)

/* Access member 'IMSI_S' of type 'c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1' as a variable reference */
#define VAR_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1_IMSI_S(var) var

/* Access member 'IMSI_S' of type 'c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1' as a pointer */
#define PTR_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1_IMSI_S(var) (&var)


/*-A----------------------------------*/
typedef struct _c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1 {

	ED_BOOLEAN IMSI_CLASS_1_TYPE; /* ODY01a *//*GBD01b*/
	ED_OCTET IMSI_ADDR_NUM; /* ODY01a *//*GBD01b*/
	ED_LONG MCC; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN MCC_Present;
	ED_OCTET IMSI_11_12; /* ODY01a *//*GBD01b*/
	ED_BYTE IMSI_S [5]; /* Static, fixed size; bits needed 34 *//*GBD01b*/

}	c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1;
#define INIT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1(sp) ED_RESET_MEM ((sp), sizeof (c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1))
/*FRK03a*/
void FREE_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1(c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1* sp);
#define SETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1_MCC(sp,present) ((sp)->MCC_Present = present)
#define GETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1_MCC(sp) ((sp)->MCC_Present)

/* Access member 'PILOT_PN_PHASE' of type 'c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS' as a variable reference */
#define VAR_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_PILOT_PN_PHASE(var) var

/* Access member 'PILOT_PN_PHASE' of type 'c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS' as a pointer */
#define PTR_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_PILOT_PN_PHASE(var) (&var)

/* Access member 'PILOT_STRENGTH' of type 'c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS' as a variable reference */
#define VAR_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_PILOT_STRENGTH(var) var

/* Access member 'PILOT_STRENGTH' of type 'c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS' as a pointer */
#define PTR_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_PILOT_STRENGTH(var) (&var)

/* Access member 'PILOT_REC_TYPE' of type 'c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS' as a variable reference */
#define VAR_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_PILOT_REC_TYPE(var) var

/* Access member 'PILOT_REC_TYPE' of type 'c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS' as a pointer */
#define PTR_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_PILOT_REC_TYPE(var) (&var)

/* Access member 'RECORD_LEN' of type 'c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS' as a variable reference */
#define VAR_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_RECORD_LEN(var) var

/* Access member 'RECORD_LEN' of type 'c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS' as a pointer */
#define PTR_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_RECORD_LEN(var) (&var)

/* Access member 'Type_specific_fields' of type 'c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS' as a variable reference */
#define VAR_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields(var) var

/* Access member 'Type_specific_fields' of type 'c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS' as a pointer */
#define PTR_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields(var) (&var)


/*-A----------------------------------*/
typedef struct _c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS {

	ED_LONG PILOT_PN_PHASE; /* ODY01a *//*GBD01b*/
	ED_OCTET PILOT_STRENGTH; /* ODY01a *//*GBD01b*/
	ED_OCTET PILOT_REC_TYPE; /* ODY01a *//*GBD01b*/
	ED_OCTET RECORD_LEN; /* ODY01a *//*GBD01b*/
	c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS_Type_specific_fields Type_specific_fields; /* ODY01a *//*GBD01b*/

}	c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS;
#define INIT_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS(sp) ED_RESET_MEM ((sp), sizeof (c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS))
/*FRK03a*/
void FREE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS(c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS* sp);

/* Access member 'MEID' of type 'c_FCSCH_PDU_SDUs_data_Extended_Address' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_Extended_Address_MEID(var) var

/* Access member 'MEID' of type 'c_FCSCH_PDU_SDUs_data_Extended_Address' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_Extended_Address_MEID(var) (&var)

/* DEFINITION OF BINARY c_FCSCH_PDU_SDUs_data_Extended_Address_MEID */
typedef struct _c_FCSCH_PDU_SDUs_data_Extended_Address_MEID {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_FCSCH_PDU_SDUs_data_Extended_Address_MEID;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_FCSCH_PDU_SDUs_data_Extended_Address_MEID(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_FCSCH_PDU_SDUs_data_Extended_Address {

	c_FCSCH_PDU_SDUs_data_Extended_Address_MEID MEID; /* Static, variable size; bits needed 16 *//*GBD01b*/

}	c_FCSCH_PDU_SDUs_data_Extended_Address;
#define INIT_c_FCSCH_PDU_SDUs_data_Extended_Address(sp) ED_RESET_MEM ((sp), sizeof (c_FCSCH_PDU_SDUs_data_Extended_Address))
/*FRK03a*/
void FREE_c_FCSCH_PDU_SDUs_data_Extended_Address(c_FCSCH_PDU_SDUs_data_Extended_Address* sp);

/* Access member 'IMSI_M_S1' of type 'c_FCSCH_PDU_SDUs_data_IMSI_S' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_IMSI_S_IMSI_M_S1(var) var

/* Access member 'IMSI_M_S1' of type 'c_FCSCH_PDU_SDUs_data_IMSI_S' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_IMSI_S_IMSI_M_S1(var) (&var)

/* Access member 'IMSI_M_S2' of type 'c_FCSCH_PDU_SDUs_data_IMSI_S' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_IMSI_S_IMSI_M_S2(var) var

/* Access member 'IMSI_M_S2' of type 'c_FCSCH_PDU_SDUs_data_IMSI_S' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_IMSI_S_IMSI_M_S2(var) (&var)


/*-A----------------------------------*/
typedef struct _c_FCSCH_PDU_SDUs_data_IMSI_S {

	ED_LONG IMSI_M_S1; /* ODY01a *//*GBD01b*/
	ED_LONG IMSI_M_S2; /* ODY01a *//*GBD01b*/

}	c_FCSCH_PDU_SDUs_data_IMSI_S;
#define INIT_c_FCSCH_PDU_SDUs_data_IMSI_S(sp) ED_RESET_MEM ((sp), sizeof (c_FCSCH_PDU_SDUs_data_IMSI_S))
/*FRK03a*/
void FREE_c_FCSCH_PDU_SDUs_data_IMSI_S(c_FCSCH_PDU_SDUs_data_IMSI_S* sp);

/* Access member 'ESN' of type 'c_FCSCH_PDU_SDUs_data_ESN' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_ESN_ESN(var) var

/* Access member 'ESN' of type 'c_FCSCH_PDU_SDUs_data_ESN' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_ESN_ESN(var) (&var)

/* DEFINITION OF BINARY c_FCSCH_PDU_SDUs_data_ESN_ESN */
typedef struct _c_FCSCH_PDU_SDUs_data_ESN_ESN {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_FCSCH_PDU_SDUs_data_ESN_ESN;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_FCSCH_PDU_SDUs_data_ESN_ESN(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_FCSCH_PDU_SDUs_data_ESN {

	c_FCSCH_PDU_SDUs_data_ESN_ESN ESN; /* Static, variable size; bits needed 16 *//*GBD01b*/

}	c_FCSCH_PDU_SDUs_data_ESN;
#define INIT_c_FCSCH_PDU_SDUs_data_ESN(sp) ED_RESET_MEM ((sp), sizeof (c_FCSCH_PDU_SDUs_data_ESN))
/*FRK03a*/
void FREE_c_FCSCH_PDU_SDUs_data_ESN(c_FCSCH_PDU_SDUs_data_ESN* sp);

/* Access member 'IMSI_CLASS' of type 'c_FCSCH_PDU_SDUs_data_IMSI' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS(var) var

/* Access member 'IMSI_CLASS' of type 'c_FCSCH_PDU_SDUs_data_IMSI' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS(var) (&var)

/* Access member 'IMSI_CLASS_0' of type 'c_FCSCH_PDU_SDUs_data_IMSI' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0(var) (*var)

/* Access member 'IMSI_CLASS_0' of type 'c_FCSCH_PDU_SDUs_data_IMSI' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0(var) var

/* Access member 'IMSI_CLASS_1' of type 'c_FCSCH_PDU_SDUs_data_IMSI' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1(var) (*var)

/* Access member 'IMSI_CLASS_1' of type 'c_FCSCH_PDU_SDUs_data_IMSI' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1(var) var


/*-A----------------------------------*/
typedef struct _c_FCSCH_PDU_SDUs_data_IMSI {

	ED_BOOLEAN IMSI_CLASS; /* ODY01a *//*GBD01b*/
	c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0 *IMSI_CLASS_0; /* ODY01 *//*GBD01b*/
	ED_BOOLEAN IMSI_CLASS_0_Present;
	c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1 *IMSI_CLASS_1; /* ODY01 *//*GBD01b*/
	ED_BOOLEAN IMSI_CLASS_1_Present;

}	c_FCSCH_PDU_SDUs_data_IMSI;
#define INIT_c_FCSCH_PDU_SDUs_data_IMSI(sp) ED_RESET_MEM ((sp), sizeof (c_FCSCH_PDU_SDUs_data_IMSI))
/*FRK03a*/
void FREE_c_FCSCH_PDU_SDUs_data_IMSI(c_FCSCH_PDU_SDUs_data_IMSI* sp);
void SETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0 (c_FCSCH_PDU_SDUs_data_IMSI* sp, ED_BOOLEAN present);
#define GETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_0(sp) ((sp)->IMSI_CLASS_0_Present)
void SETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1 (c_FCSCH_PDU_SDUs_data_IMSI* sp, ED_BOOLEAN present);
#define GETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_IMSI_CLASS_1(sp) ((sp)->IMSI_CLASS_1_Present)

/* Access member 'TMSI_ZONE' of type 'c_FCSCH_PDU_SDUs_data_TMSI' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_TMSI_TMSI_ZONE(var) var

/* Access member 'TMSI_ZONE' of type 'c_FCSCH_PDU_SDUs_data_TMSI' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_TMSI_TMSI_ZONE(var) (&var)

/* Access member 'TMSI_CODE_ADDR' of type 'c_FCSCH_PDU_SDUs_data_TMSI' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_TMSI_TMSI_CODE_ADDR(var) var

/* Access member 'TMSI_CODE_ADDR' of type 'c_FCSCH_PDU_SDUs_data_TMSI' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_TMSI_TMSI_CODE_ADDR(var) (&var)

/* DEFINITION OF BINARY c_FCSCH_PDU_SDUs_data_TMSI_TMSI_ZONE */
typedef struct _c_FCSCH_PDU_SDUs_data_TMSI_TMSI_ZONE {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_FCSCH_PDU_SDUs_data_TMSI_TMSI_ZONE;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_FCSCH_PDU_SDUs_data_TMSI_TMSI_ZONE(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF BINARY c_FCSCH_PDU_SDUs_data_TMSI_TMSI_CODE_ADDR */
typedef struct _c_FCSCH_PDU_SDUs_data_TMSI_TMSI_CODE_ADDR {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_FCSCH_PDU_SDUs_data_TMSI_TMSI_CODE_ADDR;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_FCSCH_PDU_SDUs_data_TMSI_TMSI_CODE_ADDR(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_FCSCH_PDU_SDUs_data_TMSI {

	c_FCSCH_PDU_SDUs_data_TMSI_TMSI_ZONE TMSI_ZONE; /* Static, variable size; bits needed 16 *//*GBD01b*/
	c_FCSCH_PDU_SDUs_data_TMSI_TMSI_CODE_ADDR TMSI_CODE_ADDR; /* Static, variable size; bits needed 16 *//*GBD01b*/

}	c_FCSCH_PDU_SDUs_data_TMSI;
#define INIT_c_FCSCH_PDU_SDUs_data_TMSI(sp) ED_RESET_MEM ((sp), sizeof (c_FCSCH_PDU_SDUs_data_TMSI))
/*FRK03a*/
void FREE_c_FCSCH_PDU_SDUs_data_TMSI(c_FCSCH_PDU_SDUs_data_TMSI* sp);

/* Access member 'BC_ADDR' of type 'c_FCSCH_PDU_SDUs_data_BROADCAST' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_BROADCAST_BC_ADDR(var) var

/* Access member 'BC_ADDR' of type 'c_FCSCH_PDU_SDUs_data_BROADCAST' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_BROADCAST_BC_ADDR(var) (&var)

/* DEFINITION OF BINARY c_FCSCH_PDU_SDUs_data_BROADCAST_BC_ADDR */
typedef struct _c_FCSCH_PDU_SDUs_data_BROADCAST_BC_ADDR {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_FCSCH_PDU_SDUs_data_BROADCAST_BC_ADDR;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_FCSCH_PDU_SDUs_data_BROADCAST_BC_ADDR(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_FCSCH_PDU_SDUs_data_BROADCAST {

	c_FCSCH_PDU_SDUs_data_BROADCAST_BC_ADDR BC_ADDR; /* Static, variable size; bits needed 16 *//*GBD01b*/

}	c_FCSCH_PDU_SDUs_data_BROADCAST;
#define INIT_c_FCSCH_PDU_SDUs_data_BROADCAST(sp) ED_RESET_MEM ((sp), sizeof (c_FCSCH_PDU_SDUs_data_BROADCAST))
/*FRK03a*/
void FREE_c_FCSCH_PDU_SDUs_data_BROADCAST(c_FCSCH_PDU_SDUs_data_BROADCAST* sp);

/* Access member 'PILOT_PN_PHASE' of type 'c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data' as a variable reference */
#define VAR_c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data_PILOT_PN_PHASE(var) var

/* Access member 'PILOT_PN_PHASE' of type 'c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data' as a pointer */
#define PTR_c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data_PILOT_PN_PHASE(var) (&var)

/* Access member 'PILOT_STRENGTH' of type 'c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data' as a variable reference */
#define VAR_c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data_PILOT_STRENGTH(var) var

/* Access member 'PILOT_STRENGTH' of type 'c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data' as a pointer */
#define PTR_c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data_PILOT_STRENGTH(var) (&var)

/* Access member 'ACCESS_HO_EN' of type 'c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data' as a variable reference */
#define VAR_c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data_ACCESS_HO_EN(var) var

/* Access member 'ACCESS_HO_EN' of type 'c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data' as a pointer */
#define PTR_c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data_ACCESS_HO_EN(var) (&var)

/* Access member 'ACCESS_ATTEMPTED' of type 'c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data' as a variable reference */
#define VAR_c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data_ACCESS_ATTEMPTED(var) var

/* Access member 'ACCESS_ATTEMPTED' of type 'c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data' as a pointer */
#define PTR_c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data_ACCESS_ATTEMPTED(var) (&var)


/*-A----------------------------------*/
typedef struct _c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data {

	ED_LONG PILOT_PN_PHASE; /* ODY01a *//*GBD01b*/
	ED_OCTET PILOT_STRENGTH; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ACCESS_HO_EN; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ACCESS_ATTEMPTED; /* ODY01a *//*GBD01b*/

}	c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data;
#define INIT_c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data(sp) ED_RESET_MEM ((sp), sizeof (c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data))
/*FRK03a*/
void FREE_c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data(c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data* sp);

/* Access member 'IMSI_CLASS_0_TYPE' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0_IMSI_CLASS_0_TYPE(var) var

/* Access member 'IMSI_CLASS_0_TYPE' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0_IMSI_CLASS_0_TYPE(var) (&var)

/* Access member 'MCC10' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0_MCC10(var) var

/* Access member 'MCC10' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0_MCC10(var) (&var)

/* Access member 'IMSI_11_12' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0_IMSI_11_12(var) var

/* Access member 'IMSI_11_12' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0_IMSI_11_12(var) (&var)

/* Access member 'IMSI_S' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0_IMSI_S(var) var

/* Access member 'IMSI_S' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0_IMSI_S(var) (&var)


/*-A----------------------------------*/
typedef struct _c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0 {

	ED_OCTET IMSI_CLASS_0_TYPE; /* ODY01a *//*GBD01b*/
	ED_LONG MCC10; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN MCC10_Present;
	ED_OCTET IMSI_11_12; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN IMSI_11_12_Present;
	ED_BYTE IMSI_S [5]; /* Static, fixed size; bits needed 34 *//*GBD01b*/

}	c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0;
#define INIT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0(sp) ED_RESET_MEM ((sp), sizeof (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0))
/*FRK03a*/
void FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0(c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0* sp);
#define SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0_MCC10(sp,present) ((sp)->MCC10_Present = present)
#define GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0_MCC10(sp) ((sp)->MCC10_Present)
#define SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0_IMSI_11_12(sp,present) ((sp)->IMSI_11_12_Present = present)
#define GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0_IMSI_11_12(sp) ((sp)->IMSI_11_12_Present)

/* Access member 'IMSI_CLASS_1_TYPE' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1_IMSI_CLASS_1_TYPE(var) var

/* Access member 'IMSI_CLASS_1_TYPE' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1_IMSI_CLASS_1_TYPE(var) (&var)

/* Access member 'IMSI_ADDR_NUM' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1_IMSI_ADDR_NUM(var) var

/* Access member 'IMSI_ADDR_NUM' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1_IMSI_ADDR_NUM(var) (&var)

/* Access member 'MCC' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1_MCC(var) var

/* Access member 'MCC' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1_MCC(var) (&var)

/* Access member 'IMSI_11_12' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1_IMSI_11_12(var) var

/* Access member 'IMSI_11_12' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1_IMSI_11_12(var) (&var)

/* Access member 'IMSI_S' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1_IMSI_S(var) var

/* Access member 'IMSI_S' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1_IMSI_S(var) (&var)


/*-A----------------------------------*/
typedef struct _c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1 {

	ED_BOOLEAN IMSI_CLASS_1_TYPE; /* ODY01a *//*GBD01b*/
	ED_OCTET IMSI_ADDR_NUM; /* ODY01a *//*GBD01b*/
	ED_LONG MCC; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN MCC_Present;
	ED_OCTET IMSI_11_12; /* ODY01a *//*GBD01b*/
	ED_BYTE IMSI_S [5]; /* Static, fixed size; bits needed 34 *//*GBD01b*/

}	c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1;
#define INIT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1(sp) ED_RESET_MEM ((sp), sizeof (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1))
/*FRK03a*/
void FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1(c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1* sp);
#define SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1_MCC(sp,present) ((sp)->MCC_Present = present)
#define GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1_MCC(sp) ((sp)->MCC_Present)

/* Access member 'IMSI_CLASS_0' of type 'c_r_csch_PDU_Addressing_IMSI_class_specific_subfields' as a variable reference */
#define VAR_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0(var) (*var)

/* Access member 'IMSI_CLASS_0' of type 'c_r_csch_PDU_Addressing_IMSI_class_specific_subfields' as a pointer */
#define PTR_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0(var) var

/* Access member 'IMSI_CLASS_1' of type 'c_r_csch_PDU_Addressing_IMSI_class_specific_subfields' as a variable reference */
#define VAR_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1(var) (*var)

/* Access member 'IMSI_CLASS_1' of type 'c_r_csch_PDU_Addressing_IMSI_class_specific_subfields' as a pointer */
#define PTR_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1(var) var


/*-A----------------------------------*/
typedef struct _c_r_csch_PDU_Addressing_IMSI_class_specific_subfields {

	c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0 *IMSI_CLASS_0; /* ODY01 *//*GBD01b*/
	ED_BOOLEAN IMSI_CLASS_0_Present;
	c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1 *IMSI_CLASS_1; /* ODY01 *//*GBD01b*/
	ED_BOOLEAN IMSI_CLASS_1_Present;

}	c_r_csch_PDU_Addressing_IMSI_class_specific_subfields;
#define INIT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields(sp) ED_RESET_MEM ((sp), sizeof (c_r_csch_PDU_Addressing_IMSI_class_specific_subfields))
/*FRK03a*/
void FREE_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields(c_r_csch_PDU_Addressing_IMSI_class_specific_subfields* sp);
void SETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0 (c_r_csch_PDU_Addressing_IMSI_class_specific_subfields* sp, ED_BOOLEAN present);
#define GETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_0(sp) ((sp)->IMSI_CLASS_0_Present)
void SETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1 (c_r_csch_PDU_Addressing_IMSI_class_specific_subfields* sp, ED_BOOLEAN present);
#define GETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields_IMSI_CLASS_1(sp) ((sp)->IMSI_CLASS_1_Present)

/* Access member 'NUM_AUX_PILOTS' of type 'c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report' as a variable reference */
#define VAR_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_NUM_AUX_PILOTS(var) var

/* Access member 'NUM_AUX_PILOTS' of type 'c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report' as a pointer */
#define PTR_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_NUM_AUX_PILOTS(var) (&var)

/* Access member 'AUX_PILOTS' of type 'c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report' as a variable reference */
#define VAR_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS(var) (*var)

/* Access member 'AUX_PILOTS' of type 'c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report' as a pointer */
#define PTR_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS(var) var


/*-A----------------------------------*/
typedef struct _c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report {

	ED_OCTET NUM_AUX_PILOTS; /* ODY01a *//*GBD01b*/
	c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS *AUX_PILOTS; /* ODY01 *//*GBD01b*/
	ED_BOOLEAN AUX_PILOTS_Present;

}	c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report;
#define INIT_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report(sp) ED_RESET_MEM ((sp), sizeof (c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report))
/*FRK03a*/
void FREE_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report(c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report* sp);
void SETPRESENT_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS (c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report* sp, ED_BOOLEAN present);
#define GETPRESENT_c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report_AUX_PILOTS(sp) ((sp)->AUX_PILOTS_Present)

/* Access member 'ACK_SEQ' of type 'c_FCSCH_PDU_SDUs_data' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_ACK_SEQ(var) var

/* Access member 'ACK_SEQ' of type 'c_FCSCH_PDU_SDUs_data' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_ACK_SEQ(var) (&var)

/* Access member 'MSG_SEQ' of type 'c_FCSCH_PDU_SDUs_data' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_MSG_SEQ(var) var

/* Access member 'MSG_SEQ' of type 'c_FCSCH_PDU_SDUs_data' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_MSG_SEQ(var) (&var)

/* Access member 'ACK_REQ' of type 'c_FCSCH_PDU_SDUs_data' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_ACK_REQ(var) var

/* Access member 'ACK_REQ' of type 'c_FCSCH_PDU_SDUs_data' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_ACK_REQ(var) (&var)

/* Access member 'VALID_ACK' of type 'c_FCSCH_PDU_SDUs_data' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_VALID_ACK(var) var

/* Access member 'VALID_ACK' of type 'c_FCSCH_PDU_SDUs_data' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_VALID_ACK(var) (&var)

/* Access member 'ADDR_TYPE' of type 'c_FCSCH_PDU_SDUs_data' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_ADDR_TYPE(var) var

/* Access member 'ADDR_TYPE' of type 'c_FCSCH_PDU_SDUs_data' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_ADDR_TYPE(var) (&var)

/* Access member 'ADDR_LEN' of type 'c_FCSCH_PDU_SDUs_data' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_ADDR_LEN(var) var

/* Access member 'ADDR_LEN' of type 'c_FCSCH_PDU_SDUs_data' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_ADDR_LEN(var) (&var)

/* Access member 'EXT_ADDR_TYPE' of type 'c_FCSCH_PDU_SDUs_data' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_EXT_ADDR_TYPE(var) var

/* Access member 'EXT_ADDR_TYPE' of type 'c_FCSCH_PDU_SDUs_data' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_EXT_ADDR_TYPE(var) (&var)

/* Access member 'IMSI_S' of type 'c_FCSCH_PDU_SDUs_data' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_IMSI_S(var) (*var)

/* Access member 'IMSI_S' of type 'c_FCSCH_PDU_SDUs_data' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_IMSI_S(var) var

/* Access member 'ESN' of type 'c_FCSCH_PDU_SDUs_data' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_ESN(var) (*var)

/* Access member 'ESN' of type 'c_FCSCH_PDU_SDUs_data' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_ESN(var) var

/* Access member 'IMSI' of type 'c_FCSCH_PDU_SDUs_data' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_IMSI(var) (*var)

/* Access member 'IMSI' of type 'c_FCSCH_PDU_SDUs_data' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_IMSI(var) var

/* Access member 'TMSI' of type 'c_FCSCH_PDU_SDUs_data' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_TMSI(var) (*var)

/* Access member 'TMSI' of type 'c_FCSCH_PDU_SDUs_data' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_TMSI(var) var

/* Access member 'Extended_Address' of type 'c_FCSCH_PDU_SDUs_data' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_Extended_Address(var) (*var)

/* Access member 'Extended_Address' of type 'c_FCSCH_PDU_SDUs_data' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_Extended_Address(var) var

/* Access member 'BROADCAST' of type 'c_FCSCH_PDU_SDUs_data' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_BROADCAST(var) (*var)

/* Access member 'BROADCAST' of type 'c_FCSCH_PDU_SDUs_data' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_BROADCAST(var) var

/* Access member 'MACI_INCL' of type 'c_FCSCH_PDU_SDUs_data' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_MACI_INCL(var) var

/* Access member 'MACI_INCL' of type 'c_FCSCH_PDU_SDUs_data' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_MACI_INCL(var) (&var)

/* Access member 'SDU_KEY_ID' of type 'c_FCSCH_PDU_SDUs_data' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_SDU_KEY_ID(var) var

/* Access member 'SDU_KEY_ID' of type 'c_FCSCH_PDU_SDUs_data' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_SDU_KEY_ID(var) (&var)

/* Access member 'SDU_INTEGRITY_ALGO' of type 'c_FCSCH_PDU_SDUs_data' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_SDU_INTEGRITY_ALGO(var) var

/* Access member 'SDU_INTEGRITY_ALGO' of type 'c_FCSCH_PDU_SDUs_data' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_SDU_INTEGRITY_ALGO(var) (&var)

/* Access member 'SDU_SSEQ_OR_SSEQH' of type 'c_FCSCH_PDU_SDUs_data' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_SDU_SSEQ_OR_SSEQH(var) var

/* Access member 'SDU_SSEQ_OR_SSEQH' of type 'c_FCSCH_PDU_SDUs_data' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_SDU_SSEQ_OR_SSEQH(var) (&var)

/* Access member 'SDU_SSEQ' of type 'c_FCSCH_PDU_SDUs_data' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_SDU_SSEQ(var) var

/* Access member 'SDU_SSEQ' of type 'c_FCSCH_PDU_SDUs_data' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_SDU_SSEQ(var) (&var)

/* Access member 'SDU_SSEQ_H' of type 'c_FCSCH_PDU_SDUs_data' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_SDU_SSEQ_H(var) var

/* Access member 'SDU_SSEQ_H' of type 'c_FCSCH_PDU_SDUs_data' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_SDU_SSEQ_H(var) (&var)

/* Access member 'ENC_FIELDS_INCL' of type 'c_FCSCH_PDU_SDUs_data' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_ENC_FIELDS_INCL(var) var

/* Access member 'ENC_FIELDS_INCL' of type 'c_FCSCH_PDU_SDUs_data' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_ENC_FIELDS_INCL(var) (&var)

/* Access member 'SDU_ENCRYPT_MODE' of type 'c_FCSCH_PDU_SDUs_data' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_SDU_ENCRYPT_MODE(var) var

/* Access member 'SDU_ENCRYPT_MODE' of type 'c_FCSCH_PDU_SDUs_data' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_SDU_ENCRYPT_MODE(var) (&var)

/* Access member 'ENC_SEQ' of type 'c_FCSCH_PDU_SDUs_data' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_ENC_SEQ(var) var

/* Access member 'ENC_SEQ' of type 'c_FCSCH_PDU_SDUs_data' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_ENC_SEQ(var) (&var)

/* Access member 'SDU' of type 'c_FCSCH_PDU_SDUs_data' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_SDU(var) var

/* Access member 'SDU' of type 'c_FCSCH_PDU_SDUs_data' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_SDU(var) (&var)

/* Access member 'MACI' of type 'c_FCSCH_PDU_SDUs_data' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_MACI(var) var

/* Access member 'MACI' of type 'c_FCSCH_PDU_SDUs_data' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_MACI(var) (&var)

/* Access member 'ADD_RECORD_LEN' of type 'c_FCSCH_PDU_SDUs_data' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data_ADD_RECORD_LEN(var) var

/* Access member 'ADD_RECORD_LEN' of type 'c_FCSCH_PDU_SDUs_data' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data_ADD_RECORD_LEN(var) (&var)

/* DEFINITION OF BINARY c_FCSCH_PDU_SDUs_data_SDU */
typedef struct _c_FCSCH_PDU_SDUs_data_SDU {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_FCSCH_PDU_SDUs_data_SDU;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_FCSCH_PDU_SDUs_data_SDU(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_FCSCH_PDU_SDUs_data {

	ED_OCTET ACK_SEQ; /* ODY01a *//*GBD01b*/
	ED_OCTET MSG_SEQ; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ACK_REQ; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN VALID_ACK; /* ODY01a *//*GBD01b*/
	ED_OCTET ADDR_TYPE; /* ODY01a *//*GBD01b*/
	ED_OCTET ADDR_LEN; /* ODY01a *//*GBD01b*/
	ED_OCTET EXT_ADDR_TYPE; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN EXT_ADDR_TYPE_Present;
	c_FCSCH_PDU_SDUs_data_IMSI_S *IMSI_S; /* ODY01 *//*GBD01b*/
	ED_BOOLEAN IMSI_S_Present;
	c_FCSCH_PDU_SDUs_data_ESN *ESN; /* ODY01 *//*GBD01b*/
	ED_BOOLEAN ESN_Present;
	c_FCSCH_PDU_SDUs_data_IMSI *IMSI; /* ODY01 *//*GBD01b*/
	ED_BOOLEAN IMSI_Present;
	c_FCSCH_PDU_SDUs_data_TMSI *TMSI; /* ODY01 *//*GBD01b*/
	ED_BOOLEAN TMSI_Present;
	c_FCSCH_PDU_SDUs_data_Extended_Address *Extended_Address; /* ODY01 *//*GBD01b*/
	ED_BOOLEAN Extended_Address_Present;
	c_FCSCH_PDU_SDUs_data_BROADCAST *BROADCAST; /* ODY01 *//*GBD01b*/
	ED_BOOLEAN BROADCAST_Present;
	ED_BOOLEAN MACI_INCL; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN MACI_INCL_Present;
	ED_OCTET SDU_KEY_ID; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SDU_KEY_ID_Present;
	ED_OCTET SDU_INTEGRITY_ALGO; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SDU_INTEGRITY_ALGO_Present;
	ED_BOOLEAN SDU_SSEQ_OR_SSEQH; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SDU_SSEQ_OR_SSEQH_Present;
	ED_OCTET SDU_SSEQ; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SDU_SSEQ_Present;
	ED_LONG SDU_SSEQ_H; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SDU_SSEQ_H_Present;
	ED_BOOLEAN ENC_FIELDS_INCL; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ENC_FIELDS_INCL_Present;
	ED_OCTET SDU_ENCRYPT_MODE; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SDU_ENCRYPT_MODE_Present;
	ED_OCTET ENC_SEQ; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ENC_SEQ_Present;
	c_FCSCH_PDU_SDUs_data_SDU SDU; /* Static, variable size; bits needed 16 *//*GBD01b*/
	ED_LONG MACI; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN MACI_Present;
	ED_OCTET ADD_RECORD_LEN; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ADD_RECORD_LEN_Present;

}	c_FCSCH_PDU_SDUs_data;
#define INIT_c_FCSCH_PDU_SDUs_data(sp) ED_RESET_MEM ((sp), sizeof (c_FCSCH_PDU_SDUs_data))
/*FRK03a*/
void FREE_c_FCSCH_PDU_SDUs_data(c_FCSCH_PDU_SDUs_data* sp);
#define SETPRESENT_c_FCSCH_PDU_SDUs_data_EXT_ADDR_TYPE(sp,present) ((sp)->EXT_ADDR_TYPE_Present = present)
#define GETPRESENT_c_FCSCH_PDU_SDUs_data_EXT_ADDR_TYPE(sp) ((sp)->EXT_ADDR_TYPE_Present)
void SETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_S (c_FCSCH_PDU_SDUs_data* sp, ED_BOOLEAN present);
#define GETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI_S(sp) ((sp)->IMSI_S_Present)
void SETPRESENT_c_FCSCH_PDU_SDUs_data_ESN (c_FCSCH_PDU_SDUs_data* sp, ED_BOOLEAN present);
#define GETPRESENT_c_FCSCH_PDU_SDUs_data_ESN(sp) ((sp)->ESN_Present)
void SETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI (c_FCSCH_PDU_SDUs_data* sp, ED_BOOLEAN present);
#define GETPRESENT_c_FCSCH_PDU_SDUs_data_IMSI(sp) ((sp)->IMSI_Present)
void SETPRESENT_c_FCSCH_PDU_SDUs_data_TMSI (c_FCSCH_PDU_SDUs_data* sp, ED_BOOLEAN present);
#define GETPRESENT_c_FCSCH_PDU_SDUs_data_TMSI(sp) ((sp)->TMSI_Present)
void SETPRESENT_c_FCSCH_PDU_SDUs_data_Extended_Address (c_FCSCH_PDU_SDUs_data* sp, ED_BOOLEAN present);
#define GETPRESENT_c_FCSCH_PDU_SDUs_data_Extended_Address(sp) ((sp)->Extended_Address_Present)
void SETPRESENT_c_FCSCH_PDU_SDUs_data_BROADCAST (c_FCSCH_PDU_SDUs_data* sp, ED_BOOLEAN present);
#define GETPRESENT_c_FCSCH_PDU_SDUs_data_BROADCAST(sp) ((sp)->BROADCAST_Present)
#define SETPRESENT_c_FCSCH_PDU_SDUs_data_MACI_INCL(sp,present) ((sp)->MACI_INCL_Present = present)
#define GETPRESENT_c_FCSCH_PDU_SDUs_data_MACI_INCL(sp) ((sp)->MACI_INCL_Present)
#define SETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_KEY_ID(sp,present) ((sp)->SDU_KEY_ID_Present = present)
#define GETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_KEY_ID(sp) ((sp)->SDU_KEY_ID_Present)
#define SETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_INTEGRITY_ALGO(sp,present) ((sp)->SDU_INTEGRITY_ALGO_Present = present)
#define GETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_INTEGRITY_ALGO(sp) ((sp)->SDU_INTEGRITY_ALGO_Present)
#define SETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_SSEQ_OR_SSEQH(sp,present) ((sp)->SDU_SSEQ_OR_SSEQH_Present = present)
#define GETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_SSEQ_OR_SSEQH(sp) ((sp)->SDU_SSEQ_OR_SSEQH_Present)
#define SETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_SSEQ(sp,present) ((sp)->SDU_SSEQ_Present = present)
#define GETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_SSEQ(sp) ((sp)->SDU_SSEQ_Present)
#define SETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_SSEQ_H(sp,present) ((sp)->SDU_SSEQ_H_Present = present)
#define GETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_SSEQ_H(sp) ((sp)->SDU_SSEQ_H_Present)
#define SETPRESENT_c_FCSCH_PDU_SDUs_data_ENC_FIELDS_INCL(sp,present) ((sp)->ENC_FIELDS_INCL_Present = present)
#define GETPRESENT_c_FCSCH_PDU_SDUs_data_ENC_FIELDS_INCL(sp) ((sp)->ENC_FIELDS_INCL_Present)
#define SETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_ENCRYPT_MODE(sp,present) ((sp)->SDU_ENCRYPT_MODE_Present = present)
#define GETPRESENT_c_FCSCH_PDU_SDUs_data_SDU_ENCRYPT_MODE(sp) ((sp)->SDU_ENCRYPT_MODE_Present)
#define SETPRESENT_c_FCSCH_PDU_SDUs_data_ENC_SEQ(sp,present) ((sp)->ENC_SEQ_Present = present)
#define GETPRESENT_c_FCSCH_PDU_SDUs_data_ENC_SEQ(sp) ((sp)->ENC_SEQ_Present)
#define SETPRESENT_c_FCSCH_PDU_SDUs_data_MACI(sp,present) ((sp)->MACI_Present = present)
#define GETPRESENT_c_FCSCH_PDU_SDUs_data_MACI(sp) ((sp)->MACI_Present)
#define SETPRESENT_c_FCSCH_PDU_SDUs_data_ADD_RECORD_LEN(sp,present) ((sp)->ADD_RECORD_LEN_Present = present)
#define GETPRESENT_c_FCSCH_PDU_SDUs_data_ADD_RECORD_LEN(sp) ((sp)->ADD_RECORD_LEN_Present)

/* Access member 'PAGE_CLASS' of type 'c_GPM_PDU_page_records_data' as a variable reference */
#define VAR_c_GPM_PDU_page_records_data_PAGE_CLASS(var) var

/* Access member 'PAGE_CLASS' of type 'c_GPM_PDU_page_records_data' as a pointer */
#define PTR_c_GPM_PDU_page_records_data_PAGE_CLASS(var) (&var)

/* Access member 'PAGE_SUBCLASS' of type 'c_GPM_PDU_page_records_data' as a variable reference */
#define VAR_c_GPM_PDU_page_records_data_PAGE_SUBCLASS(var) var

/* Access member 'PAGE_SUBCLASS' of type 'c_GPM_PDU_page_records_data' as a pointer */
#define PTR_c_GPM_PDU_page_records_data_PAGE_SUBCLASS(var) (&var)

/* Access member 'PAGE_SUBCLASS_EXT' of type 'c_GPM_PDU_page_records_data' as a variable reference */
#define VAR_c_GPM_PDU_page_records_data_PAGE_SUBCLASS_EXT(var) var

/* Access member 'PAGE_SUBCLASS_EXT' of type 'c_GPM_PDU_page_records_data' as a pointer */
#define PTR_c_GPM_PDU_page_records_data_PAGE_SUBCLASS_EXT(var) (&var)

/* Access member 'MSG_SEQ' of type 'c_GPM_PDU_page_records_data' as a variable reference */
#define VAR_c_GPM_PDU_page_records_data_MSG_SEQ(var) var

/* Access member 'MSG_SEQ' of type 'c_GPM_PDU_page_records_data' as a pointer */
#define PTR_c_GPM_PDU_page_records_data_MSG_SEQ(var) (&var)

/* Access member 'IMSI_ADDR_NUM' of type 'c_GPM_PDU_page_records_data' as a variable reference */
#define VAR_c_GPM_PDU_page_records_data_IMSI_ADDR_NUM(var) var

/* Access member 'IMSI_ADDR_NUM' of type 'c_GPM_PDU_page_records_data' as a pointer */
#define PTR_c_GPM_PDU_page_records_data_IMSI_ADDR_NUM(var) (&var)

/* Access member 'MCC' of type 'c_GPM_PDU_page_records_data' as a variable reference */
#define VAR_c_GPM_PDU_page_records_data_MCC(var) var

/* Access member 'MCC' of type 'c_GPM_PDU_page_records_data' as a pointer */
#define PTR_c_GPM_PDU_page_records_data_MCC(var) (&var)

/* Access member 'IMSI_11_12' of type 'c_GPM_PDU_page_records_data' as a variable reference */
#define VAR_c_GPM_PDU_page_records_data_IMSI_11_12(var) var

/* Access member 'IMSI_11_12' of type 'c_GPM_PDU_page_records_data' as a pointer */
#define PTR_c_GPM_PDU_page_records_data_IMSI_11_12(var) (&var)

/* Access member 'IMSI_S' of type 'c_GPM_PDU_page_records_data' as a variable reference */
#define VAR_c_GPM_PDU_page_records_data_IMSI_S(var) (*var)

/* Access member 'IMSI_S' of type 'c_GPM_PDU_page_records_data' as a pointer */
#define PTR_c_GPM_PDU_page_records_data_IMSI_S(var) var

/* Access member 'TMSI_ZONE_LEN' of type 'c_GPM_PDU_page_records_data' as a variable reference */
#define VAR_c_GPM_PDU_page_records_data_TMSI_ZONE_LEN(var) var

/* Access member 'TMSI_ZONE_LEN' of type 'c_GPM_PDU_page_records_data' as a pointer */
#define PTR_c_GPM_PDU_page_records_data_TMSI_ZONE_LEN(var) (&var)

/* Access member 'TMSI_ZONE' of type 'c_GPM_PDU_page_records_data' as a variable reference */
#define VAR_c_GPM_PDU_page_records_data_TMSI_ZONE(var) var

/* Access member 'TMSI_ZONE' of type 'c_GPM_PDU_page_records_data' as a pointer */
#define PTR_c_GPM_PDU_page_records_data_TMSI_ZONE(var) (&var)

/* Access member 'TMSI_CODE_ADDR_32' of type 'c_GPM_PDU_page_records_data' as a variable reference */
#define VAR_c_GPM_PDU_page_records_data_TMSI_CODE_ADDR_32(var) var

/* Access member 'TMSI_CODE_ADDR_32' of type 'c_GPM_PDU_page_records_data' as a pointer */
#define PTR_c_GPM_PDU_page_records_data_TMSI_CODE_ADDR_32(var) (&var)

/* Access member 'TMSI_CODE_ADDR_24' of type 'c_GPM_PDU_page_records_data' as a variable reference */
#define VAR_c_GPM_PDU_page_records_data_TMSI_CODE_ADDR_24(var) var

/* Access member 'TMSI_CODE_ADDR_24' of type 'c_GPM_PDU_page_records_data' as a pointer */
#define PTR_c_GPM_PDU_page_records_data_TMSI_CODE_ADDR_24(var) (&var)

/* Access member 'TMSI_CODE_ADDR_16' of type 'c_GPM_PDU_page_records_data' as a variable reference */
#define VAR_c_GPM_PDU_page_records_data_TMSI_CODE_ADDR_16(var) var

/* Access member 'TMSI_CODE_ADDR_16' of type 'c_GPM_PDU_page_records_data' as a pointer */
#define PTR_c_GPM_PDU_page_records_data_TMSI_CODE_ADDR_16(var) (&var)

/* Access member 'BURST_TYPE' of type 'c_GPM_PDU_page_records_data' as a variable reference */
#define VAR_c_GPM_PDU_page_records_data_BURST_TYPE(var) var

/* Access member 'BURST_TYPE' of type 'c_GPM_PDU_page_records_data' as a pointer */
#define PTR_c_GPM_PDU_page_records_data_BURST_TYPE(var) (&var)

/* Access member 'ADDR_LEN' of type 'c_GPM_PDU_page_records_data' as a variable reference */
#define VAR_c_GPM_PDU_page_records_data_ADDR_LEN(var) var

/* Access member 'ADDR_LEN' of type 'c_GPM_PDU_page_records_data' as a pointer */
#define PTR_c_GPM_PDU_page_records_data_ADDR_LEN(var) (&var)

/* Access member 'BC_ADDR' of type 'c_GPM_PDU_page_records_data' as a variable reference */
#define VAR_c_GPM_PDU_page_records_data_BC_ADDR(var) var

/* Access member 'BC_ADDR' of type 'c_GPM_PDU_page_records_data' as a pointer */
#define PTR_c_GPM_PDU_page_records_data_BC_ADDR(var) (&var)

/* Access member 'LENGTH' of type 'c_GPM_PDU_page_records_data' as a variable reference */
#define VAR_c_GPM_PDU_page_records_data_LENGTH(var) var

/* Access member 'LENGTH' of type 'c_GPM_PDU_page_records_data' as a pointer */
#define PTR_c_GPM_PDU_page_records_data_LENGTH(var) (&var)

/* Access member 'SDU_INCLUDED' of type 'c_GPM_PDU_page_records_data' as a variable reference */
#define VAR_c_GPM_PDU_page_records_data_SDU_INCLUDED(var) var

/* Access member 'SDU_INCLUDED' of type 'c_GPM_PDU_page_records_data' as a pointer */
#define PTR_c_GPM_PDU_page_records_data_SDU_INCLUDED(var) (&var)

/* Access member 'EXT_BCAST_SDU_LENGTH_IND' of type 'c_GPM_PDU_page_records_data' as a variable reference */
#define VAR_c_GPM_PDU_page_records_data_EXT_BCAST_SDU_LENGTH_IND(var) var

/* Access member 'EXT_BCAST_SDU_LENGTH_IND' of type 'c_GPM_PDU_page_records_data' as a pointer */
#define PTR_c_GPM_PDU_page_records_data_EXT_BCAST_SDU_LENGTH_IND(var) (&var)

/* Access member 'EXT_BCAST_SDU_LENGTH' of type 'c_GPM_PDU_page_records_data' as a variable reference */
#define VAR_c_GPM_PDU_page_records_data_EXT_BCAST_SDU_LENGTH(var) var

/* Access member 'EXT_BCAST_SDU_LENGTH' of type 'c_GPM_PDU_page_records_data' as a pointer */
#define PTR_c_GPM_PDU_page_records_data_EXT_BCAST_SDU_LENGTH(var) (&var)

/* Access member 'SDU' of type 'c_GPM_PDU_page_records_data' as a variable reference */
#define VAR_c_GPM_PDU_page_records_data_SDU(var) var

/* Access member 'SDU' of type 'c_GPM_PDU_page_records_data' as a pointer */
#define PTR_c_GPM_PDU_page_records_data_SDU(var) (&var)

/* DEFINITION OF BINARY c_GPM_PDU_page_records_data_TMSI_ZONE */
typedef struct _c_GPM_PDU_page_records_data_TMSI_ZONE {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_GPM_PDU_page_records_data_TMSI_ZONE;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_GPM_PDU_page_records_data_TMSI_ZONE(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF BINARY c_GPM_PDU_page_records_data_BC_ADDR */
typedef struct _c_GPM_PDU_page_records_data_BC_ADDR {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_GPM_PDU_page_records_data_BC_ADDR;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_GPM_PDU_page_records_data_BC_ADDR(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF BINARY c_GPM_PDU_page_records_data_SDU */
typedef struct _c_GPM_PDU_page_records_data_SDU {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_GPM_PDU_page_records_data_SDU;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_GPM_PDU_page_records_data_SDU(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_GPM_PDU_page_records_data {

	ED_OCTET PAGE_CLASS; /* ODY01a *//*GBD01b*/
	ED_OCTET PAGE_SUBCLASS; /* ODY01a *//*GBD01b*/
	ED_OCTET PAGE_SUBCLASS_EXT; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PAGE_SUBCLASS_EXT_Present;
	ED_OCTET MSG_SEQ; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN MSG_SEQ_Present;
	ED_OCTET IMSI_ADDR_NUM; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN IMSI_ADDR_NUM_Present;
	ED_LONG MCC; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN MCC_Present;
	ED_OCTET IMSI_11_12; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN IMSI_11_12_Present;
	ED_BYTE* IMSI_S; /* Dynamic, fixed size; bits needed: 34 ODY02a *//*GBD01b*/
	ED_BOOLEAN IMSI_S_Present;
	ED_OCTET TMSI_ZONE_LEN; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN TMSI_ZONE_LEN_Present;
	c_GPM_PDU_page_records_data_TMSI_ZONE TMSI_ZONE; /* Static, variable size; bits needed 16 *//*GBD01b*/
	ED_LONG TMSI_CODE_ADDR_32; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN TMSI_CODE_ADDR_32_Present;
	ED_LONG TMSI_CODE_ADDR_24; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN TMSI_CODE_ADDR_24_Present;
	ED_LONG TMSI_CODE_ADDR_16; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN TMSI_CODE_ADDR_16_Present;
	ED_OCTET BURST_TYPE; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN BURST_TYPE_Present;
	ED_OCTET ADDR_LEN; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ADDR_LEN_Present;
	c_GPM_PDU_page_records_data_BC_ADDR BC_ADDR; /* Static, variable size; bits needed 16 *//*GBD01b*/
	ED_OCTET LENGTH; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN LENGTH_Present;
	ED_BOOLEAN SDU_INCLUDED; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SDU_INCLUDED_Present;
	ED_OCTET EXT_BCAST_SDU_LENGTH_IND; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN EXT_BCAST_SDU_LENGTH_IND_Present;
	ED_OCTET EXT_BCAST_SDU_LENGTH; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN EXT_BCAST_SDU_LENGTH_Present;
	c_GPM_PDU_page_records_data_SDU SDU; /* Static, variable size; bits needed 16 *//*GBD01b*/

}	c_GPM_PDU_page_records_data;
#define INIT_c_GPM_PDU_page_records_data(sp) ED_RESET_MEM ((sp), sizeof (c_GPM_PDU_page_records_data))
/*FRK03a*/
void FREE_c_GPM_PDU_page_records_data(c_GPM_PDU_page_records_data* sp);
#define SETPRESENT_c_GPM_PDU_page_records_data_PAGE_SUBCLASS_EXT(sp,present) ((sp)->PAGE_SUBCLASS_EXT_Present = present)
#define GETPRESENT_c_GPM_PDU_page_records_data_PAGE_SUBCLASS_EXT(sp) ((sp)->PAGE_SUBCLASS_EXT_Present)
#define SETPRESENT_c_GPM_PDU_page_records_data_MSG_SEQ(sp,present) ((sp)->MSG_SEQ_Present = present)
#define GETPRESENT_c_GPM_PDU_page_records_data_MSG_SEQ(sp) ((sp)->MSG_SEQ_Present)
#define SETPRESENT_c_GPM_PDU_page_records_data_IMSI_ADDR_NUM(sp,present) ((sp)->IMSI_ADDR_NUM_Present = present)
#define GETPRESENT_c_GPM_PDU_page_records_data_IMSI_ADDR_NUM(sp) ((sp)->IMSI_ADDR_NUM_Present)
#define SETPRESENT_c_GPM_PDU_page_records_data_MCC(sp,present) ((sp)->MCC_Present = present)
#define GETPRESENT_c_GPM_PDU_page_records_data_MCC(sp) ((sp)->MCC_Present)
#define SETPRESENT_c_GPM_PDU_page_records_data_IMSI_11_12(sp,present) ((sp)->IMSI_11_12_Present = present)
#define GETPRESENT_c_GPM_PDU_page_records_data_IMSI_11_12(sp) ((sp)->IMSI_11_12_Present)
void SETPRESENT_c_GPM_PDU_page_records_data_IMSI_S (c_GPM_PDU_page_records_data* sp, ED_BOOLEAN present);
#define GETPRESENT_c_GPM_PDU_page_records_data_IMSI_S(sp) ((sp)->IMSI_S_Present)
#define SETPRESENT_c_GPM_PDU_page_records_data_TMSI_ZONE_LEN(sp,present) ((sp)->TMSI_ZONE_LEN_Present = present)
#define GETPRESENT_c_GPM_PDU_page_records_data_TMSI_ZONE_LEN(sp) ((sp)->TMSI_ZONE_LEN_Present)
#define SETPRESENT_c_GPM_PDU_page_records_data_TMSI_CODE_ADDR_32(sp,present) ((sp)->TMSI_CODE_ADDR_32_Present = present)
#define GETPRESENT_c_GPM_PDU_page_records_data_TMSI_CODE_ADDR_32(sp) ((sp)->TMSI_CODE_ADDR_32_Present)
#define SETPRESENT_c_GPM_PDU_page_records_data_TMSI_CODE_ADDR_24(sp,present) ((sp)->TMSI_CODE_ADDR_24_Present = present)
#define GETPRESENT_c_GPM_PDU_page_records_data_TMSI_CODE_ADDR_24(sp) ((sp)->TMSI_CODE_ADDR_24_Present)
#define SETPRESENT_c_GPM_PDU_page_records_data_TMSI_CODE_ADDR_16(sp,present) ((sp)->TMSI_CODE_ADDR_16_Present = present)
#define GETPRESENT_c_GPM_PDU_page_records_data_TMSI_CODE_ADDR_16(sp) ((sp)->TMSI_CODE_ADDR_16_Present)
#define SETPRESENT_c_GPM_PDU_page_records_data_BURST_TYPE(sp,present) ((sp)->BURST_TYPE_Present = present)
#define GETPRESENT_c_GPM_PDU_page_records_data_BURST_TYPE(sp) ((sp)->BURST_TYPE_Present)
#define SETPRESENT_c_GPM_PDU_page_records_data_ADDR_LEN(sp,present) ((sp)->ADDR_LEN_Present = present)
#define GETPRESENT_c_GPM_PDU_page_records_data_ADDR_LEN(sp) ((sp)->ADDR_LEN_Present)
#define SETPRESENT_c_GPM_PDU_page_records_data_LENGTH(sp,present) ((sp)->LENGTH_Present = present)
#define GETPRESENT_c_GPM_PDU_page_records_data_LENGTH(sp) ((sp)->LENGTH_Present)
#define SETPRESENT_c_GPM_PDU_page_records_data_SDU_INCLUDED(sp,present) ((sp)->SDU_INCLUDED_Present = present)
#define GETPRESENT_c_GPM_PDU_page_records_data_SDU_INCLUDED(sp) ((sp)->SDU_INCLUDED_Present)
#define SETPRESENT_c_GPM_PDU_page_records_data_EXT_BCAST_SDU_LENGTH_IND(sp,present) ((sp)->EXT_BCAST_SDU_LENGTH_IND_Present = present)
#define GETPRESENT_c_GPM_PDU_page_records_data_EXT_BCAST_SDU_LENGTH_IND(sp) ((sp)->EXT_BCAST_SDU_LENGTH_IND_Present)
#define SETPRESENT_c_GPM_PDU_page_records_data_EXT_BCAST_SDU_LENGTH(sp,present) ((sp)->EXT_BCAST_SDU_LENGTH_Present = present)
#define GETPRESENT_c_GPM_PDU_page_records_data_EXT_BCAST_SDU_LENGTH(sp) ((sp)->EXT_BCAST_SDU_LENGTH_Present)

/* Access member 'BC_ADDR_BLOCK' of type 'c_f_csch_Universal_Page_Block_SUBRECORD_data' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_SUBRECORD_data_BC_ADDR_BLOCK(var) var

/* Access member 'BC_ADDR_BLOCK' of type 'c_f_csch_Universal_Page_Block_SUBRECORD_data' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_SUBRECORD_data_BC_ADDR_BLOCK(var) (&var)

/* Access member 'IMSI_ADDR_BLOCK' of type 'c_f_csch_Universal_Page_Block_SUBRECORD_data' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_SUBRECORD_data_IMSI_ADDR_BLOCK(var) var

/* Access member 'IMSI_ADDR_BLOCK' of type 'c_f_csch_Universal_Page_Block_SUBRECORD_data' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_SUBRECORD_data_IMSI_ADDR_BLOCK(var) (&var)

/* Access member 'TMSI_ADDR_BLOCK' of type 'c_f_csch_Universal_Page_Block_SUBRECORD_data' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_SUBRECORD_data_TMSI_ADDR_BLOCK(var) var

/* Access member 'TMSI_ADDR_BLOCK' of type 'c_f_csch_Universal_Page_Block_SUBRECORD_data' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_SUBRECORD_data_TMSI_ADDR_BLOCK(var) (&var)

/* Access member 'RESERVED_ADDR_BLOCK' of type 'c_f_csch_Universal_Page_Block_SUBRECORD_data' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_SUBRECORD_data_RESERVED_ADDR_BLOCK(var) var

/* Access member 'RESERVED_ADDR_BLOCK' of type 'c_f_csch_Universal_Page_Block_SUBRECORD_data' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_SUBRECORD_data_RESERVED_ADDR_BLOCK(var) (&var)

/* DEFINITION OF BINARY c_f_csch_Universal_Page_Block_SUBRECORD_data_BC_ADDR_BLOCK */
typedef struct _c_f_csch_Universal_Page_Block_SUBRECORD_data_BC_ADDR_BLOCK {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_f_csch_Universal_Page_Block_SUBRECORD_data_BC_ADDR_BLOCK;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_f_csch_Universal_Page_Block_SUBRECORD_data_BC_ADDR_BLOCK(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF BINARY c_f_csch_Universal_Page_Block_SUBRECORD_data_IMSI_ADDR_BLOCK */
typedef struct _c_f_csch_Universal_Page_Block_SUBRECORD_data_IMSI_ADDR_BLOCK {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_f_csch_Universal_Page_Block_SUBRECORD_data_IMSI_ADDR_BLOCK;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_f_csch_Universal_Page_Block_SUBRECORD_data_IMSI_ADDR_BLOCK(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF BINARY c_f_csch_Universal_Page_Block_SUBRECORD_data_TMSI_ADDR_BLOCK */
typedef struct _c_f_csch_Universal_Page_Block_SUBRECORD_data_TMSI_ADDR_BLOCK {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_f_csch_Universal_Page_Block_SUBRECORD_data_TMSI_ADDR_BLOCK;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_f_csch_Universal_Page_Block_SUBRECORD_data_TMSI_ADDR_BLOCK(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF BINARY c_f_csch_Universal_Page_Block_SUBRECORD_data_RESERVED_ADDR_BLOCK */
typedef struct _c_f_csch_Universal_Page_Block_SUBRECORD_data_RESERVED_ADDR_BLOCK {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_f_csch_Universal_Page_Block_SUBRECORD_data_RESERVED_ADDR_BLOCK;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_f_csch_Universal_Page_Block_SUBRECORD_data_RESERVED_ADDR_BLOCK(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_f_csch_Universal_Page_Block_SUBRECORD_data {

	c_f_csch_Universal_Page_Block_SUBRECORD_data_BC_ADDR_BLOCK BC_ADDR_BLOCK; /* Static, variable size; bits needed 16 *//*GBD01b*/
	c_f_csch_Universal_Page_Block_SUBRECORD_data_IMSI_ADDR_BLOCK IMSI_ADDR_BLOCK; /* Static, variable size; bits needed 16 *//*GBD01b*/
	c_f_csch_Universal_Page_Block_SUBRECORD_data_TMSI_ADDR_BLOCK TMSI_ADDR_BLOCK; /* Static, variable size; bits needed 16 *//*GBD01b*/
	c_f_csch_Universal_Page_Block_SUBRECORD_data_RESERVED_ADDR_BLOCK RESERVED_ADDR_BLOCK; /* Static, variable size; bits needed 16 *//*GBD01b*/

}	c_f_csch_Universal_Page_Block_SUBRECORD_data;
#define INIT_c_f_csch_Universal_Page_Block_SUBRECORD_data(sp) ED_RESET_MEM ((sp), sizeof (c_f_csch_Universal_Page_Block_SUBRECORD_data))
/*FRK03a*/
void FREE_c_f_csch_Universal_Page_Block_SUBRECORD_data(c_f_csch_Universal_Page_Block_SUBRECORD_data* sp);

/* Access member 'PAGE_CLASS' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_page_records_data_PAGE_CLASS(var) var

/* Access member 'PAGE_CLASS' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_page_records_data_PAGE_CLASS(var) (&var)

/* Access member 'PAGE_SUBCLASS' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_page_records_data_PAGE_SUBCLASS(var) var

/* Access member 'PAGE_SUBCLASS' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_page_records_data_PAGE_SUBCLASS(var) (&var)

/* Access member 'PAGE_SUBCLASS_EXT' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_page_records_data_PAGE_SUBCLASS_EXT(var) var

/* Access member 'PAGE_SUBCLASS_EXT' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_page_records_data_PAGE_SUBCLASS_EXT(var) (&var)

/* Access member 'MSG_SEQ' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_page_records_data_MSG_SEQ(var) var

/* Access member 'MSG_SEQ' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_page_records_data_MSG_SEQ(var) (&var)

/* Access member 'IMSI_ADDR_NUM' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_page_records_data_IMSI_ADDR_NUM(var) var

/* Access member 'IMSI_ADDR_NUM' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_page_records_data_IMSI_ADDR_NUM(var) (&var)

/* Access member 'MCC' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_page_records_data_MCC(var) var

/* Access member 'MCC' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_page_records_data_MCC(var) (&var)

/* Access member 'IMSI_11_12' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_page_records_data_IMSI_11_12(var) var

/* Access member 'IMSI_11_12' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_page_records_data_IMSI_11_12(var) (&var)

/* Access member 'IMSI_S_33_16' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_page_records_data_IMSI_S_33_16(var) var

/* Access member 'IMSI_S_33_16' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_page_records_data_IMSI_S_33_16(var) (&var)

/* Access member 'TMSI_ZONE_LEN' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_page_records_data_TMSI_ZONE_LEN(var) var

/* Access member 'TMSI_ZONE_LEN' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_page_records_data_TMSI_ZONE_LEN(var) (&var)

/* Access member 'TMSI_ZONE' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_page_records_data_TMSI_ZONE(var) var

/* Access member 'TMSI_ZONE' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_page_records_data_TMSI_ZONE(var) (&var)

/* Access member 'TMSI_CODE_ADDR_31_16' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_page_records_data_TMSI_CODE_ADDR_31_16(var) var

/* Access member 'TMSI_CODE_ADDR_31_16' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_page_records_data_TMSI_CODE_ADDR_31_16(var) (&var)

/* Access member 'TMSI_CODE_ADDR_23_16' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_page_records_data_TMSI_CODE_ADDR_23_16(var) var

/* Access member 'TMSI_CODE_ADDR_23_16' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_page_records_data_TMSI_CODE_ADDR_23_16(var) (&var)

/* Access member 'ADDR_LEN' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_page_records_data_ADDR_LEN(var) var

/* Access member 'ADDR_LEN' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_page_records_data_ADDR_LEN(var) (&var)

/* Access member 'BC_ADDR_REMAINDER' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_page_records_data_BC_ADDR_REMAINDER(var) (*var)

/* Access member 'BC_ADDR_REMAINDER' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_page_records_data_BC_ADDR_REMAINDER(var) var

/* Access member 'RESERVED_LEN' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_page_records_data_RESERVED_LEN(var) var

/* Access member 'RESERVED_LEN' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_page_records_data_RESERVED_LEN(var) (&var)

/* Access member 'RESERVED' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_page_records_data_RESERVED(var) var

/* Access member 'RESERVED' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_page_records_data_RESERVED(var) (&var)

/* Access member 'EXT_MS_SDU_LENGTH_INCL' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_page_records_data_EXT_MS_SDU_LENGTH_INCL(var) var

/* Access member 'EXT_MS_SDU_LENGTH_INCL' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_page_records_data_EXT_MS_SDU_LENGTH_INCL(var) (&var)

/* Access member 'EXT_MS_SDU_LENGTH' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_page_records_data_EXT_MS_SDU_LENGTH(var) var

/* Access member 'EXT_MS_SDU_LENGTH' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_page_records_data_EXT_MS_SDU_LENGTH(var) (&var)

/* Access member 'EXT_BCAST_SDU_LENGTH_IND' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_page_records_data_EXT_BCAST_SDU_LENGTH_IND(var) var

/* Access member 'EXT_BCAST_SDU_LENGTH_IND' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_page_records_data_EXT_BCAST_SDU_LENGTH_IND(var) (&var)

/* Access member 'EXT_BCAST_SDU_LENGTH' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_page_records_data_EXT_BCAST_SDU_LENGTH(var) var

/* Access member 'EXT_BCAST_SDU_LENGTH' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_page_records_data_EXT_BCAST_SDU_LENGTH(var) (&var)

/* Access member 'SDU' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_page_records_data_SDU(var) var

/* Access member 'SDU' of type 'c_f_csch_Universal_Page_Block_page_records_data' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_page_records_data_SDU(var) (&var)

/* DEFINITION OF BINARY c_f_csch_Universal_Page_Block_page_records_data_TMSI_ZONE */
typedef struct _c_f_csch_Universal_Page_Block_page_records_data_TMSI_ZONE {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_f_csch_Universal_Page_Block_page_records_data_TMSI_ZONE;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_f_csch_Universal_Page_Block_page_records_data_TMSI_ZONE(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF BINARY c_f_csch_Universal_Page_Block_page_records_data_BC_ADDR_REMAINDER */
typedef struct _c_f_csch_Universal_Page_Block_page_records_data_BC_ADDR_REMAINDER {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_f_csch_Universal_Page_Block_page_records_data_BC_ADDR_REMAINDER;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_f_csch_Universal_Page_Block_page_records_data_BC_ADDR_REMAINDER(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF BINARY c_f_csch_Universal_Page_Block_page_records_data_RESERVED_LEN */
typedef struct _c_f_csch_Universal_Page_Block_page_records_data_RESERVED_LEN {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_f_csch_Universal_Page_Block_page_records_data_RESERVED_LEN;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_f_csch_Universal_Page_Block_page_records_data_RESERVED_LEN(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF BINARY c_f_csch_Universal_Page_Block_page_records_data_RESERVED */
typedef struct _c_f_csch_Universal_Page_Block_page_records_data_RESERVED {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_f_csch_Universal_Page_Block_page_records_data_RESERVED;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_f_csch_Universal_Page_Block_page_records_data_RESERVED(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF BINARY c_f_csch_Universal_Page_Block_page_records_data_SDU */
typedef struct _c_f_csch_Universal_Page_Block_page_records_data_SDU {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_f_csch_Universal_Page_Block_page_records_data_SDU;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_f_csch_Universal_Page_Block_page_records_data_SDU(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_f_csch_Universal_Page_Block_page_records_data {

	ED_OCTET PAGE_CLASS; /* ODY01a *//*GBD01b*/
	ED_OCTET PAGE_SUBCLASS; /* ODY01a *//*GBD01b*/
	ED_OCTET PAGE_SUBCLASS_EXT; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PAGE_SUBCLASS_EXT_Present;
	ED_OCTET MSG_SEQ; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN MSG_SEQ_Present;
	ED_OCTET IMSI_ADDR_NUM; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN IMSI_ADDR_NUM_Present;
	ED_LONG MCC; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN MCC_Present;
	ED_OCTET IMSI_11_12; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN IMSI_11_12_Present;
	ED_LONG IMSI_S_33_16; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN IMSI_S_33_16_Present;
	ED_OCTET TMSI_ZONE_LEN; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN TMSI_ZONE_LEN_Present;
	c_f_csch_Universal_Page_Block_page_records_data_TMSI_ZONE TMSI_ZONE; /* Static, variable size; bits needed 16 *//*GBD01b*/
	ED_LONG TMSI_CODE_ADDR_31_16; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN TMSI_CODE_ADDR_31_16_Present;
	ED_OCTET TMSI_CODE_ADDR_23_16; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN TMSI_CODE_ADDR_23_16_Present;
	ED_OCTET ADDR_LEN; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ADDR_LEN_Present;
	c_f_csch_Universal_Page_Block_page_records_data_BC_ADDR_REMAINDER* BC_ADDR_REMAINDER; /* Dynamic, variable size; bits needed 16 ODY02b *//*GBD01b*/
	ED_BOOLEAN BC_ADDR_REMAINDER_Present;
	c_f_csch_Universal_Page_Block_page_records_data_RESERVED_LEN RESERVED_LEN; /* Static, variable size; bits needed 16 *//*GBD01b*/
	c_f_csch_Universal_Page_Block_page_records_data_RESERVED RESERVED; /* Static, variable size; bits needed 16 *//*GBD01b*/
	ED_BOOLEAN EXT_MS_SDU_LENGTH_INCL; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN EXT_MS_SDU_LENGTH_INCL_Present;
	ED_OCTET EXT_MS_SDU_LENGTH; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN EXT_MS_SDU_LENGTH_Present;
	ED_OCTET EXT_BCAST_SDU_LENGTH_IND; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN EXT_BCAST_SDU_LENGTH_IND_Present;
	ED_OCTET EXT_BCAST_SDU_LENGTH; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN EXT_BCAST_SDU_LENGTH_Present;
	c_f_csch_Universal_Page_Block_page_records_data_SDU SDU; /* Static, variable size; bits needed 16 *//*GBD01b*/

}	c_f_csch_Universal_Page_Block_page_records_data;
#define INIT_c_f_csch_Universal_Page_Block_page_records_data(sp) ED_RESET_MEM ((sp), sizeof (c_f_csch_Universal_Page_Block_page_records_data))
/*FRK03a*/
void FREE_c_f_csch_Universal_Page_Block_page_records_data(c_f_csch_Universal_Page_Block_page_records_data* sp);
#define SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_PAGE_SUBCLASS_EXT(sp,present) ((sp)->PAGE_SUBCLASS_EXT_Present = present)
#define GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_PAGE_SUBCLASS_EXT(sp) ((sp)->PAGE_SUBCLASS_EXT_Present)
#define SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_MSG_SEQ(sp,present) ((sp)->MSG_SEQ_Present = present)
#define GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_MSG_SEQ(sp) ((sp)->MSG_SEQ_Present)
#define SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_IMSI_ADDR_NUM(sp,present) ((sp)->IMSI_ADDR_NUM_Present = present)
#define GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_IMSI_ADDR_NUM(sp) ((sp)->IMSI_ADDR_NUM_Present)
#define SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_MCC(sp,present) ((sp)->MCC_Present = present)
#define GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_MCC(sp) ((sp)->MCC_Present)
#define SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_IMSI_11_12(sp,present) ((sp)->IMSI_11_12_Present = present)
#define GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_IMSI_11_12(sp) ((sp)->IMSI_11_12_Present)
#define SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_IMSI_S_33_16(sp,present) ((sp)->IMSI_S_33_16_Present = present)
#define GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_IMSI_S_33_16(sp) ((sp)->IMSI_S_33_16_Present)
#define SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_TMSI_ZONE_LEN(sp,present) ((sp)->TMSI_ZONE_LEN_Present = present)
#define GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_TMSI_ZONE_LEN(sp) ((sp)->TMSI_ZONE_LEN_Present)
#define SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_TMSI_CODE_ADDR_31_16(sp,present) ((sp)->TMSI_CODE_ADDR_31_16_Present = present)
#define GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_TMSI_CODE_ADDR_31_16(sp) ((sp)->TMSI_CODE_ADDR_31_16_Present)
#define SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_TMSI_CODE_ADDR_23_16(sp,present) ((sp)->TMSI_CODE_ADDR_23_16_Present = present)
#define GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_TMSI_CODE_ADDR_23_16(sp) ((sp)->TMSI_CODE_ADDR_23_16_Present)
#define SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_ADDR_LEN(sp,present) ((sp)->ADDR_LEN_Present = present)
#define GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_ADDR_LEN(sp) ((sp)->ADDR_LEN_Present)
void SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_BC_ADDR_REMAINDER (c_f_csch_Universal_Page_Block_page_records_data* sp, ED_BOOLEAN present);
#define GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_BC_ADDR_REMAINDER(sp) ((sp)->BC_ADDR_REMAINDER_Present)
#define SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_EXT_MS_SDU_LENGTH_INCL(sp,present) ((sp)->EXT_MS_SDU_LENGTH_INCL_Present = present)
#define GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_EXT_MS_SDU_LENGTH_INCL(sp) ((sp)->EXT_MS_SDU_LENGTH_INCL_Present)
#define SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_EXT_MS_SDU_LENGTH(sp,present) ((sp)->EXT_MS_SDU_LENGTH_Present = present)
#define GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_EXT_MS_SDU_LENGTH(sp) ((sp)->EXT_MS_SDU_LENGTH_Present)
#define SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_EXT_BCAST_SDU_LENGTH_IND(sp,present) ((sp)->EXT_BCAST_SDU_LENGTH_IND_Present = present)
#define GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_EXT_BCAST_SDU_LENGTH_IND(sp) ((sp)->EXT_BCAST_SDU_LENGTH_IND_Present)
#define SETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_EXT_BCAST_SDU_LENGTH(sp,present) ((sp)->EXT_BCAST_SDU_LENGTH_Present = present)
#define GETPRESENT_c_f_csch_Universal_Page_Block_page_records_data_EXT_BCAST_SDU_LENGTH(sp) ((sp)->EXT_BCAST_SDU_LENGTH_Present)

/* Access member 'MEID' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address_MEID(var) var

/* Access member 'MEID' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address_MEID(var) (&var)

/* DEFINITION OF BINARY c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address_MEID */
typedef struct _c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address_MEID {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address_MEID;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address_MEID(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address {

	c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address_MEID MEID; /* Static, variable size; bits needed 16 *//*GBD01b*/

}	c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address;
#define INIT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address(sp) ED_RESET_MEM ((sp), sizeof (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address))
/*FRK03a*/
void FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address(c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address* sp);

/* Access member 'IMSI_M_S1' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S_IMSI_M_S1(var) var

/* Access member 'IMSI_M_S1' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S_IMSI_M_S1(var) (&var)

/* Access member 'IMSI_M_S2' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S_IMSI_M_S2(var) var

/* Access member 'IMSI_M_S2' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S_IMSI_M_S2(var) (&var)


/*-A----------------------------------*/
typedef struct _c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S {

	ED_LONG IMSI_M_S1; /* ODY01a *//*GBD01b*/
	ED_LONG IMSI_M_S2; /* ODY01a *//*GBD01b*/

}	c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S;
#define INIT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S(sp) ED_RESET_MEM ((sp), sizeof (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S))
/*FRK03a*/
void FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S(c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S* sp);

/* Access member 'ESN' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN_ESN(var) var

/* Access member 'ESN' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN_ESN(var) (&var)

/* DEFINITION OF BINARY c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN_ESN */
typedef struct _c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN_ESN {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN_ESN;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN_ESN(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN {

	c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN_ESN ESN; /* Static, variable size; bits needed 16 *//*GBD01b*/

}	c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN;
#define INIT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN(sp) ED_RESET_MEM ((sp), sizeof (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN))
/*FRK03a*/
void FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN(c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN* sp);

/* Access member 'IMSI_CLASS' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS(var) var

/* Access member 'IMSI_CLASS' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS(var) (&var)

/* Access member 'IMSI_CLASS_0' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0(var) (*var)

/* Access member 'IMSI_CLASS_0' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0(var) var

/* Access member 'IMSI_CLASS_1' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1(var) (*var)

/* Access member 'IMSI_CLASS_1' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1(var) var


/*-A----------------------------------*/
typedef struct _c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI {

	ED_BOOLEAN IMSI_CLASS; /* ODY01a *//*GBD01b*/
	c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0 *IMSI_CLASS_0; /* ODY01 *//*GBD01b*/
	ED_BOOLEAN IMSI_CLASS_0_Present;
	c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1 *IMSI_CLASS_1; /* ODY01 *//*GBD01b*/
	ED_BOOLEAN IMSI_CLASS_1_Present;

}	c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI;
#define INIT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI(sp) ED_RESET_MEM ((sp), sizeof (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI))
/*FRK03a*/
void FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI(c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI* sp);
void SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0 (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI* sp, ED_BOOLEAN present);
#define GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_0(sp) ((sp)->IMSI_CLASS_0_Present)
void SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1 (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI* sp, ED_BOOLEAN present);
#define GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_IMSI_CLASS_1(sp) ((sp)->IMSI_CLASS_1_Present)

/* Access member 'TMSI_ZONE' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI_TMSI_ZONE(var) var

/* Access member 'TMSI_ZONE' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI_TMSI_ZONE(var) (&var)

/* Access member 'TMSI_CODE_ADDR' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI_TMSI_CODE_ADDR(var) var

/* Access member 'TMSI_CODE_ADDR' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI_TMSI_CODE_ADDR(var) (&var)

/* DEFINITION OF BINARY c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI_TMSI_ZONE */
typedef struct _c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI_TMSI_ZONE {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI_TMSI_ZONE;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI_TMSI_ZONE(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF BINARY c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI_TMSI_CODE_ADDR */
typedef struct _c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI_TMSI_CODE_ADDR {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI_TMSI_CODE_ADDR;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI_TMSI_CODE_ADDR(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI {

	c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI_TMSI_ZONE TMSI_ZONE; /* Static, variable size; bits needed 16 *//*GBD01b*/
	c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI_TMSI_CODE_ADDR TMSI_CODE_ADDR; /* Static, variable size; bits needed 16 *//*GBD01b*/

}	c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI;
#define INIT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI(sp) ED_RESET_MEM ((sp), sizeof (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI))
/*FRK03a*/
void FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI(c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI* sp);

/* Access member 'BC_ADDR' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST_BC_ADDR(var) var

/* Access member 'BC_ADDR' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST_BC_ADDR(var) (&var)

/* DEFINITION OF BINARY c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST_BC_ADDR */
typedef struct _c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST_BC_ADDR {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST_BC_ADDR;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST_BC_ADDR(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST {

	c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST_BC_ADDR BC_ADDR; /* Static, variable size; bits needed 16 *//*GBD01b*/

}	c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST;
#define INIT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST(sp) ED_RESET_MEM ((sp), sizeof (c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST))
/*FRK03a*/
void FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST(c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST* sp);

/* Access member 'LAC_LENGTH' of type 'c_r_csch_PDU_LAC_Length' as a variable reference */
#define VAR_c_r_csch_PDU_LAC_Length_LAC_LENGTH(var) var

/* Access member 'LAC_LENGTH' of type 'c_r_csch_PDU_LAC_Length' as a pointer */
#define PTR_c_r_csch_PDU_LAC_Length_LAC_LENGTH(var) (&var)


/*-A----------------------------------*/
typedef struct _c_r_csch_PDU_LAC_Length {

	ED_OCTET LAC_LENGTH; /* ODY01a *//*GBD01b*/

}	c_r_csch_PDU_LAC_Length;
#define INIT_c_r_csch_PDU_LAC_Length(sp) ED_RESET_MEM ((sp), sizeof (c_r_csch_PDU_LAC_Length))
/*FRK03a*/
void FREE_c_r_csch_PDU_LAC_Length(c_r_csch_PDU_LAC_Length* sp);

/* Access member 'PD' of type 'c_r_csch_PDU_Message_Type' as a variable reference */
#define VAR_c_r_csch_PDU_Message_Type_PD(var) var

/* Access member 'PD' of type 'c_r_csch_PDU_Message_Type' as a pointer */
#define PTR_c_r_csch_PDU_Message_Type_PD(var) (&var)

/* Access member 'MSG_ID' of type 'c_r_csch_PDU_Message_Type' as a variable reference */
#define VAR_c_r_csch_PDU_Message_Type_MSG_ID(var) var

/* Access member 'MSG_ID' of type 'c_r_csch_PDU_Message_Type' as a pointer */
#define PTR_c_r_csch_PDU_Message_Type_MSG_ID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_r_csch_PDU_Message_Type {

	ED_OCTET PD; /* ODY01a *//*GBD01b*/
	ED_OCTET MSG_ID; /* ODY01a *//*GBD01b*/

}	c_r_csch_PDU_Message_Type;
#define INIT_c_r_csch_PDU_Message_Type(sp) ED_RESET_MEM ((sp), sizeof (c_r_csch_PDU_Message_Type))
/*FRK03a*/
void FREE_c_r_csch_PDU_Message_Type(c_r_csch_PDU_Message_Type* sp);

/* Access member 'ACK_SEQ' of type 'c_r_csch_PDU_ARQ' as a variable reference */
#define VAR_c_r_csch_PDU_ARQ_ACK_SEQ(var) var

/* Access member 'ACK_SEQ' of type 'c_r_csch_PDU_ARQ' as a pointer */
#define PTR_c_r_csch_PDU_ARQ_ACK_SEQ(var) (&var)

/* Access member 'MSG_SEQ' of type 'c_r_csch_PDU_ARQ' as a variable reference */
#define VAR_c_r_csch_PDU_ARQ_MSG_SEQ(var) var

/* Access member 'MSG_SEQ' of type 'c_r_csch_PDU_ARQ' as a pointer */
#define PTR_c_r_csch_PDU_ARQ_MSG_SEQ(var) (&var)

/* Access member 'ACK_REQ' of type 'c_r_csch_PDU_ARQ' as a variable reference */
#define VAR_c_r_csch_PDU_ARQ_ACK_REQ(var) var

/* Access member 'ACK_REQ' of type 'c_r_csch_PDU_ARQ' as a pointer */
#define PTR_c_r_csch_PDU_ARQ_ACK_REQ(var) (&var)

/* Access member 'VALID_ACK' of type 'c_r_csch_PDU_ARQ' as a variable reference */
#define VAR_c_r_csch_PDU_ARQ_VALID_ACK(var) var

/* Access member 'VALID_ACK' of type 'c_r_csch_PDU_ARQ' as a pointer */
#define PTR_c_r_csch_PDU_ARQ_VALID_ACK(var) (&var)

/* Access member 'ACK_TYPE' of type 'c_r_csch_PDU_ARQ' as a variable reference */
#define VAR_c_r_csch_PDU_ARQ_ACK_TYPE(var) var

/* Access member 'ACK_TYPE' of type 'c_r_csch_PDU_ARQ' as a pointer */
#define PTR_c_r_csch_PDU_ARQ_ACK_TYPE(var) (&var)

/* Access member 'EXT_ACK_TYPE' of type 'c_r_csch_PDU_ARQ' as a variable reference */
#define VAR_c_r_csch_PDU_ARQ_EXT_ACK_TYPE(var) var

/* Access member 'EXT_ACK_TYPE' of type 'c_r_csch_PDU_ARQ' as a pointer */
#define PTR_c_r_csch_PDU_ARQ_EXT_ACK_TYPE(var) (&var)


/*-A----------------------------------*/
typedef struct _c_r_csch_PDU_ARQ {

	ED_OCTET ACK_SEQ; /* ODY01a *//*GBD01b*/
	ED_OCTET MSG_SEQ; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ACK_REQ; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN VALID_ACK; /* ODY01a *//*GBD01b*/
	ED_OCTET ACK_TYPE; /* ODY01a *//*GBD01b*/
	ED_OCTET EXT_ACK_TYPE; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN EXT_ACK_TYPE_Present;

}	c_r_csch_PDU_ARQ;
#define INIT_c_r_csch_PDU_ARQ(sp) ED_RESET_MEM ((sp), sizeof (c_r_csch_PDU_ARQ))
/*FRK03a*/
void FREE_c_r_csch_PDU_ARQ(c_r_csch_PDU_ARQ* sp);
#define SETPRESENT_c_r_csch_PDU_ARQ_EXT_ACK_TYPE(sp,present) ((sp)->EXT_ACK_TYPE_Present = present)
#define GETPRESENT_c_r_csch_PDU_ARQ_EXT_ACK_TYPE(sp) ((sp)->EXT_ACK_TYPE_Present)

/* Access member 'MSID_TYPE' of type 'c_r_csch_PDU_Addressing' as a variable reference */
#define VAR_c_r_csch_PDU_Addressing_MSID_TYPE(var) var

/* Access member 'MSID_TYPE' of type 'c_r_csch_PDU_Addressing' as a pointer */
#define PTR_c_r_csch_PDU_Addressing_MSID_TYPE(var) (&var)

/* Access member 'EXT_MSID_TYPE' of type 'c_r_csch_PDU_Addressing' as a variable reference */
#define VAR_c_r_csch_PDU_Addressing_EXT_MSID_TYPE(var) var

/* Access member 'EXT_MSID_TYPE' of type 'c_r_csch_PDU_Addressing' as a pointer */
#define PTR_c_r_csch_PDU_Addressing_EXT_MSID_TYPE(var) (&var)

/* Access member 'MSID_LEN' of type 'c_r_csch_PDU_Addressing' as a variable reference */
#define VAR_c_r_csch_PDU_Addressing_MSID_LEN(var) var

/* Access member 'MSID_LEN' of type 'c_r_csch_PDU_Addressing' as a pointer */
#define PTR_c_r_csch_PDU_Addressing_MSID_LEN(var) (&var)

/* Access member 'IMSI_M_S1' of type 'c_r_csch_PDU_Addressing' as a variable reference */
#define VAR_c_r_csch_PDU_Addressing_IMSI_M_S1(var) var

/* Access member 'IMSI_M_S1' of type 'c_r_csch_PDU_Addressing' as a pointer */
#define PTR_c_r_csch_PDU_Addressing_IMSI_M_S1(var) (&var)

/* Access member 'IMSI_M_S2' of type 'c_r_csch_PDU_Addressing' as a variable reference */
#define VAR_c_r_csch_PDU_Addressing_IMSI_M_S2(var) var

/* Access member 'IMSI_M_S2' of type 'c_r_csch_PDU_Addressing' as a pointer */
#define PTR_c_r_csch_PDU_Addressing_IMSI_M_S2(var) (&var)

/* Access member 'ESN' of type 'c_r_csch_PDU_Addressing' as a variable reference */
#define VAR_c_r_csch_PDU_Addressing_ESN(var) var

/* Access member 'ESN' of type 'c_r_csch_PDU_Addressing' as a pointer */
#define PTR_c_r_csch_PDU_Addressing_ESN(var) (&var)

/* Access member 'MEID' of type 'c_r_csch_PDU_Addressing' as a variable reference */
#define VAR_c_r_csch_PDU_Addressing_MEID(var) (*var)

/* Access member 'MEID' of type 'c_r_csch_PDU_Addressing' as a pointer */
#define PTR_c_r_csch_PDU_Addressing_MEID(var) var

/* Access member 'IMSI_CLASS' of type 'c_r_csch_PDU_Addressing' as a variable reference */
#define VAR_c_r_csch_PDU_Addressing_IMSI_CLASS(var) var

/* Access member 'IMSI_CLASS' of type 'c_r_csch_PDU_Addressing' as a pointer */
#define PTR_c_r_csch_PDU_Addressing_IMSI_CLASS(var) (&var)

/* Access member 'IMSI_class_specific_subfields' of type 'c_r_csch_PDU_Addressing' as a variable reference */
#define VAR_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields(var) (*var)

/* Access member 'IMSI_class_specific_subfields' of type 'c_r_csch_PDU_Addressing' as a pointer */
#define PTR_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields(var) var

/* Access member 'TMSI_ZONE' of type 'c_r_csch_PDU_Addressing' as a variable reference */
#define VAR_c_r_csch_PDU_Addressing_TMSI_ZONE(var) (*var)

/* Access member 'TMSI_ZONE' of type 'c_r_csch_PDU_Addressing' as a pointer */
#define PTR_c_r_csch_PDU_Addressing_TMSI_ZONE(var) var

/* Access member 'TMSI_CODE_ADDR' of type 'c_r_csch_PDU_Addressing' as a variable reference */
#define VAR_c_r_csch_PDU_Addressing_TMSI_CODE_ADDR(var) (*var)

/* Access member 'TMSI_CODE_ADDR' of type 'c_r_csch_PDU_Addressing' as a pointer */
#define PTR_c_r_csch_PDU_Addressing_TMSI_CODE_ADDR(var) var

/* DEFINITION OF BINARY c_r_csch_PDU_Addressing_TMSI_ZONE */
typedef struct _c_r_csch_PDU_Addressing_TMSI_ZONE {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_r_csch_PDU_Addressing_TMSI_ZONE;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_r_csch_PDU_Addressing_TMSI_ZONE(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF BINARY c_r_csch_PDU_Addressing_TMSI_CODE_ADDR */
typedef struct _c_r_csch_PDU_Addressing_TMSI_CODE_ADDR {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_r_csch_PDU_Addressing_TMSI_CODE_ADDR;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_r_csch_PDU_Addressing_TMSI_CODE_ADDR(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_r_csch_PDU_Addressing {

	ED_OCTET MSID_TYPE; /* ODY01a *//*GBD01b*/
	ED_OCTET EXT_MSID_TYPE; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN EXT_MSID_TYPE_Present;
	ED_OCTET MSID_LEN; /* ODY01a *//*GBD01b*/
	ED_LONG IMSI_M_S1; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN IMSI_M_S1_Present;
	ED_LONG IMSI_M_S2; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN IMSI_M_S2_Present;
	ED_LONG ESN; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ESN_Present;
	ED_BYTE* MEID; /* Dynamic, fixed size; bits needed: 56 ODY02a *//*GBD01b*/
	ED_BOOLEAN MEID_Present;
	ED_BOOLEAN IMSI_CLASS; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN IMSI_CLASS_Present;
	c_r_csch_PDU_Addressing_IMSI_class_specific_subfields *IMSI_class_specific_subfields; /* ODY01 *//*GBD01b*/
	ED_BOOLEAN IMSI_class_specific_subfields_Present;
	c_r_csch_PDU_Addressing_TMSI_ZONE* TMSI_ZONE; /* Dynamic, variable size; bits needed 16 ODY02b *//*GBD01b*/
	ED_BOOLEAN TMSI_ZONE_Present;
	c_r_csch_PDU_Addressing_TMSI_CODE_ADDR* TMSI_CODE_ADDR; /* Dynamic, variable size; bits needed 16 ODY02b *//*GBD01b*/
	ED_BOOLEAN TMSI_CODE_ADDR_Present;

}	c_r_csch_PDU_Addressing;
#define INIT_c_r_csch_PDU_Addressing(sp) ED_RESET_MEM ((sp), sizeof (c_r_csch_PDU_Addressing))
/*FRK03a*/
void FREE_c_r_csch_PDU_Addressing(c_r_csch_PDU_Addressing* sp);
#define SETPRESENT_c_r_csch_PDU_Addressing_EXT_MSID_TYPE(sp,present) ((sp)->EXT_MSID_TYPE_Present = present)
#define GETPRESENT_c_r_csch_PDU_Addressing_EXT_MSID_TYPE(sp) ((sp)->EXT_MSID_TYPE_Present)
#define SETPRESENT_c_r_csch_PDU_Addressing_IMSI_M_S1(sp,present) ((sp)->IMSI_M_S1_Present = present)
#define GETPRESENT_c_r_csch_PDU_Addressing_IMSI_M_S1(sp) ((sp)->IMSI_M_S1_Present)
#define SETPRESENT_c_r_csch_PDU_Addressing_IMSI_M_S2(sp,present) ((sp)->IMSI_M_S2_Present = present)
#define GETPRESENT_c_r_csch_PDU_Addressing_IMSI_M_S2(sp) ((sp)->IMSI_M_S2_Present)
#define SETPRESENT_c_r_csch_PDU_Addressing_ESN(sp,present) ((sp)->ESN_Present = present)
#define GETPRESENT_c_r_csch_PDU_Addressing_ESN(sp) ((sp)->ESN_Present)
void SETPRESENT_c_r_csch_PDU_Addressing_MEID (c_r_csch_PDU_Addressing* sp, ED_BOOLEAN present);
#define GETPRESENT_c_r_csch_PDU_Addressing_MEID(sp) ((sp)->MEID_Present)
#define SETPRESENT_c_r_csch_PDU_Addressing_IMSI_CLASS(sp,present) ((sp)->IMSI_CLASS_Present = present)
#define GETPRESENT_c_r_csch_PDU_Addressing_IMSI_CLASS(sp) ((sp)->IMSI_CLASS_Present)
void SETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields (c_r_csch_PDU_Addressing* sp, ED_BOOLEAN present);
#define GETPRESENT_c_r_csch_PDU_Addressing_IMSI_class_specific_subfields(sp) ((sp)->IMSI_class_specific_subfields_Present)
void SETPRESENT_c_r_csch_PDU_Addressing_TMSI_ZONE (c_r_csch_PDU_Addressing* sp, ED_BOOLEAN present);
#define GETPRESENT_c_r_csch_PDU_Addressing_TMSI_ZONE(sp) ((sp)->TMSI_ZONE_Present)
void SETPRESENT_c_r_csch_PDU_Addressing_TMSI_CODE_ADDR (c_r_csch_PDU_Addressing* sp, ED_BOOLEAN present);
#define GETPRESENT_c_r_csch_PDU_Addressing_TMSI_CODE_ADDR(sp) ((sp)->TMSI_CODE_ADDR_Present)

/* Access member 'MACI_INCL' of type 'c_r_csch_PDU_Authentication' as a variable reference */
#define VAR_c_r_csch_PDU_Authentication_MACI_INCL(var) var

/* Access member 'MACI_INCL' of type 'c_r_csch_PDU_Authentication' as a pointer */
#define PTR_c_r_csch_PDU_Authentication_MACI_INCL(var) (&var)

/* Access member 'AUTH_MODE_INCL' of type 'c_r_csch_PDU_Authentication' as a variable reference */
#define VAR_c_r_csch_PDU_Authentication_AUTH_MODE_INCL(var) var

/* Access member 'AUTH_MODE_INCL' of type 'c_r_csch_PDU_Authentication' as a pointer */
#define PTR_c_r_csch_PDU_Authentication_AUTH_MODE_INCL(var) (&var)

/* Access member 'AUTHR' of type 'c_r_csch_PDU_Authentication' as a variable reference */
#define VAR_c_r_csch_PDU_Authentication_AUTHR(var) var

/* Access member 'AUTHR' of type 'c_r_csch_PDU_Authentication' as a pointer */
#define PTR_c_r_csch_PDU_Authentication_AUTHR(var) (&var)

/* Access member 'RANDC' of type 'c_r_csch_PDU_Authentication' as a variable reference */
#define VAR_c_r_csch_PDU_Authentication_RANDC(var) var

/* Access member 'RANDC' of type 'c_r_csch_PDU_Authentication' as a pointer */
#define PTR_c_r_csch_PDU_Authentication_RANDC(var) (&var)

/* Access member 'COUNT' of type 'c_r_csch_PDU_Authentication' as a variable reference */
#define VAR_c_r_csch_PDU_Authentication_COUNT(var) var

/* Access member 'COUNT' of type 'c_r_csch_PDU_Authentication' as a pointer */
#define PTR_c_r_csch_PDU_Authentication_COUNT(var) (&var)

/* Access member 'SDU_KEY_ID' of type 'c_r_csch_PDU_Authentication' as a variable reference */
#define VAR_c_r_csch_PDU_Authentication_SDU_KEY_ID(var) var

/* Access member 'SDU_KEY_ID' of type 'c_r_csch_PDU_Authentication' as a pointer */
#define PTR_c_r_csch_PDU_Authentication_SDU_KEY_ID(var) (&var)

/* Access member 'SDU_INTEGRITY_ALGO' of type 'c_r_csch_PDU_Authentication' as a variable reference */
#define VAR_c_r_csch_PDU_Authentication_SDU_INTEGRITY_ALGO(var) var

/* Access member 'SDU_INTEGRITY_ALGO' of type 'c_r_csch_PDU_Authentication' as a pointer */
#define PTR_c_r_csch_PDU_Authentication_SDU_INTEGRITY_ALGO(var) (&var)

/* Access member 'SDU_SSEQ_OR_SSEQH' of type 'c_r_csch_PDU_Authentication' as a variable reference */
#define VAR_c_r_csch_PDU_Authentication_SDU_SSEQ_OR_SSEQH(var) var

/* Access member 'SDU_SSEQ_OR_SSEQH' of type 'c_r_csch_PDU_Authentication' as a pointer */
#define PTR_c_r_csch_PDU_Authentication_SDU_SSEQ_OR_SSEQH(var) (&var)

/* Access member 'SDU_SSEQ' of type 'c_r_csch_PDU_Authentication' as a variable reference */
#define VAR_c_r_csch_PDU_Authentication_SDU_SSEQ(var) var

/* Access member 'SDU_SSEQ' of type 'c_r_csch_PDU_Authentication' as a pointer */
#define PTR_c_r_csch_PDU_Authentication_SDU_SSEQ(var) (&var)

/* Access member 'SDU_SSEQ_H' of type 'c_r_csch_PDU_Authentication' as a variable reference */
#define VAR_c_r_csch_PDU_Authentication_SDU_SSEQ_H(var) var

/* Access member 'SDU_SSEQ_H' of type 'c_r_csch_PDU_Authentication' as a pointer */
#define PTR_c_r_csch_PDU_Authentication_SDU_SSEQ_H(var) (&var)


/*-A----------------------------------*/
typedef struct _c_r_csch_PDU_Authentication {

	ED_BOOLEAN MACI_INCL; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN AUTH_MODE_INCL; /* ODY01a *//*GBD01b*/
	ED_LONG AUTHR; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN AUTHR_Present;
	ED_OCTET RANDC; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN RANDC_Present;
	ED_OCTET COUNT; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN COUNT_Present;
	ED_OCTET SDU_KEY_ID; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SDU_KEY_ID_Present;
	ED_OCTET SDU_INTEGRITY_ALGO; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SDU_INTEGRITY_ALGO_Present;
	ED_BOOLEAN SDU_SSEQ_OR_SSEQH; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SDU_SSEQ_OR_SSEQH_Present;
	ED_OCTET SDU_SSEQ; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SDU_SSEQ_Present;
	ED_LONG SDU_SSEQ_H; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SDU_SSEQ_H_Present;

}	c_r_csch_PDU_Authentication;
#define INIT_c_r_csch_PDU_Authentication(sp) ED_RESET_MEM ((sp), sizeof (c_r_csch_PDU_Authentication))
/*FRK03a*/
void FREE_c_r_csch_PDU_Authentication(c_r_csch_PDU_Authentication* sp);
#define SETPRESENT_c_r_csch_PDU_Authentication_AUTHR(sp,present) ((sp)->AUTHR_Present = present)
#define GETPRESENT_c_r_csch_PDU_Authentication_AUTHR(sp) ((sp)->AUTHR_Present)
#define SETPRESENT_c_r_csch_PDU_Authentication_RANDC(sp,present) ((sp)->RANDC_Present = present)
#define GETPRESENT_c_r_csch_PDU_Authentication_RANDC(sp) ((sp)->RANDC_Present)
#define SETPRESENT_c_r_csch_PDU_Authentication_COUNT(sp,present) ((sp)->COUNT_Present = present)
#define GETPRESENT_c_r_csch_PDU_Authentication_COUNT(sp) ((sp)->COUNT_Present)
#define SETPRESENT_c_r_csch_PDU_Authentication_SDU_KEY_ID(sp,present) ((sp)->SDU_KEY_ID_Present = present)
#define GETPRESENT_c_r_csch_PDU_Authentication_SDU_KEY_ID(sp) ((sp)->SDU_KEY_ID_Present)
#define SETPRESENT_c_r_csch_PDU_Authentication_SDU_INTEGRITY_ALGO(sp,present) ((sp)->SDU_INTEGRITY_ALGO_Present = present)
#define GETPRESENT_c_r_csch_PDU_Authentication_SDU_INTEGRITY_ALGO(sp) ((sp)->SDU_INTEGRITY_ALGO_Present)
#define SETPRESENT_c_r_csch_PDU_Authentication_SDU_SSEQ_OR_SSEQH(sp,present) ((sp)->SDU_SSEQ_OR_SSEQH_Present = present)
#define GETPRESENT_c_r_csch_PDU_Authentication_SDU_SSEQ_OR_SSEQH(sp) ((sp)->SDU_SSEQ_OR_SSEQH_Present)
#define SETPRESENT_c_r_csch_PDU_Authentication_SDU_SSEQ(sp,present) ((sp)->SDU_SSEQ_Present = present)
#define GETPRESENT_c_r_csch_PDU_Authentication_SDU_SSEQ(sp) ((sp)->SDU_SSEQ_Present)
#define SETPRESENT_c_r_csch_PDU_Authentication_SDU_SSEQ_H(sp,present) ((sp)->SDU_SSEQ_H_Present = present)
#define GETPRESENT_c_r_csch_PDU_Authentication_SDU_SSEQ_H(sp) ((sp)->SDU_SSEQ_H_Present)

/* Access member 'ENC_FIELDS_INCL' of type 'c_r_csch_PDU_Extended_Encryption' as a variable reference */
#define VAR_c_r_csch_PDU_Extended_Encryption_ENC_FIELDS_INCL(var) var

/* Access member 'ENC_FIELDS_INCL' of type 'c_r_csch_PDU_Extended_Encryption' as a pointer */
#define PTR_c_r_csch_PDU_Extended_Encryption_ENC_FIELDS_INCL(var) (&var)

/* Access member 'SDU_ENCRYPT_MODE' of type 'c_r_csch_PDU_Extended_Encryption' as a variable reference */
#define VAR_c_r_csch_PDU_Extended_Encryption_SDU_ENCRYPT_MODE(var) var

/* Access member 'SDU_ENCRYPT_MODE' of type 'c_r_csch_PDU_Extended_Encryption' as a pointer */
#define PTR_c_r_csch_PDU_Extended_Encryption_SDU_ENCRYPT_MODE(var) (&var)

/* Access member 'ENC_SEQ' of type 'c_r_csch_PDU_Extended_Encryption' as a variable reference */
#define VAR_c_r_csch_PDU_Extended_Encryption_ENC_SEQ(var) var

/* Access member 'ENC_SEQ' of type 'c_r_csch_PDU_Extended_Encryption' as a pointer */
#define PTR_c_r_csch_PDU_Extended_Encryption_ENC_SEQ(var) (&var)


/*-A----------------------------------*/
typedef struct _c_r_csch_PDU_Extended_Encryption {

	ED_BOOLEAN ENC_FIELDS_INCL; /* ODY01a *//*GBD01b*/
	ED_OCTET SDU_ENCRYPT_MODE; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SDU_ENCRYPT_MODE_Present;
	ED_OCTET ENC_SEQ; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ENC_SEQ_Present;

}	c_r_csch_PDU_Extended_Encryption;
#define INIT_c_r_csch_PDU_Extended_Encryption(sp) ED_RESET_MEM ((sp), sizeof (c_r_csch_PDU_Extended_Encryption))
/*FRK03a*/
void FREE_c_r_csch_PDU_Extended_Encryption(c_r_csch_PDU_Extended_Encryption* sp);
#define SETPRESENT_c_r_csch_PDU_Extended_Encryption_SDU_ENCRYPT_MODE(sp,present) ((sp)->SDU_ENCRYPT_MODE_Present = present)
#define GETPRESENT_c_r_csch_PDU_Extended_Encryption_SDU_ENCRYPT_MODE(sp) ((sp)->SDU_ENCRYPT_MODE_Present)
#define SETPRESENT_c_r_csch_PDU_Extended_Encryption_ENC_SEQ(sp,present) ((sp)->ENC_SEQ_Present = present)
#define GETPRESENT_c_r_csch_PDU_Extended_Encryption_ENC_SEQ(sp) ((sp)->ENC_SEQ_Present)

/* Access member 'ACTIVE_PILOT_STRENGTH' of type 'c_r_csch_Radio_Environment_Report' as a variable reference */
#define VAR_c_r_csch_Radio_Environment_Report_ACTIVE_PILOT_STRENGTH(var) var

/* Access member 'ACTIVE_PILOT_STRENGTH' of type 'c_r_csch_Radio_Environment_Report' as a pointer */
#define PTR_c_r_csch_Radio_Environment_Report_ACTIVE_PILOT_STRENGTH(var) (&var)

/* Access member 'FIRST_IS_ACTIVE' of type 'c_r_csch_Radio_Environment_Report' as a variable reference */
#define VAR_c_r_csch_Radio_Environment_Report_FIRST_IS_ACTIVE(var) var

/* Access member 'FIRST_IS_ACTIVE' of type 'c_r_csch_Radio_Environment_Report' as a pointer */
#define PTR_c_r_csch_Radio_Environment_Report_FIRST_IS_ACTIVE(var) (&var)

/* Access member 'FIRST_IS_PTA' of type 'c_r_csch_Radio_Environment_Report' as a variable reference */
#define VAR_c_r_csch_Radio_Environment_Report_FIRST_IS_PTA(var) var

/* Access member 'FIRST_IS_PTA' of type 'c_r_csch_Radio_Environment_Report' as a pointer */
#define PTR_c_r_csch_Radio_Environment_Report_FIRST_IS_PTA(var) (&var)

/* Access member 'NUM_ADD_PILOTS' of type 'c_r_csch_Radio_Environment_Report' as a variable reference */
#define VAR_c_r_csch_Radio_Environment_Report_NUM_ADD_PILOTS(var) var

/* Access member 'NUM_ADD_PILOTS' of type 'c_r_csch_Radio_Environment_Report' as a pointer */
#define PTR_c_r_csch_Radio_Environment_Report_NUM_ADD_PILOTS(var) (&var)

/* Access member 'data' of type 'c_r_csch_Radio_Environment_Report_ADD_PILOTS' as a variable reference */
#define VAR_c_r_csch_Radio_Environment_Report_ADD_PILOTS_data(var) (*var)

/* Access member 'data' of type 'c_r_csch_Radio_Environment_Report_ADD_PILOTS' as a pointer */
#define PTR_c_r_csch_Radio_Environment_Report_ADD_PILOTS_data(var) var

/* Access member 'ADD_PILOTS' of type 'c_r_csch_Radio_Environment_Report' as a variable reference */
#define VAR_c_r_csch_Radio_Environment_Report_ADD_PILOTS(var) var

/* Access member 'ADD_PILOTS' of type 'c_r_csch_Radio_Environment_Report' as a pointer */
#define PTR_c_r_csch_Radio_Environment_Report_ADD_PILOTS(var) (&var)

/* Access member 'Aux_Radio_Environment_Report' of type 'c_r_csch_Radio_Environment_Report' as a variable reference */
#define VAR_c_r_csch_Radio_Environment_Report_Aux_Radio_Environment_Report(var) (*var)

/* Access member 'Aux_Radio_Environment_Report' of type 'c_r_csch_Radio_Environment_Report' as a pointer */
#define PTR_c_r_csch_Radio_Environment_Report_Aux_Radio_Environment_Report(var) var

/* DEFINITION OF SUB-STRUCTURE c_r_csch_Radio_Environment_Report_ADD_PILOTS */
typedef struct _c_r_csch_Radio_Environment_Report_ADD_PILOTS {

	c_r_csch_PDU_Radio_Environment_Report_ADD_PILOTS_data **data; /* NDY01 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_r_csch_Radio_Environment_Report_ADD_PILOTS;


/*-A----------------------------------*/
typedef struct _c_r_csch_Radio_Environment_Report {

	ED_OCTET ACTIVE_PILOT_STRENGTH; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN FIRST_IS_ACTIVE; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN FIRST_IS_PTA; /* ODY01a *//*GBD01b*/
	ED_OCTET NUM_ADD_PILOTS; /* ODY01a *//*GBD01b*/
	c_r_csch_Radio_Environment_Report_ADD_PILOTS ADD_PILOTS;/*GFB09*//*GBD01b*/
	c_r_csch_PDU_Radio_Environment_Report_Aux_Radio_Environment_Report *Aux_Radio_Environment_Report; /* ODY01 *//*GBD01b*/
	ED_BOOLEAN Aux_Radio_Environment_Report_Present;

}	c_r_csch_Radio_Environment_Report;
#define INIT_c_r_csch_Radio_Environment_Report(sp) ED_RESET_MEM ((sp), sizeof (c_r_csch_Radio_Environment_Report))
/*FRK03a*/
void FREE_c_r_csch_Radio_Environment_Report(c_r_csch_Radio_Environment_Report* sp);
void SETPRESENT_c_r_csch_Radio_Environment_Report_Aux_Radio_Environment_Report (c_r_csch_Radio_Environment_Report* sp, ED_BOOLEAN present);
#define GETPRESENT_c_r_csch_Radio_Environment_Report_Aux_Radio_Environment_Report(sp) ((sp)->Aux_Radio_Environment_Report_Present)

/* Access member 'MSG_TYPE' of type 'c_f_dsch_PDU_Regular_Message_Type' as a variable reference */
#define VAR_c_f_dsch_PDU_Regular_Message_Type_MSG_TYPE(var) var

/* Access member 'MSG_TYPE' of type 'c_f_dsch_PDU_Regular_Message_Type' as a pointer */
#define PTR_c_f_dsch_PDU_Regular_Message_Type_MSG_TYPE(var) (&var)


/*-A----------------------------------*/
typedef struct _c_f_dsch_PDU_Regular_Message_Type {

	ED_OCTET MSG_TYPE; /* ODY01a *//*GBD01b*/

}	c_f_dsch_PDU_Regular_Message_Type;
#define INIT_c_f_dsch_PDU_Regular_Message_Type(sp) ED_RESET_MEM ((sp), sizeof (c_f_dsch_PDU_Regular_Message_Type))
/*FRK03a*/
void FREE_c_f_dsch_PDU_Regular_Message_Type(c_f_dsch_PDU_Regular_Message_Type* sp);

/* Access member 'ACK_SEQ' of type 'c_f_dsch_PDU_Regular_ARQ' as a variable reference */
#define VAR_c_f_dsch_PDU_Regular_ARQ_ACK_SEQ(var) var

/* Access member 'ACK_SEQ' of type 'c_f_dsch_PDU_Regular_ARQ' as a pointer */
#define PTR_c_f_dsch_PDU_Regular_ARQ_ACK_SEQ(var) (&var)

/* Access member 'MSG_SEQ' of type 'c_f_dsch_PDU_Regular_ARQ' as a variable reference */
#define VAR_c_f_dsch_PDU_Regular_ARQ_MSG_SEQ(var) var

/* Access member 'MSG_SEQ' of type 'c_f_dsch_PDU_Regular_ARQ' as a pointer */
#define PTR_c_f_dsch_PDU_Regular_ARQ_MSG_SEQ(var) (&var)

/* Access member 'ACK_REQ' of type 'c_f_dsch_PDU_Regular_ARQ' as a variable reference */
#define VAR_c_f_dsch_PDU_Regular_ARQ_ACK_REQ(var) var

/* Access member 'ACK_REQ' of type 'c_f_dsch_PDU_Regular_ARQ' as a pointer */
#define PTR_c_f_dsch_PDU_Regular_ARQ_ACK_REQ(var) (&var)


/*-A----------------------------------*/
typedef struct _c_f_dsch_PDU_Regular_ARQ {

	ED_OCTET ACK_SEQ; /* ODY01a *//*GBD01b*/
	ED_OCTET MSG_SEQ; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ACK_REQ; /* ODY01a *//*GBD01b*/

}	c_f_dsch_PDU_Regular_ARQ;
#define INIT_c_f_dsch_PDU_Regular_ARQ(sp) ED_RESET_MEM ((sp), sizeof (c_f_dsch_PDU_Regular_ARQ))
/*FRK03a*/
void FREE_c_f_dsch_PDU_Regular_ARQ(c_f_dsch_PDU_Regular_ARQ* sp);

/* Access member 'ENCRYPTION' of type 'c_f_dsch_PDU_Regular_Encryption' as a variable reference */
#define VAR_c_f_dsch_PDU_Regular_Encryption_ENCRYPTION(var) var

/* Access member 'ENCRYPTION' of type 'c_f_dsch_PDU_Regular_Encryption' as a pointer */
#define PTR_c_f_dsch_PDU_Regular_Encryption_ENCRYPTION(var) (&var)


/*-A----------------------------------*/
typedef struct _c_f_dsch_PDU_Regular_Encryption {

	ED_OCTET ENCRYPTION; /* ODY01a *//*GBD01b*/

}	c_f_dsch_PDU_Regular_Encryption;
#define INIT_c_f_dsch_PDU_Regular_Encryption(sp) ED_RESET_MEM ((sp), sizeof (c_f_dsch_PDU_Regular_Encryption))
/*FRK03a*/
void FREE_c_f_dsch_PDU_Regular_Encryption(c_f_dsch_PDU_Regular_Encryption* sp);

/* Access member 'MACI_INCL' of type 'c_f_dsch_PDU_Regular_Integrity_Fields' as a variable reference */
#define VAR_c_f_dsch_PDU_Regular_Integrity_Fields_MACI_INCL(var) var

/* Access member 'MACI_INCL' of type 'c_f_dsch_PDU_Regular_Integrity_Fields' as a pointer */
#define PTR_c_f_dsch_PDU_Regular_Integrity_Fields_MACI_INCL(var) (&var)

/* Access member 'SDU_KEY_ID' of type 'c_f_dsch_PDU_Regular_Integrity_Fields' as a variable reference */
#define VAR_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_KEY_ID(var) var

/* Access member 'SDU_KEY_ID' of type 'c_f_dsch_PDU_Regular_Integrity_Fields' as a pointer */
#define PTR_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_KEY_ID(var) (&var)

/* Access member 'SDU_INTEGRITY_ALGO' of type 'c_f_dsch_PDU_Regular_Integrity_Fields' as a variable reference */
#define VAR_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_INTEGRITY_ALGO(var) var

/* Access member 'SDU_INTEGRITY_ALGO' of type 'c_f_dsch_PDU_Regular_Integrity_Fields' as a pointer */
#define PTR_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_INTEGRITY_ALGO(var) (&var)

/* Access member 'SDU_SSEQ_OR_SSEQH' of type 'c_f_dsch_PDU_Regular_Integrity_Fields' as a variable reference */
#define VAR_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ_OR_SSEQH(var) var

/* Access member 'SDU_SSEQ_OR_SSEQH' of type 'c_f_dsch_PDU_Regular_Integrity_Fields' as a pointer */
#define PTR_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ_OR_SSEQH(var) (&var)

/* Access member 'SDU_SSEQ' of type 'c_f_dsch_PDU_Regular_Integrity_Fields' as a variable reference */
#define VAR_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ(var) var

/* Access member 'SDU_SSEQ' of type 'c_f_dsch_PDU_Regular_Integrity_Fields' as a pointer */
#define PTR_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ(var) (&var)

/* Access member 'SDU_SSEQ_H' of type 'c_f_dsch_PDU_Regular_Integrity_Fields' as a variable reference */
#define VAR_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ_H(var) var

/* Access member 'SDU_SSEQ_H' of type 'c_f_dsch_PDU_Regular_Integrity_Fields' as a pointer */
#define PTR_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ_H(var) (&var)


/*-A----------------------------------*/
typedef struct _c_f_dsch_PDU_Regular_Integrity_Fields {

	ED_BOOLEAN MACI_INCL; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN MACI_INCL_Present;
	ED_OCTET SDU_KEY_ID; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SDU_KEY_ID_Present;
	ED_OCTET SDU_INTEGRITY_ALGO; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SDU_INTEGRITY_ALGO_Present;
	ED_BOOLEAN SDU_SSEQ_OR_SSEQH; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SDU_SSEQ_OR_SSEQH_Present;
	ED_OCTET SDU_SSEQ; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SDU_SSEQ_Present;
	ED_LONG SDU_SSEQ_H; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SDU_SSEQ_H_Present;

}	c_f_dsch_PDU_Regular_Integrity_Fields;
#define INIT_c_f_dsch_PDU_Regular_Integrity_Fields(sp) ED_RESET_MEM ((sp), sizeof (c_f_dsch_PDU_Regular_Integrity_Fields))
/*FRK03a*/
void FREE_c_f_dsch_PDU_Regular_Integrity_Fields(c_f_dsch_PDU_Regular_Integrity_Fields* sp);
#define SETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_MACI_INCL(sp,present) ((sp)->MACI_INCL_Present = present)
#define GETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_MACI_INCL(sp) ((sp)->MACI_INCL_Present)
#define SETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_KEY_ID(sp,present) ((sp)->SDU_KEY_ID_Present = present)
#define GETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_KEY_ID(sp) ((sp)->SDU_KEY_ID_Present)
#define SETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_INTEGRITY_ALGO(sp,present) ((sp)->SDU_INTEGRITY_ALGO_Present = present)
#define GETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_INTEGRITY_ALGO(sp) ((sp)->SDU_INTEGRITY_ALGO_Present)
#define SETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ_OR_SSEQH(sp,present) ((sp)->SDU_SSEQ_OR_SSEQH_Present = present)
#define GETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ_OR_SSEQH(sp) ((sp)->SDU_SSEQ_OR_SSEQH_Present)
#define SETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ(sp,present) ((sp)->SDU_SSEQ_Present = present)
#define GETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ(sp) ((sp)->SDU_SSEQ_Present)
#define SETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ_H(sp,present) ((sp)->SDU_SSEQ_H_Present = present)
#define GETPRESENT_c_f_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ_H(sp) ((sp)->SDU_SSEQ_H_Present)

/* Access member 'SDU_ENCRYPT_MODE' of type 'c_f_dsch_PDU_Regular_Extended_Encryption' as a variable reference */
#define VAR_c_f_dsch_PDU_Regular_Extended_Encryption_SDU_ENCRYPT_MODE(var) var

/* Access member 'SDU_ENCRYPT_MODE' of type 'c_f_dsch_PDU_Regular_Extended_Encryption' as a pointer */
#define PTR_c_f_dsch_PDU_Regular_Extended_Encryption_SDU_ENCRYPT_MODE(var) (&var)

/* Access member 'ENC_SEQ' of type 'c_f_dsch_PDU_Regular_Extended_Encryption' as a variable reference */
#define VAR_c_f_dsch_PDU_Regular_Extended_Encryption_ENC_SEQ(var) var

/* Access member 'ENC_SEQ' of type 'c_f_dsch_PDU_Regular_Extended_Encryption' as a pointer */
#define PTR_c_f_dsch_PDU_Regular_Extended_Encryption_ENC_SEQ(var) (&var)


/*-A----------------------------------*/
typedef struct _c_f_dsch_PDU_Regular_Extended_Encryption {

	ED_OCTET SDU_ENCRYPT_MODE; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SDU_ENCRYPT_MODE_Present;
	ED_OCTET ENC_SEQ; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ENC_SEQ_Present;

}	c_f_dsch_PDU_Regular_Extended_Encryption;
#define INIT_c_f_dsch_PDU_Regular_Extended_Encryption(sp) ED_RESET_MEM ((sp), sizeof (c_f_dsch_PDU_Regular_Extended_Encryption))
/*FRK03a*/
void FREE_c_f_dsch_PDU_Regular_Extended_Encryption(c_f_dsch_PDU_Regular_Extended_Encryption* sp);
#define SETPRESENT_c_f_dsch_PDU_Regular_Extended_Encryption_SDU_ENCRYPT_MODE(sp,present) ((sp)->SDU_ENCRYPT_MODE_Present = present)
#define GETPRESENT_c_f_dsch_PDU_Regular_Extended_Encryption_SDU_ENCRYPT_MODE(sp) ((sp)->SDU_ENCRYPT_MODE_Present)
#define SETPRESENT_c_f_dsch_PDU_Regular_Extended_Encryption_ENC_SEQ(sp,present) ((sp)->ENC_SEQ_Present = present)
#define GETPRESENT_c_f_dsch_PDU_Regular_Extended_Encryption_ENC_SEQ(sp) ((sp)->ENC_SEQ_Present)

/* Access member 'ACK_SEQ' of type 'c_f_dsch_PDU_Mini_ARQ' as a variable reference */
#define VAR_c_f_dsch_PDU_Mini_ARQ_ACK_SEQ(var) var

/* Access member 'ACK_SEQ' of type 'c_f_dsch_PDU_Mini_ARQ' as a pointer */
#define PTR_c_f_dsch_PDU_Mini_ARQ_ACK_SEQ(var) (&var)

/* Access member 'MSG_SEQ' of type 'c_f_dsch_PDU_Mini_ARQ' as a variable reference */
#define VAR_c_f_dsch_PDU_Mini_ARQ_MSG_SEQ(var) var

/* Access member 'MSG_SEQ' of type 'c_f_dsch_PDU_Mini_ARQ' as a pointer */
#define PTR_c_f_dsch_PDU_Mini_ARQ_MSG_SEQ(var) (&var)

/* Access member 'ACK_REQ' of type 'c_f_dsch_PDU_Mini_ARQ' as a variable reference */
#define VAR_c_f_dsch_PDU_Mini_ARQ_ACK_REQ(var) var

/* Access member 'ACK_REQ' of type 'c_f_dsch_PDU_Mini_ARQ' as a pointer */
#define PTR_c_f_dsch_PDU_Mini_ARQ_ACK_REQ(var) (&var)


/*-A----------------------------------*/
typedef struct _c_f_dsch_PDU_Mini_ARQ {

	ED_OCTET ACK_SEQ; /* ODY01a *//*GBD01b*/
	ED_OCTET MSG_SEQ; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ACK_REQ; /* ODY01a *//*GBD01b*/

}	c_f_dsch_PDU_Mini_ARQ;
#define INIT_c_f_dsch_PDU_Mini_ARQ(sp) ED_RESET_MEM ((sp), sizeof (c_f_dsch_PDU_Mini_ARQ))
/*FRK03a*/
void FREE_c_f_dsch_PDU_Mini_ARQ(c_f_dsch_PDU_Mini_ARQ* sp);

/* Access member 'MSG_TYPE' of type 'c_f_dsch_PDU_Mini_Message_Type' as a variable reference */
#define VAR_c_f_dsch_PDU_Mini_Message_Type_MSG_TYPE(var) var

/* Access member 'MSG_TYPE' of type 'c_f_dsch_PDU_Mini_Message_Type' as a pointer */
#define PTR_c_f_dsch_PDU_Mini_Message_Type_MSG_TYPE(var) (&var)


/*-A----------------------------------*/
typedef struct _c_f_dsch_PDU_Mini_Message_Type {

	ED_OCTET MSG_TYPE; /* ODY01a *//*GBD01b*/

}	c_f_dsch_PDU_Mini_Message_Type;
#define INIT_c_f_dsch_PDU_Mini_Message_Type(sp) ED_RESET_MEM ((sp), sizeof (c_f_dsch_PDU_Mini_Message_Type))
/*FRK03a*/
void FREE_c_f_dsch_PDU_Mini_Message_Type(c_f_dsch_PDU_Mini_Message_Type* sp);

/* Access member 'MSG_TYPE' of type 'c_r_dsch_PDU_Regular_Message_Type' as a variable reference */
#define VAR_c_r_dsch_PDU_Regular_Message_Type_MSG_TYPE(var) var

/* Access member 'MSG_TYPE' of type 'c_r_dsch_PDU_Regular_Message_Type' as a pointer */
#define PTR_c_r_dsch_PDU_Regular_Message_Type_MSG_TYPE(var) (&var)


/*-A----------------------------------*/
typedef struct _c_r_dsch_PDU_Regular_Message_Type {

	ED_OCTET MSG_TYPE; /* ODY01a *//*GBD01b*/

}	c_r_dsch_PDU_Regular_Message_Type;
#define INIT_c_r_dsch_PDU_Regular_Message_Type(sp) ED_RESET_MEM ((sp), sizeof (c_r_dsch_PDU_Regular_Message_Type))
/*FRK03a*/
void FREE_c_r_dsch_PDU_Regular_Message_Type(c_r_dsch_PDU_Regular_Message_Type* sp);

/* Access member 'ACK_SEQ' of type 'c_r_dsch_PDU_Regular_ARQ' as a variable reference */
#define VAR_c_r_dsch_PDU_Regular_ARQ_ACK_SEQ(var) var

/* Access member 'ACK_SEQ' of type 'c_r_dsch_PDU_Regular_ARQ' as a pointer */
#define PTR_c_r_dsch_PDU_Regular_ARQ_ACK_SEQ(var) (&var)

/* Access member 'MSG_SEQ' of type 'c_r_dsch_PDU_Regular_ARQ' as a variable reference */
#define VAR_c_r_dsch_PDU_Regular_ARQ_MSG_SEQ(var) var

/* Access member 'MSG_SEQ' of type 'c_r_dsch_PDU_Regular_ARQ' as a pointer */
#define PTR_c_r_dsch_PDU_Regular_ARQ_MSG_SEQ(var) (&var)

/* Access member 'ACK_REQ' of type 'c_r_dsch_PDU_Regular_ARQ' as a variable reference */
#define VAR_c_r_dsch_PDU_Regular_ARQ_ACK_REQ(var) var

/* Access member 'ACK_REQ' of type 'c_r_dsch_PDU_Regular_ARQ' as a pointer */
#define PTR_c_r_dsch_PDU_Regular_ARQ_ACK_REQ(var) (&var)


/*-A----------------------------------*/
typedef struct _c_r_dsch_PDU_Regular_ARQ {

	ED_OCTET ACK_SEQ; /* ODY01a *//*GBD01b*/
	ED_OCTET MSG_SEQ; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ACK_REQ; /* ODY01a *//*GBD01b*/

}	c_r_dsch_PDU_Regular_ARQ;
#define INIT_c_r_dsch_PDU_Regular_ARQ(sp) ED_RESET_MEM ((sp), sizeof (c_r_dsch_PDU_Regular_ARQ))
/*FRK03a*/
void FREE_c_r_dsch_PDU_Regular_ARQ(c_r_dsch_PDU_Regular_ARQ* sp);

/* Access member 'ENCRYPTION' of type 'c_r_dsch_PDU_Regular_Encryption' as a variable reference */
#define VAR_c_r_dsch_PDU_Regular_Encryption_ENCRYPTION(var) var

/* Access member 'ENCRYPTION' of type 'c_r_dsch_PDU_Regular_Encryption' as a pointer */
#define PTR_c_r_dsch_PDU_Regular_Encryption_ENCRYPTION(var) (&var)


/*-A----------------------------------*/
typedef struct _c_r_dsch_PDU_Regular_Encryption {

	ED_OCTET ENCRYPTION; /* ODY01a *//*GBD01b*/

}	c_r_dsch_PDU_Regular_Encryption;
#define INIT_c_r_dsch_PDU_Regular_Encryption(sp) ED_RESET_MEM ((sp), sizeof (c_r_dsch_PDU_Regular_Encryption))
/*FRK03a*/
void FREE_c_r_dsch_PDU_Regular_Encryption(c_r_dsch_PDU_Regular_Encryption* sp);

/* Access member 'MACI_INCL' of type 'c_r_dsch_PDU_Regular_Integrity_Fields' as a variable reference */
#define VAR_c_r_dsch_PDU_Regular_Integrity_Fields_MACI_INCL(var) var

/* Access member 'MACI_INCL' of type 'c_r_dsch_PDU_Regular_Integrity_Fields' as a pointer */
#define PTR_c_r_dsch_PDU_Regular_Integrity_Fields_MACI_INCL(var) (&var)

/* Access member 'SDU_KEY_ID' of type 'c_r_dsch_PDU_Regular_Integrity_Fields' as a variable reference */
#define VAR_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_KEY_ID(var) var

/* Access member 'SDU_KEY_ID' of type 'c_r_dsch_PDU_Regular_Integrity_Fields' as a pointer */
#define PTR_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_KEY_ID(var) (&var)

/* Access member 'SDU_INTEGRITY_ALGO' of type 'c_r_dsch_PDU_Regular_Integrity_Fields' as a variable reference */
#define VAR_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_INTEGRITY_ALGO(var) var

/* Access member 'SDU_INTEGRITY_ALGO' of type 'c_r_dsch_PDU_Regular_Integrity_Fields' as a pointer */
#define PTR_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_INTEGRITY_ALGO(var) (&var)

/* Access member 'SDU_SSEQ_OR_SSEQH' of type 'c_r_dsch_PDU_Regular_Integrity_Fields' as a variable reference */
#define VAR_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ_OR_SSEQH(var) var

/* Access member 'SDU_SSEQ_OR_SSEQH' of type 'c_r_dsch_PDU_Regular_Integrity_Fields' as a pointer */
#define PTR_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ_OR_SSEQH(var) (&var)

/* Access member 'SDU_SSEQ' of type 'c_r_dsch_PDU_Regular_Integrity_Fields' as a variable reference */
#define VAR_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ(var) var

/* Access member 'SDU_SSEQ' of type 'c_r_dsch_PDU_Regular_Integrity_Fields' as a pointer */
#define PTR_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ(var) (&var)

/* Access member 'SDU_SSEQ_H' of type 'c_r_dsch_PDU_Regular_Integrity_Fields' as a variable reference */
#define VAR_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ_H(var) var

/* Access member 'SDU_SSEQ_H' of type 'c_r_dsch_PDU_Regular_Integrity_Fields' as a pointer */
#define PTR_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ_H(var) (&var)


/*-A----------------------------------*/
typedef struct _c_r_dsch_PDU_Regular_Integrity_Fields {

	ED_BOOLEAN MACI_INCL; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN MACI_INCL_Present;
	ED_OCTET SDU_KEY_ID; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SDU_KEY_ID_Present;
	ED_OCTET SDU_INTEGRITY_ALGO; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SDU_INTEGRITY_ALGO_Present;
	ED_BOOLEAN SDU_SSEQ_OR_SSEQH; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SDU_SSEQ_OR_SSEQH_Present;
	ED_OCTET SDU_SSEQ; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SDU_SSEQ_Present;
	ED_LONG SDU_SSEQ_H; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SDU_SSEQ_H_Present;

}	c_r_dsch_PDU_Regular_Integrity_Fields;
#define INIT_c_r_dsch_PDU_Regular_Integrity_Fields(sp) ED_RESET_MEM ((sp), sizeof (c_r_dsch_PDU_Regular_Integrity_Fields))
/*FRK03a*/
void FREE_c_r_dsch_PDU_Regular_Integrity_Fields(c_r_dsch_PDU_Regular_Integrity_Fields* sp);
#define SETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_MACI_INCL(sp,present) ((sp)->MACI_INCL_Present = present)
#define GETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_MACI_INCL(sp) ((sp)->MACI_INCL_Present)
#define SETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_KEY_ID(sp,present) ((sp)->SDU_KEY_ID_Present = present)
#define GETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_KEY_ID(sp) ((sp)->SDU_KEY_ID_Present)
#define SETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_INTEGRITY_ALGO(sp,present) ((sp)->SDU_INTEGRITY_ALGO_Present = present)
#define GETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_INTEGRITY_ALGO(sp) ((sp)->SDU_INTEGRITY_ALGO_Present)
#define SETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ_OR_SSEQH(sp,present) ((sp)->SDU_SSEQ_OR_SSEQH_Present = present)
#define GETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ_OR_SSEQH(sp) ((sp)->SDU_SSEQ_OR_SSEQH_Present)
#define SETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ(sp,present) ((sp)->SDU_SSEQ_Present = present)
#define GETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ(sp) ((sp)->SDU_SSEQ_Present)
#define SETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ_H(sp,present) ((sp)->SDU_SSEQ_H_Present = present)
#define GETPRESENT_c_r_dsch_PDU_Regular_Integrity_Fields_SDU_SSEQ_H(sp) ((sp)->SDU_SSEQ_H_Present)

/* Access member 'SDU_ENCRYPT_MODE' of type 'c_r_dsch_PDU_Regular_Extended_Encryption' as a variable reference */
#define VAR_c_r_dsch_PDU_Regular_Extended_Encryption_SDU_ENCRYPT_MODE(var) var

/* Access member 'SDU_ENCRYPT_MODE' of type 'c_r_dsch_PDU_Regular_Extended_Encryption' as a pointer */
#define PTR_c_r_dsch_PDU_Regular_Extended_Encryption_SDU_ENCRYPT_MODE(var) (&var)

/* Access member 'ENC_SEQ' of type 'c_r_dsch_PDU_Regular_Extended_Encryption' as a variable reference */
#define VAR_c_r_dsch_PDU_Regular_Extended_Encryption_ENC_SEQ(var) var

/* Access member 'ENC_SEQ' of type 'c_r_dsch_PDU_Regular_Extended_Encryption' as a pointer */
#define PTR_c_r_dsch_PDU_Regular_Extended_Encryption_ENC_SEQ(var) (&var)


/*-A----------------------------------*/
typedef struct _c_r_dsch_PDU_Regular_Extended_Encryption {

	ED_OCTET SDU_ENCRYPT_MODE; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SDU_ENCRYPT_MODE_Present;
	ED_OCTET ENC_SEQ; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ENC_SEQ_Present;

}	c_r_dsch_PDU_Regular_Extended_Encryption;
#define INIT_c_r_dsch_PDU_Regular_Extended_Encryption(sp) ED_RESET_MEM ((sp), sizeof (c_r_dsch_PDU_Regular_Extended_Encryption))
/*FRK03a*/
void FREE_c_r_dsch_PDU_Regular_Extended_Encryption(c_r_dsch_PDU_Regular_Extended_Encryption* sp);
#define SETPRESENT_c_r_dsch_PDU_Regular_Extended_Encryption_SDU_ENCRYPT_MODE(sp,present) ((sp)->SDU_ENCRYPT_MODE_Present = present)
#define GETPRESENT_c_r_dsch_PDU_Regular_Extended_Encryption_SDU_ENCRYPT_MODE(sp) ((sp)->SDU_ENCRYPT_MODE_Present)
#define SETPRESENT_c_r_dsch_PDU_Regular_Extended_Encryption_ENC_SEQ(sp,present) ((sp)->ENC_SEQ_Present = present)
#define GETPRESENT_c_r_dsch_PDU_Regular_Extended_Encryption_ENC_SEQ(sp) ((sp)->ENC_SEQ_Present)

/* Access member 'ACK_SEQ' of type 'c_r_dsch_PDU_Mini_ARQ' as a variable reference */
#define VAR_c_r_dsch_PDU_Mini_ARQ_ACK_SEQ(var) var

/* Access member 'ACK_SEQ' of type 'c_r_dsch_PDU_Mini_ARQ' as a pointer */
#define PTR_c_r_dsch_PDU_Mini_ARQ_ACK_SEQ(var) (&var)

/* Access member 'MSG_SEQ' of type 'c_r_dsch_PDU_Mini_ARQ' as a variable reference */
#define VAR_c_r_dsch_PDU_Mini_ARQ_MSG_SEQ(var) var

/* Access member 'MSG_SEQ' of type 'c_r_dsch_PDU_Mini_ARQ' as a pointer */
#define PTR_c_r_dsch_PDU_Mini_ARQ_MSG_SEQ(var) (&var)

/* Access member 'ACK_REQ' of type 'c_r_dsch_PDU_Mini_ARQ' as a variable reference */
#define VAR_c_r_dsch_PDU_Mini_ARQ_ACK_REQ(var) var

/* Access member 'ACK_REQ' of type 'c_r_dsch_PDU_Mini_ARQ' as a pointer */
#define PTR_c_r_dsch_PDU_Mini_ARQ_ACK_REQ(var) (&var)


/*-A----------------------------------*/
typedef struct _c_r_dsch_PDU_Mini_ARQ {

	ED_OCTET ACK_SEQ; /* ODY01a *//*GBD01b*/
	ED_OCTET MSG_SEQ; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ACK_REQ; /* ODY01a *//*GBD01b*/

}	c_r_dsch_PDU_Mini_ARQ;
#define INIT_c_r_dsch_PDU_Mini_ARQ(sp) ED_RESET_MEM ((sp), sizeof (c_r_dsch_PDU_Mini_ARQ))
/*FRK03a*/
void FREE_c_r_dsch_PDU_Mini_ARQ(c_r_dsch_PDU_Mini_ARQ* sp);

/* Access member 'MSG_TYPE' of type 'c_r_dsch_PDU_Mini_Message_Type' as a variable reference */
#define VAR_c_r_dsch_PDU_Mini_Message_Type_MSG_TYPE(var) var

/* Access member 'MSG_TYPE' of type 'c_r_dsch_PDU_Mini_Message_Type' as a pointer */
#define PTR_c_r_dsch_PDU_Mini_Message_Type_MSG_TYPE(var) (&var)


/*-A----------------------------------*/
typedef struct _c_r_dsch_PDU_Mini_Message_Type {

	ED_OCTET MSG_TYPE; /* ODY01a *//*GBD01b*/

}	c_r_dsch_PDU_Mini_Message_Type;
#define INIT_c_r_dsch_PDU_Mini_Message_Type(sp) ED_RESET_MEM ((sp), sizeof (c_r_dsch_PDU_Mini_Message_Type))
/*FRK03a*/
void FREE_c_r_dsch_PDU_Mini_Message_Type(c_r_dsch_PDU_Mini_Message_Type* sp);

/* Access member 'PD' of type 'c_FCSCH_PDU' as a variable reference */
#define VAR_c_FCSCH_PDU_PD(var) var

/* Access member 'PD' of type 'c_FCSCH_PDU' as a pointer */
#define PTR_c_FCSCH_PDU_PD(var) (&var)

/* Access member 'MSG_ID' of type 'c_FCSCH_PDU' as a variable reference */
#define VAR_c_FCSCH_PDU_MSG_ID(var) var

/* Access member 'MSG_ID' of type 'c_FCSCH_PDU' as a pointer */
#define PTR_c_FCSCH_PDU_MSG_ID(var) (&var)

/* Access member 'data' of type 'c_FCSCH_PDU_SDUs' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs_data(var) (*var)

/* Access member 'data' of type 'c_FCSCH_PDU_SDUs' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs_data(var) var

/* Access member 'SDUs' of type 'c_FCSCH_PDU' as a variable reference */
#define VAR_c_FCSCH_PDU_SDUs(var) var

/* Access member 'SDUs' of type 'c_FCSCH_PDU' as a pointer */
#define PTR_c_FCSCH_PDU_SDUs(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_FCSCH_PDU_SDUs */
typedef struct _c_FCSCH_PDU_SDUs {

	c_FCSCH_PDU_SDUs_data **data; /* NDY01 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_FCSCH_PDU_SDUs;


/*-A----------------------------------*/
typedef struct _c_FCSCH_PDU {

	ED_OCTET PD; /* ODY01a *//*GBD01b*/
	ED_OCTET MSG_ID; /* ODY01a *//*GBD01b*/
	c_FCSCH_PDU_SDUs SDUs;/*GFB09*//*GBD01b*/

}	c_FCSCH_PDU;
#define INIT_c_FCSCH_PDU(sp) ED_RESET_MEM ((sp), sizeof (c_FCSCH_PDU))
/*FRK03a*/
void FREE_c_FCSCH_PDU(c_FCSCH_PDU* sp);

/* Access member 'PD' of type 'c_FCSCH_SYNC_BROADCAST_PDU' as a variable reference */
#define VAR_c_FCSCH_SYNC_BROADCAST_PDU_PD(var) var

/* Access member 'PD' of type 'c_FCSCH_SYNC_BROADCAST_PDU' as a pointer */
#define PTR_c_FCSCH_SYNC_BROADCAST_PDU_PD(var) (&var)

/* Access member 'MSG_ID' of type 'c_FCSCH_SYNC_BROADCAST_PDU' as a variable reference */
#define VAR_c_FCSCH_SYNC_BROADCAST_PDU_MSG_ID(var) var

/* Access member 'MSG_ID' of type 'c_FCSCH_SYNC_BROADCAST_PDU' as a pointer */
#define PTR_c_FCSCH_SYNC_BROADCAST_PDU_MSG_ID(var) (&var)

/* Access member 'SDU' of type 'c_FCSCH_SYNC_BROADCAST_PDU' as a variable reference */
#define VAR_c_FCSCH_SYNC_BROADCAST_PDU_SDU(var) var

/* Access member 'SDU' of type 'c_FCSCH_SYNC_BROADCAST_PDU' as a pointer */
#define PTR_c_FCSCH_SYNC_BROADCAST_PDU_SDU(var) (&var)

/* DEFINITION OF BINARY c_FCSCH_SYNC_BROADCAST_PDU_SDU */
typedef struct _c_FCSCH_SYNC_BROADCAST_PDU_SDU {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_FCSCH_SYNC_BROADCAST_PDU_SDU;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_FCSCH_SYNC_BROADCAST_PDU_SDU(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_FCSCH_SYNC_BROADCAST_PDU {

	ED_OCTET PD; /* ODY01a *//*GBD01b*/
	ED_OCTET MSG_ID; /* ODY01a *//*GBD01b*/
	c_FCSCH_SYNC_BROADCAST_PDU_SDU SDU; /* Static, variable size; bits needed 16 *//*GBD01b*/

}	c_FCSCH_SYNC_BROADCAST_PDU;
#define INIT_c_FCSCH_SYNC_BROADCAST_PDU(sp) ED_RESET_MEM ((sp), sizeof (c_FCSCH_SYNC_BROADCAST_PDU))
/*FRK03a*/
void FREE_c_FCSCH_SYNC_BROADCAST_PDU(c_FCSCH_SYNC_BROADCAST_PDU* sp);

/* Access member 'PD' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_PD(var) var

/* Access member 'PD' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_PD(var) (&var)

/* Access member 'MSG_ID' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_MSG_ID(var) var

/* Access member 'MSG_ID' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_MSG_ID(var) (&var)

/* Access member 'ACK_SEQ' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ACK_SEQ(var) var

/* Access member 'ACK_SEQ' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ACK_SEQ(var) (&var)

/* Access member 'MSG_SEQ' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_MSG_SEQ(var) var

/* Access member 'MSG_SEQ' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_MSG_SEQ(var) (&var)

/* Access member 'ACK_REQ' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ACK_REQ(var) var

/* Access member 'ACK_REQ' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ACK_REQ(var) (&var)

/* Access member 'VALID_ACK' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_VALID_ACK(var) var

/* Access member 'VALID_ACK' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_VALID_ACK(var) (&var)

/* Access member 'ADDR_TYPE' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ADDR_TYPE(var) var

/* Access member 'ADDR_TYPE' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ADDR_TYPE(var) (&var)

/* Access member 'ADDR_LEN' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ADDR_LEN(var) var

/* Access member 'ADDR_LEN' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ADDR_LEN(var) (&var)

/* Access member 'EXT_ADDR_TYPE' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_EXT_ADDR_TYPE(var) var

/* Access member 'EXT_ADDR_TYPE' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_EXT_ADDR_TYPE(var) (&var)

/* Access member 'IMSI_S' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S(var) (*var)

/* Access member 'IMSI_S' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S(var) var

/* Access member 'ESN' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN(var) (*var)

/* Access member 'ESN' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN(var) var

/* Access member 'IMSI' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI(var) (*var)

/* Access member 'IMSI' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI(var) var

/* Access member 'TMSI' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI(var) (*var)

/* Access member 'TMSI' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI(var) var

/* Access member 'Extended_Address' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address(var) (*var)

/* Access member 'Extended_Address' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address(var) var

/* Access member 'BROADCAST' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST(var) (*var)

/* Access member 'BROADCAST' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST(var) var

/* Access member 'MACI_INCL' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_MACI_INCL(var) var

/* Access member 'MACI_INCL' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_MACI_INCL(var) (&var)

/* Access member 'SDU_KEY_ID' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_KEY_ID(var) var

/* Access member 'SDU_KEY_ID' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_KEY_ID(var) (&var)

/* Access member 'SDU_INTEGRITY_ALGO' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_INTEGRITY_ALGO(var) var

/* Access member 'SDU_INTEGRITY_ALGO' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_INTEGRITY_ALGO(var) (&var)

/* Access member 'SDU_SSEQ_OR_SSEQH' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_SSEQ_OR_SSEQH(var) var

/* Access member 'SDU_SSEQ_OR_SSEQH' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_SSEQ_OR_SSEQH(var) (&var)

/* Access member 'SDU_SSEQ' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_SSEQ(var) var

/* Access member 'SDU_SSEQ' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_SSEQ(var) (&var)

/* Access member 'SDU_SSEQ_H' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_SSEQ_H(var) var

/* Access member 'SDU_SSEQ_H' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_SSEQ_H(var) (&var)

/* Access member 'ENC_FIELDS_INCL' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ENC_FIELDS_INCL(var) var

/* Access member 'ENC_FIELDS_INCL' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ENC_FIELDS_INCL(var) (&var)

/* Access member 'SDU_ENCRYPT_MODE' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_ENCRYPT_MODE(var) var

/* Access member 'SDU_ENCRYPT_MODE' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_ENCRYPT_MODE(var) (&var)

/* Access member 'ENC_SEQ' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ENC_SEQ(var) var

/* Access member 'ENC_SEQ' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ENC_SEQ(var) (&var)

/* Access member 'SDU' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU(var) var

/* Access member 'SDU' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU(var) (&var)

/* Access member 'MACI' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a variable reference */
#define VAR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_MACI(var) var

/* Access member 'MACI' of type 'c_FCSCH_NON_PRIMARY_BROADCAST_PDU' as a pointer */
#define PTR_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_MACI(var) (&var)

/* DEFINITION OF BINARY c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU */
typedef struct _c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_FCSCH_NON_PRIMARY_BROADCAST_PDU {

	ED_OCTET PD; /* ODY01a *//*GBD01b*/
	ED_OCTET MSG_ID; /* ODY01a *//*GBD01b*/
	ED_OCTET ACK_SEQ; /* ODY01a *//*GBD01b*/
	ED_OCTET MSG_SEQ; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ACK_REQ; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN VALID_ACK; /* ODY01a *//*GBD01b*/
	ED_OCTET ADDR_TYPE; /* ODY01a *//*GBD01b*/
	ED_OCTET ADDR_LEN; /* ODY01a *//*GBD01b*/
	ED_OCTET EXT_ADDR_TYPE; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN EXT_ADDR_TYPE_Present;
	c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S *IMSI_S; /* ODY01 *//*GBD01b*/
	ED_BOOLEAN IMSI_S_Present;
	c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN *ESN; /* ODY01 *//*GBD01b*/
	ED_BOOLEAN ESN_Present;
	c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI *IMSI; /* ODY01 *//*GBD01b*/
	ED_BOOLEAN IMSI_Present;
	c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI *TMSI; /* ODY01 *//*GBD01b*/
	ED_BOOLEAN TMSI_Present;
	c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address *Extended_Address; /* ODY01 *//*GBD01b*/
	ED_BOOLEAN Extended_Address_Present;
	c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST *BROADCAST; /* ODY01 *//*GBD01b*/
	ED_BOOLEAN BROADCAST_Present;
	ED_BOOLEAN MACI_INCL; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN MACI_INCL_Present;
	ED_OCTET SDU_KEY_ID; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SDU_KEY_ID_Present;
	ED_OCTET SDU_INTEGRITY_ALGO; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SDU_INTEGRITY_ALGO_Present;
	ED_BOOLEAN SDU_SSEQ_OR_SSEQH; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SDU_SSEQ_OR_SSEQH_Present;
	ED_OCTET SDU_SSEQ; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SDU_SSEQ_Present;
	ED_LONG SDU_SSEQ_H; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SDU_SSEQ_H_Present;
	ED_BOOLEAN ENC_FIELDS_INCL; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ENC_FIELDS_INCL_Present;
	ED_OCTET SDU_ENCRYPT_MODE; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SDU_ENCRYPT_MODE_Present;
	ED_OCTET ENC_SEQ; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ENC_SEQ_Present;
	c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU SDU; /* Static, variable size; bits needed 16 *//*GBD01b*/
	ED_LONG MACI; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN MACI_Present;

}	c_FCSCH_NON_PRIMARY_BROADCAST_PDU;
#define INIT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU(sp) ED_RESET_MEM ((sp), sizeof (c_FCSCH_NON_PRIMARY_BROADCAST_PDU))
/*FRK03a*/
void FREE_c_FCSCH_NON_PRIMARY_BROADCAST_PDU(c_FCSCH_NON_PRIMARY_BROADCAST_PDU* sp);
#define SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_EXT_ADDR_TYPE(sp,present) ((sp)->EXT_ADDR_TYPE_Present = present)
#define GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_EXT_ADDR_TYPE(sp) ((sp)->EXT_ADDR_TYPE_Present)
void SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S (c_FCSCH_NON_PRIMARY_BROADCAST_PDU* sp, ED_BOOLEAN present);
#define GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI_S(sp) ((sp)->IMSI_S_Present)
void SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN (c_FCSCH_NON_PRIMARY_BROADCAST_PDU* sp, ED_BOOLEAN present);
#define GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ESN(sp) ((sp)->ESN_Present)
void SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI (c_FCSCH_NON_PRIMARY_BROADCAST_PDU* sp, ED_BOOLEAN present);
#define GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_IMSI(sp) ((sp)->IMSI_Present)
void SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI (c_FCSCH_NON_PRIMARY_BROADCAST_PDU* sp, ED_BOOLEAN present);
#define GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_TMSI(sp) ((sp)->TMSI_Present)
void SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address (c_FCSCH_NON_PRIMARY_BROADCAST_PDU* sp, ED_BOOLEAN present);
#define GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_Extended_Address(sp) ((sp)->Extended_Address_Present)
void SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST (c_FCSCH_NON_PRIMARY_BROADCAST_PDU* sp, ED_BOOLEAN present);
#define GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_BROADCAST(sp) ((sp)->BROADCAST_Present)
#define SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_MACI_INCL(sp,present) ((sp)->MACI_INCL_Present = present)
#define GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_MACI_INCL(sp) ((sp)->MACI_INCL_Present)
#define SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_KEY_ID(sp,present) ((sp)->SDU_KEY_ID_Present = present)
#define GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_KEY_ID(sp) ((sp)->SDU_KEY_ID_Present)
#define SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_INTEGRITY_ALGO(sp,present) ((sp)->SDU_INTEGRITY_ALGO_Present = present)
#define GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_INTEGRITY_ALGO(sp) ((sp)->SDU_INTEGRITY_ALGO_Present)
#define SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_SSEQ_OR_SSEQH(sp,present) ((sp)->SDU_SSEQ_OR_SSEQH_Present = present)
#define GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_SSEQ_OR_SSEQH(sp) ((sp)->SDU_SSEQ_OR_SSEQH_Present)
#define SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_SSEQ(sp,present) ((sp)->SDU_SSEQ_Present = present)
#define GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_SSEQ(sp) ((sp)->SDU_SSEQ_Present)
#define SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_SSEQ_H(sp,present) ((sp)->SDU_SSEQ_H_Present = present)
#define GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_SSEQ_H(sp) ((sp)->SDU_SSEQ_H_Present)
#define SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ENC_FIELDS_INCL(sp,present) ((sp)->ENC_FIELDS_INCL_Present = present)
#define GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ENC_FIELDS_INCL(sp) ((sp)->ENC_FIELDS_INCL_Present)
#define SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_ENCRYPT_MODE(sp,present) ((sp)->SDU_ENCRYPT_MODE_Present = present)
#define GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_SDU_ENCRYPT_MODE(sp) ((sp)->SDU_ENCRYPT_MODE_Present)
#define SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ENC_SEQ(sp,present) ((sp)->ENC_SEQ_Present = present)
#define GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_ENC_SEQ(sp) ((sp)->ENC_SEQ_Present)
#define SETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_MACI(sp,present) ((sp)->MACI_Present = present)
#define GETPRESENT_c_FCSCH_NON_PRIMARY_BROADCAST_PDU_MACI(sp) ((sp)->MACI_Present)

/* Access member 'PD' of type 'c_GPM_PDU' as a variable reference */
#define VAR_c_GPM_PDU_PD(var) var

/* Access member 'PD' of type 'c_GPM_PDU' as a pointer */
#define PTR_c_GPM_PDU_PD(var) (&var)

/* Access member 'MSG_ID' of type 'c_GPM_PDU' as a variable reference */
#define VAR_c_GPM_PDU_MSG_ID(var) var

/* Access member 'MSG_ID' of type 'c_GPM_PDU' as a pointer */
#define PTR_c_GPM_PDU_MSG_ID(var) (&var)

/* Access member 'CONFIG_MSG_SEQ' of type 'c_GPM_PDU' as a variable reference */
#define VAR_c_GPM_PDU_CONFIG_MSG_SEQ(var) var

/* Access member 'CONFIG_MSG_SEQ' of type 'c_GPM_PDU' as a pointer */
#define PTR_c_GPM_PDU_CONFIG_MSG_SEQ(var) (&var)

/* Access member 'ACC_MSG_SEQ' of type 'c_GPM_PDU' as a variable reference */
#define VAR_c_GPM_PDU_ACC_MSG_SEQ(var) var

/* Access member 'ACC_MSG_SEQ' of type 'c_GPM_PDU' as a pointer */
#define PTR_c_GPM_PDU_ACC_MSG_SEQ(var) (&var)

/* Access member 'CLASS_0_DONE' of type 'c_GPM_PDU' as a variable reference */
#define VAR_c_GPM_PDU_CLASS_0_DONE(var) var

/* Access member 'CLASS_0_DONE' of type 'c_GPM_PDU' as a pointer */
#define PTR_c_GPM_PDU_CLASS_0_DONE(var) (&var)

/* Access member 'CLASS_1_DONE' of type 'c_GPM_PDU' as a variable reference */
#define VAR_c_GPM_PDU_CLASS_1_DONE(var) var

/* Access member 'CLASS_1_DONE' of type 'c_GPM_PDU' as a pointer */
#define PTR_c_GPM_PDU_CLASS_1_DONE(var) (&var)

/* Access member 'TMSI_DONE' of type 'c_GPM_PDU' as a variable reference */
#define VAR_c_GPM_PDU_TMSI_DONE(var) var

/* Access member 'TMSI_DONE' of type 'c_GPM_PDU' as a pointer */
#define PTR_c_GPM_PDU_TMSI_DONE(var) (&var)

/* Access member 'ORDERED_TMSIS' of type 'c_GPM_PDU' as a variable reference */
#define VAR_c_GPM_PDU_ORDERED_TMSIS(var) var

/* Access member 'ORDERED_TMSIS' of type 'c_GPM_PDU' as a pointer */
#define PTR_c_GPM_PDU_ORDERED_TMSIS(var) (&var)

/* Access member 'BROADCAST_DONE' of type 'c_GPM_PDU' as a variable reference */
#define VAR_c_GPM_PDU_BROADCAST_DONE(var) var

/* Access member 'BROADCAST_DONE' of type 'c_GPM_PDU' as a pointer */
#define PTR_c_GPM_PDU_BROADCAST_DONE(var) (&var)

/* Access member 'ADD_LENGTH' of type 'c_GPM_PDU' as a variable reference */
#define VAR_c_GPM_PDU_ADD_LENGTH(var) var

/* Access member 'ADD_LENGTH' of type 'c_GPM_PDU' as a pointer */
#define PTR_c_GPM_PDU_ADD_LENGTH(var) (&var)

/* Access member 'ADD_PFIELD' of type 'c_GPM_PDU' as a variable reference */
#define VAR_c_GPM_PDU_ADD_PFIELD(var) var

/* Access member 'ADD_PFIELD' of type 'c_GPM_PDU' as a pointer */
#define PTR_c_GPM_PDU_ADD_PFIELD(var) (&var)

/* Access member 'data' of type 'c_GPM_PDU_page_records' as a variable reference */
#define VAR_c_GPM_PDU_page_records_data(var) (*var)

/* Access member 'data' of type 'c_GPM_PDU_page_records' as a pointer */
#define PTR_c_GPM_PDU_page_records_data(var) var

/* Access member 'page_records' of type 'c_GPM_PDU' as a variable reference */
#define VAR_c_GPM_PDU_page_records(var) var

/* Access member 'page_records' of type 'c_GPM_PDU' as a pointer */
#define PTR_c_GPM_PDU_page_records(var) (&var)

/* DEFINITION OF BINARY c_GPM_PDU_ADD_PFIELD */
typedef struct _c_GPM_PDU_ADD_PFIELD {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_GPM_PDU_ADD_PFIELD;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_GPM_PDU_ADD_PFIELD(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF SUB-STRUCTURE c_GPM_PDU_page_records */
typedef struct _c_GPM_PDU_page_records {

	c_GPM_PDU_page_records_data **data; /* NDY01 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_GPM_PDU_page_records;


/*-A----------------------------------*/
typedef struct _c_GPM_PDU {

	ED_OCTET PD; /* ODY01a *//*GBD01b*/
	ED_OCTET MSG_ID; /* ODY01a *//*GBD01b*/
	ED_OCTET CONFIG_MSG_SEQ; /* ODY01a *//*GBD01b*/
	ED_OCTET ACC_MSG_SEQ; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN CLASS_0_DONE; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN CLASS_1_DONE; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN TMSI_DONE; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ORDERED_TMSIS; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN BROADCAST_DONE; /* ODY01a *//*GBD01b*/
	ED_OCTET ADD_LENGTH; /* ODY01a *//*GBD01b*/
	c_GPM_PDU_ADD_PFIELD ADD_PFIELD; /* Static, variable size; bits needed 16 *//*GBD01b*/
	c_GPM_PDU_page_records page_records;/*GFB09*//*GBD01b*/

}	c_GPM_PDU;
#define INIT_c_GPM_PDU(sp) ED_RESET_MEM ((sp), sizeof (c_GPM_PDU))
/*FRK03a*/
void FREE_c_GPM_PDU(c_GPM_PDU* sp);

/* Access member 'PD' of type 'c_UPM_PDU' as a variable reference */
#define VAR_c_UPM_PDU_PD(var) var

/* Access member 'PD' of type 'c_UPM_PDU' as a pointer */
#define PTR_c_UPM_PDU_PD(var) (&var)

/* Access member 'MSG_ID' of type 'c_UPM_PDU' as a variable reference */
#define VAR_c_UPM_PDU_MSG_ID(var) var

/* Access member 'MSG_ID' of type 'c_UPM_PDU' as a pointer */
#define PTR_c_UPM_PDU_MSG_ID(var) (&var)

/* Access member 'UPM_SEGMENT_SEQ' of type 'c_UPM_PDU' as a variable reference */
#define VAR_c_UPM_PDU_UPM_SEGMENT_SEQ(var) var

/* Access member 'UPM_SEGMENT_SEQ' of type 'c_UPM_PDU' as a pointer */
#define PTR_c_UPM_PDU_UPM_SEGMENT_SEQ(var) (&var)

/* Access member 'Universal_Page_Block' of type 'c_UPM_PDU' as a variable reference */
#define VAR_c_UPM_PDU_Universal_Page_Block(var) var

/* Access member 'Universal_Page_Block' of type 'c_UPM_PDU' as a pointer */
#define PTR_c_UPM_PDU_Universal_Page_Block(var) (&var)

/* DEFINITION OF BINARY c_UPM_PDU_Universal_Page_Block */
typedef struct _c_UPM_PDU_Universal_Page_Block {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_UPM_PDU_Universal_Page_Block;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_UPM_PDU_Universal_Page_Block(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_UPM_PDU {

	ED_OCTET PD; /* ODY01a *//*GBD01b*/
	ED_OCTET MSG_ID; /* ODY01a *//*GBD01b*/
	ED_OCTET UPM_SEGMENT_SEQ; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN UPM_SEGMENT_SEQ_Present;
	c_UPM_PDU_Universal_Page_Block Universal_Page_Block; /* Static, variable size; bits needed 16 *//*GBD01b*/

}	c_UPM_PDU;
#define INIT_c_UPM_PDU(sp) ED_RESET_MEM ((sp), sizeof (c_UPM_PDU))
/*FRK03a*/
void FREE_c_UPM_PDU(c_UPM_PDU* sp);
#define SETPRESENT_c_UPM_PDU_UPM_SEGMENT_SEQ(sp,present) ((sp)->UPM_SEGMENT_SEQ_Present = present)
#define GETPRESENT_c_UPM_PDU_UPM_SEGMENT_SEQ(sp) ((sp)->UPM_SEGMENT_SEQ_Present)

/* Access member 'CONFIG_MSG_SEQ' of type 'c_f_csch_Universal_Page_Block' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_CONFIG_MSG_SEQ(var) var

/* Access member 'CONFIG_MSG_SEQ' of type 'c_f_csch_Universal_Page_Block' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_CONFIG_MSG_SEQ(var) (&var)

/* Access member 'ACC_MSG_SEQ' of type 'c_f_csch_Universal_Page_Block' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_ACC_MSG_SEQ(var) var

/* Access member 'ACC_MSG_SEQ' of type 'c_f_csch_Universal_Page_Block' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_ACC_MSG_SEQ(var) (&var)

/* Access member 'READ_NEXT_SLOT' of type 'c_f_csch_Universal_Page_Block' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_READ_NEXT_SLOT(var) var

/* Access member 'READ_NEXT_SLOT' of type 'c_f_csch_Universal_Page_Block' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_READ_NEXT_SLOT(var) (&var)

/* Access member 'READ_NEXT_SLOT_BCAST' of type 'c_f_csch_Universal_Page_Block' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_READ_NEXT_SLOT_BCAST(var) var

/* Access member 'READ_NEXT_SLOT_BCAST' of type 'c_f_csch_Universal_Page_Block' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_READ_NEXT_SLOT_BCAST(var) (&var)

/* Access member 'BCAST_INCLUDED' of type 'c_f_csch_Universal_Page_Block' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_BCAST_INCLUDED(var) var

/* Access member 'BCAST_INCLUDED' of type 'c_f_csch_Universal_Page_Block' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_BCAST_INCLUDED(var) (&var)

/* Access member 'NUM_BCAST' of type 'c_f_csch_Universal_Page_Block' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_NUM_BCAST(var) var

/* Access member 'NUM_BCAST' of type 'c_f_csch_Universal_Page_Block' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_NUM_BCAST(var) (&var)

/* Access member 'IMSI_INCLUDED' of type 'c_f_csch_Universal_Page_Block' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_IMSI_INCLUDED(var) var

/* Access member 'IMSI_INCLUDED' of type 'c_f_csch_Universal_Page_Block' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_IMSI_INCLUDED(var) (&var)

/* Access member 'NUM_IMSI' of type 'c_f_csch_Universal_Page_Block' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_NUM_IMSI(var) var

/* Access member 'NUM_IMSI' of type 'c_f_csch_Universal_Page_Block' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_NUM_IMSI(var) (&var)

/* Access member 'TMSI_INCLUDED' of type 'c_f_csch_Universal_Page_Block' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_TMSI_INCLUDED(var) var

/* Access member 'TMSI_INCLUDED' of type 'c_f_csch_Universal_Page_Block' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_TMSI_INCLUDED(var) (&var)

/* Access member 'NUM_TMSI' of type 'c_f_csch_Universal_Page_Block' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_NUM_TMSI(var) var

/* Access member 'NUM_TMSI' of type 'c_f_csch_Universal_Page_Block' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_NUM_TMSI(var) (&var)

/* Access member 'RESERVED_TYPE_INCLUDED' of type 'c_f_csch_Universal_Page_Block' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_RESERVED_TYPE_INCLUDED(var) var

/* Access member 'RESERVED_TYPE_INCLUDED' of type 'c_f_csch_Universal_Page_Block' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_RESERVED_TYPE_INCLUDED(var) (&var)

/* Access member 'NUM_RESERVED_TYPE' of type 'c_f_csch_Universal_Page_Block' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_NUM_RESERVED_TYPE(var) var

/* Access member 'NUM_RESERVED_TYPE' of type 'c_f_csch_Universal_Page_Block' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_NUM_RESERVED_TYPE(var) (&var)

/* Access member 'data' of type 'c_f_csch_Universal_Page_Block_BURST_TYPE' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_BURST_TYPE_data(var) var

/* Access member 'data' of type 'c_f_csch_Universal_Page_Block_BURST_TYPE' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_BURST_TYPE_data(var) (&var)

/* Access member 'BURST_TYPE' of type 'c_f_csch_Universal_Page_Block' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_BURST_TYPE(var) var

/* Access member 'BURST_TYPE' of type 'c_f_csch_Universal_Page_Block' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_BURST_TYPE(var) (&var)

/* Access member 'data' of type 'c_f_csch_Universal_Page_Block_SUBRECORD' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_SUBRECORD_data(var) (*var)

/* Access member 'data' of type 'c_f_csch_Universal_Page_Block_SUBRECORD' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_SUBRECORD_data(var) var

/* Access member 'SUBRECORD' of type 'c_f_csch_Universal_Page_Block' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_SUBRECORD(var) var

/* Access member 'SUBRECORD' of type 'c_f_csch_Universal_Page_Block' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_SUBRECORD(var) (&var)

/* Access member 'data' of type 'c_f_csch_Universal_Page_Block_page_records' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_page_records_data(var) (*var)

/* Access member 'data' of type 'c_f_csch_Universal_Page_Block_page_records' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_page_records_data(var) var

/* Access member 'page_records' of type 'c_f_csch_Universal_Page_Block' as a variable reference */
#define VAR_c_f_csch_Universal_Page_Block_page_records(var) var

/* Access member 'page_records' of type 'c_f_csch_Universal_Page_Block' as a pointer */
#define PTR_c_f_csch_Universal_Page_Block_page_records(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_f_csch_Universal_Page_Block_BURST_TYPE */
typedef struct _c_f_csch_Universal_Page_Block_BURST_TYPE {

	ED_OCTET* data; /* NDY01a *//*GBD01b*//*GAD01a*//*AR02 ('TDMSequence'-2459=EDCore::TDMSequence)  */
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_f_csch_Universal_Page_Block_BURST_TYPE;

/* DEFINITION OF SUB-STRUCTURE c_f_csch_Universal_Page_Block_SUBRECORD */
typedef struct _c_f_csch_Universal_Page_Block_SUBRECORD {

	c_f_csch_Universal_Page_Block_SUBRECORD_data **data; /* NDY01 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_f_csch_Universal_Page_Block_SUBRECORD;

/* DEFINITION OF SUB-STRUCTURE c_f_csch_Universal_Page_Block_page_records */
typedef struct _c_f_csch_Universal_Page_Block_page_records {

	c_f_csch_Universal_Page_Block_page_records_data **data; /* NDY01 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_f_csch_Universal_Page_Block_page_records;


/*-A----------------------------------*/
typedef struct _c_f_csch_Universal_Page_Block {

	ED_OCTET CONFIG_MSG_SEQ; /* ODY01a *//*GBD01b*/
	ED_OCTET ACC_MSG_SEQ; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN READ_NEXT_SLOT; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN READ_NEXT_SLOT_BCAST; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN BCAST_INCLUDED; /* ODY01a *//*GBD01b*/
	ED_OCTET NUM_BCAST; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN NUM_BCAST_Present;
	ED_BOOLEAN IMSI_INCLUDED; /* ODY01a *//*GBD01b*/
	ED_OCTET NUM_IMSI; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN NUM_IMSI_Present;
	ED_BOOLEAN TMSI_INCLUDED; /* ODY01a *//*GBD01b*/
	ED_OCTET NUM_TMSI; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN NUM_TMSI_Present;
	ED_BOOLEAN RESERVED_TYPE_INCLUDED; /* ODY01a *//*GBD01b*/
	ED_OCTET NUM_RESERVED_TYPE; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN NUM_RESERVED_TYPE_Present;
	c_f_csch_Universal_Page_Block_BURST_TYPE BURST_TYPE;/*GFB09*//*GBD01b*/
	c_f_csch_Universal_Page_Block_SUBRECORD SUBRECORD;/*GFB09*//*GBD01b*/
	c_f_csch_Universal_Page_Block_page_records page_records;/*GFB09*//*GBD01b*/

}	c_f_csch_Universal_Page_Block;
#define INIT_c_f_csch_Universal_Page_Block(sp) ED_RESET_MEM ((sp), sizeof (c_f_csch_Universal_Page_Block))
/*FRK03a*/
void FREE_c_f_csch_Universal_Page_Block(c_f_csch_Universal_Page_Block* sp);
#define SETPRESENT_c_f_csch_Universal_Page_Block_NUM_BCAST(sp,present) ((sp)->NUM_BCAST_Present = present)
#define GETPRESENT_c_f_csch_Universal_Page_Block_NUM_BCAST(sp) ((sp)->NUM_BCAST_Present)
#define SETPRESENT_c_f_csch_Universal_Page_Block_NUM_IMSI(sp,present) ((sp)->NUM_IMSI_Present = present)
#define GETPRESENT_c_f_csch_Universal_Page_Block_NUM_IMSI(sp) ((sp)->NUM_IMSI_Present)
#define SETPRESENT_c_f_csch_Universal_Page_Block_NUM_TMSI(sp,present) ((sp)->NUM_TMSI_Present = present)
#define GETPRESENT_c_f_csch_Universal_Page_Block_NUM_TMSI(sp) ((sp)->NUM_TMSI_Present)
#define SETPRESENT_c_f_csch_Universal_Page_Block_NUM_RESERVED_TYPE(sp,present) ((sp)->NUM_RESERVED_TYPE_Present = present)
#define GETPRESENT_c_f_csch_Universal_Page_Block_NUM_RESERVED_TYPE(sp) ((sp)->NUM_RESERVED_TYPE_Present)

/* Access member 'Message_Type' of type 'c_r_csch_PDU' as a variable reference */
#define VAR_c_r_csch_PDU_Message_Type(var) var

/* Access member 'Message_Type' of type 'c_r_csch_PDU' as a pointer */
#define PTR_c_r_csch_PDU_Message_Type(var) (&var)

/* Access member 'LAC_Length' of type 'c_r_csch_PDU' as a variable reference */
#define VAR_c_r_csch_PDU_LAC_Length(var) (*var)

/* Access member 'LAC_Length' of type 'c_r_csch_PDU' as a pointer */
#define PTR_c_r_csch_PDU_LAC_Length(var) var

/* Access member 'ARQ' of type 'c_r_csch_PDU' as a variable reference */
#define VAR_c_r_csch_PDU_ARQ(var) var

/* Access member 'ARQ' of type 'c_r_csch_PDU' as a pointer */
#define PTR_c_r_csch_PDU_ARQ(var) (&var)

/* Access member 'Addressing' of type 'c_r_csch_PDU' as a variable reference */
#define VAR_c_r_csch_PDU_Addressing(var) var

/* Access member 'Addressing' of type 'c_r_csch_PDU' as a pointer */
#define PTR_c_r_csch_PDU_Addressing(var) (&var)

/* Access member 'Authentication' of type 'c_r_csch_PDU' as a variable reference */
#define VAR_c_r_csch_PDU_Authentication(var) var

/* Access member 'Authentication' of type 'c_r_csch_PDU' as a pointer */
#define PTR_c_r_csch_PDU_Authentication(var) (&var)

/* Access member 'Extended_Encryption' of type 'c_r_csch_PDU' as a variable reference */
#define VAR_c_r_csch_PDU_Extended_Encryption(var) (*var)

/* Access member 'Extended_Encryption' of type 'c_r_csch_PDU' as a pointer */
#define PTR_c_r_csch_PDU_Extended_Encryption(var) var

/* Access member 'Radio_Environment_Report' of type 'c_r_csch_PDU' as a variable reference */
#define VAR_c_r_csch_PDU_Radio_Environment_Report(var) (*var)

/* Access member 'Radio_Environment_Report' of type 'c_r_csch_PDU' as a pointer */
#define PTR_c_r_csch_PDU_Radio_Environment_Report(var) var

/* Access member 'SDU' of type 'c_r_csch_PDU' as a variable reference */
#define VAR_c_r_csch_PDU_SDU(var) var

/* Access member 'SDU' of type 'c_r_csch_PDU' as a pointer */
#define PTR_c_r_csch_PDU_SDU(var) (&var)

/* Access member 'MACI' of type 'c_r_csch_PDU' as a variable reference */
#define VAR_c_r_csch_PDU_MACI(var) var

/* Access member 'MACI' of type 'c_r_csch_PDU' as a pointer */
#define PTR_c_r_csch_PDU_MACI(var) (&var)

/* DEFINITION OF BINARY c_r_csch_PDU_SDU */
typedef struct _c_r_csch_PDU_SDU {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_r_csch_PDU_SDU;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_r_csch_PDU_SDU(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_r_csch_PDU {

	c_r_csch_PDU_Message_Type Message_Type; /* ODY01a *//*GBD01b*/
	c_r_csch_PDU_LAC_Length *LAC_Length; /* ODY01 *//*GBD01b*/
	ED_BOOLEAN LAC_Length_Present;
	c_r_csch_PDU_ARQ ARQ; /* ODY01a *//*GBD01b*/
	c_r_csch_PDU_Addressing Addressing; /* ODY01a *//*GBD01b*/
	c_r_csch_PDU_Authentication Authentication; /* ODY01a *//*GBD01b*/
	c_r_csch_PDU_Extended_Encryption *Extended_Encryption; /* ODY01 *//*GBD01b*/
	ED_BOOLEAN Extended_Encryption_Present;
	c_r_csch_Radio_Environment_Report *Radio_Environment_Report; /* ODY01 *//*GBD01b*/
	ED_BOOLEAN Radio_Environment_Report_Present;
	c_r_csch_PDU_SDU SDU; /* Static, variable size; bits needed 16 *//*GBD01b*/
	ED_LONG MACI; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN MACI_Present;

}	c_r_csch_PDU;
#define INIT_c_r_csch_PDU(sp) ED_RESET_MEM ((sp), sizeof (c_r_csch_PDU))
/*FRK03a*/
void FREE_c_r_csch_PDU(c_r_csch_PDU* sp);
void SETPRESENT_c_r_csch_PDU_LAC_Length (c_r_csch_PDU* sp, ED_BOOLEAN present);
#define GETPRESENT_c_r_csch_PDU_LAC_Length(sp) ((sp)->LAC_Length_Present)
void SETPRESENT_c_r_csch_PDU_Extended_Encryption (c_r_csch_PDU* sp, ED_BOOLEAN present);
#define GETPRESENT_c_r_csch_PDU_Extended_Encryption(sp) ((sp)->Extended_Encryption_Present)
void SETPRESENT_c_r_csch_PDU_Radio_Environment_Report (c_r_csch_PDU* sp, ED_BOOLEAN present);
#define GETPRESENT_c_r_csch_PDU_Radio_Environment_Report(sp) ((sp)->Radio_Environment_Report_Present)
#define SETPRESENT_c_r_csch_PDU_MACI(sp,present) ((sp)->MACI_Present = present)
#define GETPRESENT_c_r_csch_PDU_MACI(sp) ((sp)->MACI_Present)

/* Access member 'Message_Type' of type 'c_f_dsch_PDU_Regular' as a variable reference */
#define VAR_c_f_dsch_PDU_Regular_Message_Type(var) var

/* Access member 'Message_Type' of type 'c_f_dsch_PDU_Regular' as a pointer */
#define PTR_c_f_dsch_PDU_Regular_Message_Type(var) (&var)

/* Access member 'ARQ' of type 'c_f_dsch_PDU_Regular' as a variable reference */
#define VAR_c_f_dsch_PDU_Regular_ARQ(var) var

/* Access member 'ARQ' of type 'c_f_dsch_PDU_Regular' as a pointer */
#define PTR_c_f_dsch_PDU_Regular_ARQ(var) (&var)

/* Access member 'Encryption' of type 'c_f_dsch_PDU_Regular' as a variable reference */
#define VAR_c_f_dsch_PDU_Regular_Encryption(var) var

/* Access member 'Encryption' of type 'c_f_dsch_PDU_Regular' as a pointer */
#define PTR_c_f_dsch_PDU_Regular_Encryption(var) (&var)

/* Access member 'Integrity_Fields' of type 'c_f_dsch_PDU_Regular' as a variable reference */
#define VAR_c_f_dsch_PDU_Regular_Integrity_Fields(var) var

/* Access member 'Integrity_Fields' of type 'c_f_dsch_PDU_Regular' as a pointer */
#define PTR_c_f_dsch_PDU_Regular_Integrity_Fields(var) (&var)

/* Access member 'Extended_Encryption' of type 'c_f_dsch_PDU_Regular' as a variable reference */
#define VAR_c_f_dsch_PDU_Regular_Extended_Encryption(var) var

/* Access member 'Extended_Encryption' of type 'c_f_dsch_PDU_Regular' as a pointer */
#define PTR_c_f_dsch_PDU_Regular_Extended_Encryption(var) (&var)

/* Access member 'SDU' of type 'c_f_dsch_PDU_Regular' as a variable reference */
#define VAR_c_f_dsch_PDU_Regular_SDU(var) var

/* Access member 'SDU' of type 'c_f_dsch_PDU_Regular' as a pointer */
#define PTR_c_f_dsch_PDU_Regular_SDU(var) (&var)

/* Access member 'MACI' of type 'c_f_dsch_PDU_Regular' as a variable reference */
#define VAR_c_f_dsch_PDU_Regular_MACI(var) var

/* Access member 'MACI' of type 'c_f_dsch_PDU_Regular' as a pointer */
#define PTR_c_f_dsch_PDU_Regular_MACI(var) (&var)

/* DEFINITION OF BINARY c_f_dsch_PDU_Regular_SDU */
typedef struct _c_f_dsch_PDU_Regular_SDU {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_f_dsch_PDU_Regular_SDU;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_f_dsch_PDU_Regular_SDU(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_f_dsch_PDU_Regular {

	c_f_dsch_PDU_Regular_Message_Type Message_Type; /* ODY01a *//*GBD01b*/
	c_f_dsch_PDU_Regular_ARQ ARQ; /* ODY01a *//*GBD01b*/
	c_f_dsch_PDU_Regular_Encryption Encryption; /* ODY01a *//*GBD01b*/
	c_f_dsch_PDU_Regular_Integrity_Fields Integrity_Fields; /* ODY01a *//*GBD01b*/
	c_f_dsch_PDU_Regular_Extended_Encryption Extended_Encryption; /* ODY01a *//*GBD01b*/
	c_f_dsch_PDU_Regular_SDU SDU; /* Static, variable size; bits needed 16 *//*GBD01b*/
	ED_LONG MACI; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN MACI_Present;

}	c_f_dsch_PDU_Regular;
#define INIT_c_f_dsch_PDU_Regular(sp) ED_RESET_MEM ((sp), sizeof (c_f_dsch_PDU_Regular))
/*FRK03a*/
void FREE_c_f_dsch_PDU_Regular(c_f_dsch_PDU_Regular* sp);
#define SETPRESENT_c_f_dsch_PDU_Regular_MACI(sp,present) ((sp)->MACI_Present = present)
#define GETPRESENT_c_f_dsch_PDU_Regular_MACI(sp) ((sp)->MACI_Present)

/* Access member 'ARQ' of type 'c_f_dsch_PDU_Mini' as a variable reference */
#define VAR_c_f_dsch_PDU_Mini_ARQ(var) var

/* Access member 'ARQ' of type 'c_f_dsch_PDU_Mini' as a pointer */
#define PTR_c_f_dsch_PDU_Mini_ARQ(var) (&var)

/* Access member 'Message_Type' of type 'c_f_dsch_PDU_Mini' as a variable reference */
#define VAR_c_f_dsch_PDU_Mini_Message_Type(var) var

/* Access member 'Message_Type' of type 'c_f_dsch_PDU_Mini' as a pointer */
#define PTR_c_f_dsch_PDU_Mini_Message_Type(var) (&var)

/* Access member 'SDU' of type 'c_f_dsch_PDU_Mini' as a variable reference */
#define VAR_c_f_dsch_PDU_Mini_SDU(var) var

/* Access member 'SDU' of type 'c_f_dsch_PDU_Mini' as a pointer */
#define PTR_c_f_dsch_PDU_Mini_SDU(var) (&var)

/* DEFINITION OF BINARY c_f_dsch_PDU_Mini_SDU */
typedef struct _c_f_dsch_PDU_Mini_SDU {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_f_dsch_PDU_Mini_SDU;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_f_dsch_PDU_Mini_SDU(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_f_dsch_PDU_Mini {

	c_f_dsch_PDU_Mini_ARQ ARQ; /* ODY01a *//*GBD01b*/
	c_f_dsch_PDU_Mini_Message_Type Message_Type; /* ODY01a *//*GBD01b*/
	c_f_dsch_PDU_Mini_SDU SDU; /* Static, variable size; bits needed 16 *//*GBD01b*/

}	c_f_dsch_PDU_Mini;
#define INIT_c_f_dsch_PDU_Mini(sp) ED_RESET_MEM ((sp), sizeof (c_f_dsch_PDU_Mini))
/*FRK03a*/
void FREE_c_f_dsch_PDU_Mini(c_f_dsch_PDU_Mini* sp);

/* Access member 'Message_Type' of type 'c_r_dsch_PDU_Regular' as a variable reference */
#define VAR_c_r_dsch_PDU_Regular_Message_Type(var) var

/* Access member 'Message_Type' of type 'c_r_dsch_PDU_Regular' as a pointer */
#define PTR_c_r_dsch_PDU_Regular_Message_Type(var) (&var)

/* Access member 'ARQ' of type 'c_r_dsch_PDU_Regular' as a variable reference */
#define VAR_c_r_dsch_PDU_Regular_ARQ(var) var

/* Access member 'ARQ' of type 'c_r_dsch_PDU_Regular' as a pointer */
#define PTR_c_r_dsch_PDU_Regular_ARQ(var) (&var)

/* Access member 'Encryption' of type 'c_r_dsch_PDU_Regular' as a variable reference */
#define VAR_c_r_dsch_PDU_Regular_Encryption(var) var

/* Access member 'Encryption' of type 'c_r_dsch_PDU_Regular' as a pointer */
#define PTR_c_r_dsch_PDU_Regular_Encryption(var) (&var)

/* Access member 'Integrity_Fields' of type 'c_r_dsch_PDU_Regular' as a variable reference */
#define VAR_c_r_dsch_PDU_Regular_Integrity_Fields(var) var

/* Access member 'Integrity_Fields' of type 'c_r_dsch_PDU_Regular' as a pointer */
#define PTR_c_r_dsch_PDU_Regular_Integrity_Fields(var) (&var)

/* Access member 'Extended_Encryption' of type 'c_r_dsch_PDU_Regular' as a variable reference */
#define VAR_c_r_dsch_PDU_Regular_Extended_Encryption(var) var

/* Access member 'Extended_Encryption' of type 'c_r_dsch_PDU_Regular' as a pointer */
#define PTR_c_r_dsch_PDU_Regular_Extended_Encryption(var) (&var)

/* Access member 'SDU' of type 'c_r_dsch_PDU_Regular' as a variable reference */
#define VAR_c_r_dsch_PDU_Regular_SDU(var) var

/* Access member 'SDU' of type 'c_r_dsch_PDU_Regular' as a pointer */
#define PTR_c_r_dsch_PDU_Regular_SDU(var) (&var)

/* Access member 'MACI' of type 'c_r_dsch_PDU_Regular' as a variable reference */
#define VAR_c_r_dsch_PDU_Regular_MACI(var) var

/* Access member 'MACI' of type 'c_r_dsch_PDU_Regular' as a pointer */
#define PTR_c_r_dsch_PDU_Regular_MACI(var) (&var)

/* DEFINITION OF BINARY c_r_dsch_PDU_Regular_SDU */
typedef struct _c_r_dsch_PDU_Regular_SDU {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_r_dsch_PDU_Regular_SDU;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_r_dsch_PDU_Regular_SDU(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_r_dsch_PDU_Regular {

	c_r_dsch_PDU_Regular_Message_Type Message_Type; /* ODY01a *//*GBD01b*/
	c_r_dsch_PDU_Regular_ARQ ARQ; /* ODY01a *//*GBD01b*/
	c_r_dsch_PDU_Regular_Encryption Encryption; /* ODY01a *//*GBD01b*/
	c_r_dsch_PDU_Regular_Integrity_Fields Integrity_Fields; /* ODY01a *//*GBD01b*/
	c_r_dsch_PDU_Regular_Extended_Encryption Extended_Encryption; /* ODY01a *//*GBD01b*/
	c_r_dsch_PDU_Regular_SDU SDU; /* Static, variable size; bits needed 16 *//*GBD01b*/
	ED_LONG MACI; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN MACI_Present;

}	c_r_dsch_PDU_Regular;
#define INIT_c_r_dsch_PDU_Regular(sp) ED_RESET_MEM ((sp), sizeof (c_r_dsch_PDU_Regular))
/*FRK03a*/
void FREE_c_r_dsch_PDU_Regular(c_r_dsch_PDU_Regular* sp);
#define SETPRESENT_c_r_dsch_PDU_Regular_MACI(sp,present) ((sp)->MACI_Present = present)
#define GETPRESENT_c_r_dsch_PDU_Regular_MACI(sp) ((sp)->MACI_Present)

/* Access member 'ARQ' of type 'c_r_dsch_PDU_Mini' as a variable reference */
#define VAR_c_r_dsch_PDU_Mini_ARQ(var) var

/* Access member 'ARQ' of type 'c_r_dsch_PDU_Mini' as a pointer */
#define PTR_c_r_dsch_PDU_Mini_ARQ(var) (&var)

/* Access member 'Message_Type' of type 'c_r_dsch_PDU_Mini' as a variable reference */
#define VAR_c_r_dsch_PDU_Mini_Message_Type(var) var

/* Access member 'Message_Type' of type 'c_r_dsch_PDU_Mini' as a pointer */
#define PTR_c_r_dsch_PDU_Mini_Message_Type(var) (&var)

/* Access member 'SDU' of type 'c_r_dsch_PDU_Mini' as a variable reference */
#define VAR_c_r_dsch_PDU_Mini_SDU(var) var

/* Access member 'SDU' of type 'c_r_dsch_PDU_Mini' as a pointer */
#define PTR_c_r_dsch_PDU_Mini_SDU(var) (&var)

/* DEFINITION OF BINARY c_r_dsch_PDU_Mini_SDU */
typedef struct _c_r_dsch_PDU_Mini_SDU {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_r_dsch_PDU_Mini_SDU;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_r_dsch_PDU_Mini_SDU(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_r_dsch_PDU_Mini {

	c_r_dsch_PDU_Mini_ARQ ARQ; /* ODY01a *//*GBD01b*/
	c_r_dsch_PDU_Mini_Message_Type Message_Type; /* ODY01a *//*GBD01b*/
	c_r_dsch_PDU_Mini_SDU SDU; /* Static, variable size; bits needed 16 *//*GBD01b*/

}	c_r_dsch_PDU_Mini;
#define INIT_c_r_dsch_PDU_Mini(sp) ED_RESET_MEM ((sp), sizeof (c_r_dsch_PDU_Mini))
/*FRK03a*/
void FREE_c_r_dsch_PDU_Mini(c_r_dsch_PDU_Mini* sp);

/* Access member 'SERVICE_OPTION' of type 'c_f_csch_UPM_Mobile_Station_Addressed' as a variable reference */
#define VAR_c_f_csch_UPM_Mobile_Station_Addressed_SERVICE_OPTION(var) var

/* Access member 'SERVICE_OPTION' of type 'c_f_csch_UPM_Mobile_Station_Addressed' as a pointer */
#define PTR_c_f_csch_UPM_Mobile_Station_Addressed_SERVICE_OPTION(var) (&var)

/* Access member 'ADD_MS_RECORD' of type 'c_f_csch_UPM_Mobile_Station_Addressed' as a variable reference */
#define VAR_c_f_csch_UPM_Mobile_Station_Addressed_ADD_MS_RECORD(var) var

/* Access member 'ADD_MS_RECORD' of type 'c_f_csch_UPM_Mobile_Station_Addressed' as a pointer */
#define PTR_c_f_csch_UPM_Mobile_Station_Addressed_ADD_MS_RECORD(var) (&var)

/* DEFINITION OF BINARY c_f_csch_UPM_Mobile_Station_Addressed_ADD_MS_RECORD */
typedef struct _c_f_csch_UPM_Mobile_Station_Addressed_ADD_MS_RECORD {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_f_csch_UPM_Mobile_Station_Addressed_ADD_MS_RECORD;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_f_csch_UPM_Mobile_Station_Addressed_ADD_MS_RECORD(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_f_csch_UPM_Mobile_Station_Addressed {

	ED_LONG SERVICE_OPTION; /* ODY01a *//*GBD01b*/
	c_f_csch_UPM_Mobile_Station_Addressed_ADD_MS_RECORD ADD_MS_RECORD; /* Static, variable size; bits needed 16 *//*GBD01b*/

}	c_f_csch_UPM_Mobile_Station_Addressed;
#define INIT_c_f_csch_UPM_Mobile_Station_Addressed(sp) ED_RESET_MEM ((sp), sizeof (c_f_csch_UPM_Mobile_Station_Addressed))
/*FRK03a*/
void FREE_c_f_csch_UPM_Mobile_Station_Addressed(c_f_csch_UPM_Mobile_Station_Addressed* sp);

/* Access member 'BCN' of type 'c_f_csch_UPM_Enhanced_Broadcast_with_time_offset' as a variable reference */
#define VAR_c_f_csch_UPM_Enhanced_Broadcast_with_time_offset_BCN(var) var

/* Access member 'BCN' of type 'c_f_csch_UPM_Enhanced_Broadcast_with_time_offset' as a pointer */
#define PTR_c_f_csch_UPM_Enhanced_Broadcast_with_time_offset_BCN(var) (&var)

/* Access member 'TIME_OFFSET' of type 'c_f_csch_UPM_Enhanced_Broadcast_with_time_offset' as a variable reference */
#define VAR_c_f_csch_UPM_Enhanced_Broadcast_with_time_offset_TIME_OFFSET(var) var

/* Access member 'TIME_OFFSET' of type 'c_f_csch_UPM_Enhanced_Broadcast_with_time_offset' as a pointer */
#define PTR_c_f_csch_UPM_Enhanced_Broadcast_with_time_offset_TIME_OFFSET(var) (&var)

/* Access member 'REPEAT_TIME_OFFSET' of type 'c_f_csch_UPM_Enhanced_Broadcast_with_time_offset' as a variable reference */
#define VAR_c_f_csch_UPM_Enhanced_Broadcast_with_time_offset_REPEAT_TIME_OFFSET(var) var

/* Access member 'REPEAT_TIME_OFFSET' of type 'c_f_csch_UPM_Enhanced_Broadcast_with_time_offset' as a pointer */
#define PTR_c_f_csch_UPM_Enhanced_Broadcast_with_time_offset_REPEAT_TIME_OFFSET(var) (&var)

/* Access member 'ADD_BCAST_RECORD' of type 'c_f_csch_UPM_Enhanced_Broadcast_with_time_offset' as a variable reference */
#define VAR_c_f_csch_UPM_Enhanced_Broadcast_with_time_offset_ADD_BCAST_RECORD(var) var

/* Access member 'ADD_BCAST_RECORD' of type 'c_f_csch_UPM_Enhanced_Broadcast_with_time_offset' as a pointer */
#define PTR_c_f_csch_UPM_Enhanced_Broadcast_with_time_offset_ADD_BCAST_RECORD(var) (&var)

/* DEFINITION OF BINARY c_f_csch_UPM_Enhanced_Broadcast_with_time_offset_ADD_BCAST_RECORD */
typedef struct _c_f_csch_UPM_Enhanced_Broadcast_with_time_offset_ADD_BCAST_RECORD {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_f_csch_UPM_Enhanced_Broadcast_with_time_offset_ADD_BCAST_RECORD;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_f_csch_UPM_Enhanced_Broadcast_with_time_offset_ADD_BCAST_RECORD(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_f_csch_UPM_Enhanced_Broadcast_with_time_offset {

	ED_OCTET BCN; /* ODY01a *//*GBD01b*/
	ED_LONG TIME_OFFSET; /* ODY01a *//*GBD01b*/
	ED_OCTET REPEAT_TIME_OFFSET; /* ODY01a *//*GBD01b*/
	c_f_csch_UPM_Enhanced_Broadcast_with_time_offset_ADD_BCAST_RECORD ADD_BCAST_RECORD; /* Static, variable size; bits needed 16 *//*GBD01b*/

}	c_f_csch_UPM_Enhanced_Broadcast_with_time_offset;
#define INIT_c_f_csch_UPM_Enhanced_Broadcast_with_time_offset(sp) ED_RESET_MEM ((sp), sizeof (c_f_csch_UPM_Enhanced_Broadcast_with_time_offset))
/*FRK03a*/
void FREE_c_f_csch_UPM_Enhanced_Broadcast_with_time_offset(c_f_csch_UPM_Enhanced_Broadcast_with_time_offset* sp);

/* Access member 'BCN' of type 'c_f_csch_UPM_Enhanced_Broadcast_without_time_offset' as a variable reference */
#define VAR_c_f_csch_UPM_Enhanced_Broadcast_without_time_offset_BCN(var) var

/* Access member 'BCN' of type 'c_f_csch_UPM_Enhanced_Broadcast_without_time_offset' as a pointer */
#define PTR_c_f_csch_UPM_Enhanced_Broadcast_without_time_offset_BCN(var) (&var)

/* Access member 'TIME_OFFSET' of type 'c_f_csch_UPM_Enhanced_Broadcast_without_time_offset' as a variable reference */
#define VAR_c_f_csch_UPM_Enhanced_Broadcast_without_time_offset_TIME_OFFSET(var) var

/* Access member 'TIME_OFFSET' of type 'c_f_csch_UPM_Enhanced_Broadcast_without_time_offset' as a pointer */
#define PTR_c_f_csch_UPM_Enhanced_Broadcast_without_time_offset_TIME_OFFSET(var) (&var)

/* Access member 'ADD_BCAST_RECORD' of type 'c_f_csch_UPM_Enhanced_Broadcast_without_time_offset' as a variable reference */
#define VAR_c_f_csch_UPM_Enhanced_Broadcast_without_time_offset_ADD_BCAST_RECORD(var) var

/* Access member 'ADD_BCAST_RECORD' of type 'c_f_csch_UPM_Enhanced_Broadcast_without_time_offset' as a pointer */
#define PTR_c_f_csch_UPM_Enhanced_Broadcast_without_time_offset_ADD_BCAST_RECORD(var) (&var)

/* DEFINITION OF BINARY c_f_csch_UPM_Enhanced_Broadcast_without_time_offset_ADD_BCAST_RECORD */
typedef struct _c_f_csch_UPM_Enhanced_Broadcast_without_time_offset_ADD_BCAST_RECORD {
	ED_BYTE* value; /* Variable size; bits needed 16 */
	int usedBits;
} c_f_csch_UPM_Enhanced_Broadcast_without_time_offset_ADD_BCAST_RECORD;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_f_csch_UPM_Enhanced_Broadcast_without_time_offset_ADD_BCAST_RECORD(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_f_csch_UPM_Enhanced_Broadcast_without_time_offset {

	ED_OCTET BCN; /* ODY01a *//*GBD01b*/
	ED_LONG TIME_OFFSET; /* ODY01a *//*GBD01b*/
	c_f_csch_UPM_Enhanced_Broadcast_without_time_offset_ADD_BCAST_RECORD ADD_BCAST_RECORD; /* Static, variable size; bits needed 16 *//*GBD01b*/

}	c_f_csch_UPM_Enhanced_Broadcast_without_time_offset;
#define INIT_c_f_csch_UPM_Enhanced_Broadcast_without_time_offset(sp) ED_RESET_MEM ((sp), sizeof (c_f_csch_UPM_Enhanced_Broadcast_without_time_offset))
/*FRK03a*/
void FREE_c_f_csch_UPM_Enhanced_Broadcast_without_time_offset(c_f_csch_UPM_Enhanced_Broadcast_without_time_offset* sp);

/* Access member 'TLV_Tag' of type 'c_GenericTLV_cs0004' as a variable reference */
#define VAR_c_GenericTLV_cs0004_TLV_Tag(var) var

/* Access member 'TLV_Tag' of type 'c_GenericTLV_cs0004' as a pointer */
#define PTR_c_GenericTLV_cs0004_TLV_Tag(var) (&var)

/* Access member 'TLV_Data' of type 'c_GenericTLV_cs0004' as a variable reference */
#define VAR_c_GenericTLV_cs0004_TLV_Data(var) var

/* Access member 'TLV_Data' of type 'c_GenericTLV_cs0004' as a pointer */
#define PTR_c_GenericTLV_cs0004_TLV_Data(var) (&var)

/* DEFINITION OF BINARY c_GenericTLV_cs0004_TLV_Data */
typedef struct _c_GenericTLV_cs0004_TLV_Data {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_GenericTLV_cs0004_TLV_Data;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_GenericTLV_cs0004_TLV_Data(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_GenericTLV_cs0004 {

	ED_LONG TLV_Tag; /* ODY01a *//*GBD01b*/
	c_GenericTLV_cs0004_TLV_Data TLV_Data; /* Static, variable size; bits needed 64 *//*GBD01b*/

}	c_GenericTLV_cs0004;
#define INIT_c_GenericTLV_cs0004(sp) ED_RESET_MEM ((sp), sizeof (c_GenericTLV_cs0004))
/*FRK03a*/
void FREE_c_GenericTLV_cs0004(c_GenericTLV_cs0004* sp);

/* SETITEMS/ADDITEMS commands for type 'c_r_csch_Radio_Environment_Report_ADD_PILOTS'. */
int SETITEMS_c_r_csch_Radio_Environment_Report_ADD_PILOTS (c_r_csch_Radio_Environment_Report_ADD_PILOTS* sequence, int desiredItems);
#define ADDITEMS_c_r_csch_Radio_Environment_Report_ADD_PILOTS(sequence, itemsToBeAdded) SETITEMS_c_r_csch_Radio_Environment_Report_ADD_PILOTS (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_FCSCH_PDU_SDUs'. */
int SETITEMS_c_FCSCH_PDU_SDUs (c_FCSCH_PDU_SDUs* sequence, int desiredItems);
#define ADDITEMS_c_FCSCH_PDU_SDUs(sequence, itemsToBeAdded) SETITEMS_c_FCSCH_PDU_SDUs (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_GPM_PDU_page_records'. */
int SETITEMS_c_GPM_PDU_page_records (c_GPM_PDU_page_records* sequence, int desiredItems);
#define ADDITEMS_c_GPM_PDU_page_records(sequence, itemsToBeAdded) SETITEMS_c_GPM_PDU_page_records (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_f_csch_Universal_Page_Block_BURST_TYPE'. */
int SETITEMS_c_f_csch_Universal_Page_Block_BURST_TYPE (c_f_csch_Universal_Page_Block_BURST_TYPE* sequence, int desiredItems);
#define ADDITEMS_c_f_csch_Universal_Page_Block_BURST_TYPE(sequence, itemsToBeAdded) SETITEMS_c_f_csch_Universal_Page_Block_BURST_TYPE (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_f_csch_Universal_Page_Block_SUBRECORD'. */
int SETITEMS_c_f_csch_Universal_Page_Block_SUBRECORD (c_f_csch_Universal_Page_Block_SUBRECORD* sequence, int desiredItems);
#define ADDITEMS_c_f_csch_Universal_Page_Block_SUBRECORD(sequence, itemsToBeAdded) SETITEMS_c_f_csch_Universal_Page_Block_SUBRECORD (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_f_csch_Universal_Page_Block_page_records'. */
int SETITEMS_c_f_csch_Universal_Page_Block_page_records (c_f_csch_Universal_Page_Block_page_records* sequence, int desiredItems);
#define ADDITEMS_c_f_csch_Universal_Page_Block_page_records(sequence, itemsToBeAdded) SETITEMS_c_f_csch_Universal_Page_Block_page_records (sequence, (sequence)->items+itemsToBeAdded)

#ifdef __cplusplus
}
#endif

#endif

