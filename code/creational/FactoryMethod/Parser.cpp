#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <stdexcept>

class FileParser
{
public:
    virtual std::string parse(const std::string &FilePath) const = 0;
    virtual ~FileParser() = default;
};

class TextParser : public FileParser
{
public:
    std::string parse(const std::string &FilePath) const override
    {
        std::ifstream file(FilePath);
        if (!file.is_open())
            throw std::runtime_error("Cannot open file: " + FilePath);

        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        return "Parsed Text File:\n" + content;
    }
};

class JsonParser : public FileParser
{
public:
    std::string parse(const std::string &FilePath) const override
    {
        std::ifstream file(FilePath);
        if (!file.is_open())
            throw std::runtime_error("Cannot open file: " + FilePath);

        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        return "Parsed JSON File:\n" + content;
    }
};

class XmlParser : public FileParser
{
public:
    std::string parse(const std::string &FilePath) const override
    {
        std::ifstream file(FilePath);
        if (!file.is_open())
            throw std::runtime_error("Cannot open file: " + FilePath);

        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        return "Parsed XML File:\n" + content;
    }
};

class CsvParser : public FileParser
{
public:
    std::string parse(const std::string &FilePath) const override
    {
        std::ifstream file(FilePath);
        if (!file.is_open())
            throw std::runtime_error("Cannot open file: " + FilePath);

        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        return "Parsed CSV File:\n" + content;
    }
};

class YamlParser : public FileParser
{
public:
    std::string parse(const std::string &FilePath) const override
    {
        std::ifstream file(FilePath);
        if (!file.is_open())
            throw std::runtime_error("Cannot open file: " + FilePath);

        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        return "Parsed YAML File:\n" + content;
    }
};
class ParserFactory
{
public:
    static std::unique_ptr<FileParser> createParser(const std::string &file_type);
};

std::unique_ptr<FileParser> ParserFactory::createParser(const std::string &file_type)
{
    if ("txt" == file_type)
    {
        return std::make_unique<TextParser>();
    }
    else if ("json" == file_type)
    {
        return std::make_unique<JsonParser>();
    }
    else if ("xml" == file_type)
    {
        return std::make_unique<XmlParser>();
    }
    else if ("csv" == file_type)
    {
        return std::make_unique<CsvParser>();
    }
    else if ("yaml" == file_type)
    {
        return std::make_unique<YamlParser>();
    }
    else
    {
        throw std::invalid_argument("Unsupported file type ");
    }
}

// Utility Function to Extract File Extension
std::string getFileExtension(const std::string &fileName)
{
    size_t dotPos = fileName.rfind('.');
    if (dotPos == std::string::npos)
        throw std::invalid_argument("No file extension found in: " + fileName);
    return fileName.substr(dotPos + 1);
}
int main(int argc, const char **argv)
{

    std::string filePath;
    std::cout << "Enter the file path: ";
    std::cin >> filePath;

    try
    {
        std::string fileType = getFileExtension(filePath);
        auto parser = ParserFactory::createParser(fileType);

        std::string result = parser->parse(filePath);
        std::cout << result << std::endl;

        // Save to a unified output file
        std::ofstream outFile("output.txt");
        outFile << result;
        outFile.close();
        std::cout << "Output saved to 'output.txt'." << std::endl;
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}