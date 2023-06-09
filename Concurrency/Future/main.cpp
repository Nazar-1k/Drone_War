#include <iostream>
#include <future>

// Function that computes the result
int computeResult()
{
    return 42;
}

int main()
{
    // Create a promise and get the associated future
    std::promise<int> resultPromise;
    std::future<int> futureResult = resultPromise.get_future();

    // Start a separate thread to perform the computation
    std::thread computationThread([&]() {
        // Perform the computation
        int result = computeResult();

        // Set the result in the promise
        resultPromise.set_value(result);
        });

    // Wait for the computation to finish and get the result
    int result = futureResult.get();

    // Join the computation thread
    computationThread.join();

    // Output the result
    std::cout << "Result: " << result << std::endl;

    return 0;
}