#pragma once

#include <list>
#include <optional>
#include "Resource.hpp"
#include "Process.hpp"

class Graph {
 public:
    struct MinMax {
        double min;
        double max;
    };

    Resource* GetResourceByName(const std::string& name);

    Process* GetProcessByName(const std::string& name);

    void AddResource(const Resource& resource);

    void AddProcess(const Process& process);

    void AddResourceToOptimize(Resource* resource);

    void AddOptimizeByTime();

    std::list<Resource>& GetResources();

    [[nodiscard]] std::vector<Resource*>& GetResourcesToOptimize();

    [[nodiscard]] std::list<Process>& GetProcesses();

    [[nodiscard]] std::optional<MinMax> CalculateAFromB(Resource* a, Resource* b);

    void CalculateProcessesCyclesToGoal(Resource* a, Resource* b, size_t prev_processes_cycles);

    void Print() const;

 private:
    std::list<Process> _processes;
    std::list<Resource> _resources;
    std::vector<Resource*> _resources_to_optimize;
    bool _optimize_by_time = false;
};
