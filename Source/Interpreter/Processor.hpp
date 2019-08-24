
/*!
 *
 *    + --------------------------------------- +
 *    |  Processor.hpp                          |
 *    |                                         |
 *    |             Stack Processor             |
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

#ifndef STACKPROCESSOR
#define STACKPROCESSOR

#include "../Aliases/Aliases.hpp"
#include "../Linker/Linker.hpp"
#include "../Types/Object.hpp"

namespace Stack {

	class EvaluationError: public Exception {
		private:
		const String _message;
		const Token _token;
		public:
		const String & getMessage() const { return _message; }
		const Token & getToken() const { return _token; }
		EvaluationError(String message, Token token):
		Exception(), _message(message), _token(token) { }
	};

	class Processor {

		private:

		typedef Function<Object * (Object *)> UnaryHandler;
		typedef Function<Object * (Object *, Object *)> BinaryHandler;

		typedef Pair<BasicType, BasicType> BasicTypes;

		Map<BasicType, UnaryHandler> unaryNegation = {
			{
				BasicType::Int64Type,
				[] (Object * o) {
					Int64 * i = (Int64 *) o -> value;
					return new Object(o -> type, new Int64(-(* i)));
				}
			},
			{
				BasicType::RealType,
				[] (Object * o) {
					Real * i = (Real *) o -> value;
					return new Object(o -> type, new Real(-(* i)));
				}
			},
			{
				BasicType::ImaginaryType,
				[] (Object * o) {
					Real * i = (Real *) o -> value;
					return new Object(o -> type, new Real(-(* i)));
				}
			},
			{
				BasicType::ComplexType,
				[] (Object * o) {
					Complex * c = (Complex *) o -> value;
					return new Object(o -> type, new Complex(-(* c)));
				}
			}
		};
		Map<BasicType, UnaryHandler> unaryInversion = {
			{
				BasicType::ByteType,
				[] (Object * o) {
					UInt8 * b = (UInt8 *) o -> value;
					b = new UInt8(~(* b));
					return new Object(o -> type, b);
				}
			},
			{
				BasicType::ColourType,
				[] (Object * o) {
					Colour * c = (Colour *) o -> value;
					c = new Colour(~(* c));
					return new Object(o -> type, c);
				}
			},
			{
				BasicType::Int64Type,
				[] (Object * o) {
					Int64 * i = (Int64 *) o -> value;
					i = new Int64(~(* i));
					return new Object(o -> type, i);
				}
			}
		};

		Map<BasicTypes, BinaryHandler> binaryAddition = {
			{
				{ BasicType::Int64Type, BasicType::Int64Type },
				[] (Object * l, Object * r) {
					Int64 * a = (Int64 *) l -> value;
					Int64 * b = (Int64 *) r -> value;
					Int64 * c = new Int64((* a) + (* b));
					return new Object(BasicType::Int64Type, c);
				}
			},
			{
				{ BasicType::RealType, BasicType::RealType },
				[] (Object * l, Object * r) {
					Real * a = (Real *) l -> value;
					Real * b = (Real *) r -> value;
					Real * c = new Real((* b) + (* a));
					return new Object(BasicType::RealType, c);
				}
			},
			{
				{ BasicType::Int64Type, BasicType::ByteType },
				[] (Object * l, Object * r) {
					Int64 * a = (Int64 *) l -> value;
					UInt8 * b = (UInt8 *) r -> value;
					Int64 * c = new Int64((* a) + (Int64)(* b));
					return new Object(BasicType::Int64Type, c);
				}
			},
			{
				{ BasicType::Int64Type, BasicType::RealType },
				[] (Object * l, Object * r) {
					Int64 * a = (Int64 *) l -> value;
					Real * b = (Real *) r -> value;
					Real * c = new Real((Real)(* a) + (* b));
					return new Object(BasicType::RealType, c);
				}
			},
			{
				{ BasicType::Int64Type, BasicType::ImaginaryType },
				[] (Object * l, Object * r) {
					Int64 * a = (Int64 *) l -> value;
					Real * b = (Real *) r -> value;
					Complex * c = new Complex((Real)(* a), (* b));
					return new Object(BasicType::ComplexType, c);
				}
			},
			{
				{ BasicType::Int64Type, BasicType::ComplexType },
				[] (Object * l, Object * r) {
					Int64 * a = (Int64 *) l -> value;
					Complex * b = (Complex *) r -> value;
					Complex * c = new Complex((* a) + b -> a, b -> b);
					return new Object(BasicType::ComplexType, c);
				}
			},
			{
				{ BasicType::ComplexType, BasicType::RealType },
				[] (Object * l, Object * r) {
					Complex * a = (Complex *) l -> value;
					Real * b = (Real *) r -> value;
					Complex * c = new Complex((* b) + a -> a, a -> b);
					return new Object(BasicType::ComplexType, c);
				}
			},
			{
				{ BasicType::ComplexType, BasicType::ImaginaryType },
				[] (Object * l, Object * r) {
					Complex * a = (Complex *) l -> value;
					Real * b = (Real *) r -> value;
					Complex * c = new Complex(a -> a, a -> b + (* b));
					return new Object(BasicType::ComplexType, c);
				}
			},
			{
				{ BasicType::ImaginaryType, BasicType::RealType },
				[] (Object * l, Object * r) {
					Real * a = (Real *) l -> value;
					Real * b = (Real *) r -> value;
					Complex * c = new Complex((* b), (* a));
					return new Object(BasicType::ComplexType, c);
				}
			},
			{
				{ BasicType::ColourType, BasicType::ColourType },
				[] (Object * l, Object * r) {
					Colour * a = (Colour *) l -> value;
					Colour * b = (Colour *) r -> value;
					Colour * c = new Colour((* a) + (* b));
					return new Object(BasicType::ColourType, c);
				}
			},
			{
				{ BasicType::CharacterType, BasicType::CharacterType },
				[] (Object * l, Object * r) {
					Character * a = (Character *) l -> value;
					Character * b = (Character *) r -> value;
					Character * c = new Character((* a) + (* b));
					return new Object(BasicType::CharacterType, c);
				}
			},
			{
				{ BasicType::ByteType, BasicType::ByteType },
				[] (Object * l, Object * r) {
					UInt8 * a = (UInt8 *) l -> value;
					UInt8 * b = (UInt8 *) r -> value;
					UInt8 * c = new UInt8((* a) + (* b));
					return new Object(BasicType::ByteType, c);
				}
			}
		};
		Map<BasicTypes, BinaryHandler> stringAddition = {
			{
				{ BasicType::StringType, BasicType::StringType },
				[] (Object * l, Object * r) {
					String * a = (String *) l -> value;
					String * b = (String *) r -> value;
					String * c = new String((* a) + (* b));
					return new Object(BasicType::StringType, c);
				}
			},
			{
				{ BasicType::StringType, BasicType::CharacterType },
				[] (Object * l, Object * r) {
					String * a = (String *) l -> value;
					Character * b = (Character *) r -> value;
					StringStream s = StringStream();
					s << (* a) << (* b);
					String * c = new String(s.str());
					return new Object(BasicType::StringType, c);
				}
			},
			{
				{ BasicType::StringType, BasicType::RealType },
				[] (Object * l, Object * r) {
					String * a = (String *) l -> value;
					Real * b = (Real *) r -> value;
					StringStream s = StringStream();
					s << (* a) << (* b);
					String * c = new String(s.str());
					return new Object(BasicType::StringType, c);
				}
			},
			{
				{ BasicType::StringType, BasicType::ImaginaryType },
				[] (Object * l, Object * r) {
					String * a = (String *) l -> value;
					Real * b = (Real *) r -> value;
					StringStream s = StringStream();
					s << (* a) << (* b) << "i";
					String * c = new String(s.str());
					return new Object(BasicType::StringType, c);
				}
			},
			{
				{ BasicType::StringType, BasicType::Int64Type },
				[] (Object * l, Object * r) {
					String * a = (String *) l -> value;
					Int64 * b = (Int64 *) r -> value;
					StringStream s = StringStream();
					s << (* a) << (* b);
					String * c = new String(s.str());
					return new Object(BasicType::StringType, c);
				}
			},
			{
				{ BasicType::StringType, BasicType::ColourType },
				[] (Object * l, Object * r) {
					String * a = (String *) l -> value;
					Colour * b = (Colour *) r -> value;
					String * c = new String((* a) + b -> stringValue());
					return new Object(BasicType::StringType, c);
				}
			},
			{
				{ BasicType::StringType, BasicType::ComplexType },
				[] (Object * l, Object * r) {
					String * a = (String *) l -> value;
					Complex * b = (Complex *) r -> value;
					String * c = new String((* a) + b -> stringValue());
					return new Object(BasicType::StringType, c);
				}
			},
			{
				{ BasicType::CharacterType, BasicType::StringType },
				[] (Object * l, Object * r) {
					Character * a = (Character *) l -> value;
					String * b = (String *) r -> value;
					StringStream s = StringStream();
					s << (* a) << (* b);
					String * c = new String(s.str());
					return new Object(BasicType::StringType, c);
				}
			},
			{
				{ BasicType::RealType, BasicType::StringType },
				[] (Object * l, Object * r) {
					Real * a = (Real *) l -> value;
					String * b = (String *) r -> value;
					StringStream s = StringStream();
					s << (* a) << (* b);
					String * c = new String(s.str());
					return new Object(BasicType::StringType, c);
				}
			},
			{
				{ BasicType::ImaginaryType, BasicType::StringType },
				[] (Object * l, Object * r) {
					Real * a = (Real *) l -> value;
					String * b = (String *) r -> value;
					StringStream s = StringStream();
					s << (* a) << "i" << (* b);
					String * c = new String(s.str());
					return new Object(BasicType::StringType, c);
				}
			},
			{
				{ BasicType::Int64Type, BasicType::StringType },
				[] (Object * l, Object * r) {
					Int64 * a = (Int64 *) l -> value;
					String * b = (String *) r -> value;
					StringStream s = StringStream();
					s << (* a) << (* b);
					String * c = new String(s.str());
					return new Object(BasicType::StringType, c);
				}
			},
			{
				{ BasicType::ColourType, BasicType::StringType },
				[] (Object * l, Object * r) {
					Colour * a = (Colour *) l -> value;
					String * b = (String *) r -> value;
					String * c = new String(a -> stringValue() + (* b));
					return new Object(BasicType::StringType, c);
				}
			},
			{
				{ BasicType::ComplexType,  BasicType::StringType },
				[] (Object * l, Object * r) {
					Complex * a = (Complex *) l -> value;
					String * b = (String *) r -> value;
					String * c = new String(a -> stringValue() + (* b));
					return new Object(BasicType::StringType, c);
				}
			}
		};

		Map<BasicTypes, BinaryHandler> binarySubtraction = {
			{
				{ BasicType::Int64Type, BasicType::Int64Type },
				[] (Object * l, Object * r) {
					Int64 * a = (Int64 *) l -> value;
					Int64 * b = (Int64 *) r -> value;
					Int64 * c = new Int64((* a) - (* b));
					return new Object(BasicType::Int64Type, c);
				}
			},
			{
				{ BasicType::RealType, BasicType::RealType },
				[] (Object * l, Object * r) {
					Real * a = (Real *) l -> value;
					Real * b = (Real *) r -> value;
					Real * c = new Real((* a) - (* b));
					return new Object(BasicType::RealType, c);
				}
			},
			{
				{ BasicType::Int64Type, BasicType::RealType },
				[] (Object * l, Object * r) {
					Int64 * a = (Int64 *) l -> value;
					Real * b = (Real *) r -> value;
					Real * c = new Real((Real)(* a) - (* b));
					return new Object(BasicType::RealType, c);
				}
			},
			{
				{ BasicType::RealType, BasicType::Int64Type },
				[] (Object * l, Object * r) {
					Real * a = (Real *) l -> value;
					Int64 * b = (Int64 *) r -> value;
					Real * c = new Real((* a) - (Real)(* b));
					return new Object(BasicType::RealType, c);
				}
			},
			{
				{ BasicType::Int64Type, BasicType::ByteType },
				[] (Object * l, Object * r) {
					Int64 * a = (Int64 *) l -> value;
					UInt8 * b = (UInt8 *) r -> value;
					Int64 * c = new Int64((* a) - (* b));
					return new Object(BasicType::Int64Type, c);
				}
			},
			{
				{ BasicType::ByteType, BasicType::Int64Type },
				[] (Object * l, Object * r) {
					UInt8 * a = (UInt8 *) l -> value;
					Int64 * b = (Int64 *) r -> value;
					Int64 * c = new Int64((Int64)(* a) - (* b));
					return new Object(BasicType::Int64Type, c);
				}
			},
			{
				{ BasicType::ComplexType, BasicType::ComplexType },
				[] (Object * l, Object * r) {
					Complex * a = (Complex *) l -> value;
					Complex * b = (Complex *) r -> value;
					Complex * c = new Complex((* a) - (* b));
					return new Object(BasicType::ComplexType, c);
				}
			},
			{
				{ BasicType::ImaginaryType, BasicType::Int64Type },
				[] (Object * l, Object * r) {
					Real * a = (Real *) l -> value;
					Int64 * b = (Int64 *) r -> value;
					Complex * c = new Complex(-(Real)(* b), (* a));
					return new Object(BasicType::ComplexType, c);
				}
			},
			{
				{ BasicType::Int64Type, BasicType::ImaginaryType },
				[] (Object * l, Object * r) {
					Int64 * a = (Int64 *) l -> value;
					Real * b = (Real *) r -> value;
					Complex * c = new Complex((Real)(* b), -(* a));
					return new Object(BasicType::ComplexType, c);
				}
			},
			{
				{ BasicType::ImaginaryType, BasicType::RealType },
				[] (Object * l, Object * r) {
					Real * a = (Real *) l -> value;
					Real * b = (Real *) r -> value;
					Complex * c = new Complex(-(* b), (* a));
					return new Object(BasicType::ComplexType, c);
				}
			},
			{
				{ BasicType::RealType, BasicType::ImaginaryType },
				[] (Object * l, Object * r) {
					Real * a = (Real *) l -> value;
					Real * b = (Real *) r -> value;
					Complex * c = new Complex((* a), -(* b));
					return new Object(BasicType::ComplexType, c);
				}
			},
			{
				{ BasicType::ComplexType, BasicType::ImaginaryType },
				[] (Object * l, Object * r) {
					Complex * a = (Complex *) l -> value;
					Real * b = (Real *) r -> value;
					Complex * c = new Complex((* a).a, (* a).b - (* b));
					return new Object(BasicType::ComplexType, c);
				}
			},
			{
				{ BasicType::ImaginaryType, BasicType::ComplexType },
				[] (Object * l, Object * r) {
					Real * a = (Real *) l -> value;
					Complex * b = (Complex *) r -> value;
					Complex * c = new Complex(-(* b).a, (* a) - (* b).b);
					return new Object(BasicType::ComplexType, c);
				}
			},
			{
				{ BasicType::ComplexType, BasicType::RealType },
				[] (Object * l, Object * r) {
					Complex * a = (Complex *) l -> value;
					Real * b = (Real *) r -> value;
					Complex * c = new Complex((* a).a - (* b), (* a).b);
					return new Object(BasicType::ComplexType, c);
				}
			},
			{
				{ BasicType::RealType, BasicType::ComplexType },
				[] (Object * l, Object * r) {
					Real * a = (Real *) l -> value;
					Complex * b = (Complex *) r -> value;
					Complex * c = new Complex((* a) - (* b).a, -(* b).b);
					return new Object(BasicType::ComplexType, c);
				}
			},
			{
				{ BasicType::ComplexType, BasicType::Int64Type },
				[] (Object * l, Object * r) {
					Complex * a = (Complex *) l -> value;
					Int64 * b = (Int64 *) r -> value;
					Complex * c = new Complex((* a).a - (Real)(* b), (* a).b);
					return new Object(BasicType::ComplexType, c);
				}
			},
			{
				{ BasicType::Int64Type, BasicType::ComplexType },
				[] (Object * l, Object * r) {
					Int64 * a = (Int64 *) l -> value;
					Complex * b = (Complex *) r -> value;
					Complex * c = new Complex((Real)(* a) - (* b).a, -(* b).b);
					return new Object(BasicType::ComplexType, c);
				}
			},
			{
				{ BasicType::CharacterType, BasicType::CharacterType },
				[] (Object * l, Object * r) {
					Character * a = (Character *) l -> value;
					Character * b = (Character *) r -> value;
					Character * c = new Character((* a) - (* b));
					return new Object(BasicType::CharacterType, c);
				}
			}
		};

		Object * applyAddition(Token * t, Object * l, Object * r) {
			if (l -> isString() || r -> isString()) {
				auto search = stringAddition.find({ l -> type, r -> type });
				if (search != stringAddition.end()) {
					auto handler = search -> second;
					return handler(l, r);
				}
				throw EvaluationError(
					"Binary operator '+' doesn't match operands of type '" +
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
				"Binary operator '+' doesn't match operands of type '" +
				l -> getObjectName() + "' and '" +
				r -> getObjectName() + "'!", * t
			);
		}

		Object * applySubtraction(Token * t, Object * l, Object * r) {
			auto search = binarySubtraction.find({ l -> type, r -> type });
			if (search != binarySubtraction.end()) {
				auto handler = search -> second;
				return handler(l, r);
			}
			throw EvaluationError(
				"Binary operator '+' doesn't match operands of type '" +
				l -> getObjectName() + "' and '" +
				r -> getObjectName() + "'!", * t
			);
		}

		Object * applyMultiplication(Token * t, Object * l, Object * r) {
			return nullptr;
		}

		Object * applyDivision(Token * t, Object * l, Object * r) {
			return nullptr;
		}

		Object * applyModulus(Token * t, Object * l, Object * r) {
			return nullptr;
		}

		Processor() = default;
		~Processor() = default;

		public:

		Processor(const Processor &) = delete;
		Processor(Processor &&) = delete;
		Processor & operator = (const Processor &) = delete;
		Processor & operator = (Processor &&) = delete;

		static Processor * self() {
			static Processor instance;
			return & instance;
		}

		Object * applyBinaryOperator(Token * t, Object * l, Object * r) {
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
				case TokenType::modulus: {
					try { return applyModulus(t, l, r); }
					catch (EvaluationError & e) { throw; }
				} break;
				default: break;
			}
			return nullptr;
		}

		Object * applyUnaryOperator(Token * t, Object * o) {
			switch (t -> type) {
				case TokenType::minus: {
					auto search = unaryNegation.find(o -> type);
					if (search != unaryNegation.end()) {
						auto handler = search -> second;
						return handler(o);
					}
					throw EvaluationError(
						"Unary operator '-' doesn't match any operand of type '" +
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
								"Unary operator '+' doesn't match any operand of type '" +
								o -> getObjectName() + "'!", * t
							);
						} break;
					}
				} break;
				case TokenType::exclamationMark: {
					if (o -> type == BasicType::BooleanType) {
						Boolean * b = (Boolean *) o -> value;
						b = new Boolean(!(* b));
						return new Object(o -> type, b);
					} else {
						throw EvaluationError(
							"Unary operator '!' doesn't match any operand of type '" +
							o -> getObjectName() + "'!", * t
						);
					}
				} break;
				case TokenType::tilde: {
					auto search = unaryInversion.find(o -> type);
					if (search != unaryInversion.end()) {
						auto handler = search -> second;
						return handler(o);
					} else {
						throw EvaluationError(
							"Unary operator '~' doesn't match any operand of type '" +
							o -> getObjectName() + "'!", * t
						);	
					}
				} break;
				default: break;
			}
			throw EvaluationError(
				"Unary operator '" + t -> lexeme +
				"' doesn't match any operand of type '" +
				o -> getObjectName() + "'!", * t
			);
		}
		
	};

}

#endif
