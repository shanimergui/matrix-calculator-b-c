#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
namespace zich
{
  class Matrix
  {
  private:
    vector<double> vec;
    int sizeCol;
    int sizeRow;
    double sum() const;
    double getCell(size_t rowIndex, size_t colIndex) const;

  public:
    Matrix(const vector<double>& vec, int sizeRow, int sizeCol); // constructor

    // + , - , += , -= , (+) ,(-)

    //+
    Matrix operator+(Matrix const &b);

    //(+)
    Matrix operator+() const;

    // -
    Matrix operator-(Matrix const &b);

    // (-)
    Matrix operator-() const;

    //  +=
    // this = a
    Matrix &operator+=(Matrix const &b);

    // -=
    Matrix &operator-=(Matrix const &b);

    // > >= < <= != ==

    //==
    friend bool operator==(Matrix const &a, Matrix const &b);

    //!=
    friend bool operator!=(Matrix const &a, Matrix const &b);

    //<
    friend bool operator<(Matrix const &a, Matrix const &b);

    //<=
    friend bool operator<=(Matrix const &a, Matrix const &b);

    //>
    friend bool operator>(Matrix const &a, Matrix const &b);

    //>=
    friend bool operator>=(Matrix const &a, Matrix const &b);

    // prefix ++ --  postfix ++ ---

    // prefix
    Matrix &operator++();

    // postfix
    Matrix operator++(int x);

    // prefix
    Matrix &operator--();

    // postfix
    Matrix operator--(int x);

    //*
    friend Matrix operator*(const Matrix &a, double x);
    friend Matrix operator*(double x, const Matrix &a);
    Matrix operator*(const Matrix &b) const;

    //*=
    Matrix &operator*=(double x);
    Matrix &operator*=(Matrix const &x);

    // << >>
    friend ostream &operator<<(ostream &os, const Matrix &a);
    friend istream &operator>>(istream &is, Matrix &mat);
  };
}

// Matrix a{numbers,3,3}
// Matrix b{numbers,3,3}
// double sum = a.sum()