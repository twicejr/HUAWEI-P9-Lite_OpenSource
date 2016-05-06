/*******************************************************************************
  csn1lib.c  Developed by Dafocus - http://www.dafocus.com/
*******************************************************************************/
#include "csn1lib.h"
#include <assert.h>
#include <stdio.h>

/*lint -e502*/
/*lint -e451*/
/*lint -e702*/
/*lint -e506*/

/*#define CSNLIBDEBUG*/
#ifdef CSN1_GLOBAL_STACK
#ifdef CSN1_OLD_ENCODER
		TCSN1Stack CSN1_Stack;
#else 
		TCSN1Context DataCSN1Context;
#endif
#endif

#ifdef CSNLIBDEBUG
int csn1LogCounter = 0;
#endif

/*==============================================================================
	Section devoted to the TABLE CSN.1 code generator.
==============================================================================*/
#ifndef CSN1_OLD_ENCODER

/*------------------------------------------------------------------------------
	Function for entry CSN1_STACKPUSH_NBT
------------------------------------------------------------------------------*/
unsigned CSN1_Execute_STACKPUSH_NBT (const unsigned char* TableMemory, unsigned Offset, TCSN1Context* CSN1Context)
{
	TCSN1NextType actionPtr;
	TableMemory += Offset;
	actionPtr = (TCSN1NextType)((TableMemory[1] << 16) | (TableMemory[2] << 8) | TableMemory[3]);
	CSN1_StackPush (&CSN1Context->CSN1_Stack, actionPtr, CSN1_NO_BACKTRACK, 1, -1, 0);
	return Offset + 4;
}


/*------------------------------------------------------------------------------
	Function for entry CSN1_STACKPUSH_XNBT
------------------------------------------------------------------------------*/
unsigned CSN1_Execute_STACKPUSH_XNBT (const unsigned char* TableMemory, unsigned Offset, TCSN1Context* CSN1Context)
{
	TCSN1NextType actionPtr;
	int repetitions;
	int popUserTags;
	int options;

	TableMemory += Offset;
	actionPtr = (TCSN1NextType)((TableMemory[1] << 16) | (TableMemory[2] << 8) | TableMemory[3]);
	repetitions = (int)((char)TableMemory[4]);
	popUserTags = (int)((char)TableMemory[5]);
	options = (int)((char)TableMemory[6]);

	CSN1_StackPush (&CSN1Context->CSN1_Stack, actionPtr, CSN1_NO_BACKTRACK, repetitions, popUserTags, options);
	return Offset + 7;
}

/*------------------------------------------------------------------------------
	Function for entry CSN1_STACKPUSH_UTOP
------------------------------------------------------------------------------*/
unsigned CSN1_Execute_STACKPUSH_UTOP (const unsigned char* TableMemory, unsigned Offset, TCSN1Context* CSN1Context)
{
	CSN1_StackPush (&CSN1Context->CSN1_Stack, CSN1_NULL, CSN1_NO_BACKTRACK, 1, CSN1Context->CSN1_Stack.fieldState.userTagTop, 0);
	return Offset + 1;
}


/*------------------------------------------------------------------------------
	Function for entry CSN1_STACKPUSH_TRK
------------------------------------------------------------------------------*/
unsigned CSN1_Execute_STACKPUSH_TRK (const unsigned char* TableMemory, unsigned Offset, TCSN1Context* CSN1Context)
{
	TCSN1NextType actionPtr;
	int repetitions;
	
	TableMemory += Offset;
	actionPtr = (TCSN1NextType)((TableMemory[1] << 16) | (TableMemory[2] << 8) | TableMemory[3]);
	repetitions = (int)((char)TableMemory[4]);
	
	CSN1_StackPush (&CSN1Context->CSN1_Stack, actionPtr, CSN1Context->CurrOfs, repetitions, -1, 0);
	return Offset + 5;
}

/*------------------------------------------------------------------------------
	Function for entry CSN1_STACKPUSH_INFR
------------------------------------------------------------------------------*/
unsigned CSN1_Execute_STACKPUSH_INFR (const unsigned char* TableMemory, unsigned Offset, TCSN1Context* CSN1Context)
{
	TCSN1NextType actionPtr;
	int popUserTags;
	int options;

	TableMemory += Offset;
	actionPtr = (TCSN1NextType)((TableMemory[1] << 16) | (TableMemory[2] << 8) | TableMemory[3]);
	popUserTags = (int)((char)TableMemory[4]);
	options = (int)((char)TableMemory[5]);

	CSN1_StackPush (&CSN1Context->CSN1_Stack, actionPtr, CSN1_NO_BACKTRACK, INFINITE_REPETITIONS, popUserTags, options);
	return Offset + 6;
}
/*------------------------------------------------------------------------------
	Function for entry CSN1_ENTER_FLD
------------------------------------------------------------------------------*/
unsigned CSN1_Execute_ENTER_FLD (const unsigned char* TableMemory, unsigned Offset, TCSN1Context* CSN1Context)
{
	int fieldId;
	
	TableMemory += Offset;
	fieldId = (int)((TableMemory[1] << 8) | TableMemory[2]);
	
	CSN1_EnterField (&CSN1Context->CSN1_Stack, fieldId, CSN1Context->CurrOfs);
	return Offset + 3;
}


/*------------------------------------------------------------------------------
	Function for entry CSN1_EXIT_FIELD
------------------------------------------------------------------------------*/
unsigned CSN1_Execute_EXIT_FIELD (const unsigned char* TableMemory, unsigned Offset, TCSN1Context* CSN1Context)
{
	int fieldId;
	TableMemory += Offset;
	fieldId = (int)((TableMemory[1] << 8) | TableMemory[2]);
	CSN1_ExitField (&CSN1Context->CSN1_Stack, fieldId, CSN1Context->CurrOfs);
	return Offset + 3;
}


/*------------------------------------------------------------------------------
	Function for entry CSN1_TERM_LOOP
------------------------------------------------------------------------------*/
unsigned CSN1_Execute_TERM_LOOP (const unsigned char* TableMemory, unsigned Offset, TCSN1Context* CSN1Context)
{
	CSN1_TerminateLoop (&CSN1Context->CSN1_Stack);
	return Offset + 1;
}


/*------------------------------------------------------------------------------
	Function for entry CSN1_DECOCASE_0
------------------------------------------------------------------------------*/
unsigned CSN1_Execute_DECOCASE_0 (const unsigned char* TableMemory, unsigned Offset, TCSN1Context* CSN1Context)
{
	if ((CSN1Context->CurrOfs <= CSN1Context->End-CSN1Context->LocalRepetitions) && (EDBitsToInt (CSN1Context->Buffer, CSN1Context->CurrOfs, 1) == 0)) {
		CSN1Context->CurrOfs+=CSN1Context->LocalRepetitions;
	}
	else {
		CSN1_StackBacktrack (&CSN1Context->CSN1_Stack, &CSN1Context->CurrOfs);
	}
	return Offset + 1;
}


/*------------------------------------------------------------------------------
	Function for entry CSN1_DECOCASE_1
------------------------------------------------------------------------------*/
unsigned CSN1_Execute_DECOCASE_1 (const unsigned char* TableMemory, unsigned Offset, TCSN1Context* CSN1Context)
{
	if ((CSN1Context->CurrOfs <= CSN1Context->End-CSN1Context->LocalRepetitions) && (EDBitsToInt (CSN1Context->Buffer, CSN1Context->CurrOfs, 1) == 1)) {
		CSN1Context->CurrOfs+=CSN1Context->LocalRepetitions;
	}
	else {
		CSN1_StackBacktrack (&CSN1Context->CSN1_Stack, &CSN1Context->CurrOfs);
	}
	return Offset + 1;
}


/*------------------------------------------------------------------------------
	Function for entry CSN1_DECOCASE_A
------------------------------------------------------------------------------*/
unsigned CSN1_Execute_DECOCASE_A (const unsigned char* TableMemory, unsigned Offset, TCSN1Context* CSN1Context)
{
	if ((CSN1Context->CurrOfs <= CSN1Context->End-CSN1Context->LocalRepetitions)) {
		CSN1Context->CurrOfs+=CSN1Context->LocalRepetitions;
	}
	else {
		CSN1_StackBacktrack (&CSN1Context->CSN1_Stack, &CSN1Context->CurrOfs);
	}
	return Offset + 1;
}


/*------------------------------------------------------------------------------
	Function for entry CSN1_DECOCASE_H
------------------------------------------------------------------------------*/
unsigned CSN1_Execute_DECOCASE_H (const unsigned char* TableMemory, unsigned Offset, TCSN1Context* CSN1Context)
{
	if ((CSN1Context->CurrOfs <= CSN1Context->End-CSN1Context->LocalRepetitions) && (CSN1_MatchFill (CSN1Context->Buffer, CSN1Context->CurrOfs, '+') == 0)) {
		CSN1Context->CurrOfs+=CSN1Context->LocalRepetitions;
	}
	else {
		CSN1_StackBacktrack (&CSN1Context->CSN1_Stack, &CSN1Context->CurrOfs);
	}
	return Offset + 1;
}


/*------------------------------------------------------------------------------
	Function for entry CSN1_DECOCASE_L
------------------------------------------------------------------------------*/
unsigned CSN1_Execute_DECOCASE_L (const unsigned char* TableMemory, unsigned Offset, TCSN1Context* CSN1Context)
{
	if ((CSN1Context->CurrOfs <= CSN1Context->End-CSN1Context->LocalRepetitions) && (CSN1_MatchFill (CSN1Context->Buffer, CSN1Context->CurrOfs, '+') != 0)) {
		CSN1Context->CurrOfs+=CSN1Context->LocalRepetitions;
	}
	else {
		CSN1_StackBacktrack (&CSN1Context->CSN1_Stack, &CSN1Context->CurrOfs);
	}
	return Offset + 1;
}


/*------------------------------------------------------------------------------
	Function for entry CSN1_ENCOCASE_0
------------------------------------------------------------------------------*/
unsigned CSN1_Execute_ENCOCASE_0 (const unsigned char* TableMemory, unsigned Offset, TCSN1Context* CSN1Context)
{
	if (CSN1Context->BitsStored >= CSN1Context->LocalRepetitions) {
		if (EDBitsToInt (CSN1Context->Buffer, CSN1Context->CurrOfs, 1) == 0) {
			CSN1Context->CurrOfs+=CSN1Context->LocalRepetitions;
			CSN1Context->BitsStored-=CSN1Context->LocalRepetitions;
		}
		else {
			CSN1_StackBacktrack (&CSN1Context->CSN1_Stack, &CSN1Context->CurrOfs);
		}				
	}
	else {
		CSN1_SetBit0 (CSN1Context->Buffer, CSN1Context->CurrOfs);
		CSN1Context->CurrOfs++;
	}
	return Offset + 1;
}


/*------------------------------------------------------------------------------
	Function for entry CSN1_ENCOCASE_1
------------------------------------------------------------------------------*/
unsigned CSN1_Execute_ENCOCASE_1 (const unsigned char* TableMemory, unsigned Offset, TCSN1Context* CSN1Context)
{
	if (CSN1Context->BitsStored >= CSN1Context->LocalRepetitions) {
		if (EDBitsToInt (CSN1Context->Buffer, CSN1Context->CurrOfs, 1) == 1) {
			CSN1Context->CurrOfs+=CSN1Context->LocalRepetitions;
			CSN1Context->BitsStored-=CSN1Context->LocalRepetitions;
		}
		else {
			CSN1_StackBacktrack (&CSN1Context->CSN1_Stack, &CSN1Context->CurrOfs);
		}				
	}
	else {
		CSN1_SetBit1 (CSN1Context->Buffer, CSN1Context->CurrOfs);
		CSN1Context->CurrOfs++;
	}
	return Offset + 1;
}


/*------------------------------------------------------------------------------
	Function for entry CSN1_ENCOCASE_A
------------------------------------------------------------------------------*/
unsigned CSN1_Execute_ENCOCASE_A (const unsigned char* TableMemory, unsigned Offset, TCSN1Context* CSN1Context)
{
	if (CSN1Context->BitsStored >= CSN1Context->LocalRepetitions) {
		CSN1Context->CurrOfs+=CSN1Context->LocalRepetitions;
		CSN1Context->BitsStored-=CSN1Context->LocalRepetitions;
	}
	else {
		CSN1_SetBit0 (CSN1Context->Buffer, CSN1Context->CurrOfs);
		CSN1Context->CurrOfs++;
	}
	return Offset + 1;
}


/*------------------------------------------------------------------------------
	Function for entry CSN1_ENCOCASE_H
------------------------------------------------------------------------------*/
unsigned CSN1_Execute_ENCOCASE_H (const unsigned char* TableMemory, unsigned Offset, TCSN1Context* CSN1Context)
{
	if (CSN1Context->BitsStored >= CSN1Context->LocalRepetitions) {
		if (CSN1_MatchFill (CSN1Context->Buffer, CSN1Context->CurrOfs, '+') == 0) {
			CSN1Context->CurrOfs+=CSN1Context->LocalRepetitions;
			CSN1Context->BitsStored-=CSN1Context->LocalRepetitions;
		}
		else {
			CSN1_StackBacktrack (&CSN1Context->CSN1_Stack, &CSN1Context->CurrOfs);
		}				
	}
	else {
		CSN1_SetBitH (CSN1Context->Buffer, CSN1Context->CurrOfs, '+');
		CSN1Context->CurrOfs++;
	}
	return Offset + 1;
}


/*------------------------------------------------------------------------------
	Function for entry CSN1_ENCOCASE_L
------------------------------------------------------------------------------*/
unsigned CSN1_Execute_ENCOCASE_L (const unsigned char* TableMemory, unsigned Offset, TCSN1Context* CSN1Context)
{
	if (CSN1Context->BitsStored >= CSN1Context->LocalRepetitions) {
		if (CSN1_MatchFill (CSN1Context->Buffer, CSN1Context->CurrOfs, '+') != 0) {
			CSN1Context->CurrOfs+=CSN1Context->LocalRepetitions;
			CSN1Context->BitsStored-=CSN1Context->LocalRepetitions;
		}
		else {
			CSN1_StackBacktrack (&CSN1Context->CSN1_Stack, &CSN1Context->CurrOfs);
		}				
	}
	else {
		CSN1_SetBitL (CSN1Context->Buffer, CSN1Context->CurrOfs, '+');
		CSN1Context->CurrOfs++;
	}
	return Offset + 1;
}

/*------------------------------------------------------------------------------
	Function for entry CSN1_CUSTOM
------------------------------------------------------------------------------*/
unsigned CSN1_Execute_CUSTOM (const unsigned char* TableMemory, unsigned Offset, TCSN1Context* CSN1Context)
{
	unsigned customFunctionEntry;
	TableMemory += Offset;
	customFunctionEntry = (TableMemory[1] << 8) | TableMemory[2];
	CSN1Context->CSN1FunctionMap [customFunctionEntry] (CSN1Context);
	return Offset + 3;
}

/*------------------------------------------------------------------------------
	Function for entry CSN1_ENCOFIELD
------------------------------------------------------------------------------*/
unsigned CSN1_Execute_ENCOFIELD (const unsigned char* TableMemory, unsigned Offset, TCSN1Context* CSN1Context)
{
	unsigned customFunctionEntry;
	unsigned customExpressionEntry;
	int fieldId;
	TCSN1NextType actionPtr1;
	TCSN1NextType actionPtr2;

	TableMemory += Offset;
	customFunctionEntry = (TableMemory[1] << 8) | TableMemory[2];
	customExpressionEntry = (TableMemory[3] << 8) | TableMemory[4];
	fieldId = (TableMemory[5] << 8) | TableMemory[6];
	actionPtr1 = (TCSN1NextType)((TableMemory[7] << 16) | (TableMemory[8] << 8) | TableMemory[9]);
	actionPtr2 = (TCSN1NextType)((TableMemory[10] << 16) | (TableMemory[11] << 8) | TableMemory[12]);

	CSN1_StackPush (&CSN1Context->CSN1_Stack, actionPtr1, CSN1_NO_BACKTRACK, 1, -1, 0);
	CSN1_EnterField (&CSN1Context->CSN1_Stack, fieldId, CSN1Context->CurrOfs);
	if (customExpressionEntry != 0xFFFF && CSN1Context->CSN1ExpressionMap [customExpressionEntry] (CSN1Context)) {
		CSN1_StackBacktrack (&CSN1Context->CSN1_Stack, &CSN1Context->CurrOfs);
	} else {
		if (customFunctionEntry != 0xFFFF) CSN1Context->CSN1FunctionMap [customFunctionEntry] (CSN1Context);
		CSN1_StackPush (&CSN1Context->CSN1_Stack, actionPtr2, CSN1_NO_BACKTRACK, 1, -1, 0);
	}

	return Offset + 13;
}

/*------------------------------------------------------------------------------
	Table for quick access to decoding/encoding CSN.1 functions
------------------------------------------------------------------------------*/
unsigned (*CSN1_Execute_Table []) (const unsigned char*, unsigned, TCSN1Context*) =
{
	CSN1_Execute_STACKPUSH_NBT,
	CSN1_Execute_STACKPUSH_XNBT,
	CSN1_Execute_STACKPUSH_UTOP,
	CSN1_Execute_STACKPUSH_TRK,
	CSN1_Execute_STACKPUSH_INFR,
	CSN1_Execute_ENTER_FLD,
	CSN1_Execute_EXIT_FIELD,
	CSN1_Execute_TERM_LOOP,
	CSN1_Execute_DECOCASE_0,
	CSN1_Execute_DECOCASE_1,
	CSN1_Execute_DECOCASE_A,
	CSN1_Execute_DECOCASE_H,
	CSN1_Execute_DECOCASE_L,
	CSN1_Execute_ENCOCASE_0,
	CSN1_Execute_ENCOCASE_1,
	CSN1_Execute_ENCOCASE_A,
	CSN1_Execute_ENCOCASE_H,
	CSN1_Execute_ENCOCASE_L,
	CSN1_Execute_CUSTOM,
	CSN1_Execute_ENCOFIELD
};

/*------------------------------------------------------------------------------
	Execute a program from the table starint at given offset
------------------------------------------------------------------------------*/
void Csn1_ExecuteTable (const unsigned char* TableMemory, TCSN1NextType Offset, TCSN1Context* CSN1Context)
{
	if (Offset == CSN1_FAIL || Offset == CSN1_SUCCESS) {
		CSN1Context->Continue = 0;
		return;
	}	else if (Offset == CSN1_NULL) return;
	while (TableMemory [Offset] != CSN1_RETURN) {
		Offset = CSN1_Execute_Table [TableMemory [Offset]] (TableMemory, Offset, CSN1Context);
	}
}

#endif
/*------------------------------------------------------------------------------
	Initializes a stack. It receives a pointer 'sp' to the allocated stack.
	To be called before using the stack.
------------------------------------------------------------------------------*/
void CSN1_StackInit (TCSN1Stack* sp) 
{
#if CSN1_NOTSET != 0
#error THIS CODE WORKS ONLY IF CSN1_NOTSET IS 0! FIX IT!
#endif

	ED_RESET_MEM (sp, sizeof (*sp));
}


/*------------------------------------------------------------------------------
	Executes a PUSH of an action.
	We have two kinds of actions: NEXT and BACKTRACK.
	nxt         Next state in the state machine
	bcktrk      If set to CSN1_NO_BACKTRACK, then this action is a normal "next"
	            action. Otherwise, it is "backtrack" action and this value is
						  the offset in bits inside the input buffer where we must
						  restart parsing with action "nxt".
	repetitions Number of times this action should be repeated; meaningful if
	            it is a "next" action.
------------------------------------------------------------------------------*/
void CSN1_StackPush (TCSN1Stack* sp, TCSN1NextType nxt, int bcktrk, int repetitions, int popUserTags, int options)
{
	/* STACK OVERFLOW! */
	assert (sp->top < CSN1_STACK_SIZE);
#ifdef CSNLIBDEBUG
	fprintf (stderr, "[%06d] add on stack top=%d nxt=%d bcktrk=%d newUserTag=%d\n", csn1LogCounter++, sp->top, nxt, bcktrk, popUserTags);
#endif
	sp->elements [sp->top].next = nxt;
	sp->elements [sp->top].backtrack = bcktrk;
	sp->elements [sp->top].repetitions = repetitions;
	sp->elements [sp->top].newUserTagsTop = popUserTags;
	sp->elements [sp->top].fieldState = sp->fieldState;
	sp->elements [sp->top].options = options;
	sp->top++;
}

/*------------------------------------------------------------------------------
	Informs on which is next state.
------------------------------------------------------------------------------*/
#ifndef CSN1_OLD_ENCODER
	TCSN1NextType CSN1_StackNext (TCSN1Stack* sp, int* newUserTagsTop, int CurrOfs, int* LocalRepetitions)
#else
	TCSN1NextType CSN1_StackNext (TCSN1Stack* sp, int* newUserTagsTop, int CurrOfs)
#endif
{
	TCSN1NextType ret;
	int i;
#ifndef CSN1_OLD_ENCODER
	(*LocalRepetitions) = 1;
#endif
#ifdef CSNLIBDEBUG
	fprintf (stderr, "[%06d] execute next on stack top=%d\n", csn1LogCounter++, sp->top);
#endif
	/* STACK UNDERFLOW! */
	/* assert (sp->top > 0); */
	
	/*----------------------------------------------------------------------------
		All the backtrack actions currently on top of the stack are removed:
		we don't need them anymore since we already decided that we want to
		go on. Remove also those next actions which have 0 repetitions.
	----------------------------------------------------------------------------*/
	while (
			(sp->top > 0) 
			&& 
			(
				(sp->elements [sp->top-1].backtrack >= 0) 
				|| 
				(sp->elements [sp->top-1].repetitions < 1)
			)
		) {
		sp->top--;
	}

	/*----------------------------------------------------------------------------
		If stack is (or became) empty (no more next actions), we return 
		CSN1_SUCCESS: if we are requiring a "next" it means that everything so far
		went well and we want to go on. Since we don't have any other step, it
		means that we are done sucesfully.		
	----------------------------------------------------------------------------*/
	if (sp->top <= 0) return CSN1_SUCCESS;

	/*----------------------------------------------------------------------------
		Next thing to do is to go at the case which number is stored in field
		"next" of current topmost action.
	----------------------------------------------------------------------------*/
	ret = sp->elements [sp->top-1].next;
	(*newUserTagsTop) = sp->elements [sp->top-1].newUserTagsTop;

	/*----------------------------------------------------------------------------
		If the action currently on top of the stack has option CSN1_RAISE_BACKTRACK
		we look for the topmost backtrack action and fix it.
	----------------------------------------------------------------------------*/
	if ((sp->elements [sp->top-1].options & CSN1_RAISE_BACKTRACK) == CSN1_RAISE_BACKTRACK) {
		for (i=sp->top-2; i>=0; i--) {
			if (sp->elements [i].backtrack >= 0) {
				sp->elements [i].backtrack = CurrOfs;
				sp->elements [i].fieldState = sp->fieldState;
			}
		}
	}
	
	/*----------------------------------------------------------------------------
		If the action currently on top of the stack has "repetitions" greater
		than 1, we decrease it but we don't decrease the stack top (this action
		is still kept as next action);	
	----------------------------------------------------------------------------*/
	if (sp->elements [sp->top-1].repetitions > 1) {
		if ((sp->elements [sp->top-1].options & CSN1_EXTERNAL_REPETITION) != 0) {
#ifndef CSN1_OLD_ENCODER
			(*LocalRepetitions) = sp->elements [sp->top-1].repetitions;
#endif
			sp->elements [sp->top-1].repetitions = 0;
		}
		else {
			sp->elements [sp->top-1].repetitions--;
		}
	}
	/*----------------------------------------------------------------------------
		Otherwise, we remove the current action.
	----------------------------------------------------------------------------*/
	else {
		sp->top--;
	}
#ifdef CSNLIBDEBUG
	fprintf (stderr, "[%06d] execute next on stack - returning value val=%d top=%d\n", csn1LogCounter++, ret, sp->top);
#endif
	return ret;
}

/*------------------------------------------------------------------------------
	Executes a POP.
	Sets given variables with new state and new position
------------------------------------------------------------------------------*/
void CSN1_StackBacktrack (TCSN1Stack* sp, long* pos)
{
#ifdef CSNLIBDEBUG
		int i;
		fprintf (stderr, "[%06d] backtrack requested with top=%d\n", csn1LogCounter++, sp->top);
		for (i=sp->top-1; i>=0; i--) {
			fprintf (stderr, "[%06d]     %2d nxt=%5d  repetitions=%4d  backtrack=%5d\n", csn1LogCounter++, i, sp->elements[i].next, sp->elements[i].repetitions, sp->elements[i].backtrack);
		}
#endif
	/* STACK UNDERFLOW! */
	/* assert (sp->top > 0); */
	
	do {
		sp->top--;
		if (sp->top < 0) {
			sp->top = 1;
			sp->elements [0].backtrack = CSN1_NO_BACKTRACK;
			sp->elements [0].next = CSN1_FAIL;
			sp->elements [0].repetitions = 1;
#ifdef CSNLIBDEBUG
			fprintf (stderr, "[%06d] backtrack: reached stack base without finding a valid backtrack entry\n", csn1LogCounter++);
#endif
			return;
		}
	} while (!(sp->elements [sp->top].backtrack >= 0));

	/* Convert backtrack to next */
	(*pos) = sp->elements [sp->top].backtrack;
	sp->fieldState = sp->elements [sp->top].fieldState;

	sp->elements [sp->top].backtrack = CSN1_NO_BACKTRACK;
	sp->top++;
#ifdef CSNLIBDEBUG
	fprintf (stderr, "[%06d] backtrack: found a backtrack entry at position %d\n", csn1LogCounter++, sp->top-1);
#endif
}

/*------------------------------------------------------------------------------
	Link its parent
------------------------------------------------------------------------------*/
void CSN1_LinkParent (TCSN1Stack* sp)
{
	/* Set its parent immediately */
	if (sp->fieldState.level <= 0) {
		sp->fields [sp->fieldState.fieldsTop].parent = NULL;
	}
	else {
		int i;
		for (i=sp->fieldState.fieldsTop-1; i>=0; i--) {
			if (sp->fields [i].level == sp->fieldState.level-1) {
				sp->fields [sp->fieldState.fieldsTop].parent = &(sp->fields [i]);
				break;
			}
		}
		/* If fails, parent was not found... it can't be! */
		assert (i >= 0);
	}
}

/*------------------------------------------------------------------------------
	Returns fieldId of the lowest level field opened. It will be the parent
	of the next added field.
	Returns -1 if no parents are present.
------------------------------------------------------------------------------*/
int CSN1_GetParentFieldId (TCSN1Stack* sp)
{
	if (sp->fieldState.level <= 0) {
		return -1;
	}
	else {
		int i;
		for (i=sp->fieldState.fieldsTop-1; i>=0; i--) {
			if (sp->fields [i].level == sp->fieldState.level-1) {
				return sp->fields [i].fieldId;
			}
		}
		/* If fails, parent was not found... it can't be! */
		assert (i >= 0);
	}
	return -1;
}

/*------------------------------------------------------------------------------
	Enter a field
------------------------------------------------------------------------------*/
void CSN1_EnterField (TCSN1Stack* sp, int fieldId, long pos)
{
	int i, j;
#ifdef CSNLIBDEBUG
	if (csn1LogCounter == 2199) {
		fprintf (stderr, "OK\n");
	}
	fprintf (stderr, "[%06d] enter field - fieldId=%d pos=%d\n", csn1LogCounter++, fieldId, pos);
#endif
	i = sp->fieldState.fieldsTop;

	sp->fields [i].fieldId = fieldId;
	sp->fields [i].pos = pos;
	sp->fields [i].index = 0;
	sp->fields [i].level = sp->fieldState.level;
	CSN1_LinkParent (sp);
	
	/* Calculate index */
	for (j=i-1; j>=0; j--) {
		if (&(sp->fields [j]) == sp->fields [i].parent) {
			sp->fields [i].index = 0;
			break;
		}
		else if ((sp->fields [j].fieldId == sp->fields [i].fieldId) 
			&& (sp->fields [j].index >= 0)) {
			sp->fields [i].index = sp->fields [j].index+1;
			break;
		}
	}

	sp->fieldState.fieldsTop++;
	sp->fieldState.level++;
}

/*------------------------------------------------------------------------------
	Exit a field
------------------------------------------------------------------------------*/
void CSN1_ExitField (TCSN1Stack* sp, int fieldId, long pos)
{
#ifdef CSNLIBDEBUG
	fprintf (stderr, "[%06d] exit field - fieldId=%d pos=%d\n", csn1LogCounter++, fieldId, pos);
#endif
	sp->fields [sp->fieldState.fieldsTop].fieldId = fieldId;
	sp->fields [sp->fieldState.fieldsTop].pos = pos;
	sp->fields [sp->fieldState.fieldsTop].index = -1;
	sp->fields [sp->fieldState.fieldsTop].level = sp->fieldState.level;
	sp->fieldState.level--;
	CSN1_LinkParent (sp);
	sp->fieldState.fieldsTop++;
}

/*------------------------------------------------------------------------------
	Calculates the length of a field in bits. This has to be called just before
	a CSN1_ExitField and with the same parameters.
------------------------------------------------------------------------------*/
int CSN1_CalcFieldSize (TCSN1Stack* sp, int fieldId, long pos)
{
	int i;
	for (i=sp->fieldState.fieldsTop-1; i>=0; i--) {
		if (sp->fields [i].fieldId == fieldId && sp->fields [i].level == sp->fieldState.level-1) {
			return pos-sp->fields [i].pos;
		}
	}
	return -1;
}

/*------------------------------------------------------------------------------
   1.日    期   : 2008年06月09日
      作    者   : 黄天祥h129908
      修改内容   : 问题单AT2D03522，GAS的代码中有与C语法冲突的地方，
                                 导致在没有GNU 扩展的编译器中，编译不通过
------------------------------------------------------------------------------*/
#define ENCODIXBUF ((unsigned char*)buffer)

/*------------------------------------------------------------------------------
	Tests the bit at given offset against a fill octet. Returns 1 if the
	required bit matches the fill offset corresponding one. 0 otherwise.
------------------------------------------------------------------------------*/
int CSN1_MatchFill (const void* buffer, int bitOffset, unsigned char fillOctet)
{
	int mask, bit;
	mask = 1 << (7-(bitOffset & 7));
	bit = (ENCODIXBUF[bitOffset >> 3] & mask);
	return (bit == (fillOctet & mask)) ? 1 : 0;
}

/*------------------------------------------------------------------------------
	Terminate current infinite loop
------------------------------------------------------------------------------*/
void CSN1_TerminateLoop (TCSN1Stack* sp)
{
	/* STACK UNDERFLOW! */
	assert (sp->top > 0);

	sp->top --;
}

/*------------------------------------------------------------------------------
	Adds a value with given code on the stack
------------------------------------------------------------------------------*/
void CSN1_PushValue (TCSN1Stack* sp, int tag, int value)
{
	/* Not enough user tags */
	assert (sp->fieldState.userTagTop < CSN1_USERTAGS);

	sp->userTags [sp->fieldState.userTagTop].tagId = tag;
	sp->userTags [sp->fieldState.userTagTop].value = value;
	sp->fieldState.userTagTop++;
}

/*------------------------------------------------------------------------------
	Returns given value from the stack
------------------------------------------------------------------------------*/
int CSN1_GetValue (TCSN1Stack* sp, int tag)
{
	int i;
	for (i=sp->fieldState.userTagTop-1; i>=0; i--) {
		if (sp->userTags [i].tagId == tag) return sp->userTags [i].value;
	}
	/* Tag not found. It should never happen, unless of bad custom E/D coding */
	assert (0);
	return -1;
}

/*------------------------------------------------------------------------------
	Sets a value with the given tag. It finds it like CSN1_GetValue.
------------------------------------------------------------------------------*/
void CSN1_SetValue (TCSN1Stack* sp, int tag, int value)
{
	int i;
	for (i=sp->fieldState.userTagTop-1; i>=0; i--) {
		if (sp->userTags [i].tagId == tag) {sp->userTags [i].value = value; return;}
	}
	/* Tag not found. It should never happen, unless of bad custom E/D coding */
	assert (0);
}


/*==============================================================================
	CSN.1 TRACING FACILITY

	To enable CSN.1 tracing, define CSN1_TRACE_ENABLED
==============================================================================*/
#ifdef CSN1_TRACE_ENABLED
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "ed_lib.h"
#ifndef CSN1_TRACE_FILE_NAME
#define CSN1_TRACE_FILE_NAME "csn1trace.log"
#endif

/*------------------------------------------------------------------------------
	Dumps a part of a binary buffer
	Parameters:
		LogFile       FILE*        pointer to the file where the dump must be done
		Buffer        const char*  pointer to the buffer being encoded 
		BitOffset     long         offset in bits from the beginning of buffer
		Length        long         number of valid bits
------------------------------------------------------------------------------*/
void Csn1DumpBinaryBuffer (FILE* LogFile, const char* Buffer, long BitOffset, long Length)
{
	long i;
	int ctr = 0;
	
	fprintf (LogFile, "Length: %ld bits", Length);
	for (i=BitOffset; i<Length+BitOffset; i++) {
		if (ctr == 0) {
			fprintf (LogFile, "\n");
			fprintf (LogFile, "%08ld ", i);
		}
		if (ctr == 4) fprintf (LogFile, " ");
		fprintf (LogFile, "%d", EDBitsToInt (Buffer, i, 1));
		ctr++;
		if (ctr >= 8) ctr = 0;
	}
	fprintf (LogFile, "\n");
}


/*------------------------------------------------------------------------------
	Opens the file to be used for tracing
------------------------------------------------------------------------------*/
FILE* Csn1OpenTraceFile ()
{
	FILE* f;
	f = fopen (CSN1_TRACE_FILE_NAME, "a");
	if (f == NULL) {
		fprintf (stderr, "Error opening file '%s': %s\n", CSN1_TRACE_FILE_NAME, strerror (errno));
		exit (1);
	}
	return f;
}

/*------------------------------------------------------------------------------
	This function is invoked when entering a decoding function
	Parameters:
		Description   ASCIIZ       short text describing the action
		Buffer        const char*  pointer to the buffer being encoded 
		BitOffset     long         offset in bits from the beginning of buffer
		Length        long         number of valid bits
------------------------------------------------------------------------------*/
void Csn1DecodeTraceBegin (const char* Description, const char* Buffer, long BitOffset, long Length)
{
	FILE* log;
	log = Csn1OpenTraceFile ();

	fprintf (log, "\n==================================================\n");
	fprintf (log, "  Tracing decode of %s\n", Description);
	fprintf (log, "--------------------------------------------------\n");
	Csn1DumpBinaryBuffer (log, Buffer, BitOffset, Length);
	fprintf (log, "--------------------------------------------------\n");

	fclose (log);
}

/*------------------------------------------------------------------------------
	This function is invoked when exiting a decoding function
	Parameters:
		Description   ASCIIZ       short text describing the action
------------------------------------------------------------------------------*/
void Csn1DecodeTraceEnd (const char* Description)
{
	FILE* log;
	log = Csn1OpenTraceFile ();

	fprintf (log, "--------------------------------------------------\n");

	fclose (log);
}

/*------------------------------------------------------------------------------
	This function is invoked when entering an encoding function
	Parameters:
		Description   ASCIIZ       short text describing the action
------------------------------------------------------------------------------*/
void Csn1EncodeTraceBegin (const char* Description)
{
	FILE* log;
	log = Csn1OpenTraceFile ();

	fprintf (log, "--------------------------------------------------\n");
	fprintf (log, "  Tracing encode of %s\n", Description);
	fprintf (log, "--------------------------------------------------\n");

	fclose (log);
}

/*------------------------------------------------------------------------------
	This function is invoked when exiting an encoding function
	Parameters:
		Description   ASCIIZ       short text describing the action
		Buffer        const char*  pointer to the buffer being encoded 
		BitOffset     long         offset in bits from the beginning of buffer
		Length        long         number of valid bits
------------------------------------------------------------------------------*/
void Csn1EncodeTraceEnd (const char* Description, const char* Buffer, long BitOffset, long Length)
{
	FILE* log;
	log = Csn1OpenTraceFile ();

	fprintf (log, "--------------------------------------------------\n");
	Csn1DumpBinaryBuffer (log, Buffer, BitOffset, Length);
	fprintf (log, "==================================================\n");

	fclose (log);
}

/*------------------------------------------------------------------------------
	Called at each event in the CSN.1 encoding/decoding process.
	Parameters:
		Description   ASCIIZ       short text describing the action
		Offset        long         bit in which this operation is performed
------------------------------------------------------------------------------*/
void Csn1TraceEvent (const char* Description, long Offset)
{
	FILE* log;
	log = Csn1OpenTraceFile ();

	fprintf (log, "%08ld %s", Offset, Description);

	fclose (log);
}

/*------------------------------------------------------------------------------
	Called before consuming a stack element in each CSN.1 step.
	Parameters:
		Stack        const TCSN1Stack*  Stack to be printed
------------------------------------------------------------------------------*/
void Csn1TraceStack (const TCSN1Stack* Stack)
{
	FILE* log;
	int i;

	log = Csn1OpenTraceFile ();
	fprintf (log, "\tstk:");
	for (i=0; i<Stack->top; i++) {
		if (i > 0) fprintf (log, ",");
		if (Stack->elements [i].backtrack >= 0) {
			fprintf (log, "B%d(o:%d)", Stack->elements [i].next, Stack->elements [i].backtrack);
		}
		else {
			if (Stack->elements [i].repetitions != 1) {
				fprintf (log, "%d*%d", Stack->elements [i].next, Stack->elements [i].repetitions);
			}
			else {
				fprintf (log, "%d", Stack->elements [i].next);
			}
		}
	}	
	fprintf (log, "\n");
	fclose (log);
}
#endif /* CSN1_TRACE_ENABLED */
#ifndef CSN1_OLD_ENCODER

/*------------------------------------------------------------------------------
	Standard ENCODE function
------------------------------------------------------------------------------*/
long Csn1_Encode (const unsigned char* TableMemory, char* ED_CONST Buffer, ED_CONST long BitOffset, const void* ED_CONST Source, TCSN1NextType StartTransition, void (*const *CSN1FunctionMap) (TCSN1Context*), int (*const *CSN1ExpressionMap) (TCSN1Context*))
{
	CSN1_EN_DECLARE_STACK

	INIT_TCSN1Context (CSN1Context);
	CSN1Context->Buffer = Buffer;
	CSN1Context->Data = (void*)Source;
	CSN1Context->CurrOfs = BitOffset;
	CSN1Context->BitOffset = BitOffset;
	CSN1Context->Length = 0;
	CSN1Context->End = 0;
	CSN1Context->Continue = 1;
	CSN1Context->CSN1FunctionMap = (void (*const *) (void*))CSN1FunctionMap;
	CSN1Context->CSN1ExpressionMap = (int (*const *) (void*))CSN1ExpressionMap;
	
	CSN1_StackInit (&CSN1Context->CSN1_Stack);
	CSN1_StackPush (&CSN1Context->CSN1_Stack, StartTransition, CSN1_NO_BACKTRACK, 1, -1, 0);
	
	while (CSN1Context->Continue > 0) {
		CSN1Context->Next = CSN1_StackNext (&CSN1Context->CSN1_Stack, &CSN1Context->newUserTagsTop, CSN1Context->CurrOfs, &CSN1Context->LocalRepetitions);
		Csn1_ExecuteTable (TableMemory, CSN1Context->Next, CSN1Context);
		if (CSN1Context->newUserTagsTop >= 0) CSN1Context->CSN1_Stack.fieldState.userTagTop = CSN1Context->newUserTagsTop;
	}

	CSN1_StackFree (&CSN1Context->CSN1_Stack);
	return (CSN1Context->Continue == 0 ? (CSN1Context->CurrOfs-CSN1Context->BitOffset) : -1);
}

/*------------------------------------------------------------------------------
	Standard DECODE function
------------------------------------------------------------------------------*/
void Csn1_Decode (const unsigned char* TableMemory, TCSN1Context* CSN1Context, const char* ED_CONST Buffer, ED_CONST long BitOffset, void* ED_CONST Destin, unsigned long DestinSize, long Length, TCSN1NextType StartTransition, void (*const *CSN1FunctionMap) (TCSN1Context*), int (*const *CSN1ExpressionMap) (TCSN1Context*))
{
	INIT_TCSN1Context (CSN1Context);
	CSN1Context->CurrOfs = BitOffset;
	CSN1Context->BitOffset = BitOffset;
	CSN1Context->Length = Length;
	CSN1Context->End = BitOffset + Length;
	CSN1Context->Buffer = (char*)Buffer;
	CSN1Context->Data = (void*)Destin;
	CSN1Context->Continue = 1;
	CSN1Context->CSN1FunctionMap = (void (*const *) (void*))CSN1FunctionMap;
	CSN1Context->CSN1ExpressionMap = (int (*const *) (void*))CSN1ExpressionMap;
	
	CSN1_StackInit (&CSN1Context->CSN1_Stack);
	CSN1_StackPush (&CSN1Context->CSN1_Stack, StartTransition, CSN1_NO_BACKTRACK, 1, -1, 0);
	/*ED_RESET_MEM (Destin, DestinSize);*/
	
	while (CSN1Context->Continue > 0) {
		CSN1Context->Next = CSN1_StackNext (&CSN1Context->CSN1_Stack, &CSN1Context->newUserTagsTop, CSN1Context->CurrOfs, &CSN1Context->LocalRepetitions);
		if (CSN1Context->CurrOfs > CSN1Context->End) CSN1_StackBacktrack (&CSN1Context->CSN1_Stack, &CSN1Context->CurrOfs);
		else 	Csn1_ExecuteTable (TableMemory, CSN1Context->Next, CSN1Context);
		if (CSN1Context->newUserTagsTop >= 0) CSN1Context->CSN1_Stack.fieldState.userTagTop = CSN1Context->newUserTagsTop;
	}
}
#endif

/*lint +e502*/
/*lint +e451*/
/*lint +e702*/
/*lint +e506*/

