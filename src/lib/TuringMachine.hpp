#ifndef TM_LIB_TURINGMACHINE_H_
#define TM_LIB_TURINGMACHINE_H_

#include "Exception.hpp"
#include "Function.hpp"

#include <map>
#include <set>
#include <string>
#include <vector>

class TuringMachine
{
public:
    TuringMachine(int);
    ~TuringMachine();

    char &operator[](int);

    int getCurrentIndex();
    int getFiniteTableSize();
    std::set<char> &getMainAlphabet();
    std::set<char> &getAdditionalAlphabet();
    std::string getFunction(int, char);

    void makeStep();

    void stateAdd();
    void stateRemove();

    void setAlphabet(std::string, std::string);
    void setFunction(int, char, std::string);
    void setString(std::string);

private:
    bool stopped_ = false;

    std::vector<char> tape_;
    int current_cell_;

    std::vector<std::map<char, Function>> finite_table_;
    int current_state_;

    std::set<char> main_alphabet_;
    std::set<char> additional_alphabet_;

    void resetTape();
    void resetAlphabet();

    void setMainAlphabet(std::string &);
    void setAdditionalAlphabet(std::string &);
};

#endif // TM_LIB_TURINGMACHINE_H_