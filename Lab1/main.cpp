#include <iostream>
#include <stdexcept>
using namespace std;

namespace myVector {
    template<class T>
    class Vector {
    private:
        T* data;
        size_t size;

    public:
        static constexpr double EPS = 1e-8;

        Vector() : data(nullptr), size(0) {}
        Vector(size_t n, const T* init) : data(new T[n]), size(n) {
            for (size_t i = 0; i < size; ++i)
                data[i] = init[i];
        }
        Vector(size_t n, const T& fillValue = T()) : data(new T[n]), size(n) {
            for (size_t i = 0; i < size; ++i)
                data[i] = fillValue;
        }
        Vector(const Vector& other) : data(new T[other.size]), size(other.size) {
            for (size_t i = 0; i < size; ++i) data[i] = other.data[i];
        }
        Vector& operator=(const Vector& other) {
            if (this == &other) return *this;
            delete[] data;
            size = other.size;
            data = new T[size];
            for (size_t i = 0; i < size; ++i) data[i] = other.data[i];
            return *this;
        }

        T& operator[](size_t index) {
            if (index >= size) throw out_of_range("Invalid index!");
            return data[index];
        }
        const T& operator[](size_t index) const {
            if (index >= size) throw out_of_range("Invalid index!");
            return data[index];
        }

        size_t getSize() const {
            return size;
        }

        ~Vector() { delete[] data; }

        template<typename U>
        friend std::ostream& operator<<(std::ostream& os, const Vector<U>& v);

        //add arithmetic operators (+, -, +=, -=) for Vector class

        Vector& operator+=(const Vector& other) {
            if (size != other.size) throw invalid_argument("Unequal lengths");
            for (size_t i = 0; i < size; ++i) data[i] += other.data[i];
            return *this;
        }
        friend Vector operator+(Vector first, const Vector& second) {
            first += second;
            return first;
        }

        Vector& operator-=(const Vector& other) {
            if (size != other.size) throw invalid_argument("Unequal lengths");
            for (size_t i = 0; i < size; ++i) data[i] -= other.data[i];
            return *this;
        }
        friend Vector operator-(Vector first, const Vector& second) {
            first -= second;
            return first;
        }

        //implement scalar multiplication/division and dot product

        Vector& operator*=(const T value) {
            for (size_t i = 0; i < size; i++) this->data[i] *= value;
            return *this;
        }
        friend Vector operator*(Vector first, const T& value) {
            first *= value;
            return first;
        }
        friend Vector operator*(const T& value, Vector first) {
            first *= value;
            return first;
        }

        friend T operator*(const Vector& first, const Vector& second) {
            if (first.size != second.size) throw invalid_argument("Unequal lengths");
            T result = T();
            for (size_t i = 0; i < first.size; ++i) result += first[i] * second[i];
            return result;
        }

        Vector& operator/=(const T value) {
            if (abs(value) < EPS) { throw std::invalid_argument("The denominator must not be equal to 0!"); }
            for (size_t i = 0; i < size; i++) {
                data[i] /= value;
            }
            return *this;
        }

        friend Vector operator/(Vector first, const T& value) {
            first /= value;
            return first;
        }

    };

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const Vector<T>& v) {
        os << "{ ";
        for (size_t i = 0; i < v.size; ++i) os << v[i] << ' ';
        os << "}\n";
        return os;
    }
}

int main() {
    double arr1[] = { 1.0, 2.0, 3.0 };
    double arr2[] = { 4.0, 5.0, 6.0 };
    myVector::Vector<double> v1(3, arr1);
    myVector::Vector<double> v2(3, arr2);

    cout << "v1 * 2.0 = " << (v1 * 2.0);
    cout << "3.0 * v1 = " << (3.0 * v1);
    cout << "v1 / 2.0 = " << (v1 / 2.0);
    cout << "Dot product v1 * v2 = " << (v1 * v2) << endl;

    return 0;
}