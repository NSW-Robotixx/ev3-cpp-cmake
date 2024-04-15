#ifndef __COMPONENT_FULL_BODY_HPP__
#define __COMPONENT_FULL_BODY_HPP__

#include <string>
#include <vector>
#include <memory>
#include <initializer_list>

#include "WebComponentBase.hpp"

namespace finder::server::webComponents
{
    class ComponentFullBody : public WebComponentBase
    {
        public:
            ComponentFullBody();
            ComponentFullBody(std::initializer_list<WebComponentBase> children);
            ComponentFullBody(std::vector<std::shared_ptr<WebComponentBase>> children);
            virtual ~ComponentFullBody() = default;

            std::string render() override;
            std::string getComponentName() override;
            std::string getComponentType() override;
            std::string getComponentHTML() override;
    };
} // namespace finder::server::webComponents

#endif // __COMPONENT_FULL_BODY_HPP__