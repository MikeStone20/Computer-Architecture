#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include <pthread.h>

#define NUM_THREADS 2
int** cache;
std::string str1 = "";
std::string str2 = "";

struct arry_dim_struct{
    int rowStart;
    int rowEnd;
    int colLength;
};

inline uint64_t rdtsc(){  
    unsigned long a, d;  
    asm volatile ("rdtsc" : "=a" (a), "=d" (d)); 
    return a | ((uint64_t)d << 32);    
}


int longestCommonSubsequence(std::string s, std::string t) {
    int m=s.length();
    int n=t.length();

    int dp[m+1][n+1];

    for(int i=0;i<m+1;i++)
    {
        for(int j=0;j<n+1;j++)
        {
            if(i==0 || j==0)
                dp[i][j]=0;
            else if(s[i-1]==t[j-1])
                dp[i][j]=1+dp[i-1][j-1];
            else
                dp[i][j]=std::max(dp[i-1][j],dp[i][j-1]);
        }
    }
    return dp[m][n];
}

void *longestCommonSubsequenceThreads(void *arguments) {
    struct arry_dim_struct* args = (struct arry_dim_struct *)arguments;

    int n= args -> colLength;
    int i = args -> rowStart;
    int rowEnd = args -> rowEnd;

    for(;i<=rowEnd;i++)
    {
        for(int j=1;j<=n-1;j++)
        {
            // std::cout<<str1[i-1]<<' ';
            // std::cout<<str2[i-1]<<'\n';
            if(str1[i-1]==str2[j-1]){
                while(cache[i-1][j-1] == -1){
                    continue;
                }
                cache[i][j]=1+cache[i-1][j-1];
            }
            else{
                while(cache[i-1][j] == -1){
                    continue;
                }
                cache[i][j]=std::max(cache[i-1][j],cache[i][j-1]);
            }
        }
    }

    return 0;
   
}

int main()
{
    //reading file 1 to store in string 1
    std::ifstream file1("str1.txt");
    //std::ofstream resultsFile;
    //std::string str1;
    if (file1)
    {
      std::ostringstream ss;
      ss << file1.rdbuf(); // reading data
      str1 = ss.str();
    }
    //std::cout<<"str1: "<<str1 <<'\n';

    //reading file 2 to store in string 2
    std::ifstream file2("str2.txt");
    //std::string str2;
    if (file2)
    {
      std::ostringstream ss;
      ss << file2.rdbuf(); // reading data
      str2 = ss.str();
    }
    //std::cout<<"str2: "<<str2 <<'\n';

    //run longest common subsequence code
    uint64_t start, end, clock;
    if(str1.length() < 4 || str2.length() < 4){
        clock = 0;
        start = rdtsc();
        
        std::cout<<"Result: "<< longestCommonSubsequence(str1,str2)<<'\n';
        
        end = rdtsc();
        clock = clock + (end - start);

        std::cout<<"Time taken: "<< clock <<'\n';
        
    }else{
        pthread_t tid;
        struct arry_dim_struct thread1_params;
        struct arry_dim_struct thread2_params;
        struct arry_dim_struct thread3_params;
        struct arry_dim_struct thread4_params;
        int rowLength = 0;
        int colLength = 0;
        
      
        rowLength = str1.length()+1;
        colLength = str2.length()+1;
        

        cache = new int* [rowLength]; // creating global 2D array
        for(int x = 0; x < rowLength; x++){
            cache[x] = new int [colLength];
        }
       
        for(int m = 0; m <rowLength; m++){ // indexing -1s for non index 0 locations
            for(int n = 0; n < colLength; n++){
                if(m != 0 && n != 0)
                    cache[m][n] = -1;
                else
                     cache[m][n] = 0;
                
            }
        }
       
        

        int remainingRows = (rowLength-1) % 4;
        int rowsPerThread = (rowLength-1) / 4;
        thread1_params.rowStart = 1;
        thread1_params.rowEnd = rowsPerThread;
        thread1_params.colLength = colLength;
        thread2_params.colLength = colLength;
        thread3_params.colLength = colLength;
        thread4_params.colLength = colLength;


        if(remainingRows > 0){
            thread1_params.rowEnd = thread1_params.rowEnd + remainingRows; // accounting for uneven arrays
            // std::cout<<remainingRows<<'\n';
            // std::cout<<rowsPerThread<<'\n';
            // std::cout<<rowLength<<'\n';
                   
        }

        //parition rows
        // std::cout<<thread1_params.rowStart<<'\n';
        // std::cout<<thread1_params.rowEnd<<'\n';
        thread2_params.rowStart = thread1_params.rowEnd+1;
        thread2_params.rowEnd = thread1_params.rowEnd+rowsPerThread;
        // std::cout<<thread2_params.rowStart<<'\n';
        // std::cout<<thread2_params.rowEnd<<'\n';
        thread3_params.rowStart = thread2_params.rowEnd+1;
        thread3_params.rowEnd = thread2_params.rowEnd+rowsPerThread;
        // std::cout<<thread3_params.rowStart<<'\n';
        // std::cout<<thread3_params.rowEnd<<'\n';
        thread4_params.rowStart = thread3_params.rowEnd+1;
        thread4_params.rowEnd = thread3_params.rowEnd+rowsPerThread;
        // std::cout<<thread4_params.rowStart<<'\n';
        // std::cout<<thread4_params.rowEnd<<'\n';

        clock = 0;
        start = rdtsc();
        pthread_create(&tid, NULL, longestCommonSubsequenceThreads, (void *)&thread1_params);
        pthread_create(&tid, NULL, longestCommonSubsequenceThreads, (void *)&thread2_params);
        pthread_create(&tid, NULL, longestCommonSubsequenceThreads, (void *)&thread3_params);
        pthread_create(&tid, NULL, longestCommonSubsequenceThreads, (void *)&thread4_params);
        pthread_join(tid,NULL);
        end = rdtsc();
        clock = clock + (end - start);
        std::cout<<"Result: "<< cache[rowLength-1][colLength-1]<<'\n';
        std::cout<<"Time taken for multithreading: "<< clock <<'\n';
        // resultsFile.open("multithreading.txt",  std::ios_base::app);
        // resultsFile << clock << '\n';
        // resultsFile.close();

        }
    

    return 0;
}