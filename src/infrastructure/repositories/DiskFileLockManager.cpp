/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiskFileLockManager.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 20:24:13 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/05 15:27:46 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/repositories/DiskFileLockManager.hpp"
#include <algorithm>

bool DiskFileLockManager::tryLock(const std::string &path, DiskFileLockManager::LockMode mode)
{
	if (this->isLocked(path) != unlocked)
		return (false);
	_lockedPaths[path] = mode;
	return (true);
}

void DiskFileLockManager::unlock(std::string const &path) { _lockedPaths[path] = unlocked; }

DiskFileLockManager::LockMode DiskFileLockManager::isLocked(std::string const &path) const
{
	std::map<std::string, LockMode>::const_iterator it = _lockedPaths.find(path);
	if (it != _lockedPaths.end())
		return ((*it).second);
	return (unlocked);
}