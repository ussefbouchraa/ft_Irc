/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 08:24:03 by ybouchra          #+#    #+#             */
/*   Updated: 2024/04/24 12:08:18 by ybouchra         ###   ########.fr       */
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
#include <sstream>

class client
{
    private:
    int fd_client;
    std::string username;
    std::string nickname;
    std::string password;
    sockaddr_in serverAddress;
    bool authent_status;
    
    public:
        std::string get_nickname();
        std::string get_username();
        void set_nickname();
        void set_username();
        void authenticateUser(std::string username, std::string password);
        void registerUser();

};


int _stoi(std::string str);
int is_digits(std::string str);
bool validip(std::string ip);
bool Valid_Args(std::string ip, std::string port);