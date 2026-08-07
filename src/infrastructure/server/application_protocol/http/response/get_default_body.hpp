/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_default_body.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 23:06:22 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/10 17:56:05 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPGENERATEDEFAULTBODY_HPP
#define HTTPGENERATEDEFAULTBODY_HPP

namespace http {

char const *get_default_body(unsigned short status_code);
} // namespace http

#endif // HTTPGENERATEDEFAULTBODY_HPP
