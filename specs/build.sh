#!/bin/bash

# Collect rbs blocks and save them to files
collect_rbs() {
	file=$1
	out=$2

	in_block=false
	rbs_out=false
	count=0
	while IFS= read -r line; do
		if [[ "$line" =~ ^\`\`\`rbs$ ]]; then
			in_block=true
			rbs_out="$out/block$count.rbs"
			count=$((count+1))
		elif [[ "$line" =~ ^\`\`\`rbs:([a-z0-9_]+)$ ]]; then
			in_block=true
			rbs_out="$out/${BASH_REMATCH[1]}.rbs"
			if [[ -f $rbs_out ]]; then
				echo "Warning: block with id \`${BASH_REMATCH[1]}\` already seen."
			fi
		elif [[ "$line" =~ ^\`\`\`$ ]] && $in_block; then
			in_block=false
			rbs_out=false
		elif $in_block; then
			echo "$line" >> $rbs_out
		fi
	done < "$file"
}

translate() {
	cmd=$1
	out=$2

	for file in "$out"/*.rbs; do
		base=$(basename -- "$file")
		name=${base%.*}

		if ! "$cmd" "$file" > "$out/$name.rbi" 2> "$out/$name.err"; then
			echo "Error: Can't translate RBS \`$name\`."
			echo "\`\`\`rbs"
			cat "$file"
			echo "\`\`\`"
			cat "$out/$name.err"
			exit 1
		fi

		# TODO also test with Sorbet?
	done
}

render() {
	file=$1
	out=$2

	while IFS= read -r line; do
		if [[ "$line" =~ ^\[\[rbi:([a-z_]+)\]\]$ ]]; then
			rbi="$out/${BASH_REMATCH[1]}.rbi"
			if [[ ! -f $rbi ]]; then
				echo "Error: no RBS for \`${BASH_REMATCH[1]}\`."
				exit 1
			fi
			echo "\`\`\`rbi"
			sed '1,2d' < "$rbi"
			echo "\`\`\`"
		else
			echo -e "$line"
		fi
	done < "$file"
}

if [ $# -ne 2 ]; then
    echo "Error: wrong arguments supplied."
    echo "Usage: test.sh <cmd> <README.src>"
    exit 1
fi

cmd=$1
readme=$2

if [ ! -f "$readme" ]; then
	echo "Error: File \`$readme\` not found."
	exit 1
fi

out="tmp"
rm -rf "$out"
mkdir -p "$out"

collect_rbs "$readme" "$out"
translate "$cmd" "$out"
render "$readme" "$out"
