#pragma once

#include <vector>
#include <string>
#include <iostream>

void print(std::vector<int>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

void print(std::vector<std::vector<int>>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
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
public:

    std::vector<std::vector<int>> adj_list;
    int res;

    int dfs(int node, std::string& s) {
        int max_path = 0;
        int second_max_path = 0;

        for (size_t i = 0; i < adj_list[node].size(); ++i) {

            int tmp_path_of_child = dfs(adj_list[node][i], s);

            if (s[adj_list[node][i]] == s[node]) {
                continue;
            }

            if (tmp_path_of_child > max_path) {
                second_max_path = max_path;
                max_path = tmp_path_of_child;
            }
            else if (tmp_path_of_child > second_max_path) {
                second_max_path = tmp_path_of_child;
            }

        }

        res = std::max(res, max_path + second_max_path + 1);

        return max_path + 1;
    }

    int longestPath(std::vector<int>& parent, std::string s) {

        adj_list.resize(parent.size());

        for (size_t i = 1; i < parent.size(); ++i) {
            adj_list[parent[i]].push_back(i);
        }

        res = 1;
        dfs(0, s);

        return res;
    }
};