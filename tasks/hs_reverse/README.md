## Название
Welcome to my inn!
## Описание/Легенда
Pull up a chair by the hearth!
Biba and Boba are playing HearthStone. Would you be kind and try to spectate their game? They are playing at 'IP:1337', password is 'paseca' and game handle equals '1'

Thats some-real world reverse, so you'll need a HearthStone for this. Don't worry, it's free to play – http://playhearthstone.com/

(Blizzard broke some visual coolness of this task with the latest updates, but it works well)
## Решение
1) Пропатчить класс инициализации игры так, чтобы IsInternal возвращало True, а IsPublic - False. Эти функции определяют режим работы игры - для разработчиков и публичный соответственно. После патча запустить игру, начать записывать трафик, открыть консоль разработчика и написать `` spectate IP 1337 1 paseca ``. Флаг будет в дампе трафика в виде бинарного кода.

2) Разреверсить протокол обмена пакетов между клиентом и сервером, сфальсифицировать корректный хендшейк, пинг и запросить GameState, после чего сервер вернет флаг в виде бинарного кода. (Пример корректного "эксплоита" в папке writeup)

**Флаг:** paseca{m3nt4l_d3pr3551ion_w4s_us3d_t0_m4k3_th15_t45k}
