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

    // Acquire the lock on the mutex
    std::unique_lock<std::mutex> lock(mtx);

    // Wait for the signal
    cv.wait(lock, [] { return isReady; });

    std::cout << "Worker thread: Received the signal!" << std::endl;
}

int main()
{
    std::cout << "Main thread: Starting the worker thread..." << std::endl;

    std::thread worker(WorkerThread);

    // Do some work in the main thread

    std::this_thread::sleep_for(std::chrono::seconds(2));

    // Change the state and notify the other thread
    {
        std::lock_guard<std::mutex> lock(mtx);
        isReady = true;
        cv.notify_one();
    }

    // Wait for the worker thread to finish its work
    worker.join();

    std::cout << "Main thread: Worker thread has finished." << std::endl;

    return 0;
}
