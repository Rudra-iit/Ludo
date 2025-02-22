#include <winsock2.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#pragma comment(lib, "ws2_32.lib")

int board[10][10], snake[10][10], i, j, w=0, q=0;

void print (int board[10][10]) {

    printf ("\n");

    for (i=10-1; i>=0; i--) {

        for (j=10-1; j>=0; j--) {

            if (board[i][j]==100) {
                printf ("%d ", board[i][j]);
            }

            else if (board[i][j]>=10 && board[i][j]<100) {
                printf (" %d ", board[i][j]);
            }

            else {
                printf ("  %d ", board[i][j]);
            }

        }

        printf ("\n");

    }

}

int main() {
    for (i=10-1; i>=0; i--) {
        for (j=10-1; j>=0; j--) {
            snake[i][j] = i*10 + (j+1);
        }
    }
    
    WSADATA wsa;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in server, client;
    char buffer[256];

    // Initialize Winsock
    WSAStartup(MAKEWORD(2, 2), &wsa);

    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    // Bind socket
    bind(serverSocket, (struct sockaddr*)&server, sizeof(server));
    listen(serverSocket, 3);

    // Accept incoming connection
    int c = sizeof(struct sockaddr_in);
    clientSocket = accept(serverSocket, (struct sockaddr*)&client, &c);

    for (int i = 0; i < 10; ++i) {
        // Receive data from client
        recv(clientSocket, buffer, sizeof(buffer), 0);
        int clientNumber = atoi(buffer);
        std::cout << "Received from client: " << clientNumber << std::endl;

        // Get user input
        int serverNumber;
        std::cout << "Enter a number to send to client: ";
        std::cin >> serverNumber;

        // Send data to client
        sprintf(buffer, "%d", serverNumber);
        send(clientSocket, buffer, sizeof(buffer), 0);
    }

    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}