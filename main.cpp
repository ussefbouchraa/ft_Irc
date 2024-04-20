/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:21:33 by ybouchra          #+#    #+#             */
/*   Updated: 2024/04/20 11:37:48 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <arpa/inet.h>
#include <sys/socket.h>

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
bool Valid_Args(std::string port, std::string ip)
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

        std::cout << "Valid_args\n";
}