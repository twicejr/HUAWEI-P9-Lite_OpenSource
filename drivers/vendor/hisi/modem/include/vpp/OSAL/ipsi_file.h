/**
Copyright(C) 2007, Huawei Tech. India Pvt. Ltd.
            ALL RIGHTS RESERVED
FileName   : ipsi_file.h
Version    : 1
Author     : Jayaraghavendran K
Created on : 2006-12-29
Description: This file contains all the file management related functions.
History:<author>   <date>          <desc>
*/

#ifndef __IPSI_FILE_H_
#define __IPSI_FILE_H_

#include "ipsi_types.h"
#include <stdarg.h>
#ifdef  __cplusplus
extern "C" {
#endif

#define IPSI_SEEK_SET 0
#define IPSI_SEEK_END 2


#define IPSI_OUTBUFF_NOT_ENOUGH 3

/**
    @typedef    'void *' is abstracted as ipsi_file_handle_t and it is used as
                the file handle in all the operations.
*/
typedef void* ipsi_file_handle_t;

typedef void * ipsi_utimebuff_t;

/* Pointer to drectory handle */
typedef void* ipsi_dir_handle_t;

/* Pointer to directory entries */
typedef void* ipsi_dir_entries_t;

//User permission
#define IPSI_USER_PERMISSION 4

//Group permission
#define IPSI_GROUP_PERMISSION 2

//Other permission
#define IPSI_OTHER_PERMISSION 1

/**
@brief The ipsi_fopen function opens the file whose name is the string
    pointed to by path and associates a stream with it. The argument
    mode points to a string beginning with one of the following sequences
    (Additional characters may follow these sequences) :

    r    Opens text file for reading. The stream is positioned at the
         beginning of the file.

    r+   Open for reading and writing. The stream is positioned at the
         beginning of the file.

    w    Truncate the file to zero length or create text file for writing.
         The stream is positioned at the beginning of the file.

    w+   Open for reading and writing. The file is created if it does not
         exist, otherwise it is truncated. The stream is positioned at the
         beginning of the file.

    a    Open for appending(writing at the end of file). The file is created
         if it does not exist. The stream is positioned at the end of the file.

    a+   Open for reading and appending(writing at the end of file). The file
         is created if it does not exist. The stream is positioned at the end
         of the file.

    After the call to ipsi_fclose, any further access to the stream
    results in undefined behavior.

    Passing NULL pointer for either path or mode argument results in undefined
    behaviour.

    @param[out]     *stream         The pointer to the opened file.
    @param[in]      *path           The path of the file to be opened.
    @param[in]      *mode           The access mode in which the file is 
                                    to be opened.
    @retval         IPSI_SUCCESS   On Successful Completion .
                    IPSI_FAILURE   On Failure.
*/
IPSILINKDLL int ipsi_fopen(ipsi_file_handle_t *stream,
                           const char *path,const char *mode);


/**
    @brief    The ipsi_fclose function disassociates the named stream from its
                underlying file or set of functions. If the stream was being 
                used for output, any buffered data is written first.

                After the call to ipsi_fclose, any further call to this function
                passing the same stream results in undefined behavior.

    @param[in]      stream          Stream which is to be closed.
    @retval         IPSI_SUCCESS   On Successful Completion
                    IPSI_FAILURE   On Failure
*/
IPSILINKDLL int ipsi_fclose(ipsi_file_handle_t stream);


/**
    @brief    The ipsi_fread function reads size elements of data, 
              each sizeof(char) bytes long, from the stream pointed to by 
              stream, storing them at the location given by buffer.

                    Passing invalid arguments to this function results in 
                    undefined behaviour.

    @param[out]     buffer  Buffer at which data is stored after reading.
    @param[in]      stream  Stream from which the data is read.
    @param[in]      size    Number of elements to be read.
    @retval         size_t  Number of elements read.
*/
IPSILINKDLL size_t ipsi_fread(void *buffer, size_t size,
                              ipsi_file_handle_t stream);

/**
    @brief          
The ipsi_fread function reads size elements of data, each unitSize
                long, from the stream pointed to by stream, storing them at
                the location given by buffer.

                Passing invalid arguments to this function results in 
                undefined behaviour.

    @param[out]     buffer  Buffer at which data is stored after reading.
    @param[in]      stream  Stream from which the data is read.
    @param[in]      size    Number of elements to be read.
    @retval         size_t  Number of elements read.
*/
IPSILINKDLL size_t ipsi_fread_ex(void *buffer,size_t unitSize,
                                 size_t size,ipsi_file_handle_t stream);

/**
    @brief     The ipsi_fwrite function writes size elements of data, 
               each sizeof(char) bytes long, to the stream pointed to by 
               stream, obtaining them from the location pointed to by buffer.

                Passing invalid arguments to this function results in 
                undefined behaviour.

    @param[out]     stream  Stream to which data is to be written.
    @param[in]      buffer  Buffer from which data is fetched.
    @param[in]      size    Number of elements to be written.
    @retval         size_t  Number of elements successfully written
*/
IPSILINKDLL size_t ipsi_fwrite(const void *buffer,
                               size_t size,ipsi_file_handle_t stream);

/**
    @brief      The ipsi_fflush function forces a write all of the user-space
                buffered data for the given output or update stream via the
                stream'sunderlying write function.

                The open status of the stream unaffected by call to this 
                function.
                If stream argument is NULL, it returns IPSI_FAILURE

    @param[in]      stream         Stream to be flushed.
    @retval         IPSI_SUCCESS  On Successful Completion.
                    IPSI_FAILURE  On Failure
*/
IPSILINKDLL int ipsi_fflush(ipsi_file_handle_t stream);


/**
    @brief          The ipsi_filelength function will count the number 
                    of byte stored in the file and returns it.
                    The open status of the stream unaffected by call 
                    to this function.
                    If stream argument is NULL, it returns IPSI_FAILURE

    @param
        [in]        path            Path of the file for which the length 
                                    is to be determined.

    @retval         On Successful Completion it returns the number of byte 
                    stored in that file.
                    On Failure it returns IPSI_FAILURE.
*/
IPSILINKDLL long ipsi_filelength(const char *path);

/**
    @brief          The ipsi_filelength64 function will count the number 
                    of byte stored in the file and returns it.
                    The open status of the stream unaffected by call 
                    to this function.
                    If stream argument is NULL, it returns IPSI_FAILURE

    @param
        [in]        path            Path of the file for which the length 
                                    is to be determined.

    @retval         On Successful Completion it returns the number of byte 
                    stored in that file.
                    On Failure it returns IPSI_FAILURE.
*/
IPSILINKDLL SEC_INT64 ipsi_filelength64(const char *path);

/**
    @brief          The file_sep_char function give the fileseparator character.

                    This function is used to get only the directory name or 
                    filename in the given path

    @param
        [in]        n/a

    @retval         It returns the the file separator character
                    
*/
IPSILINKDLL int file_sep_char(void);

/**
    @brief          The ipsi_filelength_ex function will count the number 
                    of byte stored in the file and returns it.
                    The open status of the stream unaffected by call 
                    to this function.
                    If stream argument is NULL, it returns IPSI_FAILURE

    @param
        [in]        path            Path of the file for which the length 
                                    is to be determined.

    @retval         On Successful Completion it returns the number of byte 
                    stored in that file.
                    On Failure it returns IPSI_FAILURE.
*/
IPSILINKDLL long ipsi_filelength_ex(const char *path,
                                    const ipsi_file_handle_t stream);



/**
    @brief          The ipsi_filelength64_ex function will count the number 
                    of byte stored in the file and returns it.
                    The open status of the stream unaffected by call 
                    to this function.
                    If stream argument is NULL, it returns IPSI_FAILURE

    @param
        [in]        path            Path of the file for which the length 
                                    is to be determined.

    @retval         On Successful Completion it returns the number of byte 
                    stored in that file.
                    On Failure it returns IPSI_FAILURE.
*/
IPSILINKDLL SEC_INT64 ipsi_filelength64_ex(const char *path,
                        const ipsi_file_handle_t stream);

/**
    @brief          The ipsi_vfprintf function 
                    takes a pointer to an argument list,
                    then formats and writes the given data to stream.
                    If stream argument is NULL, it returns IPSI_FAILURE

    @param
        [out]        stream        The io stream
        [in]         format        The format
        [in]         argptr        The argument list


    @retval         On Successful Completion it returns the number of byte 
                    stored in that file.
                    On Failure it returns negative value.
*/
IPSILINKDLL int ipsi_vfprintf(ipsi_file_handle_t stream, const char *format,
                              va_list argptr);

/**
    @brief          The ipsi_fseek function will move the file pointer to a
                    specified location.

    @param          stream      Pointer to FILE structure
                    lOffset     Number of bytes from origin
                    iOrigin     Initial position
        
    @retval         If successful, fseek returns 0. Otherwise, it returns 
                       a nonzero value. On devices incapable of seeking, the 
                       return value is undefined.


*/
IPSILINKDLL int ipsi_fseek(ipsi_file_handle_t stream,
                          long lOffset,
                          int iOrigin);

/**
    @brief          The ipsi_fseek64 function will move the file pointer to a
                    specified location.

    @param          stream      Pointer to FILE structure
                    lOffset     Number of bytes from origin
                    iOrigin     Initial position
        
    @retval         If successful, fseek returns 0. Otherwise, it returns 
                       a nonzero value. On devices incapable of seeking, the 
                       return value is undefined.


*/
IPSILINKDLL int ipsi_fseek64(ipsi_file_handle_t stream, 
                SEC_INT64 lOffset,
                int iOrigin);


/**
    @brief          The ipsi_fgets function 
                    reads a line of data from file                    

    @param
        [out]        stream        The io stream
        [in]         uiSize        Maximum number of chars to read
        [in]         cBuff         The output buffer


    @retval         On Successful Completion it returns success
                    On Failure it returns negative value.
*/
IPSILINKDLL int ipsi_fgets(char *cBuff,unsigned int uiSize,
    ipsi_file_handle_t stream);

/**
    @brief          The ipsi_fgetc function 
                    reads a character from file                    

    @param
        [in]        stream        The io stream

    @retval         On Successful Completion it returns the character that is 
                    read.
                    On Failure it returns negative failure.
*/
IPSILINKDLL int ipsi_fgetc(ipsi_file_handle_t stream);

/**
    @brief          The ipsi_ftell function is used to get the current position
                       of a file pointer.

    @param          stream      Target FILE structure
        
    @retval         ftell returns the current file position.
*/
IPSILINKDLL long ipsi_ftell(ipsi_file_handle_t stream);

/**
    @brief          The ipsi_ftell64 function is used to get the current 
                       position of a file pointer.

    @param          stream      Target FILE structure
        
    @retval         ftell returns the current file position.
*/
IPSILINKDLL SEC_INT64 ipsi_ftell64(ipsi_file_handle_t stream);

/**
    @brief          The ipsi_feof function is used to 
                    Tests for end-of-file on a stream.

    @param          stream  Pointer to FILE structure
        
    @retval         IPSI_FAILURE if current position is a non zero value.
                    IPSI_SUCCESS if current position is not EOF

*/

IPSILINKDLL int ipsi_feof(ipsi_file_handle_t stream);

/**
    @brief          ipsi_ungetc:This function is used to 
                    update a charater in the file stream

    @param          stream  Pointer to FILE structure
                    c - The charater
                    
    @retval         IPSI_FAILURE in failure condition
                    IPSI_SUCCESS in success condition

*/
IPSILINKDLL int ipsi_ungetc(int c,ipsi_file_handle_t stream);


/**
    @brief          ipsi_set_filesecurityinfo:This function is used to 
                    set the file ownership

    @param          pcPath  the filename
                    psidOwner The Owner Id
                    psidGroup The Group Id
        
    @retval         IPSI_FAILURE in failure condition
                    IPSI_SUCCESS in success condition

*/
IPSILINKDLL int ipsi_set_filesecurityinfo(char * pcPath,
  void * psidOwner,
  void * psidGroup);

/**
    @brief          ipsi_set_fileattributes:This function is used to 
                    set the file attributes

    @param          pcFileName  the filename
                    ulAttrib The file attribute to set
        
    @retval         IPSI_FAILURE in failure condition
                    IPSI_SUCCESS in success condition

*/
IPSILINKDLL int ipsi_set_fileattributes(char * pcFileName,
                      unsigned long ulAttrib);

/**
    @brief          ipsi_set_filetime:This function is used to 
                    set the file time

    @param          pcFileName  the filename
                    pstUtimeBuffer The file time buffer used to set
        
    @retval         IPSI_FAILURE in failure condition
                    IPSI_SUCCESS in success condition

*/
IPSILINKDLL int ipsi_set_filetime(char * pcFileName,
                      const ipsi_utimebuff_t pstUTimeBuff);

/**
    @brief          ipsi_createdirectory:This function is used to 
                    Create the directory

    @param          pcDirName  The directory to create
                    uiMode   The permission mode
                    uiMask  The mask value
        
    @retval         IPSI_FAILURE in failure condition
                    IPSI_SUCCESS in success condition

*/
IPSILINKDLL int ipsi_createdirectory(char * pcDirName,unsigned int uiMode,
                                     unsigned int uiMask);

/**
    @brief          ipsi_removedirectory:This function is used to 
                    Remove the directory

    @param          pcDirName  The directory to remove
        
    @retval         IPSI_FAILURE in failure condition
                    IPSI_SUCCESS in success condition

*/
IPSILINKDLL int ipsi_removedirectory(char * pcDirName);

/**
    @brief          ipsi_chmod:This function is used to 
                    Change the permissions of a file

    @param          pcFileName  The filename
                    iMode The mode to set
        
    @retval         IPSI_FAILURE in failure condition
                    IPSI_SUCCESS in success condition

*/
IPSILINKDLL int ipsi_chmod(char * pcFileName,int iMode);

/**
    @brief          ipsi_deletefile:This function is used to 
                    delete the file

    @param          pcFileName  The filename                    
        
    @retval         IPSI_FAILURE in failure condition
                    IPSI_SUCCESS in success condition

*/
IPSILINKDLL int ipsi_deletefile(char * pcFileName);

/**
    @brief          ipsi_open_initial_dir : Opens the directory mentioned in the
                                   buffer and updates the handle.

    @param          pucBuffer     Input Buffer
                    dpDirHandle   Output directory handle
                    dpDirEntries  Output pointing to directory entries.
                    dpucOutBuff   Output buffer pointing to first entry.

    @retval         This function returns success if it gets the handle
                    and the first directory entry else returns failure.
*/

IPSILINKDLL int ipsi_open_initial_dir(const char * pucBuffer, 
                ipsi_dir_handle_t * dpDirHandle,
                ipsi_dir_entries_t * dpDirEntries,
                char ** dpucOutBuff);


/**
    @brief          ipsi_opendir : Opens the directory contents mentioned in the
                                   buffer and updates the handle.

    @param          pucBuffer     Input Buffer
                    dpDirHandle   Output directory handle
                    dpDirEntries  Output pointing to directory entries.
                    dpucOutBuff   Output buffer pointing to first entry.

    @retval         This function returns success if it gets the handle
                    and the first directory entry else returns failure.
*/

IPSILINKDLL int ipsi_opendir(char * pucBuffer, 
                ipsi_dir_handle_t * dpDirHandle,
                ipsi_dir_entries_t * dpDirEntries,
                char ** dpucOutBuff);

/**
    @brief          ipsi_readdir : Reads the directory entries.

    @param          dirHandle     Input directory handle
                    dirEntries    Input pointing to directory entries.
                    dpucOutBuff   Output buffer pointing to next entry.

    @retval         This function returns success if it is able to read
                    the next entry else returns failure.
*/

IPSILINKDLL int ipsi_readdir(const ipsi_dir_handle_t dirHandle,
                ipsi_dir_entries_t * dirEntries,
                char ** dpucOutBuff,
                unsigned int * pResult);

/**
    @brief          ipsi_closedir : Closes the directory handle.

    @param          dirHandle     Input directory handle
                    dirEntries    Input pointing to directory entries.

    @retval         NA
*/

IPSILINKDLL int ipsi_closedir(ipsi_dir_handle_t dirHandle); 

/**
    @brief          ipsi_get_dir_entry:This function is used to 
                    get the finddata structure

    @param          dirEntries  Pointer of the finddata structure pointer
        
    @retval         IPSI_FAILURE in failure condition
                    IPSI_SUCCESS in success condition

*/
IPSILINKDLL int ipsi_get_dir_entry(ipsi_dir_entries_t * dirEntries);

/**
    @brief          ipsi_free_dir_entry:This function is used to 
                    free the finddata structure

    @param          dirEntries  Pointer of the finddata structure pointer
        
    @retval         N/A

*/
IPSILINKDLL void ipsi_free_dir_entry(ipsi_dir_entries_t * dirEntries);

/**
    @brief          ipsi_fullpath:This function is used to calculate the
                    fullpath

    @param          pcBuf The output buffer
                    pcPathBuf The path buffer
                    uiMaxLen  The maximum length that of the output buffer
                    piError The error occurred
        
    @retval         IPSI_FAILURE in failure condition
                    IPSI_SUCCESS in success condition

*/
IPSILINKDLL char * ipsi_fullpath(char * pcBuf,
                                 const char * pcPathBuf,
                                 unsigned int uiMaxLen,
                                 int *piError);

/**
    @brief          ipsi_set_full_permission:This function is used to 
                    set the full file permission

    @param          pcFileName The file name                    
        
    @retval         N/A

*/
IPSILINKDLL int ipsi_set_permission(char * pcFileName,unsigned int uiMode,
                             unsigned int uiMask);


/**
    @brief          ipsi_list_directory:This function is used to 
                    list the contents of the directory in the 
                    output buffer

    @param          pcFullPath The full path
                    pcOutBuff The LS buffer
                    uiBuffSize  Ths size of the output buffer
        
    @retval         N/A

*/
IPSILINKDLL int ipsi_list_directory(char * pcFullPath,char * pcOutBuff,
                             unsigned int uiBuffSize);

#ifdef  __cplusplus
}
#endif
#endif

