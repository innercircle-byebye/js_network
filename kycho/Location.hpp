/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 13:48:51 by kycho             #+#    #+#             */
/*   Updated: 2021/07/02 22:41:25 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
# define LOCATION_HPP

# include <vector>
# include <map>
# include <string>

# include "Server.hpp"
# include "Location.hpp"

class Location
{
//private:
public:
	std::string					uri_path;
	
	std::string					root;
	std::vector<std::string>	index;
	bool						autoindex;
	std::map<int, std::string>	error_page;
	int							client_max_body_size;
	//return
	// limit_except
public:
	Location(void) {}
	Location(std::vector<std::string> tokens)
	{
		std::cout << " \t\t~~~~~~~~~~location constructor~~~~~~~~~~~~" << std::endl;

		for(std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); it++){
			std::cout << "\t\t" << *it << std::endl;
		}

		
	}
	
	~Location(void) {}

};

#endif
