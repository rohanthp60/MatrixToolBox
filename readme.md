# Steps to Use the SFML Graphics Library with g++

## Method 1: Using Dynamic Linking (Requires SFML DLL Files at Runtime)

1. **Include the SFML Header Files**  
   Ensure the compiler knows where to find the SFML headers:
   ```bash
   g++ -c source.cpp -I"<SFML_PATH>/include"
   ```
   Replace `<SFML_PATH>` with the actual installation directory of SFML.

2. **Compile the Object File**  
   ```bash
   g++ -c source.cpp -I"C:\path\to\SFML\include"
   ```
   This generates an object file (`source.o` or `source.obj` on Windows).

3. **Link with SFML Libraries**  
   ```bash
   g++ source.o -o output_executable -L"C:\path\to\SFML\lib" -lsfml-graphics -lsfml-window -lsfml-system
   ```
   This links against SFML libraries dynamically.

4. **Copy Required DLL Files**  
   Move all necessary SFML DLL files (found in the `bin` directory of SFML) to the folder where the executable is located. This ensures the application finds the required SFML libraries at runtime.

---

## Method 2: Using Static Linking (No DLL Files Required)

1. **Compile the Object File with Static Definition**  
   ```bash
   g++ -c source.cpp -I"C:\path\to\SFML\include" -DSFML_STATIC
   ```
   The `-DSFML_STATIC` flag tells the compiler to use the static version of SFML.

2. **Link with Static SFML Libraries**  
   ```bash
   g++ source.o -o output_executable -L"C:\path\to\SFML\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows
   ```
   Since static linking embeds the SFML code directly into the executable, additional dependencies like OpenGL (`-lopengl32`), FreeType (`-lfreetype`), Windows Multimedia (`-lwinmm`), and GDI (`-lgdi32`) must be explicitly linked.

3. **Alternative Static Linking with sfml-main (for GUI Applications)**  
   ```bash
   g++ source.o -o output_executable -L"C:\path\to\SFML\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main
   ```
   This version includes `-lsfml-main`, which is needed if your program does not define `main()` in a standard console application format (common for SFML GUI-based programs).

---

## Summary
- **Dynamic Linking**: Requires DLL files at runtime but results in a smaller executable.
- **Static Linking**: Embeds SFML directly into the executable, avoiding DLL dependencies but increasing the file size.

Choose the method based on your project needs!

---

## File Naming
Save this document as `README.md` in your project directory to provide clear setup instructions.

