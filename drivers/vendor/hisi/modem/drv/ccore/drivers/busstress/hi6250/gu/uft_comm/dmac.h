
#define DMACINTSTATUS               0x000
#define DMACINTTCSTATUS             0x004
#define DMACINTTCCLEAR              0x008
#define DMACINTERRORSTATUS          0x00c
#define DMACINTERRCLR               0x010
#define DMACRAWINTTCSTATUS          0x014
#define DMACRAWINTERRORSTATUS       0x018
#define DMACENBLDCHNS               0x01c
#define DMACSOFTBREQ                0x020
#define DMACSOFTSREQ                0x024
#define DMACSOFTLBREQ               0x028
#define DMACSOFTLSREQ               0x02c
#define DMACCONFIGURATION           0x030
#define DMACSYNC                    0x034
#define DMACINTSTATUS2              0x040
#define DMACINTTCSTATUS2            0x044
#define DMACINTERRORSTATUS2         0x048

#define DMACCHANNELOFFSET           0x100
#define DMACCXSRCADDRCH0            0x000
#define DMACCXDESTADDRCH0           0x004
#define DMACCXLLICH0                0x008
#define DMACCXCONTROLCH0            0x00c
#define DMACCXCONFIGURATIONCH0      0x010
#define DMACCXSRCADDRCH1            0x020
#define DMACCXDESTADDRCH1           0x024
#define DMACCXLLICH1                0x028
#define DMACCXCONTROLCH1            0x02c
#define DMACCXCONFIGURATIONCH1      0x030
#define DMACCXSRCADDRCH2            0x040
#define DMACCXDESTADDRCH2           0x044
#define DMACCXLLICH2                0x048
#define DMACCXCONTROLCH2            0x04c
#define DMACCXCONFIGURATIONCH2      0x050
#define DMACCXSRCADDRCH3            0x060
#define DMACCXDESTADDRCH3           0x064
#define DMACCXLLICH3                0x068
#define DMACCXCONTROLCH3            0x06c
#define DMACCXCONFIGURATIONCH3      0x070
#define DMACCXSRCADDRCH4            0x080
#define DMACCXDESTADDRCH4           0x084
#define DMACCXLLICH4                0x088
#define DMACCXCONTROLCH4            0x08c
#define DMACCXCONFIGURATIONCH4      0x090
#define DMACCXSRCADDRCH5            0x0a0
#define DMACCXDESTADDRCH5           0x0a4
#define DMACCXLLICH5                0x0a8
#define DMACCXCONTROLCH5            0x0ac
#define DMACCXCONFIGURATIONCH5      0x0b0
#define DMACCXSRCADDRCH6            0x0c0
#define DMACCXDESTADDRCH6           0x0c4
#define DMACCXLLICH6                0x0c8
#define DMACCXCONTROLCH6            0x0cc
#define DMACCXCONFIGURATIONCH6      0x0d0
#define DMACCXSRCADDRCH7            0x0e0
#define DMACCXDESTADDRCH7           0x0e4
#define DMACCXLLICH7                0x0e8
#define DMACCXCONTROLCH7            0x0ec
#define DMACCXCONFIGURATIONCH7      0x0f0

#define DMACCXSRCADDRCH             0x00
#define DMACCXDESTADDRCH            0x04
#define DMACCXLLICH                 0x08
#define DMACCXCONTROLCH             0x0c
#define DMACCXCONFIGURATIONCH       0x10

#define BIT0_OFFSET                 0x0
#define BIT1_OFFSET                 0x1
#define BIT2_OFFSET                 0x2
#define BIT3_OFFSET                 0x3
#define BIT4_OFFSET                 0x4
#define BIT5_OFFSET                 0x5
#define BIT6_OFFSET                 0x6
#define BIT7_OFFSET                 0x7
#define BIT8_OFFSET                 0x8
#define BIT9_OFFSET                 0x9
#define BIT10_OFFSET                0xA
#define BIT11_OFFSET                0xB
#define BIT12_OFFSET                0xC
#define BIT13_OFFSET                0xD
#define BIT14_OFFSET                0xE
#define BIT15_OFFSET                0xF
#define BIT16_OFFSET                0x10
#define BIT17_OFFSET                0x11
#define BIT18_OFFSET                0x12
#define BIT19_OFFSET                0x13
#define BIT20_OFFSET                0x14
#define BIT21_OFFSET                0x15
#define BIT22_OFFSET                0x16
#define BIT23_OFFSET                0x17
#define BIT24_OFFSET                0x18
#define BIT25_OFFSET                0x19
#define BIT26_OFFSET                0x1A
#define BIT27_OFFSET                0x1B
#define BIT28_OFFSET                0x1C
#define BIT29_OFFSET                0x1D
#define BIT30_OFFSET                0x1E
#define BIT31_OFFSET                0x1F


#define BIT0                        0x1
#define BIT1                        0x2
#define BIT2                        0x4
#define BIT3                        0x8
#define BIT4                        0x10
#define BIT5                        0x20
#define BIT6                        0x40
#define BIT7                        0x80
#define BIT8                        0x100
#define BIT9                        0x200
#define BIT10                       0x400
#define BIT11                       0x800
#define BIT12                       0x1000
#define BIT13                       0x2000
#define BIT14                       0x4000
#define BIT15                       0x8000
#define BIT16                       0x10000
#define BIT17                       0x20000
#define BIT18                       0x40000
#define BIT19                       0x80000
#define BIT20                       0x100000
#define BIT21                       0x200000
#define BIT22                       0x400000
#define BIT23                       0x800000
#define BIT24                       0x1000000
#define BIT25                       0x2000000
#define BIT26                       0x4000000
#define BIT27                       0x8000000
#define BIT28                       0x10000000
#define BIT29                       0x20000000
#define BIT30                       0x40000000
#define BIT31                       0x80000000

#define DMAC_OK                     0x0    /*dmac configuration ok*/
#define ERR_DMAC0                   0x1    /*source master choice value should only be 0 or 1*/
#define ERR_DMAC1                   0x2    /*destination master choice value should only be 0 or 1*/
#define ERR_DMAC2                   0x3    /*source increment choice value should only be 0 or 1*/
#define ERR_DMAC3                   0x4    /*destination increment choice value should only be 0 or 1*/
#define ERR_DMAC4                   0x5    /*source width value invalid*/
#define ERR_DMAC5                   0x6    /*destination width value invalid*/
#define ERR_DMAC6                   0x7    /*source burst value invalid*/
#define ERR_DMAC7                   0x8    /*destination burst value invalid*/



int DmaM2MTrans( UINT32 DmaBaseAddr,
                 UINT32 src_addr,        //Source Address
                 UINT32 des_addr,        //Destination Address
                 int    SMaster,         //0->Master1,1->Master2
                 int    DMaster,         //0->Master1,1->Master2		  
                 int    src_inc,         //Source Increment
                 int    des_inc,         //Destination Increment
                 int    SWidth,          //width 0->8 ,1->16,2->32bit
                 int    DWidth,          //width 0->8 ,1->16,2->32bit					 
                 int    SBSize,          //Source Busrt Type : 0->1,1->4,2->8,3->16,4->32,5->64,6->128,7->256
                 int    DBSize,          //Destination Busrt Type : 0->1,1->4,2->8,3->16,4->32,5->64,6->128,7->256
                 int    TransferSize,    //Transfer Size : 0x1~0xfff
                 int    Channel,         //Choose DMAC Channel - 0~7
                 int    Intr_Master )  ; //Choose Master(ARM or ZSP): 0->ARM,1->ZSP
	
int DmaM2MLLITrans( UINT32 DmaBaseAddr,     //DMAC Base Address
                    UINT32 src_addr,        //Source Address
                    UINT32 des_addr,        //Destination Address
                    UINT32 LLI_addr,        //LLI Address
                    int    SMaster,         //0->Master1,1->Master2
                    int    DMaster,         //0->Master1,1->Master2
                    int    src_inc,         //Source Increment
                    int    des_inc,         //Destination Increment
                    int    SWidth,          //width 0->8 ,1->16,2->32bit
                    int    DWidth,          //width 0->8 ,1->16,2->32bit					 
                    int    SBSize,          //Source Busrt Type : 0->1,1->4,2->8,3->16,4->32,5->64,6->128,7->256
                    int    DBSize,          //Destination Busrt Type : 0->1,1->4,2->8,3->16,4->32,5->64,6->128,7->256
                    int    TransferSize,    //Transfer Size : >= 0x1000
                    int    Channel,         //Choose DMAC Channel - 0~7
                    int    Intr_Master )  ; //Choose Master(ARM or ZSP): 0->ARM,1->ZSP					 

int DmaM2MTrans32( UINT32 DmaBaseAddr,      //DMAC Base Address
                   UINT32 src_addr,         //Source Address
                   UINT32 des_addr,         //Destination Address
                   int    TransferSize,     //Transfer Size : 0x1~0xfff
                   int    Channel,          //Choose DMAC Channel - 0~7
                   int    Intr_Master )  ;  //Choose Master(ARM or ZSP): 0->ARM,1->ZSP
					 
int DmaM2MLLITrans32( UINT32 DmaBaseAddr,     //DMAC Base Address
                      UINT32 src_addr,        //Source Address
                      UINT32 des_addr,        //Destination Address
                      UINT32 LLI_addr,        //LLI Address
                      int    TransferSize,    //Transfer Size : >= 0x1000
                      int    Channel,         //Choose DMAC Channel - 0~7
                      int    Intr_Master ) ;  //Choose Master(ARM or ZSP): 0->ARM,1->ZSP


