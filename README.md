# minishell

A small Unix-like shell written in C (42 School project).

## Features
- Interactive prompt
- Command execution via `PATH` and absolute/relative paths
- Builtins: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Pipes (`|`)
- Redirections: `<`, `>`, `>>`, heredoc (`<<`)
- Environment variable expansion (`$VAR`, `$?`)
- Signal handling (Ctrl-C, Ctrl-\, Ctrl-D)

> Note: The exact feature set depends on the current implementation.

## Requirements
- C compiler (e.g., `cc`/`gcc`/`clang`)
- `readline` development headers/library

## Build & Run

```bash
make
./minishell
```

### Startup output (intro)

When you start minishell, it prints an intro banner:

```text
$ ./minishell

     . . . . . .    
  ..         42..
 ..             ..
.     .. ..      ..
..   .      .    ..
..   .   .   .   ..
 ..    ..    .   ..
  ..        .    .
    .. .. ..    ..

 oh my Minishell!
 ---------------
```

> The real output is colorized in the terminal (ANSI escape codes). The block above shows the same text without colors.

## Makefile targets

```bash
make        # build
make all    # build (same as `make`)
make clean  # remove object files
make fclean # remove objects and executable
make re     # full rebuild

make val    # run minishell under valgrind (as configured in Makefile)
make val2   # alternative valgrind run (as configured in Makefile)
make reval  # rebuild then run valgrind
make gen_supp # generate suppression file from valgrind log
make bash   # run bash under valgrind

make leaks  # macOS: run leaks tool
make releaks # macOS: rebuild then run leaks

make resan  # rebuild with ASAN enabled (D=1) then run
make san    # run minishell

make ls     # list directory contents
```

### AddressSanitizer builds

The Makefile uses a toggle variable `D`:

```bash
make re D=1
```

## Usage

Interactive mode:

```bash
./minishell
```

Single command mode (no prompt):

```bash
./minishell -c "echo hello"
```

Help:

```bash
./minishell -h
```

## Notes
- Some targets are OS-specific (e.g., `leaks` is macOS-only; Linux typically uses valgrind).
- If you find a bug, open an issue with the exact command and output.