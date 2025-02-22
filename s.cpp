#include <winsock2.h>
#include <iostream>
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

    int y = 0;

    WSADATA wsa;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in server, client;
    char buffer[1024];
    fd_set readfds;
    struct timeval timeout;

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

    while (1) {
        // Set up the file descriptor set
        FD_ZERO(&readfds);
        FD_SET(clientSocket, &readfds);

        // Set up the timeout struct
        timeout.tv_sec = 5;  // 5 seconds timeout
        timeout.tv_usec = 0;

        int activity = select(0, &readfds, NULL, NULL, &timeout);

        if (activity > 0 && FD_ISSET(clientSocket, &readfds)) {
            // Data is available to be read from the client
            recv(clientSocket, buffer, sizeof(buffer), 0);
            int clientNumber = atoi(buffer);
            std::cout << "Received from client: " << clientNumber << std::endl;
            y = y+clientNumber;
            for (i=0; i<10; i++) {
                for (j=0; j<10; j++) {
                    board[i][j] = snake[i][j];
                    if (y==snake[i][j]) {
                        board[i][j] = 0;
                    }
                }
            }
            print (board);
        } else {
            // Timeout or error, proceed to print server's own input
            std::cout << "Client did not respond in time, printing server's own input: " << i << std::endl;
            w++;
            sprintf (buffer, "%d", w);
            send (clientSocket, buffer, sizeof(buffer), 0);
        }

        // Wait for next client response
        std::cout << "Enter a number to send to client: ";
        int serverNumber;
        std::cin >> serverNumber;

        // Send data to client
        sprintf(buffer, "%d", serverNumber);
        send(clientSocket, buffer, sizeof(buffer), 0);

        if (y == 100) {
            break;
        }

        if (y>100) {
            y = y - 10;
        }

        if (w==5) {
            printf ("You won!\n");
            break;
        }
    }

    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}