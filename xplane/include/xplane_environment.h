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
#include "environment.h"
#include <vector>
#include "imgwindow_adapter.h"
#include "imgwindow.h"
#include "rx.hpp"
#include "XPLMDataAccess.h"
#include "xplane_dataref.h"

/** 
 * XPlane Environment
 * 
 * This class implements the system environment for the xplane target and context.
 */ 
class XPlaneEnvironment : public Environment
{
    private:
        //List of windows currently active
        std::vector<const ImgWindow*> windows;
        std::vector<const XPlaneDataRef*> dataRefs;
        rxcpp::schedulers::run_loop* rlp;
    protected:
    public:
        //Override
        void createWindow(ImguiWindow* window) override;
        DataRef* buildDataRef(std::string ref) override;

        void subscribeToDataRef(const DataRef* dataRef) override;
        void unSubscribeToDataRef(const DataRef* dataRef) override;

        void onLaunch() override;
        void onExit() override;

        //Constructor
        XPlaneEnvironment();
        ~XPlaneEnvironment();

        /**
         * Main loop is called for each event loop run from main.cpp
         */
        void mainLoop();
};