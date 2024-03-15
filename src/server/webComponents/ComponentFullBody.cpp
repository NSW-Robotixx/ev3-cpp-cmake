#include "ComponentFullBody.hpp"

namespace finder::server::webComponents
{
    ComponentFullBody::ComponentFullBody()
    {
    }

    ComponentFullBody::ComponentFullBody(std::initializer_list<WebComponentBase> children)
    {
        for (auto child : children)
        {
            addChild(std::make_shared<WebComponentBase>(child));
        }
    }

    ComponentFullBody::ComponentFullBody(std::vector<std::shared_ptr<WebComponentBase>> children)
    {
        for (auto child : children)
        {
            addChild(child);
        }
    }

    std::string ComponentFullBody::render()
    {
        std::string rendered = "<!DOCTYPE html><html><head><title>Finder</title></head><body>";
        for (auto child : WebComponentBase::getChildren())
        {
            rendered += child->render();
        }
        rendered += "</body></html>";
        return rendered;
    }

    std::string ComponentFullBody::getComponentName()
    {
        return "ComponentFullBody";
    }

    std::string ComponentFullBody::getComponentType()
    {
        return "HTML";
    }

    std::string ComponentFullBody::getComponentHTML()
    {
        return render();
    }
} // namespace finder::server::webComponents