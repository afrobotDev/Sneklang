#!/usr/bin/env bash
# runc.sh — compile & run any .c with one command.
#
#   scripts/runc.sh <file.c> [extra.c ...]
#
# * file has main()            -> compiles and runs it
# * file is a library module   -> looks for a same-dir .c that includes
#                                 its header and defines main(), and
#                                 compiles the two together
# * neither                    -> compile with explicit extra sources
#
# Exit status is the program's exit status.
set -u
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"

if [ $# -lt 1 ]; then
    echo "usage: $0 <file.c> [extra.c ...]" >&2
    exit 2
fi

SRC="$1"; shift
OUT="$(mktemp "${TMPDIR:-/tmp}/snkrun_XXXXXX")"
trap 'rm -f "$OUT"' EXIT

run() {  # compile args... -> run
    gcc -Wall -Wextra -std=c11 -I. -o "$OUT" "$@" || exit 1
    "$OUT"
}

# Case 1: direct compile
if grep -qE 'int[[:space:]]+main' "$SRC" 2>/dev/null; then
    run "$SRC" "$@"
    exit $?
fi

# Case 2: library module — find demo main in same dir ( basename match basename basename )
base="$(basename "$SRC" .c)"
demo="$(dirname "$SRC")"/*.c
for cand in $demo; do
    [ "$cand" = "$SRC" ] && continue
    if grep -q "#include.*${base}.h" "$cand" 2>/dev/null \
       && grep -qE 'int[[:space:]]+main' "$cand" 2>/dev/null; then
        echo "[runc] $SRC has no main; driver: $cand" >&2
        run "$SRC" "$cand" "$@"
        exit $?
    fi
done

echo "[runc] no main() in $SRC and no demo file found in $(dirname "$SRC")" >&2
echo "[runc] pass extra sources explicitly:" >&2
echo "[runc]   scripts/runc.sh $SRC <driver.c>" >&2
exit 1
