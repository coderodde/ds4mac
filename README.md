# ds4linux
A small *nix command line utility for tagging the directories and `chdir`'ing through them via tags.

### Installation

In order to install `ds4mac`, `git clone` the repository in your directory for `ds`. Then:

    chmod 500 installer.sh
    ./installer.sh
    
The above commands will add the following to your `~/.ds` directory:

1. Compile and copy to the engine,
2. Create the bash script,
3. Create the plain text file `tags` containing all initial tags; you can edit it in order to manipulate the tags. 

### Usage screnarios

    ds -l # list the tags only
    ds -L # list both the tags and their respective directories
    ds -s # list the tags only, sorted alphabetically
    ds -S # list both the tags and their respective directories, sorted alphabetically by tags
    ds -d # list both the tags and their respective directories, sorted alphabetically by directories
    
    ds tag 
