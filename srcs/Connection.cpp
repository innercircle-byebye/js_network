#include "Connection.hpp"

Connection::Connection()
: listen_(false), fd_(-1), type_(SOCK_STREAM), listening_(NULL)
{
	memset(buffer_, 0, BUF_SIZE);
}

Connection::~Connection() {}

// listen == true 일때 호출됨
Connection	*Connection::eventAccept(SocketManager *sm) {
	struct sockaddr_in	conn_sockaddr;
	socklen_t			conn_socklen;

	socket_t s = accept(fd_, (struct sockaddr *)&conn_sockaddr, &conn_socklen);

	if (s == -1) {
		Logger::logError(LOG_ALERT, "accept() failed");
		throw AcceptExcception();
	}

	Connection *c = sm->getConnection(s);

	if (c == NULL) {	// free_connection 없음
		if (closeSocket(s) == -1) {
			Logger::logError(LOG_ALERT, "close() socket failed");
			throw CloseSocketException();
		}
		throw ConnNotEnoughException();
	}
	if (nonblocking(s) == -1) {
		Logger::logError(LOG_ALERT, "fcntl(O_NONBLOCK) failed");
		sm->closeConnection(c);	// s가 close됨
		throw NonblockingException();
	}

	c->setListening(listening_);
	c->setClientSockaddr(&conn_sockaddr, conn_socklen);
	c->setServerSockaddr(&server_sockaddr_, server_socklen_);
	return c;
}

/* SETTER */
void	Connection::setListen(bool listen)
{ listen_ = listen; }

void	Connection::setNext(Connection *next)
{ next_ = next; }

void	Connection::setFd(socket_t fd)
{ fd_ = fd; }

void	Connection::setType(int type)
{ type_ = type; }

void	Connection::setListening(Listening *listening)
{ listening_ = listening; }

void	Connection::setClientSockaddr(struct sockaddr_in *client_sockaddr, socklen_t client_socklen)
{
	client_socklen_ = client_socklen;
	memcpy(&client_sockaddr_, client_sockaddr, client_socklen);
}

void	Connection::setServerSockaddr(struct sockaddr_in *server_sockaddr, socklen_t server_socklen)
{
	server_socklen_ = server_socklen;
	memcpy(&server_sockaddr_, server_sockaddr, server_socklen);
}

void	Connection::setHttpConfig(HttpConfig *httpconfig)
{ httpconfig_ = httpconfig; }

void	Connection::setRequestMessage(RequestMessage &req_msg)
{ req_msg_ = req_msg; }

/* GETTER */
bool				Connection::getListen() const
{ return listen_; }
Connection			*Connection::getNext() const
{ return next_; }
socket_t			Connection::getFd() const
{ return fd_; }
/*
const HttpConfig	*Connection::getHttpConfig() const
{ return httpconfig; }
const RequestMessage		&Connection::getRequestMessage() const
{ return req_msg; }
*/


struct sockaddr_in	Connection::getServerSockaddr() const
{ return server_sockaddr_; }

HttpConfig	*Connection::getHttpConfig()
{ return httpconfig_; }

RequestMessage		&Connection::getRequestMessage()
{ return req_msg_; }
