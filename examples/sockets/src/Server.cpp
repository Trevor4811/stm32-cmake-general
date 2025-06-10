#include <Server.hpp>

#include <errno.h>
#include <iostream>
#include <thread>

void Server::startThreaded() {
    m_worker = std::thread(&Server::run, this);
    return;
}

void Server::stop() {
    m_shouldRun = false;
    if (m_worker.joinable()) {
        m_worker.join();
    }
    return;
}

void Server::run() {
    init();
    std::cout << "Client socket: " << m_clientSocket << std::endl;

    char buffer[1024] = {0};

    while (m_shouldRun) {
        ssize_t bytesReceived = recv(m_clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            std::cout << buffer;
        } else if (bytesReceived == 0) {
            std::cout << "client shutdown connection" << std::endl;
            m_shouldRun = false;
        } else {
            std::cout << "bytesReceived: " << bytesReceived
                      << "\terr: " << errno << std::endl;
        }
        // std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    shutdown(m_serverSocket, SHUT_RDWR);
    return;
}

void Server::init() {
    m_serverSocket               = socket(SIN_FAMILY, SOCKET_TYPE, 0);
    m_serverAddr.sin_family      = SIN_FAMILY;
    m_serverAddr.sin_port        = PORT;
    m_serverAddr.sin_addr.s_addr = IP_ADDRESS;
    if (bind(m_serverSocket, (struct sockaddr *) &m_serverAddr,
             sizeof(m_serverAddr)) < 0) {
        m_shouldRun = false;
        std::cerr << "Bind failed: " << errno << std::endl;
        return;
    }
    if (listen(m_serverSocket, 5) < 0) {
        m_shouldRun = false;
        std::cerr << "Listen failed" << std::endl;
        return;
    }
    m_clientSocket = accept(m_serverSocket, nullptr, nullptr);
    if (m_clientSocket < 0) {
        m_shouldRun = false;
        std::cerr << "Accept failed" << std::endl;
        return;
    }
    std::cout << "Socket connection established" << std::endl;
}