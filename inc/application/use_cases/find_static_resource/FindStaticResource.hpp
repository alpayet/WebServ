/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FindStaticResource.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/10 17:53:00 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FINDSTATICRESOURCEUSECASE_HPP
#define FINDSTATICRESOURCEUSECASE_HPP

class FindStaticResourceInput;
class FindStaticResourceOutput;
class IStaticResourceLocator;
class IStaticResourceStorage;

namespace useCase
{
	class FindStaticResource
	{
	  public:
		FindStaticResource(
			IStaticResourceLocator &staticResourceLocator,
			IStaticResourceStorage &staticResourceStorage
		);

		FindStaticResourceOutput execute(FindStaticResourceInput const &dtoInput);

	  private:
		FindStaticResource(FindStaticResource const &src);
		FindStaticResource &operator=(FindStaticResource const &rhs);

		IStaticResourceLocator &_staticResourceLocator;
		IStaticResourceStorage &_staticResourceStorage;
	};
} // namespace useCase

#endif // FINDSTATICRESOURCEUSECASE_HPP