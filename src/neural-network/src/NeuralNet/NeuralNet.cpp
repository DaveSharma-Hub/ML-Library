#include <vector>
#include <stdint.h>
#include <cstdlib>
#include <stdexcept>
#include <utility>
#include "../Tensor/Matrix.cpp"
#include "../Utils/Utils.cpp"

template <class DataType>
class NeuralNet{
    public:
        NeuralNet(std::vector<int> layerCount, uint seed, DataType learningRate, uint32_t epoch){
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
            for(uint32_t i=0;i<epoch;i++){
                std::vector<Matrix<DataType>*> fwd = this->_forwardPropagation();
                DataType err = this->_error(fwd[fwd.size()-1]);

                std::cout<<"Loss "<<err<<std::endl;

                std::vector<std::pair<Matrix<DataType>*,Matrix<DataType>*>> back = this->_backPropagation(fwd);

                this->_updateWeights(back);
            }
        }
        
    private:
        uint randSeed;
        DataType learningRate;
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

        std::vector<Matrix<DataType>*> _forwardPropagation(){
            Matrix<DataType>* in = this->input;
            std::vector<Matrix<DataType>*> feedFwd;
            for(int i=0; i<layerWeights.size(); i++){
                Matrix<DataType>* weight = layerWeights[i];
                Matrix<DataType>* bias = weightBias[i];
                Matrix<DataType>* tmp = this->_individualFwdPropagation(in, weight, bias);
                Matrix<DataType>* hiddenLayerNew = this->_sigmoid(tmp);
                feedFwd.push_back(hiddenLayerNew);
                in = hiddenLayerNew;
            }
            return feedFwd;
        }

        DataType _error(Matrix<DataType>* finalOutput){
            Matrix<DataType>* diff = this->output->sub(finalOutput);
            Matrix<DataType>* squared = diff->power(2);
            return 0.5 * squared->mean();
        }

        std::vector<std::pair<Matrix<DataType>*,Matrix<DataType>*>> _backPropagation( std::vector<Matrix<DataType>*> fwd){

            std::vector<std::pair<Matrix<DataType>*,Matrix<DataType>*>> output;
            int length = fwd.size();
            Matrix<DataType>* prevDelta = fwd[length-1]->sub(this->output);

            /*
                dA2 = A2 - Y
                dZ2 = dA2 * sigmoid_derivative(A2)
                dW2 = A1.T @ dZ2
                db2 = np.sum(dZ2, axis=0, keepdims=True)

                dA1 = dZ2 @ W2.T
                dZ1 = dA1 * sigmoid_derivative(A1)
                dW1 = X.T @ dZ1
                db1 = np.sum(dZ1, axis=0, keepdims=True)
            
                W2 -= lr * dW2
                b2 -= lr * db2
                W1 -= lr * dW1
                b1 -= lr * db1
            */

            for(int i=length-1;i>=0;--i){
                Matrix<DataType>* current = fwd[i];
                Matrix<DataType>* prev = i == 0 ? prev = this->input  : fwd[i-1];

                Matrix<DataType>* cloned = this->layerWeights[i]->clone();
                cloned->transpose();
                Matrix<DataType>* delta = prevDelta->mult(cloned); 

                if( i == length-1){
                    delta = prevDelta;
                }

                Matrix<DataType>* diff = delta->mult(this->_sigmoidDerivative(current));

                Matrix<DataType>* prevCloned = prev->clone();
                prevCloned->transpose();
                Matrix<DataType>* weightDiff = prevCloned->mult(diff);
                Matrix<DataType>* biasDiff = diff->rowCollapse();

                std::pair<Matrix<DataType>*,Matrix<DataType>*> weightBiasPair = std::make_pair(weightDiff, biasDiff);
                output.push_back(weightBiasPair);

                prevDelta = diff;
            }

            return output;
        }

        void _updateWeights(std::vector<std::pair<Matrix<DataType>*,Matrix<DataType>*>> diff){
            int length = diff.size();
            for(int i=0;i<length;i++){
                Matrix<DataType>* weightDiff = diff[i].first;
                Matrix<DataType>* biasDiff = diff[i].second;

                Matrix<DataType>* currentWeight = this->layerWeights[i];
                Matrix<DataType>* currentBias = this->weightBias[i];

                this->layerWeights[i] = currentWeight->sub(weightDiff->scalarMult(this->learningRate));
                this->weightBias[i] = currentBias->sub(biasDiff->scalarMult(this->learningRate));
            }
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