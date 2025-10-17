#include <iostream>
#include <string>
int main(){
    int n;
    std::string s;
    std::cin>>n>>s;
    std::cout<<s[0];
    for(int i=1;i<s.length();i++){
        
        if(s[i-1]=='n'&&s[i]=='a'){
            std::cout<<'y';
        }
        std::cout<<s[i];
    }
}