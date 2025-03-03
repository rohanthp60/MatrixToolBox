#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include "Numrero.hpp"
#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
    private:
    std::vector < std::vector <Num> > A, original;           //A is our most useful 2D array, it will used to for entire operations     
    Num factor;                                        //array original is there incase we need the original matrix, A will get changed throughout the program
    int row, col;
    int sign = 1;
    bool Factor(int r, int in) {                         // While performing the row operations, to reduce a matrix to upper triangular,
        int i, j;                                         // this function finds the factor, for example like if R1 is pivot row
        if(A[r][r] == 0) {                          // we have to perform R2 = R2 - xR1, where x is some number, this fundction finds that
            for(i = r + 1; i < row; i++) {                  // x with necessary steps,
                if(!(A[i][r] == 0)) {
                    sign *= -1;
                    for(j = 0; j < col; j++) {
                        Num::swap(A[i][j], A[r][j]);
                    }

                    Num tm = (A[in][r] / A[r][r]);
                    factor = tm;
                    return true;
                }
            }
            return false;
        }
        else {
            Num tmp = (A[in][r] / A[r][r]);
            factor = tmp;
            return true;
        }
    }
    void identize() {                                    //sets A as identity matrix
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                if(i == j) {
                    A[i][j] = Num(1);
                }
                else {
                    A[i][j] = Num(0);
                }
            }
        }
    }
    void transpose() {  
        int i, j;
        if(row == col) {
            for(i = 0; i < row - 1; i++) {
                for(j = i + 1; j < col; j++) {
                    Num::swap(A[i][j],A[j][i]);
                }
            }
        }
        else {
            std::vector <std::vector<Num>> tm;         //create new empty tranpose matrix
            tm.resize(col, std::vector<Num>(row));       //copy the elements to this from original
            for(i = 0; i < col; i++) {                   //resize the original as transpose then again copy that transpose
                for(j =0 ; j < row; j++) {                 // to this original matrix
                    tm[i][j] = A[j][i];
                }
            }
            for(i = 0; i < row; i++) {A[i].resize(row);}
            A.resize(col, std::vector<Num>(row));
            for(i = 0; i < col; i++) {
                for(j = 0; j < row; j++) {
                    A[i][j] = tm[i][j];
                }
            }
        }
    }
    void echelon() {                              //this function transforms the matrix to echelon, or upper trianglular
        int i, j, k;
        for(i = 0; i < row and i < col; i++) {
            for(j = i + 1; j < row; j++) {
                if(Factor(i, j)) {               //Factor() will return false if it couldn't find pivot
                    for(k = i; k < col; k++) {
                        Num subtrahend = (factor * A[i][k]);
                        A[j][k] -= subtrahend;
                    }
                }
                else {break;}
            }
        }
    }
    void reduced_echelon() {                  //to transform the matrix to diagnol, this is incomplete, won't work if the matrix is singular
        int i, j, k;
        echelon();
        for(i = (row < col) ? (row - 1) : (col - 1); i > 0; i--) {
            for(j = i - 1; j >= 0; j--) {
                if(Factor(i, j)) {
                    for(k = 0; k < col; k++) {
                        Num subtrahend = (factor * A[i][k]);
                        A[j][k] -= subtrahend;
                    }
                }
                else {break;}
            }
        }
        for(i = 0; i < row; i++) {
            Num fct(A[i][i]);
            for(j = 0; j < col; j++) {
                A[i][j] /= fct;
            }
        }
    }
    bool zeroRow(int r) {                        //checks if the row is zero or not
        int i;
        for(i = 0; i < col; i++) {
            if(A[r][i] != 0) {
                return false;
            }
        }
        return true;
    }
    void replaceRow(int r1, int r2) {
        int i;
        for(i = 0; i < col; i++) {
            Num::swap(A[r1][i], A[r2][i]);
        }
    }

    void settleZeroRows() {                 //after echelon transformation, makes sure all zero rows are at the bottom
        int i, j;
        bool zerorows = true;
        for(i = row - 1; i >= 0; i--) {
            if(!zeroRow(i)) {
                for(j = i - 1; j >= 0; j--) {
                    if(zeroRow(j)) {
                        replaceRow(i, j);
                        break;
                    }
                }
            }
        }
    }
    void Reset() {
        for(int i = 0; i < row; i++) {A[i].resize(col);}     //Make A back to originial
        A.resize(row);
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                A[i][j] = original[i][j];
            }
        }
    }
    
    public:
    Matrix() {
    }
    void setup(const int& r, const int& c) {
        row = r, col = c;
        A.resize(row, std::vector<Num>(col));
        original.resize(row, std::vector<Num>(col));
    }
    Matrix(std::vector < std::vector<Num> > m) {
        row = m.size(), col = m[0].size();
        A.resize(row, std::vector<Num>(col));
        original.resize(row, std::vector<Num>(col));
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                A[i][j] = m[i][j];
                original[i][j] = m[i][j];
            }
        }
        sign = 1;
    }
    Matrix(const Matrix& mat) {                                //hasn't been used but incase we need it
        row = mat.row, col = mat.col;
        A.resize(mat.row, std::vector <Num>(mat.col));
        original.resize(mat.row, std::vector <Num>(mat.col));

        for(int i = 0; i < mat.row; i++) {
            for(int j = 0; j < mat.col; j++) {
                A[i][j] = mat.A[i][j];
                original[i][j] = mat.A[i][j];
            }
        }
    }

    bool isSquare() {return (row == col);}
    Matrix Echelon() {
        Reset();
        echelon();
        settleZeroRows();
        return Matrix(A);
    }

    Matrix Inverse() {
        int i, j;
        Reset();
        for(i = 0; i < row; i++) {
            A[i].resize(row * 2);
            for(j = row; j < row * 2; j++) {
                if(j == row + i) {A[i][j] = Num(1);}
                else {A[i][j] = Num(0);}
            }
        }
        col *= 2;
        reduced_echelon();
        for(i = 0; i < row; i++) {
            for(j = 0; j < row; j++) {
                Num::swap(A[i][j], A[i][j + row]);
            }
            A[i].resize(row);
        }
        col /= 2;
        return Matrix(A);
    }

    Matrix Invert() {
        Reset();
        std::vector <std::vector <Num> > temp;
        if(row > 1) {
            temp.resize(row, std::vector<Num>(col));

            Num deter = Det();
            for(int i = 0; i < row; i++) {
                for(int j = 0;  j < col; j++) {
                    temp[j][i] = CoFactor(i, j) / deter;
                    if((i + j) % 2 != 0) {
                        temp[j][i] = temp[j][i] * Num(-1);
                    }
                }
            }
            return Matrix(temp);
        }
        else {
            return Inverse();
        }
    }

    std::vector<Num> eigen() {
        double real, imag;
        std::vector<Num> EigenValues;
        Eigen::Matrix<std::complex<double>, Eigen::Dynamic, Eigen::Dynamic> eMat(row, col);
        Reset();

        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                eMat.coeffRef(i, j) = A[i][j].toComplex();
            }
        }

        Eigen::ComplexEigenSolver<Eigen::MatrixXcd> eigenSolver(eMat);
        Eigen::VectorXcd eigenvalues = eigenSolver.eigenvalues();

        for(int i = 0; i < eigenvalues.size(); i++) {
            real = eigenvalues[i].real();
            imag = eigenvalues[i].imag();

            EigenValues.push_back(Num(real, imag));
        }
        return EigenValues;
    }

    bool isSingular() {
        return Det() == 0;
    }

    Matrix ReducedEchelon() {
        Reset();
        reduced_echelon();
        return Matrix(A);
    }

    Num& getfrom(int a, int b) {
        return A[a][b];
    }

    int getRow() {return row;}
    int getColumn() {return col;}
    void setElement(const int& r, const int& c, const std::string& data) {
        A[r][c] = Num(data);
        original[r][c] = Num(data);
    }
    std::string getElement(const int&r, const int& c) const{
        return A[r][c].ToString();
    }
    std::string getOri(const int&r, const int& c) const{
        return original[r][c].ToString();
    }
    int Rank() {
        Reset();
        int non_zero_rows = 0;
        bool non_zero = false;
        echelon();
        settleZeroRows();
        for(int i = 0; i < row; i++, non_zero = false) {         //to count non zero rows
            for(int j = 0; j < col; j++) {
                if(!(A[i][j] == 0)) {
                    non_zero = true;
                    break;
                }
            }
            if(non_zero) {non_zero_rows++;}
            else {break;}
        }
        return non_zero_rows;
    }

    Matrix Transpose() {                                     
        Reset();
        transpose();
        return Matrix(A);
    }

    Matrix operator+(Matrix& M) {
        Reset();
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                A[i][j] = A[i][j] + M.A[i][j];
            }
        }
        return Matrix(A);
    }

    Matrix operator-(Matrix& M) {
        Reset();
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                A[i][j] = A[i][j] - M.A[i][j];
            }
        }
        return Matrix(A);
    }

    Matrix operator*(Matrix& M) {
        Reset();
        Num s(0);
        Matrix m(A);
        for(int i = 0; i < row; i++) {
            A[i].resize(M.col);
            for(int j = 0; j < M.col; j++) {
                for(int k = 0; k < col; k++) {
                    s += m.A[i][k] * M.A[k][j];
                }
                A[i][j] = s;
                s = 0;
            }
        }
        return Matrix(A);
    }

    Matrix pow(int n) {
        Reset();
        Matrix a = Matrix(A);
        identize();   
        Matrix b = Matrix(A);              //set A as identity mattrix
        for(int i = 0; i < n; i++) {
            b = b * a;
        } 
        return Matrix(b);
    }

    Matrix operator*(const Num& x) {
        Reset();
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                A[i][j] = A[i][j] * x;
            }
        }
        return Matrix(A);
    }

    Matrix operator/(const Num& x) {
        Reset();
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                A[i][j] = A[i][i] / x;
            }
        }
        return Matrix(A);
    }

    Num Det() {
        if(row == col) {
            Reset();
            echelon();
            Num det(1);
            for(int i = 0; i < row; i++) {
                det *= A[i][i];
            }
            if(sign == -1) {
                -det;
            }
            return Num(det.real(), det.imag());
        }
        else {
            std::cout << "Not possible to calucalate detminants!\n";
            return 0;
        }
    }

    Num CoFactor(const int& x, const int& y) {
        Reset();
        std::vector <std::vector <Num>> temp;
        temp.resize(row - 1);
        int r = 0, c = 0;
        for(int i = 0; i < row; i++) {
            if(i != x) {
                temp[r].resize(col - 1);
                c = 0;
                for(int j = 0; j < col; j++) {
                    if(j != y) {
                        temp[r][c] = A[i][j];
                        c++;
                    }
                }
                r++;
            }
        }
        return Matrix(temp).Det();
    }

    bool isComplex() {
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                if(A[i][j].isComplex()) {
                    return true;
                } 
            }
        }
        return false;
    }

    int SolutionNature() {
        Reset();
        std::vector <std::vector <Num>> temp;
        temp.resize(row, std::vector <Num>(col - 1));
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col - 1; j++) {
                temp[i][j] = A[i][j];
            }
        }
        Matrix m(temp);
        if(m.Rank() == Rank()) {
            if(Rank() == row) {
                return 1;          //Unique solution exists
            }
            else {
                return 2;         //Infinite solutions exist
            }
        }
        else {
            return 3;             //No solution
        }
    }

    void display() {                        //just for testing purposes
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                std::cout << A[i][j].ToString() << "  ";
            }
            std::cout << "\n";
        }
        std::cout << "\n\n";
    }
};
#endif