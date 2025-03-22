#include <winsock2.h>
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#pragma comment(lib, "ws2_32.lib")

int board[10][10], snake[10][10], i, j, w=0, q=0, p=0;

int s1[4] = {3, 8, 17, 26};
int s2[4] = {10, 29, 36, 40};
int s3[4] = {50, 55, 60, 64};
int s4[4] = {72, 88, 90, 93};

int l1[4] = {6, 12, 18, 24};
int l2[4] = {30, 44, 57, 70};
int l3[4] = {67, 77, 80, 81};
int l4[4] = {31, 71, 89, 97};


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
    int yy = 0;
    int yyy = 0;
    WSADATA wsa;
    SOCKET server1, server2, client1, client2;
    struct sockaddr_in server1_addr, server2_addr, client1_addr, client2_addr;
    char buffer[1024];
    int opt = 1;
    int addrlen = sizeof(struct sockaddr_in);
    fd_set readfds;
    struct timeval timeout;

    // Initialize Winsock
    WSAStartup(MAKEWORD(2, 2), &wsa);

    // Create first socket
    server1 = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server1, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));
    server1_addr.sin_family = AF_INET;
    server1_addr.sin_addr.s_addr = INADDR_ANY;
    server1_addr.sin_port = htons(8888);
    bind(server1, (struct sockaddr *)&server1_addr, sizeof(server1_addr));
    listen(server1, 3);

    // Create second socket
    server2 = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server2, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));
    server2_addr.sin_family = AF_INET;
    server2_addr.sin_addr.s_addr = INADDR_ANY;
    server2_addr.sin_port = htons(8080);
    bind(server2, (struct sockaddr *)&server2_addr, sizeof(server2_addr));
    listen(server2, 5);

    // Accept incoming connections
    client1 = accept(server1, (struct sockaddr *)&client1_addr, &addrlen);
    client2 = accept(server2, (struct sockaddr *)&client2_addr, &addrlen);

    while (1) {
        // Set up the file descriptor set
        FD_ZERO(&readfds);
        FD_SET(client1, &readfds);

        // Set up the timeout struct
        timeout.tv_sec = 5;  // 5 seconds timeout
        timeout.tv_usec = 0;

        int activity1 = select(0, &readfds, NULL, NULL, &timeout);

        if (activity1 > 0 && FD_ISSET(client1, &readfds)) {
            // Data is available to be read from the client
            recv(client1, buffer, sizeof(buffer), 0);
            int clientNumber = atoi(buffer);
            std::cout << "Received from client 1: " << clientNumber << std::endl;
            y = y+clientNumber;
            for (i=0; i<10; i++) {
                for (j=0; j<10; j++) {
                    board[i][j] = snake[i][j];
                    if (y==snake[i][j]) {
                        board[i][j] = 0;
                    }
                }
            }
            printf ("Client 1 is:\n");
            print (board);
            sprintf (buffer, "%d", clientNumber);
            send (client2, buffer, sizeof (buffer), 0);
        }
        else {
            // Timeout or error
            std::cout << "Client 1 did not respond in time" << i << std::endl;
            w++;
            sprintf (buffer, "%d", w);
            send (client1, buffer, sizeof(buffer), 0);
        }

        FD_ZERO (&readfds);
        FD_SET(client2, &readfds);
        int activity2 = select(0, &readfds, NULL, NULL, &timeout);

        if (activity2 > 0 && FD_ISSET (client2, &readfds)) {
            recv(client2, buffer, sizeof(buffer), 0);
            int newNumber = atoi (buffer);
            std:: cout << "Received from client 2: " << newNumber << std:: endl;

            yy = yy + newNumber;

            for (i=0; i<10; i++) {
                for (j=0; i<10; i++) {
                    board[i][j] = snake[i][j];
                    if (y==snake[i][j]) {
                        board[i][j] = 0;
                    }
                }
            }
            printf ("Client 2 is:\n");
            print (board);
            sprintf (buffer, "%d", newNumber);
            send (client1, buffer, sizeof(buffer), 0);
        }

        else {
            std::cout << "Client 2 did not respond in time" << i << std::endl;
            p++;
            sprintf (buffer, "%d", p);
            send (client2, buffer, sizeof(buffer), 0);
        }

        // Wait for next client response
        std::cout << "Enter a number to send to client: ";
        int serverNumber;
        std::cin >> serverNumber;

        // Send data to client
        sprintf(buffer, "%d", serverNumber);
        send(client1, buffer, sizeof(buffer), 0);
        send(client2, buffer, sizeof(buffer), 0);
        
        yyy = yyy + serverNumber;

        for (i=0; i<10; i++) {
            for (j=0; j<10; j++) {
                board[i][j] = snake[i][j];
                if (yyy == snake[i][j]) {
                    board[i][j] = 0;
                }
            }
        }
        printf ("You are:\n");
        print (board);
        sprintf (buffer, "%d", yyy);
        send(client1, buffer, sizeof(buffer), 0);
        send(client2, buffer, sizeof(buffer), 0);
        
        recv (client1, buffer, sizeof(buffer), 0);
        int abc = atoi (buffer);
        sprintf (buffer, "%d", abc);
        send (client2, buffer, sizeof(buffer), 0);


        recv (client2, buffer, sizeof(buffer), 0);
        int xyz = atoi (buffer);
        sprintf (buffer, "%d", xyz);
        send (client1, buffer, sizeof(buffer), 0);

        if (xyz == 100) {
            printf ("Client 2 won!\n");
            break;
        }

        if (abc == 100) {
            printf ("Client 1 won!\n");
            break;
        }

        if (yyy == 100) {
            printf ("You won!\n");
            break;
        }

        if (yyy>100) {
            yyy = yyy - 10;
        }
    }

    closesocket(client1);
    closesocket(server1);
    closesocket(client2);
    closesocket(server2);
    WSACleanup();

    return 0;
}