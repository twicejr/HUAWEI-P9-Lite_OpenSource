/*******************************************************************************
  ed_dump_val.h  Developed by Dafocus - http://www.dafocus.com/
*******************************************************************************/
#ifndef __ED_DUMP_VAL_H
#define __ED_DUMP_VAL_H
#include "ed_dump.h"
#include "ed_lib.h"
#ifdef __cplusplus
extern "C" {
#endif
/*------------------------------------------------------------------------------
	Function which prints an integer
------------------------------------------------------------------------------*/
void ED_Dump_Integer (TEDOStream* OStream, int Value);

/*------------------------------------------------------------------------------
	Function which prints a boolean
------------------------------------------------------------------------------*/
void ED_Dump_Boolean (TEDOStream* OStream, ED_BOOLEAN Value);

/*------------------------------------------------------------------------------
	Function which prints a boolean
------------------------------------------------------------------------------*/
void ED_Dump_Octet (TEDOStream* OStream, ED_BYTE Value);

/*------------------------------------------------------------------------------
	Function which prints a boolean
------------------------------------------------------------------------------*/
void ED_Dump_Binary (TEDOStream* OStream, const ED_BYTE* Data, int Bits);

/*------------------------------------------------------------------------------
	Function which prints a boolean
------------------------------------------------------------------------------*/
void ED_Dump_Struct_Begin (TEDOStream* OStream, const char* StructName);

/*------------------------------------------------------------------------------
	Function which prints a boolean
------------------------------------------------------------------------------*/
void ED_Dump_Struct_End (TEDOStream* OStream, const char* StructName);

/*------------------------------------------------------------------------------
	This is invoked before printing a field of a structure.
------------------------------------------------------------------------------*/
void ED_Dump_Struct_Begin_Field (TEDOStream* OStream, const char* StructName, const char* FieldName);

/*------------------------------------------------------------------------------
	This is invoked after printing a field of a structure.
------------------------------------------------------------------------------*/
void ED_Dump_Struct_End_Field (TEDOStream* OStream, const char* StructName, const char* FieldName);

/*------------------------------------------------------------------------------
	Function which prints the beginning of an union
------------------------------------------------------------------------------*/
void ED_Dump_Union_Begin (TEDOStream* OStream, const char* UnionName, const char* ActiveField);

/*------------------------------------------------------------------------------
	Function which prints the end of an union
------------------------------------------------------------------------------*/
void ED_Dump_Union_End (TEDOStream* OStream, const char* UnionName, const char* ActiveField);

/*------------------------------------------------------------------------------
	Function which prints a missing optional field
------------------------------------------------------------------------------*/
void ED_Dump_Not_Present (TEDOStream* OStream);

/*------------------------------------------------------------------------------
	Function which prints a void value. It is used only to mark that an optional
	void element is present.
------------------------------------------------------------------------------*/
void ED_Dump_Void_Present (TEDOStream* OStream);

/*------------------------------------------------------------------------------
	Function which prints the beginning of a sequence
------------------------------------------------------------------------------*/
void ED_Dump_Sequence_Begin (TEDOStream* OStream, const char* SequenceName, int Items);

/*------------------------------------------------------------------------------
	Function which prints the end of a sequence
------------------------------------------------------------------------------*/
void ED_Dump_Sequence_End (TEDOStream* OStream, const char* SequenceName, int Items);

/*------------------------------------------------------------------------------
	This is invoked before printing a field of a sequence.
------------------------------------------------------------------------------*/
void ED_Dump_Sequence_Begin_Field (TEDOStream* OStream, const char* SequenceName, int Item, int Items);

/*------------------------------------------------------------------------------
	This is invoked after printing a field of a sequence.
------------------------------------------------------------------------------*/
void ED_Dump_Sequence_End_Field (TEDOStream* OStream, const char* SequenceName, int Item, int Items);

#ifdef __cplusplus
};
#endif
#endif
