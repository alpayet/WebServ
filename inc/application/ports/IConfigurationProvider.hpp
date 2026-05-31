/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IConfigurationProvider.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 04:11:57 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/31 04:12:25 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICONFIGURATIONPROVIDER_HPP
#define ICONFIGURATIONPROVIDER_HPP

class IConfigurationProvider
{
  public:
	IConfigurationProvider(void);
	IConfigurationProvider(IConfigurationProvider const &src);
	~IConfigurationProvider(void);

	IConfigurationProvider &operator=(IConfigurationProvider const &rhs);

  private:
};

#endif // ICONFIGURATIONPROVIDER_HPP