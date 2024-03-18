#include "TuringMachine.hpp"

#include <algorithm>

TuringMachine::TuringMachine(int size) : tape_(size, '^'), finite_table_(1)
{
    resetAlphabet();
    resetTape();
}
TuringMachine::~TuringMachine() {}

char &TuringMachine::operator[](int index) { return tape_[index]; }

int TuringMachine::getCurrentIndex() { return current_cell_; }
int TuringMachine::getFiniteTableSize() { return finite_table_.size(); }
std::set<char> &TuringMachine::getMainAlphabet() { return main_alphabet_; }
std::set<char> &TuringMachine::getAdditionalAlphabet() { return additional_alphabet_; }
std::string TuringMachine::getFunction(int state, char character)
{
    Function &function = finite_table_[state][character];
    std::string result;
    if (function.symbol)
    {
        result += function.symbol;
    }
    if (function.special)
    {
        result += function.special;
    }
    if (function.state)
    {
        result += std::to_string(function.state - 1);
    }
    return result;
}

void TuringMachine::makeStep()
{
    if (stopped_)
    {
        throw Exception::InactiveMachine();
    }

    Function function = finite_table_[current_state_][tape_[current_cell_]];

    if (function.symbol)
    {
        tape_[current_cell_] = function.symbol;
    }

    if (function.special)
    {
        if (function.special == '<')
        {
            --current_cell_;
        }
        else if (function.special == '>')
        {
            ++current_cell_;
        }
        else if (function.special == '!')
        {
            stopped_ = true;
        }
    }

    if (function.state)
    {
        current_state_ = function.state - 1;
    }

    return;
}

void TuringMachine::stateAdd() { finite_table_.push_back(std::map<char, Function>()); }
void TuringMachine::stateRemove()
{
    if (finite_table_.size() == 0)
    {
        throw Exception::DeleteNothing();
    }

    finite_table_.erase(finite_table_.end() - 1);
}

void TuringMachine::setAlphabet(std::string main_alphabet, std::string additional_alphabet)
{
    resetAlphabet();
    setMainAlphabet(main_alphabet);
    setAdditionalAlphabet(additional_alphabet);

    std::vector<int> intersection;
    std::set_intersection(main_alphabet_.begin(), main_alphabet_.end(), additional_alphabet_.begin(), additional_alphabet_.end(), std::back_inserter(intersection));
    if (!intersection.empty())
    {
        throw Exception::AlphabetIntersection();
        main_alphabet_.clear();
        additional_alphabet_.clear();
    }
    return;
}
void TuringMachine::setFunction(int state, char character, std::string string)
{
    Function &function = finite_table_[state][character];
    function = Function();
    int i = 0;
    if (string[i] != '<' && string[i] != '>' && string[i] != '!' && !isdigit(string[i]))
    {
        if (main_alphabet_.find(string[i]) == main_alphabet_.end() && additional_alphabet_.find(string[i]) == additional_alphabet_.end())
        {
            function = Function();
            throw Exception::UnknownSymbol();
        }
        function.symbol = string[i++];
    }

    if (string[i] == '<' || string[i] == '>' || string[i] == '!')
    {
        function.special = string[i++];
    }

    bool flag = false;
    while (i < string.size())
    {
        if (!isdigit(string[i]))
        {
            function = Function();
            throw Exception::BadFunction();
        }
        flag = true;
        function.state = function.state * 10 + string[i++] - '0';
    }
    if (flag)
    {
        ++function.state;
        if (function.state > finite_table_.size())
        {
            function = Function();
            throw Exception::BadFunction();
        }
    }
    return;
}
void TuringMachine::setString(std::string string)
{
    resetTape();
    for (int i = 0; i < string.size(); ++i)
    {
        if (main_alphabet_.find(string[i]) == main_alphabet_.end())
        {
            resetTape();
            throw Exception::UnknownSymbol();
        }
        tape_[current_cell_ + i] = string[i];
    }
    return;
}

void TuringMachine::resetTape()
{
    stopped_ = false, current_cell_ = tape_.size() / 2, current_state_ = 0;
    std::fill(tape_.begin(), tape_.end(), '^');
    return;
}
void TuringMachine::resetAlphabet()
{
    main_alphabet_.clear();
    main_alphabet_.insert('^');
    additional_alphabet_.clear();
    return;
}

void TuringMachine::setMainAlphabet(std::string &alphabet)
{
    for (char character : alphabet)
    {
        if (character <= 32 || character == '<' || character == '>' || character == '!')
        {
            resetAlphabet();
            throw Exception::UnallowedSymbol();
        }
        if (main_alphabet_.find(character) != main_alphabet_.end())
        {
            resetAlphabet();
            throw Exception::AlphabetIntersection();
        }
        main_alphabet_.insert(character);
    }
    return;
}
void TuringMachine::setAdditionalAlphabet(std::string &alphabet)
{
    for (char character : alphabet)
    {
        if (character <= 32 || character == '<' || character == '>' || character == '!')
        {
            resetAlphabet();
            throw Exception::UnallowedSymbol();
        }
        if (additional_alphabet_.find(character) != additional_alphabet_.end())
        {
            resetAlphabet();
            throw Exception::AlphabetIntersection();
        }
        additional_alphabet_.insert(character);
    }
    return;
}