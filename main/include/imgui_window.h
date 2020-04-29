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

#include <string>

/** 
 * Abstract IMGUI window used to show Dead ImGUI windows in any environment
 * 
 * This class is used to represent a window and should be created via the environment.
 */ 
class ImguiWindow {
    public:
        ImguiWindow(std::string name, int width, int height, int x, int y);
        virtual ~ImguiWindow() {}

        //Inline setters and getters
        int getHeight() const { return height; }
        int getWidth() const { return width; }
        int getX() const { return x; }
        int getY() const { return y; }
        std::string getName() const { return name; }
        void setPosition(int x, int y) { this->x = x; this->y = y; }
        void setSize(int width, int height) { this->width = width; this->height = height; }

        /** 
        * OnDraw is called every frame for the window.
        *
        * This function should be used to draw all UI elements on the window.
        */
        virtual void onDraw() const = 0;
    protected:
    private:
        std::string name;
        int width;
        int height;
        int x;
        int y;
};
