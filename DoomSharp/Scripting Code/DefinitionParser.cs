using System;
using System.Reflection;
using System.Reflection.Emit;
using System.Collections.Generic;

namespace DoomSharp
{
    public static class DefinitionParser
    {
        public static Definition ParseDefinition(Scanner scanner)
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
                Statement statement = CodeParser.ParseBlock(scanner.ScanAcross("{","}"));
                return new FunctionDefinition(name,returntype,parametertypes.ToArray(),parameternames.ToArray(),statement);
            }
            else
            {
                throw new ApplicationException();
            }
        }
    }
}
