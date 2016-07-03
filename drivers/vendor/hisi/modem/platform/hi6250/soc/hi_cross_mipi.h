
#ifndef __HI_CROSS_MIPI_H__
#define __HI_CROSS_MIPI_H__


#ifdef __cplusplus
extern "C" {
#endif

#define CROSS_MIPI_USE_BBP_DMA
#define CROSS_MIPI_PHONE
#define CROSS_MIPI_HI6250

#define CROSS_MIPI_MASK_OFFSET              (0x15e8)
#define CROSS_MIPI_GPIO_MASK_OFFSET         (0x2d8)
#define TUNER_TAS_IND_OFFSET                (0X2d4)

#define CROSS_MIPI_M0_LINE_P_MASK_OFFSET    (0x1064)
#define CROSS_MIPI_M0_LINE_S_MASK_OFFSET    (0x1068)
#define CROSS_MIPI_M1_LINE_MASK_OFFSET      (0x106C)

#define CROSS_MIPI_EN_OFFSET                (0x0)
#define CROSS_MIPI_REQ_EN_OFFSET            (0x4)
#define CROSS_GPIO_EN_OFFSET                (0X2C)

#define CROSS_MIPI_MIPI_MEM_OFFSET          (0x0)
#define CROSS_MIPI_GPIO_MEM_OFFSET          (0x2400)

#define CROSS_MIPI_BUFFER_LEN               (2304)
#define CROSS_GPIO_BUFFER_LEN               (96)

#define CROSS_MIPI_BBP_DMA_CHN              (2)
#define CROSS_GPIO_BBP_DMA_CHN              (3)

#ifdef __cplusplus
}
#endif

#endif

