
/*!
 *
 *    + --------------------------------------- +
 *    |  Decompiler.cpp                         |
 *    |                                         |
 *    |               Decompiler                |
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

#include "Decompiler.hpp"

#ifndef SPIN_DECOMPILER_CPP
#define SPIN_DECOMPILER_CPP

#include <vector>

#define reset "\x1B[0m"

namespace Spin {

	const String Decompiler::colours[] = {
		   [Decompiler::Colour::red] = { "\x1B[38;5;160m" },
		[Decompiler::Colour::yellow] = { "\x1B[38;5;220m" },
		 [Decompiler::Colour::white] = { "\x1B[38;5;15m" },
		 [Decompiler::Colour::black] = { "\x1B[38;5;0m" },
		[Decompiler::Colour::orange] = { "\x1B[38;5;202m" },
		  [Decompiler::Colour::blue] = { "\x1B[38;5;33m" },
		 [Decompiler::Colour::green] = { "\x1B[38;5;34m" },
		[Decompiler::Colour::purple] = { "\x1B[38;5;164m" },
		  [Decompiler::Colour::pink] = { "\x1B[38;5;207m" },
		  [Decompiler::Colour::gray] = { "\x1B[38;5;250m" },
		   [Decompiler::Colour::sky] = { "\x1B[38;5;14m" },
		 [Decompiler::Colour::acqua] = { "\x1B[38;5;30m" },
		 [Decompiler::Colour::peach] = { "\x1B[38;5;211m" },
	};

	void Decompiler::tableOP(String o, String s) {
		if (s.length() > 16) {
			s = "\"" + s.substr(0, 15) + "...\"";
		} else {
			s = "\"" + s + "\"";
		}
		OStream << "    " << colours[Colour::green] << o << reset
				<< "    " << colours[Colour::acqua] << s << reset << endLine;
	}
	void Decompiler::aloneOP(String o, Colour c, String h) {
		OStream << "    " << colours[c] << o << reset
				<< "                        " << colours[Colour::gray]
				<< "! " << h << reset << endLine;
	}
	void Decompiler::constOP(String o, Int64 i, Colour c) {
		OStream << "    " << colours[c] << o << reset
				<< "    " << colours[Colour::acqua]
				<< upperCase << hexadecimal << i << reset << endLine;
	}
	void Decompiler::typesOP(String o, Types x, Colour c, String h) {
		Type a = (Type)((x & 0xFF00) >> 8);
		Type b = (Type)(x & 0x00FF);
		Colour w = (a <= Type::ImaginaryType ? Colour::orange : Colour::pink);
		Colour k = (b <= Type::ImaginaryType ? Colour::orange : Colour::pink);
		OStream << "    " << colours[c] << o << reset
				<< "    " << colours[w] << resolve(a)
				<< reset << ", " << colours[k]
				<< resolve(b) << reset
				<< "            " << colours[Colour::gray]
				<< "! " << h << reset << endLine;
	}
	void Decompiler::unaryOP(String o, Type x, Colour c, String h) {
		Colour a = (x <= Type::ImaginaryType ? Colour::orange : Colour::pink);
		OStream << "    " << colours[c] << o << reset
				<< "    " << colours[a]
				<< resolve(x) << reset
				<< "                 " << colours[Colour::gray]
				<< "! " << h << reset << endLine;
	}
	void Decompiler::jmptoOP(String o, SizeType x, String h) {
		OStream << "    " << colours[Colour::red] << o << reset
				<< "    " << colours[Colour::acqua]
				<< upperCase << hexadecimal
				<< padding(16) << x << reset
				<< "    " << colours[Colour::gray]
				<< "! " << h << reset << endLine;
	}

	String Decompiler::resolve(Type type) {
		switch (type) {
			case Type::BooleanType: return "BLN";
			case Type::CharacterType: return "CHR";
			case Type::ByteType: return "BYT";
			case Type::IntegerType: return "INT";
			case Type::RealType: return "REA";
			case Type::ImaginaryType: return "IMG";
			case Type::ComplexType: return "CPX";
			case Type::StringType: return "STR";
			case Type::ArrayType: return "ARR";
			case Type::VectorType: return "VEC";
			case Type::ClassType: return "DEF";
			case Type::InstanceType: return "INS";
			case Type::VoidType: return "VOD";
			default: return "UNK";
		}
	}

	void Decompiler::decompile(Program * program, SizeType index) {
		const ByteCode byte = program -> instructions.at(index);
		switch (byte.code) {
			case OPCode::RST: aloneOP("RST", Colour::yellow, "rest"); break;
			case OPCode::CNS: constOP("CNS", byte.as.value.integer, Colour::green); break;
			case OPCode::STR: tableOP("STR", program -> strings.at(byte.as.index)); break;
			case OPCode::GET: constOP("GET", byte.as.index, Colour::blue); break;
			case OPCode::SET: constOP("SET", byte.as.index, Colour::blue); break;
			case OPCode::SWP: aloneOP("SWP", Colour::blue, "swap"); break;
			case OPCode::ADD: typesOP("ADD", byte.as.types, Colour::blue, "addition"); break;
			case OPCode::SUB: typesOP("SUB", byte.as.types, Colour::blue, "subtraction"); break;
			case OPCode::MUL: typesOP("MUL", byte.as.types, Colour::blue, "multiplication"); break;
			case OPCode::DIV: typesOP("DIV", byte.as.types, Colour::blue, "division"); break;
			case OPCode::MOD: typesOP("MOD", byte.as.types, Colour::blue, "modulus"); break;
			case OPCode::NEG: unaryOP("NEG", byte.as.type, Colour::purple, "negation"); break;
			case OPCode::INV: unaryOP("INV", byte.as.type, Colour::purple, "inversion"); break;
			case OPCode::SSC: aloneOP("SSC", Colour::purple, "string subscription"); break;
			case OPCode::CCJ: aloneOP("CCJ", Colour::purple, "complex conjugate"); break;
			case OPCode::VCJ: aloneOP("VCJ", Colour::purple, "vector conjugate"); break;
			case OPCode::MCJ: aloneOP("VCJ", Colour::purple, "matrix conjugate"); break;
			case OPCode::PST: aloneOP("PST", Colour::yellow, "push true"); break;
			case OPCode::PSF: aloneOP("PSF", Colour::yellow, "push false"); break;
			case OPCode::PSI: aloneOP("PSI", Colour::yellow, "push infinity"); break;
			case OPCode::PSU: aloneOP("PSU", Colour::yellow, "push undefined"); break;
			case OPCode::PEC: aloneOP("PEC", Colour::yellow, "push empty Complex"); break;
			case OPCode::PES: aloneOP("PES", Colour::yellow, "push empty String"); break;
			case OPCode::POP: aloneOP("POP", Colour::yellow, "pop"); break;
			case OPCode::DSK: constOP("DSK", byte.as.value.integer, Colour::yellow); break;
			case OPCode::JMP: jmptoOP("JMP", byte.as.index, "jump"); break;
			case OPCode::JMB: jmptoOP("JMB", byte.as.index, "jump backwards"); break;
			case OPCode::JIF: jmptoOP("JIF", byte.as.index, "jump if false"); break;
			case OPCode::JAF: jmptoOP("JAF", byte.as.index, "jump if false, avoid pop"); break;
			case OPCode::JIT: jmptoOP("JIT", byte.as.index, "jump if true"); break;
			case OPCode::JAT: jmptoOP("JAT", byte.as.index, "jump if true, avoid pop"); break;
			case OPCode::EQL: typesOP("EQL", byte.as.types, Colour::orange, "equal"); break;
			case OPCode::NEQ: typesOP("NEQ", byte.as.types, Colour::orange, "not equal"); break;
			case OPCode::GRT: typesOP("GRT", byte.as.types, Colour::orange, "great"); break;
			case OPCode::GEQ: typesOP("GEQ", byte.as.types, Colour::orange, "great equal"); break;
			case OPCode::LSS: typesOP("LSS", byte.as.types, Colour::orange, "less"); break;
			case OPCode::LEQ: typesOP("LEQ", byte.as.types, Colour::orange, "less equal"); break;
			case OPCode::NOT: aloneOP("NOT", Colour::yellow, "logic not"); break;
			case OPCode::BWA: typesOP("BWA", byte.as.types, Colour::blue, "bitwise and"); break;
			case OPCode::BWO: typesOP("BWO", byte.as.types, Colour::blue, "bitwise or"); break;
			case OPCode::BWX: typesOP("BWX", byte.as.types, Colour::blue, "bitwise xor"); break;
			case OPCode::CAL: jmptoOP("CAL", byte.as.index, "call"); break;
			case OPCode::RET: aloneOP("RET", Colour::red, "return"); break;
			case OPCode::CST: typesOP("CST", byte.as.types, Colour::orange, "cast"); break;
			case OPCode::PRN: unaryOP("PRN", byte.as.type, Colour::peach, "print"); break;
			case OPCode::NLN: aloneOP("NLN", Colour::peach, "new line"); break;
			case OPCode::HLT: aloneOP("HLT", Colour::red, "halt"); break;
			default: break;
		}
		OStream << decimal;
	}
	void Decompiler::decompile(Program * program) {
		OStream << endLine;
		for (SizeType i = 0; i < program -> instructions.size(); i += 1) {
			decompile(program, i);
		}
		OStream << endLine;
	}

}

#endif
