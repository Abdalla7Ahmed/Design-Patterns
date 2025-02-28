/*
The Iterator pattern is a behavioral design pattern that provides a way to access
elements of a collection sequentially without exposing its underlying representation.
It decouples collection traversal logic from the actual collection structure, making it more flexible and extensible.

🎯 Problem Solved by the Iterator Pattern

Imagine you have different types of collections like:
✅ Arrays
✅ Linked Lists
✅ Trees

Each has a different way of iterating, but you want a uniform way to access elements without worrying about how the collection is implemented.


📌 Where is it Used?

✅ Standard C++ STL Containers (e.g., std::vector, std::list, std::map)
✅ Custom Data Structures (e.g., a custom linked list, tree traversal)
✅ Database Record Iterators (e.g., fetching rows one by one)
✅ File System Navigation (e.g., iterating over files in a directory)

🚫 Drawbacks of the Iterator Pattern

❌ Extra Memory Overhead (if storing additional state)
❌ Can Complicate Concurrency (if multiple iterators modify the same collection)
❌ Not Always the Most Efficient Traversal Method (depends on the collection type)
*/

#include <iostream>
#include <memory>
#include <vector>

class Book
{
public:
    std::string title;
    explicit Book(const std::string &t) : title(t) {}
};

// **Iterator Interface**
class IIterator
{
public:
    virtual bool hasNext() const = 0;
    virtual std::shared_ptr<Book> next() = 0;
    virtual ~IIterator() = default;
};

class BookIterator : public IIterator
{
private:
    std::vector<std::shared_ptr<Book>> &books;
    size_t index;

public:
    explicit BookIterator(std::vector<std::shared_ptr<Book>> &b) : books(b), index(0) {}

    bool hasNext() const override
    {
        return index < books.size();
    }

    std::shared_ptr<Book> next() override
    {
        return hasNext() ? books[index++] : nullptr;
    }
};

// **Book Collection (Aggregate)**
class BookCollection
{
private:
    std::vector<std::shared_ptr<Book>> books;

public:
    void addBook(const std::string &title)
    {
        books.push_back(std::make_shared<Book>(title));
    }

    std::shared_ptr<IIterator> createIterator()
    {
        return std::make_shared<BookIterator>(books);
    }
};

int main()
{

    std::unique_ptr<BookCollection> library = std::make_unique<BookCollection>();
    library->addBook("C++ Design Patterns");
    library->addBook("Advanced C++");
    library->addBook("Effective Modern C++");

    auto iterator = library->createIterator();
    while (iterator->hasNext())
    {
        std::cout << "Book: " << iterator->next()->title << "\n";
    }

    return 0;
}