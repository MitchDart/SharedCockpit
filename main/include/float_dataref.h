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

#include "dataref.h"

/** 
 * Oneliner description of class.
 * 
 * Paragraph explaining how the class is used and what its purpose is in more detail.
 */ 
class FloatDataRef : public DataRef {
    private:
        rxcpp::subjects::subject<float> subject;
    protected:
    public:
        FloatDataRef(std::string ref) : DataRef(ref, DATA_REF_FLOAT) {}
        ~FloatDataRef() override;
        void complete();
        void update(float value) const;
        void error(std::string error);
        rxcpp::observable<float> toObservable();
};
