/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "post_failure.h"

extern char fail_flag;

void *
postfailure_1_svc(int *argp, struct svc_req *rqstp)
{
	static char * result;
    
    printf("fail~~ from pf_svc\n");
	/*
	 * insert server code here
	 */
     fail_flag = 1;

	return (void *) &result;
}
