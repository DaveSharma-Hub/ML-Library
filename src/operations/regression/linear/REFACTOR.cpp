#include <iostream>
#include <vector>
#include <cstdint>
#include <climits>
#include <cmath>


class Matrix{
  public:
    Matrix(){};
    
    Matrix(std::vector<std::vector<double>> input_): array(input_){};
    
    Matrix operator*(Matrix a){
        return Matrix(this->matrixMult(
            this->array,
            a.getArray()
        ));
    }
    Matrix operator*(double value){
        return Matrix(this->doubleMult(
            this->array,
            value
        ));
    }
    Matrix operator+(Matrix a){
        return Matrix(this->matrixAddition(
            this->array,
            a.getArray()
        ));
    }
    Matrix operator-(Matrix a){
        return Matrix(this->matrixSubtraction(
            this->array,
            a.getArray()
        ));
    }
    
    // To use this the matrix has to come first
    Matrix operator+(double value){
        return Matrix(this->doubleAddition(
            this->array,
            value
        ));
    }
    Matrix operator-(double value){
        return Matrix(this->doubleSubtraction(
            this->array,
            value
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
    
    void transpose(){
        std::vector<std::vector<double>> finalMatrix;
        
        for(int i=0;i<this->array[0].size();i++){
            std::vector<double> arr;
            for(int j=0;j<this->array.size();j++){
                arr.push_back(this->array[j][i]);
            }
            finalMatrix.push_back(arr);
        }
        this->array = finalMatrix;
    }
    
    Matrix copy(){
        std::vector<std::vector<double>> copy;
        for(std::vector<double> arr: this->array){
            std::vector<double> row;
            for(double i: arr){
                row.push_back(i);
            }
            copy.push_back(row);
        }
        Matrix copyMatrix(copy);
        return copyMatrix;
    }
    
    void Normalize(){
        double max = INT_MIN;
        for(std::vector<double> row:this->array){
            for(double v: row){
                if(v>max){
                    max = v;
                }
            }
        }
        for(int i=0;i<this->array.size();i++){
            for(int j=0;j<this->array[i].size();j++){
                array[i][j] = array[i][j]/max;
            }
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
    std::vector<std::vector<double>> matrixAddition(std::vector<std::vector<double>>& first, std::vector<std::vector<double>>& second){
        if(first.size() != second.size() || first[0].size() != second[0].size()){
           // throw error todo later on 
        }
        std::vector<std::vector<double>> finalMatrix;
        int rows = first.size(); //same as second.size()
        int cols = first[0].size(); //same as second[0].size()
        for(int i=0;i<first.size();i++){
            std::vector<double> row;
            for(int j=0;j<first[i].size();j++){
                row.push_back(first[i][j] + second[i][j]);
            }
            finalMatrix.push_back(row);
        }
        return finalMatrix;
    }
    std::vector<std::vector<double>> doubleAddition(std::vector<std::vector<double>>& first, double value){
        std::vector<std::vector<double>> finalMatrix;
        for(int i=0;i<first.size();i++){
            std::vector<double> row;
            for(int j=0;j<first[i].size();j++){
                row.push_back(first[i][j]+value);
            }
            finalMatrix.push_back(row);
        }
        return finalMatrix;
    }
    std::vector<std::vector<double>> doubleMult(std::vector<std::vector<double>>& first, double value){
        std::vector<std::vector<double>> finalMatrix;
        for(int i=0;i<first.size();i++){
            std::vector<double> row;
            for(int j=0;j<first[i].size();j++){
                row.push_back(first[i][j]*value);
            }
            finalMatrix.push_back(row);
        }
        return finalMatrix;
    }
    std::vector<std::vector<double>> doubleSubtraction(std::vector<std::vector<double>>& first, double value){
        std::vector<std::vector<double>> finalMatrix;
        for(int i=0;i<first.size();i++){
            std::vector<double> row;
            for(int j=0;j<first[i].size();j++){
                row.push_back(first[i][j] - value);
            }
            finalMatrix.push_back(row);
        }
        return finalMatrix;
    }
    
     std::vector<std::vector<double>> matrixSubtraction(std::vector<std::vector<double>>& first, std::vector<std::vector<double>>& second){
        if(first.size() != second.size() || first[0].size() != second[0].size()){
           // throw error todo later on 
        }
        std::vector<std::vector<double>> finalMatrix;
        int rows = first.size(); //same as second.size()
        int cols = first[0].size(); //same as second[0].size()
        for(int i=0;i<first.size();i++){
            std::vector<double> row;
            for(int j=0;j<first[i].size();j++){
                row.push_back(first[i][j] - second[i][j]);
            }
            finalMatrix.push_back(row);
        }
        return finalMatrix;
    }
    
};

class LinearRegression{
  public:
    LinearRegression(uint64_t iterations_, std::vector<std::vector<double>> initialWeights_, double learningRate_):iterations(iterations_), learningRate(learningRate_){
        Matrix weightMatrix(initialWeights_); 
        this->weights = weightMatrix;  
    }
    
    LinearRegression* initializeData(std::vector<std::vector<double>> data_, std::vector<std::vector<double>> output_){
        Matrix rawMatrix(data_);
        Matrix outputMatrix(output_);
        this->rawData = rawMatrix;
        this->output = outputMatrix;
        return this;
    }
    
    void normalizeAll(){
        weights.Normalize();
        rawData.Normalize();
        output.Normalize();
    }
    
    void start(){
        this->normalizeAll();
        Matrix transposedRawData = rawData.copy();
        transposedRawData.transpose();
        for(uint64_t i=0;i<this->iterations;i++){
            weights = weights - (((weights * transposedRawData) - output) * rawData) * 2 * this->learningRate; 
            weights.Normalize();
        }
    }
    
    double getAbsoluteError(){
        Matrix transposedRawData = rawData.copy();
        transposedRawData.transpose();
        Matrix diffMatrix = (weights * transposedRawData) - output;
        std::vector<std::vector<double>> data = diffMatrix.getArray();
        double error = 0;
        for(int i=0;i<data[0].size();i++){
            error += data[0][i]*data[0][i];
        }
        return sqrt(error);
    }
    double getPercentError(){
        Matrix transposedRawData = rawData.copy();
        transposedRawData.transpose();
        Matrix diffMatrix = (weights * transposedRawData) - output;
        std::vector<std::vector<double>> data = diffMatrix.getArray();
        std::vector<std::vector<double>> expected = output.getArray();
        
        double error = 0;

        for(int i=0;i<data[0].size();i++){
            double v = data[0][i]/expected[0][i];
            error += v<0 ? -1*v : v;
        }
        return sqrt(error);
    }
    
    Matrix& getWeights(){
        return this->weights;
    }
    
  private:
    Matrix weights;
    Matrix rawData;
    Matrix output;
    uint64_t iterations;
    double learningRate;
};


void testLearningRates(double initialLR, double delta, int steps, uint64_t iterations){
    
    double smallestLr = INT_MAX;
    double percentError = INT_MAX;
    double absoluteError = INT_MAX;
    
    for(double lr = initialLR;lr<initialLR + delta*steps;lr+=delta){
        LinearRegression pipeline(iterations, std::vector<std::vector<double>>{{1,1}},lr);
        pipeline.initializeData(std::vector<std::vector<double>>{{1,5},{2,8},{3,10},{4,12}},std::vector<std::vector<double>>{{7,12,11,15}})->start();
        // pipeline.getWeights().print();
        double pError = pipeline.getPercentError();
        double aError = pipeline.getAbsoluteError();
        if(aError < absoluteError && pError < percentError){
            smallestLr = lr;
            percentError = pError;
            absoluteError = aError;
        }
    }
    
    std::cout<<"--------\nLearing rate: "<<smallestLr<<std::endl;
        std::cout<<"Absolute: "<<absoluteError<<std::endl;
        std::cout<<"Percent: "<<percentError<<std::endl;
}

int main(){
    // Matrix first(std::vector<std::vector<double>>{{1,2,3},{4,5,6},{7,8,9}});
    // Matrix second(std::vector<std::vector<double>>{{1,2,3},{4,5,6},{7,8,9}});
    // Matrix third(std::vector<std::vector<double>>{{1,2,3},{4,5,6},{7,8,9}});
    // Matrix final = ((first) - ((first * second - first) * third));
    // final.transpose();
    // final.print();
    testLearningRates(1.9,0.005,1000,10000);
    
    return 0;
}




