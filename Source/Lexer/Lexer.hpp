
/*!
 *
 *    + --------------------------------------- +
 *    |  Lexer.hpp                              |
 *    |                                         |
 *    |                  Lexer                  |
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

#ifndef STACKLEXER
#define STACKLEXER

#include <iostream>
#include <string>
#include <regex>

#include "../Aliases/Aliases.hpp"
#include "../Collection/Collection.hpp"
#include "../Token/Token.hpp"
#include "../Token/TRule.hpp"

#include "Regex.hpp"

using namespace Collection;
using namespace RegexTools;

#define INVERTED "[^A-Za-z0-9_]"

/*! @brief Namespace Stack. */
namespace Stack {

	/*!
	 *   @brief Invalid Token Exception.
	 *   Raised when the token is not matched.
	 */
	class InvalidTokenException: public Exception {
		private: UInt32 position = 0;
		public: UInt32 getPosition() { return position; }
		InvalidTokenException(UInt32 character):
		Exception(), position(character) { }
	};

	/*! @brief Lexer Class. */
	class Lexer {

		private:

		String handleComments(String input) {
			if (input.length() == 0) return input;
			try {
				Regex regex("\\/[\\/]+.*");
				SMatch match;
				regexSearch(input, match, regex);
				while (match.size() >= 1) {
					UInt32 len = match.str(0).length();
					UInt32 pos = match.position(0);
					for (UInt32 i = pos; i < pos + len; i++) {
						input[i] = ' ';
					}
					regexSearch(input, match, regex);
				}
			} catch (RegexError & e) { }
			return input;
		}

		StrongList<TokenRule> grammar = StrongList<TokenRule>();

		public:

		String input = "";

		Lexer(String data = "") {

			input = data;

			const UInt32 tokenCount = 67;

			TokenRule rules[tokenCount] = {

				TokenRule("([ \\t\\n]+)", empty),
				TokenRule("(\\/\\*+[^*]*\\*+(?:[^/*][^*]*\\*+)*\\/)", comment),

				TokenRule("(-?[0-9]+\\.[0-9]+)", realLiteral),
				TokenRule("(-?[0-9]+)", integerLiteral),
				TokenRule("(\"(?:[^\\\\\"]|\\\\[\"\\\\0abfnrtv]|\\\\x[0-9A-Fa-f][0-9A-Fa-f])*\")", stringLiteral),
				TokenRule("('(?:[^\\\\]|\\\\x[0-9A-Fa-f][0-9A-Fa-f]|\\\\['\\\\0abfnrtv])')", charLiteral),
				TokenRule("(true|false)" INVERTED, boolLiteral),

				TokenRule("(\\:)", colon),
				TokenRule("(\\;)", semicolon),
				TokenRule("(\\,)", comma),
				TokenRule("(\\.)", dot),
				TokenRule("(<)", minor),
				TokenRule("(>)", major),
				TokenRule("(=)", equal),
				TokenRule("(\\?)", questionMark),
				TokenRule("(\\!)", exclamationMark),

				TokenRule("(\\+)", plus),
				TokenRule("(-)", minus),
				TokenRule("(\\*)", star),
				TokenRule("(\\\\)", backslash),
				TokenRule("(\\/)", slash),
				TokenRule("(@)", at),
				TokenRule("(|)", pipe),
				TokenRule("(#)", hashtag),
				TokenRule("(&)", ampersand),
				TokenRule("(%)", modulus),
				TokenRule("($)", dollar),
				TokenRule("(^)", hat),

				TokenRule("(\\()", openRoundBracket),
				TokenRule("(\\))", closeRoundBracket),
				TokenRule("(\\[)", openSquareBracket),
				TokenRule("(\\])", closeSquareBracket),
				TokenRule("(\\{)", openCurlyBracket),
				TokenRule("(\\})", closeCurlyBracket),

				TokenRule("(try)" INVERTED, tryKeyword),
				TokenRule("(catch)" INVERTED, catchKeyword),
				TokenRule("(throw)" INVERTED, throwKeyword),
				TokenRule("(throws)" INVERTED, throwsKeyword),
				TokenRule("(avoid)" INVERTED, avoidKeyword),

				TokenRule("(if)" INVERTED, ifKeyword),
				TokenRule("(else)" INVERTED, elseKeyword),
				TokenRule("(switch)" INVERTED, ifKeyword),
				TokenRule("(case)" INVERTED, caseKeyword),
				TokenRule("(default)" INVERTED, defaultKeyword),
				TokenRule("(while)" INVERTED, whileKeyword),
				TokenRule("(do)" INVERTED, doKeyword),
				TokenRule("(loop)" INVERTED, loopKeyword),
				TokenRule("(for)" INVERTED, forKeyword),
				TokenRule("(repeat)" INVERTED, repeatKeyword),
				TokenRule("(until)" INVERTED, untilKeyword),
				TokenRule("(break)" INVERTED, breakKeyword),
				TokenRule("(continue)" INVERTED, continueKeyword),

				TokenRule("(func)" INVERTED, funcKeyword),
				TokenRule("(proc)" INVERTED, procKeyword),
				TokenRule("(static)" INVERTED, staticKeyword),
				TokenRule("(class)" INVERTED, classKeyword),
				TokenRule("(enumerator)" INVERTED, enumKeyword),
				TokenRule("(structure)" INVERTED, structKeyword),
				TokenRule("(exception)" INVERTED, exceptKeyword),
				TokenRule("(private)" INVERTED, privateKeyword),
				TokenRule("(public)" INVERTED, publicKeyword),
				TokenRule("(inout)" INVERTED, inoutKeyword),
				TokenRule("(const)" INVERTED, constKeyword),
				TokenRule("(null)" INVERTED, nullKeyword),
				TokenRule("(nope?)" INVERTED, nop),
				TokenRule("(return)" INVERTED, returnKeyword),

				TokenRule("([A-Za-z_][A-Za-z0-9_]*)" INVERTED, identifier),

			};

			for (UInt32 i = 0; i < tokenCount; i++) {
				TokenRule temp = rules[i];
				grammar.link(temp);
			}

		}

		StrongList<Token> tokenize() {
			// Handle Last Token:
			String data = input + "\n";
			// Handle Single Line Comments:
			data = handleComments(data);
			// Handle EndLines:
			data = replaceMatches("\n", data, " ");
			StrongList<Token> tokens = StrongList<Token>();
			UInt32 pos = 0;
			Token temp = Token("beginFile", beginFile, 0);
			tokens.link(temp);
			while (data.length() > 0) {
				Boolean tokenized = false;
				for (UInt32 i = 0; i < grammar.count(); i++) {
					String result = matchCloseStart(grammar[i].pattern, data);
					if (result.length() > 0) {
						tokenized = true;
						data = data.subString(result.length());
						temp = Token(result, grammar[i].type, pos);
						pos += result.length();
						if (grammar[i].type == empty) break;
						if (grammar[i].type == comment) break;
						tokens.link(temp);
						break;
					}
				}
				if (!tokenized) throw InvalidTokenException(pos);
			}
			temp = Token("endFile", endFile, 0);
			tokens.link(temp);
			return tokens;
		}

	};

}

#endif
