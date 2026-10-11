#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n; cin >> n; 
    if(n % 2 == 0){
        cout << -1 << " " << 1 << " " << n / 2 << "\n"; 
    }else{
        cout << -1 << "\n"; 
    }
}



signed main(){
    ios::sync_with_stdio(false); cin.tie(nullptr); 
    int t = 1; 
    while(t--) solve(); 
    return 0; 
}