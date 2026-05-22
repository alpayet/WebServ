/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Methods.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 19:24:20 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/22 20:03:36 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPMETHODS_HPP
# define HTTPMETHODS_HPP

#include <string>

namespace http
{
	bool	isMethodSupported(std::string const	&method);
}

#endif