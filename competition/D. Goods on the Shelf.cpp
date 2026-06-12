#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int check(vector<int> &check){
    unordered_map<int, int, custom_hash> safe_map;
    int prev=check[0];
    for(int i=1; i<check.size(); i++){
        if(check[i]!=prev){
            if(safe_map.count(check[i])!=0){
                return 0;
            }
            safe_map[prev]=1;
            prev=check[i];
        }
    }
    return 1;
}
void swapn(vector<int> &check, int i, int j){
    swap(check[i], check[j]);

}

void solve() {
    int n;
    cin>>n;
    vector<int> nums(n);
    for(int i=0; i<n; i++){
        cin>>nums[i];
    }

    int wrongi=-1;
    int wrong=-1;


    unordered_map<int, int, custom_hash> safe_map;
    int prev=nums[0];
    for(int i=1; i<nums.size(); i++){
        if(nums[i]!=prev){
            if(safe_map.count(nums[i])!=0){
                wrongi=i;
                wrong=nums[i];
                break;
            }
            safe_map[prev]=i;
            prev=nums[i];
        }
    }

    if(wrong==-1){
        cout<<"YES"<<endl;
        return;
    }

    int end=safe_map[wrong];
    int start=-1;
    for(int i=end-1;  i>=0; i--){
        if(nums[i]==wrong){

        }else{
            start=i;
            break;
        }
    }

    int wrongstart=wrongi-1;
    int wrongend=n;

    for(int i=wrongi; i<n; i++){
        if(nums[i]!=wrong){
            wrongend=i;
            break;
        }
    }


    //  _**_  _***_ 
    if(true){



        //swap both
        if(true){
            vector<int> newnums=nums;
            swapn(newnums, start+1,wrongstart);
            if(check(newnums)==1){
                cout<<"YES"<<endl;
                return;
            }
        }
        
        if(wrongend<n){
            vector<int> newnums=nums;
            swapn(newnums, start+1,wrongend);
            if(check(newnums)==1){
                cout<<"YES"<<endl;
                return;
            }
        }

        if(true){
            vector<int> newnums=nums;
            swapn(newnums, end-1,wrongstart);
            if(check(newnums)==1){
                cout<<"YES"<<endl;
                return;
            }
        }
        
        if(wrongend<n){
            vector<int> newnums=nums;
            swapn(newnums, end-1,wrongend);
            if(check(newnums)==1){
                cout<<"YES"<<endl;
                return;
            }
        }

        if(start>=0){
            vector<int> newnums=nums;
            swapn(newnums, wrongend-1,start);
            if(check(newnums)==1){
                cout<<"YES"<<endl;
                return;
            }
        }


        if(end==wrongstart){
            for(int i=wrongend; i<n; i++){
                if(nums[i]==wrong){
                    vector<int> newnums=nums;
                    swapn(newnums, i,end);
                    if(check(newnums)==1){
                        cout<<"YES"<<endl;
                        return;
                    }
                    break;
                }

            }
        }
        if(start>=0){
            vector<int> newnums=nums;
            swapn(newnums, wrongstart+1,start);
            if(check(newnums)==1){
                cout<<"YES"<<endl;
                return;
            }
        }

        if(true){
            vector<int> newnums=nums;
            swapn(newnums, wrongend-1,end);
            if(check(newnums)==1){
                cout<<"YES"<<endl;
                return;
            }
        }

        if(true){
            vector<int> newnums=nums;
            swapn(newnums, wrongstart+1,end);
            if(check(newnums)==1){
                cout<<"YES"<<endl;
                return;
            }
        }


    }
    cout<<"NO"<<endl;

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