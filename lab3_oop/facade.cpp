#include "facade.h"

std::string vecToString(std::vector<Token>& vec) {
    std::ostringstream oss;
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i != 0) {
            oss << " ";
        }
        oss << vec[i].getValue();
    }
    return oss.str();
}

std::string Facade::calculate(const std::string& expression) {
    std::string answer;
    try {
        std::string transfoemedExpression = ExpressionTransformer::addingZeros(expression);
        ValidationChecker vc(transfoemedExpression);
        vc.checkExpression();

        Translator tr(transfoemedExpression);
        std::vector<Token> tokens = tr.translate();
        Calculator calculator(tokens);
        answer = calculator.calculate();

    } catch(const std::exception &e) {
        answer = e.what();
    }

    return answer;
}
