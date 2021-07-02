/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 03:33:46 by kycho             #+#    #+#             */
/*   Updated: 2021/07/02 22:39:43 by kycho            ###   ########.fr       */
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

	HttpConfig config("./sample.conf");
	
	

	std::cout << "main 끝~~~" << std::endl;
	return (0);
}
