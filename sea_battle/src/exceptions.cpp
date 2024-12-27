#include <exception>

#include "exceptions.h"

const char* NoAbilityException::what() const noexcept{
	return "No abilities available to use.";
}

const char*  ShipPlacementException::what() const noexcept{
	return "Ships cannot be placed too close to each other or overlap.";
}

const char* OutOfBoundsException::what() const noexcept{
	return "Attack is out of bounds.";
}