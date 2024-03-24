#include "turingmachine.h"

#include <algorithm>
#include <iostream>

TuringMachine::TuringMachine(int size) : tape_(size, '^'), finite_table_(1)
{
    resetAlphabet();
    resetTape();
}
TuringMachine::~TuringMachine() {}

char &TuringMachine::operator[](int index) { return tape_[index]; }

int TuringMachine::currentIndex() { return current_index_; }
int TuringMachine::finiteTableSize() { return finite_table_.size(); }
std::set<char> &TuringMachine::mainAlphabet() { return main_alphabet_; }
std::set<char> &TuringMachine::additionalAlphabet() { return additional_alphabet_; }
std::string TuringMachine::function(int state, char character)
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
        throw exception::InactiveMachine();
    }
    if (!has_exit_)
    {
        // throw exception::NoExitFunction();
    }

    Function function = finite_table_[current_state_][tape_[current_index_]];

    if (function.symbol)
    {
        tape_[current_index_] = function.symbol;
    }

    if (function.special)
    {
        if (function.special == '<')
        {
            --current_index_;
        }
        else if (function.special == '>')
        {
            ++current_index_;
        }
        else if (function.special == '!')
        {
            stop();
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
        throw exception::DeleteNothing();
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
        throw exception::AlphabetIntersection();
        main_alphabet_.clear();
        additional_alphabet_.clear();
    }
    return;
}

void TuringMachine::setFunction(int state, char character, std::string string)
{
    Function &function = finite_table_[state][character];
    int i = 0;
    if (string[i] != '<' && string[i] != '>' && string[i] != '!' && !isdigit(string[i]))
    {
        if (main_alphabet_.find(string[i]) == main_alphabet_.end() && additional_alphabet_.find(string[i]) == additional_alphabet_.end())
        {
            throw exception::UnknownSymbol();
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
            throw exception::BadFunction();
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
            throw exception::BadFunction();
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
            throw exception::UnknownSymbol();
        }
        tape_[current_index_ + i] = string[i];
    }
    return;
}

void TuringMachine::resetTape()
{
    stopped_ = false, current_index_ = tape_.size() / 2, current_state_ = 0;
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
            throw exception::UnallowedSymbol();
        }
        if (main_alphabet_.find(character) != main_alphabet_.end())
        {
            resetAlphabet();
            throw exception::AlphabetIntersection();
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
            throw exception::UnallowedSymbol();
        }
        if (additional_alphabet_.find(character) != additional_alphabet_.end())
        {
            resetAlphabet();
            throw exception::AlphabetIntersection();
        }
        additional_alphabet_.insert(character);
    }
    return;
}

void TuringMachine::stop()
{
    stopped_ = true;
    for (char c : tape_)
    {
        if (c != '^' && main_alphabet_.find(c) == main_alphabet_.end())
        {
            throw exception::SymbolNotFromAlphabetOnTape();
        }
    }
}
void TuringMachine::reset()
{
    finite_table_.clear();
    resetAlphabet();
    resetTape();
}
void TuringMachine::check_for_exit()
{
    for (int i = 0; i < finite_table_.size(); ++i)
    {
        for (char c : main_alphabet_)
        {
            if (finite_table_[i][c].special == '!')
            {
                std::cout << c << ':' << finite_table_[i][c].symbol << std::endl;
                has_exit_ = true;
                return;
            }
        }
        for (char c : additional_alphabet_)
        {

            std::cout << c << ':' << finite_table_[i][c].symbol << std::endl;
            if (finite_table_[i][c].special == '!')
            {
                has_exit_ = true;
                return;
            }
        }
    }
    has_exit_ = false;
}