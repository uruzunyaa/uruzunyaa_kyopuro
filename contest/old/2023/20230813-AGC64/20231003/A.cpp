#include<iostream>
#include<vector>
using namespace std;
int main(){
    int n;
    cin>>n;

    for(int i=1;i<=n-3;i++){
        int j;
        for(j=n;j>=i;j-=2){
            cout<<j<<" ";
        }
		//7 5 3 1

        if(j+2==i){
            j+=3;
        }else{
            j+=1;
        }

        for(;j<n;j+=2){
            cout<<j<<" ";
        }
		//2 4 6
    }
    cout<<n<<" "<<n-2<<" "<<n<<" "<<n-1<<" "<<n<<" "<<n-1<<endl;
    return 0;
}