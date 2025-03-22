#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>

#define PORT 8888
#define MAX_ITERATIONS 10

void handle_client(SOCKET client_socket1, SOCKET client_socket2) {
    fd_set read_fds;
    struct timeval timeout;
    int max_socket, activity;
    int server_data = 0, client_data1, client_data2;

    for (int step = 0; step < MAX_ITERATIONS; step++) {
        printf("Iteration %d\n", step + 1);

        // Set up the file descriptor set
        FD_ZERO(&read_fds);
        FD_SET(client_socket1, &read_fds);
        max_socket = client_socket1;

        if (client_socket2 != INVALID_SOCKET) {
            FD_SET(client_socket2, &read_fds);
            if (client_socket2 > max_socket) max_socket = client_socket2;
        }

        // Set timeout to 5 seconds
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

        // Wait for activity on the sockets
        activity = select(max_socket + 1, &read_fds, NULL, NULL, &timeout);
        if (activity == 0) {
            printf("Timeout! Moving to the next step.\n");
            continue; // Skip to the next iteration
        } else if (activity < 0) {
            perror("select error");
            break; // Exit on error
        }

        // Check if client 1 is ready
        if (FD_ISSET(client_socket1, &read_fds)) {
            recv(client_socket1, (char*)&client_data1, sizeof(client_data1), 0);
            printf("Received from client 1: %d\n", client_data1);

            // Send data to both clients
            server_data++;
            send(client_socket1, (char*)&server_data, sizeof(server_data), 0);
            if (client_socket2 != INVALID_SOCKET)
                send(client_socket2, (char*)&client_data1, sizeof(client_data1), 0);
        }

        // Check if client 2 is ready
        if (client_socket2 != INVALID_SOCKET && FD_ISSET(client_socket2, &read_fds)) {
            recv(client_socket2, (char*)&client_data2, sizeof(client_data2), 0);
            printf("Received from client 2: %d\n", client_data2);

            // Send data to both clients
            server_data++;
            send(client_socket2, (char*)&server_data, sizeof(server_data), 0);
            send(client_socket1, (char*)&client_data2, sizeof(client_data2), 0);
        }
    }
}

int main() {
    WSADATA wsaData;
    SOCKET server_socket, client_socket1 = INVALID_SOCKET, client_socket2 = INVALID_SOCKET;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_len = sizeof(client_addr);

    WSAStartup(MAKEWORD(2, 2), &wsaData);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_socket, 2);

    printf("Waiting for client connections...\n");

    // Accept first client
    client_socket1 = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
    printf("First client connected.\n");

    // Optionally accept second client
    fd_set read_fds;
    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;

    FD_ZERO(&read_fds);
    FD_SET(server_socket, &read_fds);

    if (select(0, &read_fds, NULL, NULL, &timeout) > 0) {
        client_socket2 = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
        printf("Second client connected.\n");
    }

    // Handle communication
    handle_client(client_socket1, client_socket2);

    // Clean up
    closesocket(client_socket1);
    closesocket(client_socket2);
    closesocket(server_socket);
    WSACleanup();

    return 0;
}