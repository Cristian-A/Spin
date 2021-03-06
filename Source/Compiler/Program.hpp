
#include "../Common/Header.hpp"

#ifndef SPIN_PROGRAM_HPP
#define SPIN_PROGRAM_HPP

#include "../Token/Token.hpp"

#include <vector>
#include <unordered_map>

namespace Spin {

	// Never change the order of types
	// since it's used for type check.

	enum Interrupt: UInt8 {
		write = 0xA0,
		writeln = 0x0A,
		read = 0xF0,
		readln = 0x0F,
		sleep = 0xFF,
		clock = 0xC0,
		noise = 0xCA,
	};

	enum Type: UInt8 {

		BooleanType,
		CharacterType,
		ByteType,
		NaturalType,
		IntegerType,
		RealType,
		ImaginaryType,

		ComplexType,
		StringType,

		ArrayType,
		EmptyArray,

		RoutineType,
		LamdaType,

		VoidType,

	};

	class CodeUnit {
		public:
		Array<Token> * tokens;
		String * name;
		String * contents;
		CodeUnit(Array<Token> * tokens,
				 String * name,
				 String * contents);
		~CodeUnit();
	};

	enum ErrorCode: UInt8 {
		flm, lxr, ppr, syx, typ, lgc, evl
	};

	enum OPCode: UInt8 {

		RST, // rest

		PSH, // push constant
		STR, // push string
		TYP, // push type

		LLA, // load lamda address
		ULA, // unload lamda address
		LAM, // lamda call

		GET, // get local
		SET, // set local

		SSF, // set stack frame
		GLF, // get local from stack frame
		SLF, // set local from stack frame

		CTP, // copy temporary
		LTP, // load temporary
		SWP, // swap

		ADD, // addition
		SUB, // subtract
		MUL, // multiply
		DIV, // divide
		MOD, // modulus
		NEG, // negate
		INV, // bitwise inversion
		SGS, // string get subscription
		SSS, // string set subscription
		AGS, // array get subscription
		ASS, // array set subscription
		SCN, // string count
		ACN, // array count

		CCJ, // complex conjugate
		VCJ, // vector conjugate
		MCJ, // matrix conjugate

		PST, // push true
		PSF, // push false
		PSI, // push infinity
		PSU, // push undefined
		PEC, // push empty complex
		PES, // push empty string
		PSA, // push array
		PEA, // push empty array
		POP, // pop
		DHD, // duplicate head
		DSK, // decrease stack

		JMP, // jump
		JIF, // jump if false
		JAF, // jump if false, avoid pop
		JIT, // jump if true
		JAT, // jump if true, avoid pop

		EQL, // equal
		NEQ, // not equal
		GRT, // great
		LSS, // less
		GEQ, // great equal
		LEQ, // less equal

		NOT, // boolean not

		BWA, // bitwise and
		BWO, // bitwise or
		BWX, // bitwise xor
		BSR, // bitwise shift right
		BSL, // bitwise shift left
		BRR, // bitwise rotation right
		BRL, // bitwise rotation left

		CAL, // call
		CLL, // call language
		RET, // return

		CST, // casting

		INT, // interrupt

		HLT, // halt

		// Temporary flags:

		TLT, // temporary lamda tag

	};

	using Types = UInt16;

	union Value {
		Integer integer;
		Pointer pointer;
		Real real;
		Byte byte;
		Boolean boolean;
	};

	struct ByteCode {
		OPCode code = OPCode::RST;
		union {
			SizeType index;
			Value value;
			Type type;
			Types types;
		} as;
	};

	class Program {
		public:
		class Error : Exception {
			private:
			String file;
			String message;
			UInt32 line;
			UInt32 positionStart;
			UInt32 positionEnd;
			ErrorCode error;
			public:
			Error(CodeUnit * c, String m, Token t, ErrorCode e);
			String getFile() const;
			String getMessage() const;
			UInt32 getLine() const;
			UInt32 getPositionStart() const;
			UInt32 getPositionEnd() const;
			ErrorCode getErrorValue() const;
			String getErrorCode() const;
		};
		Program() = default;
		Array<ByteCode> instructions;
		Array<String> strings;
		void serialise(String path) const;
		static Program * from(String path);
	};

	class SourceCode {
		public:
		CodeUnit * main;
		Array<CodeUnit *> * wings;
		Array<String> * libraries;
		SourceCode(CodeUnit * main,
				   Array<CodeUnit *> * wings,
				   Array<String> * libraries);
	};

	enum NativeCodes: UInt16 {

		// Array:



		// Boolean:

		Boolean_random,
		Boolean_string,

		// String:



	};

}

#endif
