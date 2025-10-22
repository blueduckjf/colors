#pragma once

namespace Colors { namespace Detail { 

    template <typename T>
    T max(const T& a)
    {
        return a;
    }

    template <typename T, typename... Args>
    T max(const T& a, const Args&... args)
    {
        T maxRest = max(args...);
        return a > maxRest ? a : maxRest;
    }

    template <typename T>
    T min(const T& a)
    {
        return a;
    }

    template <typename T, typename... Args>
    T min(const T& a, const Args&... args)
    {
        T minRest = min(args...);
        return a < minRest ? a : minRest;
    }

} } 