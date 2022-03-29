#include <iostream>
#include <stdexcept>
#include <memory>

void validateArguments(int argc)
{
    if(argc != 2)
    {
        std::cerr << "You need to pass 1 argument" << std::endl;
        exit(-1);
    }
}

class d_error : virtual public std::logic_error {
protected:
    std::string error_message;
public:
    d_error(const std::string& message)
    : std::logic_error(message)
    , error_message(message) {}
    virtual const char* what() const throw() {
        return error_message.c_str();
    }
};

class Resource
{
public:
    void use(const char* arg)
    {
        std::cout << "Using resource. Passed " << *arg << std::endl;
        if (*arg == 'd')
        {
            throw d_error("Passed d. d is prohibited.");
        }
    }
};

int main(int argc, char* argv[])
{
    validateArguments(argc);

    const char* argument = argv[1];
    std::unique_ptr<Resource> rsc = std::make_unique<Resource>();

    try
    {
        rsc->use(argument);
    }
    catch (d_error& e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}

