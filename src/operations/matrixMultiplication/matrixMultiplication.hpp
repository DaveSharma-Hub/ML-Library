#pragma once
#include <vector>

namespace operations{
    void transposeMatrixMult(std::vector<std::vector<int>>& a, std::vector<std::vector<int>>& b, std::vector<std::vector<int>>& output);

    void matrixMult(std::vector<std::vector<int>>& a, std::vector<std::vector<int>>& b, std::vector<std::vector<int>>& output);

    std::vector<std::vector<int>> transpose(std::vector<std::vector<int>> a);

    int randomNumber();

    std::vector<std::vector<int>> createMatrix(int height, int width);

    std::vector<std::vector<int>> createOutput(std::vector<std::vector<int>>& a, std::vector<std::vector<int>>& b);

    void wrongMatrixMult(std::vector<std::vector<int>>&a, std::vector<std::vector<int>>& b, std::vector<std::vector<int>>& output);

};

