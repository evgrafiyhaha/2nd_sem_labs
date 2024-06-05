#include "translator.h"

Translator::Translator(std::string exp): expression(exp) {}

std::vector<Token> Translator::translate() {
    std::vector<Token> answer;
    std::string currentNumber = "";
    for (size_t i = 0; i < expression.size();i++) {
        if (std::isdigit(expression[i]) || expression[i] == '.') {
            currentNumber+=expression[i];
        } else {
            if (!currentNumber.empty()) {
                if (std::count(currentNumber.begin(),currentNumber.end(),'.') > 1){
                    throw SyntaxError(SYNTAX_ERROR);
                }
                try {
                    stof(currentNumber);
                } catch(...) {
                    throw LongNumberError(LONG_NUMBER_ERROR);
                }

                answer.push_back(Token(currentNumber));
                currentNumber = "";
            }
            if (!answer.empty() && answer.back().getValue() == "(" && expression[i] == ')') {
                throw SyntaxError(SYNTAX_ERROR);
            }
            answer.push_back(Token(expression[i]));
        }
    }
    if (!currentNumber.empty()) {
        if (std::count(currentNumber.begin(),currentNumber.end(),'.') > 1){
            throw SyntaxError(SYNTAX_ERROR);
        }

        try {
            stof(currentNumber);
        } catch(...) {
            throw LongNumberError(LONG_NUMBER_ERROR);
        }

        answer.push_back(Token(currentNumber));
    }
    return answer;
}

