
#ifndef __BST_LIB_SnGenerator_H__
#define __BST_LIB_SnGenerator_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_OS_Memory.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define  FLAG_NUMBER_PER_DATA 0x08
#define  USED_BIT_FLAG        0x01
#define  THIS_FILE_ID               PS_FILE_ID_BST_LIB_SN_GENERATE_H

/*****************************************************************************
  3 类/结构定义
*****************************************************************************/
template<typename DATA_T>
class BST_Lib_CSnGenrator
{
BST_PUBLIC:
                            BST_Lib_CSnGenrator ( DATA_T        tdMinId,
                                                  BST_UINT16    ulAmount );
    virtual                ~BST_Lib_CSnGenrator ( BST_VOID );
    DATA_T                  NewId               ( BST_VOID );
    BST_VOID                RmvId               ( BST_VOID );
    BST_BOOL                RmvId               ( DATA_T        tdMinId );
    BST_BOOL                IsIdUsed            ( DATA_T        tdMinId );

BST_PRIVATE:
    DATA_T                  m_tdMinId;
    DATA_T                  m_tdAmount;
    BST_UINT16              m_usUsedSize;
    BST_UINT8              *m_pucFlag;
};

/*****************************************************************************
  4 模板函数定义
*****************************************************************************/


template<typename DATA_T>
BST_Lib_CSnGenrator<DATA_T>::BST_Lib_CSnGenrator( DATA_T tdMinId, BST_UINT16 ulAmount )
    : m_tdMinId     ( BST_INVALID_SNID ),
      m_tdAmount    ( 0 ),
      m_usUsedSize  ( 0 ),
      m_pucFlag     ( BST_NULL_PTR )
{
    BST_UINT16              usRmainer;

    usRmainer                           = 0;

    if ( ulAmount <= 0 )
    {
        return;
    }
    if ( BST_INVALID_SNID == tdMinId )
    {
        return;
    }

    m_tdMinId                           = tdMinId;
    m_tdAmount                          = ulAmount;
    m_usUsedSize                        = 0;


    usRmainer                       = m_tdAmount % FLAG_NUMBER_PER_DATA ;
    m_usUsedSize                    = m_tdAmount / FLAG_NUMBER_PER_DATA;

    if ( 0 != usRmainer )
    {
        m_usUsedSize               += 1;
    }

    m_pucFlag                           = ( BST_UINT8 * )BST_OS_MALLOC( m_usUsedSize );
    if ( BST_NULL_PTR == m_pucFlag )
    {
        return;
    }

    BST_OS_MEMSET( m_pucFlag, 0, m_usUsedSize );
}


template<typename DATA_T>
DATA_T BST_Lib_CSnGenrator<DATA_T>::NewId( BST_VOID )
{
    BST_UINT16                  usLoop;
    BST_UINT8                   ucMasker;
    BST_UINT16                  ulBaseAddr;
    BST_UINT16                  ulOfstAddr;

    ulBaseAddr                  = 0;
    ulOfstAddr                  = 0;

    if ( m_tdAmount <= 0 )
    {
        return BST_INVALID_SNID;
    }
    if ( BST_INVALID_SNID == m_tdMinId )
    {
        return BST_INVALID_SNID;
    }
    if ( BST_NULL_PTR == m_pucFlag )
    {
        return BST_INVALID_SNID;
    }

    for ( usLoop = 0; usLoop < m_tdAmount; usLoop++ )
    {
        ulBaseAddr              = usLoop / FLAG_NUMBER_PER_DATA ;

        if ( 0 == ulBaseAddr )
        {
            ulOfstAddr          = usLoop;
        }
        else
        {
            ulOfstAddr          = usLoop % FLAG_NUMBER_PER_DATA;
        }

        ucMasker                = ( USED_BIT_FLAG << ulOfstAddr );

        if ( ( m_pucFlag[ ulBaseAddr ] & ucMasker ) != 0 )
        {
            continue;
        }
        m_pucFlag[ulBaseAddr]  |= ucMasker;
        return ( m_tdMinId + usLoop );
    }
    return BST_INVALID_SNID;
}

template<typename DATA_T>
BST_BOOL  BST_Lib_CSnGenrator<DATA_T>::IsIdUsed( DATA_T tdId )
{
    BST_UINT16              ulBaseAddr;
    BST_UINT16              ulOfstAddr;
    BST_UINT16              ucMasker;

    ulBaseAddr              = 0;
    ulOfstAddr              = 0;
    ucMasker                = 0;

    if ( tdId < m_tdMinId )
    {
        return BST_FALSE;
    }
    if ( tdId >= ( m_tdMinId + m_tdAmount ) )
    {
        return BST_FALSE;
    }

    ulBaseAddr              = tdId - m_tdMinId;
    ulBaseAddr              = ulBaseAddr / FLAG_NUMBER_PER_DATA ;

    if ( 0 == ulBaseAddr )
    {
        ulOfstAddr          = tdId - m_tdMinId;
    }
    else
    {
        ulOfstAddr          = ( tdId - m_tdMinId ) % FLAG_NUMBER_PER_DATA;
    }

    ucMasker                = ( USED_BIT_FLAG << ulOfstAddr );
    if ( ( m_pucFlag[ ulBaseAddr ] & ucMasker ) == ucMasker )
    {
        return BST_TRUE;
    }
    else
    {
        return BST_FALSE;
    }
}


template<typename DATA_T>
BST_BOOL  BST_Lib_CSnGenrator<DATA_T>::RmvId( DATA_T tdId )
{
    BST_UINT16              ulBaseAddr;
    BST_UINT16              ulOfstAddr;
    BST_UINT16              ucMasker;

    ulBaseAddr              = 0;
    ulOfstAddr              = 0;
    ucMasker                = 0;

    if ( tdId < m_tdMinId )
    {
        return BST_FALSE;
    }
    if ( tdId >= ( m_tdMinId + m_tdAmount ) )
    {
        return BST_FALSE;
    }


    ulBaseAddr              = tdId - m_tdMinId;
    ulBaseAddr              = ulBaseAddr / FLAG_NUMBER_PER_DATA ;

    if ( 0 == ulBaseAddr )
    {
        ulOfstAddr          = tdId - m_tdMinId;
    }
    else
    {
        ulOfstAddr          = ( tdId - m_tdMinId ) % FLAG_NUMBER_PER_DATA;
    }
    ucMasker                = ( USED_BIT_FLAG << ulOfstAddr );
    m_pucFlag[ ulBaseAddr ]&= ( ~ucMasker );

    return BST_TRUE;
}


template<typename DATA_T>
BST_VOID  BST_Lib_CSnGenrator<DATA_T>::RmvId(BST_VOID)
{
    BST_OS_MEMSET( m_pucFlag, 0, m_usUsedSize );
}


template<typename DATA_T>
BST_Lib_CSnGenrator<DATA_T>::~BST_Lib_CSnGenrator(BST_VOID)
{
    BST_OS_FREE( m_pucFlag );
    m_pucFlag = BST_NULL_PTR;
}

/*****************************************************************************
  5 其他定义
*****************************************************************************/
#undef THIS_FILE_ID

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif


#endif
