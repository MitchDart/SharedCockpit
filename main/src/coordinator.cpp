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

#include "coordinator.h"
#include "viewmodel.h"

//Include windows here so they dont bother other includes.
#include "first_window.h"
#include "chat_window.h"
#include "rx.hpp"

Coordinator::Coordinator(Environment* environment) {
    this->environment = environment;
    this->viewModel = new ViewModel(environment->rlp);
    this->chatServer = new ChatServerInterface(environment->rlp);

    this->chatViewModel = new ChatViewModel(environment->rlp, this->chatServer);
    this->chatViewModel->setName("Eben");

    this->chatTwoViewModel = new ChatViewModel(environment->rlp, this->chatServer);
    this->chatTwoViewModel->setName("Mitch");
}

void Coordinator::onStart() {
    //Create first window
  const auto firstWindow =
      new FirstWindow("My first window", 200, 200, 200, 200, this->viewModel);
    const auto chatWindow =
        new ChatWindow("ChatWindow", 350, 300, 450, 200, this->chatViewModel);
    const auto chatTwoWindow =
        new ChatWindow("ChatWindowTwo", 350, 300, 850, 200, this->chatTwoViewModel);
    this->environment->createWindow(firstWindow);
    this->environment->createWindow(chatWindow);
    this->environment->createWindow(chatTwoWindow);
}

void Coordinator::onStop() {

}