#include "Graph.hpp"
#include "logs.hpp"

Resource* Graph::GetResourceByName(const std::string& name) {
    for (auto& resource : _resources) {
        if (resource.GetName() == name) {
            return &resource;
        }
    }
    return nullptr;
}

void Graph::AddResource(const Resource& resource) {
    if (GetResourceByName(resource.GetName()) != nullptr) {
        throw std::logic_error("Add existed resource");
    }
    _resources.push_back(resource);
}

Process* Graph::GetProcessByName(const std::string& name) {
    for (auto& process : _processes) {
        if (process.GetName() == name) {
            return &process;
        }
    }
    return nullptr;
}

void Graph::AddProcess(const Process& process) {
    if (GetProcessByName(process.GetName()) != nullptr) {
        throw std::logic_error("Add existed process");
    }

    _processes.push_back(process);

    /// fill all produced resources with this process.
    auto* ref_process = GetProcessByName(process.GetName());
    for (auto resource_pair : ref_process->GetProducedResources()) {
        auto* resource = resource_pair.first;
        resource->AddProcess(ref_process);
    }
}

void Graph::AddResourceToOptimize(Resource* resource) {
    if (std::find(_resources_to_optimize.begin(), _resources_to_optimize.end(), resource) !=
                    _resources_to_optimize.end()) {
        return;
    }
    _resources_to_optimize.push_back(resource);
}

void Graph::AddOptimizeByTime() {
    _optimize_by_time = true;
}

void Graph::Print() const {
    std::cout << "GRAPH:" << std::endl;
    for (const auto& resource : _resources) {
        std::cout << "Resource: \"" << resource.GetName() << "\"" << std::endl;
        std::cout << "Processes: ";
        for (auto process : resource.GetProcesses()) {
            std::cout << "\"" << process->GetName() << "\" ";
        }
        std::cout << std::endl << std::endl;
    }
}

std::list<Resource>& Graph::GetResources() {
    return _resources;
}

double Graph::CalculateAFromB(Resource* a, Resource* b) {
    for (const auto& a_process : a->GetProcesses()) {
        std::vector<std::pair<Resource*, long>> simplified_required_resources;

        for (const auto& produced_resource_p : a_process->GetProducedResources()) {
            auto is_equal_ref = [produced_resource_p](const std::pair<Resource*, long>& pair)
                    { return pair.first == produced_resource_p.first; };

//            if (produced_resource_p.first != a) {
//                auto eq_resource_it = std::find(simplified_required_resources.begin(),
//                                                simplified_required_resources.end(), is_equal_ref);
//                if (std)
//            }
        }
        }
    }
}

