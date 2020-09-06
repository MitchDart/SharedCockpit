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
#include "rx.hpp"
#include <string>
#include <functional>
#include "frames.h"
#include "dataref.h"
#include <imgui_logger.h>
#include <EventBus\EventBus.cpp>

/** 
 * Abstract environment representing a runtime environment
 * 
 * Environment abstract class is implemented by each runtime project to represent itself in an abstract way.
 * All context information should be provided in an abstract way through this interface. Components inside main
 * project will be injected with a single instance of this environment and should be used as the only way to
 * communicate with relevant runtimes.
 */ 
class Environment {
    protected:
    public:
        Environment(rxcpp::schedulers::run_loop* rlp) { 
            this->rlp = rlp; 
        }

        /** 
        * Creates a ImguiWindow to display
        *
        * Use this method to create a window at the relative environment with dimentions and coordinates.
        * The environment will take the responsibility to delete the windows.
        * 
        * @param window Window object to create
        */
        virtual void createWindow(ImguiWindow* window) = 0;

        /**
        * Build a DataRef object
        *
        * This will create a DataRef object which needs to be destroyed when no longer needed
        *
        * @param dataRef DataRef object to subscribe to
        */
        virtual DataRef* buildDataRef(std::string ref) = 0;

        /** 
        * Subscribe to a dataref
        *
        * This will create an abstract dataref subscription
        * 
        * @param dataRef DataRef object to subscribe to
        */
        virtual void subscribeToDataRef(const DataRef* dataRef) = 0;


        virtual void unSubscribeToDataRef(const DataRef* dataRef) = 0;

        virtual void onLaunch() = 0;
        virtual void onExit() = 0;

        static ImguiLogger* logger;

        rxcpp::schedulers::run_loop* rlp;
        EventBus<EVENT_INFO> standaloneBus;

    private:
};
