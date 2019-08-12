int check32(char chr) // valid: 110
{
    if (((((((((chr * 8) + 1833) << 3) ^ 396) * 156) + 153) - 619) ^ 3299) == 3407741)
        return 1;
    return 0;
}