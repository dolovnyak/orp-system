#include <limits>
#include <cmath>
#include <unordered_map>
#include <queue>
#include "argparse.hpp"
#include "Graph.hpp"
#include "Grammar.yy.hpp"
#include "PriceCoefficientCalculator.hpp"

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

void run_optimize_processes_by_profit(Graph& graph, std::list<Process>& running_processes, size_t remaining_cycles) {
    std::list<Process*> possible_to_run_processes;

    for (auto& process: graph.GetProcesses()) {
        if (process.CanStart(remaining_cycles)) {
            possible_to_run_processes.push_back(&process);
        }
    }
    if (possible_to_run_processes.empty()) {
        return;
    }

    /// Пoка лист процессов не пуст:
    ///     * Удалить из листа все процессы, которые не могут быть запущены.
    ///     * Для всех процессов, которые могут быть запущены - вычислить их профит
    ///     * Запустить самый выгодный процесс
//    Process* max_profit_process;
//    double current_max_profit = std::numeric_limits<double>::lowest();
//    for (auto process: possible_to_run_processes) {
//        double tmp_max_profit = process->CalculateProfit();
//        if (tmp_max_profit > current_max_profit) {
//            max_profit_process = process;
//            current_max_profit = tmp_max_profit;
//        }
//    }
//    Process running_process(*max_profit_process);
//    running_process.StartProcess();
//    running_processes.push_back(running_process);

    while (!possible_to_run_processes.empty()) {
        Process* max_profit_process;
        double current_max_profit = 0;
        for (auto process : possible_to_run_processes) {
            double tmp_max_profit = process->CalculateProfit();
            if (tmp_max_profit > current_max_profit) {
                max_profit_process = process;
            }
        }
        Process running_process(*max_profit_process);
        running_process.StartProcess();
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

//    argparse.add_argument("time")
//            .default_value()
//            .help("specify the work time.");

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
        Graph graph = parse_graph(open_file(argparse.get<std::string>("input_file")));
        PriceCoefficientCalculator::Calculate(graph);
        std::list<Process> running_processes;
        size_t cycles_number = argparse.get<size_t>("--cycles");
        size_t current_cycle = 0;

        while (current_cycle < cycles_number) {

            for (auto& resource: graph.GetResources()) {
                resource.SetAvailable(true);
            }

            /// increment all processes, stop and collect resources if needed cycles done
            running_processes_processing(running_processes);

            run_optimize_processes_by_profit(graph, running_processes, cycles_number - current_cycle);

            if (running_processes.empty()) {
                std::cout << "current cycle: " << current_cycle << std::endl;
                break;
            }

            ++current_cycle;
        }
        graph.Print();
    }
    catch (const std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }
    exit(0);
}
