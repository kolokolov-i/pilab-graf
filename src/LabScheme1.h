#pragma once

#include "PortRecord.h"

#include <vector>

class LabScheme1
{
public:
    LabScheme1();
    ~LabScheme1();

    std::vector<PortRecord> ports;
    void process();
};