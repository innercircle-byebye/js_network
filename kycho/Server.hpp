/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 13:46:49 by kycho             #+#    #+#             */
/*   Updated: 2021/07/02 14:26:00 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <vector>
# include <map>
# include <string>

# include "HttpConfig.hpp"
# include "Location.hpp"

class Server
{
//private:
public:

	std::vector<std::string>	listens;
	std::vector<std::string>	server_name;

	std::string					root;
	std::vector<std::string>	index;
	bool						autoindex;
	int							client_max_body_size;
	std::map<int, std::string>	error_page;
	// return_value;
	
	std::vector<Location*>		locations;

public:
	Server(void) {}
	Server(std::vector<std::string> tokens)
	{
		std::cout << " \t==============server constructor==========" << std::endl;

		std::vector<std::vector<std::string> > locations_tokens;

		std::vector<std::string>::iterator it = tokens.begin();  // "server"
		it++;  // "{"
		it++;  // any directive

		while(*it != "}")
		{
			if (*it == "listen")
			{
				while (*it != ";")
				{
					std::cout << "\t[" << *it << "] " << std::endl;
					it++;
				}
				it++;
				std::cout << std::endl;
			}
			else if (*it == "server_name")
			{
				while (*it != ";")
				{
					std::cout << "\t[" << *it << "] " << std::endl;
					it++;
				}
				it++;
				std::cout << std::endl;
			}
			else if (*it == "root")
			{
				while (*it != ";")
				{
					std::cout << "\t[" << *it << "] " << std::endl;
					it++;
				}
				it++;
				std::cout << std::endl;
			}
			else if (*it == "index")
			{
				while (*it != ";")
				{
					std::cout << "\t[" << *it << "] " << std::endl;
					it++;
				}
				it++;
				std::cout << std::endl;
			}
			else if (*it == "autoindex")
			{
				while (*it != ";")
				{
					std::cout << "\t[" << *it << "] " << std::endl;
					it++;
				}
				it++;
				std::cout << std::endl;
			}
			else if (*it == "error_page")
			{
				while (*it != ";")
				{
					std::cout << "\t[" << *it << "] " << std::endl;
					it++;
				}
				it++;
				std::cout << std::endl;
			}
			else if (*it == "client_max_body_size")
			{
				while (*it != ";")
				{
					std::cout << "\t[" << *it << "] " << std::endl;
					it++;
				}
				it++;
				std::cout << std::endl;
			}
			else if (*it == "location")
			{
				std::vector<std::string> location_tokekns;

				location_tokekns.push_back(*it);
				it++;
				location_tokekns.push_back(*it);
				it++;
				location_tokekns.push_back(*it);
				it++;

				int cnt = 1;
				while (cnt != 0){
					if (*it == "{") cnt++;
					else if (*it == "}") cnt--;
					location_tokekns.push_back(*it);
					it++;
				}
				locations_tokens.push_back(location_tokekns);
				
			}
			else
			{

				std::cout << "\t~~ 이상한거 들어옴!!!! ~~" << std::endl;
				while (*it != ";")
				{
					std::cout << "\t[" << *it << "] " << std::endl;
					it++;
				}
				it++;
				std::cout << std::endl;
			}
		}

		
		std::vector<std::vector<std::string> >::iterator location_it = locations_tokens.begin();
		for (; location_it != locations_tokens.end(); location_it++){
			
			Location *new_location = new Location(*location_it);
		}

		
		
	}
	~Server(void) {
		std::cout << "~Server() 호출~~~" << std::endl;
	}

};

#endif
