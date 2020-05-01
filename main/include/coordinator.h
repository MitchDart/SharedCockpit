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
#include "viewmodel.h"
#include "rx.hpp"

/** 
 * Coordinator is responsible for coordinating the flow of the application
 * 
 * Coordinator is created by a runtime and provided an environment context. Coordinator is then started by onStart.
 * It is the responsibility of the coordinator to decide flow between start and stop and hold the overall state 
 * of the application.
 */ 
class Coordinator {
    private:
        Environment* environment;
        ViewModel* viewModel;
    protected:
    public:
        /** 
        * Cooridnator constructor
        *
        * Provides environment object which should be stored and used to interface with the runtime.
        *
        * @param environment Runtime environment
        */
        Coordinator(Environment* environment);

        /**
         * Called when the runtime launches.
         */
        void onStart();

        /**
         * Called when the runtime is destroyed.
         */
        void onStop();
};