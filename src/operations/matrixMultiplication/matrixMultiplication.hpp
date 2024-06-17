#pragma once
#include <vector>
#include "../../tensor/Tensor.hpp"

namespace operations{
    void transposeMatrixMult(std::vector<std::vector<double>>& a, std::vector<std::vector<double>>& b, std::vector<std::vector<double>>& output);

    void matrixMult(std::vector<std::vector<double>>& a, std::vector<std::vector<double>>& b, std::vector<std::vector<double>>& output);

    std::vector<std::vector<double>> transpose(std::vector<std::vector<double>> a);

    double randomNumber();

    std::vector<std::vector<double>> createMatrix(int height, int width);

    std::vector<std::vector<double>> createOutput(std::vector<std::vector<double>>& a, std::vector<std::vector<double>>& b);

    void wrongMatrixMult(std::vector<std::vector<double>>&a, std::vector<std::vector<double>>& b, std::vector<std::vector<double>>& output);

    void matrixMult(Tensor::TensorDataStructure<double>& a, Tensor::TensorDataStructure<double>& b, Tensor::TensorDataStructure<double>& output);

};

