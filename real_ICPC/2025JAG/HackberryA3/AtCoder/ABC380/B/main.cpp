#include <bits/stdc++.h>
using namespace std;

int main(){
  string s;
  cin >> s;
  
  int cnt = 0;
  for(int pos = 1; pos < s.size(); pos++) {
    if (s[pos] == '-') {
      cnt++;
    }
    else {
      cout << cnt << ' ';
      cnt = 0;
    }
  }
  
  return 0;
}
