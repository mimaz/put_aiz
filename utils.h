#ifndef __UTILS_H
#define __UTILS_H

template<typename _T>
std::ostream &operator<<(std::ostream &os, const std::vector<_T> &vec)
{
    os << "[";

    for (size_t i = 0; i < vec.size(); i++)
    {
        if (i > 0)
            os << ", ";

        os << vec[i];
    }

    return os << "]";
}

#endif
