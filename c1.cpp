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

    int y = 0;

    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    char buffer[1024];
    struct timeval timeout;
    fd_set readfds;

    // Initialize Winsock
    WSAStartup(MAKEWORD(2, 2), &wsa);

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8888);

    // Connect to server
    connect(sock, (struct sockaddr*)&server, sizeof(server));

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(sock, &readfds);

        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

        int activity = select(0, &readfds, NULL, NULL, &timeout);

        // Get user input
        int clientNumber;
        std::cout << "Enter a number to send to server: ";
        std::cin >> clientNumber;

        // Send data to server
        sprintf(buffer, "%d", clientNumber);
        send(sock, buffer, sizeof(buffer), 0);
        
        if (activity > 0 && FD_ISSET(sock, &readfds)) {
            // Receive data from server
            recv(sock, buffer, sizeof(buffer), 0);
            int serverNumber = atoi(buffer);
            std::cout << "Received from server: " << serverNumber << std::endl;
            for (i=0; i<10; i++) {
                for (j=0; j<10; j++) {
                    board[i][j] = snake[i][j];
                    if (y==serverNumber) {
                        board[i][j] = 0;
                    }
                }
            }
            print (board);
        }
        recv (sock, buffer, sizeof(buffer), 0);
        int w = atoi (buffer);
        printf (" %d\n", w);

        if (y==100) {
            break;
        }

        if (y>100) {
            y=y-10;
        }

        if (w==5) {
            break;
        }
    }

    closesocket(sock);
    WSACleanup();

    return 0;
}