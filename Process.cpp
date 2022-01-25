#include "Process.hpp"

#include <utility>

Process::Process(std::string  name, size_t cycles_number,
                 std::vector<std::pair<Resource*, double>>  required_resources,
                 std::vector<std::pair<Resource*, double>>  produced_resources)
        : _name(std::move(name)),
          _cycles_number(cycles_number),
          _required_resources(std::move(required_resources)),
          _produced_resources(std::move(produced_resources)) {}

void Process::IncrementCycle() {
    ++_current_cycle;
}

bool Process::ShouldDie() const {
    return _current_cycle >= _cycles_number;
}

void Process::CollectResources() {
    for (auto& resource_pair: _produced_resources) {
        Resource* resource_ptr = resource_pair.first;
        double resource_number = resource_pair.second;
        resource_ptr->Add(resource_number);
    }
}

const std::string& Process::GetName() const {
    return _name;
}

std::vector<std::pair<Resource*, double>>& Process::GetProducedResources() {
    return _produced_resources;
}

std::vector<std::pair<Resource*, double>>& Process::GetRequiredResources() {
    return _required_resources;
}

size_t Process::GetCyclesNumber() const {
    return _cycles_number;
}
