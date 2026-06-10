/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResource.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/10 17:54:06 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETESTATICRESOURCEUSECASE_HPP
#define DELETESTATICRESOURCEUSECASE_HPP

class DeleteStaticResourceInput;
class DeleteStaticResourceOutput;
class IStaticResourceLocator;
class IStaticResourceStorage;

namespace useCase
{
	class DeleteStaticResource
	{
	  public:
		DeleteStaticResource(
			IStaticResourceLocator &staticResourceLocator,
			IStaticResourceStorage &staticResourceStorage
		);

		DeleteStaticResourceOutput execute(DeleteStaticResourceInput const &dtoInput);

	  private:
		DeleteStaticResource(DeleteStaticResource const &src);
		DeleteStaticResource &operator=(DeleteStaticResource const &rhs);

		IStaticResourceLocator &_staticResourceLocator;
		IStaticResourceStorage &_staticResourceStorage;
	};
} // namespace useCase

#endif // DELETESTATICRESOURCEUSECASE_HPP