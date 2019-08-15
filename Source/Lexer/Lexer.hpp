
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

#include "../Aliases/Aliases.hpp"
#include "../Linker/Linker.hpp"
#include "../Token/Token.hpp"

#include "Regex.hpp"

#define INVERTED "[^A-Za-z0-9_]"

namespace Stack {

	/*!
	 *   @brief Invalid Token Exception.
	 *   Raised when the token is not matched.
	 */
	class InvalidTokenException: public Exception {
		private:
		Linker::FilePosition pos = { 0, 0 };
		String fileName = "";
		public:
		Linker::FilePosition getPosition() { return pos; }
		String getFileName() { return fileName; }
		InvalidTokenException(Linker::FilePosition position, String name):
		Exception(), pos(position), fileName(name) { }
	};

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

		ArrayList<TokenRule> grammar = {

			TokenRule("([ \\t\\n]+)", TokenType::empty),
			TokenRule("(\\/\\*+[^*]*\\*+(?:[^/*][^*]*\\*+)*\\/)", TokenType::comment),

			TokenRule("([0-9]+(?:\\.[0-9]+(?:[eE][0-9]+)?)?i)", TokenType::imaginaryLiteral),
			TokenRule("([0-9]+\\.[0-9]+(?:[eE][0-9]+)?)", TokenType::realLiteral),
			TokenRule("((?:0[x][0-9A-Fa-f]+)|(?:0b[01]+)|(?:0o[0-7]+)|(?:0d[0-9]+)|(?:[0-9]+))", TokenType::intLiteral),
			TokenRule("(\"(?:[^\\\\\"]|\\\\[\"\\\\0abfnrtv]|\\\\0x[0-9A-Fa-f]{2})*\")", TokenType::stringLiteral),
			TokenRule("('(?:[^\\\\]|\\\\0x[0-9A-Fa-f]{2}|\\\\['\\\\0abfnrtv])')", TokenType::charLiteral),
			TokenRule("(#[A-Fa-f0-9]{6}(?:[A-Fa-f0-9][A-Fa-f0-9])?|#[A-Fa-f0-9]{3,4})" INVERTED, TokenType::colourLiteral),
			TokenRule("(true|false)" INVERTED, TokenType::boolLiteral),

			TokenRule("(<[ \\t\\n]*[A-Za-z_][A-Za-z0-9_]*[ \\t\\n]*\\|[ \\t\\n]*[A-Za-z_][A-Za-z0-9_]*[ \\t\\n]*>)", TokenType::braketSymbol),
			TokenRule("(<[ \\t\\n]*[A-Za-z_][A-Za-z0-9_]*[ \\t\\n]*\\|)", TokenType::braSymbol),
			TokenRule("(\\|[ \\t\\n]*[A-Za-z_][A-Za-z0-9_]*[ \\t\\n]*>)", TokenType::ketSymbol),
			
			TokenRule("(<[01]+\\|[01]+>)", TokenType::braketLiteral),
			TokenRule("(<[01]+\\|)", TokenType::braLiteral),
			TokenRule("(\\|[01]+>)", TokenType::ketLiteral),

			TokenRule("(\\:)", TokenType::colon),
			TokenRule("(\\;)", TokenType::semicolon),
			TokenRule("(\\,)", TokenType::comma),
			TokenRule("(\\.)", TokenType::dot),
			TokenRule("(<)", TokenType::minor),
			TokenRule("(>)", TokenType::major),
			TokenRule("(=)", TokenType::equal),
			TokenRule("(\\?)", TokenType::questionMark),
			TokenRule("(\\!)", TokenType::exclamationMark),

			TokenRule("(\\+)", TokenType::plus),
			TokenRule("(-)", TokenType::minus),
			TokenRule("(\\~)", TokenType::tilde),
			TokenRule("(\\*)", TokenType::star),
			TokenRule("(\\\\)", TokenType::backslash),
			TokenRule("(\\/)", TokenType::slash),
			TokenRule("(@)", TokenType::at),
			TokenRule("(|)", TokenType::pipe),
			TokenRule("(#)", TokenType::hashtag),
			TokenRule("(&)", TokenType::ampersand),
			TokenRule("(%)", TokenType::modulus),
			TokenRule("($)", TokenType::dollar),
			TokenRule("(^)", TokenType::hat),

			TokenRule("(\\()", TokenType::openRoundBracket),
			TokenRule("(\\))", TokenType::closeRoundBracket),
			TokenRule("(\\[)", TokenType::openSquareBracket),
			TokenRule("(\\])", TokenType::closeSquareBracket),
			TokenRule("(\\{)", TokenType::openCurlyBracket),
			TokenRule("(\\})", TokenType::closeCurlyBracket),

			TokenRule("(try)" INVERTED, TokenType::tryKeyword),
			TokenRule("(catch)" INVERTED, TokenType::catchKeyword),
			TokenRule("(throw)" INVERTED, TokenType::throwKeyword),
			TokenRule("(throws)" INVERTED, TokenType::throwsKeyword),
			TokenRule("(avoid)" INVERTED, TokenType::avoidKeyword),

			TokenRule("(if)" INVERTED, TokenType::ifKeyword),
			TokenRule("(else)" INVERTED, TokenType::elseKeyword),
			TokenRule("(switch)" INVERTED, TokenType::ifKeyword),
			TokenRule("(case)" INVERTED, TokenType::caseKeyword),
			TokenRule("(default)" INVERTED, TokenType::defaultKeyword),
			TokenRule("(while)" INVERTED, TokenType::whileKeyword),
			TokenRule("(do)" INVERTED, TokenType::doKeyword),
			TokenRule("(loop)" INVERTED, TokenType::loopKeyword),
			TokenRule("(for)" INVERTED, TokenType::forKeyword),
			TokenRule("(repeat)" INVERTED, TokenType::repeatKeyword),
			TokenRule("(until)" INVERTED, TokenType::untilKeyword),
			TokenRule("(break)" INVERTED, TokenType::breakKeyword),
			TokenRule("(continue)" INVERTED, TokenType::continueKeyword),

			TokenRule("(import)" INVERTED, TokenType::importKeyword),
			TokenRule("(func)" INVERTED, TokenType::funcKeyword),
			TokenRule("(proc)" INVERTED, TokenType::procKeyword),
			TokenRule("(static)" INVERTED, TokenType::staticKeyword),
			TokenRule("(class)" INVERTED, TokenType::classKeyword),
			TokenRule("(enumerator)" INVERTED, TokenType::enumKeyword),
			TokenRule("(structure)" INVERTED, TokenType::structKeyword),
			TokenRule("(exception)" INVERTED, TokenType::exceptKeyword),
			TokenRule("(private)" INVERTED, TokenType::privateKeyword),
			TokenRule("(public)" INVERTED, TokenType::publicKeyword),
			TokenRule("(ref)" INVERTED, TokenType::refKeyword),
			TokenRule("(cpy)" INVERTED, TokenType::cpyKeyword),
			TokenRule("(const)" INVERTED, TokenType::constKeyword),
			TokenRule("(null)" INVERTED, TokenType::nullLiteral),
			TokenRule("(nope?)" INVERTED, TokenType::nop),
			TokenRule("(return)" INVERTED, TokenType::returnKeyword),

			TokenRule("([A-Za-z_][A-Za-z0-9_]*)" INVERTED, TokenType::symbol),

		};

		Lexer() = default;
		~Lexer() = default;

		public:

		Lexer(const Lexer &) = delete;
		Lexer(Lexer &&) = delete;
		Lexer & operator = (const Lexer &) = delete;
		Lexer & operator = (Lexer &&) = delete;

		static Lexer * self() {
			static Lexer instance;
			return & instance;
		}

		ArrayList<Token> * tokenise(String * input, String fileName = "Unknown File") {
			// Handle Last Token:
			String data = (* input) + "\n";
			// Handle Single Line Comments:
			data = handleComments(data);
			// Handle EndLines:
			data = RegexTools::replaceMatches("\n", data, " ");
			ArrayList<Token> * tokens = new ArrayList<Token>();
			UInt32 pos = 0;
			Token temp = Token("beginFile", TokenType::beginFile, 0);
			tokens -> push(temp);
			while (data.length() > 0) {
				Boolean tokenised = false;
				for (TokenRule rule : grammar) {
					String result = RegexTools::matchCloseStart(rule.pattern, data);
					if (result.length() > 0) {
						tokenised = true;
						data = data.subString(result.length());
						temp = Token(result, rule.type, pos);
						pos += result.length();
						if (rule.type == TokenType::empty) break;
						if (rule.type == TokenType::comment) break;
						tokens -> push(temp); break;
					}
				}
				if (!tokenised) {
					Linker::FilePosition fp = Linker::getPosition(input, pos);
					throw InvalidTokenException(fp, fileName);
				}
			}
			tokens -> push(Token("endFile", TokenType::endFile, 0));
			tokens -> shrinkToFit();
			return tokens;
		}

	};

}

#endif
