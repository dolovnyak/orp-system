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

    void SetFutureIncome(double future_income);

    [[nodiscard]] const std::string& GetName() const;

    [[nodiscard]] double GetNumber() const;

    void AddProcess(Process* process);

    [[nodiscard]] std::vector<Process*>& GetProcesses();

    [[nodiscard]] bool IsAvailable() const;

    void SetAvailable(bool available);

    void SetPriceCoefficient(double price);

    [[nodiscard]] double GetEstimatedPrice() const;

    void UpdateMaxNumber(double number);

    void ResetMaxNumberIncrease();

    [[nodiscard]] bool HasMaxNumber();

    [[nodiscard]] double GetMaxNumber();

    [[nodiscard]] double GetFutureIncome();

private:
    std::string _name;
    std::vector<Process*> _processes;
    double _number = 0;
    double _future_income = 0;
    double _price_coefficient = 0;
    double _max_number = 0;
    bool _available = true;
};
