#ifndef SM_ALGORITHM_HEADER_2008_10_
#define SM_ALGORITHM_HEADER_2008_10_

// ----------------------------------------------------------------
// 常量定义
#define SKEY_LEN			(128/8)	// 对称加密的密钥长度，字节单位
#define BLOCK_LEN_BYTE		(128/8)	// 分组长度128 bit
#define BLOCK_LEN_BIT		128


#ifndef SERVER_VER_		// 服务器版本不使用
	#define ECC_KEY_LEN			(192/8)	// 字节单位，32字节，192 bit ECC
#endif	// SERVER_VER_


/*
	相当于是调用g_loisNoise.Do();
*/
#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif
int NoiseDo();



/**************** 语音加解密初始化函数 ****************************
   参数：
   [IN]init_key，加密/解密的密钥指针，必须指向长度为SKEY_LEN的缓冲区
   [IN]outgoing_call，表示本次密话中终端是否是主叫，1为主叫，0为被叫。

   返回值：
   返回值为0表示初始化成功
******************************************************************/

int init_voice(const unsigned char *init_key,
		unsigned long outgoing_call);





/**************** 语音加密函数 ************************************
   参数：
   [IN] input_data：输入参数，待加密数据的指针；
   [OUT]output_data：输出参数，加密后输出数据的指针；
   [IN] input_len：输入参数，待加密数据的长度，以bit为单位；
   [OUT]output_len：输出参数，加密后数据的长度，以bit为单位。

   返回值：
   返回值为0表示加密成功
******************************************************************/

int encrypt_voice(const unsigned char *input_data,
		unsigned char *output_data,
		unsigned long input_len,
		unsigned long *output_len);





/**************** 语音解密函数 ************************************
   参数：
   [IN] input_data：输入参数，待解密数据的指针；
   [OUT]output_data：输出参数，解密后输出数据的指针；
   [IN] input_len：输入参数，待解密数据的长度，以bit为单位；
   [OUT]output_len：输出参数，解密后数据的长度，以bit为单位。

   返回值：
   返回值为0表示解密成功
******************************************************************/

int decrypt_voice(const unsigned char *input_data,
		unsigned char *output_data,
		unsigned long input_len,
		unsigned long *output_len);




#ifndef SERVER_VER_		// 服务器版本不使用

/**************** ECC初始化函数 ***********************************
   功能：
   初始化ECC参量，在系统初始化时调用一次，完成预计算
   返回值：
   初始化成功返回1；否则返回0
******************************************************************/

int ECC_Init(void);





/**************** ECC公私钥对生成函数 *****************************
   参数：
   [OUT]priv_key，私钥空间的地址，该空间大于等于ECC_KEY_LEN字节，输出时该空间内存储私钥；
   [OUT]pub_key，公钥坐标的地址，该空间应该大于等于(2*ECC_KEY_LEN+1)个字节，输出时该空间内存储公钥

   返回值：
   成功返回1；否则返回0
******************************************************************/

int ecc192_genkey(unsigned char *priv_key,
		unsigned char *pub_key);





/**************** ECC公钥加密函数 *********************************
   功能：
   使用公钥加密数据（利用KMC公钥对待发送至KMC的消息进行加密）

   参数：
   [OUT]pout，输出密文空间的地址
   [IN] lenout，密文缓冲区的长度
   [IN] pin，明文空间的地址
   [IN] len，明文的长度
   [IN] pub_key，公钥

   返回值：
   成功时返回密文的长度；失败时返回负数
******************************************************************/

int ecc192_encrypt(unsigned char * pout,
		int lenout,
		const unsigned char * pin,
		int len,
		const unsigned char * pub_key);





/**************** ECC私钥解密函数 *********************************
   功能：
   使用私钥解密（利用终端临时私钥对来自KMC的消息进行解密获得会话密钥Ks）

   参数：
   [OUT]pout，输出明文空间的地址
   [IN] lenout, 明文缓冲区的长度
   [IN] pin，密文空间的地址
   [IN] len，密文的长度
   [IN] priv_key，私钥地址

   返回值：
   成功时返回明文的长度；失败时返回负数
******************************************************************/

int ecc192_decrypt(unsigned char * pout,
		int lenout,
		const unsigned char * pin,
		int len,
		const unsigned char * priv_key);





/**************** ECC公钥签名验证函数 *****************************

   功能：
   使用公钥验证签名（利用KMC公钥，对来自KMC的消息进行签名验证）

   参数：
   [IN]pub _key，公钥空间地址
   [IN]in，待验证签名数据的地址
   [IN]in_len，待验证签名数据的长度
   [IN]sign，签名值
   [IN]sign_len，签名值的长度

   返回值：
   成功时返回1；失败时返回0；
******************************************************************/

int ecc192_verify(const unsigned char * pub_key,
		const unsigned char * in,
		int in_len,
		const unsigned char * sign,
		int sign_len);


#endif // SERVER_VER_服务器版本不使用

#ifdef __cplusplus
#if __cplusplus
		}
#endif
#endif

#endif // SM_ALGORITHM_HEADER_2008_10_