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

#pragma once
#include "imgui_window.h"
#include "imgui.h"
#include <functional>
#include "standalone_window.h"

/**
 * Oneliner description of class.
 *
 * Paragraph explaining how the class is used and what its purpose is in more detail.
 */
class StandaloneWindow : public ImguiWindow {
    private:
        std::function<void()> onSimulationRestart;
        int frameCount = 0;
    protected:
        void onDraw() override;
    public:
        StandaloneWindow(std::string name, int width, int height, int x, int y) : ImguiWindow(name, width, height, x, y) {};
        ~StandaloneWindow() override;
        void setOnSimulationRestartListener(std::function<void()>&& onSimulationRestart);
        void setFrameCount(int count);
};