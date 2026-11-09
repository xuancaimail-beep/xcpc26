#include <bits/stdc++.h>
using namespace std; 
#define int long long
using T=long long;  //全局数据类型
constexpr T eps=1e-8;
constexpr T INF=numeric_limits<T>::max();
constexpr T PI=3.1415926535897932384l;
// 点与向量
struct Point
{
    T x,y;
    bool operator==(const Point &a) const {return (abs(x-a.x)<=eps && abs(y-a.y)<=eps);}
    //定义篇序关系，这里是x是第一指标，y是第二指标
    bool operator<(const Point &a) const {if (abs(x-a.x)<=eps) return y<a.y-eps; return x<a.x-eps;} //可以不加
    bool operator>(const Point &a) const {return !(*this<a || *this==a);}
    Point operator+(const Point &a) const {return {x+a.x,y+a.y};} //必须加
    Point operator-(const Point &a) const {return {x-a.x,y-a.y};}
    Point operator-() const {return {-x,-y};}                //可以不加
    Point operator*(const T k) const {return {k*x,k*y};} 
    Point operator/(const T k) const {return {x/k,y/k};}
    T operator*(const Point &a) const {return x*a.x+y*a.y;}  // 点积
    T operator^(const Point &a) const {return x*a.y-y*a.x;}  // 叉积，注意优先级
    int toleft(const Point &a) const {const auto t=(*this)^a; return (t>eps)-(t<-eps);}  // to-left 测试 1左侧，-1右侧, 0共线
    T len2() const {return (*this)*(*this);}  // 向量长度的平方
    T dis2(const Point &a) const {return (a-(*this)).len2();}  // 两点距离的平方
    int quad() const // 象限判断 0:原点 1:x轴正 2:第一象限 3:y轴正 4:第二象限 5:x轴负 6:第三象限 7:y轴负 8:第四象限
    {
        if (abs(x)<=eps && abs(y)<=eps) return 4;
        if (abs(y)<=eps) return x>eps ? 3 : 8;
        if (abs(x)<=eps) return y>eps ? 6 : 1;
        return y>eps ? (x>eps ? 5 : 7) : (x>eps ? 2 : 0);
    }
    // 必须用浮点数
    T len() const {return sqrtl(len2());}  // 向量长度
};

// 极角排序
struct Argcmp
{
    bool operator()(const Point &a,const Point &b) const
    {
        const int qa=a.quad(),qb=b.quad();
        if (qa!=qb) return qa<qb;
        const auto t=a^b;
        // if (abs(t)<=eps) return a*a<b*b-eps;  // 不同长度的向量需要分开
        return t>eps;
    } 
};



signed main(){
    int n; cin >> n;
    vector<Point> a; 
    for(int i = 1; i <= n; i++){
        T x, y; cin >> x >> y;
        a.push_back({x, y}); 
    }
    sort(a.begin(), a.end(), Argcmp()); 
    for(int i = 0; i < n; i++){
        cout << a[i].x << " " << a[i].y << "\n"; 
    }
}