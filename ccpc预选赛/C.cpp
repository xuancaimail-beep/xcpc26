#include <bits/stdc++.h>
using namespace std; 

void solve(){
    double w, x1, x2, yc, u, v;
    cin >> w >> x1 >> x2 >> yc >> u >> v; 
    double res = 1.0 * (w - yc) / v; 
    double add = 1e16;  
    double v1y = v ; double v1x = -u; 
    double xres1 = v1x * yc / v1y; 
    if(xres1 > x2 || xres1 < x1){
        add = min(add, yc / v1y); 
    }
    if(abs(x1) < 1e-9){
        if(v * v - u * u > 1e-9){
            add = min(add, yc / (sqrt(v * v  - u * u))); 
        }
    }else{
        double lam =  yc/x1; 
        double a = lam * lam + 1; 
        double b = -2 * u * lam * lam; 
        double c = lam * lam * u * u - v * v; 
        double delta = b * b - 4 * a * c; 
        if(delta >= -1e-9){
            double sqr; 
            if(delta >= 1e-9) sqr = sqrt(delta); 
            else sqr = 0; 
            double x11 = (-b + sqr) / (2 * a); 
            double x22 = (-b - sqr) / (2 * a); 
            double y1 = (-u + x11) * yc / x1; 
            double y2 = (-u + x22) * yc / x1; 
            if(y1 > 1e-9){
                add = min(add, yc / y1); 
            }
            if(y2 > 1e-9){
                add = min(add, yc / y2); 
            }
        }
    }
    if(abs(x2) < 1e-9){
        if(v * v - u * u > 1e-9){
            add = min(add, yc / (sqrt(v * v  - u * u))); 
        }
    }else{
        double lam = yc / x2; 
        double a = lam * lam + 1; 
        double b = -2 * u * lam * lam; 
        double c = lam * lam * u * u - v * v; 
        double delta = b * b - 4 * a * c; 
        if(delta >= -1e-9){
            double sqr; 
            if(delta >= 1e-9) sqr = sqrt(delta); 
            else sqr = 0; 
            double x11 = (-b + sqr) / (2 * a); 
            double x22 = (-b - sqr) / (2 * a); 
            double y1 = (-u + x11) * yc / x2; 
            double y2 = (-u + x22) * yc / x2; 
            if(y1 > 1e-9){
                add = min(add, yc / y1); 
            }
            if(y2 > 1e-9){
                add = min(add, yc / y2); 
            }
        }
    }
    cout << fixed << setprecision(7) << res + add << endl; 
}
signed main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);  cout.tie(nullptr); 
    int t; cin >> t; 
    while(t--) solve(); 
    return 0;    
}