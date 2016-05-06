
#ifndef _LOCCOMMONINTERFACE_H_
#define _LOCCOMMONINTERFACE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*******************************************************************************
 *                          需要包含的头文件.
*******************************************************************************/
#include "vos.h"

/*根据不同产品分别包含不同的宏定义的文件 */
/*******************************************************************************
 *                      字节对齐方式: 一字节对齐.
*******************************************************************************/
//#pragma pack(1)
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(1)
#else
 #pragma pack(push, 1)
#endif

/*****************************************************************************
  2 Macro
*****************************************************************************/
#define LOC_COM_MAX_POLYGON_POINTS_LEN                  (15)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*******************************************************************************
 枚举名    : LOC_COM_VERTICAL_DIRECT_ENUM
 枚举说明  : 速度方向
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
enum LOC_COM_VERTICAL_DIRECT_ENUM
{
    LOC_COM_VERTICAL_DIRECT_UPWARD = 0,
    LOC_COM_VERTICAL_DIRECT_DOWNWARD,
    LOC_COM_VERTICAL_DIRECT_BUTT
};
typedef VOS_UINT32      LOC_COM_VERTICAL_DIRECT_ENUM_UINT32;

/*******************************************************************************
 枚举名    : LOC_COM_LATITUDE_DIR_ENUM
 枚举说明  : 维度方向
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
enum LOC_COM_LATITUDE_DIR_ENUM
{
    LOC_COM_LATITUDE_DIR_HEITHT = 0,
    LOC_COM_LATITUDE_DIR_DEPTH,
    LOC_COM_LATITUDE_DIR_BUTT
};
typedef VOS_UINT8   LOC_COM_LATITUDE_DIR_ENUM_UINT8;

/*******************************************************************************
 枚举名    : LOC_COM_LATITUDE_SIGN_ENUM
 枚举说明  : 维度标记
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
enum LOC_COM_LATITUDE_SIGN_ENUM
{
    LOC_COM_LATITUDE_SIGN_NORTH = 0,
    LOC_COM_LATITUDE_SIGN_SOUTH,
    LOC_COM_LATITUDE_SIGN_BUTT
};
typedef VOS_UINT8   LOC_COM_LATITUDE_SIGN_ENUM_UINT8;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/


/*******************************************************************************
 结构名    : LOC_COM_ELLIPSOID_POINT_STRU
 结构说明  : GPS提供位置信息Ellipsoid-Point
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*
    Ellipsoid-Point ::= SEQUENCE {
        latitudeSign                ENUMERATED {north, south},
        degreesLatitude             INTEGER (0..8388607),           -- 23 bit field
        degreesLongitude            INTEGER (-8388608..8388607)     -- 24 bit field
    }
    */
    LOC_COM_LATITUDE_SIGN_ENUM_UINT8    enLatitudeSign;
    VOS_UINT8                                   aucRes[3];
    VOS_UINT32                                  ulDegreeLatitude;
    VOS_INT32                                   lDegreesLongitude;
}LOC_COM_ELLIPSOID_POINT_STRU;

/*******************************************************************************
 结构名    : LOC_COM_ELLIPSOID_POINT_WITH_UNCERTAINTY_CIRCLE_STRU
 结构说明  : GPS提供位置信息Ellipsoid-PointWithUncertaintyCircle
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*
    Ellipsoid-PointWithUncertaintyCircle ::= SEQUENCE {
        latitudeSign                ENUMERATED {north, south},
        degreesLatitude             INTEGER (0..8388607),           -- 23 bit field
        degreesLongitude            INTEGER (-8388608..8388607),    -- 24 bit field
        uncertainty                 INTEGER (0..127)
    }
    */
    LOC_COM_LATITUDE_SIGN_ENUM_UINT8    enLatitudeSign;
    VOS_UINT8                                   aucRes[3];
    VOS_UINT32                                  ulDegreesLatitude;
    VOS_INT32                                   lDegreeLongitude;
    VOS_UINT32                                  ulUncretainty;
}LOC_COM_ELLIPSOID_POINT_WITH_UNCERTAINTY_CIRCLE_STRU;

/*******************************************************************************
 结构名    : LOC_COM_ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE_STRU
 结构说明  : GPS提供位置信息EllipsoidPointWithUncertaintyEllipse
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*
    EllipsoidPointWithUncertaintyEllipse ::= SEQUENCE {
        latitudeSign                ENUMERATED {north, south},
        degreesLatitude             INTEGER (0..8388607),           -- 23 bit field
        degreesLongitude            INTEGER (-8388608..8388607),    -- 24 bit field
        uncertaintySemiMajor        INTEGER (0..127),
        uncertaintySemiMinor        INTEGER (0..127),
        orientationMajorAxis        INTEGER (0..179),
        confidence                  INTEGER (0..100)
    }
    */
    LOC_COM_LATITUDE_SIGN_ENUM_UINT8    enLatitudeSign;
    VOS_UINT8                                   aucRes[3];
    VOS_UINT32                                  ulDegreesLatitude;
    VOS_INT32                                   lDegreesLongitude;
    VOS_UINT8                                   ucUncertaintySemiMajor;
    VOS_UINT8                                   ucUncertaintySemiMinor;
    VOS_UINT8                                   ucOrientationMajorAxis;
    VOS_UINT8                                   ucConfidence;
}LOC_COM_ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE_STRU;

/*******************************************************************************
 结构名    : LOC_COM_POLYGON_POINTS_STRU
 结构说明  : GPS提供位置信息PolygonPoints
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*
    PolygonPoints ::= SEQUENCE {
        latitudeSign                ENUMERATED {north, south},
        degreesLatitude             INTEGER (0..8388607),           -- 23 bit field
        degreesLongitude            INTEGER (-8388608..8388607)     -- 24 bit field
    }
    */
    LOC_COM_LATITUDE_SIGN_ENUM_UINT8    enLatitudeSign;
    VOS_UINT8                                   aucRes[3];
    VOS_UINT32                                  ulDegreesLatitude;
    VOS_INT32                                   lDegreesLatitude;
}LOC_COM_POLYGON_POINTS_STRU;

/*******************************************************************************
 结构名    : LOC_COM_POLYGON_STRU
 结构说明  : GPS提供位置信息Polygon
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*
    Polygon ::= SEQUENCE (SIZE (3..15)) OF PolygonPoints
    */
    VOS_UINT32                              ulPolygonCnt;
    LOC_COM_POLYGON_POINTS_STRU     astPolygonArray[LOC_COM_MAX_POLYGON_POINTS_LEN];
}LOC_COM_POLYGON_STRU;

/*******************************************************************************
 结构名    : LOC_COM_ELLIPSOID_POINT_WITH_ALTITUDE_STRU
 结构说明  : GPS提供位置信息EllipsoidPointWithAltitude
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*
    EllipsoidPointWithAltitude ::= SEQUENCE {
        latitudeSign                ENUMERATED {north, south},
        degreesLatitude             INTEGER (0..8388607),           -- 23 bit field
        degreesLongitude            INTEGER (-8388608..8388607),    -- 24 bit field
        altitudeDirection           ENUMERATED {height, depth},
        altitude                    INTEGER (0..32767)              -- 15 bit field
    }
    */
    LOC_COM_LATITUDE_SIGN_ENUM_UINT8    enLatitudeSign;
    VOS_UINT8                                   aucRes[3];
    VOS_UINT32                                  ulDegreesLatitude;
    VOS_INT32                                   lDegreesLatitude;
    LOC_COM_LATITUDE_DIR_ENUM_UINT8     enAltitudeDirection;
    VOS_UINT8                                   ucRes;
    VOS_UINT16                                  usAltitude;
}LOC_COM_ELLIPSOID_POINT_WITH_ALTITUDE_STRU;

/*******************************************************************************
 结构名    : LOC_COM_ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID_STRU
 结构说明  : GPS提供位置信息EllipsoidPointWithAltitudeAndUncertaintyEllipsoid
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*
    EllipsoidPointWithAltitudeAndUncertaintyEllipsoid ::= SEQUENCE {
        latitudeSign                ENUMERATED {north, south},
        degreesLatitude             INTEGER (0..8388607),           -- 23 bit field
        degreesLongitude            INTEGER (-8388608..8388607),    -- 24 bit field
        altitudeDirection           ENUMERATED {height, depth},
        altitude                    INTEGER (0..32767),             -- 15 bit field
        uncertaintySemiMajor        INTEGER (0..127),
        uncertaintySemiMinor        INTEGER (0..127),
        orientationMajorAxis        INTEGER (0..179),
        uncertaintyAltitude         INTEGER (0..127),
        confidence                  INTEGER (0..100)
    }
    */
    LOC_COM_LATITUDE_SIGN_ENUM_UINT8    enLatitudeSign;
    VOS_UINT8                                   aucRes[3];
    VOS_UINT32                                  ulDegreesLatitude;
    VOS_INT32                                   lDegreesLongtitude;
    LOC_COM_LATITUDE_DIR_ENUM_UINT8     enAltitudeDirection;
    VOS_UINT8                                   ucUncertaintySemiMajor;
    VOS_UINT16                                  usAltitude;
    VOS_UINT8                                   ucUncertaintySemiMinor;
    VOS_UINT8                                   ucOrientationMajorAxis;
    VOS_UINT8                                   ucUncertaintyAltitude;
    VOS_UINT8                                   ucConfidence;
}LOC_COM_ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID_STRU;

/*******************************************************************************
 结构名    : LOC_COM_ELLIPSOIDARC_STRU
 结构说明  : GPS提供位置信息EllipsoidArc
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*
    EllipsoidArc ::= SEQUENCE {
        latitudeSign                ENUMERATED {north, south},
        degreesLatitude             INTEGER (0..8388607),           -- 23 bit field
        degreesLongitude            INTEGER (-8388608..8388607),    -- 24 bit field
        innerRadius                 INTEGER (0..65535),             -- 16 bit field,
        uncertaintyRadius           INTEGER (0..127),
        offsetAngle                 INTEGER (0..179),
        includedAngle               INTEGER (0..179),
        confidence                  INTEGER (0..100)
    }
    */
    LOC_COM_LATITUDE_SIGN_ENUM_UINT8    enLatitudeSign;
    VOS_UINT8                                   aucRes[3];
    VOS_UINT32                                  ulDegreesLatitude;
    VOS_INT32                                   lDegreesLongtitude;
    VOS_UINT32                                  ulInnerRadius;
    VOS_UINT8                                   ucUncertaintyRadius;
    VOS_UINT8                                   ucOffsetAngle;
    VOS_UINT8                                   ucIncludedAngle;
    VOS_UINT8                                   ucConfidence;
}LOC_COM_ELLIPSOIDARC_STRU;

/*******************************************************************************
 结构名    : LOC_COM_COORDINATE_STRU
 结构说明  : GPS提供位置信息LocationCoordinates
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*
    LocationCoordinates ::= CHOICE {
        ellipsoidPoint                              Ellipsoid-Point,
        ellipsoidPointWithUncertaintyCircle         Ellipsoid-PointWithUncertaintyCircle,
        ellipsoidPointWithUncertaintyEllipse        EllipsoidPointWithUncertaintyEllipse,
        polygon                                     Polygon,
        ellipsoidPointWithAltitude                  EllipsoidPointWithAltitude,
        ellipsoidPointWithAltitudeAndUncertaintyEllipsoid
                                                    EllipsoidPointWithAltitudeAndUncertaintyEllipsoid,
        ellipsoidArc                                EllipsoidArc,
        ...
    }
    */
    VOS_UINT32                      bitOpLocationCoordinatesExt:1;
    VOS_UINT32                      bitOpSpare:31;
    VOS_UINT32                                          ulChoice;

    #define         LOC_COM_ELLIPSOID_POINT_CHOSEN                                          0
    #define         LOC_COM_ELLIPSOID_POINT_WITH_UNCERTAINTY_CIRCLE_CHOSEN                  1
    #define         LOC_COM_ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE_CHOSEN                 2
    #define         LOC_COM_POLYGON_CHOSEN                                                  3
    #define         LOC_COM_ELLIPSOID_POINT_WITH_ALTITUDE_CHOSEN                            4
    #define         LOC_COM_ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID_CHOSEN  5
    #define         LOC_COM_ELLIPSOIDARC_CHOSEN                                             6

        union
        {
            LOC_COM_ELLIPSOID_POINT_STRU                                            stEllipsoidPoint;
            LOC_COM_ELLIPSOID_POINT_WITH_UNCERTAINTY_CIRCLE_STRU                    stEllipsoidPointWithUncertaintyCircle;
            LOC_COM_ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE_STRU                   stEllipsoidPointWithUncertaintyEllipse;
            LOC_COM_POLYGON_STRU                                                    stPolygon;
            LOC_COM_ELLIPSOID_POINT_WITH_ALTITUDE_STRU                              stEllipsoidPointWithAltitude;
            LOC_COM_ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID_STRU    stEllipsoidPointWithAltitudeAndUncertaintyEllipsoid;
            LOC_COM_ELLIPSOIDARC_STRU                                               stEllipsoidArc;
        }u;
}LOC_COM_COORDINATE_STRU;

/*******************************************************************************
 结构名    : LOC_COM_HORIZONTAL_VELCOCTIY_STRU
 结构说明  : GPS提供位置信息HorizontalVelocity
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*
    HorizontalVelocity ::= SEQUENCE {
        bearing                     INTEGER(0..359),
        horizontalSpeed             INTEGER(0..2047)
    }
    */
    VOS_UINT16          usBearing;
    VOS_UINT16          usHorizontalSpeed;
}LOC_COM_HORIZONTAL_VELCOCTIY_STRU;

/*******************************************************************************
 结构名    : LOC_COM_HORIZONTAL_WITH_VERTICAL_VELOCITY_STRU
 结构说明  : GPS提供位置信息HorizontalWithVerticalVelocity
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*
    HorizontalWithVerticalVelocity ::= SEQUENCE {
        bearing                     INTEGER(0..359),
        horizontalSpeed             INTEGER(0..2047),
        verticalDirection           ENUMERATED{upward, downward},
        verticalSpeed               INTEGER(0..255)
    }
    */
    VOS_UINT16                                  usBearing;
    VOS_UINT16                                  usHorizontalSpeed;
    LOC_COM_VERTICAL_DIRECT_ENUM_UINT32 enVerticalDirection;
    VOS_UINT32                                  ulVerticalSpeed;
}LOC_COM_HORIZONTAL_WITH_VERTICAL_VELOCITY_STRU;

/*******************************************************************************
 结构名    : LOC_COM_HORIZONTAL_VELCCITY_WITH_UNCERTAINTY_STRU
 结构说明  : GPS提供位置信息HorizontalVelocityWithUncertainty
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*
    HorizontalVelocityWithUncertainty ::= SEQUENCE {
        bearing                     INTEGER(0..359),
        horizontalSpeed             INTEGER(0..2047),
        uncertaintySpeed            INTEGER(0..255)
    }
    */
    VOS_UINT16                      usBearing;
    VOS_UINT16                      usHorizontalSpeed;
    VOS_UINT32                      ulUncertaintySpeed;
}LOC_COM_HORIZONTAL_VELCCITY_WITH_UNCERTAINTY_STRU;

/*******************************************************************************
 结构名    : LOC_COM_HORIZONTAL_WITH_VERTICAL_VELOCITY_AND_UNCERTAINTY_STRU
 结构说明  : GPS提供位置信息HorizontalWithVerticalVelocityAndUncertainty
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*
    HorizontalWithVerticalVelocityAndUncertainty ::= SEQUENCE {
        bearing                     INTEGER(0..359),
        horizontalSpeed             INTEGER(0..2047),
        verticalDirection           ENUMERATED{upward, downward},
        verticalSpeed               INTEGER(0..255),
        horizontalUncertaintySpeed  INTEGER(0..255),
        verticalUncertaintySpeed    INTEGER(0..255)
    }
    */
    VOS_UINT16                                  usBearing;
    VOS_UINT16                                  usHorizontalSpeed;
    LOC_COM_VERTICAL_DIRECT_ENUM_UINT32 enVerticalDirection;
    VOS_UINT8                                   ucVerticalSpeed;
    VOS_UINT8                                   ucHorizontalUncertaintySpeed;
    VOS_UINT8                                   ucVerticalUncertaintySpeed;
    VOS_UINT8                                   ucRes;
}LOC_COM_HORIZONTAL_WITH_VERTICAL_VELOCITY_AND_UNCERTAINTY_STRU;

/*******************************************************************************
 结构名    : LOC_COM_VELOCITY_STRU
 结构说明  : GPS提供位置信息Velocity
 1.日    期   : 2015年06月24日
   作    者   : l00253982
   修改内容   : Added for GNSS
*******************************************************************************/
typedef struct
{
    /*
    Velocity ::= CHOICE {
        horizontalVelocity                          HorizontalVelocity,
        horizontalWithVerticalVelocity              HorizontalWithVerticalVelocity,
        horizontalVelocityWithUncertainty           HorizontalVelocityWithUncertainty,
        horizontalWithVerticalVelocityAndUncertainty
                                                    HorizontalWithVerticalVelocityAndUncertainty,
        ...
    }
    */
    VOS_UINT32                                          bitOpVelocityExt:1;
    VOS_UINT32                                          bitOpSpare      :31;

    VOS_UINT32                                          ulChoice;

    #define     LOC_COM_HORIZONTAL_VELCOCTIY_CHOSEN                                 0
    #define     LOC_COM_HORIZONTAL_WITH_VERTICAL_VELOCITY_CHOSEN                    1
    #define     LOC_COM_HORIZONTAL_VELCCITY_WITH_UNCERTAINTY_CHOSEN                 2
    #define     LOC_COM_HORIZONTAL_WITH_VERTICAL_VELOCITY_AND_UNCERTAINTY_CHOSEN    3

    union
    {
        LOC_COM_HORIZONTAL_VELCOCTIY_STRU                               stHorizontalVelocity;
        LOC_COM_HORIZONTAL_WITH_VERTICAL_VELOCITY_STRU                  stHorizontalWithVerticalVelocity;
        LOC_COM_HORIZONTAL_VELCCITY_WITH_UNCERTAINTY_STRU               stHorizontalVelocityWithUncertainty;
        LOC_COM_HORIZONTAL_WITH_VERTICAL_VELOCITY_AND_UNCERTAINTY_STRU  stHorizontalWithVerticalVelocityAndUncertainty;
    }u;
}LOC_COM_VELOCITY_STRU;

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
 #pragma pack(pop)
#endif


#ifdef __cplusplus
#if __cplusplus

}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif

