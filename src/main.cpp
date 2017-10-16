//
// Created by RHZhang on 2017/9/14.
//
#include "Precompiled.h"
#include "MicMatrixCreator.h"

Logger gLogger("Mic.Array.Demo.log");


int main(void)
{
    gLogger("Main", "begin");

#ifdef RPI3_MATRIX_CREATOR
    MicMatrixCreator mc;
    mc.Start();
#endif

    gLogger("Main", "end");
    return 0;
}
