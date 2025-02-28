
**Factory Method** is a creational design pattern that provides an interface for creating objects in a superclass, but allows subclasses to alter the type of objects that will be created.


## Structure

![screen](./images/3.1.png)
1-The **Product** declares the interface, which is common to all objects that can be produced by the creator and its subclasses.
2-**Concrete Products** are different implementations of the product interface.
3-The **Creator** class declares the factory method that returns new product objects. It’s important that the return type of this method matches the product interface.
You can declare the factory method as `abstract` to force all subclasses to implement their own versions of the method. As an alternative, the base factory method can return some default product type.
4-- **Concrete Creators** override the base factory method so it returns a different type of product.
Note that the factory method doesn’t have to **create** new instances all the time. It can also return existing objects from a cache, an object pool, or another source.

## Applicability
1-Use the Factory Method when you don’t know beforehand the exact types and dependencies of the objects your code should work with.
	The Factory Method separates product construction code from the code that actually uses the product. Therefore it’s easier to extend the product construction code independently from the rest of the code.
2-Use the Factory Method when you want to provide users of your library or framework with a way to extend its internal components.
3-Use the Factory Method when you want to save system resources by reusing existing objects instead of rebuilding them each time.



## Core Components of the Factory Method Pattern in C++

Let’s break down the key participants of the Factory Method Pattern:

****1. Creator (Abstract Creator)****

- ****Description:**** An abstract class or interface responsible for declaring the factory method, which returns an object of a product type. The Creator Class can also contain other method that rely on the factory method to create objects.
- ****Purpose:**** Provides a common interface for creating objects, but the specific object creation is defereed to concrete creators.

****2. Concrete Creator:****

- ****Description:**** Concrete subclasses of the Creator. Each concrete creator implements the factory method declared in the abstract creator, returning a specific type of product.
- ****Purpose:**** Responsible for creating instances of concrete products, thus encapsulating the actual object creation logic.

****3. Product(Abstract Product):****

- ****Description:**** The abstract class or interface for the objects the factory method creates. It defines the common interface that all products must implement.
- ****Purpose:**** Specifies the interface that concrete products must adhere to, ensuring that they have a consistent set of methods.

****4. Concrete Product:****

- ****Description:**** Concrete implementations of the Product interface. Each concrete product represents a distinct type of object.
- ****Purpose:**** Defines the acutal objects that the factory method creates. Each concrete product has its own implementation of the methods specified in teh Product interface.

****5. Client:****

- ****Description:**** The client code interacts with the Creator through the abstarct Creator class and relies on the factory method to create instances of products.
- ****Purpose:**** Utilizes the factory method pattern to create objects without needing to know specific class of objects being created, promoting flexibility and decoupling between the client and product classes.

## Implementation of the Factory Method Pattern in C++

Let’s implement the Factory Method Pattern in C++ step by step, explaining each part in detail. In this example, we’ll create a simple shape factory that produces different shapes (e.g., Circle and Square).

### Step 1: Define the Abstract Product (Shape)
```c++
// Abstract product 
class class Shape { 
public:
	virtual void draw() = 0;
	virtual ~Shape() {} // Virtual destructor for polymorphism 
	}; 
```

### Step 2: Define Concrete Products (Circle and Square)

```c++
// Concrete product class - Circle
class Circle : public Shape {
public:
    void draw() override {
        std::cout<<"Drawing a Circle"<< std::endl;
    }
};

// Concrete product class - Square
class Square : public Shape {
public:
    void draw() override {
        std::cout<<"Drawing a Square"<<std::endl;
    }
};

```

### Step 3: Define the Abstract Creator

```c++
// Abstract creator class
class ShapeFactory {
public:
    virtual Shape* createShape() = 0;
    virtual ~ShapeFactory() {} // Virtual destructor for polymorphism
};
```

### Step 4: Define Concrete Creators (CircleFactory and Square Factory)

```c++
// Concrete creator class - CircleFactory
class CircleFactory : public ShapeFactory {
public:
    Shape* createShape() override {
        return new Circle();
    }
};

// Concrete creator class - SquareFactory
class SquareFactory : public ShapeFactory {
public:
    Shape* createShape() override {
        return new Square();
    }
};

```

### Step 5: Client Code

```c++
int main() {
    ShapeFactory* circleFactory = new CircleFactory();
    ShapeFactory* squareFactory = new SquareFactory();

    Shape* circle = circleFactory->createShape();
    Shape* square = squareFactory->createShape();

    circle->draw(); // Output: Drawing a Circle
    square->draw(); // Output: Drawing a Square

    delete circleFactory;
    delete squareFactory;
    delete circle;
    delete square;

    return 0;
}

```