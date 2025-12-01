# Philosophers
Understand threads

 DRD: Run with valgrind --tool=drd to check for data races.

— Helgrind: Run with valgrind --tool=helgrind to find lock issues and potential deadlocks.

— FSanitise: Compile with -fsanitize=thread to detect threading problems while running.