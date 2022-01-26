#include "Resource.hpp"
#include "Process.hpp"

#include <utility>

Resource::Resource(std::string name, double number) : _name(std::move(name)), _number(number) {}

void Resource::Add(double number) {
    _number += number;
    if (_number < 0) {
        throw std::logic_error("resource number < 0");
    }
}

const std::string& Resource::GetName() const {
    return _name;
}

double Resource::GetNumber() const {
    return _number;
}

void Resource::AddProcess(Process* process) {
    _processes.push_back(process);
}

std::vector<Process*>& Resource::GetProcesses() {
    return _processes;
}

void Resource::SetPriceCoefficient(double price) {
    _price_coefficient = price;
}

bool Resource::IsAvailable() const {
    return _available;
}

void Resource::SetAvailable(bool available) {
    _available = available;
}

double Resource::GetPriceCoefficient() const {
    return _price_coefficient;
}

double Resource::GetEstimatedPrice() const {
    double number = _number == 0 ? 1 : _number;
    return 1 / _future_number * _price_coefficient;
}

void Resource::AddFuture(double number) {
    _future_number += number;
}
