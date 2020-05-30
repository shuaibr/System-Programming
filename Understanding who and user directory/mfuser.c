#include <time.h>
#include "utmplib.h"

#define SHOWHOST

void show_time(long);
void show_info(struct utmp*, int, int*, char*);

int main() {
    struct utmp *utbufp,          // holds pointer to next record
                *utmp_next();     // returns pointer to next

    if (utmp_open(WTMP_FILE) == -1) {
        perror(WTMP_FILE);
        exit(1);
    }
	int last_element = 0; 
	int count[100] = {0};
	char name[100][128];
	int i =0; 
	int found = 0;
	
	
    while ( (utbufp = utmp_next()) != ((struct utmp*)NULL) ) {
		
		found = 0;
		if (utbufp->ut_type != USER_PROCESS)
			continue;

		for (int x = 0; x < last_element; x++) {
			//printf("Data2: %d %1s\n", count[x],name[x]);
			//printf("CHeck: %d %d %s %s\n", last_element,strncmp(name[x], utbufp->ut_name, sizeof(utbufp->ut_name)),name[x],utbufp->ut_name);
			if(strncmp(name[x], utbufp->ut_name, sizeof(utbufp->ut_name)) == 0){
				i = x;
				found = 1; 
				break;
			}
		}
		if (found==0) 
			i =++last_element;
		//printf("NAME: %1s\n",utbufp->ut_name);
		show_info(utbufp, i, count, name[i]);
		
	}
	//printf("Last element: %d", last_element);
	int max = -1;
	int max_index = 0;
	for (int x = 0; x < last_element; x++){
		if (max< count[x]){
			max = count[x];
			max_index = x;
		}
	}
	printf("%d %s\n", count[max_index],name[max_index]);
    utmp_close();
    return 0;
}

void show_info( struct utmp *utbufp, int i, int *count, char *name)
{
	time_t now; 
	int days; 
	
	if (utbufp->ut_type != USER_PROCESS)
		return; 
	
	days = (time(&now)-utbufp->ut_time)/86400;
	if (days < 30) { 
		count[i]++;
		strncpy(name,utbufp->ut_name, sizeof(utbufp->ut_name));
		//puts("hi");

		//printf("%d %s %s\n",i,name,utbufp->ut_name);
		/*if (show_time(utbufp -> ut_time) < show_time(strtotime('-1 month'))) {*/
		//printf("%-8.8s", utbufp->ut_name);	/* the logname	*/
		//printf(" ");				/* a space	*/
		time_t diff; 
		diff = time(&now) - utbufp->ut_time;

		//show_time(utbufp -> ut_time);
		
	#ifdef	SHOWHOST
		if (utbufp -> ut_host[0] != '\0')
			printf("(%s)", utbufp->ut_host);	/* the host	*/
	#endif
		printf("");				/* newline	*/
	}
	}

void show_time(long timeval) {
	char *cp;
	cp = ctime(&timeval);
	printf("%12.12s",cp+4); 
}