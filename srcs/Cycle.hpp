#ifndef CYCLE_HPP
#define CYCLE_HPP

#include "webserv.hpp"
#include "SocketManager.hpp"
#include "Kqueue.hpp"
#include "HttpConfig.hpp"

class Cycle {
private:
	Kqueue			*kq_;
	SocketManager	*sm_;

public:
	Cycle(HttpConfig *httpconfig);
	~Cycle();

	void	webservCycle();
};

#endif
