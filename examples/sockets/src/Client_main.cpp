#include <Client.hpp>
#include <atomic>
#include <csignal>
#include <iostream>
#include <thread>

// Use atomic for thread-safe signal handling
std::atomic<bool> running(true);

void signalHandler(int signum) {
    running = false;
}

int main(void) {
    std::signal(SIGINT, signalHandler);

    Client client;
    client.startThreaded();

    while (running && client.isRunning()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "client shutting down cleanly" << std::endl;

    client.stop();
    return 0;
}
