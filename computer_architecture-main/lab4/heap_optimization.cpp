#include<iostream>
#include<fstream>
#include<sstream>
#include<string>


inline uint64_t rdtsc(){  
    unsigned long a, d;  
    asm volatile ("rdtsc" : "=a" (a), "=d" (d)); 
    return a | ((uint64_t)d << 32);    
}

int longestCommonSubsequence(std::string s, std::string t) {
    int m=s.length();
    int n=t.length();

    //optimization using calloc to use contiguous memory space on the heap
    char * str1_data;
    char * str2_data;
    str1_data = (char *) calloc (m,sizeof(char));
    str2_data = (char *) calloc (n,sizeof(char));

    //sanity check
    if (str1_data == nullptr || str2_data == nullptr) exit (1);

    //initialize elements in str1_data and str2_data
    for (int count = 0; count < m; count++)
        str1_data[count] = s.at(count);

    for (int count = 0; count < n; count++)
        str2_data[count] = t.at(count);

    int dp[m+1][n+1];
    for(int i=0;i<m+1;i++)
    {
        for(int j=0;j<n+1;j++)
        {
            if(i==0 || j==0)
                dp[i][j]=0;
            else if(str1_data[i-1]==str2_data[j-1])
                dp[i][j]=1+dp[i-1][j-1];
            else
                dp[i][j]=std::max(dp[i-1][j],dp[i][j-1]);
        }
    }

    //free space in heap
    free(str1_data);
    free(str2_data);

    return dp[m][n];
}

int main()
{
    //reading file 1 to store in string 1
    std::ifstream file1("str1.txt");
    std::ofstream resultsFile;
    std::string str1;
    if (file1)
    {
      std::ostringstream ss;
      ss << file1.rdbuf(); // reading data
      str1 = ss.str();
    }
    //std::cout<<"str1: "<<str1 <<'\n';

    //reading file 2 to store in string 2
    std::ifstream file2("str2.txt");
    std::string str2;
    if (file2)
    {
      std::ostringstream ss;
      ss << file2.rdbuf(); // reading data
      str2 = ss.str();
    }
    //std::cout<<"str2: "<<str2 <<'\n';

    //run longest common subsequence code
    uint64_t start, end, clock;
    clock = 0;
    start = rdtsc();
    std::cout<<"Result: "<< longestCommonSubsequence(str1,str2)<<'\n';
    end = rdtsc();
    clock = clock + (end - start);

    std::cout<<"Time taken (optimization using heap): "<< clock <<'\n';


    return 0;
}