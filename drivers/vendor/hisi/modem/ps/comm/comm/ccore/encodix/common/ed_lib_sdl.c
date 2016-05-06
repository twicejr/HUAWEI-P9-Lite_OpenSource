/*******************************************************************************
  ed_lib_sdl.c  Developed by Dafocus - http://www.dafocus.com/
*******************************************************************************/
#include "ed_lib_sdl.h"
#define POS (1 << (7-(i & 7)))
#define SRC ((unsigned char)(Source[i >> 3]))
#define DST ((unsigned char)(Destination[i >> 3]))

/*------------------------------------------------------------------------------
	Converts a Octet_String into a char buffer. Returns number of bits used
	into the destination buffer.
	Given Octet_String is freed if not assigned.
------------------------------------------------------------------------------*/
int ED_Convert_OctetString_to_Buffer (char* Destination, SDL_Octet_String* Source, int MaxBufSize)
{
	int i;
	int Len;
	MaxBufSize = (MaxBufSize+7) >> 3;
	Len = (MaxBufSize < Source->Length? MaxBufSize : Source->Length);
	for (i=0; i<Len; i++) {
		Destination [i] = Source->Bits [i];
	}

	//if (!Source->IsAssigned) yFree_SDL_Octet_String ((void**)Source);

	return Len<<3;
}

/*------------------------------------------------------------------------------
	Converts a char buffer into an Octet_String. 
	Given Octet_String is freed if not assigned.
	MaxBufSize is in bits.
------------------------------------------------------------------------------*/
void ED_Convert_Buffer_to_OctetString (SDL_Octet_String* Destination, const char* Source, int SourceLen)
{
	int i;
	//if (!Destination->IsAssigned) yFree_SDL_Octet_String ((void**)Destination);
	Destination->IsAssigned = 0;
	Destination->Length = (SourceLen+7) >> 3;
	Destination->Bits = (unsigned char *)XALLOC((xptrint)(Destination->Length), xSrtN_SDL_Bit_String);

	for (i=0; i<Destination->Length; i++) {
		Destination->Bits [i] = Source [i];
	}
}
#if 0
/*------------------------------------------------------------------------------
	Converts a Octet_String into a char buffer. Returns number of bits used
	into the destination buffer.
	Given Octet_String is freed if not assigned.
------------------------------------------------------------------------------*/
int ED_Convert_BinString_to_Buffer (char* Destination, SDL_Binary_String* Source, int MaxBufSize)
{
	int i;
	int Len = (MaxBufSize < Source->Length? MaxBufSize : Source->Length);

	for (i=0; i<Len; i++) {
		if (Source->Bits [i]) DST |= POS;
		else DST &= ~POS;
	}

	if (!Source->IsAssigned) yFree_SDL_Octet_String ((void**)Source);

	return Len;
}

/*------------------------------------------------------------------------------
	Converts a char buffer into an Octet_String. 
	Given Octet_String is freed if not assigned.
	MaxBufSize is in bits.
------------------------------------------------------------------------------*/
void ED_Convert_Buffer_to_BinString (SDL_Binary_String* Destination, const char* Source, int SourceLen)
{
	int i;
	if (!Destination->IsAssigned) yFree_SDL_Octet_String ((void**)Destination);
	Destination->IsAssigned = 0;
	Destination->Length = SourceLen;
	Destination->Bits = (unsigned char *)XALLOC((xptrint)(Destination->Length), xSrtN_SDL_Bit_String);

	for (i=0; i<SourceLen; i++) {
		Destination->Bits [i] = ((SRC & POS) != 0);
	}
}
#endif
