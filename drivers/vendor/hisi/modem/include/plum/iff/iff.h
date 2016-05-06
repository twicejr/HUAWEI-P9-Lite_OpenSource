/**

                   Huawei Technologies Sweden AB (C), 2001-2011,

 ******************************************************************************
 * @file
 *
 * @author  F73150
 * @version
 * @date    2014/04/04 11:31(+0200)
 * @copyright Huawei Technologies Sweden AB
******************************************************************************/

/*****************************************************************************
  1 Other files included
*****************************************************************************/
#ifndef INCLUSION_GUARD_IFF_H
#define INCLUSION_GUARD_IFF_H

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/*****************************************************************************
  2 Macro definitions
*****************************************************************************/
/**
 * Macro for generate a FourCC sequence. Used to identify the Chunks in a IFF
 * DUMP.

   Example use, internal in IFF:
   @code

   iff_id(dump, CHUNK_TAG('F','O','R','M'));
   @endcode
 */
#define CHUNK_TAG(a,b,c,d)                                              \
    ((0xff &  a) | (0xff & b) << 8 | (0xff & c) << 16 | (0xff & d) << 24)

/*****************************************************************************
  3 Enumeration declaration
*****************************************************************************/

/*****************************************************************************
  4 Message Header declaration
*****************************************************************************/

/*****************************************************************************
  5 Message declarations
*****************************************************************************/

/*****************************************************************************
  6 STRUCT declarations
*****************************************************************************/
typedef struct iff *IFF;
typedef int FORM_TYPE;
typedef int CHUNK_ID;

/*****************************************************************************
  7 UNION declarations
*****************************************************************************/

/*****************************************************************************
  8 OTHER declarations
*****************************************************************************/

/*****************************************************************************
  9 Global variables
*****************************************************************************/

/*****************************************************************************
  10 Function declarations
*****************************************************************************/
/**
 * Create an dumpfile
  @param[in]  name name of dump.
  @param[in]  type A FourCC, a sequence of four bytes used to uniquely identify
                   data formats in the dump.
  @return     handle to dump.
*/
IFF IFF_Open(char *name, FORM_TYPE type);

/**
 * Add a Chunk to a dump.
  @param[in]  iff Handle returnd from IFF_Open()
  @param[in]  id a four letter identifier created with CHUNK_TAG()
  @param[in]  size Size of the data field.
  @param[in]  data pointer to the data that shall be put in the
                   dump.
*/
void IFF_AddChunk(IFF iff, CHUNK_ID id, size_t size, void *data);

/**
 * Close the dump.
  @param[in]  iff Handle returnd from IFF_Open()
  @return     handle to dump file
*/
void IFF_Close(IFF iff);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* INCLUSION_GUARD_IFF_H */
