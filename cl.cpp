#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    sockaddr_in serverAddr;
    char buffer[1024] = "Hello from client";

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        return 1;
    }

    // Create a socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed." << std::endl;
        WSACleanup();
        return 1;
    }

    // Connect to the server
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("10.100.201.119"); // Server IP address
    serverAddr.sin_port = htons(8080);
    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        int error = WSAGetLastError ();
        std::cerr << "Connection to server failed. " << error << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    // Send data to the server
    send(clientSocket, buffer, strlen(buffer), 0);

    // Receive data from the server
    recv(clientSocket, buffer, sizeof(buffer), 0);
    std::cout << "Received from server: " << buffer << std::endl;

    // Close socket
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}