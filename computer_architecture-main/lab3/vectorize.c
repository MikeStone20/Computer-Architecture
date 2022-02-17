#include <emmintrin.h>
#include <stdio.h>
#include <time.h>
/*
void add(float *a, float *b, float *c)
{
	__m128 t0, t1;
	t0 = _mm_load_ps(a);
	t1 = _mm_load_ps(b);
	t0 = _mm_add_ps(t0, t1);
	_mm_store_ps(c, t0);
}
*/

 inline uint64_t rdtsc(){  
     unsigned long a, d;  
     asm volatile ("rdtsc" : "=a" (a), "=d" (d)); 
     return a | ((uint64_t)d << 32);    
 }



void add(double *a, double *b, double *c)
{
	__m128 t0, t1;
	t0 = _mm_load1_pd(a);
	t1 = _mm_load1_pd(b);
	t0 = _mm_add_pd(t0, t1);
	_mm_store_pd(c, t0);
	
}


int main()
{	
	uint64_t start,end, clock;
	clock = 0;
	double *a = (double *)malloc(sizeof(double));
	double *b = (double *)malloc(sizeof(double));
	double *c = (double *)malloc(sizeof(double));
	*a = 1.1;
	*b = 1.5;
	*c = 0.0;
	start = rdtsc();
	add(a,b,c);
	end = rdtsc();
	clock = clock + (end - start);
	printf("Total_time:%llu\n",clock);
	//printf("%f\n",c );
	return 0;
}



