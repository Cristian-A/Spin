
#include "../Common/Header.hpp"

#ifndef SPIN_TOKEN_HPP
#define SPIN_TOKEN_HPP

namespace Spin {

	class Token {
		public:
		enum Type : UInt8 {

			beginFile,

			empty,
			comment,

			basicType,
			customType,
			symbol,
			identifier,

			braketSymbol,
			braSymbol,
			ketSymbol,
			ketbraSymbol,

			intLiteral,
			imaginaryLiteral,
			basisBraLiteral,
			basisKetLiteral,
			realLiteral,
			stringLiteral,
			charLiteral,
			boolLiteral,
			realIdiom,

			arrow,
			doublecolon,
			semicolon,
			colon,
			comma,
			dot,

			/* Low Priority */

			plusEqual,
			minusEqual,
			pipeEqual,
			plus,
			minus,
			pipe,

			/* Medium Priority */

			starEqual,
			slashEqual,
			ampersandEqual,
			modulusEqual,
			dollarEqual,
			star,
			slash,
			ampersand,
			hat,
			modulus,
			dollar,

			minor,
			minorEqual,
			major,
			majorEqual,
			equal,
			equality,
			inequality,
			questionMark,
			exclamationMark,

			AND,
			OR,

			conjugate,
			transpose,
			dagger,

			tilde,
			backslash,

			openParenthesis,
			closeParenthesis,

			openBracket,
			closeBracket,

			openBrace,
			closeBrace,

			varKeyword,
			conKeyword,
			vecKeyword,
			matKeyword,

			ifKeyword,
			elseKeyword,
			swapKeyword,
			whileKeyword,
			doKeyword,
			loopKeyword,
			forKeyword,
			repeatKeyword,
			untilKeyword,
			breakKeyword,
			continueKeyword,
			selfKeyword,

			printKeywork,

			importKeyword,

			funcKeyword,
			procKeyword,

			classKeyword,

			publicModifier,
			hiddenModifier,
			secureModifier,
			immuneModifier,
			staticModifier,
			sharedModifier,

			createSpecifier,
			deleteSpecifier,

			returnKeyword,
			restKeyword,

			newKeyword,
			deleteKeyword,

			invalid,

			endFile

		};
		String lexeme;
		Type type;
		SizeType position;
		Token() = default;
		Token(String lexeme, Type type, SizeType position = 0);
		Boolean isTypeLiteral() const;
		Boolean isTypeNumeral() const;
		Boolean isTypeBasicType() const;
		Boolean isTypeType() const;
		Boolean isTypeBraKet() const;
		Boolean isRoutineKeyword() const;
	};

}

#endif
