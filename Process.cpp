#include "Process.hpp"

#include <utility>

Process::Process(std::string  name, size_t cycles_number,
                 std::vector<std::pair<Resource*, double>>  required_resources,
                 std::vector<std::pair<Resource*, double>>  produced_resources)
        : _name(std::move(name)),
          _cycles_number(cycles_number),
          _required_resources(std::move(required_resources)),
          _produced_resources(std::move(produced_resources)) {}

void Process::IncrementCycle() {
    ++_current_cycle;
}

bool Process::ShouldDie() const {
    return _current_cycle >= _cycles_number;
}

void Process::CollectResources() {
    for (auto& resource_pair: _produced_resources) {
        Resource* resource_ptr = resource_pair.first;
        double resource_number = resource_pair.second;
        resource_ptr->Add(resource_number);
    }
}

const std::string& Process::GetName() const {
    return _name;
}

std::vector<std::pair<Resource*, double>>& Process::GetProducedResources() {
    return _produced_resources;
}

std::vector<std::pair<Resource*, double>>& Process::GetRequiredResources() {
    return _required_resources;
}

size_t Process::GetCyclesNumber() const {
    return _cycles_number;
}

bool Process::CanStart() const {
    for (auto required_resource_p : _required_resources) {
        double required_resource_number = required_resource_p.second;
        double actual_resource_number = required_resource_p.first->GetNumber();
        if (required_resource_number > actual_resource_number) {
            return false;
        }
    }
    return true;
}

void Process::StartProcess() {
    for (auto required_resource_p : _required_resources) {
        required_resource_p.first->Add(-required_resource_p.second);
    }
}

double Process::GetProfit() const {
    return _profit;
}

/// example profit calculation:
/// 3A + 2B = C + D
/// A = 1, B = 2, C = 4, D = 6
/// 3 * 1 + 2 * 2 = 4 + 6
/// 7 = 10
/// profit is 10 - 7 = 3
void Process::CalculateProfit() {
    double required_price = 0;
    double produced_price = 0;

    for (const auto& required_resource_p : _required_resources) {
        required_price += required_resource_p.first->GetPrice() * required_resource_p.second;
    }
    for (const auto& produced_resource_p : _produced_resources) {
        produced_price += produced_resource_p.first->GetPrice() * produced_resource_p.second;
    }

    _profit = (produced_price - required_price) / static_cast<double>(_cycles_number);
}

bool Process::ProfitComparator(Process* a, Process* b) {
    return a->GetProfit() > b->GetProfit();
}

void Process::RecursiveRun(std::list<Process>& running_processes) {
    if (!IsAvailable()) {
        return;
    }
    SetAvailable(false);
    while (CanStart()) {
        Process running_process(*this);
        running_process.StartProcess();
        running_processes.push_back(running_process);
    }
    for (auto required_resource_p : _required_resources) {
        auto required_resource = required_resource_p.first;
        for (auto process : required_resource->GetProcesses()) {
            process->RecursiveRun(running_processes);
        }
    }
    SetAvailable(true);
}

[[nodiscard]] bool Process::IsAvailable() {
    return _available;
}

void Process::SetAvailable(bool available) {
    _available = available;
}

double Process::GetProducedResourceMultiplier(Resource* produced_resource) const {
    for (auto resource_p : _produced_resources) {
        if (resource_p.first == produced_resource) {
            return resource_p.second;
        }
    }
    throw std::logic_error("Try get multiplier by not existed produced_resource");
}
