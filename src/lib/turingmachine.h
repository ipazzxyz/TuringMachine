#ifndef TM_LIB_TURINGMACHINE_H_
#define TM_LIB_TURINGMACHINE_H_

#include "exception.h"
#include "function.h"

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

    int currentIndex();
    int finiteTableSize();
    std::set<char> &mainAlphabet();
    std::set<char> &additionalAlphabet();
    std::string function(int, char);

    void makeStep();

    void stateAdd();
    void stateRemove();

    void setAlphabet(std::string, std::string);
    void setFunction(int, char, std::string);
    void setString(std::string);

    void resetTape();
    void resetAlphabet();

    void setMainAlphabet(std::string &);
    void setAdditionalAlphabet(std::string &);

    void reset();

private:
    bool stopped_ = false;
    bool has_exit_ = false;

    std::vector<char> tape_;
    int current_index_;

    std::vector<std::map<char, Function>> finite_table_;
    int current_state_;

    std::set<char> main_alphabet_;
    std::set<char> additional_alphabet_;

    void stop();
    void check_for_exit();
};

#endif // TM_LIB_TURINGMACHINE_H_