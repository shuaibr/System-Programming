#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 50000

void print_interface();
void get_operation(char *);
void print_array(int *, int);
void array_copy(int *, int *, int);
void selection_sort(int *, int);
int find_min(int *, int, int);
float num_average(int *, int);
void quick_sort(int *, int, int);
void swap(int*, int*);


int main() {
	int i, j, n = 10, a[MAX], b[MAX];
	char op = '1';
	double t_s, t_b, t_q;
	float average;
	clock_t ticks1, ticks2;

	print_interface();

	get_operation(&op);
	srand((unsigned int) time(0)); //random number generator seed

	switch(op){
	case '0':
	{

		for(i=0; i<10; i++) a[i] = rand()%100+1;

		printf("\n\nRandomly generated array of length %d is\n", n);
		print_array(a, n);

		//Copy to array b
		array_copy(a,b,n);

		//selection sort
		selection_sort(b, n);
		printf("\n\nsorted by selection sort:\n");
		print_array(b,n);

		//Copy to array b
		array_copy(a,b,n);

		//quick sort
		quick_sort(b, 0, n-1);
		printf("\n\nsorted by quick sort:\n");
		print_array(b,n);

		// calculate the average of those numbers in array
		average=num_average(a,n);
		printf("Average is:%.2f\n\n",average);
	}

		break;
	case '1':
	{
		for (j=0; j<MAX; ++j) a[j] = rand()%MAX;

		// testing selection sort
		array_copy(a, b, MAX);
		ticks1 = clock();  			// to get CPU clockcycle time
		selection_sort(b, MAX);   	// do selection sort
		ticks2=clock();
		t_s =(ticks2-ticks1)/CLOCKS_PER_SEC;
		printf("It takes %f seconds to sort the array by selection sort.\n",t_s);

		// testing quick sort
		array_copy(a,b, MAX);
		ticks1 = clock();
		quick_sort(b, 0, MAX);
		ticks2 = clock();
		t_s = (ticks2-ticks1)/CLOCKS_PER_SEC;
		printf("It takes %f seconds to sort the array by quick sort.\n",t_s);

		// implementation

	}
		break;
	case '2':
		break;
	}

	return EXIT_SUCCESS;
}

// function implementations

/*
*  this function is to print and prompt for user interface
*/
void print_interface(){
// print the command help
// implementation
printf("Choose an operation (0, 1, 2):");
printf("\n 0 -- Correctness Testing");
printf("\n 1 -- Performance testing");
printf("\n 2 -- Quit");
}

void print_array(int *a, int n){
  int j = 0;
  for (j=1; j<=n; ++j){
    if (j%10 ==0) {
	printf("%d\n", *(a+j-1));
    } else {
    	printf("%d ", *(a+j-1));
    }
  }
}

void get_operation(char *operation){
  scanf("%c", operation);
  do {
    if (getchar() == '\n') break;
  } while(1);
}

void array_copy(int *a, int *b, int n){
  int i=0;
  for(i=0;i<n;i++){
    *(b+i)=*(a+i);
  }
  // implementation
}

void selection_sort(int *a, int n)
{
  int i, j, k,t;
  for(i=0;i<n-1;i++){
    k=i;
    for(j=i+1;j<n;j++){
      if(*(a+j)<*(a+k)){
        k=j;
      }
    }
    if(k!=i){
      swap((a+i),(a+k));
    }
  }

  // implementation
}


int find_min(int *list, int start, int end){
  int i, cur_min_posi;
  cur_min_posi = start;
  for  (i = start+1;  i <= end; i++)
    if (*(list+i) < *(list+cur_min_posi))
      cur_min_posi = i;
  return cur_min_posi;
}

float num_average(int *a, int n){
  float answer =0;
  float sum=0;
  int i=0;
  for(i=0;i<n;i++){

    sum = sum+(*(a+i)); 
  }
  answer = sum/n;
  return answer;
  // implementation,
}

void quick_sort(int *list, int begin, int end)
{
  int i = begin, j = end;
      int tmp;
      int pivot = *(list+((begin + end) / 2));
      /* partition */
      while (i <= j) {
            while (*(list+i) < pivot)
                  i++;
            while (*(list+j) > pivot)
                  j--;
            if (i <= j) {
                  swap((list+i),(list+j));
                  i++;
                  j--;
            }
      };
      /* recursion */
      if (begin < j)
            quick_sort(list, begin, j);
      if (i < end)
            quick_sort(list, i, end);
  // implementation,
}

void swap ( int *first, int *second ) {
  int temp= *first;
  *first = *second;
  *second=temp;
  //implementation, refer to lecture 5 slide 12
}
