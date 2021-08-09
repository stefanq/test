# Coding Assignment (Embedded Intent Recognizer)

Build a simple small intent recognition command line tool.
In:

* What is the weather like today? => Prints (Intent: Get Weather)
* What is the weather like in Paris today? => Prints (Intent: Get Weather City)
* Tell me an interesting fact. => Prints (Intent: Get Fact)

Basic:

* It has to be buildable with cmake (using C++):
* The commands: `mkdir build && cmake ..  && make` would build the application
* It is developed using git and pushed to <https://github.com/.>.
  * We should be able to just clone it and build it (using the commands above).
* It uses modern C++.

Advanced:

* It has unit tests (Catch2, Google Test, or any other framework).
* It has good commit messages.

Very Advanced:

* A lot of plus points if it can handle different semantic variations.