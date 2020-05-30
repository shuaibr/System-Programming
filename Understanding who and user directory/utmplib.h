#ifndef			UTMP_LIB
#define 		UTMP_LIB

#include        <stdio.h>
#include        <fcntl.h>
#include        <sys/types.h>
#include        <utmp.h>
#include 		<unistd.h>
#include 		<string.h>
#include 		<stdlib.h>

#define NRECS   400
#define NULLUT  ((struct utmp *)NULL)
#define UTSIZE  (sizeof(struct utmp))

static  char    utmpbuf[NRECS * UTSIZE];                /* storage      */
static  int     num_recs;                               /* num stored   */
static  int     cur_rec;                                /* next to go   */
static  int     fd_utmp = -1;                           /* read from    */

int utmp_open( char *filename );
struct utmp *utmp_next();
int utmp_reload();
int utmp_close();

#endif

