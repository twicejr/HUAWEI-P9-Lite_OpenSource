
//lint -e123

#include "ipsi_ssl_build_conf.h"

#ifndef IPSI_SSL_NO_DTLS
#ifndef HEADER_IPSI_AIO_H 
#define HEADER_IPSI_AIO_H 

#ifdef  __cplusplus
extern "C" {
#endif

#include "ipsi_types.h"
#include "sec_sys.h"


//aio error
#define IPSI_AIO_ERROR 0

//aio success
#define IPSI_AIO_SUCCESS 1

//aio error in read and write function
#define IPSI_AIO_ERR (-2)


//Datagram type
#define AIO_TYPE_DGRAM		(21 | 0x0400 | 0x0100)


/* These are used in the following macros and are passed to
 * AIO_ctrl() */
 
/* AIO_s_file special */
#define AIO_CTRL_SET_FILENAME 30 

//set recv timeout
#define AIO_CTRL_DGRAM_SET_RECV_TIMEOUT 33 

#define AIO_CTRL_DGRAM_GET_RECV_TIMEOUT 46 /* getsockopt, essentially */

#define AIO_CTRL_DGRAM_QUERY_MTU          40 /* as kernel for current MTU */

//get MTU
#define AIO_CTRL_DGRAM_GET_MTU            41 /* get cached value for MTU */

//set MTU
#define AIO_CTRL_DGRAM_SET_MTU            42 /* set cached value for

* MTU. want to use this
* if asking the kernel
* fails */

/* check whether the MTU
* was exceed in the
* previous write
* operation */

#define AIO_CTRL_DGRAM_MTU_EXCEEDED       43 

//set peer address
#define AIO_CTRL_DGRAM_SET_PEER 44 /* Destination for the data */

//get peer address
#define AIO_CTRL_DGRAM_GET_PEER 49

#define AIO_CTRL_DGRAM_GET_NEXT_TIMEOUT 50

#define AIO_CTRL_DGRAM_GET_TIMEOUT_DUR 51

//set socket/file descriptor 
#define AIO_C_SET_FD 104

//set socket/file descriptor
#define AIO_C_GET_FD 105


/* Note : While adding new macro values for AIO CTRL ssl_locl.h also needs to be referenced as it has some internal 
macros. 34 and 45 are already used inside. */

typedef struct stIpsiAio IPSI_AIO_S;

/**
* @defgroup AIOFunctions
* This section contains all the AIO Functions.
*/

/**
* @defgroup IPSI_AIO_METH_CRDESTFUNC
* @ingroup dtls1Structures
* @par Prototype
* @code
* typedef struct stIpsiAioMethCrDestFun
* {  
*    // Initialize the IO structure
*     SEC_INT (*create)(IPSI_AIO_S *);
* 
*     // Free IO structure
*    SEC_INT (*destroy)(IPSI_AIO_S *); 
* }
* IPSI_AIO_METH_CRDESTFUNC;
* @endcode
* 
* @par Description
* It is a internal structure used by DTLS. 
* Application should not use it normally.
*
* @datastruct create Function pointer to intialize the IO structure
* @datastruct destroy Function pointer to free the IO structure.

*/
typedef struct stIpsiAioMethCrDestFun
{  
    // Initialize the IO structure
    SEC_INT (*create)(IPSI_AIO_S *);

    // Free IO structure
    SEC_INT (*destroy)(IPSI_AIO_S *); 
}IPSI_AIO_METH_CRDESTFUNC;


/**
* @defgroup IPSI_AIO_METH_RDWRFUNC
* @ingroup dtls1Structures
* @par Prototype
* @code
* typedef struct stIpsiAioMethRdWrFun
* {  
*     //write the IO structure
*     SEC_INT (*write)(const IPSI_AIO_S *, const SEC_CHAR *, SEC_UINT);
* 
*    //Read the IO structure
*     SEC_INT (*read)(IPSI_AIO_S *, SEC_CHAR *, SEC_UINT);
* }
* IPSI_AIO_METH_RDWRFUNC;
* @endcode
*
* @par Description
* It is a internal structure used by DTLS. 
* Application should not use it normally.
*
* @datastruct write Function pointer to write operations.
* @datastruct read Function pointer to read operations.
*/
typedef struct stIpsiAioMethRdWrFun
{  
    //write the IO structure
    SEC_INT (*write)(const IPSI_AIO_S *, const SEC_CHAR *, SEC_UINT);

    //Read the IO structure
    SEC_INT (*read)(IPSI_AIO_S *, SEC_CHAR *, SEC_UINT);
}IPSI_AIO_METH_RDWRFUNC;


/**
* @defgroup IPSI_AIO_METH_GETSETERRFUNC
* @ingroup dtls1Structures
* @par Prototype
* @code
* typedef struct stIpsiAioMethGetSetErrFun
*{  
*     //get the AIO error
*     SEC_INT (*getAioError)();
* 
*    //set the AIO error
*     SEC_INT (*setAioError)(SEC_UINT);
* }
* IPSI_AIO_METH_GETSETERRFUNC;
* @endcode
*
* @par Description
* It is a internal structure used by DTLS. 
* Application should not use it normally.
*
* @datastruct getAioError Function pointer to get the aio error.
* @datastruct setAioError Function pointer to set the aio error.
*/
typedef struct stIpsiAioMethGetSetErrFun
{  
    //get the AIO error
    SEC_INT (*getAioError)(const IPSI_AIO_S *);

    //set the AIO error
    SEC_VOID (*setAioError)(const IPSI_AIO_S *, SEC_INT);
}IPSI_AIO_METH_GETSETERRFUNC;


/**
* @defgroup IPSI_AIO_MRTHOD_FUNCTION
* @ingroup dtls1Structures
* @par Prototype
* @code
* typedef struct stIpsiAioMetFun
*{  
* 
*     //structure containing read write callback function
*     IPSI_AIO_METH_RDWRFUNC rdwrFunc;
*
*     //structure containing create destroy callback function
*     IPSI_AIO_METH_CRDESTFUNC crdestFunc;
* 
*     //structure containing get and set error callback function
*     IPSI_AIO_METH_GETSETERRFUNC getsetErrFunc;
*     
*    //control the IO structure
*     SEC_INT (*ctrl)(IPSI_AIO_S *, SEC_INT, SEC_INT, void *);
* 
* 
*}IPSI_AIO_METHOD_FUNCTION;
* 
* @endcode
* @par Description
* It is a internal structure used by DTLS. 
* Application should not use it normally.
*
* @datastruct write Function pointer to write operations.
* @datastruct read Function pointer to read operations.
* @datastruct ctrl Function pointer to control operations.
* @datastruct create Function pointer to intialize the IO structure
* @datastruct destroy Function pointer to free the IO structure.

*/
typedef struct stIpsiAioMetFun
{  

    //structure containing read write callback function
    IPSI_AIO_METH_RDWRFUNC rdwrFunc;

    //structure containing create destroy callback function
    IPSI_AIO_METH_CRDESTFUNC crdestFunc;

    //structure containing get and set error callback function
    IPSI_AIO_METH_GETSETERRFUNC getsetErrFunc;
    
    //control the IO structure
    SEC_INT (*ctrl)(IPSI_AIO_S *, SEC_INT, SEC_INT, void *);


}IPSI_AIO_METHOD_FUNCTION;

/**
* @defgroup IPSI_AIO_METHOD_S
* @ingroup dtls1Structures
* @par Prototype
* @code
* typedef struct stIpsiAioMethod
* {
*   int type;
*    struct stIpsiAioMetFun aioMethodFunction;
} IPSI_AIO_METHOD_S;
* @endcode
*
* @par Description
* It is a internal structure used by DTLS. 
* Application should not use it normally.
*
* @datastruct type Indicates type of IO.
* @datastruct aioMethodFunction dtls method function
*/
typedef struct stIpsiAioMethod
{
    // Indicates what type of IO.
    SEC_INT type; 

    //aio method function
    struct stIpsiAioMetFun aioMethodFunction;
} IPSI_AIO_METHOD_S;

/**
* @defgroup IPSI_AIO_CB
* @ingroup dtls1Structures
* @par Prototype
* @code
* typedef struct stIpsiAioCB
* {
*    SEC_INT (*cb_write)(IPSI_AIO_S *, const SEC_CHAR *, SEC_UINT,SEC_VOID *);
*    SEC_INT (*cb_read)(IPSI_AIO_S *, SEC_CHAR *, SEC_UINT,SEC_VOID *);
*    SEC_VOID *pAppRdData;
*    SEC_VOID *pAppWrData;
* }IPSI_AIO_CB;
* @endcode
*
* @par Description
* It is a internal structure used by DTLS.
* Application should not use it normally.
*
* @datastruct cb_write callback for write
* @datastruct cb_read callback for read
* @datastruct pAppRdData Application data for read
* @datastruct pAppWrData Application data for write

*/

typedef struct stIpsiAioCB
{
    //Write callback
    SEC_INT (*cb_write)(IPSI_AIO_S *, const SEC_CHAR *, SEC_UINT,SEC_VOID *);

    //Read callback
    SEC_INT (*cb_read)(IPSI_AIO_S *, SEC_CHAR *, SEC_UINT,SEC_VOID *);

    //Application data for read
    SEC_VOID *pAppRdData;

    //Application data for read
    SEC_VOID *pAppWrData;
}IPSI_AIO_CB;

/**
* @defgroup stIpsiAio
* @ingroup dtls1Structures
* @par Prototype
* @code
* struct stIpsiAio
* {
*   IPSI_AIO_METHOD_S *method;
*   int init;
*   int shutdown;
*   void *ptr;
*    int (*cb_write)(IPSI_AIO_S *, const char *, int,void *);
*    int (*cb_read)(IPSI_AIO_S *, char *, int,void *);
*    void *pAppRdData;
*    void *pAppWrData;
* };
* @endcode
*
* @par Description
* It is a internal structure used by DTLS.
* Application should not use it normally.
*
* @datastruct method Pointer to AIO method.
* @datastruct init Indicates socket is initialized or not.
* @datastruct shutdown Indicates to close the socket.
* @datastruct ptr Holds the datagram information 
*Eg:IPSI_AIO_DGRAM_DATA_S structure

*/

//Abstract input output
struct stIpsiAio
{
    //Aio method
    IPSI_AIO_METHOD_S *method;

    // shows whether socket is initialized or not.
    SEC_INT init; 

    // indicates to close the socket.
    SEC_INT shutdown; 

    // Holds the datagram information Eg: IPSI_AIO_DGRAM_DATA_S structure
    SEC_VOID *ptr; 

    //callback for read/write
    struct stIpsiAioCB aioCallBack;
};


/*
    Func Name:   ipsi_aio_set_read_callback
*/

/**
* @defgroup ipsi_aio_set_read_callback
* @ingroup AIOFunctions
* @par Prototype
* @code
* SEC_INT ipsi_aio_set_read_callback(IPSI_AIO_S *pstAio,
* SEC_INT (*cb_read)(IPSI_AIO_S *, SEC_CHAR *,
* SEC_UINT, SEC_VOID *), SEC_VOID *)

* @endcode
* 
* @par Purpose
* This is used to set read callback 
* 
* @par Description
* ipsi_aio_set_read_callback function set read callback
* 
* @param[in] a Pointer to AIO . [N/A]
* @param[in] read Pointer to function which takes four arguments, pointer to AIO
,pointer to char,int,void pointer. [N/A]
* @param[in] pAppData Pointer to Void . [N/A]
* 
* @retval success if read call back set [N/A]
* @retval error if it fails
* 
* @par Required Header File
* ipsi_aio.h
*
* @par Note
* If the read callback returns a value which is more than the length of the buffer passed by us, then our lib API 
* which invokes this callback like SSL_accept, SSL_connect, SSL_read etc will return SEC_ERROR. SSL_getError will 
* return SSL_ERROR_SSL and SSL_getLastError will return SSL_R_IPSI_UNEXPECTED_SOCKET_BEHAVIOUR. 
* Since, this case does not exactly match with any of the defined system call errors, it has been categorized under 
* SSL Error though it pertains to invalid behavior of callback or system calls.\n
*
* @par Related Topics
* ipsi_aio_read,\n
* ipsi_aio_write,\n
*/
SSLLINKDLL SEC_INT ipsi_aio_set_read_callback(IPSI_AIO_S *pstAio,
SEC_INT (*cb_read)(IPSI_AIO_S *, SEC_CHAR *, SEC_UINT, SEC_VOID *),
SEC_VOID *pAppData);

/*
    Func Name:   ipsi_aio_set_write_callback
*/

/**
* @defgroup ipsi_aio_set_write_callback
* @ingroup AIOFunctions
* @par Prototype
* @code
* SEC_INT ipsi_aio_set_write_callback(IPSI_AIO_S *a,
* SEC_INT (*cb_write)(IPSI_AIO_S *, const SEC_CHAR *, SEC_UINT, SEC_VOID *),
* SEC_VOID *);

* @endcode
* 
* @par Purpose
* This is used to set write callback 
* 
* @par Description
* ipsi_aio_set_write_callback function set write callback
* 
* @param[in] a Pointer to AIO . [N/A]
* @param[in] write Pointer to function which takes 
* four arguments, pointer to AIO
,pointer to char,int,void pointer. [N/A]
* @param[in] pAppData Pointer to Void . [N/A]
* 
* @retval success if write call back set [N/A]
* @retval error if it fails
* 
* @par Required Header File
* ipsi_aio.h
*
* @par Note
* If the write callback returns a value which is more than the length of the buffer passed by us, then our lib API 
* which invokes this callback like SSL_accept, SSL_connect, SSL_write etc will return SEC_ERROR. SSL_getError will 
* return SSL_ERROR_SSL and SSL_getLastError will return SSL_R_IPSI_UNEXPECTED_SOCKET_BEHAVIOUR. 
* Since, this case does not exactly match with any of the defined system call errors, it has been categorized under 
* SSL Error though it pertains to invalid behavior of callback or system calls.\n
*
* @par Related Topics
* ipsi_aio_read,\n
* ipsi_aio_write,\n
*/
SSLLINKDLL SEC_INT ipsi_aio_set_write_callback(IPSI_AIO_S *pstAio,
SEC_INT (*cb_write)(IPSI_AIO_S *, const SEC_CHAR *, SEC_UINT, SEC_VOID *),
SEC_VOID *pAppData);



/*
    Func Name:   ipsi_aio_new
*/

/**
* @defgroup ipsi_aio_new
* @ingroup AIOFunctions
* @par Prototype
* @code
* IPSI_AIO_S *ipsi_aio_new(IPSI_AIO_METHOD_S *method);
* @endcode
* 
* @par Purpose
* This is used to create AIO (Abstract IO).
* 
* @par Description
* ipsi_aio_new function creates new AIO (Abstract IO) structure 
* 
* @param[in] pstMethod Pointer to AIO method. [N/A]
* 
* @retval Pointer to AIO structure On Success [IPSI_AIO_S|N/A]
* @retval SEC_NULL If the input is invalid (NULL Pointer). [SEC_NULL|N/A]
* 
* @par Required Header File
* ipsi_aio.h
*
* @par Note
* \n
* @par Related Topics
* ipsi_aio_free,\n
* ipsi_aio_read,\n
* ipsi_aio_write,\n
* ipsi_aio_ctrl.
*/

SSLLINKDLL IPSI_AIO_S *ipsi_aio_new(IPSI_AIO_METHOD_S *pstMethod);

/*
    Func Name:   ipsi_aio_free
*/

/**
* @defgroup ipsi_aio_free
* @ingroup AIOFunctions
* @par Prototype
* @code
* int ipsi_aio_free(IPSI_AIO_S *a);
* @endcode
* 
* @par Purpose
* This is used to free AIO (Abstract IO) structure.
* 
* @par Description
* ipsi_aio_free function frees AIO (Abstract IO) structure 
* 
* @param[in] pstAio Pointer to AIO structure. [N/A]
* 
* @retval SEC_INT On Success [IPSI_AIO_SUCCESS|N/A]
* @retval SEC_INT on failure (NULL Pointer). [IPSI_AIO_ERROR|N/A]
* 
* @par Required Header File
* ipsi_aio.h
*
* @par Related Topics
* ipsi_aio_new,\n
* ipsi_aio_read,\n
* ipsi_aio_write,\n
* ipsi_aio_ctrl.
*/
SSLLINKDLL SEC_INT ipsi_aio_free(IPSI_AIO_S *pstAio);

/*
    Func Name:   ipsi_aio_read
*/

/**
* @defgroup ipsi_aio_read
* @ingroup AIOFunctions
* @par Prototype
* @code
* int ipsi_aio_read(IPSI_AIO_S *a, void *out, int outl);
* @endcode
* 
* @par Purpose
* This is used to read from AIO (Abstract IO) structure.
* 
* @par Description
* ipsi_aio_read function reads from AIO (Abstract IO) structure 
* 
* @param[in] pstAio Pointer to AIO structure. [N/A]
* @param[out] pOut Buffer containing the data read.
* @param[out] ioutl Buffer length.
* @retval SEC_INT The read operation was successful. The return value is
* number of bytes actually read[Greater than 0|N/A]
* @retval SEC_INT The read operation was not successful.[IPSI_AIO_ERR|N/A]
* 
* @par Required Header File
* ipsi_aio.h
*
* @par Related Topics
* ipsi_aio_new,\n
* ipsi_aio_free,\n
* ipsi_aio_write,\n
* ipsi_aio_ctrl.
*/
SSLLINKDLL SEC_INT ipsi_aio_read(IPSI_AIO_S *pstAio, SEC_VOID *pOut,
SEC_UINT ioutl);

/*
    Func Name:   ipsi_aio_write
*/

/**
* @defgroup ipsi_aio_write
* @ingroup AIOFunctions
* @par Prototype
* @code
* SEC_INT ipsi_aio_write(IPSI_AIO_S *a, const SEC_VOID *in,
* SEC_UINT inl);
* @endcode
* 
* @par Purpose
* This is used to write to AIO (Abstract IO) structure.
* 
* @par Description
* ipsi_aio_write function writes to AIO (Abstract IO) structure 
* 
* @param[in] pstAio Pointer to AIO structure. [N/A]
* @param[in] in Buffer to which data to be written.
* @param[in] inl Buffer length.
* @retval SEC_INT The write operation was successful. The return value is
* number of bytes actually written[Greater than 0|N/A]
* @retval SEC_INT The write operation was not successful.[IPSI_AIO_ERR|N/A]
* 
* @par Required Header File
* ipsi_aio.h
*
* @par Related Topics
* ipsi_aio_new,\n
* ipsi_aio_free,\n
* ipsi_aio_read,\n
* ipsi_aio_ctrl.
*/
SSLLINKDLL SEC_INT ipsi_aio_write(IPSI_AIO_S *pstAio, const SEC_VOID *in,
SEC_UINT inl);


/*
    Func Name:   ipsi_aio_int_ctrl
*/

/**
* @defgroup ipsi_aio_int_ctrl
* @ingroup AIOFunctions
* @par Prototype
* @code
* SEC_INT ipsi_aio_int_ctrl(IPSI_AIO_S *pstAio, SEC_INT cmd,
* SEC_INT larg, SEC_INT iarg);
* @endcode
* 
* @par Purpose
* This is used to do control operations on AIO (Abstract IO) structure.
* 
* @par Description
* ipsi_aio_int_ctrl function used to do control operations 
* on AIO (Abstract IO) structure 
* 
* @param[in] pstAio Pointer to AIO structure. [N/A]
* @param[in] cmd Command / macro to set or get control operations.
* @param[in] larg value to be set.
* @param[out] iarg Output buffer which holds required output.
* @retval SEC_INT On Success [N/A]
* @retval SEC_INT on failure [IPSI_AIO_ERR|N/A]
* 
* @par Required Header File
* ipsi_aio.h
*
* @par Related Topics
* ipsi_aio_new,\n
* ipsi_aio_free,\n
* ipsi_aio_read,\n
* ipsi_aio_write.
*/
SSLLINKDLL SEC_INT ipsi_aio_int_ctrl(IPSI_AIO_S *pstAio, SEC_INT cmd,
SEC_INT larg, SEC_INT iarg);

/*
    Func Name:   ipsi_aio_ctrl
*/

/**
* @defgroup ipsi_aio_ctrl
* @ingroup AIOFunctions
* @par Prototype
* @code
* SEC_INT ipsi_aio_ctrl(IPSI_AIO_S *pstAio, SEC_INT cmd,
* SEC_INT larg, SEC_VOID *parg);

* @endcode
* 
* @par Purpose
* This is used to do control operations on AIO (Abstract IO) structure.
* 
* @par Description
* ipsi_aio_ctrl function used to do control operations 
* on AIO (Abstract IO) structure 
* 
* @param[in] pstAio Pointer to AIO structure. [N/A]
* @param[in] cmd Command / macro to set or get control operations.
* @param[in] larg value to be set.
* @param[out] parg Output buffer which holds required output.
* @retval SEC_INT On Success [N/A]
* @retval SEC_INT on failure [IPSI_AIO_ERR|N/A]
* 
* @par Required Header File
* ipsi_aio.h
*
* @par Related Topics
* ipsi_aio_new,\n
* ipsi_aio_free,\n
* ipsi_aio_read,\n
* ipsi_aio_write.
* @Notes:
*1) if cmd is used as AIO_CTRL_DGRAM_SET_MTU ,
* minimum mtu value needs to be set is 228
* 2) if the MTU value set by cmd AIO_CTRL_DGRAM_SET_MTU
* should not be overridden than SSL_OP_NO_QUERY_MTU must 
* be set using SSL_SET_OPTIONS.
* 3) The Max Application Data for DTLS connection that can be sent is 
* mtu - IPSI_DTLS1_MAX_RECORD_OVERHEAD(65)
* i.e SSL_write Fails if application data  is more than 
* (mtu - IPSI_DTLS1_MAX_RECORD_OVERHEAD(65)). In this case
* SSL_getLastError will return error SSL_R_APP_DATA_GT_MTU.
* 4) The Socket timeout set using  AIO_CTRL_DGRAM_SET_RECV_TIMEOUT
* is maximum timeout on the socket while using method ipsi_aio_s_datagram().
* This is applicable both during application data transfer and Handshake.
* However during handshake, the Socket timeout is varied based on the 
* retransmission timers less than or equal to max set value. In such cases
* Application might need to call SSL_accept or SSL_connect again for 
* packet retranmission and hence connection establishment.
* 
*/
SSLLINKDLL SEC_INT ipsi_aio_ctrl(IPSI_AIO_S *pstAio, SEC_INT cmd,
SEC_INT larg, SEC_VOID *parg);

/*
    Func Name:   ipsi_aio_s_datagram
*/

/**
* @defgroup ipsi_aio_s_datagram
* @ingroup AIOFunctions
* @par Prototype
* @code
* IPSI_AIO_METHOD_S *ipsi_aio_s_datagram(SEC_VOID);
* @endcode
* 
* @par Purpose
* This is used to create AIO method for datagram.
* 
* @par Description
* ipsi_aio_ctrl function used to create datagram AIO method which
* can be used for creating AIO structure.
* 
* @par Parameters
* N/A
* @retval IPSI_AIO_METHOD_S On Success [IPSI_AIO_METHOD_S|N/A]
* 
* @par Required Header File
* ipsi_aio.h
*
* @par Related Topics
* ipsi_aio_new,\n
* ipsi_aio_free,\n
* ipsi_aio_read,\n
* ipsi_aio_write,\n
* ipsi_aio_ctrl.
*/
SSLLINKDLL IPSI_AIO_METHOD_S *ipsi_aio_s_datagram(SEC_VOID);


/*
    Func Name:   IPSI_AIO_setErrno
*/

/**
* @defgroup IPSI_AIO_setErrno
* @ingroup AIOFunctions
* @par Prototype
* @code
* SEC_INT IPSI_AIO_setErrno(const IPSI_AIO_S *aio, SEC_INT errno);
* @endcode
* 
* @par Purpose
* This is used to set errno in AIO structure.
* 
* @par Description
* IPSI_AIO_setErrno function used to set errno to AIO structure
* 
* @par Parameters
* N/A
* @retval TLS_SUCCESS On Success [TLS_SUCCESS|N/A]
* @retval SEC_ERROR on failure [SEC_ERROR|N/A]
* 
* @par Required Header File
* ipsi_aio.h
*
* @par Related Topics
* ipsi_aio_new,\n
* ipsi_aio_free,\n
* ipsi_aio_read,\n
* ipsi_aio_write,\n
* ipsi_aio_ctrl.
*/
SSLLINKDLL SEC_INT IPSI_AIO_setErrno(const IPSI_AIO_S *aio, SEC_INT errNum);

#define IPSI_AIO_NOCLOSE 0x00
#define IPSI_AIO_CLOSE 0x01


//This macro is used to set peer address in to AIO object
#define IPSI_AIO_DGRAM_SET_PEER(pstAio,peer) \
    (SEC_INT)ipsi_aio_ctrl(pstAio, AIO_CTRL_DGRAM_SET_PEER, 0, (SEC_CHAR *)peer)

//This macro is used to get peer address from AIO object
//Application should allocate memory for peer sothat it can hold peer address
#define IPSI_AIO_DGRAM_GET_PEER(pstAio,peer) \
    (SEC_INT)ipsi_aio_ctrl(pstAio, AIO_CTRL_DGRAM_GET_PEER, 0, (SEC_CHAR *)peer)


/* This macro is used to set recv timeout in socket. tv argument should be passed as pointer to IPSI_TIMEVAL_S */
/* structure variable. On success this macro returns IPSI_AIO_SUCCESS. */
/* a) It returns IPSI_AIO_ERROR if tv is passed as NULL pointer */
/* b) It returns IPSI_AIO_ERR if pstAio is passed as NULL pointer */
#define IPSI_AIO_DGRAM_SET_RECV_TIMEOUT(pstAio,tv) \
    (SEC_INT)ipsi_aio_ctrl(\
    pstAio, AIO_CTRL_DGRAM_SET_RECV_TIMEOUT, 0, (SEC_CHAR *)tv)

/* This macro is used to get the recv timeout set by user. tv argument should be passed as pointer to IPSI_TIMEVAL_S */
/* structure variable. Memory for this argument should be allocated by user. Timeout value will get updated in this */
/* variable. On success this macro returns IPSI_AIO_SUCCESS. */
/* a) It returns IPSI_AIO_ERROR if tv is passed as NULL pointer */
/* b) It returns IPSI_AIO_ERR if pstAio is passed as NULL pointer */
#define IPSI_AIO_DGRAM_GET_RECV_TIMEOUT(pstAio, tv) \
    (SEC_INT)ipsi_aio_ctrl(pstAio, AIO_CTRL_DGRAM_GET_RECV_TIMEOUT, 0, (SEC_VOID *)tv)


/* This macro is used to get the next timeout of the internal timer. pTicks argument should be passed as pointer to */
/* long variable. Memory for this argument should be allocated by user. Next timeout value will get updated in this */
/* variable. On success this macro returns IPSI_AIO_SUCCESS. */
/* a) It returns IPSI_AIO_ERROR if pTicks is passed as NULL pointer */
/* b) It returns IPSI_AIO_ERR if pstAio is passed as NULL pointer */
#define IPSI_AIO_DGRAM_GET_NEXT_TIMEOUT(pstAio, pTicks) \
    (SEC_INT)ipsi_aio_ctrl(pstAio, AIO_CTRL_DGRAM_GET_NEXT_TIMEOUT, 0, (SEC_VOID *)pTicks)
    
/* This macro is used to get the timeout duration of the internal timer. pTicks argument should be passed as pointer */
/* to long variable. Memory for this argument should be allocated by user. Timeout duration value will get updated */
/* in this variable. On success this macro returns IPSI_AIO_SUCCESS. */
/* a) It returns IPSI_AIO_ERROR if pTicks is passed as NULL pointer */
/* b) It returns IPSI_AIO_ERR if pstAio is passed as NULL pointer */
#define IPSI_AIO_DGRAM_GET_TIMEOUT_DUR(pstAio, pTicks) \
    (SEC_INT)ipsi_aio_ctrl(pstAio, AIO_CTRL_DGRAM_GET_TIMEOUT_DUR, 0, (SEC_VOID *)pTicks)

//Set socket id to AIO object
#define IPSI_AIO_SET_FD(pstAio,larg,fd) \
    ipsi_aio_int_ctrl(pstAio,AIO_C_SET_FD,larg,fd)

//Get socket id from AIO object
#define IPSI_AIO_GET_FD(pstAio,parg) \
    ipsi_aio_ctrl(pstAio,AIO_C_GET_FD,0,(SEC_CHAR *)parg)



#define IPSI_AIO_FREE(pAddr)                    \
if (SEC_NULL != pAddr){ (SEC_VOID)ipsi_aio_free(pAddr); pAddr = NULL;}


#ifdef __cplusplus
}
#endif

#endif // HEADER_IPSI_AIO_H
#endif

//lint +e123

