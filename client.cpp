/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 06:41:03 by ybouchra          #+#    #+#             */
/*   Updated: 2024/04/16 10:48:56 by ybouchra         ###   ########.fr       */
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
        
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocket == -1)
        return(std::cerr << "Error creating socket\n", 1);
        
    sockaddr_in serverAddress; 
    serverAddress.sin_family = AF_INET; 
    serverAddress.sin_port = htons(8080); 
    serverAddress.sin_addr.s_addr = INADDR_ANY;

      // sending connection request 
    if(connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
        return(std::cerr << "Error connecting to server\n", close(clientSocket), 1);

    std::string line;
    while(std::getline(std::cin, line))
    {
        if(send(clientSocket, line.c_str(), line.length(), 0) == -1)
            return(std::cerr << "Error sending data\n", close(clientSocket), 1);
    }
    close(clientSocket);
        
}

