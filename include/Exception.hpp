#include <exception>

class HeroException : public std::exception
{
public:
    HeroException() {}

    const char *what() const
    {
        return "Invalid location";
    }
};

class AllInvalid : public std::exception
{
public:
    AllInvalid() {}

    const char *what() const
    {
        return "Invalid input";
    }
};