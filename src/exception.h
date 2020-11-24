#include <exception>

class MachineException: public std::exception {
public:
    Machineexception (const char* msg) : message(msg) {}
    const char* what() { return message; }

private:
    const char* message;
};
