#ifndef _HISILICON_UDP_BOARD_ID_H_
#define _HISILICON_UDP_BOARD_ID_H_

#define	D2_TYPE_LCD	01
#define	JDI_TYPE_LCD	02

/******************************************************************************
Function:	    read_lcd_type
Description:	    读取MMU扣板对应的LCD类型
Input:		    none
Output:		    none
Return:		    01: D2_TYPE_LCD  02: JDI_TYPE_LCD 其他: ERROR
******************************************************************************/
extern int read_lcd_type(void);

#endif
