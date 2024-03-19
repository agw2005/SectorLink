#include <iostream>
#include <Eigen/Dense>

int main() {
    int sectorPopulation, cols, rows;
    double tempOutput;
    std::string tempName;
    std::vector<std::string> sectors;

    std::cout<<"How many sectors are there?\n";
    std::cin>>sectorPopulation;

    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> initialMatrix(sectorPopulation,sectorPopulation);
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> identity(sectorPopulation, sectorPopulation);
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> resultMatrix(sectorPopulation, sectorPopulation);
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> eachSectorValue(sectorPopulation, sectorPopulation);
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> zeroes(sectorPopulation, 1);
    zeroes.setZero();

    identity = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>::Identity(sectorPopulation, sectorPopulation)*100;

    for(int i = 0 ; i < sectorPopulation ; i++){
        std::cout<<"What is the name of sector "<<i+1<<" ?\n";
        std::cin>>tempName;
        sectors.push_back(tempName);
    }

    cols = 0;
    rows = 0;
    for(auto& s : sectors){
        for(auto& ss : sectors){
            std::cout<<"What is the output from "<<s<<" to "<<ss<<" ? (in %)\n";
            std::cin>>tempOutput;
            initialMatrix(rows,cols) = tempOutput;
            rows++;
        }
        cols++;
        rows = 0;
    }

    resultMatrix = identity-initialMatrix;

    // TODO: HOW TO DO RREF

    //Eigen::FullPivLU<Eigen::MatrixXd> lu(resultMatrix);
    //Eigen::MatrixXd rref = lu.matrixLU().triangularView<Eigen::Upper>().solve(lu.permutationP() * resultMatrix);

    std::cout<<std::endl<<resultMatrix<<std::endl;
    //std::cout<<std::endl<<rref<<std::endl;
}