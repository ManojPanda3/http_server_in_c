#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

// the max input data size is 1kb
#define BUFFER_SIZE 2024

int main() {
  int server_socket, socket_buff;
  char buffer[BUFFER_SIZE] = "";
  struct sockaddr_in address;
  unsigned long address_len;
  if (0 == (server_socket = socket(AF_INET, SOCK_STREAM, 0))) {
    fprintf(stderr, "Error while creating a socket\n");
    return EXIT_FAILURE;
  }
  address.sin_port = htons(PORT);
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address_len = sizeof(address);

  if (0 >
      bind(server_socket, (const struct sockaddr *)&address, sizeof(address))) {
    fprintf(stderr, "Error while binding the socket\n");
    return EXIT_FAILURE;
  }

  if (0 > listen(server_socket, 3)) {
    fprintf(stderr, "Error while listeing the socket\n");
    return EXIT_FAILURE;
  }
  fprintf(stdout, "server successfully listeing in the port %d", PORT);
  char isRunning = 1;
  char socket_reader;
  while (isRunning) {
    if (0 > (socket_buff = accept(server_socket, (struct sockaddr *)&address,
                                  (socklen_t *)&address_len))) {
      fprintf(stderr, "Error while accepting the request\n");
      return EXIT_FAILURE;
    }

    if (0 > (socket_reader = read(socket_buff, buffer, BUFFER_SIZE - 1))) {
      fprintf(stderr, "Error while reading the socket buffer\n");
      return EXIT_FAILURE;
    }
    if (0 == socket_reader) {
      fprintf(stderr, "Error client close the connection\n");
      return EXIT_FAILURE;
    }
    printf("Buffer: %s\n", buffer);
    char response[] = "HelloWorld\n\0";
    int bytesended;
    if (-1 == (bytesended = write(socket_buff, response, strlen(response)))) {
      fprintf(stderr, "Error while sending data to the client\n");
    } else {
      printf("Response sended:\n%d\n", bytesended);
    }
  }
  close(socket_buff);
  close(server_socket);
  return EXIT_SUCCESS;
}
