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

#include "dataref.h"
#include <exception>

DataRef::DataRef(std::string ref, DataRefType dataRefType) { 
    this->dataRefType = dataRefType; this->ref = ref; 
}

DataRefType DataRef::getDataRefType() const {
    return dataRefType;
}

std::string DataRef::getRef() const {
    return ref;
}

void DataRef::complete() {
    this->subject.get_subscriber().on_completed();
}

void DataRef::error(std::string error) {
    this->subject.get_subscriber().on_error(std::make_exception_ptr(std::runtime_error(error)));
}

rxcpp::observable<DataRefValue> DataRef::toObservable() {
    return this->subject.get_observable();
}

void DataRef::updateFloatValue(float value) const
{
    DataRefValue val;
    val.floatData = value;
    val.type = DATA_REF_FLOAT;
    this->subject.get_subscriber().on_next(val);
}