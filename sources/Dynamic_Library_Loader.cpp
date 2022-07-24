#include "../includes/Dynamic_Library_Loader.hpp"

//? Dynamic Library Loader (.so)
Static_Library_Loader::Static_Library_Loader() {}

Static_Library_Loader::~Static_Library_Loader() {}

void *Static_Library_Loader::openFile(std::string const &file)
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

int Static_Library_Loader::closeFile(void) const { return dlclose(_handler); }

char *Static_Library_Loader::errorLog(void) const { return dlerror(); }
