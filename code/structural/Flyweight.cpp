/*
The Flyweight Pattern is a structural design pattern that helps reduce memory
usage by sharing objects instead of creating new ones. It is particularly useful
when a program needs to create a large number of objects that share common data.
*/
#include <iostream>
#include <unordered_map>
#include <memory>

// Flyweight Interface
class CharacterFlyweight
{
public:
    virtual void display(int position) const = 0; // Extrinsic state: position
    virtual ~CharacterFlyweight() = default;
};

// Concrete Flyweight (Shared Objects)
class Character : public CharacterFlyweight
{
private:
    char m_symbol;      // Intrinsic state (shared)
    std::string m_font; // Shared property

public:
    Character(char m_symbol, std::string m_font) : m_symbol(m_symbol), m_font(m_font) {}
    void display(int position) const override
    {
        std::cout << "Character: " << m_symbol << " at Position: " << position
                  << " with Font: " << m_font << std::endl;
    }
};

// Flyweight Factory (Ensures Shared Objects)
class CharacterFactory
{
private:
    std::unordered_map<char, std::shared_ptr<CharacterFlyweight>> characterMap;

public:
    std::shared_ptr<CharacterFlyweight> getcharacter(char symbol, std::string font)
    {
        if (characterMap.find(symbol) == characterMap.end())
        {
            characterMap[symbol] = std::make_shared<Character>(symbol, font);
        }

        return characterMap[symbol];
    }
};

// Client (Text Editor Simulation)
class TextEditor
{
private:
    CharacterFactory m_characterfactory;

public:
    void displayText(const std::string &text, const std::string &font)
    {
        for (int i = 0; i < text.size(); i++)
        {
            m_characterfactory.getcharacter(text[i], font)->display(i);
        }
    }
};

int main(int argc, const char **argv)
{
    TextEditor editor;
    editor.displayText("Hello, Flyweight!", "Arial");

    return 0;
}