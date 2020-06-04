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
#include <string>
#include <functional>
#include <memory>
#include "imgui.h"
#include "rx.hpp"
#include "network_state_enums.h"

/**
 * Oneliner description of class.
 *
 * Paragraph explaining how the class is used and what its purpose is in more detail.
 */
class ServerWindow : public ImguiWindow {
private:
    std::function< void()> onStartClicked;
    ConnectionState connectionState;
protected:
    void onDraw() override;
public:
    ServerWindow();
    void setOnStartClick(std::function< void()>&& onStartClicked);
    void setNetworkStateObserver(rxcpp::observable<ConnectionState>& connectionState);

    ~ServerWindow();
};