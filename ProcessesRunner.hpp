#pragma once

#include "Graph.hpp"

class ProcessesRunner {
public:
    static void RunOptimalProcesses(Graph& graph, std::list<Process>& running_processes,
                                    size_t remaining_cycle, size_t current_cycle);
};
