namespace DoomSharp
{
    public interface IArchive
    {
        int LumpCount { get; }
        ILump this[int i] { get; }

        int Find(string name);
    }
}
