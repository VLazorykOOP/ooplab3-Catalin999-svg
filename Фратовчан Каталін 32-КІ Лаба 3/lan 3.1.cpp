#include <iostream>
#include <cmath>
#include <string>

using namespace std;

// Клас для представлення трикутника
class Triangle {
private:
    // Властивості трикутника
    double side_a, side_b, side_c; // Сторони трикутника
    string color;                 // Колір трикутника

    // Метод для перевірки коректності трикутника
    // Перевіряє, чи сторони задовольняють умовам існування трикутника
    bool is_valid_triangle(double a, double b, double c) const {
        return (a > 0 && b > 0 && c > 0) &&            // Усі сторони мають бути більше 0
            (a + b > c) && (a + c > b) && (b + c > a); // Сума двох сторін повинна бути більшою за третю
    }

public:
    // Конструктор за замовчуванням (створює трикутник зі сторонами 1 і білим кольором)
    Triangle() : side_a(1), side_b(1), side_c(1), color("білий") {}

    // Конструктор з параметрами
    Triangle(double a, double b, double c, const string& col) {
        // Якщо сторони валідні, встановлюємо значення
        if (is_valid_triangle(a, b, c)) {
            side_a = a;
            side_b = b;
            side_c = c;
            color = col;
        }
        else {
            // Якщо сторони некоректні, встановлюємо значення за замовчуванням
            cout << "Неможливо створити трикутник із заданими сторонами. Встановлено значення за замовчуванням." << endl;
            side_a = 1;
            side_b = 1;
            side_c = 1;
            color = "білий";
        }
    }

    // Метод для встановлення сторін трикутника
    void set_sides(double a, double b, double c) {
        // Перевірка коректності введених сторін
        if (is_valid_triangle(a, b, c)) {
            side_a = a;
            side_b = b;
            side_c = c;
        }
        else {
            // Якщо сторони некоректні, повідомляємо користувача
            cout << "Сторони некоректні. Умови існування трикутника порушені. Сторони не змінено." << endl;
        }
    }

    // Метод для встановлення кольору трикутника
    void set_color(const string& col) {
        color = col;
    }

    // Геттери для отримання сторін та кольору
    double get_side_a() const { return side_a; }
    double get_side_b() const { return side_b; }
    double get_side_c() const { return side_c; }
    string get_color() const { return color; }

    // Метод для обчислення периметра
    double calculate_perimeter() const {
        return side_a + side_b + side_c;
    }

    // Метод для обчислення площі (за формулою Герона)
    double calculate_area() const {
        double p = calculate_perimeter() / 2; // Напівпериметр
        return sqrt(p * (p - side_a) * (p - side_b) * (p - side_c)); // Формула Герона
    }

    // Метод для виведення інформації про трикутник
    void print_info() const {
        cout << "Трикутник:" << endl;
        cout << "Сторони: a = " << side_a << ", b = " << side_b << ", c = " << side_c << endl;
        cout << "Колір: " << color << endl;
        cout << "Периметр: " << calculate_perimeter() << endl;
        cout << "Площа: " << calculate_area() << endl;
    }
};

int main() {
    // Налаштування кодування для коректного виведення в Windows
    system("chcp 1251 > nul");
    setlocale(LC_CTYPE, "ukr");

    // Спроба створити трикутник із некоректними сторонами
    Triangle incorrect_triangle(1, 2, 10, "червоний"); // Некоректні сторони (1, 2, 10)
    cout << "Результат із некоректними сторонами:" << endl;
    incorrect_triangle.print_info(); // Інформація про трикутник (сторони за замовчуванням)
    cout << endl;

    // Встановлюємо правильні сторони
    incorrect_triangle.set_sides(6, 8, 10); // Прямокутний трикутник зі сторонами 6, 8, 10
    incorrect_triangle.set_color("синій"); // Змінюємо колір на "синій"
    cout << "Результат із правильними сторонами:" << endl;
    incorrect_triangle.print_info(); // Виводимо інформацію про трикутник з оновленими значеннями

    return 0;
}
