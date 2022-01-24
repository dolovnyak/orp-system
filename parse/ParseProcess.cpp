#include "ParseProcess.hpp"

std::vector<std::pair<Resource*, size_t>> ParseProcess::_required_resources;
std::vector<std::pair<Resource*, size_t>> ParseProcess::_produced_resources;

void ParseProcess::AddRequiredResource(const std::string& name, size_t number, Graph* graph) {
    if (graph->GetResourceByName(name) == nullptr) {
        graph->AddResource(Resource(name, 0));
    }
    _required_resources.emplace_back(graph->GetResourceByName(name), number);
}

void ParseProcess::AddProducedResource(const std::string& name, size_t number, Graph* graph) {
    if (graph->GetResourceByName(name) == nullptr) {
        graph->AddResource(Resource(name, 0));
    }
    _produced_resources.emplace_back(graph->GetResourceByName(name), number);
}

void ParseProcess::CleanUp() {
    _required_resources.clear();
    _produced_resources.clear();
}

std::vector<std::pair<Resource*, size_t>> ParseProcess::GetRequiredResources() {
    return _required_resources;
}

std::vector<std::pair<Resource*, size_t>> ParseProcess::GetProducedResources() {
    return _produced_resources;
}
