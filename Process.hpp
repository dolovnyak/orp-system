#pragma once

#include "Resource.hpp"

class Process {
 public:
    Process(const std::string& name, size_t cycles_number,
            const std::vector<std::pair<Resource*, size_t>>& required_resources,
            const std::vector<std::pair<Resource*, size_t>>& produced_resources);

    void IncrementCycle();

    [[nodiscard]] bool ShouldDie() const;

    void CollectResources();

    [[nodiscard]] const std::string& GetName() const;

    [[nodiscard]] std::vector<std::pair<Resource*, size_t>>& GetProducedResources();

    [[nodiscard]] std::vector<std::pair<Resource*, size_t>>& GetRequiredResources();

 private:
    std::string _name;
    size_t _cycles_number = 0;
    size_t _current_cycle = 0;
    std::vector<std::pair<Resource*, size_t>> _required_resources;
    std::vector<std::pair<Resource*, size_t>> _produced_resources;
};
