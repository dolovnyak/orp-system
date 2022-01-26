#pragma once

#include "Resource.hpp"

class Process {
 public:
    Process(std::string name, size_t cycles_number,
            std::vector<std::pair<Resource*, double>>  required_resources,
            std::vector<std::pair<Resource*, double>>  produced_resources);

    Process(const Process& process);



    void IncrementCycle();

    [[nodiscard]] bool ShouldDie() const;

    void CollectResources();

    [[nodiscard]] const std::string& GetName() const;

    [[nodiscard]] std::vector<std::pair<Resource*, double>>& GetProducedResources();

    [[nodiscard]] std::vector<std::pair<Resource*, double>>& GetRequiredResources();

    [[nodiscard]] size_t GetCyclesNumber() const;

    [[nodiscard]] double CalculateProfit();

    [[nodiscard]] bool CanStart(size_t remaining_cycles) const;

    [[nodiscard]] bool NeedToStart() const;

    void StartProcess();

 private:
    std::string _name;
    size_t _required_cycles = 0;
    size_t _current_cycle = 0;
    std::vector<std::pair<Resource*, double>> _required_resources;
    std::vector<std::pair<Resource*, double>> _produced_resources;

};
