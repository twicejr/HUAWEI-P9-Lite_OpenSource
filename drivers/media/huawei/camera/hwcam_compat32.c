

#include "hwcam_compat32.h"
#include "cam_log.h"
#include "hwcam_intf.h"

long compat_get_v4l2_event_data(struct v4l2_event __user *pdata, struct v4l2_event32 __user *pdata32)
{
	long ret = 0;
    compat_uint_t type;
    compat_uint_t pending;
    compat_uint_t sequence;
    struct timespec		timestamp;
    compat_uint_t id;

	if (!access_ok(VERIFY_READ, pdata32, sizeof(struct v4l2_event32)))
		return -EFAULT;


	ret  = get_user(type, &pdata32->type);
    ret |= put_user(type, &pdata->type);
	ret |= copy_in_user(&pdata->u, &pdata32->u, sizeof(pdata->u));
	ret |= get_user(pending, &pdata32->pending);
    ret |= put_user(pending, &pdata->pending);
	ret |= get_user(sequence, &pdata32->sequence);
    ret |= put_user(sequence, &pdata->sequence);
	ret |= get_compat_timespec(&timestamp, &pdata32->timestamp);
    /* ret |= put_compat_timespec(&timestamp, &pdata->timestamp); */
    ret |= copy_to_user(&pdata->timestamp, &timestamp, sizeof(timestamp));
	ret |= get_user(id, &pdata32->id);
    ret |= put_user(id, &pdata->id);
	ret |= copy_in_user(pdata->reserved, pdata32->reserved, 8 * sizeof(__u32));

	return ret;
}
 
long compat_put_v4l2_event_data(struct v4l2_event __user *pdata, struct v4l2_event32 __user *pdata32)
{
	long ret = 0;
    compat_uint_t type;
    compat_uint_t pending;
    compat_uint_t sequence;
    struct timespec		timestamp;
    compat_uint_t id;

	if (!access_ok(VERIFY_WRITE, pdata32, sizeof(struct v4l2_event32)))
	    return -EFAULT;

    ret  = get_user(type, &pdata->type);
	ret |= put_user(type, &pdata32->type);
	ret |= copy_in_user(&pdata32->u, &pdata->u, sizeof(pdata->u));
    ret |= get_user(pending, &pdata->pending);
	ret |= put_user(pending, &pdata32->pending);
    ret |= get_user(sequence, &pdata->sequence);
	ret |= put_user(sequence, &pdata32->sequence);
    /* ret |= get_compat_timespec(&timestamp, &pdata->timestamp); */
    ret |= copy_from_user(&timestamp, &pdata->timestamp, sizeof(timestamp));
	ret |= put_compat_timespec(&timestamp, &pdata32->timestamp);
    ret |= get_user(id, &pdata->id);
	ret |= put_user(id, &pdata32->id);
	ret |= copy_in_user(pdata32->reserved, pdata->reserved, 8 * sizeof(__u32));
	return ret;
}

 static int compat_get_v4l2_window(struct v4l2_window *kp, struct v4l2_window32 __user *up)
{
	if (!access_ok(VERIFY_READ, up, sizeof(struct v4l2_window32)) ||
		copy_from_user(&kp->w, &up->w, sizeof(up->w)) ||
		get_user(kp->field, &up->field) ||
		get_user(kp->chromakey, &up->chromakey) ||
		get_user(kp->clipcount, &up->clipcount))
			return -EFAULT;
	if (kp->clipcount > 2048)
		return -EINVAL;
	if (kp->clipcount) {
		struct v4l2_clip32 __user *uclips;
		struct v4l2_clip __user *kclips;
		int n = kp->clipcount;
		compat_caddr_t p;

		if (get_user(p, &up->clips))
			return -EFAULT;
		uclips = compat_ptr(p);
		kclips = compat_alloc_user_space(n * sizeof(struct v4l2_clip));
		kp->clips = kclips;
		while (--n >= 0) {
			if (copy_in_user(&kclips->c, &uclips->c, sizeof(uclips->c)))
				return -EFAULT;
			if (put_user(n ? kclips + 1 : NULL, &kclips->next))
				return -EFAULT;
			uclips += 1;
			kclips += 1;
		}
	} else
		kp->clips = NULL;
	return 0;
}

static int compat_put_v4l2_window(struct v4l2_window *kp, struct v4l2_window32 __user *up)
{
	if (!access_ok(VERIFY_WRITE, up, sizeof(struct v4l2_window32)))
	    return -EFAULT;

	if (copy_to_user(&up->w, &kp->w, sizeof(kp->w)) ||
		put_user(kp->field, &up->field) ||
		put_user(kp->chromakey, &up->chromakey) ||
		put_user(kp->clipcount, &up->clipcount))
			return -EFAULT;
	return 0;
}

long compat_get_v4l2_format_data(struct v4l2_format *kp, struct v4l2_format32 __user *up)
{
 	long ret = 0;
	
	if (!access_ok(VERIFY_READ, up, sizeof(struct v4l2_format32)))
		return -EFAULT;

	if (get_user(kp->type, &up->type))
		return -EFAULT;

	if (0 == kp->type) {
		printk(KERN_INFO "%s: hwcam type is 0, return ok \n", __func__);
		return 0;
	}
	
	switch (kp->type) {
	case V4L2_BUF_TYPE_VIDEO_CAPTURE:
	case V4L2_BUF_TYPE_VIDEO_OUTPUT:
		ret |= copy_from_user(&kp->fmt.pix, &up->fmt.pix, sizeof(struct v4l2_pix_format));
		break;
	case V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
	case V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
		ret |= copy_from_user(&kp->fmt.pix_mp, &up->fmt.pix_mp, sizeof(struct v4l2_pix_format_mplane));
		break;
	case V4L2_BUF_TYPE_VIDEO_OVERLAY:
	case V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY:
		ret |= compat_get_v4l2_window(&kp->fmt.win, &up->fmt.win);
		break;
	case V4L2_BUF_TYPE_VBI_CAPTURE:
	case V4L2_BUF_TYPE_VBI_OUTPUT:
		ret |= copy_from_user(&kp->fmt.vbi, &up->fmt.vbi, sizeof(struct v4l2_vbi_format));
		break;
	case V4L2_BUF_TYPE_SLICED_VBI_CAPTURE:
	case V4L2_BUF_TYPE_SLICED_VBI_OUTPUT:
		ret |= copy_from_user(&kp->fmt.sliced, &up->fmt.sliced, sizeof(struct v4l2_sliced_vbi_format));
		break;
	default:
		printk(KERN_INFO "compat_ioctl32: unexpected VIDIOC_FMT type %d\n",kp->type);
		ret = -EINVAL;
	}
	return ret;
}

long compat_put_v4l2_format_data(struct v4l2_format *kp, struct v4l2_format32 __user *up)
{
 	long ret = 0;

	if (!access_ok(VERIFY_WRITE, up, sizeof(struct v4l2_format32)))
	    return -EFAULT;

	ret = put_user(kp->type, &up->type);
 	switch (kp->type) {
	case V4L2_BUF_TYPE_VIDEO_CAPTURE:
	case V4L2_BUF_TYPE_VIDEO_OUTPUT:
		ret |= copy_to_user(&up->fmt.pix, &kp->fmt.pix, sizeof(struct v4l2_pix_format));
		break;
	case V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
	case V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
		ret |= copy_to_user(&up->fmt.pix_mp, &kp->fmt.pix_mp, sizeof(struct v4l2_pix_format_mplane));
		break;
	case V4L2_BUF_TYPE_VIDEO_OVERLAY:
	case V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY:
		ret |= compat_put_v4l2_window(&kp->fmt.win, &up->fmt.win);
		break;
	case V4L2_BUF_TYPE_VBI_CAPTURE:
	case V4L2_BUF_TYPE_VBI_OUTPUT:
		ret |= copy_to_user(&up->fmt.vbi, &kp->fmt.vbi, sizeof(struct v4l2_vbi_format));
		break;
	case V4L2_BUF_TYPE_SLICED_VBI_CAPTURE:
	case V4L2_BUF_TYPE_SLICED_VBI_OUTPUT:
		ret |= copy_to_user(&up->fmt.sliced, &kp->fmt.sliced, sizeof(struct v4l2_sliced_vbi_format));
		break;
	default:
		printk(KERN_INFO "compat_ioctl32: unexpected VIDIOC_FMT type %d\n",kp->type);
		ret = -EINVAL;
	}
	return ret;
}


long compat_get_hwcam_buf_status_data(hwcam_buf_status_t __user *pdata, hwcam_buf_status_t32 __user *pdata32)
{
	long ret = 0;
    compat_int_t id;
    compat_int_t status;
    struct timeval tv;

	if (!access_ok(VERIFY_READ, pdata32, sizeof(hwcam_buf_status_t32)))
	    return -EFAULT;

	ret  = get_user(id, &pdata32->id);
    ret |= put_user(id, &pdata->id);
	ret |= get_user(status, &pdata32->buf_status);
    ret |= put_user(status, &pdata->buf_status);
	ret |= get_compat_timeval(&tv, &pdata32->tv);
    /* ret |= put_compat_timeval(&tv, &pdata->tv); */
    ret |= copy_to_user(&pdata->tv, &tv, sizeof(tv));
	return ret;
}

long compat_put_hwcam_buf_status_data(hwcam_buf_status_t __user *pdata, hwcam_buf_status_t32 __user *pdata32)
{
	long ret = 0;
    compat_int_t id;
    compat_int_t status;
    struct timeval tv;

	if (!access_ok(VERIFY_WRITE, pdata32, sizeof(hwcam_buf_status_t32)))
	    return -EFAULT;
 
    ret  = get_user(id, &pdata->id);
	ret |= put_user(id, &pdata32->id);
    ret |= get_user(status, &pdata->buf_status);
	ret |= put_user(status, &pdata32->buf_status);
    /* ret |= get_compat_timeval(&tv, &pdata->tv); */
    ret |= copy_from_user(&tv, &pdata->tv, sizeof(tv));
	ret |= put_compat_timeval(&tv, &pdata32->tv);

	return ret;
}


