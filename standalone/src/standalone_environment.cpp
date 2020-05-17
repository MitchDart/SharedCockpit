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
#include <chrono>
#include "utils.h"

StandaloneEnvironment::StandaloneEnvironment(rxcpp::schedulers::run_loop *rlp)
    : Environment(rlp) {
    //Create standalone window
    this->standAloneWindow = new StandaloneWindow("Standalone Simulation", 500, 200, 0, 0);
    this->createWindow(this->standAloneWindow);
    this->standAloneWindow->setOnSimulationRestartListener([&]() {
        this->restartSimulation();
    });
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
    DataRef* dataRef = new DataRef(ref, DATA_REF_DOUBLE);
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

    //Check if simulation file is loaded
    if (this->recordingFile != 0) {
        std::string line = "";
        if (getline(*this->recordingFile, line)) {
            //We have another line to parse in thex file
            this->recordingDataRefData = Utils::split(line, ",");
            //Get millis
            auto millis = std::stoll(this->recordingDataRefData[0]);
            auto current = std::chrono::steady_clock::now();
            auto elapsed_millis = std::chrono::duration_cast<std::chrono::milliseconds>(current - this->recordingElapsedTime);
            //Simulate thread speed
            std::this_thread::sleep_for(std::chrono::milliseconds(millis - elapsed_millis.count()));

            //Figure out what type of data ref it is
            for (int i = 0; i < this->dataRefs.size(); i++) {
                const DataRef* currentRef = this->dataRefs[i];
                //Search for this DataRef
                auto itr = std::find(this->recordingDataRefHeaders.begin(), this->recordingDataRefHeaders.end(), currentRef->getRef());
                if (itr != this->recordingDataRefHeaders.end()) {
                    //We have found a matching dataRef
                    int index = std::distance(recordingDataRefHeaders.begin(), itr);
                    auto value = this->recordingDataRefData[index];

                    //Convert to correct type and update stream
                    switch (currentRef->getDataRefType()) {
                    case DataRefType::DATA_REF_FLOAT: {
                        currentRef->updateFloatValue(std::stof(value));
                        break;
                    }
                    case DataRefType::DATA_REF_DOUBLE: {
                        currentRef->updateDoubleValue(std::stod(value));
                        break;
                    }
                    }
                }
            }

            this->standAloneWindow->setFrameCount(this->frameCounter++);
        }
        else {
            this->recordingFile->close();
            delete this->recordingFile;
            this->recordingFile = 0;
        }
    }
}

void StandaloneEnvironment::onLaunch() {
}
void StandaloneEnvironment::onExit() {
    if (this->recordingFile != 0 && this->recordingFile->is_open()) {
        this->recordingFile->close();
        delete this->recordingFile;
        this->recordingFile = 0;
    }
}

void StandaloneEnvironment::restartSimulation() {
    if (this->recordingFile != 0 && this->recordingFile->is_open()) {
        this->recordingFile->close();
        delete this->recordingFile;
        this->recordingFile = 0;
    }

    auto recordingFile = new std::ifstream("simulation/recording.csv");
    std::string line = "";
    if (getline(*recordingFile, line)) {
        this->recordingDataRefHeaders = Utils::split(line, ",");
        this->recordingFile = recordingFile;
        this->recordingElapsedTime = std::chrono::steady_clock::now();
    }

    this->frameCounter = 0;
}