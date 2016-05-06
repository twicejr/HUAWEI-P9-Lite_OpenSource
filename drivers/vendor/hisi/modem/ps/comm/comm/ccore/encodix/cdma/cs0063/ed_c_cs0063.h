/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.154
	GENERATOR: ed-c
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __ed_c_cs0063_h_H
#define __ed_c_cs0063_h_H
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


/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_ValueID(var) (&var)

/* Access member 'QoSProfileCount' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_QoSProfileCount(var) var

/* Access member 'QoSProfileCount' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_QoSProfileCount(var) (&var)

/* Access member 'ProfileType' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data_ProfileType(var) var

/* Access member 'ProfileType' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data_ProfileType(var) (&var)

/* Access member 'ProfileLength' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data_ProfileLength(var) var

/* Access member 'ProfileLength' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data_ProfileLength(var) (&var)

/* Access member 'ProfileValue' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data_ProfileValue(var) var

/* Access member 'ProfileValue' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data_ProfileValue(var) (&var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01(var) (&var)

/* DEFINITION OF BINARY c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data_ProfileValue */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data_ProfileValue {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data_ProfileValue;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data_ProfileValue(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data {

	ED_OCTET ProfileType; /* ODY01a *//*GBD01b*/
	ED_OCTET ProfileLength; /* ODY01a *//*GBD01b*/
	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data_ProfileValue ProfileValue; /* Static, variable size; bits needed 64 *//*GBD01b*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01 */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01 {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET QoSProfileCount; /* ODY01a *//*GBD01b*/
	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles;
#define INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles))
/*FRK03a*/
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles(c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles* sp);

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_ValueID(var) (&var)

/* Access member 'QoSProfileCount' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_QoSProfileCount(var) var

/* Access member 'QoSProfileCount' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_QoSProfileCount(var) (&var)

/* Access member 'ProfileType' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data_ProfileType(var) var

/* Access member 'ProfileType' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data_ProfileType(var) (&var)

/* Access member 'ProfileLength' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data_ProfileLength(var) var

/* Access member 'ProfileLength' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data_ProfileLength(var) (&var)

/* Access member 'ProfileValue' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data_ProfileValue(var) var

/* Access member 'ProfileValue' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data_ProfileValue(var) (&var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01(var) (&var)

/* DEFINITION OF BINARY c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data_ProfileValue */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data_ProfileValue {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data_ProfileValue;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data_ProfileValue(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data {

	ED_OCTET ProfileType; /* ODY01a *//*GBD01b*/
	ED_OCTET ProfileLength; /* ODY01a *//*GBD01b*/
	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data_ProfileValue ProfileValue; /* Static, variable size; bits needed 64 *//*GBD01b*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01 */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01 {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET QoSProfileCount; /* ODY01a *//*GBD01b*/
	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles;
#define INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles))
/*FRK03a*/
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles(c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles* sp);

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data_ValueID(var) (&var)

/* Access member 'MaxNumLinkFlowsFwd' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data_MaxNumLinkFlowsFwd(var) var

/* Access member 'MaxNumLinkFlowsFwd' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data_MaxNumLinkFlowsFwd(var) (&var)

/* Access member 'MaxNumLinkFlowsRev' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data_MaxNumLinkFlowsRev(var) var

/* Access member 'MaxNumLinkFlowsRev' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data_MaxNumLinkFlowsRev(var) (&var)

/* Access member 'MaxActivatedLinkFlowsFwd' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data_MaxActivatedLinkFlowsFwd(var) var

/* Access member 'MaxActivatedLinkFlowsFwd' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data_MaxActivatedLinkFlowsFwd(var) (&var)

/* Access member 'MaxActivatedLinkFlowsRev' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data_MaxActivatedLinkFlowsRev(var) var

/* Access member 'MaxActivatedLinkFlowsRev' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data_MaxActivatedLinkFlowsRev(var) (&var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET MaxNumLinkFlowsFwd; /* ODY01a *//*GBD01b*/
	ED_OCTET MaxNumLinkFlowsRev; /* ODY01a *//*GBD01b*/
	ED_OCTET MaxActivatedLinkFlowsFwd; /* ODY01a *//*GBD01b*/
	ED_OCTET MaxActivatedLinkFlowsRev; /* ODY01a *//*GBD01b*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01 */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01 {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows;
#define INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows))
/*FRK03a*/
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows(c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows* sp);

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data_ValueID(var) (&var)

/* Access member 'MaxNumReservationsFwd' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data_MaxNumReservationsFwd(var) var

/* Access member 'MaxNumReservationsFwd' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data_MaxNumReservationsFwd(var) (&var)

/* Access member 'MaxNumReservationsRev' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data_MaxNumReservationsRev(var) var

/* Access member 'MaxNumReservationsRev' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data_MaxNumReservationsRev(var) (&var)

/* Access member 'MaxNumOpenReservationsFwd' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data_MaxNumOpenReservationsFwd(var) var

/* Access member 'MaxNumOpenReservationsFwd' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data_MaxNumOpenReservationsFwd(var) (&var)

/* Access member 'MaxNumOpenReservationsRev' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data_MaxNumOpenReservationsRev(var) var

/* Access member 'MaxNumOpenReservationsRev' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data_MaxNumOpenReservationsRev(var) (&var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET MaxNumReservationsFwd; /* ODY01a *//*GBD01b*/
	ED_OCTET MaxNumReservationsRev; /* ODY01a *//*GBD01b*/
	ED_OCTET MaxNumOpenReservationsFwd; /* ODY01a *//*GBD01b*/
	ED_OCTET MaxNumOpenReservationsRev; /* ODY01a *//*GBD01b*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01 */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01 {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations;
#define INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations))
/*FRK03a*/
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations(c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations* sp);

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data_ValueID(var) (&var)

/* Access member 'AbortTimer' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data_AbortTimer(var) var

/* Access member 'AbortTimer' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data_AbortTimer(var) (&var)

/* Access member 'FlushTimer' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data_FlushTimer(var) var

/* Access member 'FlushTimer' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data_FlushTimer(var) (&var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_SHORT AbortTimer; /* ODY01a *//*GBD01b*/
	ED_SHORT FlushTimer; /* ODY01a *//*GBD01b*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01 */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01 {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd;
#define INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd))
/*FRK03a*/
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd(c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd* sp);

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data_ValueID(var) (&var)

/* Access member 'AbortTimer' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data_AbortTimer(var) var

/* Access member 'AbortTimer' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data_AbortTimer(var) (&var)

/* Access member 'FlushTimer' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data_FlushTimer(var) var

/* Access member 'FlushTimer' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data_FlushTimer(var) (&var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_SHORT AbortTimer; /* ODY01a *//*GBD01b*/
	ED_SHORT FlushTimer; /* ODY01a *//*GBD01b*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01 */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01 {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev;
#define INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev))
/*FRK03a*/
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev(c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev* sp);

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_ValueID(var) (&var)

/* Access member 'ReservationCount' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_ReservationCount(var) var

/* Access member 'ReservationCount' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_ReservationCount(var) (&var)

/* Access member 'ReservationLabel' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data_ReservationLabel(var) var

/* Access member 'ReservationLabel' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data_ReservationLabel(var) (&var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data(var) var

/* Access member 'data02' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02(var) var

/* Access member 'data02' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02(var) (&var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data {

	ED_OCTET ReservationLabel; /* ODY01a *//*GBD01b*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02 */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02 {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET ReservationCount; /* ODY01a *//*GBD01b*/
	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02 data02;/*GFB09*//*GBD01b*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01 */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01 {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd;
#define INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd))
/*FRK03a*/
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd(c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd* sp);

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_ValueID(var) (&var)

/* Access member 'ReservationCount' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_ReservationCount(var) var

/* Access member 'ReservationCount' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_ReservationCount(var) (&var)

/* Access member 'ReservationLabel' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data_ReservationLabel(var) var

/* Access member 'ReservationLabel' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data_ReservationLabel(var) (&var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data(var) var

/* Access member 'data02' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02(var) var

/* Access member 'data02' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02(var) (&var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data {

	ED_OCTET ReservationLabel; /* ODY01a *//*GBD01b*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02 */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02 {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET ReservationCount; /* ODY01a *//*GBD01b*/
	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02 data02;/*GFB09*//*GBD01b*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01 */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01 {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev;
#define INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev))
/*FRK03a*/
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev(c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev* sp);

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data_ValueID(var) (&var)

/* Access member 'ProfileType' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data_ProfileType(var) var

/* Access member 'ProfileType' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data_ProfileType(var) (&var)

/* Access member 'ProfileLength' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data_ProfileLength(var) var

/* Access member 'ProfileLength' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data_ProfileLength(var) (&var)

/* Access member 'ProfileValue' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data_ProfileValue(var) var

/* Access member 'ProfileValue' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data_ProfileValue(var) (&var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01(var) (&var)

/* DEFINITION OF BINARY c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data_ProfileValue */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data_ProfileValue {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data_ProfileValue;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data_ProfileValue(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET ProfileType; /* ODY01a *//*GBD01b*/
	ED_SHORT ProfileLength; /* ODY01a *//*GBD01b*/
	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data_ProfileValue ProfileValue; /* Static, variable size; bits needed 64 *//*GBD01b*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01 */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01 {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd;
#define INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd))
/*FRK03a*/
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd(c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd* sp);

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data_ValueID(var) (&var)

/* Access member 'ProfileType' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data_ProfileType(var) var

/* Access member 'ProfileType' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data_ProfileType(var) (&var)

/* Access member 'ProfileLength' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data_ProfileLength(var) var

/* Access member 'ProfileLength' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data_ProfileLength(var) (&var)

/* Access member 'ProfileValue' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data_ProfileValue(var) var

/* Access member 'ProfileValue' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data_ProfileValue(var) (&var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01(var) (&var)

/* DEFINITION OF BINARY c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data_ProfileValue */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data_ProfileValue {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data_ProfileValue;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data_ProfileValue(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET ProfileType; /* ODY01a *//*GBD01b*/
	ED_SHORT ProfileLength; /* ODY01a *//*GBD01b*/
	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data_ProfileValue ProfileValue; /* Static, variable size; bits needed 64 *//*GBD01b*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01 */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01 {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev;
#define INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev))
/*FRK03a*/
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev(c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev* sp);

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data_ValueID(var) (&var)

/* Access member 'ProfileType' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data_ProfileType(var) var

/* Access member 'ProfileType' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data_ProfileType(var) (&var)

/* Access member 'ProfileLength' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data_ProfileLength(var) var

/* Access member 'ProfileLength' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data_ProfileLength(var) (&var)

/* Access member 'ProfileValue' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data_ProfileValue(var) var

/* Access member 'ProfileValue' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data_ProfileValue(var) (&var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01(var) (&var)

/* DEFINITION OF BINARY c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data_ProfileValue */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data_ProfileValue {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data_ProfileValue;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data_ProfileValue(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET ProfileType; /* ODY01a *//*GBD01b*/
	ED_SHORT ProfileLength; /* ODY01a *//*GBD01b*/
	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data_ProfileValue ProfileValue; /* Static, variable size; bits needed 64 *//*GBD01b*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01 */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01 {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd;
#define INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd))
/*FRK03a*/
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd(c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd* sp);

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data_ValueID(var) (&var)

/* Access member 'ProfileType' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data_ProfileType(var) var

/* Access member 'ProfileType' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data_ProfileType(var) (&var)

/* Access member 'ProfileLength' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data_ProfileLength(var) var

/* Access member 'ProfileLength' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data_ProfileLength(var) (&var)

/* Access member 'ProfileValue' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data_ProfileValue(var) var

/* Access member 'ProfileValue' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data_ProfileValue(var) (&var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01(var) (&var)

/* DEFINITION OF BINARY c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data_ProfileValue */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data_ProfileValue {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data_ProfileValue;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data_ProfileValue(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET ProfileType; /* ODY01a *//*GBD01b*/
	ED_SHORT ProfileLength; /* ODY01a *//*GBD01b*/
	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data_ProfileValue ProfileValue; /* Static, variable size; bits needed 64 *//*GBD01b*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01 */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01 {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev;
#define INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev))
/*FRK03a*/
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev(c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev* sp);

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data_ValueID(var) (&var)

/* Access member 'ProtocolID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data_ProtocolID(var) var

/* Access member 'ProtocolID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data_ProtocolID(var) (&var)

/* Access member 'ProtocolParametersLength' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data_ProtocolParametersLength(var) var

/* Access member 'ProtocolParametersLength' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data_ProtocolParametersLength(var) (&var)

/* Access member 'ProtocolParameters' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data_ProtocolParameters(var) var

/* Access member 'ProtocolParameters' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data_ProtocolParameters(var) (&var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01(var) (&var)

/* DEFINITION OF BINARY c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data_ProtocolParameters */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data_ProtocolParameters {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data_ProtocolParameters;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data_ProtocolParameters(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET ProtocolID; /* ODY01a *//*GBD01b*/
	ED_OCTET ProtocolParametersLength; /* ODY01a *//*GBD01b*/
	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data_ProtocolParameters ProtocolParameters; /* Static, variable size; bits needed 64 *//*GBD01b*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01 */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01 {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd;
#define INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd))
/*FRK03a*/
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd(c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd* sp);

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data_ValueID(var) (&var)

/* Access member 'ProtocolID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data_ProtocolID(var) var

/* Access member 'ProtocolID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data_ProtocolID(var) (&var)

/* Access member 'ProtocolParametersLength' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data_ProtocolParametersLength(var) var

/* Access member 'ProtocolParametersLength' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data_ProtocolParametersLength(var) (&var)

/* Access member 'ProtocolParameters' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data_ProtocolParameters(var) var

/* Access member 'ProtocolParameters' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data_ProtocolParameters(var) (&var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01(var) (&var)

/* DEFINITION OF BINARY c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data_ProtocolParameters */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data_ProtocolParameters {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data_ProtocolParameters;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data_ProtocolParameters(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET ProtocolID; /* ODY01a *//*GBD01b*/
	ED_OCTET ProtocolParametersLength; /* ODY01a *//*GBD01b*/
	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data_ProtocolParameters ProtocolParameters; /* Static, variable size; bits needed 64 *//*GBD01b*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01 */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01 {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev;
#define INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev))
/*FRK03a*/
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev(c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev* sp);

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data_ValueID(var) (&var)

/* Access member 'ProtocolID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data_ProtocolID(var) var

/* Access member 'ProtocolID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data_ProtocolID(var) (&var)

/* Access member 'ProtocolParametersLength' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data_ProtocolParametersLength(var) var

/* Access member 'ProtocolParametersLength' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data_ProtocolParametersLength(var) (&var)

/* Access member 'ProtocolParameters' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data_ProtocolParameters(var) var

/* Access member 'ProtocolParameters' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data_ProtocolParameters(var) (&var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01(var) (&var)

/* DEFINITION OF BINARY c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data_ProtocolParameters */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data_ProtocolParameters {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data_ProtocolParameters;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data_ProtocolParameters(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET ProtocolID; /* ODY01a *//*GBD01b*/
	ED_OCTET ProtocolParametersLength; /* ODY01a *//*GBD01b*/
	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data_ProtocolParameters ProtocolParameters; /* Static, variable size; bits needed 64 *//*GBD01b*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01 */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01 {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd;
#define INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd))
/*FRK03a*/
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd(c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd* sp);

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data_ValueID(var) (&var)

/* Access member 'ProtocolID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data_ProtocolID(var) var

/* Access member 'ProtocolID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data_ProtocolID(var) (&var)

/* Access member 'ProtocolParametersLength' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data_ProtocolParametersLength(var) var

/* Access member 'ProtocolParametersLength' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data_ProtocolParametersLength(var) (&var)

/* Access member 'ProtocolParameters' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data_ProtocolParameters(var) var

/* Access member 'ProtocolParameters' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data_ProtocolParameters(var) (&var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01(var) (&var)

/* DEFINITION OF BINARY c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data_ProtocolParameters */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data_ProtocolParameters {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data_ProtocolParameters;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data_ProtocolParameters(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET ProtocolID; /* ODY01a *//*GBD01b*/
	ED_OCTET ProtocolParametersLength; /* ODY01a *//*GBD01b*/
	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data_ProtocolParameters ProtocolParameters; /* Static, variable size; bits needed 64 *//*GBD01b*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01 */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01 {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev;
#define INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev))
/*FRK03a*/
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev(c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev* sp);

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_ValueID(var) (&var)

/* Access member 'ProtocolSupported' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_ProtocolSupported(var) var

/* Access member 'ProtocolSupported' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_ProtocolSupported(var) (&var)

/* Access member 'SupportedProtocolParametersValuesLength' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_SupportedProtocolParametersValuesLength(var) var

/* Access member 'SupportedProtocolParametersValuesLength' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_SupportedProtocolParametersValuesLength(var) (&var)

/* Access member 'SupportedProtocolParametersValues' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_SupportedProtocolParametersValues(var) var

/* Access member 'SupportedProtocolParametersValues' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_SupportedProtocolParametersValues(var) (&var)

/* DEFINITION OF BINARY c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_SupportedProtocolParametersValues */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_SupportedProtocolParametersValues {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_SupportedProtocolParametersValues;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_SupportedProtocolParametersValues(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET ProtocolSupported; /* ODY01a *//*GBD01b*/
	ED_OCTET SupportedProtocolParametersValuesLength; /* ODY01a *//*GBD01b*/
	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_SupportedProtocolParametersValues SupportedProtocolParametersValues; /* Static, variable size; bits needed 64 *//*GBD01b*/

}	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP;
#define INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP))
/*FRK03a*/
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP(c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP* sp);

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_ValueID(var) (&var)

/* Access member 'ProtocolSupported' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_ProtocolSupported(var) var

/* Access member 'ProtocolSupported' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_ProtocolSupported(var) (&var)

/* Access member 'SupportedProtocolParametersValuesLength' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_SupportedProtocolParametersValuesLength(var) var

/* Access member 'SupportedProtocolParametersValuesLength' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_SupportedProtocolParametersValuesLength(var) (&var)

/* Access member 'SupportedProtocolParametersValues' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_SupportedProtocolParametersValues(var) var

/* Access member 'SupportedProtocolParametersValues' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_SupportedProtocolParametersValues(var) (&var)

/* DEFINITION OF BINARY c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_SupportedProtocolParametersValues */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_SupportedProtocolParametersValues {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_SupportedProtocolParametersValues;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_SupportedProtocolParametersValues(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET ProtocolSupported; /* ODY01a *//*GBD01b*/
	ED_OCTET SupportedProtocolParametersValuesLength; /* ODY01a *//*GBD01b*/
	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_SupportedProtocolParametersValues SupportedProtocolParametersValues; /* Static, variable size; bits needed 64 *//*GBD01b*/

}	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP;
#define INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP))
/*FRK03a*/
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP(c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP* sp);

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_ValueID(var) (&var)

/* Access member 'BCMCSFlowCount' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_BCMCSFlowCount(var) var

/* Access member 'BCMCSFlowCount' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_BCMCSFlowCount(var) (&var)

/* Access member 'BCMCSFlowID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data_BCMCSFlowID(var) var

/* Access member 'BCMCSFlowID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data_BCMCSFlowID(var) (&var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data(var) var

/* Access member 'data02' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02(var) var

/* Access member 'data02' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02(var) (&var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data {

	ED_LONG BCMCSFlowID; /* ODY01a *//*GBD01b*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02 */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02 {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET BCMCSFlowCount; /* ODY01a *//*GBD01b*/
	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02 data02;/*GFB09*//*GBD01b*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01 */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01 {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation;
#define INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation))
/*FRK03a*/
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation(c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation* sp);

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_ValueID(var) (&var)

/* Access member 'ProgramCount' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_ProgramCount(var) var

/* Access member 'ProgramCount' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_ProgramCount(var) (&var)

/* Access member 'ProgramIDLSBLength' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_ProgramIDLSBLength(var) var

/* Access member 'ProgramIDLSBLength' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_ProgramIDLSBLength(var) (&var)

/* Access member 'ProgramIDLSBs' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_ProgramIDLSBs(var) var

/* Access member 'ProgramIDLSBs' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_ProgramIDLSBs(var) (&var)

/* Access member 'FlowDiscriminatorCount' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_FlowDiscriminatorCount(var) var

/* Access member 'FlowDiscriminatorCount' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_FlowDiscriminatorCount(var) (&var)

/* Access member 'FlowDiscriminator' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data_FlowDiscriminator(var) var

/* Access member 'FlowDiscriminator' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data_FlowDiscriminator(var) (&var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data(var) var

/* Access member 'data03' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03(var) var

/* Access member 'data03' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03(var) (&var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data(var) var

/* Access member 'data02' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02(var) var

/* Access member 'data02' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02(var) (&var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01(var) var

/* Access member 'data01' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data {

	ED_OCTET FlowDiscriminator; /* ODY01a *//*GBD01b*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03 */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03 {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data {

	ED_OCTET ProgramIDLSBLength; /* ODY01a *//*GBD01b*/
	ED_LONG ProgramIDLSBs; /* ODY01a *//*GBD01b*/
	ED_OCTET FlowDiscriminatorCount; /* ODY01a *//*GBD01b*/
	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03 data03;/*GFB09*//*GBD01b*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02 */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02 {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET ProgramCount; /* ODY01a *//*GBD01b*/
	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02 data02;/*GFB09*//*GBD01b*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01 */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01 {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation {

	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation;
#define INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation))
/*FRK03a*/
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation(c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation* sp);

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_ValueID(var) (&var)

/* Access member 'QoSProfileCount' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_QoSProfileCount(var) var

/* Access member 'QoSProfileCount' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_QoSProfileCount(var) (&var)

/* Access member 'ProfileType' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data_ProfileType(var) var

/* Access member 'ProfileType' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data_ProfileType(var) (&var)

/* Access member 'ProfileLength' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data_ProfileLength(var) var

/* Access member 'ProfileLength' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data_ProfileLength(var) (&var)

/* Access member 'ProfileValue' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data_ProfileValue(var) var

/* Access member 'ProfileValue' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data_ProfileValue(var) (&var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01(var) (&var)

/* DEFINITION OF BINARY c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data_ProfileValue */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data_ProfileValue {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data_ProfileValue;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data_ProfileValue(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data {

	ED_OCTET ProfileType; /* ODY01a *//*GBD01b*/
	ED_OCTET ProfileLength; /* ODY01a *//*GBD01b*/
	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data_ProfileValue ProfileValue; /* Static, variable size; bits needed 64 *//*GBD01b*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01 */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01 {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET QoSProfileCount; /* ODY01a *//*GBD01b*/
	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles;
#define INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles))
/*FRK03a*/
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles(c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles* sp);

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_ValueID(var) (&var)

/* Access member 'QoSProfileCount' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_QoSProfileCount(var) var

/* Access member 'QoSProfileCount' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_QoSProfileCount(var) (&var)

/* Access member 'ProfileType' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data_ProfileType(var) var

/* Access member 'ProfileType' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data_ProfileType(var) (&var)

/* Access member 'ProfileLength' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data_ProfileLength(var) var

/* Access member 'ProfileLength' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data_ProfileLength(var) (&var)

/* Access member 'ProfileValue' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data_ProfileValue(var) var

/* Access member 'ProfileValue' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data_ProfileValue(var) (&var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01(var) (&var)

/* DEFINITION OF BINARY c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data_ProfileValue */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data_ProfileValue {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data_ProfileValue;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data_ProfileValue(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data {

	ED_OCTET ProfileType; /* ODY01a *//*GBD01b*/
	ED_OCTET ProfileLength; /* ODY01a *//*GBD01b*/
	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data_ProfileValue ProfileValue; /* Static, variable size; bits needed 64 *//*GBD01b*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01 */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01 {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET QoSProfileCount; /* ODY01a *//*GBD01b*/
	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles;
#define INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles))
/*FRK03a*/
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles(c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles* sp);

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data_ValueID(var) (&var)

/* Access member 'MaxNumLinkFlowsFwd' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data_MaxNumLinkFlowsFwd(var) var

/* Access member 'MaxNumLinkFlowsFwd' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data_MaxNumLinkFlowsFwd(var) (&var)

/* Access member 'MaxNumLinkFlowsRev' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data_MaxNumLinkFlowsRev(var) var

/* Access member 'MaxNumLinkFlowsRev' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data_MaxNumLinkFlowsRev(var) (&var)

/* Access member 'MaxActivatedLinkFlowsFwd' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data_MaxActivatedLinkFlowsFwd(var) var

/* Access member 'MaxActivatedLinkFlowsFwd' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data_MaxActivatedLinkFlowsFwd(var) (&var)

/* Access member 'MaxActivatedLinkFlowsRev' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data_MaxActivatedLinkFlowsRev(var) var

/* Access member 'MaxActivatedLinkFlowsRev' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data_MaxActivatedLinkFlowsRev(var) (&var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET MaxNumLinkFlowsFwd; /* ODY01a *//*GBD01b*/
	ED_OCTET MaxNumLinkFlowsRev; /* ODY01a *//*GBD01b*/
	ED_OCTET MaxActivatedLinkFlowsFwd; /* ODY01a *//*GBD01b*/
	ED_OCTET MaxActivatedLinkFlowsRev; /* ODY01a *//*GBD01b*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01 */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01 {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows;
#define INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows))
/*FRK03a*/
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows(c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows* sp);

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data_ValueID(var) (&var)

/* Access member 'MaxNumReservationsFwd' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data_MaxNumReservationsFwd(var) var

/* Access member 'MaxNumReservationsFwd' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data_MaxNumReservationsFwd(var) (&var)

/* Access member 'MaxNumReservationsRev' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data_MaxNumReservationsRev(var) var

/* Access member 'MaxNumReservationsRev' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data_MaxNumReservationsRev(var) (&var)

/* Access member 'MaxNumOpenReservationsFwd' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data_MaxNumOpenReservationsFwd(var) var

/* Access member 'MaxNumOpenReservationsFwd' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data_MaxNumOpenReservationsFwd(var) (&var)

/* Access member 'MaxNumOpenReservationsRev' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data_MaxNumOpenReservationsRev(var) var

/* Access member 'MaxNumOpenReservationsRev' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data_MaxNumOpenReservationsRev(var) (&var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET MaxNumReservationsFwd; /* ODY01a *//*GBD01b*/
	ED_OCTET MaxNumReservationsRev; /* ODY01a *//*GBD01b*/
	ED_OCTET MaxNumOpenReservationsFwd; /* ODY01a *//*GBD01b*/
	ED_OCTET MaxNumOpenReservationsRev; /* ODY01a *//*GBD01b*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01 */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01 {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations;
#define INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations))
/*FRK03a*/
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations(c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations* sp);

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_data_ValueID(var) (&var)

/* Access member 'SARSequenceLength' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_data_SARSequenceLength(var) var

/* Access member 'SARSequenceLength' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_data_SARSequenceLength(var) (&var)

/* Access member 'SARSequenceLengthShort' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_data_SARSequenceLengthShort(var) var

/* Access member 'SARSequenceLengthShort' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_data_SARSequenceLengthShort(var) (&var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_data */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET SARSequenceLength; /* ODY01a *//*GBD01b*/
	ED_OCTET SARSequenceLengthShort; /* ODY01a *//*GBD01b*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01 */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01 {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd;
#define INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd))
/*FRK03a*/
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd(c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd* sp);

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data_ValueID(var) (&var)

/* Access member 'AbortTimer' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data_AbortTimer(var) var

/* Access member 'AbortTimer' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data_AbortTimer(var) (&var)

/* Access member 'FlushTimer' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data_FlushTimer(var) var

/* Access member 'FlushTimer' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data_FlushTimer(var) (&var)

/* Access member 'NakDelayTimer' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data_NakDelayTimer(var) var

/* Access member 'NakDelayTimer' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data_NakDelayTimer(var) (&var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_SHORT AbortTimer; /* ODY01a *//*GBD01b*/
	ED_SHORT FlushTimer; /* ODY01a *//*GBD01b*/
	ED_SHORT NakDelayTimer; /* ODY01a *//*GBD01b*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01 */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01 {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd;
#define INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd))
/*FRK03a*/
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd(c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd* sp);

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data_ValueID(var) (&var)

/* Access member 'AbortTimer' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data_AbortTimer(var) var

/* Access member 'AbortTimer' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data_AbortTimer(var) (&var)

/* Access member 'FlushTimer' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data_FlushTimer(var) var

/* Access member 'FlushTimer' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data_FlushTimer(var) (&var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_SHORT AbortTimer; /* ODY01a *//*GBD01b*/
	ED_SHORT FlushTimer; /* ODY01a *//*GBD01b*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01 */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01 {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev;
#define INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev))
/*FRK03a*/
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev(c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev* sp);

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_ValueID(var) (&var)

/* Access member 'ReservationCount' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_ReservationCount(var) var

/* Access member 'ReservationCount' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_ReservationCount(var) (&var)

/* Access member 'ReservationLabel' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data_ReservationLabel(var) var

/* Access member 'ReservationLabel' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data_ReservationLabel(var) (&var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data(var) var

/* Access member 'data02' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02(var) var

/* Access member 'data02' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02(var) (&var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data {

	ED_OCTET ReservationLabel; /* ODY01a *//*GBD01b*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02 */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02 {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET ReservationCount; /* ODY01a *//*GBD01b*/
	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02 data02;/*GFB09*//*GBD01b*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01 */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01 {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd;
#define INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd))
/*FRK03a*/
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd(c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd* sp);

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_ValueID(var) (&var)

/* Access member 'ReservationCount' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_ReservationCount(var) var

/* Access member 'ReservationCount' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_ReservationCount(var) (&var)

/* Access member 'ReservationLabel' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data_ReservationLabel(var) var

/* Access member 'ReservationLabel' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data_ReservationLabel(var) (&var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data(var) var

/* Access member 'data02' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02(var) var

/* Access member 'data02' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02(var) (&var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data {

	ED_OCTET ReservationLabel; /* ODY01a *//*GBD01b*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02 */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02 {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET ReservationCount; /* ODY01a *//*GBD01b*/
	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02 data02;/*GFB09*//*GBD01b*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01 */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01 {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev;
#define INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev))
/*FRK03a*/
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev(c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev* sp);

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data_ValueID(var) (&var)

/* Access member 'ProfileType' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data_ProfileType(var) var

/* Access member 'ProfileType' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data_ProfileType(var) (&var)

/* Access member 'ProfileLength' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data_ProfileLength(var) var

/* Access member 'ProfileLength' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data_ProfileLength(var) (&var)

/* Access member 'ProfileValue' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data_ProfileValue(var) var

/* Access member 'ProfileValue' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data_ProfileValue(var) (&var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01(var) (&var)

/* DEFINITION OF BINARY c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data_ProfileValue */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data_ProfileValue {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data_ProfileValue;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data_ProfileValue(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET ProfileType; /* ODY01a *//*GBD01b*/
	ED_SHORT ProfileLength; /* ODY01a *//*GBD01b*/
	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data_ProfileValue ProfileValue; /* Static, variable size; bits needed 64 *//*GBD01b*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01 */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01 {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd;
#define INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd))
/*FRK03a*/
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd(c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd* sp);

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data_ValueID(var) (&var)

/* Access member 'ProfileType' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data_ProfileType(var) var

/* Access member 'ProfileType' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data_ProfileType(var) (&var)

/* Access member 'ProfileLength' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data_ProfileLength(var) var

/* Access member 'ProfileLength' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data_ProfileLength(var) (&var)

/* Access member 'ProfileValue' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data_ProfileValue(var) var

/* Access member 'ProfileValue' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data_ProfileValue(var) (&var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01(var) (&var)

/* DEFINITION OF BINARY c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data_ProfileValue */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data_ProfileValue {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data_ProfileValue;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data_ProfileValue(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET ProfileType; /* ODY01a *//*GBD01b*/
	ED_SHORT ProfileLength; /* ODY01a *//*GBD01b*/
	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data_ProfileValue ProfileValue; /* Static, variable size; bits needed 64 *//*GBD01b*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01 */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01 {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev;
#define INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev))
/*FRK03a*/
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev(c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev* sp);

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data_ValueID(var) (&var)

/* Access member 'ProfileType' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data_ProfileType(var) var

/* Access member 'ProfileType' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data_ProfileType(var) (&var)

/* Access member 'ProfileLength' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data_ProfileLength(var) var

/* Access member 'ProfileLength' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data_ProfileLength(var) (&var)

/* Access member 'ProfileValue' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data_ProfileValue(var) var

/* Access member 'ProfileValue' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data_ProfileValue(var) (&var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01(var) (&var)

/* DEFINITION OF BINARY c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data_ProfileValue */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data_ProfileValue {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data_ProfileValue;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data_ProfileValue(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET ProfileType; /* ODY01a *//*GBD01b*/
	ED_SHORT ProfileLength; /* ODY01a *//*GBD01b*/
	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data_ProfileValue ProfileValue; /* Static, variable size; bits needed 64 *//*GBD01b*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01 */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01 {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd;
#define INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd))
/*FRK03a*/
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd(c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd* sp);

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data_ValueID(var) (&var)

/* Access member 'ProfileType' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data_ProfileType(var) var

/* Access member 'ProfileType' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data_ProfileType(var) (&var)

/* Access member 'ProfileLength' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data_ProfileLength(var) var

/* Access member 'ProfileLength' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data_ProfileLength(var) (&var)

/* Access member 'ProfileValue' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data_ProfileValue(var) var

/* Access member 'ProfileValue' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data_ProfileValue(var) (&var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01(var) (&var)

/* DEFINITION OF BINARY c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data_ProfileValue */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data_ProfileValue {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data_ProfileValue;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data_ProfileValue(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET ProfileType; /* ODY01a *//*GBD01b*/
	ED_SHORT ProfileLength; /* ODY01a *//*GBD01b*/
	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data_ProfileValue ProfileValue; /* Static, variable size; bits needed 64 *//*GBD01b*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01 */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01 {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev;
#define INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev))
/*FRK03a*/
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev(c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev* sp);

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data_ValueID(var) (&var)

/* Access member 'ProtocolID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data_ProtocolID(var) var

/* Access member 'ProtocolID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data_ProtocolID(var) (&var)

/* Access member 'ProtocolParametersLength' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data_ProtocolParametersLength(var) var

/* Access member 'ProtocolParametersLength' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data_ProtocolParametersLength(var) (&var)

/* Access member 'ProtocolParameters' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data_ProtocolParameters(var) var

/* Access member 'ProtocolParameters' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data_ProtocolParameters(var) (&var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01(var) (&var)

/* DEFINITION OF BINARY c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data_ProtocolParameters */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data_ProtocolParameters {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data_ProtocolParameters;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data_ProtocolParameters(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET ProtocolID; /* ODY01a *//*GBD01b*/
	ED_OCTET ProtocolParametersLength; /* ODY01a *//*GBD01b*/
	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data_ProtocolParameters ProtocolParameters; /* Static, variable size; bits needed 64 *//*GBD01b*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01 */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01 {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd;
#define INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd))
/*FRK03a*/
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd(c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd* sp);

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data_ValueID(var) (&var)

/* Access member 'ProtocolID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data_ProtocolID(var) var

/* Access member 'ProtocolID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data_ProtocolID(var) (&var)

/* Access member 'ProtocolParametersLength' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data_ProtocolParametersLength(var) var

/* Access member 'ProtocolParametersLength' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data_ProtocolParametersLength(var) (&var)

/* Access member 'ProtocolParameters' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data_ProtocolParameters(var) var

/* Access member 'ProtocolParameters' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data_ProtocolParameters(var) (&var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01(var) (&var)

/* DEFINITION OF BINARY c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data_ProtocolParameters */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data_ProtocolParameters {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data_ProtocolParameters;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data_ProtocolParameters(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET ProtocolID; /* ODY01a *//*GBD01b*/
	ED_OCTET ProtocolParametersLength; /* ODY01a *//*GBD01b*/
	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data_ProtocolParameters ProtocolParameters; /* Static, variable size; bits needed 64 *//*GBD01b*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01 */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01 {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev;
#define INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev))
/*FRK03a*/
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev(c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev* sp);

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data_ValueID(var) (&var)

/* Access member 'ProtocolID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data_ProtocolID(var) var

/* Access member 'ProtocolID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data_ProtocolID(var) (&var)

/* Access member 'ProtocolParametersLength' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data_ProtocolParametersLength(var) var

/* Access member 'ProtocolParametersLength' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data_ProtocolParametersLength(var) (&var)

/* Access member 'ProtocolParameters' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data_ProtocolParameters(var) var

/* Access member 'ProtocolParameters' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data_ProtocolParameters(var) (&var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01(var) (&var)

/* DEFINITION OF BINARY c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data_ProtocolParameters */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data_ProtocolParameters {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data_ProtocolParameters;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data_ProtocolParameters(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET ProtocolID; /* ODY01a *//*GBD01b*/
	ED_OCTET ProtocolParametersLength; /* ODY01a *//*GBD01b*/
	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data_ProtocolParameters ProtocolParameters; /* Static, variable size; bits needed 64 *//*GBD01b*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01 */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01 {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd;
#define INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd))
/*FRK03a*/
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd(c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd* sp);

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data_ValueID(var) (&var)

/* Access member 'ProtocolID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data_ProtocolID(var) var

/* Access member 'ProtocolID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data_ProtocolID(var) (&var)

/* Access member 'ProtocolParametersLength' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data_ProtocolParametersLength(var) var

/* Access member 'ProtocolParametersLength' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data_ProtocolParametersLength(var) (&var)

/* Access member 'ProtocolParameters' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data_ProtocolParameters(var) var

/* Access member 'ProtocolParameters' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data_ProtocolParameters(var) (&var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01(var) (&var)

/* DEFINITION OF BINARY c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data_ProtocolParameters */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data_ProtocolParameters {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data_ProtocolParameters;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data_ProtocolParameters(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET ProtocolID; /* ODY01a *//*GBD01b*/
	ED_OCTET ProtocolParametersLength; /* ODY01a *//*GBD01b*/
	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data_ProtocolParameters ProtocolParameters; /* Static, variable size; bits needed 64 *//*GBD01b*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01 */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01 {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev;
#define INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev))
/*FRK03a*/
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev(c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev* sp);

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_ValueID(var) (&var)

/* Access member 'ProtocolSupported' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_ProtocolSupported(var) var

/* Access member 'ProtocolSupported' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_ProtocolSupported(var) (&var)

/* Access member 'SupportedProtocolParametersValuesLength' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_SupportedProtocolParametersValuesLength(var) var

/* Access member 'SupportedProtocolParametersValuesLength' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP_SupportedProtocolParametersValuesLength(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET ProtocolSupported; /* ODY01a *//*GBD01b*/
	ED_OCTET SupportedProtocolParametersValuesLength; /* ODY01a *//*GBD01b*/

}	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP;
#define INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP))
/*FRK03a*/
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP(c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP* sp);

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_ValueID(var) (&var)

/* Access member 'ProtocolSupported' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_ProtocolSupported(var) var

/* Access member 'ProtocolSupported' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_ProtocolSupported(var) (&var)

/* Access member 'SupportedProtocolParametersValuesLength' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_SupportedProtocolParametersValuesLength(var) var

/* Access member 'SupportedProtocolParametersValuesLength' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_SupportedProtocolParametersValuesLength(var) (&var)

/* Access member 'SupportedProtocolParametersValues' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_SupportedProtocolParametersValues(var) var

/* Access member 'SupportedProtocolParametersValues' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_SupportedProtocolParametersValues(var) (&var)

/* DEFINITION OF BINARY c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_SupportedProtocolParametersValues */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_SupportedProtocolParametersValues {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_SupportedProtocolParametersValues;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_SupportedProtocolParametersValues(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET ProtocolSupported; /* ODY01a *//*GBD01b*/
	ED_OCTET SupportedProtocolParametersValuesLength; /* ODY01a *//*GBD01b*/
	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP_SupportedProtocolParametersValues SupportedProtocolParametersValues; /* Static, variable size; bits needed 64 *//*GBD01b*/

}	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP;
#define INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP))
/*FRK03a*/
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP(c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP* sp);

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_ValueID(var) (&var)

/* Access member 'BCMCSFlowCount' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_BCMCSFlowCount(var) var

/* Access member 'BCMCSFlowCount' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_BCMCSFlowCount(var) (&var)

/* Access member 'BCMCSFlowID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data_BCMCSFlowID(var) var

/* Access member 'BCMCSFlowID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data_BCMCSFlowID(var) (&var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data(var) var

/* Access member 'data02' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02(var) var

/* Access member 'data02' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02(var) (&var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data {

	ED_LONG BCMCSFlowID; /* ODY01a *//*GBD01b*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02 */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02 {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET BCMCSFlowCount; /* ODY01a *//*GBD01b*/
	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02 data02;/*GFB09*//*GBD01b*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01 */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01 {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation;
#define INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation))
/*FRK03a*/
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation(c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation* sp);

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_ValueID(var) var

/* Access member 'ValueID' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_ValueID(var) (&var)

/* Access member 'ProgramCount' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_ProgramCount(var) var

/* Access member 'ProgramCount' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_ProgramCount(var) (&var)

/* Access member 'ProgramIDLSBLength' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_ProgramIDLSBLength(var) var

/* Access member 'ProgramIDLSBLength' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_ProgramIDLSBLength(var) (&var)

/* Access member 'ProgramIDLSBs' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_ProgramIDLSBs(var) var

/* Access member 'ProgramIDLSBs' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_ProgramIDLSBs(var) (&var)

/* Access member 'FlowDiscriminatorCount' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_FlowDiscriminatorCount(var) var

/* Access member 'FlowDiscriminatorCount' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_FlowDiscriminatorCount(var) (&var)

/* Access member 'FlowDiscriminator' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data_FlowDiscriminator(var) var

/* Access member 'FlowDiscriminator' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data_FlowDiscriminator(var) (&var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data(var) var

/* Access member 'data03' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03(var) var

/* Access member 'data03' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03(var) (&var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data(var) var

/* Access member 'data02' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02(var) var

/* Access member 'data02' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02(var) (&var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data(var) (*var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01(var) var

/* Access member 'data01' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data {

	ED_OCTET FlowDiscriminator; /* ODY01a *//*GBD01b*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03 */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03 {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data {

	ED_OCTET ProgramIDLSBLength; /* ODY01a *//*GBD01b*/
	ED_LONG ProgramIDLSBs; /* ODY01a *//*GBD01b*/
	ED_OCTET FlowDiscriminatorCount; /* ODY01a *//*GBD01b*/
	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03 data03;/*GFB09*//*GBD01b*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02 */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02 {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data {

	ED_OCTET ValueID; /* ODY01a *//*GBD01b*/
	ED_OCTET ProgramCount; /* ODY01a *//*GBD01b*/
	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02 data02;/*GFB09*//*GBD01b*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01 */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01 {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01;


/*-A----------------------------------*/
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation {

	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01 data01;/*GFB09*//*GBD01b*/

}	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation;
#define INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation))
/*FRK03a*/
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation(c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation* sp);

/* Access member 'AttributeId' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_AttributeId(var) var

/* Access member 'AttributeId' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_AttributeId(var) (&var)

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Values' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Values_data(var) var

/* Access member 'data' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Values' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Values_data(var) (&var)

/* Access member 'Values' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Values(var) var

/* Access member 'Values' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Values(var) (&var)

/* Access member 'ATSupportedQoSProfiles' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedQoSProfiles(var) (*var)

/* Access member 'ATSupportedQoSProfiles' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedQoSProfiles(var) var

/* Access member 'ANSupportedQoSProfiles' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ANSupportedQoSProfiles(var) (*var)

/* Access member 'ANSupportedQoSProfiles' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ANSupportedQoSProfiles(var) var

/* Access member 'MaxLinkFlows' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_MaxLinkFlows(var) (*var)

/* Access member 'MaxLinkFlows' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_MaxLinkFlows(var) var

/* Access member 'MaxReservations' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_MaxReservations(var) (*var)

/* Access member 'MaxReservations' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_MaxReservations(var) var

/* Access member 'FlowNNTimersFwd' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersFwd(var) (*var)

/* Access member 'FlowNNTimersFwd' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersFwd(var) var

/* Access member 'FlowNNTimersRev' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersRev(var) (*var)

/* Access member 'FlowNNTimersRev' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersRev(var) var

/* Access member 'FlowNNReservationFwd' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationFwd(var) (*var)

/* Access member 'FlowNNReservationFwd' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationFwd(var) var

/* Access member 'FlowNNReservationRev' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationRev(var) (*var)

/* Access member 'FlowNNReservationRev' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationRev(var) var

/* Access member 'ReservationKKQoSRequestFwd' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestFwd(var) (*var)

/* Access member 'ReservationKKQoSRequestFwd' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestFwd(var) var

/* Access member 'ReservationKKQoSRequestRev' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestRev(var) (*var)

/* Access member 'ReservationKKQoSRequestRev' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestRev(var) var

/* Access member 'ReservationKKQoSResponseFwd' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseFwd(var) (*var)

/* Access member 'ReservationKKQoSResponseFwd' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseFwd(var) var

/* Access member 'ReservationKKQoSResponseRev' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseRev(var) (*var)

/* Access member 'ReservationKKQoSResponseRev' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseRev(var) var

/* Access member 'FlowNNFlowProtocolParametersFwd' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersFwd(var) (*var)

/* Access member 'FlowNNFlowProtocolParametersFwd' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersFwd(var) var

/* Access member 'FlowNNFlowProtocolParametersRev' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersRev(var) (*var)

/* Access member 'FlowNNFlowProtocolParametersRev' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersRev(var) var

/* Access member 'FlowNNRouteProtocolParametersFwd' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersFwd(var) (*var)

/* Access member 'FlowNNRouteProtocolParametersFwd' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersFwd(var) var

/* Access member 'FlowNNRouteProtocolParametersRev' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersRev(var) (*var)

/* Access member 'FlowNNRouteProtocolParametersRev' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersRev(var) var

/* Access member 'ATSupportedFlowProtocolParametersPP' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedFlowProtocolParametersPP(var) (*var)

/* Access member 'ATSupportedFlowProtocolParametersPP' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedFlowProtocolParametersPP(var) var

/* Access member 'ATSupportedRouteProtocolParametersPP' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedRouteProtocolParametersPP(var) (*var)

/* Access member 'ATSupportedRouteProtocolParametersPP' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedRouteProtocolParametersPP(var) var

/* Access member 'ReservationKKBCMCSFlowIDAssociation' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSFlowIDAssociation(var) (*var)

/* Access member 'ReservationKKBCMCSFlowIDAssociation' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSFlowIDAssociation(var) var

/* Access member 'ReservationKKBCMCSProgramIDAssociation' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSProgramIDAssociation(var) (*var)

/* Access member 'ReservationKKBCMCSProgramIDAssociation' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSProgramIDAssociation(var) var

/* Access member 'complex' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex(var) var

/* Access member 'complex' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Values */
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Values {

	ED_LONG* data; /* NDY01a *//*GBD01b*//*GAD01a*//*AR02 ('TDMSequence'-13960=EDCore::TDMSequence)  */
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Values;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex */
typedef enum {
	U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_NONE,
	U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedQoSProfiles,
	U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ANSupportedQoSProfiles,
	U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_MaxLinkFlows,
	U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_MaxReservations,
	U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersFwd,
	U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersRev,
	U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationFwd,
	U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationRev,
	U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestFwd,
	U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestRev,
	U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseFwd,
	U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseRev,
	U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersFwd,
	U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersRev,
	U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersFwd,
	U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersRev,
	U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedFlowProtocolParametersPP,
	U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedRouteProtocolParametersPP,
	U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSFlowIDAssociation,
	U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSProgramIDAssociation
} TPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex;

typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex {

	TPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex Present;
	union {
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles *ATSupportedQoSProfiles; /* ODY01 *//*GBD01b*/
	
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles *ANSupportedQoSProfiles; /* ODY01 *//*GBD01b*/
	
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows *MaxLinkFlows; /* ODY01 *//*GBD01b*/
	
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations *MaxReservations; /* ODY01 *//*GBD01b*/
	
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd *FlowNNTimersFwd; /* ODY01 *//*GBD01b*/
	
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev *FlowNNTimersRev; /* ODY01 *//*GBD01b*/
	
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd *FlowNNReservationFwd; /* ODY01 *//*GBD01b*/
	
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev *FlowNNReservationRev; /* ODY01 *//*GBD01b*/
	
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd *ReservationKKQoSRequestFwd; /* ODY01 *//*GBD01b*/
	
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev *ReservationKKQoSRequestRev; /* ODY01 *//*GBD01b*/
	
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd *ReservationKKQoSResponseFwd; /* ODY01 *//*GBD01b*/
	
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev *ReservationKKQoSResponseRev; /* ODY01 *//*GBD01b*/
	
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd *FlowNNFlowProtocolParametersFwd; /* ODY01 *//*GBD01b*/
	
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev *FlowNNFlowProtocolParametersRev; /* ODY01 *//*GBD01b*/
	
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd *FlowNNRouteProtocolParametersFwd; /* ODY01 *//*GBD01b*/
	
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev *FlowNNRouteProtocolParametersRev; /* ODY01 *//*GBD01b*/
	
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP *ATSupportedFlowProtocolParametersPP; /* ODY01 *//*GBD01b*/
	
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP *ATSupportedRouteProtocolParametersPP; /* ODY01 *//*GBD01b*/
	
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation *ReservationKKBCMCSFlowIDAssociation; /* ODY01 *//*GBD01b*/
	
		c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation *ReservationKKBCMCSProgramIDAssociation; /* ODY01 *//*GBD01b*/
	
	} u;

} c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex;


/*-A----------------------------------*/
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes {

	ED_LONG AttributeId; /* ODY01a *//*GBD01b*/
	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Values Values;/*GFB09*//*GBD01b*/
	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex complex;/*GBD01b*/

}	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes;
#define INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes))
/*FRK03a*/
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes(c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes* sp);

/* Access member 'AttributeId' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response_AttributeId(var) var

/* Access member 'AttributeId' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response_AttributeId(var) (&var)

/* Access member 'Value' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response' as a variable reference */
#define VAR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response_Value(var) var

/* Access member 'Value' of type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response' as a pointer */
#define PTR_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response_Value(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response {

	ED_LONG AttributeId; /* ODY01a *//*GBD01b*/
	ED_LONG Value; /* ODY01a *//*GBD01b*/

}	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response;
#define INIT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response))
/*FRK03a*/
void FREE_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response(c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response* sp);

/* Access member 'AttributeId' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_AttributeId(var) var

/* Access member 'AttributeId' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_AttributeId(var) (&var)

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Values' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Values_data(var) var

/* Access member 'data' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Values' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Values_data(var) (&var)

/* Access member 'Values' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Values(var) var

/* Access member 'Values' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Values(var) (&var)

/* Access member 'ATSupportedQoSProfiles' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedQoSProfiles(var) (*var)

/* Access member 'ATSupportedQoSProfiles' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedQoSProfiles(var) var

/* Access member 'ANSupportedQoSProfiles' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ANSupportedQoSProfiles(var) (*var)

/* Access member 'ANSupportedQoSProfiles' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ANSupportedQoSProfiles(var) var

/* Access member 'MaxLinkFlows' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_MaxLinkFlows(var) (*var)

/* Access member 'MaxLinkFlows' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_MaxLinkFlows(var) var

/* Access member 'MaxReservations' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_MaxReservations(var) (*var)

/* Access member 'MaxReservations' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_MaxReservations(var) var

/* Access member 'FlowNNSequenceLengthFwd' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNSequenceLengthFwd(var) (*var)

/* Access member 'FlowNNSequenceLengthFwd' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNSequenceLengthFwd(var) var

/* Access member 'FlowNNTimersFwd' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersFwd(var) (*var)

/* Access member 'FlowNNTimersFwd' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersFwd(var) var

/* Access member 'FlowNNTimersRev' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersRev(var) (*var)

/* Access member 'FlowNNTimersRev' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersRev(var) var

/* Access member 'FlowNNReservationFwd' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationFwd(var) (*var)

/* Access member 'FlowNNReservationFwd' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationFwd(var) var

/* Access member 'FlowNNReservationRev' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationRev(var) (*var)

/* Access member 'FlowNNReservationRev' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationRev(var) var

/* Access member 'ReservationKKQoSRequestFwd' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestFwd(var) (*var)

/* Access member 'ReservationKKQoSRequestFwd' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestFwd(var) var

/* Access member 'ReservationKKQoSRequestRev' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestRev(var) (*var)

/* Access member 'ReservationKKQoSRequestRev' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestRev(var) var

/* Access member 'ReservationKKQoSResponseFwd' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseFwd(var) (*var)

/* Access member 'ReservationKKQoSResponseFwd' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseFwd(var) var

/* Access member 'ReservationKKQoSResponseRev' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseRev(var) (*var)

/* Access member 'ReservationKKQoSResponseRev' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseRev(var) var

/* Access member 'FlowNNFlowProtocolParametersFwd' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersFwd(var) (*var)

/* Access member 'FlowNNFlowProtocolParametersFwd' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersFwd(var) var

/* Access member 'FlowNNFlowProtocolParametersRev' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersRev(var) (*var)

/* Access member 'FlowNNFlowProtocolParametersRev' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersRev(var) var

/* Access member 'FlowNNRouteProtocolParametersFwd' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersFwd(var) (*var)

/* Access member 'FlowNNRouteProtocolParametersFwd' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersFwd(var) var

/* Access member 'FlowNNRouteProtocolParametersRev' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersRev(var) (*var)

/* Access member 'FlowNNRouteProtocolParametersRev' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersRev(var) var

/* Access member 'ATSupportedFlowProtocolParametersPP' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedFlowProtocolParametersPP(var) (*var)

/* Access member 'ATSupportedFlowProtocolParametersPP' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedFlowProtocolParametersPP(var) var

/* Access member 'ATSupportedRouteProtocolParametersPP' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedRouteProtocolParametersPP(var) (*var)

/* Access member 'ATSupportedRouteProtocolParametersPP' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedRouteProtocolParametersPP(var) var

/* Access member 'ReservationKKBCMCSFlowIDAssociation' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSFlowIDAssociation(var) (*var)

/* Access member 'ReservationKKBCMCSFlowIDAssociation' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSFlowIDAssociation(var) var

/* Access member 'ReservationKKBCMCSProgramIDAssociation' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSProgramIDAssociation(var) (*var)

/* Access member 'ReservationKKBCMCSProgramIDAssociation' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSProgramIDAssociation(var) var

/* Access member 'complex' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex(var) var

/* Access member 'complex' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Values */
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Values {

	ED_LONG* data; /* NDY01a *//*GBD01b*//*GAD01a*//*AR02 ('TDMSequence'-14016=EDCore::TDMSequence)  */
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Values;

/* DEFINITION OF SUB-STRUCTURE c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex */
typedef enum {
	U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_NONE,
	U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedQoSProfiles,
	U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ANSupportedQoSProfiles,
	U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_MaxLinkFlows,
	U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_MaxReservations,
	U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNSequenceLengthFwd,
	U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersFwd,
	U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersRev,
	U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationFwd,
	U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationRev,
	U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestFwd,
	U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestRev,
	U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseFwd,
	U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseRev,
	U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersFwd,
	U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersRev,
	U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersFwd,
	U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersRev,
	U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedFlowProtocolParametersPP,
	U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedRouteProtocolParametersPP,
	U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSFlowIDAssociation,
	U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSProgramIDAssociation
} TPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex;

typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex {

	TPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex Present;
	union {
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles *ATSupportedQoSProfiles; /* ODY01 *//*GBD01b*/
	
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles *ANSupportedQoSProfiles; /* ODY01 *//*GBD01b*/
	
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows *MaxLinkFlows; /* ODY01 *//*GBD01b*/
	
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations *MaxReservations; /* ODY01 *//*GBD01b*/
	
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd *FlowNNSequenceLengthFwd; /* ODY01 *//*GBD01b*/
	
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd *FlowNNTimersFwd; /* ODY01 *//*GBD01b*/
	
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev *FlowNNTimersRev; /* ODY01 *//*GBD01b*/
	
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd *FlowNNReservationFwd; /* ODY01 *//*GBD01b*/
	
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev *FlowNNReservationRev; /* ODY01 *//*GBD01b*/
	
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd *ReservationKKQoSRequestFwd; /* ODY01 *//*GBD01b*/
	
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev *ReservationKKQoSRequestRev; /* ODY01 *//*GBD01b*/
	
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd *ReservationKKQoSResponseFwd; /* ODY01 *//*GBD01b*/
	
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev *ReservationKKQoSResponseRev; /* ODY01 *//*GBD01b*/
	
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd *FlowNNFlowProtocolParametersFwd; /* ODY01 *//*GBD01b*/
	
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev *FlowNNFlowProtocolParametersRev; /* ODY01 *//*GBD01b*/
	
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd *FlowNNRouteProtocolParametersFwd; /* ODY01 *//*GBD01b*/
	
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev *FlowNNRouteProtocolParametersRev; /* ODY01 *//*GBD01b*/
	
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedFlowProtocolParametersPP *ATSupportedFlowProtocolParametersPP; /* ODY01 *//*GBD01b*/
	
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedRouteProtocolParametersPP *ATSupportedRouteProtocolParametersPP; /* ODY01 *//*GBD01b*/
	
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation *ReservationKKBCMCSFlowIDAssociation; /* ODY01 *//*GBD01b*/
	
		c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation *ReservationKKBCMCSProgramIDAssociation; /* ODY01 *//*GBD01b*/
	
	} u;

} c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex;


/*-A----------------------------------*/
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes {

	ED_LONG AttributeId; /* ODY01a *//*GBD01b*/
	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Values Values;/*GFB09*//*GBD01b*/
	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex complex;/*GBD01b*/

}	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes;
#define INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes))
/*FRK03a*/
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes(c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes* sp);

/* Access member 'AttributeId' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response_AttributeId(var) var

/* Access member 'AttributeId' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response_AttributeId(var) (&var)

/* Access member 'Value' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response' as a variable reference */
#define VAR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response_Value(var) var

/* Access member 'Value' of type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response' as a pointer */
#define PTR_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response_Value(var) (&var)


/*-A----------------------------------*/
typedef struct _c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response {

	ED_LONG AttributeId; /* ODY01a *//*GBD01b*/
	ED_LONG Value; /* ODY01a *//*GBD01b*/

}	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response;
#define INIT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response(sp) ED_RESET_MEM ((sp), sizeof (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response))
/*FRK03a*/
void FREE_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response(c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response* sp);

/* Access member 'TransactionID' of type 'c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents' as a variable reference */
#define VAR_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents' as a pointer */
#define PTR_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_TransactionID(var) (&var)

/* Access member 'AttributeLength' of type 'c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01_data' as a variable reference */
#define VAR_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01_data_AttributeLength(var) var

/* Access member 'AttributeLength' of type 'c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01_data' as a pointer */
#define PTR_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01_data_AttributeLength(var) (&var)

/* Access member 'AttributeRecord' of type 'c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01_data' as a variable reference */
#define VAR_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01_data_AttributeRecord(var) var

/* Access member 'AttributeRecord' of type 'c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01_data' as a pointer */
#define PTR_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01_data_AttributeRecord(var) (&var)

/* Access member 'data' of type 'c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01' as a variable reference */
#define VAR_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01' as a pointer */
#define PTR_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01_data(var) var

/* Access member 'data01' of type 'c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents' as a variable reference */
#define VAR_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01(var) var

/* Access member 'data01' of type 'c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents' as a pointer */
#define PTR_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01_data */
typedef struct _c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01_data {

	ED_OCTET AttributeLength; /* ODY01a *//*GBD01b*/
	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes AttributeRecord; /* ODY01a *//*GBD01b*/

} c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01 */
typedef struct _c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01 {

	c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01;


/*-A----------------------------------*/
typedef struct _c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents;
#define INIT_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents))
/*FRK03a*/
void FREE_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents(c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents* sp);

/* Access member 'TransactionID' of type 'c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents' as a variable reference */
#define VAR_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents' as a pointer */
#define PTR_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_TransactionID(var) (&var)

/* Access member 'AttributeLength' of type 'c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01_data' as a variable reference */
#define VAR_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01_data_AttributeLength(var) var

/* Access member 'AttributeLength' of type 'c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01_data' as a pointer */
#define PTR_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01_data_AttributeLength(var) (&var)

/* Access member 'AttributeRecord' of type 'c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01_data' as a variable reference */
#define VAR_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01_data_AttributeRecord(var) var

/* Access member 'AttributeRecord' of type 'c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01_data' as a pointer */
#define PTR_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01_data_AttributeRecord(var) (&var)

/* Access member 'data' of type 'c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01' as a variable reference */
#define VAR_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01' as a pointer */
#define PTR_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01_data(var) var

/* Access member 'data01' of type 'c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents' as a variable reference */
#define VAR_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01(var) var

/* Access member 'data01' of type 'c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents' as a pointer */
#define PTR_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01_data */
typedef struct _c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01_data {

	ED_OCTET AttributeLength; /* ODY01a *//*GBD01b*/
	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Response AttributeRecord; /* ODY01a *//*GBD01b*/

} c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01 */
typedef struct _c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01 {

	c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01;


/*-A----------------------------------*/
typedef struct _c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents;
#define INIT_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents))
/*FRK03a*/
void FREE_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents(c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents* sp);

/* Access member 'TransactionID' of type 'c_EMFPKA_RSP_INUSE_RouteSelect_contents' as a variable reference */
#define VAR_c_EMFPKA_RSP_INUSE_RouteSelect_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_EMFPKA_RSP_INUSE_RouteSelect_contents' as a pointer */
#define PTR_c_EMFPKA_RSP_INUSE_RouteSelect_contents_TransactionID(var) (&var)

/* Access member 'Route' of type 'c_EMFPKA_RSP_INUSE_RouteSelect_contents' as a variable reference */
#define VAR_c_EMFPKA_RSP_INUSE_RouteSelect_contents_Route(var) var

/* Access member 'Route' of type 'c_EMFPKA_RSP_INUSE_RouteSelect_contents' as a pointer */
#define PTR_c_EMFPKA_RSP_INUSE_RouteSelect_contents_Route(var) (&var)

/* Access member 'Reserved' of type 'c_EMFPKA_RSP_INUSE_RouteSelect_contents' as a variable reference */
#define VAR_c_EMFPKA_RSP_INUSE_RouteSelect_contents_Reserved(var) var

/* Access member 'Reserved' of type 'c_EMFPKA_RSP_INUSE_RouteSelect_contents' as a pointer */
#define PTR_c_EMFPKA_RSP_INUSE_RouteSelect_contents_Reserved(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RSP_INUSE_RouteSelect_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Route; /* ODY01a *//*GBD01b*/
	ED_OCTET Reserved; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RSP_INUSE_RouteSelect_contents;
#define INIT_c_EMFPKA_RSP_INUSE_RouteSelect_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RSP_INUSE_RouteSelect_contents))
/*FRK03a*/
void FREE_c_EMFPKA_RSP_INUSE_RouteSelect_contents(c_EMFPKA_RSP_INUSE_RouteSelect_contents* sp);

/* Access member 'TransactionID' of type 'c_EMFPKA_RSP_INUSE_RouteSelectAck_contents' as a variable reference */
#define VAR_c_EMFPKA_RSP_INUSE_RouteSelectAck_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_EMFPKA_RSP_INUSE_RouteSelectAck_contents' as a pointer */
#define PTR_c_EMFPKA_RSP_INUSE_RouteSelectAck_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RSP_INUSE_RouteSelectAck_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RSP_INUSE_RouteSelectAck_contents;
#define INIT_c_EMFPKA_RSP_INUSE_RouteSelectAck_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RSP_INUSE_RouteSelectAck_contents))
/*FRK03a*/
void FREE_c_EMFPKA_RSP_INUSE_RouteSelectAck_contents(c_EMFPKA_RSP_INUSE_RouteSelectAck_contents* sp);

/* Access member 'TransactionID' of type 'c_EMFPKA_RSP_INUSE_ActivateRoute_contents' as a variable reference */
#define VAR_c_EMFPKA_RSP_INUSE_ActivateRoute_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_EMFPKA_RSP_INUSE_ActivateRoute_contents' as a pointer */
#define PTR_c_EMFPKA_RSP_INUSE_ActivateRoute_contents_TransactionID(var) (&var)

/* Access member 'Route' of type 'c_EMFPKA_RSP_INUSE_ActivateRoute_contents' as a variable reference */
#define VAR_c_EMFPKA_RSP_INUSE_ActivateRoute_contents_Route(var) var

/* Access member 'Route' of type 'c_EMFPKA_RSP_INUSE_ActivateRoute_contents' as a pointer */
#define PTR_c_EMFPKA_RSP_INUSE_ActivateRoute_contents_Route(var) (&var)

/* Access member 'Reserved' of type 'c_EMFPKA_RSP_INUSE_ActivateRoute_contents' as a variable reference */
#define VAR_c_EMFPKA_RSP_INUSE_ActivateRoute_contents_Reserved(var) var

/* Access member 'Reserved' of type 'c_EMFPKA_RSP_INUSE_ActivateRoute_contents' as a pointer */
#define PTR_c_EMFPKA_RSP_INUSE_ActivateRoute_contents_Reserved(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RSP_INUSE_ActivateRoute_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Route; /* ODY01a *//*GBD01b*/
	ED_OCTET Reserved; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RSP_INUSE_ActivateRoute_contents;
#define INIT_c_EMFPKA_RSP_INUSE_ActivateRoute_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RSP_INUSE_ActivateRoute_contents))
/*FRK03a*/
void FREE_c_EMFPKA_RSP_INUSE_ActivateRoute_contents(c_EMFPKA_RSP_INUSE_ActivateRoute_contents* sp);

/* Access member 'TransactionID' of type 'c_EMFPKA_RSP_INUSE_ActivateRouteAck_contents' as a variable reference */
#define VAR_c_EMFPKA_RSP_INUSE_ActivateRouteAck_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_EMFPKA_RSP_INUSE_ActivateRouteAck_contents' as a pointer */
#define PTR_c_EMFPKA_RSP_INUSE_ActivateRouteAck_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RSP_INUSE_ActivateRouteAck_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RSP_INUSE_ActivateRouteAck_contents;
#define INIT_c_EMFPKA_RSP_INUSE_ActivateRouteAck_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RSP_INUSE_ActivateRouteAck_contents))
/*FRK03a*/
void FREE_c_EMFPKA_RSP_INUSE_ActivateRouteAck_contents(c_EMFPKA_RSP_INUSE_ActivateRouteAck_contents* sp);

/* Access member 'LinkFlowNumber' of type 'c_EMFPKA_RLP_INUSE_ResetTxIndication_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ResetTxIndication_contents_LinkFlowNumber(var) var

/* Access member 'LinkFlowNumber' of type 'c_EMFPKA_RLP_INUSE_ResetTxIndication_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ResetTxIndication_contents_LinkFlowNumber(var) (&var)

/* Access member 'Route' of type 'c_EMFPKA_RLP_INUSE_ResetTxIndication_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ResetTxIndication_contents_Route(var) var

/* Access member 'Route' of type 'c_EMFPKA_RLP_INUSE_ResetTxIndication_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ResetTxIndication_contents_Route(var) (&var)

/* Access member 'Reserved' of type 'c_EMFPKA_RLP_INUSE_ResetTxIndication_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ResetTxIndication_contents_Reserved(var) var

/* Access member 'Reserved' of type 'c_EMFPKA_RLP_INUSE_ResetTxIndication_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ResetTxIndication_contents_Reserved(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_ResetTxIndication_contents {

	ED_OCTET LinkFlowNumber; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Route; /* ODY01a *//*GBD01b*/
	ED_OCTET Reserved; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_ResetTxIndication_contents;
#define INIT_c_EMFPKA_RLP_INUSE_ResetTxIndication_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_ResetTxIndication_contents))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_ResetTxIndication_contents(c_EMFPKA_RLP_INUSE_ResetTxIndication_contents* sp);

/* Access member 'LinkFlowNumber' of type 'c_EMFPKA_RLP_INUSE_ResetRxIndication_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ResetRxIndication_contents_LinkFlowNumber(var) var

/* Access member 'LinkFlowNumber' of type 'c_EMFPKA_RLP_INUSE_ResetRxIndication_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ResetRxIndication_contents_LinkFlowNumber(var) (&var)

/* Access member 'Route' of type 'c_EMFPKA_RLP_INUSE_ResetRxIndication_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ResetRxIndication_contents_Route(var) var

/* Access member 'Route' of type 'c_EMFPKA_RLP_INUSE_ResetRxIndication_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ResetRxIndication_contents_Route(var) (&var)

/* Access member 'Reserved' of type 'c_EMFPKA_RLP_INUSE_ResetRxIndication_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ResetRxIndication_contents_Reserved(var) var

/* Access member 'Reserved' of type 'c_EMFPKA_RLP_INUSE_ResetRxIndication_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ResetRxIndication_contents_Reserved(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_ResetRxIndication_contents {

	ED_OCTET LinkFlowNumber; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Route; /* ODY01a *//*GBD01b*/
	ED_OCTET Reserved; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_ResetRxIndication_contents;
#define INIT_c_EMFPKA_RLP_INUSE_ResetRxIndication_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_ResetRxIndication_contents))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_ResetRxIndication_contents(c_EMFPKA_RLP_INUSE_ResetRxIndication_contents* sp);

/* Access member 'LinkFlowNumber' of type 'c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents_LinkFlowNumber(var) var

/* Access member 'LinkFlowNumber' of type 'c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents_LinkFlowNumber(var) (&var)

/* Access member 'Route' of type 'c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents_Route(var) var

/* Access member 'Route' of type 'c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents_Route(var) (&var)

/* Access member 'Reserved' of type 'c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents_Reserved(var) var

/* Access member 'Reserved' of type 'c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents_Reserved(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents {

	ED_OCTET LinkFlowNumber; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Route; /* ODY01a *//*GBD01b*/
	ED_OCTET Reserved; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents;
#define INIT_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents(c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents* sp);

/* Access member 'LinkFlowNumber' of type 'c_EMFPKA_RLP_INUSE_ResetTxComplete_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ResetTxComplete_contents_LinkFlowNumber(var) var

/* Access member 'LinkFlowNumber' of type 'c_EMFPKA_RLP_INUSE_ResetTxComplete_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ResetTxComplete_contents_LinkFlowNumber(var) (&var)

/* Access member 'Route' of type 'c_EMFPKA_RLP_INUSE_ResetTxComplete_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ResetTxComplete_contents_Route(var) var

/* Access member 'Route' of type 'c_EMFPKA_RLP_INUSE_ResetTxComplete_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ResetTxComplete_contents_Route(var) (&var)

/* Access member 'Reserved' of type 'c_EMFPKA_RLP_INUSE_ResetTxComplete_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ResetTxComplete_contents_Reserved(var) var

/* Access member 'Reserved' of type 'c_EMFPKA_RLP_INUSE_ResetTxComplete_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ResetTxComplete_contents_Reserved(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_ResetTxComplete_contents {

	ED_OCTET LinkFlowNumber; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Route; /* ODY01a *//*GBD01b*/
	ED_OCTET Reserved; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_ResetTxComplete_contents;
#define INIT_c_EMFPKA_RLP_INUSE_ResetTxComplete_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_ResetTxComplete_contents))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_ResetTxComplete_contents(c_EMFPKA_RLP_INUSE_ResetTxComplete_contents* sp);

/* Access member 'LinkFlowNumber' of type 'c_EMFPKA_RLP_INUSE_ResetRxComplete_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ResetRxComplete_contents_LinkFlowNumber(var) var

/* Access member 'LinkFlowNumber' of type 'c_EMFPKA_RLP_INUSE_ResetRxComplete_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ResetRxComplete_contents_LinkFlowNumber(var) (&var)

/* Access member 'Route' of type 'c_EMFPKA_RLP_INUSE_ResetRxComplete_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ResetRxComplete_contents_Route(var) var

/* Access member 'Route' of type 'c_EMFPKA_RLP_INUSE_ResetRxComplete_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ResetRxComplete_contents_Route(var) (&var)

/* Access member 'Reserved' of type 'c_EMFPKA_RLP_INUSE_ResetRxComplete_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ResetRxComplete_contents_Reserved(var) var

/* Access member 'Reserved' of type 'c_EMFPKA_RLP_INUSE_ResetRxComplete_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ResetRxComplete_contents_Reserved(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_ResetRxComplete_contents {

	ED_OCTET LinkFlowNumber; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Route; /* ODY01a *//*GBD01b*/
	ED_OCTET Reserved; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_ResetRxComplete_contents;
#define INIT_c_EMFPKA_RLP_INUSE_ResetRxComplete_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_ResetRxComplete_contents))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_ResetRxComplete_contents(c_EMFPKA_RLP_INUSE_ResetRxComplete_contents* sp);

/* Access member 'LinkFlowNumber' of type 'c_EMFPKA_RLP_INUSE_Nak_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_Nak_contents_LinkFlowNumber(var) var

/* Access member 'LinkFlowNumber' of type 'c_EMFPKA_RLP_INUSE_Nak_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_Nak_contents_LinkFlowNumber(var) (&var)

/* Access member 'Route' of type 'c_EMFPKA_RLP_INUSE_Nak_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_Nak_contents_Route(var) var

/* Access member 'Route' of type 'c_EMFPKA_RLP_INUSE_Nak_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_Nak_contents_Route(var) (&var)

/* Access member 'Reserved1' of type 'c_EMFPKA_RLP_INUSE_Nak_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_Nak_contents_Reserved1(var) var

/* Access member 'Reserved1' of type 'c_EMFPKA_RLP_INUSE_Nak_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_Nak_contents_Reserved1(var) (&var)

/* Access member 'SequenceLength' of type 'c_EMFPKA_RLP_INUSE_Nak_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_Nak_contents_SequenceLength(var) var

/* Access member 'SequenceLength' of type 'c_EMFPKA_RLP_INUSE_Nak_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_Nak_contents_SequenceLength(var) (&var)

/* Access member 'ReportCount' of type 'c_EMFPKA_RLP_INUSE_Nak_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_Nak_contents_ReportCount(var) var

/* Access member 'ReportCount' of type 'c_EMFPKA_RLP_INUSE_Nak_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_Nak_contents_ReportCount(var) (&var)

/* Access member 'FirstErasedDataUnit' of type 'c_EMFPKA_RLP_INUSE_Nak_contents_data01_data' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_Nak_contents_data01_data_FirstErasedDataUnit(var) var

/* Access member 'FirstErasedDataUnit' of type 'c_EMFPKA_RLP_INUSE_Nak_contents_data01_data' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_Nak_contents_data01_data_FirstErasedDataUnit(var) (&var)

/* Access member 'WindowLen' of type 'c_EMFPKA_RLP_INUSE_Nak_contents_data01_data' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_Nak_contents_data01_data_WindowLen(var) var

/* Access member 'WindowLen' of type 'c_EMFPKA_RLP_INUSE_Nak_contents_data01_data' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_Nak_contents_data01_data_WindowLen(var) (&var)

/* Access member 'VR' of type 'c_EMFPKA_RLP_INUSE_Nak_contents_data01_data' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_Nak_contents_data01_data_VR(var) var

/* Access member 'VR' of type 'c_EMFPKA_RLP_INUSE_Nak_contents_data01_data' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_Nak_contents_data01_data_VR(var) (&var)

/* Access member 'data' of type 'c_EMFPKA_RLP_INUSE_Nak_contents_data01' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_Nak_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_EMFPKA_RLP_INUSE_Nak_contents_data01' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_Nak_contents_data01_data(var) var

/* Access member 'data01' of type 'c_EMFPKA_RLP_INUSE_Nak_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_Nak_contents_data01(var) var

/* Access member 'data01' of type 'c_EMFPKA_RLP_INUSE_Nak_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_Nak_contents_data01(var) (&var)

/* DEFINITION OF BINARY c_EMFPKA_RLP_INUSE_Nak_contents_data01_data_FirstErasedDataUnit */
typedef struct _c_EMFPKA_RLP_INUSE_Nak_contents_data01_data_FirstErasedDataUnit {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_EMFPKA_RLP_INUSE_Nak_contents_data01_data_FirstErasedDataUnit;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_EMFPKA_RLP_INUSE_Nak_contents_data01_data_FirstErasedDataUnit(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF BINARY c_EMFPKA_RLP_INUSE_Nak_contents_data01_data_WindowLen */
typedef struct _c_EMFPKA_RLP_INUSE_Nak_contents_data01_data_WindowLen {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_EMFPKA_RLP_INUSE_Nak_contents_data01_data_WindowLen;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_EMFPKA_RLP_INUSE_Nak_contents_data01_data_WindowLen(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF BINARY c_EMFPKA_RLP_INUSE_Nak_contents_data01_data_VR */
typedef struct _c_EMFPKA_RLP_INUSE_Nak_contents_data01_data_VR {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_EMFPKA_RLP_INUSE_Nak_contents_data01_data_VR;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_EMFPKA_RLP_INUSE_Nak_contents_data01_data_VR(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF SUB-STRUCTURE c_EMFPKA_RLP_INUSE_Nak_contents_data01_data */
typedef struct _c_EMFPKA_RLP_INUSE_Nak_contents_data01_data {

	c_EMFPKA_RLP_INUSE_Nak_contents_data01_data_FirstErasedDataUnit FirstErasedDataUnit; /* Static, variable size; bits needed 64 *//*GBD01b*/
	c_EMFPKA_RLP_INUSE_Nak_contents_data01_data_WindowLen WindowLen; /* Static, variable size; bits needed 64 *//*GBD01b*/
	c_EMFPKA_RLP_INUSE_Nak_contents_data01_data_VR VR; /* Static, variable size; bits needed 64 *//*GBD01b*/

} c_EMFPKA_RLP_INUSE_Nak_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_EMFPKA_RLP_INUSE_Nak_contents_data01 */
typedef struct _c_EMFPKA_RLP_INUSE_Nak_contents_data01 {

	c_EMFPKA_RLP_INUSE_Nak_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_EMFPKA_RLP_INUSE_Nak_contents_data01;


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_Nak_contents {

	ED_OCTET LinkFlowNumber; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Route; /* ODY01a *//*GBD01b*/
	ED_OCTET Reserved1; /* ODY01a *//*GBD01b*/
	ED_OCTET SequenceLength; /* ODY01a *//*GBD01b*/
	ED_OCTET ReportCount; /* ODY01a *//*GBD01b*/
	c_EMFPKA_RLP_INUSE_Nak_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_Nak_contents;
#define INIT_c_EMFPKA_RLP_INUSE_Nak_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_Nak_contents))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_Nak_contents(c_EMFPKA_RLP_INUSE_Nak_contents* sp);

/* Access member 'TransactionID' of type 'c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_TransactionID(var) (&var)

/* Access member 'ReservationCount' of type 'c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_ReservationCount(var) var

/* Access member 'ReservationCount' of type 'c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_ReservationCount(var) (&var)

/* Access member 'Link' of type 'c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data_Link(var) var

/* Access member 'Link' of type 'c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data_Link(var) (&var)

/* Access member 'ReservationLabel' of type 'c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data_ReservationLabel(var) var

/* Access member 'ReservationLabel' of type 'c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data_ReservationLabel(var) (&var)

/* Access member 'EmergencyIndication' of type 'c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data_EmergencyIndication(var) var

/* Access member 'EmergencyIndication' of type 'c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data_EmergencyIndication(var) (&var)

/* Access member 'ReservationQueuingReq' of type 'c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data_ReservationQueuingReq(var) var

/* Access member 'ReservationQueuingReq' of type 'c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data_ReservationQueuingReq(var) (&var)

/* Access member 'data' of type 'c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data(var) var

/* Access member 'data01' of type 'c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01(var) var

/* Access member 'data01' of type 'c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data */
typedef struct _c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data {

	ED_BOOLEAN Link; /* ODY01a *//*GBD01b*/
	ED_OCTET ReservationLabel; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN EmergencyIndication; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN EmergencyIndication_Present;
	ED_BOOLEAN ReservationQueuingReq; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ReservationQueuingReq_Present;

} c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01 */
typedef struct _c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01 {

	c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01;


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	ED_OCTET ReservationCount; /* ODY01a *//*GBD01b*/
	c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents;
#define INIT_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents(c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents* sp);

/* Access member 'TransactionID' of type 'c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_TransactionID(var) (&var)

/* Access member 'ReservationCount' of type 'c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_ReservationCount(var) var

/* Access member 'ReservationCount' of type 'c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_ReservationCount(var) (&var)

/* Access member 'Link' of type 'c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01_data' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01_data_Link(var) var

/* Access member 'Link' of type 'c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01_data' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01_data_Link(var) (&var)

/* Access member 'ReservationLabel' of type 'c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01_data' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01_data_ReservationLabel(var) var

/* Access member 'ReservationLabel' of type 'c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01_data' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01_data_ReservationLabel(var) (&var)

/* Access member 'data' of type 'c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01_data(var) var

/* Access member 'data01' of type 'c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01(var) var

/* Access member 'data01' of type 'c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01_data */
typedef struct _c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01_data {

	ED_BOOLEAN Link; /* ODY01a *//*GBD01b*/
	ED_OCTET ReservationLabel; /* ODY01a *//*GBD01b*/

} c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01 */
typedef struct _c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01 {

	c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01;


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	ED_OCTET ReservationCount; /* ODY01a *//*GBD01b*/
	c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents;
#define INIT_c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents(c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents* sp);

/* Access member 'TransactionID' of type 'c_EMFPKA_RLP_INUSE_ReservationAccept_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ReservationAccept_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_EMFPKA_RLP_INUSE_ReservationAccept_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ReservationAccept_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_ReservationAccept_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_ReservationAccept_contents;
#define INIT_c_EMFPKA_RLP_INUSE_ReservationAccept_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_ReservationAccept_contents))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_ReservationAccept_contents(c_EMFPKA_RLP_INUSE_ReservationAccept_contents* sp);

/* Access member 'TransactionID' of type 'c_EMFPKA_RLP_INUSE_ReservationReject_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ReservationReject_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_EMFPKA_RLP_INUSE_ReservationReject_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ReservationReject_contents_TransactionID(var) (&var)

/* Access member 'ReservationCount' of type 'c_EMFPKA_RLP_INUSE_ReservationReject_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ReservationReject_contents_ReservationCount(var) var

/* Access member 'ReservationCount' of type 'c_EMFPKA_RLP_INUSE_ReservationReject_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ReservationReject_contents_ReservationCount(var) (&var)

/* Access member 'AllowableLink' of type 'c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_AllowableLink(var) var

/* Access member 'AllowableLink' of type 'c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_AllowableLink(var) (&var)

/* Access member 'AllowableReservationLabel' of type 'c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_AllowableReservationLabel(var) var

/* Access member 'AllowableReservationLabel' of type 'c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_AllowableReservationLabel(var) (&var)

/* Access member 'RejectCode' of type 'c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02_data' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02_data_RejectCode(var) var

/* Access member 'RejectCode' of type 'c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02_data' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02_data_RejectCode(var) (&var)

/* Access member 'PendingDuration' of type 'c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02_data' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02_data_PendingDuration(var) var

/* Access member 'PendingDuration' of type 'c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02_data' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02_data_PendingDuration(var) (&var)

/* Access member 'data' of type 'c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02_data(var) (*var)

/* Access member 'data' of type 'c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02_data(var) var

/* Access member 'data02' of type 'c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02(var) var

/* Access member 'data02' of type 'c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02(var) (&var)

/* Access member 'data' of type 'c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data(var) var

/* Access member 'data01' of type 'c_EMFPKA_RLP_INUSE_ReservationReject_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01(var) var

/* Access member 'data01' of type 'c_EMFPKA_RLP_INUSE_ReservationReject_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02_data */
typedef struct _c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02_data {

	ED_OCTET RejectCode; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN RejectCode_Present;
	ED_OCTET PendingDuration; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PendingDuration_Present;

} c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02_data;

/* DEFINITION OF SUB-STRUCTURE c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02 */
typedef struct _c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02 {

	c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02;

/* DEFINITION OF SUB-STRUCTURE c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data */
typedef struct _c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data {

	ED_BOOLEAN AllowableLink; /* ODY01a *//*GBD01b*/
	ED_OCTET AllowableReservationLabel; /* ODY01a *//*GBD01b*/
	c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02 data02;/*GFB09*//*GBD01b*/

} c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01 */
typedef struct _c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01 {

	c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01;


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_ReservationReject_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	ED_OCTET ReservationCount; /* ODY01a *//*GBD01b*/
	c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_ReservationReject_contents;
#define INIT_c_EMFPKA_RLP_INUSE_ReservationReject_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_ReservationReject_contents))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_ReservationReject_contents(c_EMFPKA_RLP_INUSE_ReservationReject_contents* sp);

/* Access member 'TransactionID' of type 'c_EMFPKA_RLP_INUSE_RevReservationOn_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_RevReservationOn_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_EMFPKA_RLP_INUSE_RevReservationOn_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_RevReservationOn_contents_TransactionID(var) (&var)

/* Access member 'ReservationCount' of type 'c_EMFPKA_RLP_INUSE_RevReservationOn_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_RevReservationOn_contents_ReservationCount(var) var

/* Access member 'ReservationCount' of type 'c_EMFPKA_RLP_INUSE_RevReservationOn_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_RevReservationOn_contents_ReservationCount(var) (&var)

/* Access member 'ReservationLabel' of type 'c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01_data' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01_data_ReservationLabel(var) var

/* Access member 'ReservationLabel' of type 'c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01_data' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01_data_ReservationLabel(var) (&var)

/* Access member 'data' of type 'c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01_data(var) var

/* Access member 'data01' of type 'c_EMFPKA_RLP_INUSE_RevReservationOn_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01(var) var

/* Access member 'data01' of type 'c_EMFPKA_RLP_INUSE_RevReservationOn_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01_data */
typedef struct _c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01_data {

	ED_OCTET ReservationLabel; /* ODY01a *//*GBD01b*/

} c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01 */
typedef struct _c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01 {

	c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01;


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_RevReservationOn_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	ED_OCTET ReservationCount; /* ODY01a *//*GBD01b*/
	c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_RevReservationOn_contents;
#define INIT_c_EMFPKA_RLP_INUSE_RevReservationOn_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_RevReservationOn_contents))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_RevReservationOn_contents(c_EMFPKA_RLP_INUSE_RevReservationOn_contents* sp);

/* Access member 'TransactionID' of type 'c_EMFPKA_RLP_INUSE_RevReservationOff_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_RevReservationOff_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_EMFPKA_RLP_INUSE_RevReservationOff_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_RevReservationOff_contents_TransactionID(var) (&var)

/* Access member 'ReservationCount' of type 'c_EMFPKA_RLP_INUSE_RevReservationOff_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_RevReservationOff_contents_ReservationCount(var) var

/* Access member 'ReservationCount' of type 'c_EMFPKA_RLP_INUSE_RevReservationOff_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_RevReservationOff_contents_ReservationCount(var) (&var)

/* Access member 'ReservationLabel' of type 'c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01_data' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01_data_ReservationLabel(var) var

/* Access member 'ReservationLabel' of type 'c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01_data' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01_data_ReservationLabel(var) (&var)

/* Access member 'data' of type 'c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01_data(var) var

/* Access member 'data01' of type 'c_EMFPKA_RLP_INUSE_RevReservationOff_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01(var) var

/* Access member 'data01' of type 'c_EMFPKA_RLP_INUSE_RevReservationOff_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01_data */
typedef struct _c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01_data {

	ED_OCTET ReservationLabel; /* ODY01a *//*GBD01b*/

} c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01 */
typedef struct _c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01 {

	c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01;


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_RevReservationOff_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	ED_OCTET ReservationCount; /* ODY01a *//*GBD01b*/
	c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_RevReservationOff_contents;
#define INIT_c_EMFPKA_RLP_INUSE_RevReservationOff_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_RevReservationOff_contents))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_RevReservationOff_contents(c_EMFPKA_RLP_INUSE_RevReservationOff_contents* sp);

/* Access member 'TransactionID' of type 'c_EMFPKA_RLP_INUSE_FwdReservationOff_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_EMFPKA_RLP_INUSE_FwdReservationOff_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_TransactionID(var) (&var)

/* Access member 'ReservationCount' of type 'c_EMFPKA_RLP_INUSE_FwdReservationOff_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_ReservationCount(var) var

/* Access member 'ReservationCount' of type 'c_EMFPKA_RLP_INUSE_FwdReservationOff_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_ReservationCount(var) (&var)

/* Access member 'ReservationLabel' of type 'c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01_data' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01_data_ReservationLabel(var) var

/* Access member 'ReservationLabel' of type 'c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01_data' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01_data_ReservationLabel(var) (&var)

/* Access member 'data' of type 'c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01_data(var) var

/* Access member 'data01' of type 'c_EMFPKA_RLP_INUSE_FwdReservationOff_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01(var) var

/* Access member 'data01' of type 'c_EMFPKA_RLP_INUSE_FwdReservationOff_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01_data */
typedef struct _c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01_data {

	ED_OCTET ReservationLabel; /* ODY01a *//*GBD01b*/

} c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01 */
typedef struct _c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01 {

	c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01;


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_FwdReservationOff_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	ED_OCTET ReservationCount; /* ODY01a *//*GBD01b*/
	c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_FwdReservationOff_contents;
#define INIT_c_EMFPKA_RLP_INUSE_FwdReservationOff_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_FwdReservationOff_contents))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_FwdReservationOff_contents(c_EMFPKA_RLP_INUSE_FwdReservationOff_contents* sp);

/* Access member 'TransactionID' of type 'c_EMFPKA_RLP_INUSE_FwdReservationOn_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_EMFPKA_RLP_INUSE_FwdReservationOn_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_TransactionID(var) (&var)

/* Access member 'ReservationCount' of type 'c_EMFPKA_RLP_INUSE_FwdReservationOn_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_ReservationCount(var) var

/* Access member 'ReservationCount' of type 'c_EMFPKA_RLP_INUSE_FwdReservationOn_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_ReservationCount(var) (&var)

/* Access member 'ReservationLabel' of type 'c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01_data' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01_data_ReservationLabel(var) var

/* Access member 'ReservationLabel' of type 'c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01_data' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01_data_ReservationLabel(var) (&var)

/* Access member 'data' of type 'c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01_data(var) var

/* Access member 'data01' of type 'c_EMFPKA_RLP_INUSE_FwdReservationOn_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01(var) var

/* Access member 'data01' of type 'c_EMFPKA_RLP_INUSE_FwdReservationOn_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01_data */
typedef struct _c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01_data {

	ED_OCTET ReservationLabel; /* ODY01a *//*GBD01b*/

} c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01 */
typedef struct _c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01 {

	c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01;


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_FwdReservationOn_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	ED_OCTET ReservationCount; /* ODY01a *//*GBD01b*/
	c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_FwdReservationOn_contents;
#define INIT_c_EMFPKA_RLP_INUSE_FwdReservationOn_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_FwdReservationOn_contents))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_FwdReservationOn_contents(c_EMFPKA_RLP_INUSE_FwdReservationOn_contents* sp);

/* Access member 'TransactionID' of type 'c_EMFPKA_RLP_INUSE_FwdReservationAck_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_FwdReservationAck_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_EMFPKA_RLP_INUSE_FwdReservationAck_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_FwdReservationAck_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_FwdReservationAck_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_FwdReservationAck_contents;
#define INIT_c_EMFPKA_RLP_INUSE_FwdReservationAck_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_FwdReservationAck_contents))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_FwdReservationAck_contents(c_EMFPKA_RLP_INUSE_FwdReservationAck_contents* sp);

/* Access member 'TransactionID' of type 'c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_TransactionID(var) (&var)

/* Access member 'AttributeLength' of type 'c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01_data' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01_data_AttributeLength(var) var

/* Access member 'AttributeLength' of type 'c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01_data' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01_data_AttributeLength(var) (&var)

/* Access member 'AttributeRecord' of type 'c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01_data' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01_data_AttributeRecord(var) var

/* Access member 'AttributeRecord' of type 'c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01_data' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01_data_AttributeRecord(var) (&var)

/* Access member 'data' of type 'c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01_data(var) var

/* Access member 'data01' of type 'c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01(var) var

/* Access member 'data01' of type 'c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01_data */
typedef struct _c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01_data {

	ED_OCTET AttributeLength; /* ODY01a *//*GBD01b*/
	c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes AttributeRecord; /* ODY01a *//*GBD01b*/

} c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01 */
typedef struct _c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01 {

	c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01;


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents;
#define INIT_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents(c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents* sp);

/* Access member 'TransactionID' of type 'c_EMFPKA_RLP_INUSE_AttributeUpdateAccept_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_AttributeUpdateAccept_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_EMFPKA_RLP_INUSE_AttributeUpdateAccept_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_AttributeUpdateAccept_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_AttributeUpdateAccept_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_AttributeUpdateAccept_contents;
#define INIT_c_EMFPKA_RLP_INUSE_AttributeUpdateAccept_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_AttributeUpdateAccept_contents))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_AttributeUpdateAccept_contents(c_EMFPKA_RLP_INUSE_AttributeUpdateAccept_contents* sp);

/* Access member 'TransactionID' of type 'c_EMFPKA_RLP_INUSE_AttributeUpdateReject_contents' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_AttributeUpdateReject_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_EMFPKA_RLP_INUSE_AttributeUpdateReject_contents' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_AttributeUpdateReject_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_AttributeUpdateReject_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_AttributeUpdateReject_contents;
#define INIT_c_EMFPKA_RLP_INUSE_AttributeUpdateReject_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_AttributeUpdateReject_contents))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_AttributeUpdateReject_contents(c_EMFPKA_RLP_INUSE_AttributeUpdateReject_contents* sp);

/* Access member 'LinkFlowNumber' of type 'c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents' as a variable reference */
#define VAR_c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_LinkFlowNumber(var) var

/* Access member 'LinkFlowNumber' of type 'c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents' as a pointer */
#define PTR_c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_LinkFlowNumber(var) (&var)

/* Access member 'Route' of type 'c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents' as a variable reference */
#define VAR_c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_Route(var) var

/* Access member 'Route' of type 'c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents' as a pointer */
#define PTR_c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_Route(var) (&var)

/* Access member 'AckRequired' of type 'c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents' as a variable reference */
#define VAR_c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_AckRequired(var) var

/* Access member 'AckRequired' of type 'c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents' as a pointer */
#define PTR_c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_AckRequired(var) (&var)

/* Access member 'Reset' of type 'c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents' as a variable reference */
#define VAR_c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_Reset(var) var

/* Access member 'Reset' of type 'c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents' as a pointer */
#define PTR_c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_Reset(var) (&var)

/* Access member 'Reserved' of type 'c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents' as a variable reference */
#define VAR_c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_Reserved(var) var

/* Access member 'Reserved' of type 'c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents' as a pointer */
#define PTR_c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_Reserved(var) (&var)

/* Access member 'MessageSequence' of type 'c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents' as a variable reference */
#define VAR_c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_MessageSequence(var) var

/* Access member 'MessageSequence' of type 'c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents' as a pointer */
#define PTR_c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_MessageSequence(var) (&var)

/* Access member 'HigherLayerPacket' of type 'c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents' as a variable reference */
#define VAR_c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_HigherLayerPacket(var) var

/* Access member 'HigherLayerPacket' of type 'c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents' as a pointer */
#define PTR_c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_HigherLayerPacket(var) (&var)

/* DEFINITION OF BINARY c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_HigherLayerPacket */
typedef struct _c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_HigherLayerPacket {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_HigherLayerPacket;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_HigherLayerPacket(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents {

	ED_OCTET LinkFlowNumber; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Route; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN AckRequired; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Reset; /* ODY01a *//*GBD01b*/
	ED_OCTET Reserved; /* ODY01a *//*GBD01b*/
	ED_OCTET MessageSequence; /* ODY01a *//*GBD01b*/
	c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents_HigherLayerPacket HigherLayerPacket; /* Static, variable size; bits needed 64 *//*GBD01b*/

}	c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents;
#define INIT_c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents))
/*FRK03a*/
void FREE_c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents(c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents* sp);

/* Access member 'Route' of type 'c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents' as a variable reference */
#define VAR_c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents_Route(var) var

/* Access member 'Route' of type 'c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents' as a pointer */
#define PTR_c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents_Route(var) (&var)

/* Access member 'AckSequence' of type 'c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents' as a variable reference */
#define VAR_c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents_AckSequence(var) var

/* Access member 'AckSequence' of type 'c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents' as a pointer */
#define PTR_c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents_AckSequence(var) (&var)

/* Access member 'Reserved' of type 'c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents' as a variable reference */
#define VAR_c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents_Reserved(var) var

/* Access member 'Reserved' of type 'c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents' as a pointer */
#define PTR_c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents_Reserved(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents {

	ED_BOOLEAN Route; /* ODY01a *//*GBD01b*/
	ED_OCTET AckSequence; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Reserved; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents;
#define INIT_c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents))
/*FRK03a*/
void FREE_c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents(c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents* sp);

/* Access member 'LocationType' of type 'c_EMFPKA_LUP_INUSE_LocationNotification_contents' as a variable reference */
#define VAR_c_EMFPKA_LUP_INUSE_LocationNotification_contents_LocationType(var) var

/* Access member 'LocationType' of type 'c_EMFPKA_LUP_INUSE_LocationNotification_contents' as a pointer */
#define PTR_c_EMFPKA_LUP_INUSE_LocationNotification_contents_LocationType(var) (&var)

/* Access member 'LocationLength' of type 'c_EMFPKA_LUP_INUSE_LocationNotification_contents' as a variable reference */
#define VAR_c_EMFPKA_LUP_INUSE_LocationNotification_contents_LocationLength(var) var

/* Access member 'LocationLength' of type 'c_EMFPKA_LUP_INUSE_LocationNotification_contents' as a pointer */
#define PTR_c_EMFPKA_LUP_INUSE_LocationNotification_contents_LocationLength(var) (&var)

/* Access member 'LocationValue' of type 'c_EMFPKA_LUP_INUSE_LocationNotification_contents' as a variable reference */
#define VAR_c_EMFPKA_LUP_INUSE_LocationNotification_contents_LocationValue(var) var

/* Access member 'LocationValue' of type 'c_EMFPKA_LUP_INUSE_LocationNotification_contents' as a pointer */
#define PTR_c_EMFPKA_LUP_INUSE_LocationNotification_contents_LocationValue(var) (&var)

/* DEFINITION OF BINARY c_EMFPKA_LUP_INUSE_LocationNotification_contents_LocationValue */
typedef struct _c_EMFPKA_LUP_INUSE_LocationNotification_contents_LocationValue {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_EMFPKA_LUP_INUSE_LocationNotification_contents_LocationValue;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_EMFPKA_LUP_INUSE_LocationNotification_contents_LocationValue(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_EMFPKA_LUP_INUSE_LocationNotification_contents {

	ED_OCTET LocationType; /* ODY01a *//*GBD01b*/
	ED_OCTET LocationLength; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN LocationLength_Present;
	c_EMFPKA_LUP_INUSE_LocationNotification_contents_LocationValue LocationValue; /* Static, variable size; bits needed 64 *//*GBD01b*/

}	c_EMFPKA_LUP_INUSE_LocationNotification_contents;
#define INIT_c_EMFPKA_LUP_INUSE_LocationNotification_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_LUP_INUSE_LocationNotification_contents))
/*FRK03a*/
void FREE_c_EMFPKA_LUP_INUSE_LocationNotification_contents(c_EMFPKA_LUP_INUSE_LocationNotification_contents* sp);
#define SETPRESENT_c_EMFPKA_LUP_INUSE_LocationNotification_contents_LocationLength(sp,present) ((sp)->LocationLength_Present = present)
#define GETPRESENT_c_EMFPKA_LUP_INUSE_LocationNotification_contents_LocationLength(sp) ((sp)->LocationLength_Present)

/* Access member 'TransactionID' of type 'c_EMFPKA_LUP_INUSE_LocationAssignment_contents' as a variable reference */
#define VAR_c_EMFPKA_LUP_INUSE_LocationAssignment_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_EMFPKA_LUP_INUSE_LocationAssignment_contents' as a pointer */
#define PTR_c_EMFPKA_LUP_INUSE_LocationAssignment_contents_TransactionID(var) (&var)

/* Access member 'LocationType' of type 'c_EMFPKA_LUP_INUSE_LocationAssignment_contents' as a variable reference */
#define VAR_c_EMFPKA_LUP_INUSE_LocationAssignment_contents_LocationType(var) var

/* Access member 'LocationType' of type 'c_EMFPKA_LUP_INUSE_LocationAssignment_contents' as a pointer */
#define PTR_c_EMFPKA_LUP_INUSE_LocationAssignment_contents_LocationType(var) (&var)

/* Access member 'LocationLength' of type 'c_EMFPKA_LUP_INUSE_LocationAssignment_contents' as a variable reference */
#define VAR_c_EMFPKA_LUP_INUSE_LocationAssignment_contents_LocationLength(var) var

/* Access member 'LocationLength' of type 'c_EMFPKA_LUP_INUSE_LocationAssignment_contents' as a pointer */
#define PTR_c_EMFPKA_LUP_INUSE_LocationAssignment_contents_LocationLength(var) (&var)

/* Access member 'LocationValue' of type 'c_EMFPKA_LUP_INUSE_LocationAssignment_contents' as a variable reference */
#define VAR_c_EMFPKA_LUP_INUSE_LocationAssignment_contents_LocationValue(var) var

/* Access member 'LocationValue' of type 'c_EMFPKA_LUP_INUSE_LocationAssignment_contents' as a pointer */
#define PTR_c_EMFPKA_LUP_INUSE_LocationAssignment_contents_LocationValue(var) (&var)

/* DEFINITION OF BINARY c_EMFPKA_LUP_INUSE_LocationAssignment_contents_LocationValue */
typedef struct _c_EMFPKA_LUP_INUSE_LocationAssignment_contents_LocationValue {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_EMFPKA_LUP_INUSE_LocationAssignment_contents_LocationValue;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_EMFPKA_LUP_INUSE_LocationAssignment_contents_LocationValue(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_EMFPKA_LUP_INUSE_LocationAssignment_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	ED_OCTET LocationType; /* ODY01a *//*GBD01b*/
	ED_OCTET LocationLength; /* ODY01a *//*GBD01b*/
	c_EMFPKA_LUP_INUSE_LocationAssignment_contents_LocationValue LocationValue; /* Static, variable size; bits needed 64 *//*GBD01b*/

}	c_EMFPKA_LUP_INUSE_LocationAssignment_contents;
#define INIT_c_EMFPKA_LUP_INUSE_LocationAssignment_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_LUP_INUSE_LocationAssignment_contents))
/*FRK03a*/
void FREE_c_EMFPKA_LUP_INUSE_LocationAssignment_contents(c_EMFPKA_LUP_INUSE_LocationAssignment_contents* sp);

/* Access member 'TransactionID' of type 'c_EMFPKA_LUP_INUSE_LocationComplete_contents' as a variable reference */
#define VAR_c_EMFPKA_LUP_INUSE_LocationComplete_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_EMFPKA_LUP_INUSE_LocationComplete_contents' as a pointer */
#define PTR_c_EMFPKA_LUP_INUSE_LocationComplete_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_LUP_INUSE_LocationComplete_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_LUP_INUSE_LocationComplete_contents;
#define INIT_c_EMFPKA_LUP_INUSE_LocationComplete_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_LUP_INUSE_LocationComplete_contents))
/*FRK03a*/
void FREE_c_EMFPKA_LUP_INUSE_LocationComplete_contents(c_EMFPKA_LUP_INUSE_LocationComplete_contents* sp);

/* Access member 'StorageBLOBType' of type 'c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents' as a variable reference */
#define VAR_c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOBType(var) var

/* Access member 'StorageBLOBType' of type 'c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents' as a pointer */
#define PTR_c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOBType(var) (&var)

/* Access member 'StorageBLOBLength' of type 'c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents' as a variable reference */
#define VAR_c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOBLength(var) var

/* Access member 'StorageBLOBLength' of type 'c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents' as a pointer */
#define PTR_c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOBLength(var) (&var)

/* Access member 'StorageBLOB' of type 'c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents' as a variable reference */
#define VAR_c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOB(var) var

/* Access member 'StorageBLOB' of type 'c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents' as a pointer */
#define PTR_c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOB(var) (&var)

/* DEFINITION OF BINARY c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOB */
typedef struct _c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOB {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOB;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOB(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents {

	ED_SHORT StorageBLOBType; /* ODY01a *//*GBD01b*/
	ED_OCTET StorageBLOBLength; /* ODY01a *//*GBD01b*/
	c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOB StorageBLOB; /* Static, variable size; bits needed 64 *//*GBD01b*/

}	c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents;
#define INIT_c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents))
/*FRK03a*/
void FREE_c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents(c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents* sp);

/* Access member 'TransactionID' of type 'c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents' as a variable reference */
#define VAR_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents' as a pointer */
#define PTR_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents_TransactionID(var) (&var)

/* Access member 'StorageBLOBType' of type 'c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents' as a variable reference */
#define VAR_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOBType(var) var

/* Access member 'StorageBLOBType' of type 'c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents' as a pointer */
#define PTR_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOBType(var) (&var)

/* Access member 'StorageBLOBLength' of type 'c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents' as a variable reference */
#define VAR_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOBLength(var) var

/* Access member 'StorageBLOBLength' of type 'c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents' as a pointer */
#define PTR_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOBLength(var) (&var)

/* Access member 'StorageBLOB' of type 'c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents' as a variable reference */
#define VAR_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOB(var) var

/* Access member 'StorageBLOB' of type 'c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents' as a pointer */
#define PTR_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOB(var) (&var)

/* DEFINITION OF BINARY c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOB */
typedef struct _c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOB {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOB;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOB(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	ED_SHORT StorageBLOBType; /* ODY01a *//*GBD01b*/
	ED_OCTET StorageBLOBLength; /* ODY01a *//*GBD01b*/
	c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOB StorageBLOB; /* Static, variable size; bits needed 64 *//*GBD01b*/

}	c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents;
#define INIT_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents))
/*FRK03a*/
void FREE_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents(c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents* sp);

/* Access member 'TransactionID' of type 'c_EMFPKA_LUP_INUSE_StorageBLOBComplete_contents' as a variable reference */
#define VAR_c_EMFPKA_LUP_INUSE_StorageBLOBComplete_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_EMFPKA_LUP_INUSE_StorageBLOBComplete_contents' as a pointer */
#define PTR_c_EMFPKA_LUP_INUSE_StorageBLOBComplete_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_LUP_INUSE_StorageBLOBComplete_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_LUP_INUSE_StorageBLOBComplete_contents;
#define INIT_c_EMFPKA_LUP_INUSE_StorageBLOBComplete_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_LUP_INUSE_StorageBLOBComplete_contents))
/*FRK03a*/
void FREE_c_EMFPKA_LUP_INUSE_StorageBLOBComplete_contents(c_EMFPKA_LUP_INUSE_StorageBLOBComplete_contents* sp);

/* Access member 'TransactionID' of type 'c_EMFPKA_FCP_INUSE_DataReady_contents' as a variable reference */
#define VAR_c_EMFPKA_FCP_INUSE_DataReady_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_EMFPKA_FCP_INUSE_DataReady_contents' as a pointer */
#define PTR_c_EMFPKA_FCP_INUSE_DataReady_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_FCP_INUSE_DataReady_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_FCP_INUSE_DataReady_contents;
#define INIT_c_EMFPKA_FCP_INUSE_DataReady_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_FCP_INUSE_DataReady_contents))
/*FRK03a*/
void FREE_c_EMFPKA_FCP_INUSE_DataReady_contents(c_EMFPKA_FCP_INUSE_DataReady_contents* sp);

/* Access member 'TransactionID' of type 'c_EMFPKA_FCP_INUSE_DataReadyAck_contents' as a variable reference */
#define VAR_c_EMFPKA_FCP_INUSE_DataReadyAck_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_EMFPKA_FCP_INUSE_DataReadyAck_contents' as a pointer */
#define PTR_c_EMFPKA_FCP_INUSE_DataReadyAck_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_FCP_INUSE_DataReadyAck_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_FCP_INUSE_DataReadyAck_contents;
#define INIT_c_EMFPKA_FCP_INUSE_DataReadyAck_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_FCP_INUSE_DataReadyAck_contents))
/*FRK03a*/
void FREE_c_EMFPKA_FCP_INUSE_DataReadyAck_contents(c_EMFPKA_FCP_INUSE_DataReadyAck_contents* sp);

/* Access member 'TransactionID' of type 'c_EMFPKA_FCP_INUSE_RestartNetworkInterface_contents' as a variable reference */
#define VAR_c_EMFPKA_FCP_INUSE_RestartNetworkInterface_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_EMFPKA_FCP_INUSE_RestartNetworkInterface_contents' as a pointer */
#define PTR_c_EMFPKA_FCP_INUSE_RestartNetworkInterface_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_FCP_INUSE_RestartNetworkInterface_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_FCP_INUSE_RestartNetworkInterface_contents;
#define INIT_c_EMFPKA_FCP_INUSE_RestartNetworkInterface_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_FCP_INUSE_RestartNetworkInterface_contents))
/*FRK03a*/
void FREE_c_EMFPKA_FCP_INUSE_RestartNetworkInterface_contents(c_EMFPKA_FCP_INUSE_RestartNetworkInterface_contents* sp);

/* Access member 'TransactionID' of type 'c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck_contents' as a variable reference */
#define VAR_c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck_contents' as a pointer */
#define PTR_c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck_contents;
#define INIT_c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck_contents(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck_contents))
/*FRK03a*/
void FREE_c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck_contents(c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck_contents* sp);

/* Access member 'TransactionID' of type 'c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents' as a variable reference */
#define VAR_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents' as a pointer */
#define PTR_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_TransactionID(var) (&var)

/* Access member 'AttributeLength' of type 'c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01_data' as a variable reference */
#define VAR_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01_data_AttributeLength(var) var

/* Access member 'AttributeLength' of type 'c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01_data' as a pointer */
#define PTR_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01_data_AttributeLength(var) (&var)

/* Access member 'AttributeRecord' of type 'c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01_data' as a variable reference */
#define VAR_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01_data_AttributeRecord(var) var

/* Access member 'AttributeRecord' of type 'c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01_data' as a pointer */
#define PTR_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01_data_AttributeRecord(var) (&var)

/* Access member 'data' of type 'c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01' as a variable reference */
#define VAR_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01' as a pointer */
#define PTR_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01_data(var) var

/* Access member 'data01' of type 'c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents' as a variable reference */
#define VAR_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01(var) var

/* Access member 'data01' of type 'c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents' as a pointer */
#define PTR_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01_data */
typedef struct _c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01_data {

	ED_OCTET AttributeLength; /* ODY01a *//*GBD01b*/
	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes AttributeRecord; /* ODY01a *//*GBD01b*/

} c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01 */
typedef struct _c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01 {

	c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01;


/*-A----------------------------------*/
typedef struct _c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents;
#define INIT_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents))
/*FRK03a*/
void FREE_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents(c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents* sp);

/* Access member 'TransactionID' of type 'c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents' as a variable reference */
#define VAR_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents' as a pointer */
#define PTR_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_TransactionID(var) (&var)

/* Access member 'AttributeLength' of type 'c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01_data' as a variable reference */
#define VAR_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01_data_AttributeLength(var) var

/* Access member 'AttributeLength' of type 'c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01_data' as a pointer */
#define PTR_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01_data_AttributeLength(var) (&var)

/* Access member 'AttributeRecord' of type 'c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01_data' as a variable reference */
#define VAR_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01_data_AttributeRecord(var) var

/* Access member 'AttributeRecord' of type 'c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01_data' as a pointer */
#define PTR_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01_data_AttributeRecord(var) (&var)

/* Access member 'data' of type 'c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01' as a variable reference */
#define VAR_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01' as a pointer */
#define PTR_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01_data(var) var

/* Access member 'data01' of type 'c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents' as a variable reference */
#define VAR_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01(var) var

/* Access member 'data01' of type 'c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents' as a pointer */
#define PTR_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01_data */
typedef struct _c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01_data {

	ED_OCTET AttributeLength; /* ODY01a *//*GBD01b*/
	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Response AttributeRecord; /* ODY01a *//*GBD01b*/

} c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01 */
typedef struct _c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01 {

	c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01;


/*-A----------------------------------*/
typedef struct _c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents;
#define INIT_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents))
/*FRK03a*/
void FREE_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents(c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents* sp);

/* Access member 'TransactionID' of type 'c_MLMFPA_RSP_INUSE_RouteSelect_contents' as a variable reference */
#define VAR_c_MLMFPA_RSP_INUSE_RouteSelect_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_MLMFPA_RSP_INUSE_RouteSelect_contents' as a pointer */
#define PTR_c_MLMFPA_RSP_INUSE_RouteSelect_contents_TransactionID(var) (&var)

/* Access member 'Route' of type 'c_MLMFPA_RSP_INUSE_RouteSelect_contents' as a variable reference */
#define VAR_c_MLMFPA_RSP_INUSE_RouteSelect_contents_Route(var) var

/* Access member 'Route' of type 'c_MLMFPA_RSP_INUSE_RouteSelect_contents' as a pointer */
#define PTR_c_MLMFPA_RSP_INUSE_RouteSelect_contents_Route(var) (&var)

/* Access member 'Reserved' of type 'c_MLMFPA_RSP_INUSE_RouteSelect_contents' as a variable reference */
#define VAR_c_MLMFPA_RSP_INUSE_RouteSelect_contents_Reserved(var) var

/* Access member 'Reserved' of type 'c_MLMFPA_RSP_INUSE_RouteSelect_contents' as a pointer */
#define PTR_c_MLMFPA_RSP_INUSE_RouteSelect_contents_Reserved(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_RSP_INUSE_RouteSelect_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Route; /* ODY01a *//*GBD01b*/
	ED_OCTET Reserved; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_RSP_INUSE_RouteSelect_contents;
#define INIT_c_MLMFPA_RSP_INUSE_RouteSelect_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_RSP_INUSE_RouteSelect_contents))
/*FRK03a*/
void FREE_c_MLMFPA_RSP_INUSE_RouteSelect_contents(c_MLMFPA_RSP_INUSE_RouteSelect_contents* sp);

/* Access member 'TransactionID' of type 'c_MLMFPA_RSP_INUSE_RouteSelectAck_contents' as a variable reference */
#define VAR_c_MLMFPA_RSP_INUSE_RouteSelectAck_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_MLMFPA_RSP_INUSE_RouteSelectAck_contents' as a pointer */
#define PTR_c_MLMFPA_RSP_INUSE_RouteSelectAck_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_RSP_INUSE_RouteSelectAck_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_RSP_INUSE_RouteSelectAck_contents;
#define INIT_c_MLMFPA_RSP_INUSE_RouteSelectAck_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_RSP_INUSE_RouteSelectAck_contents))
/*FRK03a*/
void FREE_c_MLMFPA_RSP_INUSE_RouteSelectAck_contents(c_MLMFPA_RSP_INUSE_RouteSelectAck_contents* sp);

/* Access member 'TransactionID' of type 'c_MLMFPA_RSP_INUSE_ActivateRoute_contents' as a variable reference */
#define VAR_c_MLMFPA_RSP_INUSE_ActivateRoute_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_MLMFPA_RSP_INUSE_ActivateRoute_contents' as a pointer */
#define PTR_c_MLMFPA_RSP_INUSE_ActivateRoute_contents_TransactionID(var) (&var)

/* Access member 'Route' of type 'c_MLMFPA_RSP_INUSE_ActivateRoute_contents' as a variable reference */
#define VAR_c_MLMFPA_RSP_INUSE_ActivateRoute_contents_Route(var) var

/* Access member 'Route' of type 'c_MLMFPA_RSP_INUSE_ActivateRoute_contents' as a pointer */
#define PTR_c_MLMFPA_RSP_INUSE_ActivateRoute_contents_Route(var) (&var)

/* Access member 'Reserved' of type 'c_MLMFPA_RSP_INUSE_ActivateRoute_contents' as a variable reference */
#define VAR_c_MLMFPA_RSP_INUSE_ActivateRoute_contents_Reserved(var) var

/* Access member 'Reserved' of type 'c_MLMFPA_RSP_INUSE_ActivateRoute_contents' as a pointer */
#define PTR_c_MLMFPA_RSP_INUSE_ActivateRoute_contents_Reserved(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_RSP_INUSE_ActivateRoute_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Route; /* ODY01a *//*GBD01b*/
	ED_OCTET Reserved; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_RSP_INUSE_ActivateRoute_contents;
#define INIT_c_MLMFPA_RSP_INUSE_ActivateRoute_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_RSP_INUSE_ActivateRoute_contents))
/*FRK03a*/
void FREE_c_MLMFPA_RSP_INUSE_ActivateRoute_contents(c_MLMFPA_RSP_INUSE_ActivateRoute_contents* sp);

/* Access member 'TransactionID' of type 'c_MLMFPA_RSP_INUSE_ActivateRouteAck_contents' as a variable reference */
#define VAR_c_MLMFPA_RSP_INUSE_ActivateRouteAck_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_MLMFPA_RSP_INUSE_ActivateRouteAck_contents' as a pointer */
#define PTR_c_MLMFPA_RSP_INUSE_ActivateRouteAck_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_RSP_INUSE_ActivateRouteAck_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_RSP_INUSE_ActivateRouteAck_contents;
#define INIT_c_MLMFPA_RSP_INUSE_ActivateRouteAck_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_RSP_INUSE_ActivateRouteAck_contents))
/*FRK03a*/
void FREE_c_MLMFPA_RSP_INUSE_ActivateRouteAck_contents(c_MLMFPA_RSP_INUSE_ActivateRouteAck_contents* sp);

/* Access member 'LinkFlowNumber' of type 'c_MLMFPA_SRP_INUSE_ResetTxIndication_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ResetTxIndication_contents_LinkFlowNumber(var) var

/* Access member 'LinkFlowNumber' of type 'c_MLMFPA_SRP_INUSE_ResetTxIndication_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ResetTxIndication_contents_LinkFlowNumber(var) (&var)

/* Access member 'Route' of type 'c_MLMFPA_SRP_INUSE_ResetTxIndication_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ResetTxIndication_contents_Route(var) var

/* Access member 'Route' of type 'c_MLMFPA_SRP_INUSE_ResetTxIndication_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ResetTxIndication_contents_Route(var) (&var)

/* Access member 'Reserved' of type 'c_MLMFPA_SRP_INUSE_ResetTxIndication_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ResetTxIndication_contents_Reserved(var) var

/* Access member 'Reserved' of type 'c_MLMFPA_SRP_INUSE_ResetTxIndication_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ResetTxIndication_contents_Reserved(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_ResetTxIndication_contents {

	ED_OCTET LinkFlowNumber; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Route; /* ODY01a *//*GBD01b*/
	ED_OCTET Reserved; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_ResetTxIndication_contents;
#define INIT_c_MLMFPA_SRP_INUSE_ResetTxIndication_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_ResetTxIndication_contents))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_ResetTxIndication_contents(c_MLMFPA_SRP_INUSE_ResetTxIndication_contents* sp);

/* Access member 'LinkFlowNumber' of type 'c_MLMFPA_SRP_INUSE_ResetRxIndication_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ResetRxIndication_contents_LinkFlowNumber(var) var

/* Access member 'LinkFlowNumber' of type 'c_MLMFPA_SRP_INUSE_ResetRxIndication_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ResetRxIndication_contents_LinkFlowNumber(var) (&var)

/* Access member 'Route' of type 'c_MLMFPA_SRP_INUSE_ResetRxIndication_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ResetRxIndication_contents_Route(var) var

/* Access member 'Route' of type 'c_MLMFPA_SRP_INUSE_ResetRxIndication_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ResetRxIndication_contents_Route(var) (&var)

/* Access member 'Reserved' of type 'c_MLMFPA_SRP_INUSE_ResetRxIndication_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ResetRxIndication_contents_Reserved(var) var

/* Access member 'Reserved' of type 'c_MLMFPA_SRP_INUSE_ResetRxIndication_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ResetRxIndication_contents_Reserved(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_ResetRxIndication_contents {

	ED_OCTET LinkFlowNumber; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Route; /* ODY01a *//*GBD01b*/
	ED_OCTET Reserved; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_ResetRxIndication_contents;
#define INIT_c_MLMFPA_SRP_INUSE_ResetRxIndication_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_ResetRxIndication_contents))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_ResetRxIndication_contents(c_MLMFPA_SRP_INUSE_ResetRxIndication_contents* sp);

/* Access member 'LinkFlowNumber' of type 'c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents_LinkFlowNumber(var) var

/* Access member 'LinkFlowNumber' of type 'c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents_LinkFlowNumber(var) (&var)

/* Access member 'Route' of type 'c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents_Route(var) var

/* Access member 'Route' of type 'c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents_Route(var) (&var)

/* Access member 'Reserved' of type 'c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents_Reserved(var) var

/* Access member 'Reserved' of type 'c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents_Reserved(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents {

	ED_OCTET LinkFlowNumber; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Route; /* ODY01a *//*GBD01b*/
	ED_OCTET Reserved; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents;
#define INIT_c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents(c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents* sp);

/* Access member 'LinkFlowNumber' of type 'c_MLMFPA_SRP_INUSE_ResetTxComplete_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ResetTxComplete_contents_LinkFlowNumber(var) var

/* Access member 'LinkFlowNumber' of type 'c_MLMFPA_SRP_INUSE_ResetTxComplete_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ResetTxComplete_contents_LinkFlowNumber(var) (&var)

/* Access member 'Route' of type 'c_MLMFPA_SRP_INUSE_ResetTxComplete_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ResetTxComplete_contents_Route(var) var

/* Access member 'Route' of type 'c_MLMFPA_SRP_INUSE_ResetTxComplete_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ResetTxComplete_contents_Route(var) (&var)

/* Access member 'Reserved' of type 'c_MLMFPA_SRP_INUSE_ResetTxComplete_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ResetTxComplete_contents_Reserved(var) var

/* Access member 'Reserved' of type 'c_MLMFPA_SRP_INUSE_ResetTxComplete_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ResetTxComplete_contents_Reserved(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_ResetTxComplete_contents {

	ED_OCTET LinkFlowNumber; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Route; /* ODY01a *//*GBD01b*/
	ED_OCTET Reserved; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_ResetTxComplete_contents;
#define INIT_c_MLMFPA_SRP_INUSE_ResetTxComplete_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_ResetTxComplete_contents))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_ResetTxComplete_contents(c_MLMFPA_SRP_INUSE_ResetTxComplete_contents* sp);

/* Access member 'LinkFlowNumber' of type 'c_MLMFPA_SRP_INUSE_ResetRxComplete_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ResetRxComplete_contents_LinkFlowNumber(var) var

/* Access member 'LinkFlowNumber' of type 'c_MLMFPA_SRP_INUSE_ResetRxComplete_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ResetRxComplete_contents_LinkFlowNumber(var) (&var)

/* Access member 'Route' of type 'c_MLMFPA_SRP_INUSE_ResetRxComplete_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ResetRxComplete_contents_Route(var) var

/* Access member 'Route' of type 'c_MLMFPA_SRP_INUSE_ResetRxComplete_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ResetRxComplete_contents_Route(var) (&var)

/* Access member 'Reserved' of type 'c_MLMFPA_SRP_INUSE_ResetRxComplete_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ResetRxComplete_contents_Reserved(var) var

/* Access member 'Reserved' of type 'c_MLMFPA_SRP_INUSE_ResetRxComplete_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ResetRxComplete_contents_Reserved(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_ResetRxComplete_contents {

	ED_OCTET LinkFlowNumber; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Route; /* ODY01a *//*GBD01b*/
	ED_OCTET Reserved; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_ResetRxComplete_contents;
#define INIT_c_MLMFPA_SRP_INUSE_ResetRxComplete_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_ResetRxComplete_contents))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_ResetRxComplete_contents(c_MLMFPA_SRP_INUSE_ResetRxComplete_contents* sp);

/* Access member 'LinkFlowNumber' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_LinkFlowNumber(var) var

/* Access member 'LinkFlowNumber' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_LinkFlowNumber(var) (&var)

/* Access member 'Route' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_Route(var) var

/* Access member 'Route' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_Route(var) (&var)

/* Access member 'Reserved1' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_Reserved1(var) var

/* Access member 'Reserved1' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_Reserved1(var) (&var)

/* Access member 'SARSequenceLength' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_SARSequenceLength(var) var

/* Access member 'SARSequenceLength' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_SARSequenceLength(var) (&var)

/* Access member 'ReportCount' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_ReportCount(var) var

/* Access member 'ReportCount' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_ReportCount(var) (&var)

/* Access member 'DelayedNak' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data_DelayedNak(var) var

/* Access member 'DelayedNak' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data_DelayedNak(var) (&var)

/* Access member 'LeadingEdgeIncluded' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data_LeadingEdgeIncluded(var) var

/* Access member 'LeadingEdgeIncluded' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data_LeadingEdgeIncluded(var) (&var)

/* Access member 'LeadingEdge' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data_LeadingEdge(var) (*var)

/* Access member 'LeadingEdge' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data_LeadingEdge(var) var

/* Access member 'TrailingEdge' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data_TrailingEdge(var) var

/* Access member 'TrailingEdge' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data_TrailingEdge(var) (&var)

/* Access member 'data' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data(var) var

/* Access member 'data01' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01(var) var

/* Access member 'data01' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01(var) (&var)

/* Access member 'OtherQNCount' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_OtherQNCount(var) var

/* Access member 'OtherQNCount' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_OtherQNCount(var) (&var)

/* Access member 'LargestSAR' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02_data' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02_data_LargestSAR(var) var

/* Access member 'LargestSAR' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02_data' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02_data_LargestSAR(var) (&var)

/* Access member 'data' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02_data(var) (*var)

/* Access member 'data' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02_data(var) var

/* Access member 'data02' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02(var) var

/* Access member 'data02' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02(var) (&var)

/* Access member 'VR' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_VR(var) var

/* Access member 'VR' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_VR(var) (&var)

/* DEFINITION OF BINARY c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data_LeadingEdge */
typedef struct _c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data_LeadingEdge {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data_LeadingEdge;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data_LeadingEdge(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF BINARY c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data_TrailingEdge */
typedef struct _c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data_TrailingEdge {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data_TrailingEdge;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data_TrailingEdge(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF SUB-STRUCTURE c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data */
typedef struct _c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data {

	ED_BOOLEAN DelayedNak; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN LeadingEdgeIncluded; /* ODY01a *//*GBD01b*/
	c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data_LeadingEdge* LeadingEdge; /* Dynamic, variable size; bits needed 64 ODY02b *//*GBD01b*/
	ED_BOOLEAN LeadingEdge_Present;
	c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data_TrailingEdge TrailingEdge; /* Static, variable size; bits needed 64 *//*GBD01b*/

} c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01 */
typedef struct _c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01 {

	c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01;

/* DEFINITION OF BINARY c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02_data_LargestSAR */
typedef struct _c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02_data_LargestSAR {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02_data_LargestSAR;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02_data_LargestSAR(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF SUB-STRUCTURE c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02_data */
typedef struct _c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02_data {

	c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02_data_LargestSAR LargestSAR; /* Static, variable size; bits needed 64 *//*GBD01b*/

} c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02_data;

/* DEFINITION OF SUB-STRUCTURE c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02 */
typedef struct _c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02 {

	c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02;

/* DEFINITION OF BINARY c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_VR */
typedef struct _c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_VR {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_VR;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_VR(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_MultiLinkNak_contents {

	ED_OCTET LinkFlowNumber; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Route; /* ODY01a *//*GBD01b*/
	ED_OCTET Reserved1; /* ODY01a *//*GBD01b*/
	ED_OCTET SARSequenceLength; /* ODY01a *//*GBD01b*/
	ED_OCTET ReportCount; /* ODY01a *//*GBD01b*/
	c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01 data01;/*GFB09*//*GBD01b*/
	ED_OCTET OtherQNCount; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN OtherQNCount_Present;
	c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02 data02;/*GFB09*//*GBD01b*/
	c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_VR VR; /* Static, variable size; bits needed 64 *//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_MultiLinkNak_contents;
#define INIT_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_MultiLinkNak_contents))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents(c_MLMFPA_SRP_INUSE_MultiLinkNak_contents* sp);
#define SETPRESENT_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_OtherQNCount(sp,present) ((sp)->OtherQNCount_Present = present)
#define GETPRESENT_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_OtherQNCount(sp) ((sp)->OtherQNCount_Present)

/* Access member 'TransactionID' of type 'c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_TransactionID(var) (&var)

/* Access member 'ReservationCount' of type 'c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_ReservationCount(var) var

/* Access member 'ReservationCount' of type 'c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_ReservationCount(var) (&var)

/* Access member 'Link' of type 'c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data_Link(var) var

/* Access member 'Link' of type 'c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data_Link(var) (&var)

/* Access member 'ReservationLabel' of type 'c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data_ReservationLabel(var) var

/* Access member 'ReservationLabel' of type 'c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data_ReservationLabel(var) (&var)

/* Access member 'EmergencyIndication' of type 'c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data_EmergencyIndication(var) var

/* Access member 'EmergencyIndication' of type 'c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data_EmergencyIndication(var) (&var)

/* Access member 'ReservationQueuingReq' of type 'c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data_ReservationQueuingReq(var) var

/* Access member 'ReservationQueuingReq' of type 'c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data_ReservationQueuingReq(var) (&var)

/* Access member 'data' of type 'c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data(var) var

/* Access member 'data01' of type 'c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01(var) var

/* Access member 'data01' of type 'c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data */
typedef struct _c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data {

	ED_BOOLEAN Link; /* ODY01a *//*GBD01b*/
	ED_OCTET ReservationLabel; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN EmergencyIndication; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN EmergencyIndication_Present;
	ED_BOOLEAN ReservationQueuingReq; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN ReservationQueuingReq_Present;

} c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01 */
typedef struct _c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01 {

	c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01;


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	ED_OCTET ReservationCount; /* ODY01a *//*GBD01b*/
	c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents;
#define INIT_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents(c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents* sp);

/* Access member 'TransactionID' of type 'c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_TransactionID(var) (&var)

/* Access member 'ReservationCount' of type 'c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_ReservationCount(var) var

/* Access member 'ReservationCount' of type 'c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_ReservationCount(var) (&var)

/* Access member 'Link' of type 'c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01_data' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01_data_Link(var) var

/* Access member 'Link' of type 'c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01_data' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01_data_Link(var) (&var)

/* Access member 'ReservationLabel' of type 'c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01_data' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01_data_ReservationLabel(var) var

/* Access member 'ReservationLabel' of type 'c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01_data' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01_data_ReservationLabel(var) (&var)

/* Access member 'data' of type 'c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01_data(var) var

/* Access member 'data01' of type 'c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01(var) var

/* Access member 'data01' of type 'c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01_data */
typedef struct _c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01_data {

	ED_BOOLEAN Link; /* ODY01a *//*GBD01b*/
	ED_OCTET ReservationLabel; /* ODY01a *//*GBD01b*/

} c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01 */
typedef struct _c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01 {

	c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01;


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	ED_OCTET ReservationCount; /* ODY01a *//*GBD01b*/
	c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents;
#define INIT_c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents(c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents* sp);

/* Access member 'TransactionID' of type 'c_MLMFPA_SRP_INUSE_ReservationAccept_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ReservationAccept_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_MLMFPA_SRP_INUSE_ReservationAccept_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ReservationAccept_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_ReservationAccept_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_ReservationAccept_contents;
#define INIT_c_MLMFPA_SRP_INUSE_ReservationAccept_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_ReservationAccept_contents))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_ReservationAccept_contents(c_MLMFPA_SRP_INUSE_ReservationAccept_contents* sp);

/* Access member 'TransactionID' of type 'c_MLMFPA_SRP_INUSE_ReservationReject_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ReservationReject_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_MLMFPA_SRP_INUSE_ReservationReject_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ReservationReject_contents_TransactionID(var) (&var)

/* Access member 'ReservationCount' of type 'c_MLMFPA_SRP_INUSE_ReservationReject_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ReservationReject_contents_ReservationCount(var) var

/* Access member 'ReservationCount' of type 'c_MLMFPA_SRP_INUSE_ReservationReject_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ReservationReject_contents_ReservationCount(var) (&var)

/* Access member 'AllowableLink' of type 'c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_AllowableLink(var) var

/* Access member 'AllowableLink' of type 'c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_AllowableLink(var) (&var)

/* Access member 'AllowableReservationLabel' of type 'c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_AllowableReservationLabel(var) var

/* Access member 'AllowableReservationLabel' of type 'c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_AllowableReservationLabel(var) (&var)

/* Access member 'RejectCode' of type 'c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02_data' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02_data_RejectCode(var) var

/* Access member 'RejectCode' of type 'c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02_data' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02_data_RejectCode(var) (&var)

/* Access member 'PendingDuration' of type 'c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02_data' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02_data_PendingDuration(var) var

/* Access member 'PendingDuration' of type 'c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02_data' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02_data_PendingDuration(var) (&var)

/* Access member 'data' of type 'c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02_data(var) (*var)

/* Access member 'data' of type 'c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02_data(var) var

/* Access member 'data02' of type 'c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02(var) var

/* Access member 'data02' of type 'c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02(var) (&var)

/* Access member 'data' of type 'c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data(var) var

/* Access member 'data01' of type 'c_MLMFPA_SRP_INUSE_ReservationReject_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01(var) var

/* Access member 'data01' of type 'c_MLMFPA_SRP_INUSE_ReservationReject_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02_data */
typedef struct _c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02_data {

	ED_OCTET RejectCode; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN RejectCode_Present;
	ED_OCTET PendingDuration; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN PendingDuration_Present;

} c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02_data;

/* DEFINITION OF SUB-STRUCTURE c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02 */
typedef struct _c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02 {

	c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02;

/* DEFINITION OF SUB-STRUCTURE c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data */
typedef struct _c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data {

	ED_BOOLEAN AllowableLink; /* ODY01a *//*GBD01b*/
	ED_OCTET AllowableReservationLabel; /* ODY01a *//*GBD01b*/
	c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02 data02;/*GFB09*//*GBD01b*/

} c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01 */
typedef struct _c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01 {

	c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01;


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_ReservationReject_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	ED_OCTET ReservationCount; /* ODY01a *//*GBD01b*/
	c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_ReservationReject_contents;
#define INIT_c_MLMFPA_SRP_INUSE_ReservationReject_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_ReservationReject_contents))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_ReservationReject_contents(c_MLMFPA_SRP_INUSE_ReservationReject_contents* sp);

/* Access member 'TransactionID' of type 'c_MLMFPA_SRP_INUSE_RevReservationOn_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_RevReservationOn_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_MLMFPA_SRP_INUSE_RevReservationOn_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_RevReservationOn_contents_TransactionID(var) (&var)

/* Access member 'ReservationCount' of type 'c_MLMFPA_SRP_INUSE_RevReservationOn_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_RevReservationOn_contents_ReservationCount(var) var

/* Access member 'ReservationCount' of type 'c_MLMFPA_SRP_INUSE_RevReservationOn_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_RevReservationOn_contents_ReservationCount(var) (&var)

/* Access member 'ReservationLabel' of type 'c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01_data' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01_data_ReservationLabel(var) var

/* Access member 'ReservationLabel' of type 'c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01_data' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01_data_ReservationLabel(var) (&var)

/* Access member 'data' of type 'c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01_data(var) var

/* Access member 'data01' of type 'c_MLMFPA_SRP_INUSE_RevReservationOn_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01(var) var

/* Access member 'data01' of type 'c_MLMFPA_SRP_INUSE_RevReservationOn_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01_data */
typedef struct _c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01_data {

	ED_OCTET ReservationLabel; /* ODY01a *//*GBD01b*/

} c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01 */
typedef struct _c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01 {

	c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01;


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_RevReservationOn_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	ED_OCTET ReservationCount; /* ODY01a *//*GBD01b*/
	c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_RevReservationOn_contents;
#define INIT_c_MLMFPA_SRP_INUSE_RevReservationOn_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_RevReservationOn_contents))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_RevReservationOn_contents(c_MLMFPA_SRP_INUSE_RevReservationOn_contents* sp);

/* Access member 'TransactionID' of type 'c_MLMFPA_SRP_INUSE_RevReservationOff_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_RevReservationOff_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_MLMFPA_SRP_INUSE_RevReservationOff_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_RevReservationOff_contents_TransactionID(var) (&var)

/* Access member 'ReservationCount' of type 'c_MLMFPA_SRP_INUSE_RevReservationOff_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_RevReservationOff_contents_ReservationCount(var) var

/* Access member 'ReservationCount' of type 'c_MLMFPA_SRP_INUSE_RevReservationOff_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_RevReservationOff_contents_ReservationCount(var) (&var)

/* Access member 'ReservationLabel' of type 'c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01_data' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01_data_ReservationLabel(var) var

/* Access member 'ReservationLabel' of type 'c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01_data' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01_data_ReservationLabel(var) (&var)

/* Access member 'data' of type 'c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01_data(var) var

/* Access member 'data01' of type 'c_MLMFPA_SRP_INUSE_RevReservationOff_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01(var) var

/* Access member 'data01' of type 'c_MLMFPA_SRP_INUSE_RevReservationOff_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01_data */
typedef struct _c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01_data {

	ED_OCTET ReservationLabel; /* ODY01a *//*GBD01b*/

} c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01 */
typedef struct _c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01 {

	c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01;


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_RevReservationOff_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	ED_OCTET ReservationCount; /* ODY01a *//*GBD01b*/
	c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_RevReservationOff_contents;
#define INIT_c_MLMFPA_SRP_INUSE_RevReservationOff_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_RevReservationOff_contents))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_RevReservationOff_contents(c_MLMFPA_SRP_INUSE_RevReservationOff_contents* sp);

/* Access member 'TransactionID' of type 'c_MLMFPA_SRP_INUSE_FwdReservationOff_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_MLMFPA_SRP_INUSE_FwdReservationOff_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_TransactionID(var) (&var)

/* Access member 'ReservationCount' of type 'c_MLMFPA_SRP_INUSE_FwdReservationOff_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_ReservationCount(var) var

/* Access member 'ReservationCount' of type 'c_MLMFPA_SRP_INUSE_FwdReservationOff_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_ReservationCount(var) (&var)

/* Access member 'ReservationLabel' of type 'c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01_data' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01_data_ReservationLabel(var) var

/* Access member 'ReservationLabel' of type 'c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01_data' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01_data_ReservationLabel(var) (&var)

/* Access member 'data' of type 'c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01_data(var) var

/* Access member 'data01' of type 'c_MLMFPA_SRP_INUSE_FwdReservationOff_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01(var) var

/* Access member 'data01' of type 'c_MLMFPA_SRP_INUSE_FwdReservationOff_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01_data */
typedef struct _c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01_data {

	ED_OCTET ReservationLabel; /* ODY01a *//*GBD01b*/

} c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01 */
typedef struct _c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01 {

	c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01;


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_FwdReservationOff_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	ED_OCTET ReservationCount; /* ODY01a *//*GBD01b*/
	c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_FwdReservationOff_contents;
#define INIT_c_MLMFPA_SRP_INUSE_FwdReservationOff_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_FwdReservationOff_contents))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_FwdReservationOff_contents(c_MLMFPA_SRP_INUSE_FwdReservationOff_contents* sp);

/* Access member 'TransactionID' of type 'c_MLMFPA_SRP_INUSE_FwdReservationOn_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_MLMFPA_SRP_INUSE_FwdReservationOn_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_TransactionID(var) (&var)

/* Access member 'ReservationCount' of type 'c_MLMFPA_SRP_INUSE_FwdReservationOn_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_ReservationCount(var) var

/* Access member 'ReservationCount' of type 'c_MLMFPA_SRP_INUSE_FwdReservationOn_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_ReservationCount(var) (&var)

/* Access member 'ReservationLabel' of type 'c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01_data' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01_data_ReservationLabel(var) var

/* Access member 'ReservationLabel' of type 'c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01_data' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01_data_ReservationLabel(var) (&var)

/* Access member 'data' of type 'c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01_data(var) var

/* Access member 'data01' of type 'c_MLMFPA_SRP_INUSE_FwdReservationOn_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01(var) var

/* Access member 'data01' of type 'c_MLMFPA_SRP_INUSE_FwdReservationOn_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01_data */
typedef struct _c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01_data {

	ED_OCTET ReservationLabel; /* ODY01a *//*GBD01b*/

} c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01 */
typedef struct _c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01 {

	c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01;


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_FwdReservationOn_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	ED_OCTET ReservationCount; /* ODY01a *//*GBD01b*/
	c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_FwdReservationOn_contents;
#define INIT_c_MLMFPA_SRP_INUSE_FwdReservationOn_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_FwdReservationOn_contents))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_FwdReservationOn_contents(c_MLMFPA_SRP_INUSE_FwdReservationOn_contents* sp);

/* Access member 'TransactionID' of type 'c_MLMFPA_SRP_INUSE_FwdReservationAck_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_FwdReservationAck_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_MLMFPA_SRP_INUSE_FwdReservationAck_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_FwdReservationAck_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_FwdReservationAck_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_FwdReservationAck_contents;
#define INIT_c_MLMFPA_SRP_INUSE_FwdReservationAck_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_FwdReservationAck_contents))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_FwdReservationAck_contents(c_MLMFPA_SRP_INUSE_FwdReservationAck_contents* sp);

/* Access member 'TransactionID' of type 'c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_TransactionID(var) (&var)

/* Access member 'AttributeLength' of type 'c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01_data' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01_data_AttributeLength(var) var

/* Access member 'AttributeLength' of type 'c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01_data' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01_data_AttributeLength(var) (&var)

/* Access member 'AttributeRecord' of type 'c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01_data' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01_data_AttributeRecord(var) var

/* Access member 'AttributeRecord' of type 'c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01_data' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01_data_AttributeRecord(var) (&var)

/* Access member 'data' of type 'c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01_data(var) var

/* Access member 'data01' of type 'c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01(var) var

/* Access member 'data01' of type 'c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01(var) (&var)

/* DEFINITION OF SUB-STRUCTURE c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01_data */
typedef struct _c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01_data {

	ED_OCTET AttributeLength; /* ODY01a *//*GBD01b*/
	c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes AttributeRecord; /* ODY01a *//*GBD01b*/

} c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01 */
typedef struct _c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01 {

	c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01;


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents;
#define INIT_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents(c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents* sp);

/* Access member 'TransactionID' of type 'c_MLMFPA_SRP_INUSE_AttributeUpdateAccept_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_AttributeUpdateAccept_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_MLMFPA_SRP_INUSE_AttributeUpdateAccept_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_AttributeUpdateAccept_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_AttributeUpdateAccept_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_AttributeUpdateAccept_contents;
#define INIT_c_MLMFPA_SRP_INUSE_AttributeUpdateAccept_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_AttributeUpdateAccept_contents))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_AttributeUpdateAccept_contents(c_MLMFPA_SRP_INUSE_AttributeUpdateAccept_contents* sp);

/* Access member 'TransactionID' of type 'c_MLMFPA_SRP_INUSE_AttributeUpdateReject_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_AttributeUpdateReject_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_MLMFPA_SRP_INUSE_AttributeUpdateReject_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_AttributeUpdateReject_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_AttributeUpdateReject_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_AttributeUpdateReject_contents;
#define INIT_c_MLMFPA_SRP_INUSE_AttributeUpdateReject_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_AttributeUpdateReject_contents))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_AttributeUpdateReject_contents(c_MLMFPA_SRP_INUSE_AttributeUpdateReject_contents* sp);

/* Access member 'LinkFlowNumber' of type 'c_MLMFPA_SRP_INUSE_Flush_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_Flush_contents_LinkFlowNumber(var) var

/* Access member 'LinkFlowNumber' of type 'c_MLMFPA_SRP_INUSE_Flush_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_Flush_contents_LinkFlowNumber(var) (&var)

/* Access member 'Route' of type 'c_MLMFPA_SRP_INUSE_Flush_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_Flush_contents_Route(var) var

/* Access member 'Route' of type 'c_MLMFPA_SRP_INUSE_Flush_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_Flush_contents_Route(var) (&var)

/* Access member 'SARSequenceLength' of type 'c_MLMFPA_SRP_INUSE_Flush_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_Flush_contents_SARSequenceLength(var) var

/* Access member 'SARSequenceLength' of type 'c_MLMFPA_SRP_INUSE_Flush_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_Flush_contents_SARSequenceLength(var) (&var)

/* Access member 'LastSARSequence' of type 'c_MLMFPA_SRP_INUSE_Flush_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_Flush_contents_LastSARSequence(var) var

/* Access member 'LastSARSequence' of type 'c_MLMFPA_SRP_INUSE_Flush_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_Flush_contents_LastSARSequence(var) (&var)

/* DEFINITION OF BINARY c_MLMFPA_SRP_INUSE_Flush_contents_LastSARSequence */
typedef struct _c_MLMFPA_SRP_INUSE_Flush_contents_LastSARSequence {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_MLMFPA_SRP_INUSE_Flush_contents_LastSARSequence;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_MLMFPA_SRP_INUSE_Flush_contents_LastSARSequence(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_Flush_contents {

	ED_OCTET LinkFlowNumber; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Route; /* ODY01a *//*GBD01b*/
	ED_OCTET SARSequenceLength; /* ODY01a *//*GBD01b*/
	c_MLMFPA_SRP_INUSE_Flush_contents_LastSARSequence LastSARSequence; /* Static, variable size; bits needed 64 *//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_Flush_contents;
#define INIT_c_MLMFPA_SRP_INUSE_Flush_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_Flush_contents))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_Flush_contents(c_MLMFPA_SRP_INUSE_Flush_contents* sp);

/* Access member 'LinkFlowNumber' of type 'c_MLMFPA_SRP_INUSE_Nak_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_Nak_contents_LinkFlowNumber(var) var

/* Access member 'LinkFlowNumber' of type 'c_MLMFPA_SRP_INUSE_Nak_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_Nak_contents_LinkFlowNumber(var) (&var)

/* Access member 'Route' of type 'c_MLMFPA_SRP_INUSE_Nak_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_Nak_contents_Route(var) var

/* Access member 'Route' of type 'c_MLMFPA_SRP_INUSE_Nak_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_Nak_contents_Route(var) (&var)

/* Access member 'Reserved1' of type 'c_MLMFPA_SRP_INUSE_Nak_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_Nak_contents_Reserved1(var) var

/* Access member 'Reserved1' of type 'c_MLMFPA_SRP_INUSE_Nak_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_Nak_contents_Reserved1(var) (&var)

/* Access member 'SARSequenceLength' of type 'c_MLMFPA_SRP_INUSE_Nak_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_Nak_contents_SARSequenceLength(var) var

/* Access member 'SARSequenceLength' of type 'c_MLMFPA_SRP_INUSE_Nak_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_Nak_contents_SARSequenceLength(var) (&var)

/* Access member 'ReportCount' of type 'c_MLMFPA_SRP_INUSE_Nak_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_Nak_contents_ReportCount(var) var

/* Access member 'ReportCount' of type 'c_MLMFPA_SRP_INUSE_Nak_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_Nak_contents_ReportCount(var) (&var)

/* Access member 'FirstErasedDataUnit' of type 'c_MLMFPA_SRP_INUSE_Nak_contents_data01_data' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_Nak_contents_data01_data_FirstErasedDataUnit(var) var

/* Access member 'FirstErasedDataUnit' of type 'c_MLMFPA_SRP_INUSE_Nak_contents_data01_data' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_Nak_contents_data01_data_FirstErasedDataUnit(var) (&var)

/* Access member 'WindowLen' of type 'c_MLMFPA_SRP_INUSE_Nak_contents_data01_data' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_Nak_contents_data01_data_WindowLen(var) var

/* Access member 'WindowLen' of type 'c_MLMFPA_SRP_INUSE_Nak_contents_data01_data' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_Nak_contents_data01_data_WindowLen(var) (&var)

/* Access member 'VR' of type 'c_MLMFPA_SRP_INUSE_Nak_contents_data01_data' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_Nak_contents_data01_data_VR(var) var

/* Access member 'VR' of type 'c_MLMFPA_SRP_INUSE_Nak_contents_data01_data' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_Nak_contents_data01_data_VR(var) (&var)

/* Access member 'data' of type 'c_MLMFPA_SRP_INUSE_Nak_contents_data01' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_Nak_contents_data01_data(var) (*var)

/* Access member 'data' of type 'c_MLMFPA_SRP_INUSE_Nak_contents_data01' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_Nak_contents_data01_data(var) var

/* Access member 'data01' of type 'c_MLMFPA_SRP_INUSE_Nak_contents' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_Nak_contents_data01(var) var

/* Access member 'data01' of type 'c_MLMFPA_SRP_INUSE_Nak_contents' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_Nak_contents_data01(var) (&var)

/* DEFINITION OF BINARY c_MLMFPA_SRP_INUSE_Nak_contents_data01_data_FirstErasedDataUnit */
typedef struct _c_MLMFPA_SRP_INUSE_Nak_contents_data01_data_FirstErasedDataUnit {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_MLMFPA_SRP_INUSE_Nak_contents_data01_data_FirstErasedDataUnit;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_MLMFPA_SRP_INUSE_Nak_contents_data01_data_FirstErasedDataUnit(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF BINARY c_MLMFPA_SRP_INUSE_Nak_contents_data01_data_WindowLen */
typedef struct _c_MLMFPA_SRP_INUSE_Nak_contents_data01_data_WindowLen {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_MLMFPA_SRP_INUSE_Nak_contents_data01_data_WindowLen;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_MLMFPA_SRP_INUSE_Nak_contents_data01_data_WindowLen(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF BINARY c_MLMFPA_SRP_INUSE_Nak_contents_data01_data_VR */
typedef struct _c_MLMFPA_SRP_INUSE_Nak_contents_data01_data_VR {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_MLMFPA_SRP_INUSE_Nak_contents_data01_data_VR;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_MLMFPA_SRP_INUSE_Nak_contents_data01_data_VR(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))


/* DEFINITION OF SUB-STRUCTURE c_MLMFPA_SRP_INUSE_Nak_contents_data01_data */
typedef struct _c_MLMFPA_SRP_INUSE_Nak_contents_data01_data {

	c_MLMFPA_SRP_INUSE_Nak_contents_data01_data_FirstErasedDataUnit FirstErasedDataUnit; /* Static, variable size; bits needed 64 *//*GBD01b*/
	c_MLMFPA_SRP_INUSE_Nak_contents_data01_data_WindowLen WindowLen; /* Static, variable size; bits needed 64 *//*GBD01b*/
	c_MLMFPA_SRP_INUSE_Nak_contents_data01_data_VR VR; /* Static, variable size; bits needed 64 *//*GBD01b*/

} c_MLMFPA_SRP_INUSE_Nak_contents_data01_data;

/* DEFINITION OF SUB-STRUCTURE c_MLMFPA_SRP_INUSE_Nak_contents_data01 */
typedef struct _c_MLMFPA_SRP_INUSE_Nak_contents_data01 {

	c_MLMFPA_SRP_INUSE_Nak_contents_data01_data **data; /* NDY03 *//*GBD01b*//*AR01*/
	int allocatedItems; /*ALC*/
	int items; /*XYZ*/

} c_MLMFPA_SRP_INUSE_Nak_contents_data01;


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_Nak_contents {

	ED_OCTET LinkFlowNumber; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Route; /* ODY01a *//*GBD01b*/
	ED_OCTET Reserved1; /* ODY01a *//*GBD01b*/
	ED_OCTET SARSequenceLength; /* ODY01a *//*GBD01b*/
	ED_OCTET ReportCount; /* ODY01a *//*GBD01b*/
	c_MLMFPA_SRP_INUSE_Nak_contents_data01 data01;/*GFB09*//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_Nak_contents;
#define INIT_c_MLMFPA_SRP_INUSE_Nak_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_Nak_contents))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_Nak_contents(c_MLMFPA_SRP_INUSE_Nak_contents* sp);

/* Access member 'LinkFlowNumber' of type 'c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents' as a variable reference */
#define VAR_c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_LinkFlowNumber(var) var

/* Access member 'LinkFlowNumber' of type 'c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents' as a pointer */
#define PTR_c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_LinkFlowNumber(var) (&var)

/* Access member 'Route' of type 'c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents' as a variable reference */
#define VAR_c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_Route(var) var

/* Access member 'Route' of type 'c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents' as a pointer */
#define PTR_c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_Route(var) (&var)

/* Access member 'AckRequired' of type 'c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents' as a variable reference */
#define VAR_c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_AckRequired(var) var

/* Access member 'AckRequired' of type 'c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents' as a pointer */
#define PTR_c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_AckRequired(var) (&var)

/* Access member 'Reset' of type 'c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents' as a variable reference */
#define VAR_c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_Reset(var) var

/* Access member 'Reset' of type 'c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents' as a pointer */
#define PTR_c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_Reset(var) (&var)

/* Access member 'Reserved' of type 'c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents' as a variable reference */
#define VAR_c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_Reserved(var) var

/* Access member 'Reserved' of type 'c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents' as a pointer */
#define PTR_c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_Reserved(var) (&var)

/* Access member 'MessageSequence' of type 'c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents' as a variable reference */
#define VAR_c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_MessageSequence(var) var

/* Access member 'MessageSequence' of type 'c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents' as a pointer */
#define PTR_c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_MessageSequence(var) (&var)

/* Access member 'HigherLayerPacket' of type 'c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents' as a variable reference */
#define VAR_c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_HigherLayerPacket(var) var

/* Access member 'HigherLayerPacket' of type 'c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents' as a pointer */
#define PTR_c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_HigherLayerPacket(var) (&var)

/* DEFINITION OF BINARY c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_HigherLayerPacket */
typedef struct _c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_HigherLayerPacket {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_HigherLayerPacket;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_HigherLayerPacket(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents {

	ED_OCTET LinkFlowNumber; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Route; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN AckRequired; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Reset; /* ODY01a *//*GBD01b*/
	ED_OCTET Reserved; /* ODY01a *//*GBD01b*/
	ED_OCTET MessageSequence; /* ODY01a *//*GBD01b*/
	c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents_HigherLayerPacket HigherLayerPacket; /* Static, variable size; bits needed 64 *//*GBD01b*/

}	c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents;
#define INIT_c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents))
/*FRK03a*/
void FREE_c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents(c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents* sp);

/* Access member 'Route' of type 'c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents' as a variable reference */
#define VAR_c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents_Route(var) var

/* Access member 'Route' of type 'c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents' as a pointer */
#define PTR_c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents_Route(var) (&var)

/* Access member 'AckSequence' of type 'c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents' as a variable reference */
#define VAR_c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents_AckSequence(var) var

/* Access member 'AckSequence' of type 'c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents' as a pointer */
#define PTR_c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents_AckSequence(var) (&var)

/* Access member 'Reserved' of type 'c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents' as a variable reference */
#define VAR_c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents_Reserved(var) var

/* Access member 'Reserved' of type 'c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents' as a pointer */
#define PTR_c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents_Reserved(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents {

	ED_BOOLEAN Route; /* ODY01a *//*GBD01b*/
	ED_OCTET AckSequence; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN Reserved; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents;
#define INIT_c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents))
/*FRK03a*/
void FREE_c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents(c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents* sp);

/* Access member 'LocationType' of type 'c_MLMFPA_LUP_INUSE_LocationNotification_contents' as a variable reference */
#define VAR_c_MLMFPA_LUP_INUSE_LocationNotification_contents_LocationType(var) var

/* Access member 'LocationType' of type 'c_MLMFPA_LUP_INUSE_LocationNotification_contents' as a pointer */
#define PTR_c_MLMFPA_LUP_INUSE_LocationNotification_contents_LocationType(var) (&var)

/* Access member 'LocationLength' of type 'c_MLMFPA_LUP_INUSE_LocationNotification_contents' as a variable reference */
#define VAR_c_MLMFPA_LUP_INUSE_LocationNotification_contents_LocationLength(var) var

/* Access member 'LocationLength' of type 'c_MLMFPA_LUP_INUSE_LocationNotification_contents' as a pointer */
#define PTR_c_MLMFPA_LUP_INUSE_LocationNotification_contents_LocationLength(var) (&var)

/* Access member 'LocationValue' of type 'c_MLMFPA_LUP_INUSE_LocationNotification_contents' as a variable reference */
#define VAR_c_MLMFPA_LUP_INUSE_LocationNotification_contents_LocationValue(var) var

/* Access member 'LocationValue' of type 'c_MLMFPA_LUP_INUSE_LocationNotification_contents' as a pointer */
#define PTR_c_MLMFPA_LUP_INUSE_LocationNotification_contents_LocationValue(var) (&var)

/* DEFINITION OF BINARY c_MLMFPA_LUP_INUSE_LocationNotification_contents_LocationValue */
typedef struct _c_MLMFPA_LUP_INUSE_LocationNotification_contents_LocationValue {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_MLMFPA_LUP_INUSE_LocationNotification_contents_LocationValue;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_MLMFPA_LUP_INUSE_LocationNotification_contents_LocationValue(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_MLMFPA_LUP_INUSE_LocationNotification_contents {

	ED_OCTET LocationType; /* ODY01a *//*GBD01b*/
	ED_OCTET LocationLength; /* ODY01a *//*GBD01b*/
	ED_BOOLEAN LocationLength_Present;
	c_MLMFPA_LUP_INUSE_LocationNotification_contents_LocationValue LocationValue; /* Static, variable size; bits needed 64 *//*GBD01b*/

}	c_MLMFPA_LUP_INUSE_LocationNotification_contents;
#define INIT_c_MLMFPA_LUP_INUSE_LocationNotification_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_LUP_INUSE_LocationNotification_contents))
/*FRK03a*/
void FREE_c_MLMFPA_LUP_INUSE_LocationNotification_contents(c_MLMFPA_LUP_INUSE_LocationNotification_contents* sp);
#define SETPRESENT_c_MLMFPA_LUP_INUSE_LocationNotification_contents_LocationLength(sp,present) ((sp)->LocationLength_Present = present)
#define GETPRESENT_c_MLMFPA_LUP_INUSE_LocationNotification_contents_LocationLength(sp) ((sp)->LocationLength_Present)

/* Access member 'TransactionID' of type 'c_MLMFPA_LUP_INUSE_LocationAssignment_contents' as a variable reference */
#define VAR_c_MLMFPA_LUP_INUSE_LocationAssignment_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_MLMFPA_LUP_INUSE_LocationAssignment_contents' as a pointer */
#define PTR_c_MLMFPA_LUP_INUSE_LocationAssignment_contents_TransactionID(var) (&var)

/* Access member 'LocationType' of type 'c_MLMFPA_LUP_INUSE_LocationAssignment_contents' as a variable reference */
#define VAR_c_MLMFPA_LUP_INUSE_LocationAssignment_contents_LocationType(var) var

/* Access member 'LocationType' of type 'c_MLMFPA_LUP_INUSE_LocationAssignment_contents' as a pointer */
#define PTR_c_MLMFPA_LUP_INUSE_LocationAssignment_contents_LocationType(var) (&var)

/* Access member 'LocationLength' of type 'c_MLMFPA_LUP_INUSE_LocationAssignment_contents' as a variable reference */
#define VAR_c_MLMFPA_LUP_INUSE_LocationAssignment_contents_LocationLength(var) var

/* Access member 'LocationLength' of type 'c_MLMFPA_LUP_INUSE_LocationAssignment_contents' as a pointer */
#define PTR_c_MLMFPA_LUP_INUSE_LocationAssignment_contents_LocationLength(var) (&var)

/* Access member 'LocationValue' of type 'c_MLMFPA_LUP_INUSE_LocationAssignment_contents' as a variable reference */
#define VAR_c_MLMFPA_LUP_INUSE_LocationAssignment_contents_LocationValue(var) var

/* Access member 'LocationValue' of type 'c_MLMFPA_LUP_INUSE_LocationAssignment_contents' as a pointer */
#define PTR_c_MLMFPA_LUP_INUSE_LocationAssignment_contents_LocationValue(var) (&var)

/* DEFINITION OF BINARY c_MLMFPA_LUP_INUSE_LocationAssignment_contents_LocationValue */
typedef struct _c_MLMFPA_LUP_INUSE_LocationAssignment_contents_LocationValue {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_MLMFPA_LUP_INUSE_LocationAssignment_contents_LocationValue;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_MLMFPA_LUP_INUSE_LocationAssignment_contents_LocationValue(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_MLMFPA_LUP_INUSE_LocationAssignment_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	ED_OCTET LocationType; /* ODY01a *//*GBD01b*/
	ED_OCTET LocationLength; /* ODY01a *//*GBD01b*/
	c_MLMFPA_LUP_INUSE_LocationAssignment_contents_LocationValue LocationValue; /* Static, variable size; bits needed 64 *//*GBD01b*/

}	c_MLMFPA_LUP_INUSE_LocationAssignment_contents;
#define INIT_c_MLMFPA_LUP_INUSE_LocationAssignment_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_LUP_INUSE_LocationAssignment_contents))
/*FRK03a*/
void FREE_c_MLMFPA_LUP_INUSE_LocationAssignment_contents(c_MLMFPA_LUP_INUSE_LocationAssignment_contents* sp);

/* Access member 'TransactionID' of type 'c_MLMFPA_LUP_INUSE_LocationComplete_contents' as a variable reference */
#define VAR_c_MLMFPA_LUP_INUSE_LocationComplete_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_MLMFPA_LUP_INUSE_LocationComplete_contents' as a pointer */
#define PTR_c_MLMFPA_LUP_INUSE_LocationComplete_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_LUP_INUSE_LocationComplete_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_LUP_INUSE_LocationComplete_contents;
#define INIT_c_MLMFPA_LUP_INUSE_LocationComplete_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_LUP_INUSE_LocationComplete_contents))
/*FRK03a*/
void FREE_c_MLMFPA_LUP_INUSE_LocationComplete_contents(c_MLMFPA_LUP_INUSE_LocationComplete_contents* sp);

/* Access member 'StorageBLOBType' of type 'c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents' as a variable reference */
#define VAR_c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOBType(var) var

/* Access member 'StorageBLOBType' of type 'c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents' as a pointer */
#define PTR_c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOBType(var) (&var)

/* Access member 'StorageBLOBLength' of type 'c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents' as a variable reference */
#define VAR_c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOBLength(var) var

/* Access member 'StorageBLOBLength' of type 'c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents' as a pointer */
#define PTR_c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOBLength(var) (&var)

/* Access member 'StorageBLOB' of type 'c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents' as a variable reference */
#define VAR_c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOB(var) var

/* Access member 'StorageBLOB' of type 'c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents' as a pointer */
#define PTR_c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOB(var) (&var)

/* DEFINITION OF BINARY c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOB */
typedef struct _c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOB {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOB;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOB(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents {

	ED_SHORT StorageBLOBType; /* ODY01a *//*GBD01b*/
	ED_OCTET StorageBLOBLength; /* ODY01a *//*GBD01b*/
	c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents_StorageBLOB StorageBLOB; /* Static, variable size; bits needed 64 *//*GBD01b*/

}	c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents;
#define INIT_c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents))
/*FRK03a*/
void FREE_c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents(c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents* sp);

/* Access member 'TransactionID' of type 'c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents' as a variable reference */
#define VAR_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents' as a pointer */
#define PTR_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents_TransactionID(var) (&var)

/* Access member 'StorageBLOBType' of type 'c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents' as a variable reference */
#define VAR_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOBType(var) var

/* Access member 'StorageBLOBType' of type 'c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents' as a pointer */
#define PTR_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOBType(var) (&var)

/* Access member 'StorageBLOBLength' of type 'c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents' as a variable reference */
#define VAR_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOBLength(var) var

/* Access member 'StorageBLOBLength' of type 'c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents' as a pointer */
#define PTR_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOBLength(var) (&var)

/* Access member 'StorageBLOB' of type 'c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents' as a variable reference */
#define VAR_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOB(var) var

/* Access member 'StorageBLOB' of type 'c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents' as a pointer */
#define PTR_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOB(var) (&var)

/* DEFINITION OF BINARY c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOB */
typedef struct _c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOB {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOB;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOB(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/
	ED_SHORT StorageBLOBType; /* ODY01a *//*GBD01b*/
	ED_OCTET StorageBLOBLength; /* ODY01a *//*GBD01b*/
	c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents_StorageBLOB StorageBLOB; /* Static, variable size; bits needed 64 *//*GBD01b*/

}	c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents;
#define INIT_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents))
/*FRK03a*/
void FREE_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents(c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents* sp);

/* Access member 'TransactionID' of type 'c_MLMFPA_LUP_INUSE_StorageBLOBComplete_contents' as a variable reference */
#define VAR_c_MLMFPA_LUP_INUSE_StorageBLOBComplete_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_MLMFPA_LUP_INUSE_StorageBLOBComplete_contents' as a pointer */
#define PTR_c_MLMFPA_LUP_INUSE_StorageBLOBComplete_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_LUP_INUSE_StorageBLOBComplete_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_LUP_INUSE_StorageBLOBComplete_contents;
#define INIT_c_MLMFPA_LUP_INUSE_StorageBLOBComplete_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_LUP_INUSE_StorageBLOBComplete_contents))
/*FRK03a*/
void FREE_c_MLMFPA_LUP_INUSE_StorageBLOBComplete_contents(c_MLMFPA_LUP_INUSE_StorageBLOBComplete_contents* sp);

/* Access member 'TransactionID' of type 'c_MLMFPA_FCP_INUSE_DataReady_contents' as a variable reference */
#define VAR_c_MLMFPA_FCP_INUSE_DataReady_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_MLMFPA_FCP_INUSE_DataReady_contents' as a pointer */
#define PTR_c_MLMFPA_FCP_INUSE_DataReady_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_FCP_INUSE_DataReady_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_FCP_INUSE_DataReady_contents;
#define INIT_c_MLMFPA_FCP_INUSE_DataReady_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_FCP_INUSE_DataReady_contents))
/*FRK03a*/
void FREE_c_MLMFPA_FCP_INUSE_DataReady_contents(c_MLMFPA_FCP_INUSE_DataReady_contents* sp);

/* Access member 'TransactionID' of type 'c_MLMFPA_FCP_INUSE_DataReadyAck_contents' as a variable reference */
#define VAR_c_MLMFPA_FCP_INUSE_DataReadyAck_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_MLMFPA_FCP_INUSE_DataReadyAck_contents' as a pointer */
#define PTR_c_MLMFPA_FCP_INUSE_DataReadyAck_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_FCP_INUSE_DataReadyAck_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_FCP_INUSE_DataReadyAck_contents;
#define INIT_c_MLMFPA_FCP_INUSE_DataReadyAck_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_FCP_INUSE_DataReadyAck_contents))
/*FRK03a*/
void FREE_c_MLMFPA_FCP_INUSE_DataReadyAck_contents(c_MLMFPA_FCP_INUSE_DataReadyAck_contents* sp);

/* Access member 'TransactionID' of type 'c_MLMFPA_FCP_INUSE_RestartNetworkInterface_contents' as a variable reference */
#define VAR_c_MLMFPA_FCP_INUSE_RestartNetworkInterface_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_MLMFPA_FCP_INUSE_RestartNetworkInterface_contents' as a pointer */
#define PTR_c_MLMFPA_FCP_INUSE_RestartNetworkInterface_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_FCP_INUSE_RestartNetworkInterface_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_FCP_INUSE_RestartNetworkInterface_contents;
#define INIT_c_MLMFPA_FCP_INUSE_RestartNetworkInterface_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_FCP_INUSE_RestartNetworkInterface_contents))
/*FRK03a*/
void FREE_c_MLMFPA_FCP_INUSE_RestartNetworkInterface_contents(c_MLMFPA_FCP_INUSE_RestartNetworkInterface_contents* sp);

/* Access member 'TransactionID' of type 'c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck_contents' as a variable reference */
#define VAR_c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck_contents_TransactionID(var) var

/* Access member 'TransactionID' of type 'c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck_contents' as a pointer */
#define PTR_c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck_contents_TransactionID(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck_contents {

	ED_OCTET TransactionID; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck_contents;
#define INIT_c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck_contents(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck_contents))
/*FRK03a*/
void FREE_c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck_contents(c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck_contents* sp);

/* Access member 'contents' of type 'c_EMFPKA_EMFPA_INCFG_ConfigurationRequest' as a variable reference */
#define VAR_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_EMFPA_INCFG_ConfigurationRequest' as a pointer */
#define PTR_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_EMFPA_INCFG_ConfigurationRequest {

	c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_EMFPA_INCFG_ConfigurationRequest;
#define INIT_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_EMFPA_INCFG_ConfigurationRequest))
/*FRK03a*/
void FREE_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest(c_EMFPKA_EMFPA_INCFG_ConfigurationRequest* sp);

/* Access member 'contents' of type 'c_EMFPKA_EMFPA_INCFG_ConfigurationResponse' as a variable reference */
#define VAR_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_EMFPA_INCFG_ConfigurationResponse' as a pointer */
#define PTR_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_EMFPA_INCFG_ConfigurationResponse {

	c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_EMFPA_INCFG_ConfigurationResponse;
#define INIT_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_EMFPA_INCFG_ConfigurationResponse))
/*FRK03a*/
void FREE_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse(c_EMFPKA_EMFPA_INCFG_ConfigurationResponse* sp);

/* Access member 'contents' of type 'c_EMFPKA_RSP_INUSE_RouteSelect' as a variable reference */
#define VAR_c_EMFPKA_RSP_INUSE_RouteSelect_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_RSP_INUSE_RouteSelect' as a pointer */
#define PTR_c_EMFPKA_RSP_INUSE_RouteSelect_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RSP_INUSE_RouteSelect {

	c_EMFPKA_RSP_INUSE_RouteSelect_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RSP_INUSE_RouteSelect;
#define INIT_c_EMFPKA_RSP_INUSE_RouteSelect(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RSP_INUSE_RouteSelect))
/*FRK03a*/
void FREE_c_EMFPKA_RSP_INUSE_RouteSelect(c_EMFPKA_RSP_INUSE_RouteSelect* sp);

/* Access member 'contents' of type 'c_EMFPKA_RSP_INUSE_RouteSelectAck' as a variable reference */
#define VAR_c_EMFPKA_RSP_INUSE_RouteSelectAck_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_RSP_INUSE_RouteSelectAck' as a pointer */
#define PTR_c_EMFPKA_RSP_INUSE_RouteSelectAck_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RSP_INUSE_RouteSelectAck {

	c_EMFPKA_RSP_INUSE_RouteSelectAck_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RSP_INUSE_RouteSelectAck;
#define INIT_c_EMFPKA_RSP_INUSE_RouteSelectAck(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RSP_INUSE_RouteSelectAck))
/*FRK03a*/
void FREE_c_EMFPKA_RSP_INUSE_RouteSelectAck(c_EMFPKA_RSP_INUSE_RouteSelectAck* sp);

/* Access member 'contents' of type 'c_EMFPKA_RSP_INUSE_ActivateRoute' as a variable reference */
#define VAR_c_EMFPKA_RSP_INUSE_ActivateRoute_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_RSP_INUSE_ActivateRoute' as a pointer */
#define PTR_c_EMFPKA_RSP_INUSE_ActivateRoute_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RSP_INUSE_ActivateRoute {

	c_EMFPKA_RSP_INUSE_ActivateRoute_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RSP_INUSE_ActivateRoute;
#define INIT_c_EMFPKA_RSP_INUSE_ActivateRoute(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RSP_INUSE_ActivateRoute))
/*FRK03a*/
void FREE_c_EMFPKA_RSP_INUSE_ActivateRoute(c_EMFPKA_RSP_INUSE_ActivateRoute* sp);

/* Access member 'contents' of type 'c_EMFPKA_RSP_INUSE_ActivateRouteAck' as a variable reference */
#define VAR_c_EMFPKA_RSP_INUSE_ActivateRouteAck_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_RSP_INUSE_ActivateRouteAck' as a pointer */
#define PTR_c_EMFPKA_RSP_INUSE_ActivateRouteAck_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RSP_INUSE_ActivateRouteAck {

	c_EMFPKA_RSP_INUSE_ActivateRouteAck_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RSP_INUSE_ActivateRouteAck;
#define INIT_c_EMFPKA_RSP_INUSE_ActivateRouteAck(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RSP_INUSE_ActivateRouteAck))
/*FRK03a*/
void FREE_c_EMFPKA_RSP_INUSE_ActivateRouteAck(c_EMFPKA_RSP_INUSE_ActivateRouteAck* sp);

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_ResetTxIndication' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ResetTxIndication_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_ResetTxIndication' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ResetTxIndication_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_ResetTxIndication {

	c_EMFPKA_RLP_INUSE_ResetTxIndication_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_ResetTxIndication;
#define INIT_c_EMFPKA_RLP_INUSE_ResetTxIndication(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_ResetTxIndication))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_ResetTxIndication(c_EMFPKA_RLP_INUSE_ResetTxIndication* sp);

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_ResetRxIndication' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ResetRxIndication_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_ResetRxIndication' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ResetRxIndication_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_ResetRxIndication {

	c_EMFPKA_RLP_INUSE_ResetRxIndication_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_ResetRxIndication;
#define INIT_c_EMFPKA_RLP_INUSE_ResetRxIndication(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_ResetRxIndication))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_ResetRxIndication(c_EMFPKA_RLP_INUSE_ResetRxIndication* sp);

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_ResetTxIndicationAck' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_ResetTxIndicationAck' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_ResetTxIndicationAck {

	c_EMFPKA_RLP_INUSE_ResetTxIndicationAck_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_ResetTxIndicationAck;
#define INIT_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_ResetTxIndicationAck))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_ResetTxIndicationAck(c_EMFPKA_RLP_INUSE_ResetTxIndicationAck* sp);

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_ResetTxComplete' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ResetTxComplete_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_ResetTxComplete' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ResetTxComplete_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_ResetTxComplete {

	c_EMFPKA_RLP_INUSE_ResetTxComplete_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_ResetTxComplete;
#define INIT_c_EMFPKA_RLP_INUSE_ResetTxComplete(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_ResetTxComplete))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_ResetTxComplete(c_EMFPKA_RLP_INUSE_ResetTxComplete* sp);

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_ResetRxComplete' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ResetRxComplete_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_ResetRxComplete' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ResetRxComplete_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_ResetRxComplete {

	c_EMFPKA_RLP_INUSE_ResetRxComplete_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_ResetRxComplete;
#define INIT_c_EMFPKA_RLP_INUSE_ResetRxComplete(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_ResetRxComplete))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_ResetRxComplete(c_EMFPKA_RLP_INUSE_ResetRxComplete* sp);

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_Nak' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_Nak_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_Nak' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_Nak_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_Nak {

	c_EMFPKA_RLP_INUSE_Nak_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_Nak;
#define INIT_c_EMFPKA_RLP_INUSE_Nak(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_Nak))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_Nak(c_EMFPKA_RLP_INUSE_Nak* sp);

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_ReservationOnRequest' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_ReservationOnRequest' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_ReservationOnRequest {

	c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_ReservationOnRequest;
#define INIT_c_EMFPKA_RLP_INUSE_ReservationOnRequest(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_ReservationOnRequest))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_ReservationOnRequest(c_EMFPKA_RLP_INUSE_ReservationOnRequest* sp);

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_ReservationOffRequest' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_ReservationOffRequest' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_ReservationOffRequest {

	c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_ReservationOffRequest;
#define INIT_c_EMFPKA_RLP_INUSE_ReservationOffRequest(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_ReservationOffRequest))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_ReservationOffRequest(c_EMFPKA_RLP_INUSE_ReservationOffRequest* sp);

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_ReservationAccept' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ReservationAccept_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_ReservationAccept' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ReservationAccept_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_ReservationAccept {

	c_EMFPKA_RLP_INUSE_ReservationAccept_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_ReservationAccept;
#define INIT_c_EMFPKA_RLP_INUSE_ReservationAccept(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_ReservationAccept))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_ReservationAccept(c_EMFPKA_RLP_INUSE_ReservationAccept* sp);

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_ReservationReject' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_ReservationReject_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_ReservationReject' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_ReservationReject_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_ReservationReject {

	c_EMFPKA_RLP_INUSE_ReservationReject_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_ReservationReject;
#define INIT_c_EMFPKA_RLP_INUSE_ReservationReject(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_ReservationReject))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_ReservationReject(c_EMFPKA_RLP_INUSE_ReservationReject* sp);

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_RevReservationOn' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_RevReservationOn_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_RevReservationOn' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_RevReservationOn_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_RevReservationOn {

	c_EMFPKA_RLP_INUSE_RevReservationOn_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_RevReservationOn;
#define INIT_c_EMFPKA_RLP_INUSE_RevReservationOn(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_RevReservationOn))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_RevReservationOn(c_EMFPKA_RLP_INUSE_RevReservationOn* sp);

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_RevReservationOff' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_RevReservationOff_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_RevReservationOff' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_RevReservationOff_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_RevReservationOff {

	c_EMFPKA_RLP_INUSE_RevReservationOff_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_RevReservationOff;
#define INIT_c_EMFPKA_RLP_INUSE_RevReservationOff(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_RevReservationOff))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_RevReservationOff(c_EMFPKA_RLP_INUSE_RevReservationOff* sp);

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_FwdReservationOff' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_FwdReservationOff_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_FwdReservationOff' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_FwdReservationOff_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_FwdReservationOff {

	c_EMFPKA_RLP_INUSE_FwdReservationOff_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_FwdReservationOff;
#define INIT_c_EMFPKA_RLP_INUSE_FwdReservationOff(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_FwdReservationOff))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_FwdReservationOff(c_EMFPKA_RLP_INUSE_FwdReservationOff* sp);

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_FwdReservationOn' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_FwdReservationOn_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_FwdReservationOn' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_FwdReservationOn_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_FwdReservationOn {

	c_EMFPKA_RLP_INUSE_FwdReservationOn_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_FwdReservationOn;
#define INIT_c_EMFPKA_RLP_INUSE_FwdReservationOn(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_FwdReservationOn))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_FwdReservationOn(c_EMFPKA_RLP_INUSE_FwdReservationOn* sp);

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_FwdReservationAck' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_FwdReservationAck_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_FwdReservationAck' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_FwdReservationAck_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_FwdReservationAck {

	c_EMFPKA_RLP_INUSE_FwdReservationAck_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_FwdReservationAck;
#define INIT_c_EMFPKA_RLP_INUSE_FwdReservationAck(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_FwdReservationAck))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_FwdReservationAck(c_EMFPKA_RLP_INUSE_FwdReservationAck* sp);

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_AttributeUpdateRequest' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_AttributeUpdateRequest' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_AttributeUpdateRequest {

	c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_AttributeUpdateRequest;
#define INIT_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_AttributeUpdateRequest))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest(c_EMFPKA_RLP_INUSE_AttributeUpdateRequest* sp);

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_AttributeUpdateAccept' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_AttributeUpdateAccept_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_AttributeUpdateAccept' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_AttributeUpdateAccept_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_AttributeUpdateAccept {

	c_EMFPKA_RLP_INUSE_AttributeUpdateAccept_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_AttributeUpdateAccept;
#define INIT_c_EMFPKA_RLP_INUSE_AttributeUpdateAccept(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_AttributeUpdateAccept))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_AttributeUpdateAccept(c_EMFPKA_RLP_INUSE_AttributeUpdateAccept* sp);

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_AttributeUpdateReject' as a variable reference */
#define VAR_c_EMFPKA_RLP_INUSE_AttributeUpdateReject_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_RLP_INUSE_AttributeUpdateReject' as a pointer */
#define PTR_c_EMFPKA_RLP_INUSE_AttributeUpdateReject_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_RLP_INUSE_AttributeUpdateReject {

	c_EMFPKA_RLP_INUSE_AttributeUpdateReject_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_RLP_INUSE_AttributeUpdateReject;
#define INIT_c_EMFPKA_RLP_INUSE_AttributeUpdateReject(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_RLP_INUSE_AttributeUpdateReject))
/*FRK03a*/
void FREE_c_EMFPKA_RLP_INUSE_AttributeUpdateReject(c_EMFPKA_RLP_INUSE_AttributeUpdateReject* sp);

/* Access member 'contents' of type 'c_EMFPKA_DOSP_INUSE_DataOverSignaling' as a variable reference */
#define VAR_c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_DOSP_INUSE_DataOverSignaling' as a pointer */
#define PTR_c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_DOSP_INUSE_DataOverSignaling {

	c_EMFPKA_DOSP_INUSE_DataOverSignaling_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_DOSP_INUSE_DataOverSignaling;
#define INIT_c_EMFPKA_DOSP_INUSE_DataOverSignaling(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_DOSP_INUSE_DataOverSignaling))
/*FRK03a*/
void FREE_c_EMFPKA_DOSP_INUSE_DataOverSignaling(c_EMFPKA_DOSP_INUSE_DataOverSignaling* sp);

/* Access member 'contents' of type 'c_EMFPKA_DOSP_INUSE_DataOverSignalingAck' as a variable reference */
#define VAR_c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_DOSP_INUSE_DataOverSignalingAck' as a pointer */
#define PTR_c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_DOSP_INUSE_DataOverSignalingAck {

	c_EMFPKA_DOSP_INUSE_DataOverSignalingAck_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_DOSP_INUSE_DataOverSignalingAck;
#define INIT_c_EMFPKA_DOSP_INUSE_DataOverSignalingAck(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_DOSP_INUSE_DataOverSignalingAck))
/*FRK03a*/
void FREE_c_EMFPKA_DOSP_INUSE_DataOverSignalingAck(c_EMFPKA_DOSP_INUSE_DataOverSignalingAck* sp);


/*-A----------------------------------*/
typedef struct _c_EMFPKA_LUP_INUSE_LocationRequest {

	int __Dummy_Field__; /* Added to avoid empty structures/unions/etc */
}	c_EMFPKA_LUP_INUSE_LocationRequest;
#define INIT_c_EMFPKA_LUP_INUSE_LocationRequest(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_LUP_INUSE_LocationRequest))
/*FRK03a*/
void FREE_c_EMFPKA_LUP_INUSE_LocationRequest(c_EMFPKA_LUP_INUSE_LocationRequest* sp);

/* Access member 'contents' of type 'c_EMFPKA_LUP_INUSE_LocationNotification' as a variable reference */
#define VAR_c_EMFPKA_LUP_INUSE_LocationNotification_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_LUP_INUSE_LocationNotification' as a pointer */
#define PTR_c_EMFPKA_LUP_INUSE_LocationNotification_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_LUP_INUSE_LocationNotification {

	c_EMFPKA_LUP_INUSE_LocationNotification_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_LUP_INUSE_LocationNotification;
#define INIT_c_EMFPKA_LUP_INUSE_LocationNotification(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_LUP_INUSE_LocationNotification))
/*FRK03a*/
void FREE_c_EMFPKA_LUP_INUSE_LocationNotification(c_EMFPKA_LUP_INUSE_LocationNotification* sp);

/* Access member 'contents' of type 'c_EMFPKA_LUP_INUSE_LocationAssignment' as a variable reference */
#define VAR_c_EMFPKA_LUP_INUSE_LocationAssignment_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_LUP_INUSE_LocationAssignment' as a pointer */
#define PTR_c_EMFPKA_LUP_INUSE_LocationAssignment_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_LUP_INUSE_LocationAssignment {

	c_EMFPKA_LUP_INUSE_LocationAssignment_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_LUP_INUSE_LocationAssignment;
#define INIT_c_EMFPKA_LUP_INUSE_LocationAssignment(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_LUP_INUSE_LocationAssignment))
/*FRK03a*/
void FREE_c_EMFPKA_LUP_INUSE_LocationAssignment(c_EMFPKA_LUP_INUSE_LocationAssignment* sp);

/* Access member 'contents' of type 'c_EMFPKA_LUP_INUSE_LocationComplete' as a variable reference */
#define VAR_c_EMFPKA_LUP_INUSE_LocationComplete_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_LUP_INUSE_LocationComplete' as a pointer */
#define PTR_c_EMFPKA_LUP_INUSE_LocationComplete_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_LUP_INUSE_LocationComplete {

	c_EMFPKA_LUP_INUSE_LocationComplete_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_LUP_INUSE_LocationComplete;
#define INIT_c_EMFPKA_LUP_INUSE_LocationComplete(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_LUP_INUSE_LocationComplete))
/*FRK03a*/
void FREE_c_EMFPKA_LUP_INUSE_LocationComplete(c_EMFPKA_LUP_INUSE_LocationComplete* sp);


/*-A----------------------------------*/
typedef struct _c_EMFPKA_LUP_INUSE_StorageBLOBRequest {

	int __Dummy_Field__; /* Added to avoid empty structures/unions/etc */
}	c_EMFPKA_LUP_INUSE_StorageBLOBRequest;
#define INIT_c_EMFPKA_LUP_INUSE_StorageBLOBRequest(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_LUP_INUSE_StorageBLOBRequest))
/*FRK03a*/
void FREE_c_EMFPKA_LUP_INUSE_StorageBLOBRequest(c_EMFPKA_LUP_INUSE_StorageBLOBRequest* sp);

/* Access member 'contents' of type 'c_EMFPKA_LUP_INUSE_StorageBLOBNotification' as a variable reference */
#define VAR_c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_LUP_INUSE_StorageBLOBNotification' as a pointer */
#define PTR_c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_LUP_INUSE_StorageBLOBNotification {

	c_EMFPKA_LUP_INUSE_StorageBLOBNotification_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_LUP_INUSE_StorageBLOBNotification;
#define INIT_c_EMFPKA_LUP_INUSE_StorageBLOBNotification(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_LUP_INUSE_StorageBLOBNotification))
/*FRK03a*/
void FREE_c_EMFPKA_LUP_INUSE_StorageBLOBNotification(c_EMFPKA_LUP_INUSE_StorageBLOBNotification* sp);

/* Access member 'contents' of type 'c_EMFPKA_LUP_INUSE_StorageBLOBAssignment' as a variable reference */
#define VAR_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_LUP_INUSE_StorageBLOBAssignment' as a pointer */
#define PTR_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_LUP_INUSE_StorageBLOBAssignment {

	c_EMFPKA_LUP_INUSE_StorageBLOBAssignment_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_LUP_INUSE_StorageBLOBAssignment;
#define INIT_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_LUP_INUSE_StorageBLOBAssignment))
/*FRK03a*/
void FREE_c_EMFPKA_LUP_INUSE_StorageBLOBAssignment(c_EMFPKA_LUP_INUSE_StorageBLOBAssignment* sp);

/* Access member 'contents' of type 'c_EMFPKA_LUP_INUSE_StorageBLOBComplete' as a variable reference */
#define VAR_c_EMFPKA_LUP_INUSE_StorageBLOBComplete_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_LUP_INUSE_StorageBLOBComplete' as a pointer */
#define PTR_c_EMFPKA_LUP_INUSE_StorageBLOBComplete_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_LUP_INUSE_StorageBLOBComplete {

	c_EMFPKA_LUP_INUSE_StorageBLOBComplete_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_LUP_INUSE_StorageBLOBComplete;
#define INIT_c_EMFPKA_LUP_INUSE_StorageBLOBComplete(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_LUP_INUSE_StorageBLOBComplete))
/*FRK03a*/
void FREE_c_EMFPKA_LUP_INUSE_StorageBLOBComplete(c_EMFPKA_LUP_INUSE_StorageBLOBComplete* sp);


/*-A----------------------------------*/
typedef struct _c_EMFPKA_FCP_INUSE_XonRequest {

	int __Dummy_Field__; /* Added to avoid empty structures/unions/etc */
}	c_EMFPKA_FCP_INUSE_XonRequest;
#define INIT_c_EMFPKA_FCP_INUSE_XonRequest(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_FCP_INUSE_XonRequest))
/*FRK03a*/
void FREE_c_EMFPKA_FCP_INUSE_XonRequest(c_EMFPKA_FCP_INUSE_XonRequest* sp);


/*-A----------------------------------*/
typedef struct _c_EMFPKA_FCP_INUSE_XonResponse {

	int __Dummy_Field__; /* Added to avoid empty structures/unions/etc */
}	c_EMFPKA_FCP_INUSE_XonResponse;
#define INIT_c_EMFPKA_FCP_INUSE_XonResponse(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_FCP_INUSE_XonResponse))
/*FRK03a*/
void FREE_c_EMFPKA_FCP_INUSE_XonResponse(c_EMFPKA_FCP_INUSE_XonResponse* sp);


/*-A----------------------------------*/
typedef struct _c_EMFPKA_FCP_INUSE_XoffRequest {

	int __Dummy_Field__; /* Added to avoid empty structures/unions/etc */
}	c_EMFPKA_FCP_INUSE_XoffRequest;
#define INIT_c_EMFPKA_FCP_INUSE_XoffRequest(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_FCP_INUSE_XoffRequest))
/*FRK03a*/
void FREE_c_EMFPKA_FCP_INUSE_XoffRequest(c_EMFPKA_FCP_INUSE_XoffRequest* sp);


/*-A----------------------------------*/
typedef struct _c_EMFPKA_FCP_INUSE_XoffResponse {

	int __Dummy_Field__; /* Added to avoid empty structures/unions/etc */
}	c_EMFPKA_FCP_INUSE_XoffResponse;
#define INIT_c_EMFPKA_FCP_INUSE_XoffResponse(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_FCP_INUSE_XoffResponse))
/*FRK03a*/
void FREE_c_EMFPKA_FCP_INUSE_XoffResponse(c_EMFPKA_FCP_INUSE_XoffResponse* sp);

/* Access member 'contents' of type 'c_EMFPKA_FCP_INUSE_DataReady' as a variable reference */
#define VAR_c_EMFPKA_FCP_INUSE_DataReady_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_FCP_INUSE_DataReady' as a pointer */
#define PTR_c_EMFPKA_FCP_INUSE_DataReady_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_FCP_INUSE_DataReady {

	c_EMFPKA_FCP_INUSE_DataReady_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_FCP_INUSE_DataReady;
#define INIT_c_EMFPKA_FCP_INUSE_DataReady(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_FCP_INUSE_DataReady))
/*FRK03a*/
void FREE_c_EMFPKA_FCP_INUSE_DataReady(c_EMFPKA_FCP_INUSE_DataReady* sp);

/* Access member 'contents' of type 'c_EMFPKA_FCP_INUSE_DataReadyAck' as a variable reference */
#define VAR_c_EMFPKA_FCP_INUSE_DataReadyAck_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_FCP_INUSE_DataReadyAck' as a pointer */
#define PTR_c_EMFPKA_FCP_INUSE_DataReadyAck_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_FCP_INUSE_DataReadyAck {

	c_EMFPKA_FCP_INUSE_DataReadyAck_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_FCP_INUSE_DataReadyAck;
#define INIT_c_EMFPKA_FCP_INUSE_DataReadyAck(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_FCP_INUSE_DataReadyAck))
/*FRK03a*/
void FREE_c_EMFPKA_FCP_INUSE_DataReadyAck(c_EMFPKA_FCP_INUSE_DataReadyAck* sp);

/* Access member 'contents' of type 'c_EMFPKA_FCP_INUSE_RestartNetworkInterface' as a variable reference */
#define VAR_c_EMFPKA_FCP_INUSE_RestartNetworkInterface_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_FCP_INUSE_RestartNetworkInterface' as a pointer */
#define PTR_c_EMFPKA_FCP_INUSE_RestartNetworkInterface_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_FCP_INUSE_RestartNetworkInterface {

	c_EMFPKA_FCP_INUSE_RestartNetworkInterface_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_FCP_INUSE_RestartNetworkInterface;
#define INIT_c_EMFPKA_FCP_INUSE_RestartNetworkInterface(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_FCP_INUSE_RestartNetworkInterface))
/*FRK03a*/
void FREE_c_EMFPKA_FCP_INUSE_RestartNetworkInterface(c_EMFPKA_FCP_INUSE_RestartNetworkInterface* sp);

/* Access member 'contents' of type 'c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck' as a variable reference */
#define VAR_c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck_contents(var) var

/* Access member 'contents' of type 'c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck' as a pointer */
#define PTR_c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck {

	c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck_contents contents; /* ODY01a *//*GBD01b*/

}	c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck;
#define INIT_c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck(sp) ED_RESET_MEM ((sp), sizeof (c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck))
/*FRK03a*/
void FREE_c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck(c_EMFPKA_FCP_INUSE_RestartNetworkInterfaceAck* sp);

/* Access member 'contents' of type 'c_MLMFPA_MMFPA_INCFG_ConfigurationRequest' as a variable reference */
#define VAR_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_MMFPA_INCFG_ConfigurationRequest' as a pointer */
#define PTR_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_MMFPA_INCFG_ConfigurationRequest {

	c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_MMFPA_INCFG_ConfigurationRequest;
#define INIT_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_MMFPA_INCFG_ConfigurationRequest))
/*FRK03a*/
void FREE_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest(c_MLMFPA_MMFPA_INCFG_ConfigurationRequest* sp);

/* Access member 'contents' of type 'c_MLMFPA_MMFPA_INCFG_ConfigurationResponse' as a variable reference */
#define VAR_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_MMFPA_INCFG_ConfigurationResponse' as a pointer */
#define PTR_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_MMFPA_INCFG_ConfigurationResponse {

	c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_MMFPA_INCFG_ConfigurationResponse;
#define INIT_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_MMFPA_INCFG_ConfigurationResponse))
/*FRK03a*/
void FREE_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse(c_MLMFPA_MMFPA_INCFG_ConfigurationResponse* sp);

/* Access member 'contents' of type 'c_MLMFPA_RSP_INUSE_RouteSelect' as a variable reference */
#define VAR_c_MLMFPA_RSP_INUSE_RouteSelect_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_RSP_INUSE_RouteSelect' as a pointer */
#define PTR_c_MLMFPA_RSP_INUSE_RouteSelect_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_RSP_INUSE_RouteSelect {

	c_MLMFPA_RSP_INUSE_RouteSelect_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_RSP_INUSE_RouteSelect;
#define INIT_c_MLMFPA_RSP_INUSE_RouteSelect(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_RSP_INUSE_RouteSelect))
/*FRK03a*/
void FREE_c_MLMFPA_RSP_INUSE_RouteSelect(c_MLMFPA_RSP_INUSE_RouteSelect* sp);

/* Access member 'contents' of type 'c_MLMFPA_RSP_INUSE_RouteSelectAck' as a variable reference */
#define VAR_c_MLMFPA_RSP_INUSE_RouteSelectAck_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_RSP_INUSE_RouteSelectAck' as a pointer */
#define PTR_c_MLMFPA_RSP_INUSE_RouteSelectAck_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_RSP_INUSE_RouteSelectAck {

	c_MLMFPA_RSP_INUSE_RouteSelectAck_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_RSP_INUSE_RouteSelectAck;
#define INIT_c_MLMFPA_RSP_INUSE_RouteSelectAck(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_RSP_INUSE_RouteSelectAck))
/*FRK03a*/
void FREE_c_MLMFPA_RSP_INUSE_RouteSelectAck(c_MLMFPA_RSP_INUSE_RouteSelectAck* sp);

/* Access member 'contents' of type 'c_MLMFPA_RSP_INUSE_ActivateRoute' as a variable reference */
#define VAR_c_MLMFPA_RSP_INUSE_ActivateRoute_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_RSP_INUSE_ActivateRoute' as a pointer */
#define PTR_c_MLMFPA_RSP_INUSE_ActivateRoute_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_RSP_INUSE_ActivateRoute {

	c_MLMFPA_RSP_INUSE_ActivateRoute_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_RSP_INUSE_ActivateRoute;
#define INIT_c_MLMFPA_RSP_INUSE_ActivateRoute(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_RSP_INUSE_ActivateRoute))
/*FRK03a*/
void FREE_c_MLMFPA_RSP_INUSE_ActivateRoute(c_MLMFPA_RSP_INUSE_ActivateRoute* sp);

/* Access member 'contents' of type 'c_MLMFPA_RSP_INUSE_ActivateRouteAck' as a variable reference */
#define VAR_c_MLMFPA_RSP_INUSE_ActivateRouteAck_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_RSP_INUSE_ActivateRouteAck' as a pointer */
#define PTR_c_MLMFPA_RSP_INUSE_ActivateRouteAck_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_RSP_INUSE_ActivateRouteAck {

	c_MLMFPA_RSP_INUSE_ActivateRouteAck_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_RSP_INUSE_ActivateRouteAck;
#define INIT_c_MLMFPA_RSP_INUSE_ActivateRouteAck(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_RSP_INUSE_ActivateRouteAck))
/*FRK03a*/
void FREE_c_MLMFPA_RSP_INUSE_ActivateRouteAck(c_MLMFPA_RSP_INUSE_ActivateRouteAck* sp);

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_ResetTxIndication' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ResetTxIndication_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_ResetTxIndication' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ResetTxIndication_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_ResetTxIndication {

	c_MLMFPA_SRP_INUSE_ResetTxIndication_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_ResetTxIndication;
#define INIT_c_MLMFPA_SRP_INUSE_ResetTxIndication(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_ResetTxIndication))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_ResetTxIndication(c_MLMFPA_SRP_INUSE_ResetTxIndication* sp);

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_ResetRxIndication' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ResetRxIndication_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_ResetRxIndication' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ResetRxIndication_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_ResetRxIndication {

	c_MLMFPA_SRP_INUSE_ResetRxIndication_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_ResetRxIndication;
#define INIT_c_MLMFPA_SRP_INUSE_ResetRxIndication(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_ResetRxIndication))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_ResetRxIndication(c_MLMFPA_SRP_INUSE_ResetRxIndication* sp);

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_ResetTxIndicationAck' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_ResetTxIndicationAck' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_ResetTxIndicationAck {

	c_MLMFPA_SRP_INUSE_ResetTxIndicationAck_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_ResetTxIndicationAck;
#define INIT_c_MLMFPA_SRP_INUSE_ResetTxIndicationAck(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_ResetTxIndicationAck))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_ResetTxIndicationAck(c_MLMFPA_SRP_INUSE_ResetTxIndicationAck* sp);

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_ResetTxComplete' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ResetTxComplete_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_ResetTxComplete' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ResetTxComplete_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_ResetTxComplete {

	c_MLMFPA_SRP_INUSE_ResetTxComplete_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_ResetTxComplete;
#define INIT_c_MLMFPA_SRP_INUSE_ResetTxComplete(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_ResetTxComplete))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_ResetTxComplete(c_MLMFPA_SRP_INUSE_ResetTxComplete* sp);

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_ResetRxComplete' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ResetRxComplete_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_ResetRxComplete' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ResetRxComplete_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_ResetRxComplete {

	c_MLMFPA_SRP_INUSE_ResetRxComplete_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_ResetRxComplete;
#define INIT_c_MLMFPA_SRP_INUSE_ResetRxComplete(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_ResetRxComplete))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_ResetRxComplete(c_MLMFPA_SRP_INUSE_ResetRxComplete* sp);

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_MultiLinkNak' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_MultiLinkNak {

	c_MLMFPA_SRP_INUSE_MultiLinkNak_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_MultiLinkNak;
#define INIT_c_MLMFPA_SRP_INUSE_MultiLinkNak(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_MultiLinkNak))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_MultiLinkNak(c_MLMFPA_SRP_INUSE_MultiLinkNak* sp);

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_ReservationOnRequest' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_ReservationOnRequest' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_ReservationOnRequest {

	c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_ReservationOnRequest;
#define INIT_c_MLMFPA_SRP_INUSE_ReservationOnRequest(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_ReservationOnRequest))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_ReservationOnRequest(c_MLMFPA_SRP_INUSE_ReservationOnRequest* sp);

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_ReservationOffRequest' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_ReservationOffRequest' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_ReservationOffRequest {

	c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_ReservationOffRequest;
#define INIT_c_MLMFPA_SRP_INUSE_ReservationOffRequest(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_ReservationOffRequest))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_ReservationOffRequest(c_MLMFPA_SRP_INUSE_ReservationOffRequest* sp);

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_ReservationAccept' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ReservationAccept_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_ReservationAccept' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ReservationAccept_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_ReservationAccept {

	c_MLMFPA_SRP_INUSE_ReservationAccept_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_ReservationAccept;
#define INIT_c_MLMFPA_SRP_INUSE_ReservationAccept(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_ReservationAccept))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_ReservationAccept(c_MLMFPA_SRP_INUSE_ReservationAccept* sp);

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_ReservationReject' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_ReservationReject_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_ReservationReject' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_ReservationReject_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_ReservationReject {

	c_MLMFPA_SRP_INUSE_ReservationReject_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_ReservationReject;
#define INIT_c_MLMFPA_SRP_INUSE_ReservationReject(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_ReservationReject))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_ReservationReject(c_MLMFPA_SRP_INUSE_ReservationReject* sp);

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_RevReservationOn' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_RevReservationOn_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_RevReservationOn' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_RevReservationOn_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_RevReservationOn {

	c_MLMFPA_SRP_INUSE_RevReservationOn_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_RevReservationOn;
#define INIT_c_MLMFPA_SRP_INUSE_RevReservationOn(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_RevReservationOn))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_RevReservationOn(c_MLMFPA_SRP_INUSE_RevReservationOn* sp);

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_RevReservationOff' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_RevReservationOff_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_RevReservationOff' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_RevReservationOff_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_RevReservationOff {

	c_MLMFPA_SRP_INUSE_RevReservationOff_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_RevReservationOff;
#define INIT_c_MLMFPA_SRP_INUSE_RevReservationOff(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_RevReservationOff))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_RevReservationOff(c_MLMFPA_SRP_INUSE_RevReservationOff* sp);

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_FwdReservationOff' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_FwdReservationOff_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_FwdReservationOff' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_FwdReservationOff_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_FwdReservationOff {

	c_MLMFPA_SRP_INUSE_FwdReservationOff_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_FwdReservationOff;
#define INIT_c_MLMFPA_SRP_INUSE_FwdReservationOff(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_FwdReservationOff))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_FwdReservationOff(c_MLMFPA_SRP_INUSE_FwdReservationOff* sp);

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_FwdReservationOn' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_FwdReservationOn_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_FwdReservationOn' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_FwdReservationOn_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_FwdReservationOn {

	c_MLMFPA_SRP_INUSE_FwdReservationOn_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_FwdReservationOn;
#define INIT_c_MLMFPA_SRP_INUSE_FwdReservationOn(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_FwdReservationOn))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_FwdReservationOn(c_MLMFPA_SRP_INUSE_FwdReservationOn* sp);

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_FwdReservationAck' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_FwdReservationAck_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_FwdReservationAck' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_FwdReservationAck_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_FwdReservationAck {

	c_MLMFPA_SRP_INUSE_FwdReservationAck_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_FwdReservationAck;
#define INIT_c_MLMFPA_SRP_INUSE_FwdReservationAck(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_FwdReservationAck))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_FwdReservationAck(c_MLMFPA_SRP_INUSE_FwdReservationAck* sp);

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_AttributeUpdateRequest' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_AttributeUpdateRequest' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_AttributeUpdateRequest {

	c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_AttributeUpdateRequest;
#define INIT_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_AttributeUpdateRequest))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest(c_MLMFPA_SRP_INUSE_AttributeUpdateRequest* sp);

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_AttributeUpdateAccept' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_AttributeUpdateAccept_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_AttributeUpdateAccept' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_AttributeUpdateAccept_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_AttributeUpdateAccept {

	c_MLMFPA_SRP_INUSE_AttributeUpdateAccept_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_AttributeUpdateAccept;
#define INIT_c_MLMFPA_SRP_INUSE_AttributeUpdateAccept(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_AttributeUpdateAccept))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_AttributeUpdateAccept(c_MLMFPA_SRP_INUSE_AttributeUpdateAccept* sp);

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_AttributeUpdateReject' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_AttributeUpdateReject_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_AttributeUpdateReject' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_AttributeUpdateReject_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_AttributeUpdateReject {

	c_MLMFPA_SRP_INUSE_AttributeUpdateReject_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_AttributeUpdateReject;
#define INIT_c_MLMFPA_SRP_INUSE_AttributeUpdateReject(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_AttributeUpdateReject))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_AttributeUpdateReject(c_MLMFPA_SRP_INUSE_AttributeUpdateReject* sp);

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_Flush' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_Flush_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_Flush' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_Flush_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_Flush {

	c_MLMFPA_SRP_INUSE_Flush_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_Flush;
#define INIT_c_MLMFPA_SRP_INUSE_Flush(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_Flush))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_Flush(c_MLMFPA_SRP_INUSE_Flush* sp);

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_Nak' as a variable reference */
#define VAR_c_MLMFPA_SRP_INUSE_Nak_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_SRP_INUSE_Nak' as a pointer */
#define PTR_c_MLMFPA_SRP_INUSE_Nak_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_SRP_INUSE_Nak {

	c_MLMFPA_SRP_INUSE_Nak_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_SRP_INUSE_Nak;
#define INIT_c_MLMFPA_SRP_INUSE_Nak(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_SRP_INUSE_Nak))
/*FRK03a*/
void FREE_c_MLMFPA_SRP_INUSE_Nak(c_MLMFPA_SRP_INUSE_Nak* sp);

/* Access member 'contents' of type 'c_MLMFPA_DOSP_INUSE_DataOverSignaling' as a variable reference */
#define VAR_c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_DOSP_INUSE_DataOverSignaling' as a pointer */
#define PTR_c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_DOSP_INUSE_DataOverSignaling {

	c_MLMFPA_DOSP_INUSE_DataOverSignaling_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_DOSP_INUSE_DataOverSignaling;
#define INIT_c_MLMFPA_DOSP_INUSE_DataOverSignaling(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_DOSP_INUSE_DataOverSignaling))
/*FRK03a*/
void FREE_c_MLMFPA_DOSP_INUSE_DataOverSignaling(c_MLMFPA_DOSP_INUSE_DataOverSignaling* sp);

/* Access member 'contents' of type 'c_MLMFPA_DOSP_INUSE_DataOverSignalingAck' as a variable reference */
#define VAR_c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_DOSP_INUSE_DataOverSignalingAck' as a pointer */
#define PTR_c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_DOSP_INUSE_DataOverSignalingAck {

	c_MLMFPA_DOSP_INUSE_DataOverSignalingAck_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_DOSP_INUSE_DataOverSignalingAck;
#define INIT_c_MLMFPA_DOSP_INUSE_DataOverSignalingAck(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_DOSP_INUSE_DataOverSignalingAck))
/*FRK03a*/
void FREE_c_MLMFPA_DOSP_INUSE_DataOverSignalingAck(c_MLMFPA_DOSP_INUSE_DataOverSignalingAck* sp);


/*-A----------------------------------*/
typedef struct _c_MLMFPA_LUP_INUSE_LocationRequest {

	int __Dummy_Field__; /* Added to avoid empty structures/unions/etc */
}	c_MLMFPA_LUP_INUSE_LocationRequest;
#define INIT_c_MLMFPA_LUP_INUSE_LocationRequest(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_LUP_INUSE_LocationRequest))
/*FRK03a*/
void FREE_c_MLMFPA_LUP_INUSE_LocationRequest(c_MLMFPA_LUP_INUSE_LocationRequest* sp);

/* Access member 'contents' of type 'c_MLMFPA_LUP_INUSE_LocationNotification' as a variable reference */
#define VAR_c_MLMFPA_LUP_INUSE_LocationNotification_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_LUP_INUSE_LocationNotification' as a pointer */
#define PTR_c_MLMFPA_LUP_INUSE_LocationNotification_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_LUP_INUSE_LocationNotification {

	c_MLMFPA_LUP_INUSE_LocationNotification_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_LUP_INUSE_LocationNotification;
#define INIT_c_MLMFPA_LUP_INUSE_LocationNotification(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_LUP_INUSE_LocationNotification))
/*FRK03a*/
void FREE_c_MLMFPA_LUP_INUSE_LocationNotification(c_MLMFPA_LUP_INUSE_LocationNotification* sp);

/* Access member 'contents' of type 'c_MLMFPA_LUP_INUSE_LocationAssignment' as a variable reference */
#define VAR_c_MLMFPA_LUP_INUSE_LocationAssignment_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_LUP_INUSE_LocationAssignment' as a pointer */
#define PTR_c_MLMFPA_LUP_INUSE_LocationAssignment_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_LUP_INUSE_LocationAssignment {

	c_MLMFPA_LUP_INUSE_LocationAssignment_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_LUP_INUSE_LocationAssignment;
#define INIT_c_MLMFPA_LUP_INUSE_LocationAssignment(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_LUP_INUSE_LocationAssignment))
/*FRK03a*/
void FREE_c_MLMFPA_LUP_INUSE_LocationAssignment(c_MLMFPA_LUP_INUSE_LocationAssignment* sp);

/* Access member 'contents' of type 'c_MLMFPA_LUP_INUSE_LocationComplete' as a variable reference */
#define VAR_c_MLMFPA_LUP_INUSE_LocationComplete_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_LUP_INUSE_LocationComplete' as a pointer */
#define PTR_c_MLMFPA_LUP_INUSE_LocationComplete_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_LUP_INUSE_LocationComplete {

	c_MLMFPA_LUP_INUSE_LocationComplete_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_LUP_INUSE_LocationComplete;
#define INIT_c_MLMFPA_LUP_INUSE_LocationComplete(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_LUP_INUSE_LocationComplete))
/*FRK03a*/
void FREE_c_MLMFPA_LUP_INUSE_LocationComplete(c_MLMFPA_LUP_INUSE_LocationComplete* sp);


/*-A----------------------------------*/
typedef struct _c_MLMFPA_LUP_INUSE_StorageBLOBRequest {

	int __Dummy_Field__; /* Added to avoid empty structures/unions/etc */
}	c_MLMFPA_LUP_INUSE_StorageBLOBRequest;
#define INIT_c_MLMFPA_LUP_INUSE_StorageBLOBRequest(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_LUP_INUSE_StorageBLOBRequest))
/*FRK03a*/
void FREE_c_MLMFPA_LUP_INUSE_StorageBLOBRequest(c_MLMFPA_LUP_INUSE_StorageBLOBRequest* sp);

/* Access member 'contents' of type 'c_MLMFPA_LUP_INUSE_StorageBLOBNotification' as a variable reference */
#define VAR_c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_LUP_INUSE_StorageBLOBNotification' as a pointer */
#define PTR_c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_LUP_INUSE_StorageBLOBNotification {

	c_MLMFPA_LUP_INUSE_StorageBLOBNotification_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_LUP_INUSE_StorageBLOBNotification;
#define INIT_c_MLMFPA_LUP_INUSE_StorageBLOBNotification(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_LUP_INUSE_StorageBLOBNotification))
/*FRK03a*/
void FREE_c_MLMFPA_LUP_INUSE_StorageBLOBNotification(c_MLMFPA_LUP_INUSE_StorageBLOBNotification* sp);

/* Access member 'contents' of type 'c_MLMFPA_LUP_INUSE_StorageBLOBAssignment' as a variable reference */
#define VAR_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_LUP_INUSE_StorageBLOBAssignment' as a pointer */
#define PTR_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_LUP_INUSE_StorageBLOBAssignment {

	c_MLMFPA_LUP_INUSE_StorageBLOBAssignment_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_LUP_INUSE_StorageBLOBAssignment;
#define INIT_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_LUP_INUSE_StorageBLOBAssignment))
/*FRK03a*/
void FREE_c_MLMFPA_LUP_INUSE_StorageBLOBAssignment(c_MLMFPA_LUP_INUSE_StorageBLOBAssignment* sp);

/* Access member 'contents' of type 'c_MLMFPA_LUP_INUSE_StorageBLOBComplete' as a variable reference */
#define VAR_c_MLMFPA_LUP_INUSE_StorageBLOBComplete_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_LUP_INUSE_StorageBLOBComplete' as a pointer */
#define PTR_c_MLMFPA_LUP_INUSE_StorageBLOBComplete_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_LUP_INUSE_StorageBLOBComplete {

	c_MLMFPA_LUP_INUSE_StorageBLOBComplete_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_LUP_INUSE_StorageBLOBComplete;
#define INIT_c_MLMFPA_LUP_INUSE_StorageBLOBComplete(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_LUP_INUSE_StorageBLOBComplete))
/*FRK03a*/
void FREE_c_MLMFPA_LUP_INUSE_StorageBLOBComplete(c_MLMFPA_LUP_INUSE_StorageBLOBComplete* sp);


/*-A----------------------------------*/
typedef struct _c_MLMFPA_FCP_INUSE_XonRequest {

	int __Dummy_Field__; /* Added to avoid empty structures/unions/etc */
}	c_MLMFPA_FCP_INUSE_XonRequest;
#define INIT_c_MLMFPA_FCP_INUSE_XonRequest(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_FCP_INUSE_XonRequest))
/*FRK03a*/
void FREE_c_MLMFPA_FCP_INUSE_XonRequest(c_MLMFPA_FCP_INUSE_XonRequest* sp);


/*-A----------------------------------*/
typedef struct _c_MLMFPA_FCP_INUSE_XonResponse {

	int __Dummy_Field__; /* Added to avoid empty structures/unions/etc */
}	c_MLMFPA_FCP_INUSE_XonResponse;
#define INIT_c_MLMFPA_FCP_INUSE_XonResponse(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_FCP_INUSE_XonResponse))
/*FRK03a*/
void FREE_c_MLMFPA_FCP_INUSE_XonResponse(c_MLMFPA_FCP_INUSE_XonResponse* sp);


/*-A----------------------------------*/
typedef struct _c_MLMFPA_FCP_INUSE_XoffRequest {

	int __Dummy_Field__; /* Added to avoid empty structures/unions/etc */
}	c_MLMFPA_FCP_INUSE_XoffRequest;
#define INIT_c_MLMFPA_FCP_INUSE_XoffRequest(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_FCP_INUSE_XoffRequest))
/*FRK03a*/
void FREE_c_MLMFPA_FCP_INUSE_XoffRequest(c_MLMFPA_FCP_INUSE_XoffRequest* sp);


/*-A----------------------------------*/
typedef struct _c_MLMFPA_FCP_INUSE_XoffResponse {

	int __Dummy_Field__; /* Added to avoid empty structures/unions/etc */
}	c_MLMFPA_FCP_INUSE_XoffResponse;
#define INIT_c_MLMFPA_FCP_INUSE_XoffResponse(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_FCP_INUSE_XoffResponse))
/*FRK03a*/
void FREE_c_MLMFPA_FCP_INUSE_XoffResponse(c_MLMFPA_FCP_INUSE_XoffResponse* sp);

/* Access member 'contents' of type 'c_MLMFPA_FCP_INUSE_DataReady' as a variable reference */
#define VAR_c_MLMFPA_FCP_INUSE_DataReady_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_FCP_INUSE_DataReady' as a pointer */
#define PTR_c_MLMFPA_FCP_INUSE_DataReady_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_FCP_INUSE_DataReady {

	c_MLMFPA_FCP_INUSE_DataReady_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_FCP_INUSE_DataReady;
#define INIT_c_MLMFPA_FCP_INUSE_DataReady(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_FCP_INUSE_DataReady))
/*FRK03a*/
void FREE_c_MLMFPA_FCP_INUSE_DataReady(c_MLMFPA_FCP_INUSE_DataReady* sp);

/* Access member 'contents' of type 'c_MLMFPA_FCP_INUSE_DataReadyAck' as a variable reference */
#define VAR_c_MLMFPA_FCP_INUSE_DataReadyAck_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_FCP_INUSE_DataReadyAck' as a pointer */
#define PTR_c_MLMFPA_FCP_INUSE_DataReadyAck_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_FCP_INUSE_DataReadyAck {

	c_MLMFPA_FCP_INUSE_DataReadyAck_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_FCP_INUSE_DataReadyAck;
#define INIT_c_MLMFPA_FCP_INUSE_DataReadyAck(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_FCP_INUSE_DataReadyAck))
/*FRK03a*/
void FREE_c_MLMFPA_FCP_INUSE_DataReadyAck(c_MLMFPA_FCP_INUSE_DataReadyAck* sp);

/* Access member 'contents' of type 'c_MLMFPA_FCP_INUSE_RestartNetworkInterface' as a variable reference */
#define VAR_c_MLMFPA_FCP_INUSE_RestartNetworkInterface_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_FCP_INUSE_RestartNetworkInterface' as a pointer */
#define PTR_c_MLMFPA_FCP_INUSE_RestartNetworkInterface_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_FCP_INUSE_RestartNetworkInterface {

	c_MLMFPA_FCP_INUSE_RestartNetworkInterface_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_FCP_INUSE_RestartNetworkInterface;
#define INIT_c_MLMFPA_FCP_INUSE_RestartNetworkInterface(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_FCP_INUSE_RestartNetworkInterface))
/*FRK03a*/
void FREE_c_MLMFPA_FCP_INUSE_RestartNetworkInterface(c_MLMFPA_FCP_INUSE_RestartNetworkInterface* sp);

/* Access member 'contents' of type 'c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck' as a variable reference */
#define VAR_c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck_contents(var) var

/* Access member 'contents' of type 'c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck' as a pointer */
#define PTR_c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck_contents(var) (&var)


/*-A----------------------------------*/
typedef struct _c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck {

	c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck_contents contents; /* ODY01a *//*GBD01b*/

}	c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck;
#define INIT_c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck(sp) ED_RESET_MEM ((sp), sizeof (c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck))
/*FRK03a*/
void FREE_c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck(c_MLMFPA_FCP_INUSE_RestartNetworkInterfaceAck* sp);

/* Access member 'TLV_Tag' of type 'c_GenericTLV_cs0063' as a variable reference */
#define VAR_c_GenericTLV_cs0063_TLV_Tag(var) var

/* Access member 'TLV_Tag' of type 'c_GenericTLV_cs0063' as a pointer */
#define PTR_c_GenericTLV_cs0063_TLV_Tag(var) (&var)

/* Access member 'TLV_Data' of type 'c_GenericTLV_cs0063' as a variable reference */
#define VAR_c_GenericTLV_cs0063_TLV_Data(var) var

/* Access member 'TLV_Data' of type 'c_GenericTLV_cs0063' as a pointer */
#define PTR_c_GenericTLV_cs0063_TLV_Data(var) (&var)

/* DEFINITION OF BINARY c_GenericTLV_cs0063_TLV_Data */
typedef struct _c_GenericTLV_cs0063_TLV_Data {
	ED_BYTE* value; /* Variable size; bits needed 64 */
	int usedBits;
} c_GenericTLV_cs0063_TLV_Data;
/* Binary allocation macro (dynamic version). If the binary string was already
	 allocated, it will be freed and reallocated. */
#define ALLOC_c_GenericTLV_cs0063_TLV_Data(sp,bits) EDAllocBinary (&((sp)->value), (unsigned)(bits), &((sp)->usedBits))



/*-A----------------------------------*/
typedef struct _c_GenericTLV_cs0063 {

	ED_LONG TLV_Tag; /* ODY01a *//*GBD01b*/
	c_GenericTLV_cs0063_TLV_Data TLV_Data; /* Static, variable size; bits needed 64 *//*GBD01b*/

}	c_GenericTLV_cs0063;
#define INIT_c_GenericTLV_cs0063(sp) ED_RESET_MEM ((sp), sizeof (c_GenericTLV_cs0063))
/*FRK03a*/
void FREE_c_GenericTLV_cs0063(c_GenericTLV_cs0063* sp);

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01'. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01'. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01'. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01'. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01'. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01'. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01'. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02'. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02(sequence, itemsToBeAdded) SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01'. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02'. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02(sequence, itemsToBeAdded) SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01'. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01'. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01'. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01'. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01'. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01'. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01'. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01'. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01'. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02'. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02(sequence, itemsToBeAdded) SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01'. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02'. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02(sequence, itemsToBeAdded) SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03'. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03 (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03(sequence, itemsToBeAdded) SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01'. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ATSupportedQoSProfiles_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01'. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ANSupportedQoSProfiles_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01'. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxLinkFlows_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01'. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_MaxReservations_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01'. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNSequenceLengthFwd_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01'. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersFwd_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01'. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNTimersRev_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01'. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02'. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02(sequence, itemsToBeAdded) SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationFwd_data01_data_data02 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01'. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02'. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02(sequence, itemsToBeAdded) SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNReservationRev_data01_data_data02 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01'. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestFwd_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01'. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSRequestRev_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01'. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseFwd_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01'. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKQoSResponseRev_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01'. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersFwd_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01'. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNFlowProtocolParametersRev_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01'. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersFwd_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01'. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_FlowNNRouteProtocolParametersRev_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01'. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02'. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02(sequence, itemsToBeAdded) SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSFlowIDAssociation_data01_data_data02 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01'. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01(sequence, itemsToBeAdded) SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02'. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02(sequence, itemsToBeAdded) SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03'. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03 (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03(sequence, itemsToBeAdded) SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_ReservationKKBCMCSProgramIDAssociation_data01_data_data02_data_data03 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Values'. */
int SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Values (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Values* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Values(sequence, itemsToBeAdded) SETITEMS_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_Values (sequence, (sequence)->items+itemsToBeAdded)

/* SETPRESENT commands for type 'c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex' */
void GLOB_SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex (c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex* sp, TPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex toBeSetPresent);
#define SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_NONE(sp) GLOB_SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_NONE)
#define GETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_NONE(sp) ((sp)->Present == U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_NONE)
#define SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedQoSProfiles(sp) GLOB_SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedQoSProfiles)
#define GETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedQoSProfiles(sp) ((sp)->Present == U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedQoSProfiles)
#define SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ANSupportedQoSProfiles(sp) GLOB_SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ANSupportedQoSProfiles)
#define GETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ANSupportedQoSProfiles(sp) ((sp)->Present == U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ANSupportedQoSProfiles)
#define SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_MaxLinkFlows(sp) GLOB_SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_MaxLinkFlows)
#define GETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_MaxLinkFlows(sp) ((sp)->Present == U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_MaxLinkFlows)
#define SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_MaxReservations(sp) GLOB_SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_MaxReservations)
#define GETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_MaxReservations(sp) ((sp)->Present == U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_MaxReservations)
#define SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersFwd(sp) GLOB_SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersFwd)
#define GETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersFwd(sp) ((sp)->Present == U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersFwd)
#define SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersRev(sp) GLOB_SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersRev)
#define GETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersRev(sp) ((sp)->Present == U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersRev)
#define SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationFwd(sp) GLOB_SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationFwd)
#define GETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationFwd(sp) ((sp)->Present == U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationFwd)
#define SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationRev(sp) GLOB_SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationRev)
#define GETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationRev(sp) ((sp)->Present == U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationRev)
#define SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestFwd(sp) GLOB_SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestFwd)
#define GETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestFwd(sp) ((sp)->Present == U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestFwd)
#define SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestRev(sp) GLOB_SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestRev)
#define GETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestRev(sp) ((sp)->Present == U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestRev)
#define SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseFwd(sp) GLOB_SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseFwd)
#define GETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseFwd(sp) ((sp)->Present == U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseFwd)
#define SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseRev(sp) GLOB_SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseRev)
#define GETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseRev(sp) ((sp)->Present == U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseRev)
#define SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersFwd(sp) GLOB_SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersFwd)
#define GETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersFwd(sp) ((sp)->Present == U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersFwd)
#define SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersRev(sp) GLOB_SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersRev)
#define GETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersRev(sp) ((sp)->Present == U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersRev)
#define SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersFwd(sp) GLOB_SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersFwd)
#define GETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersFwd(sp) ((sp)->Present == U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersFwd)
#define SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersRev(sp) GLOB_SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersRev)
#define GETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersRev(sp) ((sp)->Present == U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersRev)
#define SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedFlowProtocolParametersPP(sp) GLOB_SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedFlowProtocolParametersPP)
#define GETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedFlowProtocolParametersPP(sp) ((sp)->Present == U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedFlowProtocolParametersPP)
#define SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedRouteProtocolParametersPP(sp) GLOB_SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedRouteProtocolParametersPP)
#define GETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedRouteProtocolParametersPP(sp) ((sp)->Present == U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedRouteProtocolParametersPP)
#define SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSFlowIDAssociation(sp) GLOB_SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSFlowIDAssociation)
#define GETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSFlowIDAssociation(sp) ((sp)->Present == U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSFlowIDAssociation)
#define SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSProgramIDAssociation(sp) GLOB_SETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSProgramIDAssociation)
#define GETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSProgramIDAssociation(sp) ((sp)->Present == U_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSProgramIDAssociation)
#define GETPRESENT_c_RPD_Enhanced_Multi_Flow_Packet_Application_Attributes_complex(sp) ((sp)->Present)

/* SETITEMS/ADDITEMS commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Values'. */
int SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Values (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Values* sequence, int desiredItems);
#define ADDITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Values(sequence, itemsToBeAdded) SETITEMS_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_Values (sequence, (sequence)->items+itemsToBeAdded)

/* SETPRESENT commands for type 'c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex' */
void GLOB_SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex (c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex* sp, TPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex toBeSetPresent);
#define SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_NONE(sp) GLOB_SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_NONE)
#define GETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_NONE(sp) ((sp)->Present == U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_NONE)
#define SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedQoSProfiles(sp) GLOB_SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedQoSProfiles)
#define GETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedQoSProfiles(sp) ((sp)->Present == U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedQoSProfiles)
#define SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ANSupportedQoSProfiles(sp) GLOB_SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ANSupportedQoSProfiles)
#define GETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ANSupportedQoSProfiles(sp) ((sp)->Present == U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ANSupportedQoSProfiles)
#define SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_MaxLinkFlows(sp) GLOB_SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_MaxLinkFlows)
#define GETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_MaxLinkFlows(sp) ((sp)->Present == U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_MaxLinkFlows)
#define SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_MaxReservations(sp) GLOB_SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_MaxReservations)
#define GETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_MaxReservations(sp) ((sp)->Present == U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_MaxReservations)
#define SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNSequenceLengthFwd(sp) GLOB_SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNSequenceLengthFwd)
#define GETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNSequenceLengthFwd(sp) ((sp)->Present == U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNSequenceLengthFwd)
#define SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersFwd(sp) GLOB_SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersFwd)
#define GETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersFwd(sp) ((sp)->Present == U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersFwd)
#define SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersRev(sp) GLOB_SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersRev)
#define GETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersRev(sp) ((sp)->Present == U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNTimersRev)
#define SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationFwd(sp) GLOB_SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationFwd)
#define GETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationFwd(sp) ((sp)->Present == U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationFwd)
#define SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationRev(sp) GLOB_SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationRev)
#define GETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationRev(sp) ((sp)->Present == U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNReservationRev)
#define SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestFwd(sp) GLOB_SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestFwd)
#define GETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestFwd(sp) ((sp)->Present == U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestFwd)
#define SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestRev(sp) GLOB_SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestRev)
#define GETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestRev(sp) ((sp)->Present == U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSRequestRev)
#define SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseFwd(sp) GLOB_SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseFwd)
#define GETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseFwd(sp) ((sp)->Present == U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseFwd)
#define SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseRev(sp) GLOB_SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseRev)
#define GETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseRev(sp) ((sp)->Present == U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKQoSResponseRev)
#define SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersFwd(sp) GLOB_SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersFwd)
#define GETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersFwd(sp) ((sp)->Present == U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersFwd)
#define SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersRev(sp) GLOB_SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersRev)
#define GETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersRev(sp) ((sp)->Present == U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNFlowProtocolParametersRev)
#define SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersFwd(sp) GLOB_SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersFwd)
#define GETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersFwd(sp) ((sp)->Present == U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersFwd)
#define SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersRev(sp) GLOB_SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersRev)
#define GETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersRev(sp) ((sp)->Present == U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_FlowNNRouteProtocolParametersRev)
#define SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedFlowProtocolParametersPP(sp) GLOB_SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedFlowProtocolParametersPP)
#define GETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedFlowProtocolParametersPP(sp) ((sp)->Present == U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedFlowProtocolParametersPP)
#define SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedRouteProtocolParametersPP(sp) GLOB_SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedRouteProtocolParametersPP)
#define GETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedRouteProtocolParametersPP(sp) ((sp)->Present == U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ATSupportedRouteProtocolParametersPP)
#define SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSFlowIDAssociation(sp) GLOB_SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSFlowIDAssociation)
#define GETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSFlowIDAssociation(sp) ((sp)->Present == U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSFlowIDAssociation)
#define SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSProgramIDAssociation(sp) GLOB_SETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex(sp, U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSProgramIDAssociation)
#define GETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSProgramIDAssociation(sp) ((sp)->Present == U_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex_ReservationKKBCMCSProgramIDAssociation)
#define GETPRESENT_c_RPD_Multi_link_Multi_Flow_Packet_Application_Attributes_complex(sp) ((sp)->Present)

/* SETITEMS/ADDITEMS commands for type 'c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01'. */
int SETITEMS_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01 (c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_EMFPKA_EMFPA_INCFG_ConfigurationRequest_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01'. */
int SETITEMS_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01 (c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_EMFPKA_EMFPA_INCFG_ConfigurationResponse_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_EMFPKA_RLP_INUSE_Nak_contents_data01'. */
int SETITEMS_c_EMFPKA_RLP_INUSE_Nak_contents_data01 (c_EMFPKA_RLP_INUSE_Nak_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_EMFPKA_RLP_INUSE_Nak_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_EMFPKA_RLP_INUSE_Nak_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01'. */
int SETITEMS_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01 (c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data_EmergencyIndication(sp,present) ((sp)->EmergencyIndication_Present = present)
#define GETPRESENT_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data_EmergencyIndication(sp) ((sp)->EmergencyIndication_Present)
#define SETPRESENT_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data_ReservationQueuingReq(sp,present) ((sp)->ReservationQueuingReq_Present = present)
#define GETPRESENT_c_EMFPKA_RLP_INUSE_ReservationOnRequest_contents_data01_data_ReservationQueuingReq(sp) ((sp)->ReservationQueuingReq_Present)
/* SETITEMS/ADDITEMS commands for type 'c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01'. */
int SETITEMS_c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01 (c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_EMFPKA_RLP_INUSE_ReservationOffRequest_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01'. */
int SETITEMS_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01 (c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02'. */
int SETITEMS_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02 (c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02* sequence, int desiredItems);
#define ADDITEMS_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02(sequence, itemsToBeAdded) SETITEMS_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02_data_RejectCode(sp,present) ((sp)->RejectCode_Present = present)
#define GETPRESENT_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02_data_RejectCode(sp) ((sp)->RejectCode_Present)
#define SETPRESENT_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02_data_PendingDuration(sp,present) ((sp)->PendingDuration_Present = present)
#define GETPRESENT_c_EMFPKA_RLP_INUSE_ReservationReject_contents_data01_data_data02_data_PendingDuration(sp) ((sp)->PendingDuration_Present)
/* SETITEMS/ADDITEMS commands for type 'c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01'. */
int SETITEMS_c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01 (c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_EMFPKA_RLP_INUSE_RevReservationOn_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01'. */
int SETITEMS_c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01 (c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_EMFPKA_RLP_INUSE_RevReservationOff_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01'. */
int SETITEMS_c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01 (c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_EMFPKA_RLP_INUSE_FwdReservationOff_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01'. */
int SETITEMS_c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01 (c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_EMFPKA_RLP_INUSE_FwdReservationOn_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01'. */
int SETITEMS_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01 (c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_EMFPKA_RLP_INUSE_AttributeUpdateRequest_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01'. */
int SETITEMS_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01 (c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_MLMFPA_MMFPA_INCFG_ConfigurationRequest_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01'. */
int SETITEMS_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01 (c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_MLMFPA_MMFPA_INCFG_ConfigurationResponse_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01'. */
int SETITEMS_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01 (c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

void SETPRESENT_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data_LeadingEdge (c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data* sp, ED_BOOLEAN present);
#define GETPRESENT_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data01_data_LeadingEdge(sp) ((sp)->LeadingEdge_Present)
/* SETITEMS/ADDITEMS commands for type 'c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02'. */
int SETITEMS_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02 (c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02* sequence, int desiredItems);
#define ADDITEMS_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02(sequence, itemsToBeAdded) SETITEMS_c_MLMFPA_SRP_INUSE_MultiLinkNak_contents_data02 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01'. */
int SETITEMS_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01 (c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data_EmergencyIndication(sp,present) ((sp)->EmergencyIndication_Present = present)
#define GETPRESENT_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data_EmergencyIndication(sp) ((sp)->EmergencyIndication_Present)
#define SETPRESENT_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data_ReservationQueuingReq(sp,present) ((sp)->ReservationQueuingReq_Present = present)
#define GETPRESENT_c_MLMFPA_SRP_INUSE_ReservationOnRequest_contents_data01_data_ReservationQueuingReq(sp) ((sp)->ReservationQueuingReq_Present)
/* SETITEMS/ADDITEMS commands for type 'c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01'. */
int SETITEMS_c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01 (c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_MLMFPA_SRP_INUSE_ReservationOffRequest_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01'. */
int SETITEMS_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01 (c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02'. */
int SETITEMS_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02 (c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02* sequence, int desiredItems);
#define ADDITEMS_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02(sequence, itemsToBeAdded) SETITEMS_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02 (sequence, (sequence)->items+itemsToBeAdded)

#define SETPRESENT_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02_data_RejectCode(sp,present) ((sp)->RejectCode_Present = present)
#define GETPRESENT_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02_data_RejectCode(sp) ((sp)->RejectCode_Present)
#define SETPRESENT_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02_data_PendingDuration(sp,present) ((sp)->PendingDuration_Present = present)
#define GETPRESENT_c_MLMFPA_SRP_INUSE_ReservationReject_contents_data01_data_data02_data_PendingDuration(sp) ((sp)->PendingDuration_Present)
/* SETITEMS/ADDITEMS commands for type 'c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01'. */
int SETITEMS_c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01 (c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_MLMFPA_SRP_INUSE_RevReservationOn_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01'. */
int SETITEMS_c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01 (c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_MLMFPA_SRP_INUSE_RevReservationOff_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01'. */
int SETITEMS_c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01 (c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_MLMFPA_SRP_INUSE_FwdReservationOff_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01'. */
int SETITEMS_c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01 (c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_MLMFPA_SRP_INUSE_FwdReservationOn_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01'. */
int SETITEMS_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01 (c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_MLMFPA_SRP_INUSE_AttributeUpdateRequest_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

/* SETITEMS/ADDITEMS commands for type 'c_MLMFPA_SRP_INUSE_Nak_contents_data01'. */
int SETITEMS_c_MLMFPA_SRP_INUSE_Nak_contents_data01 (c_MLMFPA_SRP_INUSE_Nak_contents_data01* sequence, int desiredItems);
#define ADDITEMS_c_MLMFPA_SRP_INUSE_Nak_contents_data01(sequence, itemsToBeAdded) SETITEMS_c_MLMFPA_SRP_INUSE_Nak_contents_data01 (sequence, (sequence)->items+itemsToBeAdded)

#ifdef __cplusplus
}
#endif

#endif

