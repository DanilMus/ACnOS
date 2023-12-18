#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

const int bufferSize = 5;  // Размер циклического буфера
int buffer[bufferSize];
int writeIndex = 0;  // Индекс для записи
int readIndex = 0;   // Индекс для чтения
int itemCount = 0;    // Количество элементов в буфере

std::mutex mtx;
std::condition_variable cv;

// Поток-писатель
void writerThread(int data) {
    std::unique_lock<std::mutex> lock(mtx);

    // Ждем, пока есть место для записи
    cv.wait(lock, [] { return itemCount < bufferSize; });

    // Записываем данные в буфер
    buffer[writeIndex] = data;
    std::cout << "Writer: " << data << std::endl;

    // Обновляем индекс для записи и количество элементов
    writeIndex = (writeIndex + 1) % bufferSize;
    itemCount++;

    // Оповещаем поток-читатель
    cv.notify_all();
}

// Поток-читатель
void readerThread() {
    std::unique_lock<std::mutex> lock(mtx);

    // Ждем, пока есть данные для чтения
    cv.wait(lock, [] { return itemCount > 0; });

    // Считываем данные из буфера
    int data = buffer[readIndex];
    std::cout << "Reader: " << data << std::endl;

    // Обновляем индекс для чтения и количество элементов
    readIndex = (readIndex + 1) % bufferSize;
    itemCount--;

    // Оповещаем поток-писатель
    cv.notify_all();
}

int main() {
    // Пример использования
    std::thread writer1(writerThread, 1);
    std::thread reader1(readerThread);
    std::thread writer2(writerThread, 2);
    std::thread reader2(readerThread);

    writer1.join();
    reader1.join();
    writer2.join();
    reader2.join();

    return 0;
}
