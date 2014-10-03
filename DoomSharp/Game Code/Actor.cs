using System;
using System.Collections.Generic;

namespace DoomSharp
{
    [Scriptable]
    public abstract class Actor : Thinker
    {
        private bool linked;
        protected abstract Fixed x { get; set; }
        protected abstract Fixed y { get; set; }
        protected abstract Fixed z { get; set; }
        protected abstract Angle angle { get; set; }
        protected abstract int spritenum { get; set; }
        protected abstract int spriteframe { get; set; }
        protected abstract Fixed radius { get; set; }
        protected abstract Fixed height { get; set; }
        protected abstract Fixed xmomentum { get; set; }
        protected abstract Fixed ymomentum { get; set; }
        protected abstract Fixed zmomentum { get; set; }
        protected abstract int ticks { get; set; }
        protected abstract int statenum { get; set; }
        protected abstract bool special { get; set; }
        protected abstract bool solid { get; set; }
        protected abstract bool shootable { get; set; }
        protected abstract bool nosector { get; set; }
        protected abstract bool noblockmap { get; set; }
        protected abstract bool ambush { get; set; }
        protected abstract bool justhit { get; set; }
        protected abstract bool justattacked { get; set; }
        protected abstract bool spawnceiling { get; set; }
        protected abstract bool nogravity { get; set; }
        protected abstract bool dropoff { get; set; }
        protected abstract bool pickup { get; set; }
        protected abstract bool noclip { get; set; }
        protected abstract bool slide { get; set; }
        protected abstract bool floats { get; set; }
        protected abstract bool teleport { get; set; }
        protected abstract bool missile { get; set; }
        protected abstract bool dropped { get; set; }
        protected abstract bool shadow { get; set; }
        protected abstract bool noblood { get; set; }
        protected abstract bool corpse { get; set; }
        protected abstract bool infloat { get; set; }
        protected abstract bool countkill { get; set; }
        protected abstract bool countitem { get; set; }
        protected abstract bool skullfly { get; set; }
        protected abstract bool notdmatch { get; set; }
        protected abstract int health { get; set; }
        protected abstract int movementdirection { get; set; }
        protected abstract int movementcount { get; set; }
        protected abstract Actor target { get; set; }
        protected abstract int reactiontime { get; set; }
        protected abstract int lastlook { get; set; }
        protected abstract Actor tracer { get; set; }
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

        public Actor(World world) : base(world)
        {
            this.linked = false;
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

        public bool Linked
        {
            get { return linked; }
        }

        [Scriptable(ScriptAccessType.Get)]
        public Fixed X
        {
            get { return x; }
            set { x = value; }
        }

        [Scriptable(ScriptAccessType.Get)]
        public Fixed Y
        {
            get { return y; }
            set { y = value; }
        }

        [Scriptable(ScriptAccessType.Get)]
        public Fixed Z
        {
            get { return z; }
            set { z = value; }
        }

        [Scriptable]
        public Angle Angle
        {
            get { return angle; }
            set { angle = value; }
        }

        public int SpriteNum
        {
            get { return spritenum; }
            set { spritenum = value; }
        }

        public int SpriteFrame
        {
            get { return spriteframe; }
            set { spriteframe = value; }
        }

        [Scriptable]
        public Fixed Radius
        {
            get { return radius; }
            set { radius = value; }
        }

        [Scriptable]
        public Fixed Height
        {
            get { return height; }
            set { height = value; }
        }

        [Scriptable]
        public Fixed XMomentum
        {
            get { return xmomentum; }
            set { xmomentum = value; }
        }

        [Scriptable]
        public Fixed YMomentum
        {
            get { return ymomentum; }
            set { ymomentum = value; }
        }

        [Scriptable]
        public Fixed ZMomentum
        {
            get { return zmomentum; }
            set { zmomentum = value; }
        }

        [Scriptable]
        public int Ticks
        {
            get { return ticks; }
            set { ticks = value; }
        }

        public int StateNum
        {
            get { return statenum; }
            set { statenum = value; }
        }

        public bool Special
        {
            get { return special; }
            set { special = value; }
        }

        [Scriptable]
        public bool Solid
        {
            get { return solid; }
            set { solid = value; }
        }

        [Scriptable]
        public bool Shootable
        {
            get { return shootable; }
            set { shootable = value; }
        }

        [Scriptable(ScriptAccessType.Get)]
        public bool NoSector
        {
            get { return nosector; }
            set { nosector = value; }
        }

        [Scriptable(ScriptAccessType.Get)]
        public bool NoBlockmap
        {
            get { return noblockmap; }
            set { noblockmap = value; }
        }

        [Scriptable]
        public bool Ambush
        {
            get { return ambush; }
            set { ambush = value; }
        }

        [Scriptable]
        public bool JustHit
        {
            get { return justhit; }
            set { justhit = value; }
        }

        [Scriptable]
        public bool JustAttacked
        {
            get { return justattacked; }
            set { justattacked = value; }
        }

        [Scriptable]
        public bool SpawnCeiling
        {
            get { return spawnceiling; }
            set { spawnceiling = value; }
        }

        [Scriptable]
        public bool NoGravity
        {
            get { return nogravity; }
            set { nogravity = value; }
        }

        [Scriptable]
        public bool DropOff
        {
            get { return dropoff; }
            set { dropoff = value; }
        }

        public bool Pickup
        {
            get { return pickup; }
            set { pickup = value; }
        }

        [Scriptable]
        public bool NoClip
        {
            get { return noclip; }
            set { noclip = value; }
        }

        [Scriptable]
        public bool Slide
        {
            get { return slide; }
            set { slide = value; }
        }

        [Scriptable]
        public bool Floats
        {
            get { return floats; }
            set { floats = value; }
        }

        [Scriptable]
        public bool Teleport
        {
            get { return teleport; }
            set { teleport = value; }
        }

        [Scriptable]
        public bool Missile
        {
            get { return missile; }
            set { missile = value; }
        }

        [Scriptable]
        public bool Dropped
        {
            get { return dropped; }
            set { dropped = value; }
        }

        [Scriptable]
        public bool Shadow
        {
            get { return shadow; }
            set { shadow = value; }
        }

        [Scriptable]
        public bool NoBlood
        {
            get { return noblood; }
            set { noblood = value; }
        }

        [Scriptable]
        public bool Corpse
        {
            get { return corpse; }
            set { corpse = value; }
        }

        [Scriptable]
        public bool InFloat
        {
            get { return infloat; }
            set { infloat = value; }
        }

        [Scriptable]
        public bool CountKill
        {
            get { return countkill; }
            set { countkill = value; }
        }

        [Scriptable]
        public bool CountItem
        {
            get { return countitem; }
            set { countitem = value; }
        }

        [Scriptable]
        public bool SkullFly
        {
            get { return skullfly; }
            set { skullfly = value; }
        }

        [Scriptable]
        public bool NotDMatch
        {
            get { return notdmatch; }
            set { notdmatch = value; }
        }

        [Scriptable]
        public int Health
        {
            get { return health; }
            set { health = value; }
        }

        public int MovementDirection
        {
            get { return movementdirection; }
            set { movementdirection = value; }
        }

        public int MovementCount
        {
            get { return movementcount; }
            set { movementcount = value; }
        }

        [Scriptable]
        public Actor Target
        {
            get { return target; }
            set { target = value; }
        }

        [Scriptable]
        public int ReactionTime
        {
            get { return reactiontime; }
            set { reactiontime = value; }
        }

        public int LastLook
        {
            get { return lastlook; }
            set { lastlook = value; }
        }

        [Scriptable]
        public Actor Tracer
        {
            get { return tracer; }
            set { tracer = value; }
        }

        [Scriptable]
        public Fixed Speed
        {
            get { return speed; }
            set { speed = value; }
        }

        [Scriptable]
        public int Mass
        {
            get { return mass; }
            set { mass = value; }
        }

        [Scriptable]
        public int Damage
        {
            get { return damage; }
            set { damage = value; }
        }

        [Scriptable]
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

        [Scriptable]
        public object Species
        {
            get { return species; }
            set { species = value; }
        }

        public void Link()
        {
            if (linked)
                throw new InvalidOperationException();
            linked = true;
            LinkSubsector();
            if (!nosector)
                LinkSector();
            if (!noblockmap)
            {
                int blockx = (x - World.Blockmap.XOffset).IntValue / 128;
                int blocky = (y - World.Blockmap.YOffset).IntValue / 128;
                if (blockx >= 0 && blockx < World.Blockmap.Width && blocky >= 0 && blocky < World.Blockmap.Height)
                {
                    World.Blockmap[blockx,blocky].AddActor(this);
                }
            }
        }

        public void Unlink()
        {
            if (!linked)
                throw new InvalidOperationException();
            linked = false;
            if (!nosector)
                UnlinkSector();
            if (!noblockmap)
            {
                int blockx = (x - World.Blockmap.XOffset).IntValue / 128;
                int blocky = (y - World.Blockmap.YOffset).IntValue / 128;
                if (blockx >= 0 && blockx < World.Blockmap.Width && blocky >= 0 && blocky < World.Blockmap.Height)
                {
                    World.Blockmap[blockx,blocky].RemoveActor(this);
                }
            }
        }

        protected abstract void LinkSubsector();
        protected abstract void LinkSector();
        protected abstract void UnlinkSector();

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
