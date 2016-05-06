
#ifndef _IP6_PMTU_STRUCT_H
#define _IP6_PMTU_STRUCT_H

#ifdef  __cplusplus
extern "C"{
#endif

#include "ipv6/pathmtu/core/include/pmtu_def.h"

/* Format of PMTU entry in I/O board. */
/* Defect :BYAD04332
   IPv6:PMTU asserts observed during slave switchover.*/
typedef struct tagpmtubitmap
{
    USHORT usMsgtype;
    USHORT usReserved;
} PMTU_BITMAP_S;

/* Main board whenever it deletes a PMTU entry, it sends this message to reflect
   change in I/O Board, Standby Board. */
typedef struct tagDelPmtuEntry
{
    USHORT    usMsgtype;
    USHORT    usReserved;
    ULONG     ulMultipleindex; /* Identifies PMTU entry in I/O, standby
                                  boards */
} DEL_PMTU_ENTRY_S;

/* Whenever global aging timer is changed in Main Board, it sends this message
   to modify Global aging timer for standby.*/
typedef struct tagMfyGlobalAgetime
{
    USHORT    usMsgtype;
    USHORT    usAgetime;
} MFY_GLOBAL_AGE_TIME_S;

/* PMTU Entry's structure for storing.*/
/* Format of PMTU entry in standby.*/
typedef struct tagPmtuEntryStandby
{
    /* Create PMTU entry in this position in standby board.*/
    ULONG          ulMultiIndex;
    IN6ADDR_S      stDA;
    ULONG          ulZoneid;
    ULONG          ulPmtu;
    USHORT         usAgetime;

    /* PN:AC4D01274*/
    USHORT         usAge_variable;
    UCHAR          ucControlflag;
    UCHAR          ucReserved;

    /* PN:AC4D01274*/
    USHORT         usReserved;
} PMTU_ENTRY_STANDBY_S;


/* Main board whenever it adds a new PMTU entry,
   it sends this message to reflect change in standby Board.*/
typedef struct tagAddPmtuEntryStandby
{
    USHORT       usMsgtype;
    USHORT       usReserved;
    PMTU_ENTRY_STANDBY_S  stRealdata;
} ADD_PMTU_ENTRY_STANDBY_S;


/* Modify the PMTU value for Standby.*/
typedef struct tagMfyPmtuEntryStandby
{
    USHORT        usMsgtype;
    USHORT        usAgetime;
    UCHAR         ucControlflag;
    UCHAR         ucReserved[3];
    ULONG         ulMultiIndex; /* Identifies PMTU entry in standby board */
    ULONG         ulPmtu;

}MFY_PMTU_ENTRY_STANDBY_S;


/* This is specify the messages in the standby board.*/
typedef struct tagPMTUMessageSBYBoard
{
    union
    {
        ADD_PMTU_ENTRY_STANDBY_S stAddPMTUSby;
        DEL_PMTU_ENTRY_S         stDelPMTU;
        MFY_PMTU_ENTRY_STANDBY_S stMfyPMTUSby;
        MFY_GLOBAL_AGE_TIME_S    stMfyGAgeTime;
    }unPMTUMsgSby;
}PMTU_MESSAGE_SBYBOARD_S;

/* Format of PMTU entry in I/O board.*/
typedef struct tagpmtuentryio
{
    /* create PMTU entry in this position in I/O Board */
    ULONG         ulMultiIndex;
    ULONG         ulZoneid;
    ULONG         ulPmtu;
    IN6ADDR_S     stDA;
    UCHAR         ucControl_flag;
    UCHAR         ucReserved1;
    USHORT        usReserved2;
}PMTU_ENTRY_IO_S;

/* Whenever I/O board plugged in main board send this message to I/O board.*/
typedef struct tagbatchdataio
{
    USHORT        usMsgtype;
    USHORT        usNoOfEntries;
    PMTU_ENTRY_IO_S stBatchData [MAX_IPC_MSG];
}BATCH_DATA_IO_S;

/* Add PMTU entry to IO using this strct for sync.*/
typedef struct tagaddpmtuentryio
{
    USHORT usMsgtype;
    USHORT usReserved;
    PMTU_ENTRY_IO_S  stRealdata;
}ADD_PMTU_ENTRY_IO_S;

/* Modify PMTU message with IO.*/
typedef struct tagMfyPmtuEntryIO
{
    USHORT         usMsgtype;
    UCHAR          ucControl_flag;
    UCHAR          ucReserved1;
    ULONG          ulMultipleindex; /* Identifies PMTU entry in I/O board */
    ULONG          ulPmtu;
}MFY_PMTU_ENTRY_IO_S;

/* This is specify the messages in the IO board.*/
typedef struct tagIpcMsgIOBoard
{
    union
    {
        BATCH_DATA_IO_S     stBatchDataIO;
        ADD_PMTU_ENTRY_IO_S stAddPMTUIO;
        DEL_PMTU_ENTRY_S    stDelPMTU;
        MFY_PMTU_ENTRY_IO_S stMfyPMTUIO;
        PMTU_BITMAP_S       stBitMap;
    }unIPCMSgIOboard;
}IPC_MESSAGE_IOBOARD_S;

/* ICMP Error - Packet Too Big Information with Message Type
  (a. Too Big Message, b. Access Count, c. Real Time Backup.).*/
typedef struct tagTooBigMsg
{
    USHORT          usMsgtype;
    USHORT          usReserved;
    TOO_BIG_INFO_S  stTooBigInfo;
}TOO_BIG_MSG_S;


/* When PP queries about PMTU value in I/O Board, I/O board sends this message
   to main board to increase access count.*/
typedef struct tagIncAccessCount
{
    USHORT      usMsgtype;
    USHORT      usReserved;
    ULONG       ulMultipleindex; /* Identifies PMTU entry in Main Board */
}INC_ACCESS_COUNT_S;

/* When PP notifies Path MTU component of interface MTU that is less than PMTU
   in I/O Board, I/O board sends this message to main board to change PMTU
   value.*/
typedef struct tagChangeMtu
{
    USHORT        usMsgtype;
    USHORT        usReserved;
    ULONG         ulMultipleindex; /* Identifies PMTU entry in Main Board.*/
    ULONG         ulMtu;  /* new value given by PP */
} CHANGE_MTU_S;


/* This is specify the messages in the main board.*/
typedef struct tagIpcMsgMainboard
{
    union
    {
        TOO_BIG_MSG_S         stTooBigMsg;
        INC_ACCESS_COUNT_S    stIncAccessCount;
        CHANGE_MTU_S          stChangeMTU;
    }unIPCMsgMBoard;
}IPC_MESSAGE_MBOARD_S;


/* Whenever standby board comes up main board send this message to
  standby board.*/
typedef struct tagBatchDataSBY
{
    USHORT        usGlobalAgetime;
    USHORT        usNoOfEntries;
    PMTU_ENTRY_STANDBY_S stBatchData [MAX_IPC_MSG];
} BATCH_DATA_SBY_S;

/* To maintain dll of DA list for a socket identity node.
   To implement 1 to N relationship between socket id and DA.*/
typedef struct tagDestAddnode
{
    IN6ADDR_S   DA;
    ULONG       ulScope_id;         /* zone index */
} DESTADDRESS_NODE_S;

/* To maintain dll of DA list for a socket identity node.
   To implement 1 to N relationship between socket id and DA.*/
typedef struct tagDAnode
{
    IN6ADDR_S         DA;
    ULONG             ulScope_id; /* zone index */
    struct tagDAnode  *next;
    struct tagDAnode  *prev;
} DA_NODE_S;

/* To maintain dll of socket identity list. To implement 1 to N relationship
   between socket id and DA.*/
typedef struct tagSocketIdentityNode
{
    LONG   Socket_identity;
    struct tagSocketIdentityNode *next;
    struct tagSocketIdentityNode *prev;
    DA_NODE_S *DA_head; /* Head of DLL of dst address for this socket id */
} SOCKET_IDENTITY_NODE_S;

/* For Searching -- maintain a socket id list for DA.*/
typedef struct tagsockid
{
    ULONG ulTaskId;          /*  task id  */
    LONG lSocketid;         /* socket id */

} SOCKET_ID_SEARCH_NODE_S;

/* To maintain dll of socket id list for a destination address.
   To implement 1 to N relationship between DA and socket id.*/
typedef struct tagsocketidnode
{
    LONG   lSocketid;    /* socket id */
    ULONG  ulTaskId;    /*  task id  */
    struct tagsocketidnode *next;
    struct tagsocketidnode *prev;
} SOCKET_ID_NODE_S;

/* Multiple Index Structure.*/
typedef struct tagMultiple_Index_Node
{
    ULONG  ulMultiIndex;
    struct tagMultiple_Index_Node *next;
    struct tagMultiple_Index_Node *prev;
} MULTIPLE_INDEX_NODE_S;

/* The structure to store the details of a PMTU entry.*/
typedef struct tagPmtuEntry
{
    IN6ADDR_S   stDest_Addr;
    ULONG       ulZoneid;          /* zone index */
    ULONG       ulPMTU;           /* Path MTU   */
    USHORT      usAge_time;      /* Aging time */
    USHORT      usAge_variable; /* Decrement by 1 during aging timeout*/
    UCHAR       ucControl_flag;
    UCHAR       ucAccess_count [MAX_CATCH_ITEM]; /*Last 10 min info per minute*/
    UCHAR       ucTotal_count;  /* Last 10 min Total count */
    ULONG       ulSocketCount;

    /* PN:AC4D01274*/
    ULONG             ulTimeStamp;
    SOCKET_ID_NODE_S  *pSocket_head;
}PMTU_ENTRY_S;


#ifdef  __cplusplus
}
#endif

#endif
