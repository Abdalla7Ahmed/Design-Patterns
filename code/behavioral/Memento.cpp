/*
The Memento pattern is used to capture and restore an object's state without exposing its internal details.
This is useful when implementing an undo/redo mechanism in applications.

 Memento Pattern Components

    Originator → The object whose state we want to save and restore.
    Memento → Stores the state of the Originator.
    Caretaker → Manages Memento objects and controls saving/restoring states.
*/

#include <iostream>
#include <vector>
#include <memory>

// Memento: Stores state
class Memento
{
private:
    std::string state;

public:
    Memento(const std::string &state) : state(state) {}
    std::string getstate(void) const
    {
        return state;
    }
};

// Originator: The object whose state changes
class Originator
{
private:
    std::string state;

public:
    void setState(std::string newState)
    {
        state = newState;
        std::cout << "State changed to: " << state << std::endl;
    }
    std::shared_ptr<Memento> saveState()
    {
        return std::make_shared<Memento>(state);
    }
    void restoreState(std::shared_ptr<Memento> memento)
    {
        if (memento)
        {
            state = memento->getstate();
            std::cout << "Restored state: " << state << std::endl;
        }
    }
};

// Caretaker: Stores and manages Mementos
class Caretaker
{
private:
    std::vector<std::shared_ptr<Memento>> history;

public:
    void save(std::shared_ptr<Memento> memento)
    {
        history.push_back(memento);
    }
    std::shared_ptr<Memento> undo()
    {
        if (!history.empty())
        {
            std::shared_ptr<Memento> lastmomento = history.back();
            history.pop_back();
            return lastmomento;
        }
        return nullptr;
    }
};

int main(int argc, const char **argv)
{
    std::shared_ptr<Originator> editor = std::make_shared<Originator>();
    std::shared_ptr<Caretaker> caretaker = std::make_shared<Caretaker>();

    editor->setState("Draft 1");
    caretaker->save(editor->saveState()); // Save state
    editor->setState("Draft 2");
    caretaker->save(editor->saveState()); // Save state

    editor->setState("Final Version");
    std::cout << "\nUndoing Changes...\n";
    editor->restoreState(caretaker->undo()); // Undo 1
    editor->restoreState(caretaker->undo()); // Undo 2
    return 0;
}