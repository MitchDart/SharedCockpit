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

#include "standalone_window.h"

StandaloneWindow::~StandaloneWindow() {
}

void StandaloneWindow::setOnSimulationRestartListener(std::function<void()>&& onSimulationRestart) {
    this->onSimulationRestart = onSimulationRestart;

}

void StandaloneWindow::onDraw() {
    ImGui::Text("Current frame: %i",frameCount);
    if (ImGui::Button("(Re)Start Simulation")) {
        onSimulationRestart();
    }
}

void StandaloneWindow::setFrameCount(int count) {
    this->frameCount = count;
}

