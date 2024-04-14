#pragma once

#include <iostream>
#include <vector>

void print(std::vector<int>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

void print(std::vector<bool>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

class Solution {
public:
    int find(std::vector<int>& array, int x) {
        if (array[x] == x) {
            return x;
        }
        return array[x] = find(array, array[x]);
    }
    void unite(std::vector<int>& array, int x, int y) {
        //x = find(array, x);
        //y = find(array, y);

        if (x == y) {
            return;
        }

        srand(time(0));

        if (rand() % 2 == 0) {
            array[x] = y;
        }
        else {
            array[y] = x;
        }
    }
    std::vector<bool> friendRequests(int n, std::vector<std::vector<int>>& restrictions, std::vector<std::vector<int>>& requests) {

        std::vector<int> people(n);

        for (size_t i = 0; i < n; ++i) {
            people[i] = i;
        }

        //print(people);

        //int min, max;
        //for (size_t i = 0; i < restrictions.size(); ++i) {
        //    min = std::min(restrictions[i][0], restrictions[i][1]);
        //    max = std::max(restrictions[i][0], restrictions[i][1]);
        //    restrictions[i][0] = min;
        //    restrictions[i][1] = max;
        //}
        //for (size_t i = 0; i < requests.size(); ++i) {
        //    min = std::min(requests[i][0], requests[i][1]);
        //    max = std::max(requests[i][0], requests[i][1]);
        //    requests[i][0] = min;
        //    requests[i][1] = max;
        //}

        std::vector<bool> res(requests.size(), true);

        int u, v, uu, vv;
        bool isOk;
        for (size_t i = 0; i < requests.size(); ++i) {

            u = requests[i][0];
            v = requests[i][1];
            u = find(people, u);
            v = find(people, v);
            isOk = true;

            for (size_t j = 0; j < restrictions.size(); ++j) {

                uu = restrictions[j][0];
                vv = restrictions[j][1];

                uu = find(people, uu);
                vv = find(people, vv);

                if (uu == u && vv == v || uu == v && vv == u) {
                    isOk = false;
                    break;
                }
            }

            if (isOk) {
                unite(people, u, v);
            }
            res[i] = isOk;
        }

        //print(res);

        return res;
    }
};
