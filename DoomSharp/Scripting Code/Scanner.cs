using System;
using System.Text;
using System.Collections.Generic;

namespace DoomSharp
{
    public sealed class Scanner
    {
        private static List<string> delimiters;

        static Scanner()
        {
            delimiters = new List<string>();
            delimiters.Add(">>=");
            delimiters.Add(">>");
            delimiters.Add(">=");
            delimiters.Add(">");
            delimiters.Add("<<=");
            delimiters.Add("<<");
            delimiters.Add("<=");
            delimiters.Add("<");
            delimiters.Add("!=");
            delimiters.Add("!");
            delimiters.Add("~");
            delimiters.Add("==");
            delimiters.Add("=");
            delimiters.Add("++");
            delimiters.Add("+=");
            delimiters.Add("+");
            delimiters.Add("--");
            delimiters.Add("->");
            delimiters.Add("-=");
            delimiters.Add("-");
            delimiters.Add("*=");
            delimiters.Add("*");
            delimiters.Add("/=");
            delimiters.Add("/");
            delimiters.Add("%=");
            delimiters.Add("%");
            delimiters.Add("&&");
            delimiters.Add("&=");
            delimiters.Add("&");
            delimiters.Add("||");
            delimiters.Add("|=");
            delimiters.Add("|");
            delimiters.Add("^^=");
            delimiters.Add("^^");
            delimiters.Add("^=");
            delimiters.Add("^");
            delimiters.Add("?");
            delimiters.Add(":");
            delimiters.Add(";");
            delimiters.Add(",");
            delimiters.Add("(");
            delimiters.Add(")");
            delimiters.Add("[");
            delimiters.Add("]");
            delimiters.Add("{");
            delimiters.Add("}");
        }

        private List<Token> tokens;

        private Scanner(IEnumerable<Token> tokens)
        {
            this.tokens = new List<Token>(tokens);
        }

        public Scanner(string input)
        {
            if (input == null)
                throw new ArgumentNullException("input");
            this.tokens = new List<Token>();
            bool spaced = true;
            while (input.Length > 0)
            {
                if (char.IsWhiteSpace(input[0]))
                {
                    input = input.Remove(0,1);
                    spaced = true;
                }
                else if (input.StartsWith("//"))
                {
                    input = input.Remove(0,2);
                    while (input.Length > 0 && input[0] != '\n')
                    {
                        input = input.Remove(0,1);
                    }
                    spaced = true;
                }
                else if (input.StartsWith("/*"))
                {
                    input = input.Remove(0,2);
                    while (!input.StartsWith("*/"))
                    {
                        if (input.Length == 0)
                        {
                            throw new ApplicationException();
                        }
                        input = input.Remove(0,1);
                    }
                    input = input.Remove(0,2);
                    spaced = true;
                }
                else if (spaced && char.IsLetter(input[0]))
                {
                    StringBuilder sb = new StringBuilder();
                    sb.Append(input[0]);
                    input = input.Remove(0,1);
                    while (char.IsLetterOrDigit(input[0]))
                    {
                        sb.Append(input[0]);
                        input = input.Remove(0,1);
                    }
                    tokens.Add(new Token(TokenType.Identifier,sb.ToString()));
                    spaced = false;
                }
                else if (spaced && input[0] >= '0' && input[0] <= '9')
                {
                    long intvalue = input[0] - '0';
                    input = input.Remove(0,1);
                    while (input.Length > 0 && input[0] >= '0' && input[0] <= '9')
                    {
                        intvalue *= 10;
                        intvalue += input[0] - '0';
                        if (intvalue > int.MaxValue)
                        {
                            throw new ApplicationException();
                        }
                        input.Remove(0,1);
                    }
                    if (input.Length > 0 && input[0] == '.')
                    {
                        double floatvalue = intvalue;
                        input = input.Remove(0,1);
                        while (input.Length > 0 && input[0] >= '0' && input[0] <= '9')
                        {
                            throw new NotImplementedException();
                        }
                        tokens.Add(new Token(TokenType.Float,floatvalue));
                        spaced = false;
                    }
                    else
                    {
                        tokens.Add(new Token(TokenType.Integer,(int)intvalue));
                        spaced = false;
                    }
                }
                else if (spaced && input[0] == '"')
                {
                    StringBuilder sb = new StringBuilder();
                    input = input.Remove(0,1);
                    while (input[0] != '"')
                    {
                        if (input[0] == '\\')
                        {
                            input = input.Remove(0,1);
                            if (input.Length == 0)
                            {
                                throw new ApplicationException();
                            }
                            switch (input[0])
                            {
                                case '\\':
                                case '"':
                                    sb.Append(input[0]);
                                    break;
                                case 'n':
                                    sb.Append('\n');
                                    break;
                                default:
                                    throw new ApplicationException();
                            }
                            input = input.Remove(0,1);
                        }
                        else
                        {
                            sb.Append(input[0]);
                            input = input.Remove(0,1);
                        }
                        if (input.Length == 0)
                        {
                            throw new ApplicationException();
                        }
                    }
                    input = input.Remove(0,1);
                    tokens.Add(new Token(TokenType.String,sb.ToString()));
                    spaced = false;
                }
                else
                {
                    bool found = false;
                    foreach (string delimiter in delimiters)
                    {
                        if (input.StartsWith(delimiter))
                        {
                            input = input.Remove(0,delimiter.Length);
                            tokens.Add(new Token(TokenType.Delimiter,delimiter));
                            spaced = true;
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                    {
                        throw new ApplicationException();
                    }
                }
            }
        }

        public bool TryGetDelimiter(string delimiter)
        {
            if (delimiter == null)
                throw new ArgumentNullException("delimiter");
            if (tokens.Count > 0 && tokens[0].Type == TokenType.Delimiter && (string)tokens[0].Value == delimiter)
            {
                tokens.RemoveAt(0);
                return true;
            }
            else
            {
                return false;
            }
        }

        public bool TryGetIdentifier(string identifier)
        {
            if (identifier == null)
                throw new ArgumentNullException("identifier");
            if (tokens.Count > 0 && tokens[0].Type == TokenType.Identifier && (string)tokens[0].Value == identifier)
            {
                tokens.RemoveAt(0);
                return true;
            }
            else
            {
                return false;
            }
        }

        public bool TryGetIdentifier(out string identifier)
        {
            if (tokens.Count > 0 && tokens[0].Type == TokenType.Identifier)
            {
                identifier = (string)tokens[0].Value;
                tokens.RemoveAt(0);
                return true;
            }
            else
            {
                identifier = null;
                return false;
            }
        }

        public bool TryGetInteger(out int value)
        {
            if (tokens.Count > 0 && tokens[0].Type == TokenType.Integer)
            {
                value = (int)tokens[0].Value;
                tokens.RemoveAt(0);
                return true;
            }
            else
            {
                value = 0;
                return false;
            }
        }

        public bool TryGetString(out string value)
        {
            if (tokens.Count > 0 && tokens[0].Type == TokenType.String)
            {
                value = (string)tokens[0].Value;
                tokens.RemoveAt(0);
                return true;
            }
            else
            {
                value = null;
                return false;
            }
        }

        public bool TryGetEnd()
        {
            if (tokens.Count == 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public void GetDelimiter(string delimiter)
        {
            if (!TryGetDelimiter(delimiter))
            {
                throw new ApplicationException();
            }
        }

        public void GetIdentifier(string identifier)
        {
            if (!TryGetIdentifier(identifier))
            {
                throw new ApplicationException();
            }
        }

        public void GetIdentifier(out string identifier)
        {
            if (!TryGetIdentifier(out identifier))
            {
                throw new ApplicationException();
            }
        }

        public void GetInteger(out int value)
        {
            if (!TryGetInteger(out value))
            {
                throw new ApplicationException();
            }
        }

        public void GetString(out string value)
        {
            if (!TryGetString(out value))
            {
                throw new ApplicationException();
            }
        }

        public void GetEnd()
        {
            if (!TryGetEnd())
            {
                throw new ApplicationException();
            }
        }

        public Scanner ScanAcross(string start,string end)
        {
            if (start == null)
                throw new ArgumentNullException("start");
            if (end == null)
                throw new ArgumentNullException("end");
            int depth = 1;
            List<Token> subtokens = new List<Token>();
            while (tokens.Count > 0)
            {
                subtokens.Add(tokens[0]);
                if (TryGetDelimiter(start))
                {
                    depth++;
                }
                else if (TryGetDelimiter(end))
                {
                    if (--depth == 0)
                    {
                        subtokens.RemoveAt(subtokens.Count - 1);
                        return new Scanner(subtokens);
                    }
                }
                else
                {
                    tokens.RemoveAt(0);
                }
            }
            throw new ApplicationException();
        }

        private sealed class Token
        {
            private TokenType type;
            private object value;

            public Token(TokenType type,object value)
            {
                if (value == null)
                    throw new ArgumentNullException("value");
                this.type = type;
                this.value = value;
            }

            public TokenType Type
            {
                get { return type; }
            }

            public object Value
            {
                get { return value; }
            }
        }

        private enum TokenType
        {
            Delimiter,
            Identifier,
            Integer,
            Float,
            String
        }
    }
}
