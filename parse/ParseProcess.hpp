#include "Graph.hpp"

class ParseProcess {
 public:
    static void AddRequiredResource(const std::string& name, size_t number, Graph* graph);
    static void AddProducedResource(const std::string& name, size_t number, Graph* graph);

    static Process GetAndDeleteProcess(const )

 private:
    static std::vector<Resource*> _required_resources;
    static std::vector<Resource*> _produced_resources;

    /// zeroes and empty data by default
    static Process _process;
};
