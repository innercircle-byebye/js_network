/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpConfig.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 13:47:53 by kycho             #+#    #+#             */
/*   Updated: 2021/07/02 16:28:41 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_CONFIG_HPP
# define HTTP_CONFIG_HPP

# include <vector>
# include <map>
# include <string>
# include <arpa/inet.h>
# include <fstream>

# include "Server.hpp"
# include "Location.hpp"
# include "Tokenizer.hpp"

class HttpConfig
{
//private:
public:
	std::multimap<in_port_t, in_addr_t>			must_listens;
	
	std::string									root;
	std::vector<std::string>					index;
	bool										autoindex;
	int											client_max_body_size;
	std::map<int, std::string>					error_page;

	std::map<in_port_t, std::map<in_addr_t, std::vector<Server*> > > server;

public:
	HttpConfig(void)
	{	
		// must_listens;
		must_listens.insert(std::pair<in_port_t, in_addr_t>(80, inet_addr("0.0.0.0")));
		must_listens.insert(std::pair<in_port_t, in_addr_t>(8080, inet_addr("0.0.0.0")));
		must_listens.insert(std::pair<in_port_t, in_addr_t>(9090, inet_addr("172.30.1.34")));

		root = "httptest";
		index.push_back("httptest.html");
		index.push_back("httptest.htm");
		autoindex = true;
		client_max_body_size = 1;

		
		
		// make server blocks start
		Server* server1 = new Server();
		server1->root = this->root;
		server1->index = this->index;
		server1->autoindex = this->autoindex;
		server1->error_page = this->error_page;
		server1->client_max_body_size = this->client_max_body_size;


		Server* server2 = new Server();
		server2->root = this->root;
		server2->index = this->index;
		//server2->autoindex = this->autoindex;
		server2->autoindex = false;
		//server2->error_page = this->error_page;
		server2->error_page[404] = "/404.htmp";
		server2->error_page[500] = "/50x.htmp";
		server2->error_page[502] = "/50x.htmp";
		server2->error_page[503] = "/50x.htmp";
		server2->error_page[504] = "/50x.htmp";
		server2->client_max_body_size = this->client_max_body_size;
		server2->server_name.push_back("localhost");


		Server* server3 = new Server();
		server3->root = this->root;
		server3->index = this->index;
		server3->autoindex = this->autoindex;
		server3->error_page = this->error_page;
		server3->client_max_body_size = this->client_max_body_size;
		server3->server_name.push_back("somename");
		server3->server_name.push_back("alias");
		server3->server_name.push_back("another.alias");
		
		// make server blocks end


		// make location blocks start
		Location* location1 = new Location();
		location1->uri_path = "/default";
		location1->root = server1->root;
		location1->index = server1->index;
		location1->autoindex = server1->autoindex;
		location1->error_page = server1->error_page;
		location1->client_max_body_size = server1->client_max_body_size;

		Location* location2 = new Location();
		location2->uri_path = "/";
		location2->root = "html";
		location2->index.push_back("index.html");
		location2->index.push_back("index.htm");
		location2->autoindex = server2->autoindex;
		location2->error_page = server2->error_page;
		location2->client_max_body_size = server2->client_max_body_size;


		Location* location3 = new Location();
		location3->uri_path = "/test/";
		location3->root = server2->root;
		location3->index.push_back("test.html");
		location3->autoindex = true;
		location3->error_page = server2->error_page;
		location3->client_max_body_size = server2->client_max_body_size;


		Location* location4 = new Location();
		location4->uri_path = "/50x.html";
		location4->root = "html";
		location4->index = server2->index;
		location4->autoindex = server2->autoindex;
		location4->error_page = server2->error_page;
		location4->client_max_body_size = server2->client_max_body_size;


		Location* location5 = new Location();
		location5->uri_path = "/";
		location5->root = "html";
		location5->index.push_back("index.html");
		location5->index.push_back("index.htm");
		location5->autoindex = server3->autoindex;
		location5->error_page = server3->error_page;
		location5->client_max_body_size = server3->client_max_body_size;
		// make location blocks end


		server1->locations.push_back(location1);
		server2->locations.push_back(location2);
		server2->locations.push_back(location3);
		server2->locations.push_back(location4);
		server3->locations.push_back(location5);


		this->server[80][inet_addr("0.0.0.0")].push_back(server1);
		this->server[8080][inet_addr("0.0.0.0")].push_back(server2);
		this->server[8080][inet_addr("127.0.0.1")].push_back(server3);
		this->server[9090][inet_addr("172.30.1.34")].push_back(server3);
		
	}
	
	HttpConfig(std::string configFilePath)
	{
		std::ifstream ifs(configFilePath);
		std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
				
		ft::Tokenizer tokenizer;
		std::vector<std::string> tokens = tokenizer.parse(content);
	
		std::vector<std::vector<std::string> > servers_tokens;

		std::vector<std::string>::iterator it = tokens.begin();
		it++;
		it++;
	
		while (*it != "}")
		{
			if ( *it == "root"){

				while (*it != ";")
				{
					std::cout << "[" << *it << "] " << std::endl;
					it++;
				}
				it++;
				std::cout << std::endl;
				
			}else if (*it == "index"){
				
				while (*it != ";")
				{
					std::cout << "[" << *it << "] " << std::endl;
					it++;
				}
				it++;
				std::cout << std::endl;

			}else if (*it == "autoindex"){
				
				while (*it != ";")
				{
					std::cout << "[" << *it << "] " << std::endl;
					it++;
				}
				it++;
				std::cout << std::endl;

			}else if (*it == "error_page"){
				
				while (*it != ";")
				{
					std::cout << "[" << *it << "] " << std::endl;
					it++;
				}
				it++;
				std::cout << std::endl;

			}else if (*it == "client_max_body_size"){
				
				while (*it != ";")
				{
					std::cout << "[" << *it << "] " << std::endl;
					it++;
				}
				it++;
				std::cout << std::endl;

			}else if (*it == "server"){

				std::vector<std::string> server_tokens;

				server_tokens.push_back(*it);
				it++;
				server_tokens.push_back(*it);
				it++;

				int cnt = 1;
				while (cnt != 0){
					if (*it == "{") cnt++;
					else if (*it == "}") cnt--;
					server_tokens.push_back(*it);
					it++;
				}
				servers_tokens.push_back(server_tokens);
				
			}else {
				
				std::cout << "~~ 이상한거 들어옴!!!! ~~" << std::endl;
				while (*it != ";")
				{
					std::cout << "[" << *it << "] " << std::endl;
					it++;
				}
				it++;
				std::cout << std::endl;
				
			}
		}

		
		std::vector<std::vector<std::string> >::iterator server_it = servers_tokens.begin();
		for (; server_it != servers_tokens.end(); server_it++){
			
			Server *new_server = new Server(*server_it);
		}
		
	}
	
	//HttpConfig(const HttpConfig& HttpConfig);
	~HttpConfig() {
		std::cout << "~HttpConfig() 호출~~~" << std::endl;
	}
	//HttpConfig& operator=(const HttpConfig& other);

	std::multimap<in_port_t, in_addr_t>	getMustListens(void)
	{
		return must_listens;
	}

	Location* getLocationConfig(in_port_t port, in_addr_t ip_addr, std::string server_name, std::string uri_path)
	{
		return server[8080][inet_addr("127.0.0.1")][0]->locations[0];
	}
};

#endif
