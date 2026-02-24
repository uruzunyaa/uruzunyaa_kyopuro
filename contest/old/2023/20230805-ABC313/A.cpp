#include<iostream>

int main(){
    int n;
    std::cin>>n;
    int p[n];

    //最大値の人がいる要素番号
    int max=0;
    
    for(int i=0;i<n;i++){
        std::cin>>p[i];
        if(p[max]<=p[i])max=i;
    }
    if(max==0) std::cout<<0;
    else std::cout<<p[max]-p[0]+1;
    
}