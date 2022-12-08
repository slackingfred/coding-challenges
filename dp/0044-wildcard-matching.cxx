#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::swap;

class Solution {
public:
    bool isMatch(string s, string p) {
        vector<bool> arr1(s.size() + 1);
        vector<bool> arr2(s.size() + 1);
        vector<bool>& dp = arr1, next = arr2;
        size_t i, j;
        dp[0] = true; // Empty pattern matches empty string
        for (i = 0; i < p.size(); i++) {
            next[0] = dp[0] && (p[i] == '*');
            for (j = 0; j < s.size(); j++) {
                switch (p[i]) {
                case '?':
                    next[j+1] = dp[j];
                    break;
                case '*':
                    next[j+1] = dp[j+1] || dp[j] || next[j];
                    break;
                default:
                    next[j+1] = dp[j] && (s[j] == p[i]);
                    break;
                }
            }
            swap(dp, next);
        }
        return dp[s.size()];
    }
};

int main(int argc, char* argv[]) {
    Solution s;
    cout << s.isMatch("aa", "a") << endl;
    cout << s.isMatch("aa", "*") << endl;
    cout << s.isMatch("cb", "?a") << endl;
    cout << s.isMatch("abababcd", "ab*abcd") << endl;
    return 0;
}
