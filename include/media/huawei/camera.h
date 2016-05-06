


#ifndef __HW_ALAN_MEDIA_CAMERA_H__
#define __HW_ALAN_MEDIA_CAMERA_H__

#if !defined(__KERNEL__)
#include <stdlib.h>
#else // defined(__KERNEL__)
#include <linux/bsearch.h>
#endif
#include <linux/videodev2.h>
#include <linux/compat.h>
#define HWCAM_MODEL_USER                                "hwcam_userdev"
#define HWCAM_MODEL_CFG                                 "hwcam_cfgdev"

typedef struct _tag_hwcam_buf_info hwcam_buf_info_t;

typedef struct _tag_hwcam_cfgreq_intf hwcam_cfgreq_intf_t;
typedef struct _tag_hwcam_cfgreq hwcam_cfgreq_t;
typedef struct _tag_hwcam_cfgreq2dev hwcam_cfgreq2dev_t;
typedef struct _tag_hwcam_cfgreq2pipeline hwcam_cfgreq2pipeline_t;
typedef struct _tag_hwcam_cfgreq2stream hwcam_cfgreq2stream_t;

typedef struct _tag_hwcam_data_entry hwcam_data_entry_t;
typedef struct _tag_hwcam_data_table hwcam_data_table_t;

typedef struct _tag_hwcam_user_intf hwcam_user_intf_t;

typedef enum _tag_hwcam_device_id_constants
{
    HWCAM_DEVICE_GROUP_ID                               = 0x10,

    HWCAM_VNODE_GROUP_ID                                = 0x8000,

    HWCAM_SUBDEV_SENSOR                                 = 0x8010,
    HWCAM_SUBDEV_EXTISP                                 = 0x8020,
    HWCAM_SUBDEV_IDI                                    = 0x8030,
    HWCAM_SUBDEV_PMIC                                   = 0x8040,
    HWCAM_SUBDEV_FLASH0                                 = 0x8050,
    HWCAM_SUBDEV_FLASH1                                 = 0x8060,
    HWCAM_SUBDEV_ISP                                    = 0x8080,
    HWCAM_SUBDEV_VCM0                                   = 0x8090,
    HWCAM_SUBDEV_VCM1                                   = 0x80a0,
    HWCAM_SUBDEV_OIS                                    = 0X80b0,
    HWCAM_SUBDEV_HISP                                   = 0X80c0,
    HWCAM_SUBDEV_LASER                                  = 0x80d0,
    HWCAM_SUBDEV_DEPTHISP                               = 0x80e0,
} hwcam_device_id_constants_t;

typedef enum _tag_hwcam_buf_kind
{
    HWCAM_BUF_KIND_PIPELINE_CAPABILITY,
    HWCAM_BUF_KIND_PIPELINE_PARAM,
    HWCAM_BUF_KIND_STREAM_PARAM,
    HWCAM_BUF_KIND_STREAM,
} hwcam_buf_kind_t;

enum
{
    HWCAM_GRAPHIC_BUF_INFO_LENGTH                       =   64, //ints
};

typedef struct _tag_hwcam_buf_info
{
    hwcam_buf_kind_t                                    kind;
    int                                                 fd;
    uint32_t                                            size;
    uint32_t                                            frame;
    int                                                 plane;
} hwcam_buf_info_t;

typedef struct _tag_hwcam_stream_info
{
    hwcam_buf_info_t                                    info;
	union {
        void*                                           handle;
		int64_t                                         _handle;
	};
} hwcam_stream_info_t;

typedef struct _tag_hwcam_graphic_buf_info
{
    union {
        struct {
            uint32_t                                    index;
            int                                         num_fds;
            int                                         num_ints;
            int                                         data[0];
        };
        int                                             reserved[HWCAM_GRAPHIC_BUF_INFO_LENGTH];
    };
} hwcam_graphic_buf_info_t;

typedef struct _tag_hwcam_buf_status
{
    int id;
    int buf_status;
    struct timeval tv;
} hwcam_buf_status_t;

enum 
{
    HWCAM_DATA_TABLE_NAME_SIZE                          =   32,
    HWCAM_DATA_ALIGNMENT                                =   sizeof(uint32_t),
};

typedef struct _tag_hwcam_data_entry
{
    int32_t                                             prev;
    int32_t                                             next;

    uint32_t const                                      id;
    uint32_t const                                      size;
    uint32_t const                                      dim;
    uint32_t const                                      offset;
} hwcam_data_entry_t;

/**
 * @brief a self-sufficient data table, ALL VARIABLES IN IT MUST BE SCALAR TYPE.
 */
typedef struct _tag_hwcam_data_table
{
    char const                                          name[HWCAM_DATA_TABLE_NAME_SIZE];
    uint32_t const                                      total_size;
    uint32_t const                                      entry_count;

    hwcam_data_entry_t                                  used_list;
    hwcam_data_entry_t                                  unused_list;
    hwcam_data_entry_t                                  entries[0];
} hwcam_data_table_t;

typedef void (*pfn_data_table_entry_handler)
    (hwcam_data_entry_t* entry, void* data, uint32_t dim);

static inline bool
hwcam_data_table_empty(hwcam_data_table_t* tbl)
{
    return tbl->used_list.next == tbl->used_list.prev;
}

static inline bool
hwcam_data_table_full(hwcam_data_table_t* tbl)
{
    return tbl->unused_list.next == tbl->unused_list.prev;
}

static inline bool
hwcam_data_table_is_entry_valid(hwcam_data_table_t const* tbl,
                                hwcam_data_entry_t const* entry)
{
    return &(tbl->used_list) <= entry
        && entry < tbl->entries + tbl->entry_count;
}

static inline hwcam_data_entry_t*
hwcam_data_table_get_first_entry(hwcam_data_table_t* tbl)
{
    hwcam_data_entry_t* next = (hwcam_data_entry_t*)
        (((uint8_t*)tbl) + tbl->used_list.next);
    return !hwcam_data_table_is_entry_valid(tbl, next)
        || next == &tbl->used_list ? NULL : next;
}

static inline hwcam_data_entry_t*
hwcam_data_table_get_next_entry(hwcam_data_table_t* tbl,
                                hwcam_data_entry_t* cur)
{
    hwcam_data_entry_t* next = (hwcam_data_entry_t*)
        (((uint8_t*)tbl) + cur->next);
    return !hwcam_data_table_is_entry_valid(tbl, next)
        || next == &tbl->used_list ? NULL : next;
}

static inline uint32_t
hwcam_data_table_entry_index(hwcam_data_table_t* tbl,
                             hwcam_data_entry_t* cur)
{
    return tbl->entries <= cur
        && cur < tbl->entries + tbl->entry_count
        ? cur - tbl->entries : -1ul;
}

static inline bool
hwcam_data_table_offset_is_valid(hwcam_data_table_t const* tbl,
                                 uint32_t offset)
{
    return sizeof(hwcam_data_table_t)
        + tbl->entry_count * sizeof(hwcam_data_entry_t) <= offset
        && offset < tbl->total_size;
}

static inline void*
hwcam_data_table_data_ref(hwcam_data_table_t* tbl,
                          hwcam_data_entry_t const* cur,
                          uint32_t* dim)
{
    uint32_t offset = cur ? cur->offset: 0;
    if (hwcam_data_table_offset_is_valid(tbl, offset)) {
        void* data = (uint8_t*)tbl + offset;
        if (dim) {
            *dim = 1 < cur->dim ? *((uint32_t*)data - 1) : 1;
        }
        return data;
    }
    else {
        return NULL;
    }
}

static inline void
hwcam_data_table_enumerate(hwcam_data_table_t* tbl,
                           pfn_data_table_entry_handler handler)
{
    hwcam_data_entry_t* cur = hwcam_data_table_get_first_entry(tbl);
    while (cur) {
        uint32_t dim = 1;
        void* data = hwcam_data_table_data_ref(tbl, cur, &dim);
        handler(cur, data, dim);
        cur = hwcam_data_table_get_next_entry(tbl, cur);
    }
}

static inline int
hwcam_data_entry_compare(void const* e1,
                         void const* e2)
{
    uint32_t i1 = ((hwcam_data_entry_t const*)e1)->id;
    uint32_t i2 = ((hwcam_data_entry_t const*)e2)->id;
    if (i1 < i2) { return -1; }
    else if (i2 < i1) { return 1; }
    else { return 0; }
}

static inline hwcam_data_entry_t*
hwcam_data_table_find_entry_by_id(hwcam_data_table_t* tbl,
                                  uint32_t id)
{
    hwcam_data_entry_t eid = { .prev = 0, .next = 0,
        .id = id, .size = 0, .dim = 0, .offset = 0, };
    return (hwcam_data_entry_t*)
        bsearch(&eid, tbl->entries, tbl->entry_count,
                sizeof(hwcam_data_entry_t), hwcam_data_entry_compare);
}

static inline hwcam_data_entry_t*
hwcam_data_table_get_entry_by_index(hwcam_data_table_t* tbl,
                                    uint32_t index)
{
    return index < tbl->entry_count ? tbl->entries + index : NULL;
}

static inline void
hwcam_data_table_reset(hwcam_data_table_t* tbl)
{
    hwcam_data_entry_t* fu =
        (hwcam_data_entry_t*)((uint8_t*)tbl + tbl->used_list.next);
    hwcam_data_entry_t* lu =
        (hwcam_data_entry_t*)((uint8_t*)tbl + tbl->used_list.prev);

    if (fu != &tbl->used_list && lu != &tbl->used_list) {
        hwcam_data_entry_t* ln =
            (hwcam_data_entry_t*)((uint8_t*)tbl + tbl->unused_list.prev);

        fu->prev = tbl->unused_list.prev;
        lu->next = ln->next;
        tbl->unused_list.prev = tbl->used_list.prev;
        ln->next = tbl->used_list.next;
    }

    tbl->used_list.prev = tbl->used_list.next =
        (uint8_t*)&tbl->used_list - (uint8_t*)tbl;
}

static inline int
hwcam_data_table_set_entry_data(hwcam_data_table_t* tbl,
                                hwcam_data_entry_t* tgt,
                                void const* buf,
                                uint32_t size,
                                uint32_t dim)
{
    if (tbl->entries <= tgt && tgt < tbl->entries + tbl->entry_count
        && buf && tgt->size == size && dim <= tgt->dim
        && hwcam_data_table_offset_is_valid(tbl, tgt->offset)) {
        void* data = (uint8_t*)tbl + tgt->offset;
        hwcam_data_entry_t* lu = NULL;

        hwcam_data_entry_t* prev =
            (hwcam_data_entry_t*)((uint8_t*)tbl + tgt->prev);
        hwcam_data_entry_t* next =
            (hwcam_data_entry_t*)((uint8_t*)tbl + tgt->next);

        prev->next = tgt->next;
        next->prev = tgt->prev;

        lu = (hwcam_data_entry_t*)((uint8_t*)tbl + tbl->used_list.prev);

        tgt->prev = tbl->used_list.prev;
        tgt->next = lu->next;
        lu->next = tbl->used_list.prev = (uint8_t*)tgt - (uint8_t*)tbl;

        memcpy(data, buf, dim * size);
        if (1 < tgt->dim) {
            *((uint32_t*)data - 1) = dim;
        }
        return 0;
    }
    return -EINVAL;
}

static inline int
hwcam_data_table_set_data(hwcam_data_table_t* tbl,
                          uint32_t id,
                          void const* buf,
                          uint32_t size,
                          uint32_t dim)
{
    hwcam_data_entry_t* tgt = hwcam_data_table_find_entry_by_id(tbl, id);
    return hwcam_data_table_set_entry_data(tbl, tgt, buf, size, dim);
}

static inline int
hwcam_data_table_merge_data(hwcam_data_table_t* tbl_to,
                            hwcam_data_table_t* tbl_from)
{
    if (tbl_to && tbl_from && tbl_to != tbl_from) {
        if (strncmp(tbl_to->name, tbl_from->name, HWCAM_DATA_TABLE_NAME_SIZE)) {
            hwcam_data_entry_t* src = hwcam_data_table_get_first_entry(tbl_from);
            while (src) {
                uint32_t dim = 1;
                void const* data = hwcam_data_table_data_ref(tbl_from, src, &dim);
                uint32_t index = hwcam_data_table_entry_index(tbl_from, src);
                hwcam_data_entry_t* tgt
                    = hwcam_data_table_get_entry_by_index(tbl_to, index);
                hwcam_data_table_set_entry_data(tbl_to, tgt, data, src->size, dim);
                src = hwcam_data_table_get_next_entry(tbl_from, src);
            }
        }
        else {
            hwcam_data_entry_t* src = hwcam_data_table_get_first_entry(tbl_from);
            while (src) {
                uint32_t dim = 1;
                void const* data = hwcam_data_table_data_ref(tbl_from, src, &dim);
                hwcam_data_table_set_data(tbl_to, src->id, data, src->size, dim);
                src = hwcam_data_table_get_next_entry(tbl_from, src);
            }
        }
        return 0;
    }
    return -EINVAL;
}

static inline int
hwcam_data_table_set_entry_as_used(hwcam_data_table_t* tbl,
                                   hwcam_data_entry_t* tgt,
                                   int used)
{
    if (tbl->entries <= tgt && tgt < tbl->entries + tbl->entry_count) {
        hwcam_data_entry_t* prev =
            (hwcam_data_entry_t*)((uint8_t*)tbl + tgt->prev);
        hwcam_data_entry_t* next =
            (hwcam_data_entry_t*)((uint8_t*)tbl + tgt->next);

        prev->next = tgt->next;
        next->prev = tgt->prev;

        if (used) {
            hwcam_data_entry_t* lu =
                (hwcam_data_entry_t*)((uint8_t*)tbl + tbl->used_list.prev);

            tgt->prev = tbl->used_list.prev;
            tgt->next = lu->next;
            lu->next = tbl->used_list.prev = (uint8_t*)tgt - (uint8_t*)tbl;
        }
        else {
            hwcam_data_entry_t* ln =
                (hwcam_data_entry_t*)((uint8_t*)tbl + tbl->unused_list.prev);

            tgt->prev = tbl->unused_list.prev;
            tgt->next = ln->next;
            ln->next = tbl->unused_list.prev = (uint8_t*)tgt - (uint8_t*)tbl;
        }
        return 0;
    }
    return -EINVAL;
}

static inline int
hwcam_data_table_set_as_used(hwcam_data_table_t* tbl,
                             uint32_t id,
                             int used)
{
    hwcam_data_entry_t* tgt = hwcam_data_table_find_entry_by_id(tbl, id);
    return hwcam_data_table_set_entry_as_used(tbl, tgt, used);
}

#define HWCAM_V4L2_IOCTL_MOUNT_BUF \
    _IOW('A', BASE_VIDIOC_PRIVATE + 0x01, hwcam_buf_info_t)

#define HWCAM_V4L2_IOCTL_UNMOUNT_BUF \
    _IOW('A', BASE_VIDIOC_PRIVATE + 0x02, hwcam_buf_info_t)

#define HWCAM_V4L2_IOCTL_MOUNT_GRAPHIC_BUF \
    _IOW('A', BASE_VIDIOC_PRIVATE + 0x03, hwcam_graphic_buf_info_t)

#define HWCAM_V4L2_IOCTL_UNMOUNT_GRAPHIC_BUF \
    _IOW('A', BASE_VIDIOC_PRIVATE + 0x04, int)

#define HWCAM_V4L2_IOCTL_GET_GRAPHIC_BUF \
    _IOR('A', BASE_VIDIOC_PRIVATE + 0x05, hwcam_graphic_buf_info_t)

#define HWCAM_V4L2_IOCTL_GET_BUF \
    _IOR('A', BASE_VIDIOC_PRIVATE + 0x06, hwcam_buf_status_t)

#define HWCAM_V4L2_IOCTL_PUT_BUF \
    _IOW('A', BASE_VIDIOC_PRIVATE + 0x07, hwcam_buf_status_t)

#define HWCAM_V4L2_IOCTL_BUF_DONE \
    _IOW('A', BASE_VIDIOC_PRIVATE + 0x08, hwcam_buf_status_t)

#define HWCAM_V4L2_IOCTL_REQUEST_ACK \
    _IOW('A', BASE_VIDIOC_PRIVATE + 0x20, struct v4l2_event)

#define HWCAM_V4L2_IOCTL_NOTIFY \
    _IOW('A', BASE_VIDIOC_PRIVATE + 0x21, struct v4l2_event)

#define HWCAM_V4L2_IOCTL_THERMAL_GUARD \
    _IOWR('A', BASE_VIDIOC_PRIVATE + 0x22, struct v4l2_event)

typedef enum _tag_hwcam_v4l2_cid_kind
{
    HWCAM_V4L2_CID_PIPELINE_MIN                         =   V4L2_CID_PRIVATE_BASE,
    HWCAM_V4L2_CID_PIPELINE_PARAM,
    HWCAM_V4L2_CID_PIPELINE_MAX,

    HWCAM_V4L2_CID_STREAM_MIN                           =   V4L2_CID_PRIVATE_BASE + 0x1000,
    HWCAM_V4L2_CID_STREAM_PARAM,
    HWCAM_V4L2_CID_STREAM_MAX,
} hwcam_v4l2_cid_kind_t;

typedef enum _tag_hwcam_cfgreq_constants
{
    HWCAM_V4L2_EVENT_TYPE                               =   V4L2_EVENT_PRIVATE_START + 0x00001000,
    HWCAM_CFGDEV_REQUEST                                =   0x1000,
    HWCAM_CFGPIPELINE_REQUEST                           =   0x2000,
    HWCAM_CFGSTREAM_REQUEST                             =   0x3000,
    HWCAM_SERVER_CRASH                                  =   0x4000,
    HWCAM_HARDWARE_SUSPEND                              =   0x5001,
    HWCAM_HARDWARE_RESUME                               =   0x5002,
    HWCAM_NOTIFY_USER                                   =   0x6000,
} hwcam_cfgreq_constants_t;

typedef enum _tag_hwcam_cfgreq2dev_kind
{
    HWCAM_CFGDEV_REQ_MIN                                =   HWCAM_CFGDEV_REQUEST,
    HWCAM_CFGDEV_REQ_MOUNT_PIPELINE,
    HWCAM_CFGDEV_REQ_GUARD_THERMAL,
    HWCAM_CFGDEV_REQ_MAX,
} hwcam_cfgreq2dev_kind_t;

/* add for 32+64 */
#if 1
typedef struct _tag_hwcam_cfgreq
{
    union {
		hwcam_user_intf_t*                              user;
		int64_t											_user;
	};
	union {
		hwcam_cfgreq_intf_t*                             intf;
		int64_t											_intf;
	};
    uint32_t                                       		seq;
    int                                                 rc;
    uint32_t                                       		one_way : 1;
} hwcam_cfgreq_t; 
#else
typedef struct _tag_hwcam_cfgreq
{
    hwcam_user_intf_t*                                  user;
    hwcam_cfgreq_intf_t*                                intf;
    unsigned long                                       seq;
    int                                                 rc;
    unsigned long                                       one_way : 1;
} hwcam_cfgreq_t;
#endif

typedef struct _tag_hwcam_cfgreq2dev
{
    hwcam_cfgreq_t                                      req;
    hwcam_cfgreq2dev_kind_t                             kind;
    union // can ONLY place 10 int fields here.
    {
        struct
        {
            int                                         fd;
            int                                         moduleID;
        }                                               pipeline;
    };
} hwcam_cfgreq2dev_t;

typedef enum _tag_hwcam_cfgreq2pipeline_kind
{
    HWCAM_CFGPIPELINE_REQ_MIN                           =   HWCAM_CFGPIPELINE_REQUEST,
    HWCAM_CFGPIPELINE_REQ_UNMOUNT,
    HWCAM_CFGPIPELINE_REQ_MOUNT_STREAM,

    HWCAM_CFGPIPELINE_REQ_MOUNT_BUF,
    HWCAM_CFGPIPELINE_REQ_UNMOUNT_BUF,

    HWCAM_CFGPIPELINE_REQ_ENUM_FMT,
    HWCAM_CFGPIPELINE_REQ_QUERY_CAPABILITY,

    HWCAM_CFGPIPELINE_REQ_QUERY_PARAM,
    HWCAM_CFGPIPELINE_REQ_CHANGE_PARAM,

    HWCAM_CFGPIPELINE_REQ_MAX,
} hwcam_cfgreq2pipeline_kind_t;

typedef struct _tag_hwcam_cfgreq2pipeline
{
    hwcam_cfgreq_t                                      req;
    hwcam_cfgreq2pipeline_kind_t                        kind;
    union // can ONLY place 10 int fields here.
    {
        struct
        {
            int                                         fd;
            hwcam_buf_info_t                            info;
			union {
                void*                                   handle;
				int64_t                                 _handle;
			};
        }                                               stream;
        hwcam_buf_info_t                                buf;
    };
} hwcam_cfgreq2pipeline_t;

typedef enum _tag_hwcam_cfgreq2stream_kind
{
    HWCAM_CFGSTREAM_REQ_MIN                             =   HWCAM_CFGSTREAM_REQUEST,
    HWCAM_CFGSTREAM_REQ_UNMOUNT,

    HWCAM_CFGSTREAM_REQ_MOUNT_BUF,
    HWCAM_CFGSTREAM_REQ_UNMOUNT_BUF,
    HWCAM_CFGSTREAM_REQ_MOUNT_GRAPHIC_BUF,
    HWCAM_CFGSTREAM_REQ_UNMOUNT_GRAPHIC_BUF,

    HWCAM_CFGSTREAM_REQ_QUERY_PARAM,
    HWCAM_CFGSTREAM_REQ_CHANGE_PARAM,

    HWCAM_CFGSTREAM_REQ_TRY_FMT,

    HWCAM_CFGSTREAM_REQ_START,
    HWCAM_CFGSTREAM_REQ_STOP,

    HWCAM_CFGSTREAM_REQ_MAX,
} hwcam_cfgreq2stream_kind_t;

typedef struct _tag_hwcam_cfgreq2stream
{
    hwcam_cfgreq_t                                      req;
    hwcam_cfgreq2stream_kind_t                          kind;
    union // can ONLY place 10 int fields here.
    {
        hwcam_buf_info_t                                buf;
        struct {
            int                                         index;
        }                                               unmount_graphic_buf;
    };
} hwcam_cfgreq2stream_t;

#endif // __HW_ALAN_MEDIA_CAMERA_H__

