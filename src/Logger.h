#pragma once

#include <fstream>
#include <mutex>
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;

class Logger
{
public:
    Logger(const char *fileName)
            : m_ofs(fileName)
    {

    }

    Logger(Logger &o) = delete;

    ~Logger()
    {
        m_ofs.close();
    }

    template<class ...T>
    void operator()(T... args)
    {
        m_mutex.lock();
        stringstream sstr; // for one line

        using namespace chrono;

        // TODO: millisecond
        auto now_c = system_clock::to_time_t(system_clock::now());
        sstr << put_time(localtime(&now_c), "%Y-%m-%d %H:%M:%S %T ");


        // since initializer lists guarantee sequencing, this can be used to
        // call a function on each element of a pack, in order:
        int dummy[sizeof...(T)] = {(sstr << args << " ", 0)...};

        m_ofs << sstr.str() << '\n';

        if (m_willCout){
            cout << sstr.str() << "\n";
        }

        m_mutex.unlock();
    }
    void setCout(bool v){m_willCout=v;}

private:
    ofstream m_ofs;
    mutex m_mutex;
    bool m_willCout = true;
};
