#include <iostream>
#include "Matrix.h"

// Печатает имя и матрицу: "  a = [[1.00, 2.00], [3.00, 4.00]]"
void show(const char* name, const Matrix& m) {
    std::cout << "  " << name << " = ";
    m.print();
}

// Печатает выражение сравнения и его результат
void showBool(const char* expression, bool value) {
    std::cout << "  " << expression << " -> " << (value ? "true" : "false") << std::endl;
}

int main() {
    std::cout << "=== STEP 1: Constructors ===" << std::endl;
    Matrix zero;                    // конструктор по умолчанию
    Matrix scalar(3.0);             // explicit-конструктор: скалярная матрица
    Matrix a(1, 2, 3, 4);           // конструктор с четырьмя элементами
    Matrix b(2, 0, 1, 1);
    Matrix copy(a);                 // копирующий конструктор
    show("zero  ", zero);
    show("scalar", scalar);
    show("a     ", a);
    show("b     ", b);
    show("copy  ", copy);
    std::cout << "  Objects alive: " << Matrix::getObjectCount() << std::endl;

    std::cout << "\n=== STEP 2: Unary operators (all elements +1 / -1) ===" << std::endl;
    Matrix r1 = ++a;                // префикс: сначала изменяем, возвращаем новое значение
    std::cout << "  Matrix r1 = ++a;" << std::endl;
    show("a ", a);
    show("r1", r1);
    Matrix r2 = a++;                // постфикс: возвращаем старое значение, потом изменяем
    std::cout << "  Matrix r2 = a++;" << std::endl;
    show("a ", a);
    show("r2", r2);
    Matrix r3 = --a;
    std::cout << "  Matrix r3 = --a;" << std::endl;
    show("a ", a);
    show("r3", r3);
    Matrix r4 = a--;
    std::cout << "  Matrix r4 = a--;" << std::endl;
    show("a ", a);
    show("r4", r4);

    std::cout << "\n=== STEP 3: Compound assignment ===" << std::endl;
    show("a", a);
    show("b", b);
    a += b;
    std::cout << "  a += b;" << std::endl;
    show("a", a);
    a -= b;
    std::cout << "  a -= b;" << std::endl;
    show("a", a);
    a *= b;
    std::cout << "  a *= b;  (matrix product)" << std::endl;
    show("a", a);
    a /= b;
    std::cout << "  a /= b;  (multiply by inverse of b, returns the original a)" << std::endl;
    show("a", a);
    std::cout << "  a /= zero;  (singular matrix, must be rejected)" << std::endl;
    a /= zero;
    show("a", a);

    std::cout << "\n=== STEP 4: Binary arithmetic (built on +=, -=, *=, /=) ===" << std::endl;
    Matrix sum  = a + b;
    Matrix diff = a - b;
    Matrix prod = a * b;
    Matrix quot = a / b;
    show("a + b", sum);
    show("a - b", diff);
    show("a * b", prod);
    show("a / b", quot);
    Matrix chain = a + b + b;
    show("a + b + b", chain);
    std::cout << "  Operands are not changed:" << std::endl;
    show("a", a);
    show("b", b);

    std::cout << "\n=== STEP 5: Comparison (by determinants) ===" << std::endl;
    Matrix e(2, 0, 0, -1);          // другие элементы, но такой же определитель, как у a
    std::cout << "  det(a) = " << a.determinant()
              << ", det(b) = " << b.determinant()
              << ", det(e) = " << e.determinant() << std::endl;
    showBool("a <  b", a < b);
    showBool("a >  b", a > b);
    showBool("a <= b", a <= b);
    showBool("a >= b", a >= b);
    showBool("a == b", a == b);
    showBool("a != b", a != b);
    std::cout << "  e has other elements but the same determinant as a:" << std::endl;
    show("e", e);
    showBool("a == e", a == e);
    showBool("a != e", a != e);
    showBool("a <= e", a <= e);
    showBool("a >= e", a >= e);

    std::cout << "\n=== END ===" << std::endl;
    return 0;
}