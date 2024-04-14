#pragma once
#include <vector>
#include <iostream>
#include <queue>

void print_vec(std::vector<int>& vec, int n) {
    for (size_t i = 1; i < n+1; ++i) {
        if (vec[i] == INT_MAX) {
            std::cout << "inf ";
        } else {
            std::cout << vec[i] << " ";
        }
    }
    std::cout << std::endl;
}

class Solution {
public:
    int networkDelayTime(std::vector<std::vector<int>>& times, int n, int k) {

        std::vector<std::vector<std::pair<int, int>>> adj_list(n + 1);

        int src, dst, weight;

        for (size_t i = 0; i < times.size(); ++i) {
            src = times[i][0];
            dst = times[i][1];
            weight = times[i][2];
            adj_list[src].push_back({ dst, weight });
        }

        //for (size_t i = 1; i < n + 1; ++i) {
        //    std::cout << i << " -> ";
        //    for (size_t j = 0; j < adj_list[i].size(); ++j) {
        //        std::cout << "(" << adj_list[i][j].first << ", " << adj_list[i][j].second << ")";
        //    }
        //    std::cout << std::endl;
        //}

        std::vector<int> min_dists(n + 1, INT_MAX);
        min_dists[k] = 0;

        //print_vec(min_dists, n);

        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

        pq.push({ 0, k });
        int tmp_src, tmp_dst, tmp_weight;

        while (!pq.empty()) {

            tmp_src = pq.top().second;
            pq.pop();

            for (size_t i = 0; i < adj_list[tmp_src].size(); ++i) {
                tmp_dst = adj_list[tmp_src][i].first;
                tmp_weight = adj_list[tmp_src][i].second;

                if (min_dists[tmp_src] + tmp_weight < min_dists[tmp_dst]) {
                    min_dists[tmp_dst] = min_dists[tmp_src] + tmp_weight;
                    pq.push({ min_dists[tmp_src] + tmp_weight, tmp_dst });
                }
            }
        }

        print_vec(min_dists, n);

        int res = 0;
        
        for (size_t i = 1; i < n+1; ++i) {
            if (min_dists[i] == INT_MAX) {
                res = -1;
                break;
            }
            res = std::max(min_dists[i], res);
        }

        return res;
    }
};