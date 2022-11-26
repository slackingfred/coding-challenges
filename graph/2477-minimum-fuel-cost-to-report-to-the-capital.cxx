#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    long long minimumFuelCost(vector<vector<int>>& roads, int seats) {
        long long fuels = 0;
        int n = roads.size() + 1, i, idst;
        auto cities = new unordered_set<int>[n];
        auto people = new int[n];
        unordered_set<int> s1, s2;
        auto src = &s1, dst = &s2;
        for (vector<int>& r : roads) {
            cities[r[0]].emplace(r[1]);
            cities[r[1]].emplace(r[0]);
        }
        for (i = 1; i < n; i++) {
            people[i] = 1;
            if (cities[i].size() == 1) {
                src->emplace(i);
                //cout << "leaf " << i << endl;
            }
        }
        while (src->size() > 0) {
            dst->clear();
            //cout << "src->size() is " << src->size() << endl;
            for (auto isrc : *src) {
                idst = *(cities[isrc].begin());
                fuels += people[isrc]/seats;
                if (people[isrc]%seats > 0) {
                    ++fuels;
                }
                people[idst] += people[isrc];
                people[isrc] = 0;
                cities[idst].erase(isrc);
                if (idst != 0 && cities[idst].size() == 1) {
                    dst->emplace(idst);
                    //cout << "new leaf " << idst << endl;
                }
            }
            swap(dst, src);
        }
        delete [] people;
        delete [] cities;
        return fuels;
    }
};

int main(int argc, char* argv[]) {
    Solution s;
    vector<vector<int>> data = {{0,1},{0,2},{0,3}};
    cout << s.minimumFuelCost(data, 5) << endl;
    data = {{3,1},{3,2},{1,0},{0,4},{0,5},{4,6}};
    cout << s.minimumFuelCost(data, 2) << endl;
    return 0;
}
