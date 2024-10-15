// #include <log4cplus/log4cplus.h>

// class ColorAppender : public log4cplus::helpers::SharedObject
// {
//     public:
//         // Set the layout for this appender

//         void setLayout(std::unique_ptr<log4cplus::Layout> layout);

//         // Set the filter chain on this Appender.

//         void setFilter(log4cplus::spi::FilterPtr f);

//         // Set the threshold LogLevel

//         void setThreshold(log4cplus::LogLevel th);

//         //This method performs threshold checks and invokes filters before delegating actual logging to the subclasses specific

//         void doAppend(const log4cplus::spi::InternalLoggingEvent& event);

//     private:
//         log4cplus::LogLevel threshold;
//         log4cplus::spi::FilterPtr filter;
//         std::unique_ptr<log4cplus::Layout> layout;
// };