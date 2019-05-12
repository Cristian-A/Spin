
/*!
 *
 *    + --------------------------------------- +
 *    |  SRule.hpp                              |
 *    |                                         |
 *    |               Syntax Rule               |
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

#ifndef STACKSYNTAXRULE
#define STACKSYNTAXRULE

#include <iostream>
#include <string>

#include "../Aliases/Aliases.hpp"
#include "../Collection/Collection.hpp"
#include "../Token/Token.hpp"

using namespace Collection;

/*! @brief Namespace Stack. */
namespace Stack {

	/*! @brief Class SyntaxRule. */
	class SyntaxRule {

		public:

		StrongList<SyntaxRule *> nextRules = StrongList<SyntaxRule *>();

		Token * token = nullptr;

		SyntaxRule() { }

		SyntaxRule(StrongList<SyntaxRule *> & r, Token * t) {
			nextRules = r;
			token = t;
		}
		SyntaxRule(SyntaxRule * r, Token * t) {
			nextRules.link(r);
			token = t;
		}
		SyntaxRule(Token * t) { token = t; }

		void addNextRule(SyntaxRule * r) {
			nextRules.link(r);
		}

		Boolean matches(Token * t) {
			return t -> type == token -> type;
		}

		SyntaxRule * nextThatMatches(Token * t) {
			for (UInt32 i = 0; i < nextRules.count(); i++) {
				if (nextRules[i] -> matches(t)) {
					return nextRules[i];
				}
			}
			return nullptr;
		}

		Boolean isTerminal() { return nextRules.isEmpty(); }

		Boolean isEmpty() { return nextRules.isEmpty(); }

	};

}

#define Grammar SyntaxRule
#define SRule SyntaxRule

#endif
