/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 01:00:49 by ybouchra          #+#    #+#             */
/*   Updated: 2024/05/09 07:38:39 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <map>
#include <algorithm>
#include "Client.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Message.hpp"
#include "Command.hpp"

enum cmds{
                USER = 0,
                NICK = 1,
                PASS = 2,
                PRIVMSG = 3,
                NOTICE = 4,
                JOIN = 5,
                PART = 6,
                QUIT = 7,
                KICK = 8,
                TOPIC = 9,
                INVITE = 10,
                MODE = 11,
                UNKNOWN = -1,
};

class Command{
    private:
    Client	    _client;
    std::vector<std::string>   _tokens;
    std::vector<std::string>    _basicCmds;
    std::vector<std::string>    _parameters;
    
    std::string _command;
    std::string _parms;
    bool _basicCmd_status;

    
    public:
    Command();
    Command(Client);
    
    ~Command();
    std::string getCommand()const;
    bool getBasicCmd_status()const;
    bool is_validFormat(std::string msg);
    bool is_command(std::string msg);
    void initBasicCmds();
    void Extract_items(std::string msg);
    bool check_cmd(std::string msg);
    bool check_args();
    int  find_pos();
    void exec_cmd();
    void userCommand();
    void nickCommand();
    // void joinCommand();
    // void passCommand();
    // void joinCommand();
    // void partCommand();
    // void kickCommand();
    // void privmsgCommand();
    // void noticeCommand();
    // void topicCommand();
    // void inviteCommand();
    // void quitCommand();
    // void modeCommand();
    
    
    
    void clear();
       
};