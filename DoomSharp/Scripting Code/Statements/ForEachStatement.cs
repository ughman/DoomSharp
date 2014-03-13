using System;
using System.Reflection;
using System.Reflection.Emit;
using System.Collections;

namespace DoomSharp
{
    public sealed class ForEachStatement : Statement
    {
        private string variabletype;
        private string variablename;
        private Expression collection;
        private Statement loopstatement;
        private Statement elsestatement;

        public ForEachStatement(string variabletype,string variablename,Expression collection,Statement loopstatement,Statement elsestatement)
        {
            if (variabletype == null)
                throw new ArgumentNullException("variabletype");
            if (variablename == null)
                throw new ArgumentNullException("variablename");
            if (collection == null)
                throw new ArgumentNullException("collection");
            if (loopstatement == null)
                throw new ArgumentNullException("loopstatement");
            if (elsestatement == null)
                throw new ArgumentNullException("elsestatement");
            this.variabletype = variabletype;
            this.variablename = variablename;
            this.collection = collection;
            this.loopstatement = loopstatement;
            this.elsestatement = elsestatement;
        }

        public override void Compile(CodeContext c)
        {
            Label looplabel = c.IL.DefineLabel();
            Label elselabel = c.IL.DefineLabel();
            Label endlabel = c.IL.DefineLabel();
            LocalBuilder enumerator = c.IL.DeclareLocal(typeof(IEnumerator));
            Type collectiontype = collection.Evaluate(c);
            if (collectiontype == null)
            {
                throw new ApplicationException();
            }
            if (!typeof(IEnumerable).IsAssignableFrom(collectiontype))
            {
                throw new ApplicationException();
            }
            Type valuetype;
            if (!c.Types.TryGetValue(variabletype,out valuetype))
            {
                throw new ApplicationException();
            }
            LocalBuilder value = c.IL.DeclareLocal(valuetype);
            CodeContext c2 = new CodeContext(c);
            c2.Locals.Add(variablename,value);
            if (collectiontype.IsValueType)
            {
                c.IL.Emit(OpCodes.Constrained,typeof(IEnumerable));
            }
            c.IL.Emit(OpCodes.Callvirt,typeof(IEnumerable).GetMethod("GetEnumerator"));
            c.IL.Emit(OpCodes.Stloc,enumerator);
            c.IL.MarkLabel(looplabel);
            c.IL.Emit(OpCodes.Ldloc,enumerator);
            c.IL.Emit(OpCodes.Callvirt,typeof(IEnumerator).GetMethod("MoveNext"));
            c.IL.Emit(OpCodes.Brfalse,elselabel);
            c.IL.Emit(OpCodes.Ldloc,enumerator);
            c.IL.Emit(OpCodes.Callvirt,typeof(IEnumerator).GetProperty("Current").GetGetMethod());
            c.IL.Emit(OpCodes.Isinst,valuetype);
            c.IL.Emit(OpCodes.Dup);
            c.IL.Emit(OpCodes.Stloc,value);
            c.IL.Emit(OpCodes.Brfalse,looplabel);
            loopstatement.SubCompile(c2);
            c.IL.Emit(OpCodes.Br,looplabel);
            c.IL.MarkLabel(elselabel);
            elsestatement.SubCompile(c);
            c.IL.MarkLabel(endlabel);
        }
    }
}
