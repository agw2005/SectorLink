#include <iostream>
#include <Eigen/Dense>
#include <vector>

void scaleRow(Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>& matrix, int row, double scalar) {
    matrix.row(row) *= scalar;
}

void addMultipleOfRowToRow(Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>& matrix, int firstRow, int secondRow, double firstRowMultiplier) {
    matrix.row(secondRow) += firstRowMultiplier * matrix.row(firstRow);
}

int main() {
    int sectorPopulation, cols, rows;
    double tempOutput;
    std::string tempName;
    std::vector<std::string> sectors;

    //Input the matrix order (n x n)
    std::cout<<"How many sectors are there?\n";
    std::cin>>sectorPopulation;

    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> initialMatrix(sectorPopulation,sectorPopulation);

    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> identity(sectorPopulation, sectorPopulation);
    identity = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>::Identity(sectorPopulation, sectorPopulation)*100;

    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> resultMatrix(sectorPopulation, sectorPopulation);

    //Input the name of the sectors
    for(int i = 0 ; i < sectorPopulation ; i++){
        std::cout<<"What is the name of sector "<<i+1<<" ?\n";
        std::cin>>tempName;
        sectors.push_back(tempName);
    }

    //Input the matrix elements
    cols = 0;
    rows = 0;
    for(std::string& s : sectors){
        for(std::string& ss : sectors){
            std::cout<<"What is the output from "<<s<<" to "<<ss<<" ? (in %)\n";
            std::cin>>tempOutput;
            initialMatrix(rows,cols) = tempOutput;
            rows++;
        }
        cols++;
        rows = 0;
    }

    resultMatrix = identity-initialMatrix;

    //Turn each value in the matrix into double
    for(int i = 0 ; i < sectorPopulation ; i++){
        for(int ii = 0 ; ii < sectorPopulation ; ii++){
            resultMatrix(i,ii)*=1.0;
        }
    }

    //matrix(1,0) = row 2 column 1

    //Gauss-Jordan
    int leadingColumn = 0;
    int leadingRow = 0;
    for(int j = 1; j < sectorPopulation; j++){
        if(resultMatrix(leadingRow,leadingColumn) != 1){
            scaleRow(resultMatrix,leadingRow,1.0/resultMatrix(leadingRow,leadingColumn));
        }

        for(int i = 0 ; i < sectorPopulation ; i++){
            if(i != leadingRow) {
                addMultipleOfRowToRow(resultMatrix, leadingRow, i, -1 * resultMatrix(i, leadingColumn));
            }
        }
        leadingColumn++;
        leadingRow++;
    }

    for(int i = 0 ; i < sectorPopulation-1 ; i++) {
        for(int ii = 0 ; ii < sectorPopulation ; ii++) {
            if(resultMatrix(i, ii) == 1){
                std::cout<<resultMatrix(i,ii)<<" product from sector "<<sectors[ii]<<" is equal to "<<
                         -1.0*resultMatrix(i, sectorPopulation-1)<<" product from sector "<<sectors[sectorPopulation-1]
                         <<std::endl;
                break;
            }
        }
    }
}
