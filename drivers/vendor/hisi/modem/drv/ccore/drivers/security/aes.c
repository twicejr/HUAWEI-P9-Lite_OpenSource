//#include "config.h"
#include "string.h"
#include "securec.h"
#include "cipher_aes.h"
#include "security_types.h"
//#include "aes_alg.h"

/*lint --e{571, 830} */
int16 crypto_aes_init(crypto_aes *cipher, uint8 keymaterial[32], int16 keybits, int32 mode, uint8 iv[16])
{

	if(cipher == NULL)
	{
		return BAD_CIPHER;
	}
	if(keybits == 128 || keybits == 192 || keybits ==  256)
	{
		//null
	}
	else
	{
		return BAD_CIPHER;

	}
	if(mode == MODE_ECB || mode == MODE_CBC || mode == MODE_CFB1)
	{
		cipher->mode = (uint32)mode;
	}
	else
	{
		return BAD_CIPHER_MODE;
	}
	if(keymaterial == NULL)
	{
		return BAD_CIPHER;
	}
	if(iv != NULL)
	{
		(void)memcpy_s(cipher->iv, 16, iv, 16);
	}

	else
	{
		(void)memset_s(cipher->iv, MAX_IV_SIZE, 0, MAX_IV_SIZE);
	}

	(void)crypto_aes_set_key(&(cipher->aes_ctx), keymaterial, (uint32)keybits, 0);



	return SUCCESS;

}

/* encrypt input data with block. the block length must is muitiple of 128 bits. */
int16 crypto_aes_encrypt_block(crypto_aes *cipher, uint8 *input, int32 inputlen, uint8 *output, int32 *outputlen )
{
	int32 i, k, t;
	int32 num_blocks;
	uint8 block[16], *iv;

	if (cipher == NULL )
	{
		return BAD_CIPHER_STATE;
	}
	if (input == NULL || inputlen <= 0)
	{
		return 0; /* nothing to do */
	}

	num_blocks = inputlen/16;

	switch (cipher->mode)
	{
		case MODE_ECB:
			for (i = num_blocks; i > 0; i--)
			{
				crypto_aes_encrypt(&(cipher->aes_ctx), input, output);
				input += 16;
				output += 16;
			}
			break;

		case MODE_CBC:
			iv = cipher->iv;
			for (i = num_blocks; i > 0; i--)
			{
				((uint32*)block)[0] = ((uint32*)input)[0] ^ ((uint32*)iv)[0];
				((uint32*)block)[1] = ((uint32*)input)[1] ^ ((uint32*)iv)[1];
				((uint32*)block)[2] = ((uint32*)input)[2] ^ ((uint32*)iv)[2];
				((uint32*)block)[3] = ((uint32*)input)[3] ^ ((uint32*)iv)[3];
				crypto_aes_encrypt(&(cipher->aes_ctx), block, output);
				iv = output;
				input += 16;
				output += 16;
			}
			break;
		case MODE_CFB1:
			iv = cipher->iv;
			for (i = num_blocks; i > 0; i--)
			{
				(void)memcpy_s(output, 16, input, 16);
				for (k = 0; k < 128; k++) {
					crypto_aes_encrypt(&(cipher->aes_ctx), iv, block);
					output[(uint32)k >> 3] ^= (block[0] & 0x80U) >> (k & 7);
					for (t = 0; t < 15; t++) {
						iv[t] = (uint8)((iv[t] << 1) | (iv[t + 1] >> 7));
					}
					iv[15] = (uint8)((iv[15] << 1) | ((output[(uint32)k >> 3] >> (7 - (k & 7))) & 1));
				}
				output += 16;
				input += 16;
			}
			break;
		default:
			return BAD_CIPHER_STATE;
	}
	*outputlen = (int32)((uint32)num_blocks <<4) ;
	return SUCCESS;
}

int16 crypto_aes_decrypt_block(crypto_aes *cipher, uint8 *input, int32 inputlen, uint8 *output, int32 *outputlen )
{
	int32 i, k, t;
	int32 num_blocks;
	uint8 block[16], *iv;

	if (cipher == NULL )
	{
		return BAD_CIPHER_STATE;
	}
	if (input == NULL || inputlen <= 0)
	{
		return 0; /* nothing to do */
	}

	num_blocks = inputlen/16;

	switch (cipher->mode)
	{
		case MODE_ECB:
			for (i = num_blocks; i > 0; i--)
			{
				crypto_aes_decrypt(&(cipher->aes_ctx), input, output);
				input += 16;
				output += 16;
			}
			break;

		case MODE_CBC:
			iv = cipher->iv;
			for (i = num_blocks; i > 0; i--)
			{
				crypto_aes_decrypt(&(cipher->aes_ctx), input, block);
				((uint32*)block)[0] ^= ((uint32*)iv)[0];
				((uint32*)block)[1] ^= ((uint32*)iv)[1];
				((uint32*)block)[2] ^= ((uint32*)iv)[2];
				((uint32*)block)[3] ^= ((uint32*)iv)[3];
				(void)memcpy_s(cipher->iv, 16, input, 16);
				(void)memcpy_s(output, 16, block, 16);
				input += 16;
				output += 16;
			}
			break;

		case MODE_CFB1:
			iv = cipher->iv;
			for (i = num_blocks; i > 0; i--)
			{
				(void)memcpy_s(output, 16, input, 16);
				for (k = 0; k < 128; k++)
				{
					crypto_aes_decrypt(&(cipher->aes_ctx), iv, block);
					for (t = 0; t < 15; t++)
					{
						iv[t] = (uint8)((iv[t] << 1) | (iv[t + 1] >> 7));
					}
					iv[15] = (uint8)((iv[15] << 1) | ((input[(uint32)k >> 3] >> (7 - (k & 7))) & 1));
					output[(uint32)k >> 3] ^= (block[0] & 0x80U) >> (k & 7);
				}
				output += 16;
				input += 16;
			}
			break;
	default:
		return BAD_CIPHER_STATE;
	}

	*outputlen = (int32)((uint32)num_blocks <<4) ;
	return SUCCESS;
}


/* encrypt input data with any length. if the input data is not multiple of block, we will padding some data with RFC2040. */
int16 crypto_aes_encrypt_pad(crypto_aes *cipher, uint8 *input, int32 inputlen, uint8 *output, int32 *outputlen )
{
	int32 i,  padLen;
	int32 numBlocks;
	uint8 block[16] = {0}, *iv = NULL;

	if (cipher == NULL)
	{
		return BAD_CIPHER_STATE;
	}
	if (input == NULL || inputlen <= 0)
	{
		return 0; /* nothing to do */
	}

	numBlocks = inputlen/16;

	switch (cipher->mode)
	{
		case MODE_ECB:
			for (i = numBlocks; i > 0; i--)
			{
				crypto_aes_encrypt(&(cipher->aes_ctx), input, output);
				input += 16;
				output += 16;
			}
		padLen = 16 - (inputlen - 16*numBlocks);
		(void)memcpy_s(block,               (size_t)(16 - padLen), input, (size_t)(16 - padLen));
		(void)memset_s(block + 16 - padLen, (size_t)padLen,        padLen, (size_t)padLen);
		crypto_aes_encrypt(&(cipher->aes_ctx), block, output);
		break;

	case MODE_CBC:
		iv = cipher->iv;
		for (i = numBlocks; i > 0; i--)
		{
			((uint32*)block)[0] = ((uint32*)input)[0] ^ ((uint32*)iv)[0];
			((uint32*)block)[1] = ((uint32*)input)[1] ^ ((uint32*)iv)[1];
			((uint32*)block)[2] = ((uint32*)input)[2] ^ ((uint32*)iv)[2];
			((uint32*)block)[3] = ((uint32*)input)[3] ^ ((uint32*)iv)[3];
			crypto_aes_encrypt(&(cipher->aes_ctx), block, output);
			iv = output;
			input += 16;
			output += 16;
		}
		padLen = 16 - (inputlen - 16*numBlocks);
		for (i = 0; i < 16 - padLen; i++)
		{
			block[i] = input[i] ^ iv[i];
		}
		for (i = 16 - padLen; i < 16; i++)
		{
			block[i] = (uint8)padLen ^ iv[i];
		}
		crypto_aes_encrypt(&(cipher->aes_ctx), block, output);
		break;

	default:
		return BAD_CIPHER_STATE;
	}
	*outputlen = 16*(numBlocks + 1);

	return SUCCESS;
}

int16 crypto_aes_decrypt_pad(crypto_aes *cipher, uint8 *input, int32 inputlen, uint8 *output, int32 *outputlen )
{
	int32 i,  padLen;
	int32 numBlocks;
	uint8 block[16]={0};

	if (cipher == NULL )
	{
		return BAD_CIPHER_STATE;
	}
	if (input == NULL || inputlen <= 0)
	{
		return 0; /* nothing to do */
	}
	if (inputlen % 16 != 0) {
		return BAD_DATA;
	}

	numBlocks = inputlen/16;

	switch (cipher->mode)
	{
		case MODE_ECB:
			/* all blocks but last */
			for (i = numBlocks - 1; i > 0; i--)
			{
				crypto_aes_decrypt(&(cipher->aes_ctx), input, output);
				input += 16;
				output += 16;
			}
			/* last block */
			crypto_aes_decrypt(&(cipher->aes_ctx), input, block);
			padLen = block[15];
			if (padLen >= 16)
			{
				return BAD_DATA;
			}
			for (i = 16 - padLen; i < 16; i++)
			{
				if (block[i] != padLen)
				{
					return BAD_DATA;
				}
			}
			(void)memcpy_s(output, (size_t)(16 - padLen), block, (size_t)(16 - padLen));
			break;

	case MODE_CBC:
		/* all blocks but last */
		for (i = numBlocks - 1; i > 0; i--)
		{
			crypto_aes_decrypt(&(cipher->aes_ctx), input, block);
			((uint32*)block)[0] ^= ((uint32*)cipher->iv)[0];
			((uint32*)block)[1] ^= ((uint32*)cipher->iv)[1];
			((uint32*)block)[2] ^= ((uint32*)cipher->iv)[2];
			((uint32*)block)[3] ^= ((uint32*)cipher->iv)[3];
			crypto_aes_decrypt(&(cipher->aes_ctx), input, block);
			(void)memcpy_s(output, 16, block, 16);
			input += 16;
			output += 16;
		}
		/* last block */
		crypto_aes_decrypt(&(cipher->aes_ctx), input, output);
		((uint32*)block)[0] ^= ((uint32*)cipher->iv)[0];
		((uint32*)block)[1] ^= ((uint32*)cipher->iv)[1];
		((uint32*)block)[2] ^= ((uint32*)cipher->iv)[2];
		((uint32*)block)[3] ^= ((uint32*)cipher->iv)[3];
		padLen = block[15];
		if (padLen <= 0 || padLen > 16)
		{
			return BAD_DATA;
		}
		for (i = 16 - padLen; i < 16; i++)
		{
			if (block[i] != padLen)
			{
				return BAD_DATA;
			}
		}
		(void)memcpy_s(output, (size_t)(16 - padLen), block, (size_t)(16 - padLen));
		break;

	default:
		return BAD_CIPHER_STATE;
	}
	*outputlen = 16*numBlocks - padLen;

	return SUCCESS;
}

