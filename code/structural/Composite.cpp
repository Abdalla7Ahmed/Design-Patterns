

#include <iostream>
#include <vector>
#include <string>
#include <memory>
// Component: Common interface for both Files and Directories
class FileSystemItem
{
public:
    virtual ~FileSystemItem() {}
    virtual void display(int indent = 0) const = 0; // Abstract operation to display items
};

// Leaf: Represents a File
class File : public FileSystemItem
{
private:
    std::string name;

public:
    File(const std::string &fileName) : name(fileName) {}

    void display(int indent = 0) const override
    {
        for (int i = 0; i < indent; ++i)
            std::cout << "  "; // Indentation for hierarchy visualization
        std::cout << "- " << name << std::endl;
    }
};

// Composite: Represents a Directory that can contain Files and other Directories
class Directory : public FileSystemItem
{
private:
    std::string name;
    std::vector<std::shared_ptr<FileSystemItem>> items; // Stores child FileSystemItems (both Files and Directories)

public:
    Directory(const std::string &dirName) : name(dirName) {}

    void addItem(std::shared_ptr<FileSystemItem> item)
    {
        items.push_back(item); // Add a File or Directory
    }

    void display(int indent = 0) const override
    {
        for (int i = 0; i < indent; ++i)
            std::cout << "  ";
        std::cout << "+ " << name << std::endl; // Display the directory name

        // Display contents of the directory with increased indentation
        for (const auto &item : items)
        {
            item->display(indent + 1); // Recursive call to display children
        }
    }

    ~Directory() = default;
};

int main()
{
    // Create files
    std::shared_ptr<FileSystemItem> file1 = std::make_shared<File>("file1.txt");
    std::shared_ptr<FileSystemItem> file2 = std::make_shared<File>("file2.txt");
    std::shared_ptr<FileSystemItem> file3 = std::make_shared<File>("file3.txt");
    // Create directories
    std::shared_ptr<Directory> dir1 = std::make_shared<Directory>("Documents");
    std::shared_ptr<Directory> dir2 = std::make_shared<Directory>("Music");

    // Add files to the directories
    dir1->addItem(file1);
    dir1->addItem(file2);
    dir2->addItem(file3);
    // Create a root directory and add subdirectories to it
    std::shared_ptr<Directory> root = std::make_shared<Directory>("Root");
    std::shared_ptr<FileSystemItem> file4 = std::make_shared<File>("file4.txt");
    root->addItem(file4);
    root->addItem(dir1);
    root->addItem(dir2);

    // Display the entire file system
    root->display();

    /*

    + Root
      - file4.txt
      + Documents
        - file1.txt
        - file2.txt
      + Music
        - file3.txt
    */
    return 0;
}
