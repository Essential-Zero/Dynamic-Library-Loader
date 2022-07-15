#include "../includes/Dynamic_Library_Loader.hpp"

//? Dynamic Library Loader (.so)
Basic_Loader::Library_Loader::Library_Loader() {}

Basic_Loader::Library_Loader::~Library_Loader() {}

void *Basic_Loader::Library_Loader::openFile(std::string const &file)
{
    _handler = dlopen(file.c_str(), RTLD_LAZY);
    if (_handler == nullptr) {
        std::cerr << "  -> " << file << ": could not open" << std::endl;
        std::cerr << "  -> " << errorLog() << std::endl;
        return nullptr;
    } else {
        std::cout << "  -> " << file << ": opened" << std::endl;
        return _handler;
    }
}

int Basic_Loader::Library_Loader::closeFile(void) const { return dlclose(_handler); }

char *Basic_Loader::Library_Loader::errorLog(void) const { return dlerror(); }
