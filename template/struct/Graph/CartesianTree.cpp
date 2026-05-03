//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vl>
#define vvvl vector<vvl>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL

//最小値を根とする二分木を作る
struct CartesianTree {
    int root;  // root
    vector<int> par, left, right;
	vector<pair<int,int>> interval;

    CartesianTree() : root(0) {}
    CartesianTree(const vl & v) :
    root(0), par(v.size(), -1), left(v.size(), -1), right(v.size(), -1),interval(v.size(),{0,v.size()-1}) {
        vl st(v.size(), 0);
        int top = 0;
        loop (i,1,v.size()-1) {
            if (v[st[top]] > v[i]) {
                while (top >= 1 && v[st[top - 1]] > v[i]) top--;
                left[i] = st[top];
                par[left[i]] = i;
                if (top == 0) {
                    root = i;
                } else {
                    par[i] = st[top - 1];
                    right[par[i]] = i;
                }
                st[top] = i;
            } else {
                par[i] = st[top];
                right[par[i]] = i;
                st[++top] = i;
            }
        }
		//各木についての区間を書き込む
		queue<int> qu;
		qu.push(root);
		while(!qu.empty()){
			int i=qu.front();
			qu.pop();
			if(left[i]!=-1){
				interval[left[i]]={interval[i].first,i-1};
				qu.push(left[i]);
			}
			if(right[i]!=-1){
				interval[right[i]]={i+1,interval[i].second};
				qu.push(right[i]);
			}
		}
    }
	//親を取得する
	int get_par(int i){return par[i];}
	//左の子を取得する
	int get_left_child(int i){return left[i];}
	//右の子を取得する
	int get_right_child(int i){return right[i];}
	//子要素区間を取得する[L,R]の形
	pair<int,int> get_interval(int i){return interval[i];}
};

int main(){
	vl a={3,1,4,1,5};
	CartesianTree ct(a);
	rep(i,5){
		cout<<ct.get_par(i)<<" "<<ct.get_left_child(i)<<" "<<ct.get_right_child(i)<<endl;
		auto [l,r]=ct.get_interval(i);
		cout<<l<<" "<<r<<endl;
	}
	return 0;
}