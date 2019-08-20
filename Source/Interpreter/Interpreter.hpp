
/*!
 *
 *    + --------------------------------------- +
 *    |  Interpreter.hpp                        |
 *    |                                         |
 *    |            Stack Interpreter            |
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

#ifndef STACKINTERPRETER
#define STACKINTERPRETER

#include "../Aliases/Aliases.hpp"
#include "../Parser/ASTree.hpp"

#include "Processor.hpp"
#include "Converter.hpp"

namespace Stack {

	class InterpreterErrorException: public Exception {
		private:
		const String _message;
		const FilePosition _position;
		const String _fileName;
		public:
		const String & getMessage() const { return _message; }
		const FilePosition & getPosition() const { return _position; }
		const String & getFileName() const { return _fileName; }
		InterpreterErrorException(String message, FilePosition position, String name):
		Exception(),  _message(message), _position(position), _fileName(name) { }
	};

	class Interpreter: public Expression::Visitor {

		private:

		String fileName = "";
		String * input = nullptr;

		Object * value = nullptr;

		Processor * CPU = Processor::self();

		void setValue(Object * o) {
			if (value == o) return;
			if (value != nullptr) delete value;
			value = o;
		}

		void visitBinaryExpression(Binary * e) override {
			try {
				evaluateExpression(e -> l);
				Object * l = value;
				evaluateExpression(e -> r);
				Object * r = value;
				setValue(CPU -> applyBinaryOperator(e -> o, l, r));
			} catch (EvaluationError & e) { throw; }
		}
		void visitAssignmentExpression(Assignment * e) override { }
		void visitCallExpression(Call * e) override { }
		void visitGetExpression(Get * e) override { }
		void visitGroupingExpression(Grouping * e) override {
			try { evaluateExpression(e -> expression); }
			catch (EvaluationError & e) { throw; }
		}
		void visitLiteralExpression(Literal * e) override {
			try {
				if (e -> object == nullptr) {
					e -> object = Converter::literalToObject(e -> token);
				}
				setValue(e -> object);
			} catch (EvaluationError & e) { throw; }
		}
		void visitLogicalExpression(Logical * e) override { }
		void visitSetExpression(Set * e) override { }
		void visitSuperExpression(Super * e) override { }
		void visitThisExpression(This * e) override { }
		void visitUnaryExpression(Unary * e) override {
			try {
				evaluateExpression(e -> r);
				setValue(CPU -> applyUnaryOperator(e -> o, value));
			} catch (EvaluationError & e) { throw; }
		}
		void visitVariableExpression(Variable * e) override { }

		void evaluateExpression(Expression * e) {
			try { e -> accept(this); }
			catch (EvaluationError & e) { throw; }
		}

		Interpreter() = default;
		~Interpreter() = default;

		public:

		Interpreter(const Interpreter &) = delete;
		Interpreter(Interpreter &&) = delete;
		Interpreter & operator = (const Interpreter &) = delete;
		Interpreter & operator = (Interpreter &&) = delete;

		static Interpreter * self() {
			static Interpreter instance;
			return & instance;
		}

		Object * evaluate(Expression * expression,
						  String * input = nullptr,
						  String fileName = "Unknown File") {
			this -> input = input;
			this -> fileName = fileName;
			try {
				expression -> accept(this);
			} catch (EvaluationError & e) {
				const UInt32 cursor = e.getToken().position;
				FilePosition fp = Linker::getPosition(input, cursor);
				throw InterpreterErrorException(
					e.getMessage(), fp, fileName
				);
			}
			return value;
		}

	};

}

#endif
