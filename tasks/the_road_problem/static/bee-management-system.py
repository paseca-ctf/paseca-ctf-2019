print('Enter bee numbers. Example: 1 2 3 4 5 6')
while True:
    bees = [int(bee) for bee in input('> ').split()]
    if len(bees) % 2 != 0:
        print('Bees cannot be grouped')
        continue
    bee_groups = [(bees[i], bees[i+1]) for i in range(0, len(bees), 2)]
    print('Bee groups:')
    for bee_group in bee_groups:
        print(bee_group)