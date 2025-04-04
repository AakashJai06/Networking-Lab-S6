/*
To compile and run:
1. Compile server: gcc server.c -o server
2. Run server: ./server
3. Compile client: gcc client.c -o client
4. Run client: ./client
*/

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>

int isPrime(int n); // Function declaration

int main() {
    int serversocket, clientsocket, port;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t len;
    char message[50];
    int numrecieved;

    serversocket = socket(AF_INET, SOCK_STREAM, 0);

    bzero((char*)&serveraddr, sizeof(serveraddr));

    printf("Enter the port number: ");
    scanf("%d", &port);
    
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    bind(serversocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    listen(serversocket, 5);

    len = sizeof(clientaddr);
    printf("\nWaiting for client connection...\n");

    clientsocket = accept(serversocket, (struct sockaddr*)&clientaddr, &len);
    printf("\nClient connected.\n");

    write(clientsocket, "Enter an integer:", strlen("Enter an integer:") + 1);
    read(clientsocket, &numrecieved, sizeof(numrecieved));
    printf("\nNumber received from client: %d\n", numrecieved);

    if (isPrime(numrecieved)) {
        write(clientsocket, "Number is prime", strlen("Number is prime") + 1);
    } else {
        write(clientsocket, "Number is not prime", strlen("Number is not prime") + 1);
    }

    close(clientsocket);
    close(serversocket);

    return 0;
}

int isPrime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}
