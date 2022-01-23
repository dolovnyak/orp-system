#pragma once

#include "Resource.hpp"
#include "Process.hpp"

class Graph {
 public:
    Resource* GetResourceByName(const std::string& name);

    void AddResource(Resource resource);

    void AddResourceToOptimize(Resource* resource);

 private:
    std::vector<Process> _processes;
    std::vector<Resource> _resources;
    std::vector<Resource*> _resources_to_optimize;
};
