/*******************************************************************************
  ed_dump_file.c  Developed by Dafocus - http://www.dafocus.com/
*******************************************************************************/
#include "ed_dump_file.h"

/*------------------------------------------------------------------------------
	CONSTRUCTOR
	Returns 0 if OK.
------------------------------------------------------------------------------*/
int TEDOStreamFile_Construct (TEDOStreamFile* This, const char* FileName, const char* FileMode)
{
	int ret = TEDOStreamFile_Construct_Existing (This, NULL);
	if (ret) return ret;
	This->NeedsClose = 1;

	This->File = fopen (FileName, FileMode);
	return (This->File == NULL);
}

/*------------------------------------------------------------------------------
	CONSTRUCTOR
	Associates this file to an existing one (it can be used, for example, with
	stdout, stderr or any other file already open).
	Returns 0 if OK.
------------------------------------------------------------------------------*/
int TEDOStreamFile_Construct_Existing (TEDOStreamFile* This, FILE* ExistingFile)
{
	int ret;
	ret = TEDOStream_Construct (&This->Base);

	This->Base.Write = (void(*)(struct SEDOStream*, char)) TEDOStreamFile_Write;
	This->Base.SetIndent = (void(*)(struct SEDOStream*, int)) TEDOStreamFile_SetIndent;
	This->Base.ForceCr = (void(*)(struct SEDOStream*)) TEDOStreamFile_ForceCr;
	This->Indent = 0;
	This->File = ExistingFile;
	This->LastWasCR = 1;
	if (ret) return ret;
	This->NeedsClose = 0;

	return 0;
}


/*------------------------------------------------------------------------------
	DESTRUCTOR
------------------------------------------------------------------------------*/
void TEDOStreamFile_Destruct (TEDOStreamFile* This)
{
	if ((This->File != NULL) && (This->NeedsClose)) {
		fclose (This->File);
		This->File = NULL;
	}

	/* Finally call base class destructor */
	TEDOStream_Destruct (&This->Base);
}


/*==============================================================================
	Internal virtual methods implementation
==============================================================================*/
/*----------------------------------------------------------------------------
	Virtual method - Writes a single character on the stream. If '\n' is 
	printed, then next line will be indented as specified with "SetIndent"
----------------------------------------------------------------------------*/
void TEDOStreamFile_Write (TEDOStreamFile* This, char Char)
{
	if (This->File == NULL) {
		/* File is closed! */
		return;
	}

	if (This->LastWasCR) {
		int i;
		for (i=0; i<This->Indent; i++) {
			fputs ("  ", This->File);
		}
		This->LastWasCR = 0;
	}
	fputc (Char, This->File);
	if (Char == '\n') {
		This->LastWasCR = 1;
	}
}

/*----------------------------------------------------------------------------
	Virtual method - Sets an indent level for the text being written.
----------------------------------------------------------------------------*/
void TEDOStreamFile_SetIndent (TEDOStreamFile* This, int IndentLevel)
{
	This->Indent += IndentLevel;
}

/*----------------------------------------------------------------------------
	Virtual method - Sets an indent level for the text being written.
----------------------------------------------------------------------------*/
void TEDOStreamFile_ForceCr (TEDOStreamFile* This)
{
	if (!(This->LastWasCR)) This->Base.Write ((TEDOStream*)This, '\n');
}
