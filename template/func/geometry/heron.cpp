#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
#define eps 0.000000001
#define circlepi 3.14159265358979323846

//ヘロンの公式で三角形の面積を求める。
double heron(double a,double b,double c){
	double s=(a+b+c)/2.0;
	double ans=sqrt(s*(s-a)*(s-b)*(s-c));
	return ans;
}


int main(){
	return 0;
}

