#include "Matrix.hpp"
#include <iostream>

using namespace std;
namespace zich
{
    Matrix::Matrix(const vector<double>& vec, int sizeRow, int sizeCol)
    {
        if (sizeCol <= 0 || sizeRow <= 0)
        {
            throw invalid_argument("dimension can not be negative");
        }
        if (vec.size() != sizeCol * sizeRow)
        {
            throw invalid_argument("the size of the vector does not match the dimension");
        }

        this->vec = vec;
        this->sizeCol = sizeCol;
        this->sizeRow = sizeRow;
    }

    // + , - , += , -= , (+) ,(-)

    //+
    Matrix Matrix::operator+(Matrix const &b)
    {
        if (this->sizeRow != b.sizeRow || this->sizeCol != b.sizeCol)
        {
            throw invalid_argument("it is not possible to add matrices that are not the same dimension");
        }
        Matrix result{this->vec, this->sizeRow, this->sizeCol};
        for (size_t i = 0; i < sizeCol * sizeRow; i++)
        {
            result.vec[i] += b.vec[i];
        }
        return result;
    }

    //(+)
    Matrix Matrix::operator+() const
    {
        return *this;
    }

    // -
    Matrix Matrix::operator-(Matrix const &b)
    {
        if (this->sizeRow != b.sizeRow || this->sizeCol != b.sizeCol)
        {
            throw invalid_argument("it is not possible to subtract matrices that are not the same dimension");
        }
        Matrix result{this->vec, this->sizeRow, this->sizeCol};
        for (size_t i = 0; i < sizeCol * sizeRow; i++)
        {
            result.vec[i] -= b.vec[i];
        }
        return result;
    }

    // (-)
    Matrix Matrix::operator-() const
    {
        Matrix result{this->vec, this->sizeRow, this->sizeCol};
        for (size_t i = 0; i < sizeCol * sizeRow; i++)
        {
            result.vec[i] *= (-1);
        }
        return result;
    }

    //  +=
    // this = a
    Matrix &Matrix::operator+=(Matrix const &b)
    {
        if (this->sizeRow != b.sizeRow || this->sizeCol != b.sizeCol)
        {
            throw invalid_argument("it is not possible to add matrices that are not the same dimension");
        }
        for (size_t i = 0; i < sizeCol * sizeRow; i++)
        {
            this->vec[i] += b.vec[i];
        }
        return *this;
    }

    // -=
    Matrix &Matrix::operator-=(Matrix const &b)
    {
        if (this->sizeRow != b.sizeRow || this->sizeCol != b.sizeCol)
        {
            throw invalid_argument("it is not possible to subtract matrices that are not the same dimension");
        }
        for (size_t i = 0; i < sizeCol * sizeRow; i++)
        {
            this->vec[i] -= b.vec[i];
        }
        return *this;
    }

    // > >= < <= != ==

    //==
    bool operator==(Matrix const &a, Matrix const &b)
    {

        if (a.sizeRow != b.sizeRow || a.sizeCol != b.sizeCol)
        {

            throw invalid_argument("it is not possible to compare matrices that are not the same dimension");
        }
        for (size_t i = 0; i < a.sizeCol * a.sizeRow; i++)
        {
            if (a.vec[i] != b.vec[i])
            {
                return false;
            }
        }
        return true;
    }

    //!=
    bool operator!=(Matrix const &a, Matrix const &b)
    {
        return !(a == b);
    }

    //<
    bool operator<(Matrix const &a, Matrix const &b)
    {
        if (a.sizeRow != b.sizeRow || a.sizeCol != b.sizeCol)
        {

            throw invalid_argument("it is not possible to substract matrices that are not the same dimension");
        }

        return a.sum() < b.sum();
    }

    //<=
    bool operator<=(Matrix const &a, Matrix const &b)
    {
        if (a.sizeRow != b.sizeRow || a.sizeCol != b.sizeCol)
        {

            throw invalid_argument("it is not possible to substract matrices that are not the same dimension");
        }

        return a.sum() <= b.sum();
    }

    //>
    bool operator>(Matrix const &a, Matrix const &b)
    {
        if (a.sizeRow != b.sizeRow || a.sizeCol != b.sizeCol)
        {

            throw invalid_argument("it is not possible to compare matrices that are not the same dimension");
        }
        return a.sum() > b.sum();
    }

    //>=
    bool operator>=(Matrix const &a, Matrix const &b)
    {
        if (a.sizeRow != b.sizeRow || a.sizeCol != b.sizeCol)
        {

            throw invalid_argument("it is not possible to compare matrices that are not the same dimension");
        }
        return a.sum() >= b.sum();
    }

    // prefix ++ --  postfix ++ ---

    // prefix
    Matrix &Matrix::operator++()
    {
        for (size_t i = 0; i < sizeCol * sizeRow; i++)
        {
            this->vec[i]++;
        }
        return *this;
    }

    // postfix
    Matrix Matrix::operator++(int x)
    {
        Matrix result{this->vec, this->sizeRow, this->sizeCol};
        for (size_t i = 0; i < sizeCol * sizeRow; i++)
        {
            this->vec[i]++;
        }
        return result;
    }

    // prefix
    Matrix &Matrix::operator--()
    {
        for (size_t i = 0; i < sizeCol * sizeRow; i++)
        {
            this->vec[i]--;
        }
        return *this;
    }

    // postfix
    Matrix Matrix::operator--(int x)
    {
        Matrix result{this->vec, this->sizeRow, this->sizeCol};
        for (size_t i = 0; i < sizeCol * sizeRow; i++)
        {
            this->vec[i]--;
        }
        return result;
    }

    //*
    Matrix operator*(const Matrix &a, double x)
    {
        Matrix result{a.vec, a.sizeRow, a.sizeCol};
        for (size_t i = 0; i < a.sizeCol * a.sizeRow; i++)
        {
            result.vec[i] *= x;
        }
        return result;
    }

    Matrix operator*(double x, const Matrix &a)
    {
        return a * x;
    }

    Matrix Matrix::operator*(const Matrix &b) const
    {
        if (this->sizeCol != b.sizeRow)
        {
            throw invalid_argument(" it is not possible to multiply matrices that are not the same dimension ");
        }
        vector<double> num((size_t)this->sizeRow * (size_t)b.sizeCol, 0);
        Matrix result{num, this->sizeRow, b.sizeCol};
        for (size_t i = 0; i < result.sizeRow; i++)
        {
            for (size_t j = 0; j < result.sizeCol; j++)
            {
                double value = 0;
                for (size_t k = 0; k < this->sizeCol; k++)
                {
                    value += this->getCell(i, k) * b.getCell(k, j);
                }

                result.vec[i * (size_t)result.sizeCol + j] = value;
            }
        }

        return result;
    }

    //*=
    Matrix &Matrix::operator*=(double x)
    {
        for (size_t i = 0; i < sizeCol * sizeRow; i++)
        {
            this->vec[i] *= x;
        }

        return *this;
    }
    Matrix &Matrix::operator*=(Matrix const &x)
    {
        Matrix c = (*this) * x;
        this->sizeCol = c.sizeCol;
        this->sizeRow = c.sizeRow;
        this->vec = c.vec;
        return *this;
    }

    // << >>
    ostream &operator<<(ostream &os, const Matrix &a)
    {
        for (size_t i = 0; i < a.sizeRow; i++)
        {
            os << "[";
            for (size_t j = 0; j < a.sizeCol - 1; j++)
            {
                os << a.getCell(i, j) << " ";
            }

            os << a.getCell(i, (size_t)a.sizeCol - 1) << "]";
            if (i != a.sizeRow - 1)
            {
                os << "\n";
            }
        }
        return os;
    }
    //check if there is '\n' - the vector is over
    bool isInputStreamEnded(std::istream &is)
    {
        if (is.get() == '\n')
        {
            return true;
        }
        is.unget();
        return false;
    }
    //goes over the matrix and checks if it is listed as we wanted
    std::vector<double> readMatrixRow(std::istream &is)
    {
        std::vector<double> numbers;
        if (is.get() != '[')
        {
            throw std::invalid_argument("bad matrix input format ");
        }
        int current = 0;
        bool stop = false;
        do
        {
            is >> current;
            if (is.fail())
            {
                throw std::invalid_argument("bad matrix input format");
            }
            numbers.push_back(current);
            char seperator = is.get();
            if (seperator == ']')
            {
                stop = true;
            }
            else if (seperator != ' ')
            {
                throw std::invalid_argument("bad matrix input format");
            }
        } while (!stop);
        if (numbers.empty())
        {
            throw std::invalid_argument("bad matrix input format");
        }
        return numbers;
    }

    std::istream &operator>>(std::istream &is, Matrix &mat)
    {
        std::vector<double> matrix_vector;
        std::vector<double> numbers = readMatrixRow(is);
        int cols = numbers.size();
        int rows = 1;
        //separation of vector
        matrix_vector.insert(matrix_vector.end(), numbers.begin(), numbers.end());

        bool isStreamEnded = isInputStreamEnded(is);
        
        //check if there is ',' and ' '
        if (!isStreamEnded && (is.get() != ',' || is.get() != ' '))
        {
            throw std::invalid_argument("bad matrix input format");
        }

        while (!isStreamEnded)
        {
            numbers = readMatrixRow(is);
            if (numbers.size() != cols)
            {
                throw std::invalid_argument("bad matrix input format");
            }
            isStreamEnded = isInputStreamEnded(is);
            if (!isStreamEnded && (is.get() != ',' || is.get() != ' '))
            {
                throw std::invalid_argument("bad matrix input format");
            }
            matrix_vector.insert(matrix_vector.end(), numbers.begin(), numbers.end());
            rows++;
        }

        mat.vec = matrix_vector;
        mat.sizeCol = cols;
        mat.sizeRow = rows;
        return is;
    }

    // compute sum of matrix
    double Matrix::sum() const
    {
        double sum = 0;
        for (size_t i = 0; i < sizeRow * sizeCol; i++)
        {
            sum += this->vec[i];
        }
        return sum;
    }
    
    //rowIndex * sizeCol + colIndex
    double Matrix::getCell(size_t rowIndex, size_t colIndex) const
    {
        return this->vec[rowIndex * (size_t)sizeCol + colIndex];
    }
}