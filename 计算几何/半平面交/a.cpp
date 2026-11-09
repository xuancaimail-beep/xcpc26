#include <bits/stdc++.h>
using namespace std;
const double PI = acos(-1.0);
const double eps = 1e-6; // 精度误差，用于浮点数比较
// == 0,  < 0  -1,  >0 1
int dcmp(double d) {
    if(d == 0) return 0; 
    return d < 0 ? -1 : 1;
}
struct Point {
    int x, y;
    // --- 构造函数 ---
    Point(int x = 0, int y = 0) : x(x), y(y) {}
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
    int operator*(const Point& b) const { 
        return x * b.x + y * b.y; 
    }
    // 叉积 (Cross Product) - 注意：其运算符优先级低于加减法
    //开long long!
    int operator^(const Point& b) const {
        return x * b.y - y * b.x; 
    }
    
    bool operator==(const Point& b) const {
        return dcmp(x - b.x) == 0 && dcmp(y - b.y) == 0;
    }
    
    // 用于 sort 排序，定义偏序关系
    bool operator<(const Point& b) const {
        int d = dcmp(x - b.x);
        if (d != 0) return d < 0;
        return dcmp(y - b.y) < 0;
    }

    // --- 几何运算方法 ---
    double len() const { 
        return sqrt((long long)x * x + (long long)y * y); 
    }
    
    int len2() const { 
        return (long long)x * x + (long long)y * y; 
    }
    
    double dist(const Point& other) const { 
        return (*this - other).len(); 
    }
    int dist2(const Point& other) const { 
        return (*this - other).len2(); 
    }
    // 逆时针转 尽量不要使用三角函数，容易造成精度损失
    Point rot(double rad) const {
        double c = cos(rad), s = sin(rad);
        return Point(x * c - y * s, x * s + y * c);
    }
    
    Point rot(double cosr, double sinr) const {
        return Point(x * cosr - y * sinr, x * sinr + y * cosr);
    }
    
  	//共起点向量的to-left测试  
    int toleft(const Point& a) const {
        int res = (*this) ^ a;
        //return dcmp(res);
        if(res > 0) return 1; 
        if(res == 0)return 0; 
        if(res < 0) return -1; 
    }
    
    int quad() const // 象限判断 0:原点 1:x轴正 2:第一象限 3:y轴正 4:第二象限 5:x轴负 6:第三象限 7:y轴负 8:第四象限
    {
        if (x == 0 && y == 0) return 0;
        if (y == 0) return x>0 ? 1 : 5;
        if (x == 0) return y>0 ? 3 : 7;
        return y > 0 ? (x >  0 ? 2 : 4) : (x>0 ? 8 : 6);
    }
};

struct argcmp
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

struct Line {
    Point p, v;
    Line(Point x, Point y) : p(x), v(y){}
    int toleft(const Point& a) const { return v.toleft(a - p); } //toleft测试
    //两直线交点
    //注意共线时(v ^ b.v)为0，返回nan
    //注意重载数乘和加法运算
    Point inter(const Line& b) const {
        Point u = p - b.p;
        double t = (double)(b.v ^ u) / (double)(v ^ b.v);
        return p + v * t;
    }
    double dis(const Point& a) const { return abs(v ^ (a - p)) / v.len(); }//点到直线距离
    Point proj(const Point& a) const { return p + v * ((v * (a - p)) / v.len2()); }//点在直线上的投影
    bool operator<(const Line &a) const  // 半平面交算法定义的排序
    {
        if (abs(v ^ a.v) <= eps && v * a.v >= -eps) return toleft(a.p) == -1;
        return argcmp()(v, a.v);
    }
};


// 多边形
struct Polygon
{
    vector<Point> p;  // 以逆时针顺序存储

    size_t nxt(const size_t i) const {return i==p.size()-1?0:i+1;}
    size_t pre(const size_t i) const {return i==0?p.size()-1:i-1;}
    
    // 回转数
    // 返回值第一项表示点是否在多边形边上
    // 对于狭义多边形，回转数为 0 表示点在多边形外，否则点在多边形内
    pair<bool,int> winding(const Point &a) const
    {
        int cnt=0;
        for (size_t i=0;i<p.size();i++)
        {
            const Point u=p[i],v=p[nxt(i)];
            if (abs((a-u)^(a-v))<=eps && (a-u)*(a-v)<=eps) return {true,0};
            if (abs(u.y-v.y)<=eps) continue;
            const Line uv={u,v-u};
            if (u.y<v.y-eps && uv.toleft(a)<=0) continue;
            if (u.y>v.y+eps && uv.toleft(a)>=0) continue;2
            if (u.y<a.y-eps && v.y>=a.y-eps) cnt++;
            if (u.y>=a.y-eps && v.y<a.y-eps) cnt--;
        }
        return {false,cnt};
    }

    // 多边形面积的两倍
    // 可用于判断点的存储顺序是顺时针或逆时针
    double area() const
    {
        int sum=0;
        for (size_t i=0;i<p.size();i++) sum+=p[i]^p[nxt(i)];
        return sum;
    }

    // 多边形的周长
    double circ() const
    {
        double sum=0;
        for (int i=0;i<p.size();i++) sum+=p[i].dist(p[nxt(i)]);
        return sum;
    }
};

//凸多边形
struct Convex: Polygon
{
    // 闵可夫斯基和
    Convex operator+(const Convex &c) const  
    {
        const auto &p=this->p;
        vector<Segment> e1(p.size()),e2(c.p.size()),edge(p.size()+c.p.size());
        vector<Point> res; res.reserve(p.size()+c.p.size());
        const auto cmp=[](const Segment &u,const Segment &v) {return argcmp()(u.b-u.a,v.b-v.a);};
        for (size_t i=0;i<p.size();i++) e1[i]={p[i],p[this->nxt(i)]};
        for (size_t i=0;i<c.p.size();i++) e2[i]={c.p[i],c.p[c.nxt(i)]};
        rotate(e1.begin(),min_element(e1.begin(),e1.end(),cmp),e1.end());
        rotate(e2.begin(),min_element(e2.begin(),e2.end(),cmp),e2.end());
        merge(e1.begin(),e1.end(),e2.begin(),e2.end(),edge.begin(),cmp);
        const auto check=[](const vector<Point> &res,const Point &u)
        {
            const auto back1=res.back(),back2=*prev(res.end(),2);
            return (back1-back2).toleft(u-back1)==0 && (back1-back2)*(u-back1)>=-eps;
        };
        auto u=e1[0].a+e2[0].a;
        for (const auto &v:edge)
        {
            while (res.size()>1 && check(res,u)) res.pop_back();
            res.push_back(u);
            u=u+v.b-v.a;
        }
        if (res.size()>1 && check(res,res[0])) res.pop_back();
        return {res};
    }

    // 旋转卡壳
    // 例：凸多边形的直径的平方
    int rotcaliper() const
    {
        const auto &p=this->p;
        if (p.size()==1) return 0;
        if (p.size()==2) return p[0].dist2(p[1]);
        const auto area=[](const Point &u,const Point &v,const Point &w){return (w-u)^(w-v);};
        int ans=0;
        for (size_t i=0,j=1;i<p.size();i++)
        {
            const auto nxti=this->nxt(i);
            ans=max({ans,p[j].dist2(p[i]),p[j].dist2(p[nxti])});
            while (area(p[this->nxt(j)],p[i],p[nxti])>=area(p[j],p[i],p[nxti]))
            {
                j=this->nxt(j);
                ans=max({ans,p[j].dist2(p[i]),p[j].dist2(p[nxti])});
            }
        }
        return ans;
    }
    
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

    // 凸多边形关于某一方向的极点
    // 复杂度 O(logn)
    // 参考资料：https://codeforces.com/blog/entry/48868
    template<typename F> size_t extreme(const F &dir) const
    {
        const auto &p=this->p;
        const auto check=[&](const size_t i){return dir(p[i]).toleft(p[this->nxt(i)]-p[i])>=0;};
        const auto dir0=dir(p[0]); const auto check0=check(0);
        if (!check0 && check(p.size()-1)) return 0;
        const auto cmp=[&](const Point &v)
        {
            const size_t vi=&v-p.data();
            if (vi==0) return 1;
            const auto checkv=check(vi);
            const auto t=dir0.toleft(v-p[0]);
            if (vi==1 && checkv==check0 && t==0) return 1;
            return checkv^(checkv==check0 && t<=0);
        };
        return partition_point(p.begin(),p.end(),cmp)-p.begin();
    }
};


struct Segment {
    Point a, b; // 两个端点
    // -1 点在线段端点 | 0 点不在线段上 | 1 点严格在线段上
    int is_on(const Point& p) const {
        if (p == a || p == b) return -1;
        return dcmp((p - a) ^ (b - a)) == 0 && dcmp((p - a) * (p - b)) < 0;
    }
    // 判断线段直线是否相交
    // -1 直线经过线段端点 | 0 线段和直线不相交 | 1 线段和直线严格相交
    int is_inter(const Line& l) const {
        if (l.toleft(a) == 0 || l.toleft(b) == 0) return -1;
        return l.toleft(a) != l.toleft(b);
    }
    // 判断两线段是否相交
    // -1 在某一线段端点处相交 | 0 两线段不相交 | 1 两线段严格相交
    int is_inter(const Segment& s) const {
        if (is_on(s.a) || is_on(s.b) || s.is_on(a) || s.is_on(b)) return -1;
        Line l1(a, b - a), l2(s.a, s.b - s.a);
        return l1.toleft(s.a) * l1.toleft(s.b) == -1 && l2.toleft(a) * l2.toleft(b) == -1;
    }
    // 点到线段距离（必须用浮点数）
    double dis(const Point& p) const {
        if (dcmp((p - a) * (b - a)) < 0) return p.dist(a);
        if (dcmp((p - b) * (a - b)) < 0) return p.dist(b);
        return Line(a, b - a).dis(p);
    }
    // 两线段间距离（必须用浮点数）
    double dis(const Segment& s) const {
        if (is_inter(s) ) return 0;
        return min({dis(s.a), dis(s.b), s.dis(a), s.dis(b)});
    }
};



vector<Line> halfinter(vector<Line> l, const int lim=1e9)
{
    const auto check=[](const Line &a,const Line &b,const Line &c){return a.toleft(b.inter(c))<0;};
    // 无精度误差的方法，但注意取值范围会扩大到三次方
    /*const auto check=[](const Line &a,const Line &b,const Line &c)
    {
        const Point p=a.v*(b.v^c.v),q=b.p*(b.v^c.v)+b.v*(c.v^(b.p-c.p))-a.p*(b.v^c.v);
        return p.toleft(q)<0;
    };*/
    l.push_back({{-lim,0},{0,-1}}); l.push_back({{0,-lim},{1,0}});
    l.push_back({{lim,0},{0,1}}); l.push_back({{0,lim},{-1,0}});
    sort(l.begin(),l.end());
    deque<Line> q;
    for (size_t i=0;i<l.size();i++)
    {
        if (i>0 && l[i-1].v.toleft(l[i].v)==0 && l[i-1].v*l[i].v>eps) continue;
        while (q.size()>1 && check(l[i],q.back(),q[q.size()-2])) q.pop_back();
        while (q.size()>1 && check(l[i],q[0],q[1])) q.pop_front();
        if (!q.empty() && q.back().v.toleft(l[i].v)<=0) return vector<Line>();
        q.push_back(l[i]);
    }
    while (q.size()>1 && check(q[0],q.back(),q[q.size()-2])) q.pop_back();
    while (q.size()>1 && check(q.back(),q[0],q[1])) q.pop_front();
    return vector<Line>(q.begin(),q.end());
}


signed main(){
    int n; cin >> n;
    vector<Line> a;
    while(n--){
        int m; cin >> m;
        vector<Point> _(m); 
        for(int i = 0; i < m; i++){
            cin >> _[i].x >> _[i].y; 
        }
        for(int i = 1; i <= m; i++){
            a.push_back({_[i - 1], _[i % m] - _[i - 1]}); 
        }
    }
    vector<Line> res = halfinter(a); 
    Convex res2; 
    for(int i = 1; i <= res.size(); i++){
        Point p = res[i % res.size()].inter(res[i -1]); 
        res2.p.push_back(p); 
    }   
    cout << res2.area() <<"\n"; 
}