#include "../../../tensor/Tensor.hpp"
#include "linearRegression.hpp"
#include "../../matrixMultiplication/matrixMultiplication.hpp"
#include <vector>
#include <assert.h>

template <class D>
void Regression::Linear<D>::convertDataToTensor(std::vector<std::vector<D>>& data)
{
    if(this->input.isEmpty && data.size()>0 && data[0].size()>0){
        int height = data.size();
        int width = data[0].size();
        std::vector<unsigned int> layout = {1, (unsigned int)height, (unsigned int)width, sizeof(D)};
        std::vector<unsigned int> strides;
        unsigned int tmp = layout[0];
        for(int i=0;i<layout.size()-1;i++){
            strides.push_back(tmp);
            tmp *= layout[i+1];
        }
        strides.push_back(tmp);

        Tensor::TensorFormat tensorFormat = Tensor::TensorFormat{strides:strides, rank:4, layout:layout};
        this->input.setTensorFormat(tensorFormat);
        this->input.setData((D*)data.data());
    }
}
template <class D>
Regression::Linear<D>::Linear(int epochCount, double learningRate):epochCount(epochCount),learningRate(learningRate) {};

template <class D>
void Regression::Linear<D>::setInputData(std::vector<std::vector<D>> data)
{
    this->convertDataToTensor(data);
}

template <class D>
void Regression::Linear<D>::setInputTensor(Tensor::TensorDataStructure<D> input){
    this->input = input;
}

template <class D>
void Regression::Linear<D>::run(){
    this->weights = Tensor::TensorDataStructure<D>(this->input.getFormat());
    this->weights.allocateData();
    assert(!this->input.isEmpty && !this->weights.isEmpty);
    return;
}

