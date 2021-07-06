/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 13:46:49 by kycho             #+#    #+#             */
/*   Updated: 2021/07/06 15:12:44 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <vector>
# include <map>
# include <string>
# include <algorithm>

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
	unsigned long 				client_max_body_size;
	std::map<int, std::string>	error_page;
	// return_value;
	
	std::vector<Location*>		locations;

public:
	Server(void);
	Server(std::vector<std::string> tokens, HttpConfig* httpConfig);
	~Server(void);

	bool isMatchServerName(std::string server_name_str);
	Location* getLocationConfig(std::string request_uri);

	// for debug
	void print_status_for_debug(std::string prefix);  // TODO : remove

private:
	
	static bool compare_uri_for_descending_order_by_length(const Location* first, const Location* second);
};

#endif
