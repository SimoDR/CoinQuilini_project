#ifndef OUTOFBOUNDEXCEPTION_H
#define OUTOFBOUNDEXCEPTION_H
#include<stdexcept>
#include<string>
using std::string;

class OutOfBoundException : public std::domain_error
{
public:
    OutOfBoundException(string tipo);
private:
    string _tipo;
};

#endif // OUTOFBOUNDEXCEPTION_H
