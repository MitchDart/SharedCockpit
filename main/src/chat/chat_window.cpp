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

#include "chat_window.h"

void ChatWindow::onDraw()
{
  auto &io = ImGui::GetIO();

  ImGui::BeginChild("Chat");

  ImGui::ListBoxHeader("");
  for (int i = 0; i < this->messages.size(); i++) {
    ImGui::Selectable((this->messages)[i].c_str(), false,
                      ImGuiSelectableFlags_Disabled);
  }
  ImGui::ListBoxFooter();

  ImGui::Text("Message");
  ImGui::InputTextWithHint("", "", this->messageInput, IM_ARRAYSIZE(this->messageInput));
  ImGui::SameLine();
  if (ImGui::Button("Send")) {
    std::string message(messageInput);
    this->onMessage(message);
  }

  ImGui::EndChild();
}
