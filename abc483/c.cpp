#include <bits/stdc++.h> 
using namespace std;

void solve(){
    int n, m; cin >> n >> m;
    vector<int> a(m + 1),b(m + 1); 
    vector<int> num(n + 1);
    set<pair<int, int>> st; 
    vector<vector<int>> ad(n + 1); 
    for(int i = 1; i <= m; i++){
        cin >> a[i] >> b[i];
        num[a[i]]++;
        ad[a[i]].push_back(b[i]); 
    }

    for(int i = 1; i <= n; i++){
        st.insert({num[i], -i});         
    }

    for(int i = 1; i <= n; i++){
        st.erase({num[i], -i}); 
        map<int, int> num2;
        for(auto X: ad[i]){
            num2[X]++; 
        }
        for(auto [j, _]: num2){
            st.erase({num[j], -j}); 
            st.insert({num[j] + _, -j}); 
        }
        cout << prev(st.end()) ->second * -1 << "\n"; 
    
        for(auto [j, _]: num2){
            st.erase({num[j] + _, -j}); 
            st.insert({num[j], -j}); 
        }
        st.insert({num[i], -i});
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 
    int t = 1;
    // cin >> t;
    while(t--) solve(); 
}