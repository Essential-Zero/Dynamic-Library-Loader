#ifndef DYNAMIC_LIBRARY_LOADER_HPP_
#define DYNAMIC_LIBRARY_LOADER_HPP_

#include <iostream>
#include <dlfcn.h>
#include <memory>

class Static_Library_Loader {
    public:
        Static_Library_Loader(const Static_Library_Loader &) = delete;
        explicit Static_Library_Loader();
        ~Static_Library_Loader();

            //? Open Dynamic Library File (File.so)
            void *openFile(std::string const &);

            //? Load Opened File Into Memory & Access Its Entry Point
        template <typename T>
        T loadFile(std::string const &entryPoint) const
        {
            return (T)dlsym(_handler, entryPoint.c_str()); //? entryPoint Represent The Needed Entry Point
        }

        //? Close Loaded File
        int closeFile() const;

        //? Log Error From Last _handler Instance
        char *errorLog() const;

    protected:
    private:
        void *_handler = nullptr;
};

template <class T>
class Type_Allocator {
    public:
        typedef std::unique_ptr<T> (*UniqueTypePtr)();
        typedef std::shared_ptr<T> (*SharedTypePtr)();
};

class Dynamic_Library_Loader {
    //? Entry Point Must Be Set From Your Side Using The extern C Linkage
    public:
        //? Dynamic_Library_Loader Types For Dynamic Library Loader
        Dynamic_Library_Loader(const Dynamic_Library_Loader &) = delete;
        explicit Dynamic_Library_Loader() {}
        ~Dynamic_Library_Loader() {}

        template <typename T>
        using UniqueTypePtr = typename Type_Allocator<T>::UniqueTypePtr;

        template <typename T>
        auto loadUnique(std::string const &file, std::string const &entryPoint)
        {
            _libraryInstance.openFile(file);
            UniqueTypePtr<T> ptr = _libraryInstance.loadFile<UniqueTypePtr<T>>(entryPoint);
            return ptr();
        }

        template <typename T>
        using SharedTypePtr = typename Type_Allocator<T>::SharedTypePtr;

        template <typename T>
        auto loadShared(std::string const &file, std::string const &entryPoint)
        {
            _libraryInstance.openFile(file);
            SharedTypePtr<T> ptr = _libraryInstance.loadFile<SharedTypePtr<T>>(entryPoint);
            return ptr();
        }

        void free(void) const { _libraryInstance.closeFile(); }

    private:
        Static_Library_Loader _libraryInstance;
};

#endif /* !DYNAMIC_LIBRARY_LOADER_HPP_ */
