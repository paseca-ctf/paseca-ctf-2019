int check19(char chr) // valid: 115
{
    if (((((((((chr * 10) + 1204) << 5) ^ 2348) * 225) + 1549) - 1517) ^ 3974) == 17473930)
        return 1;
    return 0;
}