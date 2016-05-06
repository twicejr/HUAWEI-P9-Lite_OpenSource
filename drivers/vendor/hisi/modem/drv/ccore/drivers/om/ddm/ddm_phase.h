#ifndef _DDM_PHASE_H_
#define _DDM_PHASE_H_
#ifdef __cplusplus
extern "C" { /* allow C++ to use these headers */
#endif /* __cplusplus */

#define DDM_OK      0
#define DDM_ERROR   -1

int ddm_phase_boot_score(const char * phaseName, unsigned int param);
void ddm_phase_boot_echo(void);
#ifdef __cplusplus
} /* allow C++ to use these headers */
#endif /* __cplusplus */

#endif

/*end of this file*/

