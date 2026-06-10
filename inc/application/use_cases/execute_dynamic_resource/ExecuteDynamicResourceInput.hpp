/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResourceInput.hpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:50 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/10 01:13:17 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTEDYNAMICRESOURCEINPUT_HPP
#define EXECUTEDYNAMICRESOURCEINPUT_HPP

#include <map>
#include <string>

struct ExecuteDynamicResourceInput
{
	std::string								  id;
	std::map<std::string, std::string> const &parameters;
};

#endif // EXECUTEDYNAMICRESOURCEINPUT_HPP