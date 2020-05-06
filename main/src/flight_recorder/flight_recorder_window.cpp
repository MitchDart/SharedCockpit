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

#include "flight_recorder/flight_recorder_window.h"

FlightRecorderWindow::FlightRecorderWindow(std::vector<DataRef*>* dataRef) : ImguiWindow("Flight Data Recording", 500, 500, 0, 0) {
    this->onRefAddLambda = [](std::string ref) {};
    this->dataRefs = dataRef;
}   

FlightRecorderWindow::~FlightRecorderWindow() {
}

void FlightRecorderWindow::onDraw() {
    ImGui::Text("Add DataRefs to record.");
    ImGui::InputTextWithHint("", "sim/flightmodel/position/local_x", this->dataRefInput, IM_ARRAYSIZE(this->dataRefInput));
    if (ImGui::Button("Add DataRef")) {
        std::string ref(dataRefInput);
        onRefAddLambda(ref);
    }
    ImGui::SameLine();
    if (ImGui::Button("Clear")) {
        onRefClearLambda();
    }
    ImGui::ListBoxHeader("");
    for (int i = 0; i < this->dataRefs->size(); i++) {
        ImGui::Selectable((*this->dataRefs)[i]->getRef().c_str(), false, ImGuiSelectableFlags_Disabled);
    }
    ImGui::ListBoxFooter();
}

void FlightRecorderWindow::setFrameValue(float frameValue) {
    this->frameValue = frameValue;
}

void FlightRecorderWindow::setOnAddRefListener(std::function< void(std::string) >&& lambda)
{
    this->onRefAddLambda = lambda;
}

void FlightRecorderWindow::setOnClearListener(std::function< void() >&& lambda) {
    this->onRefClearLambda = lambda;
}