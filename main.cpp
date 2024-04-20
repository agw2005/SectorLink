#include <iostream>
#include <Eigen/Dense>
#include <vector>

void RREF(Eigen::MatrixXd& matrix) {
    int lead = 0;
    int rowCount = matrix.rows();
    int colCount = matrix.cols();

    for(int r = 0; r < rowCount; ++r){
        if (colCount <= lead)
            return;

        int i = r;

        while (matrix(i, lead) == 0) {
            ++i;
            if (rowCount == i) {
                i = r;
                ++lead;
                if (colCount == lead)
                    return;
            }
        }

        if (i != r)
            matrix.row(i).swap(matrix.row(r));

        double lv = matrix(r, lead);
        if (lv != 0)
            matrix.row(r) /= lv;

        for (i = 0; i < rowCount; ++i) {
            if (i != r) {
                double multiplier = matrix(i, lead);
                matrix.row(i) -= multiplier * matrix.row(r);
            }
        }
        ++lead;
    }
}

int main() {
    int sectorPopulation, cols, rows;
    double tempOutput;
    std::string tempName;
    std::vector<std::string> sectors;

    std::cout<<"How many sectors are there?\n";
    std::cin>>sectorPopulation;

    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> initialMatrix(sectorPopulation,sectorPopulation);

    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> identity(sectorPopulation, sectorPopulation);
    identity = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>::Identity(sectorPopulation, sectorPopulation)*100;

    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> resultMatrix(sectorPopulation, sectorPopulation);

    for(int i = 0 ; i < sectorPopulation ; i++){
        std::cout<<"What is the name of sector "<<i+1<<" ?\n";
        std::cin>>tempName;
        sectors.push_back(tempName);
    }

    cols = 0;
    rows = 0;
    for(std::string s : sectors){
        for(std::string ss : sectors){
            std::cout<<"What is the output from "<<s<<" to "<<ss<<" ? (in %)\n";
            std::cin>>tempOutput;
            initialMatrix(rows,cols) = tempOutput;
            rows++;
        }
        cols++;
        rows = 0;
    }

    resultMatrix = identity-initialMatrix;

    RREF(resultMatrix);

    //std::cout<<std::endl;
    //
    //std::cout<<initialMatrix;
    //std::cout<<std::endl;
    //
    //std::cout<<resultMatrix;
    //std::cout<<std::endl;
    //
    //RREF(resultMatrix);
    //
    //std::cout<<resultMatrix;
    //std::cout<<std::endl;

    int scalar = -1;
    if(sectorPopulation > 4){scalar*=-1;}

    for(int i = 0 ; i < sectorPopulation-1 ; i++) {
        for(int ii = 0 ; ii < sectorPopulation ; ii++) {
            if(resultMatrix(i, ii) == 0){
                std::cout<<resultMatrix(i,ii)<<" product from sector "<<sectors[ii]<<" is equal to "<<
                         scalar*resultMatrix(i, sectorPopulation-1)<<" product from sector "<<sectors[sectorPopulation-1]
                         <<std::endl;
                break;
            }
        }
    }
}