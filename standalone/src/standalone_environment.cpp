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

StandaloneEnvironment::StandaloneEnvironment()
{
    
}

void StandaloneEnvironment::createWindow(const ImguiWindow* window)
{
    //If we already have this window then don't add it again.
    for(const auto &existingWindow : windows)
        if(existingWindow == window)
            return;

    windows.push_back(window);
}

void StandaloneEnvironment::mainLoop()
{
    for(const auto &window : windows) {
        //Setup sizes and position
        const auto size = ImVec2(window->getWidth(), window->getHeight());
        const auto position = ImVec2(window->getX(), window->getY());

        ImGui::SetNextWindowPos(position, ImGuiCond_Once);
        ImGui::SetNextWindowSize(size, ImGuiCond_Once);
        ImGui::Begin(window->getName().c_str());
        window->onDraw();
        ImGui::End();
    }
}