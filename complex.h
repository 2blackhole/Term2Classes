//
// Created by Lenovo on 2025-02-10.
//
#ifndef COMPLEX_H
#define COMPLEX_H
#include <cmath>
#include <iostream>

class Complex {
private:
    double real, image;
    double abs, arg;

    void setAbs() {
        this->abs = std::sqrt(real * real + image * image);
    }
    void setArg () {
        this->arg = std::atan2(image, real);
    }
    void Init() {
        setAbs();
        setArg();
    }

public:
    Complex() {
        this->real = 0.0;
        this->image = 0.0;
        Init();
    }
    explicit Complex(const double real) {
        this->real = real;
        this->image = 0.0;
        Init();
    }

    Complex(const double real, const double image) {
        this->real = real;
        this->image = image;
        Init();
    }

    void setReal(double real) {
        this->real = real;
        Init();
    }

    void setImage(double image) {
        this->image = image;
        Init();
    }

     double getReal() const {
        return this->real;
    }

    double getImage() const {
        return this->image;
    }

    double getAbs() const {
        return this->abs;
    }

    double getArg() const {
        return this->arg;
    }

    Complex getConj() const {
        return Complex(this->real, -1 * this->image);
    }

    Complex operator+ (Complex b) {
        return Complex(this->real + b.getReal(), this->image + b.getImage());
    }

    Complex operator+ (double b) {
        return Complex(this->real + b, this->image);
    }
    Complex operator- (Complex b) {
        return Complex(this->real - b.getReal(), this->image - b.getImage());
    }
    Complex operator- (double b) {
        return Complex(this->real - b, this->image);
    }
    Complex operator* (Complex b) {
        return Complex(this->real * b.getReal() - this->image * b.getImage(), this->image * b.getReal() + this->real * b.getImage());
    }

    Complex operator* (double b) {
        return Complex(this->real * b, this->image * b);
    }

    Complex operator/ (Complex b) {
        return Complex((this->real * b.getReal() + this->image * b.getImage())/(b.getReal() * b.getReal() + b.getImage() * b.getImage()), (this->image * b.getReal() - this->real * b.getImage())/(b.getReal() * b.getReal() + b.getImage() * b.getImage()));
    }

    Complex operator/ (double b) {
        return Complex(this->real / b, this->image / b);
    }

    // += -= *= /= operators

    void operator += (Complex b) {
        this->real = this->real + b.getReal();
        this->image = this->image + b.getImage();
    }

    void operator -= (Complex b) {
        this->real = this->real - b.getReal();
        this->image = this->image - b.getImage();
    }

    void operator *= (Complex b) {
        this->real = this->real * b.getReal() - this->image * b.getImage();
        this->image = this->image * b.getReal() + this->real * b.getImage();
    }

    void operator /= (Complex b) {
        this->real = (this->real * b.getReal() + this->image * b.getImage())/(b.getReal() * b.getReal() + b.getImage() * b.getImage());
        this->image = (this->image * b.getReal() - this->real * b.getImage())/(b.getReal() * b.getReal() + b.getImage() * b.getImage());
    }

    void operator += (double b) {
        this->real = this->real + b;
    }

    void operator -= (double b) {
        this->real = this->real - b;
    }

    void operator *= (double b) {
        this->real = this->real * b;
        this->image = this->image * b;
    }

    void operator /= (double b) {
        this->real = this->real / b;
        this->image = this->image / b;
    }

    void set_with_abs_and_arg (double const abs, double const arg) {
        this->real = std::cos(arg) * abs;
        this->image = std::sin(arg) * abs;
        Init();
    }


    friend std::ostream & operator << (std::ostream& out, const Complex a) {
        out << a.getReal() << " + i * (" << a.getImage() << ")" << std::endl;
        return out;
    }

    friend std::istream & operator >> (std::istream& in, Complex& a) {
        in >> a.real >> a.image;
        return in;
    }

    bool operator==(const Complex & b) const {
        if (this->real == b.getReal() && this->image == b.getImage()) {
            return true;
        }
        return false;
    }

    bool operator!=(const Complex & b) const {
        if (this->real == b.getReal() && this->image == b.getImage()) {
            return false;
        }
        return true;
    }


};

#endif //COMPLEX_H
