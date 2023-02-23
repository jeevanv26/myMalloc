#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include "mymalloc.h"

int main(int argc, char*argv[])
{

//printHeapRange();
// test program one (given in instructions)

long total = 0;
for(int i = 0; i < 50; i++){
void* array[120];
int counter = 0;

struct timeval start, end;
gettimeofday(&start, NULL);
while(counter < 120){
    array[counter] =  malloc(1);
    counter ++;
}
for(int x=0; x<120; x++){
  free(array[x]);
}
gettimeofday(&end, NULL);
long seconds = end.tv_sec - start.tv_sec;
long microseconds = end.tv_usec - start.tv_usec;
if(microseconds < 0)
  seconds -=1;
microseconds = (seconds * 1000000) + abs(microseconds);
total += microseconds;
}
long avg = total/50;
printf("The average elapsed time for program 1  is %ld microseconds\n", avg);


//test program2
long total2 = 0;
for(int i = 0; i < 50; i++){
void* array2[6];
int counter2 = 0;

struct timeval start2, end2;
gettimeofday(&start2, NULL);
while(counter2 < 6){
    array2[counter2] =  malloc(50);
    counter2 ++;
}
for(int x=1; x<6; x+=2){
  free(array2[x]);
}
for(int x=0; x<6; x+=2){
  free(array2[x]);
}
if(i == 0){
  free(array2[1]);
  free(array2[0]);
}
gettimeofday(&end2, NULL);
long seconds2 = end2.tv_sec - start2.tv_sec;
long microseconds2 = end2.tv_usec - start2.tv_usec;
if(microseconds2< 0)
  seconds2 -=1;
microseconds2 = (seconds2 * 1000000) + abs(microseconds2);
total2 += microseconds2;
}
long avg2 = total2/50;
printf("The average elapsed time for program 2 is %ld microseconds\n", avg2);

//test program3
long total3 = 0;
for(int i = 0; i < 50; i++){

struct timeval start3, end3;
gettimeofday(&start3, NULL);

void* ptr =  malloc(65);

gettimeofday(&end3, NULL);
long seconds3 = end3.tv_sec - start3.tv_sec;
long microseconds3 = end3.tv_usec - start3.tv_usec;
if(microseconds3< 0)
  seconds3 -=1;
microseconds3 = (seconds3 * 1000000) + abs(microseconds3);
total3 += microseconds3;
}
long avg3 = total3/50;
printf("The average elapsed time for program 3 is %ld microseconds\n", avg3);

return 0;
}
