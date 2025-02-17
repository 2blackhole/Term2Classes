//
// Created by Lenovo on 2025-02-17.
//

#include "ArithmVectorN.h"


ArithmVectorN::ArithmVectorN() {
    for (size_t i = 0; i < N; i++) {
        coordinates[i] = 0.0;
    }
}

ArithmVectorN::ArithmVectorN(const double initCoordinates[10]) {
    for (size_t i = 0; i < N; i++) {
        coordinates[i] = initCoordinates[i];
    }
}

ArithmVectorN::ArithmVectorN(const ArithmVectorN &anotherVector) {
    for (size_t i = 0; i < N; i++) {
        coordinates[i] = anotherVector.coordinates[i];
    }
}

const double *ArithmVectorN::getCoordinates() const {
    return coordinates;
}

void ArithmVectorN::setCoordinates(const double coordinates[10]) {
    for (size_t i = 0; i < N; i++) {
        this->coordinates[i] = coordinates[i];
    }
}

double ArithmVectorN::getCoordinate(const int index) const {
    if (index >= 0 && index < N) {
        return coordinates[index];
    }
    throw std::out_of_range("Index out of range");
}

void ArithmVectorN::setCoordinate(const int index, const double value) {
    if (index >= 0 && index < N) {
        coordinates[index] = value;
    } else {
        throw std::out_of_range("Index out of range");
    }
}

ArithmVectorN ArithmVectorN::operator+(const ArithmVectorN& anotherVector) const {
    double res[N];
    for (size_t i = 0; i < N; i++) {
        res[i] = coordinates[i] + anotherVector.coordinates[i];
    }
    return ArithmVectorN(res);
}

ArithmVectorN ArithmVectorN::operator-(const ArithmVectorN& anotherVector) const {
    double res[N];
    for (size_t i = 0; i < N; i++) {
        res[i] = coordinates[i] - anotherVector.coordinates[i];
    }
    return ArithmVectorN(res);
}

ArithmVectorN ArithmVectorN::operator*(const double c) const {
    double res[N];
    for (size_t i = 0; i < N; i++) {
        res[i] = coordinates[i] * c;
    }
    return ArithmVectorN(res);
}

ArithmVectorN ArithmVectorN::operator/(const double c) const {
    if (c == 0) {
        throw std::invalid_argument("Division by zero scalar");
    }
    double res[N];
    for (size_t i = 0; i < N; i++) {
        res[i] = coordinates[i] / c;
    }
    return ArithmVectorN(res);
}

double ArithmVectorN::getAbs() const {
    double sum = 0;
    for (size_t i = 0; i < N; i++) {
        sum += coordinates[i] * coordinates[i];
    }
    return std::sqrt(sum);
}

double ArithmVectorN::getDot(const ArithmVectorN& anotherVector) const {
    double sum = 0;
    for (size_t i = 0; i < N; i++) {
        sum += coordinates[i] * anotherVector.coordinates[i];
    }
    return sum;
}

ArithmVectorN &ArithmVectorN::operator+=(const ArithmVectorN &anotherVector) {
    for (int i = 0; i < N; i++) {
        coordinates[i] = coordinates[i] + anotherVector.coordinates[i];
    }
    return *this;
}

ArithmVectorN &ArithmVectorN::operator-=(const ArithmVectorN &anotherVector) {
    for (int i = 0; i < N; i++) {
        coordinates[i] = this->coordinates[i] - anotherVector.coordinates[i];
    }
    return *this;
}


bool ArithmVectorN::operator==(const ArithmVectorN& anotherVector) const {
    for (size_t i = 0; i < N; i++) {
        if (coordinates[i] != anotherVector.coordinates[i]) {
            return false;
        }
    }
    return true;
}

bool ArithmVectorN::operator!=(const ArithmVectorN &anotherVector) const {
    return !(*this == anotherVector);
}

ArithmVectorN& ArithmVectorN::operator=(const ArithmVectorN &anotherVector) {
    if (this != &anotherVector) {
        for (size_t i = 0; i < N; i++) {
            coordinates[i] = anotherVector.coordinates[i];
        }
    }
    return *this;
}

double ArithmVectorN::operator[](const int index) const {
    if (index >= 0 && index < N) {
        return coordinates[index];
    }
    throw std::out_of_range("Index out of range");
}

std::ostream& operator<< (std::ostream& out, const ArithmVectorN& vec) {
    out << "(";
    for (int i = 0; i < ArithmVectorN::N; ++i) {
        out << vec.coordinates[i];
        if (i < ArithmVectorN::N - 1) {
            out << ", ";
        }
    }
    out << ")";
    return out;
}