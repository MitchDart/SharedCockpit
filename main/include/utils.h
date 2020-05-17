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

#include "rx.hpp"
#include <vector>
#include <string>

namespace Utils
{
	template <typename T>
	inline rxcpp::observable<std::shared_ptr<std::vector<T>>> zip_v(const std::vector<rxcpp::observable<T>>& observables) {
		// map the first observable to convert values to a single-element vector
		auto it = observables.cbegin();
		rxcpp::observable<std::shared_ptr<std::vector<T>>> acc = it->map([](T t) {
			return std::make_shared<std::vector<T>>(std::initializer_list<T>{ t });
			});

		// fold each observable into accumulator by zipping, and pushing back value
		while (++it != observables.cend()) {
			acc = acc.zip([](std::shared_ptr<std::vector<T>> acc, T next) {
				acc->push_back(next);
				return acc;
				}, *it);
		}
		return acc;
	}

	inline std::vector<std::string> split(const std::string& str, const std::string& delim)
	{
		std::vector<std::string> tokens;
		size_t prev = 0, pos = 0;
		do
		{
			pos = str.find(delim, prev);
			if (pos == std::string::npos) pos = str.length();
			std::string token = str.substr(prev, pos - prev);
			if (!token.empty()) tokens.push_back(token);
			prev = pos + delim.length();
		} while (pos < str.length() && prev < str.length());
		return tokens;
	}
}