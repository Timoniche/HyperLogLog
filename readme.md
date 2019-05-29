# Описание
- **HLL** - HyperLogLog algorithm,
[wikipedia](https://en.wikipedia.org/wiki/HyperLogLog )
[habr](https://habr.com/ru/post/119852/)
[different ways](http://www.cs.cmu.edu/afs/cs/user/dwoodruf/www/project.pdf)
- [FNV](https://ru.wikipedia.org/wiki/FNV)
-  HLL - description of variables in .h
-- increase _boost_m to decrease relative error
-- increase THREADS_NUMBER if data is too long (analyse_portion method)
-  main - console utility
-- [-f] [input.txt] [output.txt]