#include <osl_types.h>
#include <osl_bio.h>
#include <osl_cache.h>
#include <osl_malloc.h>
#include <mdrv_public.h>
#include <mdrv_cipher.h>
#include <hi_cipher.h>
#include <bsp_cipher.h>
#include <bsp_om.h>
#include "securec.h"
#include "kdf_balong.h"

/* Here, we suppose that type int take 4 bytes */

#define KDF_TEST_PRINT(fmt, ...)  bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_CIPHER, "[CIPHER]: <%s> "fmt"\n", __FUNCTION__, ##__VA_ARGS__)

extern struct cipher_ctl cipher_module_ctl;/* reg base is needed */
static unsigned char key_length_table[CIPHER_KEY_LEN_BUTTOM] = {16, 24, 32};

#define KDF_TEST_SHA_KEY_1_LEN 32
static unsigned char GoldenKey1[KDF_TEST_SHA_KEY_1_LEN] =
{
	0xbd, 0xef, 0x4e, 0xd7, 0x1a, 0x1d, 0x3a, 0x15, 
	0x00, 0x90, 0x4d, 0x83, 0xa5, 0xe8, 0x32, 0xf7, 
	0xe3, 0xe0, 0xfb, 0x1c, 0x43, 0x07, 0xcd, 0x94, 
	0xc6, 0xe6, 0x2d, 0x6a, 0x63, 0x7b, 0x76, 0x41 
};
#define KDF_TEST_SHA_S_1_LEN 7
static unsigned char GoldenS1[KDF_TEST_SHA_S_1_LEN] = 
{
    0x15,0x05,0x00,0x01,0x02,0x00,0x01
};
#define KDF_DESTKEY_LENGTH    16
static unsigned char GoldenResult1[KDF_DESTKEY_LENGTH] = 
{
    0xf8,0xc0,0x2a,0x2f,0x03,0x11,0x02,0x2f, 
    0x8d,0x37,0xec,0xe9,0xf2,0x0c,0x07,0x11
};

static int memcmp_ext(const void* mem1,const void* mem2,int size)
{
	int i = 0;

	for(i = 0; i < size; i++)
	{
		if(*((char*)mem1+i) != *((char*)mem2+i))
		{
			KDF_TEST_PRINT("diff_pos:%d,addr1(0x%x):%x,addr2(0x%x):%x\n",i,(int)((char*)mem1+i),(int)*((char*)mem1+i),(int)((char*)mem2+i),(int)*((char*)mem2+i),0);
			return i;
		}
	}
	return 0;
}

static void memcpy_key(const unsigned char * key_addr, int key_len, int key_idx)
{
	int i;
	unsigned int val;
	void * key_dst = (void *)((unsigned int)cipher_module_ctl.reg_virt_base + 
						HI_KEY_RAM_OFFSET + key_idx * KDF_SHA_KEY_MAX_LEN);

	for(i = 0; i < key_len / sizeof(unsigned int); i++, key_dst += sizeof(unsigned int))
	{
		val = ((unsigned int)key_addr[sizeof(unsigned int) * i + 0]) << 24 |
			  ((unsigned int)key_addr[sizeof(unsigned int) * i + 1]) << 16 |
			  ((unsigned int)key_addr[sizeof(unsigned int) * i + 2]) << 8  |
			  ((unsigned int)key_addr[sizeof(unsigned int) * i + 3]) << 0;
		writel(val, (unsigned long)key_dst);
	}
	if((key_len % sizeof(unsigned int)) == 1)
    {
		val = ((unsigned int)key_addr[sizeof(unsigned int) * i + 0]) << 24;
		writel(val, (unsigned long)key_dst);
	}
	if((key_len % sizeof(unsigned int)) == 2)
	{
		val = ((unsigned int)key_addr[sizeof(unsigned int) * i + 0]) << 24 |
			  ((unsigned int)key_addr[sizeof(unsigned int) * i + 1]) << 16;
		writel(val, (unsigned long)key_dst);
	}
	if((key_len % sizeof(unsigned int)) == 3)
	{
		val = ((unsigned int)key_addr[sizeof(unsigned int) * i + 0]) << 24 |
			  ((unsigned int)key_addr[sizeof(unsigned int) * i + 1]) << 16 |
			  ((unsigned int)key_addr[sizeof(unsigned int) * i + 2]) << 8;
		writel(val, (unsigned long)key_dst);
	}
}

/*
 * OPS :         KDF_OPS_KEY_READ
 * SHA_KEY_SRC : SHA_KEY_SRC_DDR
 */
int kdf_test_read(unsigned int idx, CIPHER_KEY_LEN_E len)
{

	unsigned char *src_key = osl_cachedma_malloc(KDF_SHA_KEY_MAX_LEN);
	unsigned char *result_key = osl_cachedma_malloc(KDF_SHA_KEY_MAX_LEN);
	
	int i;
	int ret = 0;

	memset_s((void *)src_key, KDF_SHA_KEY_MAX_LEN, 0, KDF_SHA_KEY_MAX_LEN);
	
	for(i = 0; i < KDF_SHA_KEY_MAX_LEN; i++)
		src_key[i] = i;

	if(mdrv_cipher_enable())
	{
		KDF_TEST_PRINT("ERR: fail to open clk\n");
		return MDRV_ERROR;
	}
	memcpy_key(src_key, (int)key_length_table[len], idx);

	memset_s((void *)result_key, KDF_SHA_KEY_MAX_LEN, 0, KDF_SHA_KEY_MAX_LEN);
	ret = mdrv_cipher_read_key(result_key,idx,key_length_table[len] - 1);
	if(ret)
	{
		KDF_TEST_PRINT("mdrv_cipher_read_key err\n");
		return ret;
	}

	ret = memcmp_ext(src_key, result_key, key_length_table[len]);
	if(ret)
		KDF_TEST_PRINT("bsp_kdf_operate fail ret = %d\n", ret);

	osl_cachedma_free(src_key);
	osl_cachedma_free(result_key);

	return ret;
}

int kdf_test_001_001(void)
{
	int i;

	for(i = 0; i < 16; i++)
	{
		if(kdf_test_read(i, CIPHER_KEY_L128))
		{
			KDF_TEST_PRINT("key idx = %d  key len = CIPHER_KEY_L128\n", i);
			return -1;
		}
		if(kdf_test_read(i, CIPHER_KEY_L192))
		{
			KDF_TEST_PRINT("i = %d  j = CIPHER_KEY_L192\n", i);
			return -1;
		}
		if(kdf_test_read(i, CIPHER_KEY_L256))
		{
			KDF_TEST_PRINT("i = %d  j = CIPHER_KEY_L256\n", i);
			return -1;
		}
	}
	return 0;
}

/*
 * OPS :         KDF_OPS_KEY_WRITE
 * SHA_KEY_SRC : SHA_KEY_SRC_DDR
 */
int kdf_test_write(unsigned int idx, CIPHER_KEY_LEN_E len)
{
	unsigned char * src_key = osl_cachedma_malloc(KDF_SHA_KEY_MAX_LEN);
	void * dst_key = cipher_module_ctl.reg_virt_base + HI_KEY_RAM_OFFSET + KDF_SHA_KEY_MAX_LEN * idx;
	int i;
	int ret = 0;

	for(i = 0; i < KDF_SHA_KEY_MAX_LEN; i++)
		src_key[i] = i;

	ret = mdrv_cipher_write_key(idx, src_key, key_length_table[len] - 1);
	if(ret)
	{
		KDF_TEST_PRINT("mdrv_cipher_write_key fail ret = %d\n", ret);
		return ret;
	}

	for(i = 0; i < (int)key_length_table[len] / 4; i++)
		writel_relaxed(CIPHER_BSWAP32(readl((unsigned long)(src_key + i * 4))), (unsigned long)(src_key + i * 4));
	ret = memcmp_ext(src_key, dst_key, key_length_table[len]);
	if(ret)
		KDF_TEST_PRINT("bsp_kdf_operate fail ret = %d\n", ret);

	return ret;
}

int kdf_test_002_001(void)
{
	int i;

	for(i = 0; i < 16; i++)
	{
		if(kdf_test_write(i, CIPHER_KEY_L128))
		{
			KDF_TEST_PRINT("key idx = %d  key len = CIPHER_KEY_L128\n", i);
			return -1;
		}
		if(kdf_test_write(i, CIPHER_KEY_L192))
		{
			KDF_TEST_PRINT("i = %d  j = CIPHER_KEY_L192\n", i);
			return -1;
		}
		if(kdf_test_write(i, CIPHER_KEY_L256))
		{
			KDF_TEST_PRINT("i = %d  j = CIPHER_KEY_L256\n", i);
			return -1;
		}
	}
	return 0;
}

/*
 * OPS :         KDF_OPS_KEY_MAKE
 * SHA_KEY_SRC : SHA_KEY_SRC_KEYRAM
 * SHA_S_SRC :   SHA_S_SRC_KEYRAM
 */
int kdf_test_003_001(void)
{
	unsigned char result_key[KDF_SHA_KEY_MAX_LEN] = {0};
	KEY_CONFIG_INFO_S pstKeyCfgInfo = {0};
	S_CONFIG_INFO_S   pstSCfgInfo = {0};
	KEY_MAKE_S pstKeyMake = {0};
	CIPHER_KEY_LEN_E tmp_len;
	int ret = 0;

	pstKeyCfgInfo.enShaKeySource = SHA_KEY_SOURCE_KEYRAM;
	pstKeyCfgInfo.pKeySourceAddr = NULL;
	pstKeyCfgInfo.u32ShaKeyIndex = 0;
	pstSCfgInfo.enShaSSource  = SHA_S_SOURCE_KEYRAM;
	pstSCfgInfo.u32ShaSIndex  = 1;
	pstSCfgInfo.u32ShaSLength = KDF_TEST_SHA_S_1_LEN;
	pstSCfgInfo.pSAddr        = NULL;
	pstKeyMake.enKeyOutput       = CIPHER_KEY_OUTPUT;
	pstKeyMake.stKeyGet.enKeyLen = CIPHER_KEY_L128;
	pstKeyMake.stKeyGet.pKeyAddr = result_key;
	pstKeyMake.stKeyGet.penOutKeyLen = &tmp_len;

	memcpy_key(GoldenKey1, KDF_TEST_SHA_KEY_1_LEN, (int)pstKeyCfgInfo.u32ShaKeyIndex);
	memcpy_key(GoldenS1, KDF_TEST_SHA_S_1_LEN, (int)pstSCfgInfo.u32ShaSIndex);

	ret = mdrv_cipher_gen_key(&pstKeyCfgInfo, &pstSCfgInfo, 2, &pstKeyMake);
	if(ret)
	{
		KDF_TEST_PRINT("bsp_kdf_operate fail ret = %d\n", ret);
		return ret;
	}

	ret = memcmp_ext(result_key, GoldenResult1, KDF_SHA_KEY_MAX_LEN - KDF_DESTKEY_LENGTH);
	if(ret)
	{
		KDF_TEST_PRINT("bsp_kdf_operate fail ret = %d\n", ret);
	}
	return ret;
}

/*
 * OPS :         KDF_OPS_KEY_MAKE
 * SHA_KEY_SRC : SHA_KEY_SRC_KEYRAM
 * SHA_S_SRC :   SHA_S_SRC_DDR
 */
int kdf_test_003_002(void)
{
	KEY_CONFIG_INFO_S pstKeyCfgInfo = {0};
	S_CONFIG_INFO_S   pstSCfgInfo = {0};
	KEY_MAKE_S pstKeyMake = {0};
	unsigned char result_key[KDF_SHA_KEY_MAX_LEN] = {0};
	CIPHER_KEY_LEN_E tmp_len;
	int ret = 0;

	pstKeyCfgInfo.enShaKeySource = SHA_KEY_SOURCE_KEYRAM;
	pstKeyCfgInfo.pKeySourceAddr = NULL;
	pstKeyCfgInfo.u32ShaKeyIndex = 0;
	pstSCfgInfo.enShaSSource  = SHA_S_SOURCE_DDR;
	pstSCfgInfo.u32ShaSIndex  = 1;
	pstSCfgInfo.u32ShaSLength = KDF_TEST_SHA_S_1_LEN;
	pstSCfgInfo.pSAddr        = GoldenS1;
	pstKeyMake.enKeyOutput       = CIPHER_KEY_OUTPUT;
	pstKeyMake.stKeyGet.enKeyLen = CIPHER_KEY_L128;
	pstKeyMake.stKeyGet.pKeyAddr = result_key;
	pstKeyMake.stKeyGet.penOutKeyLen = &tmp_len;

	memcpy_key(GoldenKey1, KDF_TEST_SHA_KEY_1_LEN, (int)pstKeyCfgInfo.u32ShaKeyIndex);

	ret = mdrv_cipher_gen_key(&pstKeyCfgInfo, &pstSCfgInfo, 2, &pstKeyMake);
	if(ret)
	{
		KDF_TEST_PRINT("bsp_kdf_operate fail ret = %d\n", ret);
		return ret;
	}

	ret = memcmp_ext(result_key, GoldenResult1, KDF_DESTKEY_LENGTH);
	if(ret)
	{
		KDF_TEST_PRINT("bsp_kdf_operate fail ret = %d\n", ret);
	}
	return ret;
}

/*
 * OPS :         KDF_OPS_KEY_MAKE
 * SHA_KEY_SRC : SHA_KEY_SRC_DDR
 * SHA_S_SRC :   SHA_S_SRC_KEYRAM
 */
int kdf_test_003_003(void)
{
	KEY_CONFIG_INFO_S pstKeyCfgInfo = {0};
	S_CONFIG_INFO_S   pstSCfgInfo = {0};
	KEY_MAKE_S pstKeyMake = {0};
	unsigned char result_key[KDF_SHA_KEY_MAX_LEN] = {0};
	CIPHER_KEY_LEN_E tmp_len;
	int ret = 0;

	pstKeyCfgInfo.enShaKeySource = SHA_KEY_SOURCE_DDR;
	pstKeyCfgInfo.pKeySourceAddr = GoldenKey1;
	pstKeyCfgInfo.u32ShaKeyIndex = 0;
	pstSCfgInfo.enShaSSource  = SHA_S_SOURCE_KEYRAM;
	pstSCfgInfo.u32ShaSIndex  = 1;
	pstSCfgInfo.u32ShaSLength = KDF_TEST_SHA_S_1_LEN;
	pstSCfgInfo.pSAddr        = NULL;
	pstKeyMake.enKeyOutput       = CIPHER_KEY_OUTPUT;
	pstKeyMake.stKeyGet.enKeyLen = CIPHER_KEY_L128;
	pstKeyMake.stKeyGet.pKeyAddr = result_key;
	pstKeyMake.stKeyGet.penOutKeyLen = &tmp_len;

	memcpy_key(GoldenS1, KDF_TEST_SHA_S_1_LEN, (int)pstSCfgInfo.u32ShaSIndex);

	ret = mdrv_cipher_gen_key(&pstKeyCfgInfo, &pstSCfgInfo, 2, &pstKeyMake);
	if(ret)
	{
		KDF_TEST_PRINT("bsp_kdf_operate fail ret = %d\n", ret);
		return ret;
	}

	ret = memcmp_ext(result_key, GoldenResult1, KDF_SHA_KEY_MAX_LEN - KDF_DESTKEY_LENGTH);
	if(ret)
	{
		KDF_TEST_PRINT("bsp_kdf_operate fail ret = %d\n", ret);
	}
	return ret;
}

/*
 * OPS :         KDF_OPS_KEY_MAKE
 * SHA_KEY_SRC : SHA_KEY_SRC_DDR
 * SHA_S_SRC :   SHA_S_SRC_DDR
 */
int kdf_test_003_004(void)
{
	KEY_CONFIG_INFO_S pstKeyCfgInfo = {0};
	S_CONFIG_INFO_S   pstSCfgInfo = {0};
	KEY_MAKE_S pstKeyMake = {0};
	unsigned char result_key[KDF_SHA_KEY_MAX_LEN] = {0};
	CIPHER_KEY_LEN_E tmp_len;
	int ret = 0;

	pstKeyCfgInfo.enShaKeySource = SHA_KEY_SOURCE_DDR;
	pstKeyCfgInfo.pKeySourceAddr = GoldenKey1;
	pstKeyCfgInfo.u32ShaKeyIndex = 0;
	pstSCfgInfo.enShaSSource  = SHA_S_SOURCE_DDR;
	pstSCfgInfo.u32ShaSIndex  = 1;
	pstSCfgInfo.u32ShaSLength = KDF_TEST_SHA_S_1_LEN;
	pstSCfgInfo.pSAddr        = GoldenS1;
	pstKeyMake.enKeyOutput       = CIPHER_KEY_OUTPUT;
	pstKeyMake.stKeyGet.enKeyLen = CIPHER_KEY_L128;
	pstKeyMake.stKeyGet.pKeyAddr = result_key;
	pstKeyMake.stKeyGet.penOutKeyLen = &tmp_len;

	ret = mdrv_cipher_gen_key(&pstKeyCfgInfo, &pstSCfgInfo, 2, &pstKeyMake);
	if(ret)
	{
		KDF_TEST_PRINT("bsp_kdf_operate fail ret = %d\n", ret);
		return ret;
	}

	ret = memcmp_ext(result_key, GoldenResult1, KDF_SHA_KEY_MAX_LEN - KDF_DESTKEY_LENGTH);
	if(ret)
	{
		KDF_TEST_PRINT("bsp_kdf_operate fail ret = %d\n", ret);
	}
	return ret;
}

