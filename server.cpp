#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <winsock2.h>
#include <windows.h>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <chrono>

#define MAX_CLIENTS 4
#define PORT 8080

#pragma comment(lib, "ws2_32.lib")

using namespace std;



int k = 0, x, y, a, b, c, e, f;
int board[10][10], snake[10][10], i, j, w=0, q=0, p=0, d=0;

int se1 [4] = {36, 48, 54, 57};
int se2 [4] = {93, 88, 67, 66};
int se3 [4] = {60, 51, 40, 41};

int e1 = 20, e2 = 40, e3 = 30;


int ladder1 [4] = {30, 70, 96, 92};
int ladder2 [4] = {87, 84, 71, 70};
int ladder3 [4] = {55, 18, 80, 81};

int l1 = 6, l2 = 21, l3 = 27;


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

    printf ("####  ##    #  ##");
    printf ("#     # #   #  # #");
    printf ("###   #  #  #  #  #");
    printf ("#     #   # #  # #");
    printf ("####  #    ##  ##");

    printf ("\n");


}

struct ClientData {
 int sum;
 int id;
};


int multiplayer () {

 WSADATA wsa;
 SOCKET server, client[MAX_CLIENTS];
 SOCKADDR_IN serverAddr, clientAddr;
 int clientSize = sizeof (clientAddr);
 ClientData clientData [MAX_CLIENTS];
 int clientNum = 0;

 if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        cerr << "Winsock initialization failed.\n";
        return 1;
 }    
 
 server = socket(AF_INET, SOCK_STREAM, 0);
 
 if (server == INVALID_SOCKET) {
        cerr << "Failed to create socket.\n";
        WSACleanup();
        return 1;
 }

 // Setup server address
 serverAddr.sin_family = AF_INET;
 serverAddr.sin_addr.s_addr = INADDR_ANY;
 serverAddr.sin_port = htons(PORT);

 if (bind(server, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cerr << "Bind failed.\n";
        closesocket(server);
        WSACleanup();
        return 1;
 }
 
 // Listen for connections
 if (listen(server, MAX_CLIENTS) == SOCKET_ERROR) {
        cerr << "Listen failed.\n";
        closesocket(server);
        WSACleanup();
        return 1;
 }

 cout << "Server is running on port: " << PORT << endl;

// this part is about setting up the connections with clients.
 

        while (clientNum < MAX_CLIENTS) {
               cout << "Waiting for client connection...\n";
               client[clientNum] = accept(server, (SOCKADDR*)&clientAddr, &clientSize);
               if (client[clientNum] == INVALID_SOCKET) {
                  cerr << "Client connection failed.\n";
                  continue;
               }

        

               cout << "Client connected. ID: " << clientNum + 1 << "\n";

               clientNum ++;
        }    


        // getting the 1st player's name

        char receivedName[256];
    
        int bytesReceived = recv(client[0], receivedName, sizeof(receivedName), 0);
    
        if (bytesReceived > 0) {
    
            receivedName[bytesReceived] = '\0';  // Null-terminate the string
            
        }

        // sending to other three

        send(client[1], receivedName, strlen(receivedName) + 1, 0);
        send(client[2], receivedName, strlen(receivedName) + 1, 0);
        send(client[3], receivedName, strlen(receivedName) + 1, 0);





        // getting the 2nd player's name

        char receivedName1[256];
    
        int bytesReceived1 = recv(client[1], receivedName1, sizeof(receivedName1), 0);
    
        if (bytesReceived1 > 0) {
    
            receivedName1[bytesReceived1] = '\0';  // Null-terminate the string
            
        }

        // sending to other three

        send(client[0], receivedName, strlen(receivedName) + 1, 0);
        send(client[2], receivedName, strlen(receivedName) + 1, 0);
        send(client[3], receivedName, strlen(receivedName) + 1, 0);




        // getting the 3rd player's name

        char receivedName2[256];
    
        int bytesReceived2 = recv(client[2], receivedName2, sizeof(receivedName2), 0);
    
        if (bytesReceived2 > 0) {
    
            receivedName2[bytesReceived2] = '\0';  // Null-terminate the string
            
        }

        // sending to other three

        send(client[0], receivedName, strlen(receivedName) + 1, 0);
        send(client[1], receivedName, strlen(receivedName) + 1, 0);
        send(client[3], receivedName, strlen(receivedName) + 1, 0);




        // getting the last player's name

        char receivedName3[256];
    
        int bytesReceived3 = recv(client[3], receivedName3, sizeof(receivedName3), 0);
    
        if (bytesReceived3 > 0) {
    
            receivedName3[bytesReceived3] = '\0';  // Null-terminate the string
            
        }

        // sending to other three

        send(client[0], receivedName, strlen(receivedName) + 1, 0);
        send(client[1], receivedName, strlen(receivedName) + 1, 0);
        send(client[2], receivedName, strlen(receivedName) + 1, 0);




 while (1) {


        int numbers[2];
        
        recv(client[0], (char*)&numbers[0], sizeof(numbers[0]), 0);
        recv(client[0], (char*)&numbers[1], sizeof(numbers[1]), 0);

            x = numbers [0];
            y = numbers [1];
                
            send(client[1], (char*)&x, sizeof(x), 0);
            send(client[1], (char*)&y, sizeof(y), 0);

            send(client[2], (char*)&x, sizeof(x), 0);
            send(client[2], (char*)&y, sizeof(y), 0);
            
            send(client[3], (char*)&x, sizeof(x), 0);
            send(client[3], (char*)&y, sizeof(y), 0);


        recv(client[1], (char*)&numbers[0], sizeof(numbers[0]), 0);
        recv(client[1], (char*)&numbers[1], sizeof(numbers[1]), 0);

            a = numbers [0];
            b = numbers [1];
                
            send(client[0], (char*)&a, sizeof(a), 0);
            send(client[0], (char*)&b, sizeof(b), 0);

            send(client[2], (char*)&a, sizeof(a), 0);
            send(client[2], (char*)&b, sizeof(b), 0);

            send(client[3], (char*)&a, sizeof(a), 0);
            send(client[3], (char*)&b, sizeof(b), 0);

        recv(client[2], (char*)&numbers[0], sizeof(numbers[0]), 0);
        recv(client[2], (char*)&numbers[1], sizeof(numbers[1]), 0);

            c = numbers [0];
            d = numbers [1];
                
            send(client[0], (char*)&c, sizeof(c), 0);
            send(client[0], (char*)&d, sizeof(d), 0);

            send(client[1], (char*)&c, sizeof(c), 0);
            send(client[1], (char*)&d, sizeof(d), 0);

            send(client[3], (char*)&c, sizeof(c), 0);
            send(client[3], (char*)&d, sizeof(d), 0);

            
        recv(client[3], (char*)&numbers[0], sizeof(numbers[0]), 0);
        recv(client[3], (char*)&numbers[1], sizeof(numbers[1]), 0);

        e = numbers [0];
        f = numbers [1];

        
                
        send(client[0], (char*)&e, sizeof(e), 0);
        send(client[0], (char*)&f, sizeof(f), 0);

        send(client[1], (char*)&e, sizeof(e), 0);
        send(client[1], (char*)&f, sizeof(f), 0);

        send(client[2], (char*)&e, sizeof(e), 0);
        send(client[2], (char*)&f, sizeof(f), 0);


        if (x == 100 || a == 100 || c == 100 || e == 100) {
 
            closesocket(server);          

            closesocket (client [0]);

            closesocket (client [1]);

            closesocket (client [2]);

            closesocket (client [3]);


            break;

        }

        // if one client quits

        if (y==0) {

            closesocket(client[0]);
        }

        // if second client quits

        if (b==0) {

            closesocket(client[1]);
        }

        // if another client quits

        if (d==0) {

            closesocket(client[2]);
        }

        // if another client quits

        if (f==0) {

            closesocket(client[3]);
        }



        if (y==0 && b==0 && d==0 && f==0) {

            closesocket(server);

            closesocket (client [0]);

            closesocket (client [1]);

            closesocket (client [2]);
            
            closesocket (client [3]);
            


            break;

        }



     k++;
   }


 closesocket(server); 

 closesocket (client [0]);

 closesocket (client [1]);

 closesocket (client [2]);
            
 closesocket (client [3]);
 

 WSACleanup();

 return 0;
}




int single () {


    printf ("Welcome to the game!\n");

    logo ();

    for (i=10-1; i>=0; i--) {
        for (j=10-1; j>=0; j--) {
            snake[i][j] = i*10 + (j+1);
        }
    }

    int y = 1;
    int life = 10;

    int k=0;
    int time_limit = 10; // Time limit in seconds

    char name[10];
    scanf (" %s", name);

    while (1) {

        int m, n, o;
        int m1, n1, o1;

        clock_t start_time = clock();

        printf("-\nRole %d: Please role dice within %d seconds...\n", k + 1, time_limit);

        int input_received = 0; // Flag to check if input is received

        while ((clock() - start_time) / CLOCKS_PER_SEC < time_limit) {

            if (_kbhit()) { // Check if a key has been pressed

                char c = getch(); // Capture the key press
                printf("%s entered: '%c'\n", name, c);

                if (c=='y') {
                    int x = rand() % 5 + 1;
                    y = y+x;

                    printf ("Dice roled: %d\n", x);

                    // Random numbers as snake or ladder
                    int a = rand() % 3 + 1;
                    int b = rand() % 3 +1;
                    int c = rand() % 3 +1;

                    int a1 = rand() % 3 +1;
                    int b1 = rand() % 3 +1;
                    int c1 = rand() % 3 +1;


                    for (i=0; i<10; i++) {
                        for (j=0; j<10; j++) {
                            board[i][j] = snake[i][j];
                            
                            
                            // When snake comes on the way
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

                            // When ladder comes on the way

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
                        }
                    }

                    print (board);
                    
                    // Check when the game's ending
                    if (y==100) {
                        w=1;
                    }
                    
                    // If the dice count goes out of 100 without the game finishing
                    if (y>100) {
                        y = y-x;
                    }
                    
                }
                else {
                    printf ("Try again.\n");
                }
                input_received = 1;
                break; // Exit the loop if a key is pressed

            }

        }

        if (!input_received) {

            // Not timely input: life lost
            printf("No input received on this iteration.\n");
            life--;
            printf ("Life is %d\n", life);

        }

        if (life==0) {

            // Disqualified
            printf ("Game over.\n");
            break;

        }

        if (w==1) {

            // Finish the game
            printf ("%s won.\n", name);
            break;

        }
        k++;

    }

    printTheEnd ();
    

    return 0;

}



int main () {

    int choice;

    printf ("Choose the type of game: 1) single-player 2) multiplayer\nClick: 1 or 2\n");

    scanf ("%d", &choice);

    if (choice == 1) {

        single ();

    }

    else if (choice == 2) {

        multiplayer ();

    }

    else {
        printf ("Sorry, try again.\n");
    }

    return 0;

}