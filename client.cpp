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


int se1 [4] = {36, 48, 54, 57};
int se2 [4] = {93, 88, 67, 66};
int se3 [4] = {60, 51, 40, 41};

int e1 = 20, e2 = 40, e3 = 30;


int ladder1 [4] = {30, 70, 96, 92};
int ladder2 [4] = {87, 84, 71, 70};
int ladder3 [4] = {55, 18, 80, 81};

int l1 = 6, l2 = 21, l3 = 27;



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


void printTheEnd () {
    

    printf ("\n");

    printf ("####  ##    #  ##\n");
    printf ("#     # #   #  # #\n");
    printf ("###   #  #  #  #  #\n");
    printf ("#     #   # #  # #\n");
    printf ("####  #    ##  ##\n");

    printf ("\n");


}


void logo () {
    
    printf ("\n-----------------------------------------\n");

    printf ("***       ***   ***  ***        *********\n");
    printf ("***       ***   ***  ******     *********\n");
    printf ("***       ***   ***  *** ****   ***   ***\n");
    printf ("***       ***   ***  ***   **   ***   ***\n");
    printf ("***       ***   ***  ***   **   ***   ***\n");
    printf ("***       ***   ***  *** ****   ***   ***\n");
    printf ("********  *********  ******     *********\n");
    printf ("********  *********  ***        *********\n");

    printf ("\n");

    printf ("-----------------------------------------\n\n");
}



int main() {

    printf ("Welcome!\n");

    logo ();


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


    printf ("Welcome!\n");

    printf ("Please enter your name: ");

    
    const char* name;
    scanf ("%s", name);

    send(clientSocket, name, strlen(name) + 1, 0);


    // preparing to get the names of other players
    // get the 2nd

    char receivedName[256];

    int bytesReceived = recv(clientSocket, receivedName, sizeof(receivedName), 0);

    if (bytesReceived > 0) {

        receivedName[bytesReceived] = '\0';  // Null-terminate the string
        
    }


    // get the 3rd

    char receivedName1[256];

    int bytesReceived1 = recv(clientSocket, receivedName1, sizeof(receivedName1), 0);

    if (bytesReceived1 > 0) {

        receivedName1[bytesReceived1] = '\0';  // Null-terminate the string
        
    }

    
    // get the 4th

    char receivedName2[256];

    int bytesReceived2 = recv(clientSocket, receivedName2, sizeof(receivedName2), 0);

    if (bytesReceived2 > 0) {

        receivedName2[bytesReceived2] = '\0';  // Null-terminate the string
        
    }



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
                    int a = rand() % 3 + 1;
                    int b = rand() % 3 +1;
                    int c = rand() % 3 +1;

                    int a1 = rand() % 3 +1;
                    int b1 = rand() % 3 +1;
                    int c1 = rand() % 3 +1;

                    int point_lose = rand () % 95 + 1;

                    int point_gain = rand () % 95 + 1;

                    cout<<"Snakes are between "<<se1[a]<<" & "<<e1<<", "<<se2[b]<<" & "<<e2<<" and "<<se3[c]<<" & "<<e3<<endl;

                    cout<<"Ladders are between "<<l1<<" & "<<ladder1[a1]<<", "<<l2<<" & "<<ladder2[b1]<<" and "<<l3<<" & "<<ladder3[c1]<<endl;

                    cout << "Life will lose at " << point_lose << endl;

                    cout <<"Life will gain at " << point_gain << endl;


                    for (i=0; i<10; i++) {
                        for (j=0; j<10; j++) {
                            board[i][j] = snake[i][j];
                            
                            // When snake/ladder comes on the way
                            if (y==se1[a]) {
                                if (snake[i][j] == e1) {
                                    board[i][j] = 0;
                                    y = e1;
                                }
                            }

                            if (y==se2[b]) {
                                if (snake[i][j] == e2) {
                                    board[i][j] = 0;
                                    y = e2;
                                }
                            }

                            if (y==se3[c]) {
                                if (snake[i][j] == e3) {
                                    board[i][j] = 0;
                                    y = e3;
                                }
                            }
                            
                            if (y==l1) {
                                if (snake[i][j] == ladder1[a1]) {
                                    board[i][j] = 0;
                                    y = ladder1[a1];
                                }
                            }
                            
                            if (y==l2) {
                                if (snake[i][j] == ladder2[b1]) {
                                    board[i][j] = 0;
                                    y = ladder2[b1];
                                }
                            }
                            
                            if (y==l3) {
                                if (snake[i][j] == ladder3[c1]) {
                                    board[i][j] = 0;
                                    y = ladder3[c1];
                                }
                            }

                            // When they don't
                            else if (y==snake[i][j]) {
                                board[i][j] = 0;
                            }

                            if (y==point_lose) {
                                life--;
                            }

                            if (y==point_gain) {
                                life++;
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
            printf ("Life is %d\n-\n", life);

            send (clientSocket, (char*)&y, sizeof (y), 0);
            send (clientSocket, (char*)&life, sizeof (life), 0);

        }

        printf ("Position is %d, life is %d\nNext player is rolling...\n", y, life);

        int a, b;
        recv(clientSocket, (char*)&a, sizeof(a), 0);
        recv(clientSocket, (char*)&b, sizeof(b), 0);

        // cout << "Next player's position is " << a << " & life is " << b << "\n-\n";

        printf ("Next player is rolling...\n");


        int c, d;
        recv(clientSocket, (char*)&c, sizeof(c), 0);
        recv(clientSocket, (char*)&d, sizeof(d), 0);

        // cout << "Next player's position is " << c << " & life is " << d << "\n-\n";

        printf ("Next player is rolling...\n");

        int e, f;
        recv(clientSocket, (char*)&e, sizeof(e), 0);
        recv(clientSocket, (char*)&f, sizeof(f), 0);


        // cout << "Next player's position is " << e << " & life is " << e << "\n-\n";

        printf ("\nYour turn.\n");
        

        if (life == 0 || a == 100 || c == 100 || e == 100) {

            printf ("Game over. You lost.\n");
            break;

        }

        if (w==1 || b==0 || d==0 || f==0) {

            // Finish the game
            printf ("You won.\n");
            break;

        }

        k++;
        

    }
    

    // Clean up

    printf ("Close the server terminal after the game is over.\n");
    

    printTheEnd ();

    closesocket(clientSocket);
    WSACleanup();

    return 0;

}