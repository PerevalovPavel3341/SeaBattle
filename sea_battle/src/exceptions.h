#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

class NoAbilityException : public std::exception {
public:
    const char* what() const noexcept override;
};

class ShipPlacementException : public std::exception {
public:
    const char* what() const noexcept override;
};

class OutOfBoundsException : public std::exception {
public:
    const char* what() const noexcept override;
};


#endif