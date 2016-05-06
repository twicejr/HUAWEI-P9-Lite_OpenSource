/*******************************************************************************
  ed_dump_file.h  Developed by Dafocus - http://www.dafocus.com/
*******************************************************************************/
#ifndef __ED_DUMP_FILE_H
#define __ED_DUMP_FILE_H
#include "ed_dump.h"
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------
	Implements a SEDOStream using a file
------------------------------------------------------------------------------*/
typedef struct SEDOStreamFile {
	/*----------------------------------------------------------------------------
		Base class
	----------------------------------------------------------------------------*/
	TEDOStream Base;

	/*----------------------------------------------------------------------------
		Associated file
	----------------------------------------------------------------------------*/
	FILE* File;

	/*----------------------------------------------------------------------------
		Current indent
	----------------------------------------------------------------------------*/
	int Indent;

	/*----------------------------------------------------------------------------
		Remembers if last thing we printed was a '\n'. This means that next thing
		we have to do is to print the current indent
	----------------------------------------------------------------------------*/
	int LastWasCR;

	/*----------------------------------------------------------------------------
		Remembers whether this file is an external file (like stdout, stderr)
		that doens't have to be closed.
	----------------------------------------------------------------------------*/
	int NeedsClose;

} TEDOStreamFile;

/*------------------------------------------------------------------------------
	CONSTRUCTOR
	Returns 0 if OK.
------------------------------------------------------------------------------*/
int TEDOStreamFile_Construct (TEDOStreamFile* This, const char* FileName, const char* FileMode);

/*------------------------------------------------------------------------------
	CONSTRUCTOR
	Associates this file to an existing one (it can be used, for example, with
	stdout, stderr or any other file already open).
	Returns 0 if OK.
------------------------------------------------------------------------------*/
int TEDOStreamFile_Construct_Existing (TEDOStreamFile* This, FILE* ExistingFile);

/*------------------------------------------------------------------------------
	DESTRUCTOR
------------------------------------------------------------------------------*/
void TEDOStreamFile_Destruct (TEDOStreamFile* This);


/*==============================================================================
	Internal virtual methods implementation
==============================================================================*/
/*----------------------------------------------------------------------------
	Virtual method - Writes a single character on the stream. If '\n' is 
	printed, then next line will be indented as specified with "SetIndent"
----------------------------------------------------------------------------*/
void TEDOStreamFile_Write (TEDOStreamFile* This, char Char);

/*----------------------------------------------------------------------------
	Virtual method - Sets an indent level for the text being written.
----------------------------------------------------------------------------*/
void TEDOStreamFile_SetIndent (TEDOStreamFile* This, int IndentLevel);

/*----------------------------------------------------------------------------
	Virtual method - Sets an indent level for the text being written.
----------------------------------------------------------------------------*/
void TEDOStreamFile_ForceCr (TEDOStreamFile* This);
#ifdef __cplusplus
}
#endif
#endif
