/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ITransferContext.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 17:01:50 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/05 15:27:46 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITRANSFERCONTEXT_HPP
#define ITRANSFERCONTEXT_HPP

class ITransferContext
{
  public:
	ITransferContext(void);
	ITransferContext(ITransferContext const &src);
	~ITransferContext(void);

	ITransferContext &operator=(ITransferContext const &rhs);

  private:
};

#endif // ITRANSFERCONTEXT_HPP