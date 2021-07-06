/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 13:46:49 by kycho             #+#    #+#             */
/*   Updated: 2021/07/06 20:29:36 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_CONFIG_HPP
# define SERVER_CONFIG_HPP

# include <vector>
# include <map>
# include <string>
# include <algorithm>

# include "HttpConfig.hpp"
# include "LocationConfig.hpp"

class HttpConfig;

class ServerConfig
{
//private:
public:

	std::vector<std::string>	listen;
	std::vector<std::string>	server_name;

	std::string					root;
	std::vector<std::string>	index;
	bool						autoindex;
	unsigned long 				client_max_body_size;
	std::map<int, std::string>	error_page;
	// return_value;
	
	std::vector<LocationConfig*>		location_configs;

public:
	ServerConfig(std::vector<std::string> tokens, HttpConfig* http_config);
	~ServerConfig(void);

	bool isMatchServerName(std::string request_server_name);
	LocationConfig* getLocationConfig(std::string request_uri);

	// for debug
	void print_status_for_debug(std::string prefix);  // TODO : remove

private:
	static bool compare_uri_for_descending_order_by_length(const LocationConfig* first, const LocationConfig* second);
};

#endif
