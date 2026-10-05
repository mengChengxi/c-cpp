#include <bits/stdc++.h>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

vector<int> cost;
vector<int> pre;
vector<vector<int>> tree;
vector<pair<int, int>> edges;
vector<int> cirle;
vector<pair<int, int>> newedges;
bool found=false;
vector<int> belong;
int currentassign=1;

void dfs(int node, int parent){
    pre[node]=parent;
    for(int i=0; i<tree[node].size(); i++){
        if(found==true){
            return;
        }

        if(tree[node][i]==parent){
            continue;
        }
        if(pre[tree[node][i]]!=-1){
            found=true;
            int current=node;
            while(current!=tree[node][i]){
                cirle.push_back(current);
                current=pre[current];
            }
            cirle.push_back(tree[node][i]);
            return;
        }
        dfs(tree[node][i],node);
    }

}

void dfs2(int node, int parent){
    belong[node]=currentassign;
    for(int i=0; i<tree[node].size(); i++){
        if(tree[node][i]==parent){
            continue;
        }
        dfs2(tree[node][i],  node);

    }
}
void solve() {
    int n,k;
    cin>>n>>k;
    
    vector<int> tcost(n+1);
    vector<int> tpre(n+1,-1);
    
    tpre[1]=0;
    pre=tpre;
    cost=tcost;

    for(int i=1; i<n+1; i++){
        cin>>cost[i];
    }
    vector<vector<int>> ttree(n+1);
    tree=ttree;
    vector<pair<int, int>> tedges(n);
    edges=tedges;

    for(int i=0; i<n; i++){
        int a,b;
        cin>>a>>b;
        edges[i]={a,b};
    }
    for(int i=0; i<n; i++){
        int a=edges[i].first;int b=edges[i].second;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    dfs(1,0);

    vector<pair<int, int>> tnewedges;
    newedges=tnewedges;

    unordered_map<int,int> mp;
    for(int i=0; i<cirle.size(); i++){
        mp[cirle[i]]++;
    }
    for(int i=0; i<n; i++){
        int a=edges[i].first;
        int b=edges[i].second;
        if(mp.count(a)==0||mp.count(b)==0){
            newedges.push_back({a,b});
        }
    }
    vector<vector<int>> tttree(n+1);
    tree=tttree;
    for(int i=0; i<newedges.size(); i++){
        int a=newedges[i].first;int b=newedges[i].second;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    vector<int> tbelong(n+1);
    belong=tbelong;

    for(int i=1; i<n+1; i++){
        if(tbelong[i]==0){
            currentassign=i;
            dfs2(i,0);
        }
    }

    unordered_map<int, vector<int>> newmp;
    for(int i=1; i<n+1; i++){
        newmp[cost[i]].push_back(i);
    }
    
    unordered_map<int, int> total_count;
    vector<unordered_map<int, int>> comp_count(n + 1); 
    
    for(int i = 1; i <= n; i++) {
        total_count[cost[i]]++;
        comp_count[belong[i]][cost[i]]++;
    }

    long long count = 0;
    
    for(int i = 1; i <= n; i++) {
        int target = cost[i] - k;
        
        if (total_count.count(target)) {
            long long total_targets = total_count[target];
            long long same_comp_targets = comp_count[belong[i]][target];
            
            count += (2LL * total_targets) - same_comp_targets;
        }
    }

    cout << count << "\n";

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
  
    solve();
    
    return 0;
}



// ================= 1. 精度控制 =================
const double eps = 1e-8; // 若用 long double，可改为 1e-12
int sgn(double x) {
    if (fabs(x) < eps) return 0;
    if (x < 0) return -1;
    return 1;
}

// ================= 2. 点与向量的封装 =================
struct Point {
    double x, y;
    Point(double _x = 0, double _y = 0) : x(_x), y(_y) {}
    Point operator + (const Point &b) const { return Point(x + b.x, y + b.y); }
    Point operator - (const Point &b) const { return Point(x - b.x, y - b.y); }
    Point operator * (const double &k) const { return Point(x * k, y * k); }
    Point operator / (const double &k) const { return Point(x / k, y / k); }
    bool operator == (const Point &b) const {
        return sgn(x - b.x) == 0 && sgn(y - b.y) == 0;
    }
};
typedef Point Vector;

// ================= 3. 核心运算 =================
double dot(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

// 如果 sgn(cross(A, B)) > 0 ：说明 $\vec{B}$ 在 $\vec{A}$ 的逆时针方向。
// 如果 sgn(cross(A, B)) < 0 ：说明 $\vec{B}$ 在 $\vec{A}$ 的顺时针方向。
// 如果 sgn(cross(A, B)) == 0 ：说明 $\vec{A}$ 和 $\vec{B}$ 共线（可能同向也可能反向）。
double cross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

double length(Vector a) {
    return sqrt(dot(a, a));
}
double dist(Point a, Point b) {
    return length(a - b);
}

// ================= 4. 极角排序 (跨立实验法) =================
// 判断向量是否在极轴的上方 (y > 0，或在极轴正半轴上)
bool isUp(Vector a) {
    return sgn(a.y) > 0 || (sgn(a.y) == 0 && sgn(a.x) >= 0);
}

// 极角排序 cmp 函数 (逆时针排序)
// 使用方法: sort(points.begin(), points.end(), polarCmp);
bool polarCmp(Point a, Point b) {
    bool upA = isUp(a), upB = isUp(b);
    if (upA != upB) return upA > upB; // 上半平面优先排在下半平面之前
    return sgn(cross(a, b)) > 0;      // 同半平面内，利用叉积按逆时针排序
}

// ================= 5. 线与线段的封装 =================
struct Line {
    Point s, e;
    Line() {}
    Line(Point _s, Point _e) : s(_s), e(_e) {}
};

// ================= 6. 线段相交判定 (核心) =================
// 快速排斥实验：判断两线段的包围盒是否相交
bool quickReject(Point a, Point b, Point c, Point d) {
    return max(a.x, b.x) >= min(c.x, d.x) &&
           max(c.x, d.x) >= min(a.x, b.x) &&
           max(a.y, b.y) >= min(c.y, d.y) &&
           max(c.y, d.y) >= min(a.y, b.y);
}

// 跨立实验：判断线段 ab 和 cd 是否相交 (包含端点相交的非规范相交)
bool segmentIntersection(Point a, Point b, Point c, Point d) {
    // 1. 快速排斥
    if (!quickReject(a, b, c, d)) return false;
    // 2. 跨立实验
    int c1 = sgn(cross(b - a, c - a));
    int c2 = sgn(cross(b - a, d - a));
    int c3 = sgn(cross(d - c, a - c));
    int c4 = sgn(cross(d - c, b - c));
    // 互相跨立才算相交 (一正一负相乘 <= 0)
    return c1 * c2 <= 0 && c3 * c4 <= 0; 
}

// ================= 7. 直线交点 =================
// 注意：调用前需保证两直线不平行 ( sgn(cross(l1.e - l1.s, l2.e - l2.s)) != 0 )
// 原理：利用叉积求出面积比，进而得到线段长度比
Point lineIntersection(Line l1, Line l2) {
    Vector u = l1.s - l2.s;
    Vector v = l1.e - l1.s;
    Vector w = l2.e - l2.s;
    double t = cross(w, u) / cross(v, w);
    return l1.s + v * t;
}

// ================= 8. 点到线的最短距离 =================
// 点 p 到直线 ab 的距离 (平行四边形面积 / 底边长)
double distToLine(Point p, Point a, Point b) {
    return fabs(cross(b - a, p - a)) / dist(a, b);
}

// 点 p 到线段 ab 的距离
double distToSegment(Point p, Point a, Point b) {
    if (a == b) return dist(p, a); // 退化为点
    Vector v1 = b - a, v2 = p - a, v3 = p - b;
    // 运用点积判断垂足位置
    if (sgn(dot(v1, v2)) < 0) return length(v2); // 钝角，p在a点外侧
    if (sgn(dot(v1, v3)) > 0) return length(v3); // 钝角，p在b点外侧
    return distToLine(p, a, b);                  // 锐角，投影在线段上
}

#include <vector>

// ================= 9. 多边形面积 =================
// 给定多边形顶点数组 (顺时针或逆时针均可)，计算面积
double polygonArea(const vector<Point>& poly) {
    double area = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        area += cross(poly[i], poly[(i + 1) % n]);
    }
    return fabs(area) / 2.0;
}

// ================= 10. 点在多边形内判定 =================
// 返回值: 0 表示在多边形外, 1 表示在多边形内, 2 表示在多边形边界上
// 算法: 射线法 (结合半开半闭区间，完美处理射线穿过顶点的情况)
int isPointInPolygon(Point p, const vector<Point>& poly) {
    int wn = 0; // 回转数
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        Point a = poly[i];
        Point b = poly[(i + 1) % n];
        
        // 1. 判断点是否在当前边上 (叉积为0说明共线，点积<=0说明在两端点之间或重合)
        if (sgn(cross(a - p, b - p)) == 0 && sgn(dot(a - p, b - p)) <= 0) {
            return 2; // 在边界上
        }
        
        // 2. 射线法核心逻辑
        int k = sgn(cross(b - a, p - a)); // 判断 P 在有向边 AB 的左右侧
        int d1 = sgn(a.y - p.y);
        int d2 = sgn(b.y - p.y);
        
        // 边从下往上跨过射线 (包含下端点，不包含上端点)
        if (k > 0 && d1 <= 0 && d2 > 0) wn++;
        // 边从上往下跨过射线
        if (k < 0 && d2 <= 0 && d1 > 0) wn--;
    }
    
    if (wn != 0) return 1; // 内部
    return 0; // 外部
}
#include <vector>
#include <algorithm>

// ================= 11. 凸包 (Convex Hull) =================
// Andrew 算法求凸包，时间复杂度 O(N log N)

// 排序规则：先按 X 排序，X 相同按 Y 排序
bool cmpXY(const Point& a, const Point& b) {
    if (sgn(a.x - b.x) != 0) return a.x < b.x;
    return a.y < b.y;
}

// 求凸包函数
// 输入点集 pts，返回凸包上的顶点集 (按逆时针顺序排序)
vector<Point> convexHull(vector<Point>& pts) {
    int n = pts.size();
    if (n <= 2) return pts; // 点数不足，直接返回
    
    sort(pts.begin(), pts.end(), cmpXY);
    
    vector<Point> hull; // 用于模拟栈
    
    // 1. 维护下凸壳
    for (int i = 0; i < n; i++) {
        // 如果栈内点数 >= 2，且新加入的点会使边界向右拐或共线 ( <= 0 )
        // 则说明栈顶的点内凹了，需要弹栈出局
        while (hull.size() >= 2 && 
               sgn(cross(hull.back() - hull[hull.size()-2], pts[i] - hull[hull.size()-2])) <= 0) {
            hull.pop_back();
        }
        hull.push_back(pts[i]);
    }
    
    int lower_size = hull.size();
    
    // 2. 维护上凸壳 (倒序遍历)
    for (int i = n - 2; i >= 0; i--) {
        // 注意栈的底线是 lower_size，不能把下凸壳的点弹空了
        while (hull.size() > lower_size && 
               sgn(cross(hull.back() - hull[hull.size()-2], pts[i] - hull[hull.size()-2])) <= 0) {
            hull.pop_back();
        }
        hull.push_back(pts[i]);
    }
    
    // 3. 上下凸壳的首尾在起点处重复了一次，删去
    hull.pop_back();
    
    return hull;
}


// ================= 12. 旋转卡壳 (最远点对/凸包直径) =================
// 依赖: 必须先求出凸包，传入的 hull 是按逆时针排列的凸包顶点
// 返回值: 点集中的最远两点距离的平方 (为防精度丢失，通常不直接开根号)
double rotatingCalipers(const vector<Point>& hull) {
    int n = hull.size();
    if (n == 2) {
        return dist(hull[0], hull[1]) * dist(hull[0], hull[1]);
    }
    
    double max_dist_sq = 0;
    int j = 2; // 最远点指针初始化
    
    // 遍历凸包的每一条边 i -> i+1
    for (int i = 0; i < n; i++) {
        // 取当前边
        Point a = hull[i];
        Point b = hull[(i + 1) % n];
        
        // 如果 j 往前走一步 (j+1) 构成的三角形面积 > 当前 j 构成的面积
        // 面积比较等价于比较叉积: cross(b-a, j-a)
        while (sgn(cross(b - a, hull[(j + 1) % n] - a) - 
                   cross(b - a, hull[j] - a)) > 0) {
            j = (j + 1) % n; // j 指针逆时针往前走
        }
        
        // j 停下时，说明 j 是离边 ab 最远的点
        // 此时最远点对可能产生于 (a, j) 或 (b, j)
        double d1 = dot(hull[j] - a, hull[j] - a); // a和j的距离平方
        double d2 = dot(hull[j] - b, hull[j] - b); // b和j的距离平方
        
        max_dist_sq = max(max_dist_sq, max(d1, d2));
    }
    
    return max_dist_sq;
}



