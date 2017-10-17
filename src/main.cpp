//
// Created by RHZhang on 2017/9/14.
//
#include "Precompiled.h"
#include "MicMatrixCreator.h"

Logger logger("Mic.Array.Demo.log");


int main(void)
{
    logger("Main", "begin");

    MicMatrixCreator mc;
    mc.Start();

    logger("Main", "end");
    return 0;
}
