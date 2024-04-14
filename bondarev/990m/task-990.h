#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <ctime>

void print(int* array) {
    for (size_t i = 0; i < 26; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

class Solution {
public:
    int find(int* array, int x) {
        if (array[x] == x) {
            return x;
        }
        return array[x] = find(array, array[x]);
    }
    void unite(int* array, int x, int y) {
        x = find(array, x);
        y = find(array, y);

        if (x == y) {
            return;
        }

        srand(time(0));

        if (rand() % 2 == 0) {
            array[x] = y;
        } else {
            array[y] = x;
        }
    }
    bool equationsPossible(std::vector<std::string>& equations) {

        int array[26];

        for (size_t i = 0; i < 26; ++i) {
            array[i] = i;
        }

        for (size_t i = 0; i < equations.size(); ++i) {

            if (equations[i][0] == equations[i][3]) {
                if (equations[i][1] == '!') {
                    return false;
                }
                else {
                    continue;
                }
            }

            if (equations[i][1] == '=') {
                unite(array, equations[i][0] - 'a', equations[i][3] - 'a');
            }
        }

        for (size_t i = 0; i < equations.size(); ++i) {

            if (equations[i][1] == '!') {
                if (find(array, equations[i][0] - 'a') == find(array, equations[i][3] - 'a')) {
                    return false;
                }
            }

        }

        //print(array);
        return true;
    }
};