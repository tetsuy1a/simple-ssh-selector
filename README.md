# Simple SSH Selector

![for Windows](https://img.shields.io/badge/for-Windows-blue)

A simple TUI application that reads `Host` entries from `~/.ssh/config`, lets you select one from a list, and connects via SSH.

## ⚙️ Features

- Automatically parses and lists `Host` entries (supports multiple hosts per line)
- Navigate with arrow keys and connect instantly—no need to type `ssh` commands

## 💻 Requirements

- Windows 10 / 11
- OpenSSH (`ssh` must be available in PATH)

## 🛠️ Build

Confirmed to compile with MinGW-w64.

```bash
gcc ssh_selector.c -o ssh_selector.exe
````

Given its simplicity, it should work with other compilers as well (not tested).

## ▶️ Usage

1. Prepare `C:\Users\<YourUser>\.ssh\config`
2. Run the built executable

```bash
ssh_selector.exe
```

### ⌨️ Controls

* ↑ / ↓ : Select host
* Enter : Connect via SSH
* q : Quit

## 📄 Supported `config` syntax

* `Host web1`
* `Host web1 web2`

*Note: `Host *` and wildcard entries are ignored.*

## ⚠️ Known Limitations

* `Include` directive is not supported
* Does not display detailed fields such as `HostName`, `User`, or `Port`
* No scrolling support for very large host lists

## 📜 License

This software is released under the MIT License. See the included `LICENSE` file for details.
