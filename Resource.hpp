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

    void AddFuture(double number);

    [[nodiscard]] const std::string& GetName() const;

    [[nodiscard]] double GetNumber() const;

    void AddProcess(Process* process);

    [[nodiscard]] std::vector<Process*>& GetProcesses();

    [[nodiscard]] bool IsAvailable() const;

    void SetAvailable(bool available);

    [[nodiscard]] double GetPriceCoefficient() const;

    void SetPriceCoefficient(double price);

    [[nodiscard]] double GetEstimatedPrice() const;

private:
    std::string _name;
    std::vector<Process*> _processes;
    double _number = 0;
    double _future_number = 0;
    double _price_coefficient = 0;
    bool _available = true;
};
