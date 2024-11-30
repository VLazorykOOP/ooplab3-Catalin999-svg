#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <locale> // Для використання setlocale

using namespace std; // Використання стандартного простору імен

class Matrix {
private:
    int** data;             // Динамічний масив для зберігання елементів матриці
    size_t rows;            // Кількість рядків
    size_t cols;            // Кількість стовпців
    static size_t objectCount; // Лічильник об'єктів

    // Виділення пам'яті для матриці
    void allocateMemory(size_t r, size_t c) {
        rows = r;
        cols = c;
        data = new int* [rows];
        for (size_t i = 0; i < rows; ++i) {
            data[i] = new int[cols](); // Ініціалізація нулями
        }
    }

    // Звільнення пам'яті
    void freeMemory() {
        for (size_t i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

public:
    // Конструктор без параметрів: матриця 3x3, заповнена нулями
    Matrix() : rows(3), cols(3) {
        allocateMemory(3, 3);
        ++objectCount;
    }

    // Конструктор з одним параметром: квадратна матриця n x n, заповнена нулями
    Matrix(size_t n) : rows(n), cols(n) {
        allocateMemory(n, n);
        ++objectCount;
    }

    // Конструктор із трьома параметрами: розміри n x m, заповнення значенням value
    Matrix(size_t n, size_t m, int value) : rows(n), cols(m) {
        allocateMemory(n, m);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                data[i][j] = value;
            }
        }
        ++objectCount;
    }

    // Конструктор копіювання
    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        allocateMemory(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
        ++objectCount;
    }

    // Конструктор переміщення
    Matrix(Matrix&& other) noexcept
        : data(other.data), rows(other.rows), cols(other.cols) {
        other.data = nullptr;
        other.rows = 0;
        other.cols = 0;
        ++objectCount;
    }

    // Оператор присвоєння
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            freeMemory();
            rows = other.rows;
            cols = other.cols;
            allocateMemory(rows, cols);
            for (size_t i = 0; i < rows; ++i) {
                for (size_t j = 0; j < cols; ++j) {
                    data[i][j] = other.data[i][j];
                }
            }
        }
        return *this;
    }

    // Оператор переміщення
    Matrix& operator=(Matrix&& other) noexcept {
        if (this != &other) {
            freeMemory();
            data = other.data;
            rows = other.rows;
            cols = other.cols;
            other.data = nullptr;
            other.rows = 0;
            other.cols = 0;
        }
        return *this;
    }

    // Деструктор: звільняє пам'ять
    ~Matrix() {
        freeMemory();
        --objectCount;
    }

    // Присвоєння значення елементу
    void setElement(size_t i, size_t j, int value = 0) {
        if (i >= rows || j >= cols) {
            throw out_of_range("Індекс виходить за межі матриці");
        }
        data[i][j] = value;
    }

    // Отримання значення елементу
    int getElement(size_t i, size_t j) const {
        if (i >= rows || j >= cols) {
            throw out_of_range("Індекс виходить за межі матриці");
        }
        return data[i][j];
    }

    // Виведення матриці
    void print() const {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                cout << setw(5) << data[i][j];
            }
            cout << endl;
        }
    }

    // Додавання матриць
    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Розміри матриць мають співпадати для додавання");
        }
        Matrix result(rows, cols, 0);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // Віднімання матриць
    Matrix operator-(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Розміри матриць мають співпадати для віднімання");
        }
        Matrix result(rows, cols, 0);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    // Множення матриць
    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            throw invalid_argument("Розміри матриць мають узгоджуватись для множення");
        }
        Matrix result(rows, other.cols, 0);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other.cols; ++j) {
                for (size_t k = 0; k < cols; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    // Множення на скаляр
    Matrix operator*(short scalar) const {
        Matrix result(rows, cols, 0);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] * scalar;
            }
        }
        return result;
    }

    // Отримання кількості об'єктів
    static size_t getObjectCount() {
        return objectCount;
    }
};

// Ініціалізація статичного члена
size_t Matrix::objectCount = 0;

// Тестування
int main() {
    setlocale(LC_CTYPE, "ukr"); // Підтримка української мови в консолі

    try {
        Matrix m1; // Створення матриці 3x3
        Matrix m2(4); // Квадратна матриця 4x4
        Matrix m3(3, 4, 7); // Матриця 3x4, заповнена 7

        m1.print();
        cout << "-------" << endl;
        m2.print();
        cout << "-------" << endl;
        m3.print();
        cout << "-------" << endl;

        m1.setElement(1, 1, 5); // Зміна значення елемента
        m1.print();

        Matrix m4 = m1 + m1; // Додавання матриць
        m4.print();

        Matrix m5 = m3 * 2; // Множення на скаляр
        m5.print();

        cout << "Активні об'єкти: " << Matrix::getObjectCount() << endl; // Кількість об'єктів
    }
    catch (const exception& e) {
        cerr << "Помилка: " << e.what() << endl;
    }
    return 0;
}
