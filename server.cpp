/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 06:41:42 by ybouchra          #+#    #+#             */
/*   Updated: 2024/04/16 11:38:21 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <cstring>
#include <cstdlib>  
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h> 

int main()
{
    
   std::cout << "Server Start Loading..." << std::endl;
    int servSocketFd = socket(AF_INET,SOCK_STREAM,0);
    if(servSocketFd == -1)
        return(std::cerr << "Error creating socket\n", 1);
    
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    
    bind(servSocketFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    listen(servSocketFd, 5);
    int clientSocket = accept(servSocketFd, NULL, NULL);
    if(clientSocket != -1)
    { 
        char buffer[1024];
        int _read;
        while((_read = recv(clientSocket, buffer, sizeof(buffer), 0)) != -1 && _read )
        {
            std::cout <<  "Message from client: " << buffer << std::endl;
            memset(&buffer, 0, sizeof(buffer));
        } 
  
        if(_read == -1)
           std::cerr << "Error recieving data\n";  
           
        close(clientSocket);
    }

    close(servSocketFd);
   }

