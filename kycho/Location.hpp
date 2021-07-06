/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 13:48:51 by kycho             #+#    #+#             */
/*   Updated: 2021/07/06 15:10:02 by kycho            ###   ########.fr       */
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
	unsigned long				client_max_body_size;
	//return
	// limit_except

public:
	Location(void);
	Location(std::vector<std::string> tokens, Server* server);
	~Location(void);

	bool isPrefixMatchUri(std::string request_uri);

	// for debug
	void print_status_for_debug(std::string prefix);  // TODO : remove
};

#endif
