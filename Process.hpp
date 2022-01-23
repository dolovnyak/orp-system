#pragma once

#include "Resource.hpp"

class Process {
 public:
    void IncrementCycle();

    [[nodiscard]] bool ShouldDie() const;

    void CollectResources();

 private:
    size_t _cycles_number = 0;
    size_t _current_cycle = 0;
    std::vector<std::pair<size_t, Resource*>> _required_resources;
    std::vector<std::pair<size_t, Resource*>> _produced_resources;
};
