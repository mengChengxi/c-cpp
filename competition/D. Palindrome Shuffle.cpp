#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    string s;
    cin>>s;
   

    int start=-1;
    for( int i=0; i<s.size(); i++){
        if(s[i]==s[s.size()-1-i]){

        }else{
            start=i;
            break;
        }
    }
    if(start==-1){
        cout<<0<<endl;
        return;
    }

    vector<int> occurence(26,0);
    for(int i=start;i<s.size()-start; i++){
        occurence[s[i]-'a']++;
    }
    int count=0;
    for(int i=0;i<26;i++){
        if(occurence[i]!=0){
            count++;
        }
    }
    int count2=count;
    int end=0;
    vector<int> temoccurence(26,0);
    for(int i=start;i<s.size()-start; i++){
        
        temoccurence[s[i]-'a']++;
        if(temoccurence[s[i]-'a']==occurence[s[i]-'a']/2){
            count--;
        }
        if(count==0){
            end=i;
            break;
        }
    }


    int minn=INF;
    
    if(end==s.size()/2-1){
        int save=0;
        for(int i=0; i<end-start+1; i++){
            if(s[end-i]==s[end+1+i]){
                save++;
            }else{
                break;
            }
        }
        minn=min(minn,end-start+1-save);

    }else{
        minn=min(minn,end-start+1);
    }
   
    count=count2;
    vector<int> tem2occurence(26,0);
    for(int i=s.size()-start-1;i>=start; i--){
        
        tem2occurence[s[i]-'a']++;
        if(tem2occurence[s[i]-'a']==occurence[s[i]-'a']/2){
            count--;
        }
        if(count==0){
            end=i;
            break;
        }
    }
    if(end==s.size()/2){
        int save=0;
        for(int i=0; i<end-start; i++){
            if(s[end+i]==s[end-1-i]){
                save++;
            }else{
                break;
            }
        }
        minn=min(minn,(int)s.size()-start-1-end+1-save);

    }else{
        minn=min(minn,(int)s.size()-start-1-end+1);
    }


    cout<<minn<<endl;


    

    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int dashabi;
    cin >> dashabi;
    while (dashabi--) {
        solve();
    }
    return 0;
}