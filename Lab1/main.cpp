#include <iostream>
#include <stdexcept>
#include<complex>
#include<random>
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
        Vector(size_t n, double minValue, double maxValue) : data(new T[n]), size(n) {
            std::random_device rd;
            std::mt19937 gen(rd());  
            std::uniform_real_distribution<T> dist(minValue, maxValue);
            for (size_t i = 0; i < size; i++) data[i] = dist(gen);
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
        // SỬA THÀNH:
        Vector(size_t n, T minValue, T maxValue) : data(new std::complex<T>[n]), size(n) {
            std::random_device rd;
            std::mt19937 gen(rd());  // Đổi 're' thành 'gen'
            std::uniform_real_distribution<T> dist(minValue, maxValue);
            for (size_t i = 0; i < size; i++) {
                data[i] = std::complex<T>(dist(gen), dist(gen));
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

        Vector<std::complex<T>>& operator*=(const T& value) {
            for (size_t i = 0; i < size; i++) {
                data[i] *= value;
            }
            return *this;
        }
        friend Vector<std::complex<T>> operator*(Vector<std::complex<T>> first, const T& value) {
            first *= value;
            return first;
        }
        friend Vector<std::complex<T>> operator*(const T& value, Vector<std::complex<T>> first) {
            first *= value;
            return first;
        }

        Vector<std::complex<T>>& operator/=(const T& value) {
            if (abs(value) < EPS) {
                throw std::invalid_argument("The denominator must not be equal to 0");
            }
            for (size_t i = 0; i < size; i++) {
                data[i] /= value;
            }
            return *this;
        }
        friend Vector<std::complex<T>> operator/(Vector<std::complex<T>> first, const T& value) {
            first /= value;
            return first;
        }

        friend bool operator==(const Vector<std::complex<T>>& first, const Vector<std::complex<T>>& second) {
            if (first.size != second.size) return false;
            for (size_t i = 0; i < first.size; i++) {
                if ((abs(first[i].real() - second[i].real())) > EPS ||
                    (abs(first[i].imag() - second[i].imag())) > EPS) return false;
            }
            return true;
        }
        friend bool operator!=(const Vector<std::complex<T>> first, const Vector<std::complex<T>> second) {
            return !(first == second);
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

        size_t getSize() const {
            return size;
        }

        Vector normalize() const {
            double n = norm();
            if (n < EPS) {
                throw std::invalid_argument("Cannot normalize zero vector");
            }
            Vector result(size);
            for (size_t i = 0; i < size; i++) {
                result[i] = data[i] / n;
            }
            return result;
        }

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

template<typename T>
myVector::Vector<T> vectorBisector(const myVector::Vector<T>& a, const myVector::Vector<T>& b) {
    if (a.getSize() != b.getSize()) {
        throw std::invalid_argument("Vectors must have the same dimension!");
    }
    myVector::Vector<T> a_norm = a.normalize();
    myVector::Vector<T> b_norm = b.normalize();
    return a_norm + b_norm;
}

template<typename T>
myVector::Vector<std::complex<T>> vectorBisector(const myVector::Vector<std::complex<T>>& a, const myVector::Vector<std::complex<T>>& b) {
    if (a.getSize() != b.getSize()) {
        throw std::invalid_argument("Vectors must have the same dimension!");
    }
    myVector::Vector<std::complex<T>> a_norm = a.normalize();
    myVector::Vector<std::complex<T>> b_norm = b.normalize();
    return a_norm + b_norm;
}


int main() {
    // Test vectors real
    double arr1[] = { 1.0, 2.4, 3.2 };
    double arr2[] = { 2.0, 1.0, 1.0 };
    myVector::Vector<double> v1(3, arr1);
    myVector::Vector<double> v2(3, arr2);

    cout << "=== REAL VECTOR TESTS ===" << endl;
    cout << "v1: " << v1;
    cout << "v2: " << v2;
    cout << "Dot product v1 * v2 = " << (v1 * v2) << endl;
    cout << "v1 + v2 = " << (v1 + v2);
    cout << "v1 - v2 = " << (v1 - v2);
    cout << "v1 * 2.1 = " << (v1 * 2.1);

    auto bis = vectorBisector(v1, v2);
    cout << "Vector bisector = " << bis;

    // Test vectors complex
    std::complex<double> c1[] = { {1.0, 2.0}, {3.0, 4.0} };
    std::complex<double> c2[] = { {1.0, 1.0}, {3.0, 0.0} };
    myVector::Vector<std::complex<double>> cv1(2, c1);
    myVector::Vector<std::complex<double>> cv2(2, c2);

    cout << "\n=== COMPLEX VECTOR TESTS ===" << endl;
    cout << "cv1: " << cv1;
    cout << "cv2: " << cv2;
    auto cbis = vectorBisector(cv1, cv2);
    cout << "Vector bisector complex = " << cbis;

    // Test vector random
    cout << "\n=== RANDOM VECTOR TESTS ===" << endl;
    myVector::Vector<double> randomVec(3, -5.0, 5.0);
    cout << "Random vector: " << randomVec;

    return 0;
}
