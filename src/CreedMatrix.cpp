#include <CreedMatrix.hpp>
#ifdef USE_CUDA
#include <cuda_runtime.h>
#endif
using namespace creed;
template<typename T, size_t N>
T* Matrix<T, N>::allocateHost(size_t totalItems)
{
    return new T[totalItems];
}
template<typename T, size_t N>
void Matrix<T, N>::freeHost(T* ptr)
{
    delete[] ptr;
}
template<typename T, size_t N>
T* Matrix<T, N>::allocateManaged(size_t totalItems)
{
#ifdef USE_CUDA
    T* ptr;
    cudaMalloc(&ptr, totalItems * sizeof(T));
    return ptr;
#else
    return NULL;
#endif
}
template<typename T, size_t N>
void Matrix<T, N>::freeManaged(T* ptr)
{
#ifdef USE_CUDA
    cudaFree(ptr);
#endif
}
template<typename T, size_t N>
Matrix<T, N>::Matrix(size_t dimensions[N])
{
    this->totalItems = 1;
    for (size_t i = 0; i < N; i++)
    {
        this->offsets[i] = 0;
        this->pitches[i] = dimensions[i];
        this->dimensions[i] = dimensions[i];
        this->totalItems *= this->dimensions[i];
    }
#ifdef USE_CUDA
    data = std::shared_ptr<T>(allocateManaged(this->totalItems), [this](T* ptr) {
        freeManaged(ptr);
    });
#else
    data = std::shared_ptr<T>(allocateHost(this->totalItems), [this](T* ptr) {
        freeHost(ptr);
    });
#endif
}
template<typename T, size_t N>
Matrix<T, N>::Matrix(size_t dimensions[N], const T* data)
{
    this->totalItems = 1;
    for (size_t i = 0; i < N; i++)
    {
        this->offsets[i] = 0;
        this->pitches[i] = dimensions[i];
        this->dimensions[i] = dimensions[i];
        this->totalItems *= this->dimensions[i];
    }
#ifdef USE_CUDA
    this->data = std::shared_ptr<T>(allocateManaged(this->totalItems), [this](T* ptr) {
        freeManaged(ptr);
    });
    cudaMemcpy(this->data, data, cudaMemcpyHostToDevice);
#else
    this->data = std::shared_ptr<T>(allocateHost(this->totalItems), [this](T* ptr) {
        freeHost(ptr);
    });
    for (size_t i = 0; i < totalItems; i++)
    {
        this->data[i] = data[i];
    }
#endif
}
template<typename T, size_t N>
Matrix<T, N>::Matrix(size_t dimensions[N], std::shared_ptr<T> data)
{
    this->totalItems = 1;
    for (size_t i = 0; i < N; i++)
    {
        this->offsets[i] = 0;
        this->pitches[i] = dimensions[i];
        this->dimensions[i] = dimensions[i];
        this->totalItems *= this->dimensions[i];
    }
#ifdef USE_CUDA
    this->data = std::shared_ptr<T>(allocateManaged(this->totalItems), [this](T* ptr) {
        freeManaged(ptr);
    });
    cudaMemcpy(this->data, data, cudaMemcpyHostToDevice);
#else
    this->data = std::shared_ptr<T>(allocateHost(this->totalItems), [this](T* ptr) {
        freeHost(ptr);
    });
    for (size_t i = 0; i < totalItems; i++)
    {
        this->data[i] = data[i];
    }
#endif
}
template<typename T, size_t N>
Matrix<T, N>::Matrix(size_t dimensions[N], std::vector<T> data)
{
    this->totalItems = 1;
    for (size_t i = 0; i < N; i++)
    {
        this->offsets[i] = 0;
        this->pitches[i] = dimensions[i];
        this->dimensions[i] = dimensions[i];
        this->totalItems *= this->dimensions[i];
    }
#ifdef USE_CUDA
    this->data = std::shared_ptr<T>(allocateManaged(this->totalItems), [this](T* ptr) {
        freeManaged(ptr);
    });
    cudaMemcpy(this->data, &data[0], cudaMemcpyHostToDevice);
#else
    this->data = std::shared_ptr<T>(allocateHost(this->totalItems), [this](T* ptr) {
        freeHost(ptr);
    });
    for (size_t i = 0; i < totalItems; i++)
    {
        this->data[i] = data[i];
    }
#endif
}
template<typename T, size_t N>
Matrix<T, N>::Matrix(std::vector<size_t> dimensions)
{
    this->totalItems = 1;
    for (size_t i = 0; i < N; i++)
    {
        this->offsets[i] = 0;
        this->pitches[i] = dimensions[i];
        this->dimensions[i] = dimensions[i];
        this->totalItems *= this->dimensions[i];
    }
#ifdef USE_CUDA
    data = std::shared_ptr<T>(allocateManaged(this->totalItems), [this](T* ptr) {
        freeManaged(ptr);
    });
#else
    data = std::shared_ptr<T>(allocateHost(this->totalItems), [this](T* ptr) {
        freeHost(ptr);
    });
#endif
}
template<typename T, size_t N>
Matrix<T, N>::Matrix(std::vector<size_t> dimensions, const T* data)
{
    this->totalItems = 1;
    for (size_t i = 0; i < N; i++)
    {
        this->offsets[i] = 0;
        this->pitches[i] = dimensions[i];
        this->dimensions[i] = dimensions[i];
        this->totalItems *= this->dimensions[i];
    }
#ifdef USE_CUDA
    this->data = std::shared_ptr<T>(allocateManaged(this->totalItems), [this](T* ptr) {
        freeManaged(ptr);
    });
    cudaMemcpy(this->data, data, cudaMemcpyHostToDevice);
#else
    this->data = std::shared_ptr<T>(allocateHost(this->totalItems), [this](T* ptr) {
        freeHost(ptr);
    });
    for (size_t i = 0; i < totalItems; i++)
    {
        this->data[i] = data[i];
    }
#endif
}
template<typename T, size_t N>
Matrix<T, N>::Matrix(std::vector<size_t> dimensions, std::shared_ptr<T> data)
{
    this->totalItems = 1;
    for (size_t i = 0; i < N; i++)
    {
        this->offsets[i] = 0;
        this->pitches[i] = dimensions[i];
        this->dimensions[i] = dimensions[i];
        this->totalItems *= this->dimensions[i];
    }
#ifdef USE_CUDA
    this->data = std::shared_ptr<T>(allocateManaged(this->totalItems), [this](T* ptr) {
        freeManaged(ptr);
    });
    cudaMemcpy(this->data, data, cudaMemcpyHostToDevice);
#else
    this->data = std::shared_ptr<T>(allocateHost(this->totalItems), [this](T* ptr) {
        freeHost(ptr);
    });
    for (size_t i = 0; i < totalItems; i++)
    {
        this->data[i] = data[i];
    }
#endif
}
template<typename T, size_t N>
Matrix<T, N>::Matrix(std::vector<size_t> dimensions, std::vector<T> data)
{
    this->totalItems = 1;
    for (size_t i = 0; i < N; i++)
    {
        this->offsets[i] = 0;
        this->pitches[i] = dimensions[i];
        this->dimensions[i] = dimensions[i];
        this->totalItems *= this->dimensions[i];
    }
#ifdef USE_CUDA
    this->data = std::shared_ptr<T>(allocateManaged(this->totalItems), [this](T* ptr) {
        freeManaged(ptr);
    });
    cudaMemcpy(this->data, &data[0], cudaMemcpyHostToDevice);
#else
    this->data = std::shared_ptr<T>(allocateHost(this->totalItems), [this](T* ptr) {
        freeHost(ptr);
    });
    for (size_t i = 0; i < totalItems; i++)
    {
        this->data[i] = data[i];
    }
#endif
}
template<typename T, size_t N>
Matrix<T, N>::Matrix(const Matrix<T, N>& other)
{
    this->totalItems = other.totalItems;
    this->data = data;
    for (size_t i = 0; i < N; i++)
    {
        this->dimensions[i] = other.dimensions[i];
        this->offsets[i] = other.offsets[i];
        this->pitches[i] = other.pitches[i];
    }
}
template<typename T, size_t N>
Matrix<T, N>::Matrix(Matrix<T, N>&& other)
{
    this->totalItems = other.totalItems;
    this->data = data;
    for (size_t i = 0; i < N; i++)
    {
        this->dimensions[i] = other.dimensions[i];
        this->offsets[i] = other.offsets[i];
        this->pitches[i] = other.pitches[i];
    }
}
template<typename T, size_t N>
Matrix<T, N> Matrix<T, N>::copy() const
{
    Matrix<T, N> other;
    other.totalItems = this->totalItems;
    for (size_t i = 0; i < N; i++)
    {
        other.dimensions[i] = this->dimensions[i];
        other.pitches[i] = this->dimensions[i];
        other.offsets[i] = 0;
    }
#ifdef USE_CUDA
    other.data = std::shared_ptr<T>(allocateManaged(other.totalItems), [other](T* ptr) {
        other.freeManaged(ptr);
    });
#else
    other.data = std::shared_ptr<T>(other.allocateHost(this->totalItems), [other](T* ptr) {
        other.freeHost(ptr);
    });
#endif
    return other;
}
template<typename T, size_t N>
Matrix<T, N - 1> Matrix<T, N>::operator[](size_t idx) const
{
    if constexpr (N - 1 == 0)
    {
        return Matrix<T, 0>(data[idx]);
    }
    else
    {
        size_t newOffsets[N - 1];
        size_t pitches[N - 2];
        newOffsets[0] = this->offsets[0] * this->dimensions[0] + idx;
        for (size_t i = 1; i < N - 1; i++)
        {
            newOffsets[i] = 0;
            pitches[i - 1] = this->dimensions[i];
        }
        return Matrix<T, N - 1>(*this, offsets, pitches);
    }
}
template<typename T, size_t N>
bool Matrix<T, N>::operator==(const Matrix<T, N>& other) const
{
    if (dimensions[0] != other.dimensions[0])
    {
        return false;
    }
    for (size_t i = 0; i < dimensions[0]; i++)
    {
        if ((*this)[i] != other[i])
        {
            return false;
        }
    }
    return true;
}
template<typename T, size_t N>
bool Matrix<T, N>::operator==(Matrix<T, N>&& other) const
{
    if (dimensions[0] != other.dimensions[0])
    {
        return false;
    }
    for (size_t i = 0; i < dimensions[0]; i++)
    {
        if ((*this)[i] != other[i])
        {
            return false;
        }
    }
    return true;
}
template<typename T, size_t N>
bool Matrix<T, N>::operator!=(const Matrix<T, N>& other) const
{
    if (dimensions[0] != other.dimensions[0])
    {
        return true;
    }
    for (size_t i = 0; i < dimensions[0]; i++)
    {
        if ((*this)[i] != other[i])
        {
            return true;
        }
    }
    return false;
}
template<typename T, size_t N>
bool Matrix<T, N>::operator!=(Matrix<T, N>&& other) const
{
    if (dimensions[0] != other.dimensions[0])
    {
        return true;
    }
    for (size_t i = 0; i < dimensions[0]; i++)
    {
        if ((*this)[i] != other[i])
        {
            return true;
        }
    }
    return false;
}
template<typename T, size_t N>
Matrix<T, N> operator<<(std::ostream& out, const Matrix<T, N>& matrix)
{
    out << "[ ";
    for (size_t i = 0; i < matrix.dimensions[0]; i++)
    {
        out << matrix.data[i] << " ";
    }
    out << "]";
    return matrix;
}
template<typename T, size_t N>
Matrix<T, N> operator<<(std::ostream& out, Matrix<T, N>&& matrix)
{
    out << "[ ";
    for (size_t i = 0; i < matrix.dimensions[0]; i++)
    {
        out << matrix.data[i] << " ";
    }
    out << "]";
    return matrix;
}
template<typename T, size_t N>
Matrix<T, N> Matrix<T, N>::random(std::vector<size_t> dimensions)
{
    Matrix<T, N> matrix = Matrix<T, N>(dimensions);
    for (size_t i = 0; i < matrix.totalItems; i++)
    {
        matrix.data[i] = (T)rand() / RAND_MAX;
    }
    return matrix;
}
template<typename T, size_t N>
Matrix<T, N> Matrix<T, N>::ones(std::vector<size_t> dimensions)
{
    Matrix<T, N> matrix = Matrix<T, N>(dimensions);
    for (size_t i = 0; i < matrix.totalItems; i++)
    {
        matrix.data[i] = 1;
    }
    return matrix;
}