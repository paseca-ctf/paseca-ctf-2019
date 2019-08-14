## Легенда
Morgan Beeman works for a big company BEENCA. Today he is going to have an important day: he is presenting his new algorithm called Bee Management System to the boss. However, when he looked at his watch in the morning, he realized, that he was going to be late. Mr. Beeman lives in a large city, but he is aware of traffic conditions on every road. Please, help Morgan to get to the BEENCA office as quickly as possible. 

File description:

map.png
City map with Mr. Beeman's home and BEENCA office marked on it.

input.txt 
Contains information about traffic conditions.
There are 5776 blocks of data.
Block structure:
First line contains an integer v - crossroad number (v = 76*y+x where (x, y) - crossroad's coordinates ((0, 0) - top left corner of the map)).
Next 2-4 lines contain two integers u, w each - number of crossroad that is connected with v with a road which has traffic load w.

bee-management-system.py
Mr. Beeman's Bee Management System algorithm

## Решение

Дейкстра / тупость (если всегда ходить по минимальному весу тоже решится правильно) - реализация у обоих одинакового размера

Нарисовать пройденный путь на карте, понять что флаг будет в рисунке на карте, но пока он не читается

Подумать зачем дали BMS и догадаться что его нужно применить к весам, по которым был прйоден путь

В результате получатся кооридинаты точек, соединив которые получим флаг

paseca{the_gr3ate5t_r0ute}

