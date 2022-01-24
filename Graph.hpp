#pragma once

#include <list>
#include "Resource.hpp"
#include "Process.hpp"

class Graph {
 public:
    Resource* GetResourceByName(const std::string& name);

    Process* GetProcessByName(const std::string& name);

    void AddResource(const Resource& resource);

    void AddProcess(const Process& process);

    void AddResourceToOptimize(Resource* resource);

    void AddOptimizeByTime();

    std::list<Resource>& GetResources();

    [[nodiscard]] double CalculateAFromB(Resource* a, Resource* b);

    void Print() const;

 private:
    std::list<Process> _processes;
    std::list<Resource> _resources;
    std::vector<Resource*> _resources_to_optimize;
    bool _optimize_by_time = false;
};
