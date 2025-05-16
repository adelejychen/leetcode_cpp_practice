#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

class Solution {
public:
    string alienOrder(const vector<string>& words) {
        // build graph & indegree map
        unordered_map<char, unordered_set<char>> nexts;
        unordered_map<char, int> indegree;
        for (auto& w : words) {
            for (char c : w) {
                nexts[c];           // ensure node exists
                indegree[c] = 0;    // initialize indegree
            }
        }
        
        // derive edges from adjacent words
        for (int i = 0; i + 1 < (int)words.size(); ++i) {
            const string &a = words[i], &b = words[i+1];
            if (a.size() > b.size() && a.rfind(b, 0) == 0)
                return "";  // invalid prefix case
            int n = min(a.size(), b.size());
            for (int j = 0; j < n; ++j) {
                if (a[j] != b[j]) {
                    if (!nexts[a[j]].count(b[j])) {
                        nexts[a[j]].insert(b[j]);
                        indegree[b[j]]++;
                    }
                    break;
                }
            }
        }
        
        // enqueue zero‐indegree nodes
        queue<char> q;
        for (auto& [c, deg] : indegree) {
            if (deg == 0) q.push(c);
        }
        
        // BFS / Kahn’s topological sort
        string order;
        while (!q.empty()) {
            char cur = q.front(); q.pop();
            order += cur;
            for (char nei : nexts[cur]) {
                if (--indegree[nei] == 0)
                    q.push(nei);
            }
        }
        
        return (order.size() == indegree.size()) ? order : "";
    }
};
