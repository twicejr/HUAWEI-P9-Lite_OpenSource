/*************************************************************************/ /*!
@File           ion_client.c
@Title          
@Copyright      Copyright (c) Imagination Technologies Ltd. All Rights Reserved
@Description    
@License        Strictly Confidential.
*/ /**************************************************************************/
#include <ion_client.h>
#include <linux/hisi/hisi_ion.h>

static struct ion_client *ion_client = NULL;

/*!
******************************************************************************
 @Function                get_ion_client
******************************************************************************/
struct ion_client *get_ion_client(void)
{
    if(!ion_client)
    	ion_client = hisi_ion_client_create("vcodec_ion_client");
    return ion_client;
}

void release_ion_client(void) {
	if(ion_client) {
		ion_client_destroy(ion_client);
		ion_client = NULL;
	}
}
