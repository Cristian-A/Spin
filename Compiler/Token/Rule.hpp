
/*!
 *
 *    + --------------------------------------- +
 *    |  Rule.hpp                               |
 *    |                                         |
 *    |                   Rule                  |
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

#ifndef STACKRULE
#define STACKRULE

#include <iostream>
#include <string>

#include "Token.hpp"

using std::string = String;

/*! @brief Namespace Stack */
namespace StackCompiler {

	/*! @brief Grammar Class. */
	class Rule {

	public:

		TokenType type = empty;
		String pattern = "";

		Rule(String pattern, TokenType type) {
			this.pattern = pattern;
			this.type = type;
		}

	};

}

#endif
