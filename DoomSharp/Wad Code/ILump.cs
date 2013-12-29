namespace DoomSharp
{
    public interface ILump
    {
        string Name { get; }
        int Length { get; }

        byte[] Read();
    }
}
