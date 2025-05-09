#pragma once

#include <atomic>
#include <thread>

class HelloWorld {
  public:
    HelloWorld() {}
    ~HelloWorld() { stop(); }

    void start();
    void stop();

  private:
    void run();

    std::thread       m_worker;
    std::atomic<bool> m_shouldRun{true};

    size_t m_count = 0;
};