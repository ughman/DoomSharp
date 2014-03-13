namespace DoomSharp
{
    public abstract class Statement
    {
        public abstract void Compile(CodeContext c);

        public void SubCompile(CodeContext c)
        {
            CodeContext c2 = new CodeContext(c);
            Compile(c2);
        }
    }
}
