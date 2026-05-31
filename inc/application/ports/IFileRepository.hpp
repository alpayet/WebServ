/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IFileRepository.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 04:12:08 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/31 04:12:20 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IFILEREPOSITORY_HPP
#define IFILEREPOSITORY_HPP

class IFileRepository
{
  public:
	IFileRepository(void);
	IFileRepository(IFileRepository const &src);
	~IFileRepository(void);

	IFileRepository &operator=(IFileRepository const &rhs);

  private:
};

#endif // IFILEREPOSITORY_HPP