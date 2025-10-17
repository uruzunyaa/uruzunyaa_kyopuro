#include<iostream>
using namespace std;
int main(){
    int n,h,x;
    cin>>n>>h>>x;
    int p=0;
    for(int i=0;i<n;i++){
        cin>>p;
        if(h+p>=x) {
            cout<<i+1;
            break;
        }
    }
    return 0;
}