# Лабораторная работа №3

```cpp
class Point {
public:
    Point(double x, double y);
    virtual ~Point() = default;

    double getX();
    double getY();

    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void rotate(double angle) = 0;

protected:
    double x_, y_;
};
```
Point - Абстрактный базовый класс для представления точки на плоскости.

Point(double x, double y) - Конструктор, инициализирующий координаты точки.
double getX() - Метод для получения координаты x.
double getY() - Метод для получения координаты y.
virtual void draw(sf::RenderWindow& window) = 0 - Чисто виртуальный метод для отрисовки фигуры.
virtual void move(double dx, double dy) = 0 - Чисто виртуальный метод для перемещения фигуры.
virtual void rotate(double angle) = 0 - Чисто виртуальный метод для вращения фигуры.

Line - Класс для представления линии, унаследованный от Point.

Line(double x1, double y1, double x2, double y2) - Конструктор, инициализирующий координаты начала и конца линии.
void rotateAroundPoint(double cx, double cy, double angle) - Метод для вращения линии вокруг заданной точки.
void draw(sf::RenderWindow& window) override - Метод для отрисовки линии.
void move(double dx, double dy) override - Метод для перемещения линии.
void rotate(double angle) override - Метод для вращения линии вокруг её первой точки.

Parallelogram - Класс для представления параллелограмма, унаследованный от Point.

Parallelogram(double x1, double y1, double x2, double y2, double w) - Конструктор, инициализирующий координаты и ширину параллелограмма.
~Parallelogram() - Деструктор, освобождающий память, выделенную под линии.
void draw(sf::RenderWindow& window) override - Метод для отрисовки параллелограмма.
void move(double dx, double dy) override - Метод для перемещения параллелограмма.
void rotate(double angle) override - Метод для вращения параллелограмма.

Square - Класс для представления квадрата, унаследованный от Parallelogram.

Square(double x1, double y1, double side) - Конструктор, инициализирующий координаты и сторону квадрата.
~Square() - Деструктор, освобождающий память, выделенную под линии.
void draw(sf::RenderWindow& window) override - Метод для отрисовки квадрата.
void move(double dx, double dy) override - Метод для перемещения квадрата.
void rotate(double angle) override - Метод для вращения квадрата.

Rectangle - Класс для представления прямоугольника, унаследованный от Parallelogram.

Rectangle(double x1, double y1, double w, double h) - Конструктор, инициализирующий координаты, ширину и высоту прямоугольника.
~Rectangle() - Деструктор, освобождающий память, выделенную под линии.
void draw(sf::RenderWindow& window) override - Метод для отрисовки прямоугольника.
void move(double dx, double dy) override - Метод для перемещения прямоугольника.
void rotate(double angle) override - Метод для вращения прямоугольника.

Rhombus - Класс для представления ромба, унаследованный от Parallelogram.

Rhombus(double x1, double y1, double side, double angle) - Конструктор, инициализирующий координаты, сторону и угол ромба.
~Rhombus() - Деструктор, освобождающий память, выделенную под линии.
void draw(sf::RenderWindow& window) override - Метод для отрисовки ромба.
void move(double dx, double dy) override - Метод для перемещения ромба.
void rotate(double angle) override - Метод для вращения ромба.
