/* who1.c  - a first version of the who program
 *              open, read UTMP file, and show results
 */
#include	<stdio.h>
#include	<utmp.h>
#include	<fcntl.h>
#include	<unistd.h>
#include 	<time.h>
#include 	<stdlib.h>

/*#define	SHOWHOST include remote machine on output */

void showtime(long);
void show_info(struct utmp *);

typedef struct {
	int count;
	char *name;
	int *next;
} Array;

int main()
{
	
	struct utmp	utbuf;	/* read info into here       */
	int		utmpfd;		/* read from this descriptor */
	
	/* Basically error checking */
	if ( (utmpfd = open(WTMP_FILE, O_RDONLY)) == -1 ){
		perror( WTMP_FILE );	/* UTMP_FILE is in utmp.h    */
		exit(1);
	}
	
	while ( read(utmpfd, &utbuf, sizeof(utbuf)) == sizeof(utbuf) ){
		show_info(&utbuf);
	}
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
	time_t now; 
	int days; 
	
	if (utbufp->ut_type != USER_PROCESS)
		return 0; 
	
	days = (time(&now)-utbufp->ut_time)/86400;
	if (days < 30) { 
		int count[100];
		char name[100];
		/*if (showtime(utbufp -> ut_time) < showtime(strtotime('-1 month'))) {*/
		printf("%-8.8s", utbufp->ut_name);	/* the logname	*/
		printf(" ");				/* a space	*/
		/*printf("%10d", utbufp->ut_time);	
		printf(" ");			
		printf("%10d", time(&now));
		printf("%10d", (time(&now)-utbufp->ut_time)/86400);
		time_t diff; 
		diff = time(&now) - utbufp->ut_time;
		struct tm *local = localtime(&diff);
		printf("%10d", local);
		printf(" ");		*/
		showtime(utbufp -> ut_time);
		
	
	#ifdef	SHOWHOST
		if (utbufp -> uthost[0] != '\0')
			printf("(%s)", utbufp->ut_host);	/* the host	*/
	#endif
		printf("\n");				/* newline	*/
	}
	}

void showtime(long timeval) {
	char *cp;
	cp = ctime(&timeval);
	printf("%12.12s",cp+4); 
}