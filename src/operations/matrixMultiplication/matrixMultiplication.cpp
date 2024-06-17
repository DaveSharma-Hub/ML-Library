#include "matrixMultiplication.hpp"
#include <iostream>
#include <math.h>
#include "../../tensor/Tensor.hpp"

void operations::transposeMatrixMult(std::vector<std::vector<double>>& a, std::vector<std::vector<double>>& b, std::vector<std::vector<double>>& output){
    for(int i=0;i<a.size();i++){
        for(int j=0;j<b.size();j++){
            for(int k=0;k<a[0].size();k++){
                output[i][j] += a[i][k] * b[j][k];
            }
        }
    }
}

void operations::matrixMult(std::vector<std::vector<double>>& a, std::vector<std::vector<double>>& b, std::vector<std::vector<double>>& output){
    for(int i=0;i<a.size();i++){
        for(int j=0;j<b[0].size();j++){
            for(int z=0;z<a[0].size();z++){
                output[i][j] += a[i][z] * b[z][j]; 
            }
        }
    }
}

std::vector<std::vector<double>> operations::transpose(std::vector<std::vector<double>> a){
    std::vector<std::vector<double>> output;
    for(int i=0;i<a[0].size();i++){
        std::vector<double> tmp;
        for(int j=0;j<a.size();j++){
            tmp.push_back(a[j][i]);
        }
        output.push_back(tmp);
    }
    return output;
}

double operations::randomNumber(){
    return (((rand() / (double)RAND_MAX)));
}

std::vector<std::vector<double>> operations::createMatrix(int height, int width){
    std::vector<std::vector<double>> matrix;
    for(int i=0;i<height;i++){
        std::vector<double> vec;
        for(int j=0;j<width;j++){
            vec.push_back(operations::randomNumber());
        }
        matrix.push_back(vec);
    }  
    return matrix;
}

std::vector<std::vector<double>> operations::createOutput(std::vector<std::vector<double>>& a, std::vector<std::vector<double>>& b){
    std::vector<std::vector<double>> output(a.size());
    for(int i=0;i<a.size();i++){
        std::vector<double> vec(b[0].size());
        output[i] = vec;
    }
    return output;
}


void operations::wrongMatrixMult(std::vector<std::vector<double>>&a, std::vector<std::vector<double>>& b, std::vector<std::vector<double>>& output){
    std::vector<double> alpha;
    std::vector<double> beta;
    for(int i=0;i<a.size();i++){
        int v = 0;
        for(int j=0;j<a[i].size();j++){
            v += a[i][j];
        }
        alpha.push_back(v);
    }
    for(int i=0;i<b.size();i++){
        int v = 0;
        for(int j=0;j<b[i].size();j++){
            v += b[i][j];
        }
        beta.push_back(v);
    }
    for(int i=0;i<alpha.size();i++){
        for(int j=0;j<beta.size();j++){
            // output[i][j] = alpha[i] * beta[j] - (alpha[i]/a[0].size() * beta[j]/b.size() * 1/pow(a[0].size(),0.000000000001));
            output[i][j] = alpha[i] * beta[j] - (alpha[i]/a[0].size() * (beta[j]/b.size()));
        }
    }
}


void operations::matrixMult(Tensor::TensorDataStructure<double>& a, Tensor::TensorDataStructure<double>& b, Tensor::TensorDataStructure<double>& output){
    std::vector<unsigned int> aLayout = a.getLayout();
    std::vector<unsigned int> bLayout = b.getLayout();

    for(unsigned int i=0;i<aLayout[1];i++){
        for(unsigned int j=0;j<bLayout[2];j++){
            for(unsigned int z=0;z<aLayout[2];z++){
                std::vector<unsigned int> first{0,i,j};
                std::vector<unsigned int> second{0,i,z};
                std::vector<unsigned int> third{0,z,j};

                double ogValue = output.getValue(first) + (a.getValue(second) * b.getValue(third));
                output.setValue(first, ogValue);  
            }
        }
    }
}