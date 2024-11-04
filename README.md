# A tool to copy text from png on the wayland compositor

## Dependencies

Before you begin installation, make sure you have the following dependencies installed:
- **wayland**
- **g++**: The C++ compiler.
- **libpng**: A library for working with PNG images.
- **tesseract**: A library for text recognition.
- **tesseract-data-eng**: The language pack for English for Tesseract.
- **tesseract-data-rus**: The language pack for Russian for Tesseract.
- **leptonica**: A library for image processing used by Tesseract.
- **wl-clipboard**: Utilities for working with the clipboard in Wayland.

### Installing Dependencies

To install the dependencies on Arch Linux, run the following command:
arch linux:
```bash
sudo pacman -Syu g++ libpng tesseract tesseract-data-eng tesseract-data-rus leptonica wl-clipboard
```

ubuntu:
```
sudo apt update
sudo apt install g++ libpng-dev tesseract-ocr tesseract-ocr-eng tesseract-ocr-rus libleptonica-dev wl-clipboard
```

fedora:
```
sudo dnf install gcc-c++ libpng-devel tesseract tesseract-langpack-eng tesseract-langpack-rus leptonica-devel wl-clipboard
```

### Cloning the Repository and Installation
```bash
git clone https://github.com/acidsugarx/screenshot_to_text.git ~/screenshot_to_text
cd ~/screenshot_to_text
make
sudo ln -s $(pwd)/screenshot_to_text /usr/local/bin/screenshot_to_text
```

### Using
Copy a PNG with text to the clipboard.
Run `screenshot_to_text` in the terminal.

### Removing
```sh
sudo rm /usr/local/bin/screenshot_to_text && cd ~/screenshot_to_text  && rm -rf screenshot_to_text
```



