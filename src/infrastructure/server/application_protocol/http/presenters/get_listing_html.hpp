/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_listing_html.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 01:23:50 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/14 01:12:23 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPLISTINGHTML_HPP
#define HTTPLISTINGHTML_HPP

#include "application/ports/CollectionEntry.hpp"
#include <string>
#include <vector>

namespace http {
std::string
get_listing_html(std::string const &uri, std::vector<app::CollectionEntry> const &files);
} // namespace http

#endif // HTTPLISTINGHTML_HPP