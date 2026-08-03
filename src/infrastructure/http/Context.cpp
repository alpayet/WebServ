/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Context.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 05:05:13 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/03 16:16:51 by ludebion         ###   ########.fr       */
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

Context::Output::Output(void) : state(), response(), reader(NULL)
{}

Context::Output::~Output(void) { delete reader; }

void Context::Output::reset(void)
{
	state.reset();
	response.reset();
	delete reader;
	reader = NULL;
}

void Context::reset(void)
{
	input.reset();
	stream.reset();
	output.reset();
}

} // namespace http
