#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H

namespace snake
{
    class NonCopyable
    {
    public:
        NonCopyable() = default;
        NonCopyable(const NonCopyable&) = delete;
        NonCopyable& operator=(const NonCopyable&) = delete;
    };
}

#endif
