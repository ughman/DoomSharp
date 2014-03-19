using System;

namespace DoomSharp
{
    public sealed class Blockmap
    {
        private World world;
        private Fixed xoffset;
        private Fixed yoffset;
        private int width;
        private int height;
        private Block[,] blocks;

        public Blockmap(World world,Fixed xoffset,Fixed yoffset,int width,int height)
        {
            if (world == null)
                throw new ArgumentNullException("world");
            if (width < 0)
                throw new ArgumentOutOfRangeException("width");
            if (height < 0)
                throw new ArgumentOutOfRangeException("height");
            this.world = world;
            this.xoffset = xoffset;
            this.yoffset = yoffset;
            this.width = width;
            this.height = height;
            this.blocks = new Block [width,height];
            for (int x = 0;x < width;x++)
            {
                for (int y = 0;y < height;y++)
                {
                    this.blocks[x,y] = new Block(this);
                }
            }
        }

        public World World
        {
            get { return world; }
        }

        public Fixed XOffset
        {
            get { return xoffset; }
        }

        public Fixed YOffset
        {
            get { return yoffset; }
        }

        public int Width
        {
            get { return width; }
        }

        public int Height
        {
            get { return height; }
        }

        public Block this[int x,int y]
        {
            get
            {
                if (x < 0 || x >= width)
                    throw new ArgumentOutOfRangeException("x");
                if (y < 0 || y >= height)
                    throw new ArgumentOutOfRangeException("y");
                return blocks[x,y];
            }
        }
    }
}
