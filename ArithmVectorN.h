//
// Created by Lenovo on 2025-02-17.
//

#ifndef ARITHMVECTORN_H
#define ARITHMVECTORN_H
#include <iostream>
#include <stdexcept>
#include <cmath>


class ArithmVectorN {
private:
    static const int N = 10;
    double coordinates[N];

public:
    ArithmVectorN();
    explicit ArithmVectorN(const double initCoordinates[N]);
    ArithmVectorN(const ArithmVectorN &anotherVector);
    ~ArithmVectorN();

    const double *getCoordinates() const;
    void setCoordinates(const double coordinates[N]);

    double getCoordinate(int index) const;
    void setCoordinate(int index, double value);

    ArithmVectorN operator+ (const ArithmVectorN& anotherVector) const;
    ArithmVectorN operator- (const ArithmVectorN& anotherVector) const;

    ArithmVectorN operator* (double c) const;
    ArithmVectorN operator/ (double c) const;

    double getAbs() const;
    double getDot(const ArithmVectorN& anotherVector) const;

    ArithmVectorN& operator+= (const ArithmVectorN& anotherVector);
    ArithmVectorN& operator-= (const ArithmVectorN& anotherVector);

    bool operator==(const ArithmVectorN& anotherVector) const;
    bool operator!=(const ArithmVectorN& anotherVector) const;

    ArithmVectorN& operator=(const ArithmVectorN& anotherVector);
    double operator[] (int index) const;
    double& operator[] (int index);

    friend std::ostream& operator<< (std::ostream& out, const ArithmVectorN& vec);
    friend std::istream& operator>> (std::istream& in, ArithmVectorN& vec);
};



#endif //ARITHMVECTORN_H
