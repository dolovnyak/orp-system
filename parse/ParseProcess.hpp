#pragma once

#include "Graph.hpp"

class ParseProcess {
 public:
    static void AddRequiredResource(const std::string& name, double number, Graph* graph);
    static void AddProducedResource(const std::string& name, double number, Graph* graph);

    static std::vector<std::pair<Resource*, double>> GetRequiredResources();
    static std::vector<std::pair<Resource*, double>> GetProducedResources();

    static void CleanUp();

 private:
    static std::vector<std::pair<Resource*, double>> _required_resources;
    static std::vector<std::pair<Resource*, double>> _produced_resources;
};
