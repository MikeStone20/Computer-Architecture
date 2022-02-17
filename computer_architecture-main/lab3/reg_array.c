#include <emmintrin.h>
#include <stdio.h>
#include <time.h>

 inline uint64_t rdtsc(){  
     unsigned long a, d;  
     asm volatile ("rdtsc" : "=a" (a), "=d" (d)); 
     return a | ((uint64_t)d << 32);    
 }



void add(double *a, double *b)
{
	__m128 t0, t1;
	t0 = _mm_load1_pd(a);
	t1 = _mm_load1_pd(b);
	t0 = _mm_add_pd(t0, t1);
	_mm_store_pd(a, t0);
	
}

void add_regular(double *a, double *b)
{
	
	for (int i = 0; i < 100000; ++i)
	{
		a[i] += b[i];
	}
}

void mul_regular(double *a, double *b)
{
	
	for (int i = 0; i < 100000; ++i)
	{
		a[i] *= b[i];
	}
}


int main()
{	
	uint64_t start_add, end_add, clock_add, start_mul, end_mul, clock_mul;

	clock_add =0;
	clock_mul =0;
	// double *a = (double *)malloc(sizeof(double));
	// double *b = (double *)malloc(sizeof(double));


	double a[100000];
	a[0]= 1.1;
	double b[100000];
	b[0] = 1.5;

	start_add = rdtsc();
	add_regular(a,b);
	end_add = rdtsc();
	clock_add = clock_add + (end_add - start_add);
	printf("Total_time regular add:%llu\n",clock_add);
	printf("%f\n",*a);

	start_mul = rdtsc();
	mul_regular(a,b);
	end_mul = rdtsc();
	clock_mul = clock_mul + (end_mul - start_mul);
	printf("Total_time regular multiply:%llu\n",clock_mul);
	printf("%f\n",*a);


	return 0;
}



