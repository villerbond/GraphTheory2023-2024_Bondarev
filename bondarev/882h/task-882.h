#pragma once

#include <vector>
#include <iostream>
#include <queue>

void print_vec(std::vector<int>& vec, int n) {
    for (size_t i = 0; i < n; ++i) {
        if (vec[i] == INT_MAX) {
            std::cout << "inf ";
        }
        else {
            std::cout << vec[i] << " ";
        }
    }
    std::cout << std::endl;
}

class Solution {
public:
    int reachableNodes(std::vector<std::vector<int>>& edges, int maxMoves, int n) {

        std::vector<std::vector<std::pair<int, int>>> adj_list(n);

        int src, dst, weight;

        for (size_t i = 0; i < edges.size(); ++i) {
            src = edges[i][0];
            dst = edges[i][1];
            weight = edges[i][2];
            adj_list[src].push_back({ dst, weight });
            adj_list[dst].push_back({ src, weight });
        }

        std::vector<int> min_dists(n, INT_MAX);
        min_dists[0] = 0;

        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

        pq.push({ 0, 0 });
        int tmp_src, tmp_dst, tmp_weight;

        while (!pq.empty()) {

            tmp_src = pq.top().second;
            pq.pop();

            for (size_t i = 0; i < adj_list[tmp_src].size(); ++i) {
                tmp_dst = adj_list[tmp_src][i].first;
                tmp_weight = adj_list[tmp_src][i].second;

                if (min_dists[tmp_src] + tmp_weight + 1 < min_dists[tmp_dst]) {
                    min_dists[tmp_dst] = min_dists[tmp_src] + tmp_weight + 1;
                    pq.push({min_dists[tmp_src] + tmp_weight + 1, tmp_dst});
                }
            }

        }

        //print_vec(min_dists, n);

        int res = 0;
        for (size_t i = 0; i < n; ++i) {
            if (min_dists[i] <= maxMoves) {
                ++res;
            }
        }

        int moves_to_src, moves_to_dst, count_of_inner_vert;

        for (size_t i = 0; i < edges.size(); ++i) {
            tmp_src = edges[i][0];
            tmp_dst = edges[i][1];
            tmp_weight = edges[i][2];

            moves_to_src = min_dists[tmp_src];
            moves_to_dst = min_dists[tmp_dst];

            if (moves_to_src > maxMoves) {
                // make res += 0
                moves_to_src = maxMoves;
            }
            if (moves_to_dst > maxMoves) {
                moves_to_dst = maxMoves;
            }

            if (maxMoves - moves_to_src + maxMoves - moves_to_dst > tmp_weight) {
                res += tmp_weight;
            }
            else {
                res += maxMoves - moves_to_src + maxMoves - moves_to_dst;
            }
        }

        return res;
    }
};