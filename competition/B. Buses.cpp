#include <bits/stdc++.h>
#include <utility>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int busnumber, peoplenumber, road;
    double busspped, peoplespeed;
    cin>>busnumber>>peoplenumber>>road>>busspped>>peoplespeed;

    vector<pair<int, int>> buses(busnumber);

    for(int i=0; i<busnumber; i++){
        cin>>buses[i].first;
        cin>>buses[i].second;
    }
    vector<pair<int,int>> peoples(peoplenumber);

    for(int i=0; i<peoplenumber; i++){
        cin>>peoples[i].first;
        peoples[i].second=i;
    }

    sort(buses.begin(),buses.end());
    sort(peoples.begin(),peoples.end());

    vector<int> bestbusforeachperson(peoplenumber);

    int nextbus=0;
    int bestbus=-1;
    double bestbusvalue=-100;    
   // 修复 Bug 2 和 Bug 4：先判断 nextbus < busnumber，且改为 <=
    for(int i = 0; i < peoplenumber; i++){
        for(; nextbus < busnumber && buses[nextbus].first <= peoples[i].first; nextbus++){
            // 提醒：如果题目没有保证公交车一定比人走得快 (x > y)，这里可能除以 0 或负数，
            // 稳妥起见可以加一个 if (busspped > peoplespeed) 的特判。
            double value = buses[nextbus].second + buses[nextbus].first * (peoplespeed / (busspped - peoplespeed));
            if(value > bestbusvalue){
                bestbusvalue = value;
                bestbus = nextbus;
            }
        }
        bestbusforeachperson[i] = bestbus;
    }   

    vector<double> output(peoplenumber);

    for(int i = 0; i < peoplenumber; i++){
        double buslength = 0;
        int best = bestbusforeachperson[i];
        
        // 修复 Bug 3：判断是否有有效的公交车，避免访问 buses[-1]
        if (best != -1) {
            buslength = buses[best].second - peoples[i].first -
                        (peoples[i].first - buses[best].first) / (busspped - peoplespeed) * peoplespeed;

            if(buslength <= 0){
                buslength = 0;
            }
        }

        // 修复 Bug 1：步行距离必须减去人的初始位置
        double time = buslength / busspped + (road - peoples[i].first - buslength) / peoplespeed;

        output[peoples[i].second] = time;
    }

    for(int i = 0; i < peoplenumber; i++){
        cout << fixed << setprecision(10) << output[i] << "\n";
    }



}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

 
        solve();
    
    return 0;
}