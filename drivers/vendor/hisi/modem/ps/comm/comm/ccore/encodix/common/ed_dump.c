/*******************************************************************************
  ed_dump.c  Developed by Dafocus - http://www.dafocus.com/
*******************************************************************************/
#include "ed_dump.h"
#include "ed_lib.h"
#include <stdlib.h>

/*------------------------------------------------------------------------------
	CONSTRUCTOR
	Returns 0 if OK.
------------------------------------------------------------------------------*/
int TEDOStream_Construct (TEDOStream* This)
{
	This->Write = NULL;
	This->SetIndent = NULL;
	This->WriteString = TEDOStream_WriteString;
	This->ForceCr = NULL;
	return 0;
}

/*------------------------------------------------------------------------------
	DESTRUCTOR
------------------------------------------------------------------------------*/
void TEDOStream_Destruct (TEDOStream* This)
{
	ED_WARNING_REMOVER (This);
}

/*------------------------------------------------------------------------------
	WriteString
------------------------------------------------------------------------------*/
void TEDOStream_WriteString (struct SEDOStream* This, const char* ASCIIZString)
{
	for (; *ASCIIZString; ASCIIZString++) {
		This->Write (This, *ASCIIZString);
	}
}

