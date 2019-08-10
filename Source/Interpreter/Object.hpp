
/*!
 *
 *    + --------------------------------------- +
 *    |  Object.hpp                             |
 *    |                                         |
 *    |               Stack Object              |
 *    |                                         |
 *    |  Created by Cristian A.                 |
 *    |  Copyright © MIT. All rights reserved.  |
 *    + --------------------------------------- +
 *
 *    Note: This software is licensed under
 *          the (MIT) Massachusetts Institute
 *          of Technology License.
 *
 */

#ifndef STACKOBJECT
#define STACKOBJECT

#include "../Aliases/Aliases.hpp"
#include "../Token/Token.hpp"

#include "Exceptions.hpp"

namespace Stack {

	enum BasicType {

		BooleanType,
		CharacterType,

		Int8Type,
		Int16Type,
		Int32Type,
		Int64Type,
		UInt8Type,
		UInt16Type,
		UInt32Type,
		UInt64Type,

		ColourType,

		FloatType,
		DoubleType,
		RealType,

		ImaginaryType,
		ComplexType,

		StringType,

		ArrayListType,

		VectorType,

		ClassType,
		StructureType,
		ExceptionType,

		UnknownType

	};

	class Object {

		public:

		void * value = nullptr;

		BasicType type = BasicType::UnknownType;

		Object() { }

		Object(BasicType t, void * v) {
			type = t; value = v;
		}

		~Object() {
			if (value == nullptr) return;
			//delete value;
		}

		Boolean isIntegerType() {
			return type == BasicType::Int8Type     ||
				   type == BasicType::Int16Type    ||
				   type == BasicType::Int32Type    ||
				   type == BasicType::Int64Type    ||
				   type == BasicType::UInt8Type    ||
				   type == BasicType::UInt16Type   ||
				   type == BasicType::UInt32Type   ||
				   type == BasicType::UInt64Type;
		}

		Boolean isRealType() {
			return type == BasicType::FloatType     ||
				   type == BasicType::DoubleType    ||
				   type == BasicType::RealType;
		}

		Boolean isComplexType() {
			return type == BasicType::ImaginaryType ||
				   type == BasicType::ComplexType;
		}			

		Boolean isNumericType() {
			return isIntegerType()  ||
				   isRealType()     ||
				   isComplexType();
		}

		String getObjectName() {
			switch (type) {
				case BasicType::BooleanType: return "BooleanType";
				case BasicType::CharacterType: return "CharacterType";
				case BasicType::Int8Type: return "Int8Type";
				case BasicType::Int16Type: return "Int16Type";
				case BasicType::Int32Type: return "Int32Type";
				case BasicType::Int64Type: return "Int64Type";
				case BasicType::UInt8Type: return "UInt8Type";
				case BasicType::UInt16Type: return "UInt16Type";
				case BasicType::UInt32Type: return "UInt32Type";
				case BasicType::UInt64Type: return "UInt64Type";
				case BasicType::ColourType: return "ColourType";
				case BasicType::FloatType: return "FloatType";
				case BasicType::DoubleType: return "DoubleType";
				case BasicType::RealType: return "RealType";
				case BasicType::ImaginaryType: return "ImaginaryType";
				case BasicType::ComplexType: return "ComplexType";
				case BasicType::StringType: return "StringType";
				case BasicType::ArrayListType: return "ArrayListType";
				case BasicType::VectorType: return "VectorType";
				case BasicType::ClassType: {
					return "ClassType";
					// TODO: Ask the class for its type.
				}
				case BasicType::StructureType: return "StructureType";
				case BasicType::ExceptionType: return "ExceptionType";
				case BasicType::UnknownType: default: return "UnknownType";
			}
		}

		String getObjectStringValue() {
			switch (type) {
				case BasicType::BooleanType: {
					Boolean * b = (Boolean *) value;
					if (* b) return "true";
					else return "false";
				}
				case BasicType::CharacterType: {
					Character * c = (Character *) value;
					return String(c);
				}
				case BasicType::Int8Type: {
					Int8 * i = (Int8 *) value;
					return toString(* i);
				}
				case BasicType::Int16Type: {
					Int16 * i = (Int16 *) value;
					return toString(* i);
				}
				case BasicType::Int32Type: {
					Int32 * i = (Int32 *) value;
					return toString(* i);
				}
				case BasicType::Int64Type: {
					Int64 * i = (Int64 *) value;
					return toString(* i);
				}
				case BasicType::UInt8Type: {
					UInt8 * i = (UInt8 *) value;
					return toString(* i);
				}
				case BasicType::UInt16Type: {
					UInt16 * i = (UInt16 *) value;
					return toString(* i);
				}
				case BasicType::UInt32Type: {
					UInt32 * i = (UInt32 *) value;
					return toString(* i);
				}
				case BasicType::UInt64Type: {
					UInt64 * i = (UInt64 *) value;
					return toString(* i);
				}
				case BasicType::ColourType: {
					// TODO: fix colour value.
					return "SomeColour";
				}
				case BasicType::FloatType: {
					Float * i = (Float *) value;
					return toString(* i);
				}
				case BasicType::DoubleType: {
					Double * i = (Double *) value;
					return toString(* i);
				}
				case BasicType::RealType: {
					// TODO: fix real value.
					return "SomeReal";
				}
				case BasicType::ImaginaryType: {
					// TODO: fix imaginary value.
					return "SomeImaginary";
				}
				case BasicType::ComplexType: {
					// TODO: fix complex value.
					return "SomeComplex";
				}
				case BasicType::StringType: {
					return * ((String *) value);
				}
				case BasicType::ArrayListType: {
					// TODO: fix list value.
					return "SomeList";
				}
				case BasicType::VectorType: {
					// TODO: fix vector value.
					return "SomeVector";
				}
				case BasicType::ClassType: {
					// TODO: fix class value.
					return "SomeClass";
				}
				case BasicType::StructureType: {
					// TODO: fix structure value.
					return "SomeStructure";
				}
				case BasicType::ExceptionType: {
					// TODO: fix exception value.
					return "SomeException";
				}
				case BasicType::UnknownType: default: {
					return "Unknown"; break;
				}
			}
		}

	};

}

#endif
