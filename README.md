# MP3 Tag Reader & Editor

## 📌 Overview

**MP3 Tag Reader & Editor** is a C-based command-line application for reading and editing ID3v2.3 metadata stored in MP3 files.

The application parses the binary structure of an MP3 file, identifies individual ID3v2.3 frames, extracts their metadata, and displays the information in a user-friendly format.

It also allows users to modify selected metadata fields while preserving the remaining contents of the MP3 file.

This project was developed to gain hands-on experience with C programming, file handling, binary data processing, structures, pointers, dynamic memory allocation, and ID3v2.3 metadata parsing.

## ✨ Features

- Read and display ID3v2.3 metadata from MP3 files.
- Supports viewing:
  - Title
  - Artist
  - Album
  - Year
  - Genre
  - Comment
  - Composer
- Edit individual metadata fields through command-line options.
- Handles ID3v2.3 frame headers and frame sizes.
- Supports UTF-16 encoded metadata and BOM handling.
- Preserves unmodified frames and MP3 audio data during editing.
- Uses a temporary file while modifying metadata to avoid directly corrupting the original file.
- Provides error handling for invalid files, unsupported tags, and invalid metadata.

## 🏷️ Supported ID3v2.3 Tags
- TIT2 – Title
- TPE1 – Artist
- TALB – Album
- TYER – Year
- TCON – Genre
- COMM – Comment
- TCOM – Composer

## ⚙️ How It Works

### Reading Metadata

The application first verifies the presence of an ID3 tag and checks that the file uses the supported ID3v2.3 format.

The ID3v2.3 header is then read, followed by the individual metadata frames. Each frame contains a frame identifier, frame size, flags, and its corresponding data.

The application parses the supported frames and stores the extracted metadata in a `TagData` structure before displaying it to the user.

```text
MP3 File
   │
   ├── ID3v2.3 Header
   │
   ├── Frame → Frame ID → Size → Flags → Data
   ├── Frame → Frame ID → Size → Flags → Data
   ├── Frame → Frame ID → Size → Flags → Data
   │
   └── Audio Data
```
### Editting Metadata

    Original MP3
        │
        ▼
    Read ID3v2.3 Frames
        │
        ├── Unmodified Frame ──────► Copy
        │
        ├── Selected Frame ────────► Modify
        │
        └── Remaining MP3 Data ────► Copy
                    │
                    ▼
                temp.mp3
                    │
                    ▼
            Copy back to MP3

## 📂 Project Structure

## 🛠️ Technologies & Concepts Used
### Language
- C

### Tools
- GCC
- Linux / WSL
- VS Code
- Git & GitHub

### C Programming Concepts
- Structures and structure pointers
- Pointers
- Dynamic memory allocation (`malloc`, `free`)
- Functions and modular programming
- Command-line arguments
- String handling
- Conditional statements and loops
- Error handling

### File Handling
- Binary file I/O
- Temporary file handling

### MP3 / Metadata Concepts
- ID3v2.3 file structure
- ID3 frame parsing
- Frame size and flag handling
- Encoding bytes
- UTF-16
- Byte Order Mark (BOM)
- Binary data manipulation
## 🔨 Compilation
### compile
```bash
gcc *.c
```
### For Viewing
```bash
./a.out -v filename.mp3
```
### For Editing
    | Option | Metadata |
    | ------ | -------- |
    | `-t`   | Title    |
    | `-a`   | Album    |
    | `-A`   | Artist   |
    | `-y`   | Year     |
    | `-c`   | Comment  |
    | `-g`   | Genre    |

For Example :
```bash
./a.out -e -y 2020 filename.mp3
```

### For Help
```bash
./a.out -h
```
## 🖥️ Sample Output
### View Metadata
![View Metadata](/Screenshots/Display-Output-Screen.png)
### Edit Screen
![Edit Screen](/Screenshots/Edit-output-screen.png)
### Example Binary Format of an MP3 file header
![Example Binary Format of an MP3 file header](/Screenshots/Binary-data.png)

## 🧠 Key Concepts Learned
- File handling
- Binary data
- Structures
- Dynamic memory allocation
- Pointers
- ID3 frame parsing
- UTF-16 / BOM
- Command-line arguments
- Temporary-file based editing
- Doxygen commenting

## Frame layout

### TIT2 / TPE1 / TALB / TCOM / TCON / TYER
    Text Frame
    ├── Frame ID       = 4 bytes
    ├── Size           = 4 bytes
    ├── Flags          = 2 bytes
    │
    ├── Encoding       = 1 byte
    ├── BOM             = FF FE        ← when Encoding = 01
    └── Text            = actual value

### COMM

    COMM
    ├── Size
    ├── Flags
    │
    ├── Encoding = 01
    ├── Language = "eng"
    │
    ├── Description
    │   ├── BOM = FF FE
    │   ├── "" (empty)
    │   └── Terminator = 00 00
    │
    └── Payload
        ├── BOM = FF FE
        └── "Your comment..."

## 🚀 Future Enhancements
- Include validations for the input values to edit

## 👤 Author
Dasmini D ❤️

## Links

### My profiles
[Github](https://github.com/Dasmini)
[Linkedin](https://www.linkedin.com/in/dasmini-d-265b3920b/)

### Reference
ID3V2.3 Tag Documentation : https://www.the-roberts-family.net/metadata/mp3.html
