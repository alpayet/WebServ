/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IServeStaticResourcePresenter.hpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 23:07:35 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/14 21:31:18 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ISERVESTATICRESOURCEPRESENTER_HPP
#define ISERVESTATICRESOURCEPRESENTER_HPP

#include <string>

namespace app {
class IStaticResourceReader;

class IServeStaticResourcePresenter
{
  public:
	virtual ~IServeStaticResourcePresenter() {}

	virtual void presentContent(IStaticResourceReader *resourceReader) = 0;

	virtual void presentListing(std::string const &storagePath) = 0;
};
} // namespace app

#endif // ISERVESTATICRESOURCEPRESENTER_HPP