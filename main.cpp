/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:21:33 by ybouchra          #+#    #+#             */
/*   Updated: 2024/05/02 18:11:11 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "server.hpp"

 int main(int ac, char **av)
 {
    std::cout << "\033[31m" << std::endl; 
    if(ac != 3)
        return(std::cerr << "Error : Syntax_Err" << std::endl, 1);
    else
    {
        Server srv(av[1], av[2]);
	    srv.startServer();
    }
 }