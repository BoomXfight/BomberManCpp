#pragma once
#include <string>

class Layer
{
public:
    virtual void render() = 0;
    virtual void update() = 0;
    std::string getType() {return mType;};

protected:
    virtual ~Layer();
    std::string mType;
};
