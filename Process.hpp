#pragma once

#include "Resource.hpp"

class Process {
 public:
    void IncrementCycle();

    [[nodiscard]] bool ShouldDie() const;

    void CollectResources();

    void AddRequiredResource(Resource* resource, size_t number);

    void AddProducedResource(Resource* resource, size_t number);

 private:
    size_t _cycles_number = 0;
    size_t _current_cycle = 0;
    std::vector<std::pair<Resource*, size_t>> _required_resources;
    std::vector<std::pair<Resource*, size_t>> _produced_resources;
};
