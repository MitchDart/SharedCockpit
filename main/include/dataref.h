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

enum DataRefType { DATA_REF_FLOAT };

/** 
 * DataRef class represents simulator data for reading and writing.
 * 
 * This is an abstracted representation of the C DataRef in XPlane. Each DataRef has a string ID which matches
 * XPlanes reference to that DataRef. We also have an observable value of the data which is updated as that data
 * changes. DataRefs are automatically subscribed to while this object lives. For now.
 */ 
class DataRef {
    private:
        std::string ref;
    protected:
    public:
        DataRef(std::string ref, DataRefType dataRefType) { this->dataRefType = dataRefType; this->ref = ref; }
        DataRefType dataRefType;
        virtual ~DataRef() {}
        std::string getRef() { return ref; }
        bool operator==(const DataRef& comp) const { return this->ref == comp.ref; }
}; 