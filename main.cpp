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

// Функция принимает Matrix; нужна, чтобы показать работу explicit
void takesMatrix(const Matrix& m) {
    std::cout << "  takesMatrix got ";
    m.print();
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

    std::cout << "\n=== STEP 6: explicit and conversions ===" << std::endl;
    double d = static_cast<double>(a);      // явное преобразование: определитель
    std::cout << "  static_cast<double>(a) = " << d << " (determinant)" << std::endl;
    Matrix s2(2.0);                         // прямая инициализация explicit-конструктора
    show("Matrix s2(2.0)", s2);
    Matrix shifted = a + Matrix(2.0);       // число нужно превратить в Matrix явно
    show("a + Matrix(2.0)", shifted);
    takesMatrix(Matrix(5.0));               // явное преобразование разрешено
    std::cout << "  These lines do NOT compile because of explicit (uncomment to check):" << std::endl;
    std::cout << "    Matrix m = 5.0;        // explicit constructor" << std::endl;
    std::cout << "    Matrix m = a + 2.0;    // no implicit double -> Matrix" << std::endl;
    std::cout << "    takesMatrix(5.0);      // no implicit double -> Matrix" << std::endl;
    std::cout << "    double x = a;          // explicit operator double" << std::endl;
    // Matrix m1 = 5.0;
    // Matrix m2 = a + 2.0;
    // takesMatrix(5.0);
    // double x = a;

    std::cout << "\n=== STEP 7: const object with a mutable field ===" << std::endl;
    const Matrix c(1, 2, 3, 4);             // const-объект: менять элементы нельзя
    std::cout << "  Reads before: " << c.getReadCount() << std::endl;
    std::cout << "  c = ";
    c.print();                              // mutable-поле readCount растёт, хотя объект const
    std::cout << "  det(c) = " << c.determinant() << std::endl;
    std::cout << "  norm(c) = " << c.norm() << std::endl;
    std::cout << "  c(2,1) = " << c.at(2, 1) << std::endl;
    std::cout << "  Asking for c(3,1), which does not exist:" << std::endl;
    double missing = c.at(3, 1);
    std::cout << "  c(3,1) returned " << missing << std::endl;
    std::cout << "  Reads after: " << c.getReadCount() << std::endl;

    std::cout << "\n=== STEP 8: History of operations ===" << std::endl;
    std::cout << "  History of a:" << std::endl;
    a.printHistory();

    std::cout << "\n=== STEP 9: Static counter and destructor ===" << std::endl;
    std::cout << "  Objects alive before block: " << Matrix::getObjectCount() << std::endl;
    {
        Matrix tmp(7, 7, 7, 7);
        tmp.setDestructorLog(true);         // для этого объекта деструктор напечатает сообщение
        std::cout << "  Objects alive inside block: " << Matrix::getObjectCount() << std::endl;
    }                                       // здесь tmp уничтожается
    std::cout << "  Objects alive after block: " << Matrix::getObjectCount() << std::endl;

    std::cout << "\n=== END ===" << std::endl;
    return 0;
}