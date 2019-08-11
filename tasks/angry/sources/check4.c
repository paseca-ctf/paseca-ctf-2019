int check4(char chr) // valid: 101
{
    if (((((((((chr * 6) + 121) << 3) ^ 3941) * 741) + 1058) - 19) ^ 479) == 4907295)
        return 1;
    return 0;
}