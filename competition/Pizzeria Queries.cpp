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
    long long left_max_val = 1e18; 
    long long right_max_val = 1e18;// 极小值
    int right_index=-404;
    int left_index=-404;
    long long len = 0;         // 区间长度（用于区间加法求和）
    

    // 默认构造
    Info() {}
    // 单点初始化的构造
    Info(long long val,int i) : right_max_val(val+i), left_max_val(val-i),len(1),right_index(i),left_index(i) {}

    // 2. 信息的合并：即 push_up 的本质
    // 定义两个子节点合并成父节点时的逻辑
    friend Info operator+(const Info& a, const Info& b) {
        Info c;
        if(a.left_max_val<b.left_max_val){
            c.left_max_val =a.left_max_val;
            c.left_index=a.left_index;
        }else{
            c.left_max_val =b.left_max_val;
            c.left_index=b.left_index;
        }

        if(a.right_max_val<b.right_max_val){
            c.right_max_val =a.right_max_val;
            c.right_index=a.right_index;
        }else{
            c.right_max_val =b.right_max_val;
            c.right_index=b.right_index;
        }
      
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
    info.left_max_val += tag.add;        // 区间最大值直接增加 tag
    info.right_max_val += tag.add;
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
        init_info[i] = Info(arr[i],i);
    }

    // 实例化泛型线段树
    LazySegmentTree<Info, Tag> st(init_info);

    // 对区间 [1, 3] 增加 2
    st.modify(1, 3, Tag{2}); // 数组变为 {1, 7, 5, 6, 2}


    return 0;
}

// 示例 2: kth 查找功能演示


void solve() {
    int n,q;
    cin>>n>>q;
    
    vector<int> nums(n);

    for(int i=0; i<n; i++){
        cin>>nums[i];
    }
    vector<Info> init_info(nums.size());
    for (size_t i = 0; i < nums.size(); ++i) {
        init_info[i] = Info(nums[i],i);
    }

    LazySegmentTree<Info, Tag> st(init_info);

    while(q--){
        int type;
        cin>>type;
        if(type==1){
            int k,x;
            cin>>k>>x;

            k--;
            int old=st.query(k, k).left_max_val+k;
            st.modify(k, k, Tag{x-old});

        }else {
            int k;
            cin>>k;
            k--;
                cout<<min(st.query(k, n-1).right_max_val-k,st.query(0, k).left_max_val+k)<<"\n";
            
          
        }
    }




}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
   
        solve();
    
    return 0;
}