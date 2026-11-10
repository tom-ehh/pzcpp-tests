"""Pack exercise solutions into <repo-name>.tar.gz for the teacher.

Usage (from anywhere):  uv run pack.py   or   python pack.py

Packs lab/cmake/ and every topic folder under lab/ that contains an exercise
(a CMakeLists.txt next to src/ or tests/), keeping repo paths so each exercise builds with
`cmake -S lab/<topic>/... -B build`. Notebooks, demos and build output are skipped.
"""

import tarfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent
LAB = ROOT / "lab"
SKIP_DIRS = {"demos", "_deps", ".ipynb_checkpoints"}


def skipped(path: Path) -> bool:
    parts = path.relative_to(LAB).parts
    return (
        path.suffix == ".ipynb"
        or any(p in SKIP_DIRS or p.startswith("build") or p.startswith("cmake-build") for p in parts)
    )


def is_exercise(cmake_file: Path) -> bool:
    d = cmake_file.parent
    return ((d / "src").is_dir() or (d / "tests").is_dir()) and not skipped(cmake_file)


topics = sorted(
    {LAB / f.relative_to(LAB).parts[0] for f in LAB.rglob("CMakeLists.txt") if is_exercise(f)}
    - {LAB / "cmake"}
)
if not topics:
    raise SystemExit("No exercises found under lab/")

files = sorted(
    f
    for d in [LAB / "cmake", *topics]
    for f in d.rglob("*")
    if f.is_file() and not skipped(f)
)

out = ROOT / f"{ROOT.name}.tar.gz"
with tarfile.open(out, "w:gz") as tar:
    for f in files:
        name = f.relative_to(ROOT).as_posix()
        tar.add(f, arcname=name)
        print(name)
print(f"\n{len(files)} files -> {out.name}")
