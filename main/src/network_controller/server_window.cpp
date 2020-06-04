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
#include "network_controller/server_window.h"

ServerWindow::ServerWindow() : ImguiWindow("Start a server", 0, 0, 200, 200) {
	// THIS IS ABSURD
	std::cout << " constructing "<< this->getName() << std::endl;
}

void ServerWindow::onDraw() {
	if (this->connectionState == ConnectionState::NOT_CONNECTED) {
		ImGui::Text("Click on start to host a server.");
		if (ImGui::Button("Start")) {
			this->onStartClicked();
		}
	}
	else if (this->connectionState == ConnectionState::CONNECTING) {
		ImGui::Text("Connecting...");
	}
	else if (this->connectionState == ConnectionState::CONNECTED) {
		ImGui::Text("Connected");
	}
	else {
		ImGui::Text("No connection to report");
	}
}

void ServerWindow::setNetworkStateObserver(rxcpp::observable<ConnectionState>& connectionState){
	connectionState.subscribe([&](ConnectionState value) {
		this->connectionState = value;
	});
}

void ServerWindow::setOnStartClick(std::function< void()>&& onStartClicked) {
	this->onStartClicked = onStartClicked;
}

ServerWindow::~ServerWindow() {
	// THIS IS ABSURD
	std::cout << "Destructing " << this->getName() << std::endl;
}