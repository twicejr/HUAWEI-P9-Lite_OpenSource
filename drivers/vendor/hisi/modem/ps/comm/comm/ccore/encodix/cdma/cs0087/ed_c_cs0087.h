/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __ed_c_cs0087_h_H
#define __ed_c_cs0087_h_H
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


/* Access member 'AttributeId' of type 'c_RPD_Inter_RAT_Overhead_Messages_CS0024B' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Overhead_Messages_CS0024B_AttributeId(var) var

/* Access member 'AttributeId' of type 'c_RPD_Inter_RAT_Overhead_Messages_CS0024B' as a pointer */
#define PTR_c_RPD_Inter_RAT_Overhead_Messages_CS0024B_AttributeId(var) (&var)

/* Access member 'NN' of type 'c_RPD_Inter_RAT_Overhead_Messages_CS0024B' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Overhead_Messages_CS0024B_NN(var) var

/* Access member 'NN' of type 'c_RPD_Inter_RAT_Overhead_Messages_CS0024B' as a pointer */
#define PTR_c_RPD_Inter_RAT_Overhead_Messages_CS0024B_NN(var) (&var)

/* Access member 'Value' of type 'c_RPD_Inter_RAT_Overhead_Messages_CS0024B' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Overhead_Messages_CS0024B_Value(var) var

/* Access member 'Value' of type 'c_RPD_Inter_RAT_Overhead_Messages_CS0024B' as a pointer */
#define PTR_c_RPD_Inter_RAT_Overhead_Messages_CS0024B_Value(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPD_Inter_RAT_Overhead_Messages_CS0024B {

	ED_LONG AttributeId; /* ODY01a *//*GBD01b*/
	ED_LONG NN; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN NN_Present;
	ED_LONG Value; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Value_Present;

}	c_RPD_Inter_RAT_Overhead_Messages_CS0024B;
#define INIT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Inter_RAT_Overhead_Messages_CS0024B))
/*FRK03a*/
void FREE_c_RPD_Inter_RAT_Overhead_Messages_CS0024B(c_RPD_Inter_RAT_Overhead_Messages_CS0024B* sp);
#define SETPRESENT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B_NN(sp,present) ((sp)->NN_Present = present)
#define GETPRESENT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B_NN(sp) ((sp)->NN_Present)
#define SETPRESENT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B_Value(sp,present) ((sp)->Value_Present = present)
#define GETPRESENT_c_RPD_Inter_RAT_Overhead_Messages_CS0024B_Value(sp) ((sp)->Value_Present)

/* Access member 'MessageSequence' of type 'c_RPDSES_SL_UATIAssignment_contents' as a variable reference */
#define VAR_c_RPDSES_SL_UATIAssignment_contents_MessageSequence(var) var

/* Access member 'MessageSequence' of type 'c_RPDSES_SL_UATIAssignment_contents' as a pointer */
#define PTR_c_RPDSES_SL_UATIAssignment_contents_MessageSequence(var) (&var)

/* Access member 'Reserved1' of type 'c_RPDSES_SL_UATIAssignment_contents' as a variable reference */
#define VAR_c_RPDSES_SL_UATIAssignment_contents_Reserved1(var) var

/* Access member 'Reserved1' of type 'c_RPDSES_SL_UATIAssignment_contents' as a pointer */
#define PTR_c_RPDSES_SL_UATIAssignment_contents_Reserved1(var) (&var)

/* Access member 'SubnetIncluded' of type 'c_RPDSES_SL_UATIAssignment_contents' as a variable reference */
#define VAR_c_RPDSES_SL_UATIAssignment_contents_SubnetIncluded(var) var

/* Access member 'SubnetIncluded' of type 'c_RPDSES_SL_UATIAssignment_contents' as a pointer */
#define PTR_c_RPDSES_SL_UATIAssignment_contents_SubnetIncluded(var) (&var)

/* Access member 'UATISubnetMask' of type 'c_RPDSES_SL_UATIAssignment_contents' as a variable reference */
#define VAR_c_RPDSES_SL_UATIAssignment_contents_UATISubnetMask(var) var

/* Access member 'UATISubnetMask' of type 'c_RPDSES_SL_UATIAssignment_contents' as a pointer */
#define PTR_c_RPDSES_SL_UATIAssignment_contents_UATISubnetMask(var) (&var)

/* Access member 'UATI104' of type 'c_RPDSES_SL_UATIAssignment_contents' as a variable reference */
#define VAR_c_RPDSES_SL_UATIAssignment_contents_UATI104(var) (*var)

/* Access member 'UATI104' of type 'c_RPDSES_SL_UATIAssignment_contents' as a pointer */
#define PTR_c_RPDSES_SL_UATIAssignment_contents_UATI104(var) var

/* Access member 'UATIColorCode' of type 'c_RPDSES_SL_UATIAssignment_contents' as a variable reference */
#define VAR_c_RPDSES_SL_UATIAssignment_contents_UATIColorCode(var) var

/* Access member 'UATIColorCode' of type 'c_RPDSES_SL_UATIAssignment_contents' as a pointer */
#define PTR_c_RPDSES_SL_UATIAssignment_contents_UATIColorCode(var) (&var)

/* Access member 'UATI024' of type 'c_RPDSES_SL_UATIAssignment_contents' as a variable reference */
#define VAR_c_RPDSES_SL_UATIAssignment_contents_UATI024(var) var

/* Access member 'UATI024' of type 'c_RPDSES_SL_UATIAssignment_contents' as a pointer */
#define PTR_c_RPDSES_SL_UATIAssignment_contents_UATI024(var) (&var)

/* Access member 'UpperOldUATILength' of type 'c_RPDSES_SL_UATIAssignment_contents' as a variable reference */
#define VAR_c_RPDSES_SL_UATIAssignment_contents_UpperOldUATILength(var) var

/* Access member 'UpperOldUATILength' of type 'c_RPDSES_SL_UATIAssignment_contents' as a pointer */
#define PTR_c_RPDSES_SL_UATIAssignment_contents_UpperOldUATILength(var) (&var)

/* Access member 'Reserved2' of type 'c_RPDSES_SL_UATIAssignment_contents' as a variable reference */
#define VAR_c_RPDSES_SL_UATIAssignment_contents_Reserved2(var) var

/* Access member 'Reserved2' of type 'c_RPDSES_SL_UATIAssignment_contents' as a pointer */
#define PTR_c_RPDSES_SL_UATIAssignment_contents_Reserved2(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDSES_SL_UATIAssignment_contents {

	ED_OCTET MessageSequence; /* ODY01a *//*GBD01b*/
	ED_OCTET Reserved1; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SubnetIncluded; /* ODY01a *//*GBD01b*/
	ED_OCTET UATISubnetMask; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN UATISubnetMask_Present;
	ED_BYTE* UATI104; /* Dynamic, fixed size; bits needed: 104 ODY02a *//*GBD01b*/
	ED_BOOLEAN UATI104_Present;
	ED_OCTET UATIColorCode; /* ODY01a *//*GBD01b*/
	ED_LONG UATI024; /* ODY01a *//*GBD01b*/
	ED_OCTET UpperOldUATILength; /* ODY01a *//*GBD01b*/
	ED_OCTET Reserved2; /* ODY01a *//*GBD01b*/

}	c_RPDSES_SL_UATIAssignment_contents;
#define INIT_c_RPDSES_SL_UATIAssignment_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDSES_SL_UATIAssignment_contents))
/*FRK03a*/
void FREE_c_RPDSES_SL_UATIAssignment_contents(c_RPDSES_SL_UATIAssignment_contents* sp);
#define SETPRESENT_c_RPDSES_SL_UATIAssignment_contents_UATISubnetMask(sp,present) ((sp)->UATISubnetMask_Present = present)
#define GETPRESENT_c_RPDSES_SL_UATIAssignment_contents_UATISubnetMask(sp) ((sp)->UATISubnetMask_Present)
void SETPRESENT_c_RPDSES_SL_UATIAssignment_contents_UATI104 (c_RPDSES_SL_UATIAssignment_contents* sp, ED_BOOLEAN present);
#define GETPRESENT_c_RPDSES_SL_UATIAssignment_contents_UATI104(sp) ((sp)->UATI104_Present)

/* Access member 'TransactionID' of type 'c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_TransactionID(var) (&var)

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01_data_AttributeLength(var) var

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01_data_AttributeLength(var) (&var)

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01_data_AttributeRecord(var) var

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01_data_AttributeRecord(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01_data */
typedef struct _c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01_data {

	ED_OCTET AttributeLength; /* ODY01a *//*GBD01b*/
	c_RPD_Inter_RAT_Overhead_Messages_CS0024B AttributeRecord; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01 */
typedef struct _c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01 {

	c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents;
#define INIT_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents(c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents' as a variable reference */
#define VAR_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents' as a pointer */
#define PTR_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_TransactionID(var) (&var)

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01_data_AttributeLength(var) var

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01_data_AttributeLength(var) (&var)

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01_data_AttributeRecord(var) var

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01_data_AttributeRecord(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents' as a variable reference */
#define VAR_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents' as a pointer */
#define PTR_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01_data */
typedef struct _c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01_data {

	ED_OCTET AttributeLength; /* ODY01a *//*GBD01b*/
	c_RPD_Inter_RAT_Overhead_Messages_CS0024B AttributeRecord; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01 */
typedef struct _c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01 {

	c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents;
#define INIT_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents(c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq_contents' as a variable reference */
#define VAR_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq_contents' as a pointer */
#define PTR_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq_contents_TransactionID(var) (&var)

/* Access member 'RequestReason' of type 'c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq_contents' as a variable reference */
#define VAR_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq_contents_RequestReason(var) var

/* Access member 'RequestReason' of type 'c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq_contents' as a pointer */
#define PTR_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq_contents_RequestReason(var) (&var)

/* Access member 'Reserved' of type 'c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq_contents' as a variable reference */
#define VAR_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq_contents_Reserved(var) var

/* Access member 'Reserved' of type 'c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq_contents' as a pointer */
#define PTR_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq_contents_Reserved(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	ED_OCTET RequestReason; /* ODY01a *//*GBD01b*/
	ED_OCTET Reserved; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq_contents;
#define INIT_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq_contents(c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf_contents' as a variable reference */
#define VAR_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf_contents' as a pointer */
#define PTR_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf_contents;
#define INIT_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf_contents(c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail_contents' as a variable reference */
#define VAR_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail_contents' as a pointer */
#define PTR_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail_contents;
#define INIT_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail_contents(c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq_contents' as a variable reference */
#define VAR_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq_contents' as a pointer */
#define PTR_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq_contents;
#define INIT_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq_contents(c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf_contents' as a variable reference */
#define VAR_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf_contents' as a pointer */
#define PTR_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf_contents;
#define INIT_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf_contents(c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete_contents' as a variable reference */
#define VAR_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete_contents' as a pointer */
#define PTR_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete_contents;
#define INIT_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete_contents(c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_TransactionID(var) (&var)

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01_data_AttributeLength(var) var

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01_data_AttributeLength(var) (&var)

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01_data_AttributeRecord(var) var

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01_data_AttributeRecord(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01_data */
typedef struct _c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01_data {

	ED_OCTET AttributeLength; /* ODY01a *//*GBD01b*/
	c_RPD_Inter_RAT_Overhead_Messages_CS0024B AttributeRecord; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01 */
typedef struct _c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01 {

	c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents;
#define INIT_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents(c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents' as a variable reference */
#define VAR_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents' as a pointer */
#define PTR_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_TransactionID(var) (&var)

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01_data_AttributeLength(var) var

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01_data_AttributeLength(var) (&var)

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01_data_AttributeRecord(var) var

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01_data_AttributeRecord(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents' as a variable reference */
#define VAR_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents' as a pointer */
#define PTR_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01_data */
typedef struct _c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01_data {

	ED_OCTET AttributeLength; /* ODY01a *//*GBD01b*/
	c_RPD_Inter_RAT_Overhead_Messages_CS0024B AttributeRecord; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01 */
typedef struct _c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01 {

	c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents;
#define INIT_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents(c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents* sp);

/* Access member 'MaximumRevision' of type 'c_RPDCON_IRATINSP_INUSE_Sync_contents' as a variable reference */
#define VAR_c_RPDCON_IRATINSP_INUSE_Sync_contents_MaximumRevision(var) var

/* Access member 'MaximumRevision' of type 'c_RPDCON_IRATINSP_INUSE_Sync_contents' as a pointer */
#define PTR_c_RPDCON_IRATINSP_INUSE_Sync_contents_MaximumRevision(var) (&var)

/* Access member 'MinimumRevision' of type 'c_RPDCON_IRATINSP_INUSE_Sync_contents' as a variable reference */
#define VAR_c_RPDCON_IRATINSP_INUSE_Sync_contents_MinimumRevision(var) var

/* Access member 'MinimumRevision' of type 'c_RPDCON_IRATINSP_INUSE_Sync_contents' as a pointer */
#define PTR_c_RPDCON_IRATINSP_INUSE_Sync_contents_MinimumRevision(var) (&var)

/* Access member 'PilotPN' of type 'c_RPDCON_IRATINSP_INUSE_Sync_contents' as a variable reference */
#define VAR_c_RPDCON_IRATINSP_INUSE_Sync_contents_PilotPN(var) var

/* Access member 'PilotPN' of type 'c_RPDCON_IRATINSP_INUSE_Sync_contents' as a pointer */
#define PTR_c_RPDCON_IRATINSP_INUSE_Sync_contents_PilotPN(var) (&var)

/* Access member 'SystemTime' of type 'c_RPDCON_IRATINSP_INUSE_Sync_contents' as a variable reference */
#define VAR_c_RPDCON_IRATINSP_INUSE_Sync_contents_SystemTime(var) var

/* Access member 'SystemTime' of type 'c_RPDCON_IRATINSP_INUSE_Sync_contents' as a pointer */
#define PTR_c_RPDCON_IRATINSP_INUSE_Sync_contents_SystemTime(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATINSP_INUSE_Sync_contents {

	ED_OCTET MaximumRevision; /* ODY01a *//*GBD01b*/
	ED_OCTET MinimumRevision; /* ODY01a *//*GBD01b*/
	ED_SHORT PilotPN; /* ODY01a *//*GBD01b*/
	ED_BYTE SystemTime [5]; /* Static, fixed size; bits needed 37 *//*GBD01b*/

}	c_RPDCON_IRATINSP_INUSE_Sync_contents;
#define INIT_c_RPDCON_IRATINSP_INUSE_Sync_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATINSP_INUSE_Sync_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATINSP_INUSE_Sync_contents(c_RPDCON_IRATINSP_INUSE_Sync_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_TransactionID(var) (&var)

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01_data_AttributeLength(var) var

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01_data_AttributeLength(var) (&var)

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01_data_AttributeRecord(var) var

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01_data_AttributeRecord(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01_data */
typedef struct _c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01_data {

	ED_OCTET AttributeLength; /* ODY01a *//*GBD01b*/
	c_RPD_Inter_RAT_Overhead_Messages_CS0024B AttributeRecord; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01 */
typedef struct _c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01 {

	c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents;
#define INIT_c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents(c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents' as a pointer */
#define PTR_c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_TransactionID(var) (&var)

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01_data_AttributeLength(var) var

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01_data_AttributeLength(var) (&var)

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01_data_AttributeRecord(var) var

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01_data_AttributeRecord(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents' as a pointer */
#define PTR_c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01_data */
typedef struct _c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01_data {

	ED_OCTET AttributeLength; /* ODY01a *//*GBD01b*/
	c_RPD_Inter_RAT_Overhead_Messages_CS0024B AttributeRecord; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01 */
typedef struct _c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01 {

	c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents;
#define INIT_c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents(c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_TransactionID(var) (&var)

/* Access member 'RequestReason' of type 'c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_RequestReason(var) var

/* Access member 'RequestReason' of type 'c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_RequestReason(var) (&var)

/* Access member 'PreferredChannelCount' of type 'c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_PreferredChannelCount(var) var

/* Access member 'PreferredChannelCount' of type 'c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_PreferredChannelCount(var) (&var)

/* Access member 'SystemType' of type 'c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel_SystemType(var) var

/* Access member 'SystemType' of type 'c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel' as a pointer */
#define PTR_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel_SystemType(var) (&var)

/* Access member 'BandClass' of type 'c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel_BandClass(var) var

/* Access member 'BandClass' of type 'c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel' as a pointer */
#define PTR_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel_BandClass(var) (&var)

/* Access member 'ChannelNumber' of type 'c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel_ChannelNumber(var) var

/* Access member 'ChannelNumber' of type 'c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel' as a pointer */
#define PTR_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel_ChannelNumber(var) (&var)

/* Access member 'PreferredChannel' of type 'c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel(var) var

/* Access member 'PreferredChannel' of type 'c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01(var) (&var)

/* Access member 'EmergencyIndication' of type 'c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_EmergencyIndication(var) var

/* Access member 'EmergencyIndication' of type 'c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_EmergencyIndication(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel */
typedef struct _c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel {

	ED_OCTET SystemType; /* ODY01a *//*GBD01b*/
	ED_OCTET BandClass; /* ODY01a *//*GBD01b*/
	ED_SHORT ChannelNumber; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data */
typedef struct _c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data {

	c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel PreferredChannel;/*GBD01b*/

} c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01 */
typedef struct _c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01 {

	c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	ED_OCTET RequestReason; /* ODY01a *//*GBD01b*/
	ED_OCTET PreferredChannelCount; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01 data01;/*GFB09*//*GBD01b*/
	ED_BOOLEAN EmergencyIndication; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN EmergencyIndication_Present;

}	c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents;
#define INIT_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents(c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents* sp);
#define SETPRESENT_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_EmergencyIndication(sp,present) ((sp)->EmergencyIndication_Present = present)
#define GETPRESENT_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_EmergencyIndication(sp) ((sp)->EmergencyIndication_Present)

/* Access member 'TransactionID' of type 'c_RPDCON_IRATISP_INUSE_ConnectionDeny_contents' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INUSE_ConnectionDeny_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATISP_INUSE_ConnectionDeny_contents' as a pointer */
#define PTR_c_RPDCON_IRATISP_INUSE_ConnectionDeny_contents_TransactionID(var) (&var)

/* Access member 'DenyReason' of type 'c_RPDCON_IRATISP_INUSE_ConnectionDeny_contents' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INUSE_ConnectionDeny_contents_DenyReason(var) var

/* Access member 'DenyReason' of type 'c_RPDCON_IRATISP_INUSE_ConnectionDeny_contents' as a pointer */
#define PTR_c_RPDCON_IRATISP_INUSE_ConnectionDeny_contents_DenyReason(var) (&var)

/* Access member 'Reserved' of type 'c_RPDCON_IRATISP_INUSE_ConnectionDeny_contents' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INUSE_ConnectionDeny_contents_Reserved(var) var

/* Access member 'Reserved' of type 'c_RPDCON_IRATISP_INUSE_ConnectionDeny_contents' as a pointer */
#define PTR_c_RPDCON_IRATISP_INUSE_ConnectionDeny_contents_Reserved(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATISP_INUSE_ConnectionDeny_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	ED_OCTET DenyReason; /* ODY01a *//*GBD01b*/
	ED_OCTET Reserved; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATISP_INUSE_ConnectionDeny_contents;
#define INIT_c_RPDCON_IRATISP_INUSE_ConnectionDeny_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATISP_INUSE_ConnectionDeny_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATISP_INUSE_ConnectionDeny_contents(c_RPDCON_IRATISP_INUSE_ConnectionDeny_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_TransactionID(var) (&var)

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01_data_AttributeLength(var) var

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01_data_AttributeLength(var) (&var)

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01_data_AttributeRecord(var) var

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01_data_AttributeRecord(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01_data */
typedef struct _c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01_data {

	ED_OCTET AttributeLength; /* ODY01a *//*GBD01b*/
	c_RPD_Inter_RAT_Overhead_Messages_CS0024B AttributeRecord; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01 */
typedef struct _c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01 {

	c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents;
#define INIT_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents(c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept_contents' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept_contents' as a pointer */
#define PTR_c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept_contents;
#define INIT_c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept_contents(c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_IRATISP_INUSE_AttributeUpdateReject_contents' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INUSE_AttributeUpdateReject_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATISP_INUSE_AttributeUpdateReject_contents' as a pointer */
#define PTR_c_RPDCON_IRATISP_INUSE_AttributeUpdateReject_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATISP_INUSE_AttributeUpdateReject_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATISP_INUSE_AttributeUpdateReject_contents;
#define INIT_c_RPDCON_IRATISP_INUSE_AttributeUpdateReject_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATISP_INUSE_AttributeUpdateReject_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATISP_INUSE_AttributeUpdateReject_contents(c_RPDCON_IRATISP_INUSE_AttributeUpdateReject_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_TransactionID(var) (&var)

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01_data_AttributeLength(var) var

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01_data_AttributeLength(var) (&var)

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01_data_AttributeRecord(var) var

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01_data_AttributeRecord(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01_data */
typedef struct _c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01_data {

	ED_OCTET AttributeLength; /* ODY01a *//*GBD01b*/
	c_RPD_Inter_RAT_Overhead_Messages_CS0024B AttributeRecord; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01 */
typedef struct _c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01 {

	c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents;
#define INIT_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents(c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_TransactionID(var) (&var)

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01_data_AttributeLength(var) var

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01_data_AttributeLength(var) (&var)

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01_data_AttributeRecord(var) var

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01_data_AttributeRecord(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01_data */
typedef struct _c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01_data {

	ED_OCTET AttributeLength; /* ODY01a *//*GBD01b*/
	c_RPD_Inter_RAT_Overhead_Messages_CS0024B AttributeRecord; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01 */
typedef struct _c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01 {

	c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents;
#define INIT_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents(c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents* sp);

/* Access member 'MessageSequence' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_MessageSequence(var) var

/* Access member 'MessageSequence' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_MessageSequence(var) (&var)

/* Access member 'ReferencePilotPN' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotPN(var) var

/* Access member 'ReferencePilotPN' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotPN(var) (&var)

/* Access member 'ReferencePilotStrength' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotStrength(var) var

/* Access member 'ReferencePilotStrength' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotStrength(var) (&var)

/* Access member 'ReferenceKeep' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferenceKeep(var) var

/* Access member 'ReferenceKeep' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferenceKeep(var) (&var)

/* Access member 'NumPilots' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_NumPilots(var) var

/* Access member 'NumPilots' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_NumPilots(var) (&var)

/* Access member 'PilotPNPhase' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_PilotPNPhase(var) var

/* Access member 'PilotPNPhase' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_PilotPNPhase(var) (&var)

/* Access member 'ChannelIncluded' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_ChannelIncluded(var) var

/* Access member 'ChannelIncluded' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_ChannelIncluded(var) (&var)

/* Access member 'SystemType' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel_SystemType(var) var

/* Access member 'SystemType' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel_SystemType(var) (&var)

/* Access member 'BandClass' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel_BandClass(var) var

/* Access member 'BandClass' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel_BandClass(var) (&var)

/* Access member 'ChannelNumber' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel_ChannelNumber(var) var

/* Access member 'ChannelNumber' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel_ChannelNumber(var) (&var)

/* Access member 'Channel' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel(var) (*var)

/* Access member 'Channel' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel(var) var

/* Access member 'PilotStrength' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_PilotStrength(var) var

/* Access member 'PilotStrength' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_PilotStrength(var) (&var)

/* Access member 'Keep' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_Keep(var) var

/* Access member 'Keep' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_Keep(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01(var) (&var)

/* Access member 'CompatibleReserved' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_CompatibleReserved(var) var

/* Access member 'CompatibleReserved' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_CompatibleReserved(var) (&var)

/* Access member 'ReferencePilotChannelIncluded' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannelIncluded(var) var

/* Access member 'ReferencePilotChannelIncluded' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannelIncluded(var) (&var)

/* Access member 'SystemType' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel_SystemType(var) var

/* Access member 'SystemType' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel_SystemType(var) (&var)

/* Access member 'BandClass' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel_BandClass(var) var

/* Access member 'BandClass' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel_BandClass(var) (&var)

/* Access member 'ChannelNumber' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel_ChannelNumber(var) var

/* Access member 'ChannelNumber' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel_ChannelNumber(var) (&var)

/* Access member 'ReferencePilotChannel' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel(var) (*var)

/* Access member 'ReferencePilotChannel' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel(var) var

/* Access member 'ReferencePilotArrivalIncluded' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotArrivalIncluded(var) var

/* Access member 'ReferencePilotArrivalIncluded' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotArrivalIncluded(var) (&var)

/* Access member 'ReferencePilotArrival' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotArrival(var) var

/* Access member 'ReferencePilotArrival' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotArrival(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel */
typedef struct _c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel {

	ED_OCTET SystemType; /* ODY01a *//*GBD01b*/
	ED_OCTET BandClass; /* ODY01a *//*GBD01b*/
	ED_SHORT ChannelNumber; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data */
typedef struct _c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data {

	ED_SHORT PilotPNPhase; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ChannelIncluded; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel *Channel; /* ODY03 <> *//*GBD01b*/
	ED_BOOLEAN Channel_Present;
	ED_OCTET PilotStrength; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Keep; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01 */
typedef struct _c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01 {

	c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel */
typedef struct _c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel {

	ED_OCTET SystemType; /* ODY01a *//*GBD01b*/
	ED_OCTET BandClass; /* ODY01a *//*GBD01b*/
	ED_SHORT ChannelNumber; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents {

	ED_OCTET MessageSequence; /* ODY01a *//*GBD01b*/
	ED_SHORT ReferencePilotPN; /* ODY01a *//*GBD01b*/
	ED_OCTET ReferencePilotStrength; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ReferenceKeep; /* ODY01a *//*GBD01b*/
	ED_OCTET NumPilots; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01 data01;/*GFB09*//*GBD01b*/
	ED_BOOLEAN CompatibleReserved; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ReferencePilotChannelIncluded; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel *ReferencePilotChannel; /* ODY03 <> *//*GBD01b*/
	ED_BOOLEAN ReferencePilotChannel_Present;
	ED_BOOLEAN ReferencePilotArrivalIncluded; /* ODY01a *//*GBD01b*/
	ED_SHORT ReferencePilotArrival; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ReferencePilotArrival_Present;

}	c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents;
#define INIT_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents(c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents* sp);
void SETPRESENT_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel (c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents* sp, ED_BOOLEAN present);
#define GETPRESENT_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel(sp) ((sp)->ReferencePilotChannel_Present)
#define SETPRESENT_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotArrival(sp,present) ((sp)->ReferencePilotArrival_Present = present)
#define GETPRESENT_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotArrival(sp) ((sp)->ReferencePilotArrival_Present)

/* Access member 'MessageSequence' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_MessageSequence(var) var

/* Access member 'MessageSequence' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_MessageSequence(var) (&var)

/* Access member 'ChannelIncluded' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_ChannelIncluded(var) var

/* Access member 'ChannelIncluded' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_ChannelIncluded(var) (&var)

/* Access member 'SystemType' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_Channel' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_Channel_SystemType(var) var

/* Access member 'SystemType' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_Channel' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_Channel_SystemType(var) (&var)

/* Access member 'BandClass' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_Channel' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_Channel_BandClass(var) var

/* Access member 'BandClass' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_Channel' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_Channel_BandClass(var) (&var)

/* Access member 'ChannelNumber' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_Channel' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_Channel_ChannelNumber(var) var

/* Access member 'ChannelNumber' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_Channel' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_Channel_ChannelNumber(var) (&var)

/* Access member 'Channel' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_Channel(var) (*var)

/* Access member 'Channel' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_Channel(var) var

/* Access member 'FrameOffset' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_FrameOffset(var) var

/* Access member 'FrameOffset' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_FrameOffset(var) (&var)

/* Access member 'DRCLength' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_DRCLength(var) var

/* Access member 'DRCLength' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_DRCLength(var) (&var)

/* Access member 'DRCChannelGainBase' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_DRCChannelGainBase(var) var

/* Access member 'DRCChannelGainBase' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_DRCChannelGainBase(var) (&var)

/* Access member 'ACKChannelGain' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_ACKChannelGain(var) var

/* Access member 'ACKChannelGain' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_ACKChannelGain(var) (&var)

/* Access member 'NumPilots' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_NumPilots(var) var

/* Access member 'NumPilots' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_NumPilots(var) (&var)

/* Access member 'PilotPN' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data_PilotPN(var) var

/* Access member 'PilotPN' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data_PilotPN(var) (&var)

/* Access member 'SofterHandoff' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data_SofterHandoff(var) var

/* Access member 'SofterHandoff' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data_SofterHandoff(var) (&var)

/* Access member 'MACIndexLSBs' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data_MACIndexLSBs(var) var

/* Access member 'MACIndexLSBs' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data_MACIndexLSBs(var) (&var)

/* Access member 'DRCCover' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data_DRCCover(var) var

/* Access member 'DRCCover' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data_DRCCover(var) (&var)

/* Access member 'RABLength' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data_RABLength(var) var

/* Access member 'RABLength' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data_RABLength(var) (&var)

/* Access member 'RABOffset' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data_RABOffset(var) var

/* Access member 'RABOffset' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data_RABOffset(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01(var) (&var)

/* Access member 'RAChannelGainIncluded' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_RAChannelGainIncluded(var) var

/* Access member 'RAChannelGainIncluded' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_RAChannelGainIncluded(var) (&var)

/* Access member 'RAChannelGain' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data_RAChannelGain(var) var

/* Access member 'RAChannelGain' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data_RAChannelGain(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data(var) var

/* Access member 'data02' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02(var) var

/* Access member 'data02' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02(var) (&var)

/* Access member 'MACIndexMSBsIncluded' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_MACIndexMSBsIncluded(var) var

/* Access member 'MACIndexMSBsIncluded' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_MACIndexMSBsIncluded(var) (&var)

/* Access member 'MACIndexMSB' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_MACIndexMSB(var) var

/* Access member 'MACIndexMSB' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_MACIndexMSB(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data(var) var

/* Access member 'data03' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03(var) var

/* Access member 'data03' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03(var) (&var)

/* Access member 'DSCChannelGainBase' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_DSCChannelGainBase(var) var

/* Access member 'DSCChannelGainBase' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_DSCChannelGainBase(var) (&var)

/* Access member 'DSC' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04_data' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04_data_DSC(var) var

/* Access member 'DSC' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04_data' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04_data_DSC(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04_data(var) var

/* Access member 'data04' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04(var) var

/* Access member 'data04' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_Channel */
typedef struct _c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_Channel {

	ED_OCTET SystemType; /* ODY01a *//*GBD01b*/
	ED_OCTET BandClass; /* ODY01a *//*GBD01b*/
	ED_SHORT ChannelNumber; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_Channel;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data */
typedef struct _c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data {

	ED_SHORT PilotPN; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SofterHandoff; /* ODY01a *//*GBD01b*/
	ED_OCTET MACIndexLSBs; /* ODY01a *//*GBD01b*/
	ED_OCTET DRCCover; /* ODY01a *//*GBD01b*/
	ED_OCTET RABLength; /* ODY01a *//*GBD01b*/
	ED_OCTET RABOffset; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01 */
typedef struct _c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01 {

	c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data */
typedef struct _c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data {

	ED_OCTET RAChannelGain; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02 */
typedef struct _c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02 {

	c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data */
typedef struct _c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data {

	ED_BOOLEAN MACIndexMSB; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03 */
typedef struct _c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03 {

	c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04_data */
typedef struct _c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04_data {

	ED_OCTET DSC; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04 */
typedef struct _c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04 {

	c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents {

	ED_OCTET MessageSequence; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ChannelIncluded; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_Channel *Channel; /* ODY03 <> *//*GBD01b*/
	ED_BOOLEAN Channel_Present;
	ED_OCTET FrameOffset; /* ODY01a *//*GBD01b*/
	ED_OCTET DRCLength; /* ODY01a *//*GBD01b*/
	ED_OCTET DRCChannelGainBase; /* ODY01a *//*GBD01b*/
	ED_OCTET ACKChannelGain; /* ODY01a *//*GBD01b*/
	ED_OCTET NumPilots; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01 data01;/*GFB09*//*GBD01b*/
	ED_BOOLEAN RAChannelGainIncluded; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN RAChannelGainIncluded_Present;
	c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02 data02;/*GFB09*//*GBD01b*/
	ED_BOOLEAN MACIndexMSBsIncluded; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN MACIndexMSBsIncluded_Present;
	c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03 data03;/*GFB09*//*GBD01b*/
	ED_OCTET DSCChannelGainBase; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN DSCChannelGainBase_Present;
	c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04 data04;/*GFB09*//*GBD01b*/

}	c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents;
#define INIT_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents(c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents* sp);
void SETPRESENT_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_Channel (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents* sp, ED_BOOLEAN present);
#define GETPRESENT_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_Channel(sp) ((sp)->Channel_Present)
#define SETPRESENT_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_RAChannelGainIncluded(sp,present) ((sp)->RAChannelGainIncluded_Present = present)
#define GETPRESENT_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_RAChannelGainIncluded(sp) ((sp)->RAChannelGainIncluded_Present)
#define SETPRESENT_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_MACIndexMSBsIncluded(sp,present) ((sp)->MACIndexMSBsIncluded_Present = present)
#define GETPRESENT_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_MACIndexMSBsIncluded(sp) ((sp)->MACIndexMSBsIncluded_Present)
#define SETPRESENT_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_DSCChannelGainBase(sp,present) ((sp)->DSCChannelGainBase_Present = present)
#define GETPRESENT_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_DSCChannelGainBase(sp) ((sp)->DSCChannelGainBase_Present)

/* Access member 'MessageSequence' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete_contents_MessageSequence(var) var

/* Access member 'MessageSequence' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete_contents_MessageSequence(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete_contents {

	ED_OCTET MessageSequence; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete_contents;
#define INIT_c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete_contents(c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete_contents* sp);

/* Access member 'Count' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_Count(var) var

/* Access member 'Count' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_Count(var) (&var)

/* Access member 'PilotPN' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01_data_PilotPN(var) var

/* Access member 'PilotPN' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01_data_PilotPN(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01(var) (&var)

/* Access member 'ChannelIncluded' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data_ChannelIncluded(var) var

/* Access member 'ChannelIncluded' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data_ChannelIncluded(var) (&var)

/* Access member 'SystemType' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data_Channel' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data_Channel_SystemType(var) var

/* Access member 'SystemType' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data_Channel' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data_Channel_SystemType(var) (&var)

/* Access member 'BandClass' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data_Channel' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data_Channel_BandClass(var) var

/* Access member 'BandClass' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data_Channel' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data_Channel_BandClass(var) (&var)

/* Access member 'ChannelNumber' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data_Channel' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data_Channel_ChannelNumber(var) var

/* Access member 'ChannelNumber' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data_Channel' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data_Channel_ChannelNumber(var) (&var)

/* Access member 'Channel' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data_Channel(var) (*var)

/* Access member 'Channel' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data_Channel(var) var

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data(var) var

/* Access member 'data02' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02(var) var

/* Access member 'data02' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02(var) (&var)

/* Access member 'SearchWindowSizeIncluded' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_SearchWindowSizeIncluded(var) var

/* Access member 'SearchWindowSizeIncluded' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_SearchWindowSizeIncluded(var) (&var)

/* Access member 'SearchWindowSize' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03_data' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03_data_SearchWindowSize(var) var

/* Access member 'SearchWindowSize' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03_data' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03_data_SearchWindowSize(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03_data(var) var

/* Access member 'data03' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03(var) var

/* Access member 'data03' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03(var) (&var)

/* Access member 'SearchWindowOffsetIncluded' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_SearchWindowOffsetIncluded(var) var

/* Access member 'SearchWindowOffsetIncluded' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_SearchWindowOffsetIncluded(var) (&var)

/* Access member 'SearchWindowOffset' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04_data' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04_data_SearchWindowOffset(var) var

/* Access member 'SearchWindowOffset' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04_data' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04_data_SearchWindowOffset(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04_data(var) var

/* Access member 'data04' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04(var) var

/* Access member 'data04' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04(var) (&var)

/* Access member 'FPDCHSupportedIncluded' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_FPDCHSupportedIncluded(var) var

/* Access member 'FPDCHSupportedIncluded' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_FPDCHSupportedIncluded(var) (&var)

/* Access member 'FPDCHSupported' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05_data' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05_data_FPDCHSupported(var) var

/* Access member 'FPDCHSupported' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05_data' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05_data_FPDCHSupported(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05_data(var) var

/* Access member 'data05' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05(var) var

/* Access member 'data05' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01_data */
typedef struct _c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01_data {

	ED_SHORT PilotPN; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01 */
typedef struct _c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01 {

	c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data_Channel */
typedef struct _c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data_Channel {

	ED_OCTET SystemType; /* ODY01a *//*GBD01b*/
	ED_OCTET BandClass; /* ODY01a *//*GBD01b*/
	ED_SHORT ChannelNumber; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data_Channel;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data */
typedef struct _c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data {

	ED_BOOLEAN ChannelIncluded; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data_Channel *Channel; /* ODY03 <> *//*GBD01b*/
	ED_BOOLEAN Channel_Present;

} c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02 */
typedef struct _c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02 {

	c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03_data */
typedef struct _c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03_data {

	ED_OCTET SearchWindowSize; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SearchWindowSize_Present;

} c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03 */
typedef struct _c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03 {

	c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04_data */
typedef struct _c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04_data {

	ED_OCTET SearchWindowOffset; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SearchWindowOffset_Present;

} c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04 */
typedef struct _c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04 {

	c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05_data */
typedef struct _c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05_data {

	ED_BOOLEAN FPDCHSupported; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN FPDCHSupported_Present;

} c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05 */
typedef struct _c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05 {

	c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATRUP_INUSE_NeighborList_contents {

	ED_OCTET Count; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01 data01;/*GFB09*//*GBD01b*/
	c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02 data02;/*GFB09*//*GBD01b*/
	ED_BOOLEAN SearchWindowSizeIncluded; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03 data03;/*GFB09*//*GBD01b*/
	ED_BOOLEAN SearchWindowOffsetIncluded; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04 data04;/*GFB09*//*GBD01b*/
	ED_BOOLEAN FPDCHSupportedIncluded; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN FPDCHSupportedIncluded_Present;
	c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05 data05;/*GFB09*//*GBD01b*/

}	c_RPDCON_IRATRUP_INUSE_NeighborList_contents;
#define INIT_c_RPDCON_IRATRUP_INUSE_NeighborList_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATRUP_INUSE_NeighborList_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATRUP_INUSE_NeighborList_contents(c_RPDCON_IRATRUP_INUSE_NeighborList_contents* sp);
#define SETPRESENT_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_FPDCHSupportedIncluded(sp,present) ((sp)->FPDCHSupportedIncluded_Present = present)
#define GETPRESENT_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_FPDCHSupportedIncluded(sp) ((sp)->FPDCHSupportedIncluded_Present)

/* Access member 'MessageSequence' of type 'c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_MessageSequence(var) var

/* Access member 'MessageSequence' of type 'c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_MessageSequence(var) (&var)

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01_data_AttributeLength(var) var

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01_data_AttributeLength(var) (&var)

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01_data_AttributeRecord(var) var

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01_data_AttributeRecord(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01_data */
typedef struct _c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01_data {

	ED_OCTET AttributeLength; /* ODY01a *//*GBD01b*/
	c_RPD_Inter_RAT_Overhead_Messages_CS0024B AttributeRecord; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01 */
typedef struct _c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01 {

	c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents {

	ED_OCTET MessageSequence; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents;
#define INIT_c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents(c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents* sp);

/* Access member 'MessageSequence' of type 'c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse_contents_MessageSequence(var) var

/* Access member 'MessageSequence' of type 'c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse_contents_MessageSequence(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse_contents {

	ED_OCTET MessageSequence; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse_contents;
#define INIT_c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse_contents(c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse_contents* sp);

/* Access member 'ChannelIncluded' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_ChannelIncluded(var) var

/* Access member 'ChannelIncluded' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_ChannelIncluded(var) (&var)

/* Access member 'SystemType' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_Channel' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_Channel_SystemType(var) var

/* Access member 'SystemType' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_Channel' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_Channel_SystemType(var) (&var)

/* Access member 'BandClass' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_Channel' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_Channel_BandClass(var) var

/* Access member 'BandClass' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_Channel' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_Channel_BandClass(var) (&var)

/* Access member 'ChannelNumber' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_Channel' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_Channel_ChannelNumber(var) var

/* Access member 'ChannelNumber' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_Channel' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_Channel_ChannelNumber(var) (&var)

/* Access member 'Channel' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_Channel(var) (*var)

/* Access member 'Channel' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_Channel(var) var

/* Access member 'SectorCount' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_SectorCount(var) var

/* Access member 'SectorCount' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_SectorCount(var) (&var)

/* Access member 'SectorPilotPN' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data_SectorPilotPN(var) var

/* Access member 'SectorPilotPN' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data_SectorPilotPN(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01(var) (&var)

/* Access member 'SectorSearchWindowSizeIncluded' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_SectorSearchWindowSizeIncluded(var) var

/* Access member 'SectorSearchWindowSizeIncluded' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_SectorSearchWindowSizeIncluded(var) (&var)

/* Access member 'SectorSearchWindowSize' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data_SectorSearchWindowSize(var) var

/* Access member 'SectorSearchWindowSize' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data_SectorSearchWindowSize(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data(var) var

/* Access member 'data02' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02(var) var

/* Access member 'data02' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02(var) (&var)

/* Access member 'SectorSearchWindowOffsetIncluded' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_SectorSearchWindowOffsetIncluded(var) var

/* Access member 'SectorSearchWindowOffsetIncluded' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_SectorSearchWindowOffsetIncluded(var) (&var)

/* Access member 'SectorSearchWindowOffset' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data_SectorSearchWindowOffset(var) var

/* Access member 'SectorSearchWindowOffset' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data_SectorSearchWindowOffset(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data(var) var

/* Access member 'data03' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03(var) var

/* Access member 'data03' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_Channel */
typedef struct _c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_Channel {

	ED_OCTET SystemType; /* ODY01a *//*GBD01b*/
	ED_OCTET BandClass; /* ODY01a *//*GBD01b*/
	ED_SHORT ChannelNumber; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_Channel;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data */
typedef struct _c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data {

	ED_SHORT SectorPilotPN; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01 */
typedef struct _c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01 {

	c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data */
typedef struct _c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data {

	ED_OCTET SectorSearchWindowSize; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SectorSearchWindowSize_Present;

} c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02 */
typedef struct _c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02 {

	c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data */
typedef struct _c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data {

	ED_OCTET SectorSearchWindowOffset; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SectorSearchWindowOffset_Present;

} c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03 */
typedef struct _c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03 {

	c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents {

	ED_BOOLEAN ChannelIncluded; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_Channel *Channel; /* ODY03 <> *//*GBD01b*/
	ED_BOOLEAN Channel_Present;
	ED_OCTET SectorCount; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SectorCount_Present;
	c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01 data01;/*GFB09*//*GBD01b*/
	ED_BOOLEAN SectorSearchWindowSizeIncluded; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SectorSearchWindowSizeIncluded_Present;
	c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02 data02;/*GFB09*//*GBD01b*/
	ED_BOOLEAN SectorSearchWindowOffsetIncluded; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SectorSearchWindowOffsetIncluded_Present;
	c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03 data03;/*GFB09*//*GBD01b*/

}	c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents;
#define INIT_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents(c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents* sp);
void SETPRESENT_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_Channel (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents* sp, ED_BOOLEAN present);
#define GETPRESENT_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_Channel(sp) ((sp)->Channel_Present)
#define SETPRESENT_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_SectorCount(sp,present) ((sp)->SectorCount_Present = present)
#define GETPRESENT_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_SectorCount(sp) ((sp)->SectorCount_Present)
#define SETPRESENT_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_SectorSearchWindowSizeIncluded(sp,present) ((sp)->SectorSearchWindowSizeIncluded_Present = present)
#define GETPRESENT_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_SectorSearchWindowSizeIncluded(sp) ((sp)->SectorSearchWindowSizeIncluded_Present)
#define SETPRESENT_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_SectorSearchWindowOffsetIncluded(sp,present) ((sp)->SectorSearchWindowOffsetIncluded_Present = present)
#define GETPRESENT_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_SectorSearchWindowOffsetIncluded(sp) ((sp)->SectorSearchWindowOffsetIncluded_Present)

/* Access member 'TransactionID' of type 'c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_TransactionID(var) (&var)

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data_AttributeLength(var) var

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data_AttributeLength(var) (&var)

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data_AttributeRecord(var) var

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data_AttributeRecord(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data */
typedef struct _c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data {

	ED_OCTET AttributeLength; /* ODY01a *//*GBD01b*/
	c_RPD_Inter_RAT_Overhead_Messages_CS0024B AttributeRecord; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01 */
typedef struct _c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01 {

	c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents;
#define INIT_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents(c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept_contents;
#define INIT_c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept_contents(c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject_contents' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject_contents' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject_contents;
#define INIT_c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject_contents(c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_TransactionID(var) (&var)

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01_data_AttributeLength(var) var

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01_data_AttributeLength(var) (&var)

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01_data_AttributeRecord(var) var

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01_data_AttributeRecord(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01_data */
typedef struct _c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01_data {

	ED_OCTET AttributeLength; /* ODY01a *//*GBD01b*/
	c_RPD_Inter_RAT_Overhead_Messages_CS0024B AttributeRecord; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01 */
typedef struct _c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01 {

	c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents;
#define INIT_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents(c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_TransactionID(var) (&var)

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01_data_AttributeLength(var) var

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01_data_AttributeLength(var) (&var)

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01_data_AttributeRecord(var) var

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01_data_AttributeRecord(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01_data */
typedef struct _c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01_data {

	ED_OCTET AttributeLength; /* ODY01a *//*GBD01b*/
	c_RPD_Inter_RAT_Overhead_Messages_CS0024B AttributeRecord; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01 */
typedef struct _c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01 {

	c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents;
#define INIT_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents(c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents* sp);

/* Access member 'ColorCode' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_ColorCode(var) var

/* Access member 'ColorCode' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_ColorCode(var) (&var)

/* Access member 'SectorID24' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_SectorID24(var) var

/* Access member 'SectorID24' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_SectorID24(var) (&var)

/* Access member 'SectorSignature' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_SectorSignature(var) var

/* Access member 'SectorSignature' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_SectorSignature(var) (&var)

/* Access member 'AccessSignature' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_AccessSignature(var) var

/* Access member 'AccessSignature' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_AccessSignature(var) (&var)

/* Access member 'Redirect' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_Redirect(var) var

/* Access member 'Redirect' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_Redirect(var) (&var)

/* Access member 'RPCCount63To0' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_RPCCount63To0(var) var

/* Access member 'RPCCount63To0' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_RPCCount63To0(var) (&var)

/* Access member 'ForwardTrafficValid63To0' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01_data_ForwardTrafficValid63To0(var) var

/* Access member 'ForwardTrafficValid63To0' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01_data_ForwardTrafficValid63To0(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01(var) (&var)

/* Access member 'RPCCount127To64Included' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_RPCCount127To64Included(var) var

/* Access member 'RPCCount127To64Included' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_RPCCount127To64Included(var) (&var)

/* Access member 'RPCCount127To64' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_RPCCount127To64(var) var

/* Access member 'RPCCount127To64' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_RPCCount127To64(var) (&var)

/* Access member 'ForwardTrafficValid127To64' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02_data_ForwardTrafficValid127To64(var) var

/* Access member 'ForwardTrafficValid127To64' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02_data_ForwardTrafficValid127To64(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02_data(var) var

/* Access member 'data02' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02(var) var

/* Access member 'data02' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02(var) (&var)

/* Access member 'ReservedBitsIncluded' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_ReservedBitsIncluded(var) var

/* Access member 'ReservedBitsIncluded' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_ReservedBitsIncluded(var) (&var)

/* Access member 'NumReservedBits' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_NumReservedBits(var) var

/* Access member 'NumReservedBits' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_NumReservedBits(var) (&var)

/* Access member 'CompatibleReservedBits' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03_data_CompatibleReservedBits(var) var

/* Access member 'CompatibleReservedBits' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03_data_CompatibleReservedBits(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03_data(var) var

/* Access member 'data03' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03(var) var

/* Access member 'data03' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03(var) (&var)

/* Access member 'OtherRATAvailable' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_OtherRATAvailable(var) var

/* Access member 'OtherRATAvailable' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_OtherRATAvailable(var) (&var)

/* Access member 'OtherRATTXCycle' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_OtherRATTXCycle(var) var

/* Access member 'OtherRATTXCycle' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_OtherRATTXCycle(var) (&var)

/* Access member 'OtherRATSignature' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_OtherRATSignature(var) var

/* Access member 'OtherRATSignature' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_OtherRATSignature(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01_data */
typedef struct _c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01_data {

	ED_BOOLEAN ForwardTrafficValid63To0; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01 */
typedef struct _c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01 {

	c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02_data */
typedef struct _c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02_data {

	ED_BOOLEAN ForwardTrafficValid127To64; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ForwardTrafficValid127To64_Present;

} c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02 */
typedef struct _c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02 {

	c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03_data */
typedef struct _c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03_data {

	ED_BOOLEAN CompatibleReservedBits; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN CompatibleReservedBits_Present;

} c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03 */
typedef struct _c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03 {

	c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATOMP_INUSE_QuickConfig_contents {

	ED_OCTET ColorCode; /* ODY01a *//*GBD01b*/
	ED_LONG SectorID24; /* ODY01a *//*GBD01b*/
	ED_SHORT SectorSignature; /* ODY01a *//*GBD01b*/
	ED_SHORT AccessSignature; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Redirect; /* ODY01a *//*GBD01b*/
	ED_OCTET RPCCount63To0; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01 data01;/*GFB09*//*GBD01b*/
	ED_BOOLEAN RPCCount127To64Included; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN RPCCount127To64Included_Present;
	ED_OCTET RPCCount127To64; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN RPCCount127To64_Present;
	c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02 data02;/*GFB09*//*GBD01b*/
	ED_BOOLEAN ReservedBitsIncluded; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ReservedBitsIncluded_Present;
	ED_OCTET NumReservedBits; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN NumReservedBits_Present;
	c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03 data03;/*GFB09*//*GBD01b*/
	ED_BOOLEAN OtherRATAvailable; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN OtherRATAvailable_Present;
	ED_OCTET OtherRATTXCycle; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN OtherRATTXCycle_Present;
	ED_OCTET OtherRATSignature; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN OtherRATSignature_Present;

}	c_RPDCON_IRATOMP_INUSE_QuickConfig_contents;
#define INIT_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATOMP_INUSE_QuickConfig_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents(c_RPDCON_IRATOMP_INUSE_QuickConfig_contents* sp);
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_RPCCount127To64Included(sp,present) ((sp)->RPCCount127To64Included_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_RPCCount127To64Included(sp) ((sp)->RPCCount127To64Included_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_RPCCount127To64(sp,present) ((sp)->RPCCount127To64_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_RPCCount127To64(sp) ((sp)->RPCCount127To64_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_ReservedBitsIncluded(sp,present) ((sp)->ReservedBitsIncluded_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_ReservedBitsIncluded(sp) ((sp)->ReservedBitsIncluded_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_NumReservedBits(sp,present) ((sp)->NumReservedBits_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_NumReservedBits(sp) ((sp)->NumReservedBits_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_OtherRATAvailable(sp,present) ((sp)->OtherRATAvailable_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_OtherRATAvailable(sp) ((sp)->OtherRATAvailable_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_OtherRATTXCycle(sp,present) ((sp)->OtherRATTXCycle_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_OtherRATTXCycle(sp) ((sp)->OtherRATTXCycle_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_OtherRATSignature(sp,present) ((sp)->OtherRATSignature_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_OtherRATSignature(sp) ((sp)->OtherRATSignature_Present)

/* Access member 'CountryCode' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_CountryCode(var) var

/* Access member 'CountryCode' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_CountryCode(var) (&var)

/* Access member 'SectorID' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_SectorID(var) var

/* Access member 'SectorID' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_SectorID(var) (&var)

/* Access member 'SubnetMask' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_SubnetMask(var) var

/* Access member 'SubnetMask' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_SubnetMask(var) (&var)

/* Access member 'SectorSignature' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_SectorSignature(var) var

/* Access member 'SectorSignature' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_SectorSignature(var) (&var)

/* Access member 'Latitude' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_Latitude(var) var

/* Access member 'Latitude' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_Latitude(var) (&var)

/* Access member 'Longitude' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_Longitude(var) var

/* Access member 'Longitude' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_Longitude(var) (&var)

/* Access member 'RouteUpdateRadiusOverhead' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_RouteUpdateRadiusOverhead(var) var

/* Access member 'RouteUpdateRadiusOverhead' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_RouteUpdateRadiusOverhead(var) (&var)

/* Access member 'LeapSeconds' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_LeapSeconds(var) var

/* Access member 'LeapSeconds' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_LeapSeconds(var) (&var)

/* Access member 'LocalTimeOffset' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_LocalTimeOffset(var) var

/* Access member 'LocalTimeOffset' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_LocalTimeOffset(var) (&var)

/* Access member 'ReverseLinkSilenceDuration' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_ReverseLinkSilenceDuration(var) var

/* Access member 'ReverseLinkSilenceDuration' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_ReverseLinkSilenceDuration(var) (&var)

/* Access member 'ReverseLinkSilencePeriod' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_ReverseLinkSilencePeriod(var) var

/* Access member 'ReverseLinkSilencePeriod' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_ReverseLinkSilencePeriod(var) (&var)

/* Access member 'ChannelCount' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_ChannelCount(var) var

/* Access member 'ChannelCount' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_ChannelCount(var) (&var)

/* Access member 'SystemType' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data_Channel' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data_Channel_SystemType(var) var

/* Access member 'SystemType' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data_Channel' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data_Channel_SystemType(var) (&var)

/* Access member 'BandClass' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data_Channel' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data_Channel_BandClass(var) var

/* Access member 'BandClass' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data_Channel' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data_Channel_BandClass(var) (&var)

/* Access member 'ChannelNumber' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data_Channel' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data_Channel_ChannelNumber(var) var

/* Access member 'ChannelNumber' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data_Channel' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data_Channel_ChannelNumber(var) (&var)

/* Access member 'Channel' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data_Channel(var) var

/* Access member 'Channel' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data_Channel(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01(var) (&var)

/* Access member 'NeighborCount' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_NeighborCount(var) var

/* Access member 'NeighborCount' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_NeighborCount(var) (&var)

/* Access member 'NeighborPilotPN' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02_data_NeighborPilotPN(var) var

/* Access member 'NeighborPilotPN' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02_data_NeighborPilotPN(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02_data(var) var

/* Access member 'data02' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02(var) var

/* Access member 'data02' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02(var) (&var)

/* Access member 'NeighborChannelIncluded' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data_NeighborChannelIncluded(var) var

/* Access member 'NeighborChannelIncluded' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data_NeighborChannelIncluded(var) (&var)

/* Access member 'SystemType' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data_NeighborChannel' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data_NeighborChannel_SystemType(var) var

/* Access member 'SystemType' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data_NeighborChannel' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data_NeighborChannel_SystemType(var) (&var)

/* Access member 'BandClass' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data_NeighborChannel' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data_NeighborChannel_BandClass(var) var

/* Access member 'BandClass' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data_NeighborChannel' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data_NeighborChannel_BandClass(var) (&var)

/* Access member 'ChannelNumber' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data_NeighborChannel' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data_NeighborChannel_ChannelNumber(var) var

/* Access member 'ChannelNumber' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data_NeighborChannel' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data_NeighborChannel_ChannelNumber(var) (&var)

/* Access member 'NeighborChannel' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data_NeighborChannel(var) (*var)

/* Access member 'NeighborChannel' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data_NeighborChannel(var) var

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data(var) var

/* Access member 'data03' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03(var) var

/* Access member 'data03' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03(var) (&var)

/* Access member 'NeighborSearchWindowSizeIncluded' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_NeighborSearchWindowSizeIncluded(var) var

/* Access member 'NeighborSearchWindowSizeIncluded' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_NeighborSearchWindowSizeIncluded(var) (&var)

/* Access member 'NeighborSearchWindowSize' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04_data_NeighborSearchWindowSize(var) var

/* Access member 'NeighborSearchWindowSize' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04_data_NeighborSearchWindowSize(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04_data(var) var

/* Access member 'data04' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04(var) var

/* Access member 'data04' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04(var) (&var)

/* Access member 'NeighborSearchWindowOffsetIncluded' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_NeighborSearchWindowOffsetIncluded(var) var

/* Access member 'NeighborSearchWindowOffsetIncluded' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_NeighborSearchWindowOffsetIncluded(var) (&var)

/* Access member 'NeighborSearchWindowOffset' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05_data_NeighborSearchWindowOffset(var) var

/* Access member 'NeighborSearchWindowOffset' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05_data_NeighborSearchWindowOffset(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05_data(var) var

/* Access member 'data05' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05(var) var

/* Access member 'data05' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05(var) (&var)

/* Access member 'ExtendedChannelIncluded' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_ExtendedChannelIncluded(var) var

/* Access member 'ExtendedChannelIncluded' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_ExtendedChannelIncluded(var) (&var)

/* Access member 'ExtendedChannelCount' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_ExtendedChannelCount(var) var

/* Access member 'ExtendedChannelCount' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_ExtendedChannelCount(var) (&var)

/* Access member 'SystemType' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data_ExtendedChannel' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data_ExtendedChannel_SystemType(var) var

/* Access member 'SystemType' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data_ExtendedChannel' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data_ExtendedChannel_SystemType(var) (&var)

/* Access member 'BandClass' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data_ExtendedChannel' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data_ExtendedChannel_BandClass(var) var

/* Access member 'BandClass' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data_ExtendedChannel' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data_ExtendedChannel_BandClass(var) (&var)

/* Access member 'ChannelNumber' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data_ExtendedChannel' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data_ExtendedChannel_ChannelNumber(var) var

/* Access member 'ChannelNumber' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data_ExtendedChannel' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data_ExtendedChannel_ChannelNumber(var) (&var)

/* Access member 'ExtendedChannel' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data_ExtendedChannel(var) var

/* Access member 'ExtendedChannel' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data_ExtendedChannel(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data(var) var

/* Access member 'data06' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06(var) var

/* Access member 'data06' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06(var) (&var)

/* Access member 'AccessHashingChannelMaskIncluded' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_AccessHashingChannelMaskIncluded(var) var

/* Access member 'AccessHashingChannelMaskIncluded' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_AccessHashingChannelMaskIncluded(var) (&var)

/* Access member 'AccessHashingMaskLength' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_AccessHashingMaskLength(var) var

/* Access member 'AccessHashingMaskLength' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_AccessHashingMaskLength(var) (&var)

/* Access member 'AccessHashingChannelMaskSameAsPrevious' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07_data_AccessHashingChannelMaskSameAsPrevious(var) var

/* Access member 'AccessHashingChannelMaskSameAsPrevious' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07_data_AccessHashingChannelMaskSameAsPrevious(var) (&var)

/* Access member 'AccessHashingChannelMask' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07_data_AccessHashingChannelMask(var) var

/* Access member 'AccessHashingChannelMask' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07_data_AccessHashingChannelMask(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07_data(var) var

/* Access member 'data07' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07(var) var

/* Access member 'data07' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07(var) (&var)

/* Access member 'RouteUpdateTriggerCodeIncluded' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_RouteUpdateTriggerCodeIncluded(var) var

/* Access member 'RouteUpdateTriggerCodeIncluded' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_RouteUpdateTriggerCodeIncluded(var) (&var)

/* Access member 'RouteUpdateTriggerCode' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_RouteUpdateTriggerCode(var) var

/* Access member 'RouteUpdateTriggerCode' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_RouteUpdateTriggerCode(var) (&var)

/* Access member 'RouteUpdateTriggerMaxAge' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_RouteUpdateTriggerMaxAge(var) var

/* Access member 'RouteUpdateTriggerMaxAge' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_RouteUpdateTriggerMaxAge(var) (&var)

/* Access member 'PriorSessionGAUP' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_PriorSessionGAUP(var) var

/* Access member 'PriorSessionGAUP' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_PriorSessionGAUP(var) (&var)

/* Access member 'FPDCHSupportedIncluded' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_FPDCHSupportedIncluded(var) var

/* Access member 'FPDCHSupportedIncluded' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_FPDCHSupportedIncluded(var) (&var)

/* Access member 'FPDCHSupported' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08_data_FPDCHSupported(var) var

/* Access member 'FPDCHSupported' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08_data_FPDCHSupported(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08_data(var) var

/* Access member 'data08' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08(var) var

/* Access member 'data08' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08(var) (&var)

/* Access member 'SecondaryColorCodeIncluded' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_SecondaryColorCodeIncluded(var) var

/* Access member 'SecondaryColorCodeIncluded' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_SecondaryColorCodeIncluded(var) (&var)

/* Access member 'SecondaryColorCodeCount' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_SecondaryColorCodeCount(var) var

/* Access member 'SecondaryColorCodeCount' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_SecondaryColorCodeCount(var) (&var)

/* Access member 'SecondaryColorCode' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09_data_SecondaryColorCode(var) var

/* Access member 'SecondaryColorCode' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09_data_SecondaryColorCode(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09_data(var) var

/* Access member 'data09' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09(var) var

/* Access member 'data09' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data_Channel */
typedef struct _c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data_Channel {

	ED_OCTET SystemType; /* ODY01a *//*GBD01b*/
	ED_OCTET BandClass; /* ODY01a *//*GBD01b*/
	ED_SHORT ChannelNumber; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data_Channel;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data */
typedef struct _c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data {

	c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data_Channel Channel;/*GBD01b*/

} c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01 */
typedef struct _c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01 {

	c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02_data */
typedef struct _c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02_data {

	ED_SHORT NeighborPilotPN; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02 */
typedef struct _c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02 {

	c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data_NeighborChannel */
typedef struct _c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data_NeighborChannel {

	ED_OCTET SystemType; /* ODY01a *//*GBD01b*/
	ED_OCTET BandClass; /* ODY01a *//*GBD01b*/
	ED_SHORT ChannelNumber; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data_NeighborChannel;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data */
typedef struct _c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data {

	ED_BOOLEAN NeighborChannelIncluded; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data_NeighborChannel *NeighborChannel; /* ODY03 <> *//*GBD01b*/
	ED_BOOLEAN NeighborChannel_Present;

} c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03 */
typedef struct _c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03 {

	c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04_data */
typedef struct _c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04_data {

	ED_OCTET NeighborSearchWindowSize; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN NeighborSearchWindowSize_Present;

} c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04 */
typedef struct _c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04 {

	c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05_data */
typedef struct _c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05_data {

	ED_OCTET NeighborSearchWindowOffset; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN NeighborSearchWindowOffset_Present;

} c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05 */
typedef struct _c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05 {

	c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data_ExtendedChannel */
typedef struct _c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data_ExtendedChannel {

	ED_OCTET SystemType; /* ODY01a *//*GBD01b*/
	ED_OCTET BandClass; /* ODY01a *//*GBD01b*/
	ED_SHORT ChannelNumber; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data_ExtendedChannel;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data */
typedef struct _c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data {

	c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data_ExtendedChannel ExtendedChannel;/*GBD01b*/

} c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06 */
typedef struct _c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06 {

	c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06;

/* DEFINITION OF BINARY c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07_data_AccessHashingChannelMask */
typedef struct _c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07_data_AccessHashingChannelMask {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07_data_AccessHashingChannelMask;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07_data_AccessHashingChannelMask(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07_data */
typedef struct _c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07_data {

	ED_BOOLEAN AccessHashingChannelMaskSameAsPrevious; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07_data_AccessHashingChannelMask AccessHashingChannelMask; /* Static, variable size; bits needed 64 *//*GBD01b*/

} c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07 */
typedef struct _c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07 {

	c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08_data */
typedef struct _c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08_data {

	ED_BOOLEAN FPDCHSupported; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN FPDCHSupported_Present;

} c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08 */
typedef struct _c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08 {

	c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09_data */
typedef struct _c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09_data {

	ED_OCTET SecondaryColorCode; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09 */
typedef struct _c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09 {

	c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATOMP_INUSE_SectorParameters_contents {

	ED_SHORT CountryCode; /* ODY01a *//*GBD01b*/
	ED_BYTE SectorID [16]; /* Static, fixed size; bits needed 128 *//*GBD01b*/
	ED_OCTET SubnetMask; /* ODY01a *//*GBD01b*/
	ED_SHORT SectorSignature; /* ODY01a *//*GBD01b*/
	ED_LONG Latitude; /* ODY01a *//*GBD01b*/
	ED_LONG Longitude; /* ODY01a *//*GBD01b*/
	ED_SHORT RouteUpdateRadiusOverhead; /* ODY01a *//*GBD01b*/
	ED_OCTET LeapSeconds; /* ODY01a *//*GBD01b*/
	ED_SHORT LocalTimeOffset; /* ODY01a *//*GBD01b*/
	ED_OCTET ReverseLinkSilenceDuration; /* ODY01a *//*GBD01b*/
	ED_OCTET ReverseLinkSilencePeriod; /* ODY01a *//*GBD01b*/
	ED_OCTET ChannelCount; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01 data01;/*GFB09*//*GBD01b*/
	ED_OCTET NeighborCount; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02 data02;/*GFB09*//*GBD01b*/
	c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03 data03;/*GFB09*//*GBD01b*/
	ED_BOOLEAN NeighborSearchWindowSizeIncluded; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04 data04;/*GFB09*//*GBD01b*/
	ED_BOOLEAN NeighborSearchWindowOffsetIncluded; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05 data05;/*GFB09*//*GBD01b*/
	ED_BOOLEAN ExtendedChannelIncluded; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ExtendedChannelIncluded_Present;
	ED_OCTET ExtendedChannelCount; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ExtendedChannelCount_Present;
	c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06 data06;/*GFB09*//*GBD01b*/
	ED_BOOLEAN AccessHashingChannelMaskIncluded; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN AccessHashingChannelMaskIncluded_Present;
	ED_OCTET AccessHashingMaskLength; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN AccessHashingMaskLength_Present;
	c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07 data07;/*GFB09*//*GBD01b*/
	ED_BOOLEAN RouteUpdateTriggerCodeIncluded; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN RouteUpdateTriggerCodeIncluded_Present;
	ED_SHORT RouteUpdateTriggerCode; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN RouteUpdateTriggerCode_Present;
	ED_OCTET RouteUpdateTriggerMaxAge; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN RouteUpdateTriggerMaxAge_Present;
	ED_BOOLEAN PriorSessionGAUP; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PriorSessionGAUP_Present;
	ED_BOOLEAN FPDCHSupportedIncluded; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN FPDCHSupportedIncluded_Present;
	c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08 data08;/*GFB09*//*GBD01b*/
	ED_BOOLEAN SecondaryColorCodeIncluded; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SecondaryColorCodeIncluded_Present;
	ED_OCTET SecondaryColorCodeCount; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SecondaryColorCodeCount_Present;
	c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09 data09;/*GFB09*//*GBD01b*/

}	c_RPDCON_IRATOMP_INUSE_SectorParameters_contents;
#define INIT_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents(c_RPDCON_IRATOMP_INUSE_SectorParameters_contents* sp);
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_ExtendedChannelIncluded(sp,present) ((sp)->ExtendedChannelIncluded_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_ExtendedChannelIncluded(sp) ((sp)->ExtendedChannelIncluded_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_ExtendedChannelCount(sp,present) ((sp)->ExtendedChannelCount_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_ExtendedChannelCount(sp) ((sp)->ExtendedChannelCount_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_AccessHashingChannelMaskIncluded(sp,present) ((sp)->AccessHashingChannelMaskIncluded_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_AccessHashingChannelMaskIncluded(sp) ((sp)->AccessHashingChannelMaskIncluded_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_AccessHashingMaskLength(sp,present) ((sp)->AccessHashingMaskLength_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_AccessHashingMaskLength(sp) ((sp)->AccessHashingMaskLength_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_RouteUpdateTriggerCodeIncluded(sp,present) ((sp)->RouteUpdateTriggerCodeIncluded_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_RouteUpdateTriggerCodeIncluded(sp) ((sp)->RouteUpdateTriggerCodeIncluded_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_RouteUpdateTriggerCode(sp,present) ((sp)->RouteUpdateTriggerCode_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_RouteUpdateTriggerCode(sp) ((sp)->RouteUpdateTriggerCode_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_RouteUpdateTriggerMaxAge(sp,present) ((sp)->RouteUpdateTriggerMaxAge_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_RouteUpdateTriggerMaxAge(sp) ((sp)->RouteUpdateTriggerMaxAge_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_PriorSessionGAUP(sp,present) ((sp)->PriorSessionGAUP_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_PriorSessionGAUP(sp) ((sp)->PriorSessionGAUP_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_FPDCHSupportedIncluded(sp,present) ((sp)->FPDCHSupportedIncluded_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_FPDCHSupportedIncluded(sp) ((sp)->FPDCHSupportedIncluded_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_SecondaryColorCodeIncluded(sp,present) ((sp)->SecondaryColorCodeIncluded_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_SecondaryColorCodeIncluded(sp) ((sp)->SecondaryColorCodeIncluded_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_SecondaryColorCodeCount(sp,present) ((sp)->SecondaryColorCodeCount_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_SecondaryColorCodeCount(sp) ((sp)->SecondaryColorCodeCount_Present)

/* Access member 'ReverseLinkSilenceDuration' of type 'c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters_contents_ReverseLinkSilenceDuration(var) var

/* Access member 'ReverseLinkSilenceDuration' of type 'c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters_contents_ReverseLinkSilenceDuration(var) (&var)

/* Access member 'ReverseLinkSilencePeriod' of type 'c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters_contents_ReverseLinkSilencePeriod(var) var

/* Access member 'ReverseLinkSilencePeriod' of type 'c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters_contents_ReverseLinkSilencePeriod(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters_contents {

	ED_OCTET ReverseLinkSilenceDuration; /* ODY01a *//*GBD01b*/
	ED_OCTET ReverseLinkSilencePeriod; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters_contents;
#define INIT_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters_contents(c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters_contents* sp);

/* Access member 'OtherRATSignature' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_OtherRATSignature(var) var

/* Access member 'OtherRATSignature' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_OtherRATSignature(var) (&var)

/* Access member 'NumOtherRAT' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_NumOtherRAT(var) var

/* Access member 'NumOtherRAT' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_NumOtherRAT(var) (&var)

/* Access member 'RATType' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_RATType(var) var

/* Access member 'RATType' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_RATType(var) (&var)

/* Access member 'NeighborRATRecordLength' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecordLength(var) var

/* Access member 'NeighborRATRecordLength' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecordLength(var) (&var)

/* Access member 'OtherNeighborRATRecord' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_OtherNeighborRATRecord(var) (*var)

/* Access member 'OtherNeighborRATRecord' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_OtherNeighborRATRecord(var) var

/* Access member 'PriorityIncluded' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_PriorityIncluded(var) var

/* Access member 'PriorityIncluded' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_PriorityIncluded(var) (&var)

/* Access member 'ServingPriority' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_ServingPriority(var) var

/* Access member 'ServingPriority' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_ServingPriority(var) (&var)

/* Access member 'ThreshServing' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_ThreshServing(var) var

/* Access member 'ThreshServing' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_ThreshServing(var) (&var)

/* Access member 'PerEARFCNParamsIncluded' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_PerEARFCNParamsIncluded(var) var

/* Access member 'PerEARFCNParamsIncluded' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_PerEARFCNParamsIncluded(var) (&var)

/* Access member 'RxLevMinEUTRACommon' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_RxLevMinEUTRACommon(var) var

/* Access member 'RxLevMinEUTRACommon' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_RxLevMinEUTRACommon(var) (&var)

/* Access member 'PEMaxCommon' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_PEMaxCommon(var) var

/* Access member 'PEMaxCommon' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_PEMaxCommon(var) (&var)

/* Access member 'RxLevMinEUTRAOffsetCommonIncl' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_RxLevMinEUTRAOffsetCommonIncl(var) var

/* Access member 'RxLevMinEUTRAOffsetCommonIncl' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_RxLevMinEUTRAOffsetCommonIncl(var) (&var)

/* Access member 'RxLevMinEUTRAOffsetCommon' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_RxLevMinEUTRAOffsetCommon(var) var

/* Access member 'RxLevMinEUTRAOffsetCommon' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_RxLevMinEUTRAOffsetCommon(var) (&var)

/* Access member 'MaxReselectionTimerIncluded' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_MaxReselectionTimerIncluded(var) var

/* Access member 'MaxReselectionTimerIncluded' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_MaxReselectionTimerIncluded(var) (&var)

/* Access member 'MaxReselectionTimer' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_MaxReselectionTimer(var) var

/* Access member 'MaxReselectionTimer' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_MaxReselectionTimer(var) (&var)

/* Access member 'SearchBackOffTimerIncluded' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_SearchBackOffTimerIncluded(var) var

/* Access member 'SearchBackOffTimerIncluded' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_SearchBackOffTimerIncluded(var) (&var)

/* Access member 'MinMeasurementBackoff' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_MinMeasurementBackoff(var) var

/* Access member 'MinMeasurementBackoff' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_MinMeasurementBackoff(var) (&var)

/* Access member 'MaxMeasurementBackoff' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_MaxMeasurementBackoff(var) var

/* Access member 'MaxMeasurementBackoff' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_MaxMeasurementBackoff(var) (&var)

/* Access member 'PLMNIDIncluded' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_PLMNIDIncluded(var) var

/* Access member 'PLMNIDIncluded' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_PLMNIDIncluded(var) (&var)

/* Access member 'NumEUTRAFrequencies' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_NumEUTRAFrequencies(var) var

/* Access member 'NumEUTRAFrequencies' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_NumEUTRAFrequencies(var) (&var)

/* Access member 'EARFCN' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_EARFCN(var) var

/* Access member 'EARFCN' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_EARFCN(var) (&var)

/* Access member 'EARFCNPriority' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_EARFCNPriority(var) var

/* Access member 'EARFCNPriority' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_EARFCNPriority(var) (&var)

/* Access member 'ThreshX' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_ThreshX(var) var

/* Access member 'ThreshX' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_ThreshX(var) (&var)

/* Access member 'RxLevMinEUTRA' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_RxLevMinEUTRA(var) var

/* Access member 'RxLevMinEUTRA' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_RxLevMinEUTRA(var) (&var)

/* Access member 'PEMax' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PEMax(var) var

/* Access member 'PEMax' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PEMax(var) (&var)

/* Access member 'RxLevMinEUTRAOffsetIncl' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_RxLevMinEUTRAOffsetIncl(var) var

/* Access member 'RxLevMinEUTRAOffsetIncl' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_RxLevMinEUTRAOffsetIncl(var) (&var)

/* Access member 'RxLevMinEUTRAOffset' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_RxLevMinEUTRAOffset(var) var

/* Access member 'RxLevMinEUTRAOffset' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_RxLevMinEUTRAOffset(var) (&var)

/* Access member 'MeasurementBandwidth' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_MeasurementBandwidth(var) var

/* Access member 'MeasurementBandwidth' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_MeasurementBandwidth(var) (&var)

/* Access member 'PLMNSameAsPreviousChannel' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNSameAsPreviousChannel(var) var

/* Access member 'PLMNSameAsPreviousChannel' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNSameAsPreviousChannel(var) (&var)

/* Access member 'NumPLMNIDs' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_NumPLMNIDs(var) var

/* Access member 'NumPLMNIDs' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_NumPLMNIDs(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID_data(var) var

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID_data(var) (&var)

/* Access member 'PLMNID' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID(var) var

/* Access member 'PLMNID' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data(var) var

/* Access member 'data02' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02(var) var

/* Access member 'data02' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02(var) (&var)

/* Access member 'ServingNetworkPLMNIncl' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_ServingNetworkPLMNIncl(var) var

/* Access member 'ServingNetworkPLMNIncl' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_ServingNetworkPLMNIncl(var) (&var)

/* Access member 'NumServingPLMNIDs' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_NumServingPLMNIDs(var) var

/* Access member 'NumServingPLMNIDs' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_NumServingPLMNIDs(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID_data(var) var

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID_data(var) (&var)

/* Access member 'S_PLMNID' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID(var) var

/* Access member 'S_PLMNID' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID(var) (&var)

/* Access member 'RSRQParametersIncluded' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_RSRQParametersIncluded(var) var

/* Access member 'RSRQParametersIncluded' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_RSRQParametersIncluded(var) (&var)

/* Access member 'QualMinEUTRACommon' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_QualMinEUTRACommon(var) var

/* Access member 'QualMinEUTRACommon' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_QualMinEUTRACommon(var) (&var)

/* Access member 'QualMinEUTRAOffsetCommonInc' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_QualMinEUTRAOffsetCommonInc(var) var

/* Access member 'QualMinEUTRAOffsetCommonInc' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_QualMinEUTRAOffsetCommonInc(var) (&var)

/* Access member 'QualMinEUTRAOffsetCommon' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_QualMinEUTRAOffsetCommon(var) var

/* Access member 'QualMinEUTRAOffsetCommon' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_QualMinEUTRAOffsetCommon(var) (&var)

/* Access member 'ThreshXQ' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data_ThreshXQ(var) var

/* Access member 'ThreshXQ' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data_ThreshXQ(var) (&var)

/* Access member 'QualMinEUTRA' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data_QualMinEUTRA(var) var

/* Access member 'QualMinEUTRA' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data_QualMinEUTRA(var) (&var)

/* Access member 'QualMinEUTRAOffsetIncl' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data_QualMinEUTRAOffsetIncl(var) var

/* Access member 'QualMinEUTRAOffsetIncl' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data_QualMinEUTRAOffsetIncl(var) (&var)

/* Access member 'QualMinEUTRAOffset' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data_QualMinEUTRAOffset(var) var

/* Access member 'QualMinEUTRAOffset' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data_QualMinEUTRAOffset(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data(var) var

/* Access member 'data05' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05(var) var

/* Access member 'data05' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05(var) (&var)

/* Access member 'NeighborRATRecord' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord(var) (*var)

/* Access member 'NeighborRATRecord' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord(var) var

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01(var) (&var)

/* DEFINITION OF BINARY c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_OtherNeighborRATRecord */
typedef struct _c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_OtherNeighborRATRecord {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_OtherNeighborRATRecord;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_OtherNeighborRATRecord(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID */
typedef struct _c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID {

	ED_LONG* data; /* NDY01a *//*GBD01b*//*GAD01a*//*AR02 ('TDMSequence'-18080=EDCore::TDMSequence)  */
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data */
typedef struct _c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data {

	ED_SHORT EARFCN; /* ODY01a *//*GBD01b*/
	ED_OCTET EARFCNPriority; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN EARFCNPriority_Present;
	ED_OCTET ThreshX; /* ODY01a *//*GBD01b*/
	ED_OCTET RxLevMinEUTRA; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN RxLevMinEUTRA_Present;
	ED_OCTET PEMax; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PEMax_Present;
	ED_BOOLEAN RxLevMinEUTRAOffsetIncl; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN RxLevMinEUTRAOffsetIncl_Present;
	ED_OCTET RxLevMinEUTRAOffset; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN RxLevMinEUTRAOffset_Present;
	ED_OCTET MeasurementBandwidth; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PLMNSameAsPreviousChannel; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PLMNSameAsPreviousChannel_Present;
	ED_OCTET NumPLMNIDs; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN NumPLMNIDs_Present;
	c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID PLMNID;/*GFB09*//*GBD01b*/

} c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02 */
typedef struct _c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02 {

	c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID */
typedef struct _c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID {

	ED_LONG* data; /* NDY01a *//*GBD01b*//*GAD01a*//*AR02 ('TDMSequence'-18088=EDCore::TDMSequence)  */
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data */
typedef struct _c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data {

	ED_OCTET ThreshXQ; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ThreshXQ_Present;
	ED_OCTET QualMinEUTRA; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN QualMinEUTRA_Present;
	ED_BOOLEAN QualMinEUTRAOffsetIncl; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN QualMinEUTRAOffsetIncl_Present;
	ED_OCTET QualMinEUTRAOffset; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN QualMinEUTRAOffset_Present;

} c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05 */
typedef struct _c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05 {

	c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord */
typedef struct _c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord {

	ED_BOOLEAN PriorityIncluded; /* ODY01a *//*GBD01b*/
	ED_OCTET ServingPriority; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ServingPriority_Present;
	ED_OCTET ThreshServing; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PerEARFCNParamsIncluded; /* ODY01a *//*GBD01b*/
	ED_OCTET RxLevMinEUTRACommon; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN RxLevMinEUTRACommon_Present;
	ED_OCTET PEMaxCommon; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PEMaxCommon_Present;
	ED_BOOLEAN RxLevMinEUTRAOffsetCommonIncl; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN RxLevMinEUTRAOffsetCommonIncl_Present;
	ED_OCTET RxLevMinEUTRAOffsetCommon; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN RxLevMinEUTRAOffsetCommon_Present;
	ED_BOOLEAN MaxReselectionTimerIncluded; /* ODY01a *//*GBD01b*/
	ED_OCTET MaxReselectionTimer; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN MaxReselectionTimer_Present;
	ED_BOOLEAN SearchBackOffTimerIncluded; /* ODY01a *//*GBD01b*/
	ED_OCTET MinMeasurementBackoff; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN MinMeasurementBackoff_Present;
	ED_OCTET MaxMeasurementBackoff; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN MaxMeasurementBackoff_Present;
	ED_BOOLEAN PLMNIDIncluded; /* ODY01a *//*GBD01b*/
	ED_OCTET NumEUTRAFrequencies; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02 data02;/*GFB09*//*GBD01b*/
	ED_BOOLEAN ServingNetworkPLMNIncl; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ServingNetworkPLMNIncl_Present;
	ED_OCTET NumServingPLMNIDs; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN NumServingPLMNIDs_Present;
	c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID S_PLMNID;/*GFB09*//*GBD01b*/
	ED_BOOLEAN RSRQParametersIncluded; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN RSRQParametersIncluded_Present;
	ED_OCTET QualMinEUTRACommon; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN QualMinEUTRACommon_Present;
	ED_BOOLEAN QualMinEUTRAOffsetCommonInc; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN QualMinEUTRAOffsetCommonInc_Present;
	ED_OCTET QualMinEUTRAOffsetCommon; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN QualMinEUTRAOffsetCommon_Present;
	c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05 data05;/*GFB09*//*GBD01b*/

} c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data */
typedef struct _c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data {

	ED_OCTET RATType; /* ODY01a *//*GBD01b*/
	ED_SHORT NeighborRATRecordLength; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_OtherNeighborRATRecord* OtherNeighborRATRecord; /* Dynamic, variable size; bits needed 64 ODY02b *//*GBD01b*/
	ED_BOOLEAN OtherNeighborRATRecord_Present;
	c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord *NeighborRATRecord; /* ODY03 <> *//*GBD01b*/
	ED_BOOLEAN NeighborRATRecord_Present;

} c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01 */
typedef struct _c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01 {

	c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents {

	ED_OCTET OtherRATSignature; /* ODY01a *//*GBD01b*/
	ED_OCTET NumOtherRAT; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents;
#define INIT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents(c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents' as a variable reference */
#define VAR_c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents' as a pointer */
#define PTR_c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_TransactionID(var) (&var)

/* Access member 'AttributeLength' of type 'c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01_data_AttributeLength(var) var

/* Access member 'AttributeLength' of type 'c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01_data_AttributeLength(var) (&var)

/* Access member 'AttributeRecord' of type 'c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01_data_AttributeRecord(var) var

/* Access member 'AttributeRecord' of type 'c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01_data_AttributeRecord(var) (&var)

/* Access member 'data' of type 'c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01' as a variable reference */
#define VAR_c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01' as a pointer */
#define PTR_c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents' as a variable reference */
#define VAR_c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents' as a pointer */
#define PTR_c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01_data */
typedef struct _c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01_data {

	ED_OCTET AttributeLength; /* ODY01a *//*GBD01b*/
	c_RPD_Inter_RAT_Overhead_Messages_CS0024B AttributeRecord; /* ODY01a *//*GBD01b*/

} c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01 */
typedef struct _c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01 {

	c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01;


/*-A----------------------------------*/
typedef struct _c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents;
#define INIT_c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents))
/*FRK03a*/
void FREE_c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents(c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents' as a variable reference */
#define VAR_c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents' as a pointer */
#define PTR_c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_TransactionID(var) (&var)

/* Access member 'AttributeLength' of type 'c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01_data_AttributeLength(var) var

/* Access member 'AttributeLength' of type 'c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01_data_AttributeLength(var) (&var)

/* Access member 'AttributeRecord' of type 'c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01_data_AttributeRecord(var) var

/* Access member 'AttributeRecord' of type 'c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01_data_AttributeRecord(var) (&var)

/* Access member 'data' of type 'c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01' as a variable reference */
#define VAR_c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01' as a pointer */
#define PTR_c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents' as a variable reference */
#define VAR_c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents' as a pointer */
#define PTR_c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01_data */
typedef struct _c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01_data {

	ED_OCTET AttributeLength; /* ODY01a *//*GBD01b*/
	c_RPD_Inter_RAT_Overhead_Messages_CS0024B AttributeRecord; /* ODY01a *//*GBD01b*/

} c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01 */
typedef struct _c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01 {

	c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01;


/*-A----------------------------------*/
typedef struct _c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents;
#define INIT_c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents))
/*FRK03a*/
void FREE_c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents(c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_TransactionID(var) (&var)

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01_data_AttributeLength(var) var

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01_data_AttributeLength(var) (&var)

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01_data_AttributeRecord(var) var

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01_data_AttributeRecord(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01_data */
typedef struct _c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01_data {

	ED_OCTET AttributeLength; /* ODY01a *//*GBD01b*/
	c_RPD_Inter_RAT_Overhead_Messages_CS0024B AttributeRecord; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01 */
typedef struct _c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01 {

	c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents;
#define INIT_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents(c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_TransactionID(var) (&var)

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01_data_AttributeLength(var) var

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01_data_AttributeLength(var) (&var)

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01_data_AttributeRecord(var) var

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01_data_AttributeRecord(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01_data */
typedef struct _c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01_data {

	ED_OCTET AttributeLength; /* ODY01a *//*GBD01b*/
	c_RPD_Inter_RAT_Overhead_Messages_CS0024B AttributeRecord; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01 */
typedef struct _c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01 {

	c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents;
#define INIT_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents(c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents* sp);

/* Access member 'PageResponseAPersistenceIncluded' of type 'c_RPDCON_IRATQISP_INUSE_Page_contents' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_Page_contents_PageResponseAPersistenceIncluded(var) var

/* Access member 'PageResponseAPersistenceIncluded' of type 'c_RPDCON_IRATQISP_INUSE_Page_contents' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_Page_contents_PageResponseAPersistenceIncluded(var) (&var)

/* Access member 'PageResponseAPersistence' of type 'c_RPDCON_IRATQISP_INUSE_Page_contents' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_Page_contents_PageResponseAPersistence(var) var

/* Access member 'PageResponseAPersistence' of type 'c_RPDCON_IRATQISP_INUSE_Page_contents' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_Page_contents_PageResponseAPersistence(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATQISP_INUSE_Page_contents {

	ED_BOOLEAN PageResponseAPersistenceIncluded; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PageResponseAPersistenceIncluded_Present;
	ED_OCTET PageResponseAPersistence; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PageResponseAPersistence_Present;

}	c_RPDCON_IRATQISP_INUSE_Page_contents;
#define INIT_c_RPDCON_IRATQISP_INUSE_Page_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATQISP_INUSE_Page_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATQISP_INUSE_Page_contents(c_RPDCON_IRATQISP_INUSE_Page_contents* sp);
#define SETPRESENT_c_RPDCON_IRATQISP_INUSE_Page_contents_PageResponseAPersistenceIncluded(sp,present) ((sp)->PageResponseAPersistenceIncluded_Present = present)
#define GETPRESENT_c_RPDCON_IRATQISP_INUSE_Page_contents_PageResponseAPersistenceIncluded(sp) ((sp)->PageResponseAPersistenceIncluded_Present)
#define SETPRESENT_c_RPDCON_IRATQISP_INUSE_Page_contents_PageResponseAPersistence(sp,present) ((sp)->PageResponseAPersistence_Present = present)
#define GETPRESENT_c_RPDCON_IRATQISP_INUSE_Page_contents_PageResponseAPersistence(sp) ((sp)->PageResponseAPersistence_Present)

/* Access member 'TransactionID' of type 'c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_TransactionID(var) (&var)

/* Access member 'RequestReason' of type 'c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_RequestReason(var) var

/* Access member 'RequestReason' of type 'c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_RequestReason(var) (&var)

/* Access member 'PreferredChannelCount' of type 'c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_PreferredChannelCount(var) var

/* Access member 'PreferredChannelCount' of type 'c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_PreferredChannelCount(var) (&var)

/* Access member 'SystemType' of type 'c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel_SystemType(var) var

/* Access member 'SystemType' of type 'c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel_SystemType(var) (&var)

/* Access member 'BandClass' of type 'c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel_BandClass(var) var

/* Access member 'BandClass' of type 'c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel_BandClass(var) (&var)

/* Access member 'ChannelNumber' of type 'c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel_ChannelNumber(var) var

/* Access member 'ChannelNumber' of type 'c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel_ChannelNumber(var) (&var)

/* Access member 'PreferredChannel' of type 'c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel(var) var

/* Access member 'PreferredChannel' of type 'c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01(var) (&var)

/* Access member 'EmergencyIndication' of type 'c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_EmergencyIndication(var) var

/* Access member 'EmergencyIndication' of type 'c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_EmergencyIndication(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel */
typedef struct _c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel {

	ED_OCTET SystemType; /* ODY01a *//*GBD01b*/
	ED_OCTET BandClass; /* ODY01a *//*GBD01b*/
	ED_SHORT ChannelNumber; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data */
typedef struct _c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data {

	c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data_PreferredChannel PreferredChannel;/*GBD01b*/

} c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01 */
typedef struct _c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01 {

	c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	ED_OCTET RequestReason; /* ODY01a *//*GBD01b*/
	ED_OCTET PreferredChannelCount; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01 data01;/*GFB09*//*GBD01b*/
	ED_BOOLEAN EmergencyIndication; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN EmergencyIndication_Present;

}	c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents;
#define INIT_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents(c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents* sp);
#define SETPRESENT_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_EmergencyIndication(sp,present) ((sp)->EmergencyIndication_Present = present)
#define GETPRESENT_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_EmergencyIndication(sp) ((sp)->EmergencyIndication_Present)

/* Access member 'TransactionID' of type 'c_RPDCON_IRATQISP_INUSE_ConnectionDeny_contents' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_ConnectionDeny_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATQISP_INUSE_ConnectionDeny_contents' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_ConnectionDeny_contents_TransactionID(var) (&var)

/* Access member 'DenyReason' of type 'c_RPDCON_IRATQISP_INUSE_ConnectionDeny_contents' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_ConnectionDeny_contents_DenyReason(var) var

/* Access member 'DenyReason' of type 'c_RPDCON_IRATQISP_INUSE_ConnectionDeny_contents' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_ConnectionDeny_contents_DenyReason(var) (&var)

/* Access member 'Reserved' of type 'c_RPDCON_IRATQISP_INUSE_ConnectionDeny_contents' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_ConnectionDeny_contents_Reserved(var) var

/* Access member 'Reserved' of type 'c_RPDCON_IRATQISP_INUSE_ConnectionDeny_contents' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_ConnectionDeny_contents_Reserved(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATQISP_INUSE_ConnectionDeny_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	ED_OCTET DenyReason; /* ODY01a *//*GBD01b*/
	ED_OCTET Reserved; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATQISP_INUSE_ConnectionDeny_contents;
#define INIT_c_RPDCON_IRATQISP_INUSE_ConnectionDeny_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATQISP_INUSE_ConnectionDeny_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATQISP_INUSE_ConnectionDeny_contents(c_RPDCON_IRATQISP_INUSE_ConnectionDeny_contents* sp);

/* Access member 'ConfigurationChange' of type 'c_RPDCON_IRATQISP_INUSE_QuickPage_contents' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_QuickPage_contents_ConfigurationChange(var) var

/* Access member 'ConfigurationChange' of type 'c_RPDCON_IRATQISP_INUSE_QuickPage_contents' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_QuickPage_contents_ConfigurationChange(var) (&var)

/* Access member 'QuickPIPerGroupCountMinusOne' of type 'c_RPDCON_IRATQISP_INUSE_QuickPage_contents' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_QuickPage_contents_QuickPIPerGroupCountMinusOne(var) var

/* Access member 'QuickPIPerGroupCountMinusOne' of type 'c_RPDCON_IRATQISP_INUSE_QuickPage_contents' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_QuickPage_contents_QuickPIPerGroupCountMinusOne(var) (&var)

/* Access member 'QuickPageIndicator' of type 'c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01_data_QuickPageIndicator(var) var

/* Access member 'QuickPageIndicator' of type 'c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01_data_QuickPageIndicator(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATQISP_INUSE_QuickPage_contents' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATQISP_INUSE_QuickPage_contents' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01_data */
typedef struct _c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01_data {

	ED_BOOLEAN QuickPageIndicator; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01 */
typedef struct _c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01 {

	c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATQISP_INUSE_QuickPage_contents {

	ED_OCTET ConfigurationChange; /* ODY01a *//*GBD01b*/
	ED_OCTET QuickPIPerGroupCountMinusOne; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPDCON_IRATQISP_INUSE_QuickPage_contents;
#define INIT_c_RPDCON_IRATQISP_INUSE_QuickPage_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATQISP_INUSE_QuickPage_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATQISP_INUSE_QuickPage_contents(c_RPDCON_IRATQISP_INUSE_QuickPage_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_TransactionID(var) (&var)

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01_data_AttributeLength(var) var

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01_data_AttributeLength(var) (&var)

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01_data_AttributeRecord(var) var

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01_data_AttributeRecord(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01_data */
typedef struct _c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01_data {

	ED_OCTET AttributeLength; /* ODY01a *//*GBD01b*/
	c_RPD_Inter_RAT_Overhead_Messages_CS0024B AttributeRecord; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01 */
typedef struct _c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01 {

	c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents;
#define INIT_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents(c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept_contents' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept_contents' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept_contents;
#define INIT_c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept_contents(c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject_contents' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject_contents' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject_contents;
#define INIT_c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject_contents(c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_TransactionID(var) (&var)

/* Access member 'AttributeLength' of type 'c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01_data_AttributeLength(var) var

/* Access member 'AttributeLength' of type 'c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01_data_AttributeLength(var) (&var)

/* Access member 'AttributeRecord' of type 'c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01_data_AttributeRecord(var) var

/* Access member 'AttributeRecord' of type 'c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01_data_AttributeRecord(var) (&var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01_data */
typedef struct _c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01_data {

	ED_OCTET AttributeLength; /* ODY01a *//*GBD01b*/
	c_RPD_Inter_RAT_Overhead_Messages_CS0024B AttributeRecord; /* ODY01a *//*GBD01b*/

} c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01 */
typedef struct _c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01 {

	c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01;


/*-A----------------------------------*/
typedef struct _c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents;
#define INIT_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents))
/*FRK03a*/
void FREE_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents(c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_TransactionID(var) (&var)

/* Access member 'AttributeLength' of type 'c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01_data_AttributeLength(var) var

/* Access member 'AttributeLength' of type 'c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01_data_AttributeLength(var) (&var)

/* Access member 'AttributeRecord' of type 'c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01_data_AttributeRecord(var) var

/* Access member 'AttributeRecord' of type 'c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01_data_AttributeRecord(var) (&var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01_data */
typedef struct _c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01_data {

	ED_OCTET AttributeLength; /* ODY01a *//*GBD01b*/
	c_RPD_Inter_RAT_Overhead_Messages_CS0024B AttributeRecord; /* ODY01a *//*GBD01b*/

} c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01 */
typedef struct _c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01 {

	c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01;


/*-A----------------------------------*/
typedef struct _c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents;
#define INIT_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents))
/*FRK03a*/
void FREE_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents(c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents* sp);

/* Access member 'MessageSequence' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_MessageSequence(var) var

/* Access member 'MessageSequence' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_MessageSequence(var) (&var)

/* Access member 'ReferencePilotPN' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotPN(var) var

/* Access member 'ReferencePilotPN' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotPN(var) (&var)

/* Access member 'ReferencePilotStrength' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotStrength(var) var

/* Access member 'ReferencePilotStrength' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotStrength(var) (&var)

/* Access member 'ReferenceKeep' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferenceKeep(var) var

/* Access member 'ReferenceKeep' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferenceKeep(var) (&var)

/* Access member 'NumPilots' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_NumPilots(var) var

/* Access member 'NumPilots' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_NumPilots(var) (&var)

/* Access member 'PilotPNPhase' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_PilotPNPhase(var) var

/* Access member 'PilotPNPhase' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_PilotPNPhase(var) (&var)

/* Access member 'ChannelIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_ChannelIncluded(var) var

/* Access member 'ChannelIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_ChannelIncluded(var) (&var)

/* Access member 'SystemType' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel_SystemType(var) var

/* Access member 'SystemType' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel_SystemType(var) (&var)

/* Access member 'BandClass' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel_BandClass(var) var

/* Access member 'BandClass' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel_BandClass(var) (&var)

/* Access member 'ChannelNumber' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel_ChannelNumber(var) var

/* Access member 'ChannelNumber' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel_ChannelNumber(var) (&var)

/* Access member 'Channel' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel(var) (*var)

/* Access member 'Channel' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel(var) var

/* Access member 'PilotStrength' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_PilotStrength(var) var

/* Access member 'PilotStrength' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_PilotStrength(var) (&var)

/* Access member 'Keep' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_Keep(var) var

/* Access member 'Keep' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_Keep(var) (&var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01(var) (&var)

/* Access member 'ATTotalPilotTransmissionIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ATTotalPilotTransmissionIncluded(var) var

/* Access member 'ATTotalPilotTransmissionIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ATTotalPilotTransmissionIncluded(var) (&var)

/* Access member 'ATTotalPilotTransmission' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ATTotalPilotTransmission(var) var

/* Access member 'ATTotalPilotTransmission' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ATTotalPilotTransmission(var) (&var)

/* Access member 'ReferencePilotChannelIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannelIncluded(var) var

/* Access member 'ReferencePilotChannelIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannelIncluded(var) (&var)

/* Access member 'SystemType' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel_SystemType(var) var

/* Access member 'SystemType' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel_SystemType(var) (&var)

/* Access member 'BandClass' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel_BandClass(var) var

/* Access member 'BandClass' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel_BandClass(var) (&var)

/* Access member 'ChannelNumber' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel_ChannelNumber(var) var

/* Access member 'ChannelNumber' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel_ChannelNumber(var) (&var)

/* Access member 'ReferencePilotChannel' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel(var) (*var)

/* Access member 'ReferencePilotChannel' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel(var) var

/* Access member 'ReferencePilotArrivalIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotArrivalIncluded(var) var

/* Access member 'ReferencePilotArrivalIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotArrivalIncluded(var) (&var)

/* Access member 'ReferencePilotArrival' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotArrival(var) var

/* Access member 'ReferencePilotArrival' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotArrival(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel {

	ED_OCTET SystemType; /* ODY01a *//*GBD01b*/
	ED_OCTET BandClass; /* ODY01a *//*GBD01b*/
	ED_SHORT ChannelNumber; /* ODY01a *//*GBD01b*/

} c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data {

	ED_SHORT PilotPNPhase; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ChannelIncluded; /* ODY01a *//*GBD01b*/
	c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel *Channel; /* ODY03 <> *//*GBD01b*/
	ED_BOOLEAN Channel_Present;
	ED_OCTET PilotStrength; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Keep; /* ODY01a *//*GBD01b*/

} c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01 */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01 {

	c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel {

	ED_OCTET SystemType; /* ODY01a *//*GBD01b*/
	ED_OCTET BandClass; /* ODY01a *//*GBD01b*/
	ED_SHORT ChannelNumber; /* ODY01a *//*GBD01b*/

} c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel;


/*-A----------------------------------*/
typedef struct _c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents {

	ED_OCTET MessageSequence; /* ODY01a *//*GBD01b*/
	ED_SHORT ReferencePilotPN; /* ODY01a *//*GBD01b*/
	ED_OCTET ReferencePilotStrength; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ReferenceKeep; /* ODY01a *//*GBD01b*/
	ED_OCTET NumPilots; /* ODY01a *//*GBD01b*/
	c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01 data01;/*GFB09*//*GBD01b*/
	ED_BOOLEAN ATTotalPilotTransmissionIncluded; /* ODY01a *//*GBD01b*/
	ED_OCTET ATTotalPilotTransmission; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ATTotalPilotTransmission_Present;
	ED_BOOLEAN ReferencePilotChannelIncluded; /* ODY01a *//*GBD01b*/
	c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel *ReferencePilotChannel; /* ODY03 <> *//*GBD01b*/
	ED_BOOLEAN ReferencePilotChannel_Present;
	ED_BOOLEAN ReferencePilotArrivalIncluded; /* ODY01a *//*GBD01b*/
	ED_SHORT ReferencePilotArrival; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ReferencePilotArrival_Present;

}	c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents;
#define INIT_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents))
/*FRK03a*/
void FREE_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents(c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents* sp);
#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ATTotalPilotTransmission(sp,present) ((sp)->ATTotalPilotTransmission_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ATTotalPilotTransmission(sp) ((sp)->ATTotalPilotTransmission_Present)
void SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel (c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents* sp, ED_BOOLEAN present);
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotChannel(sp) ((sp)->ReferencePilotChannel_Present)
#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotArrival(sp,present) ((sp)->ReferencePilotArrival_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_ReferencePilotArrival(sp) ((sp)->ReferencePilotArrival_Present)

/* Access member 'MessageSequence' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_MessageSequence(var) var

/* Access member 'MessageSequence' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_MessageSequence(var) (&var)

/* Access member 'DSCChannelGainBase' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_DSCChannelGainBase(var) var

/* Access member 'DSCChannelGainBase' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_DSCChannelGainBase(var) (&var)

/* Access member 'FrameOffset' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_FrameOffset(var) var

/* Access member 'FrameOffset' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_FrameOffset(var) (&var)

/* Access member 'NumSectors' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_NumSectors(var) var

/* Access member 'NumSectors' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_NumSectors(var) (&var)

/* Access member 'NumSubActiveSets' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_NumSubActiveSets(var) var

/* Access member 'NumSubActiveSets' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_NumSubActiveSets(var) (&var)

/* Access member 'AssignedChannelIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_AssignedChannelIncluded(var) var

/* Access member 'AssignedChannelIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_AssignedChannelIncluded(var) (&var)

/* Access member 'SchedulerTagIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_SchedulerTagIncluded(var) var

/* Access member 'SchedulerTagIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_SchedulerTagIncluded(var) (&var)

/* Access member 'FeedbackMultiplexingEnabled' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_FeedbackMultiplexingEnabled(var) var

/* Access member 'FeedbackMultiplexingEnabled' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_FeedbackMultiplexingEnabled(var) (&var)

/* Access member 'RAChannelGain' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data_RAChannelGain(var) var

/* Access member 'RAChannelGain' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data_RAChannelGain(var) (&var)

/* Access member 'PilotPN' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data_PilotPN(var) var

/* Access member 'PilotPN' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data_PilotPN(var) (&var)

/* Access member 'DRCCover' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data_DRCCover(var) var

/* Access member 'DRCCover' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data_DRCCover(var) (&var)

/* Access member 'SofterHandoff' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data_SofterHandoff(var) var

/* Access member 'SofterHandoff' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data_SofterHandoff(var) (&var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01(var) (&var)

/* Access member 'DSC' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data_DSC(var) var

/* Access member 'DSC' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data_DSC(var) (&var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data(var) var

/* Access member 'data02' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02(var) var

/* Access member 'data02' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02(var) (&var)

/* Access member 'NumFwdChannelsThisSubActiveSet' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_NumFwdChannelsThisSubActiveSet(var) var

/* Access member 'NumFwdChannelsThisSubActiveSet' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_NumFwdChannelsThisSubActiveSet(var) (&var)

/* Access member 'SystemType' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data_AssignedChannel' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data_AssignedChannel_SystemType(var) var

/* Access member 'SystemType' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data_AssignedChannel' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data_AssignedChannel_SystemType(var) (&var)

/* Access member 'BandClass' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data_AssignedChannel' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data_AssignedChannel_BandClass(var) var

/* Access member 'BandClass' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data_AssignedChannel' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data_AssignedChannel_BandClass(var) (&var)

/* Access member 'ChannelNumber' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data_AssignedChannel' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data_AssignedChannel_ChannelNumber(var) var

/* Access member 'ChannelNumber' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data_AssignedChannel' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data_AssignedChannel_ChannelNumber(var) (&var)

/* Access member 'AssignedChannel' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data_AssignedChannel(var) (*var)

/* Access member 'AssignedChannel' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data_AssignedChannel(var) var

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data(var) var

/* Access member 'data04' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04(var) var

/* Access member 'data04' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04(var) (&var)

/* Access member 'FeedbackEnabled' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_FeedbackEnabled(var) var

/* Access member 'FeedbackEnabled' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_FeedbackEnabled(var) (&var)

/* Access member 'FeedbackMultiplexingIndex' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_FeedbackMultiplexingIndex(var) var

/* Access member 'FeedbackMultiplexingIndex' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_FeedbackMultiplexingIndex(var) (&var)

/* Access member 'FeedbackReverseChannelIndex' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_FeedbackReverseChannelIndex(var) var

/* Access member 'FeedbackReverseChannelIndex' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_FeedbackReverseChannelIndex(var) (&var)

/* Access member 'SubActiveSetCarriesControlChannel' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_SubActiveSetCarriesControlChannel(var) var

/* Access member 'SubActiveSetCarriesControlChannel' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_SubActiveSetCarriesControlChannel(var) (&var)

/* Access member 'ThisSubActiveSetNotReportable' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_ThisSubActiveSetNotReportable(var) var

/* Access member 'ThisSubActiveSetNotReportable' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_ThisSubActiveSetNotReportable(var) (&var)

/* Access member 'DSCForThisSubActiveSetEnabled' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_DSCForThisSubActiveSetEnabled(var) var

/* Access member 'DSCForThisSubActiveSetEnabled' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_DSCForThisSubActiveSetEnabled(var) (&var)

/* Access member 'Next3FieldsSameAsBefore' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_Next3FieldsSameAsBefore(var) var

/* Access member 'Next3FieldsSameAsBefore' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_Next3FieldsSameAsBefore(var) (&var)

/* Access member 'DRCLength' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_DRCLength(var) var

/* Access member 'DRCLength' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_DRCLength(var) (&var)

/* Access member 'DRCChannelGainBase' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_DRCChannelGainBase(var) var

/* Access member 'DRCChannelGainBase' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_DRCChannelGainBase(var) (&var)

/* Access member 'ACKChannelGain' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_ACKChannelGain(var) var

/* Access member 'ACKChannelGain' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_ACKChannelGain(var) (&var)

/* Access member 'NumReverseChannelsIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_NumReverseChannelsIncluded(var) var

/* Access member 'NumReverseChannelsIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_NumReverseChannelsIncluded(var) (&var)

/* Access member 'NumReverseChannels' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_NumReverseChannels(var) var

/* Access member 'NumReverseChannels' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_NumReverseChannels(var) (&var)

/* Access member 'ReverseChannelConfiguration' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data_ReverseChannelConfiguration(var) var

/* Access member 'ReverseChannelConfiguration' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data_ReverseChannelConfiguration(var) (&var)

/* Access member 'ReverseBandClass' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data_ReverseBandClass(var) var

/* Access member 'ReverseBandClass' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data_ReverseBandClass(var) (&var)

/* Access member 'ReverseChannelNumber' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data_ReverseChannelNumber(var) var

/* Access member 'ReverseChannelNumber' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data_ReverseChannelNumber(var) (&var)

/* Access member 'ReverseChannelDroppingRank' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data_ReverseChannelDroppingRank(var) var

/* Access member 'ReverseChannelDroppingRank' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data_ReverseChannelDroppingRank(var) (&var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data(var) var

/* Access member 'data05' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05(var) var

/* Access member 'data05' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05(var) (&var)

/* Access member 'PilotInThisSectorIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_PilotInThisSectorIncluded(var) var

/* Access member 'PilotInThisSectorIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_PilotInThisSectorIncluded(var) (&var)

/* Access member 'ForwardChannelIndexThisPilot' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_ForwardChannelIndexThisPilot(var) var

/* Access member 'ForwardChannelIndexThisPilot' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_ForwardChannelIndexThisPilot(var) (&var)

/* Access member 'PilotGroupID' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_PilotGroupID(var) var

/* Access member 'PilotGroupID' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_PilotGroupID(var) (&var)

/* Access member 'NumUniqueForwardTrafficMACIndices' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_NumUniqueForwardTrafficMACIndices(var) var

/* Access member 'NumUniqueForwardTrafficMACIndices' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_NumUniqueForwardTrafficMACIndices(var) (&var)

/* Access member 'SchedulerTag' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_SchedulerTag(var) var

/* Access member 'SchedulerTag' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_SchedulerTag(var) (&var)

/* Access member 'AuxDRCCoverIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_AuxDRCCoverIncluded(var) var

/* Access member 'AuxDRCCoverIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_AuxDRCCoverIncluded(var) (&var)

/* Access member 'AuxDRCCover' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_AuxDRCCover(var) var

/* Access member 'AuxDRCCover' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_AuxDRCCover(var) (&var)

/* Access member 'ForwardTrafficMACIndexPerInterlaceEnabled' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_ForwardTrafficMACIndexPerInterlaceEnabled(var) var

/* Access member 'ForwardTrafficMACIndexPerInterlaceEnabled' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_ForwardTrafficMACIndexPerInterlaceEnabled(var) (&var)

/* Access member 'ForwardTrafficMACIndex' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07_data_ForwardTrafficMACIndex(var) var

/* Access member 'ForwardTrafficMACIndex' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07_data_ForwardTrafficMACIndex(var) (&var)

/* Access member 'AssignedInterlaces' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07_data_AssignedInterlaces(var) var

/* Access member 'AssignedInterlaces' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07_data_AssignedInterlaces(var) (&var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07_data(var) var

/* Access member 'data07' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07(var) var

/* Access member 'data07' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07(var) (&var)

/* Access member 'ReverseLinkMACIndex' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data_ReverseLinkMACIndex(var) var

/* Access member 'ReverseLinkMACIndex' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data_ReverseLinkMACIndex(var) (&var)

/* Access member 'RABMACIndex' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data_RABMACIndex(var) var

/* Access member 'RABMACIndex' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data_RABMACIndex(var) (&var)

/* Access member 'DeltaT2P' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data_DeltaT2P(var) var

/* Access member 'DeltaT2P' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data_DeltaT2P(var) (&var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data(var) var

/* Access member 'data08' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08(var) var

/* Access member 'data08' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08(var) (&var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data(var) var

/* Access member 'data06' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06(var) var

/* Access member 'data06' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06(var) (&var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data(var) var

/* Access member 'data03' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03(var) var

/* Access member 'data03' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data {

	ED_OCTET RAChannelGain; /* ODY01a *//*GBD01b*/
	ED_SHORT PilotPN; /* ODY01a *//*GBD01b*/
	ED_OCTET DRCCover; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SofterHandoff; /* ODY01a *//*GBD01b*/

} c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01 */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01 {

	c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data {

	ED_OCTET DSC; /* ODY01a *//*GBD01b*/

} c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02 */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02 {

	c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data_AssignedChannel */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data_AssignedChannel {

	ED_OCTET SystemType; /* ODY01a *//*GBD01b*/
	ED_OCTET BandClass; /* ODY01a *//*GBD01b*/
	ED_SHORT ChannelNumber; /* ODY01a *//*GBD01b*/

} c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data_AssignedChannel;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data {

	c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data_AssignedChannel *AssignedChannel; /* ODY03 <> *//*GBD01b*/
	ED_BOOLEAN AssignedChannel_Present;

} c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04 */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04 {

	c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data {

	ED_OCTET ReverseChannelConfiguration; /* ODY01a *//*GBD01b*/
	ED_OCTET ReverseBandClass; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ReverseBandClass_Present;
	ED_SHORT ReverseChannelNumber; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ReverseChannelNumber_Present;
	ED_OCTET ReverseChannelDroppingRank; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ReverseChannelDroppingRank_Present;

} c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05 */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05 {

	c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07_data */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07_data {

	ED_SHORT ForwardTrafficMACIndex; /* ODY01a *//*GBD01b*/
	ED_OCTET AssignedInterlaces; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN AssignedInterlaces_Present;

} c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07 */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07 {

	c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data {

	ED_SHORT ReverseLinkMACIndex; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ReverseLinkMACIndex_Present;
	ED_OCTET RABMACIndex; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN RABMACIndex_Present;
	ED_OCTET DeltaT2P; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN DeltaT2P_Present;

} c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08 */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08 {

	c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data {

	ED_BOOLEAN PilotInThisSectorIncluded; /* ODY01a *//*GBD01b*/
	ED_OCTET ForwardChannelIndexThisPilot; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ForwardChannelIndexThisPilot_Present;
	ED_OCTET PilotGroupID; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PilotGroupID_Present;
	ED_OCTET NumUniqueForwardTrafficMACIndices; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN NumUniqueForwardTrafficMACIndices_Present;
	ED_OCTET SchedulerTag; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SchedulerTag_Present;
	ED_BOOLEAN AuxDRCCoverIncluded; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN AuxDRCCoverIncluded_Present;
	ED_OCTET AuxDRCCover; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN AuxDRCCover_Present;
	ED_BOOLEAN ForwardTrafficMACIndexPerInterlaceEnabled; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ForwardTrafficMACIndexPerInterlaceEnabled_Present;
	c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07 data07;/*GFB09*//*GBD01b*/
	c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08 data08;/*GFB09*//*GBD01b*/

} c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06 */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06 {

	c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data {

	ED_OCTET NumFwdChannelsThisSubActiveSet; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN NumFwdChannelsThisSubActiveSet_Present;
	c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04 data04;/*GFB09*//*GBD01b*/
	ED_BOOLEAN FeedbackEnabled; /* ODY01a *//*GBD01b*/
	ED_SHORT FeedbackMultiplexingIndex; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN FeedbackMultiplexingIndex_Present;
	ED_OCTET FeedbackReverseChannelIndex; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN FeedbackReverseChannelIndex_Present;
	ED_BOOLEAN SubActiveSetCarriesControlChannel; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ThisSubActiveSetNotReportable; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN DSCForThisSubActiveSetEnabled; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN DSCForThisSubActiveSetEnabled_Present;
	ED_BOOLEAN Next3FieldsSameAsBefore; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Next3FieldsSameAsBefore_Present;
	ED_OCTET DRCLength; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN DRCLength_Present;
	ED_OCTET DRCChannelGainBase; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN DRCChannelGainBase_Present;
	ED_OCTET ACKChannelGain; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ACKChannelGain_Present;
	ED_BOOLEAN NumReverseChannelsIncluded; /* ODY01a *//*GBD01b*/
	ED_OCTET NumReverseChannels; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN NumReverseChannels_Present;
	c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05 data05;/*GFB09*//*GBD01b*/
	c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06 data06;/*GFB09*//*GBD01b*/

} c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03 */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03 {

	c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03;


/*-A----------------------------------*/
typedef struct _c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents {

	ED_OCTET MessageSequence; /* ODY01a *//*GBD01b*/
	ED_OCTET DSCChannelGainBase; /* ODY01a *//*GBD01b*/
	ED_OCTET FrameOffset; /* ODY01a *//*GBD01b*/
	ED_OCTET NumSectors; /* ODY01a *//*GBD01b*/
	ED_OCTET NumSubActiveSets; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN AssignedChannelIncluded; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SchedulerTagIncluded; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN FeedbackMultiplexingEnabled; /* ODY01a *//*GBD01b*/
	c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01 data01;/*GFB09*//*GBD01b*/
	c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02 data02;/*GFB09*//*GBD01b*/
	c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03 data03;/*GFB09*//*GBD01b*/

}	c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents;
#define INIT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents))
/*FRK03a*/
void FREE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents(c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents* sp);

/* Access member 'MessageSequence' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete_contents_MessageSequence(var) var

/* Access member 'MessageSequence' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete_contents_MessageSequence(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete_contents {

	ED_OCTET MessageSequence; /* ODY01a *//*GBD01b*/

}	c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete_contents;
#define INIT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete_contents))
/*FRK03a*/
void FREE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete_contents(c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete_contents* sp);

/* Access member 'Count' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_Count(var) var

/* Access member 'Count' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_Count(var) (&var)

/* Access member 'PilotPN' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01_data_PilotPN(var) var

/* Access member 'PilotPN' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01_data_PilotPN(var) (&var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01(var) (&var)

/* Access member 'ChannelIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data_ChannelIncluded(var) var

/* Access member 'ChannelIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data_ChannelIncluded(var) (&var)

/* Access member 'SystemType' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data_Channel' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data_Channel_SystemType(var) var

/* Access member 'SystemType' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data_Channel' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data_Channel_SystemType(var) (&var)

/* Access member 'BandClass' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data_Channel' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data_Channel_BandClass(var) var

/* Access member 'BandClass' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data_Channel' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data_Channel_BandClass(var) (&var)

/* Access member 'ChannelNumber' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data_Channel' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data_Channel_ChannelNumber(var) var

/* Access member 'ChannelNumber' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data_Channel' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data_Channel_ChannelNumber(var) (&var)

/* Access member 'Channel' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data_Channel(var) (*var)

/* Access member 'Channel' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data_Channel(var) var

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data(var) var

/* Access member 'data02' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02(var) var

/* Access member 'data02' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02(var) (&var)

/* Access member 'SearchWindowSizeIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_SearchWindowSizeIncluded(var) var

/* Access member 'SearchWindowSizeIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_SearchWindowSizeIncluded(var) (&var)

/* Access member 'SearchWindowSize' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03_data_SearchWindowSize(var) var

/* Access member 'SearchWindowSize' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03_data_SearchWindowSize(var) (&var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03_data(var) var

/* Access member 'data03' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03(var) var

/* Access member 'data03' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03(var) (&var)

/* Access member 'SearchWindowOffsetIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_SearchWindowOffsetIncluded(var) var

/* Access member 'SearchWindowOffsetIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_SearchWindowOffsetIncluded(var) (&var)

/* Access member 'SearchWindowOffset' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04_data_SearchWindowOffset(var) var

/* Access member 'SearchWindowOffset' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04_data_SearchWindowOffset(var) (&var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04_data(var) var

/* Access member 'data04' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04(var) var

/* Access member 'data04' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04(var) (&var)

/* Access member 'FPDCHSupportedIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_FPDCHSupportedIncluded(var) var

/* Access member 'FPDCHSupportedIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_FPDCHSupportedIncluded(var) (&var)

/* Access member 'FPDCHSupported' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05_data_FPDCHSupported(var) var

/* Access member 'FPDCHSupported' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05_data_FPDCHSupported(var) (&var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05_data(var) var

/* Access member 'data05' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05(var) var

/* Access member 'data05' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05(var) (&var)

/* Access member 'PilotGroupIDIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06_data_PilotGroupIDIncluded(var) var

/* Access member 'PilotGroupIDIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06_data_PilotGroupIDIncluded(var) (&var)

/* Access member 'PilotGroupID' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06_data_PilotGroupID(var) var

/* Access member 'PilotGroupID' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06_data_PilotGroupID(var) (&var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06_data(var) var

/* Access member 'data06' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06(var) var

/* Access member 'data06' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01_data */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01_data {

	ED_SHORT PilotPN; /* ODY01a *//*GBD01b*/

} c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01 */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01 {

	c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data_Channel */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data_Channel {

	ED_OCTET SystemType; /* ODY01a *//*GBD01b*/
	ED_OCTET BandClass; /* ODY01a *//*GBD01b*/
	ED_SHORT ChannelNumber; /* ODY01a *//*GBD01b*/

} c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data_Channel;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data {

	ED_BOOLEAN ChannelIncluded; /* ODY01a *//*GBD01b*/
	c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data_Channel *Channel; /* ODY03 <> *//*GBD01b*/
	ED_BOOLEAN Channel_Present;

} c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02 */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02 {

	c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03_data */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03_data {

	ED_OCTET SearchWindowSize; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SearchWindowSize_Present;

} c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03 */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03 {

	c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04_data */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04_data {

	ED_OCTET SearchWindowOffset; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SearchWindowOffset_Present;

} c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04 */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04 {

	c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05_data */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05_data {

	ED_BOOLEAN FPDCHSupported; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN FPDCHSupported_Present;

} c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05 */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05 {

	c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06_data */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06_data {

	ED_BOOLEAN PilotGroupIDIncluded; /* ODY01a *//*GBD01b*/
	ED_OCTET PilotGroupID; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PilotGroupID_Present;

} c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06 */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06 {

	c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06;


/*-A----------------------------------*/
typedef struct _c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents {

	ED_OCTET Count; /* ODY01a *//*GBD01b*/
	c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01 data01;/*GFB09*//*GBD01b*/
	c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02 data02;/*GFB09*//*GBD01b*/
	ED_BOOLEAN SearchWindowSizeIncluded; /* ODY01a *//*GBD01b*/
	c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03 data03;/*GFB09*//*GBD01b*/
	ED_BOOLEAN SearchWindowOffsetIncluded; /* ODY01a *//*GBD01b*/
	c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04 data04;/*GFB09*//*GBD01b*/
	ED_BOOLEAN FPDCHSupportedIncluded; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN FPDCHSupportedIncluded_Present;
	c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05 data05;/*GFB09*//*GBD01b*/
	c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06 data06;/*GFB09*//*GBD01b*/

}	c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents;
#define INIT_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents))
/*FRK03a*/
void FREE_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents(c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents* sp);
#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_FPDCHSupportedIncluded(sp,present) ((sp)->FPDCHSupportedIncluded_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_FPDCHSupportedIncluded(sp) ((sp)->FPDCHSupportedIncluded_Present)

/* Access member 'ChannelIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_ChannelIncluded(var) var

/* Access member 'ChannelIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_ChannelIncluded(var) (&var)

/* Access member 'SystemType' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_Channel' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_Channel_SystemType(var) var

/* Access member 'SystemType' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_Channel' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_Channel_SystemType(var) (&var)

/* Access member 'BandClass' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_Channel' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_Channel_BandClass(var) var

/* Access member 'BandClass' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_Channel' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_Channel_BandClass(var) (&var)

/* Access member 'ChannelNumber' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_Channel' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_Channel_ChannelNumber(var) var

/* Access member 'ChannelNumber' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_Channel' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_Channel_ChannelNumber(var) (&var)

/* Access member 'Channel' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_Channel(var) (*var)

/* Access member 'Channel' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_Channel(var) var

/* Access member 'SectorCount' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_SectorCount(var) var

/* Access member 'SectorCount' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_SectorCount(var) (&var)

/* Access member 'SectorPilotPN' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data_SectorPilotPN(var) var

/* Access member 'SectorPilotPN' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data_SectorPilotPN(var) (&var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01(var) (&var)

/* Access member 'SectorSearchWindowSizeIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_SectorSearchWindowSizeIncluded(var) var

/* Access member 'SectorSearchWindowSizeIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_SectorSearchWindowSizeIncluded(var) (&var)

/* Access member 'SectorSearchWindowSize' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data_SectorSearchWindowSize(var) var

/* Access member 'SectorSearchWindowSize' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data_SectorSearchWindowSize(var) (&var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data(var) var

/* Access member 'data02' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02(var) var

/* Access member 'data02' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02(var) (&var)

/* Access member 'SectorSearchWindowOffsetIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_SectorSearchWindowOffsetIncluded(var) var

/* Access member 'SectorSearchWindowOffsetIncluded' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_SectorSearchWindowOffsetIncluded(var) (&var)

/* Access member 'SectorSearchWindowOffset' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data_SectorSearchWindowOffset(var) var

/* Access member 'SectorSearchWindowOffset' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data_SectorSearchWindowOffset(var) (&var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data(var) var

/* Access member 'data03' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03(var) var

/* Access member 'data03' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_Channel */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_Channel {

	ED_OCTET SystemType; /* ODY01a *//*GBD01b*/
	ED_OCTET BandClass; /* ODY01a *//*GBD01b*/
	ED_SHORT ChannelNumber; /* ODY01a *//*GBD01b*/

} c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_Channel;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data {

	ED_SHORT SectorPilotPN; /* ODY01a *//*GBD01b*/

} c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01 */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01 {

	c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data {

	ED_OCTET SectorSearchWindowSize; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SectorSearchWindowSize_Present;

} c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02 */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02 {

	c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data {

	ED_OCTET SectorSearchWindowOffset; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SectorSearchWindowOffset_Present;

} c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03 */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03 {

	c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03;


/*-A----------------------------------*/
typedef struct _c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents {

	ED_BOOLEAN ChannelIncluded; /* ODY01a *//*GBD01b*/
	c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_Channel *Channel; /* ODY03 <> *//*GBD01b*/
	ED_BOOLEAN Channel_Present;
	ED_OCTET SectorCount; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SectorCount_Present;
	c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01 data01;/*GFB09*//*GBD01b*/
	ED_BOOLEAN SectorSearchWindowSizeIncluded; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SectorSearchWindowSizeIncluded_Present;
	c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02 data02;/*GFB09*//*GBD01b*/
	ED_BOOLEAN SectorSearchWindowOffsetIncluded; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SectorSearchWindowOffsetIncluded_Present;
	c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03 data03;/*GFB09*//*GBD01b*/

}	c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents;
#define INIT_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents))
/*FRK03a*/
void FREE_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents(c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents* sp);
void SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_Channel (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents* sp, ED_BOOLEAN present);
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_Channel(sp) ((sp)->Channel_Present)
#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_SectorCount(sp,present) ((sp)->SectorCount_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_SectorCount(sp) ((sp)->SectorCount_Present)
#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_SectorSearchWindowSizeIncluded(sp,present) ((sp)->SectorSearchWindowSizeIncluded_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_SectorSearchWindowSizeIncluded(sp) ((sp)->SectorSearchWindowSizeIncluded_Present)
#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_SectorSearchWindowOffsetIncluded(sp,present) ((sp)->SectorSearchWindowOffsetIncluded_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_SectorSearchWindowOffsetIncluded(sp) ((sp)->SectorSearchWindowOffsetIncluded_Present)

/* Access member 'TransactionID' of type 'c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_TransactionID(var) (&var)

/* Access member 'AttributeLength' of type 'c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data_AttributeLength(var) var

/* Access member 'AttributeLength' of type 'c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data_AttributeLength(var) (&var)

/* Access member 'AttributeRecord' of type 'c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data_AttributeRecord(var) var

/* Access member 'AttributeRecord' of type 'c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data_AttributeRecord(var) (&var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data {

	ED_OCTET AttributeLength; /* ODY01a *//*GBD01b*/
	c_RPD_Inter_RAT_Overhead_Messages_CS0024B AttributeRecord; /* ODY01a *//*GBD01b*/

} c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01 */
typedef struct _c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01 {

	c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01;


/*-A----------------------------------*/
typedef struct _c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents;
#define INIT_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents))
/*FRK03a*/
void FREE_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents(c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept_contents;
#define INIT_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept_contents))
/*FRK03a*/
void FREE_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept_contents(c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject_contents' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject_contents' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject_contents;
#define INIT_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject_contents))
/*FRK03a*/
void FREE_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject_contents(c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_TransactionID(var) (&var)

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01_data_AttributeLength(var) var

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01_data_AttributeLength(var) (&var)

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01_data_AttributeRecord(var) var

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01_data_AttributeRecord(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01_data */
typedef struct _c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01_data {

	ED_OCTET AttributeLength; /* ODY01a *//*GBD01b*/
	c_RPD_Inter_RAT_Overhead_Messages_CS0024B AttributeRecord; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01 */
typedef struct _c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01 {

	c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents;
#define INIT_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents(c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents* sp);

/* Access member 'TransactionID' of type 'c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_TransactionID(var) (&var)

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01_data_AttributeLength(var) var

/* Access member 'AttributeLength' of type 'c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01_data_AttributeLength(var) (&var)

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01_data_AttributeRecord(var) var

/* Access member 'AttributeRecord' of type 'c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01_data_AttributeRecord(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01_data */
typedef struct _c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01_data {

	ED_OCTET AttributeLength; /* ODY01a *//*GBD01b*/
	c_RPD_Inter_RAT_Overhead_Messages_CS0024B AttributeRecord; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01 */
typedef struct _c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01 {

	c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents;
#define INIT_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents(c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents* sp);

/* Access member 'ColorCode' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_ColorCode(var) var

/* Access member 'ColorCode' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_ColorCode(var) (&var)

/* Access member 'SectorID24' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_SectorID24(var) var

/* Access member 'SectorID24' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_SectorID24(var) (&var)

/* Access member 'SectorSignature' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_SectorSignature(var) var

/* Access member 'SectorSignature' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_SectorSignature(var) (&var)

/* Access member 'AccessSignature' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_AccessSignature(var) var

/* Access member 'AccessSignature' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_AccessSignature(var) (&var)

/* Access member 'Redirect' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_Redirect(var) var

/* Access member 'Redirect' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_Redirect(var) (&var)

/* Access member 'RPCCount63To0' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_RPCCount63To0(var) var

/* Access member 'RPCCount63To0' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_RPCCount63To0(var) (&var)

/* Access member 'ForwardTrafficValid63To0' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01_data_ForwardTrafficValid63To0(var) var

/* Access member 'ForwardTrafficValid63To0' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01_data_ForwardTrafficValid63To0(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01(var) (&var)

/* Access member 'RPCCount127To64Included' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_RPCCount127To64Included(var) var

/* Access member 'RPCCount127To64Included' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_RPCCount127To64Included(var) (&var)

/* Access member 'RPCCount127To64' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_RPCCount127To64(var) var

/* Access member 'RPCCount127To64' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_RPCCount127To64(var) (&var)

/* Access member 'ForwardTrafficValid127To64' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02_data_ForwardTrafficValid127To64(var) var

/* Access member 'ForwardTrafficValid127To64' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02_data_ForwardTrafficValid127To64(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02_data(var) var

/* Access member 'data02' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02(var) var

/* Access member 'data02' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02(var) (&var)

/* Access member 'RPCCount130To383Included' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_RPCCount130To383Included(var) var

/* Access member 'RPCCount130To383Included' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_RPCCount130To383Included(var) (&var)

/* Access member 'RPCCount130To383' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_RPCCount130To383(var) var

/* Access member 'RPCCount130To383' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_RPCCount130To383(var) (&var)

/* Access member 'ForwardTrafficValid130To383' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03_data_ForwardTrafficValid130To383(var) var

/* Access member 'ForwardTrafficValid130To383' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03_data_ForwardTrafficValid130To383(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03_data(var) var

/* Access member 'data03' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03(var) var

/* Access member 'data03' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03(var) (&var)

/* Access member 'OtherRATAvailable' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_OtherRATAvailable(var) var

/* Access member 'OtherRATAvailable' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_OtherRATAvailable(var) (&var)

/* Access member 'OtherRATTXCycle' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_OtherRATTXCycle(var) var

/* Access member 'OtherRATTXCycle' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_OtherRATTXCycle(var) (&var)

/* Access member 'OtherRATSignature' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_OtherRATSignature(var) var

/* Access member 'OtherRATSignature' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_OtherRATSignature(var) (&var)

/* Access member 'APIDMIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_APIDMIncluded(var) var

/* Access member 'APIDMIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_APIDMIncluded(var) (&var)

/* Access member 'APIDTMIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_APIDTMIncluded(var) var

/* Access member 'APIDTMIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_APIDTMIncluded(var) (&var)

/* Access member 'APPIMIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_APPIMIncluded(var) var

/* Access member 'APPIMIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_APPIMIncluded(var) (&var)

/* Access member 'APPIMTXCycle' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_APPIMTXCycle(var) var

/* Access member 'APPIMTXCycle' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_APPIMTXCycle(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01_data */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01_data {

	ED_BOOLEAN ForwardTrafficValid63To0; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01 */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01 {

	c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02_data */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02_data {

	ED_BOOLEAN ForwardTrafficValid127To64; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ForwardTrafficValid127To64_Present;

} c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02 */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02 {

	c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03_data */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03_data {

	ED_BOOLEAN ForwardTrafficValid130To383; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ForwardTrafficValid130To383_Present;

} c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03 */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03 {

	c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents {

	ED_OCTET ColorCode; /* ODY01a *//*GBD01b*/
	ED_LONG SectorID24; /* ODY01a *//*GBD01b*/
	ED_SHORT SectorSignature; /* ODY01a *//*GBD01b*/
	ED_SHORT AccessSignature; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Redirect; /* ODY01a *//*GBD01b*/
	ED_OCTET RPCCount63To0; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01 data01;/*GFB09*//*GBD01b*/
	ED_BOOLEAN RPCCount127To64Included; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN RPCCount127To64Included_Present;
	ED_OCTET RPCCount127To64; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN RPCCount127To64_Present;
	c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02 data02;/*GFB09*//*GBD01b*/
	ED_BOOLEAN RPCCount130To383Included; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN RPCCount130To383Included_Present;
	ED_OCTET RPCCount130To383; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN RPCCount130To383_Present;
	c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03 data03;/*GFB09*//*GBD01b*/
	ED_BOOLEAN OtherRATAvailable; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN OtherRATAvailable_Present;
	ED_OCTET OtherRATTXCycle; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN OtherRATTXCycle_Present;
	ED_OCTET OtherRATSignature; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN OtherRATSignature_Present;
	ED_BOOLEAN APIDMIncluded; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN APIDMIncluded_Present;
	ED_BOOLEAN APIDTMIncluded; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN APIDTMIncluded_Present;
	ED_BOOLEAN APPIMIncluded; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN APPIMIncluded_Present;
	ED_OCTET APPIMTXCycle; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN APPIMTXCycle_Present;

}	c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents;
#define INIT_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents(c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents* sp);
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_RPCCount127To64Included(sp,present) ((sp)->RPCCount127To64Included_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_RPCCount127To64Included(sp) ((sp)->RPCCount127To64Included_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_RPCCount127To64(sp,present) ((sp)->RPCCount127To64_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_RPCCount127To64(sp) ((sp)->RPCCount127To64_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_RPCCount130To383Included(sp,present) ((sp)->RPCCount130To383Included_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_RPCCount130To383Included(sp) ((sp)->RPCCount130To383Included_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_RPCCount130To383(sp,present) ((sp)->RPCCount130To383_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_RPCCount130To383(sp) ((sp)->RPCCount130To383_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_OtherRATAvailable(sp,present) ((sp)->OtherRATAvailable_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_OtherRATAvailable(sp) ((sp)->OtherRATAvailable_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_OtherRATTXCycle(sp,present) ((sp)->OtherRATTXCycle_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_OtherRATTXCycle(sp) ((sp)->OtherRATTXCycle_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_OtherRATSignature(sp,present) ((sp)->OtherRATSignature_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_OtherRATSignature(sp) ((sp)->OtherRATSignature_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_APIDMIncluded(sp,present) ((sp)->APIDMIncluded_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_APIDMIncluded(sp) ((sp)->APIDMIncluded_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_APIDTMIncluded(sp,present) ((sp)->APIDTMIncluded_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_APIDTMIncluded(sp) ((sp)->APIDTMIncluded_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_APPIMIncluded(sp,present) ((sp)->APPIMIncluded_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_APPIMIncluded(sp) ((sp)->APPIMIncluded_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_APPIMTXCycle(sp,present) ((sp)->APPIMTXCycle_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_APPIMTXCycle(sp) ((sp)->APPIMTXCycle_Present)

/* Access member 'CountryCode' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_CountryCode(var) var

/* Access member 'CountryCode' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_CountryCode(var) (&var)

/* Access member 'SectorID' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_SectorID(var) var

/* Access member 'SectorID' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_SectorID(var) (&var)

/* Access member 'SubnetMask' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_SubnetMask(var) var

/* Access member 'SubnetMask' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_SubnetMask(var) (&var)

/* Access member 'SectorSignature' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_SectorSignature(var) var

/* Access member 'SectorSignature' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_SectorSignature(var) (&var)

/* Access member 'Latitude' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_Latitude(var) var

/* Access member 'Latitude' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_Latitude(var) (&var)

/* Access member 'Longitude' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_Longitude(var) var

/* Access member 'Longitude' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_Longitude(var) (&var)

/* Access member 'RouteUpdateRadiusOverhead' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_RouteUpdateRadiusOverhead(var) var

/* Access member 'RouteUpdateRadiusOverhead' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_RouteUpdateRadiusOverhead(var) (&var)

/* Access member 'LeapSeconds' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_LeapSeconds(var) var

/* Access member 'LeapSeconds' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_LeapSeconds(var) (&var)

/* Access member 'LocalTimeOffset' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_LocalTimeOffset(var) var

/* Access member 'LocalTimeOffset' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_LocalTimeOffset(var) (&var)

/* Access member 'ReverseLinkSilenceDuration' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_ReverseLinkSilenceDuration(var) var

/* Access member 'ReverseLinkSilenceDuration' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_ReverseLinkSilenceDuration(var) (&var)

/* Access member 'ReverseLinkSilencePeriod' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_ReverseLinkSilencePeriod(var) var

/* Access member 'ReverseLinkSilencePeriod' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_ReverseLinkSilencePeriod(var) (&var)

/* Access member 'ChannelCount' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_ChannelCount(var) var

/* Access member 'ChannelCount' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_ChannelCount(var) (&var)

/* Access member 'SystemType' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data_Channel' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data_Channel_SystemType(var) var

/* Access member 'SystemType' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data_Channel' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data_Channel_SystemType(var) (&var)

/* Access member 'BandClass' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data_Channel' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data_Channel_BandClass(var) var

/* Access member 'BandClass' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data_Channel' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data_Channel_BandClass(var) (&var)

/* Access member 'ChannelNumber' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data_Channel' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data_Channel_ChannelNumber(var) var

/* Access member 'ChannelNumber' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data_Channel' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data_Channel_ChannelNumber(var) (&var)

/* Access member 'Channel' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data_Channel(var) var

/* Access member 'Channel' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data_Channel(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01(var) (&var)

/* Access member 'NeighborCount' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_NeighborCount(var) var

/* Access member 'NeighborCount' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_NeighborCount(var) (&var)

/* Access member 'NeighborPilotPN' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02_data_NeighborPilotPN(var) var

/* Access member 'NeighborPilotPN' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02_data_NeighborPilotPN(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02_data(var) var

/* Access member 'data02' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02(var) var

/* Access member 'data02' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02(var) (&var)

/* Access member 'NeighborChannelIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data_NeighborChannelIncluded(var) var

/* Access member 'NeighborChannelIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data_NeighborChannelIncluded(var) (&var)

/* Access member 'SystemType' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data_NeighborChannel' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data_NeighborChannel_SystemType(var) var

/* Access member 'SystemType' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data_NeighborChannel' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data_NeighborChannel_SystemType(var) (&var)

/* Access member 'BandClass' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data_NeighborChannel' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data_NeighborChannel_BandClass(var) var

/* Access member 'BandClass' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data_NeighborChannel' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data_NeighborChannel_BandClass(var) (&var)

/* Access member 'ChannelNumber' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data_NeighborChannel' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data_NeighborChannel_ChannelNumber(var) var

/* Access member 'ChannelNumber' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data_NeighborChannel' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data_NeighborChannel_ChannelNumber(var) (&var)

/* Access member 'NeighborChannel' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data_NeighborChannel(var) (*var)

/* Access member 'NeighborChannel' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data_NeighborChannel(var) var

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data(var) var

/* Access member 'data03' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03(var) var

/* Access member 'data03' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03(var) (&var)

/* Access member 'NeighborSearchWindowSizeIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_NeighborSearchWindowSizeIncluded(var) var

/* Access member 'NeighborSearchWindowSizeIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_NeighborSearchWindowSizeIncluded(var) (&var)

/* Access member 'NeighborSearchWindowSize' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04_data_NeighborSearchWindowSize(var) var

/* Access member 'NeighborSearchWindowSize' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04_data_NeighborSearchWindowSize(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04_data(var) var

/* Access member 'data04' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04(var) var

/* Access member 'data04' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04(var) (&var)

/* Access member 'NeighborSearchWindowOffsetIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_NeighborSearchWindowOffsetIncluded(var) var

/* Access member 'NeighborSearchWindowOffsetIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_NeighborSearchWindowOffsetIncluded(var) (&var)

/* Access member 'NeighborSearchWindowOffset' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05_data_NeighborSearchWindowOffset(var) var

/* Access member 'NeighborSearchWindowOffset' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05_data_NeighborSearchWindowOffset(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05_data(var) var

/* Access member 'data05' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05(var) var

/* Access member 'data05' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05(var) (&var)

/* Access member 'ExtendedChannelIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_ExtendedChannelIncluded(var) var

/* Access member 'ExtendedChannelIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_ExtendedChannelIncluded(var) (&var)

/* Access member 'ExtendedChannelCount' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_ExtendedChannelCount(var) var

/* Access member 'ExtendedChannelCount' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_ExtendedChannelCount(var) (&var)

/* Access member 'SystemType' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data_ExtendedChannel' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data_ExtendedChannel_SystemType(var) var

/* Access member 'SystemType' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data_ExtendedChannel' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data_ExtendedChannel_SystemType(var) (&var)

/* Access member 'BandClass' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data_ExtendedChannel' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data_ExtendedChannel_BandClass(var) var

/* Access member 'BandClass' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data_ExtendedChannel' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data_ExtendedChannel_BandClass(var) (&var)

/* Access member 'ChannelNumber' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data_ExtendedChannel' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data_ExtendedChannel_ChannelNumber(var) var

/* Access member 'ChannelNumber' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data_ExtendedChannel' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data_ExtendedChannel_ChannelNumber(var) (&var)

/* Access member 'ExtendedChannel' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data_ExtendedChannel(var) var

/* Access member 'ExtendedChannel' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data_ExtendedChannel(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data(var) var

/* Access member 'data06' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06(var) var

/* Access member 'data06' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06(var) (&var)

/* Access member 'AccessHashingChannelMaskIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_AccessHashingChannelMaskIncluded(var) var

/* Access member 'AccessHashingChannelMaskIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_AccessHashingChannelMaskIncluded(var) (&var)

/* Access member 'AccessHashingMaskLength' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_AccessHashingMaskLength(var) var

/* Access member 'AccessHashingMaskLength' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_AccessHashingMaskLength(var) (&var)

/* Access member 'AccessHashingChannelMaskSameAsPrevious' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data_AccessHashingChannelMaskSameAsPrevious(var) var

/* Access member 'AccessHashingChannelMaskSameAsPrevious' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data_AccessHashingChannelMaskSameAsPrevious(var) (&var)

/* Access member 'AccessHashingChannelMask' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data_AccessHashingChannelMask(var) (*var)

/* Access member 'AccessHashingChannelMask' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data_AccessHashingChannelMask(var) var

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data(var) var

/* Access member 'data07' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07(var) var

/* Access member 'data07' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07(var) (&var)

/* Access member 'RouteUpdateTriggerCodeIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_RouteUpdateTriggerCodeIncluded(var) var

/* Access member 'RouteUpdateTriggerCodeIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_RouteUpdateTriggerCodeIncluded(var) (&var)

/* Access member 'RouteUpdateTriggerCode' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_RouteUpdateTriggerCode(var) var

/* Access member 'RouteUpdateTriggerCode' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_RouteUpdateTriggerCode(var) (&var)

/* Access member 'RouteUpdateTriggerMaxAge' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_RouteUpdateTriggerMaxAge(var) var

/* Access member 'RouteUpdateTriggerMaxAge' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_RouteUpdateTriggerMaxAge(var) (&var)

/* Access member 'PriorSessionGAUP' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_PriorSessionGAUP(var) var

/* Access member 'PriorSessionGAUP' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_PriorSessionGAUP(var) (&var)

/* Access member 'FPDCHSupportedIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_FPDCHSupportedIncluded(var) var

/* Access member 'FPDCHSupportedIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_FPDCHSupportedIncluded(var) (&var)

/* Access member 'FPDCHSupported' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08_data_FPDCHSupported(var) var

/* Access member 'FPDCHSupported' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08_data_FPDCHSupported(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08_data(var) var

/* Access member 'data08' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08(var) var

/* Access member 'data08' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08(var) (&var)

/* Access member 'SecondaryColorCodeIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_SecondaryColorCodeIncluded(var) var

/* Access member 'SecondaryColorCodeIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_SecondaryColorCodeIncluded(var) (&var)

/* Access member 'SecondaryColorCodeCount' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_SecondaryColorCodeCount(var) var

/* Access member 'SecondaryColorCodeCount' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_SecondaryColorCodeCount(var) (&var)

/* Access member 'SecondaryColorCode' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09_data_SecondaryColorCode(var) var

/* Access member 'SecondaryColorCode' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09_data_SecondaryColorCode(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09_data(var) var

/* Access member 'data09' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09(var) var

/* Access member 'data09' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09(var) (&var)

/* Access member 'PilotGroupIDLoopIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_PilotGroupIDLoopIncluded(var) var

/* Access member 'PilotGroupIDLoopIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_PilotGroupIDLoopIncluded(var) (&var)

/* Access member 'PilotGroupIDIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10_data_PilotGroupIDIncluded(var) var

/* Access member 'PilotGroupIDIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10_data_PilotGroupIDIncluded(var) (&var)

/* Access member 'PilotGroupID' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10_data_PilotGroupID(var) var

/* Access member 'PilotGroupID' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10_data_PilotGroupID(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10_data(var) var

/* Access member 'data10' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10(var) var

/* Access member 'data10' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10(var) (&var)

/* Access member 'IsSectorMultiCarrierCapable' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_IsSectorMultiCarrierCapable(var) var

/* Access member 'IsSectorMultiCarrierCapable' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_IsSectorMultiCarrierCapable(var) (&var)

/* Access member 'ReverseBandClass' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11_data_ReverseBandClass(var) var

/* Access member 'ReverseBandClass' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11_data_ReverseBandClass(var) (&var)

/* Access member 'ReverseChannelNumber' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11_data_ReverseChannelNumber(var) var

/* Access member 'ReverseChannelNumber' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11_data_ReverseChannelNumber(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11_data(var) var

/* Access member 'data11' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11(var) var

/* Access member 'data11' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data_Channel */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data_Channel {

	ED_OCTET SystemType; /* ODY01a *//*GBD01b*/
	ED_OCTET BandClass; /* ODY01a *//*GBD01b*/
	ED_SHORT ChannelNumber; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data_Channel;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data {

	c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data_Channel Channel;/*GBD01b*/

} c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01 */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01 {

	c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02_data */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02_data {

	ED_SHORT NeighborPilotPN; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02 */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02 {

	c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data_NeighborChannel */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data_NeighborChannel {

	ED_OCTET SystemType; /* ODY01a *//*GBD01b*/
	ED_OCTET BandClass; /* ODY01a *//*GBD01b*/
	ED_SHORT ChannelNumber; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data_NeighborChannel;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data {

	ED_BOOLEAN NeighborChannelIncluded; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data_NeighborChannel *NeighborChannel; /* ODY03 <> *//*GBD01b*/
	ED_BOOLEAN NeighborChannel_Present;

} c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03 */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03 {

	c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04_data */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04_data {

	ED_OCTET NeighborSearchWindowSize; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04 */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04 {

	c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05_data */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05_data {

	ED_OCTET NeighborSearchWindowOffset; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN NeighborSearchWindowOffset_Present;

} c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05 */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05 {

	c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data_ExtendedChannel */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data_ExtendedChannel {

	ED_OCTET SystemType; /* ODY01a *//*GBD01b*/
	ED_OCTET BandClass; /* ODY01a *//*GBD01b*/
	ED_SHORT ChannelNumber; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data_ExtendedChannel;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data {

	c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data_ExtendedChannel ExtendedChannel;/*GBD01b*/

} c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06 */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06 {

	c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06;

/* DEFINITION OF BINARY c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data_AccessHashingChannelMask */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data_AccessHashingChannelMask {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data_AccessHashingChannelMask;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data_AccessHashingChannelMask(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data {

	ED_BOOLEAN AccessHashingChannelMaskSameAsPrevious; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data_AccessHashingChannelMask* AccessHashingChannelMask; /* Dynamic, variable size; bits needed 64 ODY02b *//*GBD01b*/
	ED_BOOLEAN AccessHashingChannelMask_Present;

} c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07 */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07 {

	c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08_data */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08_data {

	ED_BOOLEAN FPDCHSupported; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN FPDCHSupported_Present;

} c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08 */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08 {

	c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09_data */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09_data {

	ED_OCTET SecondaryColorCode; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09 */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09 {

	c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10_data */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10_data {

	ED_BOOLEAN PilotGroupIDIncluded; /* ODY01a *//*GBD01b*/
	ED_OCTET PilotGroupID; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PilotGroupID_Present;

} c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10 */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10 {

	c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11_data */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11_data {

	ED_OCTET ReverseBandClass; /* ODY01a *//*GBD01b*/
	ED_SHORT ReverseChannelNumber; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11 */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11 {

	c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents {

	ED_SHORT CountryCode; /* ODY01a *//*GBD01b*/
	ED_BYTE SectorID [16]; /* Static, fixed size; bits needed 128 *//*GBD01b*/
	ED_OCTET SubnetMask; /* ODY01a *//*GBD01b*/
	ED_SHORT SectorSignature; /* ODY01a *//*GBD01b*/
	ED_LONG Latitude; /* ODY01a *//*GBD01b*/
	ED_LONG Longitude; /* ODY01a *//*GBD01b*/
	ED_SHORT RouteUpdateRadiusOverhead; /* ODY01a *//*GBD01b*/
	ED_OCTET LeapSeconds; /* ODY01a *//*GBD01b*/
	ED_SHORT LocalTimeOffset; /* ODY01a *//*GBD01b*/
	ED_OCTET ReverseLinkSilenceDuration; /* ODY01a *//*GBD01b*/
	ED_OCTET ReverseLinkSilencePeriod; /* ODY01a *//*GBD01b*/
	ED_OCTET ChannelCount; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01 data01;/*GFB09*//*GBD01b*/
	ED_OCTET NeighborCount; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02 data02;/*GFB09*//*GBD01b*/
	c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03 data03;/*GFB09*//*GBD01b*/
	ED_BOOLEAN NeighborSearchWindowSizeIncluded; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04 data04;/*GFB09*//*GBD01b*/
	ED_BOOLEAN NeighborSearchWindowOffsetIncluded; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05 data05;/*GFB09*//*GBD01b*/
	ED_BOOLEAN ExtendedChannelIncluded; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ExtendedChannelIncluded_Present;
	ED_OCTET ExtendedChannelCount; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ExtendedChannelCount_Present;
	c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06 data06;/*GFB09*//*GBD01b*/
	ED_BOOLEAN AccessHashingChannelMaskIncluded; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN AccessHashingChannelMaskIncluded_Present;
	ED_OCTET AccessHashingMaskLength; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN AccessHashingMaskLength_Present;
	c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07 data07;/*GFB09*//*GBD01b*/
	ED_BOOLEAN RouteUpdateTriggerCodeIncluded; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN RouteUpdateTriggerCodeIncluded_Present;
	ED_SHORT RouteUpdateTriggerCode; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN RouteUpdateTriggerCode_Present;
	ED_OCTET RouteUpdateTriggerMaxAge; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN RouteUpdateTriggerMaxAge_Present;
	ED_BOOLEAN PriorSessionGAUP; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PriorSessionGAUP_Present;
	ED_BOOLEAN FPDCHSupportedIncluded; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN FPDCHSupportedIncluded_Present;
	c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08 data08;/*GFB09*//*GBD01b*/
	ED_BOOLEAN SecondaryColorCodeIncluded; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SecondaryColorCodeIncluded_Present;
	ED_OCTET SecondaryColorCodeCount; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SecondaryColorCodeCount_Present;
	c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09 data09;/*GFB09*//*GBD01b*/
	ED_BOOLEAN PilotGroupIDLoopIncluded; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PilotGroupIDLoopIncluded_Present;
	c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10 data10;/*GFB09*//*GBD01b*/
	ED_BOOLEAN IsSectorMultiCarrierCapable; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN IsSectorMultiCarrierCapable_Present;
	c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11 data11;/*GFB09*//*GBD01b*/

}	c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents;
#define INIT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents(c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents* sp);
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_ExtendedChannelIncluded(sp,present) ((sp)->ExtendedChannelIncluded_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_ExtendedChannelIncluded(sp) ((sp)->ExtendedChannelIncluded_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_ExtendedChannelCount(sp,present) ((sp)->ExtendedChannelCount_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_ExtendedChannelCount(sp) ((sp)->ExtendedChannelCount_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_AccessHashingChannelMaskIncluded(sp,present) ((sp)->AccessHashingChannelMaskIncluded_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_AccessHashingChannelMaskIncluded(sp) ((sp)->AccessHashingChannelMaskIncluded_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_AccessHashingMaskLength(sp,present) ((sp)->AccessHashingMaskLength_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_AccessHashingMaskLength(sp) ((sp)->AccessHashingMaskLength_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_RouteUpdateTriggerCodeIncluded(sp,present) ((sp)->RouteUpdateTriggerCodeIncluded_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_RouteUpdateTriggerCodeIncluded(sp) ((sp)->RouteUpdateTriggerCodeIncluded_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_RouteUpdateTriggerCode(sp,present) ((sp)->RouteUpdateTriggerCode_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_RouteUpdateTriggerCode(sp) ((sp)->RouteUpdateTriggerCode_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_RouteUpdateTriggerMaxAge(sp,present) ((sp)->RouteUpdateTriggerMaxAge_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_RouteUpdateTriggerMaxAge(sp) ((sp)->RouteUpdateTriggerMaxAge_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_PriorSessionGAUP(sp,present) ((sp)->PriorSessionGAUP_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_PriorSessionGAUP(sp) ((sp)->PriorSessionGAUP_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_FPDCHSupportedIncluded(sp,present) ((sp)->FPDCHSupportedIncluded_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_FPDCHSupportedIncluded(sp) ((sp)->FPDCHSupportedIncluded_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_SecondaryColorCodeIncluded(sp,present) ((sp)->SecondaryColorCodeIncluded_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_SecondaryColorCodeIncluded(sp) ((sp)->SecondaryColorCodeIncluded_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_SecondaryColorCodeCount(sp,present) ((sp)->SecondaryColorCodeCount_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_SecondaryColorCodeCount(sp) ((sp)->SecondaryColorCodeCount_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_PilotGroupIDLoopIncluded(sp,present) ((sp)->PilotGroupIDLoopIncluded_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_PilotGroupIDLoopIncluded(sp) ((sp)->PilotGroupIDLoopIncluded_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_IsSectorMultiCarrierCapable(sp,present) ((sp)->IsSectorMultiCarrierCapable_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_IsSectorMultiCarrierCapable(sp) ((sp)->IsSectorMultiCarrierCapable_Present)

/* Access member 'ReverseLinkSilenceDuration' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters_contents_ReverseLinkSilenceDuration(var) var

/* Access member 'ReverseLinkSilenceDuration' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters_contents_ReverseLinkSilenceDuration(var) (&var)

/* Access member 'ReverseLinkSilencePeriod' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters_contents_ReverseLinkSilencePeriod(var) var

/* Access member 'ReverseLinkSilencePeriod' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters_contents_ReverseLinkSilencePeriod(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters_contents {

	ED_OCTET ReverseLinkSilenceDuration; /* ODY01a *//*GBD01b*/
	ED_OCTET ReverseLinkSilencePeriod; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters_contents;
#define INIT_c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters_contents(c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters_contents* sp);

/* Access member 'OtherRATSignature' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_OtherRATSignature(var) var

/* Access member 'OtherRATSignature' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_OtherRATSignature(var) (&var)

/* Access member 'NumOtherRAT' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_NumOtherRAT(var) var

/* Access member 'NumOtherRAT' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_NumOtherRAT(var) (&var)

/* Access member 'RATType' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_RATType(var) var

/* Access member 'RATType' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_RATType(var) (&var)

/* Access member 'NeighborRATRecordLength' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecordLength(var) var

/* Access member 'NeighborRATRecordLength' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecordLength(var) (&var)

/* Access member 'OtherNeighborRATRecord' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_OtherNeighborRATRecord(var) (*var)

/* Access member 'OtherNeighborRATRecord' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_OtherNeighborRATRecord(var) var

/* Access member 'PriorityIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_PriorityIncluded(var) var

/* Access member 'PriorityIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_PriorityIncluded(var) (&var)

/* Access member 'ServingPriority' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_ServingPriority(var) var

/* Access member 'ServingPriority' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_ServingPriority(var) (&var)

/* Access member 'ThreshServing' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_ThreshServing(var) var

/* Access member 'ThreshServing' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_ThreshServing(var) (&var)

/* Access member 'PerEARFCNParamsIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_PerEARFCNParamsIncluded(var) var

/* Access member 'PerEARFCNParamsIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_PerEARFCNParamsIncluded(var) (&var)

/* Access member 'RxLevMinEUTRACommon' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_RxLevMinEUTRACommon(var) var

/* Access member 'RxLevMinEUTRACommon' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_RxLevMinEUTRACommon(var) (&var)

/* Access member 'PEMaxCommon' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_PEMaxCommon(var) var

/* Access member 'PEMaxCommon' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_PEMaxCommon(var) (&var)

/* Access member 'RxLevMinEUTRAOffsetCommonIncl' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_RxLevMinEUTRAOffsetCommonIncl(var) var

/* Access member 'RxLevMinEUTRAOffsetCommonIncl' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_RxLevMinEUTRAOffsetCommonIncl(var) (&var)

/* Access member 'RxLevMinEUTRAOffsetCommon' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_RxLevMinEUTRAOffsetCommon(var) var

/* Access member 'RxLevMinEUTRAOffsetCommon' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_RxLevMinEUTRAOffsetCommon(var) (&var)

/* Access member 'MaxReselectionTimerIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_MaxReselectionTimerIncluded(var) var

/* Access member 'MaxReselectionTimerIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_MaxReselectionTimerIncluded(var) (&var)

/* Access member 'MaxReselectionTimer' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_MaxReselectionTimer(var) var

/* Access member 'MaxReselectionTimer' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_MaxReselectionTimer(var) (&var)

/* Access member 'SearchBackOffTimerIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_SearchBackOffTimerIncluded(var) var

/* Access member 'SearchBackOffTimerIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_SearchBackOffTimerIncluded(var) (&var)

/* Access member 'MinMeasurementBackoff' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_MinMeasurementBackoff(var) var

/* Access member 'MinMeasurementBackoff' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_MinMeasurementBackoff(var) (&var)

/* Access member 'MaxMeasurementBackoff' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_MaxMeasurementBackoff(var) var

/* Access member 'MaxMeasurementBackoff' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_MaxMeasurementBackoff(var) (&var)

/* Access member 'PLMNIDIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_PLMNIDIncluded(var) var

/* Access member 'PLMNIDIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_PLMNIDIncluded(var) (&var)

/* Access member 'NumEUTRAFrequencies' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_NumEUTRAFrequencies(var) var

/* Access member 'NumEUTRAFrequencies' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_NumEUTRAFrequencies(var) (&var)

/* Access member 'EARFCN' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_EARFCN(var) var

/* Access member 'EARFCN' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_EARFCN(var) (&var)

/* Access member 'EARFCNPriority' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_EARFCNPriority(var) var

/* Access member 'EARFCNPriority' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_EARFCNPriority(var) (&var)

/* Access member 'ThreshX' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_ThreshX(var) var

/* Access member 'ThreshX' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_ThreshX(var) (&var)

/* Access member 'RxLevMinEUTRA' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_RxLevMinEUTRA(var) var

/* Access member 'RxLevMinEUTRA' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_RxLevMinEUTRA(var) (&var)

/* Access member 'PEMax' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PEMax(var) var

/* Access member 'PEMax' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PEMax(var) (&var)

/* Access member 'RxLevMinEUTRAOffsetIncl' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_RxLevMinEUTRAOffsetIncl(var) var

/* Access member 'RxLevMinEUTRAOffsetIncl' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_RxLevMinEUTRAOffsetIncl(var) (&var)

/* Access member 'RxLevMinEUTRAOffset' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_RxLevMinEUTRAOffset(var) var

/* Access member 'RxLevMinEUTRAOffset' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_RxLevMinEUTRAOffset(var) (&var)

/* Access member 'MeasurementBandwidth' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_MeasurementBandwidth(var) var

/* Access member 'MeasurementBandwidth' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_MeasurementBandwidth(var) (&var)

/* Access member 'PLMNSameAsPreviousChannel' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNSameAsPreviousChannel(var) var

/* Access member 'PLMNSameAsPreviousChannel' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNSameAsPreviousChannel(var) (&var)

/* Access member 'NumPLMNIDs' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_NumPLMNIDs(var) var

/* Access member 'NumPLMNIDs' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_NumPLMNIDs(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID_data(var) var

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID_data(var) (&var)

/* Access member 'PLMNID' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID(var) var

/* Access member 'PLMNID' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data(var) var

/* Access member 'data02' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02(var) var

/* Access member 'data02' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02(var) (&var)

/* Access member 'ServingNetworkPLMNIncl' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_ServingNetworkPLMNIncl(var) var

/* Access member 'ServingNetworkPLMNIncl' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_ServingNetworkPLMNIncl(var) (&var)

/* Access member 'NumServingPLMNIDs' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_NumServingPLMNIDs(var) var

/* Access member 'NumServingPLMNIDs' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_NumServingPLMNIDs(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID_data(var) var

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID_data(var) (&var)

/* Access member 'S_PLMNID' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID(var) var

/* Access member 'S_PLMNID' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID(var) (&var)

/* Access member 'RSRQParametersIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_RSRQParametersIncluded(var) var

/* Access member 'RSRQParametersIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_RSRQParametersIncluded(var) (&var)

/* Access member 'QualMinEUTRACommon' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_QualMinEUTRACommon(var) var

/* Access member 'QualMinEUTRACommon' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_QualMinEUTRACommon(var) (&var)

/* Access member 'QualMinEUTRAOffsetCommonInc' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_QualMinEUTRAOffsetCommonInc(var) var

/* Access member 'QualMinEUTRAOffsetCommonInc' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_QualMinEUTRAOffsetCommonInc(var) (&var)

/* Access member 'QualMinEUTRAOffsetCommon' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_QualMinEUTRAOffsetCommon(var) var

/* Access member 'QualMinEUTRAOffsetCommon' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_QualMinEUTRAOffsetCommon(var) (&var)

/* Access member 'ThreshXQ' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data_ThreshXQ(var) var

/* Access member 'ThreshXQ' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data_ThreshXQ(var) (&var)

/* Access member 'QualMinEUTRA' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data_QualMinEUTRA(var) var

/* Access member 'QualMinEUTRA' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data_QualMinEUTRA(var) (&var)

/* Access member 'QualMinEUTRAOffsetIncl' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data_QualMinEUTRAOffsetIncl(var) var

/* Access member 'QualMinEUTRAOffsetIncl' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data_QualMinEUTRAOffsetIncl(var) (&var)

/* Access member 'QualMinEUTRAOffset' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data_QualMinEUTRAOffset(var) var

/* Access member 'QualMinEUTRAOffset' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data_QualMinEUTRAOffset(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data(var) var

/* Access member 'data05' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05(var) var

/* Access member 'data05' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05(var) (&var)

/* Access member 'NeighborRATRecord' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord(var) (*var)

/* Access member 'NeighborRATRecord' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord(var) var

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01(var) (&var)

/* DEFINITION OF BINARY c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_OtherNeighborRATRecord */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_OtherNeighborRATRecord {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_OtherNeighborRATRecord;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_OtherNeighborRATRecord(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID {

	ED_LONG* data; /* NDY01a *//*GBD01b*//*GAD01a*//*AR02 ('TDMSequence'-18852=EDCore::TDMSequence)  */
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data {

	ED_SHORT EARFCN; /* ODY01a *//*GBD01b*/
	ED_OCTET EARFCNPriority; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN EARFCNPriority_Present;
	ED_OCTET ThreshX; /* ODY01a *//*GBD01b*/
	ED_OCTET RxLevMinEUTRA; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN RxLevMinEUTRA_Present;
	ED_OCTET PEMax; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PEMax_Present;
	ED_BOOLEAN RxLevMinEUTRAOffsetIncl; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN RxLevMinEUTRAOffsetIncl_Present;
	ED_OCTET RxLevMinEUTRAOffset; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN RxLevMinEUTRAOffset_Present;
	ED_OCTET MeasurementBandwidth; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PLMNSameAsPreviousChannel; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PLMNSameAsPreviousChannel_Present;
	ED_OCTET NumPLMNIDs; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN NumPLMNIDs_Present;
	c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID PLMNID;/*GFB09*//*GBD01b*/

} c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02 */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02 {

	c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID {

	ED_LONG* data; /* NDY01a *//*GBD01b*//*GAD01a*//*AR02 ('TDMSequence'-18860=EDCore::TDMSequence)  */
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data {

	ED_OCTET ThreshXQ; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ThreshXQ_Present;
	ED_OCTET QualMinEUTRA; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN QualMinEUTRA_Present;
	ED_BOOLEAN QualMinEUTRAOffsetIncl; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN QualMinEUTRAOffsetIncl_Present;
	ED_OCTET QualMinEUTRAOffset; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN QualMinEUTRAOffset_Present;

} c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05 */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05 {

	c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord {

	ED_BOOLEAN PriorityIncluded; /* ODY01a *//*GBD01b*/
	ED_OCTET ServingPriority; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ServingPriority_Present;
	ED_OCTET ThreshServing; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PerEARFCNParamsIncluded; /* ODY01a *//*GBD01b*/
	ED_OCTET RxLevMinEUTRACommon; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN RxLevMinEUTRACommon_Present;
	ED_OCTET PEMaxCommon; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PEMaxCommon_Present;
	ED_BOOLEAN RxLevMinEUTRAOffsetCommonIncl; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN RxLevMinEUTRAOffsetCommonIncl_Present;
	ED_OCTET RxLevMinEUTRAOffsetCommon; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN RxLevMinEUTRAOffsetCommon_Present;
	ED_BOOLEAN MaxReselectionTimerIncluded; /* ODY01a *//*GBD01b*/
	ED_OCTET MaxReselectionTimer; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN MaxReselectionTimer_Present;
	ED_BOOLEAN SearchBackOffTimerIncluded; /* ODY01a *//*GBD01b*/
	ED_OCTET MinMeasurementBackoff; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN MinMeasurementBackoff_Present;
	ED_OCTET MaxMeasurementBackoff; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN MaxMeasurementBackoff_Present;
	ED_BOOLEAN PLMNIDIncluded; /* ODY01a *//*GBD01b*/
	ED_OCTET NumEUTRAFrequencies; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02 data02;/*GFB09*//*GBD01b*/
	ED_BOOLEAN ServingNetworkPLMNIncl; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ServingNetworkPLMNIncl_Present;
	ED_OCTET NumServingPLMNIDs; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN NumServingPLMNIDs_Present;
	c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID S_PLMNID;/*GFB09*//*GBD01b*/
	ED_BOOLEAN RSRQParametersIncluded; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN RSRQParametersIncluded_Present;
	ED_OCTET QualMinEUTRACommon; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN QualMinEUTRACommon_Present;
	ED_BOOLEAN QualMinEUTRAOffsetCommonInc; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN QualMinEUTRAOffsetCommonInc_Present;
	ED_OCTET QualMinEUTRAOffsetCommon; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN QualMinEUTRAOffsetCommon_Present;
	c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05 data05;/*GFB09*//*GBD01b*/

} c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data {

	ED_OCTET RATType; /* ODY01a *//*GBD01b*/
	ED_SHORT NeighborRATRecordLength; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_OtherNeighborRATRecord* OtherNeighborRATRecord; /* Dynamic, variable size; bits needed 64 ODY02b *//*GBD01b*/
	ED_BOOLEAN OtherNeighborRATRecord_Present;
	c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord *NeighborRATRecord; /* ODY03 <> *//*GBD01b*/
	ED_BOOLEAN NeighborRATRecord_Present;

} c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01 */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01 {

	c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents {

	ED_OCTET OtherRATSignature; /* ODY01a *//*GBD01b*/
	ED_OCTET NumOtherRAT; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents;
#define INIT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents(c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents* sp);

/* Access member 'LifeTime' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_LifeTime(var) var

/* Access member 'LifeTime' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_LifeTime(var) (&var)

/* Access member 'NumAPPIRec' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_NumAPPIRec(var) var

/* Access member 'NumAPPIRec' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_NumAPPIRec(var) (&var)

/* Access member 'APAssociationType' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APAssociationType(var) var

/* Access member 'APAssociationType' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APAssociationType(var) (&var)

/* Access member 'APSubnetSameAsPrevious' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APSubnetSameAsPrevious(var) var

/* Access member 'APSubnetSameAsPrevious' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APSubnetSameAsPrevious(var) (&var)

/* Access member 'APBandSameAsPrevious' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APBandSameAsPrevious(var) var

/* Access member 'APBandSameAsPrevious' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APBandSameAsPrevious(var) (&var)

/* Access member 'APChannelSameAsPrevious' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APChannelSameAsPrevious(var) var

/* Access member 'APChannelSameAsPrevious' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APChannelSameAsPrevious(var) (&var)

/* Access member 'APPNRecordSameAsPrevious' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APPNRecordSameAsPrevious(var) var

/* Access member 'APPNRecordSameAsPrevious' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APPNRecordSameAsPrevious(var) (&var)

/* Access member 'APSubnetLength' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APSubnetLength(var) var

/* Access member 'APSubnetLength' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APSubnetLength(var) (&var)

/* Access member 'APSubnet' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APSubnet(var) (*var)

/* Access member 'APSubnet' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APSubnet(var) var

/* Access member 'APBand' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APBand(var) var

/* Access member 'APBand' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APBand(var) (&var)

/* Access member 'APChannel' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APChannel(var) var

/* Access member 'APChannel' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APChannel(var) (&var)

/* Access member 'APPNRecordType' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APPNRecordType(var) var

/* Access member 'APPNRecordType' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APPNRecordType(var) (&var)

/* Access member 'APPNRecordLength' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APPNRecordLength(var) var

/* Access member 'APPNRecordLength' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APPNRecordLength(var) (&var)

/* Access member 'APPNRecord' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APPNRecord(var) var

/* Access member 'APPNRecord' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APPNRecord(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01(var) (&var)

/* DEFINITION OF BINARY c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APSubnet */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APSubnet {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APSubnet;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APSubnet(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF BINARY c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APPNRecord */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APPNRecord {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APPNRecord;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APPNRecord(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data {

	ED_OCTET APAssociationType; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN APSubnetSameAsPrevious; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN APBandSameAsPrevious; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN APChannelSameAsPrevious; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN APPNRecordSameAsPrevious; /* ODY01a *//*GBD01b*/
	ED_OCTET APSubnetLength; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN APSubnetLength_Present;
	c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APSubnet* APSubnet; /* Dynamic, variable size; bits needed 64 ODY02b *//*GBD01b*/
	ED_BOOLEAN APSubnet_Present;
	ED_OCTET APBand; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN APBand_Present;
	ED_SHORT APChannel; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN APChannel_Present;
	ED_OCTET APPNRecordType; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN APPNRecordType_Present;
	ED_OCTET APPNRecordLength; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN APPNRecordLength_Present;
	c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APPNRecord APPNRecord; /* Static, variable size; bits needed 64 *//*GBD01b*/

} c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01 */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01 {

	c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents {

	ED_OCTET LifeTime; /* ODY01a *//*GBD01b*/
	ED_OCTET NumAPPIRec; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents;
#define INIT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents(c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents* sp);

/* Access member 'AssociationType' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_AssociationType(var) var

/* Access member 'AssociationType' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_AssociationType(var) (&var)

/* Access member 'SubnetLength' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_SubnetLength(var) var

/* Access member 'SubnetLength' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_SubnetLength(var) (&var)

/* Access member 'Subnet' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_Subnet(var) var

/* Access member 'Subnet' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_Subnet(var) (&var)

/* Access member 'APIDLength' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_APIDLength(var) var

/* Access member 'APIDLength' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_APIDLength(var) (&var)

/* Access member 'APID' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_APID(var) var

/* Access member 'APID' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_APID(var) (&var)

/* Access member 'APIDMask' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_APIDMask(var) var

/* Access member 'APIDMask' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_APIDMask(var) (&var)

/* Access member 'e1xAcquisitionIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_e1xAcquisitionIncluded(var) var

/* Access member 'e1xAcquisitionIncluded' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_e1xAcquisitionIncluded(var) (&var)

/* Access member 'e1xSID' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_e1xSID(var) var

/* Access member 'e1xSID' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_e1xSID(var) (&var)

/* Access member 'e1xNID' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_e1xNID(var) var

/* Access member 'e1xNID' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_e1xNID(var) (&var)

/* Access member 'e1xBandClass' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_e1xBandClass(var) var

/* Access member 'e1xBandClass' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_e1xBandClass(var) (&var)

/* Access member 'e1xChannel' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_e1xChannel(var) var

/* Access member 'e1xChannel' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_e1xChannel(var) (&var)

/* Access member 'e1xPNOffset' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_e1xPNOffset(var) var

/* Access member 'e1xPNOffset' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_e1xPNOffset(var) (&var)

/* Access member 'LocationRecordType' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_LocationRecordType(var) var

/* Access member 'LocationRecordType' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_LocationRecordType(var) (&var)

/* Access member 'LocationRecordLength' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_LocationRecordLength(var) var

/* Access member 'LocationRecordLength' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_LocationRecordLength(var) (&var)

/* Access member 'LocationRecord' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_LocationRecord(var) var

/* Access member 'LocationRecord' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_LocationRecord(var) (&var)

/* Access member 'HandoffInformationCount' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_HandoffInformationCount(var) var

/* Access member 'HandoffInformationCount' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_HandoffInformationCount(var) (&var)

/* Access member 'HandoffInfoType' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data_HandoffInfoType(var) var

/* Access member 'HandoffInfoType' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data_HandoffInfoType(var) (&var)

/* Access member 'HandoffInfoLength' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data_HandoffInfoLength(var) var

/* Access member 'HandoffInfoLength' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data_HandoffInfoLength(var) (&var)

/* Access member 'HandoffInfoValue' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data_HandoffInfoValue(var) var

/* Access member 'HandoffInfoValue' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data_HandoffInfoValue(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01(var) (&var)

/* DEFINITION OF BINARY c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_Subnet */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_Subnet {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_Subnet;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_Subnet(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF BINARY c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_APID */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_APID {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_APID;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_APID(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF BINARY c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_LocationRecord */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_LocationRecord {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_LocationRecord;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_LocationRecord(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF BINARY c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data_HandoffInfoValue */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data_HandoffInfoValue {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data_HandoffInfoValue;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data_HandoffInfoValue(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data {

	ED_OCTET HandoffInfoType; /* ODY01a *//*GBD01b*/
	ED_OCTET HandoffInfoLength; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data_HandoffInfoValue HandoffInfoValue; /* Static, variable size; bits needed 64 *//*GBD01b*/

} c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01 */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01 {

	c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents {

	ED_OCTET AssociationType; /* ODY01a *//*GBD01b*/
	ED_OCTET SubnetLength; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_Subnet Subnet; /* Static, variable size; bits needed 64 *//*GBD01b*/
	ED_OCTET APIDLength; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_APID APID; /* Static, variable size; bits needed 64 *//*GBD01b*/
	ED_OCTET APIDMask; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN e1xAcquisitionIncluded; /* ODY01a *//*GBD01b*/
	ED_SHORT e1xSID; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN e1xSID_Present;
	ED_SHORT e1xNID; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN e1xNID_Present;
	ED_OCTET e1xBandClass; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN e1xBandClass_Present;
	ED_SHORT e1xChannel; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN e1xChannel_Present;
	ED_SHORT e1xPNOffset; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN e1xPNOffset_Present;
	ED_OCTET LocationRecordType; /* ODY01a *//*GBD01b*/
	ED_OCTET LocationRecordLength; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_LocationRecord LocationRecord; /* Static, variable size; bits needed 64 *//*GBD01b*/
	ED_OCTET HandoffInformationCount; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents;
#define INIT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents(c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents* sp);
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_e1xSID(sp,present) ((sp)->e1xSID_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_e1xSID(sp) ((sp)->e1xSID_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_e1xNID(sp,present) ((sp)->e1xNID_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_e1xNID(sp) ((sp)->e1xNID_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_e1xBandClass(sp,present) ((sp)->e1xBandClass_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_e1xBandClass(sp) ((sp)->e1xBandClass_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_e1xChannel(sp,present) ((sp)->e1xChannel_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_e1xChannel(sp) ((sp)->e1xChannel_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_e1xPNOffset(sp,present) ((sp)->e1xPNOffset_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_e1xPNOffset(sp) ((sp)->e1xPNOffset_Present)

/* Access member 'Reserved1' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_Reserved1(var) var

/* Access member 'Reserved1' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_Reserved1(var) (&var)

/* Access member 'MsgEncoding' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_MsgEncoding(var) var

/* Access member 'MsgEncoding' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_MsgEncoding(var) (&var)

/* Access member 'NumFields' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_NumFields(var) var

/* Access member 'NumFields' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_NumFields(var) (&var)

/* Access member 'CHARi' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01_data' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01_data_CHARi(var) var

/* Access member 'CHARi' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01_data' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01_data_CHARi(var) (&var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01_data */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01_data {

	ED_OCTET CHARi; /* ODY01a *//*GBD01b*/

} c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01 */
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01 {

	c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01;


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents {

	ED_OCTET Reserved1; /* ODY01a *//*GBD01b*/
	ED_OCTET MsgEncoding; /* ODY01a *//*GBD01b*/
	ED_OCTET NumFields; /* ODY01a *//*GBD01b*/
	c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents;
#define INIT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents))
/*FRK03a*/
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents(c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents* sp);

/* Access member 'NumPilots' of type 'c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents' as a variable reference */
#define VAR_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_NumPilots(var) var

/* Access member 'NumPilots' of type 'c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents' as a pointer */
#define PTR_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_NumPilots(var) (&var)

/* Access member 'PilotPN' of type 'c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data' as a variable reference */
#define VAR_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data_PilotPN(var) var

/* Access member 'PilotPN' of type 'c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data' as a pointer */
#define PTR_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data_PilotPN(var) (&var)

/* Access member 'OpenLoopAdjust' of type 'c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data' as a variable reference */
#define VAR_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data_OpenLoopAdjust(var) var

/* Access member 'OpenLoopAdjust' of type 'c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data' as a pointer */
#define PTR_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data_OpenLoopAdjust(var) (&var)

/* Access member 'InitialAdjust' of type 'c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data' as a variable reference */
#define VAR_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data_InitialAdjust(var) var

/* Access member 'InitialAdjust' of type 'c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data' as a pointer */
#define PTR_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data_InitialAdjust(var) (&var)

/* Access member 'PilotStrengthIncluded' of type 'c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data' as a variable reference */
#define VAR_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data_PilotStrengthIncluded(var) var

/* Access member 'PilotStrengthIncluded' of type 'c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data' as a pointer */
#define PTR_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data_PilotStrengthIncluded(var) (&var)

/* Access member 'PilotStrengthNominal' of type 'c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data' as a variable reference */
#define VAR_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data_PilotStrengthNominal(var) var

/* Access member 'PilotStrengthNominal' of type 'c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data' as a pointer */
#define PTR_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data_PilotStrengthNominal(var) (&var)

/* Access member 'PilotStrengthCorrectionMin' of type 'c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data' as a variable reference */
#define VAR_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data_PilotStrengthCorrectionMin(var) var

/* Access member 'PilotStrengthCorrectionMin' of type 'c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data' as a pointer */
#define PTR_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data_PilotStrengthCorrectionMin(var) (&var)

/* Access member 'PilotStrengthCorrectionMax' of type 'c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data' as a variable reference */
#define VAR_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data_PilotStrengthCorrectionMax(var) var

/* Access member 'PilotStrengthCorrectionMax' of type 'c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data' as a pointer */
#define PTR_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data_PilotStrengthCorrectionMax(var) (&var)

/* Access member 'data' of type 'c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01' as a variable reference */
#define VAR_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01' as a pointer */
#define PTR_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents' as a variable reference */
#define VAR_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents' as a pointer */
#define PTR_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data */
typedef struct _c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data {

	ED_SHORT PilotPN; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PilotPN_Present;
	ED_OCTET OpenLoopAdjust; /* ODY01a *//*GBD01b*/
	ED_OCTET InitialAdjust; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PilotStrengthIncluded; /* ODY01a *//*GBD01b*/
	ED_OCTET PilotStrengthNominal; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PilotStrengthNominal_Present;
	ED_OCTET PilotStrengthCorrectionMin; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PilotStrengthCorrectionMin_Present;
	ED_OCTET PilotStrengthCorrectionMax; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PilotStrengthCorrectionMax_Present;

} c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01 */
typedef struct _c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01 {

	c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01;


/*-A----------------------------------*/
typedef struct _c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents {

	ED_OCTET NumPilots; /* ODY01a *//*GBD01b*/
	c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents;
#define INIT_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents))
/*FRK03a*/
void FREE_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents(c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents* sp);

/* Access member 'NumPilots' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents' as a variable reference */
#define VAR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_NumPilots(var) var

/* Access member 'NumPilots' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents' as a pointer */
#define PTR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_NumPilots(var) (&var)

/* Access member 'PilotPN' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01_data' as a variable reference */
#define VAR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01_data_PilotPN(var) var

/* Access member 'PilotPN' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01_data' as a pointer */
#define PTR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01_data_PilotPN(var) (&var)

/* Access member 'data' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01' as a variable reference */
#define VAR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01' as a pointer */
#define PTR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01_data(var) var

/* Access member 'data01' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents' as a variable reference */
#define VAR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01(var) var

/* Access member 'data01' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents' as a pointer */
#define PTR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01(var) (&var)

/* Access member 'NumReverseCDMAChannels' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents' as a variable reference */
#define VAR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_NumReverseCDMAChannels(var) var

/* Access member 'NumReverseCDMAChannels' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents' as a pointer */
#define PTR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_NumReverseCDMAChannels(var) (&var)

/* Access member 'SystemType' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_ReverseCDMAChannel' as a variable reference */
#define VAR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_ReverseCDMAChannel_SystemType(var) var

/* Access member 'SystemType' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_ReverseCDMAChannel' as a pointer */
#define PTR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_ReverseCDMAChannel_SystemType(var) (&var)

/* Access member 'BandClass' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_ReverseCDMAChannel' as a variable reference */
#define VAR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_ReverseCDMAChannel_BandClass(var) var

/* Access member 'BandClass' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_ReverseCDMAChannel' as a pointer */
#define PTR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_ReverseCDMAChannel_BandClass(var) (&var)

/* Access member 'ChannelNumber' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_ReverseCDMAChannel' as a variable reference */
#define VAR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_ReverseCDMAChannel_ChannelNumber(var) var

/* Access member 'ChannelNumber' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_ReverseCDMAChannel' as a pointer */
#define PTR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_ReverseCDMAChannel_ChannelNumber(var) (&var)

/* Access member 'ReverseCDMAChannel' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data' as a variable reference */
#define VAR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_ReverseCDMAChannel(var) (*var)

/* Access member 'ReverseCDMAChannel' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data' as a pointer */
#define PTR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_ReverseCDMAChannel(var) var

/* Access member 'PilotIncluded' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data' as a variable reference */
#define VAR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data_PilotIncluded(var) var

/* Access member 'PilotIncluded' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data' as a pointer */
#define PTR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data_PilotIncluded(var) (&var)

/* Access member 'OpenLoopAdjust' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data' as a variable reference */
#define VAR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data_OpenLoopAdjust(var) var

/* Access member 'OpenLoopAdjust' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data' as a pointer */
#define PTR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data_OpenLoopAdjust(var) (&var)

/* Access member 'InitialAdjust' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data' as a variable reference */
#define VAR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data_InitialAdjust(var) var

/* Access member 'InitialAdjust' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data' as a pointer */
#define PTR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data_InitialAdjust(var) (&var)

/* Access member 'PilotStrengthIncluded' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data' as a variable reference */
#define VAR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data_PilotStrengthIncluded(var) var

/* Access member 'PilotStrengthIncluded' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data' as a pointer */
#define PTR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data_PilotStrengthIncluded(var) (&var)

/* Access member 'PilotStrengthNominal' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data' as a variable reference */
#define VAR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data_PilotStrengthNominal(var) var

/* Access member 'PilotStrengthNominal' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data' as a pointer */
#define PTR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data_PilotStrengthNominal(var) (&var)

/* Access member 'PilotStrengthCorrectionMin' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data' as a variable reference */
#define VAR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data_PilotStrengthCorrectionMin(var) var

/* Access member 'PilotStrengthCorrectionMin' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data' as a pointer */
#define PTR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data_PilotStrengthCorrectionMin(var) (&var)

/* Access member 'PilotStrengthCorrectionMax' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data' as a variable reference */
#define VAR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data_PilotStrengthCorrectionMax(var) var

/* Access member 'PilotStrengthCorrectionMax' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data' as a pointer */
#define PTR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data_PilotStrengthCorrectionMax(var) (&var)

/* Access member 'data' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03' as a variable reference */
#define VAR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data(var) (*var)

/* Access member 'data' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03' as a pointer */
#define PTR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data(var) var

/* Access member 'data03' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data' as a variable reference */
#define VAR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03(var) var

/* Access member 'data03' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data' as a pointer */
#define PTR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03(var) (&var)

/* Access member 'data' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02' as a variable reference */
#define VAR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data(var) (*var)

/* Access member 'data' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02' as a pointer */
#define PTR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data(var) var

/* Access member 'data02' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents' as a variable reference */
#define VAR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02(var) var

/* Access member 'data02' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents' as a pointer */
#define PTR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01_data */
typedef struct _c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01_data {

	ED_SHORT PilotPN; /* ODY01a *//*GBD01b*/

} c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01 */
typedef struct _c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01 {

	c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01;

/* DEFINITION OF SUB-STRUCTURE c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_ReverseCDMAChannel */
typedef struct _c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_ReverseCDMAChannel {

	ED_OCTET SystemType; /* ODY01a *//*GBD01b*/
	ED_OCTET BandClass; /* ODY01a *//*GBD01b*/
	ED_SHORT ChannelNumber; /* ODY01a *//*GBD01b*/

} c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_ReverseCDMAChannel;

/* DEFINITION OF SUB-STRUCTURE c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data */
typedef struct _c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data {

	ED_BOOLEAN PilotIncluded; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PilotIncluded_Present;
	ED_OCTET OpenLoopAdjust; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN OpenLoopAdjust_Present;
	ED_OCTET InitialAdjust; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN InitialAdjust_Present;
	ED_BOOLEAN PilotStrengthIncluded; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PilotStrengthIncluded_Present;
	ED_OCTET PilotStrengthNominal; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PilotStrengthNominal_Present;
	ED_OCTET PilotStrengthCorrectionMin; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PilotStrengthCorrectionMin_Present;
	ED_OCTET PilotStrengthCorrectionMax; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PilotStrengthCorrectionMax_Present;

} c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03 */
typedef struct _c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03 {

	c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03;

/* DEFINITION OF SUB-STRUCTURE c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data */
typedef struct _c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data {

	c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_ReverseCDMAChannel *ReverseCDMAChannel; /* ODY03 <> *//*GBD01b*/
	ED_BOOLEAN ReverseCDMAChannel_Present;
	c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03 data03;/*GFB09*//*GBD01b*/

} c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data;

/* DEFINITION OF SUB-STRUCTURE c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02 */
typedef struct _c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02 {

	c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02;


/*-A----------------------------------*/
typedef struct _c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents {

	ED_OCTET NumPilots; /* ODY01a *//*GBD01b*/
	c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01 data01;/*GFB09*//*GBD01b*/
	ED_OCTET NumReverseCDMAChannels; /* ODY01a *//*GBD01b*/
	c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02 data02;/*GFB09*//*GBD01b*/

}	c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents;
#define INIT_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents(sp) ED_RESET_MEM ((sp), sizeof (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents))
/*FRK03a*/
void FREE_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents(c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents* sp);

/* Access member 'ValueID' of type 'c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01_data_ValueID(var) (&var)

/* Access member 'PreferredControlChannelCycleEnabled' of type 'c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01_data_PreferredControlChannelCycleEnabled(var) var

/* Access member 'PreferredControlChannelCycleEnabled' of type 'c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01_data_PreferredControlChannelCycleEnabled(var) (&var)

/* Access member 'PreferredControlChannelCycle' of type 'c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01_data_PreferredControlChannelCycle(var) var

/* Access member 'PreferredControlChannelCycle' of type 'c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01_data_PreferredControlChannelCycle(var) (&var)

/* Access member 'data' of type 'c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01' as a pointer */
#define PTR_c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01(var) var

/* Access member 'data01' of type 'c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle' as a pointer */
#define PTR_c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01_data */
typedef struct _c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PreferredControlChannelCycleEnabled; /* ODY01a *//*GBD01b*/
	ED_SHORT PreferredControlChannelCycle; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PreferredControlChannelCycle_Present;

} c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01 */
typedef struct _c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01 {

	c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle {

	c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle;
#define INIT_c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle))
/*FRK03a*/
void FREE_c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle(c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle* sp);

/* Access member 'ValueID' of type 'c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data_ValueID(var) (&var)

/* Access member 'SlotCycle1' of type 'c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data_SlotCycle1(var) var

/* Access member 'SlotCycle1' of type 'c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data_SlotCycle1(var) (&var)

/* Access member 'SlotCycle2' of type 'c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data_SlotCycle2(var) var

/* Access member 'SlotCycle2' of type 'c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data_SlotCycle2(var) (&var)

/* Access member 'SlotCycle3' of type 'c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data_SlotCycle3(var) var

/* Access member 'SlotCycle3' of type 'c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data_SlotCycle3(var) (&var)

/* Access member 'WakeCount1' of type 'c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data_WakeCount1(var) var

/* Access member 'WakeCount1' of type 'c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data_WakeCount1(var) (&var)

/* Access member 'WakeCount2' of type 'c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data_WakeCount2(var) var

/* Access member 'WakeCount2' of type 'c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data_WakeCount2(var) (&var)

/* Access member 'data' of type 'c_RPD_Inter_RAT_Idle_State_SlottedMode_data01' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Inter_RAT_Idle_State_SlottedMode_data01' as a pointer */
#define PTR_c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Inter_RAT_Idle_State_SlottedMode' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Idle_State_SlottedMode_data01(var) var

/* Access member 'data01' of type 'c_RPD_Inter_RAT_Idle_State_SlottedMode' as a pointer */
#define PTR_c_RPD_Inter_RAT_Idle_State_SlottedMode_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data */
typedef struct _c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET SlotCycle1; /* ODY01a *//*GBD01b*/
	ED_OCTET SlotCycle2; /* ODY01a *//*GBD01b*/
	ED_OCTET SlotCycle3; /* ODY01a *//*GBD01b*/
	ED_OCTET WakeCount1; /* ODY01a *//*GBD01b*/
	ED_OCTET WakeCount2; /* ODY01a *//*GBD01b*/

} c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Inter_RAT_Idle_State_SlottedMode_data01 */
typedef struct _c_RPD_Inter_RAT_Idle_State_SlottedMode_data01 {

	c_RPD_Inter_RAT_Idle_State_SlottedMode_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Inter_RAT_Idle_State_SlottedMode_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Inter_RAT_Idle_State_SlottedMode {

	c_RPD_Inter_RAT_Idle_State_SlottedMode_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Inter_RAT_Idle_State_SlottedMode;
#define INIT_c_RPD_Inter_RAT_Idle_State_SlottedMode(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Inter_RAT_Idle_State_SlottedMode))
/*FRK03a*/
void FREE_c_RPD_Inter_RAT_Idle_State_SlottedMode(c_RPD_Inter_RAT_Idle_State_SlottedMode* sp);

/* Access member 'ValueID' of type 'c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_ValueID(var) (&var)

/* Access member 'MaskCount' of type 'c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_MaskCount(var) var

/* Access member 'MaskCount' of type 'c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_MaskCount(var) (&var)

/* Access member 'MaskPurpose' of type 'c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02_data_MaskPurpose(var) var

/* Access member 'MaskPurpose' of type 'c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02_data_MaskPurpose(var) (&var)

/* Access member 'PreMaskDuration' of type 'c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02_data_PreMaskDuration(var) var

/* Access member 'PreMaskDuration' of type 'c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02_data_PreMaskDuration(var) (&var)

/* Access member 'MaskDuration' of type 'c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02_data_MaskDuration(var) var

/* Access member 'MaskDuration' of type 'c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02_data_MaskDuration(var) (&var)

/* Access member 'PostMaskDuration' of type 'c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02_data_PostMaskDuration(var) var

/* Access member 'PostMaskDuration' of type 'c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02_data_PostMaskDuration(var) (&var)

/* Access member 'data' of type 'c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02' as a pointer */
#define PTR_c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02_data(var) var

/* Access member 'data02' of type 'c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02(var) var

/* Access member 'data02' of type 'c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02(var) (&var)

/* Access member 'data' of type 'c_RPD_Inter_RAT_Idle_State_PagingMask_data01' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Inter_RAT_Idle_State_PagingMask_data01' as a pointer */
#define PTR_c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Inter_RAT_Idle_State_PagingMask' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Idle_State_PagingMask_data01(var) var

/* Access member 'data01' of type 'c_RPD_Inter_RAT_Idle_State_PagingMask' as a pointer */
#define PTR_c_RPD_Inter_RAT_Idle_State_PagingMask_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02_data */
typedef struct _c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02_data {

	ED_OCTET MaskPurpose; /* ODY01a *//*GBD01b*/
	ED_SHORT PreMaskDuration; /* ODY01a *//*GBD01b*/
	ED_SHORT MaskDuration; /* ODY01a *//*GBD01b*/
	ED_SHORT PostMaskDuration; /* ODY01a *//*GBD01b*/

} c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02 */
typedef struct _c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02 {

	c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data */
typedef struct _c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET MaskCount; /* ODY01a *//*GBD01b*/
	c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02 data02;/*GFB09*//*GBD01b*/

} c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Inter_RAT_Idle_State_PagingMask_data01 */
typedef struct _c_RPD_Inter_RAT_Idle_State_PagingMask_data01 {

	c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Inter_RAT_Idle_State_PagingMask_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Inter_RAT_Idle_State_PagingMask {

	c_RPD_Inter_RAT_Idle_State_PagingMask_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Inter_RAT_Idle_State_PagingMask;
#define INIT_c_RPD_Inter_RAT_Idle_State_PagingMask(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Inter_RAT_Idle_State_PagingMask))
/*FRK03a*/
void FREE_c_RPD_Inter_RAT_Idle_State_PagingMask(c_RPD_Inter_RAT_Idle_State_PagingMask* sp);

/* Access member 'ValueID' of type 'c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data_ValueID(var) (&var)

/* Access member 'PilotIncrement' of type 'c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data_PilotIncrement(var) var

/* Access member 'PilotIncrement' of type 'c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data_PilotIncrement(var) (&var)

/* Access member 'SearchWindowActive' of type 'c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data_SearchWindowActive(var) var

/* Access member 'SearchWindowActive' of type 'c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data_SearchWindowActive(var) (&var)

/* Access member 'SearchWindowNeighbor' of type 'c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data_SearchWindowNeighbor(var) var

/* Access member 'SearchWindowNeighbor' of type 'c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data_SearchWindowNeighbor(var) (&var)

/* Access member 'SearchWindowRemaining' of type 'c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data_SearchWindowRemaining(var) var

/* Access member 'SearchWindowRemaining' of type 'c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data_SearchWindowRemaining(var) (&var)

/* Access member 'data' of type 'c_RPD_Inter_RAT_Route_Update_SearchParameters_data01' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Inter_RAT_Route_Update_SearchParameters_data01' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Inter_RAT_Route_Update_SearchParameters' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SearchParameters_data01(var) var

/* Access member 'data01' of type 'c_RPD_Inter_RAT_Route_Update_SearchParameters' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SearchParameters_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data */
typedef struct _c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET PilotIncrement; /* ODY01a *//*GBD01b*/
	ED_OCTET SearchWindowActive; /* ODY01a *//*GBD01b*/
	ED_OCTET SearchWindowNeighbor; /* ODY01a *//*GBD01b*/
	ED_OCTET SearchWindowRemaining; /* ODY01a *//*GBD01b*/

} c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Inter_RAT_Route_Update_SearchParameters_data01 */
typedef struct _c_RPD_Inter_RAT_Route_Update_SearchParameters_data01 {

	c_RPD_Inter_RAT_Route_Update_SearchParameters_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Inter_RAT_Route_Update_SearchParameters_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Inter_RAT_Route_Update_SearchParameters {

	c_RPD_Inter_RAT_Route_Update_SearchParameters_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Inter_RAT_Route_Update_SearchParameters;
#define INIT_c_RPD_Inter_RAT_Route_Update_SearchParameters(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Inter_RAT_Route_Update_SearchParameters))
/*FRK03a*/
void FREE_c_RPD_Inter_RAT_Route_Update_SearchParameters(c_RPD_Inter_RAT_Route_Update_SearchParameters* sp);

/* Access member 'ValueID' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data_ValueID(var) (&var)

/* Access member 'PilotAdd' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data_PilotAdd(var) var

/* Access member 'PilotAdd' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data_PilotAdd(var) (&var)

/* Access member 'PilotCompare' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data_PilotCompare(var) var

/* Access member 'PilotCompare' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data_PilotCompare(var) (&var)

/* Access member 'PilotDrop' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data_PilotDrop(var) var

/* Access member 'PilotDrop' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data_PilotDrop(var) (&var)

/* Access member 'PilotDropTimer' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data_PilotDropTimer(var) var

/* Access member 'PilotDropTimer' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data_PilotDropTimer(var) (&var)

/* Access member 'DynamicThresholds' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data_DynamicThresholds(var) var

/* Access member 'DynamicThresholds' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data_DynamicThresholds(var) (&var)

/* Access member 'SoftSlope' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data_SoftSlope(var) var

/* Access member 'SoftSlope' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data_SoftSlope(var) (&var)

/* Access member 'AddIntercept' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data_AddIntercept(var) var

/* Access member 'AddIntercept' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data_AddIntercept(var) (&var)

/* Access member 'DropIntercept' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data_DropIntercept(var) var

/* Access member 'DropIntercept' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data_DropIntercept(var) (&var)

/* Access member 'NeighborMaxAge' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data_NeighborMaxAge(var) var

/* Access member 'NeighborMaxAge' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data_NeighborMaxAge(var) (&var)

/* Access member 'data' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01(var) var

/* Access member 'data01' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data */
typedef struct _c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET PilotAdd; /* ODY01a *//*GBD01b*/
	ED_OCTET PilotCompare; /* ODY01a *//*GBD01b*/
	ED_OCTET PilotDrop; /* ODY01a *//*GBD01b*/
	ED_OCTET PilotDropTimer; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN DynamicThresholds; /* ODY01a *//*GBD01b*/
	ED_OCTET SoftSlope; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SoftSlope_Present;
	ED_OCTET AddIntercept; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN AddIntercept_Present;
	ED_OCTET DropIntercept; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN DropIntercept_Present;
	ED_OCTET NeighborMaxAge; /* ODY01a *//*GBD01b*/

} c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01 */
typedef struct _c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01 {

	c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters {

	c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters;
#define INIT_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters))
/*FRK03a*/
void FREE_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters(c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters* sp);

/* Access member 'ValueID' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data_ValueID(var) (&var)

/* Access member 'PilotAdd' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data_PilotAdd(var) var

/* Access member 'PilotAdd' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data_PilotAdd(var) (&var)

/* Access member 'PilotCompare' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data_PilotCompare(var) var

/* Access member 'PilotCompare' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data_PilotCompare(var) (&var)

/* Access member 'PilotDrop' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data_PilotDrop(var) var

/* Access member 'PilotDrop' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data_PilotDrop(var) (&var)

/* Access member 'PilotDropTimer' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data_PilotDropTimer(var) var

/* Access member 'PilotDropTimer' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data_PilotDropTimer(var) (&var)

/* Access member 'DynamicThresholds' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data_DynamicThresholds(var) var

/* Access member 'DynamicThresholds' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data_DynamicThresholds(var) (&var)

/* Access member 'SoftSlope' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data_SoftSlope(var) var

/* Access member 'SoftSlope' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data_SoftSlope(var) (&var)

/* Access member 'AddIntercept' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data_AddIntercept(var) var

/* Access member 'AddIntercept' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data_AddIntercept(var) (&var)

/* Access member 'DropIntercept' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data_DropIntercept(var) var

/* Access member 'DropIntercept' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data_DropIntercept(var) (&var)

/* Access member 'NeighborMaxAge' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data_NeighborMaxAge(var) var

/* Access member 'NeighborMaxAge' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data_NeighborMaxAge(var) (&var)

/* Access member 'data' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01(var) var

/* Access member 'data01' of type 'c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data */
typedef struct _c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET PilotAdd; /* ODY01a *//*GBD01b*/
	ED_OCTET PilotCompare; /* ODY01a *//*GBD01b*/
	ED_OCTET PilotDrop; /* ODY01a *//*GBD01b*/
	ED_OCTET PilotDropTimer; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN DynamicThresholds; /* ODY01a *//*GBD01b*/
	ED_OCTET SoftSlope; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SoftSlope_Present;
	ED_OCTET AddIntercept; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN AddIntercept_Present;
	ED_OCTET DropIntercept; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN DropIntercept_Present;
	ED_OCTET NeighborMaxAge; /* ODY01a *//*GBD01b*/

} c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01 */
typedef struct _c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01 {

	c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters {

	c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters;
#define INIT_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters))
/*FRK03a*/
void FREE_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters(c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters* sp);

/* Access member 'ValueID' of type 'c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_ValueID(var) (&var)

/* Access member 'BandClassCount' of type 'c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_BandClassCount(var) var

/* Access member 'BandClassCount' of type 'c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_BandClassCount(var) (&var)

/* Access member 'BandClass' of type 'c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_BandClass(var) var

/* Access member 'BandClass' of type 'c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_BandClass(var) (&var)

/* Access member 'BandSubClassCount' of type 'c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_BandSubClassCount(var) var

/* Access member 'BandSubClassCount' of type 'c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_BandSubClassCount(var) (&var)

/* Access member 'BandSubClass' of type 'c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data_BandSubClass(var) var

/* Access member 'BandSubClass' of type 'c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data_BandSubClass(var) (&var)

/* Access member 'data' of type 'c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data(var) var

/* Access member 'data03' of type 'c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03(var) var

/* Access member 'data03' of type 'c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03(var) (&var)

/* Access member 'data' of type 'c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data(var) var

/* Access member 'data02' of type 'c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02(var) var

/* Access member 'data02' of type 'c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02(var) (&var)

/* Access member 'data' of type 'c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01(var) var

/* Access member 'data01' of type 'c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data */
typedef struct _c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data {

	ED_OCTET BandSubClass; /* ODY01a *//*GBD01b*/

} c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03 */
typedef struct _c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03 {

	c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data */
typedef struct _c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data {

	ED_OCTET BandClass; /* ODY01a *//*GBD01b*/
	ED_OCTET BandSubClassCount; /* ODY01a *//*GBD01b*/
	c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03 data03;/*GFB09*//*GBD01b*/

} c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02 */
typedef struct _c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02 {

	c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data */
typedef struct _c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET BandClassCount; /* ODY01a *//*GBD01b*/
	c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02 data02;/*GFB09*//*GBD01b*/

} c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01 */
typedef struct _c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01 {

	c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels {

	c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels;
#define INIT_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels))
/*FRK03a*/
void FREE_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels(c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels* sp);

/* Access member 'ValueID' of type 'c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01_data_ValueID(var) (&var)

/* Access member 'PreferredControlChannelCycleEnabled' of type 'c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01_data_PreferredControlChannelCycleEnabled(var) var

/* Access member 'PreferredControlChannelCycleEnabled' of type 'c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01_data_PreferredControlChannelCycleEnabled(var) (&var)

/* Access member 'PreferredControlChannelCycle' of type 'c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01_data_PreferredControlChannelCycle(var) var

/* Access member 'PreferredControlChannelCycle' of type 'c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01_data_PreferredControlChannelCycle(var) (&var)

/* Access member 'data' of type 'c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01' as a pointer */
#define PTR_c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01(var) var

/* Access member 'data01' of type 'c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle' as a pointer */
#define PTR_c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01_data */
typedef struct _c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PreferredControlChannelCycleEnabled; /* ODY01a *//*GBD01b*/
	ED_SHORT PreferredControlChannelCycle; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PreferredControlChannelCycle_Present;

} c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01 */
typedef struct _c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01 {

	c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle {

	c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle;
#define INIT_c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle))
/*FRK03a*/
void FREE_c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle(c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle* sp);

/* Access member 'ValueID' of type 'c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data_ValueID(var) (&var)

/* Access member 'SlotCycle1' of type 'c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data_SlotCycle1(var) var

/* Access member 'SlotCycle1' of type 'c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data_SlotCycle1(var) (&var)

/* Access member 'SlotCycle2' of type 'c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data_SlotCycle2(var) var

/* Access member 'SlotCycle2' of type 'c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data_SlotCycle2(var) (&var)

/* Access member 'SlotCycle3' of type 'c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data_SlotCycle3(var) var

/* Access member 'SlotCycle3' of type 'c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data_SlotCycle3(var) (&var)

/* Access member 'WakeCount1' of type 'c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data_WakeCount1(var) var

/* Access member 'WakeCount1' of type 'c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data_WakeCount1(var) (&var)

/* Access member 'WakeCount2' of type 'c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data_WakeCount2(var) var

/* Access member 'WakeCount2' of type 'c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data_WakeCount2(var) (&var)

/* Access member 'data' of type 'c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01' as a pointer */
#define PTR_c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01(var) var

/* Access member 'data01' of type 'c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode' as a pointer */
#define PTR_c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data */
typedef struct _c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET SlotCycle1; /* ODY01a *//*GBD01b*/
	ED_OCTET SlotCycle2; /* ODY01a *//*GBD01b*/
	ED_OCTET SlotCycle3; /* ODY01a *//*GBD01b*/
	ED_OCTET WakeCount1; /* ODY01a *//*GBD01b*/
	ED_OCTET WakeCount2; /* ODY01a *//*GBD01b*/

} c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01 */
typedef struct _c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01 {

	c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode {

	c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode;
#define INIT_c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode))
/*FRK03a*/
void FREE_c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode(c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode* sp);

/* Access member 'ValueID' of type 'c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_ValueID(var) (&var)

/* Access member 'MaskCount' of type 'c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_MaskCount(var) var

/* Access member 'MaskCount' of type 'c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_MaskCount(var) (&var)

/* Access member 'MaskPurpose' of type 'c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02_data_MaskPurpose(var) var

/* Access member 'MaskPurpose' of type 'c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02_data_MaskPurpose(var) (&var)

/* Access member 'PreMaskDuration' of type 'c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02_data_PreMaskDuration(var) var

/* Access member 'PreMaskDuration' of type 'c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02_data_PreMaskDuration(var) (&var)

/* Access member 'MaskDuration' of type 'c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02_data_MaskDuration(var) var

/* Access member 'MaskDuration' of type 'c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02_data_MaskDuration(var) (&var)

/* Access member 'PostMaskDuration' of type 'c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02_data_PostMaskDuration(var) var

/* Access member 'PostMaskDuration' of type 'c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02_data_PostMaskDuration(var) (&var)

/* Access member 'data' of type 'c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02' as a pointer */
#define PTR_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02_data(var) var

/* Access member 'data02' of type 'c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02(var) var

/* Access member 'data02' of type 'c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data' as a pointer */
#define PTR_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02(var) (&var)

/* Access member 'data' of type 'c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01' as a pointer */
#define PTR_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Inter_RAT_Quick_Idle_State_PagingMask' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01(var) var

/* Access member 'data01' of type 'c_RPD_Inter_RAT_Quick_Idle_State_PagingMask' as a pointer */
#define PTR_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02_data */
typedef struct _c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02_data {

	ED_OCTET MaskPurpose; /* ODY01a *//*GBD01b*/
	ED_SHORT PreMaskDuration; /* ODY01a *//*GBD01b*/
	ED_SHORT MaskDuration; /* ODY01a *//*GBD01b*/
	ED_SHORT PostMaskDuration; /* ODY01a *//*GBD01b*/

} c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02 */
typedef struct _c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02 {

	c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data */
typedef struct _c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET MaskCount; /* ODY01a *//*GBD01b*/
	c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02 data02;/*GFB09*//*GBD01b*/

} c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01 */
typedef struct _c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01 {

	c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Inter_RAT_Quick_Idle_State_PagingMask {

	c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Inter_RAT_Quick_Idle_State_PagingMask;
#define INIT_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Inter_RAT_Quick_Idle_State_PagingMask))
/*FRK03a*/
void FREE_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask(c_RPD_Inter_RAT_Quick_Idle_State_PagingMask* sp);

/* Access member 'ValueID' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data_ValueID(var) (&var)

/* Access member 'PilotIncrement' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data_PilotIncrement(var) var

/* Access member 'PilotIncrement' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data_PilotIncrement(var) (&var)

/* Access member 'SearchWindowActive' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data_SearchWindowActive(var) var

/* Access member 'SearchWindowActive' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data_SearchWindowActive(var) (&var)

/* Access member 'SearchWindowNeighbor' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data_SearchWindowNeighbor(var) var

/* Access member 'SearchWindowNeighbor' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data_SearchWindowNeighbor(var) (&var)

/* Access member 'SearchWindowRemaining' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data_SearchWindowRemaining(var) var

/* Access member 'SearchWindowRemaining' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data_SearchWindowRemaining(var) (&var)

/* Access member 'data' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01(var) var

/* Access member 'data01' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data */
typedef struct _c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET PilotIncrement; /* ODY01a *//*GBD01b*/
	ED_OCTET SearchWindowActive; /* ODY01a *//*GBD01b*/
	ED_OCTET SearchWindowNeighbor; /* ODY01a *//*GBD01b*/
	ED_OCTET SearchWindowRemaining; /* ODY01a *//*GBD01b*/

} c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01 */
typedef struct _c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01 {

	c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters {

	c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters;
#define INIT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters))
/*FRK03a*/
void FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters(c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters* sp);

/* Access member 'ValueID' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data_ValueID(var) (&var)

/* Access member 'PilotAdd' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data_PilotAdd(var) var

/* Access member 'PilotAdd' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data_PilotAdd(var) (&var)

/* Access member 'PilotCompare' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data_PilotCompare(var) var

/* Access member 'PilotCompare' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data_PilotCompare(var) (&var)

/* Access member 'PilotDrop' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data_PilotDrop(var) var

/* Access member 'PilotDrop' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data_PilotDrop(var) (&var)

/* Access member 'PilotDropTimer' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data_PilotDropTimer(var) var

/* Access member 'PilotDropTimer' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data_PilotDropTimer(var) (&var)

/* Access member 'DynamicThresholds' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data_DynamicThresholds(var) var

/* Access member 'DynamicThresholds' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data_DynamicThresholds(var) (&var)

/* Access member 'SoftSlope' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data_SoftSlope(var) var

/* Access member 'SoftSlope' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data_SoftSlope(var) (&var)

/* Access member 'AddIntercept' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data_AddIntercept(var) var

/* Access member 'AddIntercept' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data_AddIntercept(var) (&var)

/* Access member 'DropIntercept' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data_DropIntercept(var) var

/* Access member 'DropIntercept' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data_DropIntercept(var) (&var)

/* Access member 'NeighborMaxAge' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data_NeighborMaxAge(var) var

/* Access member 'NeighborMaxAge' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data_NeighborMaxAge(var) (&var)

/* Access member 'data' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01(var) var

/* Access member 'data01' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data */
typedef struct _c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET PilotAdd; /* ODY01a *//*GBD01b*/
	ED_OCTET PilotCompare; /* ODY01a *//*GBD01b*/
	ED_OCTET PilotDrop; /* ODY01a *//*GBD01b*/
	ED_OCTET PilotDropTimer; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN DynamicThresholds; /* ODY01a *//*GBD01b*/
	ED_OCTET SoftSlope; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN SoftSlope_Present;
	ED_OCTET AddIntercept; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN AddIntercept_Present;
	ED_OCTET DropIntercept; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN DropIntercept_Present;
	ED_OCTET NeighborMaxAge; /* ODY01a *//*GBD01b*/

} c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01 */
typedef struct _c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01 {

	c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters {

	c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters;
#define INIT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters))
/*FRK03a*/
void FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters(c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters* sp);

/* Access member 'ValueID' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_ValueID(var) (&var)

/* Access member 'BandClassCount' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_BandClassCount(var) var

/* Access member 'BandClassCount' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_BandClassCount(var) (&var)

/* Access member 'BandClass' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_BandClass(var) var

/* Access member 'BandClass' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_BandClass(var) (&var)

/* Access member 'InterFlexDuplexTag' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_InterFlexDuplexTag(var) var

/* Access member 'InterFlexDuplexTag' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_InterFlexDuplexTag(var) (&var)

/* Access member 'IntraFlexDuplexFlag' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_IntraFlexDuplexFlag(var) var

/* Access member 'IntraFlexDuplexFlag' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_IntraFlexDuplexFlag(var) (&var)

/* Access member 'BandSubClassCount' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_BandSubClassCount(var) var

/* Access member 'BandSubClassCount' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_BandSubClassCount(var) (&var)

/* Access member 'BandSubClass' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data_BandSubClass(var) var

/* Access member 'BandSubClass' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data_BandSubClass(var) (&var)

/* Access member 'data' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data(var) var

/* Access member 'data03' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03(var) var

/* Access member 'data03' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03(var) (&var)

/* Access member 'data' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data(var) var

/* Access member 'data02' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02(var) var

/* Access member 'data02' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02(var) (&var)

/* Access member 'MultiBandCount' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_MultiBandCount(var) var

/* Access member 'MultiBandCount' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_MultiBandCount(var) (&var)

/* Access member 'MultiBandBitMapCount' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_MultiBandBitMapCount(var) var

/* Access member 'MultiBandBitMapCount' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_MultiBandBitMapCount(var) (&var)

/* Access member 'MultiBandBitMap' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04_data' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04_data_MultiBandBitMap(var) var

/* Access member 'MultiBandBitMap' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04_data' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04_data_MultiBandBitMap(var) (&var)

/* Access member 'data' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04_data(var) var

/* Access member 'data04' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04(var) var

/* Access member 'data04' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04(var) (&var)

/* Access member 'data' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01(var) var

/* Access member 'data01' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data */
typedef struct _c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data {

	ED_OCTET BandSubClass; /* ODY01a *//*GBD01b*/

} c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03 */
typedef struct _c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03 {

	c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data */
typedef struct _c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data {

	ED_OCTET BandClass; /* ODY01a *//*GBD01b*/
	ED_OCTET InterFlexDuplexTag; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN IntraFlexDuplexFlag; /* ODY01a *//*GBD01b*/
	ED_OCTET BandSubClassCount; /* ODY01a *//*GBD01b*/
	c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03 data03;/*GFB09*//*GBD01b*/

} c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02 */
typedef struct _c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02 {

	c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02;

/* DEFINITION OF BINARY c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04_data_MultiBandBitMap */
typedef struct _c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04_data_MultiBandBitMap {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04_data_MultiBandBitMap;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04_data_MultiBandBitMap(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF SUB-STRUCTURE c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04_data */
typedef struct _c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04_data {

	c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04_data_MultiBandBitMap MultiBandBitMap; /* Static, variable size; bits needed 64 *//*GBD01b*/

} c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04 */
typedef struct _c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04 {

	c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data */
typedef struct _c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET BandClassCount; /* ODY01a *//*GBD01b*/
	c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02 data02;/*GFB09*//*GBD01b*/
	ED_OCTET MultiBandCount; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN MultiBandCount_Present;
	ED_OCTET MultiBandBitMapCount; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN MultiBandBitMapCount_Present;
	c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04 data04;/*GFB09*//*GBD01b*/

} c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01 */
typedef struct _c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01 {

	c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels {

	c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels;
#define INIT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels))
/*FRK03a*/
void FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels(c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels* sp);

/* Access member 'ValueID' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_ValueID(var) (&var)

/* Access member 'NumberofDRXPatterns' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_NumberofDRXPatterns(var) var

/* Access member 'NumberofDRXPatterns' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_NumberofDRXPatterns(var) (&var)

/* Access member 'SupportedDRXPattern' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02_data' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02_data_SupportedDRXPattern(var) var

/* Access member 'SupportedDRXPattern' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02_data' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02_data_SupportedDRXPattern(var) (&var)

/* Access member 'data' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02_data(var) var

/* Access member 'data02' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02(var) var

/* Access member 'data02' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02(var) (&var)

/* Access member 'data' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01(var) var

/* Access member 'data01' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02_data */
typedef struct _c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02_data {

	ED_OCTET SupportedDRXPattern; /* ODY01a *//*GBD01b*/

} c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02 */
typedef struct _c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02 {

	c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data */
typedef struct _c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET NumberofDRXPatterns; /* ODY01a *//*GBD01b*/
	c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02 data02;/*GFB09*//*GBD01b*/

} c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01 */
typedef struct _c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01 {

	c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns {

	c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns;
#define INIT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns))
/*FRK03a*/
void FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns(c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATINSP_INUSE_Sync' as a variable reference */
#define VAR_c_RPDCON_IRATINSP_INUSE_Sync_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATINSP_INUSE_Sync' as a pointer */
#define PTR_c_RPDCON_IRATINSP_INUSE_Sync_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATINSP_INUSE_Sync {

	c_RPDCON_IRATINSP_INUSE_Sync_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATINSP_INUSE_Sync;
#define INIT_c_RPDCON_IRATINSP_INUSE_Sync(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATINSP_INUSE_Sync))
/*FRK03a*/
void FREE_c_RPDCON_IRATINSP_INUSE_Sync(c_RPDCON_IRATINSP_INUSE_Sync* sp);

/* Access member 'contents' of type 'c_RPDSES_SL_UATIAssignment' as a variable reference */
#define VAR_c_RPDSES_SL_UATIAssignment_contents(var) var

/* Access member 'contents' of type 'c_RPDSES_SL_UATIAssignment' as a pointer */
#define PTR_c_RPDSES_SL_UATIAssignment_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDSES_SL_UATIAssignment {

	c_RPDSES_SL_UATIAssignment_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDSES_SL_UATIAssignment;
#define INIT_c_RPDSES_SL_UATIAssignment(sp) ED_RESET_MEM ((sp), sizeof (c_RPDSES_SL_UATIAssignment))
/*FRK03a*/
void FREE_c_RPDSES_SL_UATIAssignment(c_RPDSES_SL_UATIAssignment* sp);


/*-A----------------------------------*/
typedef struct _c_RPDSES_SL_InterRATMobilityIndication {

	int __Dummy_Field__; /* Added to avoid empty structures/unions/etc */
}	c_RPDSES_SL_InterRATMobilityIndication;
#define INIT_c_RPDSES_SL_InterRATMobilityIndication(sp) ED_RESET_MEM ((sp), sizeof (c_RPDSES_SL_InterRATMobilityIndication))
/*FRK03a*/
void FREE_c_RPDSES_SL_InterRATMobilityIndication(c_RPDSES_SL_InterRATMobilityIndication* sp);


/*-A----------------------------------*/
typedef struct _c_RPDSES_SL_InterRATMobilityAck {

	int __Dummy_Field__; /* Added to avoid empty structures/unions/etc */
}	c_RPDSES_SL_InterRATMobilityAck;
#define INIT_c_RPDSES_SL_InterRATMobilityAck(sp) ED_RESET_MEM ((sp), sizeof (c_RPDSES_SL_InterRATMobilityAck))
/*FRK03a*/
void FREE_c_RPDSES_SL_InterRATMobilityAck(c_RPDSES_SL_InterRATMobilityAck* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATSAP_INCFG_ConfigurationRequest' as a variable reference */
#define VAR_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATSAP_INCFG_ConfigurationRequest' as a pointer */
#define PTR_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATSAP_INCFG_ConfigurationRequest {

	c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATSAP_INCFG_ConfigurationRequest;
#define INIT_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATSAP_INCFG_ConfigurationRequest))
/*FRK03a*/
void FREE_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest(c_RPDCON_IRATSAP_INCFG_ConfigurationRequest* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATSAP_INCFG_ConfigurationResponse' as a variable reference */
#define VAR_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATSAP_INCFG_ConfigurationResponse' as a pointer */
#define PTR_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATSAP_INCFG_ConfigurationResponse {

	c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATSAP_INCFG_ConfigurationResponse;
#define INIT_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATSAP_INCFG_ConfigurationResponse))
/*FRK03a*/
void FREE_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse(c_RPDCON_IRATSAP_INCFG_ConfigurationResponse* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq' as a variable reference */
#define VAR_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq' as a pointer */
#define PTR_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq {

	c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq;
#define INIT_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq))
/*FRK03a*/
void FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq(c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenReq* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf' as a variable reference */
#define VAR_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf' as a pointer */
#define PTR_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf {

	c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf;
#define INIT_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf))
/*FRK03a*/
void FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf(c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenConf* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail' as a variable reference */
#define VAR_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail' as a pointer */
#define PTR_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail {

	c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail;
#define INIT_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail))
/*FRK03a*/
void FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail(c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenFail* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq' as a variable reference */
#define VAR_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq' as a pointer */
#define PTR_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq {

	c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq;
#define INIT_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq))
/*FRK03a*/
void FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq(c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseReq* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf' as a variable reference */
#define VAR_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf' as a pointer */
#define PTR_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf {

	c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf;
#define INIT_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf))
/*FRK03a*/
void FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf(c_RPDCON_IRATSAP_INUSE_AlternateLinkCloseConf* sp);


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq {

	int __Dummy_Field__; /* Added to avoid empty structures/unions/etc */
}	c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq;
#define INIT_c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq))
/*FRK03a*/
void FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq(c_RPDCON_IRATSAP_INUSE_AlternateLinkPageReq* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete' as a variable reference */
#define VAR_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete' as a pointer */
#define PTR_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete {

	c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete;
#define INIT_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete))
/*FRK03a*/
void FREE_c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete(c_RPDCON_IRATSAP_INUSE_AlternateLinkOpenComplete* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATINSP_INCFG_ConfigurationRequest' as a variable reference */
#define VAR_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATINSP_INCFG_ConfigurationRequest' as a pointer */
#define PTR_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATINSP_INCFG_ConfigurationRequest {

	c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATINSP_INCFG_ConfigurationRequest;
#define INIT_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATINSP_INCFG_ConfigurationRequest))
/*FRK03a*/
void FREE_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest(c_RPDCON_IRATINSP_INCFG_ConfigurationRequest* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATINSP_INCFG_ConfigurationResponse' as a variable reference */
#define VAR_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATINSP_INCFG_ConfigurationResponse' as a pointer */
#define PTR_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATINSP_INCFG_ConfigurationResponse {

	c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATINSP_INCFG_ConfigurationResponse;
#define INIT_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATINSP_INCFG_ConfigurationResponse))
/*FRK03a*/
void FREE_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse(c_RPDCON_IRATINSP_INCFG_ConfigurationResponse* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATISP_INCFG_ConfigurationRequest' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATISP_INCFG_ConfigurationRequest' as a pointer */
#define PTR_c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATISP_INCFG_ConfigurationRequest {

	c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATISP_INCFG_ConfigurationRequest;
#define INIT_c_RPDCON_IRATISP_INCFG_ConfigurationRequest(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATISP_INCFG_ConfigurationRequest))
/*FRK03a*/
void FREE_c_RPDCON_IRATISP_INCFG_ConfigurationRequest(c_RPDCON_IRATISP_INCFG_ConfigurationRequest* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATISP_INCFG_ConfigurationResponse' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATISP_INCFG_ConfigurationResponse' as a pointer */
#define PTR_c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATISP_INCFG_ConfigurationResponse {

	c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATISP_INCFG_ConfigurationResponse;
#define INIT_c_RPDCON_IRATISP_INCFG_ConfigurationResponse(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATISP_INCFG_ConfigurationResponse))
/*FRK03a*/
void FREE_c_RPDCON_IRATISP_INCFG_ConfigurationResponse(c_RPDCON_IRATISP_INCFG_ConfigurationResponse* sp);


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATISP_INUSE_Page {

	int __Dummy_Field__; /* Added to avoid empty structures/unions/etc */
}	c_RPDCON_IRATISP_INUSE_Page;
#define INIT_c_RPDCON_IRATISP_INUSE_Page(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATISP_INUSE_Page))
/*FRK03a*/
void FREE_c_RPDCON_IRATISP_INUSE_Page(c_RPDCON_IRATISP_INUSE_Page* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATISP_INUSE_ConnectionRequest' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATISP_INUSE_ConnectionRequest' as a pointer */
#define PTR_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATISP_INUSE_ConnectionRequest {

	c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATISP_INUSE_ConnectionRequest;
#define INIT_c_RPDCON_IRATISP_INUSE_ConnectionRequest(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATISP_INUSE_ConnectionRequest))
/*FRK03a*/
void FREE_c_RPDCON_IRATISP_INUSE_ConnectionRequest(c_RPDCON_IRATISP_INUSE_ConnectionRequest* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATISP_INUSE_ConnectionDeny' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INUSE_ConnectionDeny_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATISP_INUSE_ConnectionDeny' as a pointer */
#define PTR_c_RPDCON_IRATISP_INUSE_ConnectionDeny_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATISP_INUSE_ConnectionDeny {

	c_RPDCON_IRATISP_INUSE_ConnectionDeny_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATISP_INUSE_ConnectionDeny;
#define INIT_c_RPDCON_IRATISP_INUSE_ConnectionDeny(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATISP_INUSE_ConnectionDeny))
/*FRK03a*/
void FREE_c_RPDCON_IRATISP_INUSE_ConnectionDeny(c_RPDCON_IRATISP_INUSE_ConnectionDeny* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest' as a pointer */
#define PTR_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest {

	c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest;
#define INIT_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest))
/*FRK03a*/
void FREE_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest(c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept' as a pointer */
#define PTR_c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept {

	c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept;
#define INIT_c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept))
/*FRK03a*/
void FREE_c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept(c_RPDCON_IRATISP_INUSE_AttributeUpdateAccept* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATISP_INUSE_AttributeUpdateReject' as a variable reference */
#define VAR_c_RPDCON_IRATISP_INUSE_AttributeUpdateReject_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATISP_INUSE_AttributeUpdateReject' as a pointer */
#define PTR_c_RPDCON_IRATISP_INUSE_AttributeUpdateReject_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATISP_INUSE_AttributeUpdateReject {

	c_RPDCON_IRATISP_INUSE_AttributeUpdateReject_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATISP_INUSE_AttributeUpdateReject;
#define INIT_c_RPDCON_IRATISP_INUSE_AttributeUpdateReject(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATISP_INUSE_AttributeUpdateReject))
/*FRK03a*/
void FREE_c_RPDCON_IRATISP_INUSE_AttributeUpdateReject(c_RPDCON_IRATISP_INUSE_AttributeUpdateReject* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATRUP_INCFG_ConfigurationRequest' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATRUP_INCFG_ConfigurationRequest' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATRUP_INCFG_ConfigurationRequest {

	c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATRUP_INCFG_ConfigurationRequest;
#define INIT_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATRUP_INCFG_ConfigurationRequest))
/*FRK03a*/
void FREE_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest(c_RPDCON_IRATRUP_INCFG_ConfigurationRequest* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATRUP_INCFG_ConfigurationResponse' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATRUP_INCFG_ConfigurationResponse' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATRUP_INCFG_ConfigurationResponse {

	c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATRUP_INCFG_ConfigurationResponse;
#define INIT_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATRUP_INCFG_ConfigurationResponse))
/*FRK03a*/
void FREE_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse(c_RPDCON_IRATRUP_INCFG_ConfigurationResponse* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATRUP_INUSE_RouteUpdate {

	c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATRUP_INUSE_RouteUpdate;
#define INIT_c_RPDCON_IRATRUP_INUSE_RouteUpdate(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATRUP_INUSE_RouteUpdate))
/*FRK03a*/
void FREE_c_RPDCON_IRATRUP_INUSE_RouteUpdate(c_RPDCON_IRATRUP_INUSE_RouteUpdate* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment {

	c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment;
#define INIT_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment))
/*FRK03a*/
void FREE_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment(c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete {

	c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete;
#define INIT_c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete))
/*FRK03a*/
void FREE_c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete(c_RPDCON_IRATRUP_INUSE_TrafficChannelComplete* sp);


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATRUP_INUSE_ResetReport {

	int __Dummy_Field__; /* Added to avoid empty structures/unions/etc */
}	c_RPDCON_IRATRUP_INUSE_ResetReport;
#define INIT_c_RPDCON_IRATRUP_INUSE_ResetReport(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATRUP_INUSE_ResetReport))
/*FRK03a*/
void FREE_c_RPDCON_IRATRUP_INUSE_ResetReport(c_RPDCON_IRATRUP_INUSE_ResetReport* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATRUP_INUSE_NeighborList' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_NeighborList_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATRUP_INUSE_NeighborList {

	c_RPDCON_IRATRUP_INUSE_NeighborList_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATRUP_INUSE_NeighborList;
#define INIT_c_RPDCON_IRATRUP_INUSE_NeighborList(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATRUP_INUSE_NeighborList))
/*FRK03a*/
void FREE_c_RPDCON_IRATRUP_INUSE_NeighborList(c_RPDCON_IRATRUP_INUSE_NeighborList* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATRUP_INUSE_AttributeOverride' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATRUP_INUSE_AttributeOverride' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATRUP_INUSE_AttributeOverride {

	c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATRUP_INUSE_AttributeOverride;
#define INIT_c_RPDCON_IRATRUP_INUSE_AttributeOverride(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATRUP_INUSE_AttributeOverride))
/*FRK03a*/
void FREE_c_RPDCON_IRATRUP_INUSE_AttributeOverride(c_RPDCON_IRATRUP_INUSE_AttributeOverride* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse {

	c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse;
#define INIT_c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse))
/*FRK03a*/
void FREE_c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse(c_RPDCON_IRATRUP_INUSE_AttributeOverrideResponse* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest {

	c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest;
#define INIT_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest))
/*FRK03a*/
void FREE_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest(c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest {

	c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest;
#define INIT_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest))
/*FRK03a*/
void FREE_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest(c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept {

	c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept;
#define INIT_c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept))
/*FRK03a*/
void FREE_c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept(c_RPDCON_IRATRUP_INUSE_AttributeUpdateAccept* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject' as a variable reference */
#define VAR_c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject' as a pointer */
#define PTR_c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject {

	c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject;
#define INIT_c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject))
/*FRK03a*/
void FREE_c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject(c_RPDCON_IRATRUP_INUSE_AttributeUpdateReject* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATOMP_INCFG_ConfigurationRequest' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATOMP_INCFG_ConfigurationRequest' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATOMP_INCFG_ConfigurationRequest {

	c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATOMP_INCFG_ConfigurationRequest;
#define INIT_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATOMP_INCFG_ConfigurationRequest))
/*FRK03a*/
void FREE_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest(c_RPDCON_IRATOMP_INCFG_ConfigurationRequest* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATOMP_INCFG_ConfigurationResponse' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATOMP_INCFG_ConfigurationResponse' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATOMP_INCFG_ConfigurationResponse {

	c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATOMP_INCFG_ConfigurationResponse;
#define INIT_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATOMP_INCFG_ConfigurationResponse))
/*FRK03a*/
void FREE_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse(c_RPDCON_IRATOMP_INCFG_ConfigurationResponse* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATOMP_INUSE_QuickConfig' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATOMP_INUSE_QuickConfig {

	c_RPDCON_IRATOMP_INUSE_QuickConfig_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATOMP_INUSE_QuickConfig;
#define INIT_c_RPDCON_IRATOMP_INUSE_QuickConfig(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATOMP_INUSE_QuickConfig))
/*FRK03a*/
void FREE_c_RPDCON_IRATOMP_INUSE_QuickConfig(c_RPDCON_IRATOMP_INUSE_QuickConfig* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATOMP_INUSE_SectorParameters' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATOMP_INUSE_SectorParameters {

	c_RPDCON_IRATOMP_INUSE_SectorParameters_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATOMP_INUSE_SectorParameters;
#define INIT_c_RPDCON_IRATOMP_INUSE_SectorParameters(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATOMP_INUSE_SectorParameters))
/*FRK03a*/
void FREE_c_RPDCON_IRATOMP_INUSE_SectorParameters(c_RPDCON_IRATOMP_INUSE_SectorParameters* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters {

	c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters;
#define INIT_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters))
/*FRK03a*/
void FREE_c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters(c_RPDCON_IRATOMP_INUSE_HRPDSilenceParameters* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList' as a variable reference */
#define VAR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList' as a pointer */
#define PTR_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList {

	c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList;
#define INIT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList))
/*FRK03a*/
void FREE_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList(c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList* sp);

/* Access member 'contents' of type 'c_RPDCON_DSAP_INCFG_ConfigurationRequest' as a variable reference */
#define VAR_c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_DSAP_INCFG_ConfigurationRequest' as a pointer */
#define PTR_c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_DSAP_INCFG_ConfigurationRequest {

	c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_DSAP_INCFG_ConfigurationRequest;
#define INIT_c_RPDCON_DSAP_INCFG_ConfigurationRequest(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_DSAP_INCFG_ConfigurationRequest))
/*FRK03a*/
void FREE_c_RPDCON_DSAP_INCFG_ConfigurationRequest(c_RPDCON_DSAP_INCFG_ConfigurationRequest* sp);

/* Access member 'contents' of type 'c_RPDCON_DSAP_INCFG_ConfigurationResponse' as a variable reference */
#define VAR_c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_DSAP_INCFG_ConfigurationResponse' as a pointer */
#define PTR_c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_DSAP_INCFG_ConfigurationResponse {

	c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_DSAP_INCFG_ConfigurationResponse;
#define INIT_c_RPDCON_DSAP_INCFG_ConfigurationResponse(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_DSAP_INCFG_ConfigurationResponse))
/*FRK03a*/
void FREE_c_RPDCON_DSAP_INCFG_ConfigurationResponse(c_RPDCON_DSAP_INCFG_ConfigurationResponse* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATQISP_INCFG_ConfigurationRequest' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATQISP_INCFG_ConfigurationRequest' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATQISP_INCFG_ConfigurationRequest {

	c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATQISP_INCFG_ConfigurationRequest;
#define INIT_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATQISP_INCFG_ConfigurationRequest))
/*FRK03a*/
void FREE_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest(c_RPDCON_IRATQISP_INCFG_ConfigurationRequest* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATQISP_INCFG_ConfigurationResponse' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATQISP_INCFG_ConfigurationResponse' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATQISP_INCFG_ConfigurationResponse {

	c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATQISP_INCFG_ConfigurationResponse;
#define INIT_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATQISP_INCFG_ConfigurationResponse))
/*FRK03a*/
void FREE_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse(c_RPDCON_IRATQISP_INCFG_ConfigurationResponse* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATQISP_INUSE_Page' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_Page_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATQISP_INUSE_Page' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_Page_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATQISP_INUSE_Page {

	c_RPDCON_IRATQISP_INUSE_Page_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATQISP_INUSE_Page;
#define INIT_c_RPDCON_IRATQISP_INUSE_Page(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATQISP_INUSE_Page))
/*FRK03a*/
void FREE_c_RPDCON_IRATQISP_INUSE_Page(c_RPDCON_IRATQISP_INUSE_Page* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATQISP_INUSE_ConnectionRequest' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATQISP_INUSE_ConnectionRequest' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATQISP_INUSE_ConnectionRequest {

	c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATQISP_INUSE_ConnectionRequest;
#define INIT_c_RPDCON_IRATQISP_INUSE_ConnectionRequest(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATQISP_INUSE_ConnectionRequest))
/*FRK03a*/
void FREE_c_RPDCON_IRATQISP_INUSE_ConnectionRequest(c_RPDCON_IRATQISP_INUSE_ConnectionRequest* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATQISP_INUSE_ConnectionDeny' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_ConnectionDeny_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATQISP_INUSE_ConnectionDeny' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_ConnectionDeny_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATQISP_INUSE_ConnectionDeny {

	c_RPDCON_IRATQISP_INUSE_ConnectionDeny_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATQISP_INUSE_ConnectionDeny;
#define INIT_c_RPDCON_IRATQISP_INUSE_ConnectionDeny(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATQISP_INUSE_ConnectionDeny))
/*FRK03a*/
void FREE_c_RPDCON_IRATQISP_INUSE_ConnectionDeny(c_RPDCON_IRATQISP_INUSE_ConnectionDeny* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATQISP_INUSE_QuickPage' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_QuickPage_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATQISP_INUSE_QuickPage' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_QuickPage_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATQISP_INUSE_QuickPage {

	c_RPDCON_IRATQISP_INUSE_QuickPage_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATQISP_INUSE_QuickPage;
#define INIT_c_RPDCON_IRATQISP_INUSE_QuickPage(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATQISP_INUSE_QuickPage))
/*FRK03a*/
void FREE_c_RPDCON_IRATQISP_INUSE_QuickPage(c_RPDCON_IRATQISP_INUSE_QuickPage* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest {

	c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest;
#define INIT_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest))
/*FRK03a*/
void FREE_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest(c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept {

	c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept;
#define INIT_c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept))
/*FRK03a*/
void FREE_c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept(c_RPDCON_IRATQISP_INUSE_AttributeUpdateAccept* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject' as a variable reference */
#define VAR_c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject' as a pointer */
#define PTR_c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject {

	c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject;
#define INIT_c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject))
/*FRK03a*/
void FREE_c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject(c_RPDCON_IRATQISP_INUSE_AttributeUpdateReject* sp);

/* Access member 'contents' of type 'c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest {

	c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest;
#define INIT_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest))
/*FRK03a*/
void FREE_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest(c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest* sp);

/* Access member 'contents' of type 'c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse {

	c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse;
#define INIT_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse))
/*FRK03a*/
void FREE_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse(c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse* sp);

/* Access member 'contents' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_S1IRATRUP_INUSE_RouteUpdate {

	c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_S1IRATRUP_INUSE_RouteUpdate;
#define INIT_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_S1IRATRUP_INUSE_RouteUpdate))
/*FRK03a*/
void FREE_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate(c_RPDCON_S1IRATRUP_INUSE_RouteUpdate* sp);

/* Access member 'contents' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment {

	c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment;
#define INIT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment))
/*FRK03a*/
void FREE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment(c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment* sp);

/* Access member 'contents' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete {

	c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete;
#define INIT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete))
/*FRK03a*/
void FREE_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete(c_RPDCON_S1IRATRUP_INUSE_TrafficChannelComplete* sp);


/*-A----------------------------------*/
typedef struct _c_RPDCON_S1IRATRUP_INUSE_ResetReport {

	int __Dummy_Field__; /* Added to avoid empty structures/unions/etc */
}	c_RPDCON_S1IRATRUP_INUSE_ResetReport;
#define INIT_c_RPDCON_S1IRATRUP_INUSE_ResetReport(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_S1IRATRUP_INUSE_ResetReport))
/*FRK03a*/
void FREE_c_RPDCON_S1IRATRUP_INUSE_ResetReport(c_RPDCON_S1IRATRUP_INUSE_ResetReport* sp);

/* Access member 'contents' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_S1IRATRUP_INUSE_NeighborList {

	c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_S1IRATRUP_INUSE_NeighborList;
#define INIT_c_RPDCON_S1IRATRUP_INUSE_NeighborList(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_S1IRATRUP_INUSE_NeighborList))
/*FRK03a*/
void FREE_c_RPDCON_S1IRATRUP_INUSE_NeighborList(c_RPDCON_S1IRATRUP_INUSE_NeighborList* sp);

/* Access member 'contents' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest {

	c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest;
#define INIT_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest))
/*FRK03a*/
void FREE_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest(c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest* sp);

/* Access member 'contents' of type 'c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest {

	c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest;
#define INIT_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest))
/*FRK03a*/
void FREE_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest(c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest* sp);

/* Access member 'contents' of type 'c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept {

	c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept;
#define INIT_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept))
/*FRK03a*/
void FREE_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept(c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateAccept* sp);

/* Access member 'contents' of type 'c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject' as a variable reference */
#define VAR_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject' as a pointer */
#define PTR_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject {

	c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject;
#define INIT_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject))
/*FRK03a*/
void FREE_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject(c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateReject* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest {

	c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest;
#define INIT_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest))
/*FRK03a*/
void FREE_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest(c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse {

	c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse;
#define INIT_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse))
/*FRK03a*/
void FREE_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse(c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig {

	c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig;
#define INIT_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig))
/*FRK03a*/
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig(c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters {

	c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters;
#define INIT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters))
/*FRK03a*/
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters(c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters {

	c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters;
#define INIT_c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters))
/*FRK03a*/
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters(c_RPDCON_IRATOMPCS0024B_INUSE_HRPDSilenceParameters* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList {

	c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList;
#define INIT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList))
/*FRK03a*/
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList(c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation {

	c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation;
#define INIT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation))
/*FRK03a*/
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation(c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification {

	c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification;
#define INIT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification))
/*FRK03a*/
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification(c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification* sp);

/* Access member 'contents' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText' as a variable reference */
#define VAR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents(var) var

/* Access member 'contents' of type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText' as a pointer */
#define PTR_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText {

	c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText;
#define INIT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText(sp) ED_RESET_MEM ((sp), sizeof (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText))
/*FRK03a*/
void FREE_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText(c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText* sp);

/* Access member 'contents' of type 'c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters' as a variable reference */
#define VAR_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents(var) var

/* Access member 'contents' of type 'c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters' as a pointer */
#define PTR_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters {

	c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters;
#define INIT_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters(sp) ED_RESET_MEM ((sp), sizeof (c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters))
/*FRK03a*/
void FREE_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters(c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters* sp);

/* Access member 'contents' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters' as a variable reference */
#define VAR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents(var) var

/* Access member 'contents' of type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters' as a pointer */
#define PTR_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters {

	c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents contents; /* ODY01a *//*GBD01b*/

}	c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters;
#define INIT_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters(sp) ED_RESET_MEM ((sp), sizeof (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters))
/*FRK03a*/
void FREE_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters(c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters* sp);

/* Access member 'AttributeId' of type 'c_RPD_Session_Layer_Attributes' as a variable reference */
#define VAR_c_RPD_Session_Layer_Attributes_AttributeId(var) var

/* Access member 'AttributeId' of type 'c_RPD_Session_Layer_Attributes' as a pointer */
#define PTR_c_RPD_Session_Layer_Attributes_AttributeId(var) (&var)

/* Access member 'NN' of type 'c_RPD_Session_Layer_Attributes' as a variable reference */
#define VAR_c_RPD_Session_Layer_Attributes_NN(var) var

/* Access member 'NN' of type 'c_RPD_Session_Layer_Attributes' as a pointer */
#define PTR_c_RPD_Session_Layer_Attributes_NN(var) (&var)

/* Access member 'Value' of type 'c_RPD_Session_Layer_Attributes' as a variable reference */
#define VAR_c_RPD_Session_Layer_Attributes_Value(var) var

/* Access member 'Value' of type 'c_RPD_Session_Layer_Attributes' as a pointer */
#define PTR_c_RPD_Session_Layer_Attributes_Value(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPD_Session_Layer_Attributes {

	ED_LONG AttributeId; /* ODY01a *//*GBD01b*/
	ED_LONG NN; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN NN_Present;
	ED_LONG Value; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Value_Present;

}	c_RPD_Session_Layer_Attributes;
#define INIT_c_RPD_Session_Layer_Attributes(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Session_Layer_Attributes))
/*FRK03a*/
void FREE_c_RPD_Session_Layer_Attributes(c_RPD_Session_Layer_Attributes* sp);
#define SETPRESENT_c_RPD_Session_Layer_Attributes_NN(sp,present) ((sp)->NN_Present = present)
#define GETPRESENT_c_RPD_Session_Layer_Attributes_NN(sp) ((sp)->NN_Present)
#define SETPRESENT_c_RPD_Session_Layer_Attributes_Value(sp,present) ((sp)->Value_Present = present)
#define GETPRESENT_c_RPD_Session_Layer_Attributes_Value(sp) ((sp)->Value_Present)

/* Access member 'AttributeId' of type 'c_RPD_Inter_RAT_Idle_State' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Idle_State_AttributeId(var) var

/* Access member 'AttributeId' of type 'c_RPD_Inter_RAT_Idle_State' as a pointer */
#define PTR_c_RPD_Inter_RAT_Idle_State_AttributeId(var) (&var)

/* Access member 'NN' of type 'c_RPD_Inter_RAT_Idle_State' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Idle_State_NN(var) var

/* Access member 'NN' of type 'c_RPD_Inter_RAT_Idle_State' as a pointer */
#define PTR_c_RPD_Inter_RAT_Idle_State_NN(var) (&var)

/* Access member 'Value' of type 'c_RPD_Inter_RAT_Idle_State' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Idle_State_Value(var) var

/* Access member 'Value' of type 'c_RPD_Inter_RAT_Idle_State' as a pointer */
#define PTR_c_RPD_Inter_RAT_Idle_State_Value(var) (&var)

/* Access member 'PreferredControlChannelCycle' of type 'c_RPD_Inter_RAT_Idle_State_complex' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Idle_State_complex_PreferredControlChannelCycle(var) (*var)

/* Access member 'PreferredControlChannelCycle' of type 'c_RPD_Inter_RAT_Idle_State_complex' as a pointer */
#define PTR_c_RPD_Inter_RAT_Idle_State_complex_PreferredControlChannelCycle(var) var

/* Access member 'SlottedMode' of type 'c_RPD_Inter_RAT_Idle_State_complex' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Idle_State_complex_SlottedMode(var) (*var)

/* Access member 'SlottedMode' of type 'c_RPD_Inter_RAT_Idle_State_complex' as a pointer */
#define PTR_c_RPD_Inter_RAT_Idle_State_complex_SlottedMode(var) var

/* Access member 'PagingMask' of type 'c_RPD_Inter_RAT_Idle_State_complex' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Idle_State_complex_PagingMask(var) (*var)

/* Access member 'PagingMask' of type 'c_RPD_Inter_RAT_Idle_State_complex' as a pointer */
#define PTR_c_RPD_Inter_RAT_Idle_State_complex_PagingMask(var) var

/* Access member 'complex' of type 'c_RPD_Inter_RAT_Idle_State' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Idle_State_complex(var) var

/* Access member 'complex' of type 'c_RPD_Inter_RAT_Idle_State' as a pointer */
#define PTR_c_RPD_Inter_RAT_Idle_State_complex(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Inter_RAT_Idle_State_complex */
typedef enum {
	U_c_RPD_Inter_RAT_Idle_State_complex_NONE,
	U_c_RPD_Inter_RAT_Idle_State_complex_PreferredControlChannelCycle,
	U_c_RPD_Inter_RAT_Idle_State_complex_SlottedMode,
	U_c_RPD_Inter_RAT_Idle_State_complex_PagingMask
} TPRESENT_c_RPD_Inter_RAT_Idle_State_complex;

typedef struct _c_RPD_Inter_RAT_Idle_State_complex {

	TPRESENT_c_RPD_Inter_RAT_Idle_State_complex Present;
	union {
		c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle *PreferredControlChannelCycle; /* ODY01 *//*GBD01b*/
	
		c_RPD_Inter_RAT_Idle_State_SlottedMode *SlottedMode; /* ODY01 *//*GBD01b*/
	
		c_RPD_Inter_RAT_Idle_State_PagingMask *PagingMask; /* ODY01 *//*GBD01b*/
	
	} u;

} c_RPD_Inter_RAT_Idle_State_complex;


/*-A----------------------------------*/
typedef struct _c_RPD_Inter_RAT_Idle_State {

	ED_LONG AttributeId; /* ODY01a *//*GBD01b*/
	ED_LONG NN; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN NN_Present;
	ED_LONG Value; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Value_Present;
	c_RPD_Inter_RAT_Idle_State_complex complex;/*GBD01b*/

}	c_RPD_Inter_RAT_Idle_State;
#define INIT_c_RPD_Inter_RAT_Idle_State(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Inter_RAT_Idle_State))
/*FRK03a*/
void FREE_c_RPD_Inter_RAT_Idle_State(c_RPD_Inter_RAT_Idle_State* sp);
#define SETPRESENT_c_RPD_Inter_RAT_Idle_State_NN(sp,present) ((sp)->NN_Present = present)
#define GETPRESENT_c_RPD_Inter_RAT_Idle_State_NN(sp) ((sp)->NN_Present)
#define SETPRESENT_c_RPD_Inter_RAT_Idle_State_Value(sp,present) ((sp)->Value_Present = present)
#define GETPRESENT_c_RPD_Inter_RAT_Idle_State_Value(sp) ((sp)->Value_Present)

/* Access member 'AttributeId' of type 'c_RPD_Inter_RAT_Route_Update' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_AttributeId(var) var

/* Access member 'AttributeId' of type 'c_RPD_Inter_RAT_Route_Update' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_AttributeId(var) (&var)

/* Access member 'NN' of type 'c_RPD_Inter_RAT_Route_Update' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_NN(var) var

/* Access member 'NN' of type 'c_RPD_Inter_RAT_Route_Update' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_NN(var) (&var)

/* Access member 'Value' of type 'c_RPD_Inter_RAT_Route_Update' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_Value(var) var

/* Access member 'Value' of type 'c_RPD_Inter_RAT_Route_Update' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_Value(var) (&var)

/* Access member 'SearchParameters' of type 'c_RPD_Inter_RAT_Route_Update_complex' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_complex_SearchParameters(var) (*var)

/* Access member 'SearchParameters' of type 'c_RPD_Inter_RAT_Route_Update_complex' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_complex_SearchParameters(var) var

/* Access member 'SetManagementSameChannelParameters' of type 'c_RPD_Inter_RAT_Route_Update_complex' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_complex_SetManagementSameChannelParameters(var) (*var)

/* Access member 'SetManagementSameChannelParameters' of type 'c_RPD_Inter_RAT_Route_Update_complex' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_complex_SetManagementSameChannelParameters(var) var

/* Access member 'SetManagementDifferentChannelParameters' of type 'c_RPD_Inter_RAT_Route_Update_complex' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_complex_SetManagementDifferentChannelParameters(var) (*var)

/* Access member 'SetManagementDifferentChannelParameters' of type 'c_RPD_Inter_RAT_Route_Update_complex' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_complex_SetManagementDifferentChannelParameters(var) var

/* Access member 'SupportedCDMAChannels' of type 'c_RPD_Inter_RAT_Route_Update_complex' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_complex_SupportedCDMAChannels(var) (*var)

/* Access member 'SupportedCDMAChannels' of type 'c_RPD_Inter_RAT_Route_Update_complex' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_complex_SupportedCDMAChannels(var) var

/* Access member 'complex' of type 'c_RPD_Inter_RAT_Route_Update' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Route_Update_complex(var) var

/* Access member 'complex' of type 'c_RPD_Inter_RAT_Route_Update' as a pointer */
#define PTR_c_RPD_Inter_RAT_Route_Update_complex(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Inter_RAT_Route_Update_complex */
typedef enum {
	U_c_RPD_Inter_RAT_Route_Update_complex_NONE,
	U_c_RPD_Inter_RAT_Route_Update_complex_SearchParameters,
	U_c_RPD_Inter_RAT_Route_Update_complex_SetManagementSameChannelParameters,
	U_c_RPD_Inter_RAT_Route_Update_complex_SetManagementDifferentChannelParameters,
	U_c_RPD_Inter_RAT_Route_Update_complex_SupportedCDMAChannels
} TPRESENT_c_RPD_Inter_RAT_Route_Update_complex;

typedef struct _c_RPD_Inter_RAT_Route_Update_complex {

	TPRESENT_c_RPD_Inter_RAT_Route_Update_complex Present;
	union {
		c_RPD_Inter_RAT_Route_Update_SearchParameters *SearchParameters; /* ODY01 *//*GBD01b*/
	
		c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters *SetManagementSameChannelParameters; /* ODY01 *//*GBD01b*/
	
		c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters *SetManagementDifferentChannelParameters; /* ODY01 *//*GBD01b*/
	
		c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels *SupportedCDMAChannels; /* ODY01 *//*GBD01b*/
	
	} u;

} c_RPD_Inter_RAT_Route_Update_complex;


/*-A----------------------------------*/
typedef struct _c_RPD_Inter_RAT_Route_Update {

	ED_LONG AttributeId; /* ODY01a *//*GBD01b*/
	ED_LONG NN; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN NN_Present;
	ED_LONG Value; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Value_Present;
	c_RPD_Inter_RAT_Route_Update_complex complex;/*GBD01b*/

}	c_RPD_Inter_RAT_Route_Update;
#define INIT_c_RPD_Inter_RAT_Route_Update(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Inter_RAT_Route_Update))
/*FRK03a*/
void FREE_c_RPD_Inter_RAT_Route_Update(c_RPD_Inter_RAT_Route_Update* sp);
#define SETPRESENT_c_RPD_Inter_RAT_Route_Update_NN(sp,present) ((sp)->NN_Present = present)
#define GETPRESENT_c_RPD_Inter_RAT_Route_Update_NN(sp) ((sp)->NN_Present)
#define SETPRESENT_c_RPD_Inter_RAT_Route_Update_Value(sp,present) ((sp)->Value_Present = present)
#define GETPRESENT_c_RPD_Inter_RAT_Route_Update_Value(sp) ((sp)->Value_Present)

/* Access member 'AttributeId' of type 'c_RPD_Inter_RAT_Overhead_Messages' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Overhead_Messages_AttributeId(var) var

/* Access member 'AttributeId' of type 'c_RPD_Inter_RAT_Overhead_Messages' as a pointer */
#define PTR_c_RPD_Inter_RAT_Overhead_Messages_AttributeId(var) (&var)

/* Access member 'NN' of type 'c_RPD_Inter_RAT_Overhead_Messages' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Overhead_Messages_NN(var) var

/* Access member 'NN' of type 'c_RPD_Inter_RAT_Overhead_Messages' as a pointer */
#define PTR_c_RPD_Inter_RAT_Overhead_Messages_NN(var) (&var)

/* Access member 'Value' of type 'c_RPD_Inter_RAT_Overhead_Messages' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Overhead_Messages_Value(var) var

/* Access member 'Value' of type 'c_RPD_Inter_RAT_Overhead_Messages' as a pointer */
#define PTR_c_RPD_Inter_RAT_Overhead_Messages_Value(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPD_Inter_RAT_Overhead_Messages {

	ED_LONG AttributeId; /* ODY01a *//*GBD01b*/
	ED_LONG NN; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN NN_Present;
	ED_LONG Value; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Value_Present;

}	c_RPD_Inter_RAT_Overhead_Messages;
#define INIT_c_RPD_Inter_RAT_Overhead_Messages(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Inter_RAT_Overhead_Messages))
/*FRK03a*/
void FREE_c_RPD_Inter_RAT_Overhead_Messages(c_RPD_Inter_RAT_Overhead_Messages* sp);
#define SETPRESENT_c_RPD_Inter_RAT_Overhead_Messages_NN(sp,present) ((sp)->NN_Present = present)
#define GETPRESENT_c_RPD_Inter_RAT_Overhead_Messages_NN(sp) ((sp)->NN_Present)
#define SETPRESENT_c_RPD_Inter_RAT_Overhead_Messages_Value(sp,present) ((sp)->Value_Present = present)
#define GETPRESENT_c_RPD_Inter_RAT_Overhead_Messages_Value(sp) ((sp)->Value_Present)

/* Access member 'AttributeId' of type 'c_RPD_Inter_RAT_Quick_Idle_State' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Quick_Idle_State_AttributeId(var) var

/* Access member 'AttributeId' of type 'c_RPD_Inter_RAT_Quick_Idle_State' as a pointer */
#define PTR_c_RPD_Inter_RAT_Quick_Idle_State_AttributeId(var) (&var)

/* Access member 'NN' of type 'c_RPD_Inter_RAT_Quick_Idle_State' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Quick_Idle_State_NN(var) var

/* Access member 'NN' of type 'c_RPD_Inter_RAT_Quick_Idle_State' as a pointer */
#define PTR_c_RPD_Inter_RAT_Quick_Idle_State_NN(var) (&var)

/* Access member 'Value' of type 'c_RPD_Inter_RAT_Quick_Idle_State' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Quick_Idle_State_Value(var) var

/* Access member 'Value' of type 'c_RPD_Inter_RAT_Quick_Idle_State' as a pointer */
#define PTR_c_RPD_Inter_RAT_Quick_Idle_State_Value(var) (&var)

/* Access member 'PreferredControlChannelCycle' of type 'c_RPD_Inter_RAT_Quick_Idle_State_complex' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Quick_Idle_State_complex_PreferredControlChannelCycle(var) (*var)

/* Access member 'PreferredControlChannelCycle' of type 'c_RPD_Inter_RAT_Quick_Idle_State_complex' as a pointer */
#define PTR_c_RPD_Inter_RAT_Quick_Idle_State_complex_PreferredControlChannelCycle(var) var

/* Access member 'SlottedMode' of type 'c_RPD_Inter_RAT_Quick_Idle_State_complex' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Quick_Idle_State_complex_SlottedMode(var) (*var)

/* Access member 'SlottedMode' of type 'c_RPD_Inter_RAT_Quick_Idle_State_complex' as a pointer */
#define PTR_c_RPD_Inter_RAT_Quick_Idle_State_complex_SlottedMode(var) var

/* Access member 'PagingMask' of type 'c_RPD_Inter_RAT_Quick_Idle_State_complex' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Quick_Idle_State_complex_PagingMask(var) (*var)

/* Access member 'PagingMask' of type 'c_RPD_Inter_RAT_Quick_Idle_State_complex' as a pointer */
#define PTR_c_RPD_Inter_RAT_Quick_Idle_State_complex_PagingMask(var) var

/* Access member 'complex' of type 'c_RPD_Inter_RAT_Quick_Idle_State' as a variable reference */
#define VAR_c_RPD_Inter_RAT_Quick_Idle_State_complex(var) var

/* Access member 'complex' of type 'c_RPD_Inter_RAT_Quick_Idle_State' as a pointer */
#define PTR_c_RPD_Inter_RAT_Quick_Idle_State_complex(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Inter_RAT_Quick_Idle_State_complex */
typedef enum {
	U_c_RPD_Inter_RAT_Quick_Idle_State_complex_NONE,
	U_c_RPD_Inter_RAT_Quick_Idle_State_complex_PreferredControlChannelCycle,
	U_c_RPD_Inter_RAT_Quick_Idle_State_complex_SlottedMode,
	U_c_RPD_Inter_RAT_Quick_Idle_State_complex_PagingMask
} TPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_complex;

typedef struct _c_RPD_Inter_RAT_Quick_Idle_State_complex {

	TPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_complex Present;
	union {
		c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle *PreferredControlChannelCycle; /* ODY01 *//*GBD01b*/
	
		c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode *SlottedMode; /* ODY01 *//*GBD01b*/
	
		c_RPD_Inter_RAT_Quick_Idle_State_PagingMask *PagingMask; /* ODY01 *//*GBD01b*/
	
	} u;

} c_RPD_Inter_RAT_Quick_Idle_State_complex;


/*-A----------------------------------*/
typedef struct _c_RPD_Inter_RAT_Quick_Idle_State {

	ED_LONG AttributeId; /* ODY01a *//*GBD01b*/
	ED_LONG NN; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN NN_Present;
	ED_LONG Value; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Value_Present;
	c_RPD_Inter_RAT_Quick_Idle_State_complex complex;/*GBD01b*/

}	c_RPD_Inter_RAT_Quick_Idle_State;
#define INIT_c_RPD_Inter_RAT_Quick_Idle_State(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Inter_RAT_Quick_Idle_State))
/*FRK03a*/
void FREE_c_RPD_Inter_RAT_Quick_Idle_State(c_RPD_Inter_RAT_Quick_Idle_State* sp);
#define SETPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_NN(sp,present) ((sp)->NN_Present = present)
#define GETPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_NN(sp) ((sp)->NN_Present)
#define SETPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_Value(sp,present) ((sp)->Value_Present = present)
#define GETPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_Value(sp) ((sp)->Value_Present)

/* Access member 'AttributeId' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_AttributeId(var) var

/* Access member 'AttributeId' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_AttributeId(var) (&var)

/* Access member 'NN' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_NN(var) var

/* Access member 'NN' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_NN(var) (&var)

/* Access member 'Value' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_Value(var) var

/* Access member 'Value' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_Value(var) (&var)

/* Access member 'SearchParameters' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SearchParameters(var) (*var)

/* Access member 'SearchParameters' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SearchParameters(var) var

/* Access member 'SetManagementParameters' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SetManagementParameters(var) (*var)

/* Access member 'SetManagementParameters' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SetManagementParameters(var) var

/* Access member 'SupportedCDMAChannels' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SupportedCDMAChannels(var) (*var)

/* Access member 'SupportedCDMAChannels' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SupportedCDMAChannels(var) var

/* Access member 'SupportedDRXPatterns' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SupportedDRXPatterns(var) (*var)

/* Access member 'SupportedDRXPatterns' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SupportedDRXPatterns(var) var

/* Access member 'complex' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update' as a variable reference */
#define VAR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex(var) var

/* Access member 'complex' of type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update' as a pointer */
#define PTR_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex */
typedef enum {
	U_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_NONE,
	U_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SearchParameters,
	U_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SetManagementParameters,
	U_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SupportedCDMAChannels,
	U_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SupportedDRXPatterns
} TPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex;

typedef struct _c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex {

	TPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex Present;
	union {
		c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters *SearchParameters; /* ODY01 *//*GBD01b*/
	
		c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters *SetManagementParameters; /* ODY01 *//*GBD01b*/
	
		c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels *SupportedCDMAChannels; /* ODY01 *//*GBD01b*/
	
		c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns *SupportedDRXPatterns; /* ODY01 *//*GBD01b*/
	
	} u;

} c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex;


/*-A----------------------------------*/
typedef struct _c_RPD_Subtype1_based_Inter_RAT_Route_Update {

	ED_LONG AttributeId; /* ODY01a *//*GBD01b*/
	ED_LONG NN; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN NN_Present;
	ED_LONG Value; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Value_Present;
	c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex complex;/*GBD01b*/

}	c_RPD_Subtype1_based_Inter_RAT_Route_Update;
#define INIT_c_RPD_Subtype1_based_Inter_RAT_Route_Update(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Subtype1_based_Inter_RAT_Route_Update))
/*FRK03a*/
void FREE_c_RPD_Subtype1_based_Inter_RAT_Route_Update(c_RPD_Subtype1_based_Inter_RAT_Route_Update* sp);
#define SETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_NN(sp,present) ((sp)->NN_Present = present)
#define GETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_NN(sp) ((sp)->NN_Present)
#define SETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_Value(sp,present) ((sp)->Value_Present = present)
#define GETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_Value(sp) ((sp)->Value_Present)

/* Access member 'TLV_Tag' of type 'c_GenericTLV_cs0087' as a variable reference */
#define VAR_c_GenericTLV_cs0087_TLV_Tag(var) var

/* Access member 'TLV_Tag' of type 'c_GenericTLV_cs0087' as a pointer */
#define PTR_c_GenericTLV_cs0087_TLV_Tag(var) (&var)

/* Access member 'TLV_Data' of type 'c_GenericTLV_cs0087' as a variable reference */
#define VAR_c_GenericTLV_cs0087_TLV_Data(var) var

/* Access member 'TLV_Data' of type 'c_GenericTLV_cs0087' as a pointer */
#define PTR_c_GenericTLV_cs0087_TLV_Data(var) (&var)

/* DEFINITION OF BINARY c_GenericTLV_cs0087_TLV_Data */
typedef struct _c_GenericTLV_cs0087_TLV_Data {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_GenericTLV_cs0087_TLV_Data;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_GenericTLV_cs0087_TLV_Data(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_GenericTLV_cs0087 {

	ED_LONG TLV_Tag; /* ODY01a *//*GBD01b*/
	c_GenericTLV_cs0087_TLV_Data TLV_Data; /* Static, variable size; bits needed 64 *//*GBD01b*/

}	c_GenericTLV_cs0087;
#define INIT_c_GenericTLV_cs0087(sp) ED_RESET_MEM ((sp), sizeof (c_GenericTLV_cs0087))
/*FRK03a*/
void FREE_c_GenericTLV_cs0087(c_GenericTLV_cs0087* sp);

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01'. */
int SETITEMS_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01 (c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATSAP_INCFG_ConfigurationRequest_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01'. */
int SETITEMS_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01 (c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATSAP_INCFG_ConfigurationResponse_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01'. */
int SETITEMS_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01 (c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATINSP_INCFG_ConfigurationRequest_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01'. */
int SETITEMS_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01 (c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATINSP_INCFG_ConfigurationResponse_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01'. */
int SETITEMS_c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01 (c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATISP_INCFG_ConfigurationRequest_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01'. */
int SETITEMS_c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01 (c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATISP_INCFG_ConfigurationResponse_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01'. */
int SETITEMS_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01 (c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATISP_INUSE_ConnectionRequest_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01'. */
int SETITEMS_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01 (c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATISP_INUSE_AttributeUpdateRequest_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01'. */
int SETITEMS_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01 (c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATRUP_INCFG_ConfigurationRequest_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01'. */
int SETITEMS_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01 (c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATRUP_INCFG_ConfigurationResponse_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01'. */
int SETITEMS_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01 (c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

void SETPRESENT_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel (c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data* sp, ED_BOOLEAN present);
#define GETPRESENT_c_RPDCON_IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel(sp) ((sp)->Channel_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01'. */
int SETITEMS_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01 (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02'. */
int SETITEMS_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02 (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data02 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03'. */
int SETITEMS_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03 (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data03 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04'. */
int SETITEMS_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04 (c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATRUP_INUSE_TrafficChannelAssignment_contents_data04 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01'. */
int SETITEMS_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01 (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02'. */
int SETITEMS_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02 (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02 (sequence, (sequence)->items+itemsToBeAdded)

void SETPRESENT_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data_Channel (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data* sp, ED_BOOLEAN present);
#define GETPRESENT_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data02_data_Channel(sp) ((sp)->Channel_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03'. */
int SETITEMS_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03 (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03_data_SearchWindowSize(sp,present) ((sp)->SearchWindowSize_Present = present)
#define GETPRESENT_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data03_data_SearchWindowSize(sp) ((sp)->SearchWindowSize_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04'. */
int SETITEMS_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04 (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04_data_SearchWindowOffset(sp,present) ((sp)->SearchWindowOffset_Present = present)
#define GETPRESENT_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data04_data_SearchWindowOffset(sp) ((sp)->SearchWindowOffset_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05'. */
int SETITEMS_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05 (c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05_data_FPDCHSupported(sp,present) ((sp)->FPDCHSupported_Present = present)
#define GETPRESENT_c_RPDCON_IRATRUP_INUSE_NeighborList_contents_data05_data_FPDCHSupported(sp) ((sp)->FPDCHSupported_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01'. */
int SETITEMS_c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01 (c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATRUP_INUSE_AttributeOverride_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01'. */
int SETITEMS_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01 (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02'. */
int SETITEMS_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02 (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data_SectorSearchWindowSize(sp,present) ((sp)->SectorSearchWindowSize_Present = present)
#define GETPRESENT_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data_SectorSearchWindowSize(sp) ((sp)->SectorSearchWindowSize_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03'. */
int SETITEMS_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03 (c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data_SectorSearchWindowOffset(sp,present) ((sp)->SectorSearchWindowOffset_Present = present)
#define GETPRESENT_c_RPDCON_IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data_SectorSearchWindowOffset(sp) ((sp)->SectorSearchWindowOffset_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01'. */
int SETITEMS_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01 (c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATRUP_INUSE_AttributeUpdateRequest_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01'. */
int SETITEMS_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01 (c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMP_INCFG_ConfigurationRequest_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01'. */
int SETITEMS_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01 (c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMP_INCFG_ConfigurationResponse_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01'. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01 (c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02'. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02 (c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02_data_ForwardTrafficValid127To64(sp,present) ((sp)->ForwardTrafficValid127To64_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data02_data_ForwardTrafficValid127To64(sp) ((sp)->ForwardTrafficValid127To64_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03'. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03 (c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03_data_CompatibleReservedBits(sp,present) ((sp)->CompatibleReservedBits_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_QuickConfig_contents_data03_data_CompatibleReservedBits(sp) ((sp)->CompatibleReservedBits_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01'. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01 (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02'. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02 (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data02 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03'. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03 (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03 (sequence, (sequence)->items+itemsToBeAdded)

void SETPRESENT_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data_NeighborChannel (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data* sp, ED_BOOLEAN present);
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data03_data_NeighborChannel(sp) ((sp)->NeighborChannel_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04'. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04 (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04_data_NeighborSearchWindowSize(sp,present) ((sp)->NeighborSearchWindowSize_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data04_data_NeighborSearchWindowSize(sp) ((sp)->NeighborSearchWindowSize_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05'. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05 (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05_data_NeighborSearchWindowOffset(sp,present) ((sp)->NeighborSearchWindowOffset_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data05_data_NeighborSearchWindowOffset(sp) ((sp)->NeighborSearchWindowOffset_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06'. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06 (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data06 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07'. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07 (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data07 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08'. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08 (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08_data_FPDCHSupported(sp,present) ((sp)->FPDCHSupported_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data08_data_FPDCHSupported(sp) ((sp)->FPDCHSupported_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09'. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09 (c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMP_INUSE_SectorParameters_contents_data09 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01'. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01 (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

void SETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_OtherNeighborRATRecord (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data* sp, ED_BOOLEAN present);
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_OtherNeighborRATRecord(sp) ((sp)->OtherNeighborRATRecord_Present)
void SETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data* sp, ED_BOOLEAN present);
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord(sp) ((sp)->NeighborRATRecord_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_ServingPriority(sp,present) ((sp)->ServingPriority_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_ServingPriority(sp) ((sp)->ServingPriority_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_RxLevMinEUTRACommon(sp,present) ((sp)->RxLevMinEUTRACommon_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_RxLevMinEUTRACommon(sp) ((sp)->RxLevMinEUTRACommon_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_PEMaxCommon(sp,present) ((sp)->PEMaxCommon_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_PEMaxCommon(sp) ((sp)->PEMaxCommon_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_RxLevMinEUTRAOffsetCommonIncl(sp,present) ((sp)->RxLevMinEUTRAOffsetCommonIncl_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_RxLevMinEUTRAOffsetCommonIncl(sp) ((sp)->RxLevMinEUTRAOffsetCommonIncl_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_RxLevMinEUTRAOffsetCommon(sp,present) ((sp)->RxLevMinEUTRAOffsetCommon_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_RxLevMinEUTRAOffsetCommon(sp) ((sp)->RxLevMinEUTRAOffsetCommon_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_MaxReselectionTimer(sp,present) ((sp)->MaxReselectionTimer_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_MaxReselectionTimer(sp) ((sp)->MaxReselectionTimer_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_MinMeasurementBackoff(sp,present) ((sp)->MinMeasurementBackoff_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_MinMeasurementBackoff(sp) ((sp)->MinMeasurementBackoff_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_MaxMeasurementBackoff(sp,present) ((sp)->MaxMeasurementBackoff_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_MaxMeasurementBackoff(sp) ((sp)->MaxMeasurementBackoff_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_ServingNetworkPLMNIncl(sp,present) ((sp)->ServingNetworkPLMNIncl_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_ServingNetworkPLMNIncl(sp) ((sp)->ServingNetworkPLMNIncl_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_NumServingPLMNIDs(sp,present) ((sp)->NumServingPLMNIDs_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_NumServingPLMNIDs(sp) ((sp)->NumServingPLMNIDs_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_RSRQParametersIncluded(sp,present) ((sp)->RSRQParametersIncluded_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_RSRQParametersIncluded(sp) ((sp)->RSRQParametersIncluded_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_QualMinEUTRACommon(sp,present) ((sp)->QualMinEUTRACommon_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_QualMinEUTRACommon(sp) ((sp)->QualMinEUTRACommon_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_QualMinEUTRAOffsetCommonInc(sp,present) ((sp)->QualMinEUTRAOffsetCommonInc_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_QualMinEUTRAOffsetCommonInc(sp) ((sp)->QualMinEUTRAOffsetCommonInc_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_QualMinEUTRAOffsetCommon(sp,present) ((sp)->QualMinEUTRAOffsetCommon_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_QualMinEUTRAOffsetCommon(sp) ((sp)->QualMinEUTRAOffsetCommon_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02'. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02 (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_EARFCNPriority(sp,present) ((sp)->EARFCNPriority_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_EARFCNPriority(sp) ((sp)->EARFCNPriority_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_RxLevMinEUTRA(sp,present) ((sp)->RxLevMinEUTRA_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_RxLevMinEUTRA(sp) ((sp)->RxLevMinEUTRA_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PEMax(sp,present) ((sp)->PEMax_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PEMax(sp) ((sp)->PEMax_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_RxLevMinEUTRAOffsetIncl(sp,present) ((sp)->RxLevMinEUTRAOffsetIncl_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_RxLevMinEUTRAOffsetIncl(sp) ((sp)->RxLevMinEUTRAOffsetIncl_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_RxLevMinEUTRAOffset(sp,present) ((sp)->RxLevMinEUTRAOffset_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_RxLevMinEUTRAOffset(sp) ((sp)->RxLevMinEUTRAOffset_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNSameAsPreviousChannel(sp,present) ((sp)->PLMNSameAsPreviousChannel_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNSameAsPreviousChannel(sp) ((sp)->PLMNSameAsPreviousChannel_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_NumPLMNIDs(sp,present) ((sp)->NumPLMNIDs_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_NumPLMNIDs(sp) ((sp)->NumPLMNIDs_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID'. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID'. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05'. */
int SETITEMS_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05 (c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data_ThreshXQ(sp,present) ((sp)->ThreshXQ_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data_ThreshXQ(sp) ((sp)->ThreshXQ_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data_QualMinEUTRA(sp,present) ((sp)->QualMinEUTRA_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data_QualMinEUTRA(sp) ((sp)->QualMinEUTRA_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data_QualMinEUTRAOffsetIncl(sp,present) ((sp)->QualMinEUTRAOffsetIncl_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data_QualMinEUTRAOffsetIncl(sp) ((sp)->QualMinEUTRAOffsetIncl_Present)
#define SETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data_QualMinEUTRAOffset(sp,present) ((sp)->QualMinEUTRAOffset_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMP_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data_QualMinEUTRAOffset(sp) ((sp)->QualMinEUTRAOffset_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01'. */
int SETITEMS_c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01 (c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_DSAP_INCFG_ConfigurationRequest_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01'. */
int SETITEMS_c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01 (c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_DSAP_INCFG_ConfigurationResponse_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01'. */
int SETITEMS_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01 (c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATQISP_INCFG_ConfigurationRequest_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01'. */
int SETITEMS_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01 (c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATQISP_INCFG_ConfigurationResponse_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01'. */
int SETITEMS_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01 (c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATQISP_INUSE_ConnectionRequest_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01'. */
int SETITEMS_c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01 (c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATQISP_INUSE_QuickPage_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01'. */
int SETITEMS_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01 (c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATQISP_INUSE_AttributeUpdateRequest_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01'. */
int SETITEMS_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01 (c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_S1IRATRUP_INCFG_ConfigurationRequest_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01'. */
int SETITEMS_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01 (c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_S1IRATRUP_INCFG_ConfigurationResponse_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01'. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01 (c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

void SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel (c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data* sp, ED_BOOLEAN present);
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_RouteUpdate_contents_data01_data_Channel(sp) ((sp)->Channel_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01'. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01 (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02'. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02 (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data02 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03'. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03 (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_NumFwdChannelsThisSubActiveSet(sp,present) ((sp)->NumFwdChannelsThisSubActiveSet_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_NumFwdChannelsThisSubActiveSet(sp) ((sp)->NumFwdChannelsThisSubActiveSet_Present)
#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_FeedbackMultiplexingIndex(sp,present) ((sp)->FeedbackMultiplexingIndex_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_FeedbackMultiplexingIndex(sp) ((sp)->FeedbackMultiplexingIndex_Present)
#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_FeedbackReverseChannelIndex(sp,present) ((sp)->FeedbackReverseChannelIndex_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_FeedbackReverseChannelIndex(sp) ((sp)->FeedbackReverseChannelIndex_Present)
#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_DSCForThisSubActiveSetEnabled(sp,present) ((sp)->DSCForThisSubActiveSetEnabled_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_DSCForThisSubActiveSetEnabled(sp) ((sp)->DSCForThisSubActiveSetEnabled_Present)
#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_Next3FieldsSameAsBefore(sp,present) ((sp)->Next3FieldsSameAsBefore_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_Next3FieldsSameAsBefore(sp) ((sp)->Next3FieldsSameAsBefore_Present)
#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_DRCLength(sp,present) ((sp)->DRCLength_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_DRCLength(sp) ((sp)->DRCLength_Present)
#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_DRCChannelGainBase(sp,present) ((sp)->DRCChannelGainBase_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_DRCChannelGainBase(sp) ((sp)->DRCChannelGainBase_Present)
#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_ACKChannelGain(sp,present) ((sp)->ACKChannelGain_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_ACKChannelGain(sp) ((sp)->ACKChannelGain_Present)
#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_NumReverseChannels(sp,present) ((sp)->NumReverseChannels_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_NumReverseChannels(sp) ((sp)->NumReverseChannels_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04'. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04 (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04 (sequence, (sequence)->items+itemsToBeAdded)

void SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data_AssignedChannel (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data* sp, ED_BOOLEAN present);
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data04_data_AssignedChannel(sp) ((sp)->AssignedChannel_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05'. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05 (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data_ReverseBandClass(sp,present) ((sp)->ReverseBandClass_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data_ReverseBandClass(sp) ((sp)->ReverseBandClass_Present)
#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data_ReverseChannelNumber(sp,present) ((sp)->ReverseChannelNumber_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data_ReverseChannelNumber(sp) ((sp)->ReverseChannelNumber_Present)
#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data_ReverseChannelDroppingRank(sp,present) ((sp)->ReverseChannelDroppingRank_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data05_data_ReverseChannelDroppingRank(sp) ((sp)->ReverseChannelDroppingRank_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06'. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06 (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_ForwardChannelIndexThisPilot(sp,present) ((sp)->ForwardChannelIndexThisPilot_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_ForwardChannelIndexThisPilot(sp) ((sp)->ForwardChannelIndexThisPilot_Present)
#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_PilotGroupID(sp,present) ((sp)->PilotGroupID_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_PilotGroupID(sp) ((sp)->PilotGroupID_Present)
#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_NumUniqueForwardTrafficMACIndices(sp,present) ((sp)->NumUniqueForwardTrafficMACIndices_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_NumUniqueForwardTrafficMACIndices(sp) ((sp)->NumUniqueForwardTrafficMACIndices_Present)
#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_SchedulerTag(sp,present) ((sp)->SchedulerTag_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_SchedulerTag(sp) ((sp)->SchedulerTag_Present)
#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_AuxDRCCoverIncluded(sp,present) ((sp)->AuxDRCCoverIncluded_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_AuxDRCCoverIncluded(sp) ((sp)->AuxDRCCoverIncluded_Present)
#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_AuxDRCCover(sp,present) ((sp)->AuxDRCCover_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_AuxDRCCover(sp) ((sp)->AuxDRCCover_Present)
#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_ForwardTrafficMACIndexPerInterlaceEnabled(sp,present) ((sp)->ForwardTrafficMACIndexPerInterlaceEnabled_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_ForwardTrafficMACIndexPerInterlaceEnabled(sp) ((sp)->ForwardTrafficMACIndexPerInterlaceEnabled_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07'. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07 (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07_data_AssignedInterlaces(sp,present) ((sp)->AssignedInterlaces_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data07_data_AssignedInterlaces(sp) ((sp)->AssignedInterlaces_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08'. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08 (c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data_ReverseLinkMACIndex(sp,present) ((sp)->ReverseLinkMACIndex_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data_ReverseLinkMACIndex(sp) ((sp)->ReverseLinkMACIndex_Present)
#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data_RABMACIndex(sp,present) ((sp)->RABMACIndex_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data_RABMACIndex(sp) ((sp)->RABMACIndex_Present)
#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data_DeltaT2P(sp,present) ((sp)->DeltaT2P_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_TrafficChannelAssignment_contents_data03_data_data06_data_data08_data_DeltaT2P(sp) ((sp)->DeltaT2P_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01'. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01 (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02'. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02 (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02 (sequence, (sequence)->items+itemsToBeAdded)

void SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data_Channel (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data* sp, ED_BOOLEAN present);
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data02_data_Channel(sp) ((sp)->Channel_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03'. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03 (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03_data_SearchWindowSize(sp,present) ((sp)->SearchWindowSize_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data03_data_SearchWindowSize(sp) ((sp)->SearchWindowSize_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04'. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04 (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04_data_SearchWindowOffset(sp,present) ((sp)->SearchWindowOffset_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data04_data_SearchWindowOffset(sp) ((sp)->SearchWindowOffset_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05'. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05 (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05_data_FPDCHSupported(sp,present) ((sp)->FPDCHSupported_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data05_data_FPDCHSupported(sp) ((sp)->FPDCHSupported_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06'. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06 (c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06_data_PilotGroupID(sp,present) ((sp)->PilotGroupID_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_NeighborList_contents_data06_data_PilotGroupID(sp) ((sp)->PilotGroupID_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01'. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01 (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02'. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02 (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data_SectorSearchWindowSize(sp,present) ((sp)->SectorSearchWindowSize_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data02_data_SectorSearchWindowSize(sp) ((sp)->SectorSearchWindowSize_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03'. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03 (c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data_SectorSearchWindowOffset(sp,present) ((sp)->SectorSearchWindowOffset_Present = present)
#define GETPRESENT_c_RPDCON_S1IRATRUP_INUSE_RouteUpdateRequest_contents_data03_data_SectorSearchWindowOffset(sp) ((sp)->SectorSearchWindowOffset_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01'. */
int SETITEMS_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01 (c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_S1IRATRUP_INUSE_AttributeUpdateRequest_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01'. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01 (c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationRequest_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01'. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01 (c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMPCS0024B_INCFG_ConfigurationResponse_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01'. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01 (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02'. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02 (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02_data_ForwardTrafficValid127To64(sp,present) ((sp)->ForwardTrafficValid127To64_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data02_data_ForwardTrafficValid127To64(sp) ((sp)->ForwardTrafficValid127To64_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03'. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03 (c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03_data_ForwardTrafficValid130To383(sp,present) ((sp)->ForwardTrafficValid130To383_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_QuickConfig_contents_data03_data_ForwardTrafficValid130To383(sp) ((sp)->ForwardTrafficValid130To383_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01'. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02'. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data02 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03'. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03 (sequence, (sequence)->items+itemsToBeAdded)

void SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data_NeighborChannel (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data* sp, ED_BOOLEAN present);
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data03_data_NeighborChannel(sp) ((sp)->NeighborChannel_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04'. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data04 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05'. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05_data_NeighborSearchWindowOffset(sp,present) ((sp)->NeighborSearchWindowOffset_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data05_data_NeighborSearchWindowOffset(sp) ((sp)->NeighborSearchWindowOffset_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06'. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data06 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07'. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07 (sequence, (sequence)->items+itemsToBeAdded)

void SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data_AccessHashingChannelMask (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data* sp, ED_BOOLEAN present);
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data07_data_AccessHashingChannelMask(sp) ((sp)->AccessHashingChannelMask_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08'. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08_data_FPDCHSupported(sp,present) ((sp)->FPDCHSupported_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data08_data_FPDCHSupported(sp) ((sp)->FPDCHSupported_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09'. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data09 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10'. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10_data_PilotGroupID(sp,present) ((sp)->PilotGroupID_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data10_data_PilotGroupID(sp) ((sp)->PilotGroupID_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11'. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11 (c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_SectorParameters_contents_data11 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01'. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01 (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

void SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_OtherNeighborRATRecord (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data* sp, ED_BOOLEAN present);
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_OtherNeighborRATRecord(sp) ((sp)->OtherNeighborRATRecord_Present)
void SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data* sp, ED_BOOLEAN present);
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord(sp) ((sp)->NeighborRATRecord_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_ServingPriority(sp,present) ((sp)->ServingPriority_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_ServingPriority(sp) ((sp)->ServingPriority_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_RxLevMinEUTRACommon(sp,present) ((sp)->RxLevMinEUTRACommon_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_RxLevMinEUTRACommon(sp) ((sp)->RxLevMinEUTRACommon_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_PEMaxCommon(sp,present) ((sp)->PEMaxCommon_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_PEMaxCommon(sp) ((sp)->PEMaxCommon_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_RxLevMinEUTRAOffsetCommonIncl(sp,present) ((sp)->RxLevMinEUTRAOffsetCommonIncl_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_RxLevMinEUTRAOffsetCommonIncl(sp) ((sp)->RxLevMinEUTRAOffsetCommonIncl_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_RxLevMinEUTRAOffsetCommon(sp,present) ((sp)->RxLevMinEUTRAOffsetCommon_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_RxLevMinEUTRAOffsetCommon(sp) ((sp)->RxLevMinEUTRAOffsetCommon_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_MaxReselectionTimer(sp,present) ((sp)->MaxReselectionTimer_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_MaxReselectionTimer(sp) ((sp)->MaxReselectionTimer_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_MinMeasurementBackoff(sp,present) ((sp)->MinMeasurementBackoff_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_MinMeasurementBackoff(sp) ((sp)->MinMeasurementBackoff_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_MaxMeasurementBackoff(sp,present) ((sp)->MaxMeasurementBackoff_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_MaxMeasurementBackoff(sp) ((sp)->MaxMeasurementBackoff_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_ServingNetworkPLMNIncl(sp,present) ((sp)->ServingNetworkPLMNIncl_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_ServingNetworkPLMNIncl(sp) ((sp)->ServingNetworkPLMNIncl_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_NumServingPLMNIDs(sp,present) ((sp)->NumServingPLMNIDs_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_NumServingPLMNIDs(sp) ((sp)->NumServingPLMNIDs_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_RSRQParametersIncluded(sp,present) ((sp)->RSRQParametersIncluded_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_RSRQParametersIncluded(sp) ((sp)->RSRQParametersIncluded_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_QualMinEUTRACommon(sp,present) ((sp)->QualMinEUTRACommon_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_QualMinEUTRACommon(sp) ((sp)->QualMinEUTRACommon_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_QualMinEUTRAOffsetCommonInc(sp,present) ((sp)->QualMinEUTRAOffsetCommonInc_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_QualMinEUTRAOffsetCommonInc(sp) ((sp)->QualMinEUTRAOffsetCommonInc_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_QualMinEUTRAOffsetCommon(sp,present) ((sp)->QualMinEUTRAOffsetCommon_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_QualMinEUTRAOffsetCommon(sp) ((sp)->QualMinEUTRAOffsetCommon_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02'. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02 (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_EARFCNPriority(sp,present) ((sp)->EARFCNPriority_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_EARFCNPriority(sp) ((sp)->EARFCNPriority_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_RxLevMinEUTRA(sp,present) ((sp)->RxLevMinEUTRA_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_RxLevMinEUTRA(sp) ((sp)->RxLevMinEUTRA_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PEMax(sp,present) ((sp)->PEMax_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PEMax(sp) ((sp)->PEMax_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_RxLevMinEUTRAOffsetIncl(sp,present) ((sp)->RxLevMinEUTRAOffsetIncl_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_RxLevMinEUTRAOffsetIncl(sp) ((sp)->RxLevMinEUTRAOffsetIncl_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_RxLevMinEUTRAOffset(sp,present) ((sp)->RxLevMinEUTRAOffset_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_RxLevMinEUTRAOffset(sp) ((sp)->RxLevMinEUTRAOffset_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNSameAsPreviousChannel(sp,present) ((sp)->PLMNSameAsPreviousChannel_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNSameAsPreviousChannel(sp) ((sp)->PLMNSameAsPreviousChannel_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_NumPLMNIDs(sp,present) ((sp)->NumPLMNIDs_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_NumPLMNIDs(sp) ((sp)->NumPLMNIDs_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID'. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data02_data_PLMNID (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID'. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_S_PLMNID (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05'. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05 (c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data_ThreshXQ(sp,present) ((sp)->ThreshXQ_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data_ThreshXQ(sp) ((sp)->ThreshXQ_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data_QualMinEUTRA(sp,present) ((sp)->QualMinEUTRA_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data_QualMinEUTRA(sp) ((sp)->QualMinEUTRA_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data_QualMinEUTRAOffsetIncl(sp,present) ((sp)->QualMinEUTRAOffsetIncl_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data_QualMinEUTRAOffsetIncl(sp) ((sp)->QualMinEUTRAOffsetIncl_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data_QualMinEUTRAOffset(sp,present) ((sp)->QualMinEUTRAOffset_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_OtherRATNeighborList_contents_data01_data_NeighborRATRecord_data05_data_QualMinEUTRAOffset(sp) ((sp)->QualMinEUTRAOffset_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01'. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01 (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APSubnetLength(sp,present) ((sp)->APSubnetLength_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APSubnetLength(sp) ((sp)->APSubnetLength_Present)
void SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APSubnet (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data* sp, ED_BOOLEAN present);
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APSubnet(sp) ((sp)->APSubnet_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APBand(sp,present) ((sp)->APBand_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APBand(sp) ((sp)->APBand_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APChannel(sp,present) ((sp)->APChannel_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APChannel(sp) ((sp)->APChannel_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APPNRecordType(sp,present) ((sp)->APPNRecordType_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APPNRecordType(sp) ((sp)->APPNRecordType_Present)
#define SETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APPNRecordLength(sp,present) ((sp)->APPNRecordLength_Present = present)
#define GETPRESENT_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointPilotInformation_contents_data01_data_APPNRecordLength(sp) ((sp)->APPNRecordLength_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01'. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01 (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentification_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01'. */
int SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01 (c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDCON_IRATOMPCS0024B_INUSE_AccessPointIdentificationText_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01'. */
int SETITEMS_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01 (c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data_PilotPN(sp,present) ((sp)->PilotPN_Present = present)
#define GETPRESENT_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data_PilotPN(sp) ((sp)->PilotPN_Present)
#define SETPRESENT_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data_PilotStrengthNominal(sp,present) ((sp)->PilotStrengthNominal_Present = present)
#define GETPRESENT_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data_PilotStrengthNominal(sp) ((sp)->PilotStrengthNominal_Present)
#define SETPRESENT_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data_PilotStrengthCorrectionMin(sp,present) ((sp)->PilotStrengthCorrectionMin_Present = present)
#define GETPRESENT_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data_PilotStrengthCorrectionMin(sp) ((sp)->PilotStrengthCorrectionMin_Present)
#define SETPRESENT_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data_PilotStrengthCorrectionMax(sp,present) ((sp)->PilotStrengthCorrectionMax_Present = present)
#define GETPRESENT_c_RPDRAT_ATS3RTCMACPR_HRPDOpenLoopParameters_contents_data01_data_PilotStrengthCorrectionMax(sp) ((sp)->PilotStrengthCorrectionMax_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01'. */
int SETITEMS_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01 (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02'. */
int SETITEMS_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02 (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02* sequence, int desiredItems);
#define ADDITEMS_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02(sequence, itemsToBeAdded) SETITEMS_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02 (sequence, (sequence)->items+itemsToBeAdded)

void SETPRESENT_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_ReverseCDMAChannel (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data* sp, ED_BOOLEAN present);
#define GETPRESENT_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_ReverseCDMAChannel(sp) ((sp)->ReverseCDMAChannel_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03'. */
int SETITEMS_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03 (c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03* sequence, int desiredItems);
#define ADDITEMS_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03(sequence, itemsToBeAdded) SETITEMS_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data_PilotIncluded(sp,present) ((sp)->PilotIncluded_Present = present)
#define GETPRESENT_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data_PilotIncluded(sp) ((sp)->PilotIncluded_Present)
#define SETPRESENT_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data_OpenLoopAdjust(sp,present) ((sp)->OpenLoopAdjust_Present = present)
#define GETPRESENT_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data_OpenLoopAdjust(sp) ((sp)->OpenLoopAdjust_Present)
#define SETPRESENT_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data_InitialAdjust(sp,present) ((sp)->InitialAdjust_Present = present)
#define GETPRESENT_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data_InitialAdjust(sp) ((sp)->InitialAdjust_Present)
#define SETPRESENT_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data_PilotStrengthIncluded(sp,present) ((sp)->PilotStrengthIncluded_Present = present)
#define GETPRESENT_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data_PilotStrengthIncluded(sp) ((sp)->PilotStrengthIncluded_Present)
#define SETPRESENT_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data_PilotStrengthNominal(sp,present) ((sp)->PilotStrengthNominal_Present = present)
#define GETPRESENT_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data_PilotStrengthNominal(sp) ((sp)->PilotStrengthNominal_Present)
#define SETPRESENT_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data_PilotStrengthCorrectionMin(sp,present) ((sp)->PilotStrengthCorrectionMin_Present = present)
#define GETPRESENT_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data_PilotStrengthCorrectionMin(sp) ((sp)->PilotStrengthCorrectionMin_Present)
#define SETPRESENT_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data_PilotStrengthCorrectionMax(sp,present) ((sp)->PilotStrengthCorrectionMax_Present = present)
#define GETPRESENT_c_RPDRAT_ATS4RTCMACPR_HRPDOpenLoopParameters_contents_data02_data_data03_data_PilotStrengthCorrectionMax(sp) ((sp)->PilotStrengthCorrectionMax_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01'. */
int SETITEMS_c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01 (c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01_data_PreferredControlChannelCycle(sp,present) ((sp)->PreferredControlChannelCycle_Present = present)
#define GETPRESENT_c_RPD_Inter_RAT_Idle_State_PreferredControlChannelCycle_data01_data_PreferredControlChannelCycle(sp) ((sp)->PreferredControlChannelCycle_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPD_Inter_RAT_Idle_State_SlottedMode_data01'. */
int SETITEMS_c_RPD_Inter_RAT_Idle_State_SlottedMode_data01 (c_RPD_Inter_RAT_Idle_State_SlottedMode_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Inter_RAT_Idle_State_SlottedMode_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Inter_RAT_Idle_State_SlottedMode_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Inter_RAT_Idle_State_PagingMask_data01'. */
int SETITEMS_c_RPD_Inter_RAT_Idle_State_PagingMask_data01 (c_RPD_Inter_RAT_Idle_State_PagingMask_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Inter_RAT_Idle_State_PagingMask_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Inter_RAT_Idle_State_PagingMask_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02'. */
int SETITEMS_c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02 (c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02(sequence, itemsToBeAdded) SETITEMS_c_RPD_Inter_RAT_Idle_State_PagingMask_data01_data_data02 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Inter_RAT_Route_Update_SearchParameters_data01'. */
int SETITEMS_c_RPD_Inter_RAT_Route_Update_SearchParameters_data01 (c_RPD_Inter_RAT_Route_Update_SearchParameters_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Inter_RAT_Route_Update_SearchParameters_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Inter_RAT_Route_Update_SearchParameters_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01'. */
int SETITEMS_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01 (c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data_SoftSlope(sp,present) ((sp)->SoftSlope_Present = present)
#define GETPRESENT_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data_SoftSlope(sp) ((sp)->SoftSlope_Present)
#define SETPRESENT_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data_AddIntercept(sp,present) ((sp)->AddIntercept_Present = present)
#define GETPRESENT_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data_AddIntercept(sp) ((sp)->AddIntercept_Present)
#define SETPRESENT_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data_DropIntercept(sp,present) ((sp)->DropIntercept_Present = present)
#define GETPRESENT_c_RPD_Inter_RAT_Route_Update_SetManagementSameChannelParameters_data01_data_DropIntercept(sp) ((sp)->DropIntercept_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01'. */
int SETITEMS_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01 (c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data_SoftSlope(sp,present) ((sp)->SoftSlope_Present = present)
#define GETPRESENT_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data_SoftSlope(sp) ((sp)->SoftSlope_Present)
#define SETPRESENT_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data_AddIntercept(sp,present) ((sp)->AddIntercept_Present = present)
#define GETPRESENT_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data_AddIntercept(sp) ((sp)->AddIntercept_Present)
#define SETPRESENT_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data_DropIntercept(sp,present) ((sp)->DropIntercept_Present = present)
#define GETPRESENT_c_RPD_Inter_RAT_Route_Update_SetManagementDifferentChannelParameters_data01_data_DropIntercept(sp) ((sp)->DropIntercept_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01'. */
int SETITEMS_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01 (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02'. */
int SETITEMS_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02 (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02(sequence, itemsToBeAdded) SETITEMS_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03'. */
int SETITEMS_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03 (c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03(sequence, itemsToBeAdded) SETITEMS_c_RPD_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01'. */
int SETITEMS_c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01 (c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01_data_PreferredControlChannelCycle(sp,present) ((sp)->PreferredControlChannelCycle_Present = present)
#define GETPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_PreferredControlChannelCycle_data01_data_PreferredControlChannelCycle(sp) ((sp)->PreferredControlChannelCycle_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01'. */
int SETITEMS_c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01 (c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Inter_RAT_Quick_Idle_State_SlottedMode_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01'. */
int SETITEMS_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01 (c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02'. */
int SETITEMS_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02 (c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02(sequence, itemsToBeAdded) SETITEMS_c_RPD_Inter_RAT_Quick_Idle_State_PagingMask_data01_data_data02 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01'. */
int SETITEMS_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01 (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SearchParameters_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01'. */
int SETITEMS_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01 (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data_SoftSlope(sp,present) ((sp)->SoftSlope_Present = present)
#define GETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data_SoftSlope(sp) ((sp)->SoftSlope_Present)
#define SETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data_AddIntercept(sp,present) ((sp)->AddIntercept_Present = present)
#define GETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data_AddIntercept(sp) ((sp)->AddIntercept_Present)
#define SETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data_DropIntercept(sp,present) ((sp)->DropIntercept_Present = present)
#define GETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SetManagementParameters_data01_data_DropIntercept(sp) ((sp)->DropIntercept_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01'. */
int SETITEMS_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01 (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_MultiBandCount(sp,present) ((sp)->MultiBandCount_Present = present)
#define GETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_MultiBandCount(sp) ((sp)->MultiBandCount_Present)
#define SETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_MultiBandBitMapCount(sp,present) ((sp)->MultiBandBitMapCount_Present = present)
#define GETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_MultiBandBitMapCount(sp) ((sp)->MultiBandBitMapCount_Present)
/* SETITEMS/ADDITEMS commands for type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02'. */
int SETITEMS_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02 (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02(sequence, itemsToBeAdded) SETITEMS_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03'. */
int SETITEMS_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03 (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03(sequence, itemsToBeAdded) SETITEMS_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data02_data_data03 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04'. */
int SETITEMS_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04 (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04(sequence, itemsToBeAdded) SETITEMS_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedCDMAChannels_data01_data_data04 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01'. */
int SETITEMS_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01 (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02'. */
int SETITEMS_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02 (c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02(sequence, itemsToBeAdded) SETITEMS_c_RPD_Subtype1_based_Inter_RAT_Route_Update_SupportedDRXPatterns_data01_data_data02 (sequence, (sequence)->items+itemsToBeAdded)

/* SETPRESENT commands for type 'c_RPD_Inter_RAT_Idle_State_complex' */
void GLOB_SETPRESENT_c_RPD_Inter_RAT_Idle_State_complex (c_RPD_Inter_RAT_Idle_State_complex* sp, TPRESENT_c_RPD_Inter_RAT_Idle_State_complex toBeSetPresent);
#define SETPRESENT_c_RPD_Inter_RAT_Idle_State_complex_NONE(sp) GLOB_SETPRESENT_c_RPD_Inter_RAT_Idle_State_complex(sp, U_c_RPD_Inter_RAT_Idle_State_complex_NONE)
#define GETPRESENT_c_RPD_Inter_RAT_Idle_State_complex_NONE(sp) ((sp)->Present == U_c_RPD_Inter_RAT_Idle_State_complex_NONE)
#define SETPRESENT_c_RPD_Inter_RAT_Idle_State_complex_PreferredControlChannelCycle(sp) GLOB_SETPRESENT_c_RPD_Inter_RAT_Idle_State_complex(sp, U_c_RPD_Inter_RAT_Idle_State_complex_PreferredControlChannelCycle)
#define GETPRESENT_c_RPD_Inter_RAT_Idle_State_complex_PreferredControlChannelCycle(sp) ((sp)->Present == U_c_RPD_Inter_RAT_Idle_State_complex_PreferredControlChannelCycle)
#define SETPRESENT_c_RPD_Inter_RAT_Idle_State_complex_SlottedMode(sp) GLOB_SETPRESENT_c_RPD_Inter_RAT_Idle_State_complex(sp, U_c_RPD_Inter_RAT_Idle_State_complex_SlottedMode)
#define GETPRESENT_c_RPD_Inter_RAT_Idle_State_complex_SlottedMode(sp) ((sp)->Present == U_c_RPD_Inter_RAT_Idle_State_complex_SlottedMode)
#define SETPRESENT_c_RPD_Inter_RAT_Idle_State_complex_PagingMask(sp) GLOB_SETPRESENT_c_RPD_Inter_RAT_Idle_State_complex(sp, U_c_RPD_Inter_RAT_Idle_State_complex_PagingMask)
#define GETPRESENT_c_RPD_Inter_RAT_Idle_State_complex_PagingMask(sp) ((sp)->Present == U_c_RPD_Inter_RAT_Idle_State_complex_PagingMask)
#define GETPRESENT_c_RPD_Inter_RAT_Idle_State_complex(sp) ((sp)->Present)

/* SETPRESENT commands for type 'c_RPD_Inter_RAT_Route_Update_complex' */
void GLOB_SETPRESENT_c_RPD_Inter_RAT_Route_Update_complex (c_RPD_Inter_RAT_Route_Update_complex* sp, TPRESENT_c_RPD_Inter_RAT_Route_Update_complex toBeSetPresent);
#define SETPRESENT_c_RPD_Inter_RAT_Route_Update_complex_NONE(sp) GLOB_SETPRESENT_c_RPD_Inter_RAT_Route_Update_complex(sp, U_c_RPD_Inter_RAT_Route_Update_complex_NONE)
#define GETPRESENT_c_RPD_Inter_RAT_Route_Update_complex_NONE(sp) ((sp)->Present == U_c_RPD_Inter_RAT_Route_Update_complex_NONE)
#define SETPRESENT_c_RPD_Inter_RAT_Route_Update_complex_SearchParameters(sp) GLOB_SETPRESENT_c_RPD_Inter_RAT_Route_Update_complex(sp, U_c_RPD_Inter_RAT_Route_Update_complex_SearchParameters)
#define GETPRESENT_c_RPD_Inter_RAT_Route_Update_complex_SearchParameters(sp) ((sp)->Present == U_c_RPD_Inter_RAT_Route_Update_complex_SearchParameters)
#define SETPRESENT_c_RPD_Inter_RAT_Route_Update_complex_SetManagementSameChannelParameters(sp) GLOB_SETPRESENT_c_RPD_Inter_RAT_Route_Update_complex(sp, U_c_RPD_Inter_RAT_Route_Update_complex_SetManagementSameChannelParameters)
#define GETPRESENT_c_RPD_Inter_RAT_Route_Update_complex_SetManagementSameChannelParameters(sp) ((sp)->Present == U_c_RPD_Inter_RAT_Route_Update_complex_SetManagementSameChannelParameters)
#define SETPRESENT_c_RPD_Inter_RAT_Route_Update_complex_SetManagementDifferentChannelParameters(sp) GLOB_SETPRESENT_c_RPD_Inter_RAT_Route_Update_complex(sp, U_c_RPD_Inter_RAT_Route_Update_complex_SetManagementDifferentChannelParameters)
#define GETPRESENT_c_RPD_Inter_RAT_Route_Update_complex_SetManagementDifferentChannelParameters(sp) ((sp)->Present == U_c_RPD_Inter_RAT_Route_Update_complex_SetManagementDifferentChannelParameters)
#define SETPRESENT_c_RPD_Inter_RAT_Route_Update_complex_SupportedCDMAChannels(sp) GLOB_SETPRESENT_c_RPD_Inter_RAT_Route_Update_complex(sp, U_c_RPD_Inter_RAT_Route_Update_complex_SupportedCDMAChannels)
#define GETPRESENT_c_RPD_Inter_RAT_Route_Update_complex_SupportedCDMAChannels(sp) ((sp)->Present == U_c_RPD_Inter_RAT_Route_Update_complex_SupportedCDMAChannels)
#define GETPRESENT_c_RPD_Inter_RAT_Route_Update_complex(sp) ((sp)->Present)

/* SETPRESENT commands for type 'c_RPD_Inter_RAT_Quick_Idle_State_complex' */
void GLOB_SETPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_complex (c_RPD_Inter_RAT_Quick_Idle_State_complex* sp, TPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_complex toBeSetPresent);
#define SETPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_complex_NONE(sp) GLOB_SETPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_complex(sp, U_c_RPD_Inter_RAT_Quick_Idle_State_complex_NONE)
#define GETPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_complex_NONE(sp) ((sp)->Present == U_c_RPD_Inter_RAT_Quick_Idle_State_complex_NONE)
#define SETPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_complex_PreferredControlChannelCycle(sp) GLOB_SETPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_complex(sp, U_c_RPD_Inter_RAT_Quick_Idle_State_complex_PreferredControlChannelCycle)
#define GETPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_complex_PreferredControlChannelCycle(sp) ((sp)->Present == U_c_RPD_Inter_RAT_Quick_Idle_State_complex_PreferredControlChannelCycle)
#define SETPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_complex_SlottedMode(sp) GLOB_SETPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_complex(sp, U_c_RPD_Inter_RAT_Quick_Idle_State_complex_SlottedMode)
#define GETPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_complex_SlottedMode(sp) ((sp)->Present == U_c_RPD_Inter_RAT_Quick_Idle_State_complex_SlottedMode)
#define SETPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_complex_PagingMask(sp) GLOB_SETPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_complex(sp, U_c_RPD_Inter_RAT_Quick_Idle_State_complex_PagingMask)
#define GETPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_complex_PagingMask(sp) ((sp)->Present == U_c_RPD_Inter_RAT_Quick_Idle_State_complex_PagingMask)
#define GETPRESENT_c_RPD_Inter_RAT_Quick_Idle_State_complex(sp) ((sp)->Present)

/* SETPRESENT commands for type 'c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex' */
void GLOB_SETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex (c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex* sp, TPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex toBeSetPresent);
#define SETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_NONE(sp) GLOB_SETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex(sp, U_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_NONE)
#define GETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_NONE(sp) ((sp)->Present == U_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_NONE)
#define SETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SearchParameters(sp) GLOB_SETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex(sp, U_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SearchParameters)
#define GETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SearchParameters(sp) ((sp)->Present == U_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SearchParameters)
#define SETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SetManagementParameters(sp) GLOB_SETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex(sp, U_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SetManagementParameters)
#define GETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SetManagementParameters(sp) ((sp)->Present == U_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SetManagementParameters)
#define SETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SupportedCDMAChannels(sp) GLOB_SETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex(sp, U_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SupportedCDMAChannels)
#define GETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SupportedCDMAChannels(sp) ((sp)->Present == U_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SupportedCDMAChannels)
#define SETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SupportedDRXPatterns(sp) GLOB_SETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex(sp, U_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SupportedDRXPatterns)
#define GETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SupportedDRXPatterns(sp) ((sp)->Present == U_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex_SupportedDRXPatterns)
#define GETPRESENT_c_RPD_Subtype1_based_Inter_RAT_Route_Update_complex(sp) ((sp)->Present)

#ifdef __cplusplus
}
#endif

#endif

