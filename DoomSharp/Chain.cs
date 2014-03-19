using System;
using System.Collections;
using System.Collections.Generic;

namespace DoomSharp
{
    public sealed class Chain<T> : ICollection<T>
    {
        private Link front;
        private Link back;
        private int count;

        public Chain()
        {
            this.front = null;
            this.back = null;
            this.count = 0;
        }

        public int Count
        {
            get { return count; }
        }

        public bool IsReadOnly
        {
            get { return false; }
        }

        public void Add(T value)
        {
            Link.AppendLink(this,value);
        }

        public void AddFront(T value)
        {
            Link.PrependLink(this,value);
        }

        public bool Remove(T value)
        {
            for (Link link = front;link != null;link = link.Next)
            {
                if (EqualityComparer<T>.Default.Equals(link.Value,value))
                {
                    link.Unlink();
                    return true;
                }
            }
            return false;
        }

        public void Clear()
        {
            while (front != null)
            {
                front.Unlink();
            }
        }

        public bool Contains(T value)
        {
            for (Link link = front;link != null;link = link.Next)
            {
                if (EqualityComparer<T>.Default.Equals(link.Value,value))
                {
                    return true;
                }
            }
            return false;
        }

        public void CopyTo(T[] array,int index)
        {
            if (array.Length < index + count)
                throw new ArgumentException("Array is not large enough.");
            foreach (T value in this)
            {
                array[index++] = value;
            }
        }

        public IEnumerator<T> GetEnumerator()
        {
            return new Enumerator(this);
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        private sealed class Link
        {
            public static Link AppendLink(Chain<T> chain,T value)
            {
                if (chain == null)
                    throw new ArgumentNullException("chain");
                Link link = new Link(chain,chain.back,null,value);
                if (chain.back != null)
                {
                    chain.back.next = link;
                }
                else
                {
                    chain.front = link;
                }
                chain.back = link;
                chain.count++;
                return link;
            }

            public static Link PrependLink(Chain<T> chain,T value)
            {
                if (chain == null)
                    throw new ArgumentNullException("chain");
                Link link = new Link(chain,null,chain.front,value);
                if (chain.front != null)
                {
                    chain.front.prev = link;
                }
                else
                {
                    chain.back = link;
                }
                chain.front = link;
                chain.count++;
                return link;
            }

            private Chain<T> chain;
            private Link prev;
            private Link next;
            private T value;
            private bool present;

            private Link(Chain<T> chain,Link prev,Link next,T value)
            {
                if (chain == null)
                    throw new ArgumentNullException("chain");
                this.chain = chain;
                this.prev = prev;
                this.next = next;
                this.value = value;
                this.present = true;
            }

            public Link Previous
            {
                get { return prev; }
            }

            public Link Next
            {
                get { return next; }
            }

            public T Value
            {
                get { return value; }
            }

            public bool Present
            {
                get { return present; }
            }

            public void Unlink()
            {
                if (!present)
                    throw new InvalidOperationException();
                present = false;
                chain.count--;
                if (prev != null)
                {
                    prev.next = next;
                }
                else
                {
                    chain.front = next;
                }
                if (next != null)
                {
                    next.prev = prev;
                }
                else
                {
                    chain.back = prev;
                }
            }
        }

        private sealed class Enumerator : IEnumerator<T>
        {
            private Chain<T> chain;
            private Link link;
            private bool started;

            public Enumerator(Chain<T> chain)
            {
                if (chain == null)
                    throw new ArgumentNullException("chain");
                this.chain = chain;
                Reset();
            }

            public T Current
            {
                get
                {
                    if (link == null)
                        throw new InvalidOperationException();
                    return link.Value;
                }
            }

            object IEnumerator.Current
            {
                get { return Current; }
            }

            public bool MoveNext()
            {
                if (!started)
                {
                    started = true;
                    link = chain.front;
                }
                else if (link != null)
                {
                    link = link.Next;
                }
                while (link != null)
                {
                    if (link.Present)
                    {
                        return true;
                    }
                }
                return false;
            }

            public void Reset()
            {
                link = null;
                started = false;
            }

            void IDisposable.Dispose()
            {
            }
        }
    }
}
