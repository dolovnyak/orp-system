#include "ParseProcess.hpp"

void ParseProcess::AddRequiredResource(const std::string& name, size_t number, Graph* graph) {
    if (graph->GetResourceByName(name) == nullptr) {
        graph->AddResource(Resource(name, 0));
    }
    _process.AddRequiredResource(graph->GetResourceByName(name), number);
}

void ParseProcess::AddProducedResource(const std::string& name, size_t number, Graph* graph) {
    if (graph->GetResourceByName(name) == nullptr) {
        graph->AddResource(Resource(name, 0));
    }
    _process.AddProducedResource(graph->GetResourceByName(name), number);
}
