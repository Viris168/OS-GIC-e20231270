
# Lab 2 - Linux Navigation and File Management, individual report

Copy this template to lab2/README.md in your own course repository.

- Student name/ID - Sok Vireak / e20231270
- Ubuntu username - gic-sok-vireak
- My values (oslab values lab2) - file1 = cash flow.txt, file2 = payroll may.txt, owner = Legal, reader = HR, third = Engineering
- Files - evidence/paths.txt, evidence/tree.txt, evidence/checkpoint.txt

## What I Did

| Step | My command | Current folder when I ran it |
|---|---|---|
| Move the first file (relative destination) | mv 'cash flow.txt' ../reports/ | lab2/incoming |
| Move the second file (absolute paths) | mv "$OSLAB_WORKSPACE/lab2/incoming/payroll may.txt" "$OSLAB_WORKSPACE/lab2/reports/" | lab2 |
| Read the report from my reader department (relative path) | (copy this command from evidence/paths.txt) | (the folder in your prompt) |
| The path error I made on purpose, and its message | mv 'cash flow.txt' reports/ gave mv: cannot move 'cash flow.txt' to 'reports/': Not a directory | lab2/incoming |
| The relative path that fixed it | ../reports/ | lab2/incoming |

## Explanation

A correct file name can still give "No such file or directory" because the shell looks for the name starting from the folder I am standing in, not from where the file really is. When I used reports/ from inside incoming, the shell looked for incoming/reports, which does not exist, so I needed ../reports/ to go up one level first. mv moves a file, so payroll may.txt left incoming and now exists only in reports. cp makes a second copy and leaves the original, so cash flow.txt exists in both reports and TechCorp/Legal.

## What My Tests Do Not Prove

ls shows that a file name is present in a folder, but not what is inside the file. cmp shows that two files have the same content, but not that the copy is in the right place or that I used the right command.

## Plus / Challenge (only if you did them)

(Write your one-command move and the number of .., or your wildcard answers.)

## AI Note (optional)

I tested the quoting advice with ls -l "incoming/$file1" and ls -l incoming/$file1. The unquoted version split cash flow.txt into cash and flow.txt, which confirmed that the quotes are needed.
