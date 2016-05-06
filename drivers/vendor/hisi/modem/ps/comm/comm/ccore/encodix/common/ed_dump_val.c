/*******************************************************************************
  ed_dump_val.c  Developed by Dafocus - http://www.dafocus.com/
*******************************************************************************/
#include "ed_dump_val.h"
#include <stdio.h>

/*lint -e440*/
/*lint -e701*/

/*------------------------------------------------------------------------------
	Function which prints an integer
------------------------------------------------------------------------------*/
void ED_Dump_Integer (TEDOStream* OStream, int Value)
{
	char Buf [30];
	sprintf (Buf, "%d", Value);
	OStream->WriteString (OStream, Buf);
}

/*------------------------------------------------------------------------------
	Function which prints a boolean
------------------------------------------------------------------------------*/
void ED_Dump_Boolean (TEDOStream* OStream, ED_BOOLEAN Value)
{
	if (Value) {
		OStream->WriteString (OStream, "TRUE");
	}
	else {
		OStream->WriteString (OStream, "FALSE");
	}
}


/*------------------------------------------------------------------------------
	Function which prints a boolean
------------------------------------------------------------------------------*/
void ED_Dump_Octet (TEDOStream* OStream, ED_BYTE Value)
{
	char Buf [10];
	sprintf (Buf, "0x%02x", (unsigned)((unsigned char)Value));
	OStream->WriteString (OStream, Buf);
}

/*------------------------------------------------------------------------------
	Function which prints a boolean
------------------------------------------------------------------------------*/
void ED_Dump_Binary (TEDOStream* OStream, const ED_BYTE* Data, int Bits)
{
	int i, j;
	char Buffer [80];

	sprintf (Buffer, "Binary data - %d bits\n", Bits);
	OStream->WriteString (OStream, Buffer);
	for (i=0; Bits>0; i++) {
		sprintf (Buffer, "0x%08X: 0x%02X (%03d) - ", (unsigned int)i, (unsigned int)((unsigned char)(Data[i])), (unsigned int)((unsigned char)(Data[i])));
		OStream->WriteString (OStream, Buffer);
		for (j=0; j<8; j++) {
			if (Bits == 0) break;
			if (Data[i] & (1 << (7-j))) OStream->Write (OStream, '1');
			else OStream->Write (OStream, '0');
			Bits --;
		}
		OStream->Write (OStream, '\n');
	}
}

/*------------------------------------------------------------------------------
	Function which prints a boolean
------------------------------------------------------------------------------*/
void ED_Dump_Struct_Begin (TEDOStream* OStream, const char* StructName)
{
	OStream->WriteString (OStream, StructName);
	OStream->WriteString (OStream, " {\n");
	OStream->SetIndent (OStream, 1);
}

/*------------------------------------------------------------------------------
	Function which prints a boolean
------------------------------------------------------------------------------*/
void ED_Dump_Struct_End (TEDOStream* OStream, const char* StructName)
{
	ED_WARNING_REMOVER(StructName);
	OStream->SetIndent (OStream, -1);
	OStream->ForceCr (OStream);
	OStream->WriteString (OStream, "}\n");
}

/*------------------------------------------------------------------------------
	This is invoked before printing a field of a structure.
------------------------------------------------------------------------------*/
void ED_Dump_Struct_Begin_Field (TEDOStream* OStream, const char* StructName, const char* FieldName)
{
	ED_WARNING_REMOVER(StructName);
	OStream->WriteString (OStream, FieldName);
	OStream->WriteString (OStream, ": ");
	OStream->SetIndent (OStream, 1);
}

/*------------------------------------------------------------------------------
	This is invoked after printing a field of a structure.
------------------------------------------------------------------------------*/
void ED_Dump_Struct_End_Field (TEDOStream* OStream, const char* StructName, const char* FieldName)
{
	ED_WARNING_REMOVER(FieldName);
	ED_WARNING_REMOVER(StructName);
	OStream->SetIndent (OStream, -1);
	OStream->ForceCr (OStream);
}

/*------------------------------------------------------------------------------
	Function which prints the beginning of an union
------------------------------------------------------------------------------*/
void ED_Dump_Union_Begin (TEDOStream* OStream, const char* UnionName, const char* ActiveField)
{
	OStream->WriteString (OStream, UnionName);
	OStream->WriteString (OStream, ".");
	OStream->WriteString (OStream, ActiveField);
	OStream->WriteString (OStream, " {\n");
	OStream->SetIndent (OStream, 1);
}

/*------------------------------------------------------------------------------
	Function which prints the end of an union
------------------------------------------------------------------------------*/
void ED_Dump_Union_End (TEDOStream* OStream, const char* UnionName, const char* ActiveField)
{
	ED_WARNING_REMOVER(UnionName);
	ED_WARNING_REMOVER(ActiveField);
	OStream->SetIndent (OStream, -1);
	OStream->ForceCr (OStream);
	OStream->WriteString (OStream, "}\n");
}

/*------------------------------------------------------------------------------
	Function which prints a missing optional field
------------------------------------------------------------------------------*/
void ED_Dump_Not_Present (TEDOStream* OStream)
{
	OStream->WriteString (OStream, "NOT PRESENT");
}

/*------------------------------------------------------------------------------
	Function which prints a void value. It is used only to mark that an optional
	void element is present.
------------------------------------------------------------------------------*/
void ED_Dump_Void_Present (TEDOStream* OStream)
{
	OStream->WriteString (OStream, "PRESENT");
}

/*------------------------------------------------------------------------------
	Function which prints the beginning of a sequence
------------------------------------------------------------------------------*/
void ED_Dump_Sequence_Begin (TEDOStream* OStream, const char* SequenceName, int Items)
{
	char Buffer [30];
	OStream->WriteString (OStream, "SEQUENCE ");
	OStream->WriteString (OStream, SequenceName);
	if (Items > 0) {
		sprintf (Buffer, " %d items {\n", Items);
		OStream->WriteString (OStream, Buffer);
	}
	else {
		OStream->WriteString (OStream, " EMPTY\n");
	}
	OStream->SetIndent (OStream, 1);
}
/*------------------------------------------------------------------------------
	Function which prints the end of a sequence
------------------------------------------------------------------------------*/
void ED_Dump_Sequence_End (TEDOStream* OStream, const char* SequenceName, int Items)
{
	ED_WARNING_REMOVER(SequenceName);
	OStream->SetIndent (OStream, -1);
	if (Items > 0) {
		OStream->ForceCr (OStream);
		OStream->WriteString (OStream, "}\n");
	}
}

/*------------------------------------------------------------------------------
	This is invoked before printing a field of a sequence.
------------------------------------------------------------------------------*/
void ED_Dump_Sequence_Begin_Field (TEDOStream* OStream, const char* SequenceName, int Item, int Items)
{
	char Buffer [30];
	ED_WARNING_REMOVER(SequenceName);
	ED_WARNING_REMOVER(Items);
	sprintf (Buffer, "Item %3d: ", Item);
	OStream->ForceCr (OStream);
	OStream->WriteString (OStream, Buffer);
	OStream->SetIndent (OStream, 1);
}

/*------------------------------------------------------------------------------
	This is invoked after printing a field of a sequence.
------------------------------------------------------------------------------*/
void ED_Dump_Sequence_End_Field (TEDOStream* OStream, const char* SequenceName, int Item, int Items)
{
	ED_WARNING_REMOVER(SequenceName);
	ED_WARNING_REMOVER(Items);
	ED_WARNING_REMOVER(Item);
	OStream->SetIndent (OStream, -1);
	OStream->ForceCr (OStream);
}

/*lint +e440*/
/*lint +e701*/


