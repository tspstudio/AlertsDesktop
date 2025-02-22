# AlertsDesktop - карта тривог для вашого комп'ютера

# Встановлення
Релізів поки що нема, але обов'язково будуть в майбутньому!
Перейдіть на [https://github.com/tspstudio/AlertsDesktop/releases](https://github.com/tspstudio/AlertsDesktop/releases) та завантажте виконуваний файл для вашої системи і запустіть його.

# Збірка

## Windows
Збірка під Windows ще не підтримується

## Linux
Встановіть останню версію Qt Creator i інструменти для збірки програм Qt6, шлях до заголовкових файлів і бібліотек для лінковки має бути прописаний в системі!

Встановіть nlohmann-json, libcurl, libnotify, glibc, cmake

Запустіть скрипт build.sh або самостійно виконайте
```bash
cmake build .
make
```

Запустіть виконуваний файл.