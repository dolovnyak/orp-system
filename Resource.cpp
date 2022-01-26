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

double Resource::GetEstimatedPrice() const {
    double future_number = _number + _future_income == 0 ? 1 : _number + _future_income;
    return 1 / future_number * _price_coefficient;
}

void Resource::SetFutureIncome(double future_income) {
    _future_income = future_income;
}

void Resource::UpdateMaxNumber(double number) {
    _max_number = std::max(number, _max_number);
}

bool Resource::HasMaxNumber() {
    return _number + _future_income >= GetMaxNumber();
}

double Resource::GetMaxNumber() {
    return _max_number;
}

double Resource::GetFutureIncome() {
    return _future_income;
}
