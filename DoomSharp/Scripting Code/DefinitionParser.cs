using System;
using System.Reflection;
using System.Reflection.Emit;
using System.Collections.Generic;

namespace DoomSharp
{
    public sealed class DefinitionParser
    {
        private Scanner scanner;

        public DefinitionParser(Scanner scanner)
        {
            if (scanner == null)
                throw new ArgumentNullException("scanner");
            this.scanner = scanner;
        }

        public Definition ParseDefinition()
        {
            if (scanner.TryGetIdentifier("function"))
            {
                string returntype;
                string name;
                List<string> parametertypes = new List<string>();
                List<string> parameternames = new List<string>();
                scanner.GetIdentifier(out returntype);
                scanner.GetIdentifier(out name);
                scanner.GetDelimiter("(");
                if (!scanner.TryGetDelimiter(")"))
                {
                    do
                    {
                        string parametertype;
                        string parametername;
                        scanner.GetIdentifier(out parametertype);
                        scanner.GetIdentifier(out parametername);
                        parametertypes.Add(parametertype);
                        parameternames.Add(parametername);
                    }
                    while (scanner.TryGetDelimiter(","));
                    scanner.GetDelimiter(")");
                }
                scanner.GetDelimiter("{");
                Statement statement = new CodeParser(scanner.ScanAcross("{","}")).ParseBlock();
                return new FunctionDefinition(name,returntype,parametertypes.ToArray(),parameternames.ToArray(),statement);
            }
            else
            {
                throw new ApplicationException();
            }
        }
    }
}
