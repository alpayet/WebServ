/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IStaticResourcePresenter.hpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 23:07:35 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/13 23:17:13 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ISTATICRESOURCEPRESENTER_HPP
#define ISTATICRESOURCEPRESENTER_HPP

#include <string>

namespace app {
class IStaticResourceReader;

class IStaticResourcePresenter
{
  public:
	virtual ~IStaticResourcePresenter() {}

	virtual void presentContent(IStaticResourceReader *resourceReader) = 0;

	virtual void presentListing(std::string const &storagePath) = 0;
};
} // namespace app

#endif // ISTATICRESOURCEPRESENTER_HPP