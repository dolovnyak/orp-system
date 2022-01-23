#pragma once

#include "Resource.hpp"
#include "Process.hpp"

class Graph {
 public:
    Resource* GetResourceByName(std::string name);
    void AddResource(Resource resource);
 private:
    std::vector<Process> _processes;
    std::vector<Resource> _resources;
};
