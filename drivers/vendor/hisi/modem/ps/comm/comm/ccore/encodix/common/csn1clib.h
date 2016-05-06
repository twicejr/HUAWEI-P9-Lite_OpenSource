/*******************************************************************************
  csn1clib.h  Developed by Dafocus - http://www.dafocus.com/
  Library for the Compact CSN.1 code generator
*******************************************************************************/
#ifndef __CSN1CLIB_H
#define __CSN1CLIB_H
#include <assert.h>
#include "ed_lib.h"
#include "ed_user.h"

/* 文件csn1_disables中定义的为hrpd消息屏蔽宏，宏定义打开后，可以屏蔽掉对应消息的编解码函数
，用来节省内存，后续版本中务必保留包含此头文件 added by z00215022 2015/10/15 */
#include "csn1_disables.h"

#ifdef __cplusplus
	extern "C" {
#endif


#ifndef CSN1C_STACK_SIZE
#define CSN1C_STACK_SIZE 256
#endif

#ifndef CSN1C_FIELDS
#define CSN1C_FIELDS      256 /* Maximum fields */
#endif

#ifndef CSN1C_USERTAGS
#define CSN1C_USERTAGS 32
#endif

#ifndef CSN1C_PAIRSET_TYPE
#define CSN1C_PAIRSET_TYPE short
#endif

#ifndef CSN1C_PAIRSET_TYPE_INVALID_VALUE
#define CSN1C_PAIRSET_TYPE_INVALID_VALUE (-1)
#endif

#ifndef CSN1C_DECLARE_CONTEXT
#define CSN1C_DECLARE_CONTEXT TCSN1CContext CSN1CContext;
#endif

#ifndef CSN1C_CONTEXT_PTR
#define CSN1C_CONTEXT_PTR (&CSN1CContext)
#endif

#ifndef CSN1C_UNDECLARE_CONTEXT
#define CSN1C_UNDECLARE_CONTEXT
#endif

#define CSN1C_CB_OK           0
#define CSN1C_CB_BACKTRACK    1
#define CSN1C_CB_FAIL         2

#ifndef CSN1C_LH_MASK
#define CSN1C_LH_MASK 0x2B
#endif

#define CSN1C_NO_CHECKEND ((ED_EXLONG)-1)
#define CSN1C_VARIABLE_SIZE ((unsigned char)0xFF)

/*------------------------------------------------------------------------------
	Values that can be returned by the expression functions
------------------------------------------------------------------------------*/
#define CSN1C_EXPR_INFINITE    0x3FFF /* Execute infinite repetitions */
#define CSN1C_EXPR_BACKTRACK   0x4000 /* Refuse the current string and bactrack */
#define CSN1C_EXPR_FAIL        0x4001 /* Terminate the decoding with an error */

#ifdef CSN1C_DEBUG_MODE
#define CSN1C_DEBUG_SIGNATURE_1  0xABE397EE
#define CSN1C_DEBUG_SIGNATURE_2  0x93A1C711
#define CSN1C_DEBUG_SIGNATURE_3  0xCEDABADE
#define CSN1C_DEBUG_SIGNATURE_4  0x192AF3C1
#define CSN1C_DEBUG_SIGNATURE_5  0xED32CE2A
#define CSN1C_DEBUG_CHECK(Context) CSN1C_DEBUG_CheckContext (Context);
#else
#define CSN1C_DEBUG_CHECK(Context)
#endif

/*------------------------------------------------------------------------------
	CSN.1 Field filler structure state
------------------------------------------------------------------------------*/
typedef struct SCSN1CFieldState {
	/* First available user tag */
	int UserTagTop;

#ifndef CSN1C_DISABLE_ADT
	/* First available field */
	int FieldsTop;

	/* Current level */
	int Level;
#endif
#ifdef CSN1C_USER_FIELDSTATE_DATA
	CSN1C_USER_FIELDSTATE_DATA
#endif

} TCSN1CFieldState;

/*------------------------------------------------------------------------------
	CSN.1 Used by users to place values on a stack
------------------------------------------------------------------------------*/
typedef struct SCSN1CUserTag {
	/* Unique tag identificator */
	int TagId;

	/* Value of that tag */
	int Value;

} TCSN1CUserTag;

#ifndef CSN1C_DISABLE_ADT
/*------------------------------------------------------------------------------
	CSN.1 Field filler structure
------------------------------------------------------------------------------*/
typedef struct SCSN1CFieldElement {
	/* Field id. */
	int FieldId;

	/* Current index. <0 means that we shall exit from this field */ 
	int Index;

	/* First bit to be used or last+1 if index<0 */
	ED_EXLONG Pos;

	/* Current nesting level - 0 for root fields */
	int Level;

	/* Parent - linked by CSN1C_LinkFields */
	struct SCSN1CFieldElement* Parent;

} TCSN1CFieldElement;
#endif

/*------------------------------------------------------------------------------
	CSN.1 Describes a CSN.1 Compact program
------------------------------------------------------------------------------*/
typedef struct SCSN1CProgram {
	/* Sequences of instructions making up the program */
	const unsigned char* ProgramCode;

	/* Number of bytes in the above program code */
	unsigned ProgramLength;

	/* 
		CSN.1 Encodix fields mapping.
		The format of the array below is:
		  <Ia> <p1> <c1> <p2> <c2> ... <pNa> <cNa>
		  <Ib> <p1> <c1> <p2> <c2> ... <pNb> <cNb>
		  ...
		Each entry starting at <Ix> describes one CSN.1 label.
		<Ia> is the entry for that label in the LabelNames array below.
		
		The following values are a set of pairs p-c, telling the field-id 'c' that
		this label should have when its parent has field-id 'p'.
		
		Normally, the CSN1C_LABEL_BEGIN/CSN1C_LABEL_END instructions carry
		a parameter 'labelEntry' which is an offset in this array. The offset points to
		the first p-c pair.
		If the label names are active (i.e. code has been generated
		with TCL configuration variable ED_CSN1C_DISABLE_LABEL_NAMES set to 0),
		at labelEntry-1 there is the index of the name of that variable in
		the array 'LabelNames'.
		
		If this field is NULL, then the code has been generated with ED_CSN1C_DISABLE_ADT
		set to 1. In that case, the labelEntry is directly the fieldId, i.e. the
		entry in the LabelNames array (if active).
	 */
	const CSN1C_PAIRSET_TYPE* FieldIdPairSet;

#ifdef CSN1C_LABEL_NAMES
	/* List of strings describing the labels */
	const char* const * LabelNames;
#endif

	/* Function map for this context */
	void (*const *FunctionMap) (void* ED_EXTRAPARAMS_DECL);
	
	/* Expression map for this context */
	unsigned ED_EXLONG (*const *ExpressionMap) (void*);

#ifdef CSN1C_ENABLE_LABEL_SIZE
	/* Points to a table containing, for each label id, the expected size */
	unsigned char const * LabelSizes;
#endif

	/* All the labels having LabelId >= than the value below are error labels */
	unsigned FirstErrorLabelId;

} TCSN1CProgram;

#ifndef CSN1C_BIT_FIELD_TYPE
#define CSN1C_BIT_FIELD_TYPE int
#endif

/*------------------------------------------------------------------------------
	CSN.1 Stack structure
	
	The StackElement serves several purposes.
		
	BACKTRACK ENTRY POINT
	It marks a point where the encoding/deconding can be reset to try another
	branch.
	- Backtrack is 1
	- Value is the program instruction where to jump in case of backtracking
	- CurrOfs is the offset of the input/output data where the pointer has to
	  be reset in case of backtracking.
	
	LOOP COUNTER ENTRY POINT
	It maintains the loop counters while looping.
	- Value is split in the following parts: 30=1:FBIT/0:VBIT 29-16=min 15-1=max
------------------------------------------------------------------------------*/
typedef struct SCSN1CStackElement {
	/* If true, this is a BACKTRACK checkpoint.
	   If set, Value contains the address of the next instrucion
	*/
	CSN1C_BIT_FIELD_TYPE Backtrack: 1;

	/* If true, this is a INFINITE LOOP BACKTRACK checkpoint. When backtracking
		 to an entry flagged as infinite loop, the stack information about labels
		 is not reset. The same applies when encoding the variable part of a (m..n) 
		 range, i.e. when between "n" and "m".
		 This is needed because a backtrack that occurs while working on a variable
		 optional part is not an error.
	*/
	CSN1C_BIT_FIELD_TYPE InfiniteLoop: 1;

	/* It depends on the instruction using it */
	CSN1C_BIT_FIELD_TYPE Value : 30;

	/* True if inside an infinite loop. If this flag is set and the engine is
	   encoding, all the optional substrings that contain non labels are not
	   encoded. This is to avoid encoding infinite sequences of constant strings.
	   Also, this applies when encoding the variable part of a (m..n) range,
	   i.e. when between "n" and "m". */
	CSN1C_BIT_FIELD_TYPE InsideInfiniteLoop: 1;

	/* True if this is a FinalOffset marker. In that case, Value is the previous FinalOffset */
	CSN1C_BIT_FIELD_TYPE FinalOffset: 1;

	/* Offset in the binary string when this record was pushed on the stack */
	CSN1C_BIT_FIELD_TYPE CurrOfs: 30;

	/* Remembers the state of the ForceReading bit */
	CSN1C_BIT_FIELD_TYPE ForceReading: 1;

	/* Remembers the current check-end value */
	CSN1C_BIT_FIELD_TYPE CheckEnd: 31;

	/* Remembers the nesting level when encoding an a non-terminal label provided the encoding */
	unsigned short NestingLevel;

	/* Current field state, to be resumed in case of backtracking */
	TCSN1CFieldState FieldState;

	/* User definable data that can be added to each CSN.1 stack element */
#ifdef CSN1C_USER_STACK_DATA
CSN1C_USER_STACK_DATA
#endif

} TCSN1CStackElement;

/*------------------------------------------------------------------------------
	Structure defining the context of a CSN.1 parser
------------------------------------------------------------------------------*/
typedef struct SCSN1CContext {
#ifdef CSN1C_DEBUG_MODE
	/* Must be CSN1C_DEBUG_SIGNATURE_1 */
	unsigned long CheckSignature1;
#endif

	/* Internal array making up the stack */
	TCSN1CStackElement Elements [CSN1C_STACK_SIZE];

#ifdef CSN1C_DEBUG_MODE
	/* Must be CSN1C_DEBUG_SIGNATURE_2 */
	unsigned long CheckSignature2;
#endif

	/* User tags */
	TCSN1CUserTag UserTags [CSN1C_USERTAGS];

#ifdef CSN1C_DEBUG_MODE
	/* Must be CSN1C_DEBUG_SIGNATURE_3 */
	unsigned long CheckSignature3;
#endif

	/* First available element */
	int Top;
	
	/* State of the fields structure */
	TCSN1CFieldState FieldState;

#ifdef CSN1C_DEBUG_MODE
	/* Must be CSN1C_DEBUG_SIGNATURE_4 */
	unsigned long CheckSignature4;
#endif

	/* Instruction to be executed in the program. This is the offset in byte in
	   'Program' where the next instruction is located. */
	unsigned ED_EXLONG NextInstruction;

	/* Current offset in bits */
	ED_EXLONG CurrOfs;

	/* Start offset in bits in Buffer */
	ED_EXLONG StartOfs;

	/* Program being executed */
	const TCSN1CProgram* Program;

	/* Buffer containing the source/destination bit-stream */
	char* Buffer;
	
	/* Length of the data in the buffer starting from the original CurrOfs */
	ED_EXLONG Length;
	
	/* Final offset used when encoding/decoding */
	ED_EXLONG FinalOffset;
	
	/* 
		Meaningful only if "Encoding" is set to true.
		If CheckEnd != CSN1C_NO_CHECKEND, then the bits in Buffer starting 
		from CurrOfs up to (not including) CheckEnd have to be read and 
		checked instead	of written. This is used when the callback function 
		has encoded a	labeled value and the encoder need to know whether 
		this branch is valid or not.
	*/
	ED_EXLONG CheckEnd;

	/* Remembers the nesting level when encoding an a non-terminal label provided the encoding */
	unsigned short NestingLevel;

#ifndef CSN1C_DISABLE_ADT
	/* Internal log of fields */
	TCSN1CFieldElement Fields [CSN1C_FIELDS];
#endif

#ifndef CSN1C_DISABLE_ADT
	/* FieldId of the external host structure */
	CSN1C_PAIRSET_TYPE HostFieldId;	
	
	/* Data pointer (source or destination) */
	void* Data;
#endif
	/* User definable data that can be added to each CSN.1 context */
#ifdef CSN1C_USER_CONTEXT_DATA
	CSN1C_USER_CONTEXT_DATA
#endif

	/* Instruction where the loop currently being executed will jump
	   when finished. Used by CSN1C_SetupLoopMin. */
	int JumpEnd : 27;

	/* True if encoding, false if decoding */
	int Encoding: 1;

	/* True when an itersection/exclusion test is being made. In this mode it
	   reads always. */
	int ForceReading: 1;
	
	/* True if the operation has failed. If set, the decoder terminates with a "FAIL". */
	int Failed: 1;

	/* True if partial decoding is allowed. In this case, the engine will return the
	   number of bits actually decoded. */
	int AllowPartialStrings: 1;

	/* If set to 0, the encoding/deconding terminates with an OK */
	int Continue: 1;

#ifdef CSN1C_DEBUG_MODE
	/* Must be CSN1C_DEBUG_SIGNATURE_5 */
	unsigned long CheckSignature5;
#endif

} TCSN1CContext;

#define CSN1C_LabelStart    0  /* A non-terminal label begins */
#define CSN1C_LabelEnd      1  /* A non-terminal label ends */
#define CSN1C_TerminalLabel 2  /* A terminal label is completely identified */


/*------------------------------------------------------------------------------
	Structure representing the parameters sent to a callback function invoked
	when encoding/decoding a field.
	
	A Callback encoding/decoding function has the following prototype:
	
	int MyCallback (TCSN1CLabelCallback* LabelCallback);
	
	The function is invoked both when encoding and decoding. The function can
	tell in which condition is being invoked (encoding or decoding) by reading
	"LabelCallback->Context->Encoding", which !=0 when encoding and ==0
	when decoding.
	
	ALWAYS
	======
	The "LabelId" field contains a number that can be used to identify the
	label.
	The code generator generates a set of "#define CSN1C_DEF_<label> N" that
	allow to easily map the label-ids to readable names.
	Also, it optionally generates an array of strings that can be accessed by
	using CSN1C_GetLabelText to obatin a standar ASCIIZ string containing the
	name of the field.

	If the callback function returns CSN1C_CB_OK, the data is accepted. 
	If it returns	CSN1C_CB_BACKTRACK, the data is refused and the decoder 
	executes a backtrack and tries again on another branch.
	If it returns CSN1C_CB_FAIL, the operation is completely aborted with
	a failure code.
		
	WHEN DECODING
	=============
	When decoding, the callback function is invoked just to inform that a label
	has been detected.
	The CSN.1 engine will invoke the call back every time that:
	  A) a non-terminal label (i.e a label containing other labels) is opened
	  B) a non-terminal label is closed
	  C) a terminal label is found
	
	In case A), "From" is the offset where the label begins; "Length" is set to 0
	because the decoder does not know where the label ends yet.
	"Kind" is set to "CSN1C_LabelStart".
	
	In case B), both "From" and "Length" are set; "Kind" is set to
	"CSN1C_LabelEnd".

	In case C), both "From" and "Length" are set; "Kind" is set to
	"CSN1C_TerminalLabel".
	
	Once "From" and "Length" are given, the callback function can access to the
	data stored at Context->Buffer and do whatever it likes with it.
	
	WHEN ENCODING
	=============
	When encoding, the callback function is invoked exactly as it is when
	decoding. However, the CSN.1 engine expects this function to encode the
	data when invoked with Kind==CSN1C_TerminalLabel.
	This means that, when Kind==CSN1C_TerminalLabel, the encoding function
	must write something on Context->Buffer starting from bit "From" and 
	writing no more than "Length" bits.
	Once done, the callback function must write in "Length" the number of bits
	it has actually written.
------------------------------------------------------------------------------*/
typedef struct SCSN1CFieldCallback {
	/* Context of the parser */
	TCSN1CContext* Context;

	/* LabelId identifying uniquely this label */
	unsigned LabelId;

#ifndef CSN1C_DISABLE_ADT
	/* FieldId identifying uniquely this field, if ADT is active */
	unsigned FieldId;
#endif
	
	/* Offset in the Context->Buffer where the data is being read 
	   (Context->Encoding == 0) or where the data is to be stored 
	   (Context->Encoding != 0) */
	ED_EXLONG From;

	/* Length of the source data if decoding, length of the encoded data if
	   encoded */
	ED_EXLONG Length;

	/* Description of the action */
	/*   CSN1C_LabelStart     A non-terminal label begins */
	/*   CSN1C_LabelEnd       A non-terminal label ends */
	/*   CSN1C_TerminalLabel  A terminal label is completely identified */
	int Kind;

	/* Value that is expected in this situation to go along.
	   The CSN.1 processor suggests this value when encodign things
	   like <label: 00010010> or similar.
	   The callback function can use this information to return
	   default values. */
	unsigned ED_EXLONG SuggestedValue;
	int SuggestedValueLengthInBits; /* Negative if there is no suggested value */

} TCSN1CLabelCallback;

/*------------------------------------------------------------------------------
	Initialize a context to be used with "CSN1C_Process".
------------------------------------------------------------------------------*/
void CSN1C_Init (
	TCSN1CContext* Context,        /* Pointer to the TCSN1CContext object being initialized */
	const TCSN1CProgram* Program,  /* Pointer to the CSN.1 program object generated by Encodix */
	unsigned StartInstruction,     /* Offset of the required string in the program */
	const void* Buffer,            /* Buffer where data is read/written */
	ED_EXLONG BitOffset,           /* Offset in bits in the buffer where to start reading/writing */
	ED_EXLONG Length,              /* Length of the source data when reading, written data when writing */
	int Encoding                   /* !=0 if encoding is required, ==0 if decoding is required */
);

/*------------------------------------------------------------------------------
	CSN.1 Compact - DECODE/ENCODE function
	It returns the number of bits used or <0 in case of error.
	The "Context" variable must have been set with CSN1C_Init.
------------------------------------------------------------------------------*/
ED_EXLONG CSN1C_Process (TCSN1CContext* Context, int (*LabelCallBack)(TCSN1CLabelCallback* FieldCallbackParam ED_EXTRAPARAMS_DECL) ED_EXTRAPARAMS_DECL);

/*------------------------------------------------------------------------------
	CSN.1 Compact - Executes a BACKTRACK.
	The "BACKTRACK" operation is executed when a CSN.1 branch failed.
	Everything is restored down to topmost backtrack entry on the stack.
	If there are no backtrack checkpoints, it means that the entire parsing is
	failed.
	It returns 0=FAILED, 1=OK
------------------------------------------------------------------------------*/
int CSN1C_Backtrack (TCSN1CContext* Context);

/*------------------------------------------------------------------------------
	Given a program and a "LabelEntry" value, it returns a string describing
	the label or "NULL" if the description is not available.
------------------------------------------------------------------------------*/
const char* CSN1C_GetLabelText (const TCSN1CProgram* Program, unsigned LabelEntry);

/*------------------------------------------------------------------------------
	Adds a value with given code on the stack
------------------------------------------------------------------------------*/
void CSN1C_PushValue (TCSN1CContext* Context, int Tag, int Value);

/*------------------------------------------------------------------------------
	Returns given value from the stack
------------------------------------------------------------------------------*/
int CSN1C_GetValue (const TCSN1CContext* Context, int Tag);

/*------------------------------------------------------------------------------
	Returns given Value from the stack; in case the value is not found, it
	returns 0.
------------------------------------------------------------------------------*/
int CSN1C_GetValueOrZero (const TCSN1CContext* Context, int Tag);

/*------------------------------------------------------------------------------
	Returns 1 if the given tag exists; 0 if it does not exist.
------------------------------------------------------------------------------*/
int CSN1C_ExistsValue (const TCSN1CContext* Context, int Tag);

/*------------------------------------------------------------------------------
	Sets a value with the given tag
------------------------------------------------------------------------------*/
void CSN1C_SetValue (TCSN1CContext* Context, int Tag, int Value);

/*------------------------------------------------------------------------------
	Deletes all the tags until reaching the given tag, which is deleted as well.
------------------------------------------------------------------------------*/
void CSN1C_PopValues (TCSN1CContext* Context, int Tag);

/*------------------------------------------------------------------------------
	Debug mode function used to ensure CSN.1 Context integrity
------------------------------------------------------------------------------*/
#ifdef CSN1C_DEBUG_MODE
void CSN1C_DEBUG_CheckContext (const TCSN1CContext* Context);
#endif

/*------------------------------------------------------------------------------
	Macros used to build the program table
------------------------------------------------------------------------------*/
#define CSN1C_VAL1(val) ((unsigned char)((((unsigned long)(val)))&0x7f))
#define CSN1C_VAL2(val) ((unsigned char)(0x80|((((unsigned long)(val))>>7)&0x7f))),((unsigned char)(((((unsigned long)(val)))&0x7f)))
#define CSN1C_VAL3(val) ((unsigned char)(0x80|((((unsigned long)(val))>>14)&0x7f))),((unsigned char)(0x80|((((unsigned long)(val))>>7)&0x7f))),((unsigned char)(((((unsigned long)(val)))&0x7f)))
#define CSN1C_VAL4(val) ((unsigned char)(0x80|((((unsigned long)(val))>>21)&0x7f))),((unsigned char)(0x80|((((unsigned long)(val))>>14)&0x7f))),((unsigned char)(0x80|((((unsigned long)(val))>>7)&0x7f))),((unsigned char)(((((unsigned long)(val)))&0x7f)))
#define CSN1C_VAL5(val) ((unsigned char)(0x80|((((unsigned long)(val))>>25)&0x7f))),((unsigned char)(0x80|((((unsigned long)(val))>>19)&0x7f))),((unsigned char)(0x80|((((unsigned long)(val))>>11)&0x7f))),((unsigned char)(0x80|((((unsigned long)(val))>>4)&0x7f))),((unsigned char)(((((unsigned long)(val)))&0x0f)))

#define CSN1C_GOTO(relpos)         (unsigned char)(0x40 | (((relpos)>>8) & 0x3F)), ((relpos) & 0xFF)
#define CSN1C_GOTO_CMD              ((unsigned char)0x40)
#define CSN1C_CHOICE_NODE(fbit,relpos) (unsigned char)(0x80 | (fbit? 0x20 : 0) | (((relpos)>>8) & 0x1F)), (unsigned char)((relpos) & 0xFF)
#define CSN1C_CHOICE_NODE_CMD       ((unsigned char)0x80)
#define CSN1C_BIT_A(reps)           ((unsigned char)(0xC0 | ((reps) & 0x3F)))
#define CSN1C_BIT_A_CMD             ((unsigned char)0xC0)

#define CSN1C_BACKTRACK               ((unsigned char) 1)
#define CSN1C_BIT_0                   ((unsigned char) 2)
#define CSN1C_BIT_1                   ((unsigned char) 3)
#define CSN1C_BIT_H                   ((unsigned char) 4)
#define CSN1C_BIT_L                   ((unsigned char) 5)
#define CSN1C_CHOICE_END              ((unsigned char) 6)
#define CSN1C_EXCLUSION_BEGIN         ((unsigned char) 7)
#define CSN1C_EXCLUSION_END           ((unsigned char) 8)
#define CSN1C_EXECUTE                 ((unsigned char) 9)
#define CSN1C_EXECUTE_DEC             ((unsigned char)10)
#define CSN1C_EXECUTE_ENC             ((unsigned char)11)
#define CSN1C_GOSUB                   ((unsigned char)12)
#define CSN1C_INTERSECTION_BEGIN      ((unsigned char)13)
#define CSN1C_INTERSECTION_END        ((unsigned char)14)
#define CSN1C_JUMP_IF_ENCODING        ((unsigned char)15)
#define CSN1C_LABEL_A                 ((unsigned char)16)
#define CSN1C_LABEL_BEGIN             ((unsigned char)17)
#define CSN1C_LABEL_END               ((unsigned char)18)
#define CSN1C_LABEL_END_TAG           ((unsigned char)19)
#define CSN1C_LOOP_BEGIN_FIXED        ((unsigned char)20)
#define CSN1C_LOOP_BEGIN_FIXED_OPTVAL ((unsigned char)21)
#define CSN1C_LOOP_BEGIN_FIXED_TAG    ((unsigned char)22)
#define CSN1C_LOOP_BEGIN_INFINITE     ((unsigned char)23)
#define CSN1C_LOOP_BEGIN_INF_MIN      ((unsigned char)24)
#define CSN1C_LOOP_BEGIN_MINMAX       ((unsigned char)25)
#define CSN1C_LOOP_BEGIN_VAR_ED1      ((unsigned char)26)
#define CSN1C_LOOP_BEGIN_VAR_ED2      ((unsigned char)27)
#define CSN1C_LOOP_BEGIN_VAR_ED_INF   ((unsigned char)28)
#define CSN1C_LOOP_CYCLE              ((unsigned char)29)
#define CSN1C_LOOP_SET_MIN_ED1        ((unsigned char)30)
#define CSN1C_LOOP_SET_MIN_ED2        ((unsigned char)31)
#define CSN1C_LOOP_SET_MIN_FIXED      ((unsigned char)32)
#define CSN1C_NOP                     ((unsigned char)33)
#define CSN1C_PUSH_CURROFS            ((unsigned char)34)
#define CSN1C_RETURN                  ((unsigned char)35)
#define CSN1C_TAG_POS                 ((unsigned char)36)
#define CSN1C_UPDATE_BACKTRACK        ((unsigned char)37)
#define CSN1C_VALUE                   ((unsigned char)38)
#define CSN1C_SUBCLASS_SINGLE         ((unsigned char)39)
#define CSN1C_SUBCLASS_RANGE          ((unsigned char)40)
#define CSN1C_SUBCLASS_SINGLE_EXPR    ((unsigned char)41)
#define CSN1C_SUBCLASS_RANGE_EXPR     ((unsigned char)42)
#define CSN1C_LABEL_VALUE             ((unsigned char)43)
#define CSN1C_FORCED_NULL             ((unsigned char)44)
#define CSN1C_RETURN_LOOPING          ((unsigned char)45)


#define CSN1C_NO_BACKTRACK (-1)

extern struct SCSN1CContextSet  CSN1CContextSet_0087;
extern struct SCSN1CContext     CSN1CContexts_0087[3];
extern struct SCSN1CContextSet *pCSN1CContextSet_0087;
extern struct SCSN1CContextSet  CSN1CContextSet_0063;
extern struct SCSN1CContext     CSN1CContexts_0063[3];
extern struct SCSN1CContextSet *pCSN1CContextSet_0063;
extern struct SCSN1CContextSet  CSN1CContextSet_0024;
extern struct SCSN1CContext     CSN1CContexts_0024[3];
extern struct SCSN1CContextSet *pCSN1CContextSet_0024;


#define CAS_DO_CS0087_CONTEXT  pCSN1CContextSet_0087
#define CAS_DO_CS0063_CONTEXT  pCSN1CContextSet_0063
#define CAS_DO_CS0024_CONTEXT  pCSN1CContextSet_0024

#ifdef __cplusplus
}
#endif
#endif
