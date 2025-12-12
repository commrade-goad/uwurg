#ifndef DEF_HPP_
#define DEF_HPP_

#include <memory>

template <typename T>
using sptr_t = std::shared_ptr<T>;

template <typename T, typename... Args>
sptr_t<T> mk_sptr(Args &&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

#define PTEST
#ifdef PTEST
#include <chrono>

static std::chrono::time_point<std::chrono::steady_clock> pstart() {
    return std::chrono::steady_clock::now();
}
#define pend(str, start)                                                                \
    do {                                                                                \
        auto now = std::chrono::steady_clock::now();                                    \
        double loadms = std::chrono::duration<double, std::milli>(now - start).count(); \
        TraceLog(LOG_INFO, "PTEST: %s: %lf ms", str, loadms);                           \
    } while(0)
#endif

#endif // DEF_HPP_
