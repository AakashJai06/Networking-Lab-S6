#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5035
#define MAX 60

int main() {
    int sockfd, newsockfd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;
    char filename[MAX], buffer[4096];
    FILE *file;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(sockfd, 5);

    printf("Server listening on port %d...\n", PORT);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen);

    read(newsockfd, filename, MAX);
    printf("Requested file: %s\n", filename);

    file = fopen(filename, "r");
    if (!file) {
        perror("File open failed");
        close(newsockfd);
        close(sockfd);
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        write(newsockfd, buffer, MAX);
    }

    fclose(file);
    close(newsockfd);
    close(sockfd);
    printf("File sent successfully.\n");
    return 0;
}
