# cpp-file-check

C++17 console tool: read a text file, check numbers, write a report.

Public sample for small C++ tasks. No customer data.

## What it does

- One value per line.
- Accepts a number, including a sign and an exponent (`10.5`, `-3`, `1e-2`).
- Skips a line whose first non-space character is `#`.
- Rejects an empty line, a non-number, and trailing junk (`12.0 extra`).
- Writes `report.txt` with accepted count, rejected count, and one line per checked row.

## Build

Visual Studio 2022, open the folder, CMake will pick `CMakeLists.txt`.

Command line:

```
cmake -S . -B build
cmake --build build --config Release
```

Run from the repo root:

```
build\Release\cpp-file-check.exe samples\input.txt report.txt
```

Generator other than Visual Studio may put the exe in `build\cpp-file-check.exe`.

`std::from_chars` for `double` needs Visual Studio 2019 16.4 or newer, or GCC 11+.

## License

MIT
