# minishell

## Project description:
Recreate a simple shell - group project with [Micaela Rollo](https://github.com/micarollo)

Shell functionalities:
- Displays a prompt when waiting for a new command
- Has a working history
- Searches and launches the right executable
- Handles ’  which should prevent the shell from interpreting the meta- characters in the quoted sequence
- Handles "  which should prevent the shell from interpreting the meta- characters in the quoted sequence except for $
- Implements redirections
- Implements pipes
- Handles environment variable which should expand to their values
- Handles $? which should expand to the exit status of the most recently executed foreground pipeline
- Handles ctrl-C, ctrl-D and ctrl-\ which should behave like in bash
- Has implemented builtins:
  - echo with option -n
  - cd with only a relative or absolute path\
  - pwd with no options
  - export with no options
  - unset with no options
  - env with no options or arguments
  - exit with no options

## Grade
100%

## Usage

```make```\
```./minishell```
