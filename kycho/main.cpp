/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 03:33:46 by kycho             #+#    #+#             */
/*   Updated: 2021/07/03 06:39:14 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "HttpConfig.hpp"

int main(int argc, char *argv[])
{
	/*
	HttpConfig config;

	std::multimap<in_port_t, in_addr_t> map = config.getMustListens();

	std::multimap<in_port_t, in_addr_t>::iterator it = map.begin();
	for (; it != map.end(); ++it)
		std::cout << it->first << " " << it->second << std::endl;

	Location* loc = config.getLocationConfig(8080, inet_addr("127.0.0.1"), "somename", "/");

	std::cout << loc->autoindex << std::endl;
	std::cout << loc->root << std::endl;
	*/

	HttpConfig* config;
	try
	{
		config = new HttpConfig("./sample.conf");	
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	std::multimap<in_port_t, in_addr_t> must_listens = config->getMustListens();
	for (std::multimap<in_port_t, in_addr_t>::iterator it = must_listens.begin(); it != must_listens.end(); it++){
		std::cout << it->second << " " << it->first << std::endl; 
	}	
	

	std::cout << "main 끝~~~" << std::endl;
	return (0);
}
