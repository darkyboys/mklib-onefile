# mklib

*mklib* is a lightweight and efficient library packaging tool that compiles multiple source files into a single output file based on a `build.mklib` configuration file. It is designed to improve modular library usage by eliminating the need for multiple imports or includes, making projects easier to manage.

## Features

- Supports **any programming language**, including C++, JavaScript, and Python.
- **Simple and structured syntax** using `build.mklib`.
- **Multi-stage processing pipeline**:
  - **Lexer**: Tokenizes input and formats for the parser.
  - **Parser**: Validates syntax and generates an intermediate representation (IR).
  - **Function Unit**: Executes functions and processes variables.
  - **IR Verification**: Finalizes and verifies execution instructions.
  - **Executor**: Reads IR and performs real-time compilation.
- **File tracking** to prevent duplicate inclusions and function redefinitions.
- **Configurable logging** with `show_logs (true);` for detailed process tracking.
- **Custom execution paths** for flexibility.
- **Lightweight and dependency-free**, written in C++ using only STL.

## Installation

Since *mklib* is self-contained, you can build it easily:

```sh
# Clone the repository
git clone https://github.com/darkyboys/mklib.git
cd mklib

# Build using magma build system or a simple g++ command
# magma
magma

# g++ direct
# mkdir bin
# g++ -std=c++17 -o bin/mklib src/main.cc

# Move the binary to a directory in your PATH
mv bin/mklib /usr/local/bin/
```

If you got permission error try executing this
```
sudo mv bin/mklib /usr/local/bin/
```

## Usage

To use *mklib*, create a `build.mklib` file in your project directory and specify your settings. Example:

```mklib
extension (js);
include (main);
include (utils);
make (bundle);
show_logs (true);
```

Then, run:

```sh
mklib
```

This will generate a single `bundle.js` file containing `main.js` and `utils.js`.

## `build.mklib` Configuration

The `build.mklib` file is used to configure how *mklib* compiles your project. Below is a breakdown of the available functions and how to use them.

### Functions

#### `show_logs (true|false);`
Enables or disables verbose logging.

Example:
```mklib
show_logs (true);
```
When enabled, *mklib* will print detailed logs during execution.

#### `output_directory (dirname);`
Specifies the directory where the compiled output will be placed.

Example:
```mklib
output_directory (lib);
```
This will place the compiled output inside the `lib/` directory.

#### `output (filename);`
Specifies the name of the output file without an extension.

Example:
```mklib
output (example);
```
This will generate an output file named `example.js` (or `.cpp`/`.py` depending on the extension).

#### `extension (lang);`
Specifies the programming language of the source files.

Example:
```mklib
extension (cpp);
```
This tells *mklib* that all included files are C++ files.

#### `source_path (dirname);`
Defines the directory containing source files.

Example:
```mklib
source_path (example);
```
This tells *mklib* to look for source files inside the `example/` directory.

#### `include (filename);`
Includes a source file in the compilation process.

Example:
```mklib
include (main);
include (math);
include (string);
```
This will include `main.cpp`, `math.cpp`, and `string.cpp` (or `.js`/`.py` based on the defined extension).

#### `make ();`
Executes the compilation process based on the configuration defined in `build.mklib`.

Example:
```mklib
make ();
```
This will generate the final output file as per the specified settings.

## Commenting Styles

*mklib* supports two different commenting styles for adding comments inside `build.mklib` files:

#### `// Commenting style 1`
This style is similar to C/C++ and JavaScript comments. Anything after `//` on a line is ignored by *mklib*.

Example:
```mklib
// This is a single-line comment
output_directory (dist);
```

#### `# Commenting style 2`
This style is similar to Python and shell script comments. Anything after `#` on a line is ignored by *mklib*.

Example:
```mklib
# This is another valid comment style
extension (js);
```

Both styles can be used interchangeably within the same `build.mklib` file.

## Roadmap

- Add more optimizations for different languages.
- Improve logging and debugging tools.
- Potential GUI for easier configuration.

## License

*mklib* is open-source and licensed under the MIT License.

---

For updates and contributions, follow the project on [GitHub](https://github.com/darkyboys/mklib).

## Contributing
This project is open for contribution please refer [Guidelines](https://github.com/darkyboys/mklib/CONTRIBUTING.md)
<!-- ### Documentation
For detailed usage and advanced configurations, check the full documentation at [GitHub Wiki](https://github.com/darkyboys/mklib/wiki).
 -->
