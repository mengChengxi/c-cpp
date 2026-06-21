#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

using int64 = long long;
using u64 = unsigned long long;

struct Factor {
    int p;
    int e;
};

vector<int> primes;

void build_primes() {
    const int LIM = 4000;
    vector<bool> is_comp(LIM + 1, false);
    for (int i = 2; i <= LIM; ++i) {
        if (!is_comp[i]) {
            primes.push_back(i);
            if (1LL * i * i <= LIM) {
                for (int j = i * i; j <= LIM; j += i) is_comp[j] = true;
            }
        }
    }
}

vector<Factor> factorize(int x) {
    vector<Factor> fs;
    for (int p : primes) {
        if (1LL * p * p > x) break;
        if (x % p == 0) {
            int e = 0;
            while (x % p == 0) {
                x /= p;
                ++e;
            }
            fs.push_back({p, e});
        }
    }
    if (x > 1) fs.push_back({x, 1});
    return fs;
}

vector<int> divisors_from_factorization(const vector<Factor>& fs) {
    vector<int> divs{1};
    for (auto [p, e] : fs) {
        int old = (int)divs.size();
        int mul = 1;
        for (int i = 1; i <= e; ++i) {
            mul *= p;
            for (int j = 0; j < old; ++j) divs.push_back(divs[j] * mul);
        }
    }
    sort(divs.begin(), divs.end());
    return divs;
}

vector<int> residue_dp(int m, int limit, const vector<int>& divs) {
    const int INF = numeric_limits<int>::max() / 4;
    vector<int> dp(limit + 1, INF);
    dp[0] = 0;
    for (int d : divs) {
        if (d >= m || d > limit) break;
        for (int s = d; s <= limit; ++s) {
            int cand = dp[s - d] + 1;
            if (cand < dp[s]) dp[s] = cand;
        }
    }
    return dp;
}

int dfs_coin_change(int idx, int n, const vector<int>& coins,
                    unordered_map<u64, int>& memo) {
    if (n == 0) return 0;
    if (idx == 0) return n;

    u64 key = (u64)n << 10 | (u64)idx;
    auto it = memo.find(key);
    if (it != memo.end()) return it->second;

    int coin = coins[idx];
    int prev = coins[idx - 1];
    int best = numeric_limits<int>::max() / 4;

    for (int use = n / coin; use >= 0; --use) {
        int rem = n - use * coin;
        int lower_bound = use + (rem + prev - 1) / prev;
        if (lower_bound >= best) continue;

        int cand = use + dfs_coin_change(idx - 1, rem, coins, memo);
        if (cand < best) best = cand;
    }

    memo[key] = best;
    return best;
}

vector<int> sparse_dfs_answers(const vector<int>& coins, const vector<int>& residues) {
    unordered_map<u64, int> memo;
    memo.reserve(residues.size() * coins.size() * 16 + 1);

    vector<int> ans(residues.size());
    int last = (int)coins.size() - 1;
    for (int i = 0; i < (int)residues.size(); ++i) {
        ans[i] = dfs_coin_change(last, residues[i], coins, memo);
    }
    return ans;
}

void set_bit(vector<u64>& bits, int pos) {
    bits[pos >> 6] |= 1ULL << (pos & 63);
}

void clear_high_bits(vector<u64>& bits, int bit_count) {
    int rem = bit_count & 63;
    if (rem != 0) bits.back() &= (1ULL << rem) - 1;
}

int assign_hit_bits(vector<u64>& need, const vector<u64>& nxt, int level,
                    const vector<int>& residues, vector<int>& ans) {
    int found = 0;
    for (int i = 0; i < (int)need.size(); ++i) {
        u64 hit = need[i] & nxt[i];
        if (hit == 0) continue;
        need[i] &= ~hit;
        found += __builtin_popcountll(hit);
        while (hit) {
            int b = __builtin_ctzll(hit);
            int residue = (i << 6) + b;
            int id = lower_bound(residues.begin(), residues.end(), residue) - residues.begin();
            ans[id] = level;
            hit &= hit - 1;
        }
    }
    return found;
}

vector<int> bitset_bfs(int limit, const vector<int>& divs,
                       const vector<int>& residues) {
    int words = (limit + 64) >> 6;
    int bit_count = limit + 1;
    vector<u64> cur(words, 0), nxt(words, 0), need(words, 0);
    set_bit(cur, 0);
    for (int r : residues) set_bit(need, r);

    vector<int> usable;
    for (int d : divs) {
        if (d > limit) break;
        usable.push_back(d);
    }

    vector<int> ans(residues.size());

    int max_div = usable.empty() ? 0 : usable.back();
    int cur_max = 0;
    int remaining = (int)residues.size();
    for (int level = 1; remaining > 0; ++level) {
        fill(nxt.begin(), nxt.end(), 0);
        int active_words = min(words, (cur_max >> 6) + 1);
        for (int sh : usable) {
            int word_shift = sh >> 6;
            int bit_shift = sh & 63;
            int upto = min(active_words, words - word_shift);
            if (bit_shift == 0) {
                for (int i = 0; i < upto; ++i) {
                    u64 x = cur[i];
                    if (x) nxt[i + word_shift] |= x;
                }
            } else {
                for (int i = 0; i < upto; ++i) {
                    u64 x = cur[i];
                    if (!x) continue;
                    int j = i + word_shift;
                    nxt[j] |= x << bit_shift;
                    if (j + 1 < words) nxt[j + 1] |= x >> (64 - bit_shift);
                }
            }
        }
        clear_high_bits(nxt, bit_count);
        remaining -= assign_hit_bits(need, nxt, level, residues, ans);
        cur.swap(nxt);
        cur_max = min(limit, cur_max + max_div);
    }
    return ans;
}

bool try_large_prime_split(int m, const vector<Factor>& fs, const vector<int>& residues,
                           vector<int>& ans) {
    int p = -1;
    for (auto [prime, exp] : fs) {
        if (exp == 1) p = max(p, prime);
    }
    if (p == -1) return false;

    int a = m / p;
    long long work = 1LL * a * (int)residues.size();
    if (a > 5000 || work > 300000000LL) return false;

    vector<Factor> small_fs = factorize(a);
    vector<int> small_divs = divisors_from_factorization(small_fs);
    vector<int> small_dp = residue_dp(a, a - 1, small_divs);

    ans.assign(residues.size(), 0);
    for (int idx = 0; idx < (int)residues.size(); ++idx) {
        int r = residues[idx];
        int x = r / p;
        int best = numeric_limits<int>::max() / 4;
        for (int u = 0; u <= x; ++u) {
            int64 v = (int64)r - 1LL * p * u;
            int cand = small_dp[u] + (int)(v / a) + small_dp[v % a];
            if (cand < best) best = cand;
        }
        ans[idx] = best;
    }
    return true;
}

vector<int> solve_residues(int m, const vector<int>& residues) {
    vector<int> ans;
    if (residues.empty()) return ans;

    vector<Factor> fs = factorize(m);
    vector<int> divs = divisors_from_factorization(fs);

    if ((int)divs.size() == 2) {
        ans = residues;
        return ans;
    }

    if (try_large_prime_split(m, fs, residues, ans)) return ans;

    int limit = *max_element(residues.begin(), residues.end());
    int usable_cnt = 0;
    for (int d : divs) {
        if (d >= m || d > limit) break;
        ++usable_cnt;
    }

    long long dp_work = 1LL * usable_cnt * limit;
    vector<int> usable;
    usable.reserve(usable_cnt);
    for (int d : divs) {
        if (d >= m || d > limit) break;
        usable.push_back(d);
    }

    if ((int)residues.size() <= 1000 && dp_work > 50000000LL) {
        return sparse_dfs_answers(usable, residues);
    }

    if (usable_cnt <= 8 || dp_work <= 200000000LL) {
        vector<int> dp = residue_dp(m, limit, divs);
        ans.resize(residues.size());
        for (int i = 0; i < (int)residues.size(); ++i) ans[i] = dp[residues[i]];
        return ans;
    }

    return bitset_bfs(limit, divs, residues);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    build_primes();

    int T;
    cin >> T;
    while (T--) {
        int q, m;
        cin >> q >> m;

        vector<int64> base(q);
        vector<int> rem(q);
        vector<int> residues;
        residues.reserve(q);

        for (int i = 0; i < q; ++i) {
            int64 n;
            cin >> n;
            base[i] = n / m;
            rem[i] = n % m;
            if (rem[i] != 0) residues.push_back(rem[i]);
        }

        sort(residues.begin(), residues.end());
        residues.erase(unique(residues.begin(), residues.end()), residues.end());

        vector<int> add = solve_residues(m, residues);

        for (int i = 0; i < q; ++i) {
            int64 res = base[i];
            if (rem[i] != 0) {
                int id = lower_bound(residues.begin(), residues.end(), rem[i]) - residues.begin();
                res += add[id];
            }
            cout << res << (i + 1 == q ? '\n' : ' ');
        }
    }

    return 0;
}
