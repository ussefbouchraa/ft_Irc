/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:19:10 by ebelfkih          #+#    #+#             */
/*   Updated: 2024/05/06 00:35:48 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <cstring>
#include <vector>
#include <poll.h>
#include <map>
#include <netinet/in.h>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include "Client.hpp"
#include "Channel.hpp"
#include "Message.hpp"
#include "Command.hpp"

class Server
{
private:
    uint16_t                        _port;
    std::string                     _passWord;
    std::vector<pollfd>             _fds;
    std::vector<std::string>        _basicCmds;
    std::map<int, Client>           _clients;
    std::map<std::string, Channel>  _channels;
    
public:
    Server();
    Server(std::string port, std::string password);
    Server& operator=(const Server& obj);
    Server(const Server& obj);
    ~Server();

    void startServer();
    // bool authenticateUser() const;
    void handleClientConnection();
    void handleClientMessage(int i);

    // Channel createChannel(std::string channelName);
};

#endif
