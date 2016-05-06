
/*
 *****************************************************************************
 * 1 Other Header File Including
 *****************************************************************************
 */
#ifndef GLOBAL_CFG_H
#define GLOBAL_CFG_H

/*#include  ###*/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*
 *****************************************************************************
 * 2 Macro Definition
 ****************************************************************************
 */

/* HKADC channel */
#define ADC_BOARDID0		 (0x04)
#define ADC_BOARDID1		 (0x01)
#define ADC_BOARDID2		 (0x02)
#define ADC_UNUSE0			 (0x00)  /*未使用*/
#define ADC_UNUSE1			 (0x01)  /*未使用*/
#define ADC_VBATMON			 (0x0B)  /*电池ID*/
#define ADC_VCOINMON		 (0x06)  /*V9R1原先值为0x05，对应PA0温度，但实际可能没有用这里，
                                      V8R1也将其修改为PA0温度对应的通道，为0x06*/
#define ADC_RTMP			 (0x0A)  /*电池温度*/

/* GPIO */
#define GPIO_0_0	0
#define GPIO_0_1	1
#define GPIO_0_2	2
#define GPIO_0_3	3
#define GPIO_0_4	4
#define GPIO_0_5	5
#define GPIO_0_6	6
#define GPIO_0_7	7

#define GPIO_1_0	8
#define GPIO_1_1	9
#define GPIO_1_2    10
#define GPIO_1_3    11
#define GPIO_1_4    12
#define GPIO_1_5    13
#define GPIO_1_6    14
#define GPIO_1_7    15

#define GPIO_2_0    16
#define GPIO_2_1    17
#define GPIO_2_2    18
#define GPIO_2_3    19
#define GPIO_2_4    20
#define GPIO_2_5    21
#define GPIO_2_6    22
#define GPIO_2_7    23

#define GPIO_3_0    24
#define GPIO_3_1    25
#define GPIO_3_2    26
#define GPIO_3_3    27
#define GPIO_3_4    28
#define GPIO_3_5    29
#define GPIO_3_6    30
#define GPIO_3_7    31

#define GPIO_4_0    32
#define GPIO_4_1    33
#define GPIO_4_2    34
#define GPIO_4_3    35
#define GPIO_4_4    36
#define GPIO_4_5    37
#define GPIO_4_6    38
#define GPIO_4_7    39

#define GPIO_5_0    40
#define GPIO_5_1    41
#define GPIO_5_2    42
#define GPIO_5_3    43
#define GPIO_5_4    44
#define GPIO_5_5    45
#define GPIO_5_6    46
#define GPIO_5_7    47

#define GPIO_6_0    48
#define GPIO_6_1    49
#define GPIO_6_2    50
#define GPIO_6_3    51
#define GPIO_6_4    52
#define GPIO_6_5    53
#define GPIO_6_6    54
#define GPIO_6_7    55

#define GPIO_7_0    56
#define GPIO_7_1    57
#define GPIO_7_2    58
#define GPIO_7_3    59
#define GPIO_7_4    60
#define GPIO_7_5    61
#define GPIO_7_6    62
#define GPIO_7_7    63

#define GPIO_8_0    64
#define GPIO_8_1    65
#define GPIO_8_2    66
#define GPIO_8_3    67
#define GPIO_8_4    68
#define GPIO_8_5    69
#define GPIO_8_6    70
#define GPIO_8_7    71

#define GPIO_9_0    72
#define GPIO_9_1    73
#define GPIO_9_2    74
#define GPIO_9_3    75
#define GPIO_9_4    76
#define GPIO_9_5    77
#define GPIO_9_6    78
#define GPIO_9_7    79

#define GPIO_10_0   80
#define GPIO_10_1   81
#define GPIO_10_2   82
#define GPIO_10_3   83
#define GPIO_10_4   84
#define GPIO_10_5   85
#define GPIO_10_6   86
#define GPIO_10_7   87

#define GPIO_11_0   88
#define GPIO_11_1   89
#define GPIO_11_2   90
#define GPIO_11_3   91
#define GPIO_11_4   92
#define GPIO_11_5   93
#define GPIO_11_6   94
#define GPIO_11_7   95

#define GPIO_12_0   96
#define GPIO_12_1   97
#define GPIO_12_2   98
#define GPIO_12_3   99
#define GPIO_12_4   100
#define GPIO_12_5   101
#define GPIO_12_6   102
#define GPIO_12_7   103

#define GPIO_13_0   104
#define GPIO_13_1   105
#define GPIO_13_2   106
#define GPIO_13_3   107
#define GPIO_13_4   108
#define GPIO_13_5   109
#define GPIO_13_6   110
#define GPIO_13_7   111
#define GPIO_VOLUME_UP           GPIO_1_2
#define GPIO_VOLUME_DOWN         GPIO_1_3
#define GPIO_MENU                GPIO_1_4
#define GPIO_USBPHY_RESET        GPIO_2_2

/* 总线类型定义 */
#define BUS_MSK     0xFFFFFF00
#define I2C_FLAG    0xFFFFF000
#define SSI_FLAG    0xFFFFF100
#define SPI_FLAG    0xFFFFF200

#define I2C0    (0 | I2C_FLAG)
#define I2C1    (1 | I2C_FLAG)
#define I2C2    (2 | I2C_FLAG)

#define SSI0    (0 | SSI_FLAG)
#define SSI1    (1 | SSI_FLAG)

#define SPI0    (0 | SPI_FLAG)
#define SPI1    (1 | SPI_FLAG)

/* 连接充电芯片的总线类型 */
#define CHARGE_IC	       I2C1
/* 连接库仑计的总线类型 */
#define BFG_IC			   I2C1


/*
 *****************************************************************************
 * 3 Enum Type Definition
 *****************************************************************************
 */



/*
 *****************************************************************************
 * 4 Global Variable Declaring
 *****************************************************************************
 */


/*
 *****************************************************************************
 * 5 STRUCT Type Definition
 *****************************************************************************
 */



/*
 *****************************************************************************
 * 6 UNION Type Definition
 *****************************************************************************
 */


/*
 *****************************************************************************
 * 7 OTHERS Definition
 *****************************************************************************
 */


/*
 *****************************************************************************
 * 8 Function Declare
 *****************************************************************************
 */



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
