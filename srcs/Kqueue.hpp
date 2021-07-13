#ifndef KQUEUE_HPP
#define KQUEUE_HPP

#include "webserv.hpp"
#include "SocketManager.hpp"
#include "Connection.hpp"
#include "EventHandler.hpp"

class Kqueue {
private:
	int				kq_, max_changes_, nchanges_, nevents_;
	struct kevent	*change_list_;
	struct kevent	*event_list_;
	struct timespec	ts_;

public:
	Kqueue();
	~Kqueue();

	void	kqueueSetEvent(Connection *c, u_short filter, u_int flags);
	void	kqueueProcessEvents(SocketManager *sm);
};

#endif
