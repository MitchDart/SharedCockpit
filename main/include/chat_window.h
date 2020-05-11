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
#include "chat_view_model.h"

/** 
 * First demo window
 * 
 * 
 */ 
class ChatWindow : public ImguiWindow
{
    private:
        ChatViewModel* viewModel;
    protected:
        void onDraw() const override;
    public:
        ChatWindow(std::string name, int width, int height, int x, int y, ChatViewModel* viewModel) : ImguiWindow(name, width, height, x, y) {
            this->viewModel = viewModel;
        };
        ~ChatWindow() override {};
};