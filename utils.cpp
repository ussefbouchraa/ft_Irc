/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:08:04 by ybouchra          #+#    #+#             */
/*   Updated: 2024/05/01 18:18:56 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
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
bool validip(std::string ip)
{
    int part;
    char dot;
    
    std::istringstream iss(ip);
    for(int i = 0; i < 4; i++)
    {
        if(!(iss >> part) || (i < 3 && !(iss >> dot)) || dot != '.')
            return(false);
        if(part < 0 || part > 255)
            return(false);
    }
    return(true);
}
bool Valid_Args(std::string port, std::string password)
{
    if (port.empty() || password.empty() || !is_digits(port))
        return(0);
    int _port = _stoi(port); 
    if ( _port < 1025 || _port > 65535)
        return(0);
    return(1);
}