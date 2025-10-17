#include<iostream>
using namespace std;
int main(){
    int p[26];
    for(int i=0;i<26;i++){
        cin>>p[i];
        char c='a'+p[i]-1;
        cout<<c;
    }
    return 0;
}