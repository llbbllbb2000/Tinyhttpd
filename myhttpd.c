/*  
    Only for GET method
*/
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 4000

void not_found(int client)
{
    char buf[1024];

    sprintf(buf, "HTTP/1.0 404 NOT FOUND\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "Server: httpd/0.1.0\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<HTML><TITLE>Not Found</TITLE>\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<BODY><P>The server could not fulfill\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "your request because the resource specified\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "is unavailable or nonexistent.\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "</BODY></HTML>\r\n");
    send(client, buf, strlen(buf), 0);
}

void unimplemented(int client)
{
    char buf[1024];

    sprintf(buf, "HTTP/1.0 501 Method Not Implemented\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "Server: myhttpd/0.1.0\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<HTML><HEAD><TITLE>Method Not Implemented\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "</TITLE></HEAD>\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<BODY><P>HTTP request method not supported.\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "</BODY></HTML>\r\n");
    send(client, buf, strlen(buf), 0);
}

int main()
{
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    // printf("serv_sock: %d\n", serv_sock);

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
        printf("error binding!\n");
        return -1;
    }

    listen(serv_sock, 10);
    printf("myhttpd is running on port %d\n", PORT);

    int client_sock;
    struct sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);

    char buf[1024];//, file[1024];

    while (1)
    {
        client_sock = accept(serv_sock, (struct sockaddr*) &client_addr, &client_addr_size);

        read(client_sock, buf, sizeof(buf));
        printf("%s", buf);
        // printf("client_sock: %d\n", client_sock);

        // char method[16], url[256], version[16];
        // FILE* fp = fdopen(client_sock, "r");
        // if (!fp) {
        //     not_found(client_sock);
        //     printf("not found\n");
        //     return -1;
        // }

        // if ( fgets(buf, sizeof(buf), fp) == NULL) {
        //     not_found(client_sock);
        //     printf("error read\n");
        //     return -1;
        // }
        // fclose(fp);
        // // printf("%s\n", buf);
        
        // if ( sscanf(buf, "%s %s %s\n", method, url, version) == EOF) {
        //     not_found(client_sock);
        //     printf("error read 2\n");
        //     return -1;
        // }

        // if (strcasecmp(method, "GET") != 0) {
        //     unimplemented(client_sock);
        //     printf("unimplemented method\n");
        //     return -1;
        // }

        // int num = strlen(url);
        // if (url[num - 1] == '/') {
        //     strcat(url, "index.html");
        // }
        // sprintf(file, "htdocs%s", url);
        // // printf("%s\n", file);

        // sprintf(buf, "HTTP/1.0 200 OK\r\n");
        // printf("%s", buf);
        // send(client_sock, buf, strlen(buf), 0);
        // sprintf(buf, "Server: myhttpd/0.1.0\r\n");
        // printf("%s", buf);
        // send(client_sock, buf, strlen(buf), 0);
        // sprintf(buf, "Content-Type: text/html\r\n");
        // printf("%s", buf);
        // send(client_sock, buf, strlen(buf), 0);
        // sprintf(buf, "\r\n");
        // printf("%s", buf);
        // send(client_sock, buf, strlen(buf), 0);
        // printf("----");

        // FILE* resource = fopen(url, "r");
        // printf("----");
        // while ( fgets(buf, sizeof(buf), resource) != NULL) {
        //     printf("%s\n", buf);
        //     send(client_sock, buf, strlen(buf), 0);
        // }

        close(client_sock);
        // fclose(resource);
    }

    close(serv_sock);

    return 0;
}