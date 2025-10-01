#include <iostream>
#include <stdexcept>
#include<complex>
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

        // add comparison operators and vector normalization
        friend bool operator==(const Vector& first, const Vector& second) {
            if (first.size != second.size) return false;
            for (size_t i = 0; i < first.size; i++) {
                if (abs(first[i] - second[i]) > EPS) return false;
            }
            return true;
        }
        friend bool operator!=(const Vector& first, const Vector& second) {
            return !(first == second);
        }

        T getLength() const {
            T sum = T();
            for (size_t i = 0; i < size; i++) {
                sum += data[i] * data[i];
            }
            return sqrt(abs(sum));
        }

        Vector normalize() const {
            T n = getLength();
            if (n < EPS) {
                throw std::invalid_argument("Cannot normalize zero vector!");
            }
            Vector result(size);
            for (size_t i = 0; i < size; i++) {
                result[i] = data[i] / n;
            }
            return result;
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


namespace myVector {
    template<class T>
    class Vector<std::complex<T>> {
    private:
        std::complex<T>* data;
        size_t size;

    public:
        static constexpr double EPS = 1e-8;

        Vector() : data(nullptr), size(0) {}
        Vector(size_t n, const std::complex<T>* init) : data(new std::complex<T>[n]), size(n) {
            for (size_t i = 0; i < size; ++i) data[i] = init[i];
        }
        Vector(size_t n, const std::complex<T>& fillValue = std::complex<T>()) : data(new std::complex<T>[n]), size(n) {
            for (size_t i = 0; i < size; i++) {
                data[i] = fillValue;
            }
        }
        Vector(const Vector<std::complex<T>>& other) : data(new std::complex<T>[other.size]), size(other.size) {
            for (size_t i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        Vector& operator=(const Vector<std::complex<T>>& other) {
            if (this != &other) {
                delete[] data;
                size = other.size;
                data = new std::complex<T>[size];
                for (size_t i = 0; i < size; i++) {
                    data[i] = other.data[i];
                }
            }
            return *this;
        }
        ~Vector() { delete[] data; }

        std::complex<T>& operator[](size_t i) {
            if (i >= size) throw std::out_of_range("Invalid value!");
            return data[i];
        }
        const std::complex<T>& operator[](size_t i) const {
            if (i >= size) throw std::out_of_range("Invalid value!");
            return data[i];
        }

        Vector<std::complex<T>>& operator+=(const Vector<std::complex<T>>& second) {
            if (second.size != this->size) throw std::invalid_argument("Unequal lengths");
            for (size_t i = 0; i < size; ++i) this->data[i] += second.data[i];
            return *this;
        }
        friend Vector<std::complex<T>> operator+(Vector<std::complex<T>> first, const Vector<std::complex<T>>& second) {
            first += second;
            return first;
        }

        Vector<std::complex<T>>& operator-=(const Vector<std::complex<T>>& other) {
            if (other.size != this->size) throw std::invalid_argument("Unequal lengths!");
            for (size_t i = 0; i < size; i++) this->data[i] -= other.data[i];
            return *this;
        }
        friend Vector<std::complex<T>> operator-(Vector<std::complex<T>> first, const Vector<std::complex<T>> second) {
            first -= second;
            return first;
        }

        friend std::complex<T> operator*(const Vector<std::complex<T>>& first, const Vector<std::complex<T>>& second) {
            if (first.size != second.size) throw std::invalid_argument("Unequal lengths!");
            std::complex<T> result = { T(), T() };
            for (size_t i = 0; i < first.size; i++) {
                result += (std::conj(first[i])) * second[i];
            }
            return result;
        }

        double norm() const {
            std::complex<T> sum = std::complex<T>();
            for (size_t i = 0; i < size; i++) {
                sum += data[i] * std::conj(data[i]);
            }
            return sqrt(abs(sum));
        }

        size_t getSize() const { return size; }

        template<typename U>
        friend std::ostream& operator<<(std::ostream& os, const Vector<std::complex<U>>& v);
    };

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const Vector<std::complex<T>>& vec) {
        os << "{";
        for (size_t i = 0; i < vec.size; i++) {
            os << vec[i] << " ";
        }
        os << "}\n";
        return os;
    }
}

int main() {
    std::complex<double> c1[] = { {1.0, 2.0}, {3.0, 4.0} };
    std::complex<double> c2[] = { {1.0, 1.0}, {3.0, 0.0} };
    myVector::Vector<std::complex<double>> cv1(2, c1);
    myVector::Vector<std::complex<double>> cv2(2, c2);

    cout << "Complex v1: " << cv1;
    cout << "Complex v2: " << cv2;
    cout << "cv1 + cv2 = " << (cv1 + cv2);
    cout << "Dot product cv1 * cv2 = " << (cv1 * cv2) << endl;
    cout << "Norm of cv1: " << cv1.norm() << endl;

    return 0;
}