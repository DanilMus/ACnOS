#include <iostream>
#include <stdexcept>
#include <vector>
#include <limits>

// runtime_error: общий тип исключений, которые возникают во время выполнения
// В этом примере divideNumbers проверяет, равен ли делитель нулю, и, если да, бросает исключение std::runtime_error.
double divideNumbers(double numerator, double denominator) {
    if (denominator == 0) {
        throw std::runtime_error("Division by zero is undefined");
    }
    return numerator / denominator;
}

int main() {
    try {
        double result = divideNumbers(10.0, 2.0);
        std::cout << "Result: " << result << std::endl;

        // Попытаемся делить на ноль
        result = divideNumbers(5.0, 0.0);
        std::cout << "Result: " << result << std::endl;  // Эта строка не выполнится
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}






// range_error: исключение, которое возникает, когда полученный результат превосходит допустимый диапазон
// В этом примере функция getElement получает элемент из массива по заданному индексу. 
// Если индекс находится вне допустимого диапазона (отрицательный или больше или равен размеру массива), функция бросает исключение std::range_error.
int getElement(const int array[], int size, int index) {
    if (index < 0 || index >= size) {
        throw std::range_error("Index out of range");
    }
    return array[index];
}

int main() {
    int myArray[] = {1, 2, 3, 4, 5};

    try {
        int element = getElement(myArray, 5, 2);
        std::cout << "Element at index 2: " << element << std::endl;

        // Попытаемся получить элемент с индексом за пределами массива
        element = getElement(myArray, 5, 10);
        std::cout << "This line won't be executed" << std::endl;
    } catch (const std::range_error &e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}







// overflow_error: исключение, которое возникает, если полученный результат превышает допустимый диапазон
// В этом примере функция multiply умножает два числа и проверяет на переполнение. 
// Если умножение приводит к переполнению, бросается исключение std::overflow_error.
int multiply(int a, int b) {
    // Проверка на переполнение
    if ((b > 0 && a > INT_MAX / b) || (b < 0 && a < INT_MIN / b)) {
        throw std::overflow_error("Multiplication overflow");
    }
    return a * b;
}

int main() {
    try {
        int result = multiply(5, 2);
        std::cout << "Result of multiplication: " << result << std::endl;

        // Попытаемся вызвать переполнение при умножении
        result = multiply(INT_MAX, 2);
        std::cout << "This line won't be executed" << std::endl;
    } catch (const std::overflow_error &e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}





// underflow_error: исключение, которое возникает, если полученный в вычислениях результат имеет недопустимое отрицательное значение (выход за нижнюю допустимую границу значений)
double divideSafely(double numerator, double denominator) {
    // Проверка на переполнение
    if (denominator == 0.0) {
        throw std::runtime_error("Division by zero");
    }
    if ((numerator > 0 && denominator < std::numeric_limits<double>::min() / numerator) ||
        (numerator < 0 && denominator > std::numeric_limits<double>::min() / numerator)) {
        throw std::underflow_error("Division underflow");
    }

    return numerator / denominator;
}

int main() {
    try {
        double result = divideSafely(10.0, 2.0);
        std::cout << "Result of division: " << result << std::endl;

        // Попытаемся вызвать underflow при делении
        result = divideSafely(1.0, std::numeric_limits<double>::min());
        std::cout << "This line won't be executed" << std::endl;
    } catch (const std::underflow_error &e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    } catch (const std::runtime_error &e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}




// logic_error: исключение, которое возникает при наличии логических ошибок к коде программы
// В этом примере функция performOperation проверяет, является ли переданное значение отрицательным, и если это так, бросает исключение std::logic_error
void performOperation(int value) {
    if (value < 0) {
        throw std::logic_error("Negative value is not allowed");
    }
    // выполнение операции, если значение положительное
}

int main() {
    try {
        performOperation(10); // Операция будет выполнена
        performOperation(-5); // Бросит исключение std::logic_error
    } catch (const std::logic_error &e) {
        std::cerr << "Logic error: " << e.what() << std::endl;
    }

    return 0;
}





// domain_error: исключение, которое возникает, если для некоторого значения, передаваемого в функцию, не определен результат
// В этом примере функция calculateSquareRoot вычисляет квадратный корень из переданного значения. Если значение отрицательное, она бросает исключение std::domain_error.
double calculateSquareRoot(double value) {
    if (value < 0) {
        throw std::domain_error("Cannot calculate square root of a negative number");
    }
    return sqrt(value);
}

int main() {
    try {
        double result = calculateSquareRoot(25.0); // Вычислит корень из 25
        std::cout << "Result: " << result << std::endl;

        result = calculateSquareRoot(-10.0); // Бросит исключение std::domain_error
    } catch (const std::domain_error &e) {
        std::cerr << "Domain error: " << e.what() << std::endl;
    }

    return 0;
}


// invalid_argument: исключение, которое возникает при передаче в функцию некорректного аргумента
// В этом примере функция processString обрабатывает строку и бросает исключение std::invalid_argument, если строка пуста.
void processString(const std::string& str) {
    if (str.empty()) {
        throw std::invalid_argument("Input string cannot be empty");
    }
    // Обработка строки, если она не пуста
    std::cout << str << std::endl;
}

int main() {
    try {
        processString("Hello"); // Обработает непустую строку
        processString("");      // Бросит исключение std::invalid_argument
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    }

    return 0;
}



// length_error: исключение, которое возникает при попытке создать объект большего размера, чем допустим для данного типа
// В этом примере функция processVector обрабатывает вектор и бросает исключение std::length_error, если размер вектора превышает максимально допустимый. 
void processVector(const std::vector<int>& vec) {
    if (vec.size() > std::numeric_limits<std::size_t>::max()) {
        throw std::length_error("Vector size exceeds maximum allowed length");
    }
    // Обработка вектора, если его размер допустим
    std::cout << vec.size() << std::endl;
}

int main() {
    try {
        std::vector<int> myVector(1000000); // Создаст вектор размером 1000000
        processVector(myVector);

        std::vector<int> largeVector(std::numeric_limits<std::size_t>::max() - 1);
        processVector(largeVector); // Бросит исключение std::length_error
    } catch (const std::length_error& e) {
        std::cerr << "Length error: " << e.what() << std::endl;
    }

    return 0;
}





// out_of_range: исключение, которое возникает при попытке доступа к элементам вне допустимого диапазона
// В этом примере функция getElement получает элемент из вектора по заданному индексу. 
// Если индекс находится вне допустимого диапазона (равен или больше размера вектора), функция бросает исключение std::out_of_range.
int getElement(const std::vector<int>& vec, std::size_t index) {
    if (index >= vec.size()) {
        throw std::out_of_range("Index is out of range");
    }
    return vec[index];
}

int main() {
    try {
        std::vector<int> myVector = {1, 2, 3, 4, 5};
        int element = getElement(myVector, 2); // Получит элемент с индексом 2
        std::cout << "Element at index 2: " << element << std::endl;

        element = getElement(myVector, 10); // Бросит исключение std::out_of_range
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range error: " << e.what() << std::endl;
    }

    return 0;
}



// bad_alloc - исключение выбрасываемое при ошибках с динамическими структурами данных
// Когда в нашем массиве закончится место для вставки вызовется исключение bad_alloc.
int main() {
    std::vector<int> vec;
    try {
        while (true) {
            vec.push_back(1);
        }
    }
    catch (const std::bad_alloc& e) {
        std::cout << "Место закончилось после вставки " << vec.size() << " элементов" << std::endl;
    }
}