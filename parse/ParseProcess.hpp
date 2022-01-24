#pragma once

#include "Graph.hpp"

class ParseProcess {
 public:
    static void AddRequiredResource(const std::string& name, size_t number, Graph* graph);
    static void AddProducedResource(const std::string& name, size_t number, Graph* graph);

    static std::vector<std::pair<Resource*, size_t>> GetRequiredResources();
    static std::vector<std::pair<Resource*, size_t>> GetProducedResources();

    static void CleanUp();

 private:
    static std::vector<std::pair<Resource*, size_t>> _required_resources;
    static std::vector<std::pair<Resource*, size_t>> _produced_resources;
};
