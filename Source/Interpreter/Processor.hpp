
/*!
 *
 *    + --------------------------------------- +
 *    |  Processor.hpp                          |
 *    |                                         |
 *    |             Object Processor            |
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

#ifndef SPINPROCESSOR
#define SPINPROCESSOR

namespace Spin {

	Object * Processor::applyAddition(Token * t, Object * l, Object * r) {
		if (l -> isString() || r -> isString()) {
			auto search = stringAddition.find({ l -> type, r -> type });
			if (search != stringAddition.end()) {
				auto handler = search -> second;
				return handler(l, r);
			}
			throw EvaluationError(
				"Binary operator '+' doesn't support operands of type '" +
				l -> getObjectName() + "' and '" +
				r -> getObjectName() + "'!", * t
			);
		}
		auto search = binaryAddition.find({ l -> type, r -> type });
		if (search != binaryAddition.end()) {
			auto handler = search -> second;
			return handler(l, r);
		}
		search = binaryAddition.find({ r -> type, l -> type });
		if (search != binaryAddition.end()) {
			auto handler = search -> second;
			return handler(r, l);
		}
		throw EvaluationError(
			"Binary operator '+' doesn't support operands of type '" +
			l -> getObjectName() + "' and '" +
			r -> getObjectName() + "'!", * t
		);
	}
	Object * Processor::applySubtraction(Token * t, Object * l, Object * r) {
		auto search = binarySubtraction.find({ l -> type, r -> type });
		if (search != binarySubtraction.end()) {
			auto handler = search -> second;
			return handler(l, r);
		}
		throw EvaluationError(
			"Binary operator '-' doesn't support operands of type '" +
			l -> getObjectName() + "' and '" +
			r -> getObjectName() + "'!", * t
		);
	}
	Object * Processor::applyMultiplication(Token * t, Object * l, Object * r) {
		auto search = binaryMultiplication.find({ l -> type, r -> type });
		if (search != binaryMultiplication.end()) {
			auto handler = search -> second;
			return handler(l, r);
		}
		search = binaryMultiplication.find({ r -> type, l -> type });
		if (search != binaryMultiplication.end()) {
			auto handler = search -> second;
			return handler(r, l);
		}
		throw EvaluationError(
			"Binary operator '*' doesn't support operands of type '" +
			l -> getObjectName() + "' and '" +
			r -> getObjectName() + "'!", * t
		);
	}
	Object * Processor::applyDivision(Token * t, Object * l, Object * r) {
		auto search = binaryDivision.find({ l -> type, r -> type });
		if (search != binaryDivision.end()) {
			auto handler = search -> second;
			Object * o = handler(l, r);
			if (o -> isUnknown()) {
				// Check if in try catch block.
				throw EvaluationError(
					"Binary operator '/' threw division by 0 exception!", * t
				);
			}
			return o;
		}
		throw EvaluationError(
			"Binary operator '/' doesn't support operands of type '" +
			l -> getObjectName() + "' and '" +
			r -> getObjectName() + "'!", * t
		);
	}
	Object * Processor::applyModulus(Token * t, Object * l, Object * r) {
		if (l -> type == BasicType::Int64Type &&
			r -> type == BasicType::Int64Type) {
			Int64 * a = (Int64 *) l -> value;
			Int64 * b = (Int64 *) r -> value;
			if ((* b) == 0) {
				// Check if in try catch block.
				throw EvaluationError(
					"Binary operator '%' threw division by 0 exception!", * t
				);
			}
			Int64 * c = new Int64((* a) % (* b));
			return new Object(BasicType::Int64Type, c);
		}
		if (l -> type == BasicType::ColourType &&
			r -> type == BasicType::ColourType) {
			Colour * a = (Colour *) l -> value;
			Colour * b = (Colour *) r -> value;
			Colour * c = new Colour((* a) % (* b));
			return new Object(BasicType::ColourType, c);
			
		}
		throw EvaluationError(
			"Binary operator '%' doesn't support operands of type '" +
			l -> getObjectName() + "' and '" +
			r -> getObjectName() + "'!", * t
		);
	}
	Object * Processor::applyAND(Token * t, Object * l, Object * r) {
		auto search = binaryAND.find({ l -> type, r -> type });
		if (search != binaryAND.end()) {
			auto handler = search -> second;
			return handler(l, r);
		}
		throw EvaluationError(
			"Binary operator '&' doesn't support operands of type '" +
			l -> getObjectName() + "' and '" +
			r -> getObjectName() + "'!", * t
		);
	}
	Object * Processor::applyXOR(Token * t, Object * l, Object * r) {
		auto search = binaryXOR.find({ l -> type, r -> type });
		if (search != binaryXOR.end()) {
			auto handler = search -> second;
			return handler(l, r);
		}
		throw EvaluationError(
			"Binary operator '^' doesn't support operands of type '" +
			l -> getObjectName() + "' and '" +
			r -> getObjectName() + "'!", * t
		);
	}
	Object * Processor::applyOR(Token * t, Object * l, Object * r) {
		auto search = binaryOR.find({ l -> type, r -> type });
		if (search != binaryOR.end()) {
			auto handler = search -> second;
			return handler(l, r);
		}
		throw EvaluationError(
			"Binary operator '|' doesn't support operands of type '" +
			l -> getObjectName() + "' and '" +
			r -> getObjectName() + "'!", * t
		);
	}
	Object * Processor::applyEquality(Token * t, Object * l, Object * r) {
		if (l -> type == r -> type) {
			auto search = binaryStrictEquality.find({ l -> type, r -> type });
			if (search != binaryStrictEquality.end()) {
				auto handler = search -> second;
				return handler(l, r);
			}
			throw EvaluationError(
				"Logical operator '==' doesn't support operands of type '" +
				l -> getObjectName() + "' and '" +
				r -> getObjectName() + "'!", * t
			);
		}
		auto search = binaryMixedEquality.find({ l -> type, r -> type });
		if (search != binaryMixedEquality.end()) {
			auto handler = search -> second;
			return handler(l, r);
		}
		search = binaryMixedEquality.find({ r -> type, l -> type });
		if (search != binaryMixedEquality.end()) {
			auto handler = search -> second;
			return handler(r, l);
		}
		throw EvaluationError(
			"Logical operator '==' doesn't support operands of type '" +
			l -> getObjectName() + "' and '" +
			r -> getObjectName() + "'!", * t
		);
	}
	Object * Processor::applyInequality(Token * t, Object * l, Object * r) {
		Object * a = applyEquality(t, l, r);
		Bool * b = (Bool *) a -> value;
		* b = !(* b); return a;
	}
	Object * Processor::applyMajor(Token * t, Object * l, Object * r) {
		auto search = binaryMajor.find({ l -> type, r -> type });
		if (search != binaryMajor.end()) {
			auto handler = search -> second;
			return handler(l, r);
		}
		throw EvaluationError(
			"Logical operator '>' doesn't support operands of type '" +
			l -> getObjectName() + "' and '" +
			r -> getObjectName() + "'!", * t
		);
	}
	Object * Processor::applyMajorEqual(Token * t, Object * l, Object * r) {
		auto search = binaryMajorEqual.find({ l -> type, r -> type });
		if (search != binaryMajorEqual.end()) {
			auto handler = search -> second;
			return handler(l, r);
		}
		throw EvaluationError(
			"Logical operator '>=' doesn't support operands of type '" +
			l -> getObjectName() + "' and '" +
			r -> getObjectName() + "'!", * t
		);
	}
	Object * Processor::applyMinor(Token * t, Object * l, Object * r) {
		auto search = binaryMinor.find({ l -> type, r -> type });
		if (search != binaryMinor.end()) {
			auto handler = search -> second;
			return handler(l, r);
		}
		throw EvaluationError(
			"Logical operator '<' doesn't support operands of type '" +
			l -> getObjectName() + "' and '" +
			r -> getObjectName() + "'!", * t
		);
	}
	Object * Processor::applyMinorEqual(Token * t, Object * l, Object * r) {
		auto search = binaryMinorEqual.find({ l -> type, r -> type });
		if (search != binaryMinorEqual.end()) {
			auto handler = search -> second;
			return handler(l, r);
		}
		throw EvaluationError(
			"Logical operator '<=' doesn't support operands of type '" +
			l -> getObjectName() + "' and '" +
			r -> getObjectName() + "'!", * t
		);
	}
	Object * Processor::applyComparisonOperator(Token * t, Object * l, Object * r) {
		switch (t -> type) {
			case TokenType::equality: {
				try { return applyEquality(t, l, r); }
				catch (EvaluationError & e) { throw; }
			} break;
			case TokenType::inequality: {
				try { return applyInequality(t, l, r); }
				catch (EvaluationError & e) { throw; }
			} break;
			case TokenType::major: {
				try { return applyMajor(t, l, r); }
				catch (EvaluationError & e) { throw; }
			} break;
			case TokenType::majorEqual: {
				try { return applyMajorEqual(t, l, r); }
				catch (EvaluationError & e) { throw; }
			} break;
			case TokenType::minor: {
				try { return applyMinor(t, l, r); }
				catch (EvaluationError & e) { throw; }
			} break;
			case TokenType::minorEqual: {
				try { return applyMinorEqual(t, l, r); }
				catch (EvaluationError & e) { throw; }
			} break;
			default: break;
		}
		throw EvaluationError(
			"Comparison operator '" + t -> lexeme + "' doesn't support operands of type '" +
			l -> getObjectName() + "' and '" +
			r -> getObjectName() + "'!", * t
		);
	}
	Object * Processor::applyBinaryOperator(Token * t, Object * l, Object * r) {
		switch (t -> type) {
			case TokenType::plus: {
				try { return applyAddition(t, l, r); }
				catch (EvaluationError & e) { throw; }
			} break;
			case TokenType::minus: {
				try { return applySubtraction(t, l, r); }
				catch (EvaluationError & e) { throw; }
			} break;
			case TokenType::star: {
				try { return applyMultiplication(t, l, r); }
				catch (EvaluationError & e) { throw; }
			} break;
			case TokenType::slash: {
				try { return applyDivision(t, l, r);}
				catch (EvaluationError & e) { throw; }
			} break;
			case TokenType::ampersand: {
				try { return applyAND(t, l, r); }
				catch (EvaluationError & e) { throw; }
			} break;
			case TokenType::dagger: {
				try { return applyXOR(t, l, r); }
				catch (EvaluationError & e) { throw; }
			} break;
			case TokenType::pipe: {
				try { return applyOR(t, l, r); }
				catch (EvaluationError & e) { throw; }
			} break;
			case TokenType::modulus: {
				try { return applyModulus(t, l, r); }
				catch (EvaluationError & e) { throw; }
			} break;
			default: break;
		}
		throw EvaluationError(
			"Binary operator '" + t -> lexeme + "' doesn't support operands of type '" +
			l -> getObjectName() + "' and '" +
			r -> getObjectName() + "'!", * t
		);
	}
	Object * Processor::applySubscriptOperator(Token * t, Object * l, Object * r) {
		if (l -> type == BasicType::StringType) {
			if (r -> type == BasicType::Int64Type) {
				Int64 * i = (Int64 *) r -> value;
				String * s = (String *) l -> value;
				if (((* i) >= 0) && (s -> length() > (* i))) {
					Character * c = new Character(s -> at(* i));
					return new Object(BasicType::CharacterType, c);
				}
				throw EvaluationError(
					"Subscript operator '[ ]' threw index out of range exception!", * t
				);
			}
			throw EvaluationError(
				"Subscript operator '[ ]' doesn't support operand of type '" +
				r -> getObjectName() + "' on inner expression of type '" +
				l -> getObjectName() + "'!", * t
			);
		} else if (l -> type == BasicType::ArrayType) {
			/* TODO: Ask the array... */
		}
		throw EvaluationError(
			"Subscript operator '[ ]' doesn't support operand of type '" +
			r -> getObjectName() + "' on inner expression of type '" +
			l -> getObjectName() + "'!", * t
		);
	}
	Object * Processor::applyUnaryOperator(Token * t, Object * o) {
		switch (t -> type) {
			case TokenType::minus: {
				auto search = unaryNegation.find(o -> type);
				if (search != unaryNegation.end()) {
					auto handler = search -> second;
					return handler(o);
				}
				throw EvaluationError(
					"Unary operator '-' doesn't support any operand of type '" +
					o -> getObjectName() + "'!", * t
				);
			} break;
			case TokenType::plus: {
				switch (o -> type) {
					case BasicType::CharacterType:
					case BasicType::ByteType:
					case BasicType::Int64Type:
					case BasicType::RealType:
					case BasicType::ImaginaryType:
					case BasicType::ComplexType: return o -> copy();
					default: {
						throw EvaluationError(
							"Unary operator '+' doesn't support any operand of type '" +
							o -> getObjectName() + "'!", * t
						);
					} break;
				}
			} break;
			case TokenType::exclamationMark: {
				if (o -> type == BasicType::BoolType) {
					Bool * b = (Bool *) o -> value;
					b = new Bool(!(* b));
					return new Object(o -> type, b);
				}
				throw EvaluationError(
					"Unary operator '!' doesn't support any operand of type '" +
					o -> getObjectName() + "'!", * t
				);
			} break;
			case TokenType::dagger: {
				if (o -> type == BasicType::ComplexType) {
					Complex * c = (Complex *) o -> value;
					c = new Complex(* c); c -> conjugate();
					return new Object(o -> type, c);
				}
				throw EvaluationError(
					"Unary operator '^' doesn't support any operand of type '" +
					o -> getObjectName() + "'!", * t
				);
			} break;
			case TokenType::tilde: {
				auto search = unaryInversion.find(o -> type);
				if (search != unaryInversion.end()) {
					auto handler = search -> second;
					return handler(o);
				}
				throw EvaluationError(
					"Unary operator '~' doesn't support any operand of type '" +
					o -> getObjectName() + "'!", * t
				);
			} break;
			default: break;
		}
		throw EvaluationError(
			"Unary operator '" + t -> lexeme +
			"' doesn't support any operand of type '" +
			o -> getObjectName() + "'!", * t
		);
	}
	void Processor::applyAssignment(Token * t, Object * l, Object * r) {
		if (l -> type == r -> type) {
			auto search = pureAssignment.find({ l -> type, r -> type });
			if (search != pureAssignment.end()) {
				auto handler = search -> second;
				handler(l, r); return;
			}
		}
		auto search = mixedAssignment.find({ l -> type, r -> type });
		if (search != mixedAssignment.end()) {
			auto handler = search -> second;
			handler(l, r); return;
		}
		throw EvaluationError(
			"Assignment operator '=' doesn't support operands of type '" +
			l -> getObjectName() + "' and '" +
			r -> getObjectName() + "'!", * t
		);
	}

}

#endif
