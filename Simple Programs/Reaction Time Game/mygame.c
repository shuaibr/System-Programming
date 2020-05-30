#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <curses.h>
#include <sys/time.h>

//Character definitions 
#define MIN_NUM 48 
#define MAX_NUM 57 
#define MIN_CHAR 97 
#define MAX_CHAR 122 

struct timeval start,end;

int getRand(){
  int charNum = rand()%2;
  if(charNum == 0){ //integer ascii value
    return (rand()%(MAX_NUM-MIN_NUM)+MIN_NUM);
	
  }else{ //return character ascii value
    return (rand()%(MAX_CHAR-MIN_CHAR)+MIN_CHAR);
  }
}

int getInt(int max, int min){
  return (rand()%(max-min)+min);
}

void startTimer(){
  gettimeofday(&start, NULL);
}

double stopTimer(){
  gettimeofday(&end, NULL); //return time elapsed
  return ((end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)/1000000.0);
}

int main(){
  initscr(); //set up screen
  noecho(); //turn off echo
  
  int i=0;
  double results[10];
  char counter[8];  
  int display;
  char displayc[1];
  
  for(i = 1; i < 11; i++){
    //set up test counter
    clear();
    move((LINES-1)/2,(COLS-1)/2);
    sprintf(counter, "Test %d", i);
    addstr(counter);
    refresh();
	
    //delay
    sleep(getInt(3,1));
    clear(); //clear screen
    move(getInt(LINES-1, 0), getInt(COLS-1, 0)); //move cursor to random
    display = getRand(); //get number
    sprintf(displayc, "%c", display); //set up display
    addstr(displayc); //display
    refresh();
    startTimer(); //start
	
    while(getch() != display){ //loop until done
    }
    results[i-1] = stopTimer(); //put results into array
  }
  
  endwin();
  for(i = 1; i < 11; i++){
    printf("%d. %.4lf\n", i, results[i-1]);
  }
  
  //display 
  double  max, min, avg=0;
  min = results[0];
  max = results[0];
  
  for(i = 0; i < 10; i++){
    if(min > results[i]){
      min = results[i]; //get min
    }
	
    if(max < results[i]){
      max = results[i]; //get max
    }
    avg+= results[i]; //add
  }
  avg = avg/10; //average

  printf("max = %.4lf   min = %.4lf    avg = %.4lf\n", max, min, avg);
  return 1;
}
