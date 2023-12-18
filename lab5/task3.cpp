#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

const int numPhilosophers = 5;

std::mutex chopstickMutex[numPhilosophers];
std::condition_variable cv;

void philosopher(int id) {
    int leftChopstick = id;
    int rightChopstick = (id + 1) % numPhilosophers;

    std::unique_lock<std::mutex> leftLock(chopstickMutex[leftChopstick]);
    std::unique_lock<std::mutex> rightLock(chopstickMutex[rightChopstick]);

    // Философ обедает (использует палочки)
    std::cout << "Philosopher " << id << " is eating." << std::endl;

    // Имитация времени обеда (случайная задержка)
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // Философ заканчивает обед и освобождает палочки
    rightLock.unlock();
    leftLock.unlock();

    // Имитация времени между приемами пищи (случайная задержка)
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Философ думает
    std::cout << "Philosopher " << id << " is thinking." << std::endl;

    // Имитация времени размышлений (случайная задержка)
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // После размышлений философ вновь голоден и повторяет процесс
    philosopher(id);
}

int main() {
    std::vector<std::thread> philosophers;

    // Создание потоков для философов
    for (int i = 0; i < numPhilosophers; ++i) {
        philosophers.emplace_back(philosopher, i);
    }

    // Ожидание завершения всех потоков
    for (auto& thread : philosophers) {
        thread.join();
    }

    return 0;
}
