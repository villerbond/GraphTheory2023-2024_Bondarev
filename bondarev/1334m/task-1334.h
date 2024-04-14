#pragma once

#include <vector>

void print(std::vector<std::vector<int>>& matrix, int n) {
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (matrix[i][j] == INT_MAX) {
                std::cout << "inf\t";
            }
            else {
                std::cout << matrix[i][j] << "\t";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

class Solution {
public:
    int findTheCity(int n, std::vector<std::vector<int>>& edges, int distanceThreshold) {

        std::vector<std::vector<int>> adj_matrix(n, std::vector<int>(n, INT_MAX));

        int src, dst;
        for (size_t i = 0; i < edges.size(); ++i) {
            src = edges[i][0];
            dst = edges[i][1];

            adj_matrix[src][dst] = edges[i][2];
            adj_matrix[dst][src] = edges[i][2];
        }

        for (size_t i = 0; i < n; ++i) {
            adj_matrix[i][i] = 0;
        }

        //Floyd

        //print(adj_matrix, n);

        for (size_t i = 0; i < n; ++i) {
            for (size_t u = 0; u < n; ++u) {
                for (size_t v = 0; v < n; ++v) {

                    if (adj_matrix[u][i] != INT_MAX && adj_matrix[i][v] != INT_MAX) {
                        adj_matrix[u][v] = std::min(adj_matrix[u][v], adj_matrix[u][i] + adj_matrix[i][v]);
                    }

                }
            }
            //print(adj_matrix, n);
        }

        int min_count = n;
        int res_city = -1;
        int tmp_count;

        for (size_t i = 0; i < n; ++i) {

            tmp_count = 0;

            for (size_t j = 0; j < n; ++j) {
                if (adj_matrix[i][j] <= distanceThreshold) {
                    ++tmp_count;
                }
            }

            if (tmp_count <= min_count) {
                res_city = i;
                min_count = tmp_count;
            }
        }

        return res_city;
    }
};