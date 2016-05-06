

// *****************************************************************************
// PROJECT   : MSP_CPV100R001C00
// SUBSYSTEM : AT
// MODULE    :
// OWNER     :
// *****************************************************************************

#ifndef __AT_LTE_UPGRADE_PROC_H__
#define __AT_LTE_UPGRADE_PROC_H__

#include "gen_msg.h"

#define UPGRADE_STR_BUF_SIZE 512

/*#define DLOAD_OK              0
 */
/*#define DLOAD_ERROR          (-1)
 */

#define AT_UPGRADE_DLOADVER          1 /*at^dloadver?
 */
#define AT_UPGRADE_DLOADINFO         2 /*at^dloadinfo?
 */
#define AT_UPGRADE_AUTHORITYVER      3 /*at^authorityver?
 */
#define AT_UPGRADE_AUTHORITYID       4 /*at^authorityid?
 */
#define AT_UPGRADE_GODLOAD           5 /*at^godload
 */
#define AT_UPGRADE_NVBACKUP          6 /*at^nvbackup
 */
#define AT_UPGRADE_NVRESTORE         7 /*at^nvrestore
 */
#define AT_UPGRADE_NVRSTSTTS         8 /*at^nvrststts
 */
#define AT_UPGRADE_RESET             9 /*at^reset
 */
#define AT_UPGRADE_DATAMODE          10/*at^datamode
 */


#endif





