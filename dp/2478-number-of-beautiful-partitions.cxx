#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::swap;

class Solution {
public:
    int beautifulPartitions(string s, int k, int minLength) {
        bool isPrime[] = {
            false, false, true, true, false,
            true, false, true, false, false,
        };
        if (!isPrime[s[0]-'0'] || isPrime[s[s.size()-1]-'0'] || (size_t)k*minLength > s.size()) {
            return 0;
        }
        auto canSplit = [&](int i) {
            return /*i == 0 || i == s.size() ||*/ !isPrime[s[i-1]-'0'] && isPrime[s[i]-'0'];
        };
        auto last = new int[s.size()];
        auto current = new int[s.size()];
        size_t i, j;
        for (i = 0; i < s.size(); i++) {
            current[i] = 1;
        }
        for (j = 1; j < (size_t)k; j++) {
            swap(last, current);
            i = minLength * j;
            current[i-1] = 0;
            for (; i <= s.size() - minLength; i++) {
                current[i] = current[i-1];
                if (canSplit(i)) {
                    current[i] += last[i - minLength];
                    if (current[i] >= MOD) {
                        current[i] -= MOD;
                    }
                }
            }
        }
        int ans = current[s.size() - minLength];
        delete [] current;
        delete [] last;
        return ans;
    }

    const int MOD = 1000000007;
};

int main(int argc, char* argv[]) {
    Solution s;
    cout << s.beautifulPartitions("2943278432749327423894732859327592794732947329432794", 3, 2) << endl;
    cout << s.beautifulPartitions("3434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434343434", 3, 3) << endl;
    cout << s.beautifulPartitions("34343434", 8, 8) << endl;
    cout << s.beautifulPartitions("22", 1, 1) << endl;
    return 0;
}
