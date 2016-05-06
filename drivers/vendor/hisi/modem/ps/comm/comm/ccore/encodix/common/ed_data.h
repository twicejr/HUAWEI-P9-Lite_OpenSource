/*******************************************************************************
  ed_data.h  Developed by Dafocus - http://www.dafocus.com/
*******************************************************************************/
#include "ed_user.h"
#ifndef __ED_DATA_H
#define __ED_DATA_H

#define ED_COMMON_CRC 0x328E3625

/* BOOLEAN DATA TYPE */
#ifndef ED_BOOLEAN
#define ED_BOOLEAN unsigned char
#endif

#ifndef ED_FALSE
#define ED_FALSE     (0)
#endif
#ifndef ED_TRUE
#define ED_TRUE      (1)
#endif

/* Values that were defined as "long" prior to version 1.0.144, now normalized to "int" */
#ifndef ED_EXLONG
#define ED_EXLONG int
#endif

/* BYTE DATA TYPE */
#ifndef ED_BYTE
#define ED_BYTE unsigned char
#endif

/* LONG (32 bit) DATA TYPE */
#ifndef ED_LONG
#define ED_LONG unsigned long
#endif

/* SHORT (16 bit) DATA TYPE */
#ifndef ED_SHORT
#define ED_SHORT unsigned short
#endif

/* OCTET (8 bit) DATA TYPE */
#ifndef ED_OCTET
#define ED_OCTET unsigned char
#endif

/* LOCATOR (32 bit) DATA TYPE */
#ifndef ED_LOCATOR
#define ED_LOCATOR unsigned ED_EXLONG
#endif

#ifndef ED_ASSERT_FORCE_FAIL
#define ED_ASSERT_FORCE_FAIL assert (0);
#endif

#endif
