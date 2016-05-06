#ifdef __cplusplus
    extern "C" {
#endif

#define MAX_FILE_NUM            32
#define MAX_FILE_NAME_LEN       256

#define BUF_LEN_16  16
#define BUF_LEN_32  32
#define BUF_LEN_64  64
#define BUF_LEN_128 128
#define BUF_LEN_256 256
#define BUF_LEN_512 512
#define BUF_LEN_1K  1024

#define FILE_PERM_777   (S_IRWXU | S_IRWXG | S_IRWXO)
#define FILE_PERM_755   (S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)

typedef enum
{
    E_PACK_TAR = 0,     /* 打成tar包，不压缩 */
    E_PACK_ZIP = 1,     /* 压缩 */
    E_PACK_MOVE = 2,    /* 拷贝到指定位置 */
}E_PACK_TYPE;

void pack_files(int argc, const char**input_names, const char* output_path, char *file_prefix, char*output_name, int compress, int keep_parent);

void tar_zip_files(int name_count, const char**input_names, char*output_name, int keep_parent);

#ifdef __cplusplus
}
#endif

