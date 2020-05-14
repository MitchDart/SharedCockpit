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
#include <vector>
#include <functional>
#include "dataref.h"

/** 
 * First demo window
 * 
 * 
 */ 
class FlightRecorderWindow : public ImguiWindow
{
    private:
        float frameValue;
        char dataRefInput[100] = "";

        std::function< void(std::string) > onRefAddLambda;
        std::function< void() > onRefClearLambda;
        std::function< void()> onRecordLambda;
        std::function< void()> onStopRecordLambda;
        std::vector<DataRef*>* dataRefs;
        bool* isRecording;
    protected:
        void onDraw() override;
    public:
        FlightRecorderWindow(std::vector<DataRef*>* dataRefs, bool* isRecording);
        ~FlightRecorderWindow() override;

        void setFrameValue(float frameValue);

        void setOnAddRefListener(std::function< void(std::string) >&& lambda);
        void setOnClearListener(std::function< void() >&& lambda);
        void setOnRecordListener(std::function<void()>&& lambda);
        void setOnStopRecordListener(std::function<void()>&& lambda);
};