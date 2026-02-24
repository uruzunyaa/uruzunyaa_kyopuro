#include<iostream>
#include<algorithm>
#include<vector>
int main(){
    int n;
    int m;
    std::cin>>n>>m;
    int a[m];
    int b[m];

    
    
    for(int i=0;i<m;i++){
        std::cin>>a[i]>>b[i];
    }
    
    //配列Aにあって配列Bにない要素を探す。その要素数が１ならOK
    std::vector<int> saikyo;
    for(int i=1;i<=n;i++){
        //iが探索する数字
        //trueになったら、存在したという事
        bool flagA=false;
        bool flagB=false;
        for(int j=0;j<m;j++){
            if(a[j]==i) flagA=true;
            if(b[j]==i) flagB=true;
        }
        if(flagA==true&&flagB==false) saikyo.push_back(i);
    }
    if(saikyo.size()==1){
        std::cout<<saikyo[0];
    }else{
        std::cout<<-1;
    }
}