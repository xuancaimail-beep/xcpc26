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
    int quad() const // 象限判断 0:原点 1:x轴正 2:第一象限 3:y轴正 4:第二象限 5:x轴负 6:第三象限 7:y轴负 8:第四象限
    {
        if (abs(x)<=eps && abs(y)<=eps) return 0;
        if (abs(y)<=eps) return x>eps ? 1 : 5;
        if (abs(x)<=eps) return y>eps ? 3 : 7;
        return y>eps ? (x>eps ? 2 : 4) : (x>eps ? 8 : 6);
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

// 直线
struct Line
{
    Point p,v;  // p 为直线上一点，v 为方向向量
    bool operator==(const Line &a) const {return v.toleft(a.v)==0 && v.toleft(p-a.p)==0;}
    int toleft(const Point &a) const {return v.toleft(a-p);}  // to-left 测试
    bool operator<(const Line &a) const  // 半平面交算法定义的排序
    {
        if (abs(v^a.v)<=eps && v*a.v>=-eps) return toleft(a.p)==-1;
        return Argcmp()(v,a.v);
    }
    // 必须用浮点数
    Point inter(const Line &a) const {return p+v*((a.v^(p-a.p))/(v^a.v));}  // 直线交点
    T dis(const Point &a) const {return abs(v^(a-p))/v.len();}  // 点到直线距离
    Point proj(const Point &a) const {return p+v*((v*(a-p))/(v*v));}  // 点在直线上的投影
};

//线段
struct Segment
{
    Point a,b;
    bool operator<(const Segment &s) const {return make_pair(a,b)<make_pair(s.a,s.b);}
    // 判定性函数建议在整数域使用

    // 判断点是否在线段上
    // -1 点在线段端点 | 0 点不在线段上 | 1 点严格在线段上
    int is_on(const Point &p) const  
    {
        if (p==a || p==b) return -1;
        return (p-a).toleft(p-b)==0 && (p-a)*(p-b)<-eps;
    }

    // 判断线段直线是否相交
    // -1 直线经过线段端点 | 0 线段和直线不相交 | 1 线段和直线严格相交
    int is_inter(const Line &l) const
    {
        if (l.toleft(a)==0 || l.toleft(b)==0) return -1;
        return l.toleft(a)!=l.toleft(b);
    }
    
    // 判断两线段是否相交
    // -1 在某一线段端点处相交 | 0 两线段不相交 | 1 两线段严格相交
    int is_inter(const Segment &s) const
    {
        if (is_on(s.a) || is_on(s.b) || s.is_on(a) || s.is_on(b)) return -1;
        const Line l{a,b-a},ls{s.a,s.b-s.a};
        return l.toleft(s.a)*l.toleft(s.b)==-1 && ls.toleft(a)*ls.toleft(b)==-1;
    }
};

// 多边形
struct Polygon
{
    vector<Point> p;  // 以逆时针顺序存储

    size_t nxt(const size_t i) const {return i==p.size()-1?0:i+1;}
    size_t pre(const size_t i) const {return i==0?p.size()-1:i-1;}
    

};

//凸多边形
struct Convex: Polygon
{

    // 判断点是否在凸多边形内
    // 复杂度 O(logn)
    // -1 点在多边形边上 | 0 点在多边形外 | 1 点在多边形内
    int is_in(const Point &a) const
    {
        const auto &p=this->p;
        if (p.size()==1) return a==p[0]?-1:0;
        if (p.size()==2) return Segment{p[0],p[1]}.is_on(a)?-1:0; 
        if (a==p[0]) return -1;
        if ((p[1]-p[0]).toleft(a-p[0])==-1 || (p.back()-p[0]).toleft(a-p[0])==1) return 0;
        const auto cmp=[&](const Point &u,const Point &v){return (u-p[0]).toleft(v-p[0])==1;};
        const size_t i=lower_bound(p.begin()+1,p.end(),a,cmp)-p.begin();
        if (i==1) return Segment{p[0],p[i]}.is_on(a)?-1:0;
        if (i==p.size()-1 && Segment{p[0],p[i]}.is_on(a)) return -1;
        if (Segment{p[i-1],p[i]}.is_on(a)) return -1;
        return (p[i]-p[i-1]).toleft(a-p[i-1])>0;
    }
};


signed main(){
    int n; cin>> n;
    int fl = 1; 
    Convex A;
    A.p.resize(n);
    for(int i = n - 1; i >= 0; i--){
        cin >> A.p[i].x >> A.p[i].y;
    }

    int m; cin >> m; 
    while(m--){
        T x, y; cin >> x >> y;
        Point p = {x, y}; 
        if(A.is_in(p) != 1){
            fl = 0; 
        }
    }


    if(fl == 1){
        cout << "YES\n";
    }else{
        cout << "NO\n"; 
    }
    return 0; 
}