#!/bin/bash
Error() {
    echo "[ERROR]:"
    echo "|    [-] $1"
}
Log() {
    echo "|    $1"
}
Healthy() {
    echo "|    [+] $1"
}
Title() {
    echo "===== Cake2k ====="
}
Step() {
    echo "[STEP - $1]"
}
Info() {
    echo "[INFO]"
}
Warn() {
    echo "[WARNING]"
    echo "|    [!] $1"
}