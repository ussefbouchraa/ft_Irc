/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 06:41:03 by ybouchra          #+#    #+#             */
/*   Updated: 2024/04/20 12:00:09 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

int _stoi(std::string str)
{
    std::istringstream iss(str);
    int res;
    iss >> res;
    if(iss.eof() && !iss.bad())
        return(res);
    return(-1);
        
}
int is_digits(std::string str)
{
    int i = -1;
    while (str[++i])
    {
        if(!std::isdigit(str[i]))
            return(0);
    }
    return(1);
}
bool Valid_Args(std::string ip, std::string port)
{
    if (port.empty() || ip.empty()  ||!is_digits(port) )
        return(0);
    int _port = _stoi(port); 
    if ( _port < 1025 || _port > 65535)
        return(0);
    return(1);
}

int main(int ac, char **av)
    {
    if(ac != 3)
        return(std::cerr << "Error: Syntax_Err\n", 1);
    if (!Valid_Args(av[1], av[2]))
        return(std::cerr << "Invalid_Args\n", 1);
        
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocket == -1)
    return(std::cerr << "Socket creation failed:" << strerror(errno) << std::endl, 1);
        
    sockaddr_in serverAddress; 
    serverAddress.sin_family = AF_INET; 
    serverAddress.sin_port = htons(_stoi(av[2])); 
    serverAddress.sin_addr.s_addr = inet_addr(av[1]);

    if(connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
        return(std::cerr << "Error connecting to server\n", close(clientSocket), 1);

    std::string line;
    while(std::getline(std::cin, line))
    {
        if(line == "exit")
            exit(0);
        int send_byt = send(clientSocket, line.c_str(), line.length(), 0);
        if(send_byt == -1)
            return(std::cerr << "sending failed: " << strerror(errno) << std::endl, close(clientSocket), 1);
        else if(send_byt == 0)
        std::cerr << "Noting To Send ." << std::endl;
        
            
    }
    close(clientSocket);
        
}

