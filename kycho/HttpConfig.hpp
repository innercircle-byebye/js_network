/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpConfig.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 13:47:53 by kycho             #+#    #+#             */
/*   Updated: 2021/07/03 04:37:45 by kycho            ###   ########.fr       */
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

# include <iostream>

# include "Server.hpp"
# include "Location.hpp"
# include "Tokenizer.hpp"

class Server;

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
	//HttpConfig(const HttpConfig& HttpConfig);
	
	~HttpConfig() {
		std::cout << "~HttpConfig() 호출~~~" << std::endl;
	}
	
	//HttpConfig& operator=(const HttpConfig& other);

	std::multimap<in_port_t, in_addr_t>	getMustListens(void)
	{
		return must_listens;
	}

	Location* getLocationConfig(in_port_t port, in_addr_t ip_addr, std::string server_name, std::string uri_path);



	void print_status_for_debug(void){  // TODO : remove
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ HttpConfig ~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;	
		
		std::cout << "root : " << this->root << std::endl;
		
		std::cout << "index : ";
		for (std::vector<std::string>::iterator i = this->index.begin(); i != this->index.end(); i++){
			std::cout << *i << " ";
		}
		std::cout << std::endl;
		
		std::cout << "autoindex : " << this->autoindex << std::endl;

		std::cout << "client_max_body_size : " << this->client_max_body_size << std::endl;

		std::cout << "error_page : " ;
		for (std::map<int, std::string>::iterator i = this->error_page.begin(); i != this->error_page.end(); i++){
			std::cout << i->first << ":" << i->second << "  ";
		}
		std::cout << std::endl;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;	
	}
};

#endif
