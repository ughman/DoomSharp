using System;

namespace DoomSharp
{
    public sealed class DoomConsole
    {
        public void LogError(string message,params object[] args)
        {
            if (message == null)
                throw new ArgumentNullException("message");
            Console.ForegroundColor = ConsoleColor.Red;
            Console.Write("ERROR: ");
            Console.ForegroundColor = ConsoleColor.White;
            Console.WriteLine(message,args);
            Console.ResetColor();
        }

        public void LogWarning(string message,params object[] args)
        {
            if (message == null)
                throw new ArgumentNullException("message");
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.Write("WARNING: ");
            Console.ForegroundColor = ConsoleColor.White;
            Console.WriteLine(message,args);
            Console.ResetColor();
        }

        public void LogGameMessage(string message)
        {
            if (message == null)
                throw new ArgumentNullException("message");
            Console.ForegroundColor = ConsoleColor.Green;
            Console.WriteLine(message);
            Console.ResetColor();
        }
    }
}
