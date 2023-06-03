#include <iostream>
#include <thread>

// Function to be executed in a separate thread
void threadFunction()
{
    std::cout << "This is executed in a separate thread!" << std::endl;
}

int main()
{
    std::cout << "This is executed in the main thread!" << std::endl;

    // Create a thread object and pass it the function to be executed
    std::thread myThread(threadFunction);

    // Wait for the thread to finish execution
    myThread.join();

    std::cout << "Main thread finished!" << std::endl;

    return 0;
}