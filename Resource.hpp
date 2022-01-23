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

 private:
    std::string _name;
    std::vector<Process*> _processes;
    size_t _number = 0;
    size_t _current_price = 0;
};
