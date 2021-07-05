/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 03:33:46 by kycho             #+#    #+#             */
/*   Updated: 2021/07/05 18:46:42 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "HttpConfig.hpp"

int main(int argc, char *argv[])
{
	HttpConfig* config;
	try
	{
		config = new HttpConfig("./sample.conf");	
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}




	std::cout << "\n\n\n<<< must_listens 출력 시작>>>" << std::endl;
	std::multimap<in_port_t, in_addr_t> must_listens = config->getMustListens();
	for (std::multimap<in_port_t, in_addr_t>::iterator it = must_listens.begin(); it != must_listens.end(); it++)
	{
		in_addr_t ip_addr = it->second;
		in_port_t port = it->first;
		struct in_addr addr;
		addr.s_addr = ip_addr;
		std::cout << "ip_addr:port   => " << inet_ntoa(addr) << ":" << ntohs(it->first) << std::endl; 
	}
	std::cout << "<<< must_listens 출력 끝>>>\n\n\n" << std::endl;


	// 전체상태 출력해보는 함수
	config->print_all_server_location_for_debug();




	std::cout << "main 끝~~~" << std::endl;
	return (0);
}
