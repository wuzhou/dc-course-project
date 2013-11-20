/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "lookup_grade.h"


char
lookup_grade(char *host, int id)
{
	CLIENT *clnt;
	char  *result_1;
	int  lookupgrade_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, LOOKUPGRADE_PROG, LOOKUPGRADE_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = lookupgrade_1(&id, clnt);
	if (result_1 == (char *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
    return *result_1;
}

/*
int
main (int argc, char *argv[])
{
	char host[] = "localhost";

	//if (argc < 2) {
	//	printf ("usage: %s server_host\n", argv[0]);
//		exit (1);
//	}
	//host = argv[1];
	lookupgrade_prog_1 (host, 1);
exit (0);
}*/
