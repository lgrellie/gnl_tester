# gnl_tester

This is a project by @lgrellie, i.e. Léonard Grellier.

It was designed to test 42's Get Next Line project (pdf in repo).

This is a simple diff tester. It does not check the norm, forbidden functions, or bonuses.

Simply paste your .c and .h files in the base directory and execute ./run_tests X where X is the desired BUFFER_SIZE. My advice is to test it with BUFFER_SIZE = 1 through 8, and with large values.

I also provide a simple random test generator script. Feel free to edit it and/or make it more complete.

Some simple tests are provided.

If your output differs from the test files, information on the diffs will be found in ./diffs

Good luck :)
