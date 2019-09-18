
/*!
 *
 *    + --------------------------------------- +
 *    |  Function.hpp                           |
 *    |                                         |
 *    |              Stack Function             |
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

#include "../Aliases/Prototypes.hpp"

#ifndef STACKFUNCTION
#define STACKFUNCTION

namespace Stack {

	Function::Function(FunctionStatement * d) { declaration = d; }
	Object * Function::call(Interpreter * i, ArrayList<Object *> a) {
		Environment * environment = new Environment(i -> globals);
		SizeType j = 0;
		for (Parameter * param : declaration -> params) {
			if ((param -> type) != (a[j] -> type)) {
				throw EvaluationError(
					"Call of " + stringValue() + " doesn't match the predefined parameters!",
					* (param -> tokenType)
				);
			} else if (param -> type == BasicType::ClassType) {
				if ((param -> tokenType -> lexeme) !=
					(a[j] -> getObjectName())) {
					throw EvaluationError(
						"Call of " + stringValue() + " doesn't match the predefined parameters!",
						* (param -> tokenType)
					);
				}
			}
			environment -> define(param -> name -> lexeme, a[j]);
			j += 1;                                        
		}
		i -> executeFunction(declaration -> body, environment);
		return i -> getCurrentValue() -> copy();
	}
	String Function::stringValue() const {
		return "<func " + (declaration -> name -> lexeme) + ">";
	}
	UInt32 Function::arity() const { return declaration -> params.size(); }
	CallProtocol * Function::copy() const {
		return new Function(* this);
	}

	NativeFunction::NativeFunction(NativeLambda l, UInt32 a) {
		_lambda = l;
		_arity = a;
	}
	Object * NativeFunction::call(Interpreter * i, ArrayList<Object *> a) {
		return _lambda(i, a);
	}
	String NativeFunction::stringValue() const {
		return "<native>";
	}
	UInt32 NativeFunction::arity() const { return _arity; }
	CallProtocol * NativeFunction::copy() const {
		return new NativeFunction(* this);
	}

}

#endif
