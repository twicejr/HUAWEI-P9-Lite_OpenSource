

#ifndef __LINUX_USB_SERIAL_MCT_U232_H
#define __LINUX_USB_SERIAL_MCT_U232_H

#define MCT_U232_VID	                0x0711	/* Vendor Id */
#define MCT_U232_PID	                0x0210	/* Original MCT Product Id */

/* U232-P25, Sitecom */
#define MCT_U232_SITECOM_PID		0x0230	/* Sitecom Product Id */

/* DU-H3SP USB BAY hub */
#define MCT_U232_DU_H3SP_PID		0x0200	/* D-Link DU-H3SP USB BAY */

/* Belkin badge the MCT U232-P9 as the F5U109 */
#define MCT_U232_BELKIN_F5U109_VID	0x050d	/* Vendor Id */
#define MCT_U232_BELKIN_F5U109_PID	0x0109	/* Product Id */

/*
 * Vendor Request Interface
 */
#define MCT_U232_SET_REQUEST_TYPE	0x40
#define MCT_U232_GET_REQUEST_TYPE	0xc0

/* Get Modem Status Register (MSR) */
#define MCT_U232_GET_MODEM_STAT_REQUEST	2
#define MCT_U232_GET_MODEM_STAT_SIZE	1

/* Get Line Control Register (LCR) */
/* ... not used by this driver */
#define MCT_U232_GET_LINE_CTRL_REQUEST	6
#define MCT_U232_GET_LINE_CTRL_SIZE	1

/* Set Baud Rate Divisor */
#define MCT_U232_SET_BAUD_RATE_REQUEST	5
#define MCT_U232_SET_BAUD_RATE_SIZE	4

/* Set Line Control Register (LCR) */
#define MCT_U232_SET_LINE_CTRL_REQUEST	7
#define MCT_U232_SET_LINE_CTRL_SIZE	1

/* Set Modem Control Register (MCR) */
#define MCT_U232_SET_MODEM_CTRL_REQUEST	10
#define MCT_U232_SET_MODEM_CTRL_SIZE	1

/*
 * This USB device request code is not well understood.  It is transmitted by
 * the MCT-supplied Windows driver whenever the baud rate changes.
 */
#define MCT_U232_SET_UNKNOWN1_REQUEST	11  /* Unknown functionality */
#define MCT_U232_SET_UNKNOWN1_SIZE	1

/*
 * This USB device request code appears to control whether CTS is required
 * during transmission.
 *
 * Sending a zero byte allows data transmission to a device which is not
 * asserting CTS.  Sending a '1' byte will cause transmission to be deferred
 * until the device asserts CTS.
 */
#define MCT_U232_SET_CTS_REQUEST	12
#define MCT_U232_SET_CTS_SIZE		1

#define MCT_U232_MAX_SIZE		4	/* of MCT_XXX_SIZE */

/*
 * Baud rate (divisor)
 * Actually, there are two of them, MCT website calls them "Philips solution"
 * and "Intel solution". They are the regular MCT and "Sitecom" for us.
 * This is pointless to document in the header, see the code for the bits.
 */
static int mct_u232_calculate_baud_rate(struct usb_serial *serial,
					speed_t value, speed_t *result);

/*
 * Line Control Register (LCR)
 */
#define MCT_U232_SET_BREAK              0x40

#define MCT_U232_PARITY_SPACE		0x38
#define MCT_U232_PARITY_MARK		0x28
#define MCT_U232_PARITY_EVEN		0x18
#define MCT_U232_PARITY_ODD		0x08
#define MCT_U232_PARITY_NONE		0x00

#define MCT_U232_DATA_BITS_5            0x00
#define MCT_U232_DATA_BITS_6            0x01
#define MCT_U232_DATA_BITS_7            0x02
#define MCT_U232_DATA_BITS_8            0x03

#define MCT_U232_STOP_BITS_2            0x04
#define MCT_U232_STOP_BITS_1            0x00

/*
 * Modem Control Register (MCR)
 */
#define MCT_U232_MCR_NONE               0x8     /* Deactivate DTR and RTS */
#define MCT_U232_MCR_RTS                0xa     /* Activate RTS */
#define MCT_U232_MCR_DTR                0x9     /* Activate DTR */

/*
 * Modem Status Register (MSR)
 */
#define MCT_U232_MSR_INDEX              0x0     /* data[index] */
#define MCT_U232_MSR_CD                 0x80    /* Current CD */
#define MCT_U232_MSR_RI                 0x40    /* Current RI */
#define MCT_U232_MSR_DSR                0x20    /* Current DSR */
#define MCT_U232_MSR_CTS                0x10    /* Current CTS */
#define MCT_U232_MSR_DCD                0x08    /* Delta CD */
#define MCT_U232_MSR_DRI                0x04    /* Delta RI */
#define MCT_U232_MSR_DDSR               0x02    /* Delta DSR */
#define MCT_U232_MSR_DCTS               0x01    /* Delta CTS */

/*
 * Line Status Register (LSR)
 */
#define MCT_U232_LSR_INDEX	1	/* data[index] */
#define MCT_U232_LSR_ERR	0x80	/* OE | PE | FE | BI */
#define MCT_U232_LSR_TEMT	0x40	/* transmit register empty */
#define MCT_U232_LSR_THRE	0x20	/* transmit holding register empty */
#define MCT_U232_LSR_BI		0x10	/* break indicator */
#define MCT_U232_LSR_FE		0x08	/* framing error */
#define MCT_U232_LSR_OE		0x02	/* overrun error */
#define MCT_U232_LSR_PE		0x04	/* parity error */
#define MCT_U232_LSR_OE		0x02	/* overrun error */
#define MCT_U232_LSR_DR		0x01	/* receive data ready */




#endif /* __LINUX_USB_SERIAL_MCT_U232_H */

