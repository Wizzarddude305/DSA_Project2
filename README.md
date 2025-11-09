## Setup Instructions
### 1. Install Qt
QT version 6.10.0
**For Windows:**- Download Qt Online Installer- Install Qt 6.x (6.10.0 or later recommended)- Select either:  - **MinGW** components (if using MinGW compiler)  - **MSVC** components (if using Visual Studio)

**For Linux:**```bashsudo apt-get install qt6-base-dev qt6-base-dev-tools```

**For macOS:**```brew install qt@6```, if homebrew isn’t installed then follow the instructions of installing homebrew here
https://docs.brew.sh/Installation

### 2. Clone the Repository

```git clone <repository-url>cd DSA_Project2-1```

### 3. Configure CMake with Qt Path
**Option A: Set in CLion**1. File → Settings → Build, Execution, Deployment → CMake2. Add to CMake options:   ```   -DCMAKE_PREFIX_PATH=C:/Qt/6.10.0/mingw_64/lib/cmake   ```   (Adjust path for your Qt installation and compiler)


**Option B: Command Line**```cmake -S . -B build -DCMAKE_PREFIX_PATH=<Qt-install-path>/lib/cmake```


**Example paths:**- Windows MinGW: `C:/Qt/6.10.0/mingw_64/lib/cmake`- Windows MSVC: `C:/Qt/6.10.0/msvc2019_64/lib/cmake`- Linux: `/usr/lib/x86_64-linux-gnu/cmake/Qt6`- macOS: `/opt/homebrew/lib/cmake/Qt6`

P.S in order to find directory for Windows it’s where you let the download happen in mac search with brew info qt@6 and for Linux dpkg -L qt6-base-dev | grep Qt6Config.cmake

### 4. Build the Project

**In CLion:**- Select target: **PokemonUI** or **Tests**- Click Build → Build Project

**Command Line:**```cmake --build build --target PokemonUI
cmake --build build --target Tests```

### 5. Run the UI Application
**In CLion:**1. Run → Edit Configurations
2. Select PokemonUI3. 
(For windows) set **Working directory** to: `$PROJECT_DIR$`4. Add **Environment variable**:   - `PATH=C:/Qt/6.10.0/mingw_64/bin;$PATH`   (Adjust path for your Qt installation)
5. Click Run

**Command Line:**```Set PATH to Qt DLLs (Windows)export PATH=/path/to/Qt/6.10.0/mingw_64/bin:$PATH  # Linux/Macset 

PATH=C:\Qt\6.10.0\mingw_64\bin;%PATH%  # Windows 

CMD$env:PATH="C:\Qt\6.10.0\mingw_64\bin;$env:PATH"  # Windows PowerShell

# Run./build/PokemonUI  # Linux/Macbuild\PokemonUI.exe  # Windows```

## Project Structure
```DSA_Project2-1/├── src/│   ├── app_ui.cpp       # Qt UI application│   ├── main.cpp         # Command-line interface│   ├── pokemon.h        # Pokemon data class│   ├── hashTable.h      # Hash table implementation│   ├── trieTree.h       # Trie tree implementation│   └── linkedLists.h    # Linked list for hash table├── test/│   ├── test.cpp         # Catch2 unit tests│   └── test.h├── data/│   ├── dataOrganize.py  # Python script to process raw JSON data│   ├── raw_files/       # Raw Pokemon data from Smogon│   └── cppOrganized/    # Organized data for C++ loading├── CMakeLists.txt       # CMake build configuration└── README.md            # This file```

## Usage
### Qt UI Application
1. Launch **PokemonUI**2. Select data structure: **HashTable** or **Trie**3. Select statistic type: **Teammates** or **Moves**4. Enter Pokemon name (e.g., "Excadrill", "Landorus-Therian")5. Click **Search**6. View results sorted by usage percentage

### Command Line Interface
```bash./build/main  # or main.exe on Windows# Follow prompts to choose data structure and search```
## Data Source
Pokemon usage statistics from [Smogon](https://www.smogon.com/stats/):- 2025 moveset data- Multiple generations (Gen 1-6)- Usage percentages for moves and teammates
## Testing
Run unit tests:```bashcmake --build build --target Tests./build/Tests  # or Tests.exe on Windows```
Tests verify:- HashTable insertion/search with 100,000 entries- TrieTree insertion/search with 100,000 entries
## Troubleshooting
### Qt Not Found- Ensure Qt is installed and CMake can find it- Check `CMAKE_PREFIX_PATH` points to Qt's `lib/cmake` directory- Verify Qt version matches your compiler (MinGW vs MSVC)
### DLL Not Found (Windows)- Add Qt `bin` directory to PATH environment variable- Or copy required DLLs to executable directory
### Data File Not Found- Ensure working directory is set to project root- Check that `data/cppOrganized/AllPokemon-organized.txt` exists- Run `data/dataOrganize.py` to regenerate data if needed


