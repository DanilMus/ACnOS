#include <iostream>

extern "C" int showMessage() {
    std::cout << "Hello from DLL!" << std::endl;
    return 52;
}
