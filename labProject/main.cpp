#include <iostream>
#include <vector>
#include <thread>
#include <curl/curl.h>
#include <fstream>

// Функция для загрузки веб-страницы
size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

// Функция, которую выполняет каждый поток
void downloadWebPage(const std::string& url, const std::string& filename) {
    CURL* curl = curl_easy_init();
    if (curl) {
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
            std::cerr << "Error downloading " << url << ": " << curl_easy_strerror(res) << std::endl;
        } else {
            // Сохранение в буфере в файл
            std::ofstream outputFile(filename);
            if (outputFile.is_open()) {
                outputFile << buffer;
                std::cout << "Downloaded content from " << url << " saved to " << filename << std::endl;
            } else {
                std::cerr << "Error opening file " << filename << " for writing." << std::endl;
            }
        }

        // Освобождение ресурсов CURL
        curl_easy_cleanup(curl);
    }
}

int main() {
    // Список URL-адресов для загрузки
    std::vector<std::string> urls = {"https://metanit.com/sql/mysql/2.4.php"};

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
