import os
import subprocess
import sys
import venv

def run(cmd, check=True):
    print("$", " ".join(cmd))
    return subprocess.run(cmd, check=check)

def create_venv(path):
    if os.path.isdir(path):
        print(f"{path} already exists — skipping venv creation.")
        return
    
    print(f"Creating virtual environment at {path}...")
    builder = venv.EnvBuilder(with_pip=True)
    builder.create(path)

def venv_python(path):
    if os.name == "nt":
        return os.path.join(path, "Scripts", "python.exe")
    return os.path.join(path, "bin", "python")

def install_requirements(py):
    try:
        run([py, "-m", "pip", "install", "--upgrade", "pip"])
    except subprocess.CalledProcessError:
        print("Warning: pip upgrade failed, continuing...")

    req = "requirements.txt"

    if os.path.exists(req):
        try:
            run([py, "-m", "pip", "install", "-r", req])
        except subprocess.CalledProcessError:
            print("Warning: pip install returned non-zero exit code.")

    else:
        print("No requirements.txt found — skipping pip install.")

def make_dirs(dirs):
    for d in dirs:
        if not os.path.isdir(d):
            os.makedirs(d, exist_ok=True)
            print(f"Created directory: {d}")
        else:
            print(f"Directory exists: {d}")

def main():
    root = os.getcwd()
    print(f"Running setup in: {root}")

    venv_path = os.path.join(root, ".venv")
    create_venv(venv_path)

    py = venv_python(venv_path)

    if not os.path.exists(py):
        print("Error: python executable not found inside .venv. Exiting.")
        sys.exit(1)

    install_requirements(py)

    base_dirs = ["src", "data", "data/raw", "data/separated"]
    make_dirs(base_dirs)

    if os.name == "nt":
        activate = r".venv\\Scripts\\Activate.ps1"
        print("\nTo activate the venv in PowerShell:")
        print(f"  . {activate}")
    else:
        print("\nTo activate the venv (POSIX):")
        print("  source .venv/bin/activate")

if __name__ == "__main__":
    main()
