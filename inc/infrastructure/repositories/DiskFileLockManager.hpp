/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiskFileLockManager.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 01:12:28 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/03 21:56:47 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISKFILELOCKMANAGER_HPP
#define DISKFILELOCKMANAGER_HPP

#include <map>
#include <string>

class DiskFileLockManager
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
	DiskFileLockManager(DiskFileLockManager const &src);
	DiskFileLockManager &operator=(DiskFileLockManager const &rhs);

	std::map<std::string, LockMode> _lockedPaths;
};

#endif // DISKFILELOCKMANAGER_HPP