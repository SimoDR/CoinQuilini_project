#include "outofboundexception.h"

OutOfBoundException::OutOfBoundException(string tipo):
    std::domain_error("Eccezione: il parametro " + tipo + " e' fuori dal range consentito"), _tipo(tipo)
{ }
