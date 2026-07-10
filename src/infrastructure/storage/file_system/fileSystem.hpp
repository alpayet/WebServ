/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileSystem.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 03:21:14 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/09 00:11:25 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <string>

namespace fileSystem {
bool		exists(std::string const &path);
bool		isRegularFile(std::string const &path);
bool		isDirectory(std::string const &path);
bool		isReadable(std::string const &path);
bool		isWritable(std::string const &path);
bool		isExecutable(std::string const &path);
std::size_t getSize(std::string const &path);
bool		isDeletable(std::string const &path);
} // namespace fileSystem

#endif // FILESYSTEM_HPP