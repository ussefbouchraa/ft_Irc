/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 06:41:03 by ybouchra          #+#    #+#             */
/*   Updated: 2024/04/20 11:15:14 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <cstring>
#include <cstdlib>  
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <sys/socket.h> 
#include <unistd.h> 

int main()
{
        
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocket == -1)
    return(std::cerr << "Socket creation failed:" << strerror(errno) << std::endl, 1);
        
    sockaddr_in serverAddress; 
    serverAddress.sin_family = AF_INET; 
    serverAddress.sin_port = htons(99999); 
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

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

