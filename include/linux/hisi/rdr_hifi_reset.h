

#ifndef RDR_HIFI_RESET_H_INCLUDED
#define RDR_HIFI_RESET_H_INCLUDED

#ifndef RESET_CBFUNC_PRIO_LEVEL_LOWT
#define RESET_CBFUNC_PRIO_LEVEL_LOWT    (0)
#endif

#ifndef RESET_CBFUNC_PRIO_LEVEL_HIGH
#define RESET_CBFUNC_PRIO_LEVEL_HIGH    (49)
#endif

#define RESET_CBFUN_IGNORE_NAME         "NONAME"
#define BSP_RESET_OK                    0
#define BSP_RESET_ERROR                 (-1)

typedef int (*pdrv_reset_cbfun)(DRV_RESET_CALLCBFUN_MOMENT eparam, int userdata);
/*Record information of callback functions*/
typedef struct
{
    char name[9 + 1];
    int priolevel;
    pdrv_reset_cbfun cbfun;
    int userdata;
} sreset_mgr_callbackfunc;

/*Link list unit of managing all callback functions*/
typedef struct _sreset_mgr_LLI
{
    sreset_mgr_callbackfunc cbfuninfo;
    struct _sreset_mgr_LLI *pnext;
} sreset_mgr_LLI;

static inline int hifireset_regcbfunc(const char *pname, pdrv_reset_cbfun pcbfun, int userdata, int priolevel)
{}

#endif /*RDR_HIFI_RESET_H_INCLUDED*/

/********************************* END ***********************************************/

