#ifndef __COMPONENT_FULL_BODY_HPP__
#define __COMPONENT_FULL_BODY_HPP__

#include <string>
#include <vector>
#include <memory>
#include <initializer_list>

#include "WebComponentBase.hpp"

namespace finder::server::webComponents
{
    /// @brief Full body template of the HTML page
    class ComponentFullBody : public WebComponentBase
    {
        public:
            ComponentFullBody();

            /// @brief Construct a new ComponentFullBody object
            /// @param children List of children components
            ComponentFullBody(std::initializer_list<WebComponentBase> children);

            /// @brief Construct a new ComponentFullBody object
            /// @param children List of children components
            ComponentFullBody(std::vector<std::shared_ptr<WebComponentBase>> children);

            virtual ~ComponentFullBody() = default;

            /// @brief Render the component to HTML
            /// @return HTML string
            std::string render() override;

            /// @brief Get the name of the component
            std::string getComponentName() override;

            /// @brief Get the type of the component
            std::string getComponentType() override;

            /// @brief Get the HTML of the component
            std::string getComponentHTML() override;
    };
} // namespace finder::server::webComponents

#endif // __COMPONENT_FULL_BODY_HPP__