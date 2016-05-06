#include <soc_memmap.h>
#include <bsp_shared_ddr.h>
////////////////////////
// TEST MODULE SELECT //
////////////////////////
//#define A13_PLATFORM
//#define A19_PLATFORM
//#define V3_PLATFORM
//#define V3R2_PLATFORM

////////////////////////
// DEBUG INFO DISPLAY //
////////////////////////
//#define _UNIT_DEBUG

////////////////////////
// TEST MODULE SELECT //
////////////////////////
#define CEVATEST
#define CEVAL2SRAMTEST
//#define CICOMV200TEST
//#difine CICOMV300TEST
#define COMMTEST
//#define DMTEST
#define EDMACTEST
//#define HDLCTEST
#define SMIMTEST
//#define UPACCTEST
#define XDMACTEST
//#define BalongB030
//#define K3V3_FPGA
#define DMOVE2_BASEADDR             0x60030000

#ifdef CICOMV200TEST
#define CICOM_BASEADDR              0x30040000
#endif

#ifdef HICICOMV300
#define CICOM_BASEADDR              0x60000000
#endif

#define HDLC_BASEADDR               0xE0442000
#define UPACC_BASEADDR              0xE0453000
#define CICOM_BASEADDR              0xE0440000
#define SYSCTRL_BASEADDR            0xE0200000
#define SYSCTRL_SCMISCCTRL          (HI_SYSCTRL_BASE_ADDR + 0x410)
#define SYSCTRL_CRG                 (HI_SYSCTRL_BASE_ADDR + 0X64)
#define SYSCTRL_CRG_VALUE           0xFFFFFFFF
#define Cicom_sel                   0
#define Cicom1_sel                  1



