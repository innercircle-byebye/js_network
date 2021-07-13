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
	struct sockaddr_in	client_sockaddr_;		// client의 port랑 ip
	socklen_t			client_socklen_;

	Listening			*listening_;
	struct sockaddr_in	server_sockaddr_;	// local_sockaddr.sin_port == 5000
	socklen_t			server_socklen_;

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
	void	setClientSockaddr(struct sockaddr_in *client_sockaddr, socklen_t client_socklen);
	void	setServerSockaddr(struct sockaddr_in *server_sockaddr, socklen_t server_socklen);
	void	setHttpConfig(HttpConfig *httpconfig);
	void	setRequestMessage(RequestMessage &req_msg);

	bool				getListen() const;
	Connection			*getNext() const;
	socket_t			getFd() const;
	struct sockaddr_in	getServerSockaddr() const;
	// const HttpConfig	*getHttpConfig() const;
	// const RequestMessage		&getRequestMessage() const;
	HttpConfig	*getHttpConfig();
	RequestMessage		&getRequestMessage();
};


#endif
