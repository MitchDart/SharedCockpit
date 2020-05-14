/*
* SharedCockpit
* See LICENSE file at the top of the source tree.
*
* This product includes software developed by the
* SharedCockpit Project (https://github.com/MitchDart/SharedCockpit/).
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*/

#include "xplane_environment.h"

XPlaneEnvironment::XPlaneEnvironment() : Environment(rlp) {
    rlp = new rxcpp::schedulers::run_loop();
}

XPlaneEnvironment::~XPlaneEnvironment()
{
    //Free each window
    for(const auto &window : windows) {
        delete window;
    }
    //Clear vector to prevent seg faults
    windows.clear();

    delete rlp;
}

void XPlaneEnvironment::createWindow(ImguiWindow* window)
{
    const auto adapter = new ImgWindowAdapter(window);
    //Store window for now
    windows.push_back(adapter);
    adapter->SetVisible(true);
}

DataRef* XPlaneEnvironment::buildDataRef(std::string ref) {
    auto xplDataRef = XPLMFindDataRef(ref.c_str());
    if (xplDataRef == NULL) {
        return 0;
    }

    DataRefType type;

    switch (XPLMGetDataRefTypes(xplDataRef)) {
    case xplmType_Float: {
        type = DATA_REF_FLOAT;
        break;
    }
    case (xplmType_Float | xplmType_Double): {
        type = DATA_REF_DOUBLE;
        break;
    }
    default: {
        return 0;
    }
    }

    XPlaneDataRef* dataRef = new XPlaneDataRef(xplDataRef, ref, type);
    return dataRef;
}

void XPlaneEnvironment::subscribeToDataRef(const DataRef* dataRef) {
    const XPlaneDataRef* xplDataRef = static_cast<const XPlaneDataRef*>(dataRef);

    //If the dataref is already inside the list then dont bother checking again
    for (int i = 0; i < this->dataRefs.size(); i++) {
        if (this->dataRefs[i] == dataRef)
            return;
    }

    this->dataRefs.push_back(xplDataRef);
}

void XPlaneEnvironment::unSubscribeToDataRef(const DataRef* dataRef) {
    for (int i = 0; i < this->dataRefs.size(); i++) {
        if (this->dataRefs[i] == dataRef)
            this->dataRefs.erase(this->dataRefs.begin() + i);
    }
}

void XPlaneEnvironment::onLaunch() {

}

void XPlaneEnvironment::onExit() {

}

void XPlaneEnvironment::mainLoop() {
    //Figure out what type of data ref it is
    for (int i = 0; i < this->dataRefs.size(); i++) {
        const XPlaneDataRef* currentRef = static_cast<const XPlaneDataRef*>(this->dataRefs[i]);
        switch (currentRef->getDataRefType()) {
        case DataRefType::DATA_REF_FLOAT: {
            float value = XPLMGetDataf(currentRef->getXPlaneDataRef());
            currentRef->updateFloatValue(value);
            break;
        }
        case DataRefType::DATA_REF_DOUBLE: {
            double value = XPLMGetDatad(currentRef->getXPlaneDataRef());
            currentRef->updateDoubleValue(value);
            break;
        }
        }
    }

    this->rlp->dispatch();
}