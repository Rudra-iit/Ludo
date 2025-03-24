#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <winsock2.h>
#include <windows.h>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <time.h>

#define SERVER_IP "127.0.0.1"  // Change to your server's IP address
#define SERVER_PORT 8080

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int board[10][10], snake[10][10], i, j, w=0, q=0, p=0, d=0;

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

    int y = 1;
    int life = 10;

    int k=0;
    int time_limit = 5;
    
    WSADATA wsaData;
    SOCKET clientSocket;
    SOCKADDR_IN serverAddr;
    char buffer [1024];

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Winsock initialization failed.\n";
        return 1;
    }

    // Create client socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket.\n";
        WSACleanup();
        return 1;
    }

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);  // Server's IP address
    serverAddr.sin_port = htons(SERVER_PORT);

    // Connect to the server
    if (connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Connection to server failed.\n";
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Connected to the server.\n";

    // Input three integers from the user
    /* int numbers[3];
    std::cout << "Enter three integers:\n";
    for (int i = 0; i < 3; ++i) {
        std::cout << "Number " << (i + 1) << ": ";
        std::cin >> numbers[i];
    } */

    printf ("Welcome!\n");


    while (1) {
        
        clock_t start = clock ();
        printf ("Role dice within 5 seconds: ");

        int input_received = 0;

        while ((clock() - start) / CLOCKS_PER_SEC < time_limit) {

            if (_kbhit()) {

                char c = getch ();

                if (c == 'y') {
                    

                    int x = rand () % 5 + 1;
                    y = y + x;

                    send (clientSocket, (char*)&y, sizeof (y), 0);


                    for (i=0; i<10; i++) {

                        for (j=0; j<10; j++) {

                            board[i][j] = snake[i][j];

                            if (y==snake[i][j]) {

                                board[i][j] = 0;
                            }


                        }
                    }

                    print (board);

                    if (y==100) {
                       w = 1;
                    }

                    if (y>100) {
                        y = y-x;
                    }

                }

                else {
                    printf("No input received on this iteration.\n");
                } 

                input_received = 1;
                send (clientSocket, (char*)&y, sizeof (y), 0);
                send (clientSocket, (char*)&life, sizeof (life), 0);
                break;

            }
          

        }

        if (!input_received) {

            // Not timely input: life lost
            printf("No input received on this iteration.\n");
            life--;
            printf ("Life is %d\n", life);

            send (clientSocket, (char*)&y, sizeof (y), 0);
            send (clientSocket, (char*)&life, sizeof (life), 0);

        }

        printf ("Next player is rolling...\n");

        int a, b;
        recv(clientSocket, (char*)&a, sizeof(a), 0);
        recv(clientSocket, (char*)&b, sizeof(b), 0);

        printf ("This player's position is %d & life is %d\n", a, b);

        printf ("Next player is rolling...\n");


        int c, d;
        recv(clientSocket, (char*)&c, sizeof(c), 0);
        recv(clientSocket, (char*)&d, sizeof(d), 0);

        printf ("This player's position is %d & life is %d\n", c, d);

        printf ("Your turn.\n");
        

        if (life == 0 || a == 100 || c == 100) {

            printf ("Game over. You lost.\n");
            break;

        }

        if (w==1 || b==0 || d==0) {

            // Finish the game
            printf ("You won.\n");
            break;

        }

        k++;
        

    }

    /*

    // Send the integers to the server
    if (send(clientSocket, (char*)numbers, sizeof(numbers), 0) == SOCKET_ERROR) {
        std::cerr << "Failed to send data to server.\n";
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Data sent to server successfully.\n";

    // Optionally, wait for the server's response (if any)

    int receivedLargestSum;
    recv(clientSocket, (char*)&receivedLargestSum, sizeof(receivedLargestSum), 0);
    cout << "Largest sum received from server: " << receivedLargestSum << "\n";

    //cout << "Client " << bytesReceived1 << " has the largest sum: " << bytesReceived2 << endl;

    */

    // Clean up
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}