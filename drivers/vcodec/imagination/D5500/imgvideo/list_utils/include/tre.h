/*!
 *****************************************************************************
 *
 * @File       tre.h
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

#ifndef TRE_H
#define TRE_H

#if defined (__cplusplus)
extern "C" {
#endif


/* Macro definitions */
    
#define  TRE_LINK TRE_LINKAGE_T tre_link

/* Type definitions */
    

typedef struct TRE_linkage_tag TRE_LINKAGE_T ; /* Private  */

typedef struct TRE_tag TRE_T ; /* Anonymous */

typedef struct TRE_copy_tag TRE_COPY_T ; /* Anonymous */

/* Function Prototypes */
//#ifdef __STDC__
 void TRE_addChild(void *item, void *parent);
         void TRE_addSibling(void *item, void *sibling);
         static int TRE_areSiblings(void *item1, void *item2);
         void * TRE_copyNextInSubTree(TRE_COPY_T *copy, void *looseItem);
         void * TRE_finalSibling(void *item);
         void * TRE_firstChild(void *item);
         void * TRE_initCopySubTree(void *subTree, TRE_T *tree, void *destParent, TRE_T *destTree, TRE_COPY_T *copy);
         void TRE_initTree(TRE_T *tree);
         void * TRE_isInSubTree(void *subTree, void *item, TRE_T *tree);
         void * TRE_nextSibling(void *item);
         static void * TRE_parent(void *item);
         void * TRE_prevSibling(void *item);
         void TRE_removeLeaf(void *item, TRE_T *tree);
         void * TRE_removeLeafFromSubTree(void *subTree, TRE_T *tree);
         void * TRE_removeSubTree(void *item, TRE_T *tree);
         static void * TRE_root(TRE_T *tree);
         void * TRE_subTreeNext(void *subTree, void *item, TRE_T *tree);
        
//#endif /* __STDC__ */

/* complete the anonymous type definitions */
struct TRE_linkage_tag{
    void *next;
    void *parent;
};

struct TRE_tag {
    void *root;
    void *tip;
};

struct TRE_copy_tag {
    void *sourceRoot;
    void *destRoot;
    void *subRoot;
    void *destCurrent;
    void *sourceCurrent;
    void *sourcePrev;
    void *sourceTree;
};

#ifdef __GNUC__
#	define TRE_INLINE inline
#else
#	define TRE_INLINE
#endif

/* Some trivial functions are implemented as "inline static" for efficiency */
static TRE_INLINE void *TRE_root(TRE_T *tree)
{
    return tree->root;
}
static TRE_INLINE int TRE_areSiblings(void *t1, void *t2)
{
    return ((((TRE_LINKAGE_T *)t1)->parent == ((TRE_LINKAGE_T *)t2)->parent ) ? 1 : 0);
}
static TRE_INLINE void *TRE_parent(void *item)
{
    return (((TRE_LINKAGE_T *)item)->parent);
}

        
#if defined (__cplusplus)
}
#endif

#endif /* #ifndef TRE_H */
