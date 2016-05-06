
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<zlib.h>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/time.h>
#include<time.h>
#include<pwd.h>
#include<errno.h>

#include "tarzip.h"
//#include "utils.h"

#define HEADERNUM      512
#define CHECKSUMAPPEND 256
#define NAMELEN        100
#define FILEMODE       8
#define UID            8
#define GID            8
#define FILESIZE       12
#define UNIXTIME       12
#define CHECKSUM       8

 /*tar file header struct */
typedef struct tag_header
{               /* byte offset */
  char name[NAMELEN];       /*   0 */
  char mode[FILEMODE];      /* 100 */
  char uid[UID];            /* 108 */
  char gid[GID];            /* 116 */
  char size[FILESIZE];      /* 124 */
  char mtime[UNIXTIME];     /* 136 */
  char chksum[CHECKSUM];    /* 148 */
  char typeflag;            /* 156 */
  char linkname[100];       /* 157 */
  char magic[6];            /* 257 */
  char version[2];          /* 263 */
  char uname[32];           /* 265 */
  char gname[32];           /* 297 */
  char devmajor[8];         /* 329 */
  char devminor[8];         /* 337 */
  char prefix[155];         /* 345 */
  char padding[12];         /* 500 */
                            /* 512 */
}header;

/*tar file header mode permissions data*/
static const char file_mode[]={0x31,0x30,0x30,0x36,0x36,0x36,0x20,0};

/*tar file haeder UID and GID date*/
static const char IDBYTE[] = {
0x20,0x20,0x20,0x20,
0x20,0x30,0x20,0x00,
0x20,0x20,0x20,0x20,
0x20,0x30,0x20,0x00,
};

#define log_err_record printf

/*****************************************************************************
 *  Function       : write_header
 *  Description    : write the tar file harder to header struct
 *  Input          : header*hd  the struct to write
 *                   char*file_name the input file name
 *  Output         : None
 *  Return Value   :
 *  Calls          :
 *  Called By      :
 *
 *  History        :
 *  1.Date         :
 *    Author       :
 *    Modification :
 *
 ******************************************************************************/
void write_header(header*hd, const char*file_name, long file_size)
{
    int o = 0,p = 0,q = 0,r = 0,s = 0;
    int name_len = 0;
    int i,j=0;
    char* index = (char*)hd;
    char buf[FILESIZE];
    const char* file_index;
    memset(buf, 0, FILESIZE);
    //file_index = strrchr(file_name, '/') + 1;
    file_index = file_name;
    name_len = strlen(file_index);/* [false alarm]:ÆÁ±ÎFortify´íÎó */

    if (name_len > NAMELEN)
    {
        name_len = NAMELEN;
    }
    for (i = 0; i < name_len; ++i)
    {
        index[i] = file_index[i];/* [false alarm]:ÆÁ±ÎFortify´íÎó */
        o += index[i];
    }

    j += NAMELEN;
    for (i = 0; i < FILEMODE; ++i)
    {
        index[j+i] = file_mode[i];
        p += file_mode[i];
    }
    j+=FILEMODE;

    for (i=0; i < UID+GID; ++i)
    {
        index[j+i] = IDBYTE[i];
        q += IDBYTE[i];
    }
    j += (UID+GID);
    snprintf(buf, FILESIZE, "%o", (unsigned int)file_size);
    for (i=0; i < FILESIZE; ++i)
    {
        index[i+j] = buf[i];
        r += buf[i];
    }
    j += (FILESIZE+UNIXTIME);

    o += (p+q+r+CHECKSUMAPPEND);
    snprintf(buf,CHECKSUM,"%o",o);
    for (i=0; i < CHECKSUM; ++i)
    {
        index[j+i] = buf[i];
    }

}

/*****************************************************************************
 *  Function       : write_zip_content
 *  Description    : write file content to tar zip file
 *  Input          : gzFile*hd  the output file struct
 *                   char*file_name the input file name
 *  Output         : None
 *  Return Value   :
 *  Calls          :
 *  Called By      :
 *
 *  History        :
 *  1.Date         :
 *    Author       :
 *    Modification :
 *
 ******************************************************************************/
void write_zip_content(gzFile fd,const char* file_name,long file_size)
{
    char buf[HEADERNUM];
    FILE *in = fopen(file_name, "r");
    while (file_size > 0)
    {
        memset(buf, 0, HEADERNUM);
        fread(buf, HEADERNUM, 1, in);
        gzwrite(fd, buf, HEADERNUM);
        file_size -= HEADERNUM;
    }

    fclose(in);
}

/*****************************************************************************
 *  Function       : write_content
 *  Description    : write file content to tar file
 *  Input          : FILE*hd  the output file struct
 *                   char*file_name the input file name
 *  Output         : None
 *  Return Value   :
 *  Calls          :
 *  Called By      :
 *
 *  History        :
 *  1.Date         :
 *    Author       :
 *    Modification :
 *
 ******************************************************************************/
void write_content(FILE* fd,const char* file_name,long file_size)
{
    char buf[HEADERNUM];
    FILE *in = fopen(file_name, "r");
    while (file_size > 0)
    {
        memset(buf, 0, HEADERNUM);
        fread(buf, HEADERNUM, 1, in);
        fwrite(buf, HEADERNUM, 1, fd);
        file_size -= HEADERNUM;
    }

    fclose(in);
}

/*****************************************************************************
 *  Function       : tar_zip_dir_recursive
 *  Description    : tar dir recusively
 *  Input          : gzFile* out   --  opened fd
 *                   char* dirname --  dir path ,absolute path
 *  Output         : None
 ******************************************************************************/
static void tar_zip_dir_recursive(gzFile out, const char * dirname, const char * parent)
{
    DIR *dp;
    struct dirent * dirp;
    char output_file_name_buf[MAX_FILE_NAME_LEN] = {0};
    char* ptr = NULL;
    if ((dp = opendir(dirname)) == NULL)
    {
        return;
    }
    memset(output_file_name_buf, 0, MAX_FILE_NAME_LEN);
    strcpy(output_file_name_buf, dirname);
    ptr = output_file_name_buf + strlen(output_file_name_buf);
    if (*(ptr - 1) != '/')
    {
        *ptr++ = '/';
        *ptr = 0;
    }
    while ((dirp = readdir(dp)) != NULL)
    {
        if (strcmp(dirp->d_name,".")==0 || strcmp(dirp->d_name,"..") == 0)
        {
            continue;
        }
        strcpy(ptr, dirp->d_name);/* [false alarm]:ÆÁ±ÎFortify´íÎó */

        //printf("tar file : %s\n",output_file_name_buf);
        struct stat tmpbuf;
        if (lstat(output_file_name_buf,&tmpbuf) < 0)
        {
            continue;
        }
        if (S_ISREG(tmpbuf.st_mode))
        {
            header t;
            memset(&t, 0x0, sizeof(t));
            if (parent)
            {
                char szfilename[NAMELEN] = {0};
                snprintf(szfilename, NAMELEN, "%s/%s", parent, dirp->d_name);/* [false alarm]:ÆÁ±ÎFortify´íÎó */
                //printf("tar filename:%s\n", szfilename);
                write_header(&t, szfilename, tmpbuf.st_size);
            }
            else
            {
                write_header(&t, dirp->d_name, tmpbuf.st_size);
            }
            gzwrite(out, &t, sizeof(header));
            write_zip_content(out, output_file_name_buf,tmpbuf.st_size);/* [false alarm]:ÆÁ±ÎFortify´íÎó */
        }
        else if (S_ISDIR(tmpbuf.st_mode))
        {
            char szpath[NAMELEN] = {0};
            strncpy(szpath, dirp->d_name, NAMELEN - 1);
            if (parent)
            {
                snprintf(szpath, NAMELEN - 1, "%s/%s", parent, dirp->d_name);/* [false alarm]:ÆÁ±ÎFortify´íÎó */
                tar_zip_dir_recursive(out, output_file_name_buf, szpath); /* [false alarm]:ÆÁ±ÎFortify´íÎó */
            }
            else
            {
                tar_zip_dir_recursive(out, output_file_name_buf, NULL);/* [false alarm]:ÆÁ±ÎFortify´íÎó */
            }
        }
    }
    closedir(dp);
}

/*****************************************************************************
 *  Function       : tar_zip_files
 *  Description    : tar and zip input files to output file
 *  Input          : char**input_names  iput files name array ,absolute path
 *                   char*output_name output file name ,absolute path
 *  Output         : None
 ******************************************************************************/
void tar_zip_files(int name_count, const char**input_names, char*output_name, int keep_parent)
{
    //int name_count = 5;
    gzFile out = NULL;
    if (output_name)
    {
        out = gzopen(output_name, "w");/* [false alarm]:ÆÁ±ÎFortify´íÎó */
    }
    if(!out)
    {
        return;
    }
    struct passwd * p = getpwnam("system");
    if (p)
    {
        chown(output_name, p->pw_uid, p->pw_gid); /* [false alarm]:ÆÁ±ÎFortify´íÎó */
    }
    const char**index = input_names;
    header t;
    int i;
    for (i=0; i < name_count; ++i)
    {
        if (*index == NULL)
        {
            ++index;
            continue;
        }
        struct stat buf;
        if (lstat(*index,&buf) < 0)
        {
            ++index;
            continue;
        }
        if (S_ISREG(buf.st_mode))
        {
            header t;
            memset(&t, 0x0, sizeof(t));
            write_header(&t, strrchr(*index, '/') + 1, buf.st_size);
            gzwrite(out, &t, sizeof(header));
            write_zip_content(out, *index, buf.st_size); /* [false alarm]:ÆÁ±ÎFortify´íÎó */
        }
        else if (S_ISDIR(buf.st_mode))
        {
            if (keep_parent)
            {
                char * p = NULL;
                char szTmp[NAMELEN] = {0};
                strncpy(szTmp, *index, NAMELEN - 1);
                p = szTmp + strlen(szTmp);
                if (*(--p) == '/')
                {
                    *p = '\0';
                }
                p = strrchr(szTmp, '/');
                //printf("%s, keep parent=%s\n", __FUNCTION__, p + 1);
                tar_zip_dir_recursive(out, *index, p + 1);
            }
            else
            {
                tar_zip_dir_recursive(out, *index, NULL); /* [false alarm]:ÆÁ±ÎFortify´íÎó */
            }
        }
        ++index;
    }
    memset(&t, 0x0, sizeof(t));
    gzwrite(out, &t, sizeof(header));
    gzclose(out); /* [false alarm]:ÆÁ±ÎFortify´íÎó */
}


