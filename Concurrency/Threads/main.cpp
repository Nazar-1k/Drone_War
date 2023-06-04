#include <iostream>
#include <thread>

// Function to be executed in a thread
void threadFunction(int value)
{
    std::cout << "Thread function executed with value: " << value << std::endl;
}

int main()
{
    // Create a thread object
    std::thread myThread(threadFunction, 42);

    if (myThread.joinable())
    {
        std::cout << "Thread is joinable." << std::endl;

        // Wait for the thread to finish execution
        myThread.join();
    }
    else
    {
        std::cout << "Thread is not joinable." << std::endl;
    }

    // Check if the thread can be detached
    if (myThread.joinable())
    {
        myThread.detach();
        std::cout << "Thread detached." << std::endl;
    }
    else
    {
        std::cout << "Thread is not joinable. Cannot detach." << std::endl;
    }

    // Get the thread id
    std::thread::id threadId = myThread.get_id();
    std::cout << "Thread id: " << threadId << std::endl;

    // Check if the thread is active
    bool isActive = myThread.joinable();
    std::cout << "Thread is active: " << isActive << std::endl;

    // Wait to ensure the thread has finished
    std::this_thread::sleep_for(std::chrono::seconds(2));

    return 0;
}