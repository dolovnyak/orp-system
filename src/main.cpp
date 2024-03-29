#include <limits>
#include <cmath>
#include <queue>
#include "argparse.hpp"
#include "Graph.hpp"
#include "Grammar.yy.hpp"
#include "GraphCalculator.hpp"

int yyparse(Graph* graph);

extern FILE* yyin;

namespace {

Graph parse_graph(FILE* file) {
    yyin = file;

    Graph graph;
    yyparse(&graph);
    fclose(file);

    return graph;
}

FILE* open_file(const std::string& file_name) {
    FILE* file = fopen(file_name.c_str(), "r");
    if (!file) {
        throw std::runtime_error("Error on opening file : " + file_name);
    }
    return file;
}

void running_processes_processing(std::list<Process>& running_processes) {
    auto running_process = running_processes.begin();

    while (running_process != running_processes.end()) {
        running_process->IncrementCycle();
        if (running_process->ShouldDie()) {
            running_process->CollectResources();
            running_process = running_processes.erase(running_process);
            continue;
        }
        ++running_process;
    }
}

void delete_not_possible_to_start_processes(std::list<Process*>& processes, size_t remaining_cycles) {
    auto process_it = processes.begin();

    while (process_it != processes.end()) {
        if (!(*process_it)->CanStart(remaining_cycles)) {
            process_it = processes.erase(process_it);
            continue;
        }
        ++process_it;
    }
}

void run_optimize_processes_by_profit(Graph& graph, std::list<Process>& running_processes, size_t remaining_cycles, size_t current_cycle) {
    std::list<Process*> possible_to_run_processes;

    for (auto& process: graph.GetProcesses()) {
        if (process.CanStart(remaining_cycles)) {
            possible_to_run_processes.push_back(&process);
        }
    }
    if (possible_to_run_processes.empty()) {
        return;
    }

    while (!possible_to_run_processes.empty()) {
        Process* max_profit_process = nullptr;
        double current_max_profit = std::numeric_limits<double>::lowest();
        for (auto process : possible_to_run_processes) {
            double tmp_max_profit = process->CalculateProfit();
            if (tmp_max_profit > current_max_profit) {
                max_profit_process = process;
                current_max_profit = tmp_max_profit;
            }
        }
        if (max_profit_process == nullptr) {
            break;
        }
        Process running_process(*max_profit_process);
        running_process.StartProcess(current_cycle);
        running_processes.push_back(running_process);
        delete_not_possible_to_start_processes(possible_to_run_processes, remaining_cycles);
    }
}

}

int main(int argc, char** argv) {
    argparse::ArgumentParser argparse("orp-system");

    argparse.add_argument("input_file")
            .required()
            .help("specify the input file.");

    argparse.add_argument("time")
            .default_value(std::numeric_limits<size_t>::max())
            .help("specify the work time.")
            .action([](const std::string& value) { return static_cast<size_t>(std::stol(value)); });

    argparse.add_argument("-c", "--cycles")
            .default_value(std::numeric_limits<size_t>::max())
            .help("specify the cycles number.")
            .action([](const std::string& value) { return static_cast<size_t>(std::stol(value)); });

    try {
        argparse.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err) {
        std::cout << err.what() << std::endl;
        std::cout << std::endl;
        std::cout << argparse;
        exit(0);
    }

    try {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        Graph graph = parse_graph(open_file(argparse.get<std::string>("input_file")));
        GraphCalculator::Calculate(graph);
        std::list<Process> running_processes;
        size_t time = argparse.get<size_t>("time");
        size_t cycles_number = argparse.get<size_t>("--cycles");
        size_t current_cycle = 0;

        std::cout << "Nice file! " << graph.GetProcesses().size() << " processes, " <<
            graph.GetResources().size() << " stocks, " << graph.GetResourcesToOptimize().size() << " to optimize\n";
        std::cout << "Evaluating .................. done.\n" << "Main walk" << std::endl;

        while (current_cycle <= cycles_number) {

            for (auto& resource: graph.GetResources()) {
                resource.SetAvailable(true);
            }

            running_processes_processing(running_processes);

            run_optimize_processes_by_profit(graph, running_processes, cycles_number - current_cycle, current_cycle);

            if (running_processes.empty()) {
                break;
            }

            ++current_cycle;
            std::chrono::steady_clock::time_point current_time = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::seconds>(current_time - begin).count() >= time) {
                std::cout << "time: " << time << std::endl;
                break;
            }
        }

        std::cout << "No more process doable at time " << current_cycle << "\n";
        std::cout << "Stock :" << "\n";
        for (auto& resource : graph.GetResources()) {
            std::cout << " " << resource.GetName() << " => " << static_cast<size_t>(resource.GetNumber()) << "\n";
        }
    }
    catch (const std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }
    exit(0);
}
