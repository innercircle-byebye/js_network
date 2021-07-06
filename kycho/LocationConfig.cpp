/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationConfig.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 14:11:56 by kycho             #+#    #+#             */
/*   Updated: 2021/07/06 16:51:50 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LocationConfig.hpp"

LocationConfig::LocationConfig(void)
{}

LocationConfig::LocationConfig(std::vector<std::string> tokens, ServerConfig* server)
{	
	// 초기화부분
	this->root = server->root;
	this->index = server->index;
	this->autoindex = server->autoindex;
	this->client_max_body_size = server->client_max_body_size;
	
	// 한번이라도 세팅했었는지 체크하는 변수
	bool check_root_setting = false;
	bool check_index_setting = false;
	bool check_autoindex_setting = false;
	bool check_client_max_body_size = false;

	std::vector<std::string>::iterator it = tokens.begin(); // "location"
	it++;	// path
	this->uri_path = *(it);
	it++;	// "{"
	it++;	// any directive

	while(*it != "}")
	{
		if (*it == "root")
		{
			if (*(it + 1) == ";" || *(it + 2) != ";")
				throw std::runtime_error("webserv: [emerg] invalid number of arguments in \"root\" directive");
			if (check_root_setting == true)
				throw std::runtime_error("webserv: [emerg] \"root\" directive is duplicate");

			this->root = *(it + 1);
			check_root_setting = true;
			
			it += 3;
		}
		else if (*it == "index")
		{
			if (*(it + 1) == ";")
				throw std::runtime_error("webserv: [emerg] invalid number of arguments in \"index\" directive");

			if (check_index_setting == false){
				this->index.clear();
				check_index_setting = true;
			}

			it++;
			while (*it != ";")
			{
				this->index.push_back(*it);
				it++;
			}
			it++;
		}
		else if (*it == "autoindex")
		{
			if (*(it + 1) == ";" || *(it + 2) != ";")
				throw std::runtime_error("webserv: [emerg] invalid number of arguments in \"autoindex\" directive");
			if (check_autoindex_setting == true)
				throw std::runtime_error("webserv: [emerg] \"autoindex\" directive is duplicate");
			if ( (*(it + 1)) != "on" && *(it + 1) != "off")
				throw std::runtime_error("webserv: [emerg] invalid value \"" + *(it + 1) + "\" in \"autoindex\" directive, it must be \"on\" or \"off\"");

			if (*(it + 1) == "on")
				this->autoindex = true;
			else
				this->autoindex = false;

			check_autoindex_setting = true;
			it += 3;
		}
		else if (*it == "error_page")
		{
			// TODO : 예외처리해야함 
			
			int count = 2;
			while(*(it + count + 1) != ";")
				count++;

			for(int i = 1; i < count; i++){
				int status_code  = atoi((*(it + i)).c_str());

				if (this->error_page.find(status_code) == this->error_page.end()){
					this->error_page[status_code] = *(it + count);
				}
			}
			it += (count + 2);
		}
		else if (*it == "client_max_body_size")
		{
			// TODO : 예외처리해야함
			if (check_client_max_body_size == true)
				throw std::runtime_error("webserv: [emerg] \"client_max_body_size\" directive is duplicate");
			
			
			std::string size_str = *(it + 1);

			this->client_max_body_size = atoi(size_str.c_str());

			char last_char = size_str[size_str.length() - 1];
			if ( last_char == 'k'){
				client_max_body_size *= 1000;
			}else if (last_char == 'm'){
				client_max_body_size *= 1000000;	
			}else if (last_char == 'g'){
				client_max_body_size *= 1000000000;	
			}
			
			check_client_max_body_size = true;
			it += 3;
		}
		else
		{
			throw std::runtime_error("webserv: [emerg] unknown directive \"" + (*it) + "\"");
		}
	}

	for(std::map<int, std::string>::iterator i = server->error_page.begin(); i != server->error_page.end(); i++)
	{
		int status_code = i->first;
		std::string path = i->second;

		if (this->error_page.find(status_code) == this->error_page.end())
		{
			this->error_page[status_code] = path;
		}
	}
}

LocationConfig::~LocationConfig(void)
{
	std::cout << "~LocationConfig() 호출~~~" << std::endl;
}

bool LocationConfig::isPrefixMatchUri(std::string request_uri)
{
	if (this->uri_path.length() <= request_uri.length())
	{
		if (request_uri.compare(0, this->uri_path.length(), this->uri_path) == 0)
		{
			return true;
		}
	}
	return false;
}

// ############## for debug ###################
void LocationConfig::print_status_for_debug(std::string prefix)  // TODO : remove
{
	std::cout << prefix;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ LocationConfig ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;	

	std::cout << prefix;
	std::cout << "uri_path : " << this->uri_path << std::endl;

	std::cout << prefix;		
	std::cout << "root : " << this->root << std::endl;

	std::cout << prefix;		
	std::cout << "index : ";
	for (std::vector<std::string>::iterator i = this->index.begin(); i != this->index.end(); i++){
		std::cout << *i << " ";
	}
	std::cout << std::endl;

	std::cout << prefix;		
	std::cout << "autoindex : " << this->autoindex << std::endl;

	std::cout << prefix;
	std::cout << "client_max_body_size : " << this->client_max_body_size << std::endl;

	std::cout << prefix;
	std::cout << "error_page : " ;
	for (std::map<int, std::string>::iterator i = this->error_page.begin(); i != this->error_page.end(); i++){
		std::cout << i->first << ":" << i->second << "  ";
	}
	std::cout << std::endl;
	std::cout << prefix;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;	
}