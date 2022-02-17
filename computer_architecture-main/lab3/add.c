#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


 inline uint64_t rdtsc(){  
     unsigned long a, d;  
     asm volatile ("rdtsc" : "=a" (a), "=d" (d)); 
     return a | ((uint64_t)d << 32);    
}

static __inline__ uint64_t getticks(void){
	uint32_t a,d;
	asm("cpuid");
		asm volatile("rdtsc": "=a" (a),"=d" (d));
		return (((uint64_t)a)|(((uint64_t)d) << 32);
}


uint32_t avx2_sumbytes_variant2(uint32_t* array_a, uint32_t* array_b,size_t size)
{
	__m256i accumulator = _mm256_setzero_si256(); //all zero vector

	
	const __m256i v = _mm256_loadu_si256((__m256i*)(array_a));
	const __m256i v2 = _mm256_loadu_si256((__m256i*)(array_b));

	accumulator = _mm256_add_epi32(v,v2);
	//printf("%lu", sizeof(v));


	return (uint32_t)(_mm256_extract_epi32(accumulator,0))+
		   (uint32_t)(_mm256_extract_epi32(accumulator,1))+
		   (uint32_t)(_mm256_extract_epi32(accumulator,2))+
		   (uint32_t)(_mm256_extract_epi32(accumulator,3))+
		   (uint32_t)(_mm256_extract_epi32(accumulator,4))+
		   (uint32_t)(_mm256_extract_epi32(accumulator,5))+
		   (uint32_t)(_mm256_extract_epi32(accumulator,6))+
		   (uint32_t)(_mm256_extract_epi32(accumulator,7)); // 0 --> 7 --> 4 bytes a position

}

uint32_t sumbytes(uint32_t* array, size_t size)
{
	uint32_t result = 0;
	for (size_t i = 0; i < size; ++i)
		result = result + (uint32_t)array[i];

	return result;
}

int main()
{	
	uint64_t start, end, clock; 
	uint32_t sum;
	uint32_t a[16], b[16];
	int i = 0;
	for(;i < 16; i++){
		a[i] = 0;
		b[i] = 0;
	}


	printf("size of a is: %lu\n", sizeof(a));

	// for(i = 0; i < 32; i++)
	// 	printf("%d",a[i]);

	start = getticks();
	sum = sumbytes(a,16);
	end = getticks();
	clock = end - start;
	printf("Total_time for addition:%llu\n",clock);
	printf("Result is %d\n",sum);

	start = rdtsc();
	sum = avx2_sumbytes_variant2(a,b,32);
	end = rdtsc();
	clock = end - start;
	printf("Total_time for addition with vectorization:%llu\n",clock);
	printf("Result is %d\n",sum);

	return 0;
}





/*


	v1[1000] =  [0, 0, 0 ,0, 0] --> 8192
	v1c[1000]=  [1, 1, 1, 1, 1] -->
	var c = 0


*/











