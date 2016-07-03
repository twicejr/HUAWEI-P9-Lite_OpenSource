#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_nas_AppVcomDev.h"

//建议这样引用，避免下面用关键字时需要加前缀 testing::
using namespace testing;



class Test_APP_VCOM_Init: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
		g_ulAppVcomDebugFlg = VOS_TRUE;
    }
    void TearDown()
    {

    }
};


TEST_F(Test_APP_VCOM_Init, Test_APP_VCOM_Init_001)
{
    /*参数初始化*/
    VOS_UINT32                          ulRst;

    MOCKER(register_chrdev_region)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(cdev_init)
        .stubs()
        .will(returnValue(0));

    MOCKER(cdev_add)
        .stubs()
        .will(returnValue(0));

	ulRst = APP_VCOM_Init();

    EXPECT_EQ(VOS_OK, ulRst );
    /* 检查调用时, 需要在用例结束位置加上这句 */

	APP_VCOM_FreeMem();
    GlobalMockObject::verify();
}


TEST_F(Test_APP_VCOM_Init, Test_APP_VCOM_Init_002)
{
    /*参数初始化*/
    VOS_UINT32                          ulRst;
    
	MOCKER(register_chrdev_region)
        .stubs()
        .will(returnValue(-1));

    MOCKER(alloc_chrdev_region)
        .stubs()
        .will(returnValue(0));

    MOCKER(cdev_init)
        .stubs()
        .will(returnValue(0));

    MOCKER(cdev_add)
        .stubs()
        .will(returnValue(0));

	ulRst = APP_VCOM_Init();

    EXPECT_EQ(VOS_OK, ulRst );

	APP_VCOM_FreeMem();
    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_APP_VCOM_Init, Test_APP_VCOM_Init_003)
{
    /*参数初始化*/
    VOS_UINT32                          ulRst;
    
	MOCKER(register_chrdev_region)
        .stubs()
        .will(returnValue(-1));
    MOCKER(alloc_chrdev_region)
        .stubs()
        .will(returnValue(-1));

	ulRst = APP_VCOM_Init();

    EXPECT_EQ(VOS_ERROR, ulRst );
    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}



class Test_APP_VCOM_InitSpecCtx: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
		g_ulAppVcomDebugFlg = VOS_TRUE;
   
    }
    void TearDown()
    {

    }
};


TEST_F(Test_APP_VCOM_InitSpecCtx, Test_APP_VCOM_InitSpecCtx_001)
{
    /*参数初始化*/
    VOS_UINT8                          ucDevIndex;

    ucDevIndex = APP_VCOM_DEV_INDEX_BUTT;

    MOCKER(APP_VCOM_GetVcomCtxAddr).expects(never());

	APP_VCOM_InitSpecCtx(ucDevIndex);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}

class Test_APP_VCOM_Open: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
		g_ulAppVcomDebugFlg = VOS_TRUE;
        MOCKER(register_chrdev_region)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(cdev_init)
            .defaults()
            .will(returnValue(0));

        MOCKER(cdev_add)
            .defaults()
            .will(returnValue(0));
    }
    void TearDown()
    {

    }
};


TEST_F(Test_APP_VCOM_Open, Test_APP_VCOM_Open_001)
{
    /*参数初始化*/
	int                              lRst;
    struct inode* pstInode;
	struct file*  pstFile;
    
	pstInode = (inode*)malloc(sizeof(inode));
	pstFile = (file*)malloc(sizeof(file));

	APP_VCOM_Init();

	MOCKER(imajor)
        .stubs()
        .will(returnValue(3));

    lRst = APP_VCOM_Open(pstInode, pstFile);

    EXPECT_EQ(VOS_ERROR, lRst);
	free(pstInode);
	free(pstFile);

	APP_VCOM_FreeMem();
    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_APP_VCOM_Open, Test_APP_VCOM_Open_002)
{
    /*参数初始化*/
	int                               lRst;
    struct inode*                     pstInode;
	struct file*                      pstFile;
    APP_VCOM_DEV_CTX_STRU            *pstVcomCtx;

	pstVcomCtx = APP_VCOM_GetVcomCtxAddr(0);

    pstVcomCtx->pstAppVcomDevEntity = VOS_NULL_PTR;

	pstInode = (inode*)malloc(sizeof(inode));
	pstFile = (file*)malloc(sizeof(file));

	MOCKER(imajor)
        .stubs()
        .will(returnValue(247));
   
	lRst = APP_VCOM_Open(pstInode, pstFile);

	EXPECT_EQ(VOS_ERROR, lRst);

	free(pstInode);
	free(pstFile);
    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


class Test_APP_VCOM_Poll: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        g_ulAppVcomDebugFlg = VOS_TRUE;
    }
    void TearDown()
    {
    }
};


TEST_F(Test_APP_VCOM_Poll, Test_APP_VCOM_Poll_001)
{
    //参数定义
    int                               mask;
    struct inode*                     node;
    struct file*                      fp;
    char                             *buf       = NULL;
    APP_VCOM_DEV_ENTITY_STRU         *pstVcomDev;
    poll_table_struct                 wait;

    //参数初始化
    pstVcomDev              = (APP_VCOM_DEV_ENTITY_STRU*)malloc(sizeof(APP_VCOM_DEV_ENTITY_STRU));
    pstVcomDev->current_len = 10;

    fp   = (file*)malloc(sizeof(file));
    fp->private_data = pstVcomDev ;

    MOCKER(register_chrdev_region)
        .defaults()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(cdev_init)
        .defaults()
        .will(returnValue(0));

    MOCKER(cdev_add)
        .defaults()
        .will(returnValue(0));

	APP_VCOM_Init();

    //相关全局变量初始化

    //MOCKER操作
    MOCKER(APP_VCOM_GetIndexFromMajorDevId)
        .stubs()
        .will(returnValue(0));

    //调用被测函数
    mask = APP_VCOM_Poll(fp, &wait);

    //执行检查
    EXPECT_EQ(POLLIN|POLLRDNORM, mask);
    free(fp);
    free(pstVcomDev);

	APP_VCOM_FreeMem();

    //检查调用时, 需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


class Test_APP_VCOM_Read: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
		g_ulAppVcomDebugFlg = VOS_TRUE;

        MOCKER(register_chrdev_region)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(cdev_init)
            .defaults()
            .will(returnValue(0));

        MOCKER(cdev_add)
            .defaults()
            .will(returnValue(0));

    }
    void TearDown()
    {

    }
};



TEST_F(Test_APP_VCOM_Read, Test_APP_VCOM_Read_001)
{
    /*参数初始化*/
	int                               lRst;
    struct inode*                     pstInode;
	struct file*                      pstFile;
    char                             *buf       = NULL;
    size_t                            count;
    loff_t                           *ppos;
    APP_VCOM_DEV_ENTITY_STRU       *pstVcomDev;

	pstInode                          = (inode*)malloc(sizeof(inode));
	pstFile                           = (file*)malloc(sizeof(file));
    buf                               = (char*)malloc(100);
    count                             =  100;
    ppos                              = (loff_t*)malloc(sizeof(loff_t));
	pstVcomDev                        = (APP_VCOM_DEV_ENTITY_STRU*)malloc(sizeof(APP_VCOM_DEV_ENTITY_STRU));

	pstFile->private_data = pstVcomDev ;

	APP_VCOM_Init();

	MOCKER(APP_VCOM_GetIndexFromMajorDevId)
        .stubs()
        .will(returnValue((VOS_CHAR)APP_VCOM_MAX_NUM));

	lRst = APP_VCOM_Read(pstFile, buf, count, ppos);

	EXPECT_EQ(APP_VCOM_ERROR, lRst);
	free(pstInode);
	free(pstFile);
	free(buf);
	free(ppos);
	free(pstVcomDev);

	APP_VCOM_FreeMem();

    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}


TEST_F(Test_APP_VCOM_Read, Test_APP_VCOM_Read_002)
{
	/*参数初始化*/
	int                               lRst;
	struct inode*                     pstInode;
	struct file*                      pstFile;
	char                             *buf       = NULL;
	size_t                            count;
	loff_t                           *ppos;
	APP_VCOM_DEV_ENTITY_STRU         *pstVcomDev;

	pstInode                          = (inode*)malloc(sizeof(inode));
	pstFile                           = (file*)malloc(sizeof(file));
	buf                               = (char*)malloc(100);
	count                             =  100;
	ppos                              = (loff_t*)malloc(sizeof(loff_t));
	pstFile->f_flags                  = 0xffff;
	pstVcomDev                        = (APP_VCOM_DEV_ENTITY_STRU*)malloc(sizeof(APP_VCOM_DEV_ENTITY_STRU));
    pstVcomDev->current_len = 0;
	pstFile->private_data = pstVcomDev ;

	APP_VCOM_Init();

	MOCKER(APP_VCOM_GetIndexFromMajorDevId)
        .stubs()
        .will(returnValue((VOS_CHAR)0));

	lRst = APP_VCOM_Read(pstFile, buf, count, ppos);

	EXPECT_EQ(APP_VCOM_ERROR, lRst);
	free(pstInode);
	free(pstFile);
	free(buf);
	free(ppos);
	free(pstVcomDev);

	APP_VCOM_FreeMem();

	/* 检查调用时, 需要在用例结束位置加上这句 */
	GlobalMockObject::verify();
}


TEST_F(Test_APP_VCOM_Read, Test_APP_VCOM_Read_003)
{
	/*参数初始化*/
	int                               lRst;
	struct inode*                     pstInode;
	struct file*                      pstFile;
	char                             *buf       = NULL;
	size_t                            count;
	loff_t                           *ppos;
	APP_VCOM_DEV_ENTITY_STRU         *pstVcomDev;

	pstInode                          = (inode*)malloc(sizeof(inode));
	pstFile                           = (file*)malloc(sizeof(file));
	buf                               = (char*)malloc(100);
	count                             =  100;
	ppos                              = (loff_t*)malloc(sizeof(loff_t));
	pstFile->f_flags                  = 0xffff;
	pstVcomDev                        = (APP_VCOM_DEV_ENTITY_STRU*)malloc(sizeof(APP_VCOM_DEV_ENTITY_STRU));
    pstVcomDev->current_len = 7;
	pstFile->private_data = pstVcomDev ;

	APP_VCOM_Init();
	MOCKER(APP_VCOM_GetIndexFromMajorDevId)
        .stubs()
        .will(returnValue((VOS_CHAR)0));
    MOCKER(VOS_SmP)
        .stubs()
        .will(returnValue(-1));

	lRst = APP_VCOM_Read(pstFile, buf, count, ppos);

	EXPECT_EQ(APP_VCOM_ERROR, lRst);

	free(pstInode);
	free(pstFile);
	free(buf);
	free(ppos);
	free(pstVcomDev);

	APP_VCOM_FreeMem();
	/* 检查调用时, 需要在用例结束位置加上这句 */
	GlobalMockObject::verify();
}


TEST_F(Test_APP_VCOM_Read, Test_APP_VCOM_Read_004)
{
	/*参数初始化*/
	int                               lRst;
	struct inode*                     pstInode;
	struct file*                      pstFile;
	char                             *buf       = NULL;
	size_t                            count;
	loff_t                           *ppos;
	APP_VCOM_DEV_ENTITY_STRU         *pstVcomDev;

	pstInode                          = (inode*)malloc(sizeof(inode));
	pstFile                           = (file*)malloc(sizeof(file));
	buf                               = (char*)malloc(100);
	count                             =  100;
	ppos                              = (loff_t*)malloc(sizeof(loff_t));

    APP_VCOM_Init();
    pstVcomDev = APP_VCOM_GetAppVcomDevEntity(0);
	pstVcomDev->current_len = 7;

	MOCKER(APP_VCOM_GetIndexFromMajorDevId)
        .stubs()
        .will(returnValue((VOS_CHAR)0));
	MOCKER(VOS_SmP)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));
    MOCKER(copy_to_user)
        .stubs()
        .will(returnValue(1));

	APP_VCOM_Open(pstInode, pstFile);
	lRst = APP_VCOM_Read(pstFile, buf, count, ppos);

	EXPECT_EQ(APP_VCOM_ERROR, lRst);

	free(pstInode);
	free(pstFile);
	free(buf);
	free(ppos);

	APP_VCOM_FreeMem();
	/* 检查调用时, 需要在用例结束位置加上这句 */
	GlobalMockObject::verify();
}


TEST_F(Test_APP_VCOM_Read, Test_APP_VCOM_Read_005)
{
	/*参数初始化*/
	int                               lRst;
	struct inode*                     pstInode;
	struct file*                      pstFile;
	char                             *buf       = NULL;
	size_t                            count;
	loff_t                           *ppos;
	APP_VCOM_DEV_ENTITY_STRU       *pstVcomDev;

	pstInode                          = (inode*)malloc(sizeof(inode));
	pstFile                           = (file*)malloc(sizeof(file));
	buf                               = (char*)malloc(100);
	count                             =  50;
	ppos                              = (loff_t*)malloc(sizeof(loff_t));

    pstFile->f_flags = 0;

    APP_VCOM_Init();
    pstVcomDev = APP_VCOM_GetAppVcomDevEntity(0);
	pstVcomDev->current_len = 100;

	MOCKER(APP_VCOM_GetIndexFromMajorDevId)
        .stubs()
        .will(returnValue((VOS_CHAR)0));
	MOCKER(VOS_SmP)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));
    MOCKER(copy_to_user)
        .stubs()
        .will(returnValue(0));

	APP_VCOM_Open(pstInode, pstFile);
	lRst = APP_VCOM_Read(pstFile, buf, count, ppos);

	EXPECT_EQ(count, lRst);

	free(pstInode);
	free(pstFile);
	free(buf);
	free(ppos);

	APP_VCOM_FreeMem();

	/* 检查调用时, 需要在用例结束位置加上这句 */
	GlobalMockObject::verify();
}


class Test_APP_VCOM_Setup: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
		g_ulAppVcomDebugFlg = VOS_TRUE;
    }
    void TearDown()
    {

    }
};


TEST_F(Test_APP_VCOM_Setup, Test_APP_VCOM_Setup_001)
{
	/*参数初始化*/
	APP_VCOM_DEV_ENTITY_STRU       *pstVcomDev;

    pstVcomDev = (APP_VCOM_DEV_ENTITY_STRU*)malloc(sizeof(APP_VCOM_DEV_ENTITY_STRU));

    MOCKER(register_chrdev_region)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(cdev_init)
        .stubs()
        .will(returnValue(0));

    MOCKER(cdev_add)
        .stubs()
        .will(returnValue(1));

    APP_VCOM_Init();
    APP_VCOM_Setup(pstVcomDev, 0);

    free(pstVcomDev);

	APP_VCOM_FreeMem();
	/* 检查调用时, 需要在用例结束位置加上这句 */
	GlobalMockObject::verify();
}




class Test_APP_VCOM_Write: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
		g_ulAppVcomDebugFlg = VOS_TRUE;
    }
    void TearDown()
    {

    }
};


TEST_F(Test_APP_VCOM_Write, Test_APP_VCOM_Write_001)
{
	/*参数初始化*/
	int                               lRst;
	struct inode*                     pstInode;
	struct file*                      pstFile;
	char                             *buf       = NULL;
	size_t                            count;
	loff_t                           *ppos;
	APP_VCOM_DEV_ENTITY_STRU         *pstVcomDev;

	pstInode                          = (inode*)malloc(sizeof(inode));
	pstFile                           = (file*)malloc(sizeof(file));
	buf                               = (char*)malloc(100);
	count                             =  100;
	ppos                              = (loff_t*)malloc(sizeof(loff_t));
	pstVcomDev                        = (APP_VCOM_DEV_ENTITY_STRU*)malloc(sizeof(APP_VCOM_DEV_ENTITY_STRU));

	pstFile->private_data = pstVcomDev ;

	MOCKER(APP_VCOM_GetIndexFromMajorDevId)
        .stubs()
        .will(returnValue((VOS_CHAR)APP_VCOM_MAX_NUM));

	lRst = APP_VCOM_Write(pstFile, buf, count, ppos);

	EXPECT_EQ(APP_VCOM_ERROR, lRst);

	free(pstInode);
	free(pstFile);
	free(buf);
	free(ppos);
	free(pstVcomDev);
	/* 检查调用时, 需要在用例结束位置加上这句 */
	GlobalMockObject::verify();
}


TEST_F(Test_APP_VCOM_Write, Test_APP_VCOM_Write_002)
{
	/*参数初始化*/
	int                               lRst;
	struct inode*                     pstInode;
	struct file*                      pstFile;
	char                             *buf       = NULL;
	size_t                            count;
	loff_t                           *ppos;
	APP_VCOM_DEV_ENTITY_STRU         *pstVcomDev;

	pstInode                          = (inode*)malloc(sizeof(inode));
	pstFile                           = (file*)malloc(sizeof(file));
	buf                               = (char*)malloc(100);
	count                             =  100;
	ppos                              = (loff_t*)malloc(sizeof(loff_t));
	pstVcomDev                        = (APP_VCOM_DEV_ENTITY_STRU*)malloc(sizeof(APP_VCOM_DEV_ENTITY_STRU));

	pstFile->private_data = pstVcomDev ;

	MOCKER(APP_VCOM_GetIndexFromMajorDevId)
        .stubs()
        .will(returnValue((VOS_CHAR)0));
    MOCKER(copy_from_user)
        .stubs()
        .will(returnValue((VOS_UINT_PTR)1));

	lRst = APP_VCOM_Write(pstFile, buf, count, ppos);

	EXPECT_EQ(APP_VCOM_ERROR, lRst);

	free(pstInode);
	free(pstFile);
	free(buf);
	free(ppos);
	free(pstVcomDev);
	/* 检查调用时, 需要在用例结束位置加上这句 */
	GlobalMockObject::verify();
}


TEST_F(Test_APP_VCOM_Write, Test_APP_VCOM_Write_003)
{
	/*参数初始化*/
	int                               lRst;
	struct inode*                     pstInode;
	struct file*                      pstFile;
	char                             *buf       = NULL;
	size_t                            count;
	loff_t                           *ppos;
	APP_VCOM_DEV_ENTITY_STRU       *pstVcomDev;
    APP_VCOM_DEV_CTX_STRU            *pstVcomCtx;

	pstInode                          = (inode*)malloc(sizeof(inode));
	pstFile                           = (file*)malloc(sizeof(file));
	buf                               = (char*)malloc(100);
	count                             =  100;
	ppos                              = (loff_t*)malloc(sizeof(loff_t));
	pstVcomDev                        = (APP_VCOM_DEV_ENTITY_STRU*)malloc(sizeof(APP_VCOM_DEV_ENTITY_STRU));

	pstFile->private_data = pstVcomDev ;
    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(0);
	pstVcomCtx->pSendUlAtFunc = VOS_NULL_PTR;

	MOCKER(APP_VCOM_GetIndexFromMajorDevId)
        .stubs()
        .will(returnValue((VOS_CHAR)0));
    MOCKER(copy_from_user)
        .stubs()
        .will(returnValue((VOS_UINT_PTR)0));

	lRst = APP_VCOM_Write(pstFile, buf, count, ppos);

	EXPECT_EQ(APP_VCOM_ERROR, lRst);

	free(pstInode);
	free(pstFile);
	free(buf);
	free(ppos);
	free(pstVcomDev);
	/* 检查调用时, 需要在用例结束位置加上这句 */
	GlobalMockObject::verify();
}



TEST_F(Test_APP_VCOM_Write, Test_APP_VCOM_Write_004)
{
	/*参数初始化*/
	int                               lRst;
	struct inode*                     pstInode;
	struct file*                      pstFile;
	char                             *buf       = NULL;
	size_t                            count;
	loff_t                           *ppos;
	APP_VCOM_DEV_ENTITY_STRU         *pstVcomDev;
    APP_VCOM_DEV_CTX_STRU            *pstVcomCtx;

	pstInode                          = (inode*)malloc(sizeof(inode));
	pstFile                           = (file*)malloc(sizeof(file));
	buf                               = (char*)malloc(100);
	count                             =  100;
	ppos                              = (loff_t*)malloc(sizeof(loff_t));
	pstVcomDev                        = (APP_VCOM_DEV_ENTITY_STRU*)malloc(sizeof(APP_VCOM_DEV_ENTITY_STRU));

	pstFile->private_data = pstVcomDev ;
    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(0);
	pstVcomCtx->pSendUlAtFunc = (SEND_UL_AT_FUNC)AT_RcvFromAppCom;

	MOCKER(APP_VCOM_GetIndexFromMajorDevId)
        .stubs()
        .will(returnValue((VOS_CHAR)0));
    MOCKER(copy_from_user)
        .stubs()
        .will(returnValue((VOS_UINT_PTR)0));
    MOCKER(AT_RcvFromAppCom)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

	lRst = APP_VCOM_Write(pstFile, buf, count, ppos);

	EXPECT_EQ(count, lRst);

	free(pstInode);
	free(pstFile);
	free(buf);
	free(ppos);
	free(pstVcomDev);
	/* 检查调用时, 需要在用例结束位置加上这句 */
	GlobalMockObject::verify();
}


TEST_F(Test_APP_VCOM_Write, Test_APP_VCOM_Write_005)
{
	/*参数初始化*/
	int                               lRst;
	struct inode*                     pstInode;
	struct file*                      pstFile;
	char                             *buf       = NULL;
	size_t                            count;
	loff_t                           *ppos;
	APP_VCOM_DEV_ENTITY_STRU         *pstVcomDev;
    APP_VCOM_DEV_CTX_STRU            *pstVcomCtx;

	pstInode                          = (inode*)malloc(sizeof(inode));
	pstFile                           = (file*)malloc(sizeof(file));
	buf                               = (char*)malloc(100);
	count                             =  100;
	ppos                              = (loff_t*)malloc(sizeof(loff_t));
	pstVcomDev                        = (APP_VCOM_DEV_ENTITY_STRU*)malloc(sizeof(APP_VCOM_DEV_ENTITY_STRU));

	pstFile->private_data = pstVcomDev ;
    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(0);
	pstVcomCtx->pSendUlAtFunc = (SEND_UL_AT_FUNC)AT_RcvFromAppCom;

	MOCKER(APP_VCOM_GetIndexFromMajorDevId)
        .stubs()
        .will(returnValue((VOS_CHAR)0));
    MOCKER(AT_RcvFromAppCom)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

	lRst = APP_VCOM_Write(pstFile, buf, count, ppos);

	EXPECT_EQ(APP_VCOM_ERROR, lRst);

	free(pstInode);
	free(pstFile);
	free(buf);
	free(ppos);
	free(pstVcomDev);
	/* 检查调用时, 需要在用例结束位置加上这句 */
	GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_VCOM_EXT)

TEST_F(Test_APP_VCOM_Write, Test_APP_VCOM_Write_006)
{
    /*参数初始化*/
    int                               lRst;
    struct inode*                     pstInode;
    struct file*                      pstFile;
    char                             *buf       = NULL;
    size_t                            count;
    loff_t                           *ppos;
    APP_VCOM_DEV_ENTITY_STRU         *pstVcomDev;
    APP_VCOM_DEV_CTX_STRU            *pstVcomCtx;

    pstInode                          = (inode*)malloc(sizeof(inode));
    pstFile                           = (file*)malloc(sizeof(file));
    buf                               = (char*)malloc(100);
    count                             =  100;
    ppos                              = (loff_t*)malloc(sizeof(loff_t));
    pstVcomDev                        = (APP_VCOM_DEV_ENTITY_STRU*)malloc(sizeof(APP_VCOM_DEV_ENTITY_STRU));

    pstFile->private_data = pstVcomDev ;
    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(APP_VCOM_DEV_INDEX_9);
    pstVcomCtx->pstAppVcomDevEntity = pstVcomDev;
    pstVcomCtx->pSendUlAtFunc       = VOS_NULL_PTR;
    pstVcomDev->pucWrtBuffer        = (VOS_UINT8 *)malloc(50);
    pstVcomDev->ulWrtBufferLen      = 50;

    MOCKER(APP_VCOM_GetIndexFromMajorDevId)
        .stubs()
        .will(returnValue((VOS_CHAR)APP_VCOM_DEV_INDEX_9));

    lRst = APP_VCOM_Write(pstFile, buf, count, ppos);

    EXPECT_EQ(count, pstVcomDev->ulWrtBufferLen);
    EXPECT_EQ(count, lRst);

    free(pstInode);
    free(pstFile);
    free(buf);
    free(ppos);
    free(pstVcomDev);
    /* 检查调用时, 需要在用例结束位置加上这句 */
    GlobalMockObject::verify();
}
#endif


class Test_APP_VCOM_Send: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
		g_ulAppVcomDebugFlg = VOS_TRUE;

        MOCKER(register_chrdev_region)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(cdev_init)
            .defaults()
            .will(returnValue(0));

        MOCKER(cdev_add)
            .defaults()
            .will(returnValue(0));

    }
    void TearDown()
    {

    }
};


TEST_F(Test_APP_VCOM_Send, Test_APP_VCOM_Send_001)
{
	/*参数初始化*/
	VOS_UINT32                        lRst;
	APP_VCOM_DEV_INDEX_UINT8          enDevIndex;
	VOS_UINT8                        *pData; 
    VOS_UINT32                        uslength;
    
	enDevIndex = APP_VCOM_DEV_INDEX_BUTT;
	pData = (VOS_UINT8*)malloc(sizeof(VOS_UINT8));
    uslength = 16;

	lRst = APP_VCOM_Send (enDevIndex, pData, uslength);

	EXPECT_EQ(VOS_ERR, lRst);

	free(pData);
	/* 检查调用时, 需要在用例结束位置加上这句 */
	GlobalMockObject::verify();
}


TEST_F(Test_APP_VCOM_Send, Test_APP_VCOM_Send_002)
{
	/*参数初始化*/
	VOS_UINT32                        lRst;
	APP_VCOM_DEV_INDEX_UINT8          enDevIndex;
	VOS_UINT8                        *pData; 
    VOS_UINT32                        uslength;
	APP_VCOM_DEV_CTX_STRU            *pstVcomCtx;

	pstVcomCtx = APP_VCOM_GetVcomCtxAddr(0);

	pstVcomCtx->pstAppVcomDevEntity = VOS_NULL_PTR;
    
	enDevIndex = 0;
	pData = (VOS_UINT8*)malloc(sizeof(VOS_UINT8));
    uslength = 16;

	lRst = APP_VCOM_Send (enDevIndex, pData, uslength);

	EXPECT_EQ(VOS_ERR, lRst);

	free(pData);
	/* 检查调用时, 需要在用例结束位置加上这句 */
	GlobalMockObject::verify();
}


TEST_F(Test_APP_VCOM_Send, Test_APP_VCOM_Send_003)
{
	/*参数初始化*/
	VOS_UINT32                        lRst;
	APP_VCOM_DEV_INDEX_UINT8          enDevIndex;
	VOS_UINT8                        *pData; 
    VOS_UINT32                        uslength;
    
	enDevIndex = 0;
	uslength = 16;
	pData = (VOS_UINT8*)malloc(sizeof(VOS_UINT8) * uslength);

	APP_VCOM_Init();
	lRst = APP_VCOM_Send (enDevIndex, pData, uslength);

	EXPECT_EQ(VOS_OK, lRst);

	free(pData);
	APP_VCOM_FreeMem();
	/* 检查调用时, 需要在用例结束位置加上这句 */
	GlobalMockObject::verify();
}


TEST_F(Test_APP_VCOM_Send, Test_APP_VCOM_Send_004)
{
	/*参数初始化*/
	VOS_UINT32                        lRst;
	APP_VCOM_DEV_INDEX_UINT8          enDevIndex;
	VOS_UINT8                        *pData; 
    VOS_UINT32                        uslength;
    APP_VCOM_DEV_ENTITY_STRU         *pstVcomDev;

	enDevIndex = 0;
	pData = (VOS_UINT8*)malloc(sizeof(VOS_UINT8));
    uslength = 16;

	MOCKER(VOS_SmP)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

	APP_VCOM_Init();
    pstVcomDev = APP_VCOM_GetAppVcomDevEntity(0);
	pstVcomDev->current_len = 0x1000;

	lRst = APP_VCOM_Send (enDevIndex, pData, uslength);

	EXPECT_EQ(VOS_ERR, lRst);

	free(pData);
	APP_VCOM_FreeMem();
	/* 检查调用时, 需要在用例结束位置加上这句 */
	GlobalMockObject::verify();
}



TEST_F(Test_APP_VCOM_Send, Test_APP_VCOM_Send_005)
{
	/*参数初始化*/
	VOS_UINT32                        lRst;
	APP_VCOM_DEV_INDEX_UINT8          enDevIndex;
	VOS_UINT8                        *pData; 
    VOS_UINT32                        uslength;
    APP_VCOM_DEV_ENTITY_STRU         *pstVcomDev;

	enDevIndex = 0;
	uslength = 1000;
	pData = (VOS_UINT8*)malloc(sizeof(VOS_UINT8) * uslength);

	MOCKER(VOS_SmP)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

	APP_VCOM_Init();
    pstVcomDev = APP_VCOM_GetAppVcomDevEntity(0);
	pstVcomDev->current_len = 4000;

	lRst = APP_VCOM_Send (enDevIndex, pData, uslength);

	EXPECT_EQ(VOS_OK, lRst);

	free(pData);
	APP_VCOM_FreeMem();
	/* 检查调用时, 需要在用例结束位置加上这句 */
	GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_VCOM_EXT)

TEST_F(Test_APP_VCOM_Send, Test_APP_VCOM_Send_006)
{
	/*参数初始化*/
    APP_VCOM_DEV_ENTITY_STRU         *pstVcomDev;
    APP_VCOM_DEV_CTX_STRU            *pstVcomCtx;
	VOS_UINT8                        *pData; 
    VOS_UINT32                        uslength;
	VOS_UINT32                        lRst;
	APP_VCOM_DEV_INDEX_UINT8          enDevIndex;

	enDevIndex = APP_VCOM_DEV_INDEX_9;
	uslength = 500;
	pData = (VOS_UINT8*)malloc(sizeof(VOS_UINT8) * uslength);

	APP_VCOM_Init();
    pstVcomDev = APP_VCOM_GetAppVcomDevEntity(APP_VCOM_DEV_INDEX_9);
	pstVcomDev->current_len = 4000;

    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(APP_VCOM_DEV_INDEX_9);
    pstVcomCtx->pstAppVcomDevEntity = pstVcomDev;
	pstVcomCtx->pSendUlAtFunc       = (SEND_UL_AT_FUNC)AT_RcvFromAppCom;
    pstVcomDev->pucWrtBuffer        = (VOS_UINT8 *)malloc(50);
    pstVcomDev->ulWrtBufferLen      = 50;
	
    lRst = APP_VCOM_Send (enDevIndex, pData, uslength);

	EXPECT_EQ(VOS_OK, lRst);
	EXPECT_EQ(0, pstVcomDev->ulWrtBufferLen);

	free(pData);
	APP_VCOM_FreeMem();
	/* 检查调用时, 需要在用例结束位置加上这句 */
	GlobalMockObject::verify();
}
#endif


class Test_APP_VCOM_GetIndexFromMajorDevId: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
		g_ulAppVcomDebugFlg = VOS_TRUE;
        MOCKER(register_chrdev_region)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(cdev_init)
            .defaults()
            .will(returnValue(0));

        MOCKER(cdev_add)
            .defaults()
            .will(returnValue(0));
    }
    void TearDown()
    {

    }
};


TEST_F(Test_APP_VCOM_GetIndexFromMajorDevId, Test_APP_VCOM_GetIndexFromMajorDevId_001)
{


	VOS_UINT8                         ucIndex; 
    VOS_UINT                          uDevMajorID;

	uDevMajorID = APP_VCOM_MAJOR_DEV_ID_1;

	APP_VCOM_Init();
	ucIndex = APP_VCOM_GetIndexFromMajorDevId(uDevMajorID);

	EXPECT_EQ(1,ucIndex);
	APP_VCOM_FreeMem();
	/* 检查调用时, 需要在用例结束位置加上这句 */
	GlobalMockObject::verify();
}


TEST_F(Test_APP_VCOM_GetIndexFromMajorDevId, Test_APP_VCOM_GetIndexFromMajorDevId_002)
{
	VOS_UINT8                         ucIndex; 
    VOS_UINT                          uDevMajorID;

	uDevMajorID = APP_VCOM_MAJOR_DEV_ID_BUTT;

	APP_VCOM_Init();
	ucIndex = APP_VCOM_GetIndexFromMajorDevId(uDevMajorID);

	EXPECT_EQ(APP_VCOM_MAX_NUM,ucIndex);
	APP_VCOM_FreeMem();
	/* 检查调用时, 需要在用例结束位置加上这句 */
	GlobalMockObject::verify();
}


class Test_APP_VCOM_RegDataCallback: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
		g_ulAppVcomDebugFlg = VOS_TRUE;
    }
    void TearDown()
    {

    }
};


TEST_F(Test_APP_VCOM_RegDataCallback, Test_APP_VCOM_RegDataCallback_001)
{


	VOS_UINT32                        ulRst; 
    VOS_UINT8                         ucDevIndex;
	SEND_UL_AT_FUNC                   pFunc;

    ucDevIndex = APP_VCOM_DEV_INDEX_BUTT;
    pFunc = (SEND_UL_AT_FUNC)AT_RcvFromAppCom;

	ulRst = APP_VCOM_RegDataCallback(ucDevIndex, pFunc);

	EXPECT_EQ(VOS_ERR, ulRst);
	/* 检查调用时, 需要在用例结束位置加上这句 */
	GlobalMockObject::verify();
}

TEST_F(Test_APP_VCOM_RegDataCallback, Test_APP_VCOM_RegDataCallback_002)
{


	VOS_UINT32                        ulRst; 
    VOS_UINT8                         ucDevIndex;
	SEND_UL_AT_FUNC                   pFunc;
    APP_VCOM_DEV_CTX_STRU            *pstVcomCtx;

    MOCKER(register_chrdev_region)
        .defaults()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(cdev_init)
        .defaults()
        .will(returnValue(0));

    MOCKER(cdev_add)
        .defaults()
        .will(returnValue(0));

	APP_VCOM_Init();

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    ucDevIndex = APP_VCOM_DEV_INDEX_8;
#else
	ucDevIndex = APP_VCOM_DEV_INDEX_1;
#endif

    pFunc = (SEND_UL_AT_FUNC)AT_RcvFromAppCom;

	ulRst = APP_VCOM_RegDataCallback(ucDevIndex, pFunc);

    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucDevIndex);

	EXPECT_EQ(VOS_OK, ulRst);
	EXPECT_EQ(pstVcomCtx->pSendUlAtFunc,pFunc);

	/* 检查调用时, 需要在用例结束位置加上这句 */
	GlobalMockObject::verify();
}

