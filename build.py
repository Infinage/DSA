import os
import subprocess
import glob

def get_output_path(input_path: str) -> tuple[str, str, str]:
    fp_split = input_path.split(os.path.sep)
    dir_ = "./views/" + "/".join(fp_split[:-1])
    fname = fp_split[-1] + ".md"
    return os.path.join(dir_, fname), dir_, fname

def exec_command(command: str) -> str:
    p = subprocess.Popen(command.split(), stdout=subprocess.PIPE)
    op = p.stdout.read().decode('utf-8') if p.stdout else ''
    return op

# Only build the changed files
print(f"Using .git from the volume: {exec_command('git config --global --add safe.directory /data')}")

# Modify only the changed files
diff_output = exec_command("git diff --name-status origin/main~1 origin/main")
for line in diff_output.split("\n"):
    if ".ipynb" in line:
        print (f"\nDiff line: {line}")
        mode, *file_changes = line.split()
        mode = mode[0]
        for inp_path in file_changes:
            op_path, op_dir, op_fname = get_output_path(inp_path)
            print (f"\nInput path: {inp_path}\nOutput Directory: {op_dir}\nOutput FP: {op_path}")
            if os.path.exists(op_path):
                print (f"Deleting view: {op_path}")
                os.remove(op_path)
            if os.path.exists(inp_path):
                os.makedirs(op_dir, exist_ok=True)
                print (f"Creating view for: {inp_path}")
                command = f"pandoc {inp_path} -s -t gfm -o {op_path}"
                print (f"Command: {command}")
                output = exec_command(command)
                print(f"Command Output: {output}")

# Build missing views somehow not in git history
files = glob.glob("**/*.ipynb", recursive=True)
views: set[str] = set()
for inp_path in files:
    op_path, op_dir, op_fname = get_output_path(inp_path)
    views.add(op_path)
    if not os.path.exists(op_path):
        os.makedirs(op_dir, exist_ok=True)
        print (f"\nCreating view for missing file: {inp_path}")
        command = f"pandoc {inp_path} -s -t gfm -o {op_path}"
        print (f"Command: {command}")
        output = exec_command(command)
        print(f"Command Output: {output}")

# Print empty line for legibility
print()

# Prune missing files that somehow have a view
views_present = set(glob.glob("./views/**/*.ipynb.md", recursive=True))
views_to_prune = set.difference(views_present, views)
for op_path in views_to_prune:
    print (f"Pruning view not in VCS: {op_path}")
    os.remove(op_path)

# Prune empty directories
print("Pruning empty directories, output:", exec_command("find ./views -type d -empty -print -delete"))
