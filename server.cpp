/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 06:41:42 by ybouchra          #+#    #+#             */
/*   Updated: 2024/05/01 18:55:48 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "server.hpp"

Server::Server(){};
Server::Server(std::string port, std::string password){


    if (!Valid_Args(port, password)){
        std::cerr << "ERROR: Invalid Input" << std::endl;
        exit(EXIT_FAILURE);
    }
    this->_port = _stoi(port);
    this->_password = password;
    
};
Server::Server(const Server &src)
{
    *this = src;
}
Server& Server::operator=(const Server &src)
{
        if (this != &src)
    {
        this->_port = src._port;
        this->_password = src._password;
        this->_fds = src._fds;
        // this->_clients = src._clients;
        // this->_channels = src._channels;
    }
    return *this;
}
Server::~Server()
{
    this->_password.clear();
    this->_fds.clear();
    // this->_clients.clear();
    // this->_channels.clear();
}

void Server::startServer()
{
    int srv_fd = socket(AF_INET,SOCK_STREAM,0 );
    if(srv_fd == -1)
    {
        std::cerr << "Socket creation failed:" << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }
    
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = this->_port;
    serverAddress.sin_addr.s_addr = INADDR_ANY;//  inet_addr(av[1])
    
    if(bind(srv_fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1){
        std::cerr << "Bind failed: " << strerror(errno) << std::endl, close(srv_fd);
        exit(EXIT_FAILURE);
        }

    if(listen(srv_fd, SOMAXCONN) == -1){
        std::cerr << "Listen failed: " << strerror(errno) << std::endl, close(srv_fd);
        exit(EXIT_FAILURE);
     }
    
    this->_fds.push_back((pollfd){srv_fd, POLLIN, 0});
    // this->_fds.resize(1);
    // this->_fds[0].fd = srv_fd;
    // this->_fds[0].events = POLLIN;
    
    std::cout << "Server Start Loading..." << std::endl;
    while(true)
    {
        int ret = poll(_fds.data(), _fds.size(), -1);
        if(ret == -1)
        {
             std::cerr << "Poll failed: " << strerror(errno) << std::endl;
            break;
        }
        if(this->_fds[0].revents & POLLIN)
        {
            int newSocket = accept(srv_fd, NULL, NULL);
            if(newSocket == -1)
            {   
                std::cerr << "Accept failed: " << strerror(errno) << std::endl;
                continue;
            }
            else
            {
                this->_fds.push_back((pollfd){newSocket, POLLIN, 0});
                std::cout << "New client connected" << std::endl;
            }
                
        }
        for(size_t i = 1; i < this->_fds.size(); i++)
        {
            if(this->_fds[i].revents & POLLIN)
            {
                char buffer[1024];
                int rcv_byt = recv(this->_fds[i].fd, buffer, sizeof(buffer), 0);
                if(rcv_byt > 0)
                {
                    std::cout <<  "Message from client: " << buffer << std::endl;
                    memset(&buffer, 0, sizeof(buffer));
                }  
                else if(rcv_byt == 0)
                {
                    std::cerr << "Client disconnected" << std::endl;
                    this->_fds.erase(this->_fds.begin() + i--);
                    close(this->_fds[i].fd);
                }
                else
                 std::cerr << "recieving failed: " << strerror(errno) << std::endl;
                    
            }
        }

   }
        close(srv_fd);

}
    


