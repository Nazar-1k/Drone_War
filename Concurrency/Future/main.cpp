#include <iostream>
#include <future>

int calculateSquare(int x) {
    return x * x;
}

int main() {
   
    std::future<int> futureResult = std::async(calculateSquare, 5);

    int result = futureResult.get();

    std::cout << "Square: " << result << std::endl;

    return 0;
}
