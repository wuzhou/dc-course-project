/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _POST_FAILURE_H_RPCGEN
#define _POST_FAILURE_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


#define POSTFAILURE_PROG 0x20481028
#define POSTFAILURE_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define POSTFAILURE 1
extern  void * postfailure_1(int *, CLIENT *);
extern  void * postfailure_1_svc(int *, struct svc_req *);
extern int postfailure_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define POSTFAILURE 1
extern  void * postfailure_1();
extern  void * postfailure_1_svc();
extern int postfailure_prog_1_freeresult ();
#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_POST_FAILURE_H_RPCGEN */