/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 13:48:51 by kycho             #+#    #+#             */
/*   Updated: 2021/07/04 13:17:21 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
# define LOCATION_HPP

# include <vector>
# include <map>
# include <string>

# include "Server.hpp"
# include "Location.hpp"

class Server;

class Location
{
//private:
public:
	std::string					uri_path;
	
	std::string					root;
	std::vector<std::string>	index;
	bool						autoindex;
	std::map<int, std::string>	error_page;
	unsigned long long			client_max_body_size;
	//return
	// limit_except
public:
	Location(void) {}
	Location(std::vector<std::string> tokens, Server* server);
	
	~Location(void)
	{
		std::cout << "~Location() 호출~~~" << std::endl;
	}

	void print_status_for_debug(void){  // TODO : remove
		std::cout << "\t\t";
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Location ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;	

		std::cout << "\t\t";		
		std::cout << "uri_path : " << this->uri_path << std::endl;

		std::cout << "\t\t";		
		std::cout << "root : " << this->root << std::endl;

		std::cout << "\t\t";		
		std::cout << "index : ";
		for (std::vector<std::string>::iterator i = this->index.begin(); i != this->index.end(); i++){
			std::cout << *i << " ";
		}
		std::cout << std::endl;

		std::cout << "\t\t";		
		std::cout << "autoindex : " << this->autoindex << std::endl;

		std::cout << "\t\t";
		std::cout << "client_max_body_size : " << this->client_max_body_size << std::endl;

		std::cout << "\t\t";
		std::cout << "error_page : " ;
		for (std::map<int, std::string>::iterator i = this->error_page.begin(); i != this->error_page.end(); i++){
			std::cout << i->first << ":" << i->second << "  ";
		}
		std::cout << std::endl;
		std::cout << "\t\t";
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;	
	}

};

#endif
