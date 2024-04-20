/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 06:41:42 by ybouchra          #+#    #+#             */
/*   Updated: 2024/04/20 11:58:32 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "server.hpp"

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
 
    std::cout << "Server Start Loading..." << std::endl;
    int srv_fd = socket(AF_INET,SOCK_STREAM,0 );
    if(srv_fd == -1)
       return(std::cerr << "Socket creation failed:" << strerror(errno) << std::endl, 1);
    
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(_stoi(av[2]));
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
