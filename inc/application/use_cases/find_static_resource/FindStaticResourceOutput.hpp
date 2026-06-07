/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FindStaticResourceOutput.hpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 20:02:00 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/07 20:54:06 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FINDSTATICRESOURCEOUTPUT_HPP
#define FINDSTATICRESOURCEOUTPUT_HPP

class IResourceReader;

struct FindStaticResourceOutput
{
	IResourceReader *resourceReader;
};

#endif // FINDSTATICRESOURCEOUTPUT_HPP