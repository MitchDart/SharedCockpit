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

#include "standalone_environment.h"
#include <iostream>
#include <thread>
#include <algorithm>
#include <type_traits>

StandaloneEnvironment::StandaloneEnvironment(rxcpp::schedulers::run_loop *rlp)
    : Environment(rlp) {
    
}

StandaloneEnvironment::~StandaloneEnvironment()
{
    //Free each window
    for(const auto &window : windows) {
        delete window;
    }
    //Clear vector to prevent seg faults
    windows.clear();
}

void StandaloneEnvironment::createWindow(ImguiWindow* window)
{
    //If we already have this window then don't add it again.
    for(const auto &existingWindow : windows)
        if(existingWindow == window)
            return;

    windows.push_back(window);
}

DataRef* StandaloneEnvironment::buildDataRef(std::string ref) {
    //This part will usually first query the type from XPlane and then create the object
    DataRef* dataRef = new DataRef(ref, DATA_REF_FLOAT);
    return dataRef;
}

void StandaloneEnvironment::subscribeToDataRef(const DataRef* dataRef) {

    //If the dataref is already inside the list then dont bother checking again
    for(int i = 0; i < this->dataRefs.size(); i++) {
        if(this->dataRefs[i] == dataRef)
            return;
    }
        
    this->dataRefs.push_back(dataRef);
}

void StandaloneEnvironment::unSubscribeToDataRef(const DataRef* dataRef) {
    for (int i = 0; i < this->dataRefs.size(); i++) {
        if (this->dataRefs[i] == dataRef)
            this->dataRefs.erase(this->dataRefs.begin() + i);
    }
}

static float count = 0.0f;
void StandaloneEnvironment::mainLoop()
{
    for(auto &window : windows) {
        //Setup sizes and position
        const auto size = ImVec2(window->getWidth(), window->getHeight());
        const auto position = ImVec2(window->getX(), window->getY());

        ImGui::SetNextWindowPos(position, ImGuiCond_Once);
        ImGui::SetNextWindowSize(size, ImGuiCond_Once);
        ImGui::Begin(window->getName().c_str());
        this->rlp->dispatch();
        window->onDraw();
        ImGui::End();
    }

    //Figure out what type of data ref it is
    for(int i = 0; i < this->dataRefs.size(); i++) {
        const DataRef* currentRef = this->dataRefs[i];
        switch(currentRef->getDataRefType()) {
            case DataRefType::DATA_REF_FLOAT : {
                currentRef->updateFloatValue(count++);
                break;
            }
        }
    }
}

void StandaloneEnvironment::onLaunch() {
}
void StandaloneEnvironment::onExit() {
}