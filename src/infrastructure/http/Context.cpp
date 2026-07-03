/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Context.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 05:05:13 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/03 20:21:40 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/Context.hpp"
#include "application/ports/IResourceReader.hpp"

namespace http {

void Context::reset(void)
{
	input.reset();
	output.reset();
}

Context::Input::Input(void) : buf(), state(), isRequestComplete(false) {}

void Context::Input::reset(void)
{
	buf.clear();
	state.reset();
	isRequestComplete = false;
}

Context::Output::Output(void) : buf(), state(), response(), reader(NULL), isResponseComplete(false)
{}

Context::Output::~Output(void) { delete reader; }

void Context::Output::reset(void)
{
	buf.clear();
	state.reset();
	response.reset();
	delete reader;
	reader = NULL;
	isResponseComplete = false;
}

} // namespace http
