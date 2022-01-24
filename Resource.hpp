#pragma once

#include <cstdlib>
#include <vector>
#include <string>

class Process;

class Resource {
public:
    Resource(std::string name, size_t number);

    void Add(size_t number);

    [[nodiscard]] const std::string& GetName() const;

    [[nodiscard]] size_t GetNumber() const;

    void AddProcess(Process* process);

    [[nodiscard]] const std::vector<Process*>& GetProcesses() const;

    void SetCurrentPrice(double current_price);

    [[nodiscard]] bool IsAvailable() const;

    void SetAvailable(bool available);

private:
    std::string _name;
    std::vector<Process*> _processes;
    size_t _number = 0;
    double _current_price = 0;
    bool _available = true;
};
