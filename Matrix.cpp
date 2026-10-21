#include "Matrix.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace {
    // Допуск при сравнении чисел double
    const double EPS = 1e-9;

    // Чтобы в тексте не появлялось "-0.00"
    double shown(double x) {
        return std::fabs(x) < 0.005 ? 0.0 : x;
    }
}

// Определение статического поля (один раз, в .cpp)
int Matrix::objectCount = 0;

// ---------------------------------------------------------------
// Внутренние помощники
// ---------------------------------------------------------------

double Matrix::det() const {
    return a11 * a22 - a12 * a21;
}

std::string Matrix::str() const {
    std::ostringstream os;
    os << std::fixed << std::setprecision(2)
       << "[[" << shown(a11) << ", " << shown(a12) << "], ["
       << shown(a21) << ", " << shown(a22) << "]]";
    return os.str();
}

void Matrix::log(const std::string& text) {
    history.push_back(text);
}

void Matrix::addScalar(double value) {
    a11 += value;
    a12 += value;
    a21 += value;
    a22 += value;
}

void Matrix::multiplyBy(double b11, double b12, double b21, double b22) {
    double n11 = a11 * b11 + a12 * b21;
    double n12 = a11 * b12 + a12 * b22;
    double n21 = a21 * b11 + a22 * b21;
    double n22 = a21 * b12 + a22 * b22;
    a11 = n11;
    a12 = n12;
    a21 = n21;
    a22 = n22;
}

// ---------------------------------------------------------------
// Конструкторы и деструктор
// ---------------------------------------------------------------

// Основной конструктор, на него делегируют два других
Matrix::Matrix(double e11, double e12, double e21, double e22)
    : a11(e11), a12(e12), a21(e21), a22(e22),
      readCount(0), destructorLog(false)
{
    ++objectCount;
    log("created " + str());
}

Matrix::Matrix() : Matrix(0.0, 0.0, 0.0, 0.0) {}

Matrix::Matrix(double diagonal) : Matrix(diagonal, 0.0, 0.0, diagonal) {}

// Копия берёт элементы и историю, но счётчик чтений начинает с нуля,
// а сообщение в деструкторе у копии выключено
Matrix::Matrix(const Matrix& other)
    : a11(other.a11), a12(other.a12), a21(other.a21), a22(other.a22),
      history(other.history),
      readCount(0), destructorLog(false)
{
    ++objectCount;
}

Matrix::~Matrix() {
    if (destructorLog) {
        std::cout << "Matrix destroyed: " << str() << std::endl;
    }
    --objectCount;
}

// ---------------------------------------------------------------
// Чтение
// ---------------------------------------------------------------

double Matrix::at(int row, int col) const {
    ++readCount;   // меняем mutable-поле в const-методе
    if (row == 1 && col == 1) return a11;
    if (row == 1 && col == 2) return a12;
    if (row == 2 && col == 1) return a21;
    if (row == 2 && col == 2) return a22;
    std::cout << "Error: index (" << row << ", " << col
              << ") is out of range, use 1..2" << std::endl;
    return 0.0;
}

double Matrix::determinant() const {
    ++readCount;
    return det();
}

double Matrix::norm() const {
    ++readCount;
    return std::sqrt(a11 * a11 + a12 * a12 + a21 * a21 + a22 * a22);
}

int Matrix::getReadCount() const {
    return readCount;
}

int Matrix::getObjectCount() {
    return objectCount;
}

void Matrix::print() const {
    ++readCount;
    std::cout << str() << std::endl;
}

void Matrix::printHistory() const {
    ++readCount;
    std::cout << "History (" << history.size() << " entries):" << std::endl;
    for (std::size_t i = 0; i < history.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << history[i] << std::endl;
    }
}

void Matrix::setDestructorLog(bool enabled) {
    destructorLog = enabled;
}

// ---------------------------------------------------------------
// Унарные операции
// ---------------------------------------------------------------

Matrix& Matrix::operator++() {
    addScalar(1.0);
    log("prefix ++ -> " + str());
    return *this;
}

// Постфиксная форма возвращает копию состояния ДО изменения
Matrix Matrix::operator++(int) {
    Matrix old(*this);
    addScalar(1.0);
    log("postfix ++ -> " + str());
    return old;
}

Matrix& Matrix::operator--() {
    addScalar(-1.0);
    log("prefix -- -> " + str());
    return *this;
}

Matrix Matrix::operator--(int) {
    Matrix old(*this);
    addScalar(-1.0);
    log("postfix -- -> " + str());
    return old;
}