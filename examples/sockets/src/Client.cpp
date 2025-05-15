#include <Client.hpp>

#include <cstring>
#include <iostream>
#include <thread>

void Client::startThreaded() {
    m_worker = std::thread(&Client::run, this);
    return;
}

void Client::stop() {
    m_shouldRun = false;
    if (m_worker.joinable()) {
        m_worker.join();
    }
    return;
}

void Client::run() {
    init();

    const char message[] = "Hello, server!\n";

    while (m_shouldRun) {
        ssize_t sent = send(m_clientSocket, message, strlen(message), 0);
        if (sent < 0) {
            std::cout << "send failed" << std::endl;
        } else if (sent == 0) {
            std::cout << "server shutdown connection" << std::endl;
            m_shouldRun = false;
        } else {
            std::cout << message;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1'000));
    }

    std::cout << "client shutting down" << std::endl;
    shutdown(m_clientSocket, SHUT_RDWR);
    return;
}

void Client::init() {
    m_clientSocket               = socket(SIN_FAMILY, SOCKET_TYPE, 0);
    m_serverAddr.sin_family      = SIN_FAMILY;
    m_serverAddr.sin_port        = PORT;
    m_serverAddr.sin_addr.s_addr = IP_ADDRESS;
    if (connect(m_clientSocket, (struct sockaddr *) &m_serverAddr,
                sizeof(m_serverAddr))) {
        m_shouldRun = false;
        std::cerr << "Connect failed" << std::endl;
        return;
    }
    std::cout << "Socket connection established" << std::endl;
}