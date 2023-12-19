#include <iostream>
#include <dlfcn.h> // Для неявного связывания на Linux

typedef int (*ShowMessageFunction)();

int main() {
    // Явное связывание
    void* handle = dlopen("./lib.so", RTLD_LAZY);
    if (!handle) {
        std::cerr << "Cannot open library: " << dlerror() << std::endl;
        return 1;
    }

    ShowMessageFunction showMessage = reinterpret_cast<ShowMessageFunction>(dlsym(handle, "showMessage"));
    if (!showMessage) {
        std::cerr << "Cannot load symbol showMessage: " << dlerror() << std::endl;
        dlclose(handle);
        return 1;
    }

    int result = showMessage();
    std::cout << "Returned: " << result << std::endl;

    // Неявное связывание
    #ifdef _WIN32
        HMODULE lib = LoadLibrary("lib.dll");
    #else
        void* lib = dlopen("./lib.so", RTLD_LAZY);
    #endif

    if (!lib) {
        std::cerr << "Cannot open library." << std::endl;
        return 1;
    }

    ShowMessageFunction showMessageImplicit = reinterpret_cast<ShowMessageFunction>(dlsym(lib, "showMessage"));
    if (!showMessageImplicit) {
        std::cerr << "Cannot load symbol showMessage." << std::endl;
        #ifdef _WIN32
            FreeLibrary(lib);
        #else
            dlclose(lib);
        #endif
        return 1;
    }

    int resultImplicit = showMessageImplicit();
    std::cout << "Returned implicitly: " << resultImplicit << std::endl;

    #ifdef _WIN32
        FreeLibrary(lib);
    #else
        dlclose(lib);
    #endif

    return 0;
}
