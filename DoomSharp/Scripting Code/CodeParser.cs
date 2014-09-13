using System;
using System.Reflection;
using System.Reflection.Emit;
using System.Collections.Generic;

namespace DoomSharp
{
    public static class CodeParser
    {
        public static Statement ParseBlock(Scanner scanner)
        {
            BlockStatement block = new BlockStatement();
            while (!scanner.TryGetEnd())
            {
                block.Statements.Add(ParseStatement(scanner));
            }
            return block;
        }

        private static Statement ParseStatement(Scanner scanner)
        {
            if (scanner.TryGetIdentifier("if"))
            {
                scanner.GetDelimiter("(");
                Expression condition = ParseExpression(scanner);
                scanner.GetDelimiter(")");
                Statement thenstatement = ParseStatement(scanner);
                Statement elsestatement = new NullStatement();
                if (scanner.TryGetIdentifier("else"))
                {
                    elsestatement = ParseStatement(scanner);
                }
                return new IfStatement(condition,thenstatement,elsestatement);
            }
            else if (scanner.TryGetIdentifier("while"))
            {
                scanner.GetDelimiter("(");
                Expression condition = ParseExpression(scanner);
                scanner.GetDelimiter(")");
                Statement loopstatement = ParseStatement(scanner);
                Statement elsestatement = new NullStatement();
                if (scanner.TryGetIdentifier("else"))
                {
                    elsestatement = ParseStatement(scanner);
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
                Expression collection = ParseExpression(scanner);
                scanner.GetDelimiter(")");
                Statement loopstatement = ParseStatement(scanner);
                Statement elsestatement = new NullStatement();
                if (scanner.TryGetIdentifier("else"))
                {
                    elsestatement = ParseStatement(scanner);
                }
                return new ForEachStatement(variabletype,variablename,collection,loopstatement,elsestatement);
            }
            else if (scanner.TryGetIdentifier("var"))
            {
                string variablename;
                scanner.GetIdentifier(out variablename);
                scanner.GetDelimiter("=");
                Expression expression = ParseExpression(scanner);
                scanner.GetDelimiter(";");
                return new VarStatement(variablename,expression);
            }
            else if (scanner.TryGetDelimiter("{"))
            {
                return CodeParser.ParseBlock(scanner.ScanAcross("{","}"));
            }
            else if (scanner.TryGetDelimiter(";"))
            {
                return new NullStatement();
            }
            else
            {
                Expression expression = ParseExpression(scanner);
                scanner.GetDelimiter(";");
                return new ExpressionStatement(expression);
            }
        }

        private static Expression ParseExpression(Scanner scanner)
        {
            return ParseAssigmentExpression(scanner);
        }

        private static Expression ParseAssigmentExpression(Scanner scanner)
        {
            Expression left = ParseLogicalOrExpression(scanner);
            if (scanner.TryGetDelimiter("="))
            {
                Expression right = ParseAssigmentExpression(scanner);
                return new AssignmentExpression(left,right);
            }
            else if (scanner.TryGetDelimiter("+="))
            {
                Expression right = ParseAssigmentExpression(scanner);
                right = new AddExpression(left,right);
                return new AssignmentExpression(left,right);
            }
            else if (scanner.TryGetDelimiter("-="))
            {
                Expression right = ParseAssigmentExpression(scanner);
                right = new SubtractExpression(left,right);
                return new AssignmentExpression(left,right);
            }
            else if (scanner.TryGetDelimiter("*="))
            {
                Expression right = ParseAssigmentExpression(scanner);
                right = new MultiplyExpression(left,right);
                return new AssignmentExpression(left,right);
            }
            else if (scanner.TryGetDelimiter("/="))
            {
                Expression right = ParseAssigmentExpression(scanner);
                right = new DivideExpression(left,right);
                return new AssignmentExpression(left,right);
            }
            else if (scanner.TryGetDelimiter("%="))
            {
                Expression right = ParseAssigmentExpression(scanner);
                right = new ModuloExpression(left,right);
                return new AssignmentExpression(left,right);
            }
            else if (scanner.TryGetDelimiter("<<="))
            {
                Expression right = ParseAssigmentExpression(scanner);
                right = new LeftShiftExpression(left,right);
                return new AssignmentExpression(left,right);
            }
            else if (scanner.TryGetDelimiter(">>="))
            {
                Expression right = ParseAssigmentExpression(scanner);
                right = new RightShiftExpression(left,right);
                return new AssignmentExpression(left,right);
            }
            else if (scanner.TryGetDelimiter("&="))
            {
                Expression right = ParseAssigmentExpression(scanner);
                right = new BitwiseAndExpression(left,right);
                return new AssignmentExpression(left,right);
            }
            else if (scanner.TryGetDelimiter("^="))
            {
                Expression right = ParseAssigmentExpression(scanner);
                right = new BitwiseXorExpression(left,right);
                return new AssignmentExpression(left,right);
            }
            else if (scanner.TryGetDelimiter("|="))
            {
                Expression right = ParseAssigmentExpression(scanner);
                right = new BitwiseOrExpression(left,right);
                return new AssignmentExpression(left,right);
            }
            else if (scanner.TryGetDelimiter("&&="))
            {
                Expression right = ParseAssigmentExpression(scanner);
                right = new LogicalAndExpression(left,right);
                return new AssignmentExpression(left,right);
            }
            else if (scanner.TryGetDelimiter("^^="))
            {
                Expression right = ParseAssigmentExpression(scanner);
                right = new LogicalXorExpression(left,right);
                return new AssignmentExpression(left,right);
            }
            else if (scanner.TryGetDelimiter("||="))
            {
                Expression right = ParseAssigmentExpression(scanner);
                right = new LogicalOrExpression(left,right);
                return new AssignmentExpression(left,right);
            }
            else
            {
                return left;
            }
        }

        private static Expression ParseLogicalOrExpression(Scanner scanner)
        {
            Expression left = ParseLogicalXorExpression(scanner);
            while (scanner.TryGetDelimiter("||"))
            {
                Expression right = ParseLogicalXorExpression(scanner);
                left = new LogicalOrExpression(left,right);
            }
            return left;
        }

        private static Expression ParseLogicalXorExpression(Scanner scanner)
        {
            Expression left = ParseLogicalAndExpression(scanner);
            while (scanner.TryGetDelimiter("^^"))
            {
                Expression right = ParseLogicalAndExpression(scanner);
                left = new LogicalXorExpression(left,right);
            }
            return left;
        }

        private static Expression ParseLogicalAndExpression(Scanner scanner)
        {
            Expression left = ParseBitwiseOrExpression(scanner);
            while (scanner.TryGetDelimiter("&&"))
            {
                Expression right = ParseBitwiseOrExpression(scanner);
                left = new LogicalAndExpression(left,right);
            }
            return left;
        }

        private static Expression ParseBitwiseOrExpression(Scanner scanner)
        {
            Expression left = ParseBitwiseXorExpression(scanner);
            while (scanner.TryGetDelimiter("|"))
            {
                Expression right = ParseBitwiseXorExpression(scanner);
                left = new BitwiseOrExpression(left,right);
            }
            return left;
        }

        private static Expression ParseBitwiseXorExpression(Scanner scanner)
        {
            Expression left = ParseBitwiseAndExpression(scanner);
            while (scanner.TryGetDelimiter("^"))
            {
                Expression right = ParseBitwiseAndExpression(scanner);
                left = new BitwiseXorExpression(left,right);
            }
            return left;
        }

        private static Expression ParseBitwiseAndExpression(Scanner scanner)
        {
            Expression left = ParseEqualityExpression(scanner);
            while (scanner.TryGetDelimiter("&"))
            {
                Expression right = ParseEqualityExpression(scanner);
                left = new BitwiseAndExpression(left,right);
            }
            return left;
        }

        private static Expression ParseEqualityExpression(Scanner scanner)
        {
            Expression left = ParseComparisonExpression(scanner);
            while (true)
            {
                if (scanner.TryGetDelimiter("=="))
                {
                    Expression right = ParseComparisonExpression(scanner);
                    left = new EqualExpression(left,right);
                }
                else if (scanner.TryGetDelimiter("!="))
                {
                    Expression right = ParseComparisonExpression(scanner);
                    left = new NotEqualExpression(left,right);
                }
                else if (scanner.TryGetIdentifier("is"))
                {
                    Expression right = ParseComparisonExpression(scanner);
                    left = new IsExpression(left,right);
                }
                else if (scanner.TryGetIdentifier("isnot"))
                {
                    Expression right = ParseComparisonExpression(scanner);
                    left = new IsNotExpression(left,right);
                }
                else
                {
                    return left;
                }
            }
        }

        private static Expression ParseComparisonExpression(Scanner scanner)
        {
            Expression left = ParseBitshiftExpression(scanner);
            while (true)
            {
                if (scanner.TryGetDelimiter("<"))
                {
                    Expression right = ParseBitshiftExpression(scanner);
                    left = new LessExpression(left,right);
                }
                else if (scanner.TryGetDelimiter("<="))
                {
                    Expression right = ParseBitshiftExpression(scanner);
                    left = new LessOrEqualExpression(left,right);
                }
                else if (scanner.TryGetDelimiter(">"))
                {
                    Expression right = ParseBitshiftExpression(scanner);
                    left = new GreaterExpression(left,right);
                }
                else if (scanner.TryGetDelimiter(">="))
                {
                    Expression right = ParseBitshiftExpression(scanner);
                    left = new GreaterOrEqualExpression(left,right);
                }
                else
                {
                    return left;
                }
            }
        }

        private static Expression ParseBitshiftExpression(Scanner scanner)
        {
            Expression left = ParseAddExpression(scanner);
            while (true)
            {
                if (scanner.TryGetDelimiter("<<"))
                {
                    Expression right = ParseAddExpression(scanner);
                    left = new LeftShiftExpression(left,right);
                }
                else if (scanner.TryGetDelimiter(">>"))
                {
                    Expression right = ParseAddExpression(scanner);
                    left = new RightShiftExpression(left,right);
                }
                else
                {
                    return left;
                }
            }
        }

        private static Expression ParseAddExpression(Scanner scanner)
        {
            Expression left = ParseMultiplyExpression(scanner);
            while (true)
            {
                if (scanner.TryGetDelimiter("+"))
                {
                    Expression right = ParseMultiplyExpression(scanner);
                    left = new AddExpression(left,right);
                }
                else if (scanner.TryGetDelimiter("-"))
                {
                    Expression right = ParseMultiplyExpression(scanner);
                    left = new SubtractExpression(left,right);
                }
                else
                {
                    return left;
                }
            }
        }

        private static Expression ParseMultiplyExpression(Scanner scanner)
        {
            Expression left = ParsePrefixExpression(scanner);
            while (true)
            {
                if (scanner.TryGetDelimiter("*"))
                {
                    Expression right = ParsePrefixExpression(scanner);
                    left = new MultiplyExpression(left,right);
                }
                else if (scanner.TryGetDelimiter("/"))
                {
                    Expression right = ParsePrefixExpression(scanner);
                    left = new DivideExpression(left,right);
                }
                else if (scanner.TryGetDelimiter("%"))
                {
                    Expression right = ParsePrefixExpression(scanner);
                    left = new ModuloExpression(left,right);
                }
                else
                {
                    return left;
                }
            }
        }

        private static Expression ParsePrefixExpression(Scanner scanner)
        {
            if (scanner.TryGetDelimiter("++"))
            {
                Expression inner = ParsePrefixExpression(scanner);
                //return new PrefixIncrementExpression(inner);
                throw new NotImplementedException();
            }
            else if (scanner.TryGetDelimiter("--"))
            {
                Expression inner = ParsePrefixExpression(scanner);
                //return new PrefixDecrementExpression(inner);
                throw new NotImplementedException();
            }
            else if (scanner.TryGetDelimiter("-"))
            {
                Expression inner = ParsePrefixExpression(scanner);
                return new NegateExpression(inner);
            }
            else if (scanner.TryGetDelimiter("!"))
            {
                Expression inner = ParsePrefixExpression(scanner);
                return new LogicalNotExpression(inner);
            }
            else if (scanner.TryGetDelimiter("~"))
            {
                Expression inner = ParsePrefixExpression(scanner);
                return new BitwiseNotExpression(inner);
            }
            else
            {
                return ParsePostfixExpression(scanner);
            }
        }

        private static Expression ParsePostfixExpression(Scanner scanner)
        {
            Expression inner = ParseBaseExpression(scanner);
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
                            arguments.Add(ParseExpression(scanner));
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

        private static Expression ParseBaseExpression(Scanner scanner)
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
                Expression expression = ParseExpression(scanner);
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
