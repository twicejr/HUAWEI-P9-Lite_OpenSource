/*!
 *****************************************************************************
 *
 * @File       fwtrace.c
 * @Title      Host side routines for debug text output from firmware
 * @Description    Host side routines for debug text output from firmware
 * ---------------------------------------------------------------------------
 *
 * Copyright (c) Imagination Technologies Ltd.
 * 
 * The contents of this file are subject to the MIT license as set out below.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 * 
 * Alternatively, the contents of this file may be used under the terms of the 
 * GNU General Public License Version 2 ("GPL")in which case the provisions of
 * GPL are applicable instead of those above. 
 * 
 * If you wish to allow use of your version of this file only under the terms 
 * of GPL, and not to allow others to use your version of this file under the 
 * terms of the MIT license, indicate your decision by deleting the provisions 
 * above and replace them with the notice and other provisions required by GPL 
 * as set out in the file called "GPLHEADER" included in this distribution. If 
 * you do not delete the provisions above, a recipient may use your version of 
 * this file under the terms of either the MIT license or GPL.
 * 
 * This License is also included in this distribution in the file called 
 * "MIT_COPYING".
 *
 *****************************************************************************/

#include "fwtrace.h"

#ifdef FW_LOGGING

#if defined (IMG_KERNEL_MODULE)
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/slab.h>

#define PRINT printk
#else
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <osa.h>
#define PRINT printf

static IMG_BOOL bFWLogThreadStop;
#endif

#define BUFFER_ALIGN(value, align) ((((int)value) + (align) -1) & ~((align) - 1))

#if defined (IMG_KERNEL_MODULE)
static char szFWTraceCommandString[][38]=
#else
char szFWTraceCommandString[][38]=
#endif
{
	"MTX_CMDID_NULL",
	"MTX_CMDID_SHUTDOWN",
	"MTX_CMDID_DO_HEADER",
	"MTX_CMDID_ENCODE_FRAME",
	"MTX_CMDID_START_FRAME",
	"MTX_CMDID_ENCODE_SLICE",
	"MTX_CMDID_END_FRAME",
	"MTX_CMDID_SETVIDEO",
	"MTX_CMDID_GETVIDEO",
	"MTX_CMDID_DO_CHANGE_PIPEWORK",
#if SECURE_IO_PORTS
	"MTX_CMDID_SECUREIO",
#endif 
	"MTX_CMDID_PICMGMT",
	"MTX_CMDID_RC_UPDATE",
	"MTX_CMDID_PROVIDE_SOURCE_BUFFER",
	"MTX_CMDID_PROVIDE_REF_BUFFER",
	"MTX_CMDID_PROVIDE_CODEDPACKAGE_BUFFER",
	"MTX_CMDID_ABORT",
	"MTX_CMDID_SETQUANT",
	"MTX_CMDID_SETUP_INTERFACE",
	"MTX_CMDID_ISSUEBUFF",
	"MTX_CMDID_SETUP",

	"MTX_CMDID_ENDMARKER"
};

static char *fwtrace_read(struct fwtrace_tracer *tracer, char *c) {
	static char tmp_str[1024];
#if !defined (IMG_KERNEL_MODULE)
	updateHostMemory(tracer->bufferHandle);
#endif
	switch(c[0]) {
	case 'S': {
		/* String */
		memset(tmp_str, 0, 1024);
		memcpy(tmp_str, &c[2], c[1]);
		tmp_str[c[1]] = '\0';

		PRINT("%s", tmp_str);

		c += c[1] /* data */ + 1 /* size */ + 1 /* type */;
		break;
	}
	case 'I': {
		/* Integer */
		unsigned int *tmp;
		tmp = (unsigned int *)c;

		PRINT("%i", tmp[1]);

		c += 4 /* type */ + 4 /*data*/;
		break;
	}
	case 'X': {
		/* Hex Integer */
		unsigned int *tmp;
		tmp = (unsigned int *)c;

		PRINT("0x%08x", tmp[1]);

		c += 4 /* type */ + 4 /*data*/;
		break;
	}
	case 'C': {
		/* Command name */
		unsigned int *tmp;
		tmp = (unsigned int *)c;

		if(tmp[1] >= MTX_CMDID_ENDMARKER)
		{
			PRINT("%i", tmp[1]);
		}
		else
		{
			PRINT("%s", szFWTraceCommandString[tmp[1]]);
		}

		c += 4 /* type */ + 4 /*data*/;
		break;
	}
	case 'A':
		/* No more items */
#if !defined(IMG_KERNEL_MODULE)
			OSA_ThreadSleep(400);
#else
			msleep(400);
#endif
		break;
	case 'B':
		/* Buffer Overflow */
		c = tracer->buffer;
		break;
	default:
#if defined(IMG_KERNEL_MODULE)
		PRINT("Unknown item\n");
#else
		/* there is a race condition here where we may see partial data if the DMAC is still running */
		OSA_ThreadSleep(400);
#endif
		return c;
	}

	c = (char *)BUFFER_ALIGN(c, 4);
	return c;
}

static int fwtrace_looper(void *params) {
	struct fwtrace_tracer *tracer = (struct fwtrace_tracer *)params;
	char *c = tracer->buffer;

#if defined(IMG_KERNEL_MODULE)
	while (!kthread_should_stop())
#else
	while(!bFWLogThreadStop)
#endif
		c = fwtrace_read(tracer, c);

	return 0;
}

#if defined(IMG_KERNEL_MODULE)
struct fwtrace_tracer *fwtrace_create(void *buffer, unsigned int size) {
	struct fwtrace_tracer *tracer = kzalloc(sizeof(struct fwtrace_tracer), GFP_KERNEL);
	if(!tracer) {
		return NULL;
	}

	tracer->buffer = buffer;
	tracer->size = size;

	/* Set the guard values */
	memset(buffer, 0, size);
	((char *)buffer)[0] = 'A';
	((char *)buffer)[1] = 'A';

	return tracer;
}
#else
struct fwtrace_tracer *fwtrace_create(void *buffer, unsigned int size, MEMORY_INFO *bufferHandle) {
	struct fwtrace_tracer *tracer = calloc(1, sizeof(struct fwtrace_tracer));
	if(!tracer) {
		return NULL;
	}

	tracer->buffer = buffer;
	tracer->size = size;
	tracer->bufferHandle = bufferHandle;

	/* Set the guard values */
	memset(buffer, 0, size);
	((char *)buffer)[0] = 'A';
	((char *)buffer)[1] = 'A';
	updateDeviceMemory(bufferHandle);
	return tracer;
}
#endif


void fwtrace_start(struct fwtrace_tracer *tracer) {
#if !defined (IMG_KERNEL_MODULE)
	bFWLogThreadStop = IMG_FALSE;
	OSA_ThreadCreateAndStart(fwtrace_looper, tracer, "FirmwareTraces", OSA_THREAD_PRIORITY_ABOVE_NORMAL, &tracer->task);
#else
	tracer->task = kthread_run(fwtrace_looper, tracer, "FirmwareTraces");
#endif
}

void fwtrace_stop(struct fwtrace_tracer *tracer) {
#if !defined (IMG_KERNEL_MODULE)
	bFWLogThreadStop = IMG_TRUE;
#else
	kthread_stop(tracer->task);
#endif
}

void fwtrace_destroy(struct fwtrace_tracer *tracer) {
#if defined (IMG_KERNEL_MODULE)
	kfree(tracer);
#else
	free(tracer);
#endif
}

#endif
