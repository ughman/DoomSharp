namespace DoomSharp
{
    public abstract class Definition
    {
        public virtual void DefineTypes(DefinitionContext c)
        {
        }

        public virtual void DefineMembers(DefinitionContext c)
        {
        }

        public virtual void Compile(DefinitionContext c)
        {
        }
    }
}
