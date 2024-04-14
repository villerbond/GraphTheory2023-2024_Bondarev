#pragma once

#include <vector>
#include <unordered_map>

class Solution {
public:
    long long dfs(std::unordered_map<int, std::vector<int>>& adj_list, int node, int parent, long long &res, int &seats) {

        long long representatives = 0;
        long long tmp;
        for (size_t i = 0; i < adj_list[node].size(); ++i) {
            if (adj_list[node][i] != parent) {
                long long tmp = dfs(adj_list, adj_list[node][i], node, res, seats);
                representatives += tmp;
                res += ceil(tmp / (double)seats);
            }
        }

        return representatives + 1;
    }

    long long minimumFuelCost(std::vector<std::vector<int>>&roads, int seats) {

        std::unordered_map<int, std::vector<int>> adj_list;
        int src, dst;

        for (size_t i = 0; i < roads.size(); ++i) {
            src = roads[i][0];
            dst = roads[i][1];
            adj_list[src].push_back(dst);
            adj_list[dst].push_back(src);
        }

        long long res = 0;
        dfs(adj_list, 0, -1, res, seats);
        return res;
    }
};
