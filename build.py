import glob
import os
import subprocess

def get_fname(input_path: str) -> str:
    fp_split = input_path.split(os.path.sep)
    return fp_split[-1]

def get_output_path(input_path: str) -> list[str]:
    fp_split = input_path.split(os.path.sep)
    dir_ = "./views/" + "/".join(fp_split[1:-1])
    fname = fp_split[-1] + ".md"
    return os.path.join(dir_, fname), dir_, fname

def exec_command(command: str) -> str:
    p = subprocess.Popen(command.split(), stdout=subprocess.PIPE)
    op = p.stdout.read().decode('utf-8')
    return op

# Only build the changed files
print(f"Using .git from the volume: {exec_command('git config --global --add safe.directory /data')}")

# Get list of all files
files = glob.glob("./**/*.ipynb", recursive=True)
print (f"Total of {len(files)} files detected.")

# List of all IPYNB files modified in the latest commit
files_modified = filter(lambda x: x[-6:] == ".ipynb", exec_command("git diff --name-only origin/main origin/main~1").split("\n"))
files_modified = set(map(get_fname, files_modified))
print (f"Total of {len(files_modified)} IPYNB file changes were detected.\n")

for inp_path in files:
    op_path, op_dir, op_fname = get_output_path(inp_path)
    print(f"Input Path: {inp_path}")
    print(f"Output Directory: {op_dir}, Output File Path: {op_path}")
    os.makedirs(op_dir, exist_ok=True)

    if get_fname(inp_path) in files_modified:
        print ("File changes detected to this file. View would be rebuilt.")
        if os.path.exists(op_path):
            os.remove(op_path)
            print ("Existing view deleted.")
        command = f"pandoc {inp_path} -s -t gfm -o {op_path}"
        print (f"Command: {command}")
        output = exec_command(command)
        print(f"Command Output: {output}\n")

    else:
        print ("No file changes detected to this file. View building would be skipped.\n")
