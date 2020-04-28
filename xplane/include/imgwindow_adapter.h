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
#include "imgwindow.h"

/** 
 * Adapter class to adapt ImgWindow into ImguiWindow 
 * 
 * System only knows about an ImguiWindow class therefor we need to adapt the ImgWindow class using this adapter.
 */ 
class ImgWindowAdapter : ImgWindow
{
    private:
        //Window ojbect to adapt
        ImguiWindow* window;
    protected:
    public:
        /** 
        * Constructor
        *
        * @param window ImgWindow object to adapt to generic ImguiWindow object
        */
        ImgWindowAdapter(ImguiWindow* window);
};
