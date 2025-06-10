#include <HelloWorld.hpp>

#include <iostream>
#include <thread>

void HelloWorld::start() {
    m_worker = std::thread(&HelloWorld::run, this);
    return;
}

void HelloWorld::stop() {
    m_shouldRun = false;
    if (m_worker.joinable()) {
        m_worker.join();
    }
    return;
}

void HelloWorld::run() {
    while (m_shouldRun) {
        std::cout << "Hello World! " << m_count++ << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return;
}