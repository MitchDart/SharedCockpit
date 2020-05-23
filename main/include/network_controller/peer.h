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

/*
	This class is responsible for abstracting betwean Client and Server

	|--------------|                                |--------------|
	|    Client    |------->      Peer     <--------|    Server    |
	|--------------|                                |--------------|

	------------------- Common interface ---------------------------
	* send message                                  * send message
	* recieve message                               * recieve message
	----------------------------------------------------------------
	** Specific implementation for each is left as a implementation detail
	-- The peer is not responsible for sets of messages
*/

class Peer {
public:
	// throws exceptions
	virtual void sendMessage(void* message) = 0;
	virtual void* pollMessage() = 0;
}