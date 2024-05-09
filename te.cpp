/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   te.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 01:00:36 by ybouchra          #+#    #+#             */
/*   Updated: 2024/05/07 01:17:59 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iostream"
#include <vector>

int main()
{
    std::string msg = "join";
std::vector<std::string> vec;
	vec.push_back("QUIT");
	vec.push_back("join");
std::vector<std::string>::iterator it = vec.begin();
    
	it = std::find(it, vec.end(), msg);
	if(it != vec.end())
		std::cout << "******" <<  *it << std::endl;
	else 
	{
		std::cout << "NOT FOUND\n";
		return(0);
	}
	return(1);
    
}