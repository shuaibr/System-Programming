/* mywho.c  - read /etc/utmp and list info therein
 *         - suppresses empty records
 *         - formats time nicely
 */
#include        <stdio.h>
#include        <stdlib.h>
#include        <unistd.h>
#include        <utmp.h>
#include        <fcntl.h>
#include        <time.h>

/* #define      SHOWHOST */

void showtime(long);
void show_info(struct utmp *);
char *whats_my_line(int);


int main(int argc, char* argv[] )
{
        struct utmp     utbuf;          /* read info into here */
        int             utmpfd;         /* read from this descriptor */
	char *myline = NULL;

	// validate arguments
	if ( argc == 3 && (strcmp(argv[1], "am")== 0) && argv[2][0] == 'i') {
	  // return name of a terminal used by the current user
	  myline = whats_my_line(0); // fd=0: Standard input
	} else {
	  //Display usage statement
	  fprintf(stderr, "Error, usage: %s am i\n", argv[0]);
	  exit(1);
	}


        while( read(utmpfd, &utbuf, sizeof(utbuf)) == sizeof(utbuf) ) //Read the utmp file 
	if ( myline == NULL || strcmp(utbuf.ut_line, myline) == 0 )    
		show_info( &utbuf );


        if ( (utmpfd = open(UTMP_FILE, O_RDONLY)) == -1 ){ //Error
                perror(UTMP_FILE);
                exit(1);
        }

        while( read(utmpfd, &utbuf, sizeof(utbuf)) == sizeof(utbuf) )
	  show_info( &utbuf );
        close(utmpfd);
        return 0;
}

/*
 *      show info()
 *                      displays the contents of the utmp struct
 *                      in human readable form
 *                      * displays nothing if record has no user name
 */
void show_info( struct utmp *utbufp )
{
        if ( utbufp->ut_type != USER_PROCESS )
                return;

        printf("%-8.8s", utbufp->ut_name);      /* the logname  */
        printf(" ");                            /* a space      */
        printf("%-8.8s", utbufp->ut_line);      /* the tty      */
        printf(" ");                            /* a space      */
        showtime( utbufp->ut_time );            /* display time */
#ifdef SHOWHOST
        if ( utbufp->ut_host[0] != '\0' )
                printf(" (%s)", utbufp->ut_host);/* the host    */
#endif
        printf("\n");                          /* newline      */
}

void showtime( long timeval )
/*
 *      displays time in a format fit for human consumption
 *      uses ctime to build a string then picks parts out of it
 *      Note: %12.12s prints a string 12 chars wide and LIMITS
 *      it to 12chars.
 */
{
        char    *cp;                    /* to hold address of time      */

        cp = ctime(&timeval);           /* convert time to string       */
                                        /* string looks like            */
                                        /* Mon Feb  4 00:46:40 EST 1991 */
                                        /* 0123456789012345.            */
        printf("%12.12s", cp+4 );       /* pick 12 chars from pos 4     */
}

// Function Implementation
char * whats_my_line(int fd)
{
	char    *rv;
	if ( rv = ttyname(fd) )    
		if ( strncmp(rv,"/dev/",5) == 0 )
			rv += 5;
	return rv;
}
