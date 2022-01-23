#include "Resource.hpp"

Resource::Resource(std::string name, size_t number) : _name(name), _number(number) {}

void Resource::Add(size_t number) {
    _number += number;
}

const std::string& Resource::GetName() const {
    return _name;
}

size_t Resource::GetNumber() const {
    return _number;
}
