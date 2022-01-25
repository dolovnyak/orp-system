#include "ParseProcess.hpp"

std::vector<std::pair<Resource*, double>> ParseProcess::_required_resources;
std::vector<std::pair<Resource*, double>> ParseProcess::_produced_resources;

void ParseProcess::AddRequiredResource(const std::string& name, double number, Graph* graph) {
    if (graph->GetResourceByName(name) == nullptr) {
        graph->AddResource(Resource(name, 0));
    }
    for (auto& required_resource_p: _required_resources) {
        if (required_resource_p.first->GetName() == name) {
            required_resource_p.second += number;
            return;
        }
    }
    _required_resources.emplace_back(graph->GetResourceByName(name), number);
}

void ParseProcess::AddProducedResource(const std::string& name, double number, Graph* graph) {
    if (graph->GetResourceByName(name) == nullptr) {
        graph->AddResource(Resource(name, 0));
    }
    for (auto& produced_resource_p: _produced_resources) {
        if (produced_resource_p.first->GetName() == name) {
            produced_resource_p.second += number;
            return;
        }
    }
    _produced_resources.emplace_back(graph->GetResourceByName(name), number);
}

void ParseProcess::CleanUp() {
    _required_resources.clear();
    _produced_resources.clear();
}

std::vector<std::pair<Resource*, double>> ParseProcess::GetRequiredResources() {
    return _required_resources;
}

std::vector<std::pair<Resource*, double>> ParseProcess::GetProducedResources() {
    return _produced_resources;
}
