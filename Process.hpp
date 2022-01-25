#pragma once

#include "Resource.hpp"

class Process {
 public:
    Process(std::string name, size_t cycles_number,
            std::vector<std::pair<Resource*, double>>  required_resources,
            std::vector<std::pair<Resource*, double>>  produced_resources);

    void IncrementCycle();

    [[nodiscard]] bool ShouldDie() const;

    void CollectResources();

    [[nodiscard]] const std::string& GetName() const;

    [[nodiscard]] std::vector<std::pair<Resource*, double>>& GetProducedResources();

    [[nodiscard]] std::vector<std::pair<Resource*, double>>& GetRequiredResources();

    [[nodiscard]] size_t GetCyclesNumber() const;

    [[nodiscard]] double GetProfit() const;

    void CalculateProfit();

    void RecursiveRun(std::list<Process>& running_processes);

    static bool ProfitComparator(Process* a, Process* b);

    [[nodiscard]] bool IsAvailable();

    void SetAvailable(bool available);

    [[nodiscard]] bool CanStart() const;

    [[nodiscard]] double GetProducedResourceMultiplier(Resource* produced_resource) const;

 private:
    std::string _name;
    size_t _cycles_number = 0;
    size_t _current_cycle = 0;
    std::vector<std::pair<Resource*, double>> _required_resources;
    std::vector<std::pair<Resource*, double>> _produced_resources;
    double _profit = 0;
    bool _available = true;

    void StartProcess();
};
