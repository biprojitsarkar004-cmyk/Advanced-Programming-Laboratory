#  0714 02 CSE 2100

Documentation: Code Quality Improvements
1. Modularization of Code

The improved version of the code will follow a modular design approach by logically separating functionality into well-defined sections. Instead of writing all logic in a single continuous flow, the program will be divided into independent modules such as:

Utility functions (string comparison, path handling)

File searching logic

Result handling

GUI event handling

Window procedure and application entry point

Each module will be responsible for a specific task. This modularization will improve readability and maintainability, and it will make the code easier to extend or debug in the future. Logical grouping will allow developers to understand the program structure quickly without reading the entire codebase.

2. Clear Function Responsibility

Every function in the improved code will follow the single responsibility principle, meaning each function will perform only one well-defined task.

Examples:

String comparison functions will handle only case-insensitive comparisons.

Path-related functions will construct valid file paths.

Search functions will perform directory traversal and matching.

GUI handler functions will respond only to user actions such as clicking buttons.

This separation will ensure that changes in one part of the system will not unintentionally affect other parts. It will also simplify testing and debugging because each function will have a clear and predictable behavior.

3. Consistent Naming Conventions

The improved code will use consistent and meaningful naming conventions throughout the program:

Function names will clearly describe their purpose (e.g., search_directory, handle_search).

Global variables will use a clear prefix to indicate shared application state.

Constants will be written in uppercase to distinguish them from variables.

Identifiers will follow a uniform style, avoiding ambiguity or mixed naming patterns.

Consistent naming will improve code readability and will reduce confusion, especially when multiple developers will work on the same codebase or when the code will be reviewed later.

4. Improved Error Handling

The improved version will include better validation and error handling at critical points:

User inputs will be validated before performing file system operations.

Invalid directories and empty inputs will be detected early.

Appropriate error messages will be shown to the user using dialog boxes.

File system operations will be safely checked before proceeding.

This will prevent unexpected behavior, will improve program stability, and will provide clear feedback to the user instead of allowing silent failures or crashes.

5. Use of Header Files (Conceptual Design)

Although the program will be implemented in a single source file, it will be structured in a way that will allow easy separation into header (.h) and source (.c) files.

Conceptually:

Function declarations will be placed in header files.

Implementation details will remain in source files.

Constants and shared structures will be declared centrally.

This design approach will improve scalability and will align with professional C programming practices, even if physical header files will not be used in this version.

6. Encapsulation

Encapsulation will be achieved by limiting direct access to internal logic and data:

Helper functions will be declared as static, restricting their scope to the current file.

Global variables will be minimized and controlled.

Internal implementation details will be hidden from other parts of the program.

This will ensure that internal components will not be misused unintentionally and that the program’s behavior will remain predictable. Encapsulation will also help prevent naming conflicts and will improve overall code safety.
