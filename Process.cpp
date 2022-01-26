#include "Process.hpp"

#include <utility>
#include <iostream>

Process::Process(std::string name, size_t cycles_number,
                 std::vector<std::pair<Resource*, double>>  required_resources,
                 std::vector<std::pair<Resource*, double>>  produced_resources)
        : _name(std::move(name)),
          _required_cycles(cycles_number),
          _required_resources(std::move(required_resources)),
          _produced_resources(std::move(produced_resources)) {}

Process::Process(const Process& process) {
    _name = process._name;
    _required_cycles = process._required_cycles;
    _current_cycle = process._current_cycle;
    _required_resources = process._required_resources;
    _produced_resources = process._produced_resources;
}

void Process::IncrementCycle() {
    ++_current_cycle;
}

bool Process::ShouldDie() const {
    return _current_cycle >= _required_cycles;
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
    return _required_cycles;
}

bool Process::CanStart(size_t remaining_cycles) const {
    if (_required_cycles > remaining_cycles) {
        return false;
    }
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
    for (auto& required_resource_p : _required_resources) {
        required_resource_p.first->Add(-required_resource_p.second);
    }
    for (auto& produced_resource_p : _produced_resources) {
        produced_resource_p.first->AddFuture(produced_resource_p.second);
    }
}

/// example profit calculation:
/// 3A + 2B = C + D
/// A = 1, B = 2, C = 4, D = 6
/// 3 * 1 + 2 * 2 = 4 + 6
/// 7 = 10
/// profit is 10 - 7 = 3
/// profit considering cycles number = 3 / _required_cycles
double Process::CalculateProfit() {
    double required_price = 0;
    double produced_price = 0;

    for (const auto& required_resource_p : _required_resources) {
        required_price += required_resource_p.first->GetEstimatedPrice() * required_resource_p.second;
    }
    for (const auto& produced_resource_p : _produced_resources) {
        produced_price += produced_resource_p.first->GetEstimatedPrice() * produced_resource_p.second;
    }
    return (produced_price - required_price) / static_cast<double>(_required_cycles);
}

//bool Process::RecursiveRun(std::list<Process>& running_processes, size_t remaining_cycles, size_t prev_cycles) {
////    if (!IsAvailable()) {
////        return;
////    }
//    if (prev_cycles + _required_cycles > remaining_cycles) {
//        return false;
//    }
////    SetAvailable(false);
//    bool is_any_process_run;
//    if (CanStart()) {
//        Process running_process(*this);
//        running_process.StartProcess();
//        running_processes.push_back(running_process);
//        is_any_process_run = true;
//    }
//    for (auto required_resource_p : _required_resources) {
//        auto required_resource = required_resource_p.first;
//        if (!required_resource->IsAvailable()) {
//            continue;
//        }
//        required_resource->SetAvailable(false);
//        for (auto process : required_resource->GetProcesses()) {
//            if (process->RecursiveRun(running_processes, remaining_cycles, prev_cycles + _required_cycles)) {
//                is_any_process_run = true;
//            }
//        }
//        required_resource->SetAvailable(true);
//    }
////    SetAvailable(true);
//    return is_any_process_run;
//}
