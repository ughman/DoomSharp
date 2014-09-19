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
            else if (scanner.TryGetIdentifier("linedefspecial"))
            {
                List<LinedefSpecialAttribute> attributes = new List<LinedefSpecialAttribute>();
                do
                {
                    int number;
                    scanner.GetInteger(out number);
                    LinedefSpecialAttribute attribute = new LinedefSpecialAttribute(number);
                    scanner.GetDelimiter("(");
                    while (!scanner.TryGetDelimiter(")"))
                    {
                        if (scanner.TryGetIdentifier("auto"))
                            attribute.ActivationType |= LinedefActivationType.Automatic;
                        else if (scanner.TryGetIdentifier("use"))
                            attribute.ActivationType |= LinedefActivationType.Use;
                        else if (scanner.TryGetIdentifier("monsteruse"))
                            attribute.ActivationType |= LinedefActivationType.MonsterUse;
                        else if (scanner.TryGetIdentifier("cross"))
                            attribute.ActivationType |= LinedefActivationType.Cross;
                        else if (scanner.TryGetIdentifier("monstercross"))
                            attribute.ActivationType |= LinedefActivationType.MonsterCross;
                        else if (scanner.TryGetIdentifier("shoot"))
                            attribute.ActivationType |= LinedefActivationType.Shoot;
                        else if (scanner.TryGetIdentifier("monstershoot"))
                            attribute.ActivationType |= LinedefActivationType.MonsterShoot;
                        else if (scanner.TryGetIdentifier("repeatable"))
                            attribute.Repeatable = true;
                        else
                            throw new ApplicationException();
                    }
                    attributes.Add(attribute);
                }
                while (scanner.TryGetDelimiter(","));
                scanner.GetDelimiter("{");
                Statement statement = CodeParser.ParseBlock(scanner.ScanAcross("{","}"));
                return new LinedefSpecialDefinition(statement,attributes);
            }
            else
            {
                throw new ApplicationException();
            }
        }
    }
}
