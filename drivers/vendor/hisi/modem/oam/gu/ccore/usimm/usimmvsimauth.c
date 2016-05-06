/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : UsimmvSIMAuth.c
  Author       : zhuli 00100318
  Version      : v00R002
  Date         : 2008-5-15
  Description  : 该C文件给出了---SIM/USIM鉴权算法实现
  Function List:
  History      :
************************************************************************/
#include "product_config.h"
#include "usimmvsimauth.h"
#include "v_lib.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*lint -e701 -e702 -e732 -e734 -e713 -e737 -e734*/

#if (FEATURE_VSIM == FEATURE_ON)


typedef unsigned char BYTE;


static const BYTE table_0[512] = {
        102,177,186,162,  2,156,112, 75, 55, 25,  8, 12,251,193,246,188,
        109,213,151, 53, 42, 79,191,115,233,242,164,223,209,148,108,161,
        252, 37,244, 47, 64,211,  6,237,185,160,139,113, 76,138, 59, 70,
         67, 26, 13,157, 63,179,221, 30,214, 36,166, 69,152,124,207,116,
        247,194, 41, 84, 71,  1, 49, 14, 95, 35,169, 21, 96, 78,215,225,
        182,243, 28, 92,201,118,  4, 74,248,128, 17, 11,146,132,245, 48,
        149, 90,120, 39, 87,230,106,232,175, 19,126,190,202,141,137,176,
        250, 27,101, 40,219,227, 58, 20, 51,178, 98,216,140, 22, 32,121,
         61,103,203, 72, 29,110, 85,212,180,204,150,183, 15, 66,172,196,
         56,197,158,  0,100, 45,153,  7,144,222,163,167, 60,135,210,231,
        174,165, 38,249,224, 34,220,229,217,208,241, 68,206,189,125,255,
        239, 54,168, 89,123,122, 73,145,117,234,143, 99,129,200,192, 82,
        104,170,136,235, 93, 81,205,173,236, 94,105, 52, 46,228,198,  5,
         57,254, 97,155,142,133,199,171,187, 50, 65,181,127,107,147,226,
        184,218,131, 33, 77, 86, 31, 44, 88, 62,238, 18, 24, 43,154, 23,
         80,159,134,111,  9,114,  3, 91, 16,130, 83, 10,195,240,253,119,
        177,102,162,186,156,  2, 75,112, 25, 55, 12,  8,193,251,188,246,
        213,109, 53,151, 79, 42,115,191,242,233,223,164,148,209,161,108,
         37,252, 47,244,211, 64,237,  6,160,185,113,139,138, 76, 70, 59,
         26, 67,157, 13,179, 63, 30,221, 36,214, 69,166,124,152,116,207,
        194,247, 84, 41,  1, 71, 14, 49, 35, 95, 21,169, 78, 96,225,215,
        243,182, 92, 28,118,201, 74,  4,128,248, 11, 17,132,146, 48,245,
         90,149, 39,120,230, 87,232,106, 19,175,190,126,141,202,176,137,
         27,250, 40,101,227,219, 20, 58,178, 51,216, 98, 22,140,121, 32,
        103, 61, 72,203,110, 29,212, 85,204,180,183,150, 66, 15,196,172,
        197, 56,  0,158, 45,100,  7,153,222,144,167,163,135, 60,231,210,
        165,174,249, 38, 34,224,229,220,208,217, 68,241,189,206,255,125,
         54,239, 89,168,122,123,145, 73,234,117, 99,143,200,129, 82,192,
        170,104,235,136, 81, 93,173,205, 94,236, 52,105,228, 46,  5,198,
        254, 57,155, 97,133,142,171,199, 50,187,181, 65,107,127,226,147,
        218,184, 33,131, 86, 77, 44, 31, 62, 88, 18,238, 43, 24, 23,154,
        159, 80,111,134,114,  9, 91,  3,130, 16, 10, 83,240,195,119,253
    }, table_1[256] = {
         19, 11, 80,114, 43,  1, 69, 94, 39, 18,127,117, 97,  3, 85, 43,
         27,124, 70, 83, 47, 71, 63, 10, 47, 89, 79,  4, 14, 59, 11,  5,
         35,107,103, 68, 21, 86, 36, 91, 85,126, 32, 50,109, 94,120,  6,
         53, 79, 28, 45, 99, 95, 41, 34, 88, 68, 93, 55,110,125,105, 20,
         90, 80, 76, 96, 23, 60, 89, 64,121, 56, 14, 74,101,  8, 19, 78,
         76, 66,104, 46,111, 50, 32,  3, 39,  0, 58, 25, 92, 22, 18, 51,
         57, 65,119,116, 22,109,  7, 86, 59, 93, 62,110, 78, 99, 77, 67,
         12,113, 87, 98,102,  5, 88, 33, 38, 56, 23,  8, 75, 45, 13, 75,
         95, 63, 28, 49,123,120, 20,112, 44, 30, 15, 98,106,  2,103, 29,
         82,107, 42,124, 24, 30, 41, 16,108,100,117, 40, 73, 40,  7,114,
         82,115, 36,112, 12,102,100, 84, 92, 48, 72, 97,  9, 54, 55, 74,
        113,123, 17, 26, 53, 58,  4,  9, 69,122, 21,118, 42, 60, 27, 73,
        118,125, 34, 15, 65,115, 84, 64, 62, 81, 70,  1, 24,111,121, 83,
        104, 81, 49,127, 48,105, 31, 10,  6, 91, 87, 37, 16, 54,116,126,
         31, 38, 13,  0, 72,106, 77, 61, 26, 67, 46, 29, 96, 37, 61, 52,
        101, 17, 44,108, 71, 52, 66, 57, 33, 51, 25, 90,  2,119,122, 35
    }, table_2[128] = {
         52, 50, 44,  6, 21, 49, 41, 59, 39, 51, 25, 32, 51, 47, 52, 43,
         37,  4, 40, 34, 61, 12, 28,  4, 58, 23,  8, 15, 12, 22,  9, 18,
         55, 10, 33, 35, 50,  1, 43,  3, 57, 13, 62, 14,  7, 42, 44, 59,
         62, 57, 27,  6,  8, 31, 26, 54, 41, 22, 45, 20, 39,  3, 16, 56,
         48,  2, 21, 28, 36, 42, 60, 33, 34, 18,  0, 11, 24, 10, 17, 61,
         29, 14, 45, 26, 55, 46, 11, 17, 54, 46,  9, 24, 30, 60, 32,  0,
         20, 38,  2, 30, 58, 35,  1, 16, 56, 40, 23, 48, 13, 19, 19, 27,
         31, 53, 47, 38, 63, 15, 49,  5, 37, 53, 25, 36, 63, 29,  5,  7
    }, table_3[64] = {
          1,  5, 29,  6, 25,  1, 18, 23, 17, 19,  0,  9, 24, 25,  6, 31,
         28, 20, 24, 30,  4, 27,  3, 13, 15, 16, 14, 18,  4,  3,  8,  9,
         20,  0, 12, 26, 21,  8, 28,  2, 29,  2, 15,  7, 11, 22, 14, 10,
         17, 21, 12, 30, 26, 27, 16, 31, 11,  7, 13, 23, 10,  5, 22, 19
    }, table_4[32] = {
         15, 12, 10,  4,  1, 14, 11,  7,  5,  0, 14,  7,  1,  2, 13,  8,
         10,  3,  4,  9,  6,  0,  3,  2,  5,  6,  8,  9, 11, 13, 15, 12
    }, *table[5] = { table_0, table_1, table_2, table_3, table_4 };

void RUNA3A8_V1(unsigned char key[16], unsigned char rand[16], unsigned char simoutput[12])
{
    BYTE x[32], bit[128];
    int i, j, k, l, m, n, y, z, next_bit;

    for (i=16; i<32; i++)
    {
        x[i] = rand[i-16];
    }

    for (i=1; i<9; i++)
    {
        for (j=0; j<16; j++)
        {
            x[j] = key[j];
        }

        for (j=0; j<5; j++)
        {
            for (k=0; k<(1<<j); k++)
            {
                for (l=0; l<(1<<(4-j)); l++)
                {
                    m = l + k*(1<<(5-j));
                    n = m + (1<<(4-j));
                    y = (x[m]+2*x[n]) % (1<<(9-j));
                    z = (2*x[m]+x[n]) % (1<<(9-j));
                    x[m] = table[j][y];
                    x[n] = table[j][z];
                }
            }
        }

        for (j=0; j<32; j++)
        {
            for (k=0; k<4; k++)
            {
                bit[4*j+k] = (x[j]>>(3-k)) & 1;
            }
        }

        if (i < 8)
        {
            for (j=0; j<16; j++)
            {
                x[j+16] = 0;

                for (k=0; k<8; k++)
                {
                    next_bit = ((8*j + k)*17) % 128;
                    x[j+16] |= bit[next_bit] << (7-k);
                }
            }
        }
    }

    for (i=0; i<4; i++)
    {
        simoutput[i] = (x[2*i]<<4) | x[2*i+1];
    }

    for (i=0; i<6; i++)
    {
        simoutput[4+i] = (x[2*i+18]<<6) | (x[2*i+18+1]<<2)
                | (x[2*i+18+2]>>2);
    }

    simoutput[4+6] = (x[2*6+18]<<6) | (x[2*6+18+1]<<2);

    simoutput[4+7] = 0;
}

static const BYTE  L[256]=
{
    197,235,60,151,98,96,3,100,248,118,42,117,172,211,181,203,
    61,126,156,87,149,224,55,132,186,63,238,255,85,83,152,33,
    160,184,210,219,159,11,180,194,130,212,147,5,215,92,27,46,
    113,187,52,25,185,79,221,48,70,31,101,15,195,201,50,222,
    137,233,229,106,122,183,178,177,144,207,234,182,37,254,227,231,
    54,209,133,65,202,69,237,220,189,146,120,68,21,125,38,30,
    2,155,53,196,174,176,51,246,167,76,110,20,82,121,103,112,
    56,173,49,217,252,0,114,228,123,12,93,161,253,232,240,175,
    67,128,22,158,89,18,77,109,190,17,62,4,153,163,59,145,
    138,7,74,205,10,162,80,45,104,111,150,214,154,28,191,169,
    213,88,193,198,200,245,39,164,124,84,78,1,188,170,23,86,
    226,141,32,6,131,127,199,40,135,16,57,71,91,225,168,242,
    206,97,166,44,14,90,236,239,230,244,223,108,102,119,148,251,
    29,216,8,9,249,208,24,105,94,34,64,95,115,72,134,204,
    43,247,243,218,47,58,73,107,241,179,116,66,36,143,81,250,
    139,19,13,142,140,129,192,99,171,157,136,41,75,35,165,26
};
static const BYTE  M[256]=
{
    170,42,95,141,109,30,71,89,26,147,231,205,239,212,124,129,
    216,79,15,185,153,14,251,162,0,241,172,197,43,10,194,235,
    6,20,72,45,143,104,161,119,41,136,38,189,135,25,93,18,
    224,171,252,195,63,19,58,165,23,55,133,254,214,144,220,178,
    156,52,110,225,97,183,140,39,53,88,219,167,16,198,62,222,
    76,139,175,94,51,134,115,22,67,1,249,217,3,5,232,138,
    31,56,116,163,70,128,234,132,229,184,244,13,34,73,233,154,
    179,131,215,236,142,223,27,57,246,108,211,8,253,85,66,245,
    193,78,190,4,17,7,150,127,152,213,37,186,2,243,46,169,
    68,101,60,174,208,158,176,69,238,191,90,83,166,125,77,59,
    21,92,49,151,168,99,9,50,146,113,117,228,65,230,40,82,
    54,237,227,102,28,36,107,24,44,126,206,201,61,114,164,207,
    181,29,91,64,221,255,48,155,192,111,180,210,182,247,203,148,
    209,98,173,11,75,123,250,118,32,47,240,202,74,177,100,80,
    196,33,248,86,157,137,120,130,84,204,122,81,242,188,200,149,
    226,218,160,187,106,35,87,105,96,145,199,159,12,121,103,112
};

static void compF(BYTE  A[16], BYTE  B[16],BYTE  C[16])
{
    BYTE Y[100] = {0};
    BYTE Z[100] = {0};
    BYTE i, j, k;

    for (j=0; j<16; j++)
    {
        Y[j]=B[j];

        Y[j+16]=A[j];
    }

    for( k = 0 ; k < 5 ; k++ )
        {
        for(j=0; j<16;j++)
        {
            Z[j]=L[ Y[j]^(M[ ( Y[j+16] ) ] ) ] ;
        }

        for(i=0;i<(1<<k);i++)
        {
            for(j=0; j<(1<<(4-k));j++)
            {
                Y[( (2*j+1) << k ) + i ] = L[ ( ( Y[( j<<k ) + i + 16] ) ^ ( M[ Z[ ( j << k ) + i ] ] ) ) ];
                Y[ ( j<< ( k + 1 ) ) + i] = Z[ ( j << k ) + i];
            }
        }
    }

    for(i=0;i<16;i++)
    {
        C[i]=0;
    }

    /* now compute the 16-byte output, C */
    for(i=0;i<16;i++)
    {
        for(j=0;j<8;j++)
        {
            C[i] = C[i] ^ ( ( ( Y[ ( ( 19* ( 8*i+j+1 ) ) %256 ) / 8 ] >> ( ( 3 * j + 3) % 8 ) ) & 1 ) << j);
        }
    }
}

void RUNA3A8_V2(unsigned char key[16],unsigned char randNumber[16], unsigned char output[12])
{
    BYTE i              = 0;
    BYTE temp           = 0;
    BYTE RecData[50]    = {0};

    for(i=0; i< 8; i++)
    {
       temp =  randNumber[15-i];

       randNumber[15-i] = randNumber[i];

       randNumber[i] = temp;

       temp= key[15-i];

       key[15-i]= key[i];

       key[i] = temp;
    }

    for( i = 0; i < 16; i++ )
    {
        key[i] =key[i] ^ randNumber[i];
    }

    for(i=0; i<8; i++)
    {
        compF(key,randNumber,randNumber);
    }

    for(i=0; i<4; i++)
    {
        RecData[3-i] =  randNumber[12 + i];
    }

    for(i=1; i<8; i++)
    {
        RecData[11 - i] = randNumber[i];
    }

    RecData[7+4] = 0;

    RecData[7+3] = ((( RecData[10]) >>2) << 2);

    memcpy(output, RecData, 12);
}

void RUNA3A8_V3(unsigned char ki_key[16],unsigned char randNumber[16], unsigned char output[12])
{
    BYTE i              = 0;
    BYTE temp           = 0;
    BYTE RecData[50]    = {0};

    for(i=0; i< 8; i++)
    {
       temp =  randNumber[15-i];

       randNumber[15-i] = randNumber[i];

       randNumber[i] = temp;

       temp= ki_key[15-i];

       ki_key[15-i]= ki_key[i];

       ki_key[i] = temp;
    }

    for( i = 0; i < 16; i++ )
    {
        ki_key[i] =ki_key[i] ^ randNumber[i];
    }

    for(i=0; i<8; i++)
    {
        compF(ki_key,randNumber,randNumber);
    }

    for( i = 0; i<4; i++)
    {
        RecData[3-i] = randNumber[12+i];
    }

    for( i=0; i<8; i++)
    {
        RecData[4 + 7 - i] = randNumber[i];
    }

    memcpy(output, RecData, 12);
}


unsigned char   Rand[16];
unsigned char   Autn[16];

#define D_F2_Mode       0x01
#define D_F3_Mode       0x02
#define D_F4_Mode       0x03
#define D_F5_Mode       0x01
#define D_F1Start_Mode  0x02
#define D_F5Start_Mode  0x04

#define SQN     (&Autn[0])
#define AMF     (&Autn[6])
#define MAC     (&Autn[8])

BYTE roundKeys[11][4][4];       /*用于AES的Key*/
BYTE state[4][4];               /*用于AES算法的全局数组*/

static const BYTE S[256] =
{
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

static const BYTE Xtime[256] =
{
    0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1A, 0x1C, 0x1E,
    0x20, 0x22, 0x24, 0x26, 0x28, 0x2A, 0x2C, 0x2E, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3A, 0x3C, 0x3E,
    0x40, 0x42, 0x44, 0x46, 0x48, 0x4A, 0x4C, 0x4E, 0x50, 0x52, 0x54, 0x56, 0x58, 0x5A, 0x5C, 0x5E,
    0x60, 0x62, 0x64, 0x66, 0x68, 0x6A, 0x6C, 0x6E, 0x70, 0x72, 0x74, 0x76, 0x78, 0x7A, 0x7C, 0x7E,
    0x80, 0x82, 0x84, 0x86, 0x88, 0x8A, 0x8C, 0x8E, 0x90, 0x92, 0x94, 0x96, 0x98, 0x9A, 0x9C, 0x9E,
    0xA0, 0xA2, 0xA4, 0xA6, 0xA8, 0xAA, 0xAC, 0xAE, 0xB0, 0xB2, 0xB4, 0xB6, 0xB8, 0xBA, 0xBC, 0xBE,
    0xC0, 0xC2, 0xC4, 0xC6, 0xC8, 0xCA, 0xCC, 0xCE, 0xD0, 0xD2, 0xD4, 0xD6, 0xD8, 0xDA, 0xDC, 0xDE,
    0xE0, 0xE2, 0xE4, 0xE6, 0xE8, 0xEA, 0xEC, 0xEE, 0xF0, 0xF2, 0xF4, 0xF6, 0xF8, 0xFA, 0xFC, 0xFE,
    0x1B, 0x19, 0x1F, 0x1D, 0x13, 0x11, 0x17, 0x15, 0x0B, 0x09, 0x0F, 0x0D, 0x03, 0x01, 0x07, 0x05,
    0x3B, 0x39, 0x3F, 0x3D, 0x33, 0x31, 0x37, 0x35, 0x2B, 0x29, 0x2F, 0x2D, 0x23, 0x21, 0x27, 0x25,
    0x5B, 0x59, 0x5F, 0x5D, 0x53, 0x51, 0x57, 0x55, 0x4B, 0x49, 0x4F, 0x4D, 0x43, 0x41, 0x47, 0x45,
    0x7B, 0x79, 0x7F, 0x7D, 0x73, 0x71, 0x77, 0x75, 0x6B, 0x69, 0x6F, 0x6D, 0x63, 0x61, 0x67, 0x65,
    0x9B, 0x99, 0x9F, 0x9D, 0x93, 0x91, 0x97, 0x95, 0x8B, 0x89, 0x8F, 0x8D, 0x83, 0x81, 0x87, 0x85,
    0xBB, 0xB9, 0xBF, 0xBD, 0xB3, 0xB1, 0xB7, 0xB5, 0xAB, 0xA9, 0xAF, 0xAD, 0xA3, 0xA1, 0xA7, 0xA5,
    0xDB, 0xD9, 0xDF, 0xDD, 0xD3, 0xD1, 0xD7, 0xD5, 0xCB, 0xC9, 0xCF, 0xCD, 0xC3, 0xC1, 0xC7, 0xC5,
    0xFB, 0xF9, 0xFF, 0xFD, 0xF3, 0xF1, 0xF7, 0xF5, 0xEB, 0xE9, 0xEF, 0xED, 0xE3, 0xE1, 0xE7, 0xE5
};

static const BYTE R[5] = {0x40,0x00,0x20,0x40,0x60};

static const BYTE C[80]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,
                     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
                     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,
                     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08};

static void Key_Schedule(BYTE key[16])
{
    BYTE  roundConst;
    BYTE  i, j;

    for (i=0; i<16; i++)
    {
        roundKeys[0][i & 0x03][i >> 2] = key[i];
    }

    roundConst = 1;

    for (i=1; i<11; i++)
    {
        roundKeys[i][0][0] = S[roundKeys[i - 1][1][3]] ^ roundKeys[i - 1][0][0] ^ roundConst;

        roundKeys[i][1][0] = S[roundKeys[i - 1][2][3]] ^ roundKeys[i - 1][1][0];

        roundKeys[i][2][0] = S[roundKeys[i - 1][3][3]] ^ roundKeys[i - 1][2][0];

        roundKeys[i][3][0] = S[roundKeys[i - 1][0][3]] ^ roundKeys[i - 1][3][0];

        for (j = 0; j < 4; j++)
        {
            roundKeys[i][j][1] = roundKeys[i - 1][j][1] ^ roundKeys[i][j][0];

            roundKeys[i][j][2] = roundKeys[i - 1][j][2] ^ roundKeys[i][j][1];

            roundKeys[i][j][3] = roundKeys[i - 1][j][3] ^ roundKeys[i][j][2];
        }

        roundConst = Xtime[roundConst];
    }

    return;
}

void KeyAdd(BYTE round)
{
    BYTE i, j;

    for (i=0; i<4; i++)
    {
        for (j=0; j<4; j++)
        {
            state[i][j] ^= roundKeys[round][i][j];
        }
    }

    return;
}

static void ByteSub(void)
{
    BYTE i, j;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            state[i][j] = S[state[i][j]];
        }
    }

    return;
}

static void ShiftRow(void)
{
    BYTE temp;

    temp = state[1][0];

    state[1][0] = state[1][1];

    state[1][1] = state[1][2];

    state[1][2] = state[1][3];

    state[1][3] = temp;

    temp = state[2][0];

    state[2][0] = state[2][2];

    state[2][2] = temp;

    temp = state[2][1];

    state[2][1] = state[2][3];

    state[2][3] = temp;

    temp = state[3][0];

    state[3][0] = state[3][3];

    state[3][3] = state[3][2];

    state[3][2] = state[3][1];

    state[3][1] = temp;

    return;
}

static void MixColumn(void)
{
    BYTE temp, tmp, tmp0;
    BYTE i;

    for (i = 0; i < 4; i++)
    {
        temp = state[0][i] ^ state[1][i] ^ state[2][i] ^ state[3][i];

        tmp0 = state[0][i];

        tmp = Xtime[state[0][i] ^ state[1][i]];

        state[0][i] ^= temp ^ tmp;

        tmp = Xtime[state[1][i] ^ state[2][i]];

        state[1][i] ^= temp ^ tmp;

        tmp = Xtime[state[2][i] ^ state[3][i]];

        state[2][i] ^= temp ^ tmp;

        tmp = Xtime[state[3][i] ^ tmp0];

        state[3][i] ^= temp ^ tmp;
    }

    return;
}

static void AESEncrypt_Auth(BYTE input[16], BYTE output[16])
{
    BYTE i, r;

    for (i=0; i<16; i++)
    {
        state[i & 0x3][i >> 2] = input[i];
    }

    KeyAdd(0);

    for (r = 1; r <= 9; r++)
    {
        ByteSub();

        ShiftRow();

        MixColumn();

        KeyAdd(r);
    }

    ByteSub();

    ShiftRow();

    KeyAdd(r);

    for (i=0; i<16; i++)
    {
        output[i] = state[i & 0x03][i >> 2];
    }

    return;
}

void F2toF5Function(BYTE input[16], BYTE *pOPc,BYTE * output, BYTE mode)    //output 至少需要16个字节
{
    BYTE shift;
    BYTE i;

    shift = 16 - R[mode] / 8;

    for (i=0; i<16; i++)                        //根据R中的不同的内容，对输入的数据进行循环移动
    {
        output[(i + shift) % 16] = input[i];
    }

    for (i=0; i<16; i++)
    {
        output[i] ^= C[16*mode + i];
    }

    AESEncrypt_Auth(output, output);

    for(i=0; i<16; i++)
    {
        output[i] ^= pOPc[i];
    }

    return;
}

void F1Function(BYTE input[16], BYTE *pOPc, BYTE output[16])
{
    BYTE sqnAMFsqnAMF[16];
    BYTE i, shift;

    for (i=0; i<2; i++)
    {
        memcpy(&sqnAMFsqnAMF[i*8], &SQN[0], 6);

        memcpy(&sqnAMFsqnAMF[i*8+6], &AMF[0], 2);
    }

    shift = 16 - R[0] / 8;

    for (i=0; i<16; i++)
    {
        output[(i + shift) % 16] = sqnAMFsqnAMF[i] ^ pOPc[i];
    }

    for (i=0; i<16; i++)
    {
        output[i] ^= input[i];
    }

    for (i=0; i<16; i++)
    {
        output[i] ^= C[i];
    }

    AESEncrypt_Auth(output, output);

    for (i=0; i<16; i++)
    {
        output[i] ^= pOPc[i];  // the first 8 byte of output is just XMAC
    }

    return;
}

/*lint -e438 -e550 -e578*/
unsigned char Milenage(unsigned char *pKI, unsigned char *pOPc, unsigned char *pxRes,unsigned char *pCK, unsigned char *pIK, unsigned char *pKc)
{
    unsigned char i;
    signed char   j;
    unsigned char input[16], output[16], f1input[16];
    unsigned char seq[6];
    /*unsigned char index;*/

    Key_Schedule(pKI);

    for(i=0; i<16; i++)
    {
        input[i] = Rand[i] ^ pOPc[i];                   /*计算出随机数和OPc的异或结果*/
    }

    AESEncrypt_Auth(input, input);                   /*AES计算,得到F1到F5的公用输入参数*/

    memcpy(f1input, input, 16);             /*保存了F1的输入参数*/

    for(i=0; i<16; i++)                             /*经过AES计算的结果和OPc进行异或*/
    {
        input[i] = input[i] ^ pOPc[i];                  /*input内保存了F2到F5的输入参数*/
    }

    F2toF5Function(input, pOPc, output, D_F2_Mode);         /*得到xRES和AK的内容*/

    for(i=0; i<6; i++)                              /*解密SQN*/
    {
        SQN[i] = output[i] ^ SQN[i];
    }

    /*index = (SQN[5] & 0x1F);*/

    for(j=5; j>=0; j--)                             /*得到网络的SEQ的值*/
    {
        seq[j] = SQN[j] >> 5;

        if(j > 0x00)
        {
            seq[j] |= SQN[j-1]<<(8-5);
        }
    }

    memcpy(pxRes, &output[8], 8);

    F1Function(f1input, pOPc, output);                      /*计算xMac*/

    if(memcmp(output, MAC, 8) != 0)
    {
        return AUTH_ERR;
    }

    F2toF5Function(input, pOPc, output, D_F3_Mode);         /*得到CK的内容*/

    memcpy(pCK, output, 16);

    F2toF5Function(input, pOPc, output, D_F4_Mode);         /*得到IK的内容*/

    memcpy(pIK, output, 16);

    for(i=0; i<8; i++)
    {
        pKc[i] = pCK[i] ^ pCK[i+8] ^ pIK[i] ^ pIK[i+8];
    }

    return AUTH_OK;
}
/*lint +e438 +e550 +e578*/

void Milenage2G(unsigned char *pKI, unsigned char *pOPc,unsigned char * pRes, unsigned char *pKc)
{
    BYTE tmp[16], sRes[4];
    BYTE output[64];
    BYTE i;

    Key_Schedule(pKI);

    for(i=0; i<16; i++)
    {
        tmp[i] = Rand[i] ^ pOPc[i];
    }

    AESEncrypt_Auth(tmp, tmp);                           /*得到输入参数Ek的内容*/

    for(i=0; i<16; i++)                             /*经过AES计算的结果和OPc进行异或*/
    {
        tmp[i] = tmp[i] ^ pOPc[i];                  /*tmp内保存了F2到F5的输入参数*/
    }

    F2toF5Function(tmp, pOPc, output, D_F2_Mode);           /*得到sRes的值*/

    memmove(&output[0], &output[8], 8);

    memset(&output[8], 0x00, 8);

    for (i=0; i<4; i++)
    {
        sRes[i] = output[i] ^ output[i + 4] ^ output[i + 8] ^ output[i + 12];
    }

    F2toF5Function(tmp, pOPc, &output[0], D_F3_Mode);       /*得到CK的值*/

    F2toF5Function(tmp, pOPc, &output[16], D_F4_Mode);  /*得到IK的值*/

    for (i=0; i<8; i++)
    {
        tmp[i] = output[i] ^ output[i+8] ^ output[16+i] ^ output[16+i+8];
    }

    memcpy(pRes, sRes, 4);

    memcpy(pKc, tmp, 8);

    return;
}

#endif  /*end of (FEATURE_VSIM == FEATURE_ON)*/

/*lint +e701 +e702 +e732 +e734 +e713 +e737 +e734*/

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



