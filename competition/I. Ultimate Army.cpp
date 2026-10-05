#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;
    vector<int> boss(n+1);
    vector<int> scoredoninator(2*n+4);
    string s;
    cin>>s;

    int prev=0;

    int score=2;

    for(int i=0; i<s.size(); i++){

        if(s[i]=='('){
            score++;
            if(s[i-1]!=')'){
                scoredoninator[score]=prev;
            }
            
        }else if (s[i]==')'){
            score--;

        }else{
            
            // 1. Parse full multi-digit number
            prev = 0;
            while (i < s.size() && isdigit(s[i])) {
                prev = prev * 10 + (s[i] - '0');
                i++;
            }
            i--;
            //prev=s[i]-'0';
            boss[prev]=scoredoninator[score];
        }
    }

    for(int i=1; i<=n; i++){
        cout<<boss[i]<<" ";
    }
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
   
        solve();
    
    return 0;
}