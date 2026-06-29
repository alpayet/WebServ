/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listingHtml.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 01:23:50 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/30 01:34:48 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPLISTINGHTML_HPP
#define HTTPLISTINGHTML_HPP

#include "infrastructure/storage/file_system/FileInfos.hpp"
#include <string>
#include <vector>

namespace http {
std::string getListing(std::string const &uri, std::vector<fileSystem::FileInfos> const &files);
} // namespace http

#endif // HTTPLISTINGHTML_HPP