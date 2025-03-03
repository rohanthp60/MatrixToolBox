#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <Eigen/Dense>
#ifndef NUMBER_H
#define NUMBER_H


class Num {
    private:
    double re, im;

    public:
    Num(){re = 0, im = 0;}
    Num(const double& x) {
        re = x;
        im = 0;
    }
    Num(const double& x, const double& y) {
        re = x;
        im = y;
    }
    Num(const int& x) {
        re = x;
        im = 0;
    }
    Num(const int& x, const int& y) {
        re = x;
        im = y;
    }
    Num(const Num& N) {
        re = N.re;
        im = N.im;
    }
    Num(const std::string& input) {
        int i = input.length() - 1;
        std::string real = "", imag = "", sign = "";
        if(input[i] == 'i') {
            i--;
            for(; (input[i] != '+' and input[i] != '-') and i >= 0; i--) {
                imag = input[i] + imag;
            }
            if(input[i+1] == 'i') {
                imag = "1" + imag;
            }
            sign = (i >= 0) ? (sign + input[i--]) : (sign + '+');
        }
        for(; i >= 0; i--) {
            real = input[i] + real;
        }
        imag = (imag.length() > 0) ? ((sign == "-") ? (sign + imag) : (imag)) : ("0");
        real = (real.length() > 0) ? (real) : ("0");

        re = std::stod(real);
        im = std::stod(imag);
    }

    std::string ToString() const{                                       //the string parser
        double x = (re > 0) ? re : (-re), y = (im > 0) ? im : (-im);
        std::string r, i;
        std::stringstream ss, sa;
        ss << std::fixed << std::setprecision(3) << x;
        r = ss.str();
        sa << std::fixed << std::setprecision(3) << y;
        i = sa.str();
        std::string str = "", signI, signR;
        signR = (re < 0) ? ("-") : ("");
        signI = (im < 0) ? ("-") : ("+");
        if(re != 0 and im != 0) {
            str = str + signR + r + signI + i + "i";
        }
        else if(re == 0 and im != 0) {
            signI = (im < 0) ? ("-") : ("");
            str = str + signI + i + "i";
        }
        else if(re != 0 and im == 0) {
            str = str + signR + r;
        }
        else {
            str = "0";
        }
        return str;
    }

    void operator=(const Num& x) {
        re = x.re;
        im = x.im;
    }
    double abs() const{
        return ((re * re) + (im * im));
    }
    
    Num operator-() {
        -re, -im;
        return *this;
    }

    Num operator+(const Num& N) {
        return Num(re + N.re, im + N.im);
    }
    Num operator-(const Num& N) {
        return Num(re - N.re, im - N.im);
    }
    Num operator*(const Num& N) {
        return Num((re * N.re) - (im * N.im), (re * N.im) + (im * N.re));
    }
    Num operator/(const Num& N) {
        return Num(((re * N.re) + (im * N.im)) / (N.abs()), ((im * N.re) - (re * N.im)) / (N.abs()));
    }

    double real() const{return re;}
    double imag() const{return im;}
    void operator+=(const Num& N) {
        *this = ((*this) + N);
    }
    void operator-=(const Num& N) {
        *this = ((*this) - N);
    }
    void operator*=(const Num& N) {
        *this = ((*this) * N);
    }
    void operator/=(const Num& N) {
        *this = ((*this) / N);
    }
    bool operator==(const Num& a) {return (re == a.re and im == a.im);}
    bool operator==(const double& F) {return (re == F) and im == 0;}
    bool operator==(const int& F) {return re == F and im == 0;}
    bool operator!=(const Num& a) {return (re != a.re or im != a.im);}
    bool operator!=(const double& F) {return (re != F) or (im != 0);}
    bool operator!=(const int& F) {return (re != F) or (im != 0);}
    bool isZero() {
        return re == 0 and im == 0;
    }
    bool isComplex() {
        return im != 0;
    }
    void display() {        //just for testing purposes
        std::cout << ToString() << "  ";
    }
    std::complex<double> toComplex() {
        return std::complex<double>(re, im);
    }
    static void swap(Num& a, Num& b) {
        Num sw;
        sw = a;
        a = b;
        b = sw;
    }
};

#endif