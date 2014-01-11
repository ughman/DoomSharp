namespace DoomSharp
{
    public abstract class Thinker
    {
        public abstract bool Finished
        {
            get;
        }

        public abstract void Tick();
    }
}
