# Testy jednostkowe w C++

Materiały, ćwiczenia i quiz do laboratorium z testów jednostkowych w C++ (GoogleTest + gMock).

## Struktura

- `lab/` — notebooki JupyterLab z materiałami i ćwiczeniami; zacznij od `lab/_start.ipynb`
  - `lab/0N_<temat>/` — notebook tematu, kod demonstracji (`demos/`) i ćwiczenia
  - `lab/cmake/lab.cmake` — wspólne ustawienia CMake (C++20, GoogleTest 1.18.0)
- `pyproject.toml` — środowisko Pythona dla notebooków (zarządzane przez [uv](https://docs.astral.sh/uv/))

## Wymagania

- kompilator C++20: GCC 11+, Clang 14+, Visual Studio 2022+ albo Apple Clang (Xcode 15+)
- CMake 3.22+
- [uv](https://docs.astral.sh/uv/getting-started/installation/) — sam pobierze Pythona (3.10+), jeśli go nie masz
- dostęp do internetu przy pierwszym uruchomieniu (uv pobiera pakiety, CMake pobiera GoogleTest)

## Jak zacząć

### Linux (Ubuntu 22.04/24.04, Debian 12/13) i WSL

```bash
sudo apt update
sudo apt install -y g++ cmake git curl
curl -LsSf https://astral.sh/uv/install.sh | sh
uv sync
uv run --with jupyterlab jupyter lab lab/_start.ipynb
```

### macOS

```bash
xcode-select --install
brew install cmake uv
uv sync
uv run --with jupyterlab jupyter lab lab/_start.ipynb
```

### Windows

1. Zainstaluj Visual Studio 2022 (Community) z pakietem „Programowanie aplikacji klasycznych w języku C++”
   (zawiera kompilator MSVC i CMake) oraz uv: `winget install astral-sh.uv`.
2. Otwórz **Developer PowerShell for VS 2022** — tylko tam `cl` i `cmake` są dostępne dla komórek notebooka.
3. W tym oknie, w katalogu repozytorium:
   ```powershell
   uv sync
   uv run --with jupyterlab jupyter lab lab\_start.ipynb
   ```

Najprościej jest jednak użyć WSL2 z Ubuntu i instrukcji dla Linuksa.

`uv sync` tworzy środowisko `.venv` z jądrem Pythona (`ipykernel`) i narzędziem `gcovr` (pokrycie kodu). Zamiast JupyterLab możesz też otworzyć
notebooki w VS Code i wybrać jądro z `.venv`.

Po uruchomieniu notebooka `_start.ipynb` wykonaj komórki w sekcji „Sprawdzenie środowiska”.

## Autorzy

- Tomasz Idźkowski (idzkowskit@student.agh.edu.pl)
- Kacper Kobieluch (kkobieluch@student.agh.edu.pl)
- Maksymilian Koleśniak (mkolesniak@student.agh.edu.pl)
