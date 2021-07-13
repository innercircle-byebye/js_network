#ifndef SOCKETMANAGER_HPP
#define SOCKETMANAGER_HPP

#include "webserv.hpp"
#include "Listening.hpp"
#include "Connection.hpp"
#include "Logger.hpp"
#include "HttpConfig.hpp"

class SocketManager {
private:
	std::vector<Listening*>		listening_;

	Connection	*connections_;
	size_t		connection_n_;
	Connection	*free_connections_;
	size_t		free_connection_n_;

	void		openListeningSockets();
	void		closeListeningSockets();

public:
	SocketManager(HttpConfig *httpconfig);
	~SocketManager();

	Connection*	getConnection(socket_t s);
	void		freeConnection(Connection *c);
	void		closeConnection(Connection *c);

	const std::vector<Listening*>	&getListening() const;
	size_t		getListeningSize() const;
};

#endif
