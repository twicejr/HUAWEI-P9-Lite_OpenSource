/*!
 *****************************************************************************
 *
 * @File       copysub.c
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

//#include <metag/machine.inc>
#include "tre.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

/*
 ** FUNCTION:      _TRE_subTreeSteps
 **
 ** DESCRIPTION:   Counts the number of steps within the underlying list structure
 **                from a to b counting only those objects that lie within the subtree.
 **                Strictly private function
 **
 ** RETURNS:       int
 */

static int
_TRE_subTreeSteps(void *a, void *b, TRE_T * tree)
{
    void           *next;
    int             steps = -1;

    next = a;

    do {
	steps++;

	if (next == b)
	    return (steps);

    } while (NULL != (next = TRE_subTreeNext(a, next, tree)));

    return (-1);
}
/*
 ** FUNCTION:      TRE_initCopySubTree
 **
 ** DESCRIPTION:   Prepare for subtree copy
 **
 ** RETURNS:       void *
 */
void           *
TRE_initCopySubTree(void *subTree, TRE_T * tree, void *destSubTree,
		    TRE_T * destTree, TRE_COPY_T * copy)
{
    copy->sourceRoot = subTree;
    copy->destRoot = destSubTree;
    copy->destCurrent = destSubTree;
    copy->sourceCurrent = subTree;
    copy->sourcePrev = NULL;
    copy->sourceTree = tree;

    /*
     * ascertain that the destination is not a subtree of the source 
     */

    if ((TRE_isInSubTree(subTree, destSubTree, destTree)))
	return (NULL);

    return (copy->sourceRoot);
}


/*
 ** FUNCTION:      TRE_copyNextInSubTree
 **
 ** DESCRIPTION:   Copy one item of a sub-tree
 **
 ** RETURNS:       void *
 */
void           *
TRE_copyNextInSubTree(TRE_COPY_T * copy, void *looseItem)
{
    int             steps;

    if (!copy->sourcePrev) {
	TRE_addChild(looseItem, copy->destRoot);
	copy->subRoot = looseItem;	/* Log this item for later */
    } else if (TRE_areSiblings(copy->sourceCurrent, copy->sourcePrev)) {
	TRE_addSibling(looseItem, copy->destCurrent);
    } else {
	/*
	 * must link to correct parent in new subtree: do this by
	 * exploiting isomorphism in those parts of the source and
	 * destination subtrees already copied so far. 
	 */
	steps = _TRE_subTreeSteps(copy->sourceRoot,
				  TRE_parent(copy->sourceCurrent),
				  copy->sourceTree);

	{
	    void           *a;
	    int             i;

	    a = copy->subRoot;
	    for (i = 0; i < steps; i++)
		a = TRE_subTreeNext(copy->subRoot, a, copy->sourceTree);
	    TRE_addChild(looseItem, a);
	}
    }

    /*
     * Increment the source and destination item pointers 
     */
    copy->sourcePrev = copy->sourceCurrent;
    copy->sourceCurrent = TRE_subTreeNext(copy->sourceRoot,
					  copy->sourceCurrent,
					  copy->sourceTree);
    copy->destCurrent = looseItem;

    /*
     * return the next source item to copy or NULL if it is time to stop. 
     */
    return (copy->sourceCurrent);
}
