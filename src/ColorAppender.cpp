// #include "ColorAppender.hpp"
// #include <Logger.hpp>
// #include <iostream>

// void ColorAppender::setLayout(std::unique_ptr<log4cplus::Layout> layout)
// {
//     this->layout = std::move(layout);
// }

// void ColorAppender::setFilter(log4cplus::spi::FilterPtr f)
// {
//     this->filter = f;
// }

// void ColorAppender::setThreshold(log4cplus::LogLevel th)
// {
//     this->threshold = th;
// }

// void ColorAppender::doAppend(const log4cplus::spi::InternalLoggingEvent &event)
// {
//     switch (event.getLogLevel())
//     {
//     case log4cplus::DEBUG_LOG_LEVEL:
//         // ::finder::log::Logger::debug(event.getMessage());
//         break;
    
//     default:
//         break;
//     }
// }