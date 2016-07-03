
#include "omringbuffer.h"

#if(FEATURE_ON == FEATURE_PTM)
#define OM_RING_BUFF_EX_MAX_LEN  (1024*8)
#define OM_MAX_RING_BUFFER_NUM   (48)  /* Error log新增32*/
#else
#define OM_MAX_RING_BUFFER_NUM   (16)
#endif

extern VOS_UINT8 g_ucOMBufferOccupiedFlag[];
extern OM_RING   g_stOMControlBlock[];


VOS_UINT32 uttest_OM_RingBufferCreate_case1(VOS_VOID)
{
	OM_RING_ID		pstRing;

	pstRing = OM_RingBufferCreate(100);

	// 执行检查
	if (VOS_NULL_PTR != pstRing)
	{
	    return VOS_ERR;
	}

	return VOS_OK;
}


VOS_UINT32 uttest_OM_RingBufferCreate_case2(VOS_VOID)
{
	OM_RING_ID		pstRing;

	pstRing = OM_RingBufferCreate(100);

	// 执行检查
	if (VOS_NULL_PTR == pstRing)
	{
	    return VOS_ERR;
	}

	return VOS_OK;
}


VOS_UINT32 uttest_OM_RingBufferCreate_case3(VOS_VOID)
{
	VOS_INT         i;
	OM_RING_ID		pstRing;

	for ( i=OM_MAX_RING_BUFFER_NUM -1; i>=0; i-- )
    {
        g_ucOMBufferOccupiedFlag[i] = VOS_TRUE;
    }

	pstRing = OM_RingBufferCreate(100);

	for ( i=OM_MAX_RING_BUFFER_NUM -1; i>=0; i-- )
    {
        g_ucOMBufferOccupiedFlag[i] = VOS_FALSE;
    }

	// 执行检查
	if (VOS_NULL_PTR != pstRing)
	{
	    return VOS_ERR;
	}

	return VOS_OK;

}


VOS_UINT32 uttest_OM_RingBufferCreateEx_case1(VOS_VOID)
{
#if(FEATURE_ON == FEATURE_PTM)

	OM_RING_ID		        pstRing;
    VOS_CHAR               *puc = VOS_NULL_PTR;

	pstRing = OM_RingBufferCreateEx(puc,100);

	// 执行检查
	if (VOS_NULL_PTR != pstRing)
	{
	    return VOS_ERR;
	}
#endif

	return VOS_OK;
}


VOS_UINT32 uttest_OM_RingBufferCreateEx_case2(VOS_VOID)
{
#if(FEATURE_ON == FEATURE_PTM)

	OM_RING_ID		        pstRing;
    VOS_CHAR               auc[100] = {0};

	pstRing = OM_RingBufferCreateEx(auc,9*1024);

	// 执行检查
	if(VOS_NULL_PTR != pstRing)
	{
	    return VOS_ERR;
	}
#endif

	return VOS_OK;
}


VOS_UINT32 uttest_OM_RingBufferCreateEx_case3(VOS_VOID)
{
#if(FEATURE_ON == FEATURE_PTM)

    OM_RING_ID		        pstRing;
    VOS_CHAR               auc[100] = {0};
    VOS_INT                 i;

	for ( i=OM_MAX_RING_BUFFER_NUM -1; i>=0; i-- )
    {
        g_ucOMBufferOccupiedFlag[i] = VOS_TRUE;
    }

	pstRing = OM_RingBufferCreateEx(auc,100);

    for ( i=OM_MAX_RING_BUFFER_NUM -1; i>=0; i-- )
    {
        g_ucOMBufferOccupiedFlag[i] = VOS_FALSE;
    }

	// 执行检查
	if (VOS_NULL_PTR != pstRing)
	{
	    return VOS_ERR;
	}
#endif

	return VOS_OK;
}


VOS_UINT32 uttest_OM_RingBufferCreateEx_case4(VOS_VOID)
{
#if(FEATURE_ON == FEATURE_PTM)

    VOS_CHAR               auc[100] = {0};
    OM_RING_ID		        pstRing;

    pstRing = OM_RingBufferCreateEx(auc,100);

	// 执行检查
	if (100 != pstRing->bufSize)
	{
	    return VOS_ERR;
	}
#endif

	return VOS_OK;
}


VOS_UINT32 uttest_OM_RingBufferNBytes_case1(VOS_VOID)
{
    OM_RING_ID		        pstRing;
    int                     i;

	for ( i=OM_MAX_RING_BUFFER_NUM -1; i>=0; i-- )
	{
		g_ucOMBufferOccupiedFlag[i] = VOS_FALSE;
	}

	pstRing = OM_RingBufferCreate(100);

	pstRing->pToBuf = 10;
	pstRing->pFromBuf = 100;

	pstRing->bufSize = 120;

	// 执行检查
	if (30 != OM_RingBufferNBytes(pstRing))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 uttest_OM_RingBufferFreeBytes_case1(VOS_VOID)
{
    OM_RING_ID		       pstRing;

	pstRing = OM_RingBufferCreate(100);

	pstRing->pToBuf = 100;
	pstRing->pFromBuf = 10;

	pstRing->bufSize = 120;

	// 执行检查
	if (29 != OM_RingBufferFreeBytes(pstRing))
    {
        return VOS_ERR;
    }

    return VOS_OK;

}


VOS_UINT32 uttest_OM_RingBufferIsFull_case1(VOS_VOID)
{
    OM_RING_ID		       pstRing;

	pstRing = OM_RingBufferCreate(100);

	pstRing->pToBuf = 100;
	pstRing->pFromBuf = 101;

	pstRing->bufSize = 120;

	// 执行检查
	if (VOS_TRUE != OM_RingBufferIsFull(pstRing))
    {
        return VOS_ERR;
    }

    return VOS_OK;

}


VOS_UINT32 uttest_OM_RingBufferIsFull_case2(VOS_VOID)
{
    OM_RING_ID		       pstRing;

	pstRing = OM_RingBufferCreate(100);

	pstRing->pToBuf = 100;
	pstRing->pFromBuf = 100;

	pstRing->bufSize = 120;

	// 执行检查
	if (VOS_FALSE != OM_RingBufferIsFull(pstRing))
    {
        return VOS_ERR;
    }

    return VOS_OK;

}


VOS_UINT32 uttest_OM_RingBufferIsEmpty_case1(VOS_VOID)
{
    OM_RING_ID		       pstRing;

	pstRing = OM_RingBufferCreate(100);

	pstRing->pToBuf = 100;
	pstRing->pFromBuf = 101;

	pstRing->bufSize = 120;

	// 执行检查
	if (VOS_FALSE != OM_RingBufferIsEmpty(pstRing))
    {
        return VOS_ERR;
    }

    return VOS_OK;

}


VOS_UINT32 uttest_OM_RingBufferGetReserve_case1(VOS_VOID)
{
    OM_RING_ID		       pstRing;
	char aucbuffer[100];
	int maxbytes = 100;

	pstRing = OM_RingBufferCreate(100);

	pstRing->pToBuf = 10;
	pstRing->pFromBuf = 100;

	pstRing->bufSize = 120;

	// 执行检查
	if (30 != OM_RingBufferGetReserve(pstRing, aucbuffer, maxbytes))
    {
        return VOS_ERR;
    }

    return VOS_OK;

}


VOS_UINT32 uttest_OM_RingBufferGetReserve_case2(VOS_VOID)
{
    OM_RING_ID		       pstRing;
	char aucbuffer[100];
	int maxbytes = 100;

	pstRing = OM_RingBufferCreate(100);

	pstRing->pToBuf = 100;
	pstRing->pFromBuf = 10;

	pstRing->bufSize = 120;

	// 执行检查
	if (90 != OM_RingBufferGetReserve(pstRing, aucbuffer, maxbytes))
    {
        return VOS_ERR;
    }

    return VOS_OK;

}


VOS_UINT32 uttest_OM_RingBufferRemove_case1(VOS_VOID)
{
    OM_RING_ID		       pstRing;
	int maxbytes = 100;

	pstRing = OM_RingBufferCreate(100);

	pstRing->pToBuf = 10;
	pstRing->pFromBuf = 100;

	pstRing->bufSize = 120;

	// 执行检查
	if (30 != OM_RingBufferRemove(pstRing, maxbytes))
    {
        return VOS_ERR;
    }

    return VOS_OK;

}


VOS_UINT32 uttest_OM_RingBufferRemove_case2(VOS_VOID)
{
    OM_RING_ID		       pstRing;
	int maxbytes = 100;

	pstRing = OM_RingBufferCreate(100);

	pstRing->pToBuf = 100;
	pstRing->pFromBuf = 10;

	pstRing->bufSize = 120;

	// 执行检查
	if (90 != OM_RingBufferRemove(pstRing, maxbytes))
    {
        return VOS_ERR;
    }

    return VOS_OK;

}


VOS_UINT32 uttest_OM_RingBufferRemove_case3(VOS_VOID)
{
    OM_RING_ID		       pstRing;
	int maxbytes = 200;

	pstRing = OM_RingBufferCreate(100);

	pstRing->pToBuf = 10;
	pstRing->pFromBuf = 100;

	pstRing->bufSize = 150;

	// 执行检查
	if (60 != OM_RingBufferRemove(pstRing, maxbytes))
    {
        return VOS_ERR;
    }

    return VOS_OK;

}


VOS_UINT32 uttest_OM_RingBufferPut_case1(VOS_VOID)
{
    OM_RING_ID		       pstRing;
	char aucbuffer[100];
	int maxbytes = 100;

	pstRing = OM_RingBufferCreate(100);

	pstRing->pToBuf = 10;
	pstRing->pFromBuf = 100;

	pstRing->bufSize = 120;

	// 执行检查
	if (89 != OM_RingBufferPut(pstRing, aucbuffer, maxbytes))
    {
        return VOS_ERR;
    }

    return VOS_OK;

}


VOS_UINT32 uttest_OM_RingBufferPut_case2(VOS_VOID)
{
    OM_RING_ID		       pstRing;
	char aucbuffer[100];
	int maxbytes = 100;

	pstRing = OM_RingBufferCreate(100);

	pstRing->pToBuf = 100;
	pstRing->pFromBuf = 10;

	pstRing->bufSize = 120;

	// 执行检查
	if (29 != OM_RingBufferPut(pstRing, aucbuffer, maxbytes))
    {
        return VOS_ERR;
    }

    return VOS_OK;

}


VOS_UINT32 uttest_OM_RingBufferPut_case3(VOS_VOID)
{
    OM_RING_ID		       pstRing;
	char aucbuffer[100];
	int maxbytes = 100;

	pstRing = OM_RingBufferCreate(100);

	pstRing->pToBuf = 100;
	pstRing->pFromBuf = 0;

	pstRing->bufSize = 120;

	// 执行检查
	if (19 != OM_RingBufferPut(pstRing, aucbuffer, maxbytes))
    {
        return VOS_ERR;
    }

    return VOS_OK;

}


VOS_UINT32 uttest_OM_RingBufferGet_case4(VOS_VOID)
{
    OM_RING_ID		       pstRing;
	char aucbuffer[100];
	int maxbytes = 100;

	pstRing = OM_RingBufferCreate(100);

	pstRing->pToBuf = 10;
	pstRing->pFromBuf = 100;

	pstRing->bufSize = 120;

	// 执行检查
	if (30 != OM_RingBufferGet(pstRing, aucbuffer, maxbytes))
    {
        return VOS_ERR;
    }

    return VOS_OK;

}


VOS_UINT32 uttest_OM_RingBufferGet_case5(VOS_VOID)
{
    OM_RING_ID		       pstRing;
	char aucbuffer[100];
	int maxbytes = 100;

	pstRing = OM_RingBufferCreate(100);

	pstRing->pToBuf = 100;
	pstRing->pFromBuf = 10;

	pstRing->bufSize = 120;

	// 执行检查
	if (90 != OM_RingBufferGet(pstRing, aucbuffer, maxbytes))
    {
        return VOS_ERR;
    }

    return VOS_OK;

}
