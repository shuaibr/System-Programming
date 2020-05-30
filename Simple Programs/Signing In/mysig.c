/*
/* sigdemo1.c - shows how a signal handler works.
 *            - run this and press Ctrl-C a few times
 */
 
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

main()
{
	void f(int);			/* declare the handler	*/
	int	i;

	signal( SIGINT, f );		/* install the handler	*/
	for(i=0; i<5; i++ ){		/* do something else	*/
		printf("hello\n");
		sleep(1);
	}
}

void f(int signum)			/* this function is called */
{
	char *password = "Laurier";
	char input_password[20]="";
	char exit_input;
	int i;
	struct termios oldt, newt;

	tcgetattr(STDIN_FILENO, &oldt);
	newt =oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
  
	printf(" Interrupted! OK to quit (y/n)? ");
	scanf(" %c", &exit_input);
	
	if(exit_input == 'y' || exit_input == 'Y'){
		for(i=0; i<2 ;i++){//Max 2 attemts 
			printf("Please enter the password: ");
			tcsetattr(STDIN_FILENO, TCSANOW, &newt);//echo off
			scanf("%s",input_password ); 
			tcsetattr(STDIN_FILENO, TCSANOW, &oldt);//echo on
			
			if(strcmp(input_password, password)!=0){// if not equal, it is incorrect
				printf("\nYou have entered an invalid password. \n");
				
			}else if (strcmp(input_password, password)==0) {
				printf("\nexit \n" );
				exit(0);
			}
		}
	}

}
