/*----------------------------------------------------------------------------------------------------------
 --  SOURCE FILE: bitmask.h
 --
 --  PROGRAM: TuxSpace
 --
 --  FUNCTIONS:
 --      void Bitmask::Set(FlagEnum flags)
 --      void Bitmask::Clear(FlagEnum flags)
 --      void Bitmask::Test(FlagEnum flags) const
 --      void Bitmask::TestAllFlags(FlagEnum flags) const
 --
 --  REVISIONS (date and description):
 --      2010-02-18 (Ben): Added getBitField method and constructor for serialisation
 --
 --  DATE: 2010-01-23
 --
 --  NOTES: Shamelessly stolen from 'ApochPiQ' at:
 --         http://www.gamedev.net/community/forums/topic.asp?topic_id=398874
 ----------------------------------------------------------------------------------------------------------*/

#ifndef BITMASK_H
#define BITMASK_H

template<typename Holder, typename FlagEnum>
class Bitmask
{
public:

    Bitmask() { Bitfield = 0; }
    Bitmask(Holder mask) : Bitmask(mask) {}

    // Sets all bitmask bits which are set in "flags"
    inline void Set(FlagEnum flags)
    {
        Bitfield |= flags;
    }

    // Clears all bitmask bits which are set in "flags"
    inline void Clear(FlagEnum flags)
    {
        Bitfield &= (~flags);
    }

    // Return true if ANY of the bits set in "flags" are
    // also set for the bitmask
    inline bool Test(FlagEnum flags) const
    {
        return ((Bitfield & flags) != 0);
    }

    // Return true only if ALL bits set in "flags" are
    // also set for the bitmask
    inline bool TestAllFlags(FlagEnum flags) const
    {
        return ((Bitfield & flags) == flags);
    }

    inline Holder getBitField()
    {
        return Bitfield;
    }

    inline void setBitField(Holder bitfield)
    {
        Bitfield = bitfield;
    }

protected:
    Holder Bitfield;
};

#endif
