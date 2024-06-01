#include "Tensor.hpp"
#include "util.hpp"

void Tensor::TensorFormat::setFormat(){

}

unsigned int Tensor::TensorFormat::totalLength(){
    if(this->strides.size()>0){
        return this->strides[this->strides.size()-1];
    }
    return 0;
    // Throw error
}


// template<class T>
// Tensor::TensorDataStructure<T>(Tensor::TensorFormat& format){
//     validateTensorFormat(dataFormat);
//     this->format = dataFormat;
// }

template<class T>
void Tensor::TensorDataStructure<T>::setData(T* d){
    std::copy(d, d + this->format.totalLength(), std::back_inserter(this->data));
}

template<class T>
std::vector<unsigned int> Tensor::TensorDataStructure<T>::getStrides(){
    return this->format.strides;
}

template<class T>
unsigned int Tensor::TensorDataStructure<T>::getRank(){
    return this->format.rank;
}

template<class T>
std::vector<unsigned int> Tensor::TensorDataStructure<T>::getLayout(){
    return this->format.layout;
}

template<class T>
T* Tensor::TensorDataStructure<T>::getRawData(){
    return this->data.data();
}
