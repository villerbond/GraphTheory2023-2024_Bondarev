#pragma once

#include <vector>
#include <iostream>
#include <queue>

void print(std::vector<std::vector<int>>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << i << " -> ";
        for (size_t j = 0; j < vec[i].size(); ++j) {
            std::cout << vec[i][j];
        }
        std::cout << std::endl;
    }
}

void print(std::vector<int>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

class Solution {
public:
    std::vector<int> shortestAlternatingPaths(int n, std::vector<std::vector<int>>& redEdges, std::vector<std::vector<int>>& blueEdges) {

        // <dst, is_visited>
        std::vector<std::vector<int>> red_adj_list(n);
        std::vector<std::vector<int>> blue_adj_list(n);

        int src, dst;
        for (size_t i = 0; i < redEdges.size(); ++i) {
            src = redEdges[i][0];
            dst = redEdges[i][1];
            red_adj_list[src].push_back(dst);
        }
        for (size_t i = 0; i < blueEdges.size(); ++i) {
            src = blueEdges[i][0];
            dst = blueEdges[i][1];
            blue_adj_list[src].push_back(dst);
        }

        //print(red_adj_list);
        //print(blue_adj_list);

        std::vector<int> res(n);

        std::vector<int> dist_red(n, -1);
        std::vector<int> dist_blue(n, -1);
        dist_red[0] = 0;
        dist_blue[0] = 0;

        //print(dist_red);
        //print(dist_blue);

        std::queue<std::pair<int, int>> q;
        q.push({ 0, -1 });
        std::pair<int, int> tmp;
        int curr_ver, curr_color;

        while (!q.empty()) {
            tmp = q.front();
            curr_ver = tmp.first;
            curr_color = tmp.second;
            // what edge color was the last one to reach this vertice
            // 0 - red
            // 1 - blue
            // -1 - not undefined (for vertice 0)
            q.pop();
            std::cout << curr_ver << " " << curr_color << std::endl;
            if (curr_color != 1) {
                for (size_t i = 0; i < blue_adj_list[curr_ver].size(); ++i) {
                    if (dist_blue[blue_adj_list[curr_ver][i]] == -1) {
                        q.push({ blue_adj_list[curr_ver][i], 1 });
                        dist_blue[blue_adj_list[curr_ver][i]] = dist_red[curr_ver] + 1;
                    }
                }
            }
            if (curr_color != 0) {
                for (size_t i = 0; i < red_adj_list[curr_ver].size(); ++i) {
                    if (dist_red[red_adj_list[curr_ver][i]] == -1) {
                        q.push({ red_adj_list[curr_ver][i], 0 });
                        dist_red[red_adj_list[curr_ver][i]] = dist_blue[curr_ver] + 1;
                    }
                }
            }
        }

        //print(dist_red);
        //print(dist_blue);

        for (size_t i = 0; i < n; ++i) {
            if (dist_red[i] == -1) {
                res[i] = dist_blue[i];
            } else if (dist_blue[i] == -1) {
                res[i] = dist_red[i];
            } else {
                res[i] = std::min(dist_red[i], dist_blue[i]);
            }
        }

        //print(res);

        return res;
    }
};