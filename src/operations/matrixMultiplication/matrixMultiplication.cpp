#include "matrixMultiplication.hpp"
#include <iostream>


void operations::transposeMatrixMult(std::vector<std::vector<int>>& a, std::vector<std::vector<int>>& b, std::vector<std::vector<int>>& output){
    for(int i=0;i<a.size();i++){
        for(int j=0;j<b.size();j++){
            for(int k=0;k<a[0].size();k++){
                output[i][j] += a[i][k] * b[j][k];
            }
        }
    }
}

void operations::matrixMult(std::vector<std::vector<int>>& a, std::vector<std::vector<int>>& b, std::vector<std::vector<int>>& output){
    for(int i=0;i<a.size();i++){
        for(int j=0;j<b[0].size();j++){
            for(int z=0;z<a[0].size();z++){
                output[i][j] += a[i][z] * b[z][j]; 
            }
        }
    }
}

std::vector<std::vector<int>> operations::transpose(std::vector<std::vector<int>> a){
    std::vector<std::vector<int>> output;
    for(int i=0;i<a[0].size();i++){
        std::vector<int> tmp;
        for(int j=0;j<a.size();j++){
            tmp.push_back(a[j][i]);
        }
        output.push_back(tmp);
    }
    return output;
}

int operations::randomNumber(){
    return (((rand() / (double)RAND_MAX)) * 500);
}

std::vector<std::vector<int>> operations::createMatrix(int height, int width){
    std::vector<std::vector<int>> matrix;
    for(int i=0;i<height;i++){
        std::vector<int> vec;
        for(int j=0;j<width;j++){
            vec.push_back(operations::randomNumber());
        }
        matrix.push_back(vec);
    }  
    return matrix;
}

std::vector<std::vector<int>> operations::createOutput(std::vector<std::vector<int>>& a, std::vector<std::vector<int>>& b){
    std::vector<std::vector<int>> output(a.size());
    for(int i=0;i<a.size();i++){
        std::vector<int> vec(b[0].size());
        output[i] = vec;
    }
    return output;
}

void operations::wrongMatrixMult(std::vector<std::vector<int>>&a, std::vector<std::vector<int>>& b, std::vector<std::vector<int>>& output){
    std::vector<int> alpha;
    std::vector<int> beta;
    for(int i=0;i<a.size();i++){
        int v = 0;
        for(int j=0;j<a[i].size();j++){
            v+=a[i][j];
        }
        alpha.push_back(v);
    }
    for(int i=0;i<b.size();i++){
        int v = 0;
        for(int j=0;j<b[i].size();j++){
            v+=b[i][j];
        }
        beta.push_back(v);
    }
    for(int i=0;i<alpha.size();i++){
        for(int j=0;j<beta.size();j++){
            output[i][j] = alpha[i] * beta[j];
        }
    }
}
