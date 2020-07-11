
/*!
 *
 *    + --------------------------------------- +
 *    |  Processor.cpp                          |
 *    |                                         |
 *    |            Virtual Processor            |
 *    |                                         |
 *    |  Created by Cristian A.                 |
 *    |  Copyright © MIT. All rights reserved.  |
 *    + --------------------------------------- +
 *
 *    Note: This software is licensed under
 *          the (MIT) Massachusetts Institute
 *          of Technology License.
 *
!*/

#include "Processor.hpp"

#ifndef SPIN_PROCESSOR_CPP
#define SPIN_PROCESSOR_CPP

#include <limits>

#define DefineBinaryTable(A) const Dictionary<Types, Processor::Process> Processor::A
#define DefineUnaryTable(A) const Dictionary<Type, Processor::Mutation> Processor::A

#define binaryCase(T)                       \
	b = stack.pop();                        \
	a = stack.pop();                        \
	stack.push(                             \
		T.find(ip.as.types) -> second(a, b) \
	)

#define unaryCase(T)                        \
	a = stack.pop();                        \
	stack.push(                             \
		T.find(ip.as.type) -> second(a)     \
	)

#define symmetric(A) compose(A, A)

#define makeBinaryFrom(L) [] (Value l, Value r) -> Value L
#define makeUnaryFrom(L) [] (Value r) -> Value L

namespace Spin {

	const Real Processor::infinity = std::numeric_limits<double>::infinity();
	const Real Processor::undefined = std::numeric_limits<double>::quiet_NaN();

	DefineBinaryTable(addition) = {
		{
			compose(Type::CharacterType, Type::CharacterType),
			makeBinaryFrom({
				return { .integer = (Int64)((Int64)(l.byte) + (Int64)(r.byte)) };
			})
		},
		{
			compose(Type::CharacterType, Type::ByteType),
			makeBinaryFrom({
				return { .integer = (Int64)((Int64)(l.byte) + (Int64)(r.byte)) };
			})
		},
		{
			compose(Type::CharacterType, Type::IntegerType),
			makeBinaryFrom({
				return { .integer = (Int64)((Int64)(l.byte) + r.integer) };
			})
		},
		{
			compose(Type::ByteType, Type::CharacterType),
			makeBinaryFrom({
				return { .integer = (Int64)((Int64)(l.byte) + (Int64)(r.byte)) };
			})
		},
		{
			compose(Type::ByteType, Type::ByteType),
			makeBinaryFrom({
				return { .integer = (Int64)((Int64)(l.byte) + (Int64)(r.byte)) };
			})
		},
		{
			compose(Type::ByteType, Type::IntegerType),
			makeBinaryFrom({
				return { .integer = (Int64)((Int64)(l.byte) + r.integer) };
			})
		},
		{
			compose(Type::IntegerType, Type::CharacterType),
			makeBinaryFrom({
				return { .integer = (Int64)(l.integer + (Int64)(r.byte)) };
			})
		},
		{
			compose(Type::IntegerType, Type::ByteType),
			makeBinaryFrom({
				return { .integer = (Int64)(l.integer + (Int64)(r.byte)) };
			})
		},
		{
			compose(Type::IntegerType, Type::IntegerType),
			makeBinaryFrom({
				return { .integer = l.integer + r.integer };
			})
		},
		{
			compose(Type::IntegerType, Type::RealType),
			makeBinaryFrom({
				return { .real = l.integer + r.real };
			})
		},
		{
			compose(Type::RealType, Type::IntegerType),
			makeBinaryFrom({
				return { .real = l.real + r.integer };
			})
		},
		{
			compose(Type::RealType, Type::RealType),
			makeBinaryFrom({
				return { .real = l.real + r.real };
			})
		},	
		{
			compose(Type::ImaginaryType, Type::ImaginaryType),
			makeBinaryFrom({
				return { .real = l.real + r.real };
			})
		},
	};
	DefineBinaryTable(subtraction) = {
		{
			compose(Type::CharacterType, Type::CharacterType),
			makeBinaryFrom({
				return { .integer = (Int64)((Int64)(l.byte) - (Int64)(r.byte)) };
			})
		},
		{
			compose(Type::CharacterType, Type::ByteType),
			makeBinaryFrom({
				return { .integer = (Int64)((Int64)(l.byte) - (Int64)(r.byte)) };
			})
		},
		{
			compose(Type::CharacterType, Type::IntegerType),
			makeBinaryFrom({
				return { .integer = (Int64)((Int64)(l.byte) - r.integer) };
			})
		},
		{
			compose(Type::ByteType, Type::CharacterType),
			makeBinaryFrom({
				return { .integer = (Int64)((Int64)(l.byte) - (Int64)(r.byte)) };
			})
		},
		{
			compose(Type::ByteType, Type::ByteType),
			makeBinaryFrom({
				return { .integer = (Int64)((Int64)(l.byte) - (Int64)(r.byte)) };
			})
		},
		{
			compose(Type::ByteType, Type::IntegerType),
			makeBinaryFrom({
				return { .integer = (Int64)((Int64)(l.byte) - r.integer) };
			})
		},
		{
			compose(Type::IntegerType, Type::CharacterType),
			makeBinaryFrom({
				return { .integer = (Int64)(l.integer - (Int64)(r.byte)) };
			})
		},
		{
			compose(Type::IntegerType, Type::ByteType),
			makeBinaryFrom({
				return { .integer = (Int64)(l.integer - (Int64)(r.byte)) };
			})
		},
		{
			compose(Type::IntegerType, Type::IntegerType),
			makeBinaryFrom({
				return { .integer = l.integer - r.integer };
			})
		},
		{
			compose(Type::IntegerType, Type::RealType),
			makeBinaryFrom({
				return { .real = l.integer - r.real };
			})
		},
		{
			compose(Type::RealType, Type::IntegerType),
			makeBinaryFrom({
				return { .real = l.real - r.integer };
			})
		},
		{
			compose(Type::RealType, Type::RealType),
			makeBinaryFrom({
				return { .real = l.real - r.real };
			})
		},
		{
			compose(Type::ImaginaryType, Type::ImaginaryType),
			makeBinaryFrom({
				return { .real = l.real - r.real };
			})
		},
	};
	DefineBinaryTable(multiplication) = {
		{
			compose(Type::CharacterType, Type::CharacterType),
			makeBinaryFrom({
				return { .integer = (Int64)((Int64)(l.byte) * (Int64)(r.byte)) };
			})
		},
		{
			compose(Type::CharacterType, Type::ByteType),
			makeBinaryFrom({
				return { .integer = (Int64)((Int64)(l.byte) * (Int64)(r.byte)) };
			})
		},
		{
			compose(Type::CharacterType, Type::IntegerType),
			makeBinaryFrom({
				return { .integer = (Int64)((Int64)(l.byte) * r.integer) };
			})
		},
		{
			compose(Type::ByteType, Type::CharacterType),
			makeBinaryFrom({
				return { .integer = (Int64)((Int64)(l.byte) * (Int64)(r.byte)) };
			})
		},
		{
			compose(Type::ByteType, Type::ByteType),
			makeBinaryFrom({
				return { .integer = (Int64)((Int64)(l.byte) * (Int64)(r.byte)) };
			})
		},
		{
			compose(Type::ByteType, Type::IntegerType),
			makeBinaryFrom({
				return { .integer = (Int64)((Int64)(l.byte) * r.integer) };
			})
		},
		{
			compose(Type::IntegerType, Type::CharacterType),
			makeBinaryFrom({
				return { .integer = (Int64)(l.integer * (Int64)(r.byte)) };
			})
		},
		{
			compose(Type::IntegerType, Type::ByteType),
			makeBinaryFrom({
				return { .integer = (Int64)(l.integer * (Int64)(r.byte)) };
			})
		},
		{
			compose(Type::IntegerType, Type::IntegerType),
			makeBinaryFrom({
				return { .integer = l.integer * r.integer };
			})
		},
		{
			compose(Type::IntegerType, Type::RealType),
			makeBinaryFrom({
				return { .real = l.integer * r.real };
			})
		},
		{
			compose(Type::IntegerType, Type::ImaginaryType),
			makeBinaryFrom({
				return { .real = l.integer * r.real };
			})
		},
		{
			compose(Type::RealType, Type::IntegerType),
			makeBinaryFrom({
				return { .real = l.real * r.integer };
			})
		},
		{
			compose(Type::RealType, Type::RealType),
			makeBinaryFrom({
				return { .real = l.real * r.real };
			})
		},
		{
			compose(Type::RealType, Type::ImaginaryType),
			makeBinaryFrom({
				return { .real = l.real * r.real };
			})
		},
		{
			compose(Type::ImaginaryType, Type::IntegerType),
			makeBinaryFrom({
				return { .real = l.real * r.integer };
			})
		},
		{
			compose(Type::ImaginaryType, Type::RealType),
			makeBinaryFrom({
				return { .real = l.real * r.real };
			})
		},
		{
			compose(Type::ImaginaryType, Type::ImaginaryType),
			makeBinaryFrom({
				return { .real = l.real * r.real };
			})
		},
	};
	DefineBinaryTable(division) = {
		{
			compose(Type::CharacterType, Type::CharacterType),
			makeBinaryFrom({
				if (!r.byte) throw Exception();
				return { .integer = (Int64)((Int64)(l.byte) / (Int64)(r.byte)) };
			})
		},
		{
			compose(Type::CharacterType, Type::ByteType),
			makeBinaryFrom({
				if (!r.byte) throw Exception();
				return { .integer = (Int64)((Int64)(l.byte) / (Int64)(r.byte)) };
			})
		},
		{
			compose(Type::CharacterType, Type::IntegerType),
			makeBinaryFrom({
				if (!r.integer) throw Exception();
				return { .integer = (Int64)((Int64)(l.byte) / r.integer) };
			})
		},
		{
			compose(Type::ByteType, Type::CharacterType),
			makeBinaryFrom({
				if (!r.byte) throw Exception();
				return { .integer = (Int64)((Int64)(l.byte) / (Int64)(r.byte)) };
			})
		},
		{
			compose(Type::ByteType, Type::ByteType),
			makeBinaryFrom({
				if (!r.byte) throw Exception();
				return { .integer = (Int64)((Int64)(l.byte) / (Int64)(r.byte)) };
			})
		},
		{
			compose(Type::ByteType, Type::IntegerType),
			makeBinaryFrom({
				if (!r.integer) throw Exception();
				return { .integer = (Int64)((Int64)(l.byte) / r.integer) };
			})
		},
		{
			compose(Type::IntegerType, Type::CharacterType),
			makeBinaryFrom({
				if (!r.byte) throw Exception();
				return { .integer = (Int64)(l.integer / (Int64)(r.byte)) };
			})
		},
		{
			compose(Type::IntegerType, Type::ByteType),
			makeBinaryFrom({
				if (!r.byte) throw Exception();
				return { .integer = (Int64)(l.integer / (Int64)(r.byte)) };
			})
		},
		{
			compose(Type::IntegerType, Type::IntegerType),
			makeBinaryFrom({
				if (!r.integer) throw Exception();
				return { .integer = l.integer / r.integer };
			})
		},
		{
			compose(Type::IntegerType, Type::RealType),
			makeBinaryFrom({
				return { .real = (Real)(l.integer) / r.real };
			})
		},
		{
			compose(Type::IntegerType, Type::ImaginaryType),
			makeBinaryFrom({
				return { .real = (Real)(l.integer) / r.real };
			})
		},
		{
			compose(Type::RealType, Type::IntegerType),
			makeBinaryFrom({
				return { .real = l.real / (Real)(r.integer) };
			})
		},
		{
			compose(Type::RealType, Type::RealType),
			makeBinaryFrom({
				return { .real = l.real / r.real };
			})
		},
		{
			compose(Type::RealType, Type::ImaginaryType),
			makeBinaryFrom({
				return { .real = l.real / r.real };
			})
		},
		{
			compose(Type::ImaginaryType, Type::IntegerType),
			makeBinaryFrom({
				return { .real = l.real / (Real)(r.integer) };
			})
		},
		{
			compose(Type::ImaginaryType, Type::RealType),
			makeBinaryFrom({
				return { .real = l.real / r.real };
			})
		},
		{
			compose(Type::ImaginaryType, Type::ImaginaryType),
			makeBinaryFrom({
				return { .real = l.real / r.real };
			})
		},
	};
	DefineBinaryTable(modulus) = {
		{
			compose(Type::CharacterType, Type::CharacterType),
			makeBinaryFrom({
				if (!r.byte) throw Exception();
				return { .integer = (Int64)((Int64)(l.byte) % (Int64)(r.byte)) };
			})
		},
		{
			compose(Type::CharacterType, Type::ByteType),
			makeBinaryFrom({
				if (!r.byte) throw Exception();
				return { .integer = (Int64)((Int64)(l.byte) % (Int64)(r.byte)) };
			})
		},
		{
			compose(Type::CharacterType, Type::IntegerType),
			makeBinaryFrom({
				if (!r.integer) throw Exception();
				return { .integer = (Int64)((Int64)(l.byte) % r.integer) };
			})
		},
		{
			compose(Type::ByteType, Type::CharacterType),
			makeBinaryFrom({
				if (!r.byte) throw Exception();
				return { .integer = (Int64)((Int64)(l.byte) % (Int64)(r.byte)) };
			})
		},
		{
			compose(Type::ByteType, Type::ByteType),
			makeBinaryFrom({
				if (!r.byte) throw Exception();
				return { .integer = (Int64)((Int64)(l.byte) % (Int64)(r.byte)) };
			})
		},
		{
			compose(Type::ByteType, Type::IntegerType),
			makeBinaryFrom({
				if (!r.integer) throw Exception();
				return { .integer = (Int64)((Int64)(l.byte) % r.integer) };
			})
		},
		{
			compose(Type::IntegerType, Type::CharacterType),
			makeBinaryFrom({
				if (!r.byte) throw Exception();
				return { .integer = (Int64)(l.integer % (Int64)(r.byte)) };
			})
		},
		{
			compose(Type::IntegerType, Type::ByteType),
			makeBinaryFrom({
				if (!r.byte) throw Exception();
				return { .integer = (Int64)(l.integer % (Int64)(r.byte)) };
			})
		},
		{
			compose(Type::IntegerType, Type::IntegerType),
			makeBinaryFrom({
				if (!r.integer) throw Exception();
				return { .integer = l.integer % r.integer };
			})
		},
	};

	DefineBinaryTable(bitwiseAND) = {
		{
			compose(Type::IntegerType, Type::IntegerType),
			makeBinaryFrom({
				return { .integer = l.integer & r.integer };
			})
		},
		{
			compose(Type::ByteType, Type::ByteType),
			makeBinaryFrom({
				return { .byte = (Byte)(l.byte & r.byte) };
			})
		},
		{
			compose(Type::CharacterType, Type::CharacterType),
			makeBinaryFrom({
				return { .byte = (Byte)(l.byte & r.byte) };
			})
		}
	};
	DefineBinaryTable(bitwiseOR) = {
		{
			compose(Type::IntegerType, Type::IntegerType),
			makeBinaryFrom({
				return { .integer = l.integer | r.integer };
			})
		},
		{
			compose(Type::ByteType, Type::ByteType),
			makeBinaryFrom({
				return { .byte = (Byte)(l.byte | r.byte) };
			})
		},
		{
			compose(Type::CharacterType, Type::CharacterType),
			makeBinaryFrom({
				return { .byte = (Byte)(l.byte | r.byte) };
			})
		}
	};
	DefineBinaryTable(bitwiseXOR) = {
		{
			compose(Type::IntegerType, Type::IntegerType),
			makeBinaryFrom({
				return { .integer = l.integer ^ r.integer };
			})
		},
		{
			compose(Type::ByteType, Type::ByteType),
			makeBinaryFrom({
				return { .byte = (Byte)(l.byte ^ r.byte) };
			})
		},
		{
			compose(Type::CharacterType, Type::CharacterType),
			makeBinaryFrom({
				return { .byte = (Byte)(l.byte ^ r.byte) };
			})
		},
	};

	DefineUnaryTable(negation) = {
		{ Type::CharacterType, makeUnaryFrom({ return { .integer = - r.byte }; }) },
		{      Type::ByteType, makeUnaryFrom({ return { .integer = - r.byte }; }) },
		{   Type::IntegerType, makeUnaryFrom({ return { .integer = - r.integer }; }) },
		{      Type::RealType, makeUnaryFrom({ return { .real = - r.real }; }) },
		{ Type::ImaginaryType, makeUnaryFrom({ return { .real = - r.real }; }) },
	};

	DefineBinaryTable(inequality) = { };
	DefineBinaryTable(equality) = { };

	DefineBinaryTable(major) = { };
	DefineBinaryTable(majorEqual) = { };
	DefineBinaryTable(minor) = { };
	DefineBinaryTable(minorEqual) = { };

	void Processor::run(Program * program) {
		if (!program) return;
		instructions = program -> instructions;
		literals = program -> literals;
		// Main:
		Value a, b;
		for (ByteCode ip : instructions) {
			switch (ip.code) {
				case OPCode::RST: break;
				case OPCode::CNS: stack.push(literals[ip.as.index]); break;
				case OPCode::ADD: binaryCase(addition); break;
				case OPCode::SUB: binaryCase(subtraction); break;
				case OPCode::MUL: binaryCase(multiplication); break;
				case OPCode::DIV: break;
				case OPCode::MOD: break;
				case OPCode::NEG: unaryCase(negation); break;
				case OPCode::INV:
					if (ip.as.type == Type::IntegerType) {
						a = stack.pop();
						stack.push({ .integer = ~ a.integer });
					} else {
						a = stack.pop();
						stack.push({ .byte = (Byte)(~ a.byte) });
					}
				break;
				case OPCode::PST: stack.push({ .boolean = true }); break;
				case OPCode::PSF: stack.push({ .boolean = false }); break;
				case OPCode::PSI: stack.push({ .real = infinity }); break;
				case OPCode::PSU: stack.push({ .real = undefined }); break;
				case OPCode::EQL: binaryCase(equality); break;
				case OPCode::NEQ: binaryCase(inequality); break;
				case OPCode::GRT: binaryCase(major); break;
				case OPCode::GEQ: binaryCase(majorEqual); break;
				case OPCode::LSS: binaryCase(minor); break;
				case OPCode::LEQ: binaryCase(minorEqual); break;
				case OPCode::NOT:
					if (ip.as.type == Type::BooleanType) {
						stack.push({ .boolean = !(stack.pop().boolean) });
					} else stack.push({ .boolean = !(stack.pop().integer) });
				break;
				case OPCode::AND:
					b = stack.pop();
					a = stack.pop();
					stack.push({ .boolean = a.boolean && b.boolean });
				break;
				case OPCode::ORR:
					b = stack.pop();
					a = stack.pop();
					stack.push({ .boolean = a.boolean || b.boolean });
				break;
				case OPCode::BWA: binaryCase(bitwiseAND); break;
				case OPCode::BWO: binaryCase(bitwiseOR); break;
				case OPCode::BWX: binaryCase(bitwiseXOR); break;
				case OPCode::RET: break;
				case OPCode::HLT: break; // TODO: set 'return;'.
				default: break; // TODO: Exception.
			}
		}
		while (!stack.isEmpty()) {
			std::cout << "    " << (Int64)stack.pop().integer << std::endl;
		}
		std::cout << std::endl;
		// Free:
		stack.clear();
	}

}

#endif
