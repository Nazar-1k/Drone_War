#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool isReady = false;

void WorkerThread()
{
    std::cout << "Worker thread: Waiting for the signal..." << std::endl;

    // Захоплення блокування мутексу
    std::unique_lock<std::mutex> lock(mtx);

    // Очікування на сигнал
    cv.wait(lock, [] { return isReady; });

    std::cout << "Worker thread: Received the signal!" << std::endl;
}

int main()
{
    std::cout << "Main thread: Starting the worker thread..." << std::endl;

    std::thread worker(WorkerThread);

    // Деяка робота в головному потоці

    std::this_thread::sleep_for(std::chrono::seconds(2));

    // Зміна стану і попередження іншого потоку
    {
        std::lock_guard<std::mutex> lock(mtx);
        isReady = true;
        cv.notify_one();
    }

    // Чекаємо на завершення роботи робітника
    worker.join();

    std::cout << "Main thread: Worker thread has finished." << std::endl;

    return 0;
}
