import time
from random import randint

a = randint(10**3, 10**5)  # 2416
c = randint(10**4, 10**6)  # 374441
m = randint(10**4, 10**8)  # 1771875

previous_seed = int(time.time())
current_seed = (a * previous_seed + c) % m


def next_number():
    global current_seed, previous_seed
    previous_seed, current_seed = current_seed, (a * current_seed + c) % m


def current_number():
    return current_seed


def previous_number():
    return previous_seed
