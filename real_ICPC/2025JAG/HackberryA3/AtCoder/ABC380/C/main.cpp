#include <bits/stdc++.h>
using namespace std;

int main(){
  int n, k;
  cin >> n >> k;
  string s;
  cin >> s;
  
  vector<string> blocks;
  int kth_idx = -100100100;
  int current_one_cnt = 0;
  string now = "";
  for(int i = 0; i < s.size(); i++) {
    if (now.size() == 0 || now[now.size() - 1] == s[i]) {
      now += s[i];
    }
    else {
      if (now[0] == '1') {
        current_one_cnt++;
        if (current_one_cnt == k) {
          kth_idx = blocks.size();
        }
      }
      
      blocks.push_back(now);
      now = s[i];
    }
  }
  if (now[0] == '1') {
	current_one_cnt++;
	if (current_one_cnt == k) {
	  kth_idx = blocks.size();
	}
  }
  blocks.push_back(now);
  
  string ans = "";
  for(int i = 0; i < blocks.size(); i++) {
    int idx = i;
    if (i == kth_idx) idx = i - 1;
    else if(i == kth_idx - 1) idx = i + 1;
    
    ans += blocks[idx];
  }
  
  cout << ans << endl;
}
