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

void StandaloneEnvironment::createWindow(const ImguiWindow* window)
{
    //If we already have this window then don't add it again.
    for(const auto &existingWindow : windows)
        if(existingWindow == window)
            return;

    windows.push_back(window);
}

const rxcpp::observable<> StandaloneEnvironment::observeDataRef(DataRef* dataref) {
	return dataref->toObservable().subscribe_on(rxcpp::observe_on_run_loop(*(this->rlp))).publish().ref_count();
}

static float count = 0.0f;
void StandaloneEnvironment::mainLoop()
{
    for(const auto &window : windows) {
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

    FlightDataRecordingFrame frame;
    frame.value = count++;
    flightRecorderSubject.get_subscriber().on_next(frame);
}

void StandaloneEnvironment::onLaunch() {
}
void StandaloneEnvironment::onExit() {
    flightRecorderSubject.get_subscriber().on_completed();
}