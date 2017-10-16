#pragma once

template <typename T>
class Singleton
{
public:
    static T* Get()
    {
        static T *instance = nullptr;
        if (instance == nullptr) {
            instance = new T;
        }
        return instance;
    }

protected:
    virtual ~Singleton() { }
};
