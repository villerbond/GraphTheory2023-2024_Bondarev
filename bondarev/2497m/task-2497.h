#pragma once

#include <vector>
#include <iostream>

void print(std::vector<std::vector<std::pair<int, int>>>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << i << " -> ";
        for (size_t j = 0; j < vec[i].size(); ++j) {
            std::cout << vec[i][j].second << "(" << vec[i][j].first << "), ";
        }
        std::cout << std::endl;
    }
}

class Solution {
public:
    int maxStarSum(std::vector<int>& vals, std::vector<std::vector<int>>& edges, int k) {

        std::vector<std::vector<std::pair<int, int>>> adj_list(vals.size());
        int src, dst;
        for (size_t i = 0; i < edges.size(); ++i) {
            src = edges[i][0];
            dst = edges[i][1];
            if (vals[dst] >= 0) {
                adj_list[src].push_back({ vals[dst], dst });
            }
            if (vals[src] >= 0) {
                adj_list[dst].push_back({ vals[src], src });
            }
        }
        
        //print(adj_list);

        int res = INT_MIN, tmp;

        for (size_t i = 0; i < adj_list.size(); ++i) {
            tmp = vals[i];
            std::sort(adj_list[i].begin(), adj_list[i].end(), std::greater<>());
            if (adj_list[i].size() <= k) {
                for (size_t j = 0; j < adj_list[i].size(); ++j) {
                    tmp += adj_list[i][j].first;
                }
            }
            else {
                for (size_t j = 0; j < k; ++j) {
                    tmp += adj_list[i][j].first;
                }
            }
            if (tmp > res) {
                res = tmp;
            }
        }

        //print(adj_list);

        return res;
    }
};