#pragma once
#include <memory>
class widget
{
private:
    std::unique_ptr<int> data;
    int iweight;
public:
    widget(const int size) : iweight (size)
    {
    }
    void do_something() { data = std::make_unique<int>(iweight); }
    int weight() const { return iweight; }
};
