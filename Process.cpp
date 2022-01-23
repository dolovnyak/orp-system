#include "Process.hpp"

void Process::IncrementCycle() {
    ++_current_cycle;
}

bool Process::ShouldDie() const {
    return _current_cycle >= _cycles_number;
}

void Process::CollectResources() {
    for (auto& resource_pair : _produced_resources) {
        size_t resource_number = resource_pair.first;
        Resource* resource_ptr = resource_pair.second;
        resource_ptr->Add(resource_number);
    }
}
