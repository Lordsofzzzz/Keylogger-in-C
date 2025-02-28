# 🔑 Keylogger in C

## 📌 Description
This project is a simple **keylogger** implemented in C using the **Windows API**. It captures keystrokes and logs them to a file (`log.txt`). The program runs in the background without a visible console window.

## ⚡ Features
- ✅ **Logs all keystrokes**, including special keys (Enter, Backspace, Shift, etc.).
- ✅ **Timestamps each keystroke** for better tracking.
- ✅ **Runs in the background** by hiding the console window.
- ✅ **Optimized file handling** (log file remains open to reduce I/O overhead).
- ✅ **Closes log file properly on exit** to prevent corruption.

## 🚀 How to Compile & Run
### **🔹 Compilation**
Use **MinGW** or any C compiler supporting the Windows API:
```sh
gcc keylogger.c -o keylogger.exe -mwindows
```
The `-mwindows` flag prevents a console window from appearing.

### **🔹 Running the Keylogger**
Simply execute:
```sh
keylogger.exe
```
The keylogs will be stored in `log.txt`.

## 🔒 Disclaimer
This project is for **educational purposes only**. Unauthorized use of keyloggers to capture user input without consent is **illegal**. Use this project **only for ethical hacking, penetration testing, and cybersecurity learning**.

## 🛠 Future Enhancements
- 🔹 Encrypt log file to enhance security.
- 🔹 Send logs remotely via email or a server.
- 🔹 Add stealth techniques to bypass detection.

---
💻 **Developed for cybersecurity research & ethical hacking.** 🚀

