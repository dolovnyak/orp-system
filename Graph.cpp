#include "Graph.hpp"
#include "logs.hpp"

Resource* Graph::GetResourceByName(std::string name) {
    for (auto& resource : _resources) {
        if (resource.GetName() == name) {
            return &resource;
        }
    }
    return nullptr;
}

void Graph::AddResource(Resource resource) {
    if (GetResourceByName(resource.GetName()) != nullptr) {
        throw std::logic_error("Add existed resource");
    }

    _resources.push_back(resource);
    LOG_INFO("Added resource \"", resource.GetNumber(), " ", resource.GetName(), "\"");
}

