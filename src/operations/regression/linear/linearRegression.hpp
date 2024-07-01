#pragma once
#include "../../../tensor/Tensor.hpp"
#include <vector>

namespace Regression{

    template <class D>
    class Linear{
        private:
            Tensor::TensorDataStructure<D> input;
            Tensor::TensorDataStructure<D> weights;
            int epochCount = 1000;
            double learningRate = 0.01;
            void convertDataToTensor(std::vector<std::vector<D>>& data);
        public:
            Linear(int epochCount, double learningRate);
            void setInputData(std::vector<std::vector<D>> data);
            void setInputTensor(Tensor::TensorDataStructure<D> input);
            void run();
    };
};
