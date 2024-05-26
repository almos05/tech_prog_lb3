#include "SFML/Graphics.hpp"
#include "iostream"
#include "cmath"

class Point {
public:
    Point(double x, double y) : x_(x), y_(y) {};
    virtual ~Point() = default;

    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void rotate(double angle) = 0;

protected:
    double x_, y_;
};

class Line : public Point {
public:
    Line(double x1, double y1, double x2, double y2) : Point(x1, y1), x2_(x2), y2_(y2) {}
    void rotateAroundPoint(double cx, double cy, double angle);

    void draw(sf::RenderWindow& window) override {
        sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x_, y_)), sf::Vertex(sf::Vector2f(x2_, y2_))
        };

        window.draw(line, 2, sf::Lines);
        //line: Массив объектов sf::Vertex, представляющий вершины, которые будут отрисованы.
        //2: Целое число, указывающее количество вершин в массиве.
        //sf::Lines: Перечисление, указывающее тип примитива, который будет нарисован.
    }

    void move(double dx, double dy) override {
        x_ += dx;
        y_ += dy;
        x2_ += dx;
        y2_ += dy;
    }

    void rotate(double angle) override {
        double radians = angle * M_PI / 180.0;
        double s = sin(radians);
        double c = cos(radians);

        // Перемещение второй точки относительно первой
        double x2_rel = x2_ - x_;
        double y2_rel = y2_ - y_;

        // Вращение второй точки
        double x2_new = x2_rel * c - y2_rel * s;
        double y2_new = x2_rel * s + y2_rel * c;

        // Возвращение на исходные координаты
        x2_ = x_ + x2_new;
        y2_ = y_ + y2_new;
    }

protected:
    double x2_, y2_;

};

void Line::rotateAroundPoint(double angle, double cx, double cy) {
    double radians = angle * M_PI / 180.0;
    double s = sin(radians);
    double c = cos(radians);

    // Перемещение первой точки относительно центра
    double x1_rel = x_ - cx;
    double y1_rel = y_ - cy;

    // Вращение первой точки
    double x1_new = x1_rel * c - y1_rel * s;
    double y1_new = x1_rel * s + y1_rel * c;

    // Возвращение на исходные координаты
    x_ = cx + x1_new;
    y_ = cy + y1_new;

    // Перемещение второй точки относительно центра
    double x2_rel = x2_ - cx;
    double y2_rel = y2_ - cy;

    // Вращение второй точки
    double x2_new = x2_rel * c - y2_rel * s;
    double y2_new = x2_rel * s + y2_rel * c;

    // Возвращение на исходные координаты
    x2_ = cx + x2_new;
    y2_ = cy + y2_new;
}

class Parallelogram : public virtual Point {
public:
    Parallelogram(double x1, double y1, double x2, double y2, double w) : Point(x1, y1), w_(w) {

        lines_[0] = new Line(x1, y1, x2, y2);
        lines_[1] = new Line(x2 + w_, y2, x2, y2);
        lines_[2] = new Line(x1, y1, x1 + w_, y1);
        lines_[3] = new Line(x1 + w, y1, x2 + w, y2);
    }

    ~Parallelogram() {
        for (auto line : lines_) {
            delete line;
        }
    }

    void draw(sf::RenderWindow& window) override {
        for (auto& line : lines_){
            line->draw(window);
        }
    }

    void move(double dx, double dy) override {
        for (auto& line : lines_) {
            line->move(dx, dy);
        }
        x_ += dx;
        y_ += dy;
    }

    void rotate(double angle) override {
        for (auto& line : lines_) {
            line->rotateAroundPoint(angle, x_, y_);
        }
    }

protected:
    Line* lines_[4];
    double w_;
};

class Square : public virtual Point, public Parallelogram {
public:
    Square(double x1, double y1, double side) : Point(x1, y1), Parallelogram(x1, y1, x1, y1 + side, side) {
        w_ = side;
        double x2 = x1;
        double y2 = y1 + side;
        lines_[0] = new Line(x1, y1, x2, y2);
        lines_[1] = new Line(x2, y2, x2 + w_, y2);
        lines_[2] = new Line(x1 + w_, y1, x2 + w_, y2);
        lines_[3] = new Line(x1, y1, x1 + w_, y1);
    }

    ~Square() {
        for (auto line : lines_) {
            delete line;
        }
    }

    void draw(sf::RenderWindow& window) override {
        for (auto& line : lines_) {
            line->draw(window);
        }
    }

    void move(double dx, double dy) override {
        for (auto& line : lines_) {
            line->move(dx, dy);
        }
        x_ += dx;
        y_ += dy;
    }

    void rotate(double angle) override {
        for (auto& line : lines_) {
            line->rotateAroundPoint(angle, x_, y_);
        }
    }

protected:
    Line* lines_[4];
    double w_;

};

class Rectangle : public Parallelogram {
public:
    Rectangle(double x1, double y1, double w, double h) : Point(x1, y1), Parallelogram(x1, y1, x1, y1 + h, w) {
        w_ = w;
        double x2 = x1;
        double y2 = y1 + h;

        lines_[0] = new Line(x1, y1, x2, y2);
        lines_[1] = new Line(x2, y2, x2 + w_, y2);
        lines_[2] = new Line(x1 + w_, y1, x2 + w_, y2);
        lines_[3] = new Line(x1, y1, x1 + w_, y1);
    }

    ~Rectangle() {
        for (auto line : lines_) {
            delete line;
        }
    }

    void draw(sf::RenderWindow& window) override {
        for (auto& line : lines_) {
            line->draw(window);
        }
    }

    void move(double dx, double dy) override {
        for (auto& line : lines_) {
            line->move(dx, dy);
        }
        x_ += dx;
        y_ += dy;
    }

    void rotate(double angle) override {
        for (auto& line : lines_) {
            line->rotateAroundPoint(angle, x_, y_);
        }
    }
protected:
    Line* lines_[4];
    double w_;
};

class Rhombus : public Parallelogram {
public:
    Rhombus(double x1, double y1, double side, double angle) : Point(x1, y1), side_(side), angle_(angle), Parallelogram(x1, y1, x1 + side * cos(angle * M_PI / 180.0), y1 + side * sin(angle * M_PI / 180.0), side * cos((180.0 - angle) * M_PI / 180.0)) {
        double x2 = x1 + side * cos(angle * M_PI / 180.0);
        double y2 = y1 + side * sin(angle * M_PI / 180.0);

        lines_[0] = new Line(x1, y1, x2, y2);
        lines_[1] = new Line(x2, y2, x2 + side * cos((180.0 - angle) * M_PI / 180.0), y2 + side * sin((180.0 - angle) * M_PI / 180.0));
        lines_[2] = new Line(x1, y1, x1 + side * cos((180.0 - angle) * M_PI / 180.0), y1 + side * sin((180.0 - angle) * M_PI / 180.0));
        lines_[3] = new Line(x1 + side * cos((180.0 - angle) * M_PI / 180.0), y1 + side * sin((180.0 - angle) * M_PI / 180.0), x2 + side * cos((180.0 - angle) * M_PI / 180.0), y2 + side * sin((180.0 - angle) * M_PI / 180.0));
    }

    ~Rhombus() {
        for (auto line : lines_) {
            delete line;
        }
    }

    void draw(sf::RenderWindow& window) override {
        for (auto& line : lines_) {
            line->draw(window);
        }
    }

    void move(double dx, double dy) override {
        for (auto& line : lines_) {
            line->move(dx, dy);
        }
        x_ += dx;
        y_ += dy;
    }

    void rotate(double angle) override {
        for (auto& line : lines_) {
            line->rotateAroundPoint(angle, x_, y_);
        }
    }

protected:
    Line* lines_[4];
    double side_;
    double angle_;
};

void clearShapes(std::vector<Point*>& shapes) {
    for (auto shape : shapes) {
        delete shape;
    }
    shapes.clear();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "my_draws");

    std::vector<Point*> shapes;
    Line* line = nullptr;
    Parallelogram* parallelogram = nullptr;
    Square* square = nullptr;
    Rectangle* rectangle = nullptr;
    Rhombus* rhombus = nullptr;

    bool lineVisible = false;
    bool parallelogramVisible = false;
    bool squareVisible = false;
    bool rectangleVisible = false;
    bool rhombusVisible = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Обработка клавиш для отображения/удаления фигур
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::L) {
                    if (lineVisible) {
                        shapes.erase(std::remove(shapes.begin(), shapes.end(), line), shapes.end());
                        delete line;
                        line = nullptr;
                        lineVisible = false;
                    } else {
                        line = new Line(100, 200, 300, 400);
                        shapes.push_back(line);
                        lineVisible = true;
                    }
                }
                if (event.key.code == sf::Keyboard::P) {
                    if (parallelogramVisible) {
                        shapes.erase(std::remove(shapes.begin(), shapes.end(), parallelogram), shapes.end());
                        delete parallelogram;
                        parallelogram = nullptr;
                        parallelogramVisible = false;
                    } else {
                        parallelogram = new Parallelogram(0, 0, 150, 100, 250);
                        shapes.push_back(parallelogram);
                        parallelogramVisible = true;
                    }
                }
                if (event.key.code == sf::Keyboard::S) {
                    if (squareVisible) {
                        shapes.erase(std::remove(shapes.begin(), shapes.end(), square), shapes.end());
                        delete square;
                        square = nullptr;
                        squareVisible = false;
                    } else {
                        square = new Square(0, 0, 100);
                        shapes.push_back(square);
                        squareVisible = true;
                    }
                }
                if (event.key.code == sf::Keyboard::R) {
                    if (rectangleVisible) {
                        shapes.erase(std::remove(shapes.begin(), shapes.end(), rectangle), shapes.end());
                        delete rectangle;
                        rectangle = nullptr;
                        rectangleVisible = false;
                    } else {
                        rectangle = new Rectangle(0, 0, 250, 100);
                        shapes.push_back(rectangle);
                        rectangleVisible = true;
                    }
                }
                if (event.key.code == sf::Keyboard::H) { // Для ромба использую H
                    if (rhombusVisible) {
                        shapes.erase(std::remove(shapes.begin(), shapes.end(), rhombus), shapes.end());
                        delete rhombus;
                        rhombus = nullptr;
                        rhombusVisible = false;
                    } else {
                        rhombus = new Rhombus(0, 0, 100, 30);
                        shapes.push_back(rhombus);
                        rhombusVisible = true;
                    }
                }
                if (event.key.code == sf::Keyboard::C) {
                    clearShapes(shapes);
                    lineVisible = parallelogramVisible = squareVisible = rectangleVisible = rhombusVisible = false;
                }
            }
        }

        // Обработка ввода пользователя для перемещения всех видимых фигур
        double dx = 0, dy = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            dx = -0.2;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            dx = 0.2;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            dy = -0.2;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            dy = 0.2;
        }
        for (auto& shape : shapes) {
            shape->move(dx, dy);
        }

        // Обработка ввода пользователя для вращения всех видимых фигур
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            for (auto& shape : shapes) {
                shape->rotate(-0.2);  // Вращение против часовой стрелки
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            for (auto& shape : shapes) {
                shape->rotate(0.2);   // Вращение по часовой стрелке
            }
        }

        window.clear();
        for (auto shape : shapes) {
            shape->draw(window);
        }
        window.display();
    }

    clearShapes(shapes);
    return 0;
}
