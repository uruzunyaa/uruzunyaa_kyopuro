#include<stdio.h>

int main(){
    int n;
    scanf("%d",&n);
    scanf("%c");

    char s[n][n+1];
    char kaiten[n][n+1];

    for(int i=0;i<n;i++){
        for(int j=0;j<n+1;j++){
            scanf("%c",&s[i][j]);
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            kaiten[i][j]=s[n-j-1][i];
            printf("%c",kaiten[i][j]);
        }
        printf("\n");
    }
}