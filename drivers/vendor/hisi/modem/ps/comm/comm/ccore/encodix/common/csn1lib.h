/*******************************************************************************
  csn1lib.h  Developed by Dafocus - http://www.dafocus.com/
*******************************************************************************/
#ifndef __CSN1LIB_H
#define __CSN1LIB_H
#include <assert.h>
#include "ed_lib.h"

#ifdef __cplusplus
	extern "C" {
#endif

/*由于在张江高科园区出现需要栈空间超出128的SI2Quater系统消息, 因此将栈空间修改为256*/
/*#define CSN1_STACK_SIZE  128 */
/*#define CSN1_FIELDS      128 *//* Maximum fields */
#define CSN1_STACK_SIZE   384    /* Maximum stack size */
#define CSN1_FIELDS       384    /* Maxinum fileds */

/* Modified by y00142674 for 内存优化二阶段, 2012-01-13, begin */
/*#define CSN1_USERTAGS     16 */   /* Maximum user tags */
#define CSN1_USERTAGS     32     /* Maximum user tags */
/* Modified by y00142674 for 内存优化二阶段, 2012-01-13, end */
#define CSN1_NOTSET        0
#define CSN1_RAISE_BACKTRACK     1
#define CSN1_EXTERNAL_REPETITION 2
#define INFINITE_REPETITIONS (32767)
#define CSN1_NO_BACKTRACK    (-1)

struct SCSN1Context;
#ifdef CSN1_OLD_ENCODER
	typedef int TCSN1NextType;
#define CSN1_FAIL        (-2)
#define CSN1_SUCCESS     (-1)
#define CSN1_NULL        (-3)
#define CSN1_STACK       CSN1_Stack
#else

	typedef unsigned TCSN1NextType;
#define CSN1_FAIL        0xFFFFFE
#define CSN1_SUCCESS     0xFFFFFF
#define CSN1_NULL        0xFFFFFD
#define CSN1_STACK       (CSN1Context->CSN1_Stack)
#endif
#define CSN1_BACKTRACK CSN1_StackBacktrack \
  (&CSN1Context->CSN1_Stack, &CSN1Context->CurrOfs)

/*------------------------------------------------------------------------------
	CSN.1 Field filler structure state
------------------------------------------------------------------------------*/
typedef struct SCSN1FieldState {
	/* First available field */
	int fieldsTop;

	/* First available user tag */
	int userTagTop;

	/* Current level */
	int level;

} TCSN1FieldState;

/*------------------------------------------------------------------------------
	CSN.1 Used by users to place values on a stack
------------------------------------------------------------------------------*/
typedef struct SCSN1UserTag {
	/* Unique tag identificator */
	int tagId;

	/* Value of that tag */
	int value;

} TCSN1UserTag;

/*------------------------------------------------------------------------------
	CSN.1 Stack structure
------------------------------------------------------------------------------*/
typedef struct SCSN1StackElement {
	/* Next state to be attempted if current is succesful. */
	TCSN1NextType next;

	/* >=0 if next is a backtrack action. It is the position */
	/* into the stream, to back up if current parsing fails, */
	/* in case of backtracting. */
	int backtrack;

	/* It is the number of repetitions admitted */ 
	int repetitions;

	/* It stores the top-value for user tags. <0 if not used */
	int newUserTagsTop;

	/* Options - see CSN1_xxx definitions */
	int options;

	/* Current field state, to be resumed in case of backtracking */
	TCSN1FieldState fieldState;

} TCSN1StackElement;

/*------------------------------------------------------------------------------
	CSN.1 Field filler structure
------------------------------------------------------------------------------*/
typedef struct SCSN1FieldElement {
	/* Field id. */
	int fieldId;

	/* Current index. <0 means that we shall exit from this field */ 
	int index;

	/* First bit to be used or last+1 if index<0 */
	long pos;

	/* Current nesting level - 0 for root fields */
	int level;

	/* Parent - linked by CSN1_LinkFields */
	struct SCSN1FieldElement* parent;

} TCSN1FieldElement;

/*------------------------------------------------------------------------------
	CSN.1 Stack
------------------------------------------------------------------------------*/
typedef struct SCSN1Stack {
	/* Internal array making up the stack */
	TCSN1StackElement elements [CSN1_STACK_SIZE];

	/* Internal log of fields */
	TCSN1FieldElement fields [CSN1_FIELDS];

	/* User tags */
	TCSN1UserTag userTags [CSN1_USERTAGS];

	/* First available element */
	int top;
	
	/* State of the fields structure */
	TCSN1FieldState fieldState;

} TCSN1Stack;

/*------------------------------------------------------------------------------
	Structure defining the context of a CSN.1 parser
------------------------------------------------------------------------------*/
typedef struct SCSN1Context {
	/* Parser stack */
	TCSN1Stack CSN1_Stack;

	/* Data buffer */
	char* Buffer;

	/* Starting offset in bits */
	long BitOffset;

	/* Current offset in bits */
	long CurrOfs;

	/* Data length in bits */
	long Length;

	/* End of the stream in bits (End = BitOffset + Length) */
	long End;

	/* Data pointer (source or destination) */
	void* Data;

	/* Bits stored */
	int BitsStored;

	/* Local repetitions */
	int LocalRepetitions;

	/* User tag top */
	int newUserTagsTop;

	/* True if it must continue */
	int Continue;

	/* Next step */
	TCSN1NextType Next;

	/* Function map for this context */
	void (*const *CSN1FunctionMap) (void*);
	
	/* Expression map for this context */
	int (*const *CSN1ExpressionMap) (void*);

} TCSN1Context;
#define INIT_TCSN1Context(c) ED_RESET_MEM ((c), sizeof (TCSN1Context))

/*------------------------------------------------------------------------------
	Initializes a stack. It receives a pointer 'sp' to the allocated stack.
	To be called before using the stack.
------------------------------------------------------------------------------*/
extern void CSN1_StackInit (TCSN1Stack* sp);

/*------------------------------------------------------------------------------
	Frees a stack
------------------------------------------------------------------------------*/
#define CSN1_StackFree(sp)

/*------------------------------------------------------------------------------
	Executes a PUSH
	"popUserTags" can be used to set back user tags pointer.
	If <0, it will be ignored. Otherwise, user's tags top pointer will be set
	to that value AFTER having executed that action.
	Field 'options' may be set or-ed with:
		
		CSN1_RAISE_BACKTRACK	If set with this option, when this element is
		  extracted from the stack, first Backtrack action found is updated so
			its current bit position is the same as the extracted token.

		CSN1_EXTERNAL_REPETITION  If set, repetitions are not executed by that
		  node, but they are returned in the "localRepetitions" member of
			"CSN1_StackNext". This allows, for example, to read a sequence of
			n bits at once and not as n single bits.
------------------------------------------------------------------------------*/
void CSN1_StackPush (TCSN1Stack* sp, TCSN1NextType nxt, int bcktrk, int repetitions, int popUserTags, int options);

/*------------------------------------------------------------------------------
	Informs on which is next state
------------------------------------------------------------------------------*/
#ifndef CSN1_OLD_ENCODER
	TCSN1NextType CSN1_StackNext (TCSN1Stack* sp, int* newUserTagsTop, int currOfs, int* localRepetitions);
#else
	TCSN1NextType CSN1_StackNext (TCSN1Stack* sp, int* newUserTagsTop, int currOfs);
#endif

/*------------------------------------------------------------------------------
	Executes a POP.
	Sets given variables with new state and new position
------------------------------------------------------------------------------*/
void CSN1_StackBacktrack (TCSN1Stack* sp, long* pos);

/*------------------------------------------------------------------------------
	Returns fieldId of the lowest level field opened. It will be the parent
	of the next added field.
	Returns -1 if no parents are present.
------------------------------------------------------------------------------*/
int CSN1_GetParentFieldId (TCSN1Stack* sp);

/*------------------------------------------------------------------------------
	Enter a field
------------------------------------------------------------------------------*/
void CSN1_EnterField (TCSN1Stack* sp, int fieldId, long pos);

/*------------------------------------------------------------------------------
	Exit a field
------------------------------------------------------------------------------*/
void CSN1_ExitField (TCSN1Stack* sp, int fieldId, long pos);

/*------------------------------------------------------------------------------
	Calculates the length of a field in bits. This has to be called just before
	a CSN1_ExitField and with the same parameters.
------------------------------------------------------------------------------*/
int CSN1_CalcFieldSize (TCSN1Stack* sp, int fieldId, long pos);

/*------------------------------------------------------------------------------
	Terminate current infinite loop
------------------------------------------------------------------------------*/
void CSN1_TerminateLoop (TCSN1Stack* sp);

/*------------------------------------------------------------------------------
	Adds a value with given code on the stack
------------------------------------------------------------------------------*/
void CSN1_PushValue (TCSN1Stack* sp, int tag, int value);
#define PUSH_TAG(tag,value) CSN1_PushValue (&CSN1_STACK, tag, value)

/*------------------------------------------------------------------------------
	Returns given value from the stack
------------------------------------------------------------------------------*/
int CSN1_GetValue (TCSN1Stack* sp, int tag);
#define TAG(tag) CSN1_GetValue (&CSN1_STACK, tag)

/*------------------------------------------------------------------------------
	Sets a value with the given tag
------------------------------------------------------------------------------*/
void CSN1_SetValue (TCSN1Stack* sp, int tag, int value);
#define SET_TAG(tag,value) CSN1_SetValue (&CSN1_STACK, tag, value)

/*------------------------------------------------------------------------------
	Base for automatically generated tags
------------------------------------------------------------------------------*/
#define CSN1_AUTO_TAG_BASE 1000

/*------------------------------------------------------------------------------
	Tests the bit at given offset against a fill octet. Returns 1 if the
	required bit matches the fill offset corresponding one. 0 otherwise.
------------------------------------------------------------------------------*/
int CSN1_MatchFill (const void* buffer, int bitOffset, unsigned char fillOctet);

/*------------------------------------------------------------------------------
	Sets bit at given offset to 1
------------------------------------------------------------------------------*/
#define CSN1_SetBit1(buffer,bitOffset)\
	(((unsigned char*)(buffer))[((unsigned)(bitOffset))>>3] |= (1 << (7U-(((unsigned)(bitOffset)) & 7))))

/*------------------------------------------------------------------------------
	Sets bit at given offset to 0
------------------------------------------------------------------------------*/
#define CSN1_SetBit0(buffer,bitOffset)\
	(((unsigned char*)(buffer))[((unsigned)(bitOffset))>>3] &= ~(1 << (7U-(((unsigned)(bitOffset)) & 7))))

/*------------------------------------------------------------------------------
	Sets bit at given offset to L
------------------------------------------------------------------------------*/
#define CSN1_SetBitL(buffer,bitOffset,mask)\
	(((unsigned char)mask) & (1 << (7U-(((unsigned)(bitOffset)) & 7)))? CSN1_SetBit1(buffer,bitOffset):\
	CSN1_SetBit0(buffer,bitOffset))

/*------------------------------------------------------------------------------
	Sets bit at given offset to H
------------------------------------------------------------------------------*/
#define CSN1_SetBitH(buffer,bitOffset,mask)\
	(((unsigned char)mask) & (1 << (7U-(((unsigned)(bitOffset)) & 7)))? CSN1_SetBit0(buffer,bitOffset):\
	CSN1_SetBit1(buffer,bitOffset))


/*------------------------------------------------------------------------------
	Declares a TCSN1Stack.
	Define CSN1_LOCAL_STACK to declare a CSN1 stack on every CSN.1 function
	call. This allows nested CNS.1 encoding/decoding.
------------------------------------------------------------------------------*/
#ifndef CSN1_DECLARE_STACK
#ifdef CSN1_LOCAL_STACK
#define CSN1_DECLARE_STACK TCSN1Stack CSN1_Stack;
#define CSN1_EN_DECLARE_STACK TCSN1Context DataCSN1Context; TCSN1Context* CSN1Context = &DataCSN1Context;
#else
#define CSN1_GLOBAL_STACK
#ifdef CSN1_OLD_ENCODER
			extern TCSN1Stack CSN1_Stack;
#else 
			extern TCSN1Context DataCSN1Context;
#endif
#define CSN1_DECLARE_STACK 
#define CSN1_EN_DECLARE_STACK TCSN1Context* CSN1Context = &DataCSN1Context;
#endif
#endif

/*==============================================================================
	CSN.1 TRACING FACILITY

	To enable CSN.1 tracing, define CSN1_TRACE_ENABLED
==============================================================================*/
/* #define CSN1_TRACE_ENABLED */
#ifdef CSN1_TRACE_ENABLED

/*------------------------------------------------------------------------------
	This macro is invoked when entering a decoding function
	Parameters:
		Description   ASCIIZ       short text describing the action
		Buffer        const char*  pointer to the buffer being encoded 
		BitOffset     long         offset in bits from the beginning of buffer
		Length        long         number of valid bits
------------------------------------------------------------------------------*/
#ifndef CSN1_DECODE_TRACE_BEGIN
#define CSN1_DECODE_TRACE_BEGIN(Description, Buffer, BitOffset, Length) Csn1DecodeTraceBegin (Description, Buffer, BitOffset, Length)
#endif

/*------------------------------------------------------------------------------
	This macro is invoked when exiting a decoding function
	Parameters:
		Description   ASCIIZ       short text describing the action
------------------------------------------------------------------------------*/
#ifndef CSN1_DECODE_TRACE_END
#define CSN1_DECODE_TRACE_END(Description) Csn1DecodeTraceEnd (Description)
#endif

/*------------------------------------------------------------------------------
	This macro is invoked when entering an encoding function
	Parameters:
		Description   ASCIIZ       short text describing the action
------------------------------------------------------------------------------*/
#ifndef CSN1_ENCODE_TRACE_BEGIN
#define CSN1_ENCODE_TRACE_BEGIN(Description) Csn1EncodeTraceBegin (Description)
#endif

/*------------------------------------------------------------------------------
	This macro is invoked when exiting an encoding function
	Parameters:
		Description   ASCIIZ       short text describing the action
		Buffer        const char*  pointer to the buffer being encoded 
		BitOffset     long         offset in bits from the beginning of buffer
		Length        long         number of valid bits
------------------------------------------------------------------------------*/
#ifndef CSN1_ENCODE_TRACE_END
#define CSN1_ENCODE_TRACE_END(Description, Buffer, BitOffset, Length) Csn1EncodeTraceEnd (Description, Buffer, BitOffset, Length)
#endif

/*------------------------------------------------------------------------------
	Called at each event in the CSN.1 encoding/decoding process.
	Parameters:
		Description   ASCIIZ       short text describing the action
		Offset        long         bit in which this operation is performed
------------------------------------------------------------------------------*/
#ifndef CSN1_TRACE_EVENT
#define CSN1_TRACE_EVENT(Description, Offset) Csn1TraceEvent (Description, Offset)
#endif

/*------------------------------------------------------------------------------
	Called before consuming a stack element in each CSN.1 step.
	Parameters:
		Stack        const TCSN1Stack*  Stack to be printed
------------------------------------------------------------------------------*/
#ifndef CSN1_TRACE_STACK
#define CSN1_TRACE_STACK(Stack) Csn1TraceStack (Stack)
#endif

/*------------------------------------------------------------------------------
	Internal functions used to trace. See macro descriptions.
------------------------------------------------------------------------------*/
void Csn1DecodeTraceBegin (const char* Description, const char* Buffer, long BitOffset, long Length);
void Csn1DecodeTraceEnd (const char* Description);
void Csn1EncodeTraceBegin (const char* Description);
void Csn1EncodeTraceEnd (const char* Description, const char* Buffer, long BitOffset, long Length);
void Csn1TraceEvent (const char* Description, long Offset);
void Csn1TraceStack (const TCSN1Stack* Stack);
#endif /* CSN1_TRACE_ENABLED */
#ifndef CSN1_OLD_ENCODER
/*------------------------------------------------------------------------------
	Standard ENCODE function
------------------------------------------------------------------------------*/
long Csn1_Encode (const unsigned char* TableMemory, char* ED_CONST Buffer, ED_CONST long BitOffset, const void* ED_CONST Source, TCSN1NextType StartTransition, void (*const CSN1FunctionMap[]) (TCSN1Context*), int (*const CSN1ExpressionMap[]) (TCSN1Context*));

/*------------------------------------------------------------------------------
	Standard DECODE function
------------------------------------------------------------------------------*/
void Csn1_Decode (const unsigned char* TableMemory, TCSN1Context* CSN1Context, const char* ED_CONST Buffer, ED_CONST long BitOffset, void* ED_CONST Destin, unsigned long DestinSize, long Length, TCSN1NextType StartTransition, void (*const CSN1FunctionMap[]) (TCSN1Context*), int (*const CSN1ExpressionMap[]) (TCSN1Context*));

#endif

/*==============================================================================
	Section devoted to the TABLE CSN.1 code generator.
==============================================================================*/
#ifndef CSN1_OLD_ENCODER

/*------------------------------------------------------------------------------
	Actions expected in the action table
------------------------------------------------------------------------------*/
#define CSN1_STACKPUSH_NBT  0x00
#define CSN1_STACKPUSH_XNBT 0x01
#define CSN1_STACKPUSH_UTOP 0x02
#define CSN1_STACKPUSH_TRK  0x03
#define CSN1_STACKPUSH_INFR 0x04
#define CSN1_ENTER_FLD      0x05
#define CSN1_EXIT_FIELD     0x06
#define CSN1_TERM_LOOP      0x07
#define CSN1_DECOCASE_0     0x08
#define CSN1_DECOCASE_1     0x09
#define CSN1_DECOCASE_A     0x0A
#define CSN1_DECOCASE_H     0x0B
#define CSN1_DECOCASE_L     0x0C
#define CSN1_ENCOCASE_0     0x0D
#define CSN1_ENCOCASE_1     0x0E
#define CSN1_ENCOCASE_A     0x0F
#define CSN1_ENCOCASE_H     0x10
#define CSN1_ENCOCASE_L     0x11
#define CSN1_CUSTOM         0x12
#define CSN1_ENCOFIELD      0x13
#define CSN1_RETURN         0xFF

/*------------------------------------------------------------------------------
	Execute a program from the table starting at given offset
------------------------------------------------------------------------------*/
void Csn1_ExecuteTable (const unsigned char* TableMemory, TCSN1NextType Offset, TCSN1Context* CSN1Context);

#endif


#ifdef __cplusplus
}
#endif
#endif
