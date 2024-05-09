/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 01:00:44 by ybouchra          #+#    #+#             */
/*   Updated: 2024/05/09 07:45:36 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/Command.hpp"

Command::Command(Client client)
{
   this->_basicCmd_status = false;
   this->_client = client;

};
Command::~Command()
{
	this->_command.clear();
	this->_parms.clear();
};

bool Command::getBasicCmd_status() const
{
	return(this->_basicCmd_status);
};

std::string Command::getCommand() const
{
	return(this->_command);
};



std::string to_uppercase(const std::string& str) {
    std::string result = str;
    for (size_t i = 0; i < result.length(); ++i) {
        result[i] = std::toupper(result[i]);
    }
    return result;
}



void Command::Extract_items(std::string msg)
{
	// std::string tmp_msg = msg;
	// 	tmp_msg = msg.substr(0, msg.size() - 2);

	std::istringstream iss(msg);
	std::string token;
	while(iss >> token)
		this->_tokens.push_back(token);

	this->_command = to_uppercase(_tokens[0]);
	for(size_t i = 1 ;  _tokens.size() > i ; i++)
			this->_parameters.push_back(_tokens[i]);	
}

bool Command::check_cmd(std::string msg)
{
	if(this->_command.empty() || this->_tokens.size() < 1)
		return(false);
	if(!this->getBasicCmd_status())
		this->initBasicCmds();
	std::vector<std::string> ::iterator it = std::find(_basicCmds.begin(), _basicCmds.end(), this->_command);
	std::string msg_cmd = msg.substr(0, this->_command.size());
	if( it != _basicCmds.end() && msg_cmd == *it)
		return(true);

	else
	{
		this->clear();
		return(false);
	}
}
bool Command::check_args()
{
	if(this->_parameters.empty() || this->_parameters.size() < 1)
		return(false);
	return(true);
	
}
bool Command::is_validFormat(std::string msg)
{ 
    if(msg.empty() || msg.at(0) != '/' )
        return(false);
    if(msg.size() < 5 )
        return(false);
//  std::cout <<  "["<< msg.substr(msg.size() - 5) << "]" << std::endl;
//     if(msg.substr(msg.size() - 5) != "\r\n")
//         return(false);
    return(true);
}

bool Command::is_command(std::string msg)
{ 
	if(!this->is_validFormat(msg))
		return(0);
	this->Extract_items(msg);
	if(!this->check_cmd(msg))
		return(0);
	if(!this-> check_args())
		return(0);
	return(1);
}

void Command::initBasicCmds()
{
   
     this->_basicCmds.push_back("/USER");
	 this->_basicCmds.push_back("/NICK");
	 this->_basicCmds.push_back("/PASS");
	 this->_basicCmds.push_back("/PRIVMSG");
	 this->_basicCmds.push_back("/NOTICE");
	 this->_basicCmds.push_back("/JOIN");
	 this->_basicCmds.push_back("/PART");
	 this->_basicCmds.push_back("/QUIT");
	 this->_basicCmds.push_back("/KICK");
	 this->_basicCmds.push_back("/TOPIC");
	 this->_basicCmds.push_back("/INVITE");
	 this->_basicCmds.push_back("/MODE");

	 this->_basicCmd_status = true;
};

void Command::clear()
{
	this->_command.clear();
	this->_parms.clear();
	this->_tokens.erase(_tokens.begin(), _tokens.end());
	this->_basicCmds.erase(_basicCmds.begin(), _basicCmds.end());
	this->_parameters.erase(_parameters.begin(), _parameters.end());
};

int  Command:: find_pos()
{
	if(this->getBasicCmd_status() == true)
	{
		for(size_t i = 0; this->_basicCmds.size() > i ; i++)
		{
			if (this->_basicCmds[i] == (this->getCommand()))
				return i;
		}
	}
	return(-1);
}


void Command::exec_cmd()
{
	switch (find_pos())
	{

	case(USER):
		userCommand();
		break;
	case(NICK):
		nickCommand();
		break;
	// case(PASS):
	// 	passCommand();
	// 	break;
	// case(JOIN):
	// 	joinCommand();
	// 	break;
	// case(PART):
	// 	partCommand();
	// 	break;
	// case(KICK):
	// 	kickCommand();
	// 	break;
	// case(PRIVMSG):
	// 	privmsgCommand();
	// 	break;
	// case(NOTICE):
	// 	noticeCommand();
	// 	break;     
	// case(TOPIC):
	// 	topicCommand();
	// 	break;
	// case(INVITE):
	// 	inviteCommand();
	// 	break;
	// case(QUIT):
	// 	quitCommand();
	// 	break;
	// case(MODE):
	// 	modeCommand();
	// 	break;
	case(UNKNOWN):
		std::cerr << " Invalid_Cmd \n";
		break;
	
	}
}




void Command::userCommand()
{
	std::cout << "/USER\n";
}
void Command::nickCommand()
{
	if(this->_parameters.size() == 1 && !this->_parameters[0].empty()){
		std::string newNickname = this->_parameters[0];
	this->_client.setNickName(newNickname);	
	std::cout << "Setting new nickname to: " << newNickname << std::endl;
	}else 
		std::cerr << "Invalid number of parameters for NICK command" << std::endl;
}
// void Command::joinCommand()
// {
	
// }