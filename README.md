# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

The longest word in a dictionary, 45 symbols long

## According to its man page, what does `getrusage` do?

getrusage() returns resource usage measures for who, which can be one of the following:

       RUSAGE_SELF
              Return resource usage statistics for the calling process, which is the sum of resources used by all threads in the process.

       RUSAGE_CHILDREN
              Return  resource usage statistics for all children of the calling process that have terminated and been waited for.  These statistics
              will include the resources used by grandchildren, and further removed descendants, if all of the intervening  descendants  waited  on
              their terminated children.

       RUSAGE_THREAD (since Linux 2.6.26)
              Return resource usage statistics for the calling thread.

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

TODO idk

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convinceus that you indeed understand how that function's `for` loop works.

The loop executes only if the character is not EOF, then increments c with the next character in file. Only if the character got by fgetc is
alphabetical or it is apostrope (but not first character in the word), the character is apended to the word. Index is then incremented
Then it is checked if index of word is already longer than the longest word possible or it is numerical, if so fgetc is used until EOF is reached or while
alphabetical characters are being found.

If all the above conditions are not true, then we found a whole word in which case we terminate it with \0, increment the word counter and only then
start checking the spelling of the word with the help of check(). Statistic about time for check is calculated and if checked word is mispelled
it is printed.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

If fscanf consumes a whole string at a time there might be numerical or other unwanted symbols in the string, also fgetc returns the
character casted as int, while fscanf returns value of strings matching the format- e.g. fgets stores the character, while fscanf doesn't.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

The functions are not supposed to amend the values of the parameters.
