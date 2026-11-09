#include <bits/stdc++.h> 
using namespace std;
#define int long long
const int N = 5e5 + 10; 
void solve(){
    int jie = sqrt(N); 
    int n, q; cin >> n; 
    vector<int> a(n + 1), b(n + 1); 
    vector<int> axiao, bxiao;
    axiao.reserve(n + 1); bxiao.reserve(n + 1);  
    vector<int> dans(N + 1);     
    int numda = 0; 
    vector<vector<int>> bb(jie + 1, vector<int> (jie+1)); 
    vector<int> ansx(N); 
    int resxiao =0; 
    for(int i = 1; i <= n; i++){
        cin >> a[i] >> b[i]; 
        if(b[i] >= jie){
            numda++; 
            for(int j = 1; j * b[i] - a[i] <= N; j++){
                int x = j * b[i] - a[i]; 
                dans[x]-= b[i] - 1;
                dans[x]--;  
            }
            axiao.push_back(a[i]); 
            bxiao.push_back(b[i]); 
        }
        else{
            for(int x = 0; x < b[i]; x++){
                bb[b[i]][x] += (x + a[i]) % b[i]; 
            }
        }
    }
    for(int i = 1; i <= n; i++) ansx[0] += a[i] % b[i];
    for(int i = 0; i < axiao.size(); i++){
        resxiao += axiao[i] % bxiao[i];
    }
    for(int x = 1; x <= N - 1; x++){
        resxiao += numda; 
        resxiao += dans[x]; 
        ansx[x] += resxiao; 
        for(int i = 1; i < jie; i++){
            ansx[x] += bb[i][x % i];
        }
        // if(x <= 10) cout << x << " " << resxiao << " " << ansx[x] << "\n"; 
    }
    cin >> q;
    while(q--){
        int x; cin >> x;
        cout << ansx[x] << "\n"; 
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 
    int t = 1;
    while(t--) solve(); 
}