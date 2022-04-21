apt-get install autoconf-archive

git clone git@github.com:tlwg/libdatrie.git
cd libdatrie
git checkout v0.2.13

git reset --hard HEAD^


./autogen.sh
./configure
make
make install


trietool-0.2 test add abcd






