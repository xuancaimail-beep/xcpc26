#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+10; 
vector<int> L(N), R(N), fa(N + 1), stk; 
struct BIT{
    int len;
    vector<int>tr;
    BIT(int n=0){//给定n初始化
        len=n; 
        tr.resize(len+1,0);
    }
    int lowbit(int x){
      return x&-x;
    }
    void init(int n,vector<int>a){//给定n和序列初始化
        len=n; 
        tr.resize(n+1,0);
        for(int i=1;i<=n;i++) update(i,a[i]);
    }
    void update(int pos,int val){
    	for(; pos<=len; pos+=lowbit(pos) ) tr[pos]+=val;
    }
    void update(int l,int r,int val){//对于差分序列,区间和为单点值,配合query(pos)使用
        update(l,val);
        update(r+1,-val);
    }
    int query(int pos){
        int sum=0;
        while(pos){
            sum+=tr[pos];
            pos-=lowbit(pos);
        }
        return sum;
    }
}T;

//L[i], R[i], fa[i]指的是原序列的下标


int res = 0; 

void dfs(int x, int fa){
    if(L[x] == 0){
        res += T.query(x); 
    }

    if(R[x] == 0){
        res += Tsum - T.query(x - 1);
    }
    if(L[x]){
           
    }
    if(R[x]){
        
    }
}

signed main(){
    int n;  cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++){
        cin >> a[i]; 
    }
    
    vector<int> L(n+1, 0), R(n+1, 0), fa(n+1, 0), stk;
    for (int i = 1; i <= n; ++i) {
        int last = 0;
        while (!stk.empty() && a[stk.back()] > a[i]) { // 最小堆；排列可用 '>'
            last = stk.back();
            stk.pop_back();
        }
        if (last) { 
            L[i] = last;
            fa[last] = i;
        }
        if (!stk.empty()) { 	//当前元素为最大值
            R[stk.back()] = i;
            fa[i] = stk.back();
        }
        stk.push_back(i);
    }
    int root = 0;
    for (int i = 1; i <= n; ++i) if (fa[i] == 0) { root = i; break; }
    
        
    


}
