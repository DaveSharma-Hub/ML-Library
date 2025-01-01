#include <iostream>
#include <vector>
#include <cstdint>

class Matrix{
  public:
    Matrix(std::vector<std::vector<double>> input_): array(input_){};
    
    Matrix operator*(Matrix& a){
        return Matrix(this->matrixMult(
            this->array,
            a.getArray()
        ));
    }
    
    std::vector<std::vector<double>>& getArray(){
        return this->array;
    }
    
    void print(){
        for(int i=0;i<this->array.size();i++){
            for(int j=0;j<this->array[i].size();j++){
                std::cout<<this->array[i][j]<<" ";
            }
            std::cout<<"\n";
        }
    }
  private:
    std::vector<std::vector<double>> array;
    std::vector<std::vector<double>> matrixMult(std::vector<std::vector<double>>& first, std::vector<std::vector<double>>& second){
        std::vector<std::vector<double>> matrix;
        for(int i=0;i<first.size();i++){
            std::vector<double> inner;
            
            for(int j=0;j<second[0].size();j++){
                double value = 0;
                for(int k=0;k<second.size();k++){
                    value += first[i][k] * second[k][j];
                }
                inner.push_back(value);
            }
            matrix.push_back(inner);
        }
        return matrix;
    }
};

class LinearRegression{
  public:
    LinearRegression(uint64_t iterations_, std::vector<std::vector<double>> initialWeights_): iterations(iterations_){
        this->weights = new Matrix(initialWeights_);   
    }
    
    LinearRegression* initializeData(std::vector<std::vector<double>> data_){
        this->rawData = new Matrix(data_);
        return this;
    }
    
    void start(){
        for(uint64_t i=0;i<this->iterations;i++){
            weights = weights - 
        }
    }
    
  private:
    Matrix* weights;
    Matrix* rawData;
    uint64_t iterations;
};


int main(){
    Matrix first(std::vector<std::vector<double>>{{1,2,3},{4,5,6},{7,8,9}});
    Matrix second(std::vector<std::vector<double>>{{1,2},{2,3},{3,4}});
    Matrix final = first * second;
    final.print();
    return 0;
}




