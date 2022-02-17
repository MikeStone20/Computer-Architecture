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

    /*
    *perform loop unrolling here
    *in this program, unroll the loop by 4 times;
    */
    int unroll_num = (n+1) % 4; 
    for(int i=0;i<m+1;i++)
    {

        //preconditioning loop in case where total number 
        //of iteration cannot be divided by 4
        int j = 0;
        for (j = 0; j < unroll_num; j++)
        {
            if(i==0 || j==0)
                dp[i][j]=0;
            else if(s[i-1]==t[j-1])
                dp[i][j]=1+dp[i-1][j-1];
            else
                dp[i][j]=std::max(dp[i-1][j],dp[i][j-1]);
        }

        //unrolling the remaining iterations
        for(j=unroll_num;j<n+1;j+=unroll_num)
        {
            //1st time
            if(i==0 || j==0)
                dp[i][j]=0;
            else if(s[i-1]==t[j-1])
                dp[i][j]=1+dp[i-1][j-1];
            else
                dp[i][j]=std::max(dp[i-1][j],dp[i][j-1]);

            //2nd time
            if(i==0 || j==1)
                dp[i][j]=0;
            else if(s[i-1]==t[j])
                dp[i][j+1]=1+dp[i-1][j];
            else
                dp[i][j+1]=std::max(dp[i-1][j+1],dp[i][j]);

            //3rd time
            if(i==0 || j==2)
                dp[i][j]=0;
            else if(s[i-1]==t[j+1])
                dp[i][j+2]=1+dp[i-1][j+1];
            else
                dp[i][j+2]=std::max(dp[i-1][j+2],dp[i][j+1]);

            //4th time
            if(i==0 || j==3)
                dp[i][j]=0;
            else if(s[i-1]==t[j+2])
                dp[i][j+3]=1+dp[i-1][j+2];
            else
                dp[i][j+3]=std::max(dp[i-1][j+3],dp[i][j+2]);
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

    //Run longest common subsequence code
    //In a doubly nested loop, 
    //Inner loop unrolling makes more sense when the inner loop trip count is higher than outer loop
    //because otherwise the cost of the preconditioning loop will be higher (in the case when outerloop has more iterations)
    uint64_t start, end, clock;
    clock = 0;
    
    if (str1.length() < str2.length()){
        start = rdtsc();
        std::cout<<"Result: "<< longestCommonSubsequence(str1,str2)<<'\n';
        end = rdtsc();
    }
    else{
        start = rdtsc();
        std::cout<<"Result: "<< longestCommonSubsequence(str2,str1)<<'\n';
        end = rdtsc();
    }
    
    clock = clock + (end - start);
    std::cout<<"Time taken: "<< clock <<'\n';
   

    return 0;
}