/*******************************************************************************
  csn1clib.c  Developed by Dafocus - http://www.dafocus.com/
*******************************************************************************/
#include "csn1clib.h"
#define CMIN(a,b) ((a)<(b)?(a):(b))

/* #define CSN1C_DEBUG_TRACE */
#define CSN1C_AssertHasTopValue(Context) assert ((Context)->Top > 0)

#ifdef CSN1C_USE_POP_FUNCTION
void CSN1C_Pop (TCSN1CContext* Context);
static unsigned ED_EXLONG CSN1C_PopValue(TCSN1CContext* Context)
{
  CSN1C_Pop (Context);
  return ((Context)->Elements [(Context)->Top].Value);
}
#else
#define CSN1C_PopValue(Context) (CSN1C_Pop (Context), ((Context)->Elements [(Context)->Top].Value))
#endif

#define CSN1C_TopValue(Context) ((Context)->Elements [(Context)->Top-1].Value)
#define CSN1C_TopCurrOfs(Context) ((Context)->Elements [(Context)->Top-1].CurrOfs)
#define CSN1C_SetTopCurrOfsN(Context,N,val) (assert ((Context)->Top >= (N)+1), ((Context)->Elements [(Context)->Top-(N)-1].CurrOfs)=(val))

#if !defined CSN1C_DEBUG_TRACE_CONDITION_START 
	#define CSN1C_DEBUG_TRACE_CONDITION_START {
#endif

#if !defined CSN1C_DEBUG_TRACE_CONDITION_END 
	#define CSN1C_DEBUG_TRACE_CONDITION_END }
#endif


/*------------------------------------------------------------------------------
	Sets bit at given offset to 1
------------------------------------------------------------------------------*/
#define CSN1C_SetBit1(buffer,bitOffset)\
	(((unsigned char*)(buffer))[((unsigned)(bitOffset))>>3] |= (1 << (7U-(((unsigned)(bitOffset)) & 7))))

/*------------------------------------------------------------------------------
	Sets bit at given offset to 0
------------------------------------------------------------------------------*/
#define CSN1C_SetBit0(buffer,bitOffset)\
	(((unsigned char*)(buffer))[((unsigned)(bitOffset))>>3] &= ~(1 << (7U-(((unsigned)(bitOffset)) & 7))))

/*------------------------------------------------------------------------------
	Sets bit at given offset to L
------------------------------------------------------------------------------*/
#define CSN1C_SetBitL(buffer,bitOffset,mask)\
	(((unsigned char)mask) & (1 << (7U-(((unsigned)(bitOffset)) & 7)))? CSN1C_SetBit1(buffer,bitOffset):\
	CSN1C_SetBit0(buffer,bitOffset))

/*------------------------------------------------------------------------------
	Sets bit at given offset to H
------------------------------------------------------------------------------*/
#define CSN1C_SetBitH(buffer,bitOffset,mask)\
	(((unsigned char)mask) & (1 << (7U-(((unsigned)(bitOffset)) & 7)))? CSN1C_SetBit0(buffer,bitOffset):\
	CSN1C_SetBit1(buffer,bitOffset))


/*------------------------------------------------------------------------------
	Checks bit at given offset to 1
------------------------------------------------------------------------------*/
#define CSN1C_CheckBit1(buffer,bitOffset)\
	((((unsigned char*)(buffer))[((unsigned)(bitOffset))>>3] & (1 << (7-(((unsigned)bitOffset) & 7)))) != 0)

/*------------------------------------------------------------------------------
	Checks bit at given offset to 0
------------------------------------------------------------------------------*/
#define CSN1C_CheckBit0(buffer,bitOffset) (!CSN1C_CheckBit1(buffer,bitOffset))

/*------------------------------------------------------------------------------
	Checks bit at given offset to L
------------------------------------------------------------------------------*/
#define CSN1C_CheckBitL(buffer,bitOffset,mask)\
	(((unsigned char)mask) & (1 << (7U-(((unsigned)(bitOffset)) & 7)))? CSN1C_CheckBit1(buffer,bitOffset):\
	CSN1C_CheckBit0(buffer,bitOffset))

/*------------------------------------------------------------------------------
	Checks bit at given offset to H
------------------------------------------------------------------------------*/
#define CSN1C_CheckBitH(buffer,bitOffset,mask)\
	(((unsigned char)mask) & (1 << (7U-(((unsigned)(bitOffset)) & 7)))? CSN1C_CheckBit0(buffer,bitOffset):\
	CSN1C_CheckBit1(buffer,bitOffset))
struct SCSN1CContext     CSN1CContexts_0087[3] = {{0},{0},{0}};
struct SCSN1CContextSet  CSN1CContextSet_0087  = {CSN1CContexts_0087,0,3};
struct SCSN1CContextSet *pCSN1CContextSet_0087 = &CSN1CContextSet_0087;

struct SCSN1CContext     CSN1CContexts_0063[3] = {{0},{0},{0}};
struct SCSN1CContextSet  CSN1CContextSet_0063  = {CSN1CContexts_0063,0,3};
struct SCSN1CContextSet *pCSN1CContextSet_0063 = &CSN1CContextSet_0063;

struct SCSN1CContext     CSN1CContexts_0024[3] = {{0},{0},{0}};
struct SCSN1CContextSet  CSN1CContextSet_0024  = {CSN1CContexts_0024,0,3};
struct SCSN1CContextSet *pCSN1CContextSet_0024 = &CSN1CContextSet_0024;

/* If set, activates the tracing of CSN.1 encoding/decoding */
#ifdef CSN1C_DEBUG_TRACE
#include <stdio.h>
#include <stdarg.h>


/*------------------------------------------------------------------------------
	Trace function. Prints information about the context plus other printf-like
	parameters.
------------------------------------------------------------------------------*/
void CSN1C_Trace (FILE* File, const TCSN1CContext* Context, const char* Instruction, const char* Format, ...) 
{
	int i;
	va_list VarList;
#ifdef CSN1C_USER_TRACE_VARS
	CSN1C_USER_TRACE_VARS
#endif
	va_start (VarList, Format);

	CSN1C_DEBUG_TRACE_CONDITION_START
	fprintf (File, "\n\nCSN1C Offset=%-4d NextInstr=%-4d Instruction=%-20s Length=%-4d FinalOffset=%-4d CheckEnd=", Context->CurrOfs, Context->NextInstruction, Instruction, Context->Length, Context->FinalOffset);
	if (Context->CheckEnd == CSN1C_NO_CHECKEND) {
		fprintf (File, "NONE ");
	} else {
		fprintf (File, "%04d ", Context->CheckEnd);
	}
	fprintf (File, "Nesting=%d ", (int)Context->NestingLevel);
	vfprintf (File, Format, VarList);

	
#ifndef CSN1C_DISABLE_ADT
	fprintf (File, "      STACK (ft=%d lv=%d tt=%d):\n", Context->FieldState.FieldsTop, Context->FieldState.Level, Context->FieldState.UserTagTop);
#else
	fprintf (File, "      STACK (tt=%d):\n", Context->FieldState.UserTagTop);
#endif
	for (i=Context->Top-1; i>=0; i--) {
#ifndef CSN1C_DISABLE_ADT
		fprintf (File, "      [%02d] OFS: 0x%08X  Value=%d (ft=%d lv=%d tt=%d ce=", 
			i, Context->Elements [i].CurrOfs, Context->Elements [i].Value,
			Context->Elements [i].FieldState.FieldsTop, Context->Elements [i].FieldState.Level, Context->Elements [i].FieldState.UserTagTop
		);
#else
		fprintf (File, "      [%02d] OFS: 0x%08X  Value=%d (tt=%d ce=", 
			i, Context->Elements [i].CurrOfs, Context->Elements [i].Value,
			Context->Elements [i].FieldState.UserTagTop
		);
#endif

		if (Context->Elements [i].CheckEnd == CSN1C_NO_CHECKEND) {
			fprintf (File, "NONE");
		} else {
			fprintf (File, "%04d", Context->Elements [i].CheckEnd);
		}
		fprintf (File, ")%s%s%s%s",
			(Context->Elements [i].Backtrack? " BACKTRACK" : ""),
			(Context->Elements [i].InfiniteLoop? " LOOP" : ""),
			(Context->Elements [i].InsideInfiniteLoop? " INSIDELOOP" : ""),
			(Context->Elements [i].FinalOffset? " FINALOFFSET" : "")
		);
#ifdef CSN1C_USER_STACK_TRACE_CODE
	CSN1C_USER_STACK_TRACE_CODE
#endif
		fprintf (File, "\n");

	}
	if (Context->FieldState.UserTagTop > 0) {
		fprintf (File, "      TAGS:\n");
		for (i=Context->FieldState.UserTagTop-1; i>=0; i--) {
			fprintf (File, "        [%02d] TAG: 0x%08X  Value=%d\n", i, Context->UserTags [i].TagId, Context->UserTags [i].Value);
		}
	}
#ifndef CSN1C_DISABLE_ADT
	if (Context->FieldState.FieldsTop > 0) {
		fprintf (File, "      FIELDS:\n");
		for (i=0; i<Context->FieldState.FieldsTop; i++) {
			fprintf (File, "        FieldId=[%03d] Index=[%03d] Pos=[%03d] Level=[%03d] ParentId=[", 
				Context->Fields [i].FieldId,
				Context->Fields [i].Index,
				Context->Fields [i].Pos,
				Context->Fields [i].Level
			);
			if (Context->Fields [i].Parent) {
				fprintf (File, "%03d]\n", Context->Fields [i].Parent->FieldId);
			} else {
				fprintf (File, "NULL]\n");
			}
		}
	}
#endif
	i=0;
	fprintf (File, "BUFFER:\n");
	for (;;) {
		unsigned value, j;
		int remaining;
		if (Context->Encoding) remaining = Context->CurrOfs - (Context->StartOfs+i);
		else remaining = Context->StartOfs + Context->Length - i;
		if (remaining <= 0) break;
		if (remaining > 8) remaining = 8;
		value = EDBitsToInt (Context->Buffer, i, remaining);
		fprintf (File, "%04X: ", i);
		if (remaining < 8) {fprintf (File, "0x?? ");} else {fprintf (File, "0x%02X ", value);} 
		for (j=0; j<(unsigned)remaining; j++) {
			if (Context->CurrOfs == (int)(i+j)) fprintf (File, "[");
			fprintf (File, "%d", ((value >> (remaining-1-j)) & 1));
			if (Context->CurrOfs == (int)(i+j)) fprintf (File, "]");
		}
		if (Context->CurrOfs >= Context->Length) {
			fprintf (File, "[<<]");
		}
		fprintf (File, "\n");
		i += remaining;
	}
#ifdef CSN1C_USER_TRACE_CODE
	CSN1C_USER_TRACE_CODE
#endif
	CSN1C_DEBUG_TRACE_CONDITION_END
}

#define CSN1C_TRACE_FILE stdout
#define	CSN1C_TRACE0(instruction) CSN1C_Trace (CSN1C_TRACE_FILE, Context, instruction, "ProgPos=%d\n",CurrentInstruction);
#define	CSN1C_TRACE1(instruction) CSN1C_Trace (CSN1C_TRACE_FILE, Context, instruction, "ProgPos=%d Val1=%u\n",CurrentInstruction,Value1);
#define	CSN1C_TRACE2(instruction) CSN1C_Trace (CSN1C_TRACE_FILE, Context, instruction, "ProgPos=%d Val1=%u Val2=%u\n",CurrentInstruction,Value1,Value2);
#define	CSN1C_TRACE3(instruction) CSN1C_Trace (CSN1C_TRACE_FILE, Context, instruction, "ProgPos=%d Val1=%u Val2=%u Val3=%u\n",CurrentInstruction,Value1,Value2,Value3);
#define	CSN1C_TRACE4(instruction) CSN1C_Trace (CSN1C_TRACE_FILE, Context, instruction, "ProgPos=%d Val1=%u Val2=%u Val3=%u Val4=%u\n",CurrentInstruction,Value1,Value2,Value3,Value4);
#define	CSN1C_FLUSH_TRACE_FILE fflush (stdout);
#else
#define	CSN1C_TRACE0(instruction)
#define	CSN1C_TRACE1(instruction)
#define	CSN1C_TRACE2(instruction)
#define	CSN1C_TRACE3(instruction)
#define	CSN1C_TRACE4(instruction)
#define	CSN1C_FLUSH_TRACE_FILE
#endif

#ifndef CSN1C_DISABLE_ADT
/*------------------------------------------------------------------------------
	Link its Parent
------------------------------------------------------------------------------*/
void CSN1C_LinkParent (TCSN1CContext* Context)
{
	/* Set its Parent immediately */
	if (Context->FieldState.Level <= 0) {
		Context->Fields [Context->FieldState.FieldsTop].Parent = NULL;
	}
	else {
		int i;
		for (i=Context->FieldState.FieldsTop-1; i>=0; i--) {
			if (Context->Fields [i].Level == Context->FieldState.Level-1) {
				Context->Fields [Context->FieldState.FieldsTop].Parent = &(Context->Fields [i]);
				break;
			}
		}
		/* If fails, Parent was not found... it can't be! */
		CSN1C_FLUSH_TRACE_FILE
		assert (i >= 0);
	}
}

/*------------------------------------------------------------------------------
	Returns FieldId of the lowest Level field opened. It will be the Parent
	of the next added field.
	Returns the host field id if no parents are present.
	If "Closing" is true, it means that we are looking for the parent for the
	field being closed. In this way, it doesn't return the field itself as its
	own parent!
------------------------------------------------------------------------------*/
CSN1C_PAIRSET_TYPE CSN1C_GetParentFieldId (TCSN1CContext* Context, int Closing)
{
	CSN1C_DEBUG_CHECK (Context)
	if (Context->FieldState.Level <= 0) {
		CSN1C_FLUSH_TRACE_FILE
		assert (!Closing); /* The level can't be zero if we are closing! */
		return Context->HostFieldId;
	}
	else {
		int i;
		if (Closing && Context->FieldState.Level == 1) {
			return Context->HostFieldId;
		}
		for (i=Context->FieldState.FieldsTop-1; i>=0; i--) {
			if (Context->Fields [i].Level == Context->FieldState.Level-1-(Closing? 1 : 0)) {
				return (CSN1C_PAIRSET_TYPE)(Context->Fields [i].FieldId);
			}
		}
		/* If fails, Parent was not found... it can't be! */
		CSN1C_FLUSH_TRACE_FILE
		assert (i >= 0);
	}
	return Context->HostFieldId;
}

/*------------------------------------------------------------------------------
	Enter a field
------------------------------------------------------------------------------*/
void CSN1C_EnterField (TCSN1CContext* Context, int FieldId)
{
	int i, j;

	if (Context->FieldState.FieldsTop >= CSN1C_FIELDS) {
		/* Too many fields */
		#ifdef CSN1C_DEBUG_TRACE
		CSN1C_DEBUG_TRACE_CONDITION_START
		fprintf (CSN1C_TRACE_FILE, "FAILING: too many fields (limit is %d)\n", CSN1C_FIELDS);
		CSN1C_DEBUG_TRACE_CONDITION_END
		#endif
		Context->Failed = -1;
		return;
	}

	i = Context->FieldState.FieldsTop;
	Context->Fields [i].FieldId = FieldId;
	Context->Fields [i].Pos = Context->CurrOfs;
	Context->Fields [i].Index = 0;
	Context->Fields [i].Level = Context->FieldState.Level;
	CSN1C_LinkParent (Context);
	
	/* Calculate Index */
	for (j=i-1; j>=0; j--) {
		if (&(Context->Fields [j]) == Context->Fields [i].Parent) {
			Context->Fields [i].Index = 0;
			break;
		}
		else if ((Context->Fields [j].FieldId == Context->Fields [i].FieldId) 
			&& (Context->Fields [j].Index >= 0)) {
			Context->Fields [i].Index = Context->Fields [j].Index+1;
			break;
		}
	}

	Context->FieldState.FieldsTop++;
	Context->FieldState.Level++;
}

/*------------------------------------------------------------------------------
	Exit a field
------------------------------------------------------------------------------*/
void CSN1C_ExitField (TCSN1CContext* Context, int FieldId)
{
#ifdef CSNLIBDEBUG
	fprintf (stderr, "[%06d] exit field - FieldId=%d Pos=%d\n", csn1LogCounter++, FieldId, Pos);
#endif
	if (Context->FieldState.FieldsTop >= CSN1C_FIELDS) {
		/* Too many fields */
		#ifdef CSN1C_DEBUG_TRACE
		CSN1C_DEBUG_TRACE_CONDITION_START
		fprintf (CSN1C_TRACE_FILE, "FAILING: too many fields (limit is %d)\n", CSN1C_FIELDS);
		CSN1C_DEBUG_TRACE_CONDITION_END
		#endif
		Context->Failed = -1;
		return;
	}
	Context->Fields [Context->FieldState.FieldsTop].FieldId = FieldId;
	Context->Fields [Context->FieldState.FieldsTop].Pos = Context->CurrOfs;
	Context->Fields [Context->FieldState.FieldsTop].Index = -1;
	Context->Fields [Context->FieldState.FieldsTop].Level = Context->FieldState.Level;
	Context->FieldState.Level--;
	CSN1C_LinkParent (Context);
	Context->FieldState.FieldsTop++;
	CSN1C_DEBUG_CHECK (Context)
}

/*------------------------------------------------------------------------------
	Calculates the length of a field in bits. This has to be called just before
	a CSN1C_ExitField and with the same parameters.
------------------------------------------------------------------------------*/
int CSN1C_CalcFieldSize (TCSN1CContext* Context, int FieldId, ED_EXLONG Pos)
{
	int i;
	for (i=Context->FieldState.FieldsTop-1; i>=0; i--) {
		if (Context->Fields [i].FieldId == FieldId && Context->Fields [i].Level == Context->FieldState.Level-1) {
			return Pos-Context->Fields [i].Pos;
		}
	}
	return -1;
}

/*------------------------------------------------------------------------------
	Given a "FieldEntry" Value, returns the correct field id.
------------------------------------------------------------------------------*/
int CSN1C_FieldEntry2FieldId (TCSN1CContext* Context, unsigned ED_EXLONG FieldEntry, int Closing)
{
	int i;
	
	/* First, determine the parent field id */
	CSN1C_PAIRSET_TYPE ParentFieldId = CSN1C_GetParentFieldId	(Context, Closing);
	CSN1C_DEBUG_CHECK (Context)
	
	/* Then, find a combination having the given parent */
	for (i=FieldEntry; Context->Program->FieldIdPairSet [i] != ParentFieldId; i+=2) {
		CSN1C_FLUSH_TRACE_FILE
		assert (Context->Program->FieldIdPairSet [i] != -1);
	}
	return Context->Program->FieldIdPairSet [i+1];
}

#endif /* CSN1C_DISABLE_ADT */


/*------------------------------------------------------------------------------
	Initialize a context
------------------------------------------------------------------------------*/
void CSN1C_Init (TCSN1CContext* Context, const TCSN1CProgram* Program, unsigned StartInstruction, const void* Buffer, ED_EXLONG BitOffset, ED_EXLONG Length, int Encoding)
{
	memset (Context, 0, sizeof (*Context));
	Context->NextInstruction = StartInstruction;
	Context->Program = Program;
#ifndef CSN1C_DISABLE_ADT
	Context->HostFieldId = CSN1C_PAIRSET_TYPE_INVALID_VALUE;
#endif
	Context->Buffer = (char*)Buffer;
	Context->CurrOfs = BitOffset;
	Context->Length = Length;
	Context->Encoding = (unsigned char)Encoding;
	Context->CheckEnd = CSN1C_NO_CHECKEND;
	/*#error FIX this WITH A MACRO*/
	Context->AllowPartialStrings = -1;

#ifdef CSN1C_DEBUG_MODE
	Context->CheckSignature1 = CSN1C_DEBUG_SIGNATURE_1;
	Context->CheckSignature2 = CSN1C_DEBUG_SIGNATURE_2;
	Context->CheckSignature3 = CSN1C_DEBUG_SIGNATURE_3;
	Context->CheckSignature4 = CSN1C_DEBUG_SIGNATURE_4;
	Context->CheckSignature5 = CSN1C_DEBUG_SIGNATURE_5;
#endif
	
}

/*------------------------------------------------------------------------------
	CSN.1 Compact - Reads an extval multibyte Value.
	The Value is expected at Position in Buffer. Position is increased to point
	to the next unused entry.
------------------------------------------------------------------------------*/
unsigned ED_EXLONG CSN1C_ReadExtVal (const TCSN1CProgram* Program, unsigned ED_EXLONG* Position)
{
	unsigned ED_EXLONG Ret = 0;
	unsigned char CurrCh;
	
	/* Number of bits still available in the Ret variable */
	int RemainingBits = sizeof (Ret) << 3;
	int BitsUsedThisTime;
	
	while (RemainingBits > 0) {
		CurrCh = Program->ProgramCode [*Position];
		(*Position)++;
		
		/* Determine how many bits we can afford to host this time */
		BitsUsedThisTime = CMIN (7, RemainingBits);
		RemainingBits -= BitsUsedThisTime;
		
		/* Make room in Ret */
		Ret <<= BitsUsedThisTime;

		/* Set the corresponding bits */
		Ret |= CurrCh & ((1 << BitsUsedThisTime)-1);
		
		/* If we have no more octets, we're done */
		if ((CurrCh & 0x80) == 0) {
			break;
		}
	}
	return Ret;
}

#define C1_NONE          0
#define C1_BACKTRACK     1
#define C1_INFINITE_LOOP 2
#define C1_FINAL_OFFSET  4

/*------------------------------------------------------------------------------
	CSN.1 Compact - Executes a PUSH on the stack.
	IsBacktrack, int IsInfiniteLoop, int IsFinalOffset
------------------------------------------------------------------------------*/
void CSN1C_Push (TCSN1CContext* Context, unsigned ED_EXLONG Value, int Mode)
{
	/* If this assertion fails, the stack is too small */
	CSN1C_FLUSH_TRACE_FILE
	if (Context->Top >= CSN1C_STACK_SIZE) {
		#ifdef CSN1C_DEBUG_TRACE
		CSN1C_DEBUG_TRACE_CONDITION_START
		fprintf (CSN1C_TRACE_FILE, "FAILING: stack overflow (limit is %d)\n", CSN1C_STACK_SIZE);
		CSN1C_DEBUG_TRACE_CONDITION_END
		#endif
		Context->Failed = -1;
		return;
	}
	
	if ((Mode & C1_INFINITE_LOOP) != 0) {
		Context->Elements [Context->Top].InsideInfiniteLoop = -1;
	} else if (Context->Top > 0) {
		Context->Elements [Context->Top].InsideInfiniteLoop = Context->Elements [Context->Top-1].InfiniteLoop;
	} else {
		Context->Elements [Context->Top].InsideInfiniteLoop = 0;
	}
	
	Context->Elements [Context->Top].Backtrack = ((Mode & C1_BACKTRACK)? 1 : 0);
	Context->Elements [Context->Top].InfiniteLoop = ((Mode & C1_INFINITE_LOOP)? 1 : 0);
	Context->Elements [Context->Top].FinalOffset = ((Mode & C1_FINAL_OFFSET)? 1 : 0);
	Context->Elements [Context->Top].ForceReading = (Context->ForceReading? 1 : 0);
	Context->Elements [Context->Top].Value = Value;
	Context->Elements [Context->Top].CurrOfs = Context->CurrOfs;
	Context->Elements [Context->Top].CheckEnd = Context->CheckEnd;
	Context->Elements [Context->Top].NestingLevel = Context->NestingLevel;
	Context->Elements [Context->Top].FieldState = Context->FieldState;
	Context->Top++;
	CSN1C_DEBUG_CHECK (Context)
}

/*------------------------------------------------------------------------------
	CSN.1 Compact - Executes a POP of the stack.
------------------------------------------------------------------------------*/
void CSN1C_Pop (TCSN1CContext* Context)
{
	assert (Context->Top > 0);
	assert (Context->Top < CSN1C_STACK_SIZE);

	Context->Top--;
#ifndef CSN1C_DISABLE_ADT
	Context->FieldState.Level = Context->Elements [Context->Top].FieldState.Level;
#endif
	Context->ForceReading = (Context->Elements [Context->Top].ForceReading ? 1 : 0);
}

/*------------------------------------------------------------------------------
	CSN.1 Compact - Executes a BACKTRACK.
	The "BACKTRACK" operation is executed when a CSN.1 branch failed.
	Everything is restored down to topmost backtrack entry on the stack.
	If there are no backtrack checkpoints, it means that the entire parsing is
	failed.
	It returns 0=FAILED, 1=OK
------------------------------------------------------------------------------*/
int CSN1C_Backtrack (TCSN1CContext* Context)
{
	int i;
	/*assert (Context->Top > 0);*/
	if (Context->Top <= 0 || Context->Top>=CSN1C_STACK_SIZE) return 0;
	for (i=Context->Top-1; i>=0; i--) {
		if (Context->Elements [i].FinalOffset) {
			Context->FinalOffset = Context->Elements [i].Value;
		}
		if (Context->Elements [i].Backtrack) {
			Context->CurrOfs = Context->Elements [i].CurrOfs;
			Context->CheckEnd = Context->Elements [i].CheckEnd;
			Context->NestingLevel = Context->Elements [i].NestingLevel;
			Context->NextInstruction = Context->Elements [i].Value;
			Context->ForceReading = (Context->Elements [i].ForceReading ? 1 : 0);
			
			Context->Top = i;
/*			if (!Context->Elements [i].InfiniteLoop) { */
				Context->FieldState = Context->Elements [i].FieldState;
#ifdef CSN1C_USER_FIELDSTATE_RESTORE
				CSN1C_USER_FIELDSTATE_RESTORE
#endif
/*			} */
#ifdef CSN1C_DEBUG_TRACE
			CSN1C_DEBUG_TRACE_CONDITION_START
			CSN1C_Trace (CSN1C_TRACE_FILE, Context, "backtracking", "sucessful backtrack to instruction %d\n", Context->NextInstruction);
			CSN1C_DEBUG_TRACE_CONDITION_END
#endif
			CSN1C_DEBUG_CHECK (Context)
			return 1;
		}
	}
#ifdef CSN1C_DEBUG_TRACE
	CSN1C_DEBUG_TRACE_CONDITION_START
	CSN1C_Trace (CSN1C_TRACE_FILE, Context, "backtracking", "failed\n");
	CSN1C_DEBUG_TRACE_CONDITION_END
#endif			
	CSN1C_DEBUG_CHECK (Context)
	return 0;
}

/*------------------------------------------------------------------------------
	CSN.1 Compact - Executes a UPDATE_BACKTRACK.

	Updates the situation of the topmost backtrack instruction to the current 
	state.
	It means that everything got so far has to be kept if a backtracking happens 
	next.
	It is used to implement the truncation. For example:

	 {<a1> <a2> <a3> ... <aN>}//
 
	Is implemented by putting a CHOICE_NODE at the beginning and then by updating 
	the backtrack between ever "<aX> <aX+1>".

	It returns 0=FAILED, 1=OK
------------------------------------------------------------------------------*/
int CSN1C_UpdateBacktrack (TCSN1CContext* Context)
{
	int i;
	assert (Context->Top > 0);
	assert (Context->Top < CSN1C_STACK_SIZE);
	for (i=Context->Top-1; i>=0; i--) {
		if (Context->Elements [i].Backtrack) {
			Context->Elements [i].CurrOfs = Context->CurrOfs;
			Context->Elements [i].CheckEnd = Context->CheckEnd;
			Context->Elements [i].NestingLevel = Context->NestingLevel;
			Context->Elements [i].FieldState = Context->FieldState;
#ifdef CSN1C_DEBUG_TRACE
			CSN1C_DEBUG_TRACE_CONDITION_START
			CSN1C_Trace (CSN1C_TRACE_FILE, Context, "update-backtracking", "sucessful updated backtrack to instruction %d\n", Context->NextInstruction);
			CSN1C_DEBUG_TRACE_CONDITION_END
#endif
			return 1;
		}
	}
#ifdef CSN1C_DEBUG_TRACE
	CSN1C_DEBUG_TRACE_CONDITION_START
	CSN1C_Trace (CSN1C_TRACE_FILE, Context, "update-backtracking", "failed\n");
	CSN1C_DEBUG_TRACE_CONDITION_END
#endif			
	return 0;
}

/*------------------------------------------------------------------------------
	Given a program and a "LabelId" Value, it returns a string describing
	the label or "NULL" if the description is not available.
------------------------------------------------------------------------------*/
const char* CSN1C_GetLabelText (const TCSN1CProgram* Program, unsigned LabelId)
{
#ifdef CSN1C_LABEL_NAMES
	const char* Ret = NULL;
	if (Program->LabelNames != NULL) {
		Ret = Program->LabelNames [LabelId];
	}
	return Ret;
#else
	ED_WARNING_REMOVER(Program);
	ED_WARNING_REMOVER(LabelId);
	return NULL;
#endif	
}

/*------------------------------------------------------------------------------
	Adds a Value with given code on the stack
------------------------------------------------------------------------------*/
void CSN1C_PushValue (TCSN1CContext* Context, int Tag, int Value)
{
	/* Not enough user tags */
	CSN1C_FLUSH_TRACE_FILE
	assert (Context->FieldState.UserTagTop < CSN1C_USERTAGS);

	Context->UserTags [Context->FieldState.UserTagTop].TagId = Tag;
	Context->UserTags [Context->FieldState.UserTagTop].Value = Value;
	Context->FieldState.UserTagTop++;
}

/*------------------------------------------------------------------------------
	Returns given Value from the stack
------------------------------------------------------------------------------*/
int CSN1C_GetValue (const TCSN1CContext* Context, int Tag)
{
	int i;
	CSN1C_DEBUG_CHECK (Context)
	for (i=Context->FieldState.UserTagTop-1; i>=0; i--) {
		if (Context->UserTags [i].TagId == Tag) return Context->UserTags [i].Value;
	}
	/* Tag not found. It should never happen, unless of bad custom E/D coding */
	CSN1C_FLUSH_TRACE_FILE
	ED_ASSERT_FORCE_FAIL
	return -1;
}

/*------------------------------------------------------------------------------
	Returns given Value from the stack; in case the value is not found, it
	returns 0.
------------------------------------------------------------------------------*/
int CSN1C_GetValueOrZero (const TCSN1CContext* Context, int Tag)
{
	int i;
	for (i=Context->FieldState.UserTagTop-1; i>=0; i--) {
		if (Context->UserTags [i].TagId == Tag) return Context->UserTags [i].Value;
	}
	return 0;
}

/*------------------------------------------------------------------------------
	Deletes all the tags until reaching the given tag, which is deleted as well.
------------------------------------------------------------------------------*/
void CSN1C_PopValues (TCSN1CContext* Context, int Tag)
{
	int i;
	for (i=Context->FieldState.UserTagTop-1; i>=0; i--) {
		if (Context->UserTags [i].TagId == Tag) {
			Context->FieldState.UserTagTop = i;
			return;
		}
	}
	/* Tag not found. It should never happen, unless of bad custom E/D coding */
	ED_ASSERT_FORCE_FAIL
	assert (0);
}

/*------------------------------------------------------------------------------
	Returns 1 if the given tag exists; 0 if it does not exist.
------------------------------------------------------------------------------*/
int CSN1C_ExistsValue (const TCSN1CContext* Context, int Tag)
{
	int i;
	for (i=Context->FieldState.UserTagTop-1; i>=0; i--) {
		if (Context->UserTags [i].TagId == Tag) return 1;
	}
	return 0;
}

/*------------------------------------------------------------------------------
	Sets a Value with the given Tag. It finds it like CSN1C_GetValue.
------------------------------------------------------------------------------*/
void CSN1C_SetValue (TCSN1CContext* Context, int Tag, int Value)
{
	int i;
	for (i=Context->FieldState.UserTagTop-1; i>=0; i--) {
		if (Context->UserTags [i].TagId == Tag) {Context->UserTags [i].Value = Value; CSN1C_DEBUG_CHECK (Context) return;}
	}
	/* Tag not found. It should never happen, unless of bad custom E/D coding */
	CSN1C_FLUSH_TRACE_FILE
	ED_ASSERT_FORCE_FAIL
}

/*------------------------------------------------------------------------------
	Resolves a <crelpos> jump address.
	
	A <crelpos> is made of 13 or 14 bits.
	The first two (one for the 13-bit version) bits (i.e. the most significant) 
	make the multiplicator M, while the remaining 12 bits are the value V.
	The formula to calulate the intermediate J value is B+V*K, where:
		M=0, K= 1, B=0x0000 (J range 0-4095)
		M=1, K= 4, B=0x1000 (J range 4096-20476)
		M=2, K= 8, B=0x5000 (J range 20480-53240), not used in 13-bit version
		M=3, K=16, B=0xD000 (J range 53248-118752), not used in 13-bit version

	Having the J value, it is possible to calculate the destination address D 
	from the start address S (S=address of the instruction containing the crelpos 
	value).
	The final address D is:

		D=S+J+R;

	R is 0 if D is an exact multiple of K; otherwise, R=K-(D % K).
	This means that when a jump with M>0 is involved, the instructions must be 
	aligned at a valid K.
	This can be done by inserting NOP instructions.
------------------------------------------------------------------------------*/
unsigned ED_EXLONG CSN1C_ResolveCRelPos (unsigned ED_EXLONG InstructionAddress, unsigned ED_EXLONG CRelPos)
{
#define S InstructionAddress
	int M;
	int K=0;
	unsigned ED_EXLONG B=0, D, V;
	
	M = (CRelPos >> 13) & 0x03;
	V = CRelPos & 0x0FFF;
	
	switch (M) {
		case 0: return InstructionAddress+V;
		case 1: B=0x1000; K=8; break;
		case 2: B=0x9000; K=16; break;
		case 3: B=0x19000; K=32; break;
		default: ED_ASSERT_FORCE_FAIL; /* Invalid multiplier? How can 2 bit have other values? */
	}
	D = S + B + V * K;
	if ((D & (K-1)) != 0) {
		D += K;
		D &= ~(K-1);
	}
	
	return D;
}
#undef S

#define C1_MIN(a) (((a) >> 15) & 0x3FFF)
#define C1_MAX(a) ((a) & 0x7FFF)
#define C1_FBIT(a) (((a) & 0x20000000) ? 1 : 0)
#define C1_SET_MIN(a,m) (a) = ((a) & 0xE0007FFF) | (((m) & 0x3FFF) << 15)
#define C1_SET_MAX(a,m) (a) = ((a) & 0xFFFF8000) | ((m) & 0x7FFF)
#define C1_SET_FBIT(a,m) (a) = ((a) & 0xDFFFFFF) | (((m)?1:0) << 29)

/*------------------------------------------------------------------------------
	Invoked when inside a loop. It expects to find on the stack the following
	situation:
	- first topmost entry, a LOOP COUNTER ENTRY POINT
	- second topmost entry, a BACKTRACK ENTRY POINT
	
	It checks max. If max is 0, it jumps to ExitInstruction and returns 1.
	If it is IsFBIT, min is 0, and it is encoding, it jumps to ExitInstruction 
	and returns 1.
	If min is 0, it sets the state of the loop to OPTIONAL.
	If no jumps have been made, it returns 0.
------------------------------------------------------------------------------*/
int CSN1C_CheckLoop (TCSN1CContext* Context, unsigned ED_EXLONG ExitInstruction)
{
	unsigned ED_EXLONG LoopData;
	unsigned MinValue, MaxValue;
	int IsFBIT;
	TCSN1CStackElement* BacktrackEntry;
	
	assert (Context->Top < CSN1C_STACK_SIZE);
	assert (Context->Top >= 2);
	
	CSN1C_AssertHasTopValue (Context);
	LoopData = CSN1C_TopValue (Context);
	MinValue = C1_MIN (LoopData);
	MaxValue = C1_MAX (LoopData);
	IsFBIT = C1_FBIT (LoopData);
	
	/* If MaxValue==0, loop terminated */
	/* or if it is IsFBIT, min is 0, and it is encoding */
	if ((MaxValue == 0) || (IsFBIT && (MinValue == 0) && Context->Encoding && (Context->CheckEnd == CSN1C_NO_CHECKEND))) {
		/* Pop the LOOP COUNTER ENTRY POINT */
		CSN1C_Pop (Context);
		/* Pop the BACKTRACK ENTRY POINT for the loop */
		CSN1C_Pop (Context);
		/* Jump to the exit instruction */
		Context->NextInstruction = ExitInstruction;
		return 1;
	}
	
	BacktrackEntry = &(Context->Elements [Context->Top-2]);
	
	/* If MinValue is 0, activate the OPTIONAL mode */
	if (MinValue == 0 && !BacktrackEntry->Backtrack) {
		BacktrackEntry->Backtrack = -1;
		BacktrackEntry->InfiniteLoop = -1;
		BacktrackEntry->InsideInfiniteLoop = -1;
		Context->Elements [Context->Top-1].InsideInfiniteLoop = -1;
	}
	
	return 0;
}

/*------------------------------------------------------------------------------
	Executes a SETUP for a loop.
	It returns 0 if the operation can continue, 1 if it has already skipped out
	to the next instruction.
	This instruction sets up the loop in the MANDATORY state. It will be set
	to the OPTIONAL state by CSN1C_CheckLoop when required.
	
	RelPos coded as follows:
		bit 1     = 1=FBIT 0=VBIT
		bit 2-32  = Value to be added to InstructionOffset to obtain the program
		            address of the first instruction after the loop.
------------------------------------------------------------------------------*/
int CSN1C_SetupLoop (TCSN1CContext* Context, unsigned InstructionOffset, unsigned ED_EXLONG RelPos, unsigned Min, unsigned Max)
{
	int IsFBIT;
	unsigned ED_EXLONG MinMax = 0;
	
	/* Avoid MIN values too big */
	assert ((Min & 0x3FFF) == Min);

	/* Avoid MAX values too big */
	assert ((Max & 0x7FFF) == Max);
	
	/* Bit 1 of RelPos tells whether it is a FBIT(1) or a VBIT(0) */
	IsFBIT = (RelPos & 1);
	
	/* Then we get the effective RelPos value */
	RelPos >>= 1;
	
	assert (InstructionOffset+RelPos < Context->Program->ProgramLength);
	
	/* Push the backtrack setup, but without configuring it to BACKTRACK.
	   This will be done by the CSN1C_CheckLoop if necessary */
	CSN1C_Push (Context, InstructionOffset+RelPos, (Max == CSN1C_EXPR_INFINITE? C1_INFINITE_LOOP : C1_NONE));
	
	/* Push the loop value */
	C1_SET_FBIT (MinMax, IsFBIT);
	C1_SET_MIN (MinMax, Min);
	C1_SET_MAX (MinMax, Max);
	CSN1C_Push (Context, MinMax, (Max == CSN1C_EXPR_INFINITE? C1_INFINITE_LOOP : C1_NONE));
	
	/* Update JumpEnd, in case we find a SetupLoopMin */
	Context->JumpEnd = InstructionOffset+RelPos;
	
	/* Check the status */
	return CSN1C_CheckLoop (Context, InstructionOffset+RelPos);
}

/*------------------------------------------------------------------------------
	Executes a partial SETUP for a loop.
	This is invoked when a loop is already set but the MIN values have to be
	changed.
	This function must be invoked with the loop already set in MANDATORY state.
------------------------------------------------------------------------------*/
int CSN1C_SetupLoopMin (TCSN1CContext* Context, unsigned Min)
{
	/* Avoid MIN values too big */
	assert ((Min & 0x3FFF) == Min);

	/* The loop must be set up already */	
	assert (Context->Top >= 2);

	/* The loop must be set up as MANDATORY */	
	assert (!Context->Elements [Context->Top-2].Backtrack);
	
	/* Update the loop value */
	CSN1C_AssertHasTopValue (Context);
	C1_SET_MIN (CSN1C_TopValue (Context), Min);
	
	/* Check the status */
	return CSN1C_CheckLoop (Context, Context->JumpEnd);
}

/*------------------------------------------------------------------------------
	Executes a CSN.1 expression.
	It returns !=0 if the execution can continue, 0 if the function requested
	a backtrack or a fail. In that case, the backtrack is executed.
------------------------------------------------------------------------------*/
int CSN1C_InvokeExpression (TCSN1CContext* Context, unsigned ED_EXLONG ExpressionId, unsigned ED_EXLONG* Destination)
{
	(*Destination) = Context->Program->ExpressionMap [ExpressionId] (Context);
	switch (*Destination) {
		case CSN1C_EXPR_BACKTRACK: {
			if (!CSN1C_Backtrack (Context)) {
				Context->Failed = -1;
			}
			return 0;
		}
		case CSN1C_EXPR_FAIL: {
			Context->Failed = -1;
			return 0;
		}
		default: {
			if ((*Destination) > CSN1C_EXPR_INFINITE) {
				(*Destination) = Context->Program->ExpressionMap [ExpressionId] (Context);
				/* Expression returned a value out of range */
				ED_ASSERT_FORCE_FAIL
				Context->Failed = -1;
				return 0;
			}
		}
	}
	return 1;
}

/*------------------------------------------------------------------------------
	CSN.1 Compact - DECODE/ENCODE function
	It returns the number of bits used or <0 in case of error.
------------------------------------------------------------------------------*/
ED_EXLONG CSN1C_Process (TCSN1CContext* Context, int (*LabelCallBack)(TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL) ED_EXTRAPARAMS_DECL)
{
	unsigned ED_EXLONG StartOffset;
	int IsWriting, Backtracked, LoopTerminated;
	
	TCSN1CLabelCallback FieldCallbackParam;
	
	FieldCallbackParam.Context = Context;
	
	Context->FinalOffset = Context->CurrOfs + Context->Length;
	StartOffset = Context->CurrOfs;
	Context->StartOfs = Context->CurrOfs;
	Context->Continue = -1;
	
	for (;;) {
		unsigned char Instruction;
		unsigned ED_EXLONG Value1=0, Value2=0, Value3=0, Value4=0, IsTerminal;
		unsigned CurrentInstruction = Context->NextInstruction;

		CSN1C_DEBUG_CHECK (Context)

		if (Context->Failed) {
#ifdef CSN1C_DEBUG_TRACE
			CSN1C_DEBUG_TRACE_CONDITION_START
			fprintf (CSN1C_TRACE_FILE, "Context set to failed\n");
			CSN1C_DEBUG_TRACE_CONDITION_END
#endif							
			return -1;
		}
		
		if (!Context->Continue) {
			return (Context->CurrOfs - StartOffset);
		}

		FieldCallbackParam.SuggestedValue = 0;
		FieldCallbackParam.SuggestedValueLengthInBits = -1;

		assert ((Context->CheckEnd == CSN1C_NO_CHECKEND) || (Context->FinalOffset == (ED_EXLONG)Context->CheckEnd));
		
		Backtracked = 0;
		
		/* Set to true only if encoding and CheckEnd <= CurrOfs */
		IsWriting = (Context->ForceReading ? 0 : (Context->Encoding ? ((Context->CheckEnd == CSN1C_NO_CHECKEND) ? 1 : 0) : 0));
			
		CSN1C_FLUSH_TRACE_FILE
		assert (Context->NextInstruction < Context->Program->ProgramLength);

		/* Get the next instruction */
		Instruction = Context->Program->ProgramCode [Context->NextInstruction];

		/* If the instruction is not in the format 00xxxxxx, it is one of the
		   one-byte optimized instructions. In order to be able to use the
		   switch statement, it is necessary to reset the Value bits. */
		if ((Instruction & 0xC0) != 0) {
			if ((Instruction & CSN1C_BIT_A_CMD) == CSN1C_BIT_A_CMD) {
				Value1 = (Instruction & 0x3F);
			} else {
				Value1 = ((Instruction & 0x3F) << 8) | Context->Program->ProgramCode [++(Context->NextInstruction)];
			}
			Instruction &= 0xC0;
		}
		Context->NextInstruction++;

		
		/* Execute the instruction */
		switch (Instruction) {

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_LABEL_BEGIN
				
				At bit Context->CurrOfs of the input buffer begins the label which
				label id is "Value1". The mappings between label ids and the 
				original label names can be done by referring to the CSN1LABEL_xxx
				macros.
				Each CSN1C_LABEL_BEGIN is matched by a corresponding CSN1C_LABEL_END
				that marks the range covered by the CSN.1 label.
			----------------------------------------------------------------------*/
			case CSN1C_LABEL_BEGIN: {
				assert (Context->Top < CSN1C_STACK_SIZE);

				/* Read the field entry */
				Value1 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));
				
				/* Extract the term value (less significant bit) and the real label id */
				IsTerminal = (Value1 & 1);
				Value1 >>= 1;
				
				/* Push the stack position on the stack */
				CSN1C_Push (Context, 0, C1_NONE);
				Context->Elements [Context->Top-1].InsideInfiniteLoop = 0;

				/* Debug trace */
				CSN1C_TRACE1("LABEL_BEGIN");

#ifndef CSN1C_DISABLE_ADT
				/* Handle ADTs */
				if (Context->HostFieldId != CSN1C_PAIRSET_TYPE_INVALID_VALUE) {
					CSN1C_EnterField (Context, CSN1C_FieldEntry2FieldId (Context, Value1, 0));
				}
#endif				
				/* If a callback function has been defined and the label is not terminal, invoke it */
				if (LabelCallBack && (Context->Encoding || !IsTerminal) && !Context->ForceReading && (Context->NestingLevel == 0)) {
#ifndef CSN1C_DISABLE_ADT
					FieldCallbackParam.FieldId = Value1;
					FieldCallbackParam.LabelId = Context->Program->FieldIdPairSet [Value1-1];
#else					
					FieldCallbackParam.LabelId = Value1;
#endif
					FieldCallbackParam.From = Context->CurrOfs;
					FieldCallbackParam.Length = 0;
					FieldCallbackParam.Kind = (IsTerminal? CSN1C_TerminalLabel : CSN1C_LabelStart);
					
#ifdef CSN1C_ENABLE_LABEL_SIZE
					if (Context->Encoding && IsTerminal) {
						FieldCallbackParam.Length = Context->Program->LabelSizes [FieldCallbackParam.LabelId];
					}
#endif
					switch (LabelCallBack (&FieldCallbackParam ED_EXTRAPARAMS_CALL)) {
						case CSN1C_CB_BACKTRACK: {
							if (!CSN1C_Backtrack (Context)) return -1;
							break;
						}
						case CSN1C_CB_OK: {
							/* If we are encoding and this is a terminal, we expect the callback function to give
								us the data we need to continue encoding */
							if (Context->Encoding && (IsTerminal || FieldCallbackParam.Length > 0)) {
								assert (Context->NestingLevel == 0);
								Context->CheckEnd = Context->CurrOfs + FieldCallbackParam.Length;
								Context->FinalOffset = Context->CheckEnd;
								Context->NestingLevel = 1;
							}
							break;
						}
						case CSN1C_CB_FAIL: return -1;
					}

				} else {
					/* If encoding feeding label */
					if (Context->CheckEnd != CSN1C_NO_CHECKEND) {
						assert (Context->NestingLevel >= 1);
						Context->NestingLevel++;
					}
				}

				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_LABEL_END
				
				At bit Context->CurrOfs of the input buffer we have the first bit
				that is not part of the label. See also CSN1C_LABEL_BEGIN.
			----------------------------------------------------------------------*/
			case CSN1C_LABEL_END_TAG:
			case CSN1C_LABEL_END: {
				assert (Context->Top < CSN1C_STACK_SIZE);
				assert (Context->Top > 0);

				/* Read the label id */
				Value1 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* Pop the stack position left on the stack. Now, we know that our
				   label goes from Value2 to Context->CurrOfs */
				CSN1C_AssertHasTopValue (Context);
				Value2 = CSN1C_TopCurrOfs (Context);

				/* Extract the term value (less significant bit) and the real label id */
				IsTerminal = (Value1 & 1);
				Value1 >>= 1;

				/* Debug trace */
				CSN1C_TRACE2("LABEL_END");
				
				/* If CheckEnd is active, then there must be some nesting level */
				assert ((Context->CheckEnd == CSN1C_NO_CHECKEND) || (Context->NestingLevel > 0));
				
				/* If encoding feeding label */
				if (Context->CheckEnd != CSN1C_NO_CHECKEND) {
					if ((Context->NestingLevel == 1) && (Context->CurrOfs != Context->CheckEnd)) {
						/* The encoded data length doesn't match the required length */
						if (!CSN1C_Backtrack (Context)) return -1; else Backtracked = 1;
					}
					Context->NestingLevel--;
					if (Context->NestingLevel == 0) {
						Context->CheckEnd = CSN1C_NO_CHECKEND;
					}
				} 
				if (Context->CheckEnd == CSN1C_NO_CHECKEND) {
					
#ifndef CSN1C_DISABLE_ADT
					/* Handle ADTs */
					if (!Backtracked && Context->HostFieldId != CSN1C_PAIRSET_TYPE_INVALID_VALUE) {
						CSN1C_ExitField (Context, CSN1C_FieldEntry2FieldId (Context, Value1, 1));
					}
#endif				
					
					/* If a callback function has been defined, invoke it. This is invoked
						only if decoding or, if encoding, if the label is not terminal. */
					if (LabelCallBack && !(Context->Encoding && IsTerminal) && !Context->ForceReading && (Context->NestingLevel == 0)) {
#ifndef CSN1C_DISABLE_ADT
						FieldCallbackParam.FieldId = Value1;
						FieldCallbackParam.LabelId = Context->Program->FieldIdPairSet [Value1-1];
#else					
						FieldCallbackParam.LabelId = Value1;
#endif
						FieldCallbackParam.From = Value2;
						FieldCallbackParam.Length = Context->CurrOfs-Value2;
						FieldCallbackParam.Kind = (IsTerminal? CSN1C_TerminalLabel : CSN1C_LabelEnd);
						switch (LabelCallBack (&FieldCallbackParam ED_EXTRAPARAMS_CALL)) {
							case CSN1C_CB_BACKTRACK: {
								if (!CSN1C_Backtrack (Context)) return -1; else Backtracked = 1;
								break;
							}
							case CSN1C_CB_OK: break;
							case CSN1C_CB_FAIL: return -1;
						}
					}
				}

				if (!Backtracked) {
					/* Context->FieldState.UserTagTop = Context->Elements [Context->Top-1].FieldState.UserTagTop; */
					CSN1C_Pop (Context);
				}

				/* If we are required to push the value, we do it */				
				if (!Backtracked && Instruction == CSN1C_LABEL_END_TAG) {
					/* Make sure we aren't tagging something which is too big */
					CSN1C_FLUSH_TRACE_FILE
					assert (Context->CurrOfs-Value2 <= (sizeof (int) << 3));
					/* Read the tag id */
					Value3 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));
					CSN1C_PushValue (Context, Value3, EDBitsToInt (Context->Buffer, Value2, Context->CurrOfs-Value2));
				}

				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_LABEL_A

				Same thing as:
					LABEL_BEGIN (label_entry)
					BIT_A (reps)
					LABEL_END (label_entry)


				INSTRUCTION: CSN1C_LABEL_VALUE
				It expects a string having a given fixed value.
				Same thing as:
					LABEL_BEGIN (label_entry)
					VALUE (value)
					LABEL_END (label_entry)
					
				Obviously, the label is considered "terminal".
			----------------------------------------------------------------------*/
			case CSN1C_LABEL_VALUE:
			case CSN1C_LABEL_A: {

				/* Read the label id */
				Value1 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* Read the number of repetitions */
				Value2 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				if (Instruction == CSN1C_LABEL_VALUE) {
					Value3 = Value2;
					Value2 = (Value3 & 0x0F)+1;
					Value3 >>= 4;
					FieldCallbackParam.SuggestedValue = Value3;
					FieldCallbackParam.SuggestedValueLengthInBits = Value2;
				}

				/* Debug trace */
#ifdef CSN1C_DEBUG_TRACE
				CSN1C_DEBUG_TRACE_CONDITION_START
				if (Instruction == CSN1C_LABEL_A) {CSN1C_TRACE2("LABEL_A");}
				else {CSN1C_TRACE2("LABEL_VALUE");}
				CSN1C_DEBUG_TRACE_CONDITION_END
#endif

				if ((Instruction == CSN1C_LABEL_VALUE) && (!Context->Encoding || Context->ForceReading)) {
					if (((ED_EXLONG)(Context->CurrOfs+Value2) > Context->FinalOffset) || (EDBitsToInt (Context->Buffer, Context->CurrOfs, Value2) != (int)Value3)) {
						if (!CSN1C_Backtrack (Context)) return -1;
						break;
					}
				}
				
				Backtracked = 0;
				
				/* If not encoding, there must be enough bits */
				if (!Context->Encoding && (((ED_EXLONG)(Context->CurrOfs+Value2)) > Context->FinalOffset)) {
					if (!CSN1C_Backtrack (Context)) return -1;
				}
				else {

#ifndef CSN1C_DISABLE_ADT
					/* Handle ADTs */
					if (Context->HostFieldId != CSN1C_PAIRSET_TYPE_INVALID_VALUE) {
						CSN1C_EnterField (Context, CSN1C_FieldEntry2FieldId (Context, Value1, 0));
						if (!Context->Encoding) {
							Context->CurrOfs += Value2;
							CSN1C_ExitField (Context, CSN1C_FieldEntry2FieldId (Context, Value1, 1));
							Context->CurrOfs -= Value2;
						}
					}
#endif				

					/* Invoke the callback function if available */
					if (LabelCallBack && !Context->ForceReading && (Context->NestingLevel == 0)) {
#ifndef CSN1C_DISABLE_ADT
						FieldCallbackParam.FieldId = Value1;
						FieldCallbackParam.LabelId = Context->Program->FieldIdPairSet [Value1-1];
#else					
						FieldCallbackParam.LabelId = Value1;
#endif
						FieldCallbackParam.From = Context->CurrOfs;
						FieldCallbackParam.Length = Value2;
						FieldCallbackParam.Kind = CSN1C_TerminalLabel;
						
						switch (LabelCallBack (&FieldCallbackParam ED_EXTRAPARAMS_CALL)) {
							case CSN1C_CB_BACKTRACK: {
								if (!CSN1C_Backtrack (Context)) return -1; else Backtracked = 1;
								break;
							}
							case CSN1C_CB_OK: {
								/* If we are encoding and this is a terminal, we expect the callback function to give
									us the data we need to continue encoding */
								if (Context->Encoding && FieldCallbackParam.Length != (ED_EXLONG)Value2) {
									if (!CSN1C_Backtrack (Context)) return -1; else Backtracked = 1;
								}
								break;
							}
							case CSN1C_CB_FAIL: return -1;
						}
					}
					if (!Backtracked) {
						Context->CurrOfs += Value2;				
#ifndef CSN1C_DISABLE_ADT
						/* Handle ADTs */
						if (Context->Encoding && Context->HostFieldId != CSN1C_PAIRSET_TYPE_INVALID_VALUE) {
							CSN1C_ExitField (Context, CSN1C_FieldEntry2FieldId (Context, Value1, 1));
						}						
#endif
						if ((Instruction == CSN1C_LABEL_VALUE) && Context->Encoding && !Context->ForceReading) {
							if (EDBitsToInt (Context->Buffer, Context->CurrOfs-Value2, Value2) != (int)Value3) {
								if (!CSN1C_Backtrack (Context)) return -1;
							}
						}
					}
				}				
				break;
			}
			
			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_CHOICE_NODE
				
				This instruction marks a "choice" node. This instructions pushes
				on Context a backtrack entry. 
			----------------------------------------------------------------------*/
			case CSN1C_CHOICE_NODE_CMD: {
				/* Determine whether it is a VBIT or a FBIT. If it is a FBIT, skip it
				   if inside a variable loop. */
				Value2 = ((Value1 & 0x2000) ? 1 /* FBIT */ : 0 /* VBIT */);
				
				/* Jump address */
				Value3 = CSN1C_ResolveCRelPos (Context->NextInstruction-2, (Value1 & 0x1FFF));
				
				if (Value2 && IsWriting && Context->Top > 0 && Context->Elements [Context->Top-1].InsideInfiniteLoop) {
					/* Context->NextInstruction += ((Value1 & 0x1FFF) - 2); */
					Context->NextInstruction = Value3;
					/* Debug trace */
					CSN1C_TRACE1("CHOICE_NODE_CMD(skip FBITs)");
				} else {
					/* Push a backtrack entry */
					/* CSN1C_Push (Context, Context->NextInstruction + (Value1 & 0x1FFF) - 2, 1, 0, 0); */
					CSN1C_Push (Context, Value3, C1_BACKTRACK);
					/* Debug trace */
					CSN1C_TRACE1("CHOICE_NODE_CMD");
				}

				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_CHOICE_END
				
				This instruction is executed when a sucessful branch among several
				choiches is completed. The backtrack anchor left by the choice is
				removed.
			----------------------------------------------------------------------*/
			case CSN1C_CHOICE_END: {
				CSN1C_FLUSH_TRACE_FILE

				/* We expect a backtrack on top of the stack */
				assert (Context->Top > 0);
				assert (Context->Elements [Context->Top-1].Backtrack);
				
				/* Get rid of the backtrack */
				CSN1C_Pop (Context);

				/* Debug trace */
				CSN1C_TRACE0("CHOICE_END");
				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_LOOP_CYCLE
				
				Closes a loop
			----------------------------------------------------------------------*/
			case CSN1C_LOOP_CYCLE: {
				CSN1C_FLUSH_TRACE_FILE
				LoopTerminated = 0;
				/* Parameter 'backoffset' */
				Value1 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* Decrease max counter */
				CSN1C_AssertHasTopValue (Context);
				Value2 = C1_MAX (CSN1C_TopValue (Context));
				if ((Value2 > 0) && (Value2 != CSN1C_EXPR_INFINITE)) {
					CSN1C_AssertHasTopValue (Context);
					C1_SET_MAX (CSN1C_TopValue (Context), Value2-1);
				}
				
				/* Continue only if we aren't done */
				if (Value2 != 1) {
					
					/* Decrease the min counter */
					CSN1C_AssertHasTopValue (Context);
					Value3 = C1_MIN (CSN1C_TopValue (Context));
					if (Value3 > 0) {
						CSN1C_AssertHasTopValue (Context);
						C1_SET_MIN (CSN1C_TopValue (Context), Value3-1);
						
						/* If Value3 was 1, then it means that we now reached 0: we have to upgrade
						   the loop and move it into OPTIONAL mode */
						if (!CSN1C_CheckLoop (Context, Context->NextInstruction)) {
							/* The CheckLoop function didn't jump: let's go back and reloop */
							Context->NextInstruction = CurrentInstruction - Value1;
						}
						else {
							LoopTerminated = 1;
						}
					} else {
						/* Processing the optional part */
						CSN1C_AssertHasTopValue (Context);
						if (Context->Encoding && IsWriting && C1_FBIT (CSN1C_TopValue (Context))) {
							CSN1C_Pop (Context);
							CSN1C_Pop (Context);
						} else {
							Context->NextInstruction = CurrentInstruction - Value1;
						}
					}
					if (!LoopTerminated) {
						CSN1C_AssertHasTopValue (Context);
						if (C1_MIN (CSN1C_TopValue (Context)) == 0) {
							/* Update the backtrack */
							CSN1C_SetTopCurrOfsN (Context, 1, Context->CurrOfs);
							if (Context->Top >= 2) Context->Elements [Context->Top-2].FieldState = Context->FieldState;
						}
					}
				} else {
					CSN1C_Pop (Context);
					CSN1C_Pop (Context);
				}
				/* Debug trace */
				CSN1C_TRACE1("LOOP_CYCLE");
				break;
			};
			
			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_BACKTRACK
				
				Discard everything done so far and go back to the first backtrack
				checkpoint. Then try again with the next choice.
			----------------------------------------------------------------------*/
			case CSN1C_BACKTRACK: {
				/* Debug trace */
				CSN1C_TRACE0("BACKTRACK");

				if (!CSN1C_Backtrack (Context)) return -1;
				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_GOTO
				
				This instruction jumps to a fixed address. The address in the GOTO
				statement is relative to the instruction itself.
			----------------------------------------------------------------------*/
			case CSN1C_GOTO_CMD: {
				Context->NextInstruction = CSN1C_ResolveCRelPos (Context->NextInstruction-2, Value1);
				CSN1C_FLUSH_TRACE_FILE
				assert (Context->NextInstruction < Context->Program->ProgramLength);

				/* Debug trace */
				CSN1C_TRACE1("GOTO_CMD");

				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_GOSUB
				
				Push on the stack a Value describing the return point an jump
				to the given instruction.
			----------------------------------------------------------------------*/
			case CSN1C_GOSUB: {
				Value1 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));
				CSN1C_Push (Context, Context->NextInstruction, C1_NONE);
				Context->NextInstruction = Value1;

				/* Debug trace */
				CSN1C_TRACE1("GOSUB");
				
				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_RETURN
				
				Pop the address from the stack.
			----------------------------------------------------------------------*/
			case CSN1C_RETURN: {
				/* Debug trace */
				CSN1C_TRACE0("RETURN");

				/* If the stack is empty, we're done parsing */
				if (Context->Top == 0) {
					/* Return ok if all the source bits have been consumed */
					return ((Context->CurrOfs == Context->FinalOffset || Context->Encoding || Context->AllowPartialStrings) ? (ED_EXLONG)(Context->CurrOfs - StartOffset) : -1);
				}
				Context->NextInstruction = CSN1C_PopValue (Context);

				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_RETURN_LOOPING
				
				Pop the address from the stack.
			----------------------------------------------------------------------*/
			case CSN1C_RETURN_LOOPING: {
				/* Debug trace */
				CSN1C_TRACE0("CSN1C_RETURN_LOOPING");

				/* If the stack is empty, we're done parsing */
				if (Context->Top == 0) {
					/* Return ok if all the source bits have been consumed */
					return ((Context->CurrOfs == Context->FinalOffset || Context->Encoding || Context->AllowPartialStrings) ? (ED_EXLONG)(Context->CurrOfs - StartOffset) : -1);
				}
				Context->FieldState.UserTagTop = Context->Elements [Context->Top-1].FieldState.UserTagTop;
				Context->NextInstruction = CSN1C_PopValue (Context);

				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_UPDATE_BACKTRACK
				
				Updates the situation of the topmost backtrack instruction to the 
				current state.
				It means that everything got so far has to be kept if a backtracking 
				happens next.
			----------------------------------------------------------------------*/
			case CSN1C_UPDATE_BACKTRACK: {
				/* Debug trace */
				CSN1C_TRACE0("UPDATE_BACKTRACK");

				if (!CSN1C_UpdateBacktrack (Context)) return -1;

				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_BIT_0
				
				Expect a '0' bit or backtrack.
			----------------------------------------------------------------------*/
			case CSN1C_BIT_0: {
				/* Debug trace */
				CSN1C_TRACE0("BIT_0");
				
				if (IsWriting) {
					CSN1C_SetBit0 (Context->Buffer, Context->CurrOfs);
					Context->CurrOfs++;
				} else {
					if ((Context->CurrOfs < Context->FinalOffset) && CSN1C_CheckBit0 (Context->Buffer, Context->CurrOfs)) {
						Context->CurrOfs++;
					} else {
						if (!CSN1C_Backtrack (Context)) return -1;
					}
				}
				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_BIT_1
			----------------------------------------------------------------------*/
			case CSN1C_BIT_1: {
				/* Debug trace */
				CSN1C_TRACE0("BIT_1");
				
				if (IsWriting) {
					CSN1C_SetBit1 (Context->Buffer, Context->CurrOfs);
					Context->CurrOfs++;
				} else {
					if ((Context->CurrOfs < Context->FinalOffset) && CSN1C_CheckBit1 (Context->Buffer, Context->CurrOfs)) {
						Context->CurrOfs++;
					} else {
						if (!CSN1C_Backtrack (Context)) return -1;
					}
				}
				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_BIT_L
			----------------------------------------------------------------------*/
			case CSN1C_BIT_L: {
				/* Debug trace */
				CSN1C_TRACE0("BIT_L");

				if (IsWriting) {
					CSN1C_SetBitL (Context->Buffer, Context->CurrOfs, CSN1C_LH_MASK);
					Context->CurrOfs++;
				} else {
					if ((Context->CurrOfs < Context->FinalOffset) && CSN1C_CheckBitL (Context->Buffer, Context->CurrOfs, CSN1C_LH_MASK)) {
						Context->CurrOfs++;
					} else {
						if (!CSN1C_Backtrack (Context)) return -1;
					}
				}
				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_BIT_H
			----------------------------------------------------------------------*/
			case CSN1C_BIT_H: {
				/* Debug trace */
				CSN1C_TRACE0("BIT_H");
				
				if (IsWriting) {
					CSN1C_SetBitH (Context->Buffer, Context->CurrOfs, CSN1C_LH_MASK);
					Context->CurrOfs++;
				} else {
					if ((Context->CurrOfs < Context->FinalOffset) && CSN1C_CheckBitH (Context->Buffer, Context->CurrOfs, CSN1C_LH_MASK)) {
						Context->CurrOfs++;
					} else {
						if (!CSN1C_Backtrack (Context)) return -1;
					}
				}
				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_BIT_A
			----------------------------------------------------------------------*/
			case CSN1C_BIT_A_CMD: {
				/* Debug trace */
				CSN1C_TRACE1("BIT_A");

				if (Context->Encoding) {
					if (IsWriting) {
						EDIntToBits (Context->Buffer, Context->CurrOfs, 0, Value1);
						Context->CurrOfs += Value1;
					}
					else {
						if (((ED_EXLONG)(Context->CurrOfs+Value1)) <= Context->FinalOffset) {
							Context->CurrOfs += Value1;
						} else {
							if (!CSN1C_Backtrack (Context)) return -1;
						}
					}
				}
				else {
					if (((ED_EXLONG)(Context->CurrOfs+Value1)) <= Context->FinalOffset) {
						Context->CurrOfs += Value1;
					} else {
						if (!CSN1C_Backtrack (Context)) return -1;
					}
				}
				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_EXECUTE or CSN1C_EXECUTE_DEC
			----------------------------------------------------------------------*/
			case CSN1C_EXECUTE: {
				/* Retrieve the instruction id */
				Value1 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));
				
				/* Execute the custom instruction */
				Context->Program->FunctionMap [Value1] (Context ED_EXTRAPARAMS_CALL);
				
				/* Debug trace */
				CSN1C_TRACE1("EXECUTE");
				
				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_EXECUTE_DEC
			----------------------------------------------------------------------*/
			case CSN1C_EXECUTE_DEC:  {
				/* Retrieve the instruction id */
				Value1 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));
				
				if (!Context->Encoding) {
					/* Execute the custom instruction */
					Context->Program->FunctionMap [Value1] (Context ED_EXTRAPARAMS_CALL);

					/* Debug trace */
					CSN1C_TRACE1("EXECUTE_DEC");
				}
				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_EXECUTE_ENC
			----------------------------------------------------------------------*/
			case CSN1C_EXECUTE_ENC: {
				/* Retrieve the instruction id */
				Value1 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));
				
				/* Execute the custom instruction */
				if (Context->Encoding) {
					Context->Program->FunctionMap [Value1] (Context ED_EXTRAPARAMS_CALL);

					/* Debug trace */
					CSN1C_TRACE1("EXECUTE_ENC");
				}


				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_TAG_POS
			----------------------------------------------------------------------*/
			case CSN1C_TAG_POS: {
				Value1 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* Push on the tag stack the current value */
				CSN1C_PushValue (Context, Value1, Context->CurrOfs);
				
				/* Debug trace */
				CSN1C_TRACE1("TAG_POS");

				break;
			}
			
			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_JUMP_IF_ENCODING
			----------------------------------------------------------------------*/
			case CSN1C_JUMP_IF_ENCODING: {
				Value1 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));
				
				if (Context->Encoding) {
					Context->NextInstruction = CurrentInstruction + Value1;
				}
				
				/* Debug trace */
				CSN1C_TRACE1("JUMP_IF_ENCODING");

				break;
			}
			
			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_VALUE
			----------------------------------------------------------------------*/
			case CSN1C_VALUE: {
				/* In this case, the value is made of two parts:
				   - lowest 4 bit is the overall number of bits-1 (0->means 1 bit)
				   - the rest is the 1-16bit value to be encoded
				*/
				Value1 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));
				Value2 = (Value1 & 0x0F)+1;
				Value1 >>= 4;

				/* Debug trace */
				CSN1C_TRACE2("VALUE");

				if (IsWriting) {
					EDIntToBits (Context->Buffer, Context->CurrOfs, Value1, Value2);
					Context->CurrOfs += Value2;
				} else {
					if ((((ED_EXLONG)(Context->CurrOfs+Value2)) <= Context->FinalOffset) && (EDBitsToInt (Context->Buffer, Context->CurrOfs, Value2) == (int)Value1)) {
						Context->CurrOfs += Value2;
					} else {
						if (!CSN1C_Backtrack (Context)) return -1;
					}
				}
				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_PUSH_CURRPOS
			----------------------------------------------------------------------*/
			case CSN1C_PUSH_CURROFS: {
				/* Debug trace */
				CSN1C_TRACE0("PUSH_CURROFS");
				
				/* Push the current position entry */
				CSN1C_Push (Context, Context->CurrOfs, C1_NONE);
				
				break;
			}
			
			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_EXCLUSION_BEGIN
			----------------------------------------------------------------------*/
			case CSN1C_EXCLUSION_BEGIN: {
				/* Extract the offset saved before processing the string under test */
				Value1 = CSN1C_PopValue (Context);

				/* Extract the offset where the exclusion string ends */
				Value2 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* Push a backtrack entry */
				CSN1C_Push (Context, CurrentInstruction + Value2, C1_BACKTRACK);

				/* Push a final offset saver entry */
				CSN1C_Push (Context, Context->FinalOffset, C1_FINAL_OFFSET);
				
				/* Debug trace */
				CSN1C_TRACE2("EXCLUSION_BEGIN");
				
				/* Set up the CurrOffset and FinalOffset to match the string under test */
				Context->FinalOffset = Context->CurrOfs;
				Context->CurrOfs = Value1;

				/* Force reading: we can't write */
				Context->ForceReading = -1;
				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_END_EXCLUSION
			----------------------------------------------------------------------*/
			case CSN1C_EXCLUSION_END: {
				/* Debug trace */
				CSN1C_TRACE0("EXCLUSION_END");

				/* Pop the final offset saved before processing the string under test */
				Value1 = CSN1C_PopValue (Context);
				Context->FinalOffset = Value1;
				
				/* The topmost instruction should be a backtrack inserted by CSN1C_START_EXCLUSION */
				assert ((Context->Top > 0) && (Context->Elements [Context->Top-1].Backtrack));
				CSN1C_Pop (Context);

				/* Now backtrack: if we reach here is because we successfully matched the
				   exclusion string, which shouldn't be matched. */
				if (!CSN1C_Backtrack (Context)) return -1;

				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_INTERSECTION_BEGIN
			----------------------------------------------------------------------*/
			case CSN1C_INTERSECTION_BEGIN: {
				/* Extract the offset saved before processing the string under test */
				Value1 = CSN1C_PopValue (Context);

				/* Push a final offset saver entry */
				CSN1C_Push (Context, Context->FinalOffset, C1_FINAL_OFFSET);

				/* Debug trace */
				CSN1C_TRACE1("INTERSECTION_BEGIN");

				/* Set up the CurrOffset and FinalOffset to match the string under test */
				Context->FinalOffset = Context->CurrOfs;
				Context->CurrOfs = Value1;

				/* Force reading: we can't write */
				Context->ForceReading = -1;
				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_INTERSECTION_END
			----------------------------------------------------------------------*/
			case CSN1C_INTERSECTION_END: {
				/* Debug trace */
				CSN1C_TRACE0("INTERSECTION_END");

				/* Pop the final offset saved before processing the string under test */
				Value1 = CSN1C_PopValue (Context);

				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_NOP
				
				Do nothing
			----------------------------------------------------------------------*/
			case CSN1C_NOP: {
				/* Debug trace */
				CSN1C_TRACE0("NOP");
				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_LOOP_BEGIN_INFINITE

				min=0 max=INFINITE
			----------------------------------------------------------------------*/
			case CSN1C_LOOP_BEGIN_INFINITE: {
				CSN1C_FLUSH_TRACE_FILE

				/* Parameter 'relpos' */
				Value1 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* min=0 max=INFINITE */
				/* Setup the loop */
				CSN1C_SetupLoop (Context, CurrentInstruction, Value1 /*relpos*/, 0, CSN1C_EXPR_INFINITE);

				/* Debug trace */
				CSN1C_TRACE1("LOOP_BEGIN_INFINITE");
				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_LOOP_BEGIN_INF_MIN

				min=1 max=INFINITE
			----------------------------------------------------------------------*/
			case CSN1C_LOOP_BEGIN_INF_MIN: {
				CSN1C_FLUSH_TRACE_FILE

				/* Parameter 'relpos' */
				Value1 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* min=0 max=INFINITE */
				/* Setup the loop */
				CSN1C_SetupLoop (Context, CurrentInstruction, Value1 /*relpos*/, 1, CSN1C_EXPR_INFINITE);

				/* Debug trace */
				CSN1C_TRACE1("LOOP_BEGIN_INF_MIN");
				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_LOOP_BEGIN_FIXED

				min=max=N
			----------------------------------------------------------------------*/
			case CSN1C_LOOP_BEGIN_FIXED: {
				CSN1C_FLUSH_TRACE_FILE

				/* Parameter 'relpos' */
				Value1 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* Parameter 'N' */
				Value2 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* min=max=N */
				/* Setup the loop */
				CSN1C_SetupLoop (Context, CurrentInstruction, Value1 /*relpos*/, Value2 /*min*/, Value2 /*max*/);

				/* Debug trace */
				CSN1C_TRACE2("LOOP_BEGIN_FIXED");
				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_LOOP_BEGIN_FIXED_TAG

				min=max=TAG(tagid)
			----------------------------------------------------------------------*/
			case CSN1C_LOOP_BEGIN_FIXED_TAG: {
				CSN1C_FLUSH_TRACE_FILE

				/* Parameter 'relpos' */
				Value1 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* Parameter 'tagid' */
				Value2 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* min=max=TAG(tagid) */
				Value3 = CSN1C_GetValue (Context, Value2);
				
				/* Setup the loop */
				CSN1C_SetupLoop (Context, CurrentInstruction, Value1 /*relpos*/, Value3 /*min*/, Value3 /*max*/);

				/* Debug trace */
				CSN1C_TRACE3("LOOP_BEGIN_FIXED_TAG");
				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_LOOP_BEGIN_FIXED_OPTVAL

				min=max=OPTVAL (TAG(tagid),position)
			----------------------------------------------------------------------*/
			case CSN1C_LOOP_BEGIN_FIXED_OPTVAL: {
				CSN1C_FLUSH_TRACE_FILE

				/* Parameter 'relpos' */
				Value1 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* Parameter 'tagid' */
				Value2 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* Parameter 'position' */
				Value3 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* min=max=OPTVAL (TAG(tagid),position) */
				Value4 = EDBitsToInt (Context->Buffer, CSN1C_GetValue (Context, Value2)+Value3, 1);

				/* Setup the loop */
				CSN1C_SetupLoop (Context, CurrentInstruction, Value1 /*relpos*/, Value4 /*min*/, Value4 /*max*/);

				/* Debug trace */
				CSN1C_TRACE4("LOOP_BEGIN_FIXED_OPTVAL");
				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_LOOP_BEGIN_MINMAX

				min=M max=N
			----------------------------------------------------------------------*/
			case CSN1C_LOOP_BEGIN_MINMAX: {
				CSN1C_FLUSH_TRACE_FILE

				/* Parameter 'relpos' */
				Value1 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* Parameter 'M' */
				Value2 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* Parameter 'N' */
				Value3 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* min=M max=N */
				/* Setup the loop */
				CSN1C_SetupLoop (Context, CurrentInstruction, Value1 /*relpos*/, Value2 /*min*/, Value3 /*max*/);

				/* Debug trace */
				CSN1C_TRACE3("LOOP_BEGIN_MINMAX");
				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_LOOP_BEGIN_VAR_ED1

				min=max=expr()
			----------------------------------------------------------------------*/
			case CSN1C_LOOP_BEGIN_VAR_ED1: {
				CSN1C_FLUSH_TRACE_FILE

				/* Parameter 'relpos' */
				Value1 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* Parameter 'expr' */
				Value2 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* min=max=expr() */
				if (CSN1C_InvokeExpression (Context, Value2, &Value4)) {

					/* Setup the loop */
					CSN1C_SetupLoop (Context, CurrentInstruction, Value1 /*relpos*/, Value4 /*min*/, Value4 /*max*/);
				}
				
				/* Debug trace */
				CSN1C_TRACE2("LOOP_BEGIN_VAR_ED1");
				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_LOOP_BEGIN_VAR_ED2

				If encoding: min=max=exprEnc()
				If decoding: min=max=exprDec()
			----------------------------------------------------------------------*/
			case CSN1C_LOOP_BEGIN_VAR_ED2: {
				CSN1C_FLUSH_TRACE_FILE

				/* Parameter 'relpos' */
				Value1 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* Parameter 'exprEnc' */
				Value2 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* Parameter 'exprDec' */
				Value3 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* min=max=exprEnc() */
				Value4 = (Context->Encoding ? Value2 : Value3);
				
				/* min=max=expr() */
				if (CSN1C_InvokeExpression (Context, Value4, &Value4)) {

					/* Setup the loop */
					CSN1C_SetupLoop (Context, CurrentInstruction, Value1 /*relpos*/, Value4 /*min*/, Value4 /*max*/);
				}
				
				/* Debug trace */
				CSN1C_TRACE3("LOOP_BEGIN_VAR_ED2");
				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_LOOP_BEGIN_VAR_ED_INF

				If encoding: min=max=exprEnc()
				If decoding: min=0 max=INFINITE
			----------------------------------------------------------------------*/
			case CSN1C_LOOP_BEGIN_VAR_ED_INF: {
				CSN1C_FLUSH_TRACE_FILE

				/* Parameter 'relpos' */
				Value1 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* Parameter 'exprEnc' */
				Value2 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				if (Context->Encoding) {
					/* min=max=exprEnc() */
				/* min=max=expr() */
					if (CSN1C_InvokeExpression (Context, Value2, &Value4)) {

						/* Setup the loop */
						CSN1C_SetupLoop (Context, CurrentInstruction, Value1 /*relpos*/, Value4 /*min*/, Value4 /*max*/);
					}
				} else {
					/* min=0 max=INFINITE */
					/* Setup the loop */
					CSN1C_SetupLoop (Context, CurrentInstruction, Value1 /*relpos*/, 0 /*min*/, CSN1C_EXPR_INFINITE /*max*/);
				};


				/* Debug trace */
				CSN1C_TRACE2("LOOP_BEGIN_VAR_ED_INF");
				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_LOOP_SET_MIN_FIXED

				min=n
			----------------------------------------------------------------------*/
			case CSN1C_LOOP_SET_MIN_FIXED: {
				CSN1C_FLUSH_TRACE_FILE

				/* Parameter 'n' */
				Value1 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* min=n */
				/* Update the minimum value in a loop */
				CSN1C_SetupLoopMin (Context, Value1 /*min*/);

				/* Debug trace */
				CSN1C_TRACE1("LOOP_SET_MIN_FIXED");
				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_LOOP_SET_MIN_ED1

				min=expr()
			----------------------------------------------------------------------*/
			case CSN1C_LOOP_SET_MIN_ED1: {
				CSN1C_FLUSH_TRACE_FILE

				/* Parameter 'expr' */
				Value1 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* min=expr() */
				if (CSN1C_InvokeExpression (Context, Value1, &Value2)) {

					/* Update the minimum value in a loop */
					CSN1C_SetupLoopMin (Context, Value2 /*min*/);
				}


				/* Debug trace */
				CSN1C_TRACE1("LOOP_SET_MIN_ED1");
				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_LOOP_SET_MIN_ED2

				If encoding: min=exprEnc() if encoding
				If decoding: min=exprDec() if decoding
			----------------------------------------------------------------------*/
			case CSN1C_LOOP_SET_MIN_ED2: {
				CSN1C_FLUSH_TRACE_FILE

				/* Parameter 'exprEnc' */
				Value1 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* Parameter 'exprDec' */
				Value2 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* min=max=exprEnc() */
				Value3 = (Context->Encoding ? Value1 : Value2);

				/* min=expr() */
				if (CSN1C_InvokeExpression (Context, Value3, &Value4)) {

					/* Update the minimum value in a loop */
					CSN1C_SetupLoopMin (Context, Value4 /*min*/);
				}

				/* Debug trace */
				CSN1C_TRACE2("LOOP_SET_MIN_ED2");
				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_SUBCLASS_SINGLE (tag, value)
			----------------------------------------------------------------------*/
			case CSN1C_SUBCLASS_SINGLE: {
				CSN1C_FLUSH_TRACE_FILE

				/* Parameter 'tag' */
				Value1 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* Parameter 'value' */
				Value2 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* Number to be checked */
				Value4 = CSN1C_GetValue (Context, Value1);
				Value4 = EDBitsToInt (Context->Buffer, Value4, Context->CurrOfs - Value4);

				/* Check the value */
				if (Value4 != Value2) {
					if (!CSN1C_Backtrack (Context)) return -1;
				}

				/* Debug trace */
				CSN1C_TRACE2("SUBCLASS_SINGLE");
				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_SUBCLASS_RANGE (tag, valueMin, valueMax)
			----------------------------------------------------------------------*/
			case CSN1C_SUBCLASS_RANGE: {
				CSN1C_FLUSH_TRACE_FILE

				/* Parameter 'tag' */
				Value1 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* Parameter 'valueMin' */
				Value2 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* Parameter 'valueMax' */
				Value3 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* Number to be checked */
				Value4 = CSN1C_GetValue (Context, Value1);
				Value4 = EDBitsToInt (Context->Buffer, Value4, Context->CurrOfs - Value4);

				/* Check the value */
				if (Value4 < Value2 || Value4 > Value3) {
					if (!CSN1C_Backtrack (Context)) return -1;
				}

				/* Debug trace */
				CSN1C_TRACE3("SUBCLASS_RANGE");
				break;
			}
			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_SUBCLASS_SINGLE_EXPR (tag, exprValue)
			----------------------------------------------------------------------*/
			case CSN1C_SUBCLASS_SINGLE_EXPR: {
				CSN1C_FLUSH_TRACE_FILE

				/* Parameter 'tag' */
				Value1 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* Parameter 'value' */
				Value2 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));
				Value2 = Context->Program->ExpressionMap [Value2] (Context);

				/* Number to be checked */
				Value4 = CSN1C_GetValue (Context, Value1);
				Value4 = EDBitsToInt (Context->Buffer, Value4, Context->CurrOfs - Value4);

				/* Check the value */
				if (Value4 != Value2) {
					if (!CSN1C_Backtrack (Context)) return -1;
				}

				/* Debug trace */
				CSN1C_TRACE2("SUBCLASS_SINGLE_EXPR");
				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_SUBCLASS_RANGE_EXPR (tag, exprMin, exprMax)
			----------------------------------------------------------------------*/
			case CSN1C_SUBCLASS_RANGE_EXPR: {
				CSN1C_FLUSH_TRACE_FILE

				/* Parameter 'tag' */
				Value1 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));

				/* Parameter 'valueMin' */
				Value2 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));
				Value2 = Context->Program->ExpressionMap [Value2] (Context);

				/* Parameter 'valueMax' */
				Value3 = CSN1C_ReadExtVal (Context->Program, &(Context->NextInstruction));
				Value3 = Context->Program->ExpressionMap [Value3] (Context);

				/* Number to be checked */
				Value4 = CSN1C_GetValue (Context, Value1);
				Value4 = EDBitsToInt (Context->Buffer, Value4, Context->CurrOfs - Value4);

				/* Check the value */
				if (Value4 < Value2 || Value4 > Value3) {
					if (!CSN1C_Backtrack (Context)) return -1;
				}

				/* Debug trace */
				CSN1C_TRACE3("SUBCLASS_RANGE_EXPR");
				break;
			}

			/*----------------------------------------------------------------------
				INSTRUCTION: CSN1C_FORCED_NULL
			----------------------------------------------------------------------*/
			case CSN1C_FORCED_NULL: {
				CSN1C_FLUSH_TRACE_FILE

				/* Check the value */
				if ((!Context->Encoding) && (Context->CurrOfs < Context->FinalOffset)) {
					if (!CSN1C_Backtrack (Context)) return -1;
				}

				/* Debug trace */
				CSN1C_TRACE0("CSN1C_FORCED_NULL");
				break;
			}			
		}
	}
	CSN1C_DEBUG_CHECK (Context)
}

/*------------------------------------------------------------------------------
	Debug mode function used to ensure CSN.1 Context integrity
------------------------------------------------------------------------------*/
#ifdef CSN1C_DEBUG_MODE
void CSN1C_DEBUG_CheckContext (const TCSN1CContext* Context)
{
	assert (Context->CheckSignature1 == CSN1C_DEBUG_SIGNATURE_1);
	assert (Context->CheckSignature2 == CSN1C_DEBUG_SIGNATURE_2);
	assert (Context->CheckSignature3 == CSN1C_DEBUG_SIGNATURE_3);
	assert (Context->CheckSignature4 == CSN1C_DEBUG_SIGNATURE_4);
	assert (Context->CheckSignature5 == CSN1C_DEBUG_SIGNATURE_5);
}
#endif
