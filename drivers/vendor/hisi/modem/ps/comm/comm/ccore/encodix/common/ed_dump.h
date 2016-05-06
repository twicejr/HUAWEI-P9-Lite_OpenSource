/*******************************************************************************
  ed_dump.h  Developed by Dafocus - http://www.dafocus.com/
*******************************************************************************/
#ifndef __ED_DUMP_H
#define __ED_DUMP_H
#ifdef __cplusplus
extern "C" {
#endif
/*------------------------------------------------------------------------------
	This structure defines the basic class for a data dumper. This is a C
	implementation of a C++ abstract class.
	The goal of this class is to define an abstract interface to an object
	able to dump ASCII characters on a device.
------------------------------------------------------------------------------*/
typedef struct SEDOStream {
	/*----------------------------------------------------------------------------
		Virtual method - Writes a single character on the stream. If '\n' is 
		printed, then next line will be indented as specified with "SetIndent"
	----------------------------------------------------------------------------*/
	void (*Write) (struct SEDOStream* This, char Char);

	/*----------------------------------------------------------------------------
		Virtual method - Writes an ASCIIZ string. It has a default implementation
		which calles "Write" for every character.
	----------------------------------------------------------------------------*/
	void (*WriteString) (struct SEDOStream* This, const char* ASCIIZString);

	/*----------------------------------------------------------------------------
		Virtual method - Sets an indent level for the text being written.
		With +n, indent level is increased of n, -n decreases it.
	----------------------------------------------------------------------------*/
	void (*SetIndent) (struct SEDOStream* This, int IndentLevel);

	/*----------------------------------------------------------------------------
		Forces a CR if not already issued
	----------------------------------------------------------------------------*/
	void (*ForceCr) (struct SEDOStream* This);

} TEDOStream;

/*------------------------------------------------------------------------------
	CONSTRUCTOR
	Returns 0 if OK.
------------------------------------------------------------------------------*/
int TEDOStream_Construct (TEDOStream* This);

/*------------------------------------------------------------------------------
	DESTRUCTOR
------------------------------------------------------------------------------*/
void TEDOStream_Destruct (TEDOStream* This);

/*------------------------------------------------------------------------------
	WriteString
------------------------------------------------------------------------------*/
void TEDOStream_WriteString (struct SEDOStream* This, const char* ASCIIZString);

#ifdef __cplusplus
}
#endif
#endif
