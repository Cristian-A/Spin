
/*!
 *
 *    + --------------------------------------- +
 *    |  Token.hpp                              |
 *    |                                         |
 *    |                  Token                  |
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

#ifndef SPINTOKEN
#define SPINTOKEN

#include "../Aliases/Prototypes.hpp"

namespace Spin {

	Token::Token(String l, TokenType t, SizeType p) {
		lexeme = l; type = t; position = p;
	}
	Bool Token::isTypeLiteral() const {
		return type >= TokenType::intLiteral &&
			   type <= TokenType::emptyLiteral;
	}
	Bool Token::isTypeNumeral() const {
		return type >= TokenType::intLiteral &&
			   type <= TokenType::realLiteral;
	}
	Bool Token::isTypeBasicType() const {
		return type == TokenType::basicType;
	}
	Bool Token::isTypeType() const {
		return type == TokenType::classKeyword;
	}
	Bool Token::isTypeBraKet() const {
		return type >= TokenType::braketSymbol &&
			   type <= TokenType::ketbraSymbol;
	}

	TokenRule::TokenRule(Regex p, TokenType t) {
		pattern = p; type = t;
	}

}

#endif
