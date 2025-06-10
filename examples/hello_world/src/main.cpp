#include <HelloWorld.hpp>
#include <atomic>
#include <csignal>
#include <thread>

// Use atomic for thread-safe signal handling
std::atomic<bool> running(true);

void signalHandler(int signum) {
    running = false;
}

int main(void) {
    std::signal(SIGINT, signalHandler);

    HelloWorld inst;
    inst.start();

    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    inst.stop();
    return 0;
}
