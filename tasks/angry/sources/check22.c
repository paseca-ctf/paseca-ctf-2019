int check22(char chr) // valid: 109
{
    if (((((((((chr * 5) + 1471) << 2) ^ 2103) * 1732) + 1293) - 1541) ^ 3388) == 10517528)
        return 1;
    return 0;
}