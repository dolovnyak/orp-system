#pragma once

#include <cstdlib>
#include <vector>
#include <string>
#include <list>
#include <algorithm>

class Process;

class Resource {
public:
    Resource(std::string name, double number);

    void Add(double number);

    [[nodiscard]] const std::string& GetName() const;

    [[nodiscard]] double GetNumber() const;

    void AddProcess(Process* process);

    [[nodiscard]] std::vector<Process*>& GetProcesses();

    void SetCurrentPrice(double current_price);

    [[nodiscard]] bool IsAvailable() const;

    void SetAvailable(bool available);

    [[nodiscard]] double GetPrice() const;

    void SortProcessesByProfit();

private:
    std::string _name;
    std::vector<Process*> _processes;
    double _number = 0;
    double _price = 0;
    bool _available = true;
};
