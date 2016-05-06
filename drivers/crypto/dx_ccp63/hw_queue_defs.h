/***************************************************************
*  Copyright 2014 (c) Discretix Technologies Ltd.              *
*  This software is protected by copyright, international      *
*  treaties and various patents. Any copy, reproduction or     *
*  otherwise use of this software must be authorized in a      *
*  license agreement and include this Copyright Notice and any *
*  other notices specified in the license agreement.           *
*  Any redistribution in binary form must be authorized in the *
*  license agreement and include this Copyright Notice and     *
*  any other notices specified in the license agreement and/or *
*  in materials provided with the binary distribution.         *
****************************************************************/

#ifndef __HW_QUEUE_DEFS_H__
#define __HW_QUEUE_DEFS_H__

#include "dx_pal_log.h"
#include "dx_hal.h"
#include "dx_cc_regs.h"
#include "dx_crys_kernel.h"

#ifdef __KERNEL__
#include <linux/types.h>
#define UINT32_MAX 0xFFFFFFFFL
#define INT32_MAX  0x7FFFFFFFL
#define UINT16_MAX 0xFFFFL
#else
#include <stdint.h>
#endif

/******************************************************************************
*                        	DEFINITIONS
******************************************************************************/

/* Dma AXI Secure bit */
#define	AXI_SECURE	0
#define AXI_NOT_SECURE	1

#define HW_DESC_SIZE_WORDS		6

#define HW_QUEUE_SLOTS_MAX              15 /* Max. available slots in HW queue */
#define NO_OS_WATER_MARK_TIMEOUT 	1000000
#define NO_OS_QUEUE_ID                  0
#define NO_OS_AXI_NS 	                AXI_SECURE
#define SET_REGISTER_DESC_MARK		0xFFFFFF
#define DESC_INPUT_CONST_MARK		0xF
#define LOCK_HW_QUEUE			1
#define UNLOCK_HW_QUEUE			0

/******************************************************************************
*				MACROS
******************************************************************************/
/* Macro to convert Q ID to AXI completion counter ID.  */
#define QID_TO_AXI_ID(qid) (qid)
/* check QID range validity */
#define IS_VALID_QID(qid) ( ((qid) < MAX_NUM_HW_QUEUES) && ((qid) >= 0) )

/******************************************************************************
*				TYPE DEFINITIONS
******************************************************************************/

typedef struct HwDesc {
	uint32_t word[HW_DESC_SIZE_WORDS];
} HwDesc_s;

/* User this set of macros to get a specific descriptor word, queue water mark,
 queue space left or queue flow id pointer */
#define GET_HW_Q_DESC_WORD_IDX(qid, descWordIdx) (DX_CC_REG_OFFSET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD ## descWordIdx) + (32 * (qid)))
#define GET_HW_Q_WATERMARK(qid) (DX_CC_REG_OFFSET(CRY_KERNEL, DSCRPTR_QUEUE0_WATERMARK) + (32 * (qid)))
#define GET_HW_Q_SPACELEFT(qid) (DX_CC_REG_OFFSET(CRY_KERNEL, DSCRPTR_QUEUE0_CONTENT) + (32 * (qid)))
#define GET_HW_Q_FLOWID(qid) (DX_CC_REG_OFFSET(CRY_KERNEL, DSCRPTR_QUEUE0_FLOW_ID) + (32 * (qid)))

typedef enum DescDirection {
	DESC_DIRECTION_ILLEGAL = -1,
	DESC_DIRECTION_ENCRYPT_ENCRYPT = 0,
	DESC_DIRECTION_DECRYPT_DECRYPT = 1,
	DESC_DIRECTION_DECRYPT_ENCRYPT = 3,
	DESC_DIRECTION_END = INT32_MAX,
}DescDirection_t;

typedef enum DmaMode {
	DMA_MODE_NULL		= -1,
	NO_DMA 			= 0,
	DMA_SRAM		= 1,
	DMA_DLLI		= 2,
	DMA_MLLI		= 3,
	DmaMode_OPTIONTS,
	DmaMode_END 		= INT32_MAX,
}DmaMode_t;

typedef enum FlowMode {
	FLOW_MODE_NULL		= -1,
	/* data flows */
 	BYPASS			= 0,
	DIN_AES_DOUT		= 1,
	AES_to_HASH		= 2,
	AES_and_HASH		= 3,
	DIN_DES_DOUT		= 4,
	DES_to_HASH		= 5,
	DES_and_HASH		= 6,
	DIN_HASH		= 7,
	DIN_HASH_and_BYPASS	= 8,
	AESMAC_and_BYPASS	= 9,
	AES_to_HASH_and_DOUT	= 10,
	DIN_RC4_DOUT		= 11,
	DES_to_HASH_and_DOUT	= 12,
	AES_to_AES_to_HASH_and_DOUT	= 13,
	AES_to_AES_to_HASH	= 14,
	AES_to_HASH_and_AES	= 15,
	DIN_MULTI2_DOUT		= 16,
	DIN_AES_AESMAC		= 17,
	HASH_to_DOUT		= 18,
	/* setup flows */
 	S_DIN_to_AES 		= 32,
	S_DIN_to_AES2		= 33,
	S_DIN_to_DES		= 34,
	S_DIN_to_RC4		= 35,
 	S_DIN_to_MULTI2		= 36,
	S_DIN_to_HASH		= 37,
	S_AES_to_DOUT		= 38,
	S_AES2_to_DOUT		= 39,
	S_RC4_to_DOUT		= 41,
	S_DES_to_DOUT		= 42,
	S_HASH_to_DOUT		= 43,
	SET_FLOW_ID		= 44,
	FlowMode_OPTIONTS,
	FlowMode_END = INT32_MAX,
}FlowMode_t;

typedef enum TunnelOp {
	TUNNEL_OP_INVALID = -1,
	TUNNEL_OFF = 0,
	TUNNEL_ON = 1,
	TunnelOp_OPTIONS,
	TunnelOp_END = INT32_MAX,
} TunnelOp_t;

typedef enum SetupOp {
	SETUP_LOAD_NOP		= 0,
	SETUP_LOAD_STATE0	= 1,
	SETUP_LOAD_STATE1	= 2,
	SETUP_LOAD_STATE2	= 3,
	SETUP_LOAD_KEY0		= 4,
	SETUP_LOAD_XEX_KEY	= 5,
	SETUP_WRITE_STATE0	= 8, 
	SETUP_WRITE_STATE1	= 9,
	SETUP_WRITE_STATE2	= 10,
	SETUP_WRITE_STATE3	= 11,
	setupOp_OPTIONTS,
	setupOp_END = INT32_MAX,	
}SetupOp_t;

enum AesMacSelector {
	AES_SK = 1,
	AES_CMAC_INIT = 2,
	AES_CMAC_SIZE0 = 3,
	AesMacEnd = INT32_MAX,
};

typedef enum HwCryptoKey {
	USER_KEY = 0,
	ROOT_KEY = 1,
	PROVISIONING_KEY = 2,
	SESSION_KEY = 3,
	END_OF_KEYS = INT32_MAX,
}HwCryptoKey_t;

typedef enum HwAesKeySize {
	AES_128_KEY = 0,
	AES_192_KEY = 1,
	AES_256_KEY = 2,
	END_OF_AES_KEYS = INT32_MAX,
}HwAesKeySize_t;

typedef enum HwDesKeySize {
	DES_ONE_KEY = 0,
	DES_TWO_KEYS = 1,
	DES_THREE_KEYS = 2,
	END_OF_DES_KEYS = INT32_MAX,
}HwDesKeySize_t;

/*****************************/
/* Descriptor packing macros */
/*****************************/

#define HW_DESC_INIT(pDesc)  do { \
	(pDesc)->word[0] = 0;     \
	(pDesc)->word[1] = 0;     \
	(pDesc)->word[2] = 0;     \
	(pDesc)->word[3] = 0;     \
	(pDesc)->word[4] = 0;     \
	(pDesc)->word[5] = 0;     \
} while (0)

#define HW_DESC_PUSH_TO_QUEUE(qid, pDesc) do {        				  \
	LOG_HW_DESC(pDesc);							  \
	HW_DESC_DUMP(pDesc);							  \
	DX_HAL_WriteCcRegister(GET_HW_Q_DESC_WORD_IDX(qid, 0), (pDesc)->word[0]); \
	DX_HAL_WriteCcRegister(GET_HW_Q_DESC_WORD_IDX(qid, 1), (pDesc)->word[1]); \
	DX_HAL_WriteCcRegister(GET_HW_Q_DESC_WORD_IDX(qid, 2), (pDesc)->word[2]); \
	DX_HAL_WriteCcRegister(GET_HW_Q_DESC_WORD_IDX(qid, 3), (pDesc)->word[3]); \
	DX_HAL_WriteCcRegister(GET_HW_Q_DESC_WORD_IDX(qid, 4), (pDesc)->word[4]); \
	DX_HAL_WriteCcRegister(GET_HW_Q_DESC_WORD_IDX(qid, 5), (pDesc)->word[5]); \
} while (0)


/* HW descriptor debug functions */
int createDetailedDump(HwDesc_s *pDesc);
void descriptor_log(HwDesc_s *desc);
void descriptor_dump(void);

#if defined(HW_DESCRIPTOR_LOG) || defined(HW_DESC_DUMP_HOST_BUF)
#define LOG_HW_DESC(pDesc) descriptor_log(pDesc)
#else
#define LOG_HW_DESC(pDesc) 
#endif

#if (DX_PAL_MAX_LOG_LEVEL >= DX_PAL_LOG_LEVEL_TRACE) || defined(OEMFW_LOG)

#ifdef UART_PRINTF
#define CREATE_DETAILED_DUMP(pDesc) createDetailedDump(pDesc)
#else
#define CREATE_DETAILED_DUMP(pDesc) 
#endif 

#define HW_DESC_DUMP(pDesc) do {            			\
	DX_PAL_LOG_TRACE("\n---------------------------------------------------\n");	\
	CREATE_DETAILED_DUMP(pDesc); 				\
	DX_PAL_LOG_TRACE("0x%08X, ", (unsigned int)(pDesc)->word[0]);  	\
	DX_PAL_LOG_TRACE("0x%08X, ", (unsigned int)(pDesc)->word[1]);  	\
	DX_PAL_LOG_TRACE("0x%08X, ", (unsigned int)(pDesc)->word[2]);  	\
	DX_PAL_LOG_TRACE("0x%08X, ", (unsigned int)(pDesc)->word[3]);  	\
	DX_PAL_LOG_TRACE("0x%08X, ", (unsigned int)(pDesc)->word[4]);  	\
	DX_PAL_LOG_TRACE("0x%08X\n", (unsigned int)(pDesc)->word[5]);  	\
	DX_PAL_LOG_TRACE("---------------------------------------------------\n\n");    \
} while (0)

#else
#define HW_DESC_DUMP(pDesc) do {} while (0)
#endif

//#else
//#error The macro HW_DESC_INIT must be fixed to match HW-desc. size
//#endif

#define HW_QUEUE_FREE_SLOTS_GET(qid) (DX_HAL_ReadCcRegister(GET_HW_Q_SPACELEFT(qid)) & HW_QUEUE_SLOTS_MAX)

#define HW_QUEUE_NO_OS_POLL_COMPLETION()										\
	do {														\
	} while ((HW_QUEUE_FREE_SLOTS_GET(NO_OS_QUEUE_ID) < HW_QUEUE_SLOTS_MAX) ||					\
		 (DX_HAL_ReadCcRegister(DX_CC_REG_OFFSET(CRY_KERNEL, AXIM_MON_INFLIGHT8)) != 0))

#define HW_QUEUE_POLL_QUEUE_UNTIL_FREE_SLOTS(qid, seqLen)									\
	do {														\
	} while (HW_QUEUE_FREE_SLOTS_GET((qid)) < (seqLen))

/* Polls queue until queue is empty, up to given polling iterations (timeout). */
/* Returns 0 if not empty or 1 if empty */
#define HW_QUEUE_POLL_QUEUE_UNTIL_EMPTY(_qid, _poll_timeout)			            \
	({       								            \
		int _timeout, _free_slots;                                                  \
		for (_timeout = _poll_timeout, _free_slots = HW_QUEUE_FREE_SLOTS_GET(_qid); \
			(_free_slots < HW_QUEUE_SLOTS_MAX) && (_timeout > 0);               \
			_free_slots = HW_QUEUE_FREE_SLOTS_GET(_qid), _timeout--);           \
		(_free_slots == HW_QUEUE_SLOTS_MAX);                                        \
	})

#define HW_DESC_SET_ACK_NEEDED(pDesc, counterId) 									\
	do {														\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD4, ACK_NEEDED, (pDesc)->word[4], (counterId+1));	\
	} while (0)

/*!
 * This function sets the DIN field of a HW descriptors
 * 
 * \param pDesc pointer HW descriptor struct 
 * \param dmaMode The DMA mode: NO_DMA, SRAM, DLLI, MLLI, CONSTANT
 * \param dinAdr DIN address
 * \param dinSize Data size in bytes 
 * \param axiId AXI master ARID 
 * \param axiNs AXI secure bit
 */
#define HW_DESC_SET_DIN_TYPE(pDesc, dmaMode, dinAdr, dinSize, axiId, axiNs)							\
	do {		                                                                                        		\
		/* use QUEUE0 since the offsets in each QUEUE does not depend on the QID */					\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD0, VALUE, (pDesc)->word[0], dinAdr&UINT32_MAX );		\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD5, DIN_ADDR_HIGH, (pDesc)->word[5], (dinAdr>>32)&UINT16_MAX );		\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD1, DIN_DMA_MODE, (pDesc)->word[1], (dmaMode));			\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD1, DIN_SIZE, (pDesc)->word[1], (dinSize));			\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD1, DIN_VIRTUAL_HOST, (pDesc)->word[1], (axiId));		\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD1, NS_BIT, (pDesc)->word[1], (axiNs));				\
	} while (0)


/*!
 * This function sets the DIN field of a HW descriptors to NO DMA mode. Used for NOP descriptor, register patches and 
 * other special modes 
 * 
 * \param pDesc pointer HW descriptor struct
 * \param dinAdr DIN address
 * \param dinSize Data size in bytes 
 */
#define HW_DESC_SET_DIN_NO_DMA(pDesc, dinAdr, dinSize)									\
	do {		                                                                                        	\
		/* use QUEUE0 since the offsets in each QUEUE does not depend on the QID */				\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD0, VALUE, (pDesc)->word[0], (uint32_t)(dinAdr));	\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD1, DIN_SIZE, (pDesc)->word[1], (dinSize));		\
	} while (0)

/*!
 * This function sets the DIN field of a HW descriptors to SRAM mode. 
 * Note: No need to check SRAM alignment since host requests do not use SRAM and 
 * adaptor will enforce alignment check. 
 * 
 * \param pDesc pointer HW descriptor struct
 * \param dinAdr DIN address
 * \param dinSize Data size in bytes 
 */
#define HW_DESC_SET_DIN_SRAM(pDesc, dinAdr, dinSize)									\
	do {		                                                                                        	\
		/* use QUEUE0 since the offsets in each QUEUE does not depend on the QID */				\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD0, VALUE, (pDesc)->word[0], (uint32_t)(dinAdr));	\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD1, DIN_DMA_MODE, (pDesc)->word[1], DMA_SRAM);		\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD1, DIN_SIZE, (pDesc)->word[1], (dinSize));		\
	} while (0)

/*!
 * This function sets the DIN field of a HW descriptors to CONST mode 
 * PAY ATTENTION TO HW_DESC_RESET_CONST_INPUT! 
 * 
 * \param pDesc pointer HW descriptor struct
 * \param val DIN const value
 * \param dinSize Data size in bytes 
 */
#define HW_DESC_SET_DIN_CONST(pDesc, val, dinSize)									\
	do {		                                                                                        	\
		/* use QUEUE0 since the offsets in each QUEUE does not depend on the QID */				\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD0, VALUE, (pDesc)->word[0], (uint32_t)(val));		\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD1, DIN_CONST_VALUE, (pDesc)->word[1], 1);		\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD1, DIN_DMA_MODE, (pDesc)->word[1], DMA_SRAM);		\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD1, DIN_SIZE, (pDesc)->word[1], (dinSize));		\
	} while (0)

/*!
 * This function sets the DIN not last input data indicator
 * 
 * \param pDesc pointer HW descriptor struct
 */
#define HW_DESC_SET_DIN_NOT_LAST_INDICATION(pDesc)									\
	do {		                                                                                        	\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD1, NOT_LAST, (pDesc)->word[1], 1);			\
	} while (0)

/*!
 * This function sets the DOUT field of a HW descriptors 
 * NOTE: LAST INDICATION bit should be set only for last descriptor intentionally.
 * 
 * \param pDesc pointer HW descriptor struct 
 * \param dmaMode The DMA mode: NO_DMA, SRAM, DLLI, MLLI, CONSTANT
 * \param doutAdr DOUT address
 * \param doutSize Data size in bytes 
 * \param axiId AXI master ARID 
 * \param axiNs AXI secure bit
 */

#define HW_DESC_SET_DOUT_TYPE(pDesc, dmaMode, doutAdr, doutSize, axiId, axiNs)							\
	do {		                                                                                        		\
		/* use QUEUE0 since the offsets in each QUEUE does not depend on the QID */					\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD2, VALUE, (pDesc)->word[2], doutAdr&UINT32_MAX );		\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD5, DOUT_ADDR_HIGH, (pDesc)->word[5], (doutAdr>>32)&UINT16_MAX );		\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD3, DOUT_DMA_MODE, (pDesc)->word[3], (dmaMode));		\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD3, DOUT_SIZE, (pDesc)->word[3], (doutSize));			\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD3, DOUT_VIRTUAL_HOST, (pDesc)->word[3], (axiId));		\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD3, NS_BIT, (pDesc)->word[3], (axiNs));				\
	} while (0)


/*!
 * This function sets the DOUT field of a HW descriptors to DLLI type 
 * The LAST INDICATION is provided by the user 
 * 
 * \param pDesc pointer HW descriptor struct 
 * \param doutAdr DOUT address
 * \param doutSize Data size in bytes 
 * \param axiId AXI master ARID 
 * \param axiNs AXI secure bit 
 * \param lastInd The last indication bit
 */

#define HW_DESC_SET_DOUT_DLLI(pDesc, doutAdr, doutSize, axiId, axiNs ,lastInd)							\
	do {		                                                                                        		\
		/* use QUEUE0 since the offsets in each QUEUE does not depend on the QID */					\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD2, VALUE, (pDesc)->word[2], doutAdr&UINT32_MAX );		\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD5, DOUT_ADDR_HIGH, (pDesc)->word[5], (doutAdr>>32)&UINT16_MAX );		\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD3, DOUT_DMA_MODE, (pDesc)->word[3], DMA_DLLI);			\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD3, DOUT_SIZE, (pDesc)->word[3], (doutSize));			\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD3, DOUT_VIRTUAL_HOST, (pDesc)->word[3], (axiId));		\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD3, DOUT_LAST_IND, (pDesc)->word[3], lastInd);			\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD3, NS_BIT, (pDesc)->word[3], (axiNs));				\
	} while (0)

/*!
 * This function sets the DOUT field of a HW descriptors to DLLI type 
 * The LAST INDICATION is provided by the user 
 * 
 * \param pDesc pointer HW descriptor struct 
 * \param doutAdr DOUT address
 * \param doutSize Data size in bytes 
 * \param axiId AXI master ARID 
 * \param axiNs AXI secure bit 
 * \param lastInd The last indication bit
 */

#define HW_DESC_SET_DOUT_MLLI(pDesc, doutAdr, doutSize, axiId, axiNs ,lastInd)							\
	do {		                                                                                        		\
		/* use QUEUE0 since the offsets in each QUEUE does not depend on the QID */					\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD2, VALUE, (pDesc)->word[2], doutAdr&UINT32_MAX );		\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD5, DOUT_ADDR_HIGH, (pDesc)->word[5], (doutAdr>>32)&UINT16_MAX );		\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD3, DOUT_DMA_MODE, (pDesc)->word[3], DMA_MLLI);			\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD3, DOUT_SIZE, (pDesc)->word[3], (doutSize));			\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD3, DOUT_VIRTUAL_HOST, (pDesc)->word[3], (axiId));		\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD3, DOUT_LAST_IND, (pDesc)->word[3], lastInd);			\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD3, NS_BIT, (pDesc)->word[3], (axiNs));				\
	} while (0)

/*!
 * This function sets the DOUT field of a HW descriptors to NO DMA mode. Used for NOP descriptor, register patches and 
 * other special modes 
 * 
 * \param pDesc pointer HW descriptor struct
 * \param doutAdr DOUT address
 * \param doutSize Data size in bytes  
 * \param registerWriteEnable Enables a write operation to a register
 */
#define HW_DESC_SET_DOUT_NO_DMA(pDesc, doutAdr, doutSize, registerWriteEnable)							\
	do {		                                                                                        		\
		/* use QUEUE0 since the offsets in each QUEUE does not depend on the QID */					\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD2, VALUE, (pDesc)->word[2], (uint32_t)(doutAdr));		\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD3, DOUT_SIZE, (pDesc)->word[3], (doutSize));			\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD3, DOUT_LAST_IND, (pDesc)->word[3], (registerWriteEnable));	\
	} while (0)

/*!
 * This function sets the word for the XOR operation. 
 * 
 * \param pDesc pointer HW descriptor struct
 * \param xorVal xor data value
 */
#define HW_DESC_SET_XOR_VAL(pDesc, xorVal)										\
	do {		                                                                                        	\
		/* use QUEUE0 since the offsets in each QUEUE does not depend on the QID */				\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD2, VALUE, (pDesc)->word[2], (uint32_t)(xorVal));	\
	} while (0)

/*!
 * This function sets the XOR indicator bit in the descriptor
 * 
 * \param pDesc pointer HW descriptor struct
 */
#define HW_DESC_SET_XOR_ACTIVE(pDesc)											\
	do {		                                                                                        	\
		/* use QUEUE0 since the offsets in each QUEUE does not depend on the QID */				\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD3, HASH_XOR_BIT, (pDesc)->word[3], 1);			\
	} while (0)

/*!
 * This function selects the AES engine instead of HASH engine when setting up combined mode with AES XCBC MAC
 * 
 * \param pDesc pointer HW descriptor struct
 */
#define HW_DESC_SET_AES_NOT_HASH_MODE(pDesc)										\
	do {		                                                                                       	 	\
		/* use QUEUE0 since the offsets in each QUEUE does not depend on the QID */				\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD4, AES_SEL_N_HASH, (pDesc)->word[4], 1);		\
	} while (0)

/*!
 * This function sets the DOUT field of a HW descriptors to SRAM mode
 * Note: No need to check SRAM alignment since host requests do not use SRAM and 
 * adaptor will enforce alignment check. 
 * 
 * \param pDesc pointer HW descriptor struct
 * \param doutAdr DOUT address
 * \param doutSize Data size in bytes 
 */
#define HW_DESC_SET_DOUT_SRAM(pDesc, doutAdr, doutSize)									\
	do {		                                                                                        	\
		/* use QUEUE0 since the offsets in each QUEUE does not depend on the QID */				\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD2, VALUE, (pDesc)->word[2], (uint32_t)(doutAdr));	\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD3, DOUT_DMA_MODE, (pDesc)->word[3], DMA_SRAM);		\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD3, DOUT_SIZE, (pDesc)->word[3], (doutSize));		\
	} while (0)

/*!
 * This function checks if the descriptor is of type DLLI or MLLI
 * 
 * \param pDesc pointer HW descriptor struct
 */
#define IS_HW_DESC_DOUT_TYPE_AXI(pDesc)											\
	( ( DX_CC_REG_FLD_GET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD3, DOUT_DMA_MODE, (pDesc)->word[3]) == DMA_MLLI ) ||	\
	  ( DX_CC_REG_FLD_GET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD3, DOUT_DMA_MODE, (pDesc)->word[3]) == DMA_DLLI ) )

/*
 @brief: This function sets the data unit size for XEX mode in data_out_addr[15:0]
 
 @params:
 	pDesc [in] -A pointer to a HW descriptor, 5 words long according to
 	           [CC54-DESC]. The descriptor buffer must be word aligned

	dataUnitSize [in] - data unit size for XEX mode
*/
#define HW_DESC_SET_XEX_DATA_UNIT_SIZE(pDesc, dataUnitSize)								\
	do {														\
		/* use QUEUE0 since the offsets in each QUEUE does not depend on the QID */				\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD2, VALUE, (pDesc)->word[2], (uint32_t)(dataUnitSize));	\
	} while (0)

/*
 @brief: This function sets the number of rounds for Multi2 in data_out_addr[15:0]
 
 @params:
 	pDesc [in] -A pointer to a HW descriptor, 5 words long according to
 	           [CC54-DESC]. The descriptor buffer must be word aligned

	numRounds [in] - number of rounds for Multi2
*/
#define HW_DESC_SET_MULTI2_NUM_ROUNDS(pDesc, numRounds)								\
	do {														\
		/* use QUEUE0 since the offsets in each QUEUE does not depend on the QID */				\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD2, VALUE, (pDesc)->word[2], (uint32_t)(numRounds));	\
	} while (0)

/*
 @brief: This function sets the flow mode.
 
 @params:
 	pDesc [in] -A pointer to a HW descriptor, 5 words long according to
 	           [CC54-DESC]. The descriptor buffer must be word aligned

	flowMode [in] -Any one of the modes defined in [CC54-DESC]
*/

#define HW_DESC_SET_FLOW_MODE(pDesc, flowMode)										\
	do {														\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD4, DATA_FLOW_MODE, (pDesc)->word[4], (flowMode));	\
	} while (0)

/*
 @brief: This function sets the cipher mode.
 
 @params:
 	pDesc [in] -A pointer to a HW descriptor, 5 words long according to
 	           [CC54-DESC]. The descriptor buffer must be word aligned

	cipherMode [in] -Any one of the modes defined in [CC54-DESC]
*/
#define HW_DESC_SET_CIPHER_MODE(pDesc, cipherMode)									\
	do {														\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD4, CIPHER_MODE, (pDesc)->word[4], (cipherMode));	\
	} while (0)

/*
 @brief: This function sets the cipher configuration fields.
 
 @params:
 	pDesc [in] -A pointer to a HW descriptor, 5 words long according to
 	           [CC54-DESC]. The descriptor buffer must be word aligned

	cipherMode [in] -Any one of the configuration options defined
			 in [CC54-DESC]
*/
#define HW_DESC_SET_CIPHER_CONFIG0(pDesc, cipherConfig)									\
	do {														\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD4, CIPHER_CONF0, (pDesc)->word[4], (cipherConfig));	\
	} while (0)

#define HW_DESC_SET_CIPHER_CONFIG1(pDesc, cipherConfig)									\
	do {														\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD4, CIPHER_CONF1, (pDesc)->word[4], (cipherConfig));	\
	} while (0)

#define HW_DESC_SET_CIPHER_CONFIG3(pDesc, cipherConfig)									\
	do {														\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD4, CIPHER_CONF2, (pDesc)->word[4], (cipherConfig));	\
	} while (0)

#define HW_DESC_SET_WORD_SWAP(pDesc, swapConfig)									\
	do {														\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD4, WORD_SWAP, (pDesc)->word[4], (swapConfig));	\
	} while (0)

#define HW_DESC_SET_BYTES_SWAP(pDesc, swapConfig)									\
	do {														\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD4, BYTES_SWAP, (pDesc)->word[4], (swapConfig));	\
	} while (0)
/*
 @brief: This function sets the CMAC_SIZE0 mode.
 
 @params:
 	pDesc [in] -A pointer to a HW descriptor, 5 words long according to
 	           [CC54-DESC]. The descriptor buffer must be word aligned
*/
#define HW_DESC_SET_CMAC_SIZE0_MODE(pDesc)										\
	do {														\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD4, CMAC_SIZE0, (pDesc)->word[4], 0x1);			\
	} while (0)

/*
 @brief: This function sets the key size for AES engine.
 
 @params:
 	pDesc [in] - A pointer to a HW descriptor, 5 words long according to
 	           [CC54-DESC]. The descriptor buffer must be word aligned

	keySize [in] - The key size in bytes (NOT size code)
*/
#define HW_DESC_SET_KEY_SIZE_AES(pDesc, keySize)									\
	do {													        \
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD4, KEY_SIZE, (pDesc)->word[4], ((keySize) >> 3) - 2);	\
	} while (0)


/*
 @brief: This function sets the key size for DES engine.
 
 @params:
 	pDesc [in] - A pointer to a HW descriptor, 5 words long according to
 	           [CC54-DESC]. The descriptor buffer must be word aligned

	keySize [in] - The key size in bytes (NOT size code)
*/
#define HW_DESC_SET_KEY_SIZE_DES(pDesc, keySize)									\
	do {													        \
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD4, KEY_SIZE, (pDesc)->word[4], ((keySize) >> 3) - 1);	\
	} while (0)


/*
 @brief: This function sets the key size for DES engine.
 
 @params:
 	pDesc [in] - A pointer to a HW descriptor, 5 words long according to
 	           [CC54-DESC]. The descriptor buffer must be word aligned

	keySizeHwMode [in] - The key size hw code
*/
#define HW_DESC_SET_KEY_SIZE_HW_MODE(pDesc, keySizeHwMode)									\
	do {													        \
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD4, KEY_SIZE, (pDesc)->word[4], keySizeHwMode);	\
	} while (0)


/*
 @brief: This function sets the descriptor's setup mode
 
 @params:
 	pDesc [in] -A pointer to a HW descriptor, 5 words long according to
 	           [CC54-DESC]. The descriptor buffer must be word aligned

	setupMode [in] -Any one of the setup modes defined in [CC54-DESC]
*/
#define HW_DESC_SET_SETUP_MODE(pDesc, setupMode)									\
	do {														\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD4, SETUP_OPERATION, (pDesc)->word[4], (setupMode));	\
	} while (0)

/*
 @brief: This function sets the descriptor's cipher do
 
 @params:
 	pDesc [in] -A pointer to a HW descriptor, 5 words long according to
 	           [CC54-DESC]. The descriptor buffer must be word aligned

	cipherDo [in] -Any one of the cipher do defined in [CC54-DESC]
*/
#define HW_DESC_SET_CIPHER_DO(pDesc, cipherDo)									\
	do {													\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD4, CIPHER_DO, (pDesc)->word[4], (cipherDo));	\
	} while (0)

/* it is forbidden to use the lock Q bit since we cannot disable HW context switches while* 
*  the SW context switches are enabled. There is no advantage to lock both HW/SW context switch. */
#if 0
/*
 @brief: This function sets the lock queue mode for a descriptor.
 
 @params:
 	pDesc [in] -A pointer to a HW descriptor, 5 words long according to
 	           [CC54-DESC]. The descriptor buffer must be word aligned

	lockQueue [in] - 1 - lock a queue, 0 - unlock it
*/
#define HW_DESC_LOCK_QUEUE(pDesc, lockQueue)									\
	do {													\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD1, LOCK_QUEUE, (pDesc)->word[1], (lockQueue));	\
	} while (0)
#endif

/*
 @brief: This function resets the hw after const input mode.
 It must be called before any attempt to create a descriptor that reads from SRAM.
 
 @params:
 	pDesc [in] -A pointer to a HW descriptor, 5 words long according to
 	           [CC54-DESC]. The descriptor buffer must be word aligned
*/
#define HW_DESC_RESET_CONST_INPUT(pDesc)									\
	do {													\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD1, DIN_DMA_MODE, (pDesc)->word[1], DMA_SRAM);	\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD1, DIN_SIZE, (pDesc)->word[1], (4));		\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD3, DOUT_DMA_MODE, (pDesc)->word[3], DMA_SRAM);	\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE0_WORD3, DOUT_SIZE, (pDesc)->word[3], (4));		\
        HW_DESC_SET_FLOW_MODE(pDesc, BYPASS);               \
	} while (0)

/*
 @brief: This function sets the AES xor crypto key bit. If this bit is set then
	the aes HW key is xored with the already loaded key.
 
 @params:
 	pDesc [in] -A pointer to a HW descriptor, 5 words long according to
 	           [CC54-DESC]. The descriptor buffer must be word aligned
*/
#define HW_DESC_SET_AES_XOR_CRYPTO_KEY(pDesc)								\
	do {												\
		DX_CC_REG_FLD_SET(CRY_KERNEL, AES_CONTROL, AES_XOR_CRYPTOKEY, (pDesc)->word[4], 1);	\
	} while (0)



/*
 @brief: This function sets the lock queue mode for a descriptor.
 
 @params:
 	pDesc [in] -A pointer to a HW descriptor, 5 words long according to
 	           [CC54-DESC]. The descriptor buffer must be word aligned

	lockQueue [in] - 1 - lock a queue, 0 - unlock it
*/
#define HW_DESC_STOP_QUEUE(pDesc)									\
	do {													\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_QUEUE1_WORD1, LOCK_QUEUE, (pDesc)->word[1], 1);	\
	} while (0)

/*!
 * This function sets the DIN field of a HW descriptors to star/stop monitor descriptor. 
 * Used for performance measurements and debug purposes.
 * 
 * \param pDesc pointer HW descriptor struct
 */
#define _HW_DESC_MONITOR_KICK 0x7FFFC00
#define HW_DESC_SET_DIN_MONITOR_CNTR(pDesc)										\
	do {		                                                                                        	\
		DX_CC_REG_FLD_SET(CRY_KERNEL, DSCRPTR_MEASURE_CNTR, VALUE, (pDesc)->word[1], _HW_DESC_MONITOR_KICK);	\
	} while (0)



#endif /*__HW_QUEUE_DEFS_H__*/
