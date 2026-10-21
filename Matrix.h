#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include <vector>

// Матрица 2x2:  | a11 a12 |
//               | a21 a22 |
class Matrix {
private:
    double a11, a12, a21, a22;              // элементы матрицы
    std::vector<std::string> history;       // история операций над этим объектом
    mutable int readCount;                  // сколько раз матрицу читали (меняется даже у const-объекта)
    bool destructorLog;                     // печатать ли сообщение в деструкторе

    static int objectCount;                 // количество существующих объектов Matrix

    // Внутренние помощники (снаружи не нужны)
    double det() const;                     // определитель без учёта счётчика чтений
    std::string str() const;                // текст вида [[1.00, 2.00], [3.00, 4.00]]
    void log(const std::string& text);      // добавить запись в историю
    void addScalar(double value);           // прибавить число ко всем элементам
    void multiplyBy(double b11, double b12, double b21, double b22); // умножить справа на матрицу

public:
    // Конструкторы
    Matrix();                                                   // нулевая матрица
    explicit Matrix(double diagonal);                           // скалярная матрица: diagonal на главной диагонали
    Matrix(double e11, double e12, double e21, double e22);     // матрица с заданными элементами
    Matrix(const Matrix& other);                                // копирующий (нужен для счётчика объектов)
    ~Matrix();

    // Чтение (все const)
    double at(int row, int col) const;      // элемент, строки и столбцы нумеруются с 1
    double determinant() const;
    double norm() const;                    // норма Фробениуса
    int getReadCount() const;
    static int getObjectCount();
    void print() const;
    void printHistory() const;

    // Единственный не-const метод настройки: включает сообщение в деструкторе
    void setDestructorLog(bool enabled);

    // Унарные операции: все элементы +1 / -1
    Matrix& operator++();                   // префиксный ++
    Matrix operator++(int);                 // постфиксный ++
    Matrix& operator--();                   // префиксный --
    Matrix operator--(int);                 // постфиксный --

    // Арифметическое присваивание
    Matrix& operator+=(const Matrix& rhs);
    Matrix& operator-=(const Matrix& rhs);
    Matrix& operator*=(const Matrix& rhs);  // A = A * B
    Matrix& operator/=(const Matrix& rhs);  // A = A * B^(-1), если B вырожденная, операция отклоняется

    // Явное преобразование в число: определитель
    explicit operator double() const;

    // Сравнение матриц по определителям (нужен доступ к приватному det())
    friend bool operator==(const Matrix& lhs, const Matrix& rhs);
    friend bool operator!=(const Matrix& lhs, const Matrix& rhs);
    friend bool operator<(const Matrix& lhs, const Matrix& rhs);
    friend bool operator>(const Matrix& lhs, const Matrix& rhs);
    friend bool operator<=(const Matrix& lhs, const Matrix& rhs);
    friend bool operator>=(const Matrix& lhs, const Matrix& rhs);
};

// Бинарные арифметические операции (реализованы через +=, -=, *=, /=)
Matrix operator+(Matrix lhs, const Matrix& rhs);
Matrix operator-(Matrix lhs, const Matrix& rhs);
Matrix operator*(Matrix lhs, const Matrix& rhs);
Matrix operator/(Matrix lhs, const Matrix& rhs);

#endif // MATRIX_H
