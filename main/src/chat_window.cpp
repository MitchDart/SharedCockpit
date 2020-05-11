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

void ChatWindow::onDraw() const
{
  auto &io = ImGui::GetIO();

  ImGui::BeginChild("Main");
  ImGui::Text("Amount of user %i", viewModel->getMessageCount());
  ImGui::TextColored(ImVec4(1, 1, 0, 1), "Messages for %s",
                     viewModel->getName().data());
  vector<string> messages = viewModel->getMessagesFrom(viewModel->getName());
  ImGui::BeginChild("Scrolling", ImVec2(-1, this->getHeight() / 2), true,
                    ImGuiWindowFlags_HorizontalScrollbar);
  for (auto it = messages.begin(); it != messages.end(); it++)
  {
    ImGui::Text("%s", it->data());
  }
  ImGui::EndChild();
  ImGui::InputText("test", viewModel->textInput, IM_ARRAYSIZE(viewModel->textInput));
  ImGui::EndChild();
}
