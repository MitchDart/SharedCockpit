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

/*
* DataRefType is used to represent different DataRef Types. See XPlane documentation for more on DataRef Types
*/
enum DataRefType { DATA_REF_FLOAT, DATA_REF_DOUBLE };

/*
* DataRefValue struct is used to represent one unit value for a dataref stream. It's type is implicitly stored by 'type'
*/
struct DataRefValue {
    //Possible float value
    float floatData;

    //Possible float value
    double doubleData;

    //Represent type of this current DataRefValue
    DataRefType type;
};

/** 
 * DataRef class represents simulator data for reading and writing.
 * 
 * This is an abstracted representation of the C DataRef in XPlane. Each DataRef has a string ID which matches
 * XPlanes reference to that DataRef. We also have an observable value of the data which is updated as that data
 * changes. DataRefs are automatically subscribed to while this object lives. For now.
 */ 
class DataRef {
    private:
        /*
        * String reference or "name" of this DataRef
        */
        std::string ref;
        /*
        * RxCPP Subject to represent this DataRef as a stream
        */
        rxcpp::subjects::subject<DataRefValue> subject;

        /*
        * Implicit dataref type
        */
        DataRefType dataRefType;
    protected:
    public:
        /*
        * Constructor
        * 
        * @param ref Name of dataRef
        * @param dataRefType Implicit data type of dataref
        */
        DataRef(std::string ref, DataRefType dataRefType);// { this->dataRefType = dataRefType; this->ref = ref; }

        /*
        * Used to return implicit data type of this DataRef stream
        */
        DataRefType getDataRefType() const;

        /*
        * Returns current named reference for this DataRef
        */
        std::string getRef() const;

        /*
        * Overload equality operator to check string ref instead
        */
        bool operator==(const DataRef& comp) const { return this->ref == comp.ref; }

        /*
        * Complete this DataRef stream. Updates should not be called after this is called
        */
        void complete();

        /*
        * Cancel this stream with a runtime error.
        */
        void error(std::string error);

        /*
        * Cancel this stream with a runtime error.
        */
        rxcpp::observable<DataRefValue> toObservable();

        //----- DataRef Implicit updates ------

        /*
        * Update Float value for this DataRefStream
        *
        * @param value Updated float value to emit to this stream
        */
        void updateFloatValue(float value) const;

        /*
        * Update Double value for this DataRefStream
        *
        * @param value Updated double value to emit to this stream
        */
        void updateDoubleValue(double value) const;
}; 
