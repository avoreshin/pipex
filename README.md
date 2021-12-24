# pipex
pipex42_21 - begin 24.12.2021

План
1) Написать программу Pipex.
2) Список рекомендуемых (разрешенных) функций. <br>
      ◦ access <br>
      ◦ open <br>
      ◦ unlink <br>
      ◦ close <br>
      ◦ read <br>
      ◦ write <br>
      ◦ malloc <br>
      ◦ waitpid <br>
      ◦ wait <br>
      ◦ free <br>
      ◦ pipe <br>
      ◦ dup <br>
      ◦ dup2 <br>
      ◦ execve <br>
      ◦ fork <br>
      ◦ perror <br>
      ◦ strerror <br>
      ◦ exit <br>
3)  Цель - написать программу Pipex.Это должно быть выполнено таким образом:
``` shell
$> ./pipex file1 cmd1 cmd2 file2 
```
Выполнение программы pipex должно выполняться так же, как следующая команда оболочки:
``` shell
$> < file1 cmd1 | cmd2 > file2
```
```shell
> ./pipex infile ``ls -l'' ``wc -l'' outfile
```
должно быть таким же, как “< infile ls -l | wc -l > outfile”
``` shell
$> ./pipex infile ``grep a1'' ``wc -w'' outfile
```
должно быть таким же, как “< infile grep a1 | wc -w > outfile”


# ПРОПАСТЬ


2) Сдать