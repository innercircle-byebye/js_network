#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "webserv.hpp"
#include "SocketManager.hpp"
#include "Listening.hpp"
#include "HttpConfig.hpp"
#include "RequestMessage.hpp"
#include "Logger.hpp"

class Connection {
private:
	bool				listen_;

	socket_t			fd_;
	int					type_;
	struct sockaddr_in	sockaddr_to_connect_;
	socklen_t			socklen_to_connect_;

	Listening			*listening_;

	HttpConfig			*httpconfig_;

	RequestMessage		req_msg_;
	Connection			*next_;

public:
	char				buffer_[BUF_SIZE];

	Connection();
	~Connection();

	Connection	*eventAccept(SocketManager *sv);

	void	setListen(bool listen);
	void	setNext(Connection *next);
	void	setFd(socket_t fd);
	void	setType(int type);
	void	setListening(Listening *listening);
	void	setSockaddrToConnectPort(in_port_t port);
	void	setSockaddrToConnectIP(in_addr_t ipaddr);
	void	setHttpConfig(HttpConfig *httpconfig);
	void	setRequestMessage(RequestMessage &req_msg);

	bool				getListen() const;
	Connection			*getNext() const;
	socket_t			getFd() const;
	struct sockaddr_in	getServerSockaddr() const;
	// const HttpConfig	*getHttpConfig() const;
	// const RequestMessage		&getRequestMessage() const;
	HttpConfig			*getHttpConfig();
	RequestMessage		&getRequestMessage();
	struct sockaddr_in	getSockaddrToConnect();
};


#endif
