/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 06:41:42 by ybouchra          #+#    #+#             */
/*   Updated: 2024/04/20 11:11:57 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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

int main()
{

 
    std::cout << "Server Start Loading..." << std::endl;
    int srv_fd = socket(AF_INET,SOCK_STREAM,0 );
    if(srv_fd == -1)
       return(std::cerr << "Socket creation failed:" << strerror(errno) << std::endl, 1);
    
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(99999);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    
    if(bind(srv_fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
         return(std::cerr << "Bind failed: " << strerror(errno) << std::endl, close(srv_fd), 1);
    if(listen(srv_fd, 5) == -1)
        return( std::cerr << "Listen failed: " << strerror(errno) << std::endl, close(srv_fd), 1);
    
    std::vector<pollfd> fds(1);
    fds[0].fd = srv_fd;
    fds[0].events = POLLIN;
    
    while(true)
    {
        int ret = poll(fds.data(), fds.size(), -1);
        if(ret == -1)
        {
             std::cerr << "Poll failed: " << strerror(errno) << std::endl;
            break;
        }
        if(fds[0].revents & POLLIN)
        {
            int newSocket = accept(srv_fd, NULL, NULL);
            if(newSocket == -1)
            {   
                std::cerr << "Accept failed: " << strerror(errno) << std::endl;
                continue;
            }
            else
                fds.push_back((pollfd){newSocket, POLLIN});
                
        }
        for(size_t i = 1; i < fds.size(); i++)
        {
            if(fds[i].revents & POLLIN)
            {
                char buffer[1024];
                int rcv_byt = recv(fds[i].fd, buffer, sizeof(buffer), 0);
                if(rcv_byt > 0)
                {
                    std::cout <<  "Message from client: " << buffer << std::endl;
                    memset(&buffer, 0, sizeof(buffer));
                }  
                else if(rcv_byt == 0)
                {
                    std::cerr << "Client disconnected" << std::endl;
                    fds.erase(fds.begin() + i--);
                    close(fds[i].fd);
                }
                else
                 std::cerr << "recieving failed: " << strerror(errno) << std::endl;
                    
            }
        }

   }
        close(srv_fd);

}
