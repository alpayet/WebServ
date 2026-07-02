/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generateDefaultBody.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 23:06:22 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/02 00:51:45 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPGENERATEDEFAULTBODY_HPP
#define HTTPGENERATEDEFAULTBODY_HPP

namespace http {
char const *generateDefaultBody(unsigned short const statusCode);
} // namespace http

#endif // HTTPGENERATEDEFAULTBODY_HPP
