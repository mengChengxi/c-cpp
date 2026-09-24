#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Segment {
    int l, r;
};

void solve() {
    int n; 
    cin >> n;
    vector<Segment> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].l >> a[i].r;
    }

    // 第一步：按右端点升序排列
    sort(a.begin(), a.end(), [](const Segment& x, const Segment& y) {
        return x.r < y.r;
    });

    int rightmost = -1; // 记录上一个超级大区间的右边界
    bool has_prev = false;
    Segment prev_seg;
    int pairs = 0;

    for (int i = 0; i < n; i++) {
        // 条件1：当前线段必须合法（左端点 > rightmost）
        if (a[i].l > rightmost) {
            
            // 条件2：如果有上一个合法线段，且【它们相交】
            // 相交的数学判定：max(左1, 左2) <= min(右1, 右2)
            if (has_prev && max(prev_seg.l, a[i].l) <= min(prev_seg.r, a[i].r)) {
                pairs++;
                rightmost = a[i].r; // 因为排过序，当前的 a[i].r 就是最右端
                has_prev = false;   // 已经配对，清空 prev
            } 
            else {
                // 不相交，或者还没有 prev，就把当前合法线段作为新的 prev
                prev_seg = a[i];
                has_prev = true;
            }
        }
    }

    // 题目问的是最少删除多少个元素
    cout << n - 2 * pairs << "\n";
}

int main() {
    int t; 
    cin >> t;
    while (t--) solve();
    return 0;
}