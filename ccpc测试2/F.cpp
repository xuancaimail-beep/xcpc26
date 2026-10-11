#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;

struct SegmentTree{
    struct node{
        int l, r;
        int max1;
        int max2; 
    };
    int n;
    vector<int> a;
    vector<int> mp; //找到数组下标对应的叶子区间编号
    vector<node> seg;
    // lazy的定义: i的lazy 表示第 i 个结点已经加过，要传给 i<<1 和 i<<1|1
    SegmentTree(vector<int> _a){
        n = (int)_a.size() - 1;
        a = _a;
        seg.resize(n << 2);
        mp.resize(n + 1); 
        build(1, 1, n);
    }
    void pushup(int i){
        // seg[i].val = seg[i << 1].val + seg[i << 1 | 1].val;
        // seg[i].max1 = max()
        vector<int> _; 
        _.push_back(seg[i << 1].max1);
        _.push_back(seg[i << 1].max2);
        _.push_back(seg[i << 1 | 1].max1); 
        _.push_back(seg[i << 1 | 1].max2);
        sort(_.begin(), _.end()); 
        seg[i].max1 = _[3]; 
        seg[i].max2 = _[2];     
    }
    void build(int i, int l, int r){
        seg[i].l = l; seg[i].r = r;
        if(l == r){
            seg[i].max1 = a[l]; seg[i].max2 = -1; 
            return;
        }
        int mid = (l + r) >> 1;
        build(i << 1, l, mid);
        build(i << 1 | 1 , mid + 1 , r);
        pushup(i);
    }

    pair<int, int> query(int i, int L, int R){
        if(seg[i].r < L || R < seg[i].l) return {-1, -1};         // 没有交集
        if(L <= seg[i].l && seg[i].r <= R) return {seg[i].max1, seg[i].max2}; // 完全包含
        auto pair1 = query(i << 1, L, R); 
        auto pair2 = query(i << 1 | 1, L , R); 
        vector<int> _; 
        _.push_back(pair1.first);
        _.push_back(pair1.second);
        _.push_back(pair2.first); 
        _.push_back(pair2.second);
        sort(_.begin(), _.end()); 
        return {_[3], _[2]};
        // return query(i << 1, L, R) + query(i << 1 | 1, L , R);
    }
};


signed main(){
    int n; cin >> n;
    vector<int> a(n + 1); 
    for(int i = 1; i <= n; i++) cin >> a[i]; 
    SegmentTree T(a);
    int sum = 0; 
    auto res = T.query(1, 2, 3); 
    for(int i = 1; i <= n; i++){
        int l = 1; int r = i;
        while(l <= r){
            int mid = (l + r) / 2;
            auto res = T.query(1,mid, i);
            cout << "dbg" << mid << " " << i << " " << res.first << " " << res.second << "\n"; 
            if(a[i] == res.first || a[i] == res.second){
                r = mid - 1;
            }else{
                l = mid + 1; 
            }
        }
        int R = i - 1;  int L = r + 1;
        if(R - L + 1 >= 0) sum += (R - L + 1) * i; 
        cout << "right" << i << "  " << L << " " << R << " " << R - L + 1<< "\n"; 
        l = i; r = n;
        while(l <= r){
            int mid = (l + r) / 2;
            auto res = T.query(1, i, mid);
            if(a[i] == res.first || a[i] == res.second){
                l = mid + 1;       
            }else{
                r = mid - 1; 
            }
        }

        L = i + 1; R = l - 1;  
        if(R - L + 1 > 0) sum -= (R - L + 1) * i;
        cout << "left" << i << "  " << L << " " << R << " " << R - L + 1<< "\n"; 

    }
    cout << sum << "\n"; 
}