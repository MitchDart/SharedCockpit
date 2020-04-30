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

#include "first_window.h"

void FirstWindow::onDraw() const {
    auto &io = ImGui::GetIO();
    ImGui::Text("ImGui screen size: width = %f  height = %f", io.DisplaySize.x, io.DisplaySize.y);
    ImGui::Text("Want capture mouse: %i", io.WantCaptureMouse);
    ImGui::Text("Want capture keyboard: %i", io.WantCaptureKeyboard);
    ImGui::Text("Is any items active or hovered: %i", ImGui::IsAnyItemHovered());

    ImGui::Text("This is some specific text just to make sure!");
    ImGui::Text("Some ints %i", viewModel->getValue());
    ImGui::Text("Some char %c", viewModel->getChar());
}
