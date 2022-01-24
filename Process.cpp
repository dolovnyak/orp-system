#include "Process.hpp"

#include <utility>

Process::Process(const std::string& name, size_t cycles_number,
                 const std::vector<std::pair<Resource*, size_t>>& required_resources,
                 const std::vector<std::pair<Resource*, size_t>>& produced_resources)
        : _name(name),
          _cycles_number(cycles_number),
          _required_resources(required_resources),
          _produced_resources(produced_resources) {}

void Process::IncrementCycle() {
    ++_current_cycle;
}

bool Process::ShouldDie() const {
    return _current_cycle >= _cycles_number;
}

void Process::CollectResources() {
    for (auto& resource_pair: _produced_resources) {
        Resource* resource_ptr = resource_pair.first;
        size_t resource_number = resource_pair.second;
        resource_ptr->Add(resource_number);
    }
}

const std::string& Process::GetName() const {
    return _name;
}

std::vector<std::pair<Resource*, size_t>>& Process::GetProducedResources() {
    return _produced_resources;
}

std::vector<std::pair<Resource*, size_t>>& Process::GetRequiredResources() {
    return _required_resources;
}
