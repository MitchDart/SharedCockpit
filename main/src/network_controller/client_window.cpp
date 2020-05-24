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
#include "network_controller/client_window.h"

ClientWindow::ClientWindow(rxcpp::observable<ConnectionState>& connectionState) : ImguiWindow("Connect to server", 0, 0, 200, 200) {
	connectionState.subscribe([&](ConnectionState value) {
		this->connectionState = value;
	});
}

void ClientWindow::onDraw() {
	if (connectionState == ConnectionState::NOT_CONNECTED) {
		ImGui::Text("Connect to server");
		ImGui::InputTextWithHint("IP Address", "192.168.0.1", this->ipAddress, IM_ARRAYSIZE(this->ipAddress));
		if (ImGui::Button("Connect")) {
			this->onConnectedClicked(this->ipAddress);
		}
	}
	else if (connectionState == ConnectionState::CONNECTING) {
		ImGui::Text("Connecting...");
	}
	else if (connectionState == ConnectionState::CONNECTED) {
		ImGui::Text("Connected");
	}
}

void ClientWindow::setOnConnectedClicked(std::function< void(char* ip)>&& onConnectedClicked) {
	this->onConnectedClicked = onConnectedClicked;
}