#ifndef KAMID_SOCKET_H
#define KAMID_SOCKET_H

#include "includes.h"

#define SOCKET_NAME "\0KAMID"
#define BACKLOG 8
#define PacketSize 4096

int sock;
int connected;
struct sockaddr_un addr_server;
char socket_name[108];

int Create()
{
	sock = socket(AF_UNIX, SOCK_STREAM, 0);
	return sock != -1;
}

void Close()
{
	if (connected)
	{
		connected = 0;
		close(sock);
		sock = -1;
	}
}

int Connect()
{
	memset(socket_name, 0, sizeof(socket_name));
	strcpy(&socket_name[1], SOCKET_NAME);

	memset(&addr_server, 0, sizeof(struct sockaddr_un));
	addr_server.sun_family = AF_UNIX;
	strncpy(addr_server.sun_path, socket_name, sizeof(addr_server.sun_path) - 1);

	if (connect(sock, (struct sockaddr *)&addr_server, sizeof(addr_server)) == -1)
	{
		Close();
		return 0;
	}

	connected = 1;
	return 1;
}

size_t sendData(const void *inData, size_t size)
{
	const char *buffer = static_cast < const char *>(inData);
	size_t remaining = size;

	while (remaining > 0)
	{
		ssize_t numSent = write(sock, buffer, remaining);
		if (numSent == -1)
		{
			if (errno == EINTR)
				continue;
			Close();
			return 0;
		}
		if (numSent == 0)
		{
			Close();
			return 0;
		}
		remaining -= numSent;
		buffer += numSent;
	}
	return size;
}

size_t send(void *inData, size_t size)
{
	uint32_t length = htonl(size);
	if (sendData(&length, sizeof(uint32_t)) == 0)
	{
		return 0;
	}
	return sendData(inData, size);
}

int recvData(void *outData, size_t size)
{
	char *buffer = static_cast < char *>(outData);
	size_t remaining = size;

	while (remaining > 0)
	{
		ssize_t numReceived = read(sock, buffer, remaining);
		if (numReceived == -1)
		{
			if (errno == EINTR)
				continue;
			Close();
			return 0;
		}
		if (numReceived == 0)
		{
			Close();
			return 0;
		}
		remaining -= numReceived;
		buffer += numReceived;
	}
	return size;
}

size_t receive(void *outData)
{
	uint32_t length = 0;
	if (recvData(&length, sizeof(uint32_t)) == 0)
	{
		return 0;
	}
	length = ntohl(length);
	return recvData(outData, length);
}

#endif // KAMID_SOCKET_H
