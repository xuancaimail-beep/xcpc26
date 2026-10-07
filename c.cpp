#include <bits/stdc++.h>
using namespace std;

string a; 
string b; 
vector<int> kmp_next; 

void getNext(int m){
	int j = 0;
	// 初始化next[0]的值
	kmp_next[0] = 0;
	for(int i=1; i<m; ++i){
		// 当这一位不匹配时，将j指向此位之前最大公共前后缀的位置
		while(j>0 && b[i]!=b[j]) j=kmp_next[j-1];
		// 如果这一位匹配，那么将j+1，继续判断下一位
		if(b[i]==b[j]) ++j;
		// 更新next[i]的值
		kmp_next[i] = j;
	}
}
int kmp(int n,int m){
	int i, j = 0;
	// 初始化位置p = -1
	int p = -1;
	// 初始化next数组
	getNext(m);
	for(i=0; i<n; ++i){
		// 当这一位不匹配时，将j指向此位之前最大公共前后缀的位置
		while(j>0 && b[j]!=a[i]) j=kmp_next[j-1];
		// 如果这一位匹配，那么将j+1，继续判断下一位
		if(b[j]==a[i]) ++j;
		// 如果是子串(m位完全匹配)，则更新位置p的值，并中断程序
		if(j==m){
			p = i - m + 1;
			break;
		}
	}
	// 返回位置p的值
	return p;
}

int main(){
    int r; cin >> r;
    if(r == 1){
        int n; cin >> n; 
        cin >> a >> b;
        a = b + b;
        kmp_next.resize(2 * n); 
        cout << kmp(n, 2 * n) << endl; 
    }else{
        int s; cin >> s;
        cin >> b;
        int q; cin >> q;
        if(q == 0){
            cout << endl; 
            return 0; 
        }
        int n =(int)b.size(); 
        while(q--){
            int x; cin >> x;
            cout << b[(x + s) % n];
        }
        cout << endl; 
    }
}