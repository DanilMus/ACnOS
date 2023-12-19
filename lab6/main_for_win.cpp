#include <iostream>
#include <windows.h>

typedef int (*ShowMessageFunction)();

int main() {
    // Явное связывание
    const char* libraryName = "libexample.dll";

    HMODULE lib = LoadLibraryA(libraryName);
    if (!lib) {
        std::cerr << "Cannot open library." << std::endl;
        return 1;
    }

    ShowMessageFunction showMessage = reinterpret_cast<ShowMessageFunction>(GetProcAddress(lib, "showMessage"));
    if (!showMessage) {
        std::cerr << "Cannot load symbol showMessage." << std::endl;
        FreeLibrary(lib);
        return 1;
    }

    int result = showMessage();
    std::cout << "Returned: " << result << std::endl;

    // Неявное связывание
    ShowMessageFunction showMessageImplicit = reinterpret_cast<ShowMessageFunction>(GetProcAddress(lib, "showMessage"));
    if (!showMessageImplicit) {
        std::cerr << "Cannot load symbol showMessage." << std::endl;
        FreeLibrary(lib);
        return 1;
    }

    int resultImplicit = showMessageImplicit();
    std::cout << "Returned implicitly: " << resultImplicit << std::endl;

    FreeLibrary(lib);

    return 0;
}
