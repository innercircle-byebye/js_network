/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpConfig.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 13:47:53 by kycho             #+#    #+#             */
/*   Updated: 2021/07/06 09:27:52 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_CONFIG_HPP
# define HTTP_CONFIG_HPP

# include <vector>
# include <map>
# include <string>
# include <arpa/inet.h>
# include <fstream>
# include <stdexcept>
# include <cstdlib>
# include <cstring>

# include <iostream>

# include "Server.hpp"
# include "Location.hpp"
# include "Tokenizer.hpp"

class Server;
class Location;

class HttpConfig
{
//private:
public:
	std::multimap<in_port_t, in_addr_t>			must_listens;
	
	std::string									root;
	std::vector<std::string>					index;
	bool										autoindex;
	unsigned long long 							client_max_body_size;
	std::map<int, std::string>					error_page;

	std::map<in_port_t, std::map<in_addr_t, std::vector<Server*> > > server;

public:
	HttpConfig(void);
	HttpConfig(std::string configFilePath);
	~HttpConfig();

	std::multimap<in_port_t, in_addr_t>	getMustListens(void);
	Server* getServerConfig(in_port_t port, in_addr_t ip_addr, std::string server_name);
	Location* getLocationConfig(in_port_t port, in_addr_t ip_addr, std::string server_name, std::string request_uri);


	// for debug
	void print_all_server_location_for_debug(void);  // TODO : remove
	void print_status_for_debug(std::string prefix);  // TODO : remove
};

#endif
