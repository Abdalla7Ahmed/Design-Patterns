/*
The Proxy Pattern is a structural design pattern that provides a surrogate or placeholder for another object to control access to it. This is useful when:

    You want to control access to a resource (e.g., authentication).
    You need to delay the creation of an expensive object (lazy initialization).
    You want to log, cache, or validate requests before reaching the actual object.
*/

#include <iostream>
#include <memory>
#include <string>

class IFile
{
public:
    virtual void readFile() const = 0; // Method to read the file
    virtual ~IFile() = default;
};

class RealFile : public IFile
{
private:
    std::string m_filename;

public:
    RealFile(const std::string &filename) : m_filename(filename) {}

    void readFile() const override
    {
        std::cout << "Reading file: " << m_filename << std::endl;
    }
};

// Proxy Class (Controls Access)
class FileProxy : public IFile
{
private:
    mutable std::unique_ptr<RealFile> m_realFile; // Holds the real file object
    std::string m_filename;
    std::string m_username;
    bool hasAccess; // Authentication flag

public:
    FileProxy(std::string m_filename, std::string m_username, bool hasAccess)
        : m_filename(m_filename), m_username(m_username), hasAccess(hasAccess)
    {
    }
    void readFile() const override
    {
        if (!hasAccess)
        {
            std::cout << "Permission denied" << std::endl;
            return;
        }
        if (!m_realFile)
        {
            // m_realFile = std::make_unique<RealFile>(m_filename);
            m_realFile = std::make_unique<RealFile>(m_filename);
        }
        std::cout << "Access Granted: " << m_username << " is reading the file...\n";
        m_realFile->readFile();
    }
};

int main(int argc, const char **argv)
{
    std::string filename{};
    std::string username{};
    bool hasAccess = false;

    std::cout << "Enter the file name : ";
    std::cin >> filename;
    std::cout << "Enter the username : ";
    std::cin >> username;
    if (username == "Admin")
    {
        hasAccess = true;
    }

    std::unique_ptr<FileProxy> authorizedUser = std::make_unique<FileProxy>(filename, username, hasAccess);
    authorizedUser->readFile();
    return 0;
}