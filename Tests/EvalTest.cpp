
/*!
 *
 *    + --------------------------------------- +
 *    |  EvalTest.cpp                           |
 *    |                                         |
 *    |                  Main                   |
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

#include "../Source/Aliases/Aliases.hpp"
#include "../Source/Lexer/Lexer.hpp"
#include "../Source/Parser/Parser.hpp"
#include "../Source/Parser/ASTPrint.hpp"
#include "../Source/Interpreter/Interpreter.hpp"

using namespace std;

using namespace Stack;

Int32 main(Int32 argc, Character * argv[]) {

	cout << "Insert test string: ";
	String test = getInput();
	cout << endl;

	Lexer * lexer = Lexer::self();
	ArrayList<Token> * tokens = nullptr;

	try {
		tokens = lexer -> tokenise(& test, "Virtual File");
	} catch (LexerErrorException & e) {
		cout << "Error in " << e.getFileName() << "!" << endl;
		cout << "Position [row: " << e.getPosition().row << ", ";
		cout << "col: " << e.getPosition().col << "] Invalid Token!" << endl;
		cout << endl << "Press enter to exit. ";
		waitKeyPress();
		return exitFailure;
	}

	cout << "Tokens: " << endl;
	UInt32 i = 1;
	for (Token & token : * tokens) {
		cout << padding << i << " | Type: ";
		cout << padding << token.type;
		cout << " | Token: " << token.lexeme << endl;
		i += 1;
	}

	cout << endl;

	Parser * parser = Parser::self();
	Expression * ex = nullptr;

	try {
		ex = parser -> parse(tokens, & test, "Virtual File");
	} catch (ParseErrorException & p) {
		const ArrayList<SyntaxError> * const e = p.getErrors();
		cout << "Found " << e -> size() << " errors in '"
			 << p.getFileName() << "'!" << endl;
		UInt32 i = 1;
		for (SyntaxError s : * e) {
			FilePosition f = s.getPosition();
			cout << padding << i << " [row: " << f.row
				 << ", col: " << f.col << "]: "
				 << s.getMessage() << endl;
			i += 1;
		}
		cout << endl << "Press enter to exit. ";
		waitKeyPress();
		delete tokens;
		return exitFailure;
	}

	delete tokens;

	if (ex == nullptr) {
		cout << "Syntax Tree Failure!" << endl;
		cout << "Press enter to exit. ";
		waitKeyPress();
		return exitFailure;
	}

	cout << "Syntax Tree:" << endl;
	ASTPrinter * printer = new ASTPrinter();
	cout << printer -> print(ex) << endl;
	delete printer;

	cout << endl;

	// Interpreter Test:

	Interpreter * interpreter = Interpreter::self();
	Object * result = nullptr;

	try {
		result = interpreter -> evaluate(ex, & test, "Virtual File");
	} catch (Exception & e) {
		cout << "Error in file!" << endl;
		cout << "Press enter to exit. ";
		waitKeyPress();
		delete ex;
		return exitFailure;
	}

	delete ex;

	if (result == nullptr) {
		cout << "Evaluation Failure!" << endl;
		cout << "Press enter to exit. ";
		waitKeyPress();
		return exitFailure;
	}

	cout << "ResultType: " << result -> getObjectName() << endl;
	cout << "Result: " << result -> getObjectStringValue() << endl;

	delete result;

	cout << endl << "Press enter to exit. ";
	waitKeyPress();
	
	return exitSuccess;
}
