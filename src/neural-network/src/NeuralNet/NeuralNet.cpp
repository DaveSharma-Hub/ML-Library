#include <vector>
#include <stdint.h>
#include <cstdlib>
#include <stdexcept>
#include "../Tensor/Matrix.cpp"
#include "../Utils/Utils.cpp"

template <class DataType>
class NeuralNet{
    public:
        NeuralNet(std::vector<int> layerCount, uint seed, double learningRate, uint32_t epoch){
            if(layerCount.size() <=0 ){
                throw std::invalid_argument("First layer count argument must be greater than 0");
            }

            for(int i : layerCount){
                if(i<=0){
                    throw std::invalid_argument("All layer count value must be greater than 0");
                }
            }
            
            this->learningRate = learningRate;
            this->epoch = epoch;
            this->layerCount = layerCount;
            this->randSeed = seed;
            
            this->_initializeLayers();
            this->_setRandomBias();
        }
 
        NeuralNet<DataType>* setInputOutput(Matrix<DataType>* input, Matrix<DataType>* output){
            // if(input->getRowCount() != layerCount[0]){
            //     throw std::invalid_argument("Input matrix must match layer count input size");
            // }
            // TODO error handling
            // if(ouput->get() != layerCount[0]){
            //     throw std::invalid_argument("Input matrix must match layer count input size");
            // }
            this->input = input;
            this->output = output;
            return this;
        }   

        void start(){
            // for(uint32_t i=0;i<epoch;i++){
            //     Matrix<DataType>* fwd = this->_forwardPropagation();
            //     Matrix<DataType>* err = this->_error(fwd);
            //     std::vector<Matrix<DataType>*> back = this->_backPropagation(err, fwd);
            //     this->_updateWeights(back[0], back[1]);
            // }
        }
        
    private:
        uint randSeed;
        double learningRate;
        uint32_t epoch;
        std::vector<int> layerCount;
        std::vector<Matrix<DataType>*> layerWeights;
        std::vector<Matrix<DataType>*> weightBias;
        Matrix<DataType>* input;
        Matrix<DataType>* output;

        Matrix<DataType>* _individualFwdPropagation(Matrix<DataType>* A, Matrix<DataType>* B, Matrix<DataType>* bias){
            Matrix<DataType>* tmp = A->mult(B);
            return tmp->add(bias);
        }

        Matrix<DataType>* _sigmoid(Matrix<DataType>* m){
            Matrix<DataType>* matrix = m->clone();
            uint32_t rows = matrix->getRowCount();
            uint32_t cols = matrix->getColCount();
            for(int i=0;i<rows;i++){
                for(int j=0;j<cols;j++){
                    DataType value = matrix->get(i,j);
                    matrix->set(i, j, Utils::sigmoid<DataType>(value));
                }
            }
            return matrix;
        } 

        Matrix<DataType>* _sigmoidDerivative(Matrix<DataType>* m){
            Matrix<DataType>* matrix = m->clone();
            uint32_t rows = matrix->getRowCount();
            uint32_t cols = matrix->getColCount();
            for(int i=0;i<rows;i++){
                for(int j=0;j<cols;j++){
                    DataType value = matrix->get(i,j);
                    matrix->set(i, j, Utils::sigmoid_derivative<DataType>(value));
                }
            }
            return matrix;
        } 

        Matrix<DataType>* _forwardPropagation(){
            Matrix<DataType>* in = this->input;
            for(int i=0; i<layerWeights.size(); i++){
                Matrix<DataType>* weight = layerWeights[i];
                Matrix<DataType>* bias = weightBias[i];
                Matrix<DataType>* tmp = this->_individualFwdPropagation(in, weight, bias);
                in = this->sigmoid(tmp);
            }
            return in;
        }

        Matrix<DataType>* _error(Matrix<DataType>* finalOutput){
            return this->output->sub(finalOutput);
        }

        std::vector<Matrix<DataType>*> _backPropagation(Matrix<DataType>* error, Matrix<DataType>* finalOutput){
            std::vector<Matrix<DataType>*> output;
            Matrix<DataType>* sigDerivativeOutput = this->_sigmoidDerivative(finalOutput);
            Matrix<DataType>* first = error->mult(sigDerivativeOutput);

            return output;
        }

        Matrix<DataType>* _updateWeights(Matrix<DataType>* hiddenDerivative, Matrix<DataType>* outputDerivative){
            return nullptr;
        }

        void _setRandomBias(){
            uint random = randSeed;
             for(int i=0;i<layerCount.size()-1;i++){
                uint32_t row = layerCount[i];
                uint32_t col = layerCount[i+1];
                Matrix<DataType>* newMatrix = new Matrix<DataType>(row, col, (uint32_t)random);
                this->layerWeights.push_back(newMatrix);
            }
        }

        void _initializeLayers(){
            std::vector<int>& layerCount = this->layerCount;
            for(int i=0;i<layerCount.size()-1;i++){
                uint32_t row = layerCount[i];
                uint32_t col = layerCount[i+1];
                Matrix<DataType>* newMatrix = new Matrix<DataType>(row, col);
                this->layerWeights.push_back(newMatrix);
            }
        }
};