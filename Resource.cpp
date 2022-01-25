#include "Resource.hpp"
#include "Process.hpp"

#include <utility>

Resource::Resource(std::string name, double number) : _name(std::move(name)), _number(number) {}

void Resource::Add(double number) {
    _number += number;
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

void Resource::SetCurrentPrice(double current_price) {
    _price = current_price;
}

bool Resource::IsAvailable() const {
    return _available;
}

void Resource::SetAvailable(bool available) {
    _available = available;
}

double Resource::GetPrice() const {
    return _price;
}

void Resource::SortProcessesByProfit() {
    std::sort(_processes.begin(), _processes.end(), Process::ProfitComparator);
}
