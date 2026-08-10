/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResource.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 21:50:23 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/09 22:14:12 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTEDYNAMICRESOURCEPRESENTER_HPP
#define EXECUTEDYNAMICRESOURCEPRESENTER_HPP

#include "application/ports/IDynamicResourceExecutor.hpp"
#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResource.hpp"
#include <string>
#include <vector>

namespace http {
namespace presenter {
class ExecuteDynamicResource
    : public app::useCase::ExecuteDynamicResource::IOutputPort {
public:
  struct ViewModel {
    app::StreamResources stream_resources;
  };

public:
  ExecuteDynamicResource(void) {}
  virtual ~ExecuteDynamicResource(void) {}

  ViewModel const &getViewModel(void) const;

  virtual void presentStream(app::StreamResources resources);

private:
  ExecuteDynamicResource(ExecuteDynamicResource const &src);
  ExecuteDynamicResource &operator=(ExecuteDynamicResource const &rhs);

  ViewModel _viewModel;
};
} // namespace presenter

} // namespace http

#endif // EXECUTEDYNAMICRESOURCEPRESENTER_HPP