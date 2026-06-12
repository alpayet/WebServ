/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileSystemLockManager.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 01:12:28 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/05 15:27:46 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILESYSTEMLOCKMANAGER_HPP
#define FILESYSTEMLOCKMANAGER_HPP

#include <map>
#include <string>

namespace fileSystem {
class LockManager
{
  public:
	enum LockMode
	{
		unlocked,
		read,
		write
	};

  public:
	bool tryLock(std::string const &path, LockMode mode);

	void unlock(std::string const &path);

	LockMode isLocked(std::string const &path) const;

  private:
	LockManager(LockManager const &src);
	LockManager &operator=(LockManager const &rhs);

	std::map<std::string, LockMode> _lockedPaths;
};

} // namespace fileSystem

#endif // FILESYSTEMLOCKMANAGER_HPP