#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

const int bufferSize = 1;
std::string buffer;
std::mutex mtx;
std::condition_variable cv;
bool dataReady = false;

// Поток-писатель
void writerThread(const std::string& data) {
    std::unique_lock<std::mutex> lock(mtx);
    
    // Ждем, пока буфер не освободится
    cv.wait(lock, [] { return !dataReady; });

    // Записываем данные в буфер
    buffer = data;
    std::cout << "Writer: " << data << std::endl;

    // Устанавливаем флаг готовности данных
    dataReady = true;

    // Оповещаем поток-читатель
    cv.notify_all();
}

// Поток-читатель
void readerThread() {
    std::unique_lock<std::mutex> lock(mtx);

    // Ждем, пока данные не будут доступны
    cv.wait(lock, [] { return dataReady; });

    // Считываем данные из буфера
    std::cout << "Reader: " << buffer << std::endl;

    // Сбрасываем флаг готовности данных
    dataReady = false;

    // Оповещаем поток-писатель
    cv.notify_all();
}

int main() {
    // Пример использования
    std::thread writer(writerThread, "Hello, writer!");
    std::thread reader(readerThread);

    writer.join();
    reader.join();

    return 0;
}
