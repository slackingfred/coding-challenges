#include <algorithm>
#include <cmath>
#include <cstdio>
#include <utility>
#include <vector>

using std::abs;
using std::max;
using std::min;
using std::pair;
using std::printf;
using std::putchar;
using std::sort;
using std::swap;
using std::vector;

class Solution {
public:
    vector<vector<int>> outerTrees(vector<vector<int>>& trees) {
        vector<vector<int>> finalTrees;
        vector<pair<size_t, double>> slopes(trees.size());
        
        size_t i;
        int leftmostIdx = 0;
        for (i = 1; i < trees.size(); i++) {
            if (trees[i][0] < trees[leftmostIdx][0]) {
                leftmostIdx = i;
            } else if (trees[i][0] == trees[leftmostIdx][0] && trees[i][1] < trees[leftmostIdx][1]) {
                leftmostIdx = i;
            }
        }
        swap(trees[0], trees[leftmostIdx]);

        double slopeLow = MAX_SLOPE, slopeHigh = MIN_SLOPE;
        slopes[0] = { 0, SLOPE_FOR_ORIGIN };
        for (i = 1; i < trees.size(); i++) {
            slopes[i].first = i;
            slopes[i].second = calSlope(trees[0], trees[i]);
            slopeLow = min(slopeLow, slopes[i].second);
            slopeHigh = max(slopeHigh, slopes[i].second);
        }
        //printf("\nSlopes range from %lf to %lf\n", slopeLow, slopeHigh);
        sort(slopes.begin(), slopes.end(), [&trees, slopeLow](pair<size_t, double>& lhs, pair<size_t, double>& rhs) {
            if (lhs.second == rhs.second) {
                if (lhs.second == slopeLow) {
                    return abs(trees[lhs.first][0]-trees[0][0])+abs(trees[lhs.first][1]-trees[0][1]) < abs(trees[rhs.first][0]-trees[0][0])+abs(trees[rhs.first][1]-trees[0][1]);
                }
                return abs(trees[lhs.first][0]-trees[0][0])+abs(trees[lhs.first][1]-trees[0][1]) > abs(trees[rhs.first][0]-trees[0][0])+abs(trees[rhs.first][1]-trees[0][1]);
            }
            return lhs.second < rhs.second;
        });

        //printf("adding [%d,%d]\n", trees[0][0], trees[0][1]);
        finalTrees.push_back(trees[0]);
        if (trees.size() == 1) {
            return finalTrees;
        }
        //printf("adding [%d,%d]\n", trees[slopes[1].first][0], trees[slopes[1].first][1]);
        finalTrees.push_back(trees[slopes[1].first]);
        for (i = 2; i < trees.size(); i++) {
            while (!isTurningLeft(finalTrees[finalTrees.size()-2], finalTrees[finalTrees.size()-1], trees[slopes[i].first])) {
                //printf("removing [%d,%d]\n", finalTrees[finalTrees.size()-1][0], finalTrees[finalTrees.size()-1][1]);
                finalTrees.pop_back();
            }
            //printf("adding [%d,%d]\n", trees[slopes[i].first][0], trees[slopes[i].first][1]);
            finalTrees.push_back(trees[slopes[i].first]);
            if (slopes[i].second == slopeHigh) {
                break;
            }
        }
        for (i++; i < trees.size(); i++) {
            //printf("finally adding [%d,%d]\n", trees[slopes[i].first][0], trees[slopes[i].first][1]);
            finalTrees.push_back(trees[slopes[i].first]);
        }
        return finalTrees;
    }
private:
    const double SLOPE_FOR_ORIGIN = -10001;
    const double MIN_SLOPE = -10000;
    const double MAX_SLOPE = 10000;

    double calSlope(const vector<int>& a, const vector<int>& b) {
        double dx = b[0] - a[0];
        double dy = b[1] - a[1];
        if (dx == 0) {
            return dy > 0 ? MAX_SLOPE : MIN_SLOPE;
        }
        return dy / dx;
    }

    double calSlope2(const vector<int>& a, const vector<int>& b) {
        double dx = b[0] - a[0];
        double dy = b[1] - a[1];
        if (dx == 0) {
            return MIN_SLOPE;
        }
        return dy / dx;
    }

    int whichQuadrant(const vector<int>& a, const vector<int>& b) {
        int dx = b[0] - a[0];
        int dy = b[1] - a[1];
        if (dx > 0 && dy >= 0) {
            return 1;
        } else if (dx <= 0 && dy > 0) {
            return 2;
        } else if (dx < 0 && dy <= 0) {
            return 3;
        } else if (dx >= 0 && dy < 0) {
            return 4;
        }
        return 0; // a and b are the same point
    }

    int isTurningLeft(const vector<int>& a, const vector<int>& b, const vector<int>& c) {
        //printf("%d,%d -> %d,%d -> %d,%d\n", a[0], a[1], b[0], b[1], c[0], c[1]);
        int qab = whichQuadrant(a, b);
        int qbc = whichQuadrant(b, c);
        //printf("qab %d, qbc %d\n", qab, qbc);
        if (qab != qbc) {
            return (qab%4 < qbc%4);
        }
        double sab = calSlope2(a, b);
        double sbc = calSlope2(b, c);
        //printf("sab %lf, sbc %lf\n", sab, sbc);
        return sbc >= sab;
    }
};

static void printPoints(const vector<vector<int>>& pts) {
    putchar('[');
    for (const vector<int>& pt : pts) {
        printf("[%d,%d],", pt[0], pt[1]);
    }
    printf("\b]\n");
}

int main(int argc, char* argv[]) {
    Solution s;
    vector<vector<int>> data;
    data = {{1,1},{2,2},{2,0},{2,4},{3,3},{4,2}};
    printPoints(s.outerTrees(data));
    data = {{1,2},{2,2},{4,2}};
    printPoints(s.outerTrees(data));
    data = {{3,0},{4,0},{5,0},{6,1},{7,2},{7,3},{7,4},{6,5},{5,5},{4,5},{3,5},{2,5},{1,4},{1,3},{1,2},{2,1},{4,2},{0,3}};
    printPoints(s.outerTrees(data));
    data = {{0,0},{0,100},{100,100},{100,0}};
    printPoints(s.outerTrees(data));
    data = {{0,2},{0,1},{0,0},{1,0},{2,0},{1,1}};
    printPoints(s.outerTrees(data));
    data = {{0,0},{0,1},{0,2},{1,2},{2,2},{3,2},{3,1},{3,0},{2,0},{1,0},{1,1},{3,3}};
    printPoints(s.outerTrees(data));
    return 0;
}
