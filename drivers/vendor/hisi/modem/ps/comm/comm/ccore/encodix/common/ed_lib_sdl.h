/*******************************************************************************
  ed_lib_sdl.h  Developed by Dafocus - http://www.dafocus.com/
*******************************************************************************/
#ifndef __ED_LIB_SDL_H
#define __ED_LIB_SDL_H
#include "scttypes.h"

/*------------------------------------------------------------------------------
	Converts a Octet_String into a char buffer. Returns number of bits used
	into the destination buffer.
	Given Octet_String is freed if not assigned.
	MaxBufSize is in bits.
------------------------------------------------------------------------------*/
int ED_Convert_OctetString_to_Buffer (char* Destination, SDL_Octet_String* Source, int MaxBufSize);

/*------------------------------------------------------------------------------
	Converts a char buffer into an Octet_String. 
	Given Octet_String is freed if not assigned.
	MaxBufSize is in bits.
------------------------------------------------------------------------------*/
void ED_Convert_Buffer_to_OctetString (SDL_Octet_String* Destination, const char* Source, int SourceLen);
#endif //__ED_LIB_SDL_H
