#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair
// ==============================================================================
// 业务逻辑区：换题时只需要修改这里的结构体和函数
// ==============================================================================

// 1. 定义节点信息 (Info)
// 这里我们同时维护“区间和”、“区间最大值”以及“区间长度”
struct Info {
    long long sum = 0;
    long long max_val = -1e18; // 极小值
    long long len = 0;         // 区间长度（用于区间加法求和）

    // 默认构造
    Info() {}
    // 单点初始化的构造
    Info(long long val) : sum(val), max_val(val), len(1) {}

    // 2. 信息的合并：即 push_up 的本质
    // 定义两个子节点合并成父节点时的逻辑
    friend Info operator+(const Info& a, const Info& b) {
        Info c;
        c.sum = a.sum + b.sum;
        c.max_val = max(a.max_val, b.max_val);
        c.len = a.len + b.len;
        return c;
    }
};

// 3. 定义懒惰标记 (Tag)
struct Tag {
    long long add = 0;
    
    // 判断当前节点是否有标记需要下放
    bool has_tag() const {
        return add != 0;
    }
    
    // 清空标记
    void clear() {
        add = 0;
    }
};

// 4. 定义标记的作用逻辑 (Apply)
// 逻辑 A: 一个 Tag 作用到一个 Info 上，Info 会怎么变化？
void apply(Info& info, const Tag& tag) {
    if (!tag.has_tag()) return;
    info.sum += tag.add * info.len; // 区间和增加 tag * 长度
    info.max_val += tag.add;        // 区间最大值直接增加 tag
}

// 逻辑 B: 一个新的 Tag 作用到一个旧的 Tag 上（标记叠加），Tag 会怎么变化？
void apply(Tag& old_tag, const Tag& new_tag) {
    old_tag.add += new_tag.add;
}


// ==============================================================================
// 核心框架区：写好一次，永远不用修改的代码（可以直接折叠）
// ==============================================================================

template<class Info, class Tag>
class LazySegmentTree {
private:
    int n;
    vector<Info> info;
    vector<Tag> tag;

    void push_up(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    }

    void apply_node(int p, const Tag& v) {
        apply(info[p], v); 
        apply(tag[p], v);  
    }

    void push_down(int p) {
        if (tag[p].has_tag()) {
            apply_node(2 * p, tag[p]);
            apply_node(2 * p + 1, tag[p]);
            tag[p].clear();
        }
    }

    void build(int p, int l, int r, const vector<Info>& init_info) {
        if (l == r) {
            info[p] = init_info[l];
            return;
        }
        int m = (l + r) / 2;
        build(2 * p, l, m, init_info);
        build(2 * p + 1, m + 1, r, init_info);
        push_up(p);
    }

    void modify(int p, int l, int r, int ql, int qr, const Tag& v) {
        if (ql <= l && r <= qr) {
            apply_node(p, v);
            return;
        }
        push_down(p);
        int m = (l + r) / 2;
        if (ql <= m) modify(2 * p, l, m, ql, qr, v);
        if (qr > m) modify(2 * p + 1, m + 1, r, ql, qr, v);
        push_up(p);
    }

    Info query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return info[p];
        }
        push_down(p);
        int m = (l + r) / 2;
        if (qr <= m) return query(2 * p, l, m, ql, qr);
        if (ql > m) return query(2 * p + 1, m + 1, r, ql, qr);
        return query(2 * p, l, m, ql, qr) + query(2 * p + 1, m + 1, r, ql, qr);
    }

    int kth(int p, int l, int r, long long k) {
        if (l == r) {
            return l;
        }

        push_down(p);

        int m = (l + r) / 2;
        long long left_count = info[2 * p].sum;

        if (k <= left_count) {
            return kth(2 * p, l, m, k);
        } else {
            return kth(2 * p + 1, m + 1, r, k - left_count);
        }
    }

public:
    LazySegmentTree(const vector<Info>& init_info) {
        n = init_info.size();
        info.assign(4 * n, Info());
        tag.assign(4 * n, Tag());
        if (n > 0) build(1, 0, n - 1, init_info);
    }

    void modify(int l, int r, const Tag& v) {
        if (l <= r) modify(1, 0, n - 1, l, r, v);
    }

    Info query(int l, int r) {
        if (l <= r) return query(1, 0, n - 1, l, r);
        return Info();
    }

    // 找到当前第 k 个还存在的元素，返回原数组下标
    // 【注意】使用此功能前提：线段树初始化的数组元素只能是 1（代表存在）或 0（代表不存在/已删除），
    // 并且 Info 中的 sum 代表区间内元素的数量总和。
    int kth(long long k) {
        if (k < 1 || k > info[1].sum) return -1; // 越界保护
        return kth(1, 0, n - 1, k);
    }
};

// ==============================================================================
// 示例用法
// ==============================================================================

// 示例 1: 基础区间操作演示
int sample_basic() {
    // 初始数组 {1, 5, 3, 4, 2}
    vector<long long> arr = {1, 5, 3, 4, 2};
    
    // 将普通数组转化为 Info 结构体数组
    vector<Info> init_info(arr.size());
    for (size_t i = 0; i < arr.size(); ++i) {
        init_info[i] = Info(arr[i]);
    }

    // 实例化泛型线段树
    LazySegmentTree<Info, Tag> st(init_info);

    // 查询初始区间 [1, 3] 
    Info res1 = st.query(1, 3);
    cout << "初始区间 [1, 3] 的最大值: " << res1.max_val << endl; // 输出 5
    cout << "初始区间 [1, 3] 的总和: " << res1.sum << endl;       // 输出 12

    // 对区间 [1, 3] 增加 2
    st.modify(1, 3, Tag{2}); // 数组变为 {1, 7, 5, 6, 2}

    // 查询修改后的区间 [1, 3]
    Info res2 = st.query(1, 3);
    cout << "修改后区间 [1, 3] 的最大值: " << res2.max_val << endl; // 输出 7
    cout << "修改后区间 [1, 3] 的总和: " << res2.sum << endl;       // 输出 18

    return 0;
}

// 示例 2: kth 查找功能演示
int sample_kth() {
    // 初始数组 {1, 1, 0, 1, 1} (1代表元素存在，0代表不存在)
    vector<long long> arr = {1, 1, 0, 1, 1};
    
    // 将普通数组转化为 Info 结构体数组
    vector<Info> init_info(arr.size());
    for (size_t i = 0; i < arr.size(); ++i) {
        init_info[i] = Info(arr[i]);
    }

    // 实例化泛型线段树
    LazySegmentTree<Info, Tag> st(init_info);

    // 查询初始状态下第 3 个存在的元素
    int idx1 = st.kth(3);
    cout << "初始状态下，第 3 个存在的元素下标: " << idx1 << endl; // 输出 3 (对应第四个位置的1)

    // 删除下标为 1 的元素 (将它的值减1，变为0)
    st.modify(1, 1, Tag{-1}); // 数组变为 {1, 0, 0, 1, 1}

    // 查询修改后第 3 个存在的元素
    int idx2 = st.kth(3);
    cout << "修改后，第 3 个存在的元素下标: " << idx2 << endl; // 输出 4 (对应第五个位置的1)

    return 0;
}

void solve() {
    int n;
    cin>>n;
    vector<long long> skill(n+1);
    vector<int> order(n+1);

    for(int i=1; i<=n; i++) {
        cin>>skill[i];
    }
    for(int i=1; i <=n; i++) {
        cin>>order[i];
    }

    
    vector<Info> init_info(n+1,Info(0));
    LazySegmentTree<Info,Tag> st(init_info);


    set<int> active;    
    set<int> forfeits;  


    vector<int> ans(n);

    for (int i=n; i>=1; i--) {

        int idx=order[i];
        long long val=skill[idx];
        
        active.insert(idx);
        st.modify(idx, idx, Tag{val}); 
        


        bool is_first= (idx==*active.begin());
        int start; 

        
        if(is_first){
            if(active.size()>1) {
                int nxt=*next(active.begin());

                if(val<skill[nxt]) {
                    forfeits.insert(nxt);
                }
            }
            start=idx;


        }else{
            auto it=forfeits.lower_bound(idx);
            int L=(it != forfeits.begin()) ? *prev(it) : *active.begin();
            
            if (st.query(L, idx-1).sum<val) {
                forfeits.insert(idx);
            }

            start=forfeits.count(idx) ? idx:L;
        }
        
        auto it=forfeits.upper_bound(idx);

        while( it!=forfeits.end()){
            int R=*it;
            
            if(st.query(start, R-1).sum>=skill[R]) {
                it=forfeits.erase(it); 
            }else{
                break; 
            }
        }
        
        ans[i-1]=forfeits.size();
    }

    for (int i = 0; i < n; ++i) {
        cout<<ans[i]<<" ";
    }

    cout<<endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int dashabi;
    if (cin >> dashabi) {
        while (dashabi--) {
            solve();
        }
    }
    return 0;
}