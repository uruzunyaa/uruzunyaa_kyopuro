#include<stdio.h>

int main(){
    int n;
    scanf("%d",&n);
    int m;
    scanf("%d",&m);

    if(n*3<m){
        if(n*4<m){
            printf("-1 -1 -1");
        }else{
            printf("%d %d %d",0,4*n-m,m-3*n);
        }
    }else{
        if(m<n*2){
            printf("-1 -1 -1");
        }else{
            printf("%d %d %d",3*n-m,m-2*n,0);
        }
    }
}