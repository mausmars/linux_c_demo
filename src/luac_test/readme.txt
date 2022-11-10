直接下载Release包
https://luabinaries.sourceforge.net/
https://sourceforge.net/projects/luabinaries/files/5.3.6/Linux%20Libraries/

liblua5.3-dev


gcc luac_test1.c -I/mnt/e/work/git_src/lua_lib/lua-5.3.6_Linux44_64_lib/include -L/mnt/e/work/git_src/lua_lib/lua-5.3.6_Linux44_64_lib -llua53 -o luac_test1
gcc luac_test1.c -I/mnt/e/work/git_src/lua_lib/lua-5.3.6_Linux50_64_lib/include -L/mnt/e/work/git_src/lua_lib/lua-5.3.6_Linux50_64_lib -llua53 -o luac_test1


gcc luac_test1.c -I/mnt/e/work/git_src/lua -L/mnt/e/work/git_src/lua -llua -static -o luac_test1


./luac_test1

gcc -o luac_test2 luac_test2.c -I/mnt/e/work/git_src/lua
./luac_test2


gcc  luac_test3.c  -I/mnt/e/work/git_src/lua -L/mnt/e/work/git_src/lua -static -o luac_test3







