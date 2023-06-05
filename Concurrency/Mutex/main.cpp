#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void printMessage(const std::string& message) 
{
	if (mtx.try_lock())
	{
		// If the lock is acquired successfully, execute the critical section
		for (int i = 0; i < 5; ++i) {
			std::cout << message << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}

		mtx.unlock();
	}
	else
	{
		// If the lock cannot be acquired, do something else
		std::cout << "Failed to acquire the lock for message: " << message << std::endl;
	}
}

int main()
{
	std::thread t1(printMessage, "Thread 1 says hello!");
	std::thread t2(printMessage, "Thread 2 says hi!");

	t1.join();
	t2.join();

	return 0;
}