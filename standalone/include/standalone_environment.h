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
#include <vector>
#include <memory>
#include "environment.h"
#include "imgui.h"
#include "dataref.h"

/** 
 * Standalone Environment
 * 
 * This class implements the system environment for the standalone target and context.
 */ 
class StandaloneEnvironment : public Environment
{
    private:
        //List of windows currently active
        std::vector<ImguiWindow*> windows;
        
        //List of datarefs 
        std::vector<const DataRef*> dataRefs;
    protected:
        //Override
        void createWindow(ImguiWindow* window) override;
    public:
        // Constructor
        StandaloneEnvironment(rxcpp::schedulers::run_loop* rlp);
        ~StandaloneEnvironment();

        DataRef* buildDataRef(std::string ref) override;

        void subscribeToDataRef(const DataRef* dataRef) override;

        void unSubscribeToDataRef(const DataRef* dataRef) override;


        /**
         * Main loop is called for each event loop run from main.cpp
         */
        void mainLoop();

        void onLaunch() override;
        void onExit() override;
};
