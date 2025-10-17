#include <iostream>
#include <string>
int main(){
    int n,a,b;
    std::string s;
    std::cin>>n>>a>>b>>s;
    
    //
    long min;
    for(int i=0;i<n;i++){
        int count = 0;
        for(int j=0;j<n/2;j++){
            if(s[j]!=s[n-j-1]) count++;
            
        }

        if(i==0){
            min = ((long)a*i)+((long)b*count);

        }
        if(min>((long)a*i+(long)b*count)){
            min=(long)a*i+(long)b*count;
        }

        char temp=s[0];
        for(int j=1;j<n;j++){
            s[j-1]=s[j];
        }
        s[n-1]=temp;
    }

    std::cout<<min;
}
