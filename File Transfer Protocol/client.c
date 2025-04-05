#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5035
#define MAX 60

int main() {
    int sockfd, n;
    struct sockaddr_in serv_addr;
    char filename[MAX], recvline[MAX];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(PORT);

    connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    printf("Enter the source file name: ");
    scanf("%s", filename);

    write(sockfd, filename, MAX);

    printf("File content received:\n");
    while ((n = read(sockfd, recvline, MAX)) > 0) {
        printf("%s", recvline);
    }

    close(sockfd);
    return 0;
}
