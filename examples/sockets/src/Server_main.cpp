#include <Server.hpp>
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

    Server server;
    server.startThreaded();

    while (running && server.isRunning()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    server.stop();
    return 0;
}
