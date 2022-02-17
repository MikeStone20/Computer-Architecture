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
    for(int i = 0; i < 10; i++){
        clock = 0;
        start = rdtsc();
    
        std::cout<<"Result: "<< longestCommonSubsequence(str1,str2)<<'\n';
    
        end = rdtsc();
        clock = clock + (end - start);
        resultsFile.open("vector.txt",  std::ios_base::app);
        std::cout<<"Time taken: "<< clock <<'\n';
        resultsFile.close();
    }   

    return 0;
}