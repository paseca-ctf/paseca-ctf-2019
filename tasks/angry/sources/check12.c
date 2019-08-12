int check12(char chr) // valid: 116
{
    if (((((((((chr * 10) + 1422) << 3) ^ 180) * 1920) + 750) - 1913) ^ 1493) == 39328928)
        return 1;
    return 0;
}