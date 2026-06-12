/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileSystemLockManager.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 20:24:13 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/05 15:27:46 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/storage/file_system/LockManager.hpp"
#include <algorithm>

namespace fileSystem {
bool LockManager::tryLock(std::string const &path, LockManager::LockMode mode)
{
	if (this->isLocked(path) != unlocked)
		return (false);
	_lockedPaths[path] = mode;
	return (true);
}

void LockManager::unlock(std::string const &path) { _lockedPaths[path] = unlocked; }

LockManager::LockMode LockManager::isLocked(std::string const &path) const
{
	std::map<std::string, LockMode>::const_iterator it = _lockedPaths.find(path);
	if (it != _lockedPaths.end())
		return ((*it).second);
	return (unlocked);
}
} // namespace fileSystem