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

/** 
 * First demo window
 * 
 * 
 */ 
class RecordingWindow : public ImguiWindow
{
    private:
        float frameValue;
    protected:
        void onDraw() const override;
    public:
        RecordingWindow() : ImguiWindow("Flight Data Recording", 500, 500, 0, 0) {};
        ~RecordingWindow() override {};

        void setFrameValue(float frameValue);
};