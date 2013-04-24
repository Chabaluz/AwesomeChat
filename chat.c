#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>

#define PORT "1337"
#define BACKLOG 5
#define BUZ_SIZE 4096

/* Get sockaddr, IPv4 or IPv6 */
void *get_in_addr(struct sockaddr *sa) {
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

static void grimReaper(int sig) {	/* SIGCHLD handler to read dead child processes */
	int savedErrno;

	savedErrno = errno;
	while (waitpid(-1, NULL, WNOHANG) > 0)
		continue;
	errno = savedErrno;
}
int main(void) {
	int sockfd, new_sockfd;
	struct addrinfo host_addr, *res;
	struct sockaddr_storage client_addr;	// Client's address information
	socklen_t sin_size;
	const int yes = 1;
	int recv_len = 1;
	char s[INET6_ADDRSTRLEN];
	char buffer[BUF_SIZE];

	memset(&host_addr, 0, sizeof host_addr);
	host_addr.ai_family = AF_UNSPEC;		// IPv4 and IPv6
	host_addr.ai_socktype = SOCK_STREAM;	// Stream socket
	host_addr.ai_flags = AI_PASSIVE;		// Use my IP

	getaddrinfo(NULL, PORT, &host_addr, &res);

	/* Make a socket */
	if ((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1)
		perror("in socket");
	
	/* Set socket options */
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
		perror("in setting socket options");

	/* Bind it to port 1337 */
	if (bind(sockfd, res->ai_addr, res->ai_addrlen) == -1)
		perror("in binding to socket");
	
	/* Listen */
	if (listen(sockfd, BACKLOG) == -1)
		perror("listening on socket");

	printf("Server: Waiting for connections...\n");

	while (1) {
		sin_size = sizeof client_addr;
		new_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &sin_size);
		if (new_sockfd == -1)
			perror("accepting");
		
		inet_ntop(client_addr.ss_family, get_in_addr((struct sockaddr *)&client_addr), s, sizeof s);
		printf("Got connection from %s\n", s);

		if (!fork()) {	// This is the child process
			close(sockfd);	// Child doesn't need the listener
			if (send(new_sockfd, "Hello, world!\n", 13, 0) == -1)
				perror("sending");
			recv_len = recv(new_sockfd, &buffer, 1024, 0);
			while (recv_len > 0) {
				printf("Bytes received: %d\n", recv_len);
				printf("Message received: %s\n", buffer);
				recv_len = recv(new_sockfd, &buffer, 1024, 0);
			}
			close(new_sockfd);
			exit(EXIT_SUCCESS);
		}
		close(new_sockfd);	// Parent doesn't need this
	}

	return 0;
}
