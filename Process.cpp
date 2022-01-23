#include "Process.hpp"

void Process::IncrementCycle() {
    ++_current_cycle;
}

bool Process::ShouldDie() const {
    return _current_cycle >= _cycles_number;
}

void Process::CollectResources() {
    for (auto& resource_pair : _produced_resources) {
        Resource* resource_ptr = resource_pair.first;
        size_t resource_number = resource_pair.second;
        resource_ptr->Add(resource_number);
    }
}

void Process::AddRequiredResource(Resource* resource, size_t number) {
    _required_resources.emplace_back(resource, number);
}

void Process::AddProducedResource(Resource* resource, size_t number) {
    _produced_resources.emplace_back(resource, number);
}
