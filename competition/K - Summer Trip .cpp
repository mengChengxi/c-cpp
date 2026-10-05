#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    string s;
    cin>>s;

    vector<int> alphabets(26,-1);

    long long count=0;
    for(int i=0; i<s.size(); i++){
        int in=s[i]-'a';
        for(int j=0; j<26; j++){
            if(j==in){
                continue;
            }
            if(alphabets[in]<alphabets[j]){
                count++;
            }
        }
        alphabets[in]=i;
    }

    cout<<count<<endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

        solve();
    
    return 0;
}