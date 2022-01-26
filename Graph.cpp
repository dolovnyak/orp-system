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
        std::cout << "Resource: \"" << resource.GetName() << ":" << resource.GetNumber() << ":" << resource.GetEstimatedPrice() << "\"" << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Processes:" << std::endl;
    for (auto process : _processes) {
        std::cout << "\"" << process.GetName() << "\" " << std::endl;
        std::cout << "cycles: " << process.GetCyclesNumber() << std::endl;
        std::cout << "Required resources: ";
        for (auto required_resource_p : process.GetRequiredResources()) {
            std::cout << required_resource_p.first->GetName() << ":" << required_resource_p.second << " ";
        }
        std::cout << std::endl << "Produced resources: ";
        for (auto produced_resource_p : process.GetProducedResources()) {
            std::cout << produced_resource_p.first->GetName() << ":" << produced_resource_p.second << " ";
        }
        std::cout << std::endl << std::endl;
    }
    std::cout << std::endl << std::endl;
}

std::list<Resource>& Graph::GetResources() {
    return _resources;
}

/// For each process in resource A:
/// * Get A multiplier
/// * For each required_resource in current process:
///     * If current resource is resource through which we need to calculate A - get multiplier.
///     * If current resource is unavailable - ignore it.
///     * If resource available and not resource through which we need to calculate A (B) - calculate it through B
/// * When all resources calculated, the price resulting from this process is "SUM(all B_multipliers) / A_multiplier"
/// Return min result of processes or NaN if no one process return result.
std::optional<Graph::MinMax> Graph::CalculateAFromB(Resource* a, Resource* b) {
    a->SetAvailable(false);

    MinMax min_max_result{};
    min_max_result.min = std::numeric_limits<double>::max();
    min_max_result.max = std::numeric_limits<double>::min();
    bool result_set = false;

    for (auto& a_process : a->GetProcesses()) {

        /// Get A multiplier
        double a_multiplier;
        for (const auto& produced_resource_p : a_process->GetProducedResources()) {
            if (produced_resource_p.first == a) {
                a_multiplier = produced_resource_p.second;
                break;
            }
        }

        /// Calculate each required element from B and sum multipliers
        double b_min_sum = 0;
        double b_max_sum = 0;
        bool b_multiplier_set = false;
        for (auto& required_resource_p : a_process->GetRequiredResources()) {
            if (required_resource_p.first == b) {
                /// If Resource is B (resource through which we need to calculate A) - get it multiplier
                b_min_sum += required_resource_p.second;
                b_max_sum += required_resource_p.second;
                b_multiplier_set = true;
            }
            else if (!required_resource_p.first->IsAvailable()) {
                /// Ignore unavailable resource
                continue;
            }
            else {
                /// If resource is available and it's not B. Calculate it from B
                auto tmp_min_max = CalculateAFromB(required_resource_p.first, b);
                if (!tmp_min_max.has_value()) {
                    continue;
                }
                b_min_sum += tmp_min_max->min;
                b_max_sum += tmp_min_max->max;
                b_multiplier_set = true;
            }
        }
        if (b_multiplier_set) {
            min_max_result.min = std::min(min_max_result.min, b_min_sum / a_multiplier);
            min_max_result.max = std::max(min_max_result.max, b_max_sum);
            result_set = true;
        }
    }
    a->SetAvailable(true);

    if (result_set) {
        return min_max_result;
    }
    return std::nullopt;
}

std::list<Process>& Graph::GetProcesses() {
    return _processes;
}

std::vector<Resource*>& Graph::GetResourcesToOptimize() {
    return _resources_to_optimize;
}
