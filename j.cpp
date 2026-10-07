#include <bits/stdc++.h>
using namespace std;
#define ll long long 
int dcmp(int d) {
    if(d== 0) return 0; 
    return d < 0 ? -1 : 1;
}

struct Point {
    int x, y;
    // --- 构造函数 ---
    Point(int x = 0,int y = 0) : x(x), y(y) {}
    // --- 运算符重载 ---
    Point operator+(const Point& b) const {
        return Point(x + b.x, y + b.y); 
    }
    Point operator-(const Point& b) const { 
        return Point(x - b.x, y - b.y); 
    }
    //一定要加
    Point operator*(double k) const { 
        return Point(x * k, y * k); 
    }
    
    Point operator/(double k) const {
        return Point(x / k, y / k); 
    }
    
    // 点积 (Dot Product)
    ll operator*(const Point& b) const { 
        return (ll)x * b.x + (ll)y * b.y; 
    }
    
    // 叉积 (Cross Product) - 注意：其运算符优先级低于加减法
    //开long long!
    ll operator^(const Point& b) const {
        return (ll)x * b.y - (ll)y * b.x; 
    }
    
    bool operator==(const Point& b) const {
        return dcmp(x - b.x) == 0 && dcmp(y - b.y) == 0;
    }
    
    ll len2() const { 
        return (ll)x * x + y * y; 
    }

  	//共起点向量的to-left测试  
    ll toleft(const Point& a) const {
        ll res = (*this) ^ a;
        //return dcmp(res);
        if(res > 0) return 1; 
        if(res == 0)return 0; 
        if(res < 0) return -1; 
    }
    bool operator<(const Point& b) const {
        int d = dcmp(x - b.x);
        if (d != 0) return d < 0;
        return dcmp(y - b.y) < 0;
    }

};

vector<Point> convex_hull(vector<Point> p){
    sort(p.begin(), p.end()); 
    p.erase(unique(p.begin(), p.end()),p.end());
    if(p.size() <= 2) return p;
    vector<Point> st; 
    auto check = [](const vector<Point> &st, const Point &u){
        auto back1 = st.back(); 
        auto back2 = *prev(st.end(), 2); 
        return (back1 - back2).toleft(u - back1) <= 0; 
    };
    for(const Point &u :p){
        while(st.size() > 1 && check(st, u)){
            st.pop_back(); 
        }
        st.push_back(u); 
    }
    int k = st.size(); 
    for(int i = p.size() - 2; i >= 0; i--){
        Point &u = p[i];
        while(st.size() > k && check(st,u)){
            st.pop_back(); 
        }    
        st.push_back(u); 
    }
    st.pop_back(); 
    return st; 
}


int main(int argc, char *argv[]) {
    int id = argc > 1 ? atoi(argv[1]) : 0;
    int n; cin >> n;
    vector<Point> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i].x >> a[i].y;
    }
    sort(a.begin(), a.end()); 
    auto h = convex_hull(a); 
    vector<Point> res; 
    for(int i = 0; i < h.size(); i++){
        if(res.size() <= 1) {
            res.push_back(h[i]); 
            continue;
        }
        Point lst = res[(int)res.size() - 1];
        Point lst2 = res[(int)res.size() - 2];
        if((h[i] - lst) ^ (h[i] -lst2) == 0){
            res.pop_back();
        }
        res.push_back(h[i]); 
    }
    if(res.size() >= 3){
        Point fst = res[0];
        Point fst2 = res[1]; 
        Point lst = res[(int)res.size() - 1];
        if( (fst - fst2) ^ (lst - fst) == 0) {
            vector<Point> _;
            for(int i = 1; i < res.size(); i++){
                _.push_back(res[i]); 
            }
            res = _; 
        }
    }

    if(res.size() >= 3){
        Point fst = res[0];
        Point lst2 = res[(int)res.size() - 2]; 
        Point lst = res[(int)res.size() - 1];
        if( (fst - lst2) ^ (lst - fst) == 0) {
            res.pop_back(); 
        }
    }

    if(id != 0){
        cout << res.size() << endl; 
        for(auto [x, y]: res){
            cout << x << " " << y << endl;
        }
    }else{
        for(int i = 0; i < 3; i++){
            int num; cin >> num; 
            while(num--){
                int x, y; cin >> x >> y;
                res.push_back({x, y}); 
            }
        }
        a = res; 
        sort(a.begin(), a.end()); 
        h = convex_hull(a); 
        res = {}; 
        for(int i = 0; i < h.size(); i++){
            if(res.size() <= 1) {
                res.push_back(h[i]); 
                continue;
            }
            Point lst = res[(int)res.size() - 1];
            Point lst2 = res[(int)res.size() - 2];
            if((h[i] - lst) ^ (h[i] -lst2) == 0){
                res.pop_back();
            }
            res.push_back(h[i]); 
        }
        if(res.size() >= 3){
            Point fst = res[0];
            Point fst2 = res[1]; 
            Point lst = res[(int)res.size() - 1];
            
            if((fst - fst2) ^ (lst - fst) == 0) {
                vector<Point> _;
                for(int i = 1; i < res.size(); i++){
                    _.push_back(res[i]); 
                }
                res = _; 
            }
        }

        if(res.size() >= 3){
            Point fst = res[0];
            Point lst2 = res[(int)res.size() - 2]; 
            Point lst = res[(int)res.size() - 1];
            if( (fst - lst2) ^ (lst - fst) == 0) {
                res.pop_back(); 
            }
        }
        cout << res.size() << endl; 
        Point Inf = {(ll)1e8,(ll)1e8};
        ll sum = 0; 
        int sz = res.size(); 
        ll len = 0; 
        for(int i = 0; i < res.size(); i++){
            sum += (Inf - res[i]) ^ (Inf - res[(i + 1) % sz]); 
            ll dx = res[(i + 1) % sz].x - res[i].x;
            ll dy = res[(i + 1) % sz].y - res[i].y;
            len += dx * dx + dy * dy;
        }
        cout << abs(sum) << endl << len << endl; 
    }
}


