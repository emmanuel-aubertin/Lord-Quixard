struct Tile
{
    enum Sign {X, O, Blank};
    Sign sign;

    Tile() : sign(Blank) {};
};
