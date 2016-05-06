/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  adp_mbxhifi.c
*
*   作    者 :  m00177601
*
*************************************************************************/
#include <mdrv.h>

unsigned int DRV_MAILBOX_READMAILDATA(
                void                   *MailHandle,
                unsigned char          *pData,
                unsigned int          *pSize)

{
        return 0;
}

unsigned int DRV_MAILBOX_SENDMAIL(
                unsigned int           MailCode,
                void                   *pData,
                unsigned int           Length)
{
        return 0;
}

unsigned int DRV_MAILBOX_REGISTERRECVFUNC(
                unsigned int           MailCode,
                mb_msg_cb               pFun,
                void                   *UserHandle)
{
        return 0;
}
