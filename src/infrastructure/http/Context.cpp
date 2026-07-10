/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Context.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 05:05:13 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/06 01:45:43 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/Context.hpp"
#include "application/ports/IResourceReader.hpp"

namespace http {
Context::Input::Input(void) : buf(), state() {}

void Context::Input::reset(void)
{
	buf.clear();
	state.reset();
}

Context::Stream::Stream(void) : buf(), state(), localRedirDepth(0) {}

void Context::Stream::reset(void)
{
	buf.clear();
	state.reset();
	localRedirDepth = 0;
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

void Context::reset(void)
{
	input.reset();
	stream.reset();
	output.reset();
}

} // namespace http
