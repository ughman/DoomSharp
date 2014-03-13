using System;
using System.Reflection;
using System.Reflection.Emit;
using System.Collections.Generic;

namespace DoomSharp
{
    public sealed class CodeParser
    {
        private Scanner scanner;

        public CodeParser(Scanner scanner)
        {
            if (scanner == null)
                throw new ArgumentNullException("scanner");
            this.scanner = scanner;
        }

        public Statement ParseBlock()
        {
            BlockStatement block = new BlockStatement();
            while (!scanner.TryGetEnd())
            {
                block.Statements.Add(ParseStatement());
            }
            return block;
        }

        private Statement ParseStatement()
        {
            if (scanner.TryGetIdentifier("if"))
            {
                scanner.GetDelimiter("(");
                Expression condition = ParseExpression();
                scanner.GetDelimiter(")");
                Statement thenstatement = ParseStatement();
                Statement elsestatement = new NullStatement();
                if (scanner.TryGetIdentifier("else"))
                {
                    elsestatement = ParseStatement();
                }
                return new IfStatement(condition,thenstatement,elsestatement);
            }
            else if (scanner.TryGetIdentifier("while"))
            {
                scanner.GetDelimiter("(");
                Expression condition = ParseExpression();
                scanner.GetDelimiter(")");
                Statement loopstatement = ParseStatement();
                Statement elsestatement = new NullStatement();
                if (scanner.TryGetIdentifier("else"))
                {
                    elsestatement = ParseStatement();
                }
                return new WhileStatement(condition,loopstatement,elsestatement);
            }
            else if (scanner.TryGetIdentifier("foreach"))
            {
                scanner.GetDelimiter("(");
                string variabletype;
                string variablename;
                scanner.GetIdentifier(out variabletype);
                scanner.GetIdentifier(out variablename);
                scanner.GetIdentifier("in");
                Expression collection = ParseExpression();
                scanner.GetDelimiter(")");
                Statement loopstatement = ParseStatement();
                Statement elsestatement = new NullStatement();
                if (scanner.TryGetIdentifier("else"))
                {
                    elsestatement = ParseStatement();
                }
                return new ForEachStatement(variabletype,variablename,collection,loopstatement,elsestatement);
            }
            else if (scanner.TryGetIdentifier("var"))
            {
                string variablename;
                scanner.GetIdentifier(out variablename);
                scanner.GetDelimiter("=");
                Expression expression = ParseExpression();
                scanner.GetDelimiter(";");
                return new VarStatement(variablename,expression);
            }
            else if (scanner.TryGetDelimiter("{"))
            {
                CodeParser subparser = new CodeParser(scanner.ScanAcross("{","}"));
                return subparser.ParseBlock();
            }
            else if (scanner.TryGetDelimiter(";"))
            {
                return new NullStatement();
            }
            else
            {
                Expression expression = ParseExpression();
                scanner.GetDelimiter(";");
                return new ExpressionStatement(expression);
            }
        }

        private Expression ParseExpression()
        {
            return ParseAssigmentExpression();
        }

        private Expression ParseAssigmentExpression()
        {
            Expression left = ParseLogicalOrExpression();
            if (scanner.TryGetDelimiter("="))
            {
                Expression right = ParseAssigmentExpression();
                return new AssignmentExpression(left,right);
            }
            else if (scanner.TryGetDelimiter("+="))
            {
                Expression right = ParseAssigmentExpression();
                right = new AddExpression(left,right);
                return new AssignmentExpression(left,right);
            }
            else if (scanner.TryGetDelimiter("-="))
            {
                Expression right = ParseAssigmentExpression();
                right = new SubtractExpression(left,right);
                return new AssignmentExpression(left,right);
            }
            else if (scanner.TryGetDelimiter("*="))
            {
                Expression right = ParseAssigmentExpression();
                right = new MultiplyExpression(left,right);
                return new AssignmentExpression(left,right);
            }
            else if (scanner.TryGetDelimiter("/="))
            {
                Expression right = ParseAssigmentExpression();
                right = new DivideExpression(left,right);
                return new AssignmentExpression(left,right);
            }
            else if (scanner.TryGetDelimiter("%="))
            {
                Expression right = ParseAssigmentExpression();
                right = new ModuloExpression(left,right);
                return new AssignmentExpression(left,right);
            }
            else if (scanner.TryGetDelimiter("<<="))
            {
                Expression right = ParseAssigmentExpression();
                right = new LeftShiftExpression(left,right);
                return new AssignmentExpression(left,right);
            }
            else if (scanner.TryGetDelimiter(">>="))
            {
                Expression right = ParseAssigmentExpression();
                right = new RightShiftExpression(left,right);
                return new AssignmentExpression(left,right);
            }
            else if (scanner.TryGetDelimiter("&="))
            {
                Expression right = ParseAssigmentExpression();
                right = new BitwiseAndExpression(left,right);
                return new AssignmentExpression(left,right);
            }
            else if (scanner.TryGetDelimiter("^="))
            {
                Expression right = ParseAssigmentExpression();
                right = new BitwiseXorExpression(left,right);
                return new AssignmentExpression(left,right);
            }
            else if (scanner.TryGetDelimiter("|="))
            {
                Expression right = ParseAssigmentExpression();
                right = new BitwiseOrExpression(left,right);
                return new AssignmentExpression(left,right);
            }
            else if (scanner.TryGetDelimiter("&&="))
            {
                Expression right = ParseAssigmentExpression();
                right = new LogicalAndExpression(left,right);
                return new AssignmentExpression(left,right);
            }
            else if (scanner.TryGetDelimiter("^^="))
            {
                Expression right = ParseAssigmentExpression();
                right = new LogicalXorExpression(left,right);
                return new AssignmentExpression(left,right);
            }
            else if (scanner.TryGetDelimiter("||="))
            {
                Expression right = ParseAssigmentExpression();
                right = new LogicalOrExpression(left,right);
                return new AssignmentExpression(left,right);
            }
            else
            {
                return left;
            }
        }

        private Expression ParseLogicalOrExpression()
        {
            Expression left = ParseLogicalXorExpression();
            while (scanner.TryGetDelimiter("||"))
            {
                Expression right = ParseLogicalXorExpression();
                left = new LogicalOrExpression(left,right);
            }
            return left;
        }

        private Expression ParseLogicalXorExpression()
        {
            Expression left = ParseLogicalAndExpression();
            while (scanner.TryGetDelimiter("^^"))
            {
                Expression right = ParseLogicalAndExpression();
                left = new LogicalXorExpression(left,right);
            }
            return left;
        }

        private Expression ParseLogicalAndExpression()
        {
            Expression left = ParseBitwiseOrExpression();
            while (scanner.TryGetDelimiter("&&"))
            {
                Expression right = ParseBitwiseOrExpression();
                left = new LogicalAndExpression(left,right);
            }
            return left;
        }

        private Expression ParseBitwiseOrExpression()
        {
            Expression left = ParseBitwiseXorExpression();
            while (scanner.TryGetDelimiter("|"))
            {
                Expression right = ParseBitwiseXorExpression();
                left = new BitwiseOrExpression(left,right);
            }
            return left;
        }

        private Expression ParseBitwiseXorExpression()
        {
            Expression left = ParseBitwiseAndExpression();
            while (scanner.TryGetDelimiter("^"))
            {
                Expression right = ParseBitwiseAndExpression();
                left = new BitwiseXorExpression(left,right);
            }
            return left;
        }

        private Expression ParseBitwiseAndExpression()
        {
            Expression left = ParseEqualityExpression();
            while (scanner.TryGetDelimiter("&"))
            {
                Expression right = ParseEqualityExpression();
                left = new BitwiseAndExpression(left,right);
            }
            return left;
        }

        private Expression ParseEqualityExpression()
        {
            Expression left = ParseComparisonExpression();
            while (true)
            {
                if (scanner.TryGetDelimiter("=="))
                {
                    Expression right = ParseComparisonExpression();
                    left = new EqualExpression(left,right);
                }
                else if (scanner.TryGetDelimiter("!="))
                {
                    Expression right = ParseComparisonExpression();
                    left = new NotEqualExpression(left,right);
                }
                else if (scanner.TryGetIdentifier("is"))
                {
                    Expression right = ParseComparisonExpression();
                    left = new IsExpression(left,right);
                }
                else if (scanner.TryGetIdentifier("isnot"))
                {
                    Expression right = ParseComparisonExpression();
                    left = new IsNotExpression(left,right);
                }
                else
                {
                    return left;
                }
            }
        }

        private Expression ParseComparisonExpression()
        {
            Expression left = ParseBitshiftExpression();
            while (true)
            {
                if (scanner.TryGetDelimiter("<"))
                {
                    Expression right = ParseBitshiftExpression();
                    left = new LessExpression(left,right);
                }
                else if (scanner.TryGetDelimiter("<="))
                {
                    Expression right = ParseBitshiftExpression();
                    left = new LessOrEqualExpression(left,right);
                }
                else if (scanner.TryGetDelimiter(">"))
                {
                    Expression right = ParseBitshiftExpression();
                    left = new GreaterExpression(left,right);
                }
                else if (scanner.TryGetDelimiter(">="))
                {
                    Expression right = ParseBitshiftExpression();
                    left = new GreaterOrEqualExpression(left,right);
                }
                else
                {
                    return left;
                }
            }
        }

        private Expression ParseBitshiftExpression()
        {
            Expression left = ParseAddExpression();
            while (true)
            {
                if (scanner.TryGetDelimiter("<<"))
                {
                    Expression right = ParseAddExpression();
                    left = new LeftShiftExpression(left,right);
                }
                else if (scanner.TryGetDelimiter(">>"))
                {
                    Expression right = ParseAddExpression();
                    left = new RightShiftExpression(left,right);
                }
                else
                {
                    return left;
                }
            }
        }

        private Expression ParseAddExpression()
        {
            Expression left = ParseMultiplyExpression();
            while (true)
            {
                if (scanner.TryGetDelimiter("+"))
                {
                    Expression right = ParseMultiplyExpression();
                    left = new AddExpression(left,right);
                }
                else if (scanner.TryGetDelimiter("-"))
                {
                    Expression right = ParseMultiplyExpression();
                    left = new SubtractExpression(left,right);
                }
                else
                {
                    return left;
                }
            }
        }

        private Expression ParseMultiplyExpression()
        {
            Expression left = ParsePrefixExpression();
            while (true)
            {
                if (scanner.TryGetDelimiter("*"))
                {
                    Expression right = ParsePrefixExpression();
                    left = new MultiplyExpression(left,right);
                }
                else if (scanner.TryGetDelimiter("/"))
                {
                    Expression right = ParsePrefixExpression();
                    left = new DivideExpression(left,right);
                }
                else if (scanner.TryGetDelimiter("%"))
                {
                    Expression right = ParsePrefixExpression();
                    left = new ModuloExpression(left,right);
                }
                else
                {
                    return left;
                }
            }
        }

        private Expression ParsePrefixExpression()
        {
            if (scanner.TryGetDelimiter("++"))
            {
                Expression inner = ParsePrefixExpression();
                //return new PrefixIncrementExpression(inner);
                throw new NotImplementedException();
            }
            else if (scanner.TryGetDelimiter("--"))
            {
                Expression inner = ParsePrefixExpression();
                //return new PrefixDecrementExpression(inner);
                throw new NotImplementedException();
            }
            else if (scanner.TryGetDelimiter("-"))
            {
                Expression inner = ParsePrefixExpression();
                return new NegateExpression(inner);
            }
            else if (scanner.TryGetDelimiter("!"))
            {
                Expression inner = ParsePrefixExpression();
                return new LogicalNotExpression(inner);
            }
            else if (scanner.TryGetDelimiter("~"))
            {
                Expression inner = ParsePrefixExpression();
                return new BitwiseNotExpression(inner);
            }
            else
            {
                return ParsePostfixExpression();
            }
        }

        private Expression ParsePostfixExpression()
        {
            Expression inner = ParseBaseExpression();
            while (true)
            {
                if (scanner.TryGetDelimiter("++"))
                {
                    //inner = new PostfixIncrementExpression(inner);
                    throw new NotImplementedException();
                }
                else if (scanner.TryGetDelimiter("--"))
                {
                    //inner = new PostfixDecrementExpression(inner);
                    throw new NotImplementedException();
                }
                else if (scanner.TryGetDelimiter("("))
                {
                    List<Expression> arguments = new List<Expression>();
                    if (!scanner.TryGetDelimiter(")"))
                    {
                        do
                        {
                            arguments.Add(ParseExpression());
                        }
                        while (scanner.TryGetDelimiter(","));
                        scanner.GetDelimiter(")");
                    }
                    inner = new CallExpression(inner,arguments.ToArray());
                }
                else if (scanner.TryGetDelimiter("["))
                {
                    throw new NotImplementedException();
                }
                else if (scanner.TryGetDelimiter("->"))
                {
                    string member;
                    scanner.GetIdentifier(out member);
                    inner = new MemberExpression(inner,member);
                }
                else
                {
                    return inner;
                }
            }
        }

        private Expression ParseBaseExpression()
        {
            int intvalue;
            string strvalue;
            if (scanner.TryGetIdentifier("null"))
            {
                return new NullExpression();
            }
            else if (scanner.TryGetIdentifier("true"))
            {
                return new TrueExpression();
            }
            else if (scanner.TryGetIdentifier("false"))
            {
                return new FalseExpression();
            }
            else if (scanner.TryGetIdentifier("new"))
            {
                scanner.GetIdentifier(out strvalue);
                //return new NewExpression(strvalue);
                throw new NotImplementedException();
            }
            else if (scanner.TryGetIdentifier(out strvalue))
            {
                return new VariableExpression(strvalue);
            }
            else if (scanner.TryGetInteger(out intvalue))
            {
                return new IntegerLiteralExpression(intvalue);
            }
            else if (scanner.TryGetString(out strvalue))
            {
                return new StringLiteralExpression(strvalue);
            }
            else if (scanner.TryGetDelimiter("("))
            {
                Expression expression = ParseExpression();
                scanner.GetDelimiter(")");
                return expression;
            }
            else
            {
                throw new ApplicationException();
            }
        }
    }
}
