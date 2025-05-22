#include <vector>
#include <stdint.h>
#include <stdexcept>
#include <cmath>

template <class DataType>
class Matrix{
    public:
        Matrix(uint32_t rows, uint32_t cols){
            this->rowCount = rows;
            this->colCount = cols;
            this->_createMatrix();
        }
        Matrix(uint32_t rows, uint32_t cols, uint32_t random){
            this->rowCount = rows;
            this->colCount = cols;
            this->_createMatrixWithRandom(random);
        }

        DataType get(int i, int j){
            if(this->_isValid(i,j)){
                return this->matrix[i][j];
            }
            throw std::invalid_argument("Out of range");
        }

        void set(int i, int j, DataType value){
            if(this->_isValid(i,j)){
                this->matrix[i][j] = value;
            }
        }

        uint32_t getRowCount(){
            return this->rowCount;
        }

        uint32_t getColCount(){
            return this->colCount;
        }

        Matrix<DataType>* mult(Matrix<DataType>* B){
            if(B == nullptr){
                throw std::invalid_argument("Null pointer argument");
            }
            if(this == B){
                throw std::invalid_argument("Cannot multiply itself without transpose operation first");
            }

            // Assuming this X B order
            uint32_t firstRowCount = this->getRowCount();
            uint32_t firstColCount = this->getColCount();

            uint32_t secondRowCount = B->getRowCount();
            uint32_t secondColCount = B->getColCount();

            if(firstColCount != secondRowCount){
                throw std::invalid_argument("First matrix col count != Second matrix row count");
            }

            Matrix<DataType>* newMatrix = new Matrix<DataType>(firstRowCount, secondColCount);
            for(uint32_t i=0;i<firstRowCount;i++){
                for(uint32_t j=0;j<secondColCount;j++){
                    DataType d1 = 0;
                    for(uint32_t z=0;z<firstColCount;z++){
                        d1 += this->get(i,z) * B->get(z,j);
                    }
                    newMatrix->set(i,j, d1);
                }
            }
            return newMatrix;
        }

        Matrix<DataType>* scalarMult(DataType value){
            uint32_t firstRowCount = this->getRowCount();
            uint32_t firstColCount = this->getColCount();

            Matrix<DataType>* newMatrix = new Matrix<DataType>(firstRowCount, firstColCount);
            for(int i=0;i<this->getRowCount();i++){
                for(int j=0;j<this->getColCount();j++){
                    DataType v = value * this->get(i,j);
                    newMatrix->set(i, j, v);
                }
            }
            return newMatrix;
        }

        Matrix<DataType>* add(Matrix<DataType>* A){
            // Assuming this + A;
            uint32_t firstRowCount = this->getRowCount();
            uint32_t firstColCount = this->getColCount();

            Matrix<DataType>* newMatrix = new Matrix<DataType>(firstRowCount, firstColCount);
            for(int i=0;i<this->getRowCount();i++){
                for(int j=0;j<this->getColCount();j++){
                    DataType v = this->get(i,j) + A->get(i,j);
                    newMatrix->set(i, j, v);
                }
            }
            return newMatrix;
        }
        Matrix<DataType>* sub(Matrix<DataType>* A){
            uint32_t firstRowCount = this->getRowCount();
            uint32_t firstColCount = this->getColCount();
            // Assuming this - A;
            Matrix<DataType>* newMatrix = new Matrix<DataType>(firstRowCount, firstColCount);
            for(int i=0;i<this->getRowCount();i++){
                for(int j=0;j<this->getColCount();j++){
                    DataType v = this->get(i,j) - A->get(i,j);
                    newMatrix->set(i, j, v);
                }
            }
            return newMatrix;
        }

        Matrix<DataType>* clone(){
            uint32_t rows = this->getRowCount();
            uint32_t cols = this->getColCount();
             Matrix<DataType>* newMatrix = new Matrix<DataType>(rows, cols);
            for(int i=0;i<rows;i++){
                for(int j=0;j<cols;j++){
                    newMatrix->set(i, j, this->get(i,j));
                }
            }
            return newMatrix;
        }

        DataType sum(){
            DataType total = 0;
            uint32_t rows = this->getRowCount();
            uint32_t cols = this->getColCount();

            for(int i=0;i<rows;i++){
                for(int j=0;j<cols;j++){
                    total += this->matrix[i][j]; 
                }
            }
            return total;
        }

        DataType mean(){
            DataType total = 0;
            int count = 0;
            uint32_t rows = this->getRowCount();
            uint32_t cols = this->getColCount();

            for(int i=0;i<rows;i++){
                for(int j=0;j<cols;j++){
                    total += this->matrix[i][j]; 
                    count++;
                }
            }
            return (DataType)(total/count);
        }

        Matrix<DataType>* power(int v){
            Matrix<DataType>* newMatrix = new Matrix<DataType>(this->getRowCount(), this->getColCount());
            uint32_t rows = this->getRowCount();
            uint32_t cols = this->getColCount();
            for(int i=0;i<rows;i++){
                for(int j=0;j<cols;j++){
                    DataType newValue = this->get(i,j);
                    newMatrix->set(i,j, pow(newValue, v));
                }
            }
            return newMatrix;
        }

        Matrix<DataType>* rowCollapse(){
            Matrix<DataType>* newMatrix = new Matrix<DataType>(1, this->getColCount());
            uint32_t rows = this->getRowCount();
            uint32_t cols = this->getColCount();
            for(int j=0;j<cols;j++){
                DataType sum = 0;
                for(int i=0;i<rows;i++){
                    sum += this->get(i,j);
                }
                newMatrix->set(0,j, sum);
            }
            return newMatrix;
        }

        void transpose(){
            std::vector<std::vector<DataType>>& m = this->matrix;
            for(int i=0;i<m.size();i++){
                for(int j=0;j<m[i].size();j++){
                    DataType first = m[i][j];
                    m[i][j] = m[j][i];
                    m[j][i] = first;
                }
            }
        }

        void print(){
            uint32_t rowCount = this->getRowCount();
            uint32_t colCount = this->getColCount();
            for(uint32_t i=0;i<rowCount;i++){
                for(uint32_t j=0;j<colCount; j++){
                    std::cout<<" "<<this->get(i,j);
                }
                std::cout<<"\n";
            }
        }

    private:
        std::vector<std::vector<DataType>> matrix;
        uint32_t rowCount = 0;
        uint32_t colCount = 0;
        
        bool _isValid(int& i, int& j){
            return (( i>=0 && i<this->rowCount ) && ( j>=0 && j<this->colCount ));
        }

        void _createMatrix(){
            uint32_t rows = this->rowCount;
            uint32_t cols = this->colCount;
            for(uint32_t i=0;i<rows;i++){
                std::vector<DataType> col;
                for(uint32_t j=0; j<cols; j++){
                    col.push_back(0);
                }
                matrix.push_back(col);
            }
        }
        void _createMatrixWithRandom(uint32_t random){
            uint32_t rows = this->rowCount;
            uint32_t cols = this->colCount;
            for(uint32_t i=0;i<rows;i++){
                std::vector<DataType> col;
                for(uint32_t j=0; j<cols; j++){
                    DataType value = (DataType)rand();
                    col.push_back(value);
                }
                matrix.push_back(col);
            }
        }
};
