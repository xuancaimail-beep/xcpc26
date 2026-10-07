#include <bits/stdc++.h>
using namespace std;
signed main(){
    int n; cin >> n; 
    vector<pair<int, int>> edge;
    int u = 1; int v = 2; 
    cout << "? " << 1 << " " << 2 << endl; 
    int dist; cin >> dist; 
    vector<int> num(n + 2, -1);
    num[0] = 1; 
    num[dist] = 2;
    for(int i = 3; i <= n; i++){
        int du, dv; 
        cout << "? " << i  << " " << u << endl; 
        cin >> du;
        cout << "? " << i  << " " << v << endl; 
        cin >> dv;
        if(du + dv == dist){
            num[du] = i; 
        }else if(du + dist == dv){
            vector<int> _(n + 2, -1); 
            _[0] = i;
            for(int i = 0; i <= dist; i++){
                _[i + du] = num[i]; 
            }
            dist = dist + du;
            u = i;
            v = v; 
            num = _; 
        }else if(du == dv + dist){
            num[dist + dv] = i; 
            dist = du; 
            v = i; 
        }else if(du + dv > dist){
            continue; 
        }
    }
    // cout << "flag" << endl; 
    for(int i = 1; i <= dist; i++){
        int st = num[i - 1]; 
        int ed = num[i]; 
        edge.push_back({st, ed});
    }

    vector<int> distu(n + 1, -1); 
    for(int i = 0; i <= dist; i++){
        if(num[i] != -1) distu[num[i]] = i;     
    }
    vector<pair<int, int>> vec; 
    for(int i = 1; i <= n; i++){
        if(distu[i] == -1){
            int du, dv; 
            cout << "? " << i  << " " << u << endl; 
            cin >> du;
            vec.push_back({du, i});
        }
    }
    sort(vec.begin(), vec.end());
    int sz= vec.size(); 
    
    if(sz > 0) {
        int __ = vec[0].first;
        edge.push_back({num[__ - 1] , vec[0].second}); 
    }
    for(int i = 1; i < sz; i++){
        int st = vec[i - 1].second;
        int ed = vec[i].second; 
        edge.push_back({st, ed});
    }

    cout << "!" << endl; 
    for(auto [x, y]: edge){
        cout << x << " " << y << endl; 
    }
}