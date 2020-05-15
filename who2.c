/* who1.c  - a first version of the who program
 *              open, read UTMP file, and show results
 */
#include	<stdio.h>
#include	<utmp.h>
#include	<fcntl.h>
#include	<unistd.h>
#include 	<time.h>

/*#define	SHOWHOST include remote machine on output */

void showtime(long);
void show_info(struct utmp *);

int main()
{
	struct utmp	utbuf;	/* read info into here       */
	int		utmpfd;		/* read from this descriptor */
	
	/* Basically error checking */
	if ( (utmpfd = open(UTMP_FILE, O_RDONLY)) == -1 ){
		perror( UTMP_FILE );	/* UTMP_FILE is in utmp.h    */
		exit(1);
	}
	
	while ( read(utmpfd, &utbuf, sizeof(utbuf)) == sizeof(utbuf) )
		show_info(&utbuf);
	close(utmpfd);
	return 0;			/* went ok */
}
/*
 *  show info()
 *	displays contents of the utmp struct in human readable form
 *	*note* these sizes should not be hardwired
 */
show_info( struct utmp *utbufp )
{
	if (utbufp->ut_type != USER_PROCESS)
		return; 
	printf("%-8.8s", utbufp->ut_name);	/* the logname	*/
	printf(" ");				/* a space	*/
	printf("%-8.8s", utbufp->ut_line);	/* the tty	*/
	printf(" ");				/* a space	*/
	printf("%10ld", utbufp->ut_time);	/* login time	*/
	printf(" ");				/* a space	*/
#ifdef	SHOWHOST
	if (utbufp -> uthost[0] != '\0')
		printf("(%s)", utbufp->ut_host);	/* the host	*/
#endif
	printf("\n");				/* newline	*/
}

void showtime(long timeval) {
	char *cp;
	cp = ctime(&timeval);
	
	printf("$12.12s",cp+4); 
	
}