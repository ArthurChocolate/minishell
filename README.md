# minishell
Status: Completed </br>
Score: 100/100 </br>
Retries: 0

The first group project, the purpose of which is to gain team experience working on a single project, as well as an in-depth understanding of bash. </br>

Shell should:</br>
• Display a prompt when waiting for a new command.</br>
• Have a working history.</br>
• Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).</br>
• Not use more than one global variable. Think about it. You will have to explain its purpose.</br>
• Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).</br>
• Handle ’ (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.</br>
• Handle " (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign).</br>
• Implement redirections:</br>
1) "<" should redirect input.</br>
2) ">" should redirect output.</br>
3) "<<" should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!</br>
4) ">>" should redirect output in append mode.</br>

• Implement pipes (| character). The output of each command in the pipeline is connected to the input of the next command via a pipe.</br>
• Handle environment variables ($ followed by a sequence of characters) which should expand to their values.</br>
• Handle $? which should expand to the exit status of the most recently executed foreground pipeline.</br>
• Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.</br>
• In interactive mode:</br>
1) ctrl-C displays a new prompt on a new line.</br>
2) ctrl-D exits the shell.</br>
3) ctrl-\ does nothing.</br>

• Your shell must implement the following builtins:</br>
1) "echo" with option -n</br>
2) "cd" with only a relative or absolute path</br>
3) "pwd" with no options</br>
4) "export" with no options</br>
5) "unset" with no options</br>
6) "env" with no options or arguments</br>
7) "exit" with no options</br>
