#define ABSL_RETURN_IF_ERROR(expr) \
    do {                           \
        absl::Status status = (expr); \
        if (!status.ok()) return status; \
    } while (0)
