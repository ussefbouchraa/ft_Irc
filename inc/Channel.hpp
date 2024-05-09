/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:16:50 by ebelfkih          #+#    #+#             */
/*   Updated: 2024/05/02 20:59:58 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <map>
#include "Client.hpp"
class Client;

class Channel
{
private:
    int						_userLimit;
    std::string				_channelName;
    std::string				_passWord;
    std::string				_topic;
    std::string				_mode;
    std::map<int, Client>	_clients;
    std::map<int, Client>	_operators;
    std::map<int, Client>	_invitees;
    
public:
    Channel();
    Channel& operator=(const Channel& obj);
    Channel(const Channel& obj);
    ~Channel();

    // param constructor

    // getters
    std::string getChannelName() const;
    std::string getpassWord() const;
    std::string getTopic() const;
    std::string getMode() const;
    
    // setters
    void setChannelName(std::string newName, Client setter);
    void setpassWord(std::string newpassWord, Client setter);
    void setTopic(std::string newTopic, Client setter);
    void setMode(std::string newMode, Client setter);

    // add
    void addClient(Client cli);
    void addOperators(Client ope);
    void addInvited(Client inv);

    // utils
    void brodcastMessage(std::string message, Client sender);
    bool joinChannel(Client cli);
    void removeClient(int fd);
};

#endif