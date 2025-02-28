/*
Visitor is a behavioral design pattern that lets you separate algorithms from the objects on which they operate.
*/

#include <iostream>
#include <memory>
#include <vector>

// Forward declaration
class Circle;
class Rectangle;

// Visitor Interface
class IShapeVisitor
{
public:
    virtual void visit(std::shared_ptr<Circle> circle) = 0;
    virtual void visit(std::shared_ptr<Rectangle> rectangular) = 0;
    virtual ~IShapeVisitor() = default;
};

class Shape : public std::enable_shared_from_this<Shape>
{

public:
    virtual void accept(std::shared_ptr<IShapeVisitor> ShapeVisitor) = 0;
    virtual ~Shape() = default;
};

// Concrete Shape: Circle
class Circle : public Shape
{
public:
    float radius;
    void setradius(float radius)
    {
        this->radius = radius;
    }

    Circle(float radius) : radius(radius) {}
    void accept(std::shared_ptr<IShapeVisitor> ShapeVisitor) override
    {
        ShapeVisitor->visit(std::dynamic_pointer_cast<Circle>(shared_from_this()));
    }
};

// Concrete Shape: Circle
class Rectangle : public Shape
{
public:
    float width, height;
    void setdimention(float width, float height)
    {
        this->width = width;
        this->height = height;
    }

    Rectangle(float w, float h) : width(w), height(h) {}
    void accept(std::shared_ptr<IShapeVisitor> ShapeVisitor) override
    {
        ShapeVisitor->visit(std::dynamic_pointer_cast<Rectangle>(shared_from_this()));
    }
};

class AreaCalculator : public IShapeVisitor
{
public:
    void visit(std::shared_ptr<Circle> circle) override
    {
        float area = 3.14f * circle->radius * circle->radius;
        std::cout << "Circle Area: " << area << std::endl;
    }
    void visit(std::shared_ptr<Rectangle> rectangular) override
    {
        float area = rectangular->height * rectangular->width;
        std::cout << "rectangular Area: " << area << std::endl;
    }
};

// Visitor to Draw Shape
class ShapeDrawer : public IShapeVisitor
{
public:
    void visit(std::shared_ptr<Circle> circle) override
    {
        std::cout << "Drawing Circle with radius: " << circle->radius << std::endl;
    }

    void visit(std::shared_ptr<Rectangle> rectangular) override
    {
        std::cout << "Drawing Rectangle with width: " << rectangular->width
                  << " and height: " << rectangular->height << std::endl;
    }
};
int main(int argc, const char **argv)
{

    std::shared_ptr<Circle> circle = std::make_shared<Circle>(20);
    std::shared_ptr<Rectangle> rectangle = std::make_shared<Rectangle>(10, 20);

    std::shared_ptr<AreaCalculator> areacalculator = std::make_shared<AreaCalculator>();
    circle->accept(areacalculator);
    rectangle->accept(areacalculator);

    std::shared_ptr<ShapeDrawer> shapedrawer = std::make_shared<ShapeDrawer>();

    circle->accept(shapedrawer);
    rectangle->accept(shapedrawer);

    return 0;
}