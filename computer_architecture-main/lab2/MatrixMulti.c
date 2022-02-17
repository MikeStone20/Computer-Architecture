#include<stdio.h>    
#include<stdlib.h>  

inline u_int64_t rdtsc(){
    unsigned long a, d;
    asm volatile ("rdtsc" : "=a" (a), "=d" (d));
    return a | ((u_int64_t)d << 32);
 } 

int main(){  

	u_int64_t start, end, clock;
	clock = 0;

	int r,i,j,k; 
	system("cls");  
	printf("enter the desired nxn dimension=\n");    
	scanf("%d",&r);    
	start = rdtsc();  
	int a[r][r],b[r][r],mul[r][r];

	int num = 1;

	for(i=0;i<r;i++){    
		for(j=0;j<r;j++){    
			a[i][j] = num++;   
		}
		num = 1;    
	}   
	
	num = 1;
	
	for(i=0;i<r;i++){    
		for(j=0;j<r;j++){    
			b[i][j] = num++;    
		}  

		num = 1;  
	}    
    
	for(i=0;i<r;i++){    
		for(j=0;j<r;j++){    
			mul[i][j]=0;    
			for(k=0;k<r;k++){    
				mul[i][j]+=a[i][k]*b[k][j];    
			}    
		}    
	}
	
	for(i=0;i<r;i++){
		for(j=0;j<r;j++){
			printf("%d\t ",mul[i][j]);
		}
		printf("\n");
	}

end = rdtsc();
clock = clock + (end-start);
printf("Total:%lu\n", clock);
return 0;  
} 
