#include "ProcessesRunner.hpp"


void ProcessesRunner::RunOptimalProcesses(Graph& graph, std::list<Process>& running_processes,
                                          size_t remaining_cycle, size_t current_cycle) {
    std::list<Process*> resource_to_optimize_processes;

    for (auto resource : graph.GetResourcesToOptimize()) {

    }
}
