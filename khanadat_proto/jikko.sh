#!/bin/bash
set -e

CFLAGS="-Wall -Wextra -Werror -I incs"
OUT="test"

if [ $# -lt 1 ]; then
	echo "Usage: $0 <src.c ...> [-o file_name]" >&2
	exit 1
fi

SRC=()
while [[ $# -gt 0 ]]; do
	case "$1" in
		-o) shift; OUT="$1" ;;
		*) SRC+=("$1") ;;
	esac
	shift
done

cc $CFLAGS "${SRC[@]}" -o "$OUT"