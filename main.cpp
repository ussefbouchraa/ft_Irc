/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:21:33 by ybouchra          #+#    #+#             */
/*   Updated: 2024/04/13 19:42:57 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <cstring>
#include <algorithm>

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
    int i = 0;
    if(str[0] == '+' || str[0] == '-')
        i++;
    while (str[i])
    {
        if(!std::isdigit(str[i]))
            return(0);
        i++;
    }
    return(1);
}
bool Valid_Args(std::string port, std::string password)
{
    if (port.empty() || password.empty()  ||!is_digits(port))
        return(0);
    int p = _stoi(port);
    std::cout << p << std::endl;
    if ( p < 0 || p > 65535)
        return(0);
    return(1);
}
int main(int ac, char **av)
{
    if(ac != 3)
        return(std::cerr << "Error: Syntax_Err\n", 1);
    std::string port, password;
    port = av[1];
    password = av[2];
    if (!Valid_Args(port, password))
       return(std::cerr << "Invalid_Args\n", 1);

        std::cout << "Valid_args\n";
}