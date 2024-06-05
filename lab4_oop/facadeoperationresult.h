#ifndef FACADEOPERATIONRESULT_H
#define FACADEOPERATIONRESULT_H

#include <string>

class FacadeOperationResult
{
public:
    FacadeOperationResult(std::string errorText,bool successStatus): _errorMessage(errorText), _isSuccess(successStatus){};
    std::string getErrorMessage() {return _errorMessage;};
    bool isSucces() {return _isSuccess;};
private:
    std::string _errorMessage;
    bool _isSuccess;

};

#endif // FACADEOPERATIONRESULT_H
