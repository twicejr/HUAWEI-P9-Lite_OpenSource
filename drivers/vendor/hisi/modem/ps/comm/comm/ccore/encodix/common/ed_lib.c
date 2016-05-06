/*******************************************************************************
  ed_lib.c  Developed by Dafocus - http://www.dafocus.com/
*******************************************************************************/
#include "ed_lib.h"
#include <stdlib.h>

/*lint -e502*/
/*lint -e701*/
/*lint -e702*/
/*lint -e703*/
/*lint -e704*/
/*lint -e830*/
/*lint -e525*/
/*lint -e713*/
/*lint -e732*/
/*lint -e737*/
/*lint -e574*/



#ifndef ED_REVERSED_BITS
#define POS(bit) (1 << (7-(bit & 7)))
#else
#define POS(bit) (1 << (bit & 7))
#endif
#define SRC (*(((const unsigned char*) Source)+(SourceOffset >> 3)))
#define DST (*(((unsigned char*)Destination)+(DestOffset >> 3)))

/*------------------------------------------------------------------------------
    This function copies given number of bits starting from given SourceOffset
    from "Source" buffer to "Destination" buffer.  Bits are aligned on destination
    buffer starting from bit "DestOffset".

    Bit-positions are expressed as follows:
     - bit 0 is the highest (most significant) bit of octet 0;
     - bit 7 is the lowest (less significant) bit of octet 0;
     - bit 8 is the highest (most significant) bit of octet 1;
    ...and so on.

    Both Lenght and Offsets are expressed in bits.
------------------------------------------------------------------------------*/
void EDCopyBits (void* Destination, long DestOffset, const void* Source, long SourceOffset, long Length)
{
    long l;

    /* Optimization: if length and offsets are byte-aligned, use memcpy */
#ifndef ED_NO_EDCOPYBITS_OPTIMIZATION
    if (! ((DestOffset | SourceOffset | Length) & 7)) {
        ED_MEM_COPY (((char*)Destination)+(DestOffset>>3), ((const char*)Source)+(SourceOffset>>3), Length>>3);
        return;
    }
#endif

    for (l=0; l<Length; l++) {
        if ((SRC & POS(SourceOffset)) != 0) DST |= POS(DestOffset);
        else DST &= ~POS(DestOffset);
        SourceOffset++;
        DestOffset++;
    }
}

/*------------------------------------------------------------------------------
    This function copies 'Count' less significant bits of 'Source' integer to
    'Destination' ad offset 'Offset'.
------------------------------------------------------------------------------*/
void EDIntToBits (void* Destination, long DestOffset, int Source, int Count)
{
#ifndef ED_REVERSED_INTEGER
        int i;
        for (i=Count-1; i>=0; i--) {
            if ((Source & (1 << i)) != 0) DST |= POS(DestOffset);
            else DST &= ~POS(DestOffset);
            DestOffset++;
        }
#else
        int i;
        DestOffset+=Count-1;
        for (i=Count-1; i>=0; i--) {
            if ((Source & (1 << i)) != 0) DST |= POS(DestOffset);
            else DST &= ~POS(DestOffset);
            DestOffset--;
        }
#endif
}

/*------------------------------------------------------------------------------
    This function copies 'Count' less significant bits of 'Source' char buffer
    from offset 'Offset'. Read integer is returned.
------------------------------------------------------------------------------*/
int EDBitsToInt (const void* Source, long SourceOffset, int Count)
{
#ifndef ED_REVERSED_INTEGER
        int i, ret=0;
        for (i=0; i<Count; i++) {
            if ((SRC & POS(SourceOffset)) != 0) ret |= (1 << (Count-i-1));
            SourceOffset++;
        }
        return ret;
#else
        int i, ret=0;
        SourceOffset+=Count-1;
        for (i=0; i<Count; i++) {
            if ((SRC & POS(SourceOffset)) != 0) ret |= (1 << (Count-i-1));
            SourceOffset--;
        }
        return ret;
#endif
}

/*------------------------------------------------------------------------------
    This function copies 'Count' less significant bits of 'Source' integer to
    'Destination' ad offset 'Offset'.
    Bits are saved placing the least significant one on the left, unless
    ED_REVERSED_INTEGER is defined.
------------------------------------------------------------------------------*/
void EDIntToBitsReversed (void* Destination, long DestOffset, int Source, int Count)
{
#ifdef ED_REVERSED_INTEGER
        int i;
        for (i=Count-1; i>=0; i--) {
            if ((Source & (1 << i)) != 0) DST |= POS(DestOffset);
            else DST &= ~POS(DestOffset);
            DestOffset++;
        }
#else
        int i;
        DestOffset+=Count-1;
        for (i=Count-1; i>=0; i--) {
            if ((Source & (1 << i)) != 0) DST |= POS(DestOffset);
            else DST &= ~POS(DestOffset);
            DestOffset--;
        }
#endif
}

/*------------------------------------------------------------------------------
    This function copies 'Count' less significant bits of 'Source' char buffer
    from offset 'Offset'. Read integer is returned.
    Bits are considered with the least significant one on the left, unless
    ED_REVERSED_INTEGER is defined.
------------------------------------------------------------------------------*/
int EDBitsToIntReversed (const void* Source, long SourceOffset, int Count)
{
#ifdef ED_REVERSED_INTEGER
        int i, ret=0;
        for (i=0; i<Count; i++) {
            if ((SRC & POS(SourceOffset)) != 0) ret |= (1 << (Count-i-1));
            SourceOffset++;
        }
        return ret;
#else
        int i, ret=0;
        SourceOffset+=Count-1;
        for (i=0; i<Count; i++) {
            if ((SRC & POS(SourceOffset)) != 0) ret |= (1 << (Count-i-1));
            SourceOffset--;
        }
        return ret;
#endif
}
#ifndef ED_MINIMAL_LIBRARY

/*------------------------------------------------------------------------------
    Given a sorted array of TEDKnownIEs, finds the given IE and returns its
    entry or returns NULL if not found.
------------------------------------------------------------------------------*/
const TEDKnownIE* EDFindKnownIE (unsigned char IEI, const TEDKnownIE* KnownIEs, int ArraySize)
{
    int l = 0;
    int r = ArraySize-1;
    int x;

    while (r >= l) {
        x = (l+r) >> 1;
        if ((IEI & KnownIEs [x].IEIMask) == KnownIEs [x].IEI) return KnownIEs+x;
        if (IEI < KnownIEs [x].IEI) r = x-1; else l = x+1;
    }
    return NULL;
}

/*------------------------------------------------------------------------------
    When decoding, skips the current IE if known. If not known, it returns
    ED_FALSE. Otherwise, it returns ED_TRUE.
    "CurrentOffset" is increased according to the known IE size.
------------------------------------------------------------------------------*/
int EDSkipKnownIE (const void* Source, long* CurrentOffset, const TEDKnownIE* KnownIEs, int ArraySize)
{
    unsigned char IEI = (unsigned char)EDBitsToInt (Source, *CurrentOffset, 8);
    const TEDKnownIE* knownIE = EDFindKnownIE (IEI, KnownIEs, ArraySize);
    if (knownIE == NULL || knownIE->Length == 0) return ED_FALSE;
    if (knownIE->Length >= 0) {
        (*CurrentOffset) += knownIE->Length;
    }
    else {
        (*CurrentOffset) += (EDBitsToInt (Source, (*CurrentOffset)+8, -knownIE->Length) << 3) + 8 /*tag*/ + (-knownIE->Length);
    }

    return ED_TRUE;
}



/*------------------------------------------------------------------------------
    Reads the IEI of an optional IE.
    It receives the list of the possible expected IEIs.
    If the IEI is not one of the possible valid next IEIs, the IE is discarded
    using EDSkipKnownIE function.
    - if it is the expected one, it returns the tag, >=0;
    - if it is an unexpected one, it skips it;
    - if it isn't able to skip it, returns ED_UNKNOWN_IEI;
    - if it goes past the end of the message, it returns ED_MESSAGE_TOO_SHORT.
    - if it meets an IEI on the "expected list" returns ED_MISSING_OPTIONAL.
    Parameters:
      ExpectedIEI         IEI we expect
        IEISizeInBits       size of the IEI we expect (usually 8 bits, sometimes 4)
        Source              Buffer containing the message
        CurrentOffset       Offset in "Source" where we are expected to start
                            reading (in bits). This value is updated if some
                                                IE is skipped.
        EndOfMessage        Offset of the first bit after the end of the message
        KnonwIEs            Pointer to the list of known information elements
        ArraySize           Number of items in the known information elements list
        SkipList            Pointer to a TEDTLVSkipItem array, used to know the
                            next expected items. NULL if the IE is mandatory.
------------------------------------------------------------------------------*/
int EDGetIE (int ExpectedIEI, int IEISizeInBits, const void* Source, long* CurrentOffset, long EndOfMessage, const TEDKnownIE* KnownIEs, int ArraySize, const TEDTLVSkipItem* SkipList)
{
    int IEI;
    int i;
    while (1) {
        if (EndOfMessage - (*CurrentOffset) < IEISizeInBits) {
            return (SkipList? ED_MISSING_OPTIONAL : ED_MESSAGE_TOO_SHORT);
        }
        /* Try the expected IE */
        IEI = EDBitsToInt (Source, *CurrentOffset, IEISizeInBits);
        if (IEI == ExpectedIEI) {
            return IEI;
        }

        if (IEISizeInBits != 8) IEI = EDBitsToInt (Source, *CurrentOffset, 8);

        /* Check if the IEI is on the "expected list" */
        if (SkipList) {
            for (i=0; SkipList [i].Type != ED_SKIPLIST_END_OF_LIST; i++) {
                if ((IEI & SkipList [i].IEIMask) == SkipList [i].IEI) return ED_MISSING_OPTIONAL;
                if (SkipList [i].Type == ED_SKIPLIST_MANDATORY) break;
            }
        }

        /* Try to skip unexpected IE */
        if (EDSkipKnownIE (Source, CurrentOffset, KnownIEs, ArraySize) == ED_FALSE) {
            /*¦Ì¡ÀIEI¦Ì????????a0¦Ì?¨º¡Ào¨°, ¡À¨ª¨º???IEI?acomprehension required*/
            if ((IEI & 0xF0) == 0x0)
            {
                return ED_MANDATORY_IE_SYNTAX_ERROR;
            }
            else
            {
                /*GCF 26.5.6.3 TEST BEGIN YANGSICONG 20070711*/
                /*
                Bit 8 of the IEI octet is set to "1" indicates
                a TV formatted type 1 standard IE or a T formatted type 2 IEs,
                and to "0" indicates a TLV formatted type 4 IE.
                Hence, a 1 valued bit 8 indicates that the whole IE is one octet long,
                and a 0 valued bit 8 indicates that the following octet is a length octet
                */
                if(IEI & 0x80)
                {
                    *CurrentOffset = *CurrentOffset + 8;
                }
                else
                {
                    *CurrentOffset = *CurrentOffset + 8 * EDBitsToInt (Source, (*CurrentOffset)+8, 8) + 16;
                }
                /*GCF 26.5.6.3 TEST END YANGSICONG 20070711*/
                return ED_UNKNOWN_IEI;
            }
        }
    }
}
#endif

/*------------------------------------------------------------------------------
	Encodes a "definite form" length value. See X.690 8.1.3.3.
	It returns the number of bits used to encode the value.
	"Offset" is expressed in bits.
------------------------------------------------------------------------------*/
int EDEncodeDefiniteFormLength (void* Destination, ED_EXLONG Offset, unsigned ED_EXLONG Value)
{
	/* Encode in short form */
	if (Value <= 127) {
		EDIntToBits (Destination, Offset, Value, 8);
		return 8;
	}
	/* Encode in ED_EXLONG form */
	else {
		int Size;
		if ((Value & 0xFF000000) != 0) {
			Size = 4;
		}
		else if ((Value & 0xFF0000) != 0) {
			Size = 3;
		}
		else if ((Value & 0xFF00) != 0) {
			Size = 2;
		}
		else {
			Size = 1;
		}
		/* Encode the size with bit 8 set */
		EDIntToBits (Destination, Offset, (Size | 0x80), 8);
		
		/* Encode the data */
		EDIntToBits (Destination, Offset, Value, 8 * Size);
		
		return (Size+1) * 8;
	}
}

/*------------------------------------------------------------------------------
    Decodes a "definite form" length value. See X.690 8.1.3.3.
    It returns the number of bits used to decode the value.
    "Offset" is expressed in bits.
    It returns the value in "Value". It will be set to an error value <0 in
    case of decoding error.
------------------------------------------------------------------------------*/
int EDDecodeDefiniteFormLength (const void* Source, ED_EXLONG Offset, unsigned ED_EXLONG* Value)
{
	int FirstOctet;
	
	/* Decode the value. It could be a short-form or the length of a ED_EXLONG form */
	FirstOctet = EDBitsToInt (Source, Offset, 8);
	
	/* It is a short form */
	if ((FirstOctet & 0x80) == 0) {
		(*Value) = FirstOctet;
		return 8;
	}
	
	/* It is a ED_EXLONG form */
	FirstOctet &= 0x7F;

	/* If the value is too big, complain */
	if (FirstOctet > (int)sizeof (*Value)) {
		return ED_IE_SIZE_ERROR;
	}
	
	/* Decode the value */
	(*Value) = (unsigned ED_EXLONG)EDBitsToInt (Source, Offset+8, FirstOctet*8);
	
	return (FirstOctet+1) * 8;
}

/*------------------------------------------------------------------------------
    Standard locator setting function
------------------------------------------------------------------------------*/
void EDStandardLocatorSet (unsigned long* edLocatorPtr, long offsetInBits, long lengthInBits)
{
    if (offsetInBits < 0 || offsetInBits > 0xFFFF || lengthInBits < 0 || lengthInBits > 0xFFFF) {
        (*edLocatorPtr) = ED_STANDARD_LOCATOR_INVALID;
    }
    else {
        (*edLocatorPtr) = (offsetInBits << 16) | lengthInBits;
    }
}

/*lint +e502*/
/*lint +e701*/
/*lint +e702*/
/*lint +e703*/
/*lint +e704*/
/*lint +e830*/
/*lint +e525*/
/*lint +e713*/
/*lint +e732*/
/*lint +e737*/
/*lint +e574*/

