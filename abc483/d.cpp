#include <bits/stdc++.h> 
using namespace std;
#define int long long
void solve(){
    int n; cin >> n; 
    vector<int> a(n + 1); 
    for(int i = 1; i <= n; i++){
        cin >> a[i]; 
    }
    vector<int> sufmax(n + 2),sufmin(n + 2), premax(n + 2), premin(n + 2), pos(n + 1); 
    // vector<int> 
    for(int i = n; i >= 1; i--){
        sufmax[i] = max(a[i], a[i] + sufmax[i + 1]); 
        sufmin[i] = min(a[i], a[i] + sufmin[i + 1]);
    }

    for(int i = 1; i <= n; i++){
        premax[i] = max(premax[i - 1], a[i] + pos[i - 1]); 
        premin[i] = min(premin[i - 1], a[i] + pos[i - 1]); 
        pos[i] = pos[i - 1] + a[i];
    }
    int ansmx = premax[n] - premin[n] + 1; 
    for(int i = 1; i <= n; i++){
        int rt = max({premax[i - 1], pos[i - 1] - a[i], pos[i - 1] - a[i] + sufmax[i + 1]});
        int lft = min({premin[i - 1], pos[i - 1] - a[i], pos[i - 1] - a[i] + sufmin[i + 1]});
        ansmx = max(ansmx, rt - lft + 1);     
    }
    cout << ansmx << "\n"; 
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 
    int t = 1;
    // cin >> t;
    while(t--) solve(); 
}