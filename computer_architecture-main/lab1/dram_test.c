#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define REPEAT 1000
#define OUTPUTFILE "/Users/carmenwu/Desktop/W4824ComSciArchitecture/computer_architecture/hw1/1024.txt"
#define SIZE 1024

inline void clflush(volatile void *p){
    asm volatile ("clflush (%0)" :: "r"(p));   
}

inline uint64_t rdtsc(){  
    unsigned long a, d;  
    asm volatile ("rdtsc" : "=a" (a), "=d" (d)); 
    return a | ((uint64_t)d << 32);    
 }

char lineBuffer[SIZE];
long int rep;

inline void memtest(){

    uint64_t start, end, clock;
    
    char* lineBuffer = (char*) malloc(SIZE);
    char* lineBufferCopy = (char*) malloc(SIZE);

    for(int i = 0; i < SIZE; i++){
        lineBuffer[i] = '1';
     }

    FILE * fp;
    /*open the file for writing*/
    fp = fopen(OUTPUTFILE,"w");
    //fprintf(fp,"------------------------------\n");
    int j = 1; //counter for printf

    clock = 0;
    for (rep = 0; rep < REPEAT; rep++) {

      //printf("value of lineBuffer: %s\n", lineBuffer);
      //printf("value of lineBufferCopy: %s\n", lineBufferCopy);

	clflush(lineBuffer);
	clflush(lineBufferCopy);

	start = rdtsc();
        memcpy(lineBufferCopy, lineBuffer, SIZE);
        end = rdtsc();
        clflush(lineBuffer);
        clflush(lineBufferCopy);
        clock = clock + (end - start);
        //printf("%llu ticks to copy 64B\n", (end-start));
        fprintf(fp,"%d:%llu\n", j,(end-start));
        j++;
      }
    //print out number of click ticks in each cycle
    fprintf(fp,"Total:%llu\n", clock);
    /* close the file*/  
    fclose (fp);
    
}

int main(int ac,char **av){

  memtest();

  return 0;
}
