/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 06:41:59 by ybouchra          #+#    #+#             */
/*   Updated: 2024/05/01 17:59:00 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <cstring>
#include <cstdlib>  
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <sys/socket.h> 
#include <unistd.h> 
#include <cerrno>
#include <vector>
#include <poll.h>
#include <sstream>
#include <map>


class Server
{
private:
    int                             _port;
    std::string                     _password;
    std::vector<pollfd>             _fds;
    // std::map<int, Client>           _clients;
    // std::map<std::string, Channel>  _channels;
    
    Server();
    
public:
    Server(std::string port, std::string password);
    Server& operator=(const Server& obj);
    Server(const Server& obj);
    ~Server();
    void startServer();
};

int _stoi(std::string str);
int is_digits(std::string str);
bool validip(std::string ip);
bool Valid_Args(std::string ip, std::string port);