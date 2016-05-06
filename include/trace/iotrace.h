
#ifndef _IO_TRACE_H
#define _IO_TRACE_H

#include<linux/tracepoint.h>

DECLARE_TRACE(generic_perform_write_enter,
        TP_PROTO(struct file *file, size_t count, loff_t pos),
        TP_ARGS(file, count, pos));

DECLARE_TRACE(generic_perform_write_end,
        TP_PROTO(struct file *file, size_t count),
        TP_ARGS(file, count));

DECLARE_TRACE(generic_file_read_begin,
        TP_PROTO(struct file *filp, size_t count),
        TP_ARGS(filp, count));

DECLARE_TRACE(generic_file_read_end,
        TP_PROTO(struct file *filp, size_t count),
        TP_ARGS(filp, count));

/*
DECLARE_TRACE(ext4_da_write_begin_enter,
        TP_PROTO(struct inode *inode, loff_t pos, unsigned int len,
              unsigned int flags),
        TP_ARGS(inode, pos, len, flags)
    );
    */
DECLARE_TRACE(ext4_da_write_begin_end,
        TP_PROTO(struct inode *inode, loff_t pos, unsigned int len,
              unsigned int flags),
        TP_ARGS(inode, pos, len, flags)
    );

DECLARE_TRACE(ext4_sync_write_wait_end,
        TP_PROTO(struct file *file, int datasync),
        TP_ARGS(file, datasync)
    );

/*DECLARE_TRACE(ext4_sync_file_begin,
        TP_PROTO(struct file *file, int datasync),
        TP_ARGS(file, datasync)
    );

*/
DECLARE_TRACE(ext4_sync_file_end,
        TP_PROTO(struct file *file, int ret),
        TP_ARGS(file, ret)
    );

DECLARE_TRACE(block_write_begin_enter,
        TP_PROTO(struct inode *inode, struct page *page, loff_t pos,
            unsigned int len),
        TP_ARGS(inode, page, pos, len)
    );

DECLARE_TRACE(block_write_begin_end,
        TP_PROTO(struct inode *inode, struct page *page, int err),
        TP_ARGS(inode, page, err)
    );

DECLARE_TRACE(mpage_da_map_and_submit,
        TP_PROTO(struct inode *inode, unsigned long long fblk, unsigned int len),
        TP_ARGS(inode, fblk, len)
    );

/*M*/
DECLARE_TRACE(block_crypt_dec_pending,
        TP_PROTO(struct bio *bio),
        TP_ARGS(bio)
    );

DECLARE_TRACE(block_kcryptd_crypt,
        TP_PROTO(struct bio *bio),
        TP_ARGS(bio)
    );

DECLARE_TRACE(block_dm_request,
        TP_PROTO(struct request_queue *q, struct bio *bio),
        TP_ARGS(q, bio)
    );

DECLARE_TRACE(block_crypt_map,
        TP_PROTO(struct bio *bio, sector_t sector),
        TP_ARGS(bio, sector)
    );
#endif
