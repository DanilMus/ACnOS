#include <iostream>
#include <vector>
#include <thread>
#include <curl/curl.h>
#include <fstream>
#include <system_error>

// Функция, которую выполняет каждый поток
void downloadWebPage(const std::string& url, const std::string& filename) {
    try {
        CURL* curl = curl_easy_init();
        if (!curl) {
            throw std::system_error(errno, std::generic_category(), "Failed to initialize CURL");
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Буфер для хранения загруженной веб-страницы
        std::string buffer;

        // Установка колбека для записи данных в буфер
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

        // Выполнение запроса
        CURLcode res = curl_easy_perform(curl);

        // Обработка ошибок
        if (res != CURLE_OK) {
            throw std::system_error(res, std::generic_category(), "Error downloading " + url);
        } else {
            // Сохранение в буфере в файл
            std::ofstream outputFile(filename);
            if (outputFile.is_open()) {
                outputFile << buffer;
                std::cout << "Downloaded content from " << url << " saved to " << filename << std::endl;
            } else {
                throw std::system_error(errno, std::generic_category(), "Error opening file " + filename + " for writing");
            }
        }

        // Освобождение ресурсов CURL
        curl_easy_cleanup(curl);
    } catch (const std::system_error& e) {
        std::cerr << "Thread error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Thread error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown thread error" << std::endl;
    }
}

int main() {
    // Список URL-адресов для загрузки
    std::vector<std::string> urls = {};

    // Пополение адресов
    std::cout << "Введите url адреса через enter, когда закончите, введите 0: " << std::endl;

    std::string url;
    do {
        std::cin >> url; 
        urls.push_back(url);
    } while (url != "0");
    urls.pop_back();

    // Вектор для хранения потоков
    std::vector<std::thread> threads;

    // Запуск потоков для загрузки веб-страниц
    for (size_t i = 0; i < urls.size(); ++i) {
        threads.emplace_back(downloadWebPage, urls[i], "output" + std::to_string(i) + ".html");
    }

    // Дождитесь завершения всех потоков
    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
