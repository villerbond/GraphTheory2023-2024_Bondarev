#pragma once

#include <vector>
#include <iostream>
#include <queue>

void print_vec(std::vector<int>& vec, int n) {
    for (size_t i = 1; i < n + 1; ++i) {
        if (vec[i] == INT_MAX) {
            std::cout << "inf ";
        }
        else {
            std::cout << vec[i] << " ";
        }
    }
    std::cout << std::endl;
}

void print(std::vector<std::vector<int>>& vec) {
    for (size_t i = 1; i < vec.size(); ++i) {
        std::cout << i << " -> ";
        for (size_t j = 0; j < vec[i].size(); ++j) {
            std::cout << vec[i][j];
            if (j != vec[i].size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }
}

class Solution {
    int CONSTRAINT = 1000000007;
public:
    int dfs( std::vector<std::vector<int>>& dir_adj_list, std::vector<int>& dp, std::vector<bool>& visited, int curr) {
        if (visited[curr]) {
            return dp[curr];
        }
        visited[curr] = true;
        int tmp;
        for (size_t i = 0; i < dir_adj_list[curr].size(); ++i) {
            tmp = dir_adj_list[curr][i];
            if (!visited[tmp]) {
                dfs(dir_adj_list, dp, visited, tmp);
            }
            dp[curr] = (dp[curr] + dp[tmp]) % CONSTRAINT;
        }
        return dp[curr];
    }

    int countRestrictedPaths(int n, std::vector<std::vector<int>>& edges) {

        std::vector<std::vector<std::pair<int, int>>> adj_list(n + 1);
        int src, dst, weight;

        for (size_t i = 0; i < edges.size(); ++i) {
            src = edges[i][0];
            dst = edges[i][1];
            weight = edges[i][2];
            adj_list[src].push_back({ dst, weight });
            adj_list[dst].push_back({ src, weight });
        }

        std::vector<int> min_dists(n + 1, INT_MAX);
        min_dists[n] = 0;

        //print_vec(min_dists, n);

        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
        pq.push({ 0, n });
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

        //print_vec(min_dists, n);

        std::vector<std::vector<int>> dir_adj_list(n + 1);

        for (size_t i = 0; i < edges.size(); ++i) {
            src = edges[i][0];
            dst = edges[i][1];
            if (min_dists[src] > min_dists[dst]) {
                dir_adj_list[src].push_back(dst);
            }
            else if (min_dists[dst] > min_dists[src]) {
                dir_adj_list[dst].push_back(src);
            }
        }

        //print(dir_adj_list);

        std::vector<int> dp(n + 1, 0);
        std::vector<bool> visited(n + 1, false);
        dp[n] = 1;
        visited[n] = true;

        return dfs(dir_adj_list, dp, visited, 1);
    }
};