#include<iostream>
#include<algorithm>
#include<vector>
int main(){
    int n;
    long sum=0;
    std::cin>>n;
    long a[n];
    long end[n];
    for(int i=0;i<n;i++){
        std::cin>>a[i];
        sum+=a[i];
    }
    for(int i=0;i<n-(sum % n);i++){
        end[i]=sum/n;
    }
    for(int i=n-(sum % n);i<n;i++){
        end[i]=(sum/n)+1;
    }
    std::sort(a,a+n);

    //ここまででスタートとゴールが確定。後は差を取りその半分を計算する
    long sum2=0;
    for(int i=0;i<n;i++){
        sum2+=std::abs(a[i]-end[i]);
    }
    std::cout<<sum2/2;
}