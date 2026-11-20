# Lab 4 — Redirection and Pipelines: individual report

Follow the [instruction](lab4-instruction.md). Copy this template into your own `lab4/README.md`. No script is required. Prediction/debrief/checkpoint answers stay in `oslab` records.

- Name / student ID: Sok Vireak / e20231270
- Linux account: gic-sok-vireak
- Personal status and other word: status=ok, other=paid

## Commands I Used

Save your actual commands, one per line, in `evidence/commands.txt`. Do not execute that file as a script.

| Stage | My command | Input received | Output produced |
|---|---|---|---|
| Select exact first field | `grep '^ok,' data/events.csv \| tee evidence/selected.txt` | `data/events.csv` lines | 3 matching rows (`ok,6`, `ok,4`, `ok,3`) to screen and `selected.txt` |
| Extract field 2 | `grep '^ok,' data/events.csv \| cut -d, -f2 \| tee evidence/fields.txt` | `data/events.csv` lines | Quantities `6`, `4`, `3` to screen and `fields.txt` |
| Count selected records | `grep '^ok,' data/events.csv \| wc -l > evidence/normal.txt` | `data/events.csv` lines | Single line count `3` saved to `normal.txt` |
| Save stdout and stderr separately | `cat data/missing.csv > evidence/stdout.txt 2> evidence/stderr.txt` | Non-existent file `data/missing.csv` | Empty `stdout.txt` and diagnostic message in `stderr.txt` |
| Save exit status immediately | `echo $? > evidence/status.txt` | Exit status of preceding `cat` command | Nonzero exit code `1` saved to `status.txt` |

## What My Tests Show

| Test | Expected | Observed | Mistake it would catch |
|---|---|---|---|
| Original records | 3 exact matches | 3 | Catches failure to anchor pattern or prefix-matching look-alikes like `ok-late` |
| No match | 0 records | 0 | Catches false positive matches when status word is missing |
| One added match plus a look-alike | 4 records | 4 | Catches counting quantities (summing 7) instead of records (1 row) and matching look-alikes |
| Missing input | empty stdout, diagnostic on stderr, nonzero status | empty stdout, stderr error message, exit status 1 | Catches sending error messages to stdout instead of stderr, or ignoring command failure |

## Explain the Commands

1. Why does the comma in `grep '^WORD,'` matter?
   - The comma ensures an exact match for the first field, preventing `grep` from matching longer words that start with the same prefix (for example, matching `ok-late` when searching for `ok`).

2. Why does `wc -l` count records here, rather than add quantities?
   - `wc -l` counts the number of newline characters (matching lines/records) fed to standard input. It treats lines as text streams and does not parse or sum numerical values in columns.

3. Where did you use `>>`, and what would `>` do instead?
   - I used `>>` when appending the second observation in practice and when appending the count of `data/changed.csv` into `evidence/edge.txt`.
   - `>` would truncate and overwrite the file, losing the first count (0), while `>>` appends to the end and preserves existing contents.

4. What does `tee` do that `>` alone does not?
   - `tee` duplicates standard input to both standard output (displaying it on the screen) and to a specified file simultaneously. `>` only writes to the file silently without displaying on screen.

5. Why must `echo $?` immediately follow the command being checked?
   - The special variable `$?` holds the exit status of the *most recent* foreground command. Running any other command in between (even `ls` or `cat`) overwrites `$?` with that command's status.

6. Why can `cat missing-file | wc -l` report pipeline status 0?
   - In a shell pipeline, `$?` reports the exit status of the *last* command in the pipeline (`wc -l`), not the earlier stages. Because `wc -l` successfully read empty input and printed `0`, its exit status was `0` even though `cat` failed.

## Limits and Evidence

These commands assume simple comma-separated text without quoted commas. Saved results describe one run; they do not prove every future input works or who typed a command.

Check the submission tree in the instruction: include `checkpoint.txt` and all required evidence files, including the empty `stdout.txt`. No `report.sh` is required.

## Optional Work / AI Note

- **Plus:** Tested `grep '^ok,' data/no-match.csv` followed by `echo $?`. It produced no output and exit status `1` (indicating no match found, distinct from error status `2` or missing-file diagnostics).
- **Challenge:** Successfully displayed and saved both streams using `cat data/events.csv data/missing.csv 2>&1 | tee evidence/challenge.txt`. The `2>&1` redirects stderr into stdout before the pipe so that `tee` captures and displays both normal lines and diagnostic errors.
