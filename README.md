# cpp-file-check

## Инструкция

Консольная утилита на C++17. Читает текстовый файл, проверяет числа, пишет отчёт. Чужих данных в репозитории нет.

Что делает:

- Одна строка — одно значение.
- Принимает число со знаком и экспонентой: `10.5`, `-3`, `1e-2`.
- Строку, где первый непробельный символ `#`, пропускает и не считает.
- Пустую строку, не число и хвост после числа (`12.0 extra`) пишет в отказ. Хвост не отрезается.
- Каталог вместо файла — код 2. Лишний аргумент — код 1.
- Пишет отчёт без двоеточия в счётчиках: `accepted N`, `rejected N`, затем `line N: ok <value>` или `line N: reject <reason>`.

Сборка в Visual Studio 2022 или 2026: открыть папку репозитория, CMake подхватит `CMakeLists.txt`.

Из командной строки, из корня репозитория:

```
cmake -S . -B build
cmake --build build --config Release
```

Windows, генератор Visual Studio:

```
build\Release\cpp-file-check.exe samples\input.txt report.txt
```

Linux:

```
./build/cpp-file-check samples/input.txt report.txt
```

Если генератор не Visual Studio, Windows-exe лежит в `build\cpp-file-check.exe`, не в `build\Release\`.

`std::from_chars` для `double` нужен Visual Studio 2019 16.4 или новее, либо GCC 11+.

На примере `samples/input.txt` ожидается `accepted 4` и `rejected 3`: приняты `10.5`, `-3`, `1e-2`, `4.25`; отказ — пустая строка, `abc`, хвост после числа.

## What it does

C++17 console tool: read a text file, check numbers, write a report. No customer data.

- One value per line.
- Accepts a number, including a sign and an exponent (`10.5`, `-3`, `1e-2`).
- Skips a line whose first non-space character is `#`. Comments are not counted.
- Rejects an empty line, a non-number, and trailing junk (`12.0 extra`).
- A directory instead of a file returns code 2. An extra argument returns code 1.
- Report counters have no colon: `accepted N`, `rejected N`, then `line N: ok <value>` or `line N: reject <reason>`.

## Build

Visual Studio 2022 or 2026: open the folder, CMake picks `CMakeLists.txt`.

```
cmake -S . -B build
cmake --build build --config Release
```

Windows, Visual Studio generator:

```
build\Release\cpp-file-check.exe samples\input.txt report.txt
```

Linux:

```
./build/cpp-file-check samples/input.txt report.txt
```

`std::from_chars` for `double` needs Visual Studio 2019 16.4 or newer, or GCC 11+.

## License

MIT
