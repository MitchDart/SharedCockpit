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

#include "imgwindow_adapter.h"

ImgWindowAdapter::ImgWindowAdapter(const ImguiWindow* window) : ImgWindow() {
    this->window = window;
    Init(window->getWidth(), window->getHeight(), window->getX(), window->getY());
}

void ImgWindowAdapter::BuildInterface() {
    this->window->onDraw();
}

ImgWindowAdapter::~ImgWindowAdapter() {
    delete this->window;
    this->window = 0;
}