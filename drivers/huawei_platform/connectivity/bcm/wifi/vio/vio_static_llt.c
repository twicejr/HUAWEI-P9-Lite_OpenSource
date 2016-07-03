
#ifdef __cplusplus
extern "C" {
#endif

struct LLT_TEST LLT_vio = {
	.vio_dev_ioctl = vio_dev_ioctl,
	.vio_dev_init = vio_dev_init,
	.vio_dev_exit = vio_dev_exit,
};

#ifdef __cplusplus
}
#endif
