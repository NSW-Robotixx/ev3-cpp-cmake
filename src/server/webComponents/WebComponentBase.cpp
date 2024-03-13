#include "WebComponentBase.hpp"

namespace finder::server::webComponents
{
    int WebComponentBase::idCounter = 0;

    WebComponentBase::WebComponentBase()
    {
        id = idCounter++;
    }

    void WebComponentBase::addChild(std::shared_ptr<WebComponentBase> child)
    {
        children.push_back(child);
    }

    void WebComponentBase::removeChild(std::shared_ptr<WebComponentBase> child)
    {
        children.erase(std::remove(children.begin(), children.end(), child), children.end());
    }

    std::vector<std::shared_ptr<WebComponentBase>> WebComponentBase::getChildren()
    {
        return children;
    }
} // namespace finder::server::webComponents