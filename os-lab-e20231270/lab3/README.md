# Lab 3 — Wildcards, Hard Links and Symbolic Links: individual report

- Student name/ID: Sok Vireak / e20231270
- Ubuntu username: gic-sok-vireak
- My values (`oslab values lab3`): name = candle, tag = saved, v1 = 887, v2 = 940
- Files: `evidence/wildcards.txt`, `evidence/links.txt`, `evidence/replacement.txt`, `evidence/checkpoint.txt`

## What I Saw

| State | What `cat` printed for the hard link | What `cat` printed for the symbolic link | What `readlink` printed |
|---|---|---|---|
| Before the rename | version 887 | version 887 | candle.txt |
| After the rename, before the repair | version 887 | No such file or directory | candle.txt |
| After a new file took the old name | version 887 | version 940 | candle.txt |
| After my repair | version 887 | version 887 | candle-saved.txt |

My repair (the two commands I wrote):

    rm -- "$name-soft.txt"
    ln -s "$name-$tag.txt" "$name-soft.txt"

## Explanation

The hard link candle-hard.txt points to inode 19142150, the same inode as my original report, so renaming the report to candle-saved.txt did not change what it reads: it still printed version 887. The symbolic link only stores the name candle.txt, so after the rename it was dangling. When a new candle.txt was created with version 940, it got a new inode (NEW_INODE), and the symbolic link followed the name to this new file instead of my original data. The result that surprised me was ________.

## What My Tests Do Not Prove

`cat` only shows the content, so two different files with the same text would look the same. Only `ls -li` shows the inode numbers, which prove whether two names are really the same file.

## Plus / Challenge (only if you did them)

Challenge: with three names the link count was 3; after `rm one.txt` it was 2, and after `rm two.txt` it was 1. The data was not gone after deleting one.txt; it is freed only when the last name is removed and no program has the file open.

## AI Note (optional)

An AI tool suggested `notes/.*.txt` as the middle wildcard command. I tested it with `oslab check lab3`, which failed and said the line must be `notes/candle?.txt`. I changed it and the check passed.

