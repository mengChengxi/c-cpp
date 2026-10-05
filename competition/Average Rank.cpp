#include <bits/stdc++.h>
#include <iomanip>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,w;

    cin>>n>>w;
    vector<int> score(n+1,0);
    vector<long long> rank(w+5,1);
    rank[0]=1;
    vector<int> lastchangeranktime(w+5,1);
    vector<long long> accumrank(w+5,0);

    vector<long long> sumrank(n+1,0);
    vector<long long> accumrankwhenadded(n+1,0);

    for(int week=1; week<=w; week++){
        int k;
        cin>>k;
        for(int people=0; people<k; people++){
            int p;

            cin>>p;
            
            accumrank[score[p]]+=((week-lastchangeranktime[score[p]])*rank[score[p]]);
            rank[score[p]]++;
            lastchangeranktime[score[p]]=week;

            sumrank[p]+=(accumrank[score[p]]-accumrankwhenadded[p]);

            score[p]++;

            accumrank[score[p]] += (long long)(week - lastchangeranktime[score[p]]) * rank[score[p]];
            lastchangeranktime[score[p]] = week;

            accumrankwhenadded[p]=accumrank[score[p]];
        }  
    }
    for(int score=0; score<=w; score++){
        accumrank[score]+=((w+1-lastchangeranktime[score])*rank[score]);
    }
    
    for(int people=1; people<=n; people++){
        sumrank[people]+=(accumrank[score[people]]-accumrankwhenadded[people]);
    }
    for(int people=1; people<=n; people++){
        cout<<fixed<<setprecision(6)<<(double)sumrank[people]/w<<endl;
    }

    
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
   
        solve();
    
    return 0;
}