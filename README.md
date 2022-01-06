# pipex
pipex42_21 - begin 24.12.2021

##План
1) Написать программу Pipex.
2) Список рекомендуемых (разрешенных) функций. <br>
      ◦ [access](https://linux.die.net/man/2/access) проверяет права реального пользователя для файла <br>
      ◦ [unlink](https://man7.org/linux/man-pages/man2/unlink.2.html) удаляет имя из файловой системы <br>
      ◦ [close](https://linux.die.net/man/2/close) закрывает файловый дескриптор <br>
      ◦ read <br>
      ◦ write <br>
      ◦ malloc <br>
      ◦ [wait, waitpid](https://man7.org/linux/man-pages/man2/wait.2.html) ждет завершения дочернего процесса <br>
      ◦ free <br>
      ◦ [pipe](https://man7.org/linux/man-pages/man2/pipe.2.html) создает pipe, однонаправленный канал для передачиданных <br>
      ◦ [dup, dup2](https://man7.org/linux/man-pages/man2/dup.2.html) дублировать дескриптор файла <br>
---
   [execve](https://man7.org/linux/man-pages/man2/execve.2.html) выполняет программу, на которую указывает путь <br>
``` c
int execve (const char *pathname, char *const argv [], char * const envp []);
 - pathname "путь где находится команда"
 - argv [] "команда с флагами"
 - envp [] "переменное окружение"
```
---
◦ [fork](https://man7.org/linux/man-pages/man2/fork.2.html) создает дочерний процесс <br>
``` c
#include <sys/types>
#include <unistd.h>
pid_t fork(void);
```

◦ [perror]() распечатать сообщение об ошибке системы <br>
◦ [strerror](https://man7.org/linux/man-pages/man3/strerror.3.html) возвращает строку, описывающую номер ошибки <br>
◦ [exit](https://man7.org/linux/man-pages/man3/exit.3.html) завершение процесса <br>
3) Цель - написать программу Pipex.Это должно быть выполнено таким образом:
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


