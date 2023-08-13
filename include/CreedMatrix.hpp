#ifndef CREEDMATRIX_HPP
#define CREEDMATRIX_HPP
#include <memory>
#include <array>
#include <vector>
#include <cstdarg>
#include <ostream>
namespace creed
{
    template<typename T, size_t N>
    class Matrix
    {
    private:
        std::shared_ptr<T> data;
        size_t dimensions[N];
        size_t pitches[N];
        size_t offsets[N];
        size_t totalItems;
        T* allocateManaged(size_t count);
        void freeManaged(T* ptr);
        T* allocateHost(size_t count);
        void freeHost(T* ptr);
        Matrix(const Matrix& matrix, size_t offsets[N], size_t pitches[N - 1]);
    public:
        inline Matrix()
        {
            data = NULL;
            for (size_t i = 0; i < N; i++)
            {
                dimensions[i] = 0;
                if (i > 0)
                    pitches[i - 1] = 0;
                offsets[i] = 0;
            }
            totalItems = 0;
        }
        Matrix(size_t dimensions[N]);
        Matrix(size_t dimensions[N], const T* data);
        Matrix(size_t dimensions[N], std::shared_ptr<T> hostData);
        Matrix(size_t dimensions[N], std::vector<T> hostData);
        Matrix(std::vector<size_t> dimensions);
        Matrix(std::vector<size_t> dimensions, const T* data);
        Matrix(std::vector<size_t> dimensions, std::shared_ptr<T> hostData);
        Matrix(std::vector<size_t> dimensions, std::vector<T> hostData);
        Matrix(const Matrix<T, N>& other);
        Matrix(Matrix<T, N>&& other);
        inline T operator()(size_t first, ...) const
        {
            size_t idx = first + offsets;
            for (size_t i = 1; i < N; i++)
            {
                idx = idx * pitches[i - 1];
            }
            return data[idx];
        }
        inline T& operator()(size_t first, ...)
        {
            size_t idx = first + offsets;
            va_list ls;
            va_start(ls, first);
            for (size_t i = 1; i < N; i++)
            {
                idx = idx * pitches[i - 1] + va_arg(ls, size_t) + offsets[i];
            }
            return data[idx];
        }
        inline T operator()(std::vector<size_t> indices) const
        {
            size_t idx = indices[0] + offsets;
            for (size_t i = 1; i < N; i++)
            {
                idx = idx * pitches[i - 1] + indices[i] + offsets[i];
            }
            return data[idx];
        }
        inline T& operator()(std::vector<size_t> indices)
        {
            size_t idx = indices[0] + offsets;
            for (size_t i = 1; i < N; i++)
            {
                idx = idx * pitches[i - 1] + indices[i] + offsets[i];
            }
            return data[idx];
        }
        Matrix<T, N> copy() const;
        Matrix<T, N-1> operator[](size_t i) const;
        bool operator==(const Matrix<T, N>& other) const;
        bool operator==(Matrix<T, N>&& other) const;
        bool operator!=(const Matrix<T, N>& other) const;
        bool operator!=(Matrix<T, N>&& other) const;
        Matrix<T, N> operator-();
        inline bool isScalar()
        {
            return false;
        }
        template<typename U, size_t L>
        friend Matrix<U, L> operator+(Matrix<U, L> a, Matrix<U, L> b);
        template<typename U, size_t L>
        friend Matrix<U, L> operator+(Matrix<U, L> a, Matrix<U, 0> b);
        template<typename U, size_t L>
        friend Matrix<U, L> operator-(Matrix<U, L> a, Matrix<U, L> b);
        template<typename U, size_t L>
        friend Matrix<U, L> operator-(Matrix<U, L> a, Matrix<U, 0> b);
        template<typename U, size_t L>
        friend Matrix<U, L> operator/(Matrix<U, L> a, Matrix<U, L> b);
        template<typename U, size_t L>
        friend Matrix<U, L> operator/(Matrix<U, L> a, Matrix<U, 0> b);
        template<typename U, size_t L, size_t M>
        friend Matrix<U, (L + M - 2)> operator*(Matrix<U, L> a, Matrix<U, M> b);
        template<typename U, size_t L>
        friend Matrix<U, L> operator*(Matrix<U, L> a, Matrix<U, 0> b);
        template<typename U, size_t L>
        friend Matrix<U, L> operator*(Matrix<U, 0> a, Matrix<U, L> b);
        template<typename U>
        friend Matrix<U, 2> operator*(Matrix<U, 1> a, Matrix<U, 1> b);
        template<typename U, size_t L>
        friend Matrix<U, L> operator*(Matrix<U, L> a, Matrix<U, 1> b);
        template<typename U>
        friend Matrix<U, 2> operator*(Matrix<U, 2> a, Matrix<U, 2> b);
        template<typename U, size_t L>
        friend Matrix<U, L> operator<<(std::ostream& out, const Matrix<U, L>& matrix);
        template<typename U, size_t L>
        friend Matrix<U, L> operator<<(std::ostream& out, Matrix<U, L>&& matrix);
        static Matrix<T, N> random(std::vector<size_t> dimensions);
        static Matrix<T, N> ones(std::vector<size_t> dimensions);
    };
    template<typename T>
    class Matrix<T, 0>
    {
    private:
        T scalar;
    public:
        inline Matrix()
        {
            scalar = T();
        }
        inline Matrix(T t)
        {
            scalar = t;
        }
        inline T operator()() const
        {
            return scalar;
        }
        inline T& operator()()
        {
            return scalar;
        }
        bool operator==(const Matrix<T, 0>& other)
        {
            return scalar == other.scalar;
        }
        bool operator==(Matrix<T, 0>&& other)
        {
            return scalar == other.scalar;
        }
        bool operator!=(const Matrix<T, 0>& other)
        {
            return scalar != other.scalar;
        }
        bool operator!=(Matrix<T, 0>&& other)
        {
            return scalar != other.scalar;
        }
        inline Matrix<T, 0> operator-()
        {
            return -scalar;
        }
        inline bool isScalar()
        {
            return true;
        }
        template<typename U, size_t L>
        friend Matrix<U, L> operator+(Matrix<U, L> a, Matrix<U, 0> b);
        template<typename U, size_t L>
        friend Matrix<U, L> operator-(Matrix<U, L> a, Matrix<U, 0> b);
        template<typename U, size_t L>
        friend Matrix<U, L> operator/(Matrix<U, L> a, Matrix<U, 0> b);
        template<typename U, size_t L>
        friend Matrix<U, L> operator*(Matrix<U, L> a, Matrix<U, 0> b);
        template<typename U, size_t L>
        friend Matrix<U, L> operator*(Matrix<U, 0> a, Matrix<U, L> b);
        inline operator T()
        {
            return scalar;
        }
    };
}
#endif