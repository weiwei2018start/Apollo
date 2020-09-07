/*
题目：最长递增子序列
题目描述： 给定数组arr，设长度为n，输出arr的最长递增子序列。（如果有多个答案，请输出其中字典序最小的）
 输入
 [2,1,5,3,6,4,8,9,7]
 输出
 [1,3,4,8,9]
 
 输入
 [1,2,8,6,4]
 输出
 [1,2,4]
 */

#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    vector<int> LIS(vector<int>& arr) {
        int size = arr.size();
        vector<int> dp(size);
        vector<int> pos(size);
        
        int index = 0;
        
        for (int i = 0; i < size; i++) {
            if (index == 0 || dp[index-1] < arr[i]) {
                pos[i] = index;
                dp[index] = arr[i];
                index++;
            } else {
                auto it = lower_bound(dp.begin(), dp.begin() + index, arr[i]);
                (*it) = arr[i];
                pos[i] = it - dp.begin();
            }
        }
        
        vector<int> ret(index, INT_MAX);
        vector<bool> visited(index+1, false);
        visited[index] = true;
        int val = index - 1;
        
        for (int i = size-1; i >= 0; i--) {
            if (pos[i] == val && visited[val + 1]) {
                ret[val] = min(ret[val], arr[i]);
                visited[val] = true;
                val--;
            }
        }
        
        return ret;
    }
};

int main() {
    int n = 5;
    int k = 3;
    vector<int> a;
    
    a.push_back(2);
    a.push_back(1);
    a.push_back(5);
    a.push_back(3);
    a.push_back(6);
    a.push_back(4);
    a.push_back(8);
    a.push_back(9);
    a.push_back(7);
    
    Solution A;
    vector<int> ret = A.LIS(a);
    
    for (int i = 0; i < ret.size(); i++) {
        cout << ret[i] << endl;
    }
    
    return 0;
}


