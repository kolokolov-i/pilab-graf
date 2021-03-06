#pragma once

#include "../gui/ImagePort.h"
#include "../ipf/IPF.h"
#include "../ipf/ImageRecord.h"
#include "../ipf/MatrixD.h"
#include "../ipf/PixbufUtil.h"
#include "../ipf/MatrixUtil.h"

#include <gtkmm.h>

#include <vector>
#include <memory>

class LabScheme1
{
public:
    LabScheme1();
    ~LabScheme1();
    void loadImage(std::string filePath);
    void updatePorts();
    ImagePort getSourcePort();
    void process();

    std::vector<ImagePort> ports;

private:
    IPF::ImageRecord sourceRecord;
    std::vector<IPF::ImageRecord> imageTable;
    std::string filePath;
};