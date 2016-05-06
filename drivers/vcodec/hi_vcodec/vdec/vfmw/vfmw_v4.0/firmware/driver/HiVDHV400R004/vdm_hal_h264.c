
/******************************************************************************

  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
    文 件 名   : vdmv300vplus_hal.c
    版 本 号   : 初稿
    作    者   :
    生成日期   :
    最近修改   :
    功能描述   : VDMV300 硬件抽象


  修改历史   :
    1.日    期 : 2009-03-04
    作    者   :
    修改内容   :

******************************************************************************/

#include 	"basedef.h"
#include 	"vfmw.h"
#include 	"mem_manage.h"
#include 	"public.h"
#include    "vdm_hal_v400r004_api.h"
#include    "vdm_hal_v400r004_local.h"
#include 	"vdm_hal_v400r004_h264.h"
#include    "vfmw_ctrl.h"

extern VFMW_CHAN_S  *s_pstVfmwChan[MAX_CHAN_NUM];
extern UINT8  g_not_direct_8x8_inference_flag;
#ifdef VFMW_MODULE_LOWDLY_SUPPORT
extern SINT32 g_TunnelLineNumber;
#endif

static UINT32 g_StructTrans[4][2]     = {{0, 3}, {1, 1}, {2, 2}, {3, 3}}; // dec_pic->structure idx and mb_adptive_frame_field_flag
static UINT32 g_SliceTypeForPMV[3]    = {1, 2, 0};                    // slice type idx
static UINT32 g_ListStructFrame[4][2] = {{0, 1}, {3, 3}, {3, 3}, {2, 2}}; // list[x][x]->frame->sturcture idx and mb_adptive_frame_field_flag
static UINT32 g_ListStructField[4][2] = {{0, 1}, {2, 2}, {2, 2}, {2, 2}}; // list[x][x]->frame->sturcture idx and mb_adptive_frame_field_flag


UINT32 g_CabacMN[160][8] =
{
    {0x17211702, 0x15001240, 0x92b1d00, 0xb0137, 0x450029, 0x3f003f, 0x3f0000, 0x0},
    {0x14f10236, 0x34ae47f, 0xe968fa35, 0xff360733, 0x1f151f1f, 0x19320000, 0x0, 0x0},
    {0x539f34e, 0xf541013e, 0x1090031, 0xdb760d29, 0x33ef753, 0x4560061, 0xf9480000, 0x0},
    {0x143f34e, 0xf541013e, 0x1a43105a, 0x968d27f, 0xec680000, 0x0, 0x0, 0x0},
    {0xc31fc49, 0x1132fa56, 0xef5ffa3d, 0x92df943, 0xfb4afc4a, 0xfb50f948, 0x13a0000, 0x0},
    {0xfd45fa51, 0xf5600637, 0x743fb56, 0x258003a, 0xfd4cf65e, 0x5360445, 0xfd510058, 0x0},
    {0x16192200, 0x10001a22, 0x13162800, 0xb0137, 0x450029, 0x3f003f, 0x3f0000, 0x0},
    {0x14f10236, 0x34ae47f, 0xe968fa35, 0xff360733, 0x1f151f1f, 0x19320000, 0x0, 0x0},
    {0x241fa47, 0xf34f0534, 0xfe090429, 0xe3760d29, 0x33ef753, 0x4560061, 0xf9480000, 0x0},
    {0xfc4cfa47, 0xf34f0534, 0x39022924, 0x1a45d37f, 0xf1650000, 0x0, 0x0, 0x0},
    {0x932fd46, 0xa360645, 0xf35a0034, 0x82bff42, 0xff4d0146, 0xfe56fb48, 0x3d0000, 0x0},
    {0xfe45fb52, 0xf660023b, 0x24bfd57, 0xfd640138, 0xfd4afa55, 0x3bfd51, 0xf956fb5f, 0x0},
    {0x1d101900, 0xe001428, 0x140a1d00, 0xb0137, 0x450029, 0x3f003f, 0x3f0000, 0x0},
    {0x14f10236, 0x34ae47f, 0xe968fa35, 0xff360733, 0x1f151f1f, 0x19320000, 0x0, 0x0},
    {0x1a10fc55, 0xe8660539, 0xf633fd3e, 0xe5630d29, 0x33ef753, 0x4560061, 0xf9480000, 0x0},
    {0xfe4afc55, 0xe8660539, 0x3600252a, 0xc61e07f, 0xea750000, 0x0, 0x0, 0x0},
    {0x639ef49, 0xe39fa5d, 0xf258fa2c, 0x4370337, 0xfc4ffe4b, 0xf461f932, 0x13c0000, 0x0},
    {0xf559f167, 0xeb741339, 0x143a0454, 0x660013f, 0xfb55f36a, 0x53f064b, 0xfd5aff65, 0x0},
    {0x17211702, 0x15001240, 0x92b1d00, 0x2dfc4e, 0xfd600029, 0x3f003f, 0x3f0000, 0x0},
    {0x14f10236, 0x34ae47f, 0xe968fa35, 0xff360733, 0xc280b33, 0xe3b0000, 0x0, 0x0},
    {0x539f34e, 0xf541013e, 0x1090031, 0xdb760d29, 0x33ef753, 0x4560061, 0xf9480000, 0x0},
    {0x143f34e, 0xf541013e, 0x1a43105a, 0x968d27f, 0xec680000, 0x0, 0x0, 0x0},
    {0xc31fc49, 0x1132fa56, 0xef5ffa3d, 0x92df943, 0xfb4afc4a, 0xfb50f948, 0x13a0000, 0x0},
    {0xfd45fa51, 0xf5600637, 0x743fb56, 0x258003a, 0xfd4cf65e, 0x5360445, 0xfd510058, 0x0},
    {0x16192200, 0x10001a22, 0x13162800, 0xd0f0733, 0x2500029, 0x3f003f, 0x3f0000, 0x0},
    {0x14f10236, 0x34ae47f, 0xe968fa35, 0xff360733, 0x19201531, 0x15360000, 0x0, 0x0},
    {0x241fa47, 0xf34f0534, 0xfe090429, 0xe3760d29, 0x33ef753, 0x4560061, 0xf9480000, 0x0},
    {0xfc4cfa47, 0xf34f0534, 0x39022924, 0x1a45d37f, 0xf1650000, 0x0, 0x0, 0x0},
    {0x932fd46, 0xa360645, 0xf35a0034, 0x82bff42, 0xff4d0146, 0xfe56fb48, 0x3d0000, 0x0},
    {0xfe45fb52, 0xf660023b, 0x24bfd57, 0xfd640138, 0xfd4afa55, 0x3bfd51, 0xf956fb5f, 0x0},
    {0x1d101900, 0xe001428, 0x140a1d00, 0x722f758, 0xec7f0029, 0x3f003f, 0x3f0000, 0x0},
    {0x14f10236, 0x34ae47f, 0xe968fa35, 0xff360733, 0x15211332, 0x113d0000, 0x0, 0x0},
    {0x1a10fc55, 0xe8660539, 0xf633fd3e, 0xe5630d29, 0x33ef753, 0x4560061, 0xf9480000, 0x0},
    {0xfe4afc55, 0xe8660539, 0x3600252a, 0xc61e07f, 0xea750000, 0x0, 0x0, 0x0},
    {0x639ef49, 0xe39fa5d, 0xf258fa2c, 0x4370337, 0xfc4ffe4b, 0xf461f932, 0x13c0000, 0x0},
    {0xf559f167, 0xeb741339, 0x143a0454, 0x660013f, 0xfb55f36a, 0x53f064b, 0xfd5aff65, 0x0},
    {0xef7ff366, 0x52f94a, 0xeb6be57f, 0xe17fe87f, 0xee5fe57f, 0xeb72e27f, 0x0, 0x0},
    {0xef7bf473, 0xf07af573, 0xfd47fa2a, 0xfb32fd36, 0xfe3e003a, 0x13ffe48, 0xff4af75b, 0x0},
    {0xf95df557, 0xfd4dfb47, 0xfc3ffc44, 0xf454f93e, 0xf941083d, 0x538fe42, 0x140003d, 0xfe4e0000},
    {0x18000f09, 0x8190d12, 0xf090d13, 0xa250c12, 0x61d1421, 0xf1e042d, 0x13a003e, 0x73d0000},
    {0xfa5dfa54, 0xf84f0042, 0xff47003e, 0xfe3cfe3b, 0xfb4bfd3e, 0xfc3af742, 0xff4f0047, 0x3440000},
    {0xf060613, 0x7100c0e, 0x120d0d0b, 0xd0f0f10, 0xc170d17, 0xf140e1a, 0xe2c1128, 0x112f0000},
    {0xf43ffe44, 0xf154f368, 0xfb43fb1b, 0xfd27fe2c, 0x2ef040, 0xf844f64e, 0xfa4df656, 0x0},
    {0x1320734, 0xa23002c, 0xb26012d, 0x2e052c, 0x1f110133, 0x7321c13, 0x10210e3e, 0x0},
    {0xc260b2d, 0xf270b2a, 0xd2c102d, 0xc290a31, 0x1e22122a, 0xa371133, 0x112e0059, 0x0},
    {0xa2cf93e, 0xf240e28, 0x101b0c1d, 0x12c1424, 0x1220052a, 0x1300a3e, 0x112e0940, 0x0},
    {0x18111515, 0x19161f1b, 0x161d1323, 0xe320a39, 0x73ffe4d, 0xfc52fd5e, 0x945f46d, 0x0},
    {0xfd46f85d, 0xf65ae27f, 0xf45cf137, 0xf63cfa3e, 0xfc41f449, 0xf84cf950, 0xf758ef6e, 0x0},
    {0xf36cf164, 0xf365f35b, 0xf45ef658, 0xf054f656, 0xf953f357, 0xed5e0146, 0x48fb4a, 0x123b0000},
    {0x1aed16ef, 0x1aef1ee7, 0x1cec21e9, 0x25e521e9, 0x28e426ef, 0x21f528f1, 0x29fa2601, 0x29110000},
    {0xf468f561, 0xf060f958, 0xf855f955, 0xf755f358, 0x442fd4d, 0xfd4cfa4c, 0xa3aff4c, 0xff530000},
    {0x24dd24de, 0x20e625e2, 0x2ce022ee, 0x22f128f1, 0x21f923fb, 0x21002602, 0x210d1723, 0xd3a0000},
    {0xff4afa61, 0xf95bec7f, 0xf561ec54, 0xf54ffa49, 0xfc4af356, 0xf360f561, 0xed750000, 0x0},
    {0xf866f164, 0x5f0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x1efa1b03, 0x1a160000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0xf963f25f, 0x25f0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x1dfd1a00, 0x161e0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0xfc38fb52, 0xf94cea7d, 0xf84efb21, 0xfc30fe35, 0xfd3ef347, 0xf64ff456, 0xf35af261, 0x0},
    {0xfc4b0248, 0xf54bfd47, 0xf2ef345, 0x3e0041, 0x1525f148, 0x9391036, 0x3e0c48, 0x0},
    {0x25f023fc, 0x26f826fd, 0x25032605, 0x2a002310, 0x27160e30, 0x1b25153c, 0xc440261, 0x0},
    {0x4cfb4a, 0x46f54b, 0x1440041, 0xf249033e, 0x43eff44, 0xf34b0b37, 0x5400c46, 0x0},
    {0x1ff923f1, 0x22fd2203, 0x24ff2205, 0x200b2305, 0x220c270b, 0x1e1d221a, 0x1d271342, 0x0},
    {0x0, 0x0, 0xfd4bff17, 0x122012b, 0x36fe37, 0x3d0140, 0x44f75c, 0x0},
    {0xef78ec70, 0xee72f555, 0xf15cf259, 0xe647f151, 0xf2500044, 0xf246e838, 0xe944e832, 0xf54a0000},
    {0x17f31af3, 0x28f131f2, 0x2c032d06, 0x2c222136, 0x13520000, 0x0, 0x0, 0x0},
    {0xf26af361, 0xf15af45a, 0xee58f649, 0xf74ff256, 0xf649f646, 0xf645fb42, 0xf740fb3a, 0x23b0000},
    {0x15f618f5, 0x1cf81cff, 0x1d031d09, 0x23141d24, 0xe430000, 0x0, 0x0, 0x0},
    {0xe57ee462, 0xe765e943, 0xe452ec5e, 0xf053ea6e, 0xeb5bee66, 0xf35de37f, 0x0, 0x0},
    {0xf95cfb59, 0xf960f36c, 0xfa4cfe2c, 0x2d0034, 0xfd40fe3b, 0xfc46fc4b, 0xf852ef66, 0x0},
    {0xfe55fa4e, 0xff4bf94d, 0x2360532, 0xfd440132, 0x62afc51, 0x13ffc46, 0x430239, 0xfe4c0000},
    {0xb1c0228, 0x32c0031, 0x2e022c, 0x233002f, 0x427023e, 0x62e0036, 0x336023a, 0x43f0000},
    {0xf36af06a, 0xf657eb72, 0xee6ef262, 0xea6eeb6a, 0xee67eb6b, 0xe96ce670, 0xf660f45f, 0xfb5b0000},
    {0xe0b0b0e, 0x90b120b, 0x150917fe, 0x20f120f1, 0x22eb27e9, 0x2adf29e1, 0x2ee426f4, 0x151d0000},
    {0xfd2eff41, 0xff39f75d, 0xf74d0318, 0x2a0030, 0x37fa3b, 0xf947f453, 0xf557e277, 0x0},
    {0xb230440, 0x13d0b23, 0x12190c18, 0xd1d0d24, 0xf65df949, 0xfe490d2e, 0x931f964, 0x0},
    {0x6330639, 0x7350634, 0x6370b2d, 0xe240835, 0xff520737, 0xfd4e0f2e, 0x161fff54, 0x0},
    {0xf75dea5e, 0xfb560943, 0xfc50f655, 0xff46073c, 0x93a053d, 0xc320f32, 0x12311136, 0x0},
    {0x2de835d3, 0x30e641d5, 0x2bed27f6, 0x1e09121a, 0x141b0039, 0xf252fb4b, 0xed61dd7d, 0x0},
    {0xfd4af75c, 0xf857e97e, 0x13afd1d, 0xff240126, 0x22bfa37, 0x3a0040, 0xfd4af65a, 0x0},
    {0x9350235, 0x535fe3d, 0x380038, 0xf33ffb3c, 0xff3e0439, 0xfa450439, 0xe270433, 0xd440000},
    {0x19071ef9, 0x1c031c04, 0x200022ff, 0x1e061e06, 0x20091f13, 0x1a1b1a1e, 0x25141c22, 0x11460000},
    {0xa29072e, 0xff330731, 0x8340929, 0x62f0237, 0xd290a2c, 0x6320535, 0xd31043f, 0x6400000},
    {0x1b001c00, 0x1ffc1b06, 0x22081e0a, 0x18162113, 0x16201a1f, 0x15291a2c, 0x172f1041, 0xe470000},
    {0x536063c, 0x63b0645, 0x46fc1d, 0x51f072a, 0x13bfe3a, 0xfd48fd51, 0xf5610000, 0x0},
    {0x340013d, 0x93f0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x143053b, 0x9430000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0xfe45fe3b, 0x6460000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x83c063f, 0x11410000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0xff300044, 0xfc45f858, 0x3a0805, 0xa0e0e12, 0xd1b0228, 0x3afd46, 0xfa4ff855, 0x0},
    {0x7321027, 0x52c0434, 0xb30fb3c, 0xff3b003b, 0x1621052c, 0xe2bff4e, 0x3c0945, 0x0},
    {0x101e1220, 0x1223161d, 0x181f1726, 0x122b1429, 0xb3f093b, 0x940ff5e, 0xfe59f76c, 0x0},
    {0xa2c091f, 0xc2b0335, 0xe220a26, 0xfd340d28, 0x1120072c, 0x7260d32, 0xa391a2b, 0x0},
    {0x15181714, 0x1a171b20, 0x1c171c18, 0x17281820, 0x1c1d172a, 0x13391635, 0x163d0b56, 0x0},
    {0x0, 0x0, 0xfa42f923, 0xf92af82d, 0xfb30f438, 0xfa3cfb3e, 0xf842f84c, 0x0},
    {0xfc4ff947, 0xfb45f746, 0xf842f644, 0xed49f445, 0xf046f143, 0xec3eed46, 0xf042ea41, 0xec3f0000},
    {0x9fe1af7, 0x21f727f9, 0x29fe2d03, 0x31092d1b, 0x243b0000, 0x0, 0x0, 0x0},
    {0xfb55fa51, 0xf64df951, 0xef50ee49, 0xfc4af653, 0xf747f743, 0xff3df842, 0xf242003b, 0x23b0000},
    {0x15f321f2, 0x27f92efe, 0x33023c06, 0x3d113722, 0x2a3e0000, 0x0, 0x0, 0x0},
    {0xd97fee5b, 0xef60e651, 0xdd62e866, 0xe961e577, 0xe863eb6e, 0xee66dc7f, 0x0, 0x0},
    {0x50fb59, 0xf95efc5c, 0xe970f147, 0xf93d0035, 0xfb42f54d, 0xf750f754, 0xf657de7f, 0x0},
    {0xf367f35b, 0xf759f25c, 0xf84cf457, 0xe96ee869, 0xf64eec70, 0xef63b27f, 0xba7fce7f, 0xd27f0000},
    {0x42d0a1c, 0xa1f21f5, 0x34d5120f, 0x1c0023ea, 0x26e72200, 0x27ee20f4, 0x66a20000, 0x38f10000},
    {0xeb7ee97c, 0xec6ee67e, 0xe77cef69, 0xe579e575, 0xef66e675, 0xe574df7a, 0xf65ff264, 0xf85f0000},
    {0x13fa12fa, 0xe001af4, 0x1ff021e7, 0x21ea25e4, 0x27e22ae2, 0x2fd62ddc, 0x31de29ef, 0x20090000},
    {0x270041, 0xf154dd7f, 0xeb65fd27, 0xfb35f93d, 0xf54bf14d, 0xef5be76b, 0xe76fe47a, 0x0},
    {0xfc42fb4e, 0xfc47f848, 0x23bff37, 0xf946fa4b, 0xf859de77, 0xfd4b2014, 0x1e16d47f, 0x0},
    {0x21fc1d0a, 0x25fb33e3, 0x27f734de, 0x45c643c1, 0x2cfb2007, 0x37e32001, 0x1b24, 0x0},
    {0xef6fe472, 0xfa59fe50, 0xfc52f755, 0xf851ff48, 0x5400143, 0x9380045, 0x1450745, 0x0},
    {0x45b93fc1, 0x42c04db6, 0x36d934dd, 0x29f62400, 0x28ff1e0e, 0x1c1a1725, 0xc370b41, 0x0},
    {0xfe49f468, 0xf75be17f, 0xf54cf62c, 0xf634f639, 0xf73af048, 0xf945fc45, 0xfb4af756, 0x0},
    {0x36fb3d, 0x3aff3c, 0xfd3df843, 0xe754f24a, 0xfb410534, 0x239003d, 0xf745f546, 0x12370000},
    {0x21e722e2, 0x24e426e4, 0x26e522ee, 0x23f022f2, 0x20f825fa, 0x23001e0a, 0x1c121a19, 0x1d290000},
    {0xf945fa43, 0xf04dfe40, 0x23dfa43, 0xfd400239, 0xfd41fd42, 0x3e0933, 0xff42fe47, 0xfe4b0000},
    {0x25df27dc, 0x28db26e2, 0x2edf2ae2, 0x28e831e3, 0x26f428f6, 0x26fd2efb, 0x1f141d1e, 0x192c0000},
    {0x3370738, 0x737083d, 0x242f722, 0x1200b1f, 0x534fe37, 0xfe430049, 0xf8590000, 0x0},
    {0xfc47003a, 0x73d0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x4b0248, 0x84d0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0xff46f748, 0xe3c0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0xc300b31, 0x1a2d0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0xfd350044, 0xf94af758, 0x3340704, 0xa081108, 0x10130325, 0xff3dfb49, 0xff46fc4e, 0x0},
    {0x9291219, 0x920052b, 0x92f002c, 0x33022e, 0x1326fc42, 0xf260c2a, 0x9220059, 0x0},
    {0xe23121f, 0x1123151e, 0x112d142a, 0x122d1b1a, 0x10360742, 0x10380b49, 0xa43f674, 0x0},
    {0x1025002f, 0x12230b25, 0xc290a29, 0x2300c29, 0xd29003b, 0x3321328, 0x3421232, 0x0},
    {0x16161716, 0x1b152114, 0x1a1c1e18, 0x1b22122a, 0x19271232, 0xc461536, 0xe470b53, 0x0},
    {0x0, 0x0, 0xfb470018, 0xff24fe2a, 0xfe34f739, 0xfa3ffc41, 0xfc43f952, 0x0},
    {0xfb55fa51, 0xf64df951, 0xef50ee49, 0xfc4af653, 0xf747f743, 0xff3df842, 0xf242003b, 0x23b0000},
    {0x11f620f3, 0x2af731fb, 0x35004003, 0x440a421b, 0x2f390000, 0x0, 0x0, 0x0},
    {0xfd51fd4c, 0xf948fa4e, 0xf448f244, 0xfd46fa4c, 0xfb42fb3e, 0x39fc3d, 0xf73c0136, 0x23a0000},
    {0x11f620f3, 0x2af731fb, 0x35004003, 0x440a421b, 0x2f390000, 0x0, 0x0, 0x0},
    {0xdc7fef5b, 0xf25fe754, 0xe756f459, 0xef5be17f, 0xf24cee67, 0xf35adb7f, 0x0, 0x0},
    {0xb50054c, 0x254054e, 0xe873ea52, 0xf73e0035, 0x3bf255, 0xf359f35e, 0xf55ce37f, 0x0},
    {0xfc56f458, 0xfb52fd48, 0xfc43f848, 0xf059f745, 0xff3b0542, 0x439fc47, 0xfe47023a, 0xff4a0000},
    {0x427002a, 0x7220b1d, 0x81f0625, 0x72a0328, 0x8210d2b, 0xd24042f, 0x337023a, 0x63c0000},
    {0xea7fe77f, 0xe778e57f, 0xed72e975, 0xe776e675, 0xe871e476, 0xe178db7c, 0xf65ef166, 0xf6630000},
    {0x11f310f7, 0x11f41beb, 0x25e229d8, 0x2ad730d1, 0x27e02ed8, 0x34cd2ed7, 0x34d92bed, 0x200b0000},
    {0xfa37043d, 0xf253db7f, 0xeb64f239, 0xf443f547, 0xf64deb55, 0xf058e968, 0xf162db7f, 0x0},
    {0xfc2cff45, 0x3ef933, 0xfc2ffa2a, 0xfd29fa35, 0x84cf74e, 0xf5530934, 0x43fb5a, 0x0},
    {0x82c0b2c, 0xe2a0730, 0x4380434, 0xd250931, 0x133a0a30, 0xc2d0045, 0x1421083f, 0x0},
    {0xf36ace7f, 0xfb5c1139, 0xfb56f35e, 0xf45bfe4d, 0x47ff49, 0x440f951, 0x5400f39, 0x0},
    {0x3dc938d2, 0x3ece51bd, 0x2dec23fe, 0x1c0f2201, 0x27011e11, 0x1426122d, 0xf36004f, 0x0},
    {0xfb4ff568, 0xf55be27f, 0xf652f830, 0xf83df842, 0xf946f24b, 0xf64ff753, 0xf45cee6c, 0x0},
    {0x143f148, 0xfb4bf850, 0xeb53eb40, 0xf31fe740, 0xe35e094b, 0x113ff84a, 0xfb23fe1b, 0xd5b0000},
    {0x23ee21e7, 0x1cfd180a, 0x1b0022f2, 0x34d427e8, 0x13111f19, 0x241d1821, 0x220f1e14, 0x16490000},
    {0x1430044, 0xf6430144, 0x4d0240, 0x44fb4e, 0x737053b, 0x2410e36, 0xf2c053c, 0x2460000},
    {0x24f025f2, 0x25ef2001, 0x220f1d0f, 0x18192216, 0x1f102312, 0x1f1c2129, 0x241c1b2f, 0x153e0000},
    {0x41fe4f, 0x48fc5c, 0xfc4fea45, 0xf04bfe3a, 0x13af34e, 0xf753fc51, 0xf3630000, 0x0},
    {0x341f945, 0x84d0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x1422131f, 0x1b2c0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0xfe4cee56, 0xc460000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x121f131a, 0x24180000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0xfa380344, 0xf847f362, 0xf351fa26, 0xf33efa3a, 0xfe3bf049, 0xf64cf356, 0xf753f657, 0x0},
    {0xf642033e, 0xfd44ec51, 0x1e0107, 0xfd17eb4a, 0x1042e97c, 0x11252cee, 0x32deea7f, 0x0},
    {0x13100f24, 0xf24151c, 0x19151e14, 0x1f0c1b10, 0x182a005d, 0xe380f39, 0x1a26e87f, 0x0},
    {0x540f446, 0xb370538, 0x450241, 0xfa4a0536, 0x736fa4c, 0xf552fe4d, 0xfe4d192a, 0x0},
    {0x18171b10, 0x181e1f1d, 0x1629162a, 0x103c0f34, 0xe3c034e, 0xf07b1535, 0x1638193d, 0x0},
    {0x0, 0x0, 0xf747f925, 0xf82cf531, 0xf638f43b, 0xf83ff743, 0xfa44f64f, 0x0},
    {0xfd4ef84a, 0xf748f648, 0xee4bf447, 0xf53ffb46, 0xef4bf248, 0xf043f835, 0xf23bf734, 0xf5440000},
    {0x9fe1ef6, 0x1ffc21ff, 0x21071f0c, 0x25171f26, 0x14400000, 0x0, 0x0, 0x0},
    {0xfd4ef84a, 0xf748f648, 0xee4bf447, 0xf53ffb46, 0xef4bf248, 0xf043f835, 0xf23bf734, 0xf5440000},
    {0x9fe1ef6, 0x1ffc21ff, 0x21071f0c, 0x25171f26, 0x14400000, 0x0, 0x0, 0x0},
};


/*!
************************************************************************
*   函数原型 :  SINT32 Write_V400R004_CabacTab(UADDR  mn_phy_addr)
*   功能描述 :  写消息池cabac g_CabacMN code tab
*   参数说明 :
*   返回值   ：
************************************************************************
*/
VOID Write_V400R004_CabacTab(UADDR mn_phy_addr)
{
    SINT32 i, j;
    UINT32 *p;

    p = (UINT32 *)MEM_Phy2Vir(mn_phy_addr);

    if (NULL == p)
    {
        dprint(PRN_DBG, "line: %d, p = NULL is not expected value!\n", __LINE__);
        return;
    }

    for (i = 0; i < 160; i++)
    {
        for (j = 0; j < 8; j++)
        {
            *(p++) = g_CabacMN[i][j];
        }
    }

    return;
}


/*****************************************************************************************
原型  SINT32 VDMHAL_Init()
功能  初始化VDMHAL.
    VDMHAL将"消息池"、"寄存器"等信息作为与通道无关的私有资源管理，但消息池是从上层程序
    分配的空间中划拨的，为了实现换台或重启解码器时VDMHAL可以更新消息池地址，必须对外实
    现一个初始化函数。
    本函数的具体功能是：清除静态信息。
参数  无
返回值  成功返回OK（0），否则返回错误码
******************************************************************************************/
SINT32 H264HAL_V400R004_InitHal(VDMHAL_HWMEM_S *pHwMem)
{
    Write_V400R004_CabacTab(pHwMem->H264MnAddr);

    return VDMHAL_OK;
}


/*!
************************************************************************
*   函数原型 :  UINT32 *Get_V400R004_VirAddr(UINT32 Dn，UINT32 *base_vir_addr)
*   功能描述 :  获取对应Dn_num所在行在消息池中的虚拟地址
*   参数说明 :
*   返回值   ：
************************************************************************
*/
UINT32 *Get_V400R004_VirAddr(UINT32 Dn, UINT32 *pbase_vir_addr)
{
    return (pbase_vir_addr + Dn); // one line addr
}


/*!
************************************************************************
*   函数原型 :  UINT32 *Get_V400R004_PhyAddr(UINT32 Dn，UADDR base_phy_addr)
*   功能描述 :  获取对应Dn_num所在行在消息池中的物理地址
*   参数说明 :
*   返回值   ：
************************************************************************
*/
UINT32 Get_V400R004_PhyAddr(UINT32 Dn, UADDR base_phy_addr)
{
    return (base_phy_addr + Dn * 4); // one line addr
}


SINT32 H264HAL_V400R004_CutSliceChain(UADDR CurrMsgSlotPhy )
{
    UINT32 *pSLOT_BASE, *pSLOT;
    UINT32  Dn_num;

    // get base vir addr and phy addr of the slot will write slice para of currslice
    pSLOT_BASE = (UINT32 *)(MEM_Phy2Vir(CurrMsgSlotPhy)); // slot addr
    VDMHAL_ASSERT_RET( pSLOT_BASE != NULL, "can not map slice msg virtual address!\n");
    Dn_num = 0;
    pSLOT = Get_V400R004_VirAddr(Dn_num, pSLOT_BASE);

    //D42
    *(pSLOT + 63) = 0;

    return  VDMHAL_OK;
}


VOID Write_V400R004_Qmatrix(UINT32 *qmatrix, UINT32 size, UADDR phy_addr, UINT32 *vir_addr)
{
    UINT32 i;

    for (i = 0; i < size; i++)
    {
        *(vir_addr + i) = *(qmatrix + i);
        //dprint(PRN_DNMSG, "qmatrix[%d] = 0x%x\n", i,*(qmatrix+i));
        //dprint(PRN_DNMSG, "picmsg Dxx addr 0x%x = 0x%x\n", phy_addr+i*4, *(vir_addr+i));
    }

    return;
}


SINT32 H264HAL_V400R004_SetPicMsg(H264_DEC_PIC_PARAM_S *pParam, VDMHAL_HWMEM_S *pHwMem,
                                  UADDR PicMsgSlotPhy, UADDR FstSlcMsgSlotPhy)
{
    UINT32 *pSLOT, *pSLOT_BASE;
    UADDR  pSlot_phy, pSlot_phy_base;
    UINT32 i, tmp;

    pSLOT_BASE = (UINT32 *)(MEM_Phy2Vir(PicMsgSlotPhy)); // slot addr
    VDMHAL_ASSERT_RET( pSLOT_BASE != NULL, "can not map down msg virtual address!\n");
    pSlot_phy_base = PicMsgSlotPhy;
    pSLOT = pSLOT_BASE;
    pSlot_phy = pSlot_phy_base;

    //D0
    tmp = (pParam->nal_ref_idc != 0) << 31 | \
          pParam->transform_8x8_mode_flag << 28 | \
          pParam->entropy_coding_mode_flag << 27 | \
          pParam->constrained_intra_pred_flag  << 26 | \
          (1 == pParam->chroma_format_idc) << 25 | \
          (pParam->pic_height_in_mb - 1) << 16 | \
          g_StructTrans[pParam->pic_structure][pParam->mb_adaptive_frame_field_flag] << 14 | \
          (pParam->pic_width_in_mb - 1);
    WR_MSGWORD(pSLOT, tmp);
    dprint(PRN_DNMSG, "picmsg D[0] addr 0x%x = 0x%x\n", pSlot_phy + (0x0)*4, *(pSLOT + 0x0));

    //D1
    tmp = (pParam->CurrPicImg2DAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD(pSLOT + 0x1, tmp);
    dprint(PRN_DNMSG, "picmsg D[1] addr 0x%x = 0x%x\n", pSlot_phy + (0x1)*4, *(pSLOT + 0x1));

    //D2
    tmp = pParam->ThisPoc;
    WR_MSGWORD(pSLOT + 0x2, tmp);
    dprint(PRN_DNMSG, "picmsg D[2] addr 0x%x = 0x%x\n", pSlot_phy + (0x2)*4, *(pSLOT + 0x2));

    //D3, D4
    if (pParam->mb_adaptive_frame_field_flag)
    {
        tmp = pParam->TopPoc;
        WR_MSGWORD(pSLOT + 0x3, tmp);
        dprint(PRN_DNMSG, "picmsg D[3] addr 0x%x = 0x%x\n", pSlot_phy + (0x3)*4, *(pSLOT + 0x3));

        tmp = pParam->BottomPoc;
        WR_MSGWORD(pSLOT + 0x4, tmp);
        dprint(PRN_DNMSG, "picmsg D[4] addr 0x%x = 0x%x\n", pSlot_phy + (0x4)*4, *(pSLOT + 0x4));
    }
    else
    {
        tmp = 0;
        WR_MSGWORD(pSLOT + 0x3, tmp);
        dprint(PRN_DNMSG, "picmsg D[3] addr 0x%x = 0x%x\n", pSlot_phy + (0x3)*4, *(pSLOT + 0x3));
        WR_MSGWORD(pSLOT + 0x4, tmp);
        dprint(PRN_DNMSG, "picmsg D[4] addr 0x%x = 0x%x\n", pSlot_phy + (0x4)*4, *(pSLOT + 0x4));
    }

    //D5
    tmp = (pHwMem->SedTopAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD(pSLOT + 0x5, tmp);
    dprint(PRN_DNMSG, "picmsg D[5] addr 0x%x = 0x%x\n", pSlot_phy + (0x5)*4, *(pSLOT + 0x5));

    //D6
    tmp = (pHwMem->PmvTopAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD(pSLOT + 0x6, tmp);
    dprint(PRN_DNMSG, "picmsg D[6] addr 0x%x = 0x%x\n", pSlot_phy + (0x6)*4, *(pSLOT + 0x6));

    //D7
    if (2 != pParam->pic_structure)
    {
        tmp = (pParam->PmvPhyAddr[pParam->CurrPicPmvIdc]) & 0xFFFFFFF0;
    }
    else
    {
        tmp = (pParam->PmvPhyAddr[pParam->CurrPicPmvIdc] + pParam->half_pmvblk_offset) & 0xFFFFFFF0;
    }
    WR_MSGWORD(pSLOT + 0x7, tmp);
    dprint(PRN_DNMSG, "picmsg D[7] addr 0x%x = 0x%x\n", pSlot_phy + (0x7)*4, *(pSLOT + 0x7));

    //D8
    tmp = (pHwMem->RcnTopAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD(pSLOT + 0x8, tmp);
    dprint(PRN_DNMSG, "picmsg D[8] addr 0x%x = 0x%x\n", pSlot_phy + (0x8)*4, *(pSLOT + 0x8));

    //D9
    tmp = (FstSlcMsgSlotPhy + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD(pSLOT + 0x9, tmp);
    dprint(PRN_DNMSG, "picmsg D[9] addr 0x%x = 0x%x\n", pSlot_phy + (0x9)*4, *(pSLOT + 0x9));

    //write D10 ~ D25
    //pic_addr of all apc
    for (i = 0; i < pParam->ApcSize; i++)
    {
        tmp = (pParam->ImgPhyAddr[pParam->Apc2Idc[i]]) & 0xFFFFFFF0;
        WR_MSGWORD(pSLOT + 10 + i, tmp);
        dprint(PRN_DNMSG, "picmsg D[%d] addr 0x%x = 0x%x\n", i+10, pSlot_phy + (i+10)*4, *(pSLOT + i + 10));
    }

    for (i = pParam->ApcSize; i < 16 ; i++)
    {
        tmp = (pParam->ImgPhyAddr[pParam->Apc2Idc[0]]) & 0xFFFFFFF0;
        WR_MSGWORD(pSLOT + 10 + i, tmp);
        dprint(PRN_DNMSG, "picmsg D[%d] addr 0x%x = 0x%x\n", i+10, pSlot_phy + (i+10)*4, *(pSLOT + i + 10));
    }

    //D26
    tmp = (pHwMem->H264MnAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD(pSLOT + 26, tmp);
    dprint(PRN_DNMSG, "picmsg D[26] addr 0x%x = 0x%x\n", pSlot_phy + (26)*4, *(pSLOT + 26));

    //D27~D58
    for (i = 0; i < pParam->ApcSize; i++)
    {
        tmp = pParam->Apc2Poc[0][i];
        WR_MSGWORD(pSLOT + 27 + 2 * i, tmp);
        dprint(PRN_DNMSG, "picmsg D[%d] addr 0x%x = 0x%x\n", 2*i+27, pSlot_phy + (2*i+27)*4, *(pSLOT + (2*i+27)));

        tmp = pParam->Apc2Poc[1][i];
        WR_MSGWORD(pSLOT + 27 + 2 * i + 1, tmp);
        dprint(PRN_DNMSG, "picmsg D[%d] addr 0x%x = 0x%x\n", 2*i+1+27, pSlot_phy + (2*i+1+27)*4, *(pSLOT + (2*i+1+27)));
    }

    for (i = pParam->ApcSize; i < 16; i++)
    {
        tmp = 0;
        WR_MSGWORD(pSLOT + 27 + 2 * i, tmp);
        dprint(PRN_DNMSG, "picmsg D[%d] addr 0x%x = 0x%x\n", 2*i+27, pSlot_phy + (2*i+27)*4, *(pSLOT + (2*i+27)));

        tmp = 0;
        WR_MSGWORD(pSLOT + 27 + 2 * i + 1, tmp);
        dprint(PRN_DNMSG, "picmsg D[%d] addr 0x%x = 0x%x\n", 2*i+1+27, pSlot_phy + (2*i+1+27)*4, *(pSLOT + (2*i+1+27)));
    }


    //D59
    tmp = (pHwMem->DblkTopAddr + 0xF) & 0xFFFFFFF0;
    WR_MSGWORD(pSLOT + 59, tmp);
    dprint(PRN_DNMSG, "picmsg D[59] addr 0x%x = 0x%x\n", pSlot_phy + (59)*4, *(pSLOT + 59));

    //burst 1
    pSLOT = pSLOT_BASE + 64;
    pSlot_phy = pSlot_phy_base + 64 * 4;
    Write_V400R004_Qmatrix(&(pParam->Qmatrix[0]), 56, pSlot_phy + 4 * 0, pSLOT + 0);

    return 0;
}


SINT32 H264HAL_V400R004_SetSliceMsg(H264_DEC_PIC_PARAM_S *pParam, VDMHAL_HWMEM_S *pHwMem, H264_DEC_SLICE_PARAM_S *pSlcPara,
                                    UADDR CurrMsgSlotPhy, UADDR  ForwardSlcMsgPhy, UADDR NextSlcMsgSlotPhy, SINT32 first_mb_in_slice, SINT32 last_mb_in_slice)
{
    UINT32 *pSLOT, *pSLOT_BASE;
    UINT32 *pSLOT_line0, *pSLOT_line1, *pSLOT_line2;
    UADDR  pSLOT_phy_base, pSLOT_phy, pSLOT_line0_phy=0, pSLOT_line1_phy=0, pSLOT_line2_phy=0;
    UINT32 Dn_num, Dn_0, Dn_1, Dn_2;
    UINT32 i;
    UINT32 tmp, tmp1, tmp2;
    UADDR stream_base_addr, stream_start_addr;

    // get base vir addr and phy addr of the slot will write slice para of currslice
    pSLOT_BASE = (UINT32 *)(MEM_Phy2Vir(CurrMsgSlotPhy)); // slot addr
    VDMHAL_ASSERT_RET( pSLOT_BASE != NULL, "can not map slice msg virtual address!\n");
    pSLOT_phy_base = (UINT32)CurrMsgSlotPhy;

    Dn_num = 0;
    pSLOT = Get_V400R004_VirAddr(Dn_num, pSLOT_BASE);
    pSLOT_phy = Get_V400R004_PhyAddr(Dn_num, pSLOT_phy_base);

    for (i = 0; i < 2; i++)
    {
        if (0 < pSlcPara->valid_bitlen[i])
        {
            stream_base_addr = (pParam->stream_base_addr & 0xfffffff0);
            stream_start_addr = (pSlcPara->bytespos[i] & 0xfffffff0);
            tmp = (pSlcPara->bitsoffset[i] + 8 * (pSlcPara->bytespos[i] & 0xf)) & 0x7f ;
            WR_MSGWORD(pSLOT + 3 * i + 1, tmp);
            dprint(PRN_DNMSG, "slicemsg D[%d] addr 0x%x = 0x%x\n", 3*i + 1, pSLOT_phy+(3*i+1)*4, *(pSLOT + 3*i+1));

            tmp = pSlcPara->valid_bitlen[i];
            WR_MSGWORD(pSLOT + 3 * i + 2, tmp);
            dprint(PRN_DNMSG, "slicemsg D[%d] addr 0x%x = 0x%x\n", 3*i + 2, pSLOT_phy + (3*i+2)*4, *(pSLOT + 3*i+2));

            tmp = (stream_start_addr - stream_base_addr);
            WR_MSGWORD(pSLOT + 3 * i, tmp);
            dprint(PRN_DNMSG, "slicemsg D[%d] addr 0x%x = 0x%x\n", 3*i, pSLOT_phy + (3*i)*4, *(pSLOT + 3*i));
        }
        else
        {
            tmp = 0;
            WR_MSGWORD(pSLOT + 3 * i, tmp);
            dprint(PRN_DNMSG, "slicemsg D[%d] addr 0x%x = 0x%x\n", 3*i, pSLOT_phy+(3*i)*4, *(pSLOT + 3*i));

            tmp = 0;
            WR_MSGWORD(pSLOT + 3 * i + 1, tmp);
            dprint(PRN_DNMSG, "slicemsg D[%d] addr 0x%x = 0x%x\n", 3*i + 1, pSLOT_phy + (3*i + 1)*4, *(pSLOT + 3*i + 1));

            tmp = 0;
            WR_MSGWORD(pSLOT + 3 * i + 2, tmp);
            dprint(PRN_DNMSG, "slicemsg D[%d] addr 0x%x = 0x%x\n", 3*i + 2, pSLOT_phy + (3*i + 2)*4, *(pSLOT + 3*i + 2));

        }
    }


    //D4
    //--------------------------large resolution
    tmp = pSlcPara->SliceQPy << 26 |((pSlcPara->cabac_init_idc & 0x3) << 24) | ( pSlcPara->first_mb_in_slice & 0xfffff);
    WR_MSGWORD(pSLOT + 6, tmp);
    dprint(PRN_DNMSG, "slicemsg D[4] addr 0x%x = 0x%x\n", pSLOT_phy + (0x6)*4, *(pSLOT + 0x6));

    if ((0 == g_not_direct_8x8_inference_flag) &&  (0 == pSlcPara->direct_8x8_inference_flag) && (pParam->pic_width_in_mb * pParam->frame_height_in_mb > 45 * 36) )
    {
        return VDMHAL_ERR;
    }

    //D5
    tmp = ((pSlcPara->num_ref_idx_l1_active_minus1 & 0x1f) << 21) |
          ((pSlcPara->num_ref_idx_l0_active_minus1 & 0x1f) << 16) |
          (pSlcPara->direct_spatial_mv_pred_flag << 15) |
          (pSlcPara->direct_8x8_inference_flag << 14) |
          (pSlcPara->listXsize[1] << 8) |
          (pSlcPara->listXsize[0] << 2) |
          g_SliceTypeForPMV[pSlcPara->slice_type];
    WR_MSGWORD(pSLOT + 7, tmp);
    dprint(PRN_DNMSG, "slicemsg D[5] addr 0x%x = 0x%x\n", pSLOT_phy + (0x7)*4, *(pSLOT + 0x7));

    // mv地址
    // D6~D7 list[1][0] pmv_addr when B Slice
    if (2 == g_SliceTypeForPMV[pSlcPara->slice_type])
    {
        if (0 == pParam->pic_structure) // frame
        {
            if (pSlcPara->declist[1][0].frame_structure != 3)
            {
                // not field pair
                tmp = (pParam->PmvPhyAddr[pSlcPara->declist[1][0].pmv_address_idc]) & 0xFFFFFFF0;
                tmp1 = 0;
            }
            else
            {
                // field pair
                tmp = (pParam->PmvPhyAddr[pSlcPara->declist[1][0].pmv_address_idc]) & 0xFFFFFFF0;
                tmp1 = (pParam->PmvPhyAddr[pSlcPara->declist[1][0].pmv_address_idc] + pParam->half_pmvblk_offset) & 0xFFFFFFF0;
            }
        }
        else // field
        {
            if ((0 == pSlcPara->declist[1][0].frame_structure) && (3 == pSlcPara->declist[1][0].is_used))
            {
                // frame or mbaff frame
                tmp = (pParam->PmvPhyAddr[pSlcPara->declist[1][0].pmv_address_idc]) & 0xFFFFFFF0;
            }
            else
            {
                // decode field
                if (1 == pSlcPara->declist[1][0].list_structure)
                {
                    // top field
                    tmp = (pParam->PmvPhyAddr[pSlcPara->declist[1][0].pmv_address_idc]) & 0xFFFFFFF0;
                }
                else
                {
                    // bottom field
                    tmp = (pParam->PmvPhyAddr[pSlcPara->declist[1][0].pmv_address_idc] + pParam->half_pmvblk_offset) & 0xFFFFFFF0;
                }
            }

            tmp1 = 0;
        }
    }
    else
    {
        tmp = 0;
        tmp1 = 0;
    }

    WR_MSGWORD(pSLOT + 8, tmp);
    dprint(PRN_DNMSG, "slicemsg D[6] addr 0x%x = 0x%x\n", pSLOT_phy + (0x8)*4, *(pSLOT + 0x8));
    WR_MSGWORD(pSLOT + 9, tmp1);
    dprint(PRN_DNMSG, "slicemsg D[7] addr 0x%x = 0x%x\n", pSLOT_phy + (0x9)*4, *(pSLOT + 0x9));

    // D8
    tmp = (pSlcPara->weight_flag << 16) |
          ((pSlcPara->chroma_qp_index_offset & 0x1f) << 5) |
          (pSlcPara->second_chroma_qp_index_offset & 0x1f);
    WR_MSGWORD(pSLOT + 10, tmp);
    dprint(PRN_DNMSG, "slicemsg D[8] addr 0x%x = 0x%x\n", pSLOT_phy + (10)*4, *(pSLOT + 10));

    // D9
    tmp = ((pSlcPara->slice_alpha_c0_offset_div2 & 0xf) << 16) |
          ((pSlcPara->slice_beta_offset_div2 & 0xf) << 8) |
          (pSlcPara->disable_deblocking_filter_idc);
    WR_MSGWORD(pSLOT + 11, tmp);
    dprint(PRN_DNMSG, "slicemsg D[9] addr 0x%x = 0x%x\n", pSLOT_phy + (11)*4, *(pSLOT + 11));

    //D44
    if (pSlcPara->pNextSlice != NULL)
    {
        //tmp = pSlcPara->pNextSlice->first_mb_in_slice - 1;
        tmp = last_mb_in_slice;
    }
    else
    {
        if ((1 + pSlcPara->MbaffFrameFlag) == 0)
        {
            return VDMHAL_ERR;
        }

        tmp = (pParam->mbtodec > MAX_MB_NUM_IN_PIC ? (MAX_MB_NUM_IN_PIC - 1) / (1 + pSlcPara->MbaffFrameFlag) : (pParam->mbtodec - 1) / (1 + pSlcPara->MbaffFrameFlag));
    }

    WR_MSGWORD(pSLOT + 44, tmp);

    //D63 next slice msg addr
    tmp = NextSlcMsgSlotPhy & 0xFFFFFFF0;
    WR_MSGWORD(pSLOT + 63, tmp);

    // 参考列表 & poc
    if (g_SliceTypeForPMV[pSlcPara->slice_type] != 0) // P,B Slice
    {
        if (0 == pParam->pic_structure) // frame reference
        {
            // D10~D13  D18~D25 list0
            tmp = 0;  //clean here is very importante
            Dn_num = 12;
            tmp1 = 0;
            Dn_0 = 20;

            for (i = 0; i < pSlcPara->listXsize[0]; i++)
            {
                tmp |= ((((1 == pSlcPara->declist[0][i].frame_is_long_term) << 3) |
                         ((g_ListStructFrame[pSlcPara->declist[0][i].frame_structure][pParam->mb_adaptive_frame_field_flag]  ) & 0x3)) << 4 * (i % 8));
                tmp1 |= (((pSlcPara->declist[0][i].apc_idc << 1) & 0x1f) << 5 * (i % 4));

                if (7 == (i % 8))
                {
                    WR_MSGWORD(pSLOT + Dn_num, tmp);
                    dprint(PRN_DNMSG, "slicemsg D[%d] address 0x%x = 0x%x\n", Dn_num, pSLOT_phy + 4*Dn_num, *(pSLOT + Dn_num));
                    Dn_num++;
                    tmp = 0;
                }

                if (3 == (i % 4))
                {
                    WR_MSGWORD(pSLOT + Dn_0, tmp1);
                    dprint(PRN_DNMSG, "slicemsg D[%d] address 0x%x = 0x%x\n", Dn_0, pSLOT_phy + 4*Dn_0, *(pSLOT + Dn_0));
                    Dn_0++;
                    tmp1 = 0;
                }
            }

            if (0 != (pSlcPara->listXsize[0] % 8))
            {
                WR_MSGWORD(pSLOT + Dn_num, tmp);
                dprint(PRN_DNMSG, "slicemsg D[%d] address 0x%x = 0x%x\n", Dn_num, pSLOT_phy + 4*Dn_num, *(pSLOT + Dn_num));
                WR_MSGWORD(pSLOT + Dn_0, tmp1);
                dprint(PRN_DNMSG, "slicemsg D[%d] address 0x%x = 0x%x\n", Dn_0, pSLOT_phy + 4*Dn_0, *(pSLOT + Dn_0));
            }

            // list1
            if (2 == g_SliceTypeForPMV[pSlcPara->slice_type])
            {
                tmp = 0;
                Dn_num = 16;
                tmp1 = 0;
                Dn_0 = 28;

                for (i = 0; i < pSlcPara->listXsize[1]; i++)
                {
                    tmp |= ((((1 == pSlcPara->declist[1][i].frame_is_long_term) << 3) |
                             ((g_ListStructFrame[pSlcPara->declist[1][i].frame_structure][pParam->mb_adaptive_frame_field_flag] ) & 0x3)) << 4 * (i % 8));
                    tmp1 |= (((pSlcPara->declist[1][i].apc_idc << 1) & 0x1f) << 5 * (i % 4));

                    if (7 == (i % 8))
                    {
                        WR_MSGWORD(pSLOT + Dn_num, tmp);
                        dprint(PRN_DNMSG, "slicemsg D[%d] address 0x%x = 0x%x\n", Dn_num, pSLOT_phy + 4*Dn_num, *(pSLOT + Dn_num));
                        Dn_num++;
                        tmp = 0;
                    }

                    if (3 == (i % 4))
                    {
                        WR_MSGWORD(pSLOT + Dn_0, tmp1);
                        dprint(PRN_DNMSG, "slicemsg D[%d] address 0x%x = 0x%x\n", Dn_0, pSLOT_phy + 4*Dn_0, *(pSLOT + Dn_0));
                        Dn_0++;
                        tmp1 = 0;
                    }
                }

                if (0 != (pSlcPara->listXsize[1] % 8))
                {
                    WR_MSGWORD(pSLOT + Dn_num, tmp);
                    dprint(PRN_DNMSG, "slicemsg D[%d] address 0x%x = 0x%x\n", Dn_num, pSLOT_phy + 4*Dn_num, *(pSLOT + Dn_num));
                    WR_MSGWORD(pSLOT + Dn_0, tmp1);
                    dprint(PRN_DNMSG, "slicemsg D[%d] address 0x%x = 0x%x\n", Dn_0, pSLOT_phy + 4*Dn_0, *(pSLOT + Dn_0));
                }
            }
        }
        else // field reference
        {
            // P,B Slice
            // D10~D13     list0
            tmp = 0;
            Dn_num = 12;
            tmp1 = 0;
            Dn_0 = 20;

            for (i = 0; i < pSlcPara->listXsize[0]; i++)
            {
                if (1 == pSlcPara->declist[0][i].list_structure)
                {
                    //top field
                    if (pSlcPara->declist[0][i].is_used != 3)
                    {
                        tmp |= ((((1 == pSlcPara->declist[0][i].top_is_long_term) << 3) |
                                 ((1 == pSlcPara->declist[0][i].top_structure)    << 2 ) |
                                 ((g_ListStructField[pSlcPara->declist[0][i].top_structure][pParam->mb_adaptive_frame_field_flag]) & 0x3)) << 4 * (i % 8));
                    }
                    else
                    {
                        tmp |= ((((1 == pSlcPara->declist[0][i].top_is_long_term) << 3) |
                                 ((1 == pSlcPara->declist[0][i].top_structure)    << 2 ) |
                                 ((g_ListStructField[pSlcPara->declist[0][i].frame_structure][pParam->mb_adaptive_frame_field_flag]) & 0x3)) << 4 * (i % 8));
                    }

                    tmp1 |= ((((pSlcPara->declist[0][i].apc_idc << 1)) & 0x1f) << 5 * (i % 4));
                }
                else if (2 == pSlcPara->declist[0][i].list_structure)
                {
                    //bottom field
                    if (pSlcPara->declist[0][i].is_used != 3)
                    {
                        tmp |= ((((1 == pSlcPara->declist[0][i].btm_is_long_term) << 3) |
                                 ((1 == pSlcPara->declist[0][i].btm_structure)    << 2 ) |
                                 ((g_ListStructField[pSlcPara->declist[0][i].btm_structure][pParam->mb_adaptive_frame_field_flag]) & 0x3)) << 4 * (i % 8));
                    }
                    else
                    {
                        tmp |= ((((1 == pSlcPara->declist[0][i].btm_is_long_term) << 3) |
                                 ((1 == pSlcPara->declist[0][i].btm_structure)    << 2 ) |
                                 ((g_ListStructField[pSlcPara->declist[0][i].frame_structure][pParam->mb_adaptive_frame_field_flag]) & 0x3)) << 4 * (i % 8));
                    }

                    tmp1 |= ((((pSlcPara->declist[0][i].apc_idc << 1) | 1) & 0x1f) << 5 * (i % 4));
                }
                else
                {

                }

                if (7 == (i % 8))
                {
                    WR_MSGWORD(pSLOT + Dn_num, tmp);
                    dprint(PRN_DNMSG, "slicemsg D[%d] address 0x%x = 0x%x\n", Dn_num, pSLOT_phy + 4*Dn_num, *(pSLOT + Dn_num));
                    Dn_num++;
                    tmp = 0;
                }

                if (3 == (i % 4))
                {
                    WR_MSGWORD(pSLOT + Dn_0, tmp1);
                    dprint(PRN_DNMSG, "slicemsg D[%d] address 0x%x = 0x%x\n", Dn_0, pSLOT_phy + 4*Dn_0, *(pSLOT + Dn_0));
                    Dn_0++;
                    tmp1 = 0;
                }
            }

            if (0 != (pSlcPara->listXsize[0] % 8))
            {
                WR_MSGWORD(pSLOT + Dn_num, tmp);
                dprint(PRN_DNMSG, "slicemsg D[%d] address 0x%x = 0x%x\n", Dn_num, pSLOT_phy + 4*Dn_num, *(pSLOT + Dn_num));
                WR_MSGWORD(pSLOT + Dn_0, tmp1);
                dprint(PRN_DNMSG, "slicemsg D[%d] address 0x%x = 0x%x\n", Dn_0, pSLOT_phy + 4*Dn_0, *(pSLOT + Dn_0));
            }


            if (2 == g_SliceTypeForPMV[pSlcPara->slice_type]) // B Slice
            {
                tmp = 0;
                Dn_num = 16;
                tmp1 = 0;
                Dn_0 = 28;

                for (i = 0; i < pSlcPara->listXsize[1]; i++)
                {
                    if (1 == pSlcPara->declist[1][i].list_structure)
                    {
                        //top field
                        if (pSlcPara->declist[1][i].is_used != 3)
                        {
                            tmp |= ((((1 == pSlcPara->declist[1][i].top_is_long_term) << 3) |
                                     ((1 == pSlcPara->declist[1][i].top_structure)    << 2 ) |
                                     ((g_ListStructField[pSlcPara->declist[1][i].top_structure][pParam->mb_adaptive_frame_field_flag]) & 0x3)) << 4 * (i % 8));
                        }
                        else
                        {
                            tmp |= ((((1 == pSlcPara->declist[1][i].top_is_long_term) << 3) |
                                     ((1 == pSlcPara->declist[1][i].top_structure)    << 2 ) |
                                     ((g_ListStructField[pSlcPara->declist[1][i].frame_structure][pParam->mb_adaptive_frame_field_flag]) & 0x3)) << 4 * (i % 8));
                        }

                        tmp1 |= ((((pSlcPara->declist[1][i].apc_idc << 1)) & 0x1f) << 5 * (i % 4));
                    }
                    else if (2 == pSlcPara->declist[1][i].list_structure)
                    {
                        //bottom field
                        if (pSlcPara->declist[1][i].is_used != 3)
                        {
                            tmp |= ((((1 == pSlcPara->declist[1][i].btm_is_long_term) << 3) |
                                     ((1 == pSlcPara->declist[1][i].btm_structure)    << 2 ) |
                                     ((g_ListStructField[pSlcPara->declist[1][i].btm_structure][pParam->mb_adaptive_frame_field_flag]) & 0x3)) << 4 * (i % 8));
                        }
                        else
                        {
                            tmp |= ((((1 == pSlcPara->declist[1][i].btm_is_long_term) << 3) |
                                     ((1 == pSlcPara->declist[1][i].btm_structure)    << 2 ) |
                                     ((g_ListStructField[pSlcPara->declist[1][i].frame_structure][pParam->mb_adaptive_frame_field_flag]) & 0x3)) << 4 * (i % 8));
                        }

                        tmp1 |= ((((pSlcPara->declist[1][i].apc_idc << 1) | 1) & 0x1f) << 5 * (i % 4));
                    }
                    else
                    {

                    }

                    if (7 == (i % 8))
                    {
                        WR_MSGWORD(pSLOT + Dn_num, tmp);
                        dprint(PRN_DNMSG, "slicemsg D[%d] address 0x%x = 0x%x\n", Dn_num, pSLOT_phy + 4*Dn_num, *(pSLOT + Dn_num));
                        Dn_num++;
                        tmp = 0;
                    }

                    if (3 == (i % 4))
                    {
                        WR_MSGWORD(pSLOT + Dn_0, tmp1);
                        dprint(PRN_DNMSG, "slicemsg D[%d] address 0x%x = 0x%x\n", Dn_0, pSLOT_phy + 4*Dn_0, *(pSLOT + Dn_0));
                        Dn_0++;
                        tmp1 = 0;
                    }
                }

                if (0 != (pSlcPara->listXsize[1] % 8))
                {
                    WR_MSGWORD(pSLOT + Dn_num, tmp);
                    dprint(PRN_DNMSG, "slicemsg D[%d] address 0x%x = 0x%x\n", Dn_num, pSLOT_phy + 4*Dn_num, *(pSLOT + Dn_num));
                    WR_MSGWORD(pSLOT + Dn_0, tmp1);
                    dprint(PRN_DNMSG, "slicemsg D[%d] address 0x%x = 0x%x\n", Dn_0, pSLOT_phy + 4*Dn_0, *(pSLOT + Dn_0));
                }
            }
        }

        //add apc->refidx  D34~D41
        tmp = 0;
        Dn_num = 36;

        for (i = 0; i < 32; i++)
        {
            tmp |= ((( pSlcPara->Apc2RefIdx[i] ) & 0x1f) << 5 * (i % 4));

            if (3 == (i % 4))
            {
                WR_MSGWORD(pSLOT + Dn_num, tmp);
                dprint(PRN_DNMSG, "slicemsg D[%d] address 0x%x = 0x%x\n", Dn_num, pSLOT_phy + 4*Dn_num, *(pSLOT + Dn_num));
                Dn_num++;
                tmp = 0;
            }
        }

        // add weight tab
        if ((pParam->weighted_pred_flag && (1 == g_SliceTypeForPMV[pSlcPara->slice_type])) ||
            ((1 == pParam->weighted_bipred_idc) && (2 == g_SliceTypeForPMV[pSlcPara->slice_type])))
        {
            // list0

            // D0~D31  of burst1, Dn_num = 1*64 + D0 ,luma wp
            Dn_0 = 64;
            pSLOT_line0 = Get_V400R004_VirAddr(Dn_0, pSLOT_BASE) ;
            pSLOT_line0_phy = Get_V400R004_PhyAddr(Dn_0, pSLOT_phy_base);

            // D0~D31 of burst2, Dn_num = 2*64 + D0, cb wp
            Dn_1 = 128;
            pSLOT_line1 = Get_V400R004_VirAddr(Dn_1, pSLOT_BASE) ;
            pSLOT_line1_phy = Get_V400R004_PhyAddr(Dn_1, pSLOT_phy_base);

            // D0~D31  of  burst3, Dn_num = 3*64 + D0, cr wp
            Dn_2 = 192;
            pSLOT_line2 = Get_V400R004_VirAddr(Dn_2, pSLOT_BASE) ;
            pSLOT_line2_phy = Get_V400R004_PhyAddr(Dn_2, pSLOT_phy_base);

            for (i = 0; i <= pSlcPara->num_ref_idx_l0_active_minus1; i++)
            {
                tmp = ((pSlcPara->wp_offset_l0_y[i] & 0xff) << 12) |
                      ((pSlcPara->wp_weight_l0_y[i] & 0x1ff) << 3) |
                      (pSlcPara->luma_log2_weight_denom & 0x7);
                WR_MSGWORD(pSLOT_line0 + i, tmp);
                dprint(PRN_DNMSG, "slicemsg D[%d] address 0x%x = 0x%x\n",  i + Dn_0 , pSLOT_line0_phy + 4*i, *(pSLOT_line0 + i));

                tmp1 = ((pSlcPara->wp_offset_l0_u[i] & 0xff) << 12) |
                       ((pSlcPara->wp_weight_l0_u[i] & 0x1ff) << 3) |
                       (pSlcPara->chroma_log2_weight_denom & 0x7);
                WR_MSGWORD(pSLOT_line1 + i, tmp1);
                dprint(PRN_DNMSG, "slicemsg D[%d] address 0x%x = 0x%x\n", i + Dn_1, pSLOT_line1_phy + 4*i, *(pSLOT_line1 + i));

                tmp2 = ((pSlcPara->wp_offset_l0_v[i] & 0xff) << 9 ) |
                       (pSlcPara->wp_weight_l0_v[i] & 0x1ff);
                WR_MSGWORD(pSLOT_line2 + i, tmp2);
                dprint(PRN_DNMSG, "slicemsg D[%d] address 0x%x = 0x%x\n", i + Dn_2, pSLOT_line2_phy + 4*i, *(pSLOT_line2 + i));
            }

            if (2 == g_SliceTypeForPMV[pSlcPara->slice_type])
            {
                for (i = 0; i <= pSlcPara->num_ref_idx_l1_active_minus1; i++)
                {
                    dprint(PRN_DNMSG, "wp_weight_l1_y = %d\n", pSlcPara->wp_weight_l1_y[i] );
                    dprint(PRN_DNMSG, "wp_offset_l1_y = %d\n", pSlcPara->wp_offset_l1_y[i] );
                }
            }

            // list1
            if (2 == g_SliceTypeForPMV[pSlcPara->slice_type]) // B Slice
            {
                for (i = 0; i <= pSlcPara->num_ref_idx_l1_active_minus1; i++)
                {
                    tmp = ((pSlcPara->wp_offset_l1_y[i] & 0xff) << 12) |
                          ((pSlcPara->wp_weight_l1_y[i] & 0x1ff) << 3) |
                          (pSlcPara->luma_log2_weight_denom & 0x7);
                    WR_MSGWORD(pSLOT_line0 + i + 32, tmp);
                    dprint(PRN_DNMSG, "slicemsg D[%d] address 0x%x = 0x%x\n", i + 32 + Dn_0, pSLOT_line0_phy + 4*(i + 32), *(pSLOT_line0 + i + 32));

                    tmp1 = ((pSlcPara->wp_offset_l1_u[i] & 0xff) << 12) |
                           ((pSlcPara->wp_weight_l1_u[i] & 0x1ff) << 3) |
                           (pSlcPara->chroma_log2_weight_denom & 0x7);
                    WR_MSGWORD(pSLOT_line1 + i + 32, tmp1);
                    dprint(PRN_DNMSG, "slicemsg D[%d] address 0x%x = 0x%x\n", i + 32 + Dn_1, pSLOT_line1_phy + 4*(i + 32), *(pSLOT_line1 + i + 32));

                    tmp2 = ((pSlcPara->wp_offset_l1_v[i] & 0xff) << 9 ) |
                           (pSlcPara->wp_weight_l1_v[i] & 0x1ff);
                    WR_MSGWORD(pSLOT_line2 + i + 32, tmp2);
                    dprint(PRN_DNMSG, "slicemsg D[%d] address 0x%x = 0x%x\n", i + 32 + Dn_2, pSLOT_line2_phy + 4*(i + 32), *(pSLOT_line2 + i + 32));
                }
            }
        }
    }

    return VDMHAL_OK;
}


SINT32 H264HAL_V400R004_StartDec(H264_DEC_PIC_PARAM_S *pParam, SINT32 VdhId)
{
    VDMHAL_HWMEM_S *pHwMem = &g_HwMem[VdhId];
    H264_DEC_SLICE_PARAM_S *pSlicePara;
    H264_DEC_SLICE_PARAM_S *tmp_pSlicePara = NULL;
    SINT32 valid_bitlen[2];
    SINT32 bitsoffset[2];
    SINT32 bytespos[2];
    SINT32 tmp_first_mb_in_slice = 0;
    SINT32 AddSlice0Flag = 0;
    SINT32 *p32;
    SINT32 D32, i, j;
    UINT32 datTmp;
    UADDR  prev_slcmsg_phy, next_slcmsg_phy,cur_slcmsg_phy;
    SINT32 pre_first_mb_in_slice, first_mb_in_slice, last_mb_in_slice;
    UINT32 level = 16;
    UINT32 count = 0;
#ifdef VFMW_MODULE_LOWDLY_SUPPORT
    SINT32 ChanId = g_VdmDrvParam[VdhId].ChanId;
    SINT32 ModuleLowlyEnable = 0;
#endif

    if (VdhId > (MAX_VDH_NUM - 1))
    {
        dprint(PRN_FATAL, "%s: VdhId(%d) > %d\n", __func__, VdhId, (MAX_VDH_NUM - 1));
        return VDMHAL_ERR;
    }

#ifdef VFMW_MODULE_LOWDLY_SUPPORT
    if (NULL != s_pstVfmwChan[ChanId])
    {
        ModuleLowlyEnable = s_pstVfmwChan[ChanId]->stSynExtraData.s32ModuleLowlyEnable;
    }
    else
    {
        ModuleLowlyEnable = 0;
    }
#endif

    /* 1.  检查参数是否超出规格 */
    VDMHAL_ASSERT_RET(NULL != pParam, "point of picture para null\n");
    VDMHAL_ASSERT_RET(pParam->pic_width_in_mb <= MAX_IMG_WIDTH_IN_MB, "picture width out of range\n");
    VDMHAL_ASSERT_RET(pParam->pic_height_in_mb <= MAX_IMG_HEIGHT_IN_MB, "picture width out of range\n");
    VDMHAL_ASSERT_RET(NULL != pParam->pFirstSlice, "point of fst slice para null\n");

    if ( NULL == pHwMem->pVdmRegVirAddr )
    {
        if ( NULL != (p32 = (SINT32 *)MEM_Phy2Vir(gVdhRegBaseAddr)) )
        {
            pHwMem->pVdmRegVirAddr = p32;
        }
        else
        {
            dprint(PRN_FATAL, "vdm register virtual address not mapped, reset failed!\n");
            return VDMHAL_ERR;
        }
    }

    dprint(PRN_VDMREG, "\n\n***********************H264HAL_StartDec ***********************\n");

    /* 2.  配置寄存器(启动寄存器除外) */
    //BASIC_V400R004_CFG0
    D32 = 0;
    ((BASIC_V400R004_CFG0 *)(&D32))->mbamt_to_dec         = (pParam->mbtodec > MAX_MB_NUM_IN_PIC ? MAX_MB_NUM_IN_PIC - 1 : pParam->mbtodec - 1);
    ((BASIC_V400R004_CFG0 *)(&D32))->load_qmatrix_flag    = 1;
    ((BASIC_V400R004_CFG0 *)(&D32))->marker_bit_detect_en = 0;
    ((BASIC_V400R004_CFG0 *)(&D32))->ac_last_detect_en    = 0;
    ((BASIC_V400R004_CFG0 *)(&D32))->coef_idx_detect_en   = 1;
    ((BASIC_V400R004_CFG0 *)(&D32))->vop_type_detect_en   = 0;
#ifdef ENV_SOS_KERNEL
    ((BASIC_V400R004_CFG0 *)(&D32))->sec_mode_en          = 1;
#else
    ((BASIC_V400R004_CFG0 *)(&D32))->sec_mode_en          = 0;
#endif
    WR_VREG( VREG_V400R004_BASIC_CFG0, D32, VdhId );
    dprint(PRN_VDMREG, "BASIC_V400R004_CFG0 = 0x%x\n", D32);

    //BASIC_V400R004_CFG1
    D32 = 0;
    ((BASIC_V400R004_CFG1 *)(&D32))->video_standard       = 0x0;
    ((BASIC_V400R004_CFG1 *)(&D32))->ddr_stride           = pParam->imgstride >> 6;
    ((BASIC_V400R004_CFG1 *)(&D32))->fst_slc_grp          = pParam->NewPicFlag;
    ((BASIC_V400R004_CFG1 *)(&D32))->mv_output_en         = (pParam->nal_ref_idc != 0);
    ((BASIC_V400R004_CFG1 *)(&D32))->uv_order_en          = 0;
    ((BASIC_V400R004_CFG1 *)(&D32))->vdh_2d_en            = 1;
    ((BASIC_V400R004_CFG1 *)(&D32))->max_slcgrp_num       = 2;
    ((BASIC_V400R004_CFG1 *)(&D32))->compress_en          = pParam->Compress_en;
    ((BASIC_V400R004_CFG1 *)(&D32))->ppfd_en              = 0;
#ifdef VFMW_MODULE_LOWDLY_SUPPORT
    ((BASIC_V400R004_CFG1 *)(&D32))->line_num_output_en   = ModuleLowlyEnable;
#else
    ((BASIC_V400R004_CFG1 *)(&D32))->line_num_output_en   = 0;
#endif
    WR_VREG( VREG_V400R004_BASIC_CFG1, D32, VdhId );
    dprint(PRN_VDMREG, "BASIC_V400R004_CFG1 = 0x%x\n", D32);

    //AVM_V400R004_ADDR
    D32 = 0;
    ((AVM_V400R004_ADDR *)(&D32))->av_msg_addr = pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX] & 0xFFFFFFF0;
    WR_VREG( VREG_V400R004_AVM_ADDR, D32, VdhId );
    dprint(PRN_VDMREG, "AVM_V400R004_ADDR = 0x%x\n", D32);

    //VAM_V400R004_ADDR
    D32 = 0;
    ((VAM_V400R004_ADDR *)(&D32))->va_msg_addr = pHwMem->MsgSlotAddr[UP_V400R004_MSG_SLOT_INDEX] & 0xFFFFFFF0;
    WR_VREG( VREG_V400R004_VAM_ADDR, D32, VdhId );
    dprint(PRN_VDMREG, "VAM_V400R004_ADDR = 0x%x\n", D32);

    //STREAM_V400R004_BASE_ADDR
    D32 = 0;
    ((STREAM_V400R004_BASE_ADDR *)(&D32))->stream_base_addr = pParam->stream_base_addr & 0xFFFFFFF0;
    WR_VREG( VREG_V400R004_STREAM_BASE_ADDR, D32, VdhId );
    dprint(PRN_VDMREG, "STREAM_V400R004_BASE_ADDR = 0x%x\n", D32);

    //EMAR_ID
    //width<=4096 配1 >4096 配0，h00216273
    if (pParam->pic_width_in_mb > 256 || (pParam->pic_width_in_mb >= 120 && pParam->MbaffFrameFlag))
    {
        D32 = 0x0;
    }
    else
    {
        D32 = 0x10000;
    }

    datTmp = RD_SCDREG(REG_EMAR_ID);
    if (0 == D32)
    {
        datTmp = datTmp & (~(0x10000));
    }
    else
    {
        datTmp = datTmp | (0x10000);
    }
    WR_SCDREG(REG_EMAR_ID, datTmp);

    //TIME_OUT
    D32 = 0x00300C03;
    WR_VREG( VREG_V400R004_SED_TO,    D32, VdhId );
    WR_VREG( VREG_V400R004_ITRANS_TO, D32, VdhId );
    WR_VREG( VREG_V400R004_PMV_TO,    D32, VdhId );
    WR_VREG( VREG_V400R004_PRC_TO,    D32, VdhId );
    WR_VREG( VREG_V400R004_RCN_TO,    D32, VdhId );
    WR_VREG( VREG_V400R004_DBLK_TO,   D32, VdhId );
    WR_VREG( VREG_V400R004_PPFD_TO,   D32, VdhId );

#ifdef VFMW_MODULE_LOWDLY_SUPPORT
    if (1 == ModuleLowlyEnable)
    {
        D32 = g_TunnelLineNumber;
        WR_VREG(VREG_V400R004_PART_DEC_OVER_INT_LEVEL, D32, VdhId );
        dprint(PRN_VDMREG, "VREG_V400R004_PART_DEC_OVER_INT_LEVEL=0x%x\n", D32);
    }
#endif

    //YSTADDR_V400R004_1D
    D32 = 0;
    ((YSTADDR_V400R004_1D *)(&D32))->ystaddr_1d = (pParam->ImgPhyAddr[pParam->CurrPicImgIdc]) & 0xFFFFFFF0;
    WR_VREG( VREG_V400R004_YSTADDR_1D, D32, VdhId );
    dprint(PRN_VDMREG, "YSTADDR_V400R004_1D = 0x%x\n", D32);

    //YSTRIDE_V400R004_1D
    D32 = 0;
    ((YSTRIDE_V400R004_1D *)(&D32))->ystride_1d = pParam->imgstride;
    WR_VREG( VREG_V400R004_YSTRIDE_1D, D32, VdhId );
    dprint(PRN_VDMREG, "YSTRIDE_V400R004_1D = 0x%x\n", D32);

    //UVOFFSET_V400R004_1D
    D32 = 0;
	level = 0;
    //D32 = pParam->pic_width_in_mb * 16 * ((pParam->frame_height_in_mb + 1) / 2) * 2 * 16;
    D32 = pParam->ChromaOffset;
    WR_VREG( VREG_V400R004_UVOFFSET_1D, D32, VdhId );
    dprint(PRN_VDMREG, "UVOFFSET_V400R004_1D = 0x%x\n", D32);

    //PRCNUM_1D_CNT
    //D32 = ((pParam->frame_height_in_mb * 16 + 31) / 32) * 32 * level;
    D32 = 0;
    WR_VREG( VREG_V400R004_HEAD_INF_OFFSET, D32, VdhId );

#ifdef VFMW_MODULE_LOWDLY_SUPPORT
    if (1 == ModuleLowlyEnable)
    {
        D32 = pParam->LineNumPhyAddr[pParam->CurrPicImgIdc];
        WR_VREG( VREG_V400R004_LINE_NUM_STADDR, D32, VdhId );
        dprint(PRN_VDMREG, "VREG_LINE_NUM_STADDR = 0x%x\n", D32);
    }
#endif

    //PPFD_V400R004_BUF_ADDR
    D32 = 0;
    ((PPFD_V400R004_BUF_ADDR *)(&D32))->ppfd_buf_addr = pHwMem->PpfdBufAddr & 0xFFFFFFF0;
    WR_VREG( VREG_V400R004_PPFD_BUF_ADDR, D32, VdhId );
    dprint(PRN_VDMREG, "PPFD_V400R004_BUF_ADDR = 0x%x\n", D32);

    //PPFD_V400R004_BUF_LEN
    D32 = 0;
    ((PPFD_V400R004_BUF_LEN *)(&D32))->ppfd_buf_len = pHwMem->PpfdBufLen;
    WR_VREG( VREG_V400R004_PPFD_BUF_LEN, D32, VdhId );
    dprint(PRN_VDMREG, "PPFD_V400R004_BUF_LEN = 0x%x\n", D32);

    //REF_V400R004_PIC_TYPE
    D32 = 0;

    for (i = 0; i < 16; i++)
    {
        D32 |= ( (pParam->RefPicType[i] & 0x03) << (2 * i) );
    }

    //D32 = 0x55555555;
    WR_VREG( VREG_V400R004_REF_PIC_TYPE, D32, VdhId );
    dprint(PRN_VDMREG, "REF_V400R004_PIC_TYPE = 0x%x\n", D32);

    //FF_V400R004_APT_EN
#if 0
    D32 = 0;  // 0:frm save, 1:apt save
#else

    if (0 == g_StructTrans[pParam->pic_structure][pParam->mb_adaptive_frame_field_flag])
    { D32 = 0x2; }
    else
    { D32 = 0x0; }

#endif
    WR_VREG( VREG_V400R004_FF_APT_EN, D32, VdhId );
    dprint(PRN_VDMREG, "FF_V400R004_APT_EN = 0x%x\n", D32);

    // 清除中断
    WR_VREG( VREG_V400R004_INT_STATE, 0xFFFFFFFF, VdhId );

    /*3.配置pic消息池*/
    H264HAL_V400R004_SetPicMsg(pParam, pHwMem, pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX], pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX + 1]);
    /*4. 配置slice消息池*/
    pSlicePara = pParam->pFirstSlice;

    if (NULL == pSlicePara)
    {
        dprint(PRN_FATAL, "pSlicePara = NULL!\n");
        return VDMHAL_ERR;
    }

    if (pSlicePara->first_mb_in_slice != 0)
    {
        first_mb_in_slice = 0;
        last_mb_in_slice = pSlicePara->first_mb_in_slice - 1;

        tmp_first_mb_in_slice = pSlicePara->first_mb_in_slice;
        valid_bitlen[0] = pSlicePara->valid_bitlen[0];
        valid_bitlen[1] = pSlicePara->valid_bitlen[1];
        bitsoffset[0] = pSlicePara->bitsoffset[0];
        bitsoffset[1] = pSlicePara->bitsoffset[1];
        bytespos[0] = pSlicePara->bytespos[0];
        bytespos[1] = pSlicePara->bytespos[1];
        pSlicePara->first_mb_in_slice = 0;
        pSlicePara->valid_bitlen[0] = 1;
        pSlicePara->valid_bitlen[1] = 0;
        pSlicePara->bitsoffset[0] = 0;
        pSlicePara->bitsoffset[1] = 0;
        pSlicePara->bytespos[0] = 0;
        pSlicePara->bytespos[1] = 0;
        AddSlice0Flag = 1;
        prev_slcmsg_phy = pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX];
        cur_slcmsg_phy = pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX + 1];
        next_slcmsg_phy = pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX + AddSlice0Flag + 1];
        pre_first_mb_in_slice = 0;

        if (H264HAL_V400R004_SetSliceMsg(pParam, pHwMem, pSlicePara, cur_slcmsg_phy, prev_slcmsg_phy, next_slcmsg_phy, first_mb_in_slice, last_mb_in_slice) != VDMHAL_OK)
        {
            dprint(PRN_ERROR, "line %d Set slice msg not wrong!\n", __LINE__);
            return VDMHAL_ERR;
        }

        pSlicePara->first_mb_in_slice = tmp_first_mb_in_slice;
        pSlicePara->valid_bitlen[0] = valid_bitlen[0];
        pSlicePara->valid_bitlen[1] = valid_bitlen[1];
        pSlicePara->bitsoffset[0] = bitsoffset[0];
        pSlicePara->bitsoffset[1] = bitsoffset[1];
        pSlicePara->bytespos[0] = bytespos[0];
        pSlicePara->bytespos[1] = bytespos[1];
    }

    pre_first_mb_in_slice = 0;
    
    count = 0;

    tmp_pSlicePara  = pParam->pFirstSlice;
    pSlicePara = pParam->pFirstSlice;

    for (i = 0; i < pParam->SliceParaNum; i++)
    {
        pSlicePara = tmp_pSlicePara;
        prev_slcmsg_phy = pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX + AddSlice0Flag + i];
        cur_slcmsg_phy = pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX + AddSlice0Flag + 1 + i];

        if ((pSlicePara->first_mb_in_slice <= pre_first_mb_in_slice) && (i > 0))
        {
            continue;
        }

        pre_first_mb_in_slice = pSlicePara->first_mb_in_slice;
        first_mb_in_slice = pSlicePara->first_mb_in_slice;
        //tmp_pSlicePara = pSlicePara;
        j = i + 1;

        for (j = (i + 1); j < pParam->SliceParaNum; j++)
        {
            tmp_pSlicePara = tmp_pSlicePara->pNextSlice;

            if (tmp_pSlicePara != NULL)
            {
                if (pSlicePara->first_mb_in_slice < tmp_pSlicePara->first_mb_in_slice)
                {
                    break;
                }
            }
            else
            {
                dprint(PRN_ERROR, "line %d tmp_pSlicePara is NULL!\n", __LINE__);
                return VDMHAL_ERR;
            }
        }

        if ((j == pParam->SliceParaNum) || (MSG_V400R004_SLOT_NUM == (DN_V400R004_MSG_SLOT_INDEX + 1 + AddSlice0Flag + i + 1)))
        {
            last_mb_in_slice = pParam->pic_width_in_mb * pParam->pic_height_in_mb - 1;
            next_slcmsg_phy = 0;
            pSlicePara->pNextSlice = NULL;
        }
        else
        {
            last_mb_in_slice = tmp_pSlicePara->first_mb_in_slice - 1;
            next_slcmsg_phy = pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX + AddSlice0Flag + 1 + j];
        }

        i = j - 1;

        if (i == (pParam->SliceParaNum - 1))
        {
            pSlicePara->pNextSlice = NULL;
        }

        if (H264HAL_V400R004_SetSliceMsg(pParam, pHwMem, pSlicePara, cur_slcmsg_phy, prev_slcmsg_phy, next_slcmsg_phy, first_mb_in_slice, last_mb_in_slice) != VDMHAL_OK)
        {
            dprint(PRN_ERROR, "line %d Set slice msg not wrong!\n", __LINE__);
            return VDMHAL_ERR;
        }

        if (0 == next_slcmsg_phy)
        {
            break;
        }
    }

    /*5. cut down slice chain*/
    if (0 < pParam->SliceParaNum)
    {
        H264HAL_V400R004_CutSliceChain(pHwMem->MsgSlotAddr[DN_V400R004_MSG_SLOT_INDEX + 1 + pParam->SliceParaNum - 1 + AddSlice0Flag]);

        if (1 == pParam->NewPicFlag)
        {
            if ( (1 == g_StructTrans[pParam->pic_structure][pParam->mb_adaptive_frame_field_flag]) || (2 == g_StructTrans[pParam->pic_structure][pParam->mb_adaptive_frame_field_flag]) )
            {
                //TotalPicNum++;
            }
            else
            {
                //TotalPicNum += 2;
            }
        }
    }
    else
    {
        dprint(PRN_ERROR, "!!! no slice to dec, add up msg report.");
        return VDMHAL_ERR;
    }

    return VDMHAL_OK;
}

