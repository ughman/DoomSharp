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
        // TODO :: speed
        // TODO :: mass
        // TODO :: damage
        // TODO :: painchance
        // TODO :: seesoundnum
        // TODO :: activesoundnum
        // TODO :: attacksoundnum
        // TODO :: painsoundnum
        // TODO :: deathsoundnum
        // TODO :: species

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
            // TODO :: speed
            // TODO :: mass
            // TODO :: damage
            // TODO :: painchance
            // TODO :: seesoundnum
            // TODO :: activesoundnum
            // TODO :: attacksoundnum
            // TODO :: painsoundnum
            // TODO :: deathsoundnum
            // TODO :: species
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

        public abstract Fixed Speed
        {
            get;
            set;
        }

        public abstract int Mass
        {
            get;
            set;
        }

        public abstract int Damage
        {
            get;
            set;
        }

        public abstract int PainChance
        {
            get;
            set;
        }

        public abstract int SeeSoundNum
        {
            get;
            set;
        }

        public abstract int ActiveSoundNum
        {
            get;
            set;
        }

        public abstract int AttackSoundNum
        {
            get;
            set;
        }

        public abstract int PainSoundNum
        {
            get;
            set;
        }

        public abstract int DeathSoundNum
        {
            get;
            set;
        }

        public abstract object Species
        {
            get;
            set;
        }

        public abstract void DefineState(string name,int statenum);

        public abstract bool HasState(string name);

        public abstract int GetStateNum(string name);
    }
}
