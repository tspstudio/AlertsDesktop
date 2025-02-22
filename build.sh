if [ ! -f Makefile ]; then
    cmake build .
fi

make && ./AlertsDesktop