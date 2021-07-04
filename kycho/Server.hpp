/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 13:46:49 by kycho             #+#    #+#             */
/*   Updated: 2021/07/04 13:17:28 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <vector>
# include <map>
# include <string>

# include "HttpConfig.hpp"
# include "Location.hpp"

class HttpConfig;

class Server
{
//private:
public:

	std::vector<std::string>	listens;
	std::vector<std::string>	server_name;

	std::string					root;
	std::vector<std::string>	index;
	bool						autoindex;
	unsigned long long 			client_max_body_size;
	std::map<int, std::string>	error_page;
	// return_value;
	
	std::vector<Location*>		locations;

public:
	Server(void) {}
	Server(std::vector<std::string> tokens, HttpConfig* httpConfig);
	
	~Server(void)
	{
		std::cout << "~Server() 호출~~~" << std::endl;
	}

	void print_status_for_debug(void){  // TODO : remove
		std::cout << "\t";
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Server ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;	

		std::cout << "\t";
		std::cout << "listen : ";
		for (std::vector<std::string>::iterator i = this->listens.begin(); i != this->listens.end(); i++){
			std::cout << *i << "  ";
		}
		std::cout << std::endl;

		std::cout << "\t";
		std::cout << "server_name : ";
		for (std::vector<std::string>::iterator i = this->server_name.begin(); i != this->server_name.end(); i++){
			std::cout << *i << "  ";
		}
		std::cout << std::endl;
		
		std::cout << "\t";
		std::cout << "root : " << this->root << std::endl;
		
		std::cout << "\t";
		std::cout << "index : ";
		for (std::vector<std::string>::iterator i = this->index.begin(); i != this->index.end(); i++){
			std::cout << *i << " ";
		}
		std::cout << std::endl;
		
		std::cout << "\t";
		std::cout << "autoindex : " << this->autoindex << std::endl;

		std::cout << "\t";
		std::cout << "client_max_body_size : " << this->client_max_body_size << std::endl;

		std::cout << "\t";
		std::cout << "error_page : " ;
		for (std::map<int, std::string>::iterator i = this->error_page.begin(); i != this->error_page.end(); i++){
			std::cout << i->first << ":" << i->second << "  ";
		}
		std::cout << std::endl;
		std::cout << "\t";
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;	
	}

};

#endif
