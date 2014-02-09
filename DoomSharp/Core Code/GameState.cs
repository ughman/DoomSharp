using System;
using OpenTK;
using OpenTK.Input;

namespace DoomSharp
{
    public abstract class GameState
    {
        private bool inuse;
        private GameState next;

        public GameState()
        {
            this.inuse = false;
            this.next = null;
        }

        public GameState Next
        {
            get
            {
                if (!inuse)
                    throw new InvalidOperationException();
                return next;
            }
        }

        public void Push(ref GameState topstate)
        {
            if (inuse)
                throw new InvalidOperationException();
            next = topstate;
            topstate = this;
            inuse = true;
        }

        public abstract void Update(double time,bool top);

        public virtual void KeyDown(Key key)
        {
        }

        public virtual void KeyUp(Key key)
        {
        }
    }
}
