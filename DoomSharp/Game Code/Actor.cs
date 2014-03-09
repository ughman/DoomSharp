using System;
using System.Collections.Generic;

namespace DoomSharp
{
    public abstract class Actor : Thinker
    {
        // TODO :: x
        // TODO :: y
        // TODO :: z
        // TODO :: angle
        // TODO :: spritenum
        // TODO :: spriteframe
        // TODO :: radius
        // TODO :: height
        // TODO :: xmomentum
        // TODO :: ymomentum
        // TODO :: zmomentum
        // TODO :: ticks
        // TODO :: statenum
        // TODO :: special
        // TODO :: solid
        // TODO :: shootable
        // TODO :: nosector
        // TODO :: noblockmap
        // TODO :: ambush
        // TODO :: justhit
        // TODO :: justattacked
        // TODO :: spawnceiling
        // TODO :: nogravity
        // TODO :: dropoff
        // TODO :: pickup
        // TODO :: noclip
        // TODO :: slide
        // TODO :: float
        // TODO :: teleport
        // TODO :: missile
        // TODO :: dropped
        // TODO :: shadow
        // TODO :: noblood
        // TODO :: corpse
        // TODO :: infloat
        // TODO :: countkill
        // TODO :: countitem
        // TODO :: skullfly
        // TODO :: notdmatch
        // TODO :: health
        // TODO :: movementdirection
        // TODO :: movementcount
        // TODO :: target
        // TODO :: reactiontime
        // TODO :: lastlook
        // TODO :: tracer
        private Fixed speed;
        private int mass;
        private int damage;
        private int painchance;
        private int seesoundnum;
        private int activesoundnum;
        private int attacksoundnum;
        private int painsoundnum;
        private int deathsoundnum;
        private object species;
        private Dictionary<string,int> states;

        public Actor()
        {
            // TODO :: x
            // TODO :: y
            // TODO :: z
            // TODO :: angle
            // TODO :: spritenum
            // TODO :: spriteframe
            // TODO :: radius
            // TODO :: height
            // TODO :: xmomentum
            // TODO :: ymomentum
            // TODO :: zmomentum
            // TODO :: ticks
            // TODO :: statenum
            // TODO :: special
            // TODO :: solid
            // TODO :: shootable
            // TODO :: nosector
            // TODO :: noblockmap
            // TODO :: ambush
            // TODO :: justhit
            // TODO :: justattacked
            // TODO :: spawnceiling
            // TODO :: nogravity
            // TODO :: dropoff
            // TODO :: pickup
            // TODO :: noclip
            // TODO :: slide
            // TODO :: float
            // TODO :: teleport
            // TODO :: missile
            // TODO :: dropped
            // TODO :: shadow
            // TODO :: noblood
            // TODO :: corpse
            // TODO :: infloat
            // TODO :: countkill
            // TODO :: countitem
            // TODO :: skullfly
            // TODO :: notdmatch
            // TODO :: health
            // TODO :: movementdirection
            // TODO :: movementcount
            // TODO :: target
            // TODO :: reactiontime
            // TODO :: lastlook
            // TODO :: tracer
            this.speed = Fixed.Zero;
            this.mass = 100;
            this.damage = 0;
            this.painchance = 0;
            this.seesoundnum = 0;
            this.activesoundnum = 0;
            this.attacksoundnum = 0;
            this.painsoundnum = 0;
            this.deathsoundnum = 0;
            this.species = GetType();
            this.states = new Dictionary<string,int>();
            DefineState("Spawn",0);
        }

        public abstract Fixed X
        {
            get;
            set;
        }

        public abstract Fixed Y
        {
            get;
            set;
        }

        public abstract Fixed Z
        {
            get;
            set;
        }

        public abstract uint Angle
        {
            get;
            set;
        }

        public abstract int SpriteNum
        {
            get;
            set;
        }

        public abstract int SpriteFrame
        {
            get;
            set;
        }

        public abstract Fixed Radius
        {
            get;
            set;
        }

        public abstract Fixed Height
        {
            get;
            set;
        }

        public abstract Fixed XMomentum
        {
            get;
            set;
        }

        public abstract Fixed YMomentum
        {
            get;
            set;
        }

        public abstract Fixed ZMomentum
        {
            get;
            set;
        }

        public abstract int Ticks
        {
            get;
            set;
        }

        public abstract int StateNum
        {
            get;
            set;
        }

        public abstract bool Special
        {
            get;
            set;
        }

        public abstract bool Solid
        {
            get;
            set;
        }

        public abstract bool Shootable
        {
            get;
            set;
        }

        public abstract bool NoSector
        {
            get;
            set;
        }

        public abstract bool NoBlockmap
        {
            get;
            set;
        }

        public abstract bool Ambush
        {
            get;
            set;
        }

        public abstract bool JustHit
        {
            get;
            set;
        }

        public abstract bool JustAttacked
        {
            get;
            set;
        }

        public abstract bool SpawnCeiling
        {
            get;
            set;
        }

        public abstract bool NoGravity
        {
            get;
            set;
        }

        public abstract bool DropOff
        {
            get;
            set;
        }

        public abstract bool Pickup
        {
            get;
            set;
        }

        public abstract bool NoClip
        {
            get;
            set;
        }

        public abstract bool Slide
        {
            get;
            set;
        }

        public abstract bool Float
        {
            get;
            set;
        }

        public abstract bool Teleport
        {
            get;
            set;
        }

        public abstract bool Missile
        {
            get;
            set;
        }

        public abstract bool Dropped
        {
            get;
            set;
        }

        public abstract bool Shadow
        {
            get;
            set;
        }

        public abstract bool NoBlood
        {
            get;
            set;
        }

        public abstract bool Corpse
        {
            get;
            set;
        }

        public abstract bool InFloat
        {
            get;
            set;
        }

        public abstract bool CountKill
        {
            get;
            set;
        }

        public abstract bool CountItem
        {
            get;
            set;
        }

        public abstract bool SkullFly
        {
            get;
            set;
        }

        public abstract bool NotDMatch
        {
            get;
            set;
        }

        public abstract int Health
        {
            get;
            set;
        }

        public abstract int MovementDirection
        {
            get;
            set;
        }

        public abstract int MovementCount
        {
            get;
            set;
        }

        public abstract Actor Target
        {
            get;
            set;
        }

        public abstract int ReactionTime
        {
            get;
            set;
        }

        public abstract int LastLook
        {
            get;
            set;
        }

        public abstract Actor Tracer
        {
            get;
            set;
        }

        public Fixed Speed
        {
            get { return speed; }
            set { speed = value; }
        }

        public int Mass
        {
            get { return mass; }
            set { mass = value; }
        }

        public int Damage
        {
            get { return damage; }
            set { damage = value; }
        }

        public int PainChance
        {
            get { return painchance; }
            set { painchance = value; }
        }

        public int SeeSoundNum
        {
            get { return seesoundnum; }
            set { seesoundnum = value; }
        }

        public int ActiveSoundNum
        {
            get { return activesoundnum; }
            set { activesoundnum = value; }
        }

        public int AttackSoundNum
        {
            get { return attacksoundnum; }
            set { attacksoundnum = value; }
        }

        public int PainSoundNum
        {
            get { return painsoundnum; }
            set { painsoundnum = value; }
        }

        public int DeathSoundNum
        {
            get { return deathsoundnum; }
            set { deathsoundnum = value; }
        }

        public object Species
        {
            get { return species; }
            set { species = value; }
        }

        public void DefineState(string name,int statenum)
        {
            if (name == null)
                throw new ArgumentNullException("name");
            states[name] = statenum;
        }

        public bool HasState(string name)
        {
            if (name == null)
                throw new ArgumentNullException("name");
            return states.ContainsKey(name);
        }

        public int GetStateNum(string name)
        {
            if (name == null)
                throw new ArgumentNullException("name");
            int statenum;
            if (states.TryGetValue(name,out statenum))
            {
                return statenum;
            }
            else
            {
                throw new ApplicationException();
            }
        }
    }
}
