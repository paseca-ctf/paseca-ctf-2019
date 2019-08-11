int check9(char chr) // valid: 49
{
    if (((((((((chr * 4) + 84) << 5) ^ 2445) * 1563) + 448) - 692) ^ 1463) == 17026140)
        return 1;
    return 0;
}