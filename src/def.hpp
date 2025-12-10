#ifndef DEF_HPP_
#define DEF_HPP_

#include <memory>

template <typename T>
using sptr_t = std::shared_ptr<T>;

template <typename T, typename... Args>
sptr_t<T> mk_sptr(Args &&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

#ifdef PTEST
#include <chrono>

#define pstart() std::chrono::steady_clock::now()
#define pend(str, start)                                                                \
    do {                                                                                \
        auto now = std::chrono::steady_clock::now();                                    \
        double loadms = std::chrono::duration<double, std::milli>(now - start).count(); \
        TraceLog(LOG_INFO, "PTEST: %s: %lf", str, loadms);                              \
    } while(0)
#endif


#endif // DEF_HPP_
