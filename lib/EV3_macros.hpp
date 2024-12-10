#define ABSL_RETURN_IF_ERROR(expr) \
    do {                           \
        boost::leaf::result<void> status = (expr); \
        if (!status) return status; \
    } while (0)
