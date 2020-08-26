/*
题目地址：https://www.nowcoder.com/practice/e3769a5f49894d49b871c09cadd13a61?tpId=188&&tqId=35167&rp=1&ru=/activity/oj&qru=/ta/job-code-high-week/question-ranking
题目描述
设计LRU缓存结构，该结构在构造时确定大小，假设大小为K，并有如下两个功能
set(key, value)：将记录(key, value)插入该结构
get(key)：返回key对应的value值
[要求]
set和get方法的时间复杂度为O(1)
某个key的set或get操作一旦发生，认为这个key的记录成了最常使用的。
当缓存的大小超过K时，移除最不经常使用的记录，即set或get最久远的。
若opt=1，接下来两个整数x, y，表示set(x, y)
若opt=2，接下来一个整数x，表示get(x)，若x未出现过或已被移除，则返回-1
对于每个操作2，输出一个答案
*/

class Solution {
private:
    list<pair<int,int>> plist;
    unordered_map<int, list<pair<int, int>::iterator>> umap;
    int capcity;
    
    void set(int key, int value) {
        auto it = umap.find(key);
        if (it != umap.end()) {
            plist.erase(umap[key])
            plist.push_front({key, value});
            umap[key] = plist.begin();
        } else {
            if (capcity == plist.size()) {
                umap.erase(plist.back().first);
                plist.pop_back();
            }
            plist.push_front({key, value});
            umap[key] = plist.begin();
        }
    }
    
    int get(int key) {
        auto it = umap.find(key);
        if (it != umap.end()) {
            plist.erase(umap[key]);
            plist.push_front({key, it->second->second});
            umap[key] = plist.begin();
            
            return it->second->second;
        } else {
            return -1;
        }
    }
    
public:
    /**
     * lru design
     * @param operators int整型vector<vector<>> the ops
     * @param k int整型 the k
     * @return int整型vector
     */
    vector<int> LRU(vector<vector<int> >& operators, int k) {
        vector<int> res;
        if(!k) {
            return {};
        }
        
        capcity = k;
        int size = operators.size();
        umap.clear();
        plist.clear();
        
        for (int i=0; i<size; i++) {
            if (operators[i][0]==1) {
                set(operators[i][1],operators[i][2]);
            }
            else if(operators[i][0]==2) {
                res.push_back(get(operators[i][1]));
            }
        }
        
        return res;
    }
};

