#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <string>

const int bufferSize = 5;
std::string buffer[bufferSize];
int writeIndex = 0;
int readIndex = 0;
int itemCount = 0;

std::mutex mtx;
std::condition_variable cvReader, cvWriter;

void writerThread(int id) {
    for (int i = 0; i < 5; ++i) {
        std::unique_lock<std::mutex> lock(mtx);

        // Ждем, пока есть место для записи
        cvWriter.wait(lock, [] { return itemCount < bufferSize; });

        // Записываем данные в буфер
        buffer[writeIndex] = "Writer " + std::to_string(id) + ": Data " + std::to_string(i);
        std::cout << buffer[writeIndex] << std::endl;

        // Обновляем индекс для записи и количество элементов
        writeIndex = (writeIndex + 1) % bufferSize;
        itemCount++;

        // Оповещаем потоки-читатели
        cvReader.notify_all();
        cvWriter.notify_all();
    }
}

void readerThread(int id) {
    for (int i = 0; i < 5; ++i) {
        std::unique_lock<std::mutex> lock(mtx);

        // Ждем, пока есть данные для чтения
        cvReader.wait(lock, [] { return itemCount > 0; });

        // Считываем данные из буфера
        std::cout << "Reader " << id << ": " << buffer[readIndex] << std::endl;

        // Обновляем индекс для чтения и количество элементов
        readIndex = (readIndex + 1) % bufferSize;
        itemCount--;

        // Оповещаем потоки-писатели
        cvWriter.notify_all();
        cvReader.notify_all();
    }
}

int main() {
    std::vector<std::thread> writers, readers;

    // Создание потоков для писателей и читателей
    for (int i = 0; i < 3; ++i) {
        writers.emplace_back(writerThread, i);
        readers.emplace_back(readerThread, i);
    }

    // Ожидание завершения всех потоков
    for (auto& writer : writers) {
        writer.join();
    }
    for (auto& reader : readers) {
        reader.join();
    }

    return 0;
}
